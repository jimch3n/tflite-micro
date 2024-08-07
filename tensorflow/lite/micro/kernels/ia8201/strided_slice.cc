/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

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

#if 1 //ndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/strided_slice.h"
#endif
#include <cmath>
#include <cstring>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {
namespace {
//namespace micro {
//namespace strided_slice {

constexpr int kInputTensor = 0;
constexpr int kBeginTensor = 1;
constexpr int kEndTensor = 2;
constexpr int kStridesTensor = 3;
constexpr int kOutputTensor = 0;

struct StridedSliceContext {
  StridedSliceContext(TfLiteContext* context, TfLiteNode* node) {
    params = reinterpret_cast<TfLiteStridedSliceParams*>(node->builtin_data);
    micro_context = GetMicroContext(context);
    input = micro_context->AllocateTempInputTensor(node, kInputTensor);
    begin = micro_context->AllocateTempInputTensor(node, kBeginTensor);
    end = micro_context->AllocateTempInputTensor(node, kEndTensor);
    strides = micro_context->AllocateTempInputTensor(node, kStridesTensor);
    output = micro_context->AllocateTempOutputTensor(node, kOutputTensor);
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
struct StridedSliceOpData {
    tflite::StridedSliceParams op_params;
    int opt_constraint;
    int src_offset;
   // uint16_t* srcIdx;
};
// This Op only supports 1-4D cases and since we use the reference 4D
// implementation, the 1-3D tensors are mapped to 4D.
const int kMaxDim = 4;
// input 1x10x40 -> output -> 1x7x40
template <typename T>
static void SlicedCopyOptOffset(const T* src, T* dst, int nElement)
{
    block_copy_bytes((int8_t*)dst, (int8_t*)src, sizeof(T) * nElement);
}
tflite::StridedSliceParams BuildStridedSliceParams(
    StridedSliceContext* op_context, tflite::StridedSliceParams &op_params) {
  
  op_params.start_indices_count = op_context->dims;
  op_params.stop_indices_count = op_context->dims;
  op_params.strides_count = op_context->dims;

  for (int i = 0; i < op_context->dims; ++i) {
    op_params.start_indices[i] = GetTensorData<int32_t>(op_context->begin)[i];
    op_params.stop_indices[i] = GetTensorData<int32_t>(op_context->end)[i];
    op_params.strides[i] = GetTensorData<int32_t>(op_context->strides)[i];
  }

  op_params.begin_mask = op_context->params->begin_mask;
  op_params.ellipsis_mask = 0;
  op_params.end_mask = op_context->params->end_mask;
  op_params.new_axis_mask = 0;
  op_params.shrink_axis_mask = op_context->params->shrink_axis_mask;
  return op_params;
}

// Processes the indexing tensors (begin, end and strides) to resize the
// output tensor. This function is callable from both Prepare() and Eval() as
// long as the caller ensures the indexing tensors are present.
TfLiteStatus CheckOutputSize(TfLiteContext* context,
                             StridedSliceContext* op_context) {
  using ::tflite::strided_slice::StartForAxis;
  using ::tflite::strided_slice::StopForAxis;
  TfLiteIntArray* output_shape = op_context->output->dims;
  int shape_size = 0;
  // from external
  tflite::StridedSliceParams op_params;  // auto op_params = ;
  BuildStridedSliceParams(op_context, op_params);
  auto input_shape = GetTensorShape(op_context->input);
  for (int idx = 0; idx < op_context->dims; ++idx) {
    int32_t stride = GetTensorData<int32_t>(op_context->strides)[idx];
    TF_LITE_ENSURE_MSG(context, stride != 0, "stride value has to be non-zero");
    int32_t begin = StartForAxis(op_params, input_shape, idx);
    int32_t end = StopForAxis(op_params, input_shape, idx, begin);

    // When shrinking an axis, the end position does not matter (and can be
    // incorrect when negative indexing is used, see Issue #19260). Always use
    // begin + 1 to generate a length 1 slice, since begin has
    // already been adjusted for negative indices by StartForAxis.
    const bool shrink_axis = op_context->params->shrink_axis_mask & (1 << idx);
    if (shrink_axis) {
      end = begin + 1;
    }

    // This is valid for both positive and negative strides
    int32_t dim_shape = std::ceil((end - begin) / static_cast<float>(stride));
    dim_shape = dim_shape < 0 ? 0 : dim_shape;
    if (!shrink_axis) {
      TF_LITE_ENSURE_EQ(context, output_shape->data[shape_size], dim_shape);
      shape_size++;
    }
  }
  TF_LITE_ENSURE_EQ(context, output_shape->size, shape_size);
  return kTfLiteOk;
}

void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof( StridedSliceOpData));
}

TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  StridedSliceOpData* op_data =
      static_cast<StridedSliceOpData*>(node->user_data);
 // StridedSliceParams* op_params2 =
 //     static_cast<StridedSliceParams*>(node->user_data);

  //pOpStridedSliceData->op_params = op_params;
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 4);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);
  StridedSliceContext op_context(context, node);
  TF_LITE_ENSURE_MSG(context, op_context.dims <= kMaxDim,
                     "input dim should not exceed 4");
  //auto params = 
   tflite::StridedSliceParams params; 
  BuildStridedSliceParams(&op_context, params);
  memcpy(&op_data->op_params, &params, sizeof(StridedSliceParams));
  // allocate persist op data to store opt_context

  //pOpStridedSliceData->op_params = op_params;
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)


  // check special case begin 0, x, 0,
  //                    end  0, 0, 0
  //                    strides 1, 1, 1
  // CROP case from source at 2 dim.

      // able to satisfied optimization condition
  auto input_shape = GetTensorShape(op_context.input);
  auto output_shape = GetTensorShape(op_context.output);
  //int output_size = ElementCount(*op_context.output->dims);

  op_data->opt_constraint = 0;
  //op_data->srcIdx = NULL;

  int all_strides_one = 1;
  for (int ii = 0; ii < params.strides_count; ii++)
  {
      if (1 != params.strides[ii])
      {
          all_strides_one = 0; break;
      }
  }
  // linear copy: FIXME to a generic copy and fast
  if (all_strides_one)
  {
      // type 1: dim = 3,
      // begin: 0, x, 0 , x < 0
      // end: 0, 0, 0
      if (params.start_indices_count == 3 && params.stop_indices_count == 3 &&
          (params.stop_indices[0] == 0  && params.stop_indices[1] == 0 && params.stop_indices[2]  == 0 &&
           params.start_indices[0] == 0 && params.start_indices[1] < 0 && params.start_indices[2] == 0))
      {
          op_data->opt_constraint = 1;
          op_data->src_offset = (input_shape.Dims(1) + params.start_indices[1]) * input_shape.Dims(2);

      }
      // type 2: dim = 3,
      // begin: 0, x, 0
      // end:   0, y, 0
      else if (params.start_indices_count == 3 && params.stop_indices_count == 3 &&
              (params.stop_indices[0] == 0 && params.stop_indices[2] == 0 &&
              params.start_indices[0] == 0 && params.start_indices[2] == 0))
      {
          op_data->opt_constraint = 2;
          op_data->src_offset = (params.start_indices[1]) * input_shape.Dims(2);
      }
      // type 3: dim = 4,
      // begin: 0, x, 0, 0
      // end:   0, y, 0, y
      #if 0
      else if (params.start_indices_count == 4 && params.stop_indices_count == 4 &&
              (params.stop_indices[0] == 0  && params.stop_indices[2] == 0 &&
               params.start_indices[0] == 0 && params.start_indices[2] == 0 && params.start_indices[3] == 0))
      {
          op_data->opt_constraint =3;
          op_data->src_offset = ( params.start_indices[1]) * input_shape.Dims(3);
      }
      #endif
  }
  KN_PRINTD(op_data->opt_constraint);
  // TODO: type 3 begin 0,0,0,0 
  //         end 0 1, 0, 1
  //         stride 1, 1, 1, 1
  //else 
//#endif
  //{
  //    op_data->srcIdx = (uint16_t*)context->AllocatePersistentBuffer(context,
  //        sizeof(uint16_t) * output_size);
 // }
#endif
#if 0
  if (op_data->srcIdx)
  {
      switch (op_context.output->type)
      {
      case kTfLiteFloat32:
          // reference _op get source index, and check dst is linear
      {
          reference_ops::StridedSliceSrcIndx<float>(params,
              input_shape,
              output_shape,
              op_data->srcIdx);
      }
      break;
      case kTfLiteInt8:
      case kTfLiteUInt8:
          {
              reference_ops::StridedSliceSrcIndx<int8_t>(params,
                  input_shape,
                  output_shape,
                  op_data->srcIdx);
          }
          break;
      case kTfLiteInt32:
      reference_ops::StridedSliceSrcIndx<int32_t>(params,
                  input_shape,
                  output_shape,
                  op_data->srcIdx);
      break;
    case kTfLiteBool:
      reference_ops::StridedSliceSrcIndx<bool>(params,
                  input_shape,
                  output_shape,
                  op_data->srcIdx);
      break;
      default:
          //TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
         //     TfLiteTypeGetName(op_context.output), iop_context.output);
          return kTfLiteError;
      }
      KN_PRINT_Q15_SIZE(op_data->srcIdx, output_size);
  }
  //KN_PRINTD(pOpStridedSliceData->srcIdx);
  
#endif
  return CheckOutputSize(context, &op_context);
}




TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const StridedSliceOpData * op_data = (static_cast<const StridedSliceOpData*>(node->user_data));

  const StridedSliceParams& op_params = op_data->op_params;
  //    *(static_cast<const StridedSliceParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);
  switch (output->type) {
    case kTfLiteFloat32:

        //KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input), ElementCount(*input->dims));
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
        KN_PRINTD(op_data->opt_constraint);
        if (op_data->opt_constraint > 0)
        {
            const float* Src = tflite::micro::GetTensorData<float>(input) + op_data->src_offset;
            int nElement = ElementCount(*output->dims);

            
            float* Dst = tflite::micro::GetTensorData<float>(output) ;
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
            reference_ops::StridedSlice(op_params,
                tflite::micro::GetTensorShape(input),
                tflite::micro::GetTensorData<float>(input),
                tflite::micro::GetTensorShape(output),
                tflite::micro::GetTensorData<float>(output));
        }
      //KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output), ElementCount(*output->dims));

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
        KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input), ElementCount(*input->dims));
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
        
        if (op_data->opt_constraint > 0)
        {
            const int8_t* Src = tflite::micro::GetTensorData<int8_t>(input) + op_data->src_offset;
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
            reference_ops::StridedSlice(op_params,
                tflite::micro::GetTensorShape(input),
                tflite::micro::GetTensorData<int8_t>(input),
                tflite::micro::GetTensorShape(output),
                tflite::micro::GetTensorData<int8_t>(output));
        }
        KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output), ElementCount(*output->dims));
      break;
      // REMOVE SAVE CODE SIZE
    case kTfLiteFloat16:

#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
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
      reference_ops::StridedSlice(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int32_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int32_t>(output));
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

TfLiteStatus EvalFloat32(TfLiteContext* context, TfLiteNode* node) {

   
   const StridedSliceOpData* op_data = (static_cast<const StridedSliceOpData*>(node->user_data));

   //const StridedSliceParams& op_params = op_data->op_params;
   //    *(static_cast<const StridedSliceParams*>(node->user_data));

   const TfLiteEvalTensor* input =
       tflite::micro::GetEvalInput(context, node, kInputTensor);
   TfLiteEvalTensor* output =
       tflite::micro::GetEvalOutput(context, node, kOutputTensor);

   if (output->type != kTfLiteFloat32)
   {
       TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
           TfLiteTypeGetName(input->type), input->type);
       return kTfLiteError;
   }
       // KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(input), ElementCount(*input->dims));
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
       KN_PRINTD(op_data->opt_constraint);
       if (op_data->opt_constraint > 0)
       {
           const float* Src = tflite::micro::GetTensorData<float>(input) + op_data->src_offset;
           int nElement = ElementCount(*output->dims);
           float* Dst = tflite::micro::GetTensorData<float>(output);
           SlicedCopyOptOffset<float>(Src, Dst, nElement);
       }
       else 
#endif
       {
           //  else {
            //     SlicedCopyFloat(tflite::micro::GetTensorData<float>(input),
              //       op_data->srcIdx, tflite::micro::GetTensorData<float>(output),
              //       ElementCount(*output->dims));
            // }

           const StridedSliceParams& op_params = op_data->op_params;
           
           reference_ops::StridedSlice(op_params,
               tflite::micro::GetTensorShape(input),
               tflite::micro::GetTensorData<float>(input),
               tflite::micro::GetTensorShape(output),
               tflite::micro::GetTensorData<float>(output));
       }

       //  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output), ElementCount(*output->dims));

  return kTfLiteOk;
}
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
TfLiteStatus EvalInt8(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const StridedSliceParams& op_params =
      *(static_cast<const StridedSliceParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);
   if (output->type !=kTfLiteInt8)
    {
          TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
    }
      reference_ops::StridedSlice(op_params,
                                  tflite::micro::GetTensorShape(input),
                                  tflite::micro::GetTensorData<int8_t>(input),
                                  tflite::micro::GetTensorShape(output),
                                  tflite::micro::GetTensorData<int8_t>(output));
  return kTfLiteOk;
}

TfLiteStatus EvalInt16(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const StridedSliceParams& op_params =
      *(static_cast<const StridedSliceParams*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);
   if (output->type !=kTfLiteInt16)
    {
          TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
    }

      reference_ops::StridedSlice(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int16_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int16_t>(output));
  return kTfLiteOk;
}
#endif
}  // namespace strided_slice

TFLMRegistration Register_STRIDED_SLICE() {
  return tflite::micro::RegisterOp(Init,
          /*prepare=*/Prepare,
          /*invoke=*/Eval);
}

TFLMRegistration Register_STRIDED_SLICE_FLOAT32() {
 return tflite::micro::RegisterOp(Init,
          /*prepare=*/Prepare,
          /*invoke=*/EvalFloat32);
}
#if defined(DMX1A_STRIDED_SLICE_OPT) || defined(HMD1A_STRIDED_SLICE_OPT)
TFLMRegistration Register_STRIDED_SLICE_INT8() {
  return tflite::micro::RegisterOp(Init,
          /*prepare=*/Prepare,
          /*invoke=*/EvalInt8);
}


TFLMRegistration Register_STRIDED_SLICE_INT16() {
  return tflite::micro::RegisterOp(Init,
          /*prepare=*/Prepare,
          /*invoke=*/EvalInt16);
}
#endif
//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
