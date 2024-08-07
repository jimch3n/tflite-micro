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

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/ia8201/config.h"

#if 1  // ndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/integer_ops/mean.h"
#include "tensorflow/lite/kernels/internal/reference/reduce.h"
#endif
#include "tensorflow/lite/kernels/internal/quantization_util.h"

#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/reduce.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"

#include "tensorflow/lite/micro/micro_utils.h"
namespace tflite {
//namespace ops {
//namespace micro {
//namespace reduce {
#ifndef REMOVE_REFOP_SUPPORT
//constexpr int kMaxNumberOfAxis = 4;
//constexpr int kMaxNumberOfReducedAxis = 2;
#endif
struct OpData {

  struct OpDataReduce ReduceOp;


  tflite::MeanParams op_params;  // Prepare - once
  bool special_case_4d_axes_1_and_2;
  AScalar input_scale_aflt;
  AScalar output_scale_aflt;
  AScalar bias_aflt;
  AScalar scale_aflt;  // input/output
  AScalar inv_count;
  int num_elements_in_axis;
  int num_input_dim0;  // per next
  int opt_constraint;
  int opt_constraint_float;
};

void* InitReduce(TfLiteContext* context, const char* buffer, size_t length) {
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus PrepareSimple(TfLiteContext* context, TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  // Inputs Tensor (dtype depends on quantization):
  // [0] = Input
  // [1] = Axis
  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, 0);

  // Outputs Tensor (dtype depends on quantization):
  // [0] = Output

  // Validate number of inputs and outputs
  TF_LITE_ENSURE_EQ(context, node->inputs->size, 2);
  TF_LITE_ENSURE_EQ(context, node->outputs->size, 1);

  // Validate axis type
  TfLiteTensor* axis = micro_context->AllocateTempInputTensor(node, 1);
  TF_LITE_ENSURE(context, axis != nullptr);
  TF_LITE_ENSURE_TYPES_EQ(context, axis->type, kTfLiteInt32);

  if (input->type == kTfLiteInt8) {
    OpData* data_ex = static_cast<OpData*>(node->user_data);
    OpDataReduce* data = &data_ex->ReduceOp;
    TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, 0);
    const double real_multiplier = static_cast<double>(input->params.scale) /
                                   static_cast<double>(output->params.scale);
    QuantizeMultiplier(real_multiplier, &data->multiplier, &data->shift);
    micro_context->DeallocateTempTfLiteTensor(output);
  }

  micro_context->DeallocateTempTfLiteTensor(axis);
  micro_context->DeallocateTempTfLiteTensor(input);
  return kTfLiteOk;
}
static void ResolveAxis(const int* axis_data, int axis_count,
	tflite::MeanParams* op_params) {
	int i = 0;
	for (; i < axis_count; ++i) {
		op_params->axis[i] = static_cast<int16_t>(axis_data[i]);
	}
	for (; i < 4; ++i) {
		op_params->axis[i] = 1;
	}
	op_params->axis_count = axis_count;
}

TfLiteStatus PrepareMax(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_OK(context, PrepareSimple(context, node));

  OpData* op_data_ex = static_cast<OpData*>(node->user_data);

  OpDataReduce* op_data = static_cast<OpDataReduce*>(&op_data_ex->ReduceOp);

  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, 0);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, 0);
  TfLiteTensor* axis = micro_context->AllocateTempInputTensor(node, 1);

  op_data->input_scale = input->params.scale;
  op_data->output_scale = output->params.scale;
  op_data->num_output_elements = NumElements(output);
  //
  int output_size = NumElements(output);
  RuntimeShape input_shape = GetTensorShape(input);
  //const TfLiteEvalTensor* axis = tflite::micro::GetEvalInput(context, node, 1);

 
  op_data->num_axis = NumElements(axis);
  ResolveAxis(GetTensorData<int>(axis),op_data->num_axis,
	  &op_data_ex->op_params);
  op_data_ex->special_case_4d_axes_1_and_2 =
      input->dims->size == 4 && op_data_ex->op_params.axis_count == 2 &&
      ((op_data_ex->op_params.axis[0] == 1 &&
        op_data_ex->op_params.axis[1] == 2) ||
       (op_data_ex->op_params.axis[0] == 2 &&
        op_data_ex->op_params.axis[1] == 1));

  context->RequestScratchBufferInArena(context, sizeof(int) * NumElements(output),
                                       &op_data->temp_buffer_idx);
  context->RequestScratchBufferInArena(
      context, sizeof(int) * static_cast<int>(ElementCount(*axis->dims)),
      &op_data->resolved_axis_idx);

  op_data_ex->opt_constraint = 0;

#if defined(DMX1A_REDUCE_MAX_OPT) || defined(HMD1A_REDUCE_MAX_OPT)
  op_data_ex->opt_constraint = (output_size & 3) == 0 &&
	  (input->type == kTfLiteInt8) &&
                               op_data_ex->special_case_4d_axes_1_and_2;

  if (op_data_ex->opt_constraint) {
	  //const TfLiteTensor* axi = GetInput(context, node, 1);

	  RuntimeShape axis_shape = GetTensorShape(axis);

	  op_data_ex->input_scale_aflt = AScalar(op_data->input_scale);
      op_data_ex->output_scale_aflt = AScalar(op_data->output_scale);
      op_data_ex->scale_aflt =
              op_data_ex->input_scale_aflt / op_data_ex->output_scale_aflt;

	  op_data_ex->num_input_dim0 = input_shape.Dims(0);
	 // op_data->inv_count = AScalar(num_elements_in_axis).inverse();
	  // -input_zero_point * scale;
          op_data_ex->bias_aflt =
              AScalar(-op_data->input_zp) * op_data_ex->scale_aflt;

	  // KN_PRINTD(num_elements_in_axis);
  }
#endif
  KN_PRINTD(op_data_ex->opt_constraint);

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  micro_context->DeallocateTempTfLiteTensor(axis);
  return kTfLiteOk;
}


TfLiteStatus PrepareMeanOrSum(TfLiteContext* context, TfLiteNode* node) {

  OpData* op_data_ex = reinterpret_cast<OpData*>(node->user_data);

  OpDataReduce* op_data =
      reinterpret_cast<OpDataReduce*>(&op_data_ex->ReduceOp);
  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, 0);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, 0);
  TfLiteTensor* axis = micro_context->AllocateTempInputTensor(node, 1);

  if (input->type == kTfLiteInt8 || input->type == kTfLiteInt16) {
    const double real_multiplier = static_cast<double>(input->params.scale) /
                                   static_cast<double>(output->params.scale);
    QuantizeMultiplier(real_multiplier, &op_data->multiplier, &op_data->shift);
  }

  int output_size = NumElements(output);
  op_data->num_output_elements = output_size;

  op_data->num_axis = static_cast<int>(ElementCount(*axis->dims));
  const TfLiteEvalTensor* axis_eval = tflite::micro::GetEvalInput(context, node, 1);
  // tflite::MeanParams op_params;
  ResolveAxis(tflite::micro::GetTensorData<int>(axis_eval), op_data->num_axis,
              &op_data_ex->op_params);
  op_data_ex->special_case_4d_axes_1_and_2 =
      input->dims->size == 4 && op_data_ex->op_params.axis_count == 2 &&
      ((op_data_ex->op_params.axis[0] == 1 &&
        op_data_ex->op_params.axis[1] == 2) ||
       (op_data_ex->op_params.axis[0] == 2 &&
        op_data_ex->op_params.axis[1] == 1));
  RuntimeShape input_shape = GetTensorShape(input);
  int num_elements_in_axis = 1;
  for (int ax = 0; ax < op_data->num_axis; ax++) {
    int axis_dim = op_data_ex->op_params.axis[ax];
    // KN_PRINTD( input_shape.Dims(axis_dim));
	if (axis_dim >= 0)
	{
		num_elements_in_axis *= input_shape.Dims(axis_dim);
	}
	else {
		// < 0 mean last one-1, last one
		num_elements_in_axis *= input_shape.Dims(input_shape.DimensionsCount() + axis_dim);
	}
  }
  op_data_ex->num_elements_in_axis = num_elements_in_axis;
  op_data_ex->opt_constraint = 0;
  op_data_ex->opt_constraint_float = 0;
  if (input->type == kTfLiteInt8 || input->type == kTfLiteInt16) {
    context->RequestScratchBufferInArena(context, output_size * sizeof(int32_t),
                                         &op_data->temp_buffer_idx);
    op_data->input_zp = input->params.zero_point;
    op_data->input_scale = input->params.scale;
    op_data->output_zp = output->params.zero_point;
    op_data->output_scale = output->params.scale;

    op_data_ex->num_input_dim0 = input_shape.Dims(0);  // odd at-least

    
#if defined(DMX1A_MEAN_OPT) || defined(HMD1A_MEAN_OPT)
    op_data_ex->opt_constraint = (output_size & 7) == 0 &&
                              (input->type == kTfLiteInt8) &&
                                 op_data_ex->special_case_4d_axes_1_and_2;

    if (op_data_ex->opt_constraint) {
      //const TfLiteTensor* axis2 = GetInput(context, node, 1);

      RuntimeShape axis_shape = GetTensorShape(axis);

      op_data_ex->input_scale_aflt = AScalar(op_data->input_scale);
      op_data_ex->output_scale_aflt = AScalar(op_data->output_scale);
      op_data_ex->scale_aflt =
          op_data_ex->input_scale_aflt / op_data_ex->output_scale_aflt;

      op_data_ex->num_input_dim0 = input_shape.Dims(0);
      op_data_ex->inv_count = AScalar(num_elements_in_axis).inverse();
      // -input_zero_point * scale;
      op_data_ex->bias_aflt =
          AScalar(-op_data->input_zp) * op_data_ex->scale_aflt;

      // KN_PRINTD(num_elements_in_axis);
    }
#endif
  }

  TF_LITE_ENSURE_OK(context, PrepareSimple(context, node));
  // TODO(b/144955155): Support uint8_t(b/144955155) and int8_t(b/144955018)

  if (input->type == kTfLiteFloat32) {
    TF_LITE_ENSURE_OK(context, PrepareSimple(context, node));

    // OpData* op_data = static_cast<OpData*>(node->user_data);
    // const TfLiteTensor* input = GetInput(context, node, 0);
    // const TfLiteTensor* output = GetOutput(context, node, 0);
    // const TfLiteTensor* axis = GetInput(context, node, 1);

    op_data->input_scale = input->params.scale;
    op_data->output_scale = output->params.scale;
    op_data->num_output_elements = NumElements(output);
    // ? remove
    context->RequestScratchBufferInArena(
        context, sizeof(int) * output_size, &op_data->temp_buffer_idx);
    context->RequestScratchBufferInArena(
        context, sizeof(int) * static_cast<int>(ElementCount(*axis->dims)),
        &op_data->resolved_axis_idx);

    
#if defined(DMX1A_MEAN_OPT) || defined(HMD1A_MEAN_OPT)

    // FIXME: float need check and verify 
    if ((output_size & 3) == 0 && 1 == op_data->num_axis &&
        (1 == op_data_ex->op_params
                  .axis[0]))  // axis == 1, and output[0] == input[0]
    {
      op_data_ex->opt_constraint_float = 2;  // 2;
    }else if (//(output_size & 3) == 0 &&
        1 == op_data->num_axis && (-1 == op_data_ex->op_params.axis[0]) &&
        output_size == 1)  // axis == 1, and output[0] == input[0]
	{
      op_data_ex->opt_constraint_float = 3;
    }// type 4: input 1,150,1,128, axis: 1,2 -> output 1,128
    //FIXME: more generic condition
#if 1
    else if ((output_size & 3) == 0 && 
        2 == op_data->num_axis &&
             (1 == op_data_ex->op_params.axis[0] &&
              2 == op_data_ex->op_params.axis[1]))
    {
      op_data_ex->opt_constraint_float = 4;
    }
#endif

    KN_PRINTD(op_data_ex->opt_constraint_float);
    if (op_data_ex->opt_constraint_float) {
      //const TfLiteTensor* axis = GetInput(context, node, 1);
      //  RuntimeShape input_shape = GetTensorShape(input);
      RuntimeShape axis_shape = GetTensorShape(axis);

      op_data_ex->input_scale_aflt = AScalar(op_data->input_scale);
      op_data_ex->output_scale_aflt = AScalar(op_data->output_scale);
      op_data_ex->scale_aflt =
          op_data_ex->input_scale_aflt / op_data_ex->output_scale_aflt;

      op_data_ex->num_input_dim0 = input_shape.Dims(0);
      op_data_ex->inv_count = AScalar(num_elements_in_axis).inverse();
      // -input_zero_point * scale;
      op_data_ex->bias_aflt =
          AScalar(-op_data->input_zp) * op_data_ex->scale_aflt;
    }
#endif
  }
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  micro_context->DeallocateTempTfLiteTensor(axis);
  return kTfLiteOk;
}

#ifdef DMX1A_REDUCE_MAX_OPT

int ReduceMaxQuantizedInt8(
	const OpData *data,
	const int8_t *x,  // align up16 buffer, zero paddding
	int8_t *pOut, int32_t *pScratchOuput, int n, int depth) {
	// int n4 = (n)>>2; // align-up 4 padding 16 byte zero
	vr128 VR_data, VR_max, VR_out;

	int m2 = (depth + 3) >> 2;
	const int8_t *pData = x;
	int8_t *pDataGroup = (int8_t *)pData;
	int32_t *pDst = pScratchOuput;
	int8_t *pY = pOut;
	// int idx;
	mir30 mir_idx;
	int n4 = (n / depth);  // >> 2;
	int cvt_32f = 7;
	int depthInc = (depth + 3) >> 2;
#ifdef KN_DEBUG
	CHECK_ALIGN_4(pData);
#endif

	for (int jj = 0; jj < m2; jj++) {
		pData = pDataGroup;
		load32x1_vr_postR(VR_data, pData, depthInc, VRQ0);

		VR_out = shift8_into32_arith(VR_data, 24, 0, VRQ0);

		convert_16I_to_32F_x4(VR_out, cvt_32f);
		vmaxmin_init(VR_max, VR_out, mir_idx);

		for (int ii = 0; ii < n4 - 1; ii++) {
			load32x1_vr_postR(VR_data, pData, depthInc, VRQ0);

			VR_out = shift8_into32_arith(VR_data, 24, 0, VRQ0);

			convert_16I_to_32F_x4(VR_out, cvt_32f);
			vmax_idx(VR_max, VR_out, mir_idx);
		}

		convert_32F_to_16I_x4(VR_max, 15, 1);  // rounding
		VR_max = shift32_arith(VR_max, (unsigned)-16, 0);

		store32x4_vr_postI(VR_max, pDst, INC1);

		pDataGroup += 4;  // byte ?
	}
	int m4 = depth >> 2;
	pDst = pScratchOuput;
	if (m4 > 0) {
		ulsr128 UR_Y = align_8x4_store(pY);
		for (int jj = 0; jj < m4; jj++) {
			load32x4_vr_postI(VR_max, pDst, INC1);
			//SATURATE_INT32_VR128(VR_max, VR_max, data->activation_min,
			//	data->activation_max);
			VR_out = shift32_arith(VR_max, 24, 0);

			store_8x4_vr_a(VR_out, UR_Y, pY);
		}
		flush_8x4(UR_Y, pY);
	}

	for (int jj = 0; jj < (depth & 3); jj++) {
		load32x1_vr_postI(VR_max, pDst, INC1, VRQ0);
		//SATURATE_INT32_VR_IDX(VR_max, VR_max, data->activation_min,
		//	data->activation_max, VRQ0);
		VR_out = shift32_arith(VR_max, 24, 0);
		store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
	}
	return 0;
}

#endif
#ifdef DMX1A_MEAN_OPT
void ReduceMeanQuantizedInt8(OpData* data, const int8_t* input, int8_t* output,
                             int32_t* temp_buffer, int sign) {
  int32_t* pY = (int32_t*)output;
  AScalar Scale = data->scale_aflt;
  AScalar invScale = data->inv_count;
  AScalar Bias = data->bias_aflt;
  int num_elements_in_axis = data->num_elements_in_axis;
  // int total_input = 12*8*256;
  int total_output = data->ReduceOp.num_output_elements;
  int groupOutputAU8 = (((total_output + 7) >> 3));
  int groupOutput4 = total_output >> 2;
  int blockInput = num_elements_in_axis >> 1;
  int nextGroupInput;
  int32_t* pDst = temp_buffer;

  int exp_fxp =
      30;  //(sign == 3 )? 15: ((sign == 1)? 16: 17); // 31-(14+2), 31-

  vr128 VR_const_one;
  vr128 VR_scale, VR_bias, VR_invCount;
  ulsr128 UR_Dst = align_32x4_store(pDst);
  replicate_ar(VR_const_one, 0xf, 0x01010101);

  replicate_ar(VR_scale, 0xf, Scale.fr);
  replicate_ar(VR_bias, 0xf, Bias.fr);
  replicate_ar(VR_invCount, 0xf, invScale.fr);

  if (total_output >= 8)  // FIXME: AND DIM0 == 1, DIM3 = total_output
  {
    // per group, 8 elements
    nextGroupInput = total_output >> 3;

    for (int ii = 0; ii < groupOutputAU8; ii++) {
      vr128 VR_x;
      vr128 VR_acc = vseta_vr(0, 0, 0);
      mov_AccExtend_vr(VR_acc);
      int32_t* pInput1 = (int32_t*)input + ii * 2;
      load32x2_vr_postR(VR_x, pInput1, nextGroupInput, VRL);
      load32x2_vr_postR(VR_x, pInput1, nextGroupInput, VRH);
      WUR_MvmAux(0);

      for (int jj = 0; jj < blockInput - 1; jj++)  // input 2,
      {
        vr128 VR_y = vexp_adji(VR_x, 0);
        mac8bx8b(VR_acc, VR_y, VR_const_one, sign);

        load32x2_vr_postR(VR_x, pInput1, nextGroupInput, VRL);
        load32x2_vr_postR(VR_x, pInput1, nextGroupInput, VRH);
      }
      mac8bx8b(VR_acc, VR_x, VR_const_one, sign);
      // output sum * 2 fix-point if required

      //store32x4_vr_postI(VR_acc, pDst, INC1);
      //store_AccExtend_postI(pDst, INC1);
	  store_32x4_vr_a(VR_acc, UR_Dst, pDst);
	  store_32x4_vr_a(mov_vr_AccExtend(), UR_Dst, pDst);
	
    }
	flush_32x4(UR_Dst, pDst);
  }

  vr128 VR_xor_0x80;

  if (data->ReduceOp.output_zp == -128) {
    replicate_ar(VR_xor_0x80, 0xf, 0x80808080);
  } else {
    replicate_ar(VR_xor_0x80, 0xf, 0x00000000);
  }
  int32_t* pSrc = temp_buffer;
  ulsr128 UR_Src = align_32x4_load(pSrc);
  for (int ii = 0; ii < groupOutput4; ii++) {
    vr128 VR_acc, VR_out, VR_q7_out;
	load_32x4_vr_a(VR_acc, UR_Src, pSrc); // , INC1);
    convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ0);
    convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ1);
    convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ2);
    convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ3);

    VR_out = vmuls(VR_acc, VR_invCount, 0);  // / num_element_in_axis
    VR_out = vmacs_adj(VR_bias, VR_out, VR_scale, 0, 0);  // acc
    //	VR_out = vexp_adji(VR_out, 8);
    convert_32F_to_16I_x4(VR_out, (unsigned int)15 - 8, 0);

    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);

    VR_q7_out = vbool(VR_q7_out, VR_xor_0x80, 0x6);

    store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
  }

  if (total_output & 3) {
    for (int ii = 0; ii < (total_output & 3); ii++) {
      vr128 VR_acc, VR_out, VR_q7_out;
      load32x1_vr_postI(VR_acc, pSrc, INC1, VRQ0);
      convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ0);

      VR_out = vmuls(VR_acc, VR_invCount, 0);  // / num_element_in_axis
      VR_out = vmacs_adj(VR_bias, VR_out, VR_scale, 0, 0);  // acc
      //	VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)15 - 8, 0);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      VR_q7_out = vbool(VR_q7_out, VR_xor_0x80, 0x6);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
    }
  }
}
#endif
#if defined(HMD1A_MEAN_OPT)
void ReduceMeanorSumFloat(OpData* data, const TfLiteEvalTensor* inputTensor, const float* input, float* output,
    int mean) {
    float* pY = (float*)output;
    // AScalar Scale = data->scale_aflt;
    AScalar invScale = data->inv_count;
    // AScalar Bias = data->bias_aflt;
    int num_elements_in_axis = data->num_elements_in_axis;
    // int total_input = 12*8*256;
    int total_output = data->ReduceOp.num_output_elements;
    // int groupOutputAU4 = (((total_output + 3) >> 2));
    int groupOutput2 = total_output >> 1;
    int blockInput = num_elements_in_axis;  // >> 2;
    // int nextGroupInput;

    // vr128 VR_const_one;
    atbool xt_mean = atbool(mean ? 0x3 : 0);
    
    vr64 VR_invCount;
    vr64 VR_x0;
    replicate_ar(VR_invCount, 0x3, invScale.fr);

    if (2 == data->opt_constraint_float) {
        float* pInput0;
        // nextGroupInput = total_output >> 2;
        ulsr32 UR_out = align_32x2_store(pY);
        pInput0 = (float*)input;
        if (groupOutput2 > 0)
        {
            for (int ii = 0; ii < groupOutput2; ii++) {
                vr64 VR_y0 = vseta_vr(0,  0);


                float* pInputBlk = pInput0;
                ulsr32 UR_x = align_32x2_load(pInput0);
                load_32x2_vr_a(VR_x0, UR_x, pInput0);

                for (int jj = 1; jj < blockInput; jj++)  // input 2,
                {
                    float* pInput2 = (float*)pInputBlk + jj * total_output;
                    convert_IEEE_float_to_32F_x2(VR_x0);

                    VR_y0 = vadds(VR_y0, VR_x0, 0);

                    UR_x = align_32x2_load(pInput2);
                    load_32x2_vr_a(VR_x0, UR_x, pInput2);
                }
                convert_IEEE_float_to_32F_x2(VR_x0);
                VR_y0 = vadds(VR_y0, VR_x0, 0);

                // if (mean)
                {
                    vr64 VR_mean = vmuls(VR_y0, VR_invCount, 0);

                    VR_y0 = vsel(VR_mean, VR_y0, xt_mean);
                }
                convert_32F_to_IEEE_float_x2(VR_y0);
                store_32x2_vr_a(VR_y0, UR_out, pY);  // , INC1);
            }
            flush_32x2(UR_out, pY);
        }
        // one 1 output
        pInput0 = (float*)input + (groupOutput2) * 2;
        //for (int ii = 0; ii < (total_output & 3); ii++) 
        if(total_output&1){
            vr64 VR_y0 = vseta_vr(0,  0);
            float* pInput1 = pInput0;
            load32x1_vr_postR(VR_x0, pInput1, total_output, VRQ0);
            for (int jj = 0; jj < blockInput - 1; jj++)  // input 2,
            {
                convert_IEEE_float_to_32F_x2(VR_x0);
                VR_y0 = vadds(VR_y0, VR_x0, 0);
                load32x1_vr_postR(VR_x0, pInput1, total_output, VRQ0);
            }
            convert_IEEE_float_to_32F_x2(VR_x0);
            VR_y0 = vadds(VR_y0, VR_x0, 0);
            // if (mean)
            {
                vr64 VR_mean = vmuls(VR_y0, VR_invCount, 0);

                VR_y0 = vsel(VR_mean, VR_y0, xt_mean);
            }
            convert_32F_to_IEEE_float_x2(VR_y0);
            store32x1_vr_postI(VR_y0, pY, INC1, VRQ0);
            // load32x1_vr_postR(VR_x0, pInput0, nextGroupInput, VRQ0);
        }
    }

    else if (3 == data->opt_constraint_float) // for axis -1 is , output is 1
    {
        int loopLim = blockInput >> 1;
        vr64 VR_input;
        AScalar inv_count = AScalar(blockInput).inverse();
        vr64 VR_sum = vseta_vr(kConstTable_Zero,  0);

        float* pInput0;
        pInput0 = (float*)input;
        ulsr32 UR_Input = align_32x2_load(pInput0);
        if (loopLim > 0)
        {
            load_32x2_vr_a(VR_input, UR_Input, pInput0);
            for (int ii = 0; ii < loopLim - 1; ii++)
            {
                convert_IEEE_float_to_32F_x2(VR_input);
                VR_sum = vadds(VR_sum, VR_input, 0);
                load_32x2_vr_a(VR_input, UR_Input, pInput0);
            }
            convert_IEEE_float_to_32F_x2(VR_input);
            VR_sum = vadds(VR_sum, VR_input, 0);

        }
        VR_input = vseta_vr(kConstTable_Zero, 0);
        //for (int ii = 0; ii < (blockInput & 3); ii++)
        if(1& blockInput)
        {
            load32x1_vr_postI(VR_input, pInput0, INC1, VRQ0);
            convert_IEEE_float_to_32F_x2(VR_input);
            VR_sum = vadds(VR_sum, VR_input, 0);
        }
        fr32 fr_sum = fadds(get_VRL(VR_sum), get_VRH(VR_sum), 0);
        //dsums_L(VR_sum, VR_sum, 0, 0);
       // dsums_L(VR_sum, VR_sum, 0, 0);
        //AScalar ove32_ar_vr_idx(VR_sum, VRQ0);
        AScalar total = fr_sum; //move32_fr_vr_idx(VR_sum, VRQ0);
        AScalar out = total * inv_count;
        *output = out.to_float();
        KN_PRINTAFLT(*output);
        //store32x1_vr_postI(VR_out, output, INC1, VRQ0);
    }
    else if (4 == data->opt_constraint_float) // keep dims, 4d special
  {
  // global avg pooling mean, axis -> 12
  // int batches = input->dim.
  // int32_t* pY = (int32_t*)output;
  float* pDst = output;
  ulsr32 UR_Dst = align_32x2_store(pDst);
  //int total_output = data->num_output_elements; // per batch
  int batches = inputTensor->dims->data[0];
  int inputGroup = inputTensor->dims->data[inputTensor->dims->size - 1];
  int grpOutput2 = inputGroup >> 1;

  float* pInput0 = (float*)input;
  

  while (batches)
  {

      float* pInput1 = pInput0;

      if (grpOutput2 > 0)  // FIXME: AND DIM0 == 1, DIM3 = total_output
      {
          // per group, 8 elements
           //>> 2;
          //int inputGroup4 = inputGroup >> 2;
          for (int ii = 0; ii < grpOutput2; ii++)
          {
              vr64 VR_x;
              vr64 VR_acc = vseta_vr(0,  0);
              float* pInput2 = ii * 2 + pInput1;
              //load32x2_vr_postR(VR_x, pInput2, grpOutput2);
              load32x1_vr_postI(VR_x, pInput2, INC1, VRQ0);
              load32x1_vr_postI(VR_x, pInput2, INC1, VRQ1); pInput2 += (grpOutput2-1)*2;
              convert_IEEE_float_to_32F_x2(VR_x);

              for (int jj = 0; jj < blockInput - 1; jj++)  //
              {
                  VR_acc = vadds(VR_acc, VR_x, 0);
                  //load32x2_vr_postR(VR_x, pInput2, grpOutput2);

                  load32x1_vr_postI(VR_x, pInput2, INC1, VRQ0);
                  load32x1_vr_postI(VR_x, pInput2, INC1, VRQ1); pInput2 += (grpOutput2 - 1) * 2;
                  convert_IEEE_float_to_32F_x2(VR_x);
              }
              VR_acc = vadds(VR_acc, VR_x, 0);

              VR_acc = vsel(vmuls(VR_acc, VR_invCount, 0), VR_acc, xt_mean);

              convert_32F_to_IEEE_float_x2(VR_acc);
              store_32x2_vr_a(VR_acc, UR_Dst, pDst);


          }
          flush_32x2(UR_Dst, pDst);
      }
      if (inputGroup & 1)
      {
          //for (int ii = 0; ii < (inputGroup & 3); ii++)
          {
              float* pInput2 = 0 + pInput1;
              vr64 VR_x;
              vr64 VR_acc = vseta_vr(0, 0);
              mov_AccExtend_vr(VR_acc);
              load32x1_vr_postR(VR_x, pInput2, inputGroup, VRQ0);
              convert_IEEE_float_to_32F_x2(VR_x);

              for (int jj = 0; jj < blockInput - 1; jj++)  // input 2,
              {
                  VR_acc = vadds(VR_acc, VR_x, 0);
                  load32x1_vr_postR(VR_x, pInput2, inputGroup, VRQ0);
                  convert_IEEE_float_to_32F_x2(VR_x);
              }
              VR_acc = vadds(VR_acc, VR_x, 0);

              VR_acc = vsel(vmuls(VR_acc, VR_invCount, 0), VR_acc, xt_mean);

              convert_32F_to_IEEE_float_x2(VR_acc);
              store32x1_vr_postI(VR_acc, pDst, INC1, VRQ0);

          }
      }
      batches--;
      pInput0 += inputGroup * num_elements_in_axis;
  }


    }
    else {
    // error
    TF_LITE_ASSERT(data->opt_constraint_float >= 5);
    }
}
#endif
#if defined(DMX1A_SUM_OPT) //|| defined(HMD1A_SUM_OPT) 
void ReduceMeanorSumFloat(OpData* data,const TfLiteEvalTensor *inputTensor, const float* input, float* output,
                          int mean) {
  float* pY = (float*)output;
  // AScalar Scale = data->scale_aflt;
  AScalar invScale = data->inv_count;
  // AScalar Bias = data->bias_aflt;
  int num_elements_in_axis = data->num_elements_in_axis;
  // int total_input = 12*8*256;
  int total_output = data->ReduceOp.num_output_elements;
  // int groupOutputAU4 = (((total_output + 3) >> 2));
  int groupOutput4 = total_output >> 2;
  int blockInput = num_elements_in_axis;  // >> 2;
  // int nextGroupInput;

  // vr128 VR_const_one;


  if (2 == data->opt_constraint_float ) {
    float* pInput0;
    xtbool4 xt_mean = int_to_xt_bool4(mean ? 0xf : 0);
    vr128 VR_invCount;
    vr128 VR_x0;
    replicate_ar(VR_invCount, 0xf, invScale.fr);
    // nextGroupInput = total_output >> 2;
    ulsr128 UR_out = align_32x4_store(pY);
	pInput0 = (float*)input;
	if (groupOutput4 > 0)
	{
		for (int ii = 0; ii < groupOutput4; ii++) {
			vr128 VR_y0 = vseta_vr(0, 0, 0);


			float *pInputBlk = pInput0;
			ulsr128 UR_x = align_32x4_load(pInput0);
			load_32x4_vr_a(VR_x0, UR_x, pInput0);

			for (int jj = 1; jj < blockInput; jj++)  // input 2,
			{
				float* pInput2 = (float*)pInputBlk + jj * total_output;
				convert_IEEE_float_to_32F_x4(VR_x0);

				VR_y0 = vadds(VR_y0, VR_x0, 0);

				UR_x = align_32x4_load(pInput2);
				load_32x4_vr_a(VR_x0, UR_x, pInput2);
			}
			convert_IEEE_float_to_32F_x4(VR_x0);
			VR_y0 = vadds(VR_y0, VR_x0, 0);

			{
				vr128 VR_mean = vmuls(VR_y0, VR_invCount, 0);

				VR_y0 = vsel(VR_mean, VR_y0, xt_mean);
			}
			convert_32F_to_IEEE_float_x4(VR_y0);
			store_32x4_vr_a(VR_y0, UR_out, pY);  // , INC1);
		}
		flush_32x4(UR_out, pY);
	}
    // one 1 output
    pInput0 = (float*)input + (groupOutput4)*4;
    for (int ii = 0; ii < (total_output & 3); ii++) {
      vr128 VR_y0 = vseta_vr(0, 0, 0);
      float* pInput1 = pInput0 + (ii);
      load32x1_vr_postR(VR_x0, pInput1, total_output, VRQ0);
      for (int jj = 0; jj < blockInput - 1; jj++)  // input 2,
      {
        convert_IEEE_float_to_32F_x4(VR_x0);
        VR_y0 = vadds(VR_y0, VR_x0, 0);
        load32x1_vr_postR(VR_x0, pInput1, total_output, VRQ0);
      }
      convert_IEEE_float_to_32F_x4(VR_x0);
      VR_y0 = vadds(VR_y0, VR_x0, 0);
      // if (mean)
      {
        vr128 VR_mean = vmuls(VR_y0, VR_invCount, 0);

        VR_y0 = vsel(VR_mean, VR_y0, xt_mean);
      }
      convert_32F_to_IEEE_float_x4(VR_y0);
      store32x1_vr_postI(VR_y0, pY, INC1, VRQ0);
      // load32x1_vr_postR(VR_x0, pInput0, nextGroupInput, VRQ0);
    }
  }

  else if (3 == data->opt_constraint_float) // for axis -1 is , output is 1
  {
	  int loopLim = blockInput >> 2;
	  vr128 VR_input; 
	  AScalar inv_count = AScalar(blockInput).inverse();
	  vr128 VR_sum = vseta_vr(kConstTable_Zero, 0, 0);
	  
	  float* pInput0;
	  pInput0 = (float*)input;
	  ulsr128 UR_Input = align_32x4_load(pInput0);
	  if (loopLim > 0)
	  {
		  load_32x4_vr_a(VR_input, UR_Input, pInput0);
			for (int ii = 0; ii < loopLim-1; ii++)
			{
				convert_IEEE_float_to_32F_x4(VR_input);
				VR_sum = vadds(VR_sum, VR_input, 0);
				load_32x4_vr_a(VR_input, UR_Input, pInput0);
			}
			convert_IEEE_float_to_32F_x4(VR_input);
			VR_sum = vadds(VR_sum, VR_input, 0);
			
	  }
	  VR_input = vseta_vr(kConstTable_Zero, 0, 0);
	  for (int ii = 0; ii < (blockInput & 3); ii++)
	  {
		  load32x1_vr_postI(VR_input, pInput0, INC1, VRQ0);
		  convert_IEEE_float_to_32F_x4(VR_input);
		  VR_sum = vadds(VR_sum, VR_input, 0);
	  }

	  dsums_L(VR_sum, VR_sum, 0, 0);
	  dsums_L(VR_sum, VR_sum, 0, 0);
	  //AScalar ove32_ar_vr_idx(VR_sum, VRQ0);
	  AScalar total = move32_fr_vr_idx(VR_sum, VRQ0);
	  AScalar out = total * inv_count;
	  *output = out.to_float();
      KN_PRINTAFLT(*output);
  }
  else if (4 == data->opt_constraint_float) // keep dims, 4d special
  {
        // global avg pooling mean, axis -> 12
        // int batches = input->dim.
        // int32_t* pY = (int32_t*)output;
        float* pDst = output;
        ulsr128 UR_Dst = align_32x4_store(pDst);
        //int total_output = data->num_output_elements; // per batch
        int batches = inputTensor->dims->data[0];
        int inputGroup = inputTensor->dims->data[inputTensor->dims->size - 1];
        int grpOutput4 = inputGroup >> 2;
        int inputGroup_minus4 = inputGroup - 4;
        float* pInput0 = (float*)input;
       // int num_elements_in_axis = data->num_elements_in_axis;
       

        //int blockInput = num_elements_in_axis;
        xtbool4 xt_mean = int_to_xt_bool4(mean ? 0xf : 0);
        vr128 VR_invCount;

        replicate_ar(VR_invCount, 0xf, invScale.fr);

      while (batches)
      {
          
          float* pInput1 = pInput0;

          if (grpOutput4 > 0)  // FIXME: AND DIM0 == 1, DIM3 = total_output
          {
              // per group, 8 elements
               //>> 2;
              //int inputGroup4 = inputGroup >> 2;
              ulsr128 UR_x;
              for (int ii = 0; ii < grpOutput4; ii++)
              {
                  vr128 VR_x;
                  vr128 VR_acc = vseta_vr(0, 0, 0);
                  float* pInput2 = ii *4 + pInput1;
                  
                  UR_x = align_32x4_load(pInput2);
                  load_32x4_vr_a(VR_x, UR_x, pInput2);
                  pInput2 += inputGroup_minus4;
                  //load32x4_vr_postR(VR_x, pInput2, grpOutput4);
                  convert_IEEE_float_to_32F_x4(VR_x);

                  for (int jj = 0; jj < blockInput - 1; jj++)  //
                  {
                      VR_acc = vadds(VR_acc, VR_x, 0);
                      //load32x4_vr_postR(VR_x, pInput2, grpOutput4);
                      UR_x = align_32x4_load(pInput2);
                      load_32x4_vr_a(VR_x, UR_x, pInput2);
                      pInput2 += inputGroup_minus4;
                      convert_IEEE_float_to_32F_x4(VR_x);
                  }
                  VR_acc = vadds(VR_acc, VR_x, 0);

                  VR_acc = vsel(vmuls(VR_acc, VR_invCount, 0), VR_acc, xt_mean);

                  convert_32F_to_IEEE_float_x4(VR_acc);
                  store_32x4_vr_a(VR_acc, UR_Dst, pDst);


              }
              flush_32x4(UR_Dst, pDst);
          }
              if (inputGroup & 3)
              {
                  for (int ii = 0; ii < (inputGroup & 3); ii++)
                  {
                      float* pInput2 = ii + pInput1;
                      vr128 VR_x;
                      vr128 VR_acc = vseta_vr(0, 0, 0);
                      mov_AccExtend_vr(VR_acc);
                      load32x1_vr_postR(VR_x, pInput2, inputGroup, VRQ0);
                      convert_IEEE_float_to_32F_x4(VR_x);

                      for (int jj = 0; jj < blockInput - 1; jj++)  // input 2,
                      {
                          VR_acc = vadds(VR_acc, VR_x, 0);
                          load32x1_vr_postR(VR_x, pInput2, inputGroup, VRQ0);
                          convert_IEEE_float_to_32F_x4(VR_x);
                      }
                      VR_acc = vadds(VR_acc, VR_x, 0);

                      VR_acc = vsel(vmuls(VR_acc, VR_invCount, 0), VR_acc, xt_mean);

                      convert_32F_to_IEEE_float_x4(VR_acc);
                      store32x1_vr_postI(VR_acc,  pDst, INC1, VRQ0);

              }
          }
          batches--;
          pInput0 += inputGroup* num_elements_in_axis;
      }


  }
}

#endif


#ifdef HMD1A_REDUCE_MAX_OPT

int ReduceMaxQuantizedInt8(
	const OpData *data,
	const int8_t *x,  // align up16 buffer, zero paddding
	int8_t *pOut, int32_t *pScratchOuput, int n, int depth) {
	// int n4 = (n)>>2; // align-up 4 padding 16 byte zero
	vr64 VR_data, VR_max, VR_out;
	// vr128 VR_mask;
	int m2 = (depth + 1) >> 1;
	const int8_t *pData = x;
	int8_t *pDataGroup = (int8_t *)pData;
	int32_t *pDst = pScratchOuput;
	int8_t *pY = pOut;
	// int idx;
	mir18 mir_idx;
	int n4 = (n / depth);  // >> 2;
	int cvt_32f = 7;
	int depthInc = (depth + 1) >> 1;
#ifdef KN_DEBUG
	CHECK_ALIGN_4(pData);
#endif

	for (int jj = 0; jj < m2; jj++) {
		pData = pDataGroup;
		load16x1_vr_postR(VR_data, pData, depthInc, VRQ0);

		VR_out = shift8_into32_arith(VR_data, 24, 0, VRQ0, 1);

		convert_16I_to_32F_x2(VR_out, cvt_32f);
		vmaxmin_init(VR_max, VR_out, mir_idx);

		for (int ii = 0; ii < n4 - 1; ii++) {
			load16x1_vr_postR(VR_data, pData, depthInc, VRQ0);

			VR_out = shift8_into32_arith(VR_data, 24, 0, VRQ0, 1);

			convert_16I_to_32F_x2(VR_out, cvt_32f);
			vmax_idx(VR_max, VR_out, mir_idx);
		}

		convert_32F_to_16I_x2(VR_max, 15, 1);  // rounding
		VR_max = shift32_arith(VR_max, (unsigned)-16, 0);

		store32x2_vr_postI(VR_max, pDst, INC1);
		pDataGroup += 2;  // byte ?
	}

	int loopLim = depth >> 1;
	pDst = pScratchOuput;
	if (loopLim > 0) {
        ulsr32 UR_Dst = align_32x2_load(pDst);
		for (int ii = 0; ii < loopLim; ii++) {
            load_32x2_vr_a(VR_max, UR_Dst, pDst); //, INC1);
		//	SATURATE_INT32_VR64(VR_max, VR_max, data.activation_min,
		//		data.activation_max);
			VR_out = shift32_arith(VR_max, 24, 0);

			store8x2_vr_postI(VR_out, pY, INC1);
		}
	}

	if (depth & 1) {
		load32x1_vr_postI(VR_max, pDst, INC1, VRQ0);
		//SATURATE_INT32_VR_IDX(VR_max, VR_max, data.activation_min,
	//		data.activation_max, VRQ0);
		VR_out = shift32_arith(VR_max, 24, 0);

		store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
	}
	return 0;
}

#endif
#ifdef HMD1A_MEAN_OPT

void ReduceMeanQuantizedInt8(OpData* data, const int8_t* input, int8_t* output,
                             int32_t* temp_buffer, int sign) {
  int32_t* pY = (int32_t*)output;
  AScalar Scale = data->scale_aflt;
  AScalar invScale = data->inv_count;
  AScalar Bias = data->bias_aflt;
  int num_elements_in_axis = data->num_elements_in_axis;
  // int total_input = 12*8*256;
  int total_output = data->ReduceOp.num_output_elements;
  int groupOutputAU4 = (((total_output + 3) >> 2));
  int groupOutput2 = total_output >> 1;
  int blockInput = num_elements_in_axis >> 1;
  int nextGroupInput;
  int32_t* pDst = temp_buffer;

  int exp_fxp =
      30;  //(sign == 3 )? 15: ((sign == 1)? 16: 17); // 31-(14+2), 31-

  vr64 VR_const_one;
  vr64 VR_scale, VR_bias, VR_invCount;
  replicate_ar(VR_const_one, 0x3, 0x01010101);

  replicate_ar(VR_scale, 0x3, Scale.fr);
  replicate_ar(VR_bias, 0x3, Bias.fr);
  replicate_ar(VR_invCount, 0x3, invScale.fr);

  if (total_output >= 4)  // FIXME: AND DIM0 == 1, DIM3 = total_output
  {
    // per group, 8 elements
    nextGroupInput = total_output >> 2;

    for (int ii = 0; ii < groupOutputAU4; ii++) {
      vr64 VR_x;
      vr64 VR_acc = vseta_vr(0, 0);
      mov_AccExtend_vr(VR_acc);
      int32_t* pInput1 = (int32_t*)input + ii * 1;  // 32 bit pointer, 1*4
      load32x1_vr_postR(VR_x, pInput1, nextGroupInput, VRL);
      load32x1_vr_postR(VR_x, pInput1, nextGroupInput, VRH);
      WUR_MvmAux(0);

      for (int jj = 0; jj < blockInput - 1; jj++)  // input 2,
      {
        vr64 VR_y = vexp_adji(VR_x, 0);
        mac8bx8b(VR_acc, VR_y, VR_const_one, sign);
        load32x1_vr_postR(VR_x, pInput1, nextGroupInput, VRL);
        load32x1_vr_postR(VR_x, pInput1, nextGroupInput, VRH);
      }
      mac8bx8b(VR_acc, VR_x, VR_const_one, sign);
      // output sum * 2 fix-point if required
      store32x2_vr_postI(VR_acc, pDst, INC1);
      store_AccExtend_postI(pDst, INC1);
    }
  }

  vr64 VR_xor_0x80;
  KN_PRINT_Q31_SIZE(temp_buffer, total_output);
  if (data->ReduceOp.output_zp == -128) {
    replicate_ar(VR_xor_0x80, 0x3, 0x80808080);
  } else {
    replicate_ar(VR_xor_0x80, 0x3, 0x00000000);
  }
  int32_t* pSrc = temp_buffer;
  ulsr32 UR_src = align_32x2_load(pSrc);
  for (int ii = 0; ii < groupOutput2; ii++) {
    vr64 VR_acc, VR_out, VR_q7_out;
    //load32x2_vr_postI(VR_acc, pSrc, INC1);
    load_32x2_vr_a(VR_acc, UR_src, pSrc);
    convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ0);
    convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ1);

    VR_out = vmuls(VR_acc, VR_invCount, 0);           // / num_element_in_axis
    VR_out = vmacs(VR_bias, VR_out, VR_scale, 0, 0);  // acc
    convert_32F_to_16I_x2(VR_out, (unsigned int)15 - 8, 0);
    rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
    VR_q7_out = vbool(VR_q7_out, VR_xor_0x80, 0x6);
    store16x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
  }

  if (total_output & 1) {
    // for(int ii = 0; ii < (total_output&3); ii++)
    {
      vr64 VR_acc, VR_out, VR_q7_out;
      load32x1_vr_postI(VR_acc, pSrc, INC1, VRQ0);
      convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ0);

      VR_out = vmuls(VR_acc, VR_invCount, 0);           // / num_element_in_axis
      VR_out = vmacs(VR_bias, VR_out, VR_scale, 0, 0);  // acc
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x1(VR_out, (unsigned int)15 - 8, 0, VRQ0);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_out, VR_out, 1);
      VR_q7_out = vbool(VR_q7_out, VR_xor_0x80, 0x6);
      VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
    }
  }
}

#endif
TfLiteStatus EvalMean(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);

  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);
  OpData* op_data_ex = reinterpret_cast<OpData*>(node->user_data);
  OpDataReduce* op_data =
      reinterpret_cast<OpDataReduce*>(&op_data_ex->ReduceOp);
#if defined(DMX1A_MEAN_OPT) || defined(HMD1A_MEAN_OPT)
  if (op_data_ex->opt_constraint == 1) {
    int32_t* temp_buffer = static_cast<int32_t*>(
        context->GetScratchBuffer(context, op_data->temp_buffer_idx));

    ReduceMeanQuantizedInt8(
        op_data_ex, tflite::micro::GetTensorData<int8_t>(input),
        tflite::micro::GetTensorData<int8_t>(output), temp_buffer, 1);

  }
#if defined(DMX1A_SUM_OPT) || defined(HMD1A_SUM_OPT) || defined(HMD1A_MEAN_OPT)
  else if (op_data_ex->opt_constraint_float) {
    //  int32_t* temp_buffer = static_cast<int32_t*>(
    //	  context->GetScratchBuffer(context, op_data->temp_buffer_idx));

    ReduceMeanorSumFloat(op_data_ex,input, tflite::micro::GetTensorData<float>(input),
                         tflite::micro::GetTensorData<float>(output), 1);

    KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                   ElementCount(*output->dims));
  }
#endif
  else
#endif

  {
#ifndef REMOVE_REFOP_SUPPORT

return EvalMeanHelper(context, node,
                        op_data);

   // KN_PRINT_Q7_SIZE(output->data.int8, ElementCount(*output->dims));
#else
    return kTfLiteError;
#endif
  }
  return kTfLiteOk;
}


TfLiteStatus EvalSum(TfLiteContext* context, TfLiteNode* node) {
  //OpContext op_context(context, node);
  // ruy::profiler::ScopeLabel label("Sum");
  // static_cast , reinterpreter_cast will allocate new tensors
  OpData* op_data_ex = static_cast<OpData*>(node->user_data);

  OpDataReduce* op_data = static_cast<OpDataReduce*>(&op_data_ex->ReduceOp);
  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);
  //const TfLiteEvalTensor* axis = tflite::micro::GetEvalInput(context, node, 1);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);
#if defined(DMX1A_SUM_OPT) || defined(HMD1A_SUM_OPT)
  if (op_data_ex->opt_constraint) {
    // TODO
    TF_LITE_ENSURE_EQ(context, 1, 0);
    return kTfLiteError;
  } else if (op_data_ex->opt_constraint_float) {
	  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input),
		  ElementCount(*input->dims));
    ReduceMeanorSumFloat(op_data_ex, input,
                         tflite::micro::GetTensorData<float>(input),
                         tflite::micro::GetTensorData<float>(output), 0);

    KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                   ElementCount(*output->dims));
  } else
#endif
  {

    TfLiteStatus status =  EvalSumHelper(context, node, op_data);

    return status;
    //KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
    //               ElementCount(*output->dims));
  }

  return kTfLiteOk;
}
TfLiteStatus EvalMeanInt8(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);

  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);

  // ResolveAxis(tflite::micro::GetTensorData<int>(axis), num_axis, &op_params);

  OpData* op_data_ex = static_cast<OpData*>(node->user_data);

  OpDataReduce* op_data = static_cast<OpDataReduce*>(&op_data_ex->ReduceOp);
  if (kTfLiteInt8 != input->type) {
    TF_LITE_ENSURE_MSG(context, false,
                       "Currently, only float32, int8 or uint8 input type "
                       "is supported.");
    return kTfLiteError;
  }

  // Defer to specialized implementation for 4D Mean across axes 1 & 2.
#if defined(DMX1A_MEAN_OPT) || defined(HMD1A_MEAN_OPT)
  if (op_data_ex->opt_constraint == 1) {
    int32_t* temp_buffer = static_cast<int32_t*>(
        context->GetScratchBuffer(context, op_data->temp_buffer_idx));

    ReduceMeanQuantizedInt8(
        op_data_ex, tflite::micro::GetTensorData<int8_t>(input),
        tflite::micro::GetTensorData<int8_t>(output), temp_buffer, 1);
    // KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
    // ElementCount(*output->dims));
  }
#endif
  else {
#ifndef REMOVE_REFOP_SUPPORT
 return EvalMeanHelper(context, node,
                       op_data);

#else
    return kTfLiteError;

#endif
  }

  return kTfLiteOk;
}
TfLiteStatus EvalMax(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);
  const TfLiteEvalTensor* axis = tflite::micro::GetEvalInput(context, node, 1);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);
  TF_LITE_ENSURE_TYPES_EQ(context, input->type, output->type);
  TfLiteReducerParams* params =
      static_cast<TfLiteReducerParams*>(node->builtin_data);
  OpData* op_data_ex = static_cast<OpData*>(node->user_data);

  OpDataReduce* op_data = static_cast<OpDataReduce*>(&op_data_ex->ReduceOp);

  // Interpret an axis tensor with null dimensions as a scalar
  int num_axis = static_cast<int>(ElementCount(*axis->dims));
  int* temp_buffer = static_cast<int*>(
      context->GetScratchBuffer(context, op_data->temp_buffer_idx));
  int* resolved_axis = static_cast<int*>(
      context->GetScratchBuffer(context, op_data->resolved_axis_idx));
  switch (input->type) {
    case kTfLiteFloat32:
      TF_LITE_ENSURE(
          context,
          reference_ops::ReduceGeneric<float>(
              tflite::micro::GetTensorData<float>(input), input->dims->data,
              input->dims->size, tflite::micro::GetTensorData<float>(output),
              output->dims->data, output->dims->size,
              tflite::micro::GetTensorData<int>(axis), num_axis,
              params->keep_dims, temp_buffer, resolved_axis,
              std::numeric_limits<float>::lowest(),
              [](const float current, const float in) -> float {
                return (in > current) ? in : current;
              }));
      break;
    case kTfLiteInt8:
      TF_LITE_ENSURE_EQ(context, static_cast<double>(op_data->input_scale),
                        static_cast<double>(op_data->output_scale));
      TF_LITE_ENSURE_EQ(context, op_data->input_zp, op_data->output_zp);
#if defined(DMX1A_REDUCE_MAX_OPT) || defined(HMD1A_REDUCE_MAX_OPT)

	  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input), ElementCount(*input->dims));
	  if (op_data_ex->opt_constraint)
	  {
		  // size  sizeof(int) * input->dims->size,
		  // max pooling ?
		  ReduceMaxQuantizedInt8(
			  op_data_ex, tflite::micro::GetTensorData<int8_t>(input),
			  tflite::micro::GetTensorData<int8_t>(output), temp_buffer,
			  ElementCount(*input->dims), ElementCount(*output->dims));
	  }
	  else
#endif
	  {
		  TF_LITE_ENSURE(
			  context,
			  reference_ops::ReduceGeneric<int8_t>(
				  tflite::micro::GetTensorData<int8_t>(input), input->dims->data,
				  input->dims->size, tflite::micro::GetTensorData<int8_t>(output),
				  output->dims->data, output->dims->size,
				  tflite::micro::GetTensorData<int>(axis), num_axis,
				  params->keep_dims, temp_buffer, resolved_axis,
				  std::numeric_limits<int8_t>::lowest(),
				  [](const int8_t current, const int8_t in) -> int8_t {
			  return (in > current) ? in : current;
		  }));
	  }
	  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output), ElementCount(*output->dims));
      break;
    default:
      TF_LITE_KERNEL_LOG(context,
                         "Only float32 and int8 types are supported.\n");
      return kTfLiteError;
  }
  return kTfLiteOk;
}
//}  // namespace reduce

TFLMRegistration Register_MEAN() {
  return tflite::micro::RegisterOp(InitReduce,
          /*prepare=*/PrepareMeanOrSum,
          /*invoke=*/EvalMean);
}
TFLMRegistration Register_MEAN_INT8() {
 return tflite::micro::RegisterOp(InitReduce,
          /*prepare=*/PrepareMeanOrSum,
          /*invoke=*/EvalMeanInt8);
}
TFLMRegistration Register_REDUCE_MAX() {
 return tflite::micro::RegisterOp(InitReduce,
          /*prepare=*/PrepareMax,
          /*invoke=*/EvalMax);
}

TFLMRegistration Register_SUM() {
 return tflite::micro::RegisterOp(InitReduce,
          /*prepare=*/PrepareMeanOrSum,
          /*invoke=*/EvalSum);
}
//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
