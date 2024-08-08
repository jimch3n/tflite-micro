/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

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
#ifndef TENSORFLOW_LITE_MICRO_KERNELS_SOFTMAX_H_
#define TENSORFLOW_LITE_MICRO_KERNELS_SOFTMAX_H_

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/micro/micro_common.h"

namespace tflite {

void* SoftmaxInit(TfLiteContext* context, const char* buffer, size_t length);

// Common helper function to SoftmaxPrepare.
TfLiteStatus CalculateSoftmaxParams(TfLiteContext* context,
                                    const TfLiteTensor* input,
                                    TfLiteTensor* output,
                                    const TfLiteSoftmaxParams* params,
                                    SoftmaxParams* op_data);

TfLiteStatus SoftmaxPrepare(TfLiteContext* context, TfLiteNode* node);
#if defined(IA8201) || defined(IA700)
TfLiteStatus SoftmaxPrepareInt8(TfLiteContext* context, TfLiteNode* node);
#endif
// This is the most generic TFLMRegistration. The actual supported types
// may still be target dependent. The only requirement is that every
// implementation (reference or optimized) must define this function.
TFLMRegistration Register_SOFTMAX();

#if defined(XTENSA) || defined(CMSIS_NN)
// Returns a TFLMRegistration struct for kernel variant that only supports
// int8 input and int16 output.
TFLMRegistration Register_SOFTMAX_INT8_INT16();
#else
#if defined(IA700) || defined(IA8201)
TFLMRegistration Register_SOFTMAX_INT8_INT8();
TFLMRegistration Register_SOFTMAX_FLOAT32_FLOAT32();
TFLMRegistration Register_SOFTMAX_INT8_INT16();
#endif
// inline TFLMRegistration Register_SOFTMAX_INT8_INT16() {
//  return Register_SOFTMAX();
//}
#endif

#if defined(CMSIS_NN)
// Returns a TFLMRegistration struct for kernel variant that only supports
// int8 input/output and uses the latency optimized implementations.
TFLMRegistration Register_SOFTMAX_INT8();

// Returns a TFLMRegistration struct for kernel variant that only supports
// int16 input/output and uses the latency optimized implementations.
TFLMRegistration Register_SOFTMAX_INT16();

#else
inline TFLMRegistration Register_SOFTMAX_INT8() { return Register_SOFTMAX(); }

inline TFLMRegistration Register_SOFTMAX_INT16() { return Register_SOFTMAX(); }
#endif

}  // namespace tflite

#endif  // TENSORFLOW_LITE_MICRO_KERNELS_SOFTMAX_H_
