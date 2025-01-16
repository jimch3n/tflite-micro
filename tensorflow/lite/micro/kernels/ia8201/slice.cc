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
//#define KN_DEBUG
#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/kernels/internal/reference/slice.h"

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {

namespace {

constexpr int kInputTensor = 0;
constexpr int kBeginTensor = 1;
constexpr int kSizeTensor = 2;
constexpr int kOutputTensor = 0;

const int kMaxDim = 5;

template <typename T>
void GetBeginAndSizeVectors(int dimensions, const TfLiteEvalTensor* begin,
                            const TfLiteEvalTensor* size, int32_t* begins,
                            int32_t* sizes) {
  int offset = kMaxDim - dimensions;
  for (int idx = 0; idx < dimensions; ++idx) {
    begins[offset + idx] = tflite::micro::GetTensorData<T>(begin)[idx];
    sizes[offset + idx] = tflite::micro::GetTensorData<T>(size)[idx];
  }
}

TfLiteStatus SlicePrepare(TfLiteContext* context, TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  TF_LITE_ENSURE_EQ(context, NumInputs(node), 3);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kInputTensor);
  TFLITE_DCHECK(input != nullptr);
  TfLiteTensor* begin =
      micro_context->AllocateTempInputTensor(node, kBeginTensor);
  TFLITE_DCHECK(begin != nullptr);
  TfLiteTensor* size =
      micro_context->AllocateTempInputTensor(node, kSizeTensor);
  TFLITE_DCHECK(size != nullptr);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kOutputTensor);
  TFLITE_DCHECK(output != nullptr);

  // Ensure validity of input tensor and its dimension.
  TFLITE_DCHECK(input->type == output->type);
  TFLITE_DCHECK(begin->type == size->type);
  TFLITE_DCHECK(begin->type == kTfLiteInt32 || begin->type == kTfLiteInt64);
  TFLITE_DCHECK(size->type == kTfLiteInt32 || size->type == kTfLiteInt64);
  TFLITE_DCHECK(NumDimensions(begin) == 1);
  TFLITE_DCHECK(NumDimensions(size) == 1);
  TFLITE_DCHECK(NumElements(begin) == NumElements(size));
  TFLITE_DCHECK(NumDimensions(input) <= kMaxDim);

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(begin);
  micro_context->DeallocateTempTfLiteTensor(size);
  micro_context->DeallocateTempTfLiteTensor(output);

  return kTfLiteOk;
}

TfLiteStatus SliceEval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  const TfLiteEvalTensor* begin =
      tflite::micro::GetEvalInput(context, node, kBeginTensor);
  const TfLiteEvalTensor* size =
      tflite::micro::GetEvalInput(context, node, kSizeTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  tflite::SliceParams op_params;
  op_params.begin_count = kMaxDim;
  op_params.size_count = kMaxDim;
  for (int i = 0; i < kMaxDim; ++i) {
    op_params.begin[i] = 0;
    op_params.size[i] = 1;
  }

  if (begin->type == kTfLiteInt32) {
    GetBeginAndSizeVectors<int32_t>(input->dims->size, begin, size,
                                    op_params.begin, op_params.size);
  } else if (begin->type == kTfLiteInt64) {
    GetBeginAndSizeVectors<int64_t>(input->dims->size, begin, size,
                                    op_params.begin, op_params.size);
  } else {
    MicroPrintf("Begin tensor type %s (%d) not supported.",
                TfLiteTypeGetName(input->type), input->type);
    return kTfLiteError;
  }
  KN_PRINT_Q31_SIZE(op_params.begin, kMaxDim);
  KN_PRINT_Q31_SIZE(op_params.size, kMaxDim);
  
  #if defined(DMX1A_SLICE_OPT)
  bool is_opt = input->dims->size == 3 && op_params.begin[2] == 0 &&
                op_params.size[2] == 1 &&
                op_params.size[3] == input->dims->data[1];
  #endif
  switch (input->type) {
    case kTfLiteFloat32:
      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input),
                     ElementCount(*input->dims));
#if defined(DMX1A_SLICE_OPT)
      if(is_opt) // 2-d slice ,
      {
        float* src0 = (float *)tflite::micro::GetTensorData<float>(input);
        float* dst0 = tflite::micro::GetTensorData<float>(output);
        float *src = src0;
        float* dst = dst0;
        int copy_size = op_params.size[kMaxDim - 1];
        int offset = op_params.begin[kMaxDim - 1];
        for (int ii = 0; ii < input->dims->data[1]; ii++) {
          //for (int jj = op_params.begin[ii];
          //     jj < op_params.begin[ii] + op_params.size[ii]; jj++) {
          const float* src1 = src +offset;

          KN_PRINTD(src1 - src0);
          KN_PRINTD(dst - dst0);
          //KN_PRINTD(op_params.size[kMaxDim - 1 - ii]);
          block_copy_bytes((int8_t*)dst, (int8_t*)src1,
                           sizeof(float) * copy_size);
          src += input->dims->data[2]; //size d
          dst += copy_size;
          }
      } else 
#endif
      {
        reference_ops::Slice<float>(
            op_params, tflite::micro::GetTensorShape(input),
            tflite::micro::GetTensorData<float>(input),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<float>(output));
      }
      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                     ElementCount(*output->dims));
      break;
    case kTfLiteInt32:
      reference_ops::Slice<int32_t>(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int32_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int32_t>(output));
      break;
    case kTfLiteInt8:
      reference_ops::Slice<int8_t>(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int8_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int8_t>(output));
      break;
    case kTfLiteInt16:
      reference_ops::Slice<int16_t>(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int16_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int16_t>(output));
      break;
    case kTfLiteBool:
      reference_ops::Slice<bool>(op_params,
                                 tflite::micro::GetTensorShape(input),
                                 tflite::micro::GetTensorData<bool>(input),
                                 tflite::micro::GetTensorShape(output),
                                 tflite::micro::GetTensorData<bool>(output));
      break;
    default:
      MicroPrintf("Input tensor type %s (%d) not supported.",
                  TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
  }
  return kTfLiteOk;
}

}  // namespace

TFLMRegistration Register_SLICE() {
  return tflite::micro::RegisterOp(nullptr, SlicePrepare, SliceEval);
}

}  // namespace tflite
