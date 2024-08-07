/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

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
#include "tensorflow/lite/micro/ia700/config.h"

#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/quantize.h"
#endif
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/requantize.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/quantize.h"
#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
#include "tensorflow/lite/micro/micro_utils.h"
namespace tflite {
namespace {
// local structure include QuantedReference
struct OpData {
  struct OpDataQuantizeReference QuantizeOp;
  // tflite::QuantizationParams quantization_params;
  // The scaling factor from input to output (aka the 'real multiplier') can
  // be represented as a fixed point multiplier plus a left shift.
  // int32_t output_multiplier;
  // int output_shift;
  // AScalar outputMultipler;
  AScalar inv_scale;
  AScalar zero_point;
  int32_t input_zero_point;

  // requantize
   AScalar Requantize;
   AScalar inZeroPoint;
   AScalar outZeroPoint;
};

#ifdef HEMILITE_QUANTIZE_OPT
void AffineQuantizeFloat32ToInt8(struct OpData* op_data,
                                 const RuntimeShape& input_shape,
                                 const float* input_data,
                                 const RuntimeShape& output_shape,
                                 int8_t* output_data) {
  // tflite::QuantizationParams op_params = op_data->quantization_params;
  //  const int32_t zero_point = op_params.zero_point;
  //  const double scale = op_params.scale;
  const int flat_size = MatchingFlatSize(input_shape, output_shape);

  int loopLim = flat_size >> 1;
  uint32_t* pInput = (uint32_t*)input_data;
  vr64 VR_dataIn, VR_scale;
  vr64 VR_zeroPoint;
  vr64 VR_out, VR_q7_out;
  ulsr32 UR_dataIn = align_32x2_load(pInput);
  
  replicate_ar(VR_scale, 0x3, op_data->inv_scale.fr);
  replicate_ar(VR_zeroPoint, 0x3, op_data->zero_point.fr);

  //  KN_PRINT_Q7_SIZE(output_data, flat_size);

  uint32_t* pDst = (uint32_t*)output_data;
  if (loopLim > 0)
  {
	  load_32x2_vr_a(VR_dataIn, UR_dataIn, pInput);
	 
	  for (int i = 0; i < loopLim - 1; i++) {
		  convert_IEEE_float_to_32F_x2(VR_dataIn);
		  VR_out = vmacs(VR_zeroPoint, VR_scale, VR_dataIn, 0, 0);
		  load_32x2_vr_a(VR_dataIn, UR_dataIn, pInput);
		  // VR_out = vexp_adji(VR_out, 8);
		  convert_32F_to_16I_x2(VR_out, 15 - 8, 1);
		  rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
		  store16x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
		  
	  }
	  convert_IEEE_float_to_32F_x2(VR_dataIn);
	  VR_out = vmacs(VR_zeroPoint, VR_scale, VR_dataIn, 0, 0);

	  // VR_out = vexp_adji(VR_out, 8);
	  convert_32F_to_16I_x2(VR_out, 15 - 8, 1);

	  rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
	  store16x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
  }
  // TODO:
  if (flat_size & 1) {
    {
      load32x1_vr_postI(VR_dataIn, pInput, INC1, VRQ0);
      convert_IEEE_float_to_32F_x2(VR_dataIn);
      VR_out = vmacs(VR_zeroPoint, VR_scale, VR_dataIn, 0, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x1(VR_out, 15 - 8, 1, VRQ0);

      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(VR_out, pDst, INC1, VRQ0);
    }
  }
}


void ReQuantizeInt8ToInt8(struct OpData* op_data,
	const RuntimeShape& input_shape,
	const int8_t* input_data,
	const RuntimeShape& output_shape,
	int8_t* output_data) {
	// tflite::QuantizationParams op_params = op_data->quantization_params;
	//  const int32_t zero_point = op_params.zero_point;
	//  const double scale = op_params.scale;
	const int flat_size = MatchingFlatSize(input_shape, output_shape);

	const AScalar &ReQuantize = op_data->Requantize;
	const AScalar &inZeroPoint = op_data->inZeroPoint;
	const AScalar &outZeroPoint = op_data->outZeroPoint;

	int loopLim = flat_size >> 1;
	uint32_t* pInput = (uint32_t*)input_data;
	vr64 VR_dataIn, VR_Reqantize;
	vr64 VR_inZp, VR_outZp, VR_inp;
	vr64 VR_out, VR_q7_out, VR_Rnd, VR_RndNeg, VR_tmp;
	//ulsr32 UR_dataIn = align_8x4_load(pInput);
	
	replicate_ar(VR_Reqantize, 0x3, ReQuantize.fr);

	replicate_ar(VR_inZp, 0x3, inZeroPoint.fr);
	replicate_ar(VR_outZp, 0x3, outZeroPoint.fr);
	//  KN_PRINT_Q7_SIZE(output_data, flat_size);
	int out_shift = op_data->QuantizeOp.requantize_output_shift;
	if (out_shift < 0)
	{
		VR_Rnd = vseta_vr(1, 0);
		VR_Rnd = vexp_adj(VR_Rnd, -8 + out_shift);
		VR_RndNeg = s_vneg(VR_Rnd);
	}
	else {
		VR_Rnd = VR_RndNeg = vseta_vr(kConstTable_Zero, 0);
	}
	uint32_t* pDst = (uint32_t*)output_data;
	if (loopLim > 0)
	{
		load8x2_vr_postI(VR_dataIn, pInput, INC1);
		for (int i = 0; i < loopLim - 1; i++) {
			convert_16I_to_32F_x2(VR_dataIn, 0);
			VR_inp = vadds(VR_dataIn, VR_inZp, 0xa); //  input_data[i] - input_zeropoint;
#if 1
			VR_out = vmacs(VR_outZp, VR_inp, VR_Reqantize, 0, 0);

			VR_tmp = vsel(VR_Rnd, VR_RndNeg, vge_const(VR_inp, kConstTable_Zero, 0));
			VR_out = vadds(VR_out, VR_tmp, 0x0); //HACK
			convert_32F_to_16I_x2(VR_out, 0, 0);
#endif
			rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
			store16x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
			load8x2_vr_postI(VR_dataIn, pInput, INC1);
		}
		convert_16I_to_32F_x2(VR_dataIn, 0);
		VR_out = vadds(VR_dataIn, VR_inZp, 0xa); //  input_data[i] - input_zeropoint;
												  // VR_out = vexp_adji(VR_out, 8);
		VR_out = vmacs(VR_outZp, VR_out, VR_Reqantize, 0, 0);
		VR_tmp = vsel(VR_Rnd, VR_RndNeg, vge_const(VR_inp, kConstTable_Zero, 0));
		VR_out = vadds(VR_out, VR_tmp, 0x0); //HACK
		convert_32F_to_16I_x2(VR_out, 0, 0);

		rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
		store16x1_vr_postI(VR_q7_out, pDst, INC1, VRQ0);
	}
	if (flat_size & 1) {

		load8x1_vr_postI(VR_dataIn, pInput, INC1, VRQ0);
		convert_16I_to_32F_x2(VR_dataIn, 0);
		VR_out = vadds(VR_dataIn, VR_inZp, 0xa); //  input_data[i] - input_zeropoint;
													// VR_out = vexp_adji(VR_out, 8);
		VR_out = vmacs(VR_outZp, VR_out, VR_Reqantize, 0, 0);
		// VR_out = vexp_adji(VR_out, 8);
		VR_tmp = vsel(VR_Rnd, VR_RndNeg, vge_const(VR_inp, kConstTable_Zero, 0));
		VR_out = vadds(VR_out, VR_tmp, 0x0); //HACK
		convert_32F_to_16I_x2(VR_out, 0, 0);


		rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
		VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
		store8x1_vr_postI(VR_out, pDst, INC1, VRQ0);
		
	}
}


#endif

void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data_ex = static_cast<OpData*>(node->user_data);
  auto* data = static_cast<struct tflite::OpDataQuantizeReference*>(
      &data_ex->QuantizeOp);
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);


  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, 0);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, 0);
  TF_LITE_ENSURE(context, output != nullptr);

  // TODO(b/128934713): Add support for fixed-point per-channel quantization.
  // Currently this only support affine per-layer quantization.
  TF_LITE_ENSURE_EQ(context, output->quantization.type,
                    kTfLiteAffineQuantization);
  const auto* affine_quantization =
      reinterpret_cast<TfLiteAffineQuantization*>(output->quantization.params);
  TF_LITE_ENSURE(context, affine_quantization);
  TF_LITE_ENSURE(context, affine_quantization->scale);
  TF_LITE_ENSURE(context, affine_quantization->scale->size == 1);

  TF_LITE_ENSURE(
      context, input->type == kTfLiteFloat32 || input->type == kTfLiteInt32 ||
                   input->type == kTfLiteInt16 || input->type == kTfLiteInt8 ||
                   input->type == kTfLiteUInt8);
  TF_LITE_ENSURE(context, output->type == kTfLiteInt8 ||
                              output->type == kTfLiteInt16 ||
                              output->type == kTfLiteInt32 ||
                              output->type == kTfLiteUInt8);

  if ((input->type == kTfLiteInt16 && output->type == kTfLiteInt8) ||
      (input->type == kTfLiteInt8 && output->type == kTfLiteInt8) ||
      (input->type == kTfLiteInt8 && output->type == kTfLiteUInt8) ||
      (input->type == kTfLiteUInt8 && output->type == kTfLiteInt8) ||
      (input->type == kTfLiteInt8 && output->type == kTfLiteInt16) ||
      (input->type == kTfLiteInt8 && output->type == kTfLiteInt32) ||
      (input->type == kTfLiteInt16 && output->type == kTfLiteInt16) ||
      (input->type == kTfLiteInt16 && output->type == kTfLiteInt32) ||
      (input->type == kTfLiteInt32 && output->type == kTfLiteInt8) ||
      (input->type == kTfLiteInt32 && output->type == kTfLiteInt16)) {
    double effective_scale = static_cast<double>(input->params.scale) /
                             static_cast<double>(output->params.scale);

    QuantizeMultiplier(effective_scale, &data->requantize_output_multiplier,
                       &data->requantize_output_shift);

    // data->outputMultipler = AScalar(effective_scale);
  }
  data_ex->inv_scale = AScalar(output->params.scale).inverse();
  data_ex->zero_point = AScalar(output->params.zero_point);

  data->quantization_params.zero_point = output->params.zero_point;
  data->quantization_params.scale = static_cast<double>(output->params.scale);

  data->input_zero_point = input->params.zero_point;

  // support int8->int8
  if ((input->type == kTfLiteInt8 && output->type == kTfLiteInt8))
  {
	  //  AScalar Requantize, inputZeroPoint, outputZeroPoint;
	  ConvertQ31ToAfloat(data_ex->QuantizeOp.requantize_output_multiplier, data_ex->Requantize,
		  data_ex->QuantizeOp.requantize_output_shift);
	  // load, Q7
	  ConvertQ31ToAfloat(data_ex->QuantizeOp.input_zero_point, data_ex->inZeroPoint,
		  24);
	  ConvertQ31ToAfloat(data_ex->QuantizeOp.quantization_params.zero_point, data_ex->outZeroPoint,
		  24);
	  KN_PRINTAFLT(data_ex->Requantize);
	  KN_PRINTAFLT(data_ex->inZeroPoint);
	  KN_PRINTAFLT(data_ex->outZeroPoint);
  }

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);

  OpData* data_ex = static_cast<OpData*>(node->user_data);


  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);

#if defined(HEMILITE_QUANTIZE_OPT)
 if (input->type == kTfLiteFloat32 && kTfLiteInt8 == output->type) 
    {

        AffineQuantizeFloat32ToInt8(
            data_ex, tflite::micro::GetTensorShape(input),
            tflite::micro::GetTensorData<float>(input),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<int8_t>(output));
        
        KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                         ElementCount(*output->dims));
         return kTfLiteOk;
	}
	else if (input->type == kTfLiteInt8 && kTfLiteInt8 == output->type) {
		KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input),
			ElementCount(*input->dims));
		//	data->input_zero_point, data->quantization_params.zero_point,
		ReQuantizeInt8ToInt8(data_ex, tflite::micro::GetTensorShape(input),
			tflite::micro::GetTensorData<int8_t>(input),
			tflite::micro::GetTensorShape(output),
			tflite::micro::GetTensorData<int8_t>(output));

		KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
			ElementCount(*output->dims));
		return kTfLiteOk;
	}
	else
#endif
	{
#ifndef REMOVE_REFOP_SUPPORT
		auto* data = static_cast<struct tflite::OpDataQuantizeReference*>(
			&data_ex->QuantizeOp);
          if (input->type == kTfLiteFloat32) {
            switch (output->type) {
              case kTfLiteInt8:
                reference_ops::AffineQuantize(
                    data->quantization_params,
                    tflite::micro::GetTensorShape(input),
                    tflite::micro::GetTensorData<float>(input),
                    tflite::micro::GetTensorShape(output),
                    tflite::micro::GetTensorData<int8_t>(output));
                break;
              case kTfLiteInt16:
                reference_ops::AffineQuantize(
                    data->quantization_params,
                    tflite::micro::GetTensorShape(input),
                    tflite::micro::GetTensorData<float>(input),
                    tflite::micro::GetTensorShape(output),
                    tflite::micro::GetTensorData<int16_t>(output));
                return kTfLiteOk;
              default:
                TF_LITE_KERNEL_LOG(context,
                                   "Input %s, output %s not supported.",
                            TfLiteTypeGetName(input->type),
                            TfLiteTypeGetName(output->type));
                return kTfLiteError;
            }
          } else if (input->type == kTfLiteInt32) {
            size_t size = ElementCount(*input->dims);
            switch (output->type) {
              case kTfLiteInt8:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int32_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int8_t>(output));
                break;
              case kTfLiteInt16:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int32_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int16_t>(output));
                break;
              default:
                TF_LITE_KERNEL_LOG(context,
                                   "Input %s, output %s not supported.",
                            TfLiteTypeGetName(input->type),
                            TfLiteTypeGetName(output->type));
                return kTfLiteError;
            }
          } else if (input->type == kTfLiteInt16) {
            size_t size = ElementCount(*input->dims);
            switch (output->type) {
              case kTfLiteInt8:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int16_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int8_t>(output));
                break;
              case kTfLiteInt16:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int16_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int16_t>(output));
                return kTfLiteOk;
              case kTfLiteInt32:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int16_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int32_t>(output));
                return kTfLiteOk;
              default:
                TF_LITE_KERNEL_LOG(context,
                                   "Input %s, output %s not supported.",
                            TfLiteTypeGetName(input->type),
                            TfLiteTypeGetName(output->type));
                return kTfLiteError;
            }
          } else if (input->type == kTfLiteInt8) {
            // Int8 to Int8 requantization, required if the input and output
            // tensors have different scales and/or zero points.
            size_t size = ElementCount(*input->dims);
            switch (output->type) {
              case kTfLiteInt8:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int8_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int8_t>(output));
                break;
              case kTfLiteUInt8:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int8_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<uint8_t>(output));
                break;
              case kTfLiteInt16:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int8_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int16_t>(output));
                break;
              case kTfLiteInt32:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<int8_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int32_t>(output));
                break;
              default:
                TF_LITE_KERNEL_LOG(context,
                                   "Input %s, output %s not supported.",
                            TfLiteTypeGetName(input->type),
                            TfLiteTypeGetName(output->type));
                return kTfLiteError;
            }
          } else if (input->type == kTfLiteUInt8) {
            size_t size = ElementCount(*input->dims);
            switch (output->type) {
              case kTfLiteInt8:
                reference_ops::Requantize(
                    tflite::micro::GetTensorData<uint8_t>(input), size,
                    data->requantize_output_multiplier,
                    data->requantize_output_shift, data->input_zero_point,
                    data->quantization_params.zero_point,
                    tflite::micro::GetTensorData<int8_t>(output));
                break;
              default:
                TF_LITE_KERNEL_LOG(context,
                                   "Input %s, output %s not supported.",
                            TfLiteTypeGetName(input->type),
                            TfLiteTypeGetName(output->type));
                return kTfLiteError;
            }
          } else {
            TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
                        TfLiteTypeGetName(input->type),
                        TfLiteTypeGetName(output->type));
            return kTfLiteError;
          }

          return kTfLiteOk;
#else

		return kTfLiteError;
#endif

		return kTfLiteOk;
	}
}

TfLiteStatus EvalFloat32Int8(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);

  OpData* data_ex = static_cast<OpData*>(node->user_data);
 // auto* data = static_cast<struct tflite::OpDataQuantizeReference*>(
   //   &data_ex->QuantizeOp);

    const TfLiteEvalTensor* input =
        tflite::micro::GetEvalInput(context, node, 0);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);
#if defined(HEMILITE_QUANTIZE_OPT)
    if (input->type == kTfLiteFloat32 && kTfLiteInt8 == output->type) {
      AffineQuantizeFloat32ToInt8(data_ex, tflite::micro::GetTensorShape(input),
                                  tflite::micro::GetTensorData<float>(input),
                                  tflite::micro::GetTensorShape(output),
                                  tflite::micro::GetTensorData<int8_t>(output));

      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                       ElementCount(*output->dims));
      return kTfLiteOk;
    } else 
#endif
	{
#ifndef REMOVE_REFOP_SUPPORT
		if (input->type == kTfLiteFloat32 && kTfLiteInt8 == output->type) {
			reference_ops::AffineQuantize(
				data_ex->QuantizeOp.quantization_params, tflite::micro::GetTensorShape(input),
				tflite::micro::GetTensorData<float>(input),
				tflite::micro::GetTensorShape(output),
				tflite::micro::GetTensorData<int8_t>(output));
		}
		else 
#endif
		{
			TF_LITE_KERNEL_LOG(context, "Input %s, output %s not supported.",
				TfLiteTypeGetName(input->type),
				TfLiteTypeGetName(output->type));
		}
      return kTfLiteError;
    }

  return kTfLiteOk;
}

}  // namespace

TFLMRegistration Register_QUANTIZE() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/Prepare,
                                   /*invoke=*/Eval);
}
TFLMRegistration Register_QUANTIZE_FLOAT32_INT8() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/Prepare,
                                   /*invoke=*/EvalFloat32Int8);
}
}  // namespace tflite
