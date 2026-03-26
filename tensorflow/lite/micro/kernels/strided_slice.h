/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

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

#ifndef TENSORFLOW_LITE_MICRO_KERNELS_STRIDED_SLICE_H_
#define TENSORFLOW_LITE_MICRO_KERNELS_STRIDED_SLICE_H_

#include <cstdint>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_common.h"

namespace tflite {

constexpr int kStridedSliceInputTensor = 0;
constexpr int kStridedSliceBeginTensor = 1;
constexpr int kStridedSliceEndTensor = 2;
constexpr int kStridedSliceStridesTensor = 3;
constexpr int kStridedSliceOutputTensor = 0;

void* StridedSliceInit(TfLiteContext* context, const char* buffer,
                       size_t length);

TfLiteStatus StridedSlicePrepare(TfLiteContext* context, TfLiteNode* node);

#if defined(IA8201) || defined(IA700)
// only for 8201
struct StridedSliceOpData {
  tflite::StridedSliceParams op_params;
  int opt_constraint;
  int src_offset;
  // uint16_t* srcIdx;
};
//#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#endif


namespace {
  #if defined(IA8201)
  template <typename T>
  static void SlicedCopyOptOffset(const T* src, T* dst, int nElement) {
    block_copy_bytes((int8_t*)dst, (int8_t*)src, sizeof(T) * nElement);
  }
  #endif
}

}  // namespace tflite

#endif  // TENSORFLOW_LITE_MICRO_KERNELS_STRIDED_SLICE_H_
