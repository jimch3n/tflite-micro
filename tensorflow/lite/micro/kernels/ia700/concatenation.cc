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
#include "tensorflow/lite/kernels/internal/reference/concatenation.h"

#include <cstdint>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/ia700/config.h"
#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
namespace tflite {
// namespace  {
// namespace micro {
namespace {

constexpr int kMaxInputNum = 64;  // Maximum number of input tensors
constexpr int kOutputTensor = 0;

struct OpData {
  ConcatenationParams params;
  uint16_t* input_offset;
  uint32_t* input_size;
  int outer_size;
  int inputs_count;
  int opt_constraint;
};

// Handles negative axis index, coerces to positive index value.
inline int CalculatePositiveAxis(int axis, const TfLiteTensor* output_tensor) {
  if (axis >= 0) {
    return axis;
  } else {
    return NumDimensions(output_tensor) + axis;
  }
}

// The following functions are helpers to get tensor data in the format that the
// reference op implementation expects. They provide the same functionality as
// class VectorOfTensors and class VectorOfQuantizedTensors in TFLite.

// Gets shapes from a list of tensors.
inline void GetAllInputTensorShapes(const TfLiteContext* context,
                                    const TfLiteNode* node,
                                    RuntimeShape all_shapes[kMaxInputNum]) {
  TFLITE_DCHECK(context != nullptr);
  TFLITE_DCHECK(node != nullptr);
  for (int i = 0; i < node->inputs->size; ++i) {
    const TfLiteEvalTensor* t = tflite::micro::GetEvalInput(context, node, i);
    RuntimeShape shape = tflite::micro::GetTensorShape(t);
    all_shapes[i].ReplaceWith(shape.DimensionsCount(), shape.DimsData());
  }
}

// Get shape pointers from a list of shapes.
inline void GetShapesPointers(const RuntimeShape* shapes, size_t num,
                              const RuntimeShape* pointers[]) {
  for (size_t i = 0; i < num; ++i) {
    pointers[i] = &shapes[i];
  }
}

// Gets data pointers from a list of tensors.
template <typename T>
inline void GetAllInputTensorData(const TfLiteContext* context,
                                  const TfLiteNode* node,
                                  T* all_data[kMaxInputNum]) {
  TFLITE_DCHECK(context != nullptr);
  TFLITE_DCHECK(node != nullptr);
  for (int i = 0; i < node->inputs->size; ++i) {
    const TfLiteEvalTensor* t = tflite::micro::GetEvalInput(context, node, i);
    all_data[i] = tflite::micro::GetTensorData<T>(t);
  }
}

template <typename data_type>
void EvalUnquantized(TfLiteContext* context, TfLiteNode* node) {
  // Collect the shapes and data pointer of input tensors
  RuntimeShape inputs_shape[kMaxInputNum];
  const RuntimeShape* inputs_shape_ptr[kMaxInputNum];
  const data_type* inputs_data[kMaxInputNum];
  GetAllInputTensorShapes(context, node, inputs_shape);
  GetShapesPointers(inputs_shape, node->inputs->size, inputs_shape_ptr);
  GetAllInputTensorData(context, node, inputs_data);

  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData* data = static_cast<const OpData*>(node->user_data);

#if defined(HEMILITE_CONCATENATION_OPT)
  if (data->opt_constraint) {
    int8_t* output_ptr = tflite::micro::GetTensorData<int8_t>(output);
    uint32_t* cp_size = data->input_size;
    uint16_t* cp_offset = data->input_offset;
    for (int k = 0; k < data->outer_size; k++) {
      for (int i = 0; i < data->inputs_count; ++i) {
        const int copy_size =
            *cp_size;  // input_shapes[i]->Dims(axis) * base_inner_size;
        const data_type* input_ptr = inputs_data[i] + *cp_offset;

        block_copy_bytes((int8_t*)output_ptr, (const int8_t*)input_ptr,
                         copy_size);
        cp_offset++;
        cp_size++;
        output_ptr += copy_size;  // use byte as pointer
      }
    }
  } else
#endif
  {
    reference_ops::Concatenation(
        data->params, inputs_shape_ptr, inputs_data,
        tflite::micro::GetTensorShape(output),
        tflite::micro::GetTensorData<data_type>(output));
  }
}

void EvalQuantizedUInt8(TfLiteContext* context, TfLiteNode* node) {
  // Collect the shapes and data pointer of input tensors
  RuntimeShape inputs_shape[kMaxInputNum];
  const RuntimeShape* inputs_shape_ptr[kMaxInputNum];
  const uint8_t* inputs_data[kMaxInputNum];
  GetAllInputTensorShapes(context, node, inputs_shape);
  GetShapesPointers(inputs_shape, node->inputs->size, inputs_shape_ptr);
  GetAllInputTensorData(context, node, inputs_data);

  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData* data = static_cast<const OpData*>(node->user_data);

  reference_ops::ConcatenationWithScaling(
      data->params, inputs_shape_ptr, inputs_data,
      tflite::micro::GetTensorShape(output),
      tflite::micro::GetTensorData<uint8_t>(output));
}

void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  // This function only checks the types. Additional shape validations are
  // performed in the reference implementation called during Eval().
  const TfLiteConcatenationParams* params =
      reinterpret_cast<TfLiteConcatenationParams*>(node->builtin_data);

  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input_tensor = micro_context->AllocateTempInputTensor(node, 0);
  TF_LITE_ENSURE(context, input_tensor != nullptr);
  TfLiteType input_type = input_tensor->type;
  TfLiteTensor* output_tensor =
      micro_context->AllocateTempOutputTensor(node, kOutputTensor);
  TF_LITE_ENSURE(context, output_tensor != nullptr);
  TfLiteType output_type = output_tensor->type;

  micro_context->DeallocateTempTfLiteTensor(input_tensor);
  micro_context->DeallocateTempTfLiteTensor(output_tensor);

  // Check activation and input type
  TF_LITE_ENSURE_EQ(context, params->activation, kTfLiteActNone);
  TF_LITE_ENSURE(context,
                 input_type == kTfLiteFloat32 || input_type == kTfLiteInt8 ||
                     input_type == kTfLiteInt16 || input_type == kTfLiteInt32 ||
                     input_type == kTfLiteInt64 || input_type == kTfLiteBool);

  // Output type must match input type
  TF_LITE_ENSURE_EQ(context, output_type, input_type);

  // This implementation does not support large number of input tensors
  const int num_inputs = NumInputs(node);
  TF_LITE_ENSURE(context, num_inputs <= kMaxInputNum);

  // Shapes with dimensions >4 are not yet supported with static allocation.
  for (int i = 0; i < num_inputs; ++i) {
    //  const TfLiteTensor* input = GetInput(context, node, i);
    TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, i);
    TF_LITE_ENSURE(context, input != nullptr);
    int num_dimensions = NumDimensions(input);

    if (num_dimensions > RuntimeShape::kMaxSmallSize) {
      TF_LITE_KERNEL_LOG(
          context,
          "Op Concatenation does not currently support num dimensions > %d "
          "Tensor has %d dimensions.",
          RuntimeShape::kMaxSmallSize, num_dimensions);
      return kTfLiteError;
    }
    micro_context->DeallocateTempTfLiteTensor(input);
  }

  // Calculate OpData.
  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data = static_cast<OpData*>(node->user_data);

  // TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kOutputTensor);

  TF_LITE_ENSURE(context, output != nullptr);

  switch (output_type) {  // Already know in/outtypes are same.
    case kTfLiteBool:
    case kTfLiteFloat32:
    case kTfLiteInt16:
    case kTfLiteInt32:
    case kTfLiteInt64: {
      data->params.axis = CalculatePositiveAxis(params->axis, output);
      data->params.inputs_count = node->inputs->size;
      break;
    }
    case kTfLiteInt8: {
      data->params.axis = CalculatePositiveAxis(params->axis, output);
      data->params.inputs_count = node->inputs->size;

      float* input_scales =
          reinterpret_cast<float*>(context->AllocatePersistentBuffer(
              context, node->inputs->size * sizeof(float)));

      int32_t* input_zero_points =
          reinterpret_cast<int32_t*>(context->AllocatePersistentBuffer(
              context, node->inputs->size * sizeof(int32_t)));

      // Allocate persistent scale and zeropoint buffers.
      // Store input scale and zero point values in OpParams:
      for (int i = 0; i < node->inputs->size; ++i) {
        // const TfLiteTensor* t = GetInput(context, node, i);
        TfLiteTensor* t = micro_context->AllocateTempInputTensor(node, i);
        TF_LITE_ENSURE(context, t != nullptr);
        input_scales[i] = t->params.scale;
        input_zero_points[i] = t->params.zero_point;
        micro_context->DeallocateTempTfLiteTensor(t);
      }

      data->params.input_scale = input_scales;
      data->params.input_zeropoint = input_zero_points;
      data->params.output_zeropoint = output->params.zero_point;
      data->params.output_scale = output->params.scale;
      break;
    }
    default:
      TF_LITE_KERNEL_LOG(
          context, "Op Concatenation does not currently support Type '%s'.",
          TfLiteTypeGetName(output_type));
      return kTfLiteError;
  }
#if defined(HEMILITE_CONCATENATION_OPT)

  const RuntimeShape* inputs_shape_ptr[kMaxInputNum];
  const float* inputs_data_flt[kMaxInputNum];
  const int8_t* inputs_data_int8[kMaxInputNum];
  int inputs_count = data->params.inputs_count;
  const RuntimeShape& output_shape = GetTensorShape(output);
  int32_t outer_size = 1;
  for (int i = 0; i < data->params.axis; ++i) {
    outer_size *= output_shape.Dims(i);
  }
  data->inputs_count = inputs_count;
  data->outer_size = outer_size;
  data->input_offset = (uint16_t*)context->AllocatePersistentBuffer(
      context, sizeof(uint16_t) * inputs_count * outer_size);
  data->input_size = (uint32_t*)context->AllocatePersistentBuffer(
      context, sizeof(uint32_t) * inputs_count * outer_size);
  data->opt_constraint = 0;
  // const RuntimeShape* input_shape =(const RuntimeShape*)
  // GetTensorShape(input);
  RuntimeShape inputs_shape[kMaxInputNum];
  GetAllInputTensorShapes(context, node, inputs_shape);
  GetShapesPointers(inputs_shape, node->inputs->size, inputs_shape_ptr);
  // const uint8_t* inputs_data[kMaxInputNum];

  switch (output_type) {
    case kTfLiteFloat32:
    case kTfLiteInt32:
      GetAllInputTensorData(context, node, inputs_data_flt);
      reference_ops::Concatenation<float>(
          data->params, inputs_shape_ptr, inputs_data_flt, output_shape,
          (float*)0, data->input_offset, data->input_size);
      data->opt_constraint = 1;
      break;
    case kTfLiteInt8:
      GetAllInputTensorData(context, node, inputs_data_int8);
      reference_ops::Concatenation<int8_t>(
          data->params, inputs_shape_ptr, inputs_data_int8, output_shape,
          (int8_t*)0, data->input_offset, data->input_size);
      data->opt_constraint = 1;
      break;
    case kTfLiteInt64:
    case kTfLiteBool:
    case kTfLiteInt16:
      // GetAllInputTensorData(context, node, inputs_data_int8);
      //  reference_ops::Concatenation<int8_t>(data->params, inputs_shape_ptr,
      //  inputs_data_int8,
      //      output_shape,
      //      (int8_t*)0, data->input_offset, data->input_size);
      break;
    default:
      return kTfLiteError;
  }

  KN_PRINT_Q15_SIZE(data->input_offset, int(inputs_count * outer_size));
  KN_PRINT_Q15_SIZE(data->input_size, int(inputs_count * outer_size));
#endif

  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  // const TfLiteTensor* output_tensor = GetOutput(context, node,
  // kOutputTensor); TF_LITE_ENSURE(context, output_tensor != nullptr); get
  // output from eval saving times
  TfLiteEvalTensor* output_tensor =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  TfLiteType output_type = output_tensor->type;

  switch (output_type) {  // Already know in/outtypes are same.
    case kTfLiteFloat32:
      EvalUnquantized<float>(context, node);
      break;
    case kTfLiteInt32:
      EvalUnquantized<int32_t>(context, node);
      break;
    case kTfLiteUInt8:
      EvalQuantizedUInt8(context, node);
      break;
    case kTfLiteInt8:
      EvalUnquantized<int8_t>(context, node);
      break;
    case kTfLiteInt64:
      EvalUnquantized<int64_t>(context, node);
      break;
    case kTfLiteInt16:
      EvalUnquantized<int16_t>(context, node);
      break;
    case kTfLiteBool:
      EvalUnquantized<bool>(context, node);
      break;

    default:
      TF_LITE_KERNEL_LOG(
          context, "Op Concatenation does not currently support Type '%s'.",
          TfLiteTypeGetName(output_type));
      return kTfLiteError;
  }

  return kTfLiteOk;
}

TfLiteStatus EvalFloat32(TfLiteContext* context, TfLiteNode* node) {
  // const TfLiteTensor* output_tensor = GetOutput(context, node,
  // kOutputTensor); TF_LITE_ENSURE(context, output_tensor != nullptr); get
  // output from eval saving times
  TfLiteEvalTensor* output_tensor =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  TfLiteType output_type = output_tensor->type;
  if (output_type != kTfLiteFloat32) {
    TF_LITE_KERNEL_LOG(context,
                       "Op Concatenation does not currently support Type '%s'.",
                       TfLiteTypeGetName(output_type));
    return kTfLiteError;
  }
  EvalUnquantized<float>(context, node);

  return kTfLiteOk;
}

}  // namespace

TFLMRegistration Register_CONCATENATION() {
  return tflite::micro::RegisterOp(Init,
                                   /*prepare=*/Prepare,
                                   /*invoke=*/Eval);
}

TFLMRegistration Register_CONCATENATION_FLOAT32() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/Prepare,
                                   /*invoke=*/EvalFloat32);
}
//}  // namespace micro
//}  // namespace ops
}  // namespace tflite
