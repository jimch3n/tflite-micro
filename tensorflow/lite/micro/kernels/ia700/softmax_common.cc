/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

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
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/ia700/config.h"
//#include "tensorflow/lite/micro/kernels/softmax.h"
#include "tensorflow/lite/micro/micro_context.h"
#if defined(KN_TFLITE_AFLOAT)
#include "AVL.h"
#endif
namespace tflite {

namespace {
// Softmax parameter data that persists in user_data
const int kInt16LUTArraySize = LUTSize<int16_t>();

}  // namespace
TfLiteStatus CalculateSoftmaxParams(TfLiteContext* context,
                                    const TfLiteTensor* input,
                                    TfLiteTensor* output,
                                    const TfLiteSoftmaxParams* params,
                                    SoftmaxParams* op_data);

void* SoftmaxInit(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(SoftmaxParams));
}
TfLiteStatus SoftmaxPrepareInt8(TfLiteContext* context, TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);
  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, 0);
  TF_LITE_ENSURE(context, input != nullptr);
  TF_LITE_ENSURE(context, NumDimensions(input) >= 1);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, 0);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE(context, node->user_data != nullptr);

  SoftmaxParams* op_data = static_cast<SoftmaxParams*>(node->user_data);
  // Only allocate LUTs for KTfLiteInt16 data type

  TF_LITE_ENSURE_EQ(context, input->type, output->type);

  auto* params = static_cast<TfLiteSoftmaxParams*>(node->builtin_data);
  auto ret_val =
      CalculateSoftmaxParams(context, input, output, params, op_data);
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);

  return ret_val;
}

TfLiteStatus SoftmaxPrepare(TfLiteContext* context, TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  TF_LITE_ENSURE_EQ(context, NumInputs(node), 1);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);
  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, 0);
  TF_LITE_ENSURE(context, input != nullptr);
  TF_LITE_ENSURE(context, NumDimensions(input) >= 1);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, 0);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE(context, node->user_data != nullptr);

  SoftmaxParams* op_data = static_cast<SoftmaxParams*>(node->user_data);
  // Only allocate LUTs for KTfLiteInt16 data type
  if (input->type == kTfLiteInt16) {
    void* raw_exp_lut = context->AllocatePersistentBuffer(
        context, sizeof(int16_t) * kInt16LUTArraySize);
    TF_LITE_ENSURE(context, raw_exp_lut != nullptr);
    op_data->exp_lut = reinterpret_cast<int16_t*>(raw_exp_lut);
    void* one_over_one_plus_x_lut = context->AllocatePersistentBuffer(
        context, sizeof(int16_t) * kInt16LUTArraySize);
    TF_LITE_ENSURE(context, one_over_one_plus_x_lut != nullptr);
    op_data->one_over_one_plus_x_lut =
        reinterpret_cast<int16_t*>(one_over_one_plus_x_lut);
  }

  if (output->type == kTfLiteInt16) {
    TF_LITE_ENSURE(context,
                   input->type == kTfLiteInt8 || input->type == kTfLiteInt16);
  } else {
    TF_LITE_ENSURE_EQ(context, input->type, output->type);
  }

  // Populate LUT if required
  if (input->type == kTfLiteInt16) {
    TF_LITE_ENSURE_EQ(context, output->params.zero_point, 0);
    // exp LUT only used on negative values
    // we consider exp(-10.0) is insignificant to accumulation
    const int32_t range = std::numeric_limits<int16_t>::max() -
                          std::numeric_limits<int16_t>::min();
    LUTPopulate<int16_t>(
        10.0f / range, std::numeric_limits<int16_t>::max(), 2.0f / range, 0,
        [](float value) { return std::exp(value); }, op_data->exp_lut);

    LUTPopulate<int16_t>(
        1.0f / range, std::numeric_limits<int16_t>::min(), 2.0f / range, 0,
        [](float value) { return 1.0f / (1.0f + value); },
        op_data->one_over_one_plus_x_lut);

    op_data->zero_point = output->params.zero_point;
    op_data->scale = output->params.scale;
  }

  auto* params = static_cast<TfLiteSoftmaxParams*>(node->builtin_data);
  auto ret_val =
      CalculateSoftmaxParams(context, input, output, params, op_data);

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return ret_val;
}

TfLiteStatus CalculateSoftmaxParams(TfLiteContext* context,
                                    const TfLiteTensor* input,
                                    TfLiteTensor* output,
                                    const TfLiteSoftmaxParams* params,
                                    SoftmaxParams* op_data) {
  if (input->type == kTfLiteInt8 || input->type == kTfLiteInt16) {
    if (input->type == kTfLiteInt16) {
#if defined(KN_TFLITE_AFLOAT)

      AScalar inv_32768 = AScalar(32768).inverse();
      TF_LITE_ENSURE_EQ(context, output->params.zero_point, 0);
      TF_LITE_ENSURE_NEAR_AFLOAT(context, AScalar(output->params.scale),
                                 inv_32768, CONST_ASCALAR(0.001f) * inv_32768);

#else
      TF_LITE_ENSURE_EQ(context, output->params.zero_point, 0);
      TF_LITE_ENSURE_NEAR(context, output->params.scale, 1.f / 32768,
                          (0.001f * 1.f / 32768));

#endif
    } else {  // input->type == kTfLiteInt8
      TF_LITE_ENSURE_TYPES_EQ(context, input->type, kTfLiteInt8);
      if (output->type == kTfLiteInt16) {
        TF_LITE_ENSURE_EQ(context, output->params.zero_point, -32768);
#if defined(KN_TFLITE_AFLOAT)

        AScalar inv_65536 = AScalar(65536.0f).inverse();
        TF_LITE_ENSURE_NEAR_AFLOAT(context, AScalar(output->params.scale),
                                   inv_65536,
                                   CONST_ASCALAR(0.001f) * inv_65536);

#else

        TF_LITE_ENSURE_NEAR(context, output->params.scale, 1.f / 65536,
                            (0.001f * 1.f / 65536));

#endif

      } else {  // output->type == kTfLiteint8
        TF_LITE_ENSURE_TYPES_EQ(context, output->type, kTfLiteInt8);

        TF_LITE_ENSURE_EQ(context, output->params.zero_point, -128);

#if defined(KN_TFLITE_AFLOAT)
        AScalar inv_256 = AScalar(256.f).inverse();

        TF_LITE_ENSURE(context, output->params.scale == inv_256.to_float());
#else
        TF_LITE_ENSURE(context, output->params.scale == 1.f / 256);
#endif
      }
    }

    static const int kScaledDiffIntegerBits = 5;
#if defined(KN_TFLITE_AFLOAT)

    if (input->type == kTfLiteInt16) {
      int input_left_shift;

      AScalar input_scale_beta_rescale =
          AScalar(input->params.scale) * AScalar(params->beta) /
          CONST_ASCALAR(10.0 /
                        65535.0);  // scale the input_diff such that [-65535, 0]
                                   // correspond to [-10.0, 0.0]
      QuantizeMultiplier(input_scale_beta_rescale.to_double(),
                         &op_data->input_multiplier, &input_left_shift);
      op_data->input_left_shift = input_left_shift;
    } else {
      int input_left_shift;
      tflite::PreprocessSoftmaxScaling(
          AScalar(params->beta).to_double(),
          AScalar(input->params.scale).to_double(), kScaledDiffIntegerBits,
          &op_data->input_multiplier, &input_left_shift);
      op_data->input_left_shift = input_left_shift;
      op_data->diff_min =
          -1.0 * tflite::CalculateInputRadius(kScaledDiffIntegerBits,
                                              op_data->input_left_shift);
    }
#else
    // Calculate input_multiplier and input_left_shift
    if (input->type == kTfLiteInt16) {
      int input_left_shift;
      double input_scale_beta_rescale =
          static_cast<double>(input->params.scale) *
          static_cast<double>(params->beta) /
          (10.0 / 65535.0);  // scale the input_diff such that [-65535, 0]
                             // correspond to [-10.0, 0.0]
      QuantizeMultiplier(input_scale_beta_rescale, &op_data->input_multiplier,
                         &input_left_shift);
      op_data->input_left_shift = input_left_shift;
    } else {
      int input_left_shift;
      tflite::PreprocessSoftmaxScaling(
          static_cast<double>(params->beta),
          static_cast<double>(input->params.scale), kScaledDiffIntegerBits,
          &op_data->input_multiplier, &input_left_shift);
      op_data->input_left_shift = input_left_shift;
      op_data->diff_min =
          -1.0 * tflite::CalculateInputRadius(kScaledDiffIntegerBits,
                                              op_data->input_left_shift);
    }
#endif
  } else {
    TF_LITE_ENSURE_TYPES_EQ(context, input->type, kTfLiteFloat32);
    TF_LITE_ENSURE_TYPES_EQ(context, output->type, kTfLiteFloat32);
#if defined(KN_TFLITE_AFLOAT)

    op_data->beta = AScalar(params->beta).to_double();
#else
    op_data->beta = static_cast<double>(params->beta);
#endif
  }
  return kTfLiteOk;
}

}  // namespace tflite
