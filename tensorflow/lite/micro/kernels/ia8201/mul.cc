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
#include "tensorflow/lite/micro/ia8201/config.h"

#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/mul.h"
#endif
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/integer_ops/mul.h"
#endif
#include "tensorflow/lite/kernels/internal/reference/process_broadcast_shapes.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"


#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/memory_helpers.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {
//namespace ops {
//namespace micro {
//namespace mul {

const int kMulInput1Tensor = 0;
const int kMulInput2Tensor = 1;
const int kMulOutputTensor = 0;
typedef enum {
    MUL_OPT_NONE = 0, 
    MUL_OPT_TYPE1 = 1, //,ELEMENT_WISE = 1,
    MUL_OPT_TYPE2 = 2, //INPUT1_LAST_EQ_INPUT2 size, input1 == output 1
    MUL_OPT_TYPE3 = 3 // input2 is constat value 1,
}mul_opt_type;
#if defined(IA8201)
static void CalculateActivationRange(TfLiteFusedActivation activation,
                              AScalar* activation_min,
                              AScalar* activation_max) {
  if (activation == kTfLiteActRelu) {
    *activation_min = CONST_ASCALAR(0);
    *activation_max = AScalar::MaxAFloat();  // std::numeric_limits<T>::max();
  } else if (activation == kTfLiteActRelu6) {
    *activation_min = CONST_ASCALAR(0);
    *activation_max = CONST_ASCALAR(6);
  } else if (activation == kTfLiteActReluN1To1) {
    *activation_min = CONST_ASCALAR(-1);
    *activation_max = CONST_ASCALAR(1);
  } else {
    *activation_min =
        AScalar::MinAFloat();  // std::numeric_limits<T>::lowest();
    *activation_max = AScalar::MaxAFloat();
    // std::numeric_limits<T>::max();
  }
}
#endif
struct OpData {
  int32_t output_activation_min;
  int32_t output_activation_max;

  int32_t output_multiplier;
  int output_shift;

  // Cached tensor zero point values for quantized operations.
  int32_t input1_zero_point;
  int32_t input2_zero_point;
  int32_t output_zero_point;
  //	AScalar input1_multiplier_fr32;
  //	AScalar input2_multiplier_fr32;
  AScalar output_multiplier_fr32;

  AScalar input1_offset_fr32;
  AScalar input2_offset_fr32;
  AScalar output_offset_fr32;

  int opt_constraint;
  int opt_constraint_float;
  AScalar output_activation_min_fr32;
  AScalar output_activation_max_fr32;
};

TfLiteStatus CalculateOpData(TfLiteContext* context, TfLiteNode* node,
                             TfLiteMulParams* params, OpData* data) {
  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input1 =
      micro_context->AllocateTempInputTensor(node, kMulInput1Tensor);
  TF_LITE_ENSURE(context, input1 != nullptr);
  TfLiteTensor* input2 =
      micro_context->AllocateTempInputTensor(node, kMulInput2Tensor);
  TF_LITE_ENSURE(context, input2 != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kMulOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);


  TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  TF_LITE_ENSURE_TYPES_EQ(context, input1->type, input2->type);

  if (output->type == kTfLiteInt16 || output->type == kTfLiteInt8) {
    TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
        context, params->activation, output, &data->output_activation_min,
        &data->output_activation_max));

    double real_multiplier = static_cast<double>(input1->params.scale) *
                             static_cast<double>(input2->params.scale) /
                             static_cast<double>(output->params.scale);
    QuantizeMultiplier(real_multiplier, &data->output_multiplier,
                       &data->output_shift);
  } else if (output->type == kTfLiteInt32) {
    CalculateActivationRange(params->activation, &data->output_activation_min,
                             &data->output_activation_max);
  } else {
    CalculateActivationRange(params->activation,
                             &data->output_activation_min_fr32,
                             &data->output_activation_max_fr32);
  }

  micro_context->DeallocateTempTfLiteTensor(input1);
  micro_context->DeallocateTempTfLiteTensor(input2);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

void* InitMul(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus PrepareMul(TfLiteContext* context, TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input1 =
      micro_context->AllocateTempInputTensor(node, kMulInput1Tensor);
  TF_LITE_ENSURE(context, input1 != nullptr);
  TfLiteTensor* input2 =
      micro_context->AllocateTempInputTensor(node, kMulInput2Tensor);
  TF_LITE_ENSURE(context, input2 != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kMulOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

  if (output->dims->size == 0) {
    return AllocateOutputDimensionsFromInput(context, input1, input2, output);
  }

  TFLITE_DCHECK(node->builtin_data != nullptr);
  auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);
  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data = static_cast<OpData*>(node->user_data);
  int input1_count = ElementCount(*input1->dims);
  int input2_count = ElementCount(*input2->dims);
  int output_count = ElementCount(*output->dims);
  KN_PRINTD(input1_count);
  KN_PRINTD(input2_count);
  KN_PRINTD(output_count);
  data->input1_zero_point = input1->params.zero_point;
  data->input2_zero_point = input2->params.zero_point;
  data->output_zero_point = output->params.zero_point;
  CalculateOpData(context, node, params, data);

  data->opt_constraint = MUL_OPT_NONE;
  data->opt_constraint_float = MUL_OPT_NONE;
#if (defined(DMX1A_MUL_OPT) || defined(HMD1A_MUL_OPT))
  if (output->type == kTfLiteInt8)
  {
      // check in run time, broad cast

      int input_shape0 = input1->dims->data[input1->dims->size - 1]; // Dims(0);
      if (input2_count == input1_count &&
          input1_count == output_count) {
          data->opt_constraint = MUL_OPT_TYPE1;
      }
      else if (input_shape0 == input2_count &&
          output_count == input1_count &&
          (input_shape0 & 3) == 0) {
          data->opt_constraint = MUL_OPT_TYPE2;  // 

      }
      else if (1 == input2_count && output_count == input1_count)
          data->opt_constraint = MUL_OPT_TYPE3;  // FloatNulWithScalarBroadcast


  }
  // only min = -128 and max=127 acceptable for rnd_sat_pack

  KN_PRINTD(data->output_activation_min);
  KN_PRINTD(data->output_activation_max);
  KN_PRINTD(data->opt_constraint);
  if (data->opt_constraint) {
    // tflite::ConvertQ31ToAfloat(data->input1_multiplier,
    // data->input1_multiplier_fr32, 17);
    // tflite::ConvertQ31ToAfloat(data->input2_multiplier,
    // data->input2_multiplier_fr32,  17);
    tflite::ConvertQ31ToAfloat(data->output_multiplier,
                               data->output_multiplier_fr32,
                               7 + data->output_shift);  // 17);//-19
	// NOTE: Input offset is -zero_point for add offset
    tflite::ConvertQ31ToAfloat(-data->input1_zero_point,
                               data->input1_offset_fr32, 31 - 7);
    tflite::ConvertQ31ToAfloat(-data->input2_zero_point,
                               data->input2_offset_fr32, 31 - 7);
    tflite::ConvertQ31ToAfloat(data->output_zero_point,
                               data->output_offset_fr32, 31 - 7);
  }

  if (output->type == kTfLiteFloat32) {

      int input_shape0 = input1->dims->data[input1->dims->size - 1];
      if (input1_count == input2_count && input2_count == output_count)
      {
          data->opt_constraint_float = MUL_OPT_TYPE1;
      }
      else if (input_shape0 == input2_count &&
          output_count == input1_count) {
          data->opt_constraint_float = MUL_OPT_TYPE2;  // 1: 1,1,3,64 , in2: 64, out: 1,3,64
      }
      else if (1 == input2_count && output_count == input1_count)

      {
          data->opt_constraint_float = MUL_OPT_TYPE3;  // FloatNulWithScalarBroadcast
      }
  }
  
#endif

  micro_context->DeallocateTempTfLiteTensor(input1);
  micro_context->DeallocateTempTfLiteTensor(input2);
  micro_context->DeallocateTempTfLiteTensor(output);

  return kTfLiteOk;
}
#ifdef DMX1A_MUL_OPT

static void MulFloatConstI(float* output, const float* input1,
                           const AScalar& input2, int size,
                           const AScalar& act_min, const AScalar& act_max) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 2;
  int remain = (size & 3);
  vr128 VR_input1, VR_input2;
  vr128 VR_min, VR_max;

  ulsr128 UR_input1;  //, UR_input2;
  vr128 VR_out;
  UR_input1 = align_32x4_load(input1);
  // UR_input2 = align_32x4_load(input2);
  ulsr128 UR_output = align_32x4_store(output);

  replicate_ar(VR_min, 0xf, act_min.fr);
  replicate_ar(VR_max, 0xf, act_max.fr);
  replicate_ar(VR_input2, 0xf, input2.fr);

  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x4_vr_a(VR_input1, UR_input1, input1);
    //  load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x4(VR_input1);

      //     KN_PRINT_VR128(VR_input1);
      //      KN_PRINT_VR128(VR_input2);
      VR_out = vmuls(VR_input1, VR_input2, 0);
      // KN_PRINT_VR128(VR_out);
      load_32x4_vr_a(VR_input1, UR_input1, input1);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x4(VR_out);

      store_32x4_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x4(VR_input1);

    VR_out = vmuls(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    // KN_PRINT_VR128(VR_input1);
    // KN_PRINT_VR128(VR_input2);
    // KN_PRINT_VR128(VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);

    store_32x4_vr_a(VR_out, UR_output, output);
    flush_32x4(UR_output, output);
  }
  for (int ii = 0; ii < remain; ii++) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);

    convert_IEEE_float_to_32F_x4(VR_input1);

    fmuls(VR_out, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

static void MulFloat(float* output, const float* input1, const float* input2,
                     int size, const AScalar& act_min, const AScalar& act_max) {
  int loopLim = size >> 2;
  int remain = (size & 3);
  vr128 VR_input1, VR_input2;
  vr128 VR_min, VR_max;

  ulsr128 UR_input1, UR_input2;
  vr128 VR_out;
  UR_input1 = align_32x4_load(input1);
  UR_input2 = align_32x4_load(input2);
  ulsr128 UR_output = align_32x4_store(output);
  //  float act_min = op_params.float_activation_min;
  // float act_max = op_params.float_activation_max;
  replicate_ar(VR_min, 0xf, act_min.fr);
  replicate_ar(VR_max, 0xf, act_max.fr);
  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x4_vr_a(VR_input1, UR_input1, input1);
    load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x4(VR_input1);
      convert_IEEE_float_to_32F_x4(VR_input2);
      KN_PRINT_VR128(VR_input1);
      KN_PRINT_VR128(VR_input2);
      VR_out = vmuls(VR_input1, VR_input2, 0);
      KN_PRINT_VR128(VR_out);
      load_32x4_vr_a(VR_input1, UR_input1, input1);
      load_32x4_vr_a(VR_input2, UR_input2, input2);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x4(VR_out);

      store_32x4_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x4(VR_input1);
    convert_IEEE_float_to_32F_x4(VR_input2);
    VR_out = vmuls(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    KN_PRINT_VR128(VR_input1);
    KN_PRINT_VR128(VR_input2);
    KN_PRINT_VR128(VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);

    store_32x4_vr_a(VR_out, UR_output, output);
    flush_32x4(UR_output, output);
  }
  for (int ii = 0; ii < remain; ii++) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);
    load32x1_vr_postI(VR_input2, input2, INC1, VRQ0);
    convert_IEEE_float_to_32F_x4(VR_input1);
    convert_IEEE_float_to_32F_x4(VR_input2);
    fmuls(VR_out, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x4(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

// TODO: VIP
void MulQuantizedInt8Sat(const OpData* data, const int8_t* input1,
                         const int8_t* input2, int8_t* output, int n) {
  vr128 vr_input1, vr_input2;
  int loopLim = n >> 2;
  //
  // ulsr128 ur_input1, ur_input2;

  vr128 vr_offset1, vr_offset2;
  // vr128 vr_multiplier_input1, vr_multiplier_input2;
  vr128 vr_multiplier_output;
  vr128 vr_output_offset;
  vr128 vr_shift_input1, vr_shift_input2;
  vr128 vr_raw_sum, vr_output, vr_q7_out;
  ulsr128 UR_input1, UR_input2;
  ulsr128 UR_output;

  replicate_ar(vr_offset1, 0xf, data->input1_offset_fr32.fr);  // Afloat
  replicate_ar(vr_offset2, 0xf, data->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0xf, data->output_offset_fr32.fr);
  // replicate_ar(vr_multiplier_input1, 0xf, data->input1_multiplier_fr32);
  // replicate_ar(vr_multiplier_input2, 0xf, data->input2_multiplier_fr32);

  replicate_ar(vr_multiplier_output, 0xf, data->output_multiplier_fr32.fr);

  UR_input1 = align_8x4_load(input1);
  UR_input2 = align_8x4_load(input2);

  UR_output = align_8x4_store(output);
  if (loopLim > 0)
  {
	  load_8x4_vr_a(vr_input1, UR_input1, input1);
	  load_8x4_vr_a(vr_input2, UR_input2, input2);

	  convert_16I_to_32F_x4(vr_input1, 0);
	  for (int ii = 0; ii < loopLim - 1; ii++) {
		  convert_16I_to_32F_x4(vr_input2, 0);
		  // add offset each input
		  // q7*1<<left
		  vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
		  vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

		  vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

		  // align to integer type: 14
		  vr_output =
			  vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
		  // convert to 8 bit rndsat-back
		  convert_32F_to_16I_x4(vr_output, 0, 0);
		  rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
		  vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
		  store_8x4_vr_a(vr_output, UR_output, output);
		  //store32x1_vr_postI(vr_q7_out, output, INC1, VRQ0);
		  load_8x4_vr_a(vr_input1, UR_input1, input1);
		  load_8x4_vr_a(vr_input2, UR_input2, input2);
		  convert_16I_to_32F_x4(vr_input1, 0);
	  }
	  convert_16I_to_32F_x4(vr_input2, 0);
	  // add offset each input
	  // q7*1<<left
	  vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
	  vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

	  vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

	  // align to integer type: 14
	  vr_output =
		  vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
	  // convert to 8 bit rndsat-back
	  convert_32F_to_16I_x4(vr_output, 0, 0);

	  rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);

	  vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
	  store_8x4_vr_a(vr_output, UR_output, output);
	  flush_8x4(UR_output, output);
  }
  // reminder
  if (n & 3) {
    load_8x4_vr_a(vr_input1, UR_input1, input1);
    load_8x4_vr_a(vr_input2, UR_input2, input2);

    convert_16I_to_32F_x4(vr_input1, 0);
    convert_16I_to_32F_x4(vr_input2, 0);
    // add offset each input
    // q7*1<<left
    vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
    vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

    vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

    // align to integer type: 14
    vr_output =
        vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x4(vr_output, 0, 0);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
    for (int32_t ii = 0; ii < (n & 3); ii++) {
      store8x1_vr_postI(vr_output, output, INC1, VRQ0);
      vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
    }
  }
}


// TODO: VIP
void MulQuantizedInt8SatConstI(const OpData* data, const int8_t* input1,
	const int8_t* input2, int8_t* output, int n) {
	vr128 vr_input1, vr_input2;
	int loopLim = n >> 2;
	//
	// ulsr128 ur_input1, ur_input2;

	vr128 vr_offset1, vr_offset2;
	// vr128 vr_multiplier_input1, vr_multiplier_input2;
	vr128 vr_multiplier_output;
	vr128 vr_output_offset;
	vr128 vr_shift_input1, vr_shift_input2;
	vr128 vr_raw_sum, vr_output, vr_q7_out;
	ulsr128 UR_input1;
	ulsr128 UR_output;

	replicate_ar(vr_offset1, 0xf, data->input1_offset_fr32.fr);  // Afloat
	replicate_ar(vr_offset2, 0xf, data->input2_offset_fr32.fr);
	replicate_ar(vr_output_offset, 0xf, data->output_offset_fr32.fr);
	// replicate_ar(vr_multiplier_input1, 0xf, data->input1_multiplier_fr32);
	// replicate_ar(vr_multiplier_input2, 0xf, data->input2_multiplier_fr32);

	replicate_ar(vr_multiplier_output, 0xf, data->output_multiplier_fr32.fr);

	UR_input1 = align_8x4_load(input1);


	UR_output = align_8x4_store(output);
	load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);

	vr_input2 = vreplicate(vr_input2, VRQ0);
	//replicate_ar(vr_input2, 0xf, input2[0].fr);
	convert_16I_to_32F_x4(vr_input2, 0);
	if (loopLim > 0)
	{
		load_8x4_vr_a(vr_input1, UR_input1, input1);
		convert_16I_to_32F_x4(vr_input1, 0);
		for (int ii = 0; ii < loopLim - 1; ii++) {

			// add offset each input
			// q7*1<<left
			vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
			vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

			vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

																	  // align to integer type: 14
			vr_output =
				vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
			// convert to 8 bit rndsat-back
			convert_32F_to_16I_x4(vr_output, 0, 0);
			rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
			vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
			store_8x4_vr_a(vr_output, UR_output, output);
			load_8x4_vr_a(vr_input1, UR_input1, input1);

			convert_16I_to_32F_x4(vr_input1, 0);
		}
		//convert_16I_to_32F_x4(vr_input2, 0);
		// add offset each input
		// q7*1<<left
		vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
		vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

		vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

																  // align to integer type: 14
		vr_output =
			vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
		// convert to 8 bit rndsat-back
		convert_32F_to_16I_x4(vr_output, 0, 0);

		rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);

		vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
		store_8x4_vr_a(vr_output, UR_output, output);
		flush_8x4(UR_output, output);
	}
	// reminder
	if (n & 3) {
		load_8x4_vr_a(vr_input1, UR_input1, input1);

		convert_16I_to_32F_x4(vr_input1, 0);
		//convert_16I_to_32F_x4(vr_input2, 0);
		// add offset each input
		// q7*1<<left
		vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
		vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

		vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

																  // align to integer type: 14
		vr_output =
			vmacs_adj(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
		// convert to 8 bit rndsat-back
		convert_32F_to_16I_x4(vr_output, 0, 0);
		rnd_sat_pack(vr_q7_out, VRQ0, vr_output, 1);
		vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);
		for (int32_t ii = 0; ii < (n & 3); ii++) {
			store8x1_vr_postI(vr_output, output, INC1, VRQ0);
			vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
		}
	}
}
#endif
#ifdef HMD1A_MUL_OPT


static void MulFloatConstI(float* output, const float* input1,
                           const AScalar& input2, int size,
                           const AScalar& act_min, const AScalar& act_max) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 1;
  int remain = (size & 1);
  vr64 VR_input1, VR_input2;
  vr64 VR_min, VR_max;

  ulsr32 UR_input1;  //, UR_input2;
  vr64 VR_out;
  UR_input1 = align_32x2_load(input1);
  // UR_input2 = align_32x4_load(input2);
  ulsr32 UR_output = align_32x2_store(output);

  replicate_ar(VR_min, 0x3, act_min.fr);
  replicate_ar(VR_max, 0x3, act_max.fr);
  replicate_ar(VR_input2, 0x3, input2.fr);

  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x2_vr_a(VR_input1, UR_input1, input1);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x2(VR_input1);

      //     KN_PRINT_VR128(VR_input1);
      //      KN_PRINT_VR128(VR_input2);
      VR_out = vmuls(VR_input1, VR_input2, 0);
      // KN_PRINT_VR128(VR_out);
      load_32x2_vr_a(VR_input1, UR_input1, input1);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);

      store_32x2_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x2(VR_input1);

    VR_out = vmuls(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);

    store_32x2_vr_a(VR_out, UR_output, output);
    flush_32x2(UR_output, output);
  }
  if(remain) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);

    convert_IEEE_float_to_32F_x2(VR_input1);
     VR_out = vmuls(VR_input1, VR_input2, 0);
  //  fmuls(VR_out, VRQ0, VR_input1, VRQ0, VR_input2, VRQ0, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

static void MulFloat(float* output, const float* input1, const float* input2,
                     int size, const AScalar& act_min, const AScalar& act_max) {
  int loopLim = size >>1;
  int remain = (size & 1);
  vr64 VR_input1, VR_input2;
  vr64 VR_min, VR_max;

  ulsr32 UR_input1, UR_input2;
  vr64 VR_out;
  UR_input1 = align_32x2_load(input1);
  UR_input2 = align_32x2_load(input2);
  ulsr32 UR_output = align_32x2_store(output);
  //  float act_min = op_params.float_activation_min;
  // float act_max = op_params.float_activation_max;
  replicate_ar(VR_min, 0x3, act_min.fr);
  replicate_ar(VR_max, 0x3, act_max.fr);
  //  UR_input1 = algn_32x4_load();
  KN_PRINTD(size);
  KN_PRINTD(loopLim);
  KN_PRINTD(remain);
  if (loopLim > 0) {
    load_32x2_vr_a(VR_input1, UR_input1, input1);
    load_32x2_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x2(VR_input1);
      convert_IEEE_float_to_32F_x2(VR_input2);

      VR_out = vmuls(VR_input1, VR_input2, 0);

      load_32x2_vr_a(VR_input1, UR_input1, input1);
      load_32x2_vr_a(VR_input2, UR_input2, input2);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);

      store_32x2_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x2(VR_input1);
    convert_IEEE_float_to_32F_x2(VR_input2);
    VR_out = vmuls(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);

    convert_32F_to_IEEE_float_x2(VR_out);

    store_32x2_vr_a(VR_out, UR_output, output);
    flush_32x2(UR_output, output);
  }
  if(remain) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);
    load32x1_vr_postI(VR_input2, input2, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_input1);
    convert_IEEE_float_to_32F_x2(VR_input2);
      VR_out = vmuls(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

// TODO: VIP
void MulQuantizedInt8SatConstI(const OpData* data, const int8_t* input1,
	const int8_t* input2, int8_t* output, int n) {
	vr64 vr_input1, vr_input2;
	int loopLim = n >> 1;
	//
	// ulsr128 ur_input1, ur_input2;

	vr64 vr_offset1, vr_offset2;
	// vr64 vr_multiplier_input1, vr_multiplier_input2;
	vr64 vr_multiplier_output;
	vr64 vr_output_offset;
	vr64 vr_shift_input1, vr_shift_input2;
	vr64 vr_raw_sum, vr_output, vr_q7_out;
	KN_PRINTAFLT(data->input1_offset_fr32);
	KN_PRINTAFLT(data->input2_offset_fr32);
	KN_PRINTAFLT(data->output_multiplier_fr32);
	replicate_ar(vr_offset1, 0x3, data->input1_offset_fr32.fr);  // Afloat
	replicate_ar(vr_offset2, 0x3, data->input2_offset_fr32.fr);
	replicate_ar(vr_output_offset, 0x3, data->output_offset_fr32.fr);
	// replicate_ar(vr_multiplier_input1, 0x3, data->input1_multiplier_fr32);
	// replicate_ar(vr_multiplier_input2, 0x3, data->input2_multiplier_fr32);

	replicate_ar(vr_multiplier_output, 0x3, data->output_multiplier_fr32.fr);

	load8x2_vr_postI(vr_input1, input1, INC1);
	load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);
	vr_input2 = vreplicate(vr_input2, VRQ0);
	convert_16I_to_32F_x2(vr_input1, 0);
	convert_16I_to_32F_x2(vr_input2, 0);
	for (int ii = 0; ii < loopLim - 1; ii++) {
	
		// add offset each input
		// q7*1<<left
		vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
		vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

		vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

																  // align to integer type: 14
		vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
		// convert to 8 bit rndsat-back
		convert_32F_to_16I_x2(vr_output, 0, 0);
		rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
		store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);
		load8x2_vr_postI(vr_input1, input1, INC1);

		convert_16I_to_32F_x2(vr_input1, 0);
	}

	// add offset each input
	// q7*1<<left
	vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
	vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

	vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

															  // align to integer type: 14
	vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
	// convert to 8 bit rndsat-back
	convert_32F_to_16I_x2(vr_output, 0, 0);

	rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);

	store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);

	// reminder
	if (n & 1) {
		load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);


		convert_16I_to_32F_x2(vr_input1, 0);

		// add offset each input
		// q7*1<<left
		vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
		vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

		vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

																  // align to integer type: 14
		vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
		// convert to 8 bit rndsat-back
		convert_32F_to_16I_x2(vr_output, 0, 0);
		rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
		vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);

		store8x1_vr_postI(vr_output, output, INC1, VRQ0);
	
	}
}
// TODO: VIP
void MulQuantizedInt8Sat(const OpData* data, const int8_t* input1,
                         const int8_t* input2, int8_t* output, int n) {
  vr64 vr_input1, vr_input2;
  int loopLim = n >> 1;
  //
  // ulsr128 ur_input1, ur_input2;

  vr64 vr_offset1, vr_offset2;
  // vr64 vr_multiplier_input1, vr_multiplier_input2;
  vr64 vr_multiplier_output;
  vr64 vr_output_offset;
  vr64 vr_shift_input1, vr_shift_input2;
  vr64 vr_raw_sum, vr_output, vr_q7_out;
  KN_PRINTAFLT(data->input1_offset_fr32);
  KN_PRINTAFLT(data->input2_offset_fr32);
  KN_PRINTAFLT(data->output_multiplier_fr32);
  replicate_ar(vr_offset1, 0x3, data->input1_offset_fr32.fr);  // Afloat
  replicate_ar(vr_offset2, 0x3, data->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0x3, data->output_offset_fr32.fr);
  // replicate_ar(vr_multiplier_input1, 0x3, data->input1_multiplier_fr32);
  // replicate_ar(vr_multiplier_input2, 0x3, data->input2_multiplier_fr32);

  replicate_ar(vr_multiplier_output, 0x3, data->output_multiplier_fr32.fr);

  load8x2_vr_postI(vr_input1, input1, INC1);
  load8x2_vr_postI(vr_input2, input2, INC1);

  convert_16I_to_32F_x2(vr_input1, 0);
  for (int ii = 0; ii < loopLim - 1; ii++) {
    convert_16I_to_32F_x2(vr_input2, 0);
    // add offset each input
    // q7*1<<left
    vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
    vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

    vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

    // align to integer type: 14
    vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x2(vr_output, 0, 0);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
    store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);
    load8x2_vr_postI(vr_input1, input1, INC1);
    load8x2_vr_postI(vr_input2, input2, INC1);
    convert_16I_to_32F_x2(vr_input1, 0);
  }
  convert_16I_to_32F_x2(vr_input2, 0);
  // add offset each input
  // q7*1<<left
  vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
  vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

  vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

  // align to integer type: 14
  vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
  // convert to 8 bit rndsat-back
  convert_32F_to_16I_x2(vr_output, 0, 0);

  rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);

  store16x1_vr_postI(vr_q7_out, output, INC1, VRQ0);

  // reminder
  if (n & 1) {
    load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);
    load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);

    convert_16I_to_32F_x2(vr_input1, 0);
    convert_16I_to_32F_x2(vr_input2, 0);
    // add offset each input
    // q7*1<<left
    vr_shift_input1 = vadds(vr_input1, vr_offset1, 0);
    vr_shift_input2 = vadds(vr_input2, vr_offset2, 0);

    vr_raw_sum = vmuls(vr_shift_input1, vr_shift_input2, 0);  // exp = 14

    // align to integer type: 14
    vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);
    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x2(vr_output, 0, 0);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
    // for (int32_t ii = 0; ii < (n&3);ii++)
    // {
    store8x1_vr_postI(vr_output, output, INC1, VRQ0);
    // vr_output = vpermsi(vr_output, vr_output, 0, SHR_BY_1_ELEM);
    // }
  }
}
#endif
TfLiteStatus EvalQuantized(TfLiteContext* context, TfLiteNode* node,
                           TfLiteMulParams* params, const OpData& data,
                           const TfLiteEvalTensor* input1,
                           const TfLiteEvalTensor* input2,
                           TfLiteEvalTensor* output) {
  TfLiteStatus status = kTfLiteOk;
  if (output->type == kTfLiteInt8 || output->type == kTfLiteInt16 ||
      output->type == kTfLiteInt32) {
    tflite::ArithmeticParams op_params;
    SetActivationParams(data.output_activation_min, data.output_activation_max,
                        &op_params);
    op_params.input1_offset = -data.input1_zero_point;
    op_params.input2_offset = -data.input2_zero_point;
    op_params.output_offset = data.output_zero_point;
    op_params.output_multiplier = data.output_multiplier;
    op_params.output_shift = data.output_shift;
#ifndef REMOVE_REFOP_SUPPORT
    bool need_broadcast = reference_ops::ProcessBroadcastShapes(
        tflite::micro::GetTensorShape(input1),
        tflite::micro::GetTensorShape(input2), &op_params);
#endif
#define TF_LITE_MUL(type, opname, dtype)                         \
  type::opname(op_params, tflite::micro::GetTensorShape(input1), \
               tflite::micro::GetTensorData<dtype>(input1),      \
               tflite::micro::GetTensorShape(input2),            \
               tflite::micro::GetTensorData<dtype>(input2),      \
               tflite::micro::GetTensorShape(output),            \
               tflite::micro::GetTensorData<dtype>(output));

	if (output->type == kTfLiteInt8) {
#if (defined(DMX1A_MUL_OPT) || defined(HMD1A_MUL_OPT))
		if (data.opt_constraint == MUL_OPT_TYPE1){
			MulQuantizedInt8Sat(
				&data, tflite::micro::GetTensorData<int8_t>(input1),
				tflite::micro::GetTensorData<int8_t>(input2),
				tflite::micro::GetTensorData<int8_t>(output),
				MatchingElementsSize(tflite::micro::GetTensorShape(input1),
					tflite::micro::GetTensorShape(input2),
					tflite::micro::GetTensorShape(output)));
			KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
				ElementCount(*output->dims));
		}
		else if (data.opt_constraint == MUL_OPT_TYPE2) {
			// dim input1 [a,b,c,d], input2 = [d]
			// for loop all a*b*c for each d 
			const int8_t *input1_data = tflite::micro::GetTensorData<int8_t>(input1);
			const int8_t *input2_data = tflite::micro::GetTensorData<int8_t>(input2);
			int8_t *output_data = tflite::micro::GetTensorData<int8_t>(output);

			int internal_loop_count = tflite::micro::GetTensorShape(input2).FlatSize();
			int external_loop_count = tflite::micro::GetTensorShape(input1).FlatSize();


			for (int ii = 0; ii <external_loop_count; ii += internal_loop_count) // dim 2 , dim3
			{
				MulQuantizedInt8Sat(&data, input1_data,
					input2_data,
					output_data,
					internal_loop_count);
				input1_data += internal_loop_count;
				output_data += internal_loop_count;

			}

		}
		else if (data.opt_constraint == MUL_OPT_TYPE3)
		{
			const int8_t *input1_data = tflite::micro::GetTensorData<int8_t>(input1);
			const int8_t *input2_data = tflite::micro::GetTensorData<int8_t>(input2);
			int8_t *output_data = tflite::micro::GetTensorData<int8_t>(output);
			int loop_count = tflite::micro::GetTensorShape(input1).FlatSize();

			MatchingElementsSize(tflite::micro::GetTensorShape(input1), tflite::micro::GetTensorShape(output));
			// input 1 (size) * scale (1) = output( size) , size equal
			MulQuantizedInt8SatConstI(&data, input1_data,
				input2_data,
				output_data,
				loop_count);
	}
	else 
#endif
#ifndef REMOVE_REFOP_SUPPORT
      {
		if (need_broadcast) {
        TF_LITE_MUL(reference_integer_ops, BroadcastMul4DSlow, int8_t);
      } else {

		

        reference_integer_ops::Mul(
            op_params, tflite::micro::GetTensorShape(input1),
            tflite::micro::GetTensorData<int8_t>(input1),
            tflite::micro::GetTensorShape(input2),
            tflite::micro::GetTensorData<int8_t>(input2),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<int8_t>(output));
      
      }

    }
		KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
			ElementCount(*output->dims));
#else
      { return kTfLiteError; }
#endif

    }
#ifndef REMOVE_REFOP_SUPPORT
    /*else if (output->type == kTfLiteUInt8) {
      if (need_broadcast) {
        TF_LITE_MUL(reference_ops, BroadcastMul4DSlow, uint8_t);
      } else {
        TF_LITE_MUL(reference_ops, Mul, uint8_t);
        // TODO
      }
    } */
        else if (input1->type == kTfLiteInt32) {
          if (need_broadcast) {
            reference_ops::BroadcastMul4DSlow(
                op_params, tflite::micro::GetTensorShape(input1),
                tflite::micro::GetTensorData<int32_t>(input1),
                tflite::micro::GetTensorShape(input2),
                tflite::micro::GetTensorData<int32_t>(input2),
                tflite::micro::GetTensorShape(output),
                tflite::micro::GetTensorData<int32_t>(output));
          } else {
            reference_ops::Mul(op_params, tflite::micro::GetTensorShape(input1),
                               tflite::micro::GetTensorData<int32_t>(input1),
                               tflite::micro::GetTensorShape(input2),
                               tflite::micro::GetTensorData<int32_t>(input2),
                               tflite::micro::GetTensorShape(output),
                               tflite::micro::GetTensorData<int32_t>(output));
          }
        } else if (input1->type == kTfLiteInt16) {
      TF_LITE_ENSURE_EQ(context, op_params.input1_offset, 0);
      TF_LITE_ENSURE_EQ(context, op_params.input2_offset, 0);
      TF_LITE_ENSURE_EQ(context, op_params.output_offset, 0);

      if (need_broadcast) {
        reference_integer_ops::BroadcastMul4DSlow(
            op_params, tflite::micro::GetTensorShape(input1),
            tflite::micro::GetTensorData<int16_t>(input1),
            tflite::micro::GetTensorShape(input2),
            tflite::micro::GetTensorData<int16_t>(input2),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<int16_t>(output));
      } else {
        reference_integer_ops::Mul(
            op_params, tflite::micro::GetTensorShape(input1),
            tflite::micro::GetTensorData<int16_t>(input1),
            tflite::micro::GetTensorShape(input2),
            tflite::micro::GetTensorData<int16_t>(input2),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<int16_t>(output));
      }
    }
#endif
  }  // end of type == int8 or uint8
#undef TF_LITE_MUL
  return status;
}

TfLiteStatus EvalFloat(TfLiteContext* context, TfLiteNode* node,
                       TfLiteMulParams* params, const OpData* data,
                       const TfLiteEvalTensor* input1,
                       const TfLiteEvalTensor* input2,
                       TfLiteEvalTensor* output) {
  float output_activation_min, output_activation_max;
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);
  tflite::ArithmeticParams op_params;
  TfLiteStatus status = kTfLiteOk;
  SetActivationParams(output_activation_min, output_activation_max, &op_params);
#ifndef REMOVE_REFOP_SUPPORT
  bool need_broadcast = reference_ops::ProcessBroadcastShapes(
      tflite::micro::GetTensorShape(input1),
      tflite::micro::GetTensorShape(input2), &op_params);
#endif
#define TF_LITE_MUL(opname)                                               \
  reference_ops::opname(op_params, tflite::micro::GetTensorShape(input1), \
                        tflite::micro::GetTensorData<float>(input1),      \
                        tflite::micro::GetTensorShape(input2),            \
                        tflite::micro::GetTensorData<float>(input2),      \
                        tflite::micro::GetTensorShape(output),            \
                        tflite::micro::GetTensorData<float>(output));

  AScalar act_min, act_max;
  CalculateActivationRangeAflt(params->activation, &act_min, &act_max);
#if defined(DMX1A_MUL_OPT) || defined(HMD1A_MUL_OPT)
  if (data->opt_constraint_float == MUL_OPT_TYPE1) {
    const int flat_size =
        MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                             tflite::micro::GetTensorShape(input2),
                             tflite::micro::GetTensorShape(output));
	//KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input1), flat_size);
	//KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input2), flat_size);
    MulFloat(tflite::micro::GetTensorData<float>(output),
             tflite::micro::GetTensorData<float>(input1),
             tflite::micro::GetTensorData<float>(input2), flat_size, act_min,
             act_max);
	//KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output), flat_size);
    return kTfLiteOk;
  }
  else if (data->opt_constraint_float == MUL_OPT_TYPE2) {
      const float* input1_data = tflite::micro::GetTensorData<float>(input1);
      const float* input2_data = tflite::micro::GetTensorData<float>(input2);
      float* output_data = tflite::micro::GetTensorData<float>(output);

      int internal_loop_count = tflite::micro::GetTensorShape(input2).FlatSize();
      int external_loop_count = tflite::micro::GetTensorShape(input1).FlatSize();


      for (int ii = 0; ii < external_loop_count; ii += internal_loop_count) // dim 2 , dim3
      {
          MulFloat(output_data, 
              input1_data,
              input2_data,
              internal_loop_count, act_min,
              act_max);
          input1_data += internal_loop_count;
          output_data += internal_loop_count;

      }

  }
   else if (data->opt_constraint_float == MUL_OPT_TYPE3) {
    AScalar input2Element;
    const int flat_size =
        MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                             tflite::micro::GetTensorShape(output));

    const float* input2Flt = tflite::micro::GetTensorData<float>(input2);
    KN_PRINTF(input2Flt[0]);
    input2Element = AScalar(input2Flt[0]);
    KN_PRINTAFLT(input2Element);

    MulFloatConstI(tflite::micro::GetTensorData<float>(output),
                   tflite::micro::GetTensorData<float>(input1), input2Element,
                   flat_size, act_min, act_max);
   // return kTfLiteOk;
  } else
#endif
#ifndef REMOVE_REFOP_SUPPORT
  {
    if (need_broadcast) {
      TF_LITE_MUL(BroadcastMul4DSlow);
    } else {
      TF_LITE_MUL(Mul);
    }
  }
#else
  { return kTfLiteError; }
#endif


  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));
  return status;
#undef TF_LITE_MUL
}

TfLiteStatus EvalMul(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);
  TfLiteStatus status = kTfLiteOk;
  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kMulInput1Tensor);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kMulInput2Tensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kMulOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data = *(static_cast<const OpData*>(node->user_data));

  switch (input1->type) {
    case kTfLiteInt16:
    case kTfLiteInt32:
    case kTfLiteInt8:
      status =
          EvalQuantized(context, node, params, data, input1, input2, output);
      break;

    case kTfLiteFloat32:
      status = EvalFloat(context, node, params, &data, input1, input2, output);
      break;

    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input1->type), input1->type);
      return kTfLiteError;
  }

  return status;
}

TfLiteStatus EvalInt8Mul(TfLiteContext* context, TfLiteNode* node) {
  // auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kMulInput1Tensor);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kMulInput2Tensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kMulOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data = *(static_cast<const OpData*>(node->user_data));

  if (kTfLiteInt8 != input1->type) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(input1->type), input1->type);
    return kTfLiteError;
  }

  auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);
  EvalQuantized(context, node, params, data, input1, input2, output);


  return kTfLiteOk;
}

TfLiteStatus EvalFloat32Mul(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kMulInput1Tensor);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kMulInput2Tensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kMulOutputTensor);
  TfLiteStatus status = kTfLiteOk;
  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data = *(static_cast<const OpData*>(node->user_data));
  if (kTfLiteFloat32 != input1->type) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(input1->type), input1->type);
    return kTfLiteError;
  }

  status = EvalFloat(context, node, params, &data, input1, input2, output);

  return status;
}
//}  // namespace mul

TFLMRegistration Register_MUL() {
  return tflite::micro::RegisterOp(InitMul,
          /* PrepareMul=*/PrepareMul,
          /*invoke=*/EvalMul);
}
TFLMRegistration Register_MUL_INT8() {
  return tflite::micro::RegisterOp(InitMul,
       
          /* PrepareMul=*/PrepareMul,
          /*invoke=*/EvalInt8Mul);
}
TFLMRegistration Register_MUL_FLOAT32() {
  return tflite::micro::RegisterOp(InitMul,
          /* PrepareMul=*/PrepareMul,
          /*invoke=*/EvalFloat32Mul);
}

//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
