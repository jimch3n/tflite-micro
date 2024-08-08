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

#define USE_HIFI_TIME_DOT   // hybrid mode, fixed point processing 16x16
#define UNALIGNED_OPERATOR  // support that operator's weight cannot convert to
                            // aligned mode
#include "tensorflow/lite/micro/kernels/svdf.h"

#include <cmath>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/kernels/activation_utils.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/xtensa/xtensa.h"
#include "tensorflow/lite/micro/kernels/xtensa/xtensa_svdf.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/xtensa/mvm_helper.h"
//#include "UtilsBasicLib.h"

// for hifi
#include <xtensa/config/core-isa.h>
#include "xtensa/tie/xt_hifi2.h"
#include "xa_nnlib_common_macros.h"
#include "xa_nnlib_hifi_isa_compat.h"
namespace tflite {
namespace {

struct OpData {
  OpDataSvdf SvdfOp;

  int32_t* map_weight_feat;
  AScalar scaleFeat;
  AScalar scaleAct;
  AScalar outputOffset;
  // AScalar *bias; // constant , prepare convert to aflt
  int16_t* weight_time;
  int opt_constraint;
  int32_t* pScratch;
  int32_t* pScratchOutput;
  uint32_t input_offset_int8;
  int32_t* inputOffsetWithW;
  // int32_t input_offset_int8_neg;
};
#if defined(HIFI3) || defined(HIFI4) || defined(HIFI5)
#ifndef USE_HMD_MVM_OPT
TfLiteStatus EvalIntegerSvdfHifi(TfLiteContext* context, TfLiteNode* node,
                                 const TfLiteEvalTensor* input_tensor,
                                 const TfLiteEvalTensor* weights_feature_tensor,
                                 const TfLiteEvalTensor* weights_time_tensor,
                                 const TfLiteEvalTensor* bias_tensor,
                                 const TfLiteSVDFParams* params,
                                 TfLiteEvalTensor* activation_state_tensor,
                                 TfLiteEvalTensor* output_tensor,
                                 const OpDataSvdf& data) {
  const int n_rank = params->rank;
  const int n_batch = input_tensor->dims->data[0];
  const int n_input = input_tensor->dims->data[1];
  const int n_filter = weights_feature_tensor->dims->data[0];
  const int n_unit = n_filter / n_rank;
  const int n_memory = weights_time_tensor->dims->data[1];

  TFLITE_DCHECK(context != nullptr);
  TFLITE_DCHECK(context->GetScratchBuffer != nullptr);

  // Shift states.
  int16_t* const state_ptr =
      tflite::micro::GetTensorData<int16_t>(activation_state_tensor);

  // Left shift the activation_state.
  int num_bytes = sizeof(*state_ptr) * (n_batch * n_filter * n_memory - 1);
#if defined(HIFI5)
  memcpy(state_ptr, state_ptr + 1, num_bytes);
#else
  xa_nn_memmove_16(state_ptr, state_ptr + 1, (num_bytes >> 1));
#endif  // defined(HIFI5)

  // Note: no need to clear the latest activation, matmul is not accumulative.

  // Feature matmul.
  const int8_t* input = tflite::micro::GetTensorData<int8_t>(input_tensor);
  const int8_t* weight_feature =
      tflite::micro::GetTensorData<int8_t>(weights_feature_tensor);
  int16_t* result_in_batch = state_ptr + (n_memory - 1);

  for (int b = 0; b < n_batch; b++) {
    TF_LITE_ENSURE_EQ(context,
                      xa_nn_matXvec_out_stride_sym8sxasym8s_16(
                          &result_in_batch[b * n_filter * n_memory],
                          weight_feature, &input[b * n_input], NULL, n_filter,
                          n_input, n_input, n_memory, -data.input_zero_point,
                          (data.effective_scale_1_a), data.effective_scale_1_b),
                      0);
  }

  // Time weights dot product + activation
  for (int b = 0; b < n_batch; ++b) {
    const int16_t* vector1_ptr =
        tflite::micro::GetTensorData<int16_t>(weights_time_tensor);
    const int16_t* vector2_ptr =
        tflite::micro::GetTensorData<int16_t>(activation_state_tensor) +
        b * n_memory * n_filter;
    // TODO(#1751): account for optional bias tensor
    const int32_t* bias_ptr =
        tflite::micro::GetTensorData<int32_t>(bias_tensor);
    int8_t* output_ptr =
        tflite::micro::GetTensorData<int8_t>(output_tensor) + b * n_unit;

    // TODO(#1751): account for optional bias tensor
    TF_LITE_ENSURE_EQ(
        context,
        xa_nn_dot_prod_16x16_asym8s(
            output_ptr, vector1_ptr, vector2_ptr, bias_ptr, n_memory * n_rank,
            (data.effective_scale_2_a), data.effective_scale_2_b,
            data.output_zero_point, n_unit),
        0);
  }
  return kTfLiteOk;
}
#endif
#endif  // defined(HIFI3) || defined(HIFI4) || defined(HIFI5)
#ifndef USE_HMD_MVM_OPT
void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpDataSvdf));
}
#else
void* InitHmd(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}
#endif
#ifndef USE_HMD_MVM_OPT
TfLiteStatus PrepareInt8(TfLiteContext* context, TfLiteNode* node) {
#if defined(HIFIMINI) || defined(HIFI3) || defined(HIFI4) || defined(HIFI5)
  TFLITE_DCHECK(node->builtin_data != nullptr);
  const auto* params = static_cast<const TfLiteSVDFParams*>(node->builtin_data);

  // Validate Tensor Inputs (dtype depends on quantization):
  // [0] = Input, {2, batch_size, input_size}
  // [1] = Weights Feature, {2, num_filters, input_size}
  // [2] = Weights Time, {2, num_filters, memory_size}
  // [3] = Bias (optional), {1, num_units}
  // [4] = Activation State (variable),
  //         {2, batch_size, memory_size * num_filters}
  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kSvdfInputTensor);
  TfLiteTensor* weights_feature =
      micro_context->AllocateTempInputTensor(node, kSvdfWeightsFeatureTensor);
  TfLiteTensor* weights_time =
      micro_context->AllocateTempInputTensor(node, kSvdfWeightsTimeTensor);
  TfLiteTensor* bias =
      micro_context->AllocateTempInputTensor(node, kSvdfBiasTensor);
  TfLiteTensor* activation_state = micro_context->AllocateTempInputTensor(
      node, kSvdfInputActivationStateTensor);

  // Define input constants based on input tensor definition above:
  const int rank = params->rank;
  const int input_size = input->dims->data[1];
  const int batch_size = input->dims->data[0];

#if defined(HIFIMINI)
  // Ensure the input size is a multiple of two.  This is necessary since
  // optimized kernels access the memory in chunks of two, and all accesses
  // must be aligned to 16 bits.
  // TODO(b/153202598): Remove when padding is allowed in TFLite tensors.
  TF_LITE_ENSURE_EQ(context, input_size % 2, 0);
#endif  // defined(HIFIMINI)

  const int num_filters = weights_feature->dims->data[0];
  TF_LITE_ENSURE_EQ(context, num_filters % rank, 0);
  const int num_units = num_filters / rank;
  const int memory_size = weights_time->dims->data[1];

  // Validate Input Tensor:
  TF_LITE_ENSURE(context, input->type == kTfLiteInt8);
  TF_LITE_ENSURE_EQ(context, NumDimensions(input), 2);

  // Validate Tensor Output:
  // [0] = float/int8_t, {2, batch_size, num_units}
  TF_LITE_ENSURE_EQ(context, node->outputs->size, 1);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kSvdfOutputTensor);
  TF_LITE_ENSURE_EQ(context, NumDimensions(output), 2);
  TF_LITE_ENSURE_EQ(context, output->dims->data[0], batch_size);
  TF_LITE_ENSURE_EQ(context, output->dims->data[1], num_units);

  // Validate Weights Feature Input Tensor:
  TF_LITE_ENSURE_EQ(context, NumDimensions(weights_feature), 2);
  TF_LITE_ENSURE_EQ(context, weights_feature->dims->data[1], input_size);

  // Validate Weights Time Input Tensor:
  TF_LITE_ENSURE_EQ(context, NumDimensions(weights_time), 2);
  TF_LITE_ENSURE_EQ(context, weights_time->dims->data[0], num_filters);
  TF_LITE_ENSURE_EQ(context, weights_time->dims->data[1], memory_size);

  // Validate Optional Bias Input Tensor:
  if (bias != nullptr) {
    TF_LITE_ENSURE_EQ(context, bias->dims->data[0], num_units);
    TF_LITE_ENSURE_EQ(context, bias->type, kTfLiteInt32);
  }

  // Validate Activation State Input Tensor:
  TF_LITE_ENSURE_EQ(context, NumDimensions(activation_state), 2);
  TF_LITE_ENSURE_EQ(context, activation_state->dims->data[0], batch_size);
  TF_LITE_ENSURE_EQ(context, activation_state->dims->data[1],
                    memory_size * num_filters);

  TF_LITE_ENSURE_EQ(context, node->inputs->size, 5);
  TF_LITE_ENSURE_EQ(context, weights_feature->type, kTfLiteInt8);
  TF_LITE_ENSURE_EQ(context, weights_time->type, kTfLiteInt16);
  TF_LITE_ENSURE_EQ(context, activation_state->type, kTfLiteInt16);

  // Validate output tensor:
  TF_LITE_ENSURE_TYPES_EQ(context, output->type, kTfLiteInt8);

  const double effective_scale_1 =
      static_cast<double>(input->params.scale * weights_feature->params.scale /
                          activation_state->params.scale);
  const double effective_scale_2 =
      static_cast<double>(activation_state->params.scale *
                          weights_time->params.scale / output->params.scale);

  // TODO(#1751): account for optional bias tensor
  TF_LITE_ENSURE_NEAR(context, static_cast<double>(bias->params.scale),
                      static_cast<double>(activation_state->params.scale *
                                          weights_time->params.scale),
                      1e-5);

  TFLITE_DCHECK(node->user_data != nullptr);
  OpDataSvdf* data = static_cast<OpDataSvdf*>(node->user_data);

#if defined(HIFIMINI)
  QuantizeMultiplierForInt24(effective_scale_1, &data->effective_scale_1_a,
                             &data->effective_scale_1_b);
  QuantizeMultiplierForInt24(effective_scale_2, &data->effective_scale_2_a,
                             &data->effective_scale_2_b);
#else
  QuantizeMultiplier(effective_scale_1, &(data->effective_scale_1_a),
                     &(data->effective_scale_1_b));
  QuantizeMultiplier(effective_scale_2, &(data->effective_scale_2_a),
                     &(data->effective_scale_2_b));
#endif  // defined(HIFIMINI)

  data->input_zero_point = input->params.zero_point;
  data->output_zero_point = output->params.zero_point;

  const TfLiteStatus scratch_status = context->RequestScratchBufferInArena(
      context, batch_size * num_filters * sizeof(int32_t),
      &(data->scratch_tensor_index));
  TF_LITE_ENSURE_OK(context, scratch_status);
  const TfLiteStatus scratch_output_status =
      context->RequestScratchBufferInArena(
          context, batch_size * num_units * sizeof(int32_t),
          &(data->scratch_output_tensor_index));
  TF_LITE_ENSURE_OK(context, scratch_output_status);

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(weights_time);
  micro_context->DeallocateTempTfLiteTensor(weights_feature);
  if (bias != nullptr) {
    micro_context->DeallocateTempTfLiteTensor(bias);
  }
  micro_context->DeallocateTempTfLiteTensor(activation_state);
  micro_context->DeallocateTempTfLiteTensor(output);

  return kTfLiteOk;
#else
  return PrepareSvdf(context, node);
#endif  // defined(HIFIMINI) || defined(HIFI3) || defined(HIFI4) ||
        // defined(HIFI5)
}

TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
#if defined(HIFIMINI) || defined(HIFI3) || defined(HIFI4) || defined(HIFI5)

  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kSvdfInputTensor);
  TfLiteTensor* weights_time =
      micro_context->AllocateTempInputTensor(node, kSvdfWeightsTimeTensor);

  TfLiteStatus status;
  if (input->type == kTfLiteInt8 && weights_time->type == kTfLiteInt16) {
    status = PrepareInt8(context, node);
  } else {
    status = PrepareSvdf(context, node);
  }

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(weights_time);

  return status;
#else
  return PrepareSvdf(context, node);
#endif  // defined(HIFIMINI) || defined(HIFI3) || defined(HIFI4) ||
        // defined(HIFI5)
}

TfLiteStatus EvalInt8(TfLiteContext* context, TfLiteNode* node) {
  auto* params = static_cast<TfLiteSVDFParams*>(node->builtin_data);

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kSvdfInputTensor);
  const TfLiteEvalTensor* weights_feature =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsFeatureTensor);
  const TfLiteEvalTensor* weights_time =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsTimeTensor);
  // TODO(#1751): account for optional bias tensor
  const TfLiteEvalTensor* bias =
      (NumInputs(node) == 5)
          ? tflite::micro::GetEvalInput(context, node, kSvdfBiasTensor)
          : nullptr;
  TfLiteEvalTensor* activation_state = tflite::micro::GetMutableEvalInput(
      context, node, kSvdfInputActivationStateTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kSvdfOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpDataSvdf& data = *(static_cast<const OpDataSvdf*>(node->user_data));

#if defined(HIFIMINI)
  return EvalIntegerSvdfHifimini(context, node, input, weights_feature,
                                 weights_time, bias, params, activation_state,
                                 output, data);
#elif defined(HIFI3) || defined(HIFI4) || defined(HIFI5)
  TfLiteStatus status =
      EvalIntegerSvdfHifi(context, node, input, weights_feature, weights_time,
                          bias, params, activation_state, output, data);

  KN_PRINT_Q7_SIZE(output->data.int8, ElementCount(*output->dims));
  return status;
#else
  EvalInt16SvdfReference(context, node, input, weights_feature, weights_time,
                         bias, params, activation_state, output, data);

  // KN_PRINT_Q7_SIZE(output->data.int8, ElementCount(*output->dims));
  return kTfLiteOk;
#endif  // defined(HIFI3) || defined(HIFI4) || defined(HIFI5)
}
#endif
#ifndef USE_HMD_MVM_OPT
TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  auto* params = static_cast<TfLiteSVDFParams*>(node->builtin_data);

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kSvdfInputTensor);
  const TfLiteEvalTensor* weights_feature =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsFeatureTensor);
  const TfLiteEvalTensor* weights_time =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsTimeTensor);
  // TODO(#1751): account for optional bias tensor
  const TfLiteEvalTensor* bias =
      (NumInputs(node) == 5)
          ? tflite::micro::GetEvalInput(context, node, kSvdfBiasTensor)
          : nullptr;
  TfLiteEvalTensor* activation_state = tflite::micro::GetMutableEvalInput(
      context, node, kSvdfInputActivationStateTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kSvdfOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpDataSvdf& data = *(static_cast<const OpDataSvdf*>(node->user_data));

  switch (weights_feature->type) {
    case kTfLiteFloat32: {
      EvalFloatSvdfReference(
          context, node, input, weights_feature, weights_time, bias, params,
          data.scratch_tensor_index, activation_state, output);
      break;
    }

    case kTfLiteInt8: {
      switch (weights_time->type) {
        case kTfLiteInt16: {
          return EvalInt8(context, node);
        }

        case kTfLiteInt8: {
          EvalInt8SvdfReference(context, node, input, weights_feature,
                                weights_time, bias, params, activation_state,
                                output, data);
          break;
        }

        default: {
          MicroPrintf("Type %s not currently supported.",
                      TfLiteTypeGetName(weights_time->type));
          return kTfLiteError;
        }
      }
      break;
    }

    default: {
      MicroPrintf("Type %s not currently supported.",
                  TfLiteTypeGetName(weights_feature->type));
      return kTfLiteError;
    }
  }

  return kTfLiteOk;
}
#else

TfLiteStatus PrepareHmdInt8(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->builtin_data != nullptr);
  bool use_internal_persist_weight = false;
  const auto* params = static_cast<const TfLiteSVDFParams*>(node->builtin_data);

  MicroContext* micro_context = GetMicroContext(context);

  // Validate Tensor Inputs (dtype depends on quantization):
  // [0] = Input, {2, batch_size, input_size}
  // [1] = Weights Feature, {2, num_filters, input_size}
  // [2] = Weights Time, {2, num_filters, memory_size}
  // [3] = Bias (optional), {1, num_units}
  // [4] = Activation State (variable),
  //         {2, batch_size, memory_size * num_filters}
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kSvdfInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor* weights_feature =
      micro_context->AllocateTempInputTensor(node, kSvdfWeightsFeatureTensor);
  TF_LITE_ENSURE(context, weights_feature != nullptr);
  TfLiteTensor* weights_time =
      micro_context->AllocateTempInputTensor(node, kSvdfWeightsTimeTensor);
  TF_LITE_ENSURE(context, weights_time != nullptr);
  TfLiteTensor* bias =
      micro_context->AllocateTempInputTensor(node, kSvdfBiasTensor);
  TfLiteTensor* activation_state = micro_context->AllocateTempInputTensor(
      node, kSvdfInputActivationStateTensor);
  TF_LITE_ENSURE(context, activation_state != nullptr);

  // Define input constants based on input tensor definition above:
  const int rank = params->rank;
  const int input_size = input->dims->data[1];
  const int batch_size = input->dims->data[0];
  const int num_filters = weights_feature->dims->data[0];
  TF_LITE_ENSURE_EQ(context, num_filters % rank, 0);
  const int num_units = num_filters / rank;
  const int memory_size = weights_time->dims->data[1];

  // Validate Input Tensor:
  TF_LITE_ENSURE(context,
                 input->type == kTfLiteFloat32 || input->type == kTfLiteInt8);
  TF_LITE_ENSURE_EQ(context, NumDimensions(input), 2);

  // Validate Tensor Output:
  // [0] = float/int8, {2, batch_size, num_units}
  TF_LITE_ENSURE_EQ(context, node->outputs->size, 1);
  TfLiteTensor* output =
      micro_context->AllocateTempOutputTensor(node, kSvdfOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);
  TF_LITE_ENSURE_EQ(context, NumDimensions(output), 2);
  TF_LITE_ENSURE_EQ(context, output->dims->data[0], batch_size);
  TF_LITE_ENSURE_EQ(context, output->dims->data[1], num_units);

  // Validate Weights Feature Input Tensor:
  TF_LITE_ENSURE_EQ(context, NumDimensions(weights_feature), 2);
  TF_LITE_ENSURE_EQ(context, weights_feature->dims->data[1], input_size);

  // Validate Weights Time Input Tensor:
  TF_LITE_ENSURE_EQ(context, NumDimensions(weights_time), 2);
  TF_LITE_ENSURE_EQ(context, weights_time->dims->data[0], num_filters);
  TF_LITE_ENSURE_EQ(context, weights_time->dims->data[1], memory_size);

  // Validate Optional Bias Input Tensor:
  if (bias != nullptr) {
    TF_LITE_ENSURE_EQ(context, bias->dims->data[0], num_units);
  }

  // Validate Activation State Input Tensor:
  TF_LITE_ENSURE_EQ(context, NumDimensions(activation_state), 2);
  TF_LITE_ENSURE_EQ(context, activation_state->dims->data[0], batch_size);
  TF_LITE_ENSURE_EQ(context, activation_state->dims->data[1],
                    memory_size * num_filters);
  // Since is_variable is not part of TFLiteEvalTensor, check is_variable here.
  TF_LITE_ENSURE_EQ(context, activation_state->is_variable, true);

  TF_LITE_ENSURE_EQ(context, node->inputs->size, 5);

  TFLITE_DCHECK(node->user_data != nullptr);
  OpData* data_ex = static_cast<OpData*>(node->user_data);

  OpDataSvdf* data = static_cast<OpDataSvdf*>(&data_ex->SvdfOp);
  if (input->type == kTfLiteInt8) {
    TF_LITE_ENSURE_EQ(context, weights_feature->type, kTfLiteInt8);
    TF_LITE_ENSURE(context, (weights_time->type == kTfLiteInt16) ||
                                (weights_time->type == kTfLiteInt8));
    TF_LITE_ENSURE(context, (activation_state->type == kTfLiteInt16) ||
                                (activation_state->type == kTfLiteInt8));
    if (bias != nullptr) {
      TF_LITE_ENSURE_EQ(context, bias->type, kTfLiteInt32);
    }

    TF_LITE_ENSURE_TYPES_EQ(context, output->type, kTfLiteInt8);

    const double effective_scale_1 = static_cast<double>(
        input->params.scale * weights_feature->params.scale /
        activation_state->params.scale);
    const double effective_scale_2 =
        static_cast<double>(activation_state->params.scale *
                            weights_time->params.scale / output->params.scale);

    // TODO(b/162018098): Use TF_LITE_ENSURE_NEAR when it is ready.
    TF_LITE_ENSURE(
        context,
        std::abs(static_cast<double>(bias->params.scale) -
                 static_cast<double>(activation_state->params.scale *
                                     weights_time->params.scale)) < 1e-5);

    QuantizeMultiplier(effective_scale_1, &(data->effective_scale_1_a),
                       &(data->effective_scale_1_b));
    QuantizeMultiplier(effective_scale_2, &(data->effective_scale_2_a),
                       &(data->effective_scale_2_b));

    data->input_zero_point = input->params.zero_point;
    data->output_zero_point = output->params.zero_point;
    data->activation_state_zero_point = activation_state->params.zero_point;

    TFLITE_DCHECK(context->RequestScratchBufferInArena != nullptr);
    // REMOVED?
    const TfLiteStatus scratch_status = context->RequestScratchBufferInArena(
        context, batch_size * num_filters * sizeof(int32_t),
        &(data->scratch_tensor_index));
    TF_LITE_ENSURE_OK(context, scratch_status);

    const TfLiteStatus scratch_output_status =
        context->RequestScratchBufferInArena(
            context, batch_size * num_units * sizeof(int32_t),
            &(data->scratch_output_tensor_index));

    KN_PRINTD(batch_size);
    KN_PRINTD(num_units);
    KN_PRINTD(rank);
    KN_PRINTD(input_size);
    KN_PRINTD(num_filters);
    TF_LITE_ENSURE_OK(context, scratch_output_status);

#if 0  //!(defined(DMX1A_SVDF_OPT) || defined(HMD1A_SVDF_OPT))
    data_ex->opt_constraint = 0;
    // check able to optimized  input as multiple of 8 ~ 64
    //   int input_length = input->dims->data[0];
#else
    data_ex->opt_constraint =
        input->type == kTfLiteInt8 &&
        weights_time->type == kTfLiteInt16;  //  weight time ttype must 16 only

#ifdef UNALIGNED_OPERATOR
    if ((num_filters & ((1 << LOG2_ROWS_PER_GROUP) - 1)) != 0 ||
        (input_size & ((1 << LOG2_COLS_PER_BLOCK) - 1)) != 0) {
      KN_PRINTD(num_filters);
      KN_PRINTD(input_size);
      use_internal_persist_weight = true;
    }

#endif

    KN_PRINTD(use_internal_persist_weight);
    // if(data_ex->opt_constraint)
    {
      // data_ex->opt_constraint;

      if (data_ex->opt_constraint) {
        int32_t* p_dmx1a_fc_mapped_filter = nullptr;

        const TfLiteEvalTensor* filterEval = tflite::micro::GetEvalInput(
            context, node, kSvdfWeightsFeatureTensor);
        const int8_t* filter_input =
            tflite::micro::GetTensorData<int8_t>(filterEval);
        const int32_t map_coeff_size = tflite::FullyConnectedMap8bitCoeffs(
            NULL, NULL, num_filters, input_size);

        KN_PRINTD(map_coeff_size);
#ifdef KERNEL_COEFF_MAP_ENABLE
        if (true)
#else
        if (use_internal_persist_weight)
#endif
        {
          KN_PRINTD(map_coeff_size);
          p_dmx1a_fc_mapped_filter =
              (int32_t*)context->AllocatePersistentBuffer(context,
                                                          map_coeff_size);
          if (p_dmx1a_fc_mapped_filter) {
            tflite::FullyConnectedMap8bitCoeffs(
                (int8_t*)p_dmx1a_fc_mapped_filter, (int8_t*)filter_input,
                num_filters, input_size);
          }
          KN_PRINT_Q7_SIZE_ATMOST(p_dmx1a_fc_mapped_filter, map_coeff_size, 64);
        } else {
          p_dmx1a_fc_mapped_filter = (int32_t*)filter_input;  // remapping
          KN_PRINT_Q7_SIZE_ATMOST(p_dmx1a_fc_mapped_filter, map_coeff_size, 64);
        }
        // KN_PRINTX(data->activation_state_zero_point);
        data_ex->map_weight_feat = (int32_t*)p_dmx1a_fc_mapped_filter;
        // const TfLiteEvalTensor* biasEval =
        // tflite::micro::GetEvalInput(context, node, kSvdfBiasTensor);
        // const int32_t
        //*bias_input =  tflite::micro::GetTensorData<int32_t>(biasEval);
        //
        // tflite::ConvertQ31ToAfloat(bias_input,(AScalar*) bias_input, , 17);
        tflite::ConvertQ31ToAfloat(data->effective_scale_1_a,
                                   data_ex->scaleFeat,
                                   data->effective_scale_1_b);
        tflite::ConvertQ31ToAfloat(data->effective_scale_2_a, data_ex->scaleAct,
                                   data->effective_scale_2_b + 16);
        KN_PRINTAFLT(data_ex->scaleFeat);
        KN_PRINTAFLT(data_ex->scaleAct);
        uint8_t offsetInput = -(data->input_zero_point & 0xff);
        KN_PRINTD(data->input_zero_point);
        // uint32_t offsetVR=offsetInput;
        data_ex->input_offset_int8 = (offsetInput << 24) | (offsetInput << 16) |
                                     (offsetInput << 8) | offsetInput;
        //			offsetInput = ( data->input_zero_point&0xff);
        //				data->input_offset_int8_neg =
        //(offsetInput<<24)|(offsetInput<<16)|(offsetInput<<8)|offsetInput;
        KN_PRINTX(data_ex->input_offset_int8);
        tflite::ConvertQ31ToAfloat(data->output_zero_point,
                                   data_ex->outputOffset, 17);
        KN_PRINTAFLT(data_ex->outputOffset);

        if (data_ex->input_offset_int8 == 0x80808080 ||
            data_ex->input_offset_int8 == 0x0) {
          data_ex->opt_constraint = 2;  // faster without input offset
          data_ex->inputOffsetWithW = nullptr;

        } else {
          int inFCMA8 = (((num_filters + 7) >> 3) << 3);
          int32_t* inputOffsetWithW =
              (int32_t*)context->AllocatePersistentBuffer(
                  context, inFCMA8 * sizeof(int32_t));
          data_ex->inputOffsetWithW = inputOffsetWithW;
          // KN_PRINTD( inFCMA8);
          MVMInputOffsetPrepare(data_ex->map_weight_feat, inputOffsetWithW,
                                num_filters, input_size,
                                data_ex->input_offset_int8);
          // KN_PRINT_Q31_SIZE(data_ex->inputOffsetWithW, inFCMA8);
        }
        KN_PRINTD(data_ex->opt_constraint);
      }
    }
#endif
  } else {
    TF_LITE_ENSURE_EQ(context, weights_feature->type, kTfLiteFloat32);
    TF_LITE_ENSURE_EQ(context, weights_time->type, kTfLiteFloat32);
    TF_LITE_ENSURE_EQ(context, activation_state->type, kTfLiteFloat32);
    if (bias != nullptr) {
      TF_LITE_ENSURE_EQ(context, bias->type, kTfLiteFloat32);
    }
    TF_LITE_ENSURE_TYPES_EQ(context, output->type, kTfLiteFloat32);

    TFLITE_DCHECK(context->RequestScratchBufferInArena != nullptr);
    const TfLiteStatus scratch_status = context->RequestScratchBufferInArena(
        context, batch_size * num_filters * sizeof(float),
        &(data->scratch_tensor_index));
    TF_LITE_ENSURE_OK(context, scratch_status);
  }
  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(weights_feature);
  micro_context->DeallocateTempTfLiteTensor(weights_time);
  micro_context->DeallocateTempTfLiteTensor(activation_state);
  micro_context->DeallocateTempTfLiteTensor(output);
  // TODO(#1751): account for optional bias tensor
  micro_context->DeallocateTempTfLiteTensor(bias);

  return kTfLiteOk;
}

TfLiteStatus PrepareHmd(TfLiteContext* context, TfLiteNode* node) {
#if defined(HIFIMINI) || defined(HIFI3) || defined(HIFI4) || defined(HIFI5)

  MicroContext* micro_context = GetMicroContext(context);
  TfLiteTensor* input =
      micro_context->AllocateTempInputTensor(node, kSvdfInputTensor);
  TfLiteTensor* weights_time =
      micro_context->AllocateTempInputTensor(node, kSvdfWeightsTimeTensor);

  TfLiteStatus status;
  if (input->type == kTfLiteInt8 && weights_time->type == kTfLiteInt16) {
    status = PrepareHmdInt8(context, node);
  } else {
    status = PrepareSvdf(context, node);
  }

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(weights_time);

  return status;
#else
  return PrepareSvdf(context, node);
#endif  // defined(HIFIMINI) || defined(HIFI3) || defined(HIFI4) ||
        // defined(HIFI5)
}

int SVDFFeatMatInt8InputOffset(int32_t* x, const int32_t* A,

                               int32_t* inputOffsetWithW, int16_t* output,
                               int n_filter, int n_input, int n_memory,
                               // const AScalar& outMultiplerFr32,
                               int signs, int b_shift, int32_t out_multiplier,
                               int out_shift) {
  int16_t* pY = (int16_t*)output;  // act
  int m = n_filter;
  int n = n_input;
  const int32_t* pA = A;
  const int32_t* pX;
  // const int32_t *pB = (  const int32_t *)bias;
  // int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2),
  // 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 8
  int loopLimRow = ((m + 3) >> 2);         // group 4 alignment
  int processLastLoop = ((m & 3) != 0);

  int out_stride_by_2 = n_memory << 1;
  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x2_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    KN_PRINTS("ERROR!\n");
    return -1;
  }

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;

  atbool signSpec = (atbool)signs;

  int left_shift, right_shift;
  left_shift = out_shift < 0 ? 0 : out_shift;
  right_shift = out_shift > 0 ? 0 : -out_shift;
  const int32_t* inputOffsetW = inputOffsetWithW;

  KN_PRINTD(loopLimRow);
  KN_PRINTD(loopLimCol);

  for (int i = 0; i < loopLimRow; i++) {
    if (inputOffsetWithW) {
      load32x2_vr_postI(VR_y, inputOffsetW, INC1);
      load32x2_vr_postI(VR_x, inputOffsetW, INC1);
      mov_AccExtend_vr(VR_x);
    } else {
      VR_y = vseta_vr(0, 0);
      mov_AccExtend_vr(VR_y);
    }

    pX = x;
    ulsr32 UR_A = align_32x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    load_32x2_vr_a(VR_A, UR_A, pA);
    // KN_PRINTX_VR64(VR_A);
    for (int j = 0; j < loopLimCol; j++) {
      load_32x2_vr_a(VR_x, UR_x, pX);  // KN_PRINTX_VR64(VR_x);
      WUR_MvmAux(0);
      // KN_PRINTX_VR64(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
      // KN_PRINTX_VR64(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 2); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      //   KN_PRINTX_VR128(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }
    // KN_PRINTX_VR64(VR_y);

    VR_y = shift32_arith(VR_y, -b_shift, 0);

    ae_int32x2 ae_in =
        AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));

    ae_int32x2 ae_out0 = AE_SLAA32S(ae_in, left_shift);
    ae_out0 = AE_MULFP32X2RAS(ae_out0, AE_MOVDA32(out_multiplier));
    ae_out0 =
        AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out0), right_shift),
                            AE_SRAA64(AE_CVT64F32_L(ae_out0), right_shift));

    VR_y = mov_vr_AccExtend();
    VR_y = shift32_arith(VR_y, -b_shift, 0);
    ae_in = AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));
    // KN_PRINTX_AE32X2(ae_in);
    ae_int32x2 ae_out1 = AE_SLAA32S(ae_in, left_shift);
    ae_out1 = AE_MULFP32X2RAS(ae_out1, AE_MOVDA32(out_multiplier));
    ae_out1 =
        AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out1), right_shift),
                            AE_SRAA64(AE_CVT64F32_L(ae_out1), right_shift));

    ae_int16x4 out16_0 = AE_SAT16X4(ae_out1, ae_out0);
    if (i != (loopLimRow - 1) || !processLastLoop) {
      //
      // KN_PRINTX_AE32X2(AE_SEL16_5432(out16_0, out16_0));
      // KN_PRINTX_AE32X2(AE_SEL16_6543(out16_0, out16_0));
      // KN_PRINTX_AE32X2(AE_SEL16_4321(out16_0, out16_0));
      AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
      AE_S16_0_XP(AE_SEL16_4321(out16_0, out16_0), (ae_int16*)pY,
                  out_stride_by_2);
      AE_S16_0_XP(AE_SEL16_5432(out16_0, out16_0), (ae_int16*)pY,
                  out_stride_by_2);
      AE_S16_0_XP(AE_SEL16_6543(out16_0, out16_0), (ae_int16*)pY,
                  out_stride_by_2);

    } else {
      switch (m & 3) {
        case 3:
          AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
          AE_S16_0_XP(AE_SEL16_4321(out16_0, out16_0), (ae_int16*)pY,
                      out_stride_by_2);
          AE_S16_0_XP(AE_SEL16_5432(out16_0, out16_0), (ae_int16*)pY,
                      out_stride_by_2);
          break;
        case 2:
          AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
          AE_S16_0_XP(AE_SEL16_4321(out16_0, out16_0), (ae_int16*)pY,
                      out_stride_by_2);
          break;

        case 1:
          AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

int SVDFFeatMatInt8(int32_t* x, const int32_t* A, int16_t* output, int n_filter,
                    int n_input, int n_memory,
                    const uint32_t input_offset_int8x4, int signs, int b_shift,
                    int32_t out_multiplier, int out_shift) {
  int16_t* pY = (int16_t*)output;  // act
  int m = n_filter;
  int n = n_input;
  const int32_t* pA = A;
  const int32_t* pX;
  // const int32_t *pB = (  const int32_t *)bias;
  // int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2),
  // 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 8
  int loopLimRow = ((m + 3) >> 2);         // group 4 alignment
  int processLastLoop = ((m & 3) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x2_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  int out_stride_by_2 = n_memory << 1;

  if (((unsigned int)x & 1) != 0) {
    KN_PRINTX(x);
    KN_PRINTS("ERROR!!!!\n");
    return -1;
  }
  KN_PRINTX(out_multiplier);
  KN_PRINTX(out_shift);
  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  // vr64 VR_round, VR_nround;
  atbool signSpec = (atbool)signs;

  int left_shift, right_shift;
  left_shift = out_shift < 0 ? 0 : out_shift;
  right_shift = out_shift > 0 ? 0 : -out_shift;

  // vr64 VR_outMult;
  vr64 VR_inputOffset;
  // replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  replicate_ar(VR_inputOffset, 0x3, input_offset_int8x4);

  // replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  for (int i = 0; i < loopLimRow; i++) {
    VR_y = vseta_vr(0, 0);
    mov_AccExtend_vr(VR_y);
    pX = x;
    ulsr32 UR_A = align_32x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    // ulsr128 UR_b = align_32x4_load(pB);
    load_32x2_vr_a(VR_A, UR_A, pA);

    // vr128 VR_b0, VR_b1;
    // load_32x4_vr_a(VR_b0, UR_b, pB); // suppose not grate than 16 bit

    for (int j = 0; j < loopLimCol; j++) {
      load_32x2_vr_a(VR_x, UR_x, pX);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(0);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 2); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      KN_PRINTX_VR64(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    KN_PRINTX_VR64(VR_y);
    VR_y = shift32_arith(VR_y, -b_shift, 0);
    if (1) {
      KN_PRINTX_VR64(VR_y);
    }
    ae_int32x2 ae_in =
        AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));
    if (1) {
      KN_PRINTX_AE32X2(ae_in);
    }
    ae_int32x2 ae_out0 = AE_SLAA32S(ae_in, left_shift);
    ae_out0 = AE_MULFP32X2RAS(ae_out0, AE_MOVDA32(out_multiplier));
    ae_out0 =
        AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out0), right_shift),
                            AE_SRAA64(AE_CVT64F32_L(ae_out0), right_shift));
    KN_PRINTX_AE32X2(ae_out0);
    VR_y = mov_vr_AccExtend();
    VR_y = shift32_arith(VR_y, -b_shift, 0);
    ae_in = AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));
    KN_PRINTX_AE32X2(ae_in);
    ae_int32x2 ae_out1 = AE_SLAA32S(ae_in, left_shift);
    ae_out1 = AE_MULFP32X2RAS(ae_out1, AE_MOVDA32(out_multiplier));
    ae_out1 =
        AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out1), right_shift),
                            AE_SRAA64(AE_CVT64F32_L(ae_out1), right_shift));
    KN_PRINTX_AE32X2(ae_out1);
    ae_int16x4 out16_0 = AE_SAT16X4(ae_out1, ae_out0);

    KN_PRINTX_AE16X4(out16_0);
    if (i != (loopLimRow - 1) || !processLastLoop) {
      AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
      AE_S16_0_XP(AE_SEL16_4321(out16_0, out16_0), (ae_int16*)pY,
                  out_stride_by_2);
      AE_S16_0_XP(AE_SEL16_5432(out16_0, out16_0), (ae_int16*)pY,
                  out_stride_by_2);
      AE_S16_0_XP(AE_SEL16_6543(out16_0, out16_0), (ae_int16*)pY,
                  out_stride_by_2);

    } else {
      switch (m & 3) {
        case 3:

          AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
          AE_S16_0_XP(AE_SEL16_4321(out16_0, out16_0), (ae_int16*)pY,
                      out_stride_by_2);
          AE_S16_0_XP(AE_SEL16_5432(out16_0, out16_0), (ae_int16*)pY,
                      out_stride_by_2);
          break;
        case 2:

          AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
          AE_S16_0_XP(AE_SEL16_4321(out16_0, out16_0), (ae_int16*)pY,
                      out_stride_by_2);
          break;
        case 1:

          AE_S16_0_XP(out16_0, (ae_int16*)pY, out_stride_by_2);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}
#ifndef USE_HIFI_TIME_DOT
// BatchVectorBatchVectorDotProduct
void SVDFTimeInt16(OpData* data, const int16_t* weight_time,
                   const int16_t* activation_state, int feature_batch,
                   int time_batches, int32_t* output) {
  int loopLim = time_batches >> 1;
  vr64 vr_weight, vr_state;
  vr64 vr_sum;  //, vr_out;//, vr_bias;
  const int16_t* pWeight = weight_time;
  const int16_t* pState = activation_state;
  //   const AScalar *pBias = bias;
  // ulsr128 UR_w, UR_state;

  for (int ii = 0; ii < feature_batch; ii++) {
    // UR_w = align_16x4_load(pWeight);
    // UR_state = align_16x4_load(pState);

    // convert to 32F from 16I is faster,
    load16x2_vr_postI(vr_weight, pWeight, INC1);
    load16x2_vr_postI(vr_state, pState, INC1);
    vr_sum = vseta_vr(kConstTable_Zero, 0);
    for (int j = 0; j < loopLim - 1; j++) {
      convert_16I_to_32F_x2(vr_weight, 0);
      convert_16I_to_32F_x2(vr_state, 0);
      vr_sum = vmacs(vr_sum, vr_weight, vr_state, 0, 0);
      //  sum += *v1 * *v2;
      load16x2_vr_postI(vr_weight, pWeight, INC1);
      load16x2_vr_postI(vr_state, pState, INC1);
    }

    convert_16I_to_32F_x2(vr_weight, 0);
    convert_16I_to_32F_x2(vr_state, 0);

    vr_sum = vmacs(vr_sum, vr_weight, vr_state, 0, 0);

    fr32 fr_out = get_VRL(vr_sum);
    if (time_batches & 1) {
      // for(int jj = 0; jj < (time_batches&3); jj++)
      // {
      load16x1_vr_postI(vr_weight, pWeight, INC1, VRQ0);
      load16x1_vr_postI(vr_state, pState, INC1, VRQ0);

      convert_16I_to_32F_x1(vr_weight, 0, VRQ0);
      convert_16I_to_32F_x1(vr_state, 0, VRQ0);

      // fmacs(vr_sum, VRQ0, vr_weight, VRQ0, vr_state, VRQ0, 0);
      fr_out = fmac(fr_out, get_VRL(vr_weight), get_VRL(vr_state));
      // vr_weight = vpermsi(vr_weight, vr_weight, 0, SHR_BY_1_ELEM);
      // vr_state = vpermsi(vr_state, vr_state, 0, SHR_BY_1_ELEM);
      // }
    }
    // dsums_L(vr_sum, vr_sum, 0, 0);
    fr_out = fadds(fr_out, get_VRH(vr_sum), 0);
    // convert to fix-point ?
    // store32x1_vr_postI(vr_out, output, INC1, VRQ0);
    // KN_PRINTAFLT(fr_out);
    st_FR_postI(fr_out, output, 4);
  }
}

#else
void SVDFTimeInt16HifiAddBias(OpData* data, const int16_t* weight_time,
                              const int16_t* activation_state,
                              int feature_batch, int time_batches,
                              const int32_t* bias, int32_t out_multiplier,
                              int32_t out_shift, int32_t out_zero_bias,
                              int8_t* p_output8) {
  int loopLim = time_batches >> 2;

  ae_int64 d_out64_0;
  ae_valign align_inp1, align_inp2;
  const ae_int16x4 *pt_inp1, *pt_inp2;
  ae_int16x4 d_inp1_0;
  ae_int16x4 d_inp2_0;
  ae_int32x2 d_out32;
  const int32_t* pBias = bias;
  ae_int32x2 d_bias;
  ae_int32x2 max_int8 = AE_MOVDA32(127);
  ae_int32x2 min_int8 = AE_MOVDA32(-128);

  int left_shift, right_shift;
  left_shift = out_shift < 0 ? 0 : out_shift;
  right_shift = out_shift > 0 ? 0 : -out_shift;

  int8_t* p_out8 = p_output8;
  pt_inp1 = (const ae_int16x4*)((WORD16*)weight_time);
  pt_inp2 = (const ae_int16x4*)((WORD16*)activation_state);
  KN_PRINTD(time_batches);
  KN_PRINTD(feature_batch);
  for (int ii = 0; ii < feature_batch; ii++) {
    align_inp1 = AE_LA64_PP(pt_inp1);
    align_inp2 = AE_LA64_PP(pt_inp2);
    d_out64_0 = ZERO64;

    AE_LA16X4_IP(d_inp1_0, align_inp1, pt_inp1);

    AE_LA16X4_IP(d_inp2_0, align_inp2, pt_inp2);

    /*
    #define AE_MULAAAAQ16(q0, d0, d1) \
    { \
      ae_int32x2 d2,d3; \
      ae_int16x4 d = 1; \
      AE_MUL16X4(d3,d2,d0,d1); \
      AE_MULAAD32X16_H0_L1(q0,d2,d); \
      AE_MULAAD32X16_H0_L1(q0,d3,d); \
    }
    */
    for (int j = 0; j < loopLim - 1; j++) {
      // AE_MULAAAAQ16(d_out64_0, d_inp1_0, d_inp2_0);
      ae_int32x2 d2, d3;
      ae_int16x4 d = 1;
      KN_PRINTX_AE16X4(d_inp1_0);
      KN_PRINTX_AE16X4(d_inp2_0);

      AE_MUL16X4(d3, d2, d_inp1_0, d_inp2_0);

      AE_LA16X4_IP(d_inp1_0, align_inp1, pt_inp1);
      AE_LA16X4_IP(d_inp2_0, align_inp2, pt_inp2);

      AE_MULAAD32X16_H0_L1(d_out64_0, d2, d);
      AE_MULAAD32X16_H0_L1_S2(d_out64_0, d3, d);
    }
    AE_MULAAAAQ16(d_out64_0, d_inp1_0, d_inp2_0);
    for (int i = 0; i < (time_batches & 3); i++) {
      AE_L16_IP(d_inp1_0, (ae_int16*)pt_inp1, 2);
      AE_L16_IP(d_inp2_0, (ae_int16*)pt_inp2, 2);
      KN_PRINTX_AE16X4(d_inp1_0);
      KN_PRINTX_AE16X4(d_inp2_0);
      AE_MULA16_00(d_out64_0, d_inp1_0, d_inp2_0);
    }
    // AE_SAT32X2_HIFI4(d_out32, d_out64_0);
    d_out32 = AE_TRUNCA32X2F64S(ZERO64, d_out64_0, 32);
    KN_PRINTX_AE32X2(d_out32);
    AE_L32_XP(d_bias, (ae_int32*)pBias, sizeof(WORD32));
    // d_bias = AE_SRAI32(d_bias, 1);
    KN_PRINTX_AE32X2(d_bias);

    d_out32 = AE_ADD32S(d_out32, d_bias);

    KN_PRINTX_AE32X2(d_out32);
    MPY_BY_QUANT_MULT_X2_OUT32(d_out32, d_out32, out_multiplier, left_shift,
                               right_shift);
    KN_PRINTX_AE32X2(d_out32);
    d_out32 = AE_ADD32S(d_out32, out_zero_bias);
    KN_PRINTX_AE32X2(d_out32);
    // AE_MINMAX32_HIFI4(d_out32, min_int8, max_int8);
    d_out32 = AE_MAX32(d_out32, min_int8);
    d_out32 = AE_MIN32(d_out32, max_int8);
    KN_PRINTX_AE32X2(d_out32);
    *p_out8++ = (int8_t)AE_MOVAD32_L(d_out32);

    // store_fr_postI(fr_out, p_out, INC1);
    //*p_out++ = AE_MOVAD32_L(d_out32);
  }
}

#endif

void SVDFQauntizedInt8(OpData* data, const TfLiteSVDFParams* params,
                       const int8_t* input, const int32_t input_batches,
                       const int32_t input_height, const int8_t* weight_feature,
                       const int32_t feature_batches,
                       const int16_t* weight_time, const int32_t time_batches,
                       int n_memory, const int32_t* bias, int16_t* state_data,
                       int8_t* output) {
  // Shift states.
  int16_t* const state_ptr = state_data;
  //   tflite::micro::GetTensorData<int16_t>(activation_state_tensor);

  // Left shift the activation_state.
  int num_bytes =
      sizeof(*state_ptr) * (input_batches * feature_batches * n_memory - 1);

  // memmove_HMD
  xa_nn_memmove_16(state_ptr, state_ptr + 1, (num_bytes >> 1));

  int16_t* result_in_batch = state_data + (n_memory - 1);

  int sign = (-128 == data->SvdfOp.input_zero_point)
                 ? 1
                 : 3;  // assumption: 128 + sign 8bit = unsigned
  int b_shift = (sign == 1) ? 1 : 2;
  // KN_PRINTD(data->SvdfOp.input_zero_point);
  // KN_PRINTD(input_height);
  // KN_PRINTD(b_shift);KN_PRINTD(b_shift);
  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    //    const int8_t *buffer_1 = weight_feature;

    // MVM8bx8b with input offset
    const int8_t* input_data_batch = input + i_batch * input_height;
    int16_t* output_data_batch =

        result_in_batch + i_batch * n_memory * feature_batches;

    if (data->opt_constraint == 2) {
      SVDFFeatMatInt8((int32_t*)input_data_batch,
                      (const int32_t*)data->map_weight_feat, output_data_batch,
                      feature_batches, input_height, n_memory,
                      data->input_offset_int8,
                      // data->scaleFeat,

                      sign, b_shift, (data->SvdfOp.effective_scale_1_a),
                      data->SvdfOp.effective_scale_1_b);

    } else {
      SVDFFeatMatInt8InputOffset(
          (int32_t*)input_data_batch, (const int32_t*)data->map_weight_feat,
          data->inputOffsetWithW, output_data_batch, feature_batches,
          input_height, n_memory,
          // data->scaleFeat,
          sign, b_shift, (data->SvdfOp.effective_scale_1_a),
          data->SvdfOp.effective_scale_1_b);
    }
  }

  KN_PRINT_Q15_SIZE(result_in_batch, feature_batches * n_memory);
  KN_PRINT_Q15_OFFSET_SIZE(result_in_batch, feature_batches * n_memory,
                           n_memory);
  KN_PRINT_Q15_SIZE(state_data, feature_batches * time_batches);

#ifndef USE_HIFI_TIME_DOT
  // time
  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    int32_t* outputScratch = data->pScratch + i_batch * feature_batches;

    // const int16_t *v1 = weights_time_data;
    const int16_t* activation_state_batch =
        state_data + i_batch * time_batches * feature_batches;

    SVDFTimeInt16(data, weight_time, activation_state_batch, feature_batches,
                  time_batches, outputScratch);
    //   KN_PRINT_AFLOAT(outputScratch, feature_batches);
    // KN_PRINT_AFLOAT
  }

#else

  KN_PRINTD(feature_batches);
  KN_PRINTD(time_batches);
  KN_PRINTD(input_batches);

  int feat_per_batch = feature_batches / input_batches;
  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    // const int16_t* vector1_ptr =
    //    tflite::micro::GetTensorData<int16_t>(weights_time_tensor);

    const int16_t* activation_state_batch =
        state_data + i_batch * time_batches * feature_batches;
    int8_t* output_batch = output + i_batch * feat_per_batch;
    // int32_t* outputScratch = data->pScratch + i_batch * feature_batches;

    SVDFTimeInt16HifiAddBias(data, weight_time, activation_state_batch,
                             feat_per_batch, time_batches * input_batches, bias,
                             (data->SvdfOp.effective_scale_2_a),
                             data->SvdfOp.effective_scale_2_b,
                             data->SvdfOp.output_zero_point, output_batch);
  }
#endif
}

void EvalIntegerSVDF(TfLiteContext* context, TfLiteNode* node,
                     const TfLiteEvalTensor* input_tensor,
                     const TfLiteEvalTensor* weights_feature_tensor,
                     const TfLiteEvalTensor* weights_time_tensor,
                     const TfLiteEvalTensor* bias_tensor,
                     const TfLiteSVDFParams* params,
                     TfLiteEvalTensor* activation_state_tensor,
                     TfLiteEvalTensor* output_tensor, OpData* data_ex) {
  TFLITE_DCHECK(context != nullptr);
  TFLITE_DCHECK(context->GetScratchBuffer != nullptr);

  //  const int n_memory = weights_time_tensor->dims->data[1];
#if 1  // defined(DMX1A_SVDF_OPT) || defined(HMD1A_SVDF_OPT)

  OpDataSvdf* data = static_cast<OpDataSvdf*>(&data_ex->SvdfOp);
  if (data_ex->opt_constraint > 0) {
    // SIZE: batch_size * num_filters * sizeof(int32_t)
    data_ex->pScratch = static_cast<int32_t*>(
        context->GetScratchBuffer(context, data->scratch_tensor_index));

    // cmsis_nn_context scratch_output_ctx;
    data_ex->pScratchOutput = static_cast<int32_t*>(
        context->GetScratchBuffer(context, data->scratch_output_tensor_index));

    //  int8_t* output_data =
    //  tflite::micro::GetTensorData<int8_t>(output_tensor);
    int input_batches = input_tensor->dims->data[0];
    int input_height = input_tensor->dims->data[1];

    int feature_batches = weights_feature_tensor->dims->data[0];
    // int wei
    int time_batches = weights_time_tensor->dims->data[1];

    const int n_memory = weights_time_tensor->dims->data[1];
    SVDFQauntizedInt8(
        data_ex, params,
        (int8_t*)tflite::micro::GetTensorData<int8_t>(input_tensor),
        input_batches, input_height,
        (int8_t*)tflite::micro::GetTensorData<int8_t>(weights_feature_tensor),
        feature_batches,
        (int16_t*)tflite::micro::GetTensorData<int16_t>(weights_time_tensor),
        time_batches, n_memory,
        tflite::micro::GetTensorData<int32_t>(bias_tensor),
        (int16_t*)tflite::micro::GetTensorData<int16_t>(
            activation_state_tensor),
        tflite::micro::GetTensorData<int8_t>(output_tensor));
    KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output_tensor),
                     ElementCount(*output_tensor->dims));
  } else
#endif
  {
    EvalInt8SvdfReference(context, node, input_tensor, weights_feature_tensor,
                          weights_time_tensor, bias_tensor, params,
                          activation_state_tensor, output_tensor, *data);
    // EvalIntegerSVDFRef(context, node, input_tensor, weights_feature_tensor,
    //                     weights_time_tensor, bias_tensor, params,
    //                     activation_state_tensor, output_tensor, *data_ex);
  }
}

TfLiteStatus EvalInt8Hmd(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteSVDFParams*>(node->builtin_data);
  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data = *(static_cast<const OpData*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kSvdfInputTensor);
  const TfLiteEvalTensor* weights_feature =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsFeatureTensor);
  const TfLiteEvalTensor* weights_time =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsTimeTensor);
  const TfLiteEvalTensor* bias =
      (NumInputs(node) == 5)
          ? tflite::micro::GetEvalInput(context, node, kSvdfBiasTensor)
          : nullptr;
  TfLiteEvalTensor* activation_state = tflite::micro::GetMutableEvalInput(
      context, node, kSvdfInputActivationStateTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kSvdfOutputTensor);

  if (weights_feature->type != kTfLiteInt8) {
    TF_LITE_KERNEL_LOG(context, "Type %s not currently supported.",
                       TfLiteTypeGetName(weights_feature->type));
    return kTfLiteError;
  }
  EvalIntegerSVDF(context, node, input, weights_feature, weights_time, bias,
                  params, activation_state, output, (OpData*)&data);

  return kTfLiteOk;
}
TfLiteStatus EvalHmd(TfLiteContext* context, TfLiteNode* node) {
  auto* params = static_cast<TfLiteSVDFParams*>(node->builtin_data);

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kSvdfInputTensor);
  const TfLiteEvalTensor* weights_feature =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsFeatureTensor);
  const TfLiteEvalTensor* weights_time =
      tflite::micro::GetEvalInput(context, node, kSvdfWeightsTimeTensor);
  // TODO(#1751): account for optional bias tensor
  const TfLiteEvalTensor* bias =
      (NumInputs(node) == 5)
          ? tflite::micro::GetEvalInput(context, node, kSvdfBiasTensor)
          : nullptr;
  TfLiteEvalTensor* activation_state = tflite::micro::GetMutableEvalInput(
      context, node, kSvdfInputActivationStateTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kSvdfOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpDataSvdf& data = *(static_cast<const OpDataSvdf*>(node->user_data));

  switch (weights_feature->type) {
    case kTfLiteFloat32: {
      EvalFloatSvdfReference(
          context, node, input, weights_feature, weights_time, bias, params,
          data.scratch_tensor_index, activation_state, output);
      break;
    }

    case kTfLiteInt8: {
      switch (weights_time->type) {
        case kTfLiteInt16: {
          return EvalInt8Hmd(context, node);
        }

        case kTfLiteInt8: {
          EvalInt8SvdfReference(context, node, input, weights_feature,
                                weights_time, bias, params, activation_state,
                                output, data);
          break;
        }

        default: {
          MicroPrintf("Type %s not currently supported.",
                      TfLiteTypeGetName(weights_time->type));
          return kTfLiteError;
        }
      }
      break;
    }

    default: {
      MicroPrintf("Type %s not currently supported.",
                  TfLiteTypeGetName(weights_feature->type));
      return kTfLiteError;
    }
  }

  return kTfLiteOk;
}
#endif
}  // namespace
#ifdef USE_HMD_MVM_OPT
TFLMRegistration Register_SVDF() {
  return tflite::micro::RegisterOp(InitHmd, PrepareHmd, EvalHmd);
}

TFLMRegistration Register_SVDF_INT8() {
  return tflite::micro::RegisterOp(InitHmd, PrepareHmdInt8, EvalInt8Hmd);
}

#else
TFLMRegistration Register_SVDF() {
  return tflite::micro::RegisterOp(Init, Prepare, Eval);
}
TFLMRegistration Register_SVDF_INT8() {
  return tflite::micro::RegisterOp(Init, PrepareInt8, EvalInt8);
}

#endif

}  // namespace tflite
