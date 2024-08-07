/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
//#define KN_DEBUG
#include "tensorflow/lite/micro/ia8201/config.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/dequantize.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/quantize.h"
#include "tensorflow/lite/kernels/internal/reference/requantize.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {
namespace ops {
namespace micro {
namespace dequantize {

struct OpData {
  tflite::DequantizationParams quantization_params;
  // The scaling factor from input to output (aka the 'real multiplier') can
  // be represented as a fixed point multiplier plus a left shift.
  int32_t output_multiplier;
  int output_shift;
  int32_t output_zero_point;

  AScalar scale;
  AScalar zero_point;
  
  // requantize
  //AScalar Requantize;
  //AScalar inZeroPoint;
  //AScalar outZeroPoint;

};

void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data = static_cast<OpData*>(node->user_data);

  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  // TODO(b/140515557): Add cached dequant to improve hybrid model performance.
  const TfLiteTensor* input = GetInput(context, node, 0);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* output = GetOutput(context, node, 0);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE(context, input->type == kTfLiteUInt8 ||
                         input->type == kTfLiteInt8 ||
                         input->type == kTfLiteInt16 ||
  input->type == kTfLiteFloat16);

  TF_LITE_ENSURE(context, output->type == kTfLiteFloat32);

  if (output->type == kTfLiteInt32) {
    const double effective_output_scale =
        static_cast<double>(input->params.scale) /
        static_cast<double>(output->params.scale);
    QuantizeMultiplier(effective_output_scale, &data->output_multiplier,
                       &data->output_shift);
  }

  data->quantization_params.zero_point = input->params.zero_point;
  data->quantization_params.scale = static_cast<double>(input->params.scale);
  data->output_zero_point = output->params.zero_point;

  data->scale = AScalar(data->quantization_params.scale);
  data->zero_point = AScalar(data->quantization_params.zero_point);// / CONST_ASCALAR(128.0); //Q7 for INT8


  return kTfLiteOk;
}

#ifdef DMX1A_DEQUANTIZE_OPT
void DequantizeFloat16ToAFloat32(struct OpData* op_data,
    const RuntimeShape& input_shape,
    const int8_t* input_data,
    const RuntimeShape& output_shape,
    float* output_data)
{
    // tflite::QuantizationParams op_params = op_data->quantization_params;
 //  const int32_t zero_point = op_params.zero_point;
 //  const double scale = op_params.scale;
    const int flat_size = MatchingFlatSize(input_shape, output_shape);

    int loopLim = flat_size >> 2;
    uint8_t* pInput = (uint8_t*)input_data;
    uint32_t* pOut = (uint32_t*)output_data;
    vr128 VR_dataIn;
    vr128 VR_output;
    ulsr128 UR_dataIn = align_16x4_load(pInput);
    ulsr128 UR_out = align_32x4_store(pOut);

    if (loopLim > 0)
    {
        load_16x4_vr_a(VR_dataIn, UR_dataIn, pInput);
        for (int i = 0; i < loopLim - 1; i++) {
            convert_16F_to_32F_x4(VR_dataIn, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
            //VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xf0), 0x0);
            VR_output = vexp_adji(VR_dataIn, 0);
            load_16x4_vr_a(VR_dataIn, UR_dataIn, pInput);
            //convert_32F_to_IEEE_float_x4(VR_output);
            store_32x4_vr_a(VR_output, UR_out, pOut);

        }
        convert_16F_to_32F_x4(VR_dataIn, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
        //VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xf0), 0x0);
        //convert_32F_to_IEEE_float_x4(VR_output);
        store_32x4_vr_a(VR_dataIn, UR_out, pOut);

        flush_32x4(UR_out, pOut);
    }
    // TODO:
    if (flat_size & 3) {
        for (int ii = 0; ii < (flat_size & 3); ii++) {
            load16x1_vr_postI(VR_dataIn, pInput, INC1, VRQ0);
            //convert_16I_to_32F_x4(VR_dataIn, 7);
            //fadds(VR_dataIn, VRQ0, VR_dataIn, VRQ0, VR_zeroPoint, VRQ0, 0x10);
            //fmuls(VR_output, VRQ0, VR_scale, VRQ0, VR_dataIn, VRQ0, 0);
            convert_16F_to_32F_x4(VR_dataIn, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
            //convert_32F_to_IEEE_float_x4(VR_output);
            store32x1_vr_postI(VR_dataIn, pOut, INC1, VRQ0);
        }
    }
}
void DequantizeFloat16ToFloat32(struct OpData* op_data,
    const RuntimeShape& input_shape,
    const TfLiteFloat16* input_data,
    const RuntimeShape& output_shape,
    float* output_data)
{
    // tflite::QuantizationParams op_params = op_data->quantization_params;
 //  const int32_t zero_point = op_params.zero_point;
 //  const double scale = op_params.scale;
    const int flat_size = MatchingFlatSize(input_shape, output_shape);

    int loopLim = flat_size >> 2;
    TfLiteFloat16* pInput = (TfLiteFloat16*)input_data;
    uint32_t* pOut = (uint32_t*)output_data;
    vr128 VR_dataIn;

    vr128 VR_output;
    ulsr128 UR_dataIn = align_16x4_load(pInput);
    ulsr128 UR_out = align_32x4_store(pOut);

    //KN_
    KN_PRINTAFLT(op_data->scale);
    KN_PRINTAFLT(op_data->zero_point);
    if (loopLim > 0)
    {
        load_16x4_vr_a(VR_dataIn, UR_dataIn, pInput);
        for (int i = 0; i < loopLim - 1; i++) {
            convert_16F_to_32F_x4(VR_dataIn, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
            //VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xf0), 0x0);
            VR_output = vexp_adji(VR_dataIn, 0);
            load_16x4_vr_a(VR_dataIn, UR_dataIn, pInput);
            convert_32F_to_IEEE_float_x4(VR_output);
            store_32x4_vr_a(VR_output, UR_out, pOut);
        }
        convert_16F_to_32F_x4(VR_dataIn, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
        //VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xf0), 0x0);
        convert_32F_to_IEEE_float_x4(VR_dataIn);
        store_32x4_vr_a(VR_dataIn, UR_out, pOut);

        flush_32x4(UR_out, pOut);
    }
    // TODO:
    if (flat_size & 3) {
        for (int ii = 0; ii < (flat_size & 3); ii++) {
            load16x1_vr_postI(VR_dataIn, pInput, INC1, VRQ0);
            //convert_16I_to_32F_x4(VR_dataIn, 7);
            //fadds(VR_dataIn, VRQ0, VR_dataIn, VRQ0, VR_zeroPoint, VRQ0, 0x10);
            //fmuls(VR_output, VRQ0, VR_scale, VRQ0, VR_dataIn, VRQ0, 0);
            convert_16F_to_32F_x4(VR_dataIn, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
            convert_32F_to_IEEE_float_x4(VR_dataIn);
            store32x1_vr_postI(VR_dataIn, pOut, INC1, VRQ0);
        }
    }
}
void DequantizeInt8ToFloat32(struct OpData* op_data,
    const RuntimeShape& input_shape,
    const int8_t* input_data,
    const RuntimeShape& output_shape,
    float* output_data)
{
    // tflite::QuantizationParams op_params = op_data->quantization_params;
 //  const int32_t zero_point = op_params.zero_point;
 //  const double scale = op_params.scale;
    const int flat_size = MatchingFlatSize(input_shape, output_shape);

    int loopLim = flat_size >> 2;
    uint8_t* pInput = (uint8_t*)input_data;
    uint32_t* pOut = (uint32_t*)output_data;
    vr128 VR_dataIn, VR_scale;
    vr128 VR_zeroPoint;
    vr128 VR_output;
    ulsr128 UR_dataIn = align_8x4_load(pInput);
    ulsr128 UR_out = align_32x4_store(pOut);
    replicate_ar(VR_scale, 0xf, op_data->scale.fr);
    replicate_ar(VR_zeroPoint, 0xf, op_data->zero_point.fr);

    //KN_
    KN_PRINTAFLT(op_data->scale);
    KN_PRINTAFLT(op_data->zero_point);
    if (loopLim > 0)
    {
        load_8x4_vr_a(VR_dataIn, UR_dataIn, pInput);
        for (int i = 0; i < loopLim - 1; i++) {
            convert_16I_to_32F_x4(VR_dataIn, 7);
            VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xf0), 0x0);
            load_8x4_vr_a(VR_dataIn, UR_dataIn, pInput);
            convert_32F_to_IEEE_float_x4(VR_output);
            store_32x4_vr_a(VR_output, UR_out, pOut);
           
        }
        convert_16I_to_32F_x4(VR_dataIn, 7);
        VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xf0), 0x0);
        convert_32F_to_IEEE_float_x4(VR_output);
        store_32x4_vr_a(VR_output, UR_out, pOut);

        flush_32x4(UR_out, pOut);
    }
    // TODO:
    if (flat_size & 3) {
        for (int ii = 0; ii < (flat_size & 3); ii++) {
            load8x1_vr_postI(VR_dataIn, pInput, INC1, VRQ0);
            convert_16I_to_32F_x4(VR_dataIn, 7);
            fadds(VR_dataIn, VRQ0, VR_dataIn, VRQ0, VR_zeroPoint, VRQ0, 0x10 );
            fmuls(VR_output, VRQ0, VR_scale, VRQ0, VR_dataIn, VRQ0, 0);
            convert_32F_to_IEEE_float_x4(VR_output);
            store32x1_vr_postI(VR_output,  pOut, INC1, VRQ0);
        }
    }
}
#endif

#ifdef HMD1A_DEQUANTIZE_OPT
void DequantizeInt8ToFloat32(struct OpData* op_data,
    const RuntimeShape& input_shape,
    const int8_t* input_data,
    const RuntimeShape& output_shape,
    float* output_data)
{
    // tflite::QuantizationParams op_params = op_data->quantization_params;
 //  const int32_t zero_point = op_params.zero_point;
 //  const double scale = op_params.scale;
    const int flat_size = MatchingFlatSize(input_shape, output_shape);

    int loopLim = flat_size >> 1;
    int remain = flat_size & 1;
    uint8_t* pInput = (uint8_t*)input_data;
    uint32_t* pOut = (uint32_t*)output_data;
    vr64 VR_dataIn, VR_scale;
    vr64 VR_zeroPoint;
    vr64 VR_output;
    //ulsr32 UR_dataIn = align_8x4_load(pInput);
    ulsr32 UR_out = align_32x2_store(pOut);
    replicate_ar(VR_scale, 0x3, op_data->scale.fr);
    replicate_ar(VR_zeroPoint, 0x3, op_data->zero_point.fr);

    //KN_
    KN_PRINTAFLT(op_data->scale);
    KN_PRINTAFLT(op_data->zero_point);
    if (loopLim > 0)
    {
        load8x2_vr_postI(VR_dataIn,  pInput, INC1);
        for (int i = 0; i < loopLim - 1; i++) {
            convert_16I_to_32F_x2(VR_dataIn, 7);
            VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xa), 0x0);
            load8x2_vr_postI(VR_dataIn,  pInput, INC1);
            convert_32F_to_IEEE_float_x2(VR_output);
            store_32x2_vr_a(VR_output, UR_out, pOut);

        }
        convert_16I_to_32F_x2(VR_dataIn, 7);
        VR_output = vmuls(VR_scale, vadds(VR_dataIn, VR_zeroPoint, 0xa), 0x0);
        convert_32F_to_IEEE_float_x2(VR_output);
        store_32x2_vr_a(VR_output, UR_out, pOut);

        flush_32x2(UR_out, pOut);
    }

    if (remain) {
        fr32 fr_dataIn;
        fr32 fr_zeroPoint = get_VRL(VR_zeroPoint);
        fr32 fr_scale = get_VRL(VR_scale);

        load_fr_postI(fr_dataIn, pInput, INC1);
        set_VRL(VR_dataIn, fr_dataIn);

        convert_16I_to_32F_x2(VR_dataIn, 7);
            
        fr_dataIn = fadds(fr_dataIn, fr_zeroPoint,  0x2);//x-y
        fr32 fr_output = fmuls(fr_dataIn, fr_scale,  0);
        set_VRL(VR_output, fr_output);
        convert_32F_to_IEEE_float_x2(VR_output);
        store32x1_vr_postI(VR_output, pOut, INC1, VRQ0);

    }
}
#endif



TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data = static_cast<OpData*>(node->user_data);

  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);

  if (output->type == kTfLiteFloat32) 
  {
    switch (input->type) {
#ifndef REMOVE_REFOP_SUPPORT
      case kTfLiteUInt8:
        reference_ops::Dequantize(data->quantization_params,
                                  tflite::micro::GetTensorShape(input),
                                  tflite::micro::GetTensorData<uint8_t>(input),
                                  tflite::micro::GetTensorShape(output),
                                  tflite::micro::GetTensorData<float>(output));
        break;
#endif
      case kTfLiteInt8:
          KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input), ElementCount(*input->dims));
#if defined(DMX1A_DEQUANTIZE_OPT) || defined(HMD1A_DEQUANTIZE_OPT)
          DequantizeInt8ToFloat32(data,
              tflite::micro::GetTensorShape(input),
              tflite::micro::GetTensorData<int8_t>(input),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<float>(output));
#else
          reference_ops::Dequantize(data->quantization_params,
                                  tflite::micro::GetTensorShape(input),
                                  tflite::micro::GetTensorData<int8_t>(input),
                                  tflite::micro::GetTensorShape(output),
                                  tflite::micro::GetTensorData<float>(output));
#endif
          KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output), ElementCount(*output->dims));
        break;
#ifndef REMOVE_REFOP_SUPPORT
      case kTfLiteInt16:
        reference_ops::Dequantize(data->quantization_params,
                                  tflite::micro::GetTensorShape(input),
                                  tflite::micro::GetTensorData<int16_t>(input),
                                  tflite::micro::GetTensorShape(output),
                                  tflite::micro::GetTensorData<float>(output));
        break;
#endif
      case kTfLiteFloat16:
          KN_PRINT_AFLOAT16(tflite::micro::GetTensorData<TfLiteFloat16>(input),
              ElementCount(*input->dims));
#if defined(DMX1A_DEQUANTIZE_OPT) || defined(HMD1A_DEQUANTIZE_OPT)
          DequantizeFloat16ToFloat32(data,
              tflite::micro::GetTensorShape(input),
              tflite::micro::GetTensorData<TfLiteFloat16>(input),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<float>(output));

#endif
          break;
      default:
        TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                           TfLiteTypeGetName(input->type),
                           TfLiteTypeGetName(output->type));
        return kTfLiteError;
    }
  }
  else if (output->type == kTfLiteAfloat32) {
      // THIS TYPE IS from KN converter
      switch (input->type)
      {
      case kTfLiteFloat16:
          KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input), ElementCount(*input->dims));
#if defined(DMX1A_DEQUANTIZE_OPT) || defined(HMD1A_DEQUANTIZE_OPT)
          DequantizeFloat16ToAFloat32(data,
              tflite::micro::GetTensorShape(input),
              tflite::micro::GetTensorData<int8_t>(input),
              tflite::micro::GetTensorShape(output),
              tflite::micro::GetTensorData<float>(output));

#endif
          break;
      default:
          TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
              TfLiteTypeGetName(input->type),
              TfLiteTypeGetName(output->type));
          return kTfLiteError;
      }
  }
  else {
    TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                       TfLiteTypeGetName(input->type),
                       TfLiteTypeGetName(output->type));
    return kTfLiteError;
  }

  return kTfLiteOk;
}

}  // namespace dequantize

TfLiteRegistration Register_DEQUANTIZE() {
  return {/*init=*/dequantize::Init,
          /*free=*/nullptr,
          /*prepare=*/dequantize::Prepare,
          /*invoke=*/dequantize::Eval,
          /*profiling_string=*/nullptr,
          /*builtin_code=*/0,
          /*custom_name=*/nullptr,
          /*version=*/0};
}

}  // namespace micro
}  // namespace ops
}  // namespace tflite
