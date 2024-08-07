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

#include <stdint.h>

#include "signal/src/circular_buffer.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/flatbuffer_utils.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/memory_helpers.h"
#include "tensorflow/lite/micro/micro_utils.h"

namespace tflite {
namespace {

constexpr int kInputTensor = 0;
constexpr int kOutputTensor = 0;
constexpr int kOutputValidTensor = 1;

// Indices into the init flexbuffer's vector.
// The parameter's name is in the comment that follows.
// Elements in the vectors are ordered alphabetically by parameter name.
constexpr int kNumChannelsIndex = 0;          // 'num_channels'
constexpr int kStackerLeftContextIndex = 1;   // 'stacker_left_context'
constexpr int kStackerRightContextIndex = 2;  // 'stacker_right_context'
constexpr int kStackerStepIndex = 3;          // 'stacker_step'

struct TFLMDummyParams {
  int32_t num_channels;
  int32_t stacker_left_context;
  int32_t stacker_right_context;
  int32_t stacker_step;

  size_t buffer_size;
  size_t step_size;
  void* test;
};

void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  const uint8_t* buffer_t = reinterpret_cast<const uint8_t*>(buffer);

  auto* params =
      static_cast<TFLMDummyParams*>(context->AllocatePersistentBuffer(
          context, sizeof(TFLMDummyParams)));
  if (params == nullptr) {
    return nullptr;
  }

  return params;
}

TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  MicroPrintf("Dummy input: %d output: %d\n", NumInputs(node), NumOutputs(node));

  // for print dimension, dtype
#if 0
  MicroContext* micro_context = GetMicroContext(context);
  
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);
  TfLiteTensor* output_valid =
      micro_context->AllocateTempOutputTensor(node, kOutputValidTensor);
  TF_LITE_ENSURE(context, output_valid != nullptr);

  TF_LITE_ENSURE_EQ(context, NumDimensions(input), 1);
  TF_LITE_ENSURE_EQ(context, NumDimensions(output), 1);
  TF_LITE_ENSURE_EQ(context, NumDimensions(output_valid), 0);

  TF_LITE_ENSURE_TYPES_EQ(context, input->type, kTfLiteInt16);
  TF_LITE_ENSURE_TYPES_EQ(context, output->type, kTfLiteInt16);
  TF_LITE_ENSURE_TYPES_EQ(context, output_valid->type, kTfLiteBool);

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  micro_context->DeallocateTempTfLiteTensor(output_valid);
  #endif
  return kTfLiteOk;
}

TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  printf("dummy ops eval\n");
  return kTfLiteOk;
}

void Reset(TfLiteContext* context, void* buffer) { printf("dummy ops reset\n"); }

}  // namespace
#ifndef REMOVE_TFLM_SIGNAL
namespace tflm_signal {
  #endif
TFLMRegistration* Register_DUMMY() {
  static TFLMRegistration r =
      tflite::micro::RegisterOp(Init, Prepare, Eval, /*Free*/ nullptr, Reset);
  return &r;
}
#ifndef REMOVE_TFLM_SIGNAL
}  // namespace tflm_signal
#endif
}  // namespace tflite
