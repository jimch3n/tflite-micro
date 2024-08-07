/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

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

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/l2normalization.h"
#include "tensorflow/lite/kernels/internal/reference/l2normalization.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"

#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/micro_utils.h"

namespace tflite {
//namespace ops {
//namespace micro {
//namespace l2norm {

namespace {

// This file has two implementation of L2Norm.
enum KernelType {
  kReference,
  kGenericOptimized,
};

constexpr int kInputTensor = 0;
constexpr int kOutputTensor = 0;

}  // namespace

TfLiteStatus PrepareL2Norm(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  auto* params = reinterpret_cast<TfLiteL2NormParams*>(node->builtin_data);
  L2NormalizationParams* data =
      static_cast<L2NormalizationParams*>(node->user_data);

  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kOutputTensor);

  TF_LITE_ENSURE(context, NumDimensions(input) <= 4);

  TF_LITE_ENSURE(context, output->type == kTfLiteFloat32 ||
                              output->type == kTfLiteUInt8 ||
                              output->type == kTfLiteInt8);
  TF_LITE_ENSURE_TYPES_EQ(context, input->type, output->type);

  if (output->type == kTfLiteUInt8 || output->type == kTfLiteInt8) {
    data->input_zero_point = input->params.zero_point;
  } else if (output->type == kTfLiteFloat32) {
    data->input_zero_point = 0;
  }

  // Our implementations don't currently support activations.
  TF_LITE_ENSURE_EQ(context, params->activation, kTfLiteActNone);

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

void* InitL2Norm(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context,
                                           sizeof(L2NormalizationParams));
}

#ifdef DMX1A_L2NORM_OPT
void
L2NormEval(const tflite::L2NormalizationParams& op_params,
	const RuntimeShape& input_shape,
	const float* input_data,
	const RuntimeShape& output_shape,
	float* output_data, float epsilon = 1e-6)
{
	const int trailing_dim = input_shape.DimensionsCount() - 1;
	const int outer_size =
		MatchingFlatSizeSkipDim(input_shape, trailing_dim, output_shape);
	const int depth =
		MatchingDim(input_shape, trailing_dim, output_shape, trailing_dim);
	int loopDepth4 = depth >> 2;

	
	float *output = (float *)output_data;
	vr128 VR_epsilon;
	replicate_ar(VR_epsilon, 0xf, AScalar(epsilon).fr);
	for (int i = 0; i < outer_size; ++i) {
		//AScalar squared_l2_norm = CONST_ASCALAR(0);
		float *input = (float *)&input_data[depth*i];
		vr128 VR_input;
		vr128 VR_acc = vseta_vr(kConstTable_Zero, 0, 0);
		if (loopDepth4 > 0)
		{
			ulsr128 UR_input = align_32x4_load(input);
			load_32x4_vr_a(VR_input, UR_input, input);
			for (int c = 0; c < loopDepth4 - 1; ++c) {
				convert_IEEE_float_to_32F_x4(VR_input);

				//	const float val = input_data[depth * i + c];
				//	squared_l2_norm += val * val;
				affine_adj_L(VR_acc, VR_input, VR_input, 0, 0);
				load_32x4_vr_a(VR_input, UR_input, input);
			}
			//float l2_norm = std::sqrt(squared_l2_norm);
			convert_IEEE_float_to_32F_x4(VR_input);
			affine_adj_L(VR_acc, VR_input, VR_input, 0, 0);
		}
		for (int ii = 0; ii < (depth & 3); ii++)
		{
			load32x1_vr_postI(VR_input, input, INC1, VRQ0);
			convert_IEEE_float_to_32F_x4(VR_input);
			fmacs(VR_acc, VRQ0, VR_input, VRQ0, VR_input, VRQ0, 0);
			//VR_acc = vmacs_adj(VR_acc, VR_input, VR_input, 0, 0);

		}
		dsums_L(VR_acc, VR_acc, 0, 0);
		//l2_norm = std::max(l2_norm, epsilon);
		vr128 VR_l2norm;// = vmax(VR_epsilon, VR_l2norm);
		AScalar l2_norm;
		l2_norm.fr = move32_ar_vr_idx(VR_acc, VRQ0);

		replicate_ar(VR_l2norm, 0xf, l2_norm.f_sqrt().inverse().fr);
		VR_l2norm = vmax(VR_epsilon, VR_l2norm);
		vr128 VR_out;
		ulsr128 UR_out = align_32x4_store(output);
		input = (float *)&input_data[depth*i];
		
		if (loopDepth4 > 0)
		{
			ulsr128 UR_input = align_32x4_load(input);
			load_32x4_vr_a(VR_input, UR_input, input);
			for (int c = 0; c < loopDepth4 - 1; ++c) {
				convert_IEEE_float_to_32F_x4(VR_input);
				//output_data[depth * i + c] = input_data[depth * i + c] / l2_norm;
				VR_out = vmuls(VR_input, VR_l2norm, 0);
				load_32x4_vr_a(VR_input, UR_input, input);
				convert_32F_to_IEEE_float_x4(VR_out);
				store_32x4_vr_a(VR_out, UR_out, output);
				
			}
			convert_IEEE_float_to_32F_x4(VR_input);
			VR_out = vmuls(VR_input, VR_l2norm, 0);
			convert_32F_to_IEEE_float_x4(VR_out);
			store_32x4_vr_a(VR_out, UR_out, output);
			flush_32x4(UR_out, output);

		}
		for (int ii = 0; ii < (depth & 3); ii++)
		{
			load32x1_vr_postI(VR_input, input, INC1, VRQ0);
			convert_IEEE_float_to_32F_x4(VR_input);
			VR_out = vmuls(VR_input, VR_l2norm, 0);
			convert_32F_to_IEEE_float_x4(VR_out);
			store32x1_vr_postI(VR_out, output, INC1, VRQ0);
		}
	}
}
#endif
TfLiteStatus EvalL2Norm(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const L2NormalizationParams& data =
      *(static_cast<const L2NormalizationParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);
	//return kTfLiteOk;
  // TODO(b/143912164): instead of hardcode the epsilon here, we should read it
  // from tensorflow, i.e., adding a params.
  // We don't compute epsilon for quantized kernel:
  //
  // epsilon_float = (epsilon_quant - zp) * scale
  // so
  // espsilon_quant = epsilon_float / scale + zp
  // We know epsilon_float is just a very small number to avoid division by
  // zero error, and scale is > 1, so the integer value of epsilon for quant
  // is just dominated by the zero point.
  // Also, GetInvSqrtQuantizedMultiplierExp handles the scenario where the sum
  // of input value squared is zero case well.
  // So we don't even need to do handle the epsilon for quantized kernel case.
  const float epsilon = 1e-6f;
  if (output->type == kTfLiteFloat32) {
#ifdef DMX1A_L2NORM_OPT
	  L2NormEval(data, tflite::micro::GetTensorShape(input),
		  tflite::micro::GetTensorData<float>(input),
		  tflite::micro::GetTensorShape(output),
		  tflite::micro::GetTensorData<float>(output),
		  epsilon);
#else
    reference_ops::L2Normalization(data, tflite::micro::GetTensorShape(input),
                                   tflite::micro::GetTensorData<float>(input),
                                   tflite::micro::GetTensorShape(output),
                                   tflite::micro::GetTensorData<float>(output),
                                   epsilon);

#endif
	KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output), ElementCount(*output->dims));

  } else if (output->type == kTfLiteUInt8) {
    reference_ops::L2Normalization(
        data, tflite::micro::GetTensorShape(input),
        tflite::micro::GetTensorData<uint8_t>(input),
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<uint8_t>(output));
  } else if (output->type == kTfLiteInt8) {
    const auto input_shape = tflite::micro::GetTensorShape(input);
    const auto output_shape = tflite::micro::GetTensorShape(output);
    const int trailing_dim = input_shape.DimensionsCount() - 1;
    const int depth =
        MatchingDim(input_shape, trailing_dim, output_shape, trailing_dim);
    const int outer_size =
        MatchingFlatSizeSkipDim(input_shape, trailing_dim, output_shape);
    reference_integer_ops::L2Normalization(
        data.input_zero_point, outer_size, depth,
        tflite::micro::GetTensorData<int8_t>(input),
        tflite::micro::GetTensorData<int8_t>(output));
  } else {
    TF_LITE_KERNEL_LOG(context, "Output type is %s, requires float.",
                       TfLiteTypeGetName(output->type));
    return kTfLiteError;
  }

  return kTfLiteOk;
}

//}  // namespace l2norm

TFLMRegistration Register_L2NORM_REF() {
  return tflite::micro::RegisterOp(InitL2Norm,
          /*prepare=*/PrepareL2Norm,
          /*invoke=*/EvalL2Norm);
}

TFLMRegistration Register_L2_NORMALIZATION() { return Register_L2NORM_REF(); }

}  // namespace tflite
