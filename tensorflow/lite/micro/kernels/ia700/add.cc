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
#include "tensorflow/lite/kernels/internal/reference/add.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/integer_ops/add.h"
#include "tensorflow/lite/kernels/internal/reference/process_broadcast_shapes.h"
#endif
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/kernels/add.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/memory_helpers.h"

#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
#include "tensorflow/lite/micro/micro_utils.h"
namespace tflite {
//namespace ops {
//namespace micro {
//namespace add {

//constexpr int kAddInputTensor1 = 0;
//constexpr int kAddInputTensor2 = 1;
//constexpr int kAddOutputTensor = 0;

struct OpData {

  OpDataAdd AddOp; // from reference
  AScalar input1_multiplier_fr32;
  AScalar input2_multiplier_fr32;
  AScalar output_multiplier_fr32;

  AScalar input1_offset_fr32;
  AScalar input2_offset_fr32;
  AScalar output_offset_fr32;

  int opt_constraint;
  int opt_constraint_float;
};
#if 0 //replace in add common 
TfLiteStatus CalculateOpData(TfLiteContext* context, TfLiteAddParams* params,
                             const TfLiteTensor* input1,
                             const TfLiteTensor* input2, TfLiteTensor* output,
                             OpData* data) {
  data->requires_broadcast = !HaveSameShapes(input1, input2);

  if (output->type == kTfLiteUInt8 || output->type == kTfLiteInt8) {
    // 8bit -> 8bit general quantized path, with general rescalings
    data->input1_offset = -input1->params.zero_point;
    data->input2_offset = -input2->params.zero_point;
    data->output_offset = output->params.zero_point;
    data->left_shift = 20;
    const double twice_max_input_scale =
        2 * static_cast<double>(
                std::max(input1->params.scale, input2->params.scale));
    const double real_input1_multiplier =
        static_cast<double>(input1->params.scale) / twice_max_input_scale;
    const double real_input2_multiplier =
        static_cast<double>(input2->params.scale) / twice_max_input_scale;
    const double real_output_multiplier =
        twice_max_input_scale /
        ((1 << data->left_shift) * static_cast<double>(output->params.scale));

    QuantizeMultiplierSmallerThanOneExp(
        real_input1_multiplier, &data->input1_multiplier, &data->input1_shift);

    QuantizeMultiplierSmallerThanOneExp(
        real_input2_multiplier, &data->input2_multiplier, &data->input2_shift);

    QuantizeMultiplierSmallerThanOneExp(
        real_output_multiplier, &data->output_multiplier, &data->output_shift);

    TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
        context, params->activation, output, &data->output_activation_min,
        &data->output_activation_max));
  }

  return kTfLiteOk;
}
#endif

#ifdef HEMILITE_ADD_OPT

static void AddFloatConstI(float* output, const float* input1,
                           const AScalar& input2, const AScalar& act_min,
                           const AScalar& act_max, int size) {
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
    //  load_32x4_vr_a(VR_input2, UR_input2, input2);
    for (int ii = 0; ii < loopLim - 1; ii++) {
      convert_IEEE_float_to_32F_x2(VR_input1);

      VR_out = vadds(VR_input1, VR_input2, 0);

      load_32x2_vr_a(VR_input1, UR_input1, input1);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);

      store_32x2_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x2(VR_input1);

    VR_out = vadds(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);

    convert_32F_to_IEEE_float_x2(VR_out);

    store_32x2_vr_a(VR_out, UR_output, output);
    flush_32x2(UR_output, output);
  }
  if (remain) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);

    convert_IEEE_float_to_32F_x2(VR_input1);

    VR_out = vadds(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}

static void AddFloat(float* output, const float* input1, const float* input2,
                     const AScalar& act_min, const AScalar& act_max, int size) {
  //  const int size =
  // MatchingElementsSize( tflite::micro::GetTensorShape(input1),
  // tflite::micro::GetTensorShape(input2),
  // tflite::micro::GetTensorShape(output));

  int loopLim = size >> 1;
  int remain = (size & 1);
  vr64 VR_input1, VR_input2;
  vr64 VR_min, VR_max;

  ulsr32 UR_input1, UR_input2;
  vr64 VR_out;
  UR_input1 = align_32x2_load(input1);
  UR_input2 = align_32x2_load(input2);
  ulsr32 UR_output = align_32x2_store(output);

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
      VR_out = vadds(VR_input1, VR_input2, 0);
      load_32x2_vr_a(VR_input1, UR_input1, input1);
      load_32x2_vr_a(VR_input2, UR_input2, input2);

      VR_out = vmin(VR_max, VR_out);
      VR_out = vmax(VR_min, VR_out);
      convert_32F_to_IEEE_float_x2(VR_out);

      store_32x2_vr_a(VR_out, UR_output, output);
    }
    convert_IEEE_float_to_32F_x2(VR_input1);
    convert_IEEE_float_to_32F_x2(VR_input2);
    VR_out = vadds(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);

    store_32x2_vr_a(VR_out, UR_output, output);
    flush_32x2(UR_output, output);
  }
  if (remain) {
    load32x1_vr_postI(VR_input1, input1, INC1, VRQ0);
    load32x1_vr_postI(VR_input2, input2, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_input1);
    convert_IEEE_float_to_32F_x2(VR_input2);
    VR_out = vadds(VR_input1, VR_input2, 0);
    VR_out = vmin(VR_max, VR_out);
    VR_out = vmax(VR_min, VR_out);
    convert_32F_to_IEEE_float_x2(VR_out);
    store32x1_vr_postI(VR_out, output, INC1, VRQ0);
  }
}


static TfLiteStatus AddQuantizedInt8Sat(const OpData* data_ex, const int8_t* input1,
                         const int8_t* input2, int8_t* output, int n) {
  vr64 vr_input1, vr_input2;
  const OpDataAdd* data = &data_ex->AddOp;
  int loopLim = n >> 1;
  //
  // ulsr128 ur_input1, ur_input2;

  vr64 vr_offset1, vr_offset2;
  vr64 vr_multiplier_input1, vr_multiplier_input2;
  vr64 vr_multiplier_output;
  vr64 vr_output_offset;
  vr64 vr_shift_input1, vr_shift_input2;
  vr64 vr_raw_sum, vr_output, vr_q7_out;

  replicate_ar(vr_offset1, 0x3, data_ex->input1_offset_fr32.fr);  // Afloat
  replicate_ar(vr_offset2, 0x3, data_ex->input2_offset_fr32.fr);
  replicate_ar(vr_output_offset, 0x3, data_ex->output_offset_fr32.fr);
  replicate_ar(vr_multiplier_input1, 0x3, data_ex->input1_multiplier_fr32.fr);
  replicate_ar(vr_multiplier_input2, 0x3, data_ex->input2_multiplier_fr32.fr);

  replicate_ar(vr_multiplier_output, 0x3, data_ex->output_multiplier_fr32.fr);


  if (loopLim > 0)
  {
	  load8x2_vr_postI(vr_input1, input1, INC1);
	  load8x2_vr_postI(vr_input2, input2, INC1);

	  convert_16I_to_32F_x2(vr_input1, 0);
	  for (int ii = 0; ii < loopLim - 1; ii++) {
		  // q7*1<<left
		  convert_16I_to_32F_x2(vr_input2, 0);
		  vr_shift_input1 =
			  vexp_adj(vadds(vr_input1, vr_offset1, 0), 31 - 8 - data->left_shift);
		  vr_shift_input2 =
			  vexp_adj(vadds(vr_input2, vr_offset2, 0), 31 - 8 - data->left_shift);

		  vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
		  vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

		  vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0);  // Q24

		  vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

		  // convert to 8 bit rndsat-back
		  convert_32F_to_16I_x2(vr_output, 0, 0);

		  rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
		  vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
		  store8x1_vr_postI(vr_output, output, INC1, VRQ0);
		  store8x1_vr_postI(vr_output, output, INC1, VRQ1);
		  load8x2_vr_postI(vr_input1, input1, INC1);
		  load8x2_vr_postI(vr_input2, input2, INC1);
		  convert_16I_to_32F_x2(vr_input1, 0);
	  }
	  convert_16I_to_32F_x2(vr_input2, 0);
	  // add offset each input

	  // q7*1<<left
	  vr_shift_input1 =
		  vexp_adj(vadds(vr_input1, vr_offset1, 0), 31 - 8 - data->left_shift);
	  vr_shift_input2 =
		  vexp_adj(vadds(vr_input2, vr_offset2, 0), 31 - 8 - data->left_shift);

	  vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
	  vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

	  vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0);  // Q24

	  vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

	  // convert to 8 bit rndsat-back
	  convert_32F_to_16I_x2(vr_output, 0, 0);

	  rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
	  vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
	  store8x1_vr_postI(vr_output, output, INC1, VRQ0);
	  store8x1_vr_postI(vr_output, output, INC1, VRQ1);
  }
  // reminder
  if (n & 1) {
    load8x1_vr_postI(vr_input1, input1, INC1, VRQ0);
    load8x1_vr_postI(vr_input2, input2, INC1, VRQ0);

    convert_16I_to_32F_x2(vr_input1, 0);
    convert_16I_to_32F_x2(vr_input2, 0);

    vr_shift_input1 =
        vexp_adj(vadds(vr_input1, vr_offset1, 0), 31 - 8 - data->left_shift);
    vr_shift_input2 =
        vexp_adj(vadds(vr_input2, vr_offset2, 0), 31 - 8 - data->left_shift);

    vr_shift_input1 = vmuls(vr_multiplier_input1, vr_shift_input1, 0);
    vr_shift_input2 = vmuls(vr_multiplier_input2, vr_shift_input2, 0);

    vr_raw_sum = vadds(vr_shift_input1, vr_shift_input2, 0);  // Q24

    vr_output = vmacs(vr_output_offset, vr_raw_sum, vr_multiplier_output, 0, 0);

    // convert to 8 bit rndsat-back
    convert_32F_to_16I_x2(vr_output, 0, 0);
    // store 1 byt one
    rnd_sat_pack(vr_q7_out, VRQ0, vr_output, vr_output, 1);
    vr_output = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);
    store8x1_vr_postI(vr_output, output, INC1, VRQ0);
  }
  return kTfLiteOk;
}
#endif

static TfLiteStatus EvalAddFloat(TfLiteContext* context, TfLiteNode* node, TfLiteAddParams* params,
             const OpData* data_ex, const TfLiteEvalTensor* input1,
             const TfLiteEvalTensor* input2, TfLiteEvalTensor* output) {
  tflite::ArithmeticParams op_params;
  float output_activation_min, output_activation_max;

 
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);
  SetActivationParams(output_activation_min, output_activation_max, &op_params);

#define TF_LITE_ADD(opname)                                               \
  reference_ops::opname(op_params, tflite::micro::GetTensorShape(input1), \
                        tflite::micro::GetTensorData<float>(input1),      \
                        tflite::micro::GetTensorShape(input2),            \
                        tflite::micro::GetTensorData<float>(input2),      \
                        tflite::micro::GetTensorShape(output),            \
                        tflite::micro::GetTensorData<float>(output))

  KN_PRINT_SHAPE(tflite::micro::GetTensorShape(input2));
  KN_PRINT_SHAPE(tflite::micro::GetTensorShape(input1));
  KN_PRINT_SHAPE(tflite::micro::GetTensorShape(output));

  KN_PRINTD(data_ex->AddOp.requires_broadcast);
  KN_PRINTD(data_ex->opt_constraint_float);

  //  KN_PRINTF(op_params.float_activation_min);
  //  KN_PRINTF(op_params.float_activation_max);



#ifdef HEMILITE_ADD_OPT
  AScalar act_min, act_max;
  CalculateActivationRangeAflt(params->activation, &act_min, &act_max);

  if (data_ex->opt_constraint_float == 1) {
    const int flat_size =
        MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                             tflite::micro::GetTensorShape(input2),
                             tflite::micro::GetTensorShape(output));

	KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input1), flat_size);
	KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input2), flat_size);

    AddFloat(tflite::micro::GetTensorData<float>(output),
             tflite::micro::GetTensorData<float>(input1),
             tflite::micro::GetTensorData<float>(input2), act_min, act_max,
             flat_size);
   KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),      flat_size);
  } else if (data_ex->opt_constraint_float == 2) {
    AScalar input2Element;
    const int flat_size =
        MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                             tflite::micro::GetTensorShape(output));

    const float* input2Flt = tflite::micro::GetTensorData<float>(input2);
    KN_PRINTF(input2Flt[0]);
    input2Element = AScalar(input2Flt[0]);
    KN_PRINTAFLT(input2Element);
    AddFloatConstI(tflite::micro::GetTensorData<float>(output),
                   tflite::micro::GetTensorData<float>(input1), input2Element,
                   act_min, act_max, flat_size);
  }
  else if (data_ex->opt_constraint_float == 3) {
      // dim input1 [a,b,c,d], input2 = [d]
    // for loop all a*b*c for each d 
      const float* input1_data = tflite::micro::GetTensorData<float>(input1);
      const float* input2_data = tflite::micro::GetTensorData<float>(input2);
      float* output_data = tflite::micro::GetTensorData<float>(output);

      int internal_loop_count = tflite::micro::GetTensorShape(input2).FlatSize();
      int external_loop_count = tflite::micro::GetTensorShape(input1).FlatSize();
      /*
          tflite::micro::GetTensorData<int8_t>(output),
          MatchingElementsSize(tflite::micro::GetTensorShape(input1),
              tflite::micro::GetTensorShape(input2),
              tflite::micro::GetTensorShape(output));
              */
      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input1),
          ElementCount(*input1->dims));
      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input2),
          ElementCount(*input2->dims));

      for (int ii = 0; ii < external_loop_count; ii += internal_loop_count) // dim 2 , dim3
      {
          AddFloat(output_data, input1_data,
              input2_data, act_min, act_max,
              internal_loop_count);
          input1_data += internal_loop_count;
          output_data += internal_loop_count;

      }
      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
          ElementCount(*output->dims));
  }
  else
#endif
  {
 #ifndef REMOVE_REFOP_SUPPORT
    const OpDataAdd* data = &data_ex->AddOp;
    if (data->requires_broadcast) {
      TF_LITE_ADD(BroadcastAdd4DSlow);

    } else {
      TF_LITE_ADD(Add);
    }
    #else
return kTfLiteError;
    #endif
    //    KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
    //    ElementCount(*output->dims));
  }
#undef TF_LITE_ADD
    return kTfLiteOk;
}

static TfLiteStatus EvalAddQuantized(TfLiteContext* context, TfLiteNode* node,
                              TfLiteAddParams* params, const OpData* data_ex,
                              const TfLiteEvalTensor* input1,
                              const TfLiteEvalTensor* input2,
                              TfLiteEvalTensor* output) {
  const OpDataAdd* data = &data_ex->AddOp;
  if (output->type == kTfLiteInt16 || output->type == kTfLiteInt8) {
    tflite::ArithmeticParams op_params;
    op_params.left_shift = data->left_shift;
    op_params.input1_offset = data->input1_offset;
    op_params.input1_multiplier = data->input1_multiplier;
    op_params.input1_shift = data->input1_shift;
    op_params.input2_offset = data->input2_offset;
    op_params.input2_multiplier = data->input2_multiplier;
    op_params.input2_shift = data->input2_shift;
    op_params.output_offset = data->output_offset;
    op_params.output_multiplier = data->output_multiplier;
    op_params.output_shift = data->output_shift;
    SetActivationParams(data->output_activation_min,
                        data->output_activation_max, &op_params);

#define TF_LITE_ADD(type, opname, dtype)                         \
  type::opname(op_params, tflite::micro::GetTensorShape(input1), \
               tflite::micro::GetTensorData<dtype>(input1),      \
               tflite::micro::GetTensorShape(input2),            \
               tflite::micro::GetTensorData<dtype>(input2),      \
               tflite::micro::GetTensorShape(output),            \
               tflite::micro::GetTensorData<dtype>(output));
#if defined(HEMILITE_ADD_OPT)
if((data_ex->opt_constraint == 1) &&output->type == kTfLiteInt8)
{
	
		return AddQuantizedInt8Sat(
			data_ex, tflite::micro::GetTensorData<int8_t>(input1),
			tflite::micro::GetTensorData<int8_t>(input2),
			tflite::micro::GetTensorData<int8_t>(output),
			MatchingElementsSize(tflite::micro::GetTensorShape(input1),
				tflite::micro::GetTensorShape(input2),
				tflite::micro::GetTensorShape(output)));
		KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
			ElementCount(*output->dims));
}
else if ((data_ex->opt_constraint == 2) && output->type == kTfLiteInt8)
{
	// dim input1 [a,b,c,d], input2 = [d]
	// for loop all a*b*c for each d 
	const int8_t *input1_data = tflite::micro::GetTensorData<int8_t>(input1);
	const int8_t *input2_data = tflite::micro::GetTensorData<int8_t>(input2);
	int8_t *output_data = tflite::micro::GetTensorData<int8_t>(output);
	
	int internal_loop_count = tflite::micro::GetTensorShape(input2).FlatSize();
	int external_loop_count = tflite::micro::GetTensorShape(input1).FlatSize();
	/*
		tflite::micro::GetTensorData<int8_t>(output),
		MatchingElementsSize(tflite::micro::GetTensorShape(input1),
			tflite::micro::GetTensorShape(input2),
			tflite::micro::GetTensorShape(output));
			*/
	KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input1),
		ElementCount(*input1->dims));
	KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input2),
		ElementCount(*input2->dims));

	for (int ii = 0; ii <external_loop_count; ii+= internal_loop_count) // dim 2 , dim3
	{
		AddQuantizedInt8Sat(data_ex, input1_data,
			input2_data,
			output_data,
			internal_loop_count);
		input1_data += internal_loop_count;
		output_data += internal_loop_count;

	}
	KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
		ElementCount(*output->dims));
}

else
#endif
{
#ifndef REMOVE_REFOP_SUPPORT
    bool need_broadcast = reference_ops::ProcessBroadcastShapes(
        tflite::micro::GetTensorShape(input1),
        tflite::micro::GetTensorShape(input2), &op_params);
  switch (output->type) {
    case kTfLiteInt8:

    {
      //KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input1),
     //                  ElementCount(*input1->dims));
     // KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input2),
     //                  ElementCount(*input2->dims));
      if (need_broadcast) {
        TF_LITE_ADD(reference_integer_ops, BroadcastAdd4DSlow, int8_t);

        // KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
        //                 ElementCount(*output->dims));

      } else {
        TF_LITE_ADD(reference_integer_ops, Add, int8_t);
      }
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                       ElementCount(*output->dims));
    } break;
    case kTfLiteInt16: {
      if (need_broadcast) {
        reference_ops::BroadcastAdd4DSlow(
            op_params, tflite::micro::GetTensorShape(input1),
            tflite::micro::GetTensorData<int16_t>(input1),
            tflite::micro::GetTensorShape(input2),
            tflite::micro::GetTensorData<int16_t>(input2),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<int16_t>(output));
      } else {
        reference_ops::Add(op_params, tflite::micro::GetTensorShape(input1),
                           tflite::micro::GetTensorData<int16_t>(input1),
                           tflite::micro::GetTensorShape(input2),
                           tflite::micro::GetTensorData<int16_t>(input2),
                           tflite::micro::GetTensorShape(output),
                           tflite::micro::GetTensorData<int16_t>(output),
                           false);
      }
      break;
    }
    default:
      return kTfLiteError;
      break;
  }
#else

    return kTfLiteError;
#endif
          //  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
       //                  ElementCount(*output->dims));
#undef TF_LITE_ADD
  }
    }// end of uint or int
  return kTfLiteOk;
}

void* AddInit(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus AddPrepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);



  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input1 =
      micro_context->AllocateTempInputTensor(node, kAddInputTensor1);
  TF_LITE_ENSURE(context, input1 != nullptr);
  TfLiteTensor* input2 =
      micro_context->AllocateTempInputTensor(node, kAddInputTensor2);
  TF_LITE_ENSURE(context, input2 != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kAddOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

  OpData* data_ex = static_cast<OpData*>(node->user_data);
  OpDataAdd *data = static_cast<OpDataAdd *>(&data_ex->AddOp);

  auto* params = reinterpret_cast<TfLiteAddParams*>(node->builtin_data);
  int input1_count = ElementCount(*input1->dims);
  int input2_count = ElementCount(*input2->dims);
  int output_count = ElementCount(*output->dims);
  //   MatchingFlatSize();
  KN_PRINTD(input1_count);
  KN_PRINTD(input2_count);
  KN_PRINTD(output_count);
  // tflite::dmx1a::ConvertQ31ToAfloat(&data->input1_multiplier,
  // &data->input1_multiplier_fr32, data->input1_offset);
  TF_LITE_ENSURE_STATUS(
      CalculateOpDataAdd(context, params, input1, input2, output, data));

  data_ex->opt_constraint = 0;
  data_ex->opt_constraint_float = 0;
#if defined(HEMILITE_ADD_OPT)
  //data->opt_constraint = 0;
  if ((output->type == kTfLiteInt8) && (data->output_activation_min == -128 &&
	  data->output_activation_max == 127))
  {
	  KN_PRINTD(data->requires_broadcast);
	  if (0 == data->requires_broadcast)
		  data_ex->opt_constraint = 1;

	  // type 2 optimizaition
#if 1
	  // determine input 2 is match the latest one
	  {
		  // int input2_count = tflite::micro::GetTensorShape(input2).FlatSize()
		  int input_shape0 = input1->dims->data[input1->dims->size-1]; // Dims(0);
		  if (input_shape0 == input2_count && 
			  output_count == input1_count && 
			  (input_shape0&3)==0)
			  data_ex->opt_constraint = 2;  // 
	  }
#endif 
  }
  if (data_ex->opt_constraint) {
	  tflite::ConvertQ31ToAfloat(data->input1_multiplier,
                               data_ex->input1_multiplier_fr32,
		  data->input1_shift);
	  tflite::ConvertQ31ToAfloat(data->input2_multiplier,
                                     data_ex->input2_multiplier_fr32,
		  data->input2_shift);
	  tflite::ConvertQ31ToAfloat(data->output_multiplier,
                                     data_ex->output_multiplier_fr32,
		  31 - 14 + data->output_shift);  //-19

	  tflite::ConvertQ31ToAfloat(data->input1_offset,
                                     data_ex->input1_offset_fr32,
		  31 - 7);
          tflite::ConvertQ31ToAfloat(data->input2_offset,
                                     data_ex->input2_offset_fr32,
		  31 - 7);
          tflite::ConvertQ31ToAfloat(data->output_offset,
                                     data_ex->output_offset_fr32,
		  31 - 7);
  }
  // only min = -128 and max=127 acceptable for rnd_sat_pack

  if (output->type == kTfLiteFloat32)
  {


	  data_ex->opt_constraint_float =
        input1_count == input2_count &&
		  input2_count == output_count 
		  ? 1
		  : 0;


	  // runtime change ?
	  // TODO: compare each dims in input1 and output;
	  // input2 only 1

	  // determine input 2 is match the latest one

	  if (1 == input2_count && output_count == input1_count)
            data_ex->opt_constraint_float = 2;  // FloatAddWithScalarBroadcast

      // case 3: input 1: 1,1,3,64, input 2, 64, output 1,1,3,64
      {
          // int input2_count = tflite::micro::GetTensorShape(input2).FlatSize()
          int input_shape0 = input1->dims->data[input1->dims->size - 1]; // Dims(0);
          if (input_shape0 == input2_count &&
              output_count == input1_count &&
              (input_shape0 & 3) == 0)
            data_ex->opt_constraint_float = 3;  // 
      }
  }
  KN_PRINTD(data->output_activation_min);
  KN_PRINTD(data->output_activation_max);

#endif
  KN_PRINTD(data_ex->opt_constraint);

  
  micro_context->DeallocateTempTfLiteTensor(input1);
  micro_context->DeallocateTempTfLiteTensor(input2);
  micro_context->DeallocateTempTfLiteTensor(output);

  return kTfLiteOk;
}

TfLiteStatus EvalAdd(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteAddParams*>(node->builtin_data);

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kAddInputTensor1);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kAddInputTensor2);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kAddOutputTensor);
    TfLiteStatus status = kTfLiteOk;
  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData* data_ex = static_cast<const OpData*>(node->user_data);



  if (output->type == kTfLiteFloat32) {
    status = EvalAddFloat(context, node, params, data_ex, input1, input2, output);
  } else if (output->type == kTfLiteInt16 || output->type == kTfLiteInt8) {
    status = EvalAddQuantized(context, node, params, data_ex,
                                                input1, input2, output);
  } 
#ifndef REMOVE_REFOP_SUPPORT
  else if (output->type == kTfLiteInt32) {
    tflite::ArithmeticParams op_params;
    SetActivationParams(std::numeric_limits<int32_t>::lowest(),
                        std::numeric_limits<int32_t>::max(), &op_params);
    const OpDataAdd* data = static_cast<const OpDataAdd*>(&data_ex->AddOp);
    if (data->requires_broadcast) {
      reference_ops::BroadcastAdd4DSlow(
          op_params, tflite::micro::GetTensorShape(input1),
          tflite::micro::GetTensorData<int32_t>(input1),
          tflite::micro::GetTensorShape(input2),
          tflite::micro::GetTensorData<int32_t>(input2),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int32_t>(output));
    } else {
      reference_ops::Add(op_params, tflite::micro::GetTensorShape(input1),
                         tflite::micro::GetTensorData<int32_t>(input1),
                         tflite::micro::GetTensorShape(input2),
                         tflite::micro::GetTensorData<int32_t>(input2),
                         tflite::micro::GetTensorShape(output),
                         tflite::micro::GetTensorData<int32_t>(output));
    }
  
  
  }
#endif
  else {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(output->type), output->type);
    return kTfLiteError;
  }

  return status;
}


TfLiteStatus EvalAddInt8(TfLiteContext* context, TfLiteNode* node) {

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kAddInputTensor1);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kAddInputTensor2);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kAddOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData* data = static_cast<const OpData*>(node->user_data);

    if(output->type != kTfLiteInt8 ) {

       TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(output->type), output->type);
    return kTfLiteError;

 
  } 
#if defined(HEMILITE_ADD_OPT)
  if(data->opt_constraint)
  {
   return AddQuantizedInt8Sat(
              data, tflite::micro::GetTensorData<int8_t>(input1),
              tflite::micro::GetTensorData<int8_t>(input2),
              tflite::micro::GetTensorData<int8_t>(output),
              MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                                   tflite::micro::GetTensorShape(input2),
                                   tflite::micro::GetTensorShape(output))); 
  }else
#endif
  {
	  TfLiteStatus status = kTfLiteOk;
	  auto* params = reinterpret_cast<TfLiteAddParams*>(node->builtin_data);
	  status = EvalAddQuantized(context, node, params, data,
		  input1, input2, output);

    return status;
      }

}
TfLiteStatus EvalAddFloat32(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteAddParams*>(node->builtin_data);

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kAddInputTensor1);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kAddInputTensor2);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kAddOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData* data = static_cast<const OpData*>(node->user_data);
    if(output->type != kTfLiteFloat32) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(output->type), output->type);
    return kTfLiteError;

 
  } 
 EvalAddFloat(context, node, params, data, input1, input2, output);
    
  return kTfLiteOk;
}
//}  // namespace add

TFLMRegistration Register_ADD() {
  return tflite::micro::RegisterOp(AddInit,
          /*prepare=*/AddPrepare,
          /*invoke=*/EvalAdd);
}
TFLMRegistration Register_ADD_INT8() {
  return tflite::micro::RegisterOp(AddInit,
          /*prepare=*/AddPrepare,
          /*invoke=*/EvalAddInt8);
}
TFLMRegistration Register_ADD_FLOAT32() {
  return tflite::micro::RegisterOp(AddInit,
          /*prepare=*/AddPrepare,
          /*invoke=*/EvalAddFloat32);
}

//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
