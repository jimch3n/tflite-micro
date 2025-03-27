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
//#define KN_DEBUG
#include "tensorflow/lite/micro/ia8201/config.h"

#if 1  // ndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/strided_slice.h"
#endif
#include <cstdint>
#include <cstring>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"

#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/strided_slice.h"
namespace tflite {
namespace {

struct StridedSliceContext {
  StridedSliceContext(TfLiteContext* context, TfLiteNode* node) {
    params = reinterpret_cast<TfLiteStridedSliceParams*>(node->builtin_data);
    micro_context = GetMicroContext(context);
    input =
        micro_context->AllocateTempInputTensor(node, kStridedSliceInputTensor);
    begin =
        micro_context->AllocateTempInputTensor(node, kStridedSliceBeginTensor);
    end = micro_context->AllocateTempInputTensor(node, kStridedSliceEndTensor);
    strides = micro_context->AllocateTempInputTensor(
        node, kStridedSliceStridesTensor);
    output = micro_context->AllocateTempOutputTensor(node,
                                                     kStridedSliceOutputTensor);
    dims = NumDimensions(input);
  }
  ~StridedSliceContext() {
    micro_context->DeallocateTempTfLiteTensor(input);
    micro_context->DeallocateTempTfLiteTensor(begin);
    micro_context->DeallocateTempTfLiteTensor(end);
    micro_context->DeallocateTempTfLiteTensor(strides);
    micro_context->DeallocateTempTfLiteTensor(output);
  }
  const TfLiteStridedSliceParams* params;
  MicroContext* micro_context;
  TfLiteTensor* input;
  TfLiteTensor* begin;
  TfLiteTensor* end;
  TfLiteTensor* strides;
  TfLiteTensor* output;
  int dims;
};


int32_t ia8201_strided_slice_int8(int8_t* __restrict__ p_out,
  const   int8_t* __restrict__ p_inp,
  int32_t start_0, int32_t stop_0,
  int32_t start_1, int32_t stop_1,
  int32_t start_2, int32_t stop_2,
  int32_t start_3, int32_t stop_3,
  int32_t start_4, int32_t stop_4,
  int32_t stride_0, int32_t stride_1,
  int32_t stride_2, int32_t stride_3, int32_t stride_4,
  int32_t dims_1, int32_t dims_2,
  int32_t dims_3, int32_t dims_4)
{
  /* NULL pointer checks */
  ARG_CHK_PTR(p_out, -1);
  ARG_CHK_PTR(p_inp, -1);

  /* Pointer alignment checks */
  ARG_CHK_ALIGN(p_out, sizeof(int8_t), -1);
  ARG_CHK_ALIGN(p_inp, sizeof(int8_t), -1);

  /* Invalid input checks */
  ARG_CHK_COND(((dims_1 <= 0) || (dims_2 <= 0) || (dims_3 <= 0) || (dims_4 <= 0)), -1);
  ARG_CHK_COND(((stride_0 == 0) || (stride_1 == 0) || (stride_2 == 0) || (stride_3 == 0) || (stride_4 == 0)), -1);
  ARG_CHK_COND(((stride_0 != 1) || (start_0 != 0) || (stop_0 != 1)), -1); /* TFLM reference Op only supports upto 4D cases*/
  /* Below conditions are derived from TFLM ref implementation */
  if (stride_1 > 0)
  {
    ARG_CHK_COND(((start_1 < 0) || (start_1 > dims_1) || (stop_1 < 0) || (stop_1 > dims_1)), -1);
  }
  else
  {
    ARG_CHK_COND(((start_1 < -1) || (start_1 > (dims_1 - 1)) || (stop_1 < -1) || (stop_1 > (dims_1 - 1))), -1);
  }
  if (stride_2 > 0)
  {
    ARG_CHK_COND(((start_2 < 0) || (start_2 > dims_2) || (stop_2 < 0) || (stop_2 > dims_2)), -1);
  }
  else
  {
    ARG_CHK_COND(((start_2 < -1) || (start_2 > (dims_2 - 1)) || (stop_2 < -1) || (stop_2 > (dims_2 - 1))), -1);
  }
  if (stride_3 > 0)
  {
    ARG_CHK_COND(((start_3 < 0) || (start_3 > dims_3) || (stop_3 < 0) || (stop_3 > dims_3)), -1);
  }
  else
  {
    ARG_CHK_COND(((start_3 < -1) || (start_3 > (dims_3 - 1)) || (stop_3 < -1) || (stop_3 > (dims_3 - 1))), -1);
  }
  if (stride_4 > 0)
  {
    ARG_CHK_COND(((start_4 < 0) || (start_4 > dims_4) || (stop_4 < 0) || (stop_4 > dims_4)), -1);
  }
  else
  {
    ARG_CHK_COND(((start_4 < -1) || (start_4 > (dims_4 - 1)) || (stop_4 < -1) || (stop_4 > (dims_4 - 1))), -1);
  }

  int i0, i1, i2, i3, i4;
  int a1 = dims_1 * dims_2 * dims_3 * dims_4;
  int a2 = dims_2 * dims_3 * dims_4;
  int a3 = dims_3 * dims_4;
  int a4 = dims_4;

  if ((stride_0 == 1) && (stride_1 == 1) && (stride_2 == 1) && (stride_3 == 1) && (stride_4 == 1))
  {
    int start_0_a1 = start_0 * a1;
    int start_1_a2 = start_1 * a2;
    int start_2_a3 = start_2 * a3;
    int start_3_a4 = start_3 * a4;

    int stride_0_a1 = a1;
    int stride_1_a2 = a2;
    int stride_2_a3 = a3;
    int stride_3_a4 = a4;

    int stop_2_start_2_a3 = (stop_2 - start_2) * a3;
    int stop_3_start_3_a4 = (stop_3 - start_3) * a4;
    int stop_4_start_4 = (stop_4 - start_4);

    int8_t* p_inp0 = (int8_t*)p_inp + (start_0_a1);

    for (i0 = start_0; i0 < stop_0; i0++)
    {
      int8_t* p_inp1 = p_inp0 + (start_1_a2);
      for (i1 = start_1; i1 < stop_1; i1++)
      {
        int8_t* p_inp2 = p_inp1 + (start_2_a3);
        if ((start_3 == 0) && (start_4 == 0) && (stop_3 == dims_3) && (stop_4 == dims_4))
        {
          //xa_nn_memcpy((void*)p_out, (void*)p_inp2, stop_2_start_2_a3);
          block_copy_bytes(p_out, p_inp2, stop_2_start_2_a3);
          p_out += stop_2_start_2_a3;
        }
        else
        {
          for (i2 = start_2; i2 < stop_2; i2++)
          {
            int8_t* p_inp3 = p_inp2 + (start_3_a4);
            if ((start_4 == 0) && (stop_4 == dims_4))
            {
              block_copy_bytes((int8_t*)p_out, (int8_t*)p_inp3, stop_3_start_3_a4);
              p_out += stop_3_start_3_a4;
            }
            else
            {
              for (i3 = start_3; i3 < stop_3; i3++)
              {
                int8_t* p_inp4 = p_inp3 + start_4;
                block_copy_bytes((int8_t*)p_out, (int8_t*)p_inp4, stop_4_start_4);
                p_out += stop_4_start_4;
                p_inp3 += stride_3_a4;
              } // for i3
            }
            p_inp2 += stride_2_a3;
          } // for i2
        }
        p_inp1 += stride_1_a2;
      } //for i1
      p_inp0 += stride_0_a1;
    } //for i0
  }
  else
  {
    /* ceil((stop - start) / stride) */
    int i0_cnt = ((stop_0 - start_0 + (stride_0 - (stride_0 > 0 ? 1 : -1))) / stride_0);
    int i1_cnt = ((stop_1 - start_1 + (stride_1 - (stride_1 > 0 ? 1 : -1))) / stride_1);
    int i2_cnt = ((stop_2 - start_2 + (stride_2 - (stride_2 > 0 ? 1 : -1))) / stride_2);
    int i3_cnt = ((stop_3 - start_3 + (stride_3 - (stride_3 > 0 ? 1 : -1))) / stride_3);
    int i4_cnt = ((stop_4 - start_4 + (stride_4 - (stride_4 > 0 ? 1 : -1))) / stride_4);

    i0_cnt = i0_cnt < 0 ? 0 : i0_cnt;
    i1_cnt = i1_cnt < 0 ? 0 : i1_cnt;
    i2_cnt = i2_cnt < 0 ? 0 : i2_cnt;
    i3_cnt = i3_cnt < 0 ? 0 : i3_cnt;
    i4_cnt = i4_cnt < 0 ? 0 : i4_cnt;

    int start_0_a1 = start_0 * a1;
    int start_1_a2 = start_1 * a2;
    int start_2_a3 = start_2 * a3;
    int start_3_a4 = start_3 * a4;

    int stride_0_a1 = stride_0 * a1;
    int stride_1_a2 = stride_1 * a2;
    int stride_2_a3 = stride_2 * a3;
    int stride_3_a4 = stride_3 * a4;

    int stop_2_start_2_a3 = (stop_2 - start_2) * a3;
    int stop_3_start_3_a4 = (stop_3 - start_3) * a4;
    int stop_4_start_4 = (stop_4 - start_4);

    int8_t* p_inp0 = (int8_t*)p_inp + (start_0_a1);
    for (i0 = 0; i0 < i0_cnt; i0++)
    {
      int8_t* p_inp1 = p_inp0 + (start_1_a2);
      for (i1 = 0; i1 < i1_cnt; i1++)
      {
        int8_t* p_inp2 = p_inp1 + (start_2_a3);
        if ((stride_2 == 1) && (stride_3 == 1) && (stride_4 == 1) && (start_3 == 0) && (start_4 == 0) && (stop_3 == dims_3) && (stop_4 == dims_4))
        {
          block_copy_bytes((int8_t*)p_out, (int8_t*)p_inp2, stop_2_start_2_a3);
          p_out += stop_2_start_2_a3;
        }
        else
        {
          for (i2 = 0; i2 < i2_cnt; i2++)
          {
            int8_t* p_inp3 = p_inp2 + (start_3_a4);
            if ((stride_3 == 1) && (stride_4 == 1) && (start_4 == 0) && (stop_4 == dims_4))
            {
              block_copy_bytes((int8_t*)p_out, (int8_t*)p_inp3, stop_3_start_3_a4);
              p_out += stop_3_start_3_a4;
            }
            else
            {
              for (i3 = 0; i3 < i3_cnt; i3++)
              {
                int8_t* p_inp4 = p_inp3 + start_4;
                if (stride_4 == 1)
                {
                  block_copy_bytes((int8_t*)p_out, (int8_t*)p_inp4, stop_4_start_4);
                  p_out += stop_4_start_4;
                }
                else
                {
                  int8_t d1;
                  for (i4 = 0; i4 < i4_cnt; i4++)
                  {
                    d1 = *p_inp4;
                    *p_out++ = d1;
                    p_inp4 += (stride_4 * sizeof(int8_t));
                  } //for i4
                }
                p_inp3 += stride_3_a4;
              } // for i3
            }
            p_inp2 += stride_2_a3;
          } // for i2
        }
        p_inp1 += stride_1_a2;
      } //for i1
      p_inp0 += stride_0_a1;
    } //for i0
  }
  return 0;
}


#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
void StridedSlice_int8(const tflite::StridedSliceParams& op_params,
  const RuntimeShape& unextended_input_shape,
  const int8_t* input_data,
  const RuntimeShape& unextended_output_shape,
  int8_t* output_data) {
  using ::tflite::strided_slice::StartForAxis;
  using ::tflite::strided_slice::StopForAxis;

  //ruy::profiler::ScopeLabel label("StridedSlice");

  // Note that the output_shape is not used herein.
  tflite::StridedSliceParams params_copy = op_params;

  TFLITE_DCHECK_LE(unextended_input_shape.DimensionsCount(), 5);
  TFLITE_DCHECK_LE(unextended_output_shape.DimensionsCount(), 5);
  const RuntimeShape input_shape =
    RuntimeShape::ExtendedShape(5, unextended_input_shape);
  const RuntimeShape output_shape =
    RuntimeShape::ExtendedShape(5, unextended_output_shape);

  // Reverse and pad to 5 dimensions because that is what the runtime code
  // requires (ie. all shapes must be 5D and are given backwards).
  ::tflite::strided_slice::StridedSlicePadIndices(&params_copy, 5);

  const int start_0 = StartForAxis(params_copy, input_shape, 0);
  const int stop_0 = StopForAxis(params_copy, input_shape, 0, start_0);
  const int start_1 = StartForAxis(params_copy, input_shape, 1);
  const int stop_1 = StopForAxis(params_copy, input_shape, 1, start_1);
  const int start_2 = StartForAxis(params_copy, input_shape, 2);
  const int stop_2 = StopForAxis(params_copy, input_shape, 2, start_2);
  const int start_3 = StartForAxis(params_copy, input_shape, 3);
  const int stop_3 = StopForAxis(params_copy, input_shape, 3, start_3);
  const int start_4 = StartForAxis(params_copy, input_shape, 4);
  const int stop_4 = StopForAxis(params_copy, input_shape, 4, start_4);

  ia8201_strided_slice_int8(output_data, input_data, static_cast<int>(start_0),
    static_cast<int>(stop_0), static_cast<int>(start_1),
    static_cast<int>(stop_1), static_cast<int>(start_2),
    static_cast<int>(stop_2), static_cast<int>(start_3),
    static_cast<int>(stop_3), static_cast<int>(start_4),
    static_cast<int>(stop_4), params_copy.strides[0],
    params_copy.strides[1], params_copy.strides[2],
    params_copy.strides[3], params_copy.strides[4],
    input_shape.Dims(1), input_shape.Dims(2),
    input_shape.Dims(3), input_shape.Dims(4));
}
#endif  // defined(HIFI3) || defined(HIFI4) || defined(HIFI5)


TfLiteStatus StridedSliceEval(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const StridedSliceOpData* op_data =
      (static_cast<const StridedSliceOpData*>(node->user_data));

  const StridedSliceParams& op_params = op_data->op_params;
  //    *(static_cast<const StridedSliceParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kStridedSliceInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kStridedSliceOutputTensor);
  switch (output->type) {
    case kTfLiteFloat32:

      // KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input),
      // ElementCount(*input->dims));
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
      KN_PRINTD(op_data->opt_constraint);
      if (op_data->opt_constraint > 0) {
        const float* Src =
            tflite::micro::GetTensorData<float>(input) + op_data->src_offset;
        int nElement = ElementCount(*output->dims);

        float* Dst = tflite::micro::GetTensorData<float>(output);
        SlicedCopyOptOffset<float>(Src, Dst, nElement);
      }
      /*else {
          SlicedCopyFloat(tflite::micro::GetTensorData<float>(input),
              op_data->srcIdx, tflite::micro::GetTensorData<float>(output),
              ElementCount(*output->dims));
      }*/
      else
#endif
      {
        reference_ops::StridedSlice(
            op_params, tflite::micro::GetTensorShape(input),
            tflite::micro::GetTensorData<float>(input),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<float>(output));
      }
      // KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
      // ElementCount(*output->dims));

      break;
      // REMOVE SAVE CODE SIZE
#if !defined(DMX1A_STRIDED_SLICE_OPT) && !defined(HMD1A_STRIDED_SLICE_OPT)
    case kTfLiteUInt8:
      reference_ops::StridedSlice(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<uint8_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<uint8_t>(output));
      break;
#endif
    case kTfLiteInt8:
      KN_PRINTD(op_data->opt_constraint);
      KN_PRINT_Q7_SIZE_ATMOST(tflite::micro::GetTensorData<int8_t>(input),
                       ElementCount(*input->dims),1024);
#if 0 //defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)

      if (op_data->opt_constraint > 0) {
        const int8_t* Src =
            tflite::micro::GetTensorData<int8_t>(input) + op_data->src_offset;
        int nElement = ElementCount(*output->dims);
        int8_t* Dst = tflite::micro::GetTensorData<int8_t>(output);
        SlicedCopyOptOffset<int8_t>(Src, Dst, nElement);
      }
      /* else {
           SlicedStrideCopyInt8(tflite::micro::GetTensorData<int8_t>(input),
               op_data->srcIdx, tflite::micro::GetTensorData<int8_t>(output),
               ElementCount(*output->dims));
       }*/
      else
#endif

      {
        // new opt without constriant
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
        StridedSlice_int8(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int8_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int8_t>(output));
#else
        reference_ops::StridedSlice(
            op_params, tflite::micro::GetTensorShape(input),
            tflite::micro::GetTensorData<int8_t>(input),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<int8_t>(output));
#endif
      }
      KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                       ElementCount(*output->dims));
      break;
      // REMOVE SAVE CODE SIZE
    case kTfLiteFloat16:

#if 0 //defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
      KN_PRINTD(op_data->opt_constraint);
      if (op_data->opt_constraint > 0) {
        const int16_t* Src =
            tflite::micro::GetTensorData<int16_t>(input) + op_data->src_offset;
        int nElement = ElementCount(*output->dims);

        int16_t* Dst = tflite::micro::GetTensorData<int16_t>(output);
        SlicedCopyOptOffset<int16_t>(Src, Dst, nElement);
      } else
#endif
      {

        reference_ops::StridedSlice(
            op_params, tflite::micro::GetTensorShape(input),
            tflite::micro::GetTensorData<int16_t>(input),
            tflite::micro::GetTensorShape(output),
            tflite::micro::GetTensorData<int16_t>(output));
      }
      break;
    case kTfLiteInt16:
      reference_ops::StridedSlice(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int16_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int16_t>(output));
      break;
    case kTfLiteInt32:
      KN_PRINTX(tflite::micro::GetTensorData<int32_t>(output));
      reference_ops::StridedSlice(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int32_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int32_t>(output));

      KN_PRINT_Q31_SIZE(output->data.i32,
                        ElementCount(*output->dims));
      break;
    case kTfLiteBool:
      reference_ops::StridedSlice(op_params,
                                  tflite::micro::GetTensorShape(input),
                                  tflite::micro::GetTensorData<bool>(input),
                                  tflite::micro::GetTensorShape(output),
                                  tflite::micro::GetTensorData<bool>(output));
      break;

    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
  }
  return kTfLiteOk;
}
// multiple evaluation ffunction to register correct one to saving code size.
// since template cost around 3k for each type

TfLiteStatus StridedSliceEvalFloat32(TfLiteContext* context, TfLiteNode* node) {
  const StridedSliceOpData* op_data =
      (static_cast<const StridedSliceOpData*>(node->user_data));

  // const StridedSliceParams& op_params = op_data->op_params;
  //    *(static_cast<const StridedSliceParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kStridedSliceInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kStridedSliceOutputTensor);

  if (output->type != kTfLiteFloat32) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(input->type), input->type);
    return kTfLiteError;
  }
  // KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input),
  // ElementCount(*input->dims));
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
  KN_PRINTD(op_data->opt_constraint);
  if (op_data->opt_constraint > 0) {
    const float* Src =
        tflite::micro::GetTensorData<float>(input) + op_data->src_offset;
    int nElement = ElementCount(*output->dims);
    float* Dst = tflite::micro::GetTensorData<float>(output);
    SlicedCopyOptOffset<float>(Src, Dst, nElement);
  } else
#endif
  {
    //  else {
    //     SlicedCopyFloat(tflite::micro::GetTensorData<float>(input),
    //       op_data->srcIdx, tflite::micro::GetTensorData<float>(output),
    //       ElementCount(*output->dims));
    // }

    const StridedSliceParams& op_params = op_data->op_params;

    reference_ops::StridedSlice(op_params, tflite::micro::GetTensorShape(input),
                                tflite::micro::GetTensorData<float>(input),
                                tflite::micro::GetTensorShape(output),
                                tflite::micro::GetTensorData<float>(output));
  }

  //  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
  //  ElementCount(*output->dims));

  return kTfLiteOk;
}
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
TfLiteStatus StridedSliceEvalInt8(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const StridedSliceParams& op_params =
      *(static_cast<const StridedSliceParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kStridedSliceInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kStridedSliceOutputTensor);
  if (output->type != kTfLiteInt8) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(input->type), input->type);
    return kTfLiteError;
  }
  reference_ops::StridedSlice(op_params, tflite::micro::GetTensorShape(input),
                              tflite::micro::GetTensorData<int8_t>(input),
                              tflite::micro::GetTensorShape(output),
                              tflite::micro::GetTensorData<int8_t>(output));
  return kTfLiteOk;
}

TfLiteStatus StridedSliceEvalInt16(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const StridedSliceParams& op_params =
      *(static_cast<const StridedSliceParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kStridedSliceInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kStridedSliceOutputTensor);
  if (output->type != kTfLiteInt16) {
    TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                       TfLiteTypeGetName(input->type), input->type);
    return kTfLiteError;
  }

  reference_ops::StridedSlice(op_params, tflite::micro::GetTensorShape(input),
                              tflite::micro::GetTensorData<int16_t>(input),
                              tflite::micro::GetTensorShape(output),
                              tflite::micro::GetTensorData<int16_t>(output));
  return kTfLiteOk;
}
#endif
}  // namespace

TFLMRegistration Register_STRIDED_SLICE() {
  return tflite::micro::RegisterOp(StridedSliceInit,
                                   /*prepare=*/StridedSlicePrepare,
                                   /*invoke=*/StridedSliceEval);
}

TFLMRegistration Register_STRIDED_SLICE_FLOAT32() {
  return tflite::micro::RegisterOp(StridedSliceInit,
                                   /*prepare=*/StridedSlicePrepare,
                                   /*invoke=*/StridedSliceEvalFloat32);
}
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
TFLMRegistration Register_STRIDED_SLICE_INT8() {
  return tflite::micro::RegisterOp(StridedSliceInit,
                                   /*prepare=*/StridedSlicePrepare,
                                   /*invoke=*/StridedSliceEvalInt8);
}

TFLMRegistration Register_STRIDED_SLICE_INT16() {
  return tflite::micro::RegisterOp(StridedSliceInit,
                                   /*prepare=*/StridedSlicePrepare,
                                   /*invoke=*/StridedSliceEvalInt16);
}
#endif
//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
