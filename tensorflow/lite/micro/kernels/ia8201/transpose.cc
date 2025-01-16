/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

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
#include "tensorflow/lite/kernels/internal/reference/transpose.h"

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"


namespace tflite {
namespace {

constexpr int kInputTensor = 0;
constexpr int kPermTensor = 1;
constexpr int kOutputTensor = 0;

struct TransposeContext {
  TransposeContext(TfLiteContext* context, TfLiteNode* node) {
    micro_context = GetMicroContext(context);
    input = micro_context->AllocateTempInputTensor(node, kInputTensor);
    perm = micro_context->AllocateTempInputTensor(node, kPermTensor);
    output = micro_context->AllocateTempOutputTensor(node, kOutputTensor);
  }
  ~TransposeContext() {
    micro_context->DeallocateTempTfLiteTensor(input);
    micro_context->DeallocateTempTfLiteTensor(perm);
    micro_context->DeallocateTempTfLiteTensor(output);
  }
  MicroContext* micro_context;
  TfLiteTensor* input;
  TfLiteTensor* perm;
  TfLiteTensor* output;
};

TfLiteStatus TransposePrepare(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  TransposeContext op_context(context, node);

  // Ensure validity of input tensor.
  TF_LITE_ENSURE_MSG(context, NumDimensions(op_context.input) <= 5,
                     "Transpose op only supports 1D-5D input arrays.");
  TF_LITE_ENSURE_TYPES_EQ(context, op_context.input->type,
                          op_context.output->type);

  int dims = NumDimensions(op_context.input);
  const int32_t* perm_data = GetTensorData<int32_t>(op_context.perm);

  // Ensure validity of the permutations tensor as a 1D tensor.
  TF_LITE_ENSURE_EQ(context, NumDimensions(op_context.perm), 1);
  TF_LITE_ENSURE_EQ(context, op_context.perm->dims->data[0], dims);
  for (int idx = 0; idx < dims; ++idx) {
    TF_LITE_ENSURE_MSG(context, (perm_data[idx] >= 0 && perm_data[idx] < dims),
                       "Transpose op permutations array is out of bounds.");
  }

  return kTfLiteOk;
}

TfLiteStatus TransposeEval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* perm_tensor =
      tflite::micro::GetEvalInput(context, node, kPermTensor);
  const int32_t* perm_data = perm_tensor->data.i32;
  const int size = perm_tensor->dims->data[0];
  TransposeParams params;
  params.perm_count = size;
  for (int i = 0; i < size; ++i) {
    params.perm[i] = perm_data[i];
  }
  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);
  // convolution happen in pytorch to tflite
  //bool is_4d_0231 = false;
  // n==1
  #if defined(DMX1A_TRANSPOSE_OPT)
  bool is_4d_0231 = size == 4 && params.perm[0] == 0 && params.perm[1] == 2 &&
                    params.perm[2] == 3 && params.perm[3] == 1 &&
                    input->dims->data[0]==1;
                    // make sure is 1d conv
  KN_PRINTD(is_4d_0231);
  KN_PRINT_Q31_SIZE(params.perm, size);
  #endif

 
  // Transpose kernel only does rearranging values not numeric evaluations
  // on each cell. It's safe to implement per size of scalar type and this
  // trick keeps the total code size in a reasonable range.


    KN_PRINT_Q31_SIZE(input->dims->data, input->dims->size);
  // Transpose kernel only does
  switch (input->type) {
    case kTfLiteFloat32:
      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input),
                     ElementCount(*input->dims));
#if defined(DMX1A_TRANSPOSE_OPT)
      if(is_4d_0231) {
        //nchw -> nhwc, h ==1
        int channel = input->dims->data[1];
        int height  = input->dims->data[2];
        int width  = input->dims->data[3];
        const float *src = tflite::micro::GetTensorData<float>(input);
        float *dst = tflite::micro::GetTensorData<float>(output);
        int hw = height*width;
        const float *pSrc = src;
        int loopLim = hw>>2;

        for(int ii =0; ii < channel; ii++)
        {
          vr128 VR_src;
          ulsr128 UR_src = align_32x4_load(pSrc);
          float *pDst = &dst[ii];
          //pSrc = &src[ii * hw];
          int jj=0;
          if(loopLim > 0)
          {
            
            for(jj =0; jj <loopLim; jj++)
            {
              load_32x4_vr_a(VR_src, UR_src, pSrc);
              //KN_PRINTD(ii*hw+jj);KN_PRINTD(jj*channel+ii);
            //    dst[jj*channel+ii] = src[ii*hw+jj];
              store32x1_vr_postR(VR_src, pDst, channel, VRQ0);
              store32x1_vr_postR(VR_src, pDst, channel, VRQ1);
              store32x1_vr_postR(VR_src, pDst, channel, VRQ2);
              store32x1_vr_postR(VR_src, pDst, channel, VRQ3);
            }
          }
          for(jj =loopLim<<2; jj < hw; jj++)
          {
            load32x1_vr_postI(VR_src, pSrc, INC1, VRQ0);
            store32x1_vr_postR(VR_src, pDst, channel, VRQ0);
          }
        }
      } else 
  #endif
      {
        reference_ops::Transpose(params, tflite::micro::GetTensorShape(input),
                                 tflite::micro::GetTensorData<float>(input),
                                 tflite::micro::GetTensorShape(output),
                                 tflite::micro::GetTensorData<float>(output));
      }
      KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                     ElementCount(*output->dims));

      break;
    case kTfLiteInt8:
      reference_ops::Transpose(params, tflite::micro::GetTensorShape(input),
                               tflite::micro::GetTensorData<int8_t>(input),
                               tflite::micro::GetTensorShape(output),
                               tflite::micro::GetTensorData<int8_t>(output));
      break;
    default:
      MicroPrintf(
          "Type %s is currently not supported by Transpose. "
          "Only float32 and int8 is supported",
          TfLiteTypeGetName(input->type));
      return kTfLiteError;
  }

  return kTfLiteOk;
}

}  // namespace

TFLMRegistration Register_TRANSPOSE() {
  return tflite::micro::RegisterOp(nullptr, TransposePrepare, TransposeEval);
}
}  // namespace tflite
