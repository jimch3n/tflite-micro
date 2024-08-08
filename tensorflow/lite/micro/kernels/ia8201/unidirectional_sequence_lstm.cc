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

// Integer version of unidirectional sequence lstm. Only the standard LSTM
// (defined in the keras LSTM layer, e.g., no peephole etc.) is supported here.
// Currently used by the 16 bits activation case only

#include <algorithm>
#include <limits>

//#define KN_DEBUG

#include "tensorflow/lite/micro/ia8201/config.h"
//#include "tensorflow/lite/ia8201/debug_helper.h"

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor_utils.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/portable_tensor_utils_impl.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/fully_connected.h"
#include "tensorflow/lite/micro/kernels/ia8201/lstm_eval.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
//#include "tensorflow/lite/kernels/kernel_util.h"
//#include "tensorflow/lite/micro/kernels/fully_connected.h"
//#include "tensorflow/lite/micro/kernels/kernel_util.h"

#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount

#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#ifndef DEALLOC_IF_VALID
#define DEALLOC_IF_VALID(x)                              \
  do {                                                   \
    if (x) micro_context->DeallocateTempTfLiteTensor(x); \
  } while (0)
#endif

#define GET_TENSOR_DATA_REMAP(NODE, CONTEXT, KINDEX, D_OUT)                  \
  do {                                                                       \
    MicroContext* micro_context = GetMicroContext(CONTEXT);                  \
    const TfLiteTensor* w =                                                  \
        micro_context->AllocateTempInputTensor(NODE, KINDEX);                \
    const TfLiteEvalTensor* w_eval =                                         \
        tflite::micro::GetEvalInput(CONTEXT, NODE, KINDEX);                  \
    const int8_t* filter = tflite::micro::GetTensorData<int8_t>(w_eval);     \
    int map_coeff_size = tflite::FullyConnectedMap8bitCoeffs(                \
        NULL, NULL, GetTensorShape(w).Dims(0), GetTensorShape(w).Dims(1));   \
    int8_t* temp =                                                           \
        (int8_t*)CONTEXT->AllocatePersistentBuffer(CONTEXT, map_coeff_size); \
    tflite::FullyConnectedMap8bitCoeffs(temp, (int8_t*)filter,               \
                                        GetTensorShape(w).Dims(0),           \
                                        GetTensorShape(w).Dims(1));          \
    D_OUT = temp;                                                            \
    if (w) {                                                                 \
      micro_context->DeallocateTempTfLiteTensor((TfLiteTensor*)w);           \
    }                                                                        \
  } while (0)
namespace tflite {

namespace {
/*Helper Functions*/

/*Kernel functions*/

void* UnidirectionalSequenceLstmInit(TfLiteContext* context, const char* buffer,
                                     size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpDataLSTMEx));
}
#if 0
// copy from xtensa unitdirectional sequence lstm
TfLiteStatus PopulateQuantizedLstmParams8x8_16(
    TfLiteContext* context, TfLiteNode* node,
    IntegerLstmParameter* integer_lstm_param) {
  // Calculate quantized clip for projection and cell.
  const auto* params =
      static_cast<TfLiteUnidirectionalSequenceLSTMParams*>(node->builtin_data);
  const float cell_clip = static_cast<float>(params->cell_clip);
  const float proj_clip = static_cast<float>(params->proj_clip);
  // FIX BUG: malloc
  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* cell_state = micro_context->AllocateTempInputTensor(node, kLstmCellStateTensor);
  //    GetVariableInput(context, node, kCellStateTensor);

  TF_LITE_ENSURE(context, cell_state != nullptr);
  TfLiteTensor* output_tensor = micro_context->AllocateTempOutputTensor(node, kLstmOutputTensor);
  ;
  // TF_LITE_ENSURE_OK(
  //    context, GetOutputSafe(context, node, kOutputTensor,
  //                           &output_tensor));
  //FIXME: quantization.params is empty use params
  auto* cell_state_params = static_cast<TfLiteQuantizationParams*> (&cell_state->params);  //(cell_state->quantization.params);
  auto* proj_params = static_cast<TfLiteQuantizationParams*>(&output_tensor->params);
      //(
      //output_tensor->quantization.params);

  KN_PRINTX(cell_state);
  KN_PRINTF(cell_state_params->scale);
  KN_PRINTD(cell_state_params->zero_point);

  if (cell_clip > static_cast<float>(0.0)) {
    integer_lstm_param->quantized_cell_clip = static_cast<int16_t>(std::min(
        std::max(cell_clip / cell_state_params->scale, -32768.0f),
        32767.0f));
  } else {
    integer_lstm_param->quantized_cell_clip = 0;
  }
  if (proj_clip > static_cast<float>(0.0)) {
    integer_lstm_param->quantized_proj_clip = static_cast<int8_t>(std::min(
        std::max(proj_clip / proj_params->scale, -128.0f), 127.0f));
  } else {
    integer_lstm_param->quantized_proj_clip = 0;
  }
  micro_context->DeallocateTempTfLiteTensor(cell_state);
  micro_context->DeallocateTempTfLiteTensor(output_tensor);
  // Calculate effective scales.
  OpDataLSTMEx* op_data_ex = static_cast<OpDataLSTMEx*>(node->user_data);

  const bool use_layer_norm = op_data_ex->use_layer_norm;

  TfLiteTensor* input = micro_context->AllocateTempInputTensor(node, kLstmInputTensor);
  // TF_LITE_ENSURE_OK(
  //    context,
  //    GetInputSafe(context, node, kInputTensor, &input));

  TfLiteTensor* input_to_input_weights = micro_context->AllocateTempInputTensor(
      node, kLstmInputToInputWeightsTensor);
  // GetOptionalInputTensor(
  //    context, node, kLstmInputToInputWeightsTensor);
  TfLiteTensor* input_to_forget_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmInputToForgetWeightsTensor);
  // TF_LITE_ENSURE_OK(context,
  //                 GetInputSafe(context, node,
  //                              kLstmInputToForgetWeightsTensor,
  //                             &input_to_forget_weights));
  TfLiteTensor* input_to_cell_weights = micro_context->AllocateTempInputTensor(
      node, kLstmInputToCellWeightsTensor);
  //  TF_LITE_ENSURE_OK(
  //    context,
  //     GetInputSafe(context, node,
  //     kLstmInputToCellWeightsTensor,
  //                  &input_to_cell_weights));
  TfLiteTensor* input_to_output_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmInputToOutputWeightsTensor);
  // TF_LITE_ENSURE_OK(context,
  //                   GetInputSafe(context, node,
  //                               kLstmInputToOutputWeightsTensor,
  //                               &input_to_output_weights));

  TfLiteTensor* recurrent_to_input_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToInputWeightsTensor);

  // = GetOptionalInputTensor(
  //     context, node, kLstmRecurrentToInputWeightsTensor);
  TfLiteTensor* recurrent_to_forget_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToForgetWeightsTensor);
  // TF_LITE_ENSURE_OK(
  //    context, GetInputSafe(context, node,
  //                          kLstmRecurrentToForgetWeightsTensor,
  //                          &recurrent_to_forget_weights));
  TfLiteTensor* recurrent_to_cell_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToCellWeightsTensor);
  // TF_LITE_ENSURE_OK(
  //   context, GetInputSafe(context, node,
  //                         kLstmRecurrentToCellWeightsTensor,
  //                         &recurrent_to_cell_weights));
  TfLiteTensor* recurrent_to_output_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToOutputWeightsTensor);
  // TF_LITE_ENSURE_OK(
  //   context, GetInputSafe(context, node,
  //                         kLstmRecurrentToOutputWeightsTensor,
  //                         &recurrent_to_output_weights));

  TfLiteTensor* cell_to_input_weights = micro_context->AllocateTempInputTensor(
      node, kLstmCellToInputWeightsTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmCellToInputWeightsTensor);
  TfLiteTensor* cell_to_forget_weights = micro_context->AllocateTempInputTensor(
      node, kLstmCellToForgetWeightsTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmCellToForgetWeightsTensor);
  TfLiteTensor* cell_to_output_weights = micro_context->AllocateTempInputTensor(
      node, kLstmCellToOutputWeightsTensor);
  // GetOptionalInputTensor(
  //    context, node, kLstmCellToOutputWeightsTensor);

  TfLiteTensor* input_layer_norm_coefficients =
      micro_context->AllocateTempInputTensor(
          node, kLstmInputLayerNormCoefficientsTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmInputLayerNormCoefficientsTensor);
  TfLiteTensor* forget_layer_norm_coefficients =
      micro_context->AllocateTempInputTensor(
          node, kLstmForgetLayerNormCoefficientsTensor);
  // GetOptionalInputTensor(
  //    context, node, kLstmForgetLayerNormCoefficientsTensor);
  TfLiteTensor* cell_layer_norm_coefficients =
      micro_context->AllocateTempInputTensor(
          node, kLstmCellLayerNormCoefficientsTensor);
  // GetOptionalInputTensor(
  //    context, node, kLstmCellLayerNormCoefficientsTensor);
  TfLiteTensor* output_layer_norm_coefficients =
      micro_context->AllocateTempInputTensor(
          node, kLstmOutputLayerNormCoefficientsTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmOutputLayerNormCoefficientsTensor);

  TfLiteTensor* projection_weights = micro_context->AllocateTempInputTensor(
      node, kLstmProjectionWeightsTensor);
  // GetOptionalInputTensor(
  //    context, node, kLstmProjectionWeightsTensor);

  TfLiteTensor* output_state = micro_context->AllocateTempInputTensor(
      node, kLstmOutputStateTensor);
  // GetVariableInput(context, node, kLstmOutputStateTensor);

  TF_LITE_ENSURE(context, output_state != nullptr);

  // Since we have already checked that weights are all there or none, we can
  // check the existence of only one to get the condition.
  const bool use_cifg = (input_to_input_weights == nullptr);
  const bool use_peephole = (cell_to_output_weights != nullptr);
  const bool use_projection = (projection_weights != nullptr);

  // Get intermediate scales and zero points.
  constexpr size_t kIntermediateCount = 5;
  float intermediate_scale[kIntermediateCount];
  int32_t intermediate_zp[kIntermediateCount];
  KN_PRINTD(use_layer_norm);
  //KN_PRINT_Q31_SIZE(node->intermediates->data, 5);
  for (int i = 0; i < 4; ++i) {
    if (use_layer_norm) {
      TfLiteTensor* intermediate =
          context->GetTensor(context, node->intermediates->data[i]);
      auto* tmp_params = static_cast<TfLiteAffineQuantization*>(
          intermediate->quantization.params);
      intermediate_scale[i] = tmp_params->scale->data[0];
      intermediate_zp[i] = tmp_params->zero_point->data[0];
    } else {
      // Q3.12 for activation functions.
      intermediate_scale[i] = std::pow(2, -12);
      intermediate_zp[i] = 0;
    }
  }
  KN_PRINTD(node->intermediates->data[4]);
  // In the absence of projection, hidden becomes otuput and this intermediate
  // is ignored.
  TfLiteTensor* hidden =
      // micro_context->AllocateTempInputTensor(node,
      // node->intermediates->data[4]);
      context->GetTensor(context, node->intermediates->data[4]);

  KN_PRINTD(hidden->is_variable);
  KN_PRINTD(hidden->type);
  KN_PRINTD(hidden->bytes);
  KN_PRINTD(hidden->dims->size);
  KN_PRINTX(hidden);
  auto* hidden_params =
      static_cast<TfLiteAffineQuantization*>(hidden->quantization.params);
  intermediate_scale[4] = hidden_params->scale->data[0];
  intermediate_zp[4] = hidden_params->zero_point->data[0];
  // if(hidden) micro_context->DeallocateTempTfLiteTensor(hidden);
  // Scales.
  KN_PRINTF(intermediate_scale[4]);
  KN_PRINTD(intermediate_zp[4]);

  if (hidden) micro_context->DeallocateTempTfLiteTensor(hidden);
  const float default_scale = 1.0;
  float input_scale = default_scale;
  float input_to_input_weight_scale = default_scale;
  float recurrent_to_input_weight_scale = default_scale;
  float cell_to_input_weight_scale = default_scale;
  float input_to_forget_weight_scale = default_scale;
  float recurrent_to_forget_weight_scale = default_scale;
  float cell_to_forget_weight_scale = default_scale;
  float input_to_cell_weight_scale = default_scale;
  float recurrent_to_cell_weight_scale = default_scale;
  float input_to_output_weight_scale = default_scale;
  float recurrent_to_output_weight_scale = default_scale;
  float cell_to_output_weight_scale = default_scale;
  float projection_weight_scale = default_scale;
  float layer_norm_input_scale = default_scale;
  float layer_norm_forget_scale = default_scale;
  float layer_norm_cell_scale = default_scale;
  float layer_norm_output_scale = default_scale;
  float output_state_scale = default_scale;
  int cell_scale = 1;

  // Effective scales.
  float effective_input_to_input_scale = default_scale;
  float effective_recurrent_to_input_scale = default_scale;
  float effective_cell_to_input_scale = default_scale;
  float effective_input_to_forget_scale = default_scale;
  float effective_recurrent_to_forget_scale = default_scale;
  float effective_cell_to_forget_scale = default_scale;
  float effective_input_to_cell_scale = default_scale;
  float effective_recurrent_to_cell_scale = default_scale;
  float effective_input_to_output_scale = default_scale;
  float effective_recurrent_to_output_scale = default_scale;
  float effective_cell_to_output_scale = default_scale;
  float effective_proj_scale = default_scale;
  float effective_hidden_scale = default_scale;

  KN_PRINTD(use_cifg);
  KN_PRINTD(use_peephole);
  KN_PRINTD(use_projection);
  KN_PRINTD(use_layer_norm);
  // Populate scales.
  if (!use_cifg) {
    input_to_input_weight_scale = input_to_input_weights->params.scale;
    recurrent_to_input_weight_scale = recurrent_to_input_weights->params.scale;
  }

  if (use_peephole) {
    if (!use_cifg) {
      cell_to_input_weight_scale = cell_to_input_weights->params.scale;
    }
    cell_to_forget_weight_scale = cell_to_forget_weights->params.scale;
    cell_to_output_weight_scale = cell_to_output_weights->params.scale;
  }

  if (use_layer_norm) {
    if (!use_cifg) {
      layer_norm_input_scale = input_layer_norm_coefficients->params.scale;
    }
    layer_norm_forget_scale = forget_layer_norm_coefficients->params.scale;
    layer_norm_cell_scale = cell_layer_norm_coefficients->params.scale;
    layer_norm_output_scale = output_layer_norm_coefficients->params.scale;
  }

  if (use_projection) {
    projection_weight_scale = projection_weights->params.scale;
  }
  output_state_scale = output_state->params.scale;

  input_to_forget_weight_scale = input_to_forget_weights->params.scale;
  input_to_cell_weight_scale = input_to_cell_weights->params.scale;
  input_to_output_weight_scale = input_to_output_weights->params.scale;
  recurrent_to_forget_weight_scale = recurrent_to_forget_weights->params.scale;
  recurrent_to_cell_weight_scale = recurrent_to_cell_weights->params.scale;
  recurrent_to_output_weight_scale = recurrent_to_output_weights->params.scale;
  KN_PRINTD(node->inputs->size);
  // Check cell state (already used above)
  TF_LITE_ENSURE(context, CheckedLog2(cell_state->params.scale, &cell_scale));
  // TF_LITE_ENSURE(context, cell_scale <= -9);
  integer_lstm_param->cell_scale = cell_scale;
  input_scale = input->params.scale;

  // Calculate effective scales.
  if (!use_cifg) {
    effective_input_to_input_scale =
        input_to_input_weight_scale * input_scale / intermediate_scale[0];
    effective_recurrent_to_input_scale = recurrent_to_input_weight_scale *
                                         output_state_scale /
                                         intermediate_scale[0];
  }
  effective_input_to_forget_scale =
      input_to_forget_weight_scale * input_scale / intermediate_scale[1];
  effective_recurrent_to_forget_scale = recurrent_to_forget_weight_scale *
                                        output_state_scale /
                                        intermediate_scale[1];

  effective_input_to_cell_scale =
      input_to_cell_weight_scale * input_scale / intermediate_scale[2];
  effective_recurrent_to_cell_scale = recurrent_to_cell_weight_scale *
                                      output_state_scale /
                                      intermediate_scale[2];

  effective_input_to_output_scale =
      input_to_output_weight_scale * input_scale / intermediate_scale[3];
  effective_recurrent_to_output_scale = recurrent_to_output_weight_scale *
                                        output_state_scale /
                                        intermediate_scale[3];

  effective_hidden_scale = std::pow((float)2, (float)-15) /
                           intermediate_scale[4] *
                           std::pow((float)2, (float)-15);

  effective_proj_scale =
      projection_weight_scale * intermediate_scale[4] / output_state_scale;

  if (use_peephole) {
    if (!use_cifg) {
      effective_cell_to_input_scale =
          std::pow((float)(2), (float)cell_scale) *  // NOLINT
          (float)(cell_to_input_weight_scale) / intermediate_scale[0];
    }
    effective_cell_to_forget_scale =
        std::pow((float)2, (float)cell_scale) *  // NOLINT
        (float)cell_to_forget_weight_scale / intermediate_scale[1];
    effective_cell_to_output_scale =
        std::pow((float)2, (float)cell_scale) *  // NOLINT
        (float)cell_to_output_weight_scale / intermediate_scale[3];
  }
  KN_PRINTD(node->inputs->size);
  // Decompose scales.
  QuantizeMultiplier(static_cast<double>(effective_input_to_input_scale),
                     &integer_lstm_param->effective_input_to_input_scale_a,
                     &integer_lstm_param->effective_input_to_input_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_recurrent_to_input_scale),
                     &integer_lstm_param->effective_recurrent_to_input_scale_a,
                     &integer_lstm_param->effective_recurrent_to_input_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_cell_to_input_scale),
                     &integer_lstm_param->effective_cell_to_input_scale_a,
                     &integer_lstm_param->effective_cell_to_input_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_input_to_forget_scale),
                     &integer_lstm_param->effective_input_to_forget_scale_a,
                     &integer_lstm_param->effective_input_to_forget_scale_b);
  QuantizeMultiplier(
      static_cast<double>(effective_recurrent_to_forget_scale),
      &integer_lstm_param->effective_recurrent_to_forget_scale_a,
      &integer_lstm_param->effective_recurrent_to_forget_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_cell_to_forget_scale),
                     &integer_lstm_param->effective_cell_to_forget_scale_a,
                     &integer_lstm_param->effective_cell_to_forget_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_input_to_cell_scale),
                     &integer_lstm_param->effective_input_to_cell_scale_a,
                     &integer_lstm_param->effective_input_to_cell_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_recurrent_to_cell_scale),
                     &integer_lstm_param->effective_recurrent_to_cell_scale_a,
                     &integer_lstm_param->effective_recurrent_to_cell_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_input_to_output_scale),
                     &integer_lstm_param->effective_input_to_output_scale_a,
                     &integer_lstm_param->effective_input_to_output_scale_b);
  QuantizeMultiplier(
      static_cast<double>(effective_recurrent_to_output_scale),
      &integer_lstm_param->effective_recurrent_to_output_scale_a,
      &integer_lstm_param->effective_recurrent_to_output_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_cell_to_output_scale),
                     &integer_lstm_param->effective_cell_to_output_scale_a,
                     &integer_lstm_param->effective_cell_to_output_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_proj_scale),
                     &integer_lstm_param->effective_proj_scale_a,
                     &integer_lstm_param->effective_proj_scale_b);
  QuantizeMultiplier(static_cast<double>(effective_hidden_scale),
                     &integer_lstm_param->effective_hidden_scale_a,
                     &integer_lstm_param->effective_hidden_scale_b);
  QuantizeMultiplier(static_cast<double>(layer_norm_input_scale),
                     &integer_lstm_param->layer_norm_input_scale_a,
                     &integer_lstm_param->layer_norm_input_scale_b);
  QuantizeMultiplier(static_cast<double>(layer_norm_forget_scale),
                     &integer_lstm_param->layer_norm_forget_scale_a,
                     &integer_lstm_param->layer_norm_forget_scale_b);
  QuantizeMultiplier(static_cast<double>(layer_norm_cell_scale),
                     &integer_lstm_param->layer_norm_cell_scale_a,
                     &integer_lstm_param->layer_norm_cell_scale_b);
  QuantizeMultiplier(static_cast<double>(layer_norm_output_scale),
                     &integer_lstm_param->layer_norm_output_scale_a,
                     &integer_lstm_param->layer_norm_output_scale_b);

  integer_lstm_param->hidden_zp = intermediate_zp[4];

  // 10000 is used to make sure the kernel logic does not overflow.
  if (!use_cifg) {
    integer_lstm_param->input_variance_guard =
        std::max(static_cast<int32_t>(1),
                 static_cast<int32_t>(10000 * layer_norm_input_scale));
  }
  integer_lstm_param->forget_variance_guard =
      std::max(static_cast<int32_t>(1),
               static_cast<int32_t>(10000 * layer_norm_forget_scale));
  integer_lstm_param->cell_variance_guard =
      std::max(static_cast<int32_t>(1),
               static_cast<int32_t>(10000 * layer_norm_cell_scale));
  integer_lstm_param->output_variance_guard =
      std::max(static_cast<int32_t>(1),
               static_cast<int32_t>(10000 * layer_norm_output_scale));

  // free
  DEALLOC_IF_VALID(input);

  DEALLOC_IF_VALID(input_to_input_weights);
  DEALLOC_IF_VALID(input_to_forget_weights);
  DEALLOC_IF_VALID(input_to_cell_weights);
  DEALLOC_IF_VALID(input_to_output_weights);

  DEALLOC_IF_VALID(recurrent_to_input_weights);
  DEALLOC_IF_VALID(recurrent_to_forget_weights);
  DEALLOC_IF_VALID(recurrent_to_cell_weights);
  DEALLOC_IF_VALID(recurrent_to_output_weights);  // 9



  DEALLOC_IF_VALID(cell_to_input_weights);
  DEALLOC_IF_VALID(cell_to_forget_weights);
  DEALLOC_IF_VALID(cell_to_output_weights);  // 4

  DEALLOC_IF_VALID(input_layer_norm_coefficients);
  DEALLOC_IF_VALID(forget_layer_norm_coefficients);
  DEALLOC_IF_VALID(cell_layer_norm_coefficients);
  DEALLOC_IF_VALID(output_layer_norm_coefficients);  // 4

  DEALLOC_IF_VALID(projection_weights);
  DEALLOC_IF_VALID(output_state);  // 2

  return kTfLiteOk;
}


// Check that input tensor dimensions matches with each other.
TfLiteStatus CheckInputTensorDimensions(TfLiteContext* context,
                                        TfLiteNode* node, int n_input,
                                        int n_output, int n_cell,
                                        bool use_layer_norm, bool is_integer) {
  const auto* params = reinterpret_cast<TfLiteLSTMParams*>(node->builtin_data);
  MicroContext* micro_context = GetMicroContext(context);

  // Making sure clipping parameters have valid values.
  // == 0 means no clipping
  //  > 0 means clipping
  TF_LITE_ENSURE(context, params->cell_clip >= 0);
  TF_LITE_ENSURE(context, params->proj_clip >= 0);
  const TfLiteEvalTensor* input_to_input_weights = tflite::micro::GetEvalInput(
      context, node, kLstmInputToInputWeightsTensor);
  if (input_to_input_weights != nullptr) {
    TF_LITE_ENSURE_EQ(context, input_to_input_weights->dims->size, 2);
    TF_LITE_ENSURE_EQ(context, input_to_input_weights->dims->data[0], n_cell);
    TF_LITE_ENSURE_EQ(context, input_to_input_weights->dims->data[1], n_input);
  }
  const TfLiteEvalTensor* input_to_forget_weights = tflite::micro::GetEvalInput(
      context, node, kLstmInputToForgetWeightsTensor);

  TF_LITE_ENSURE_EQ(context, input_to_forget_weights->dims->size, 2);
  TF_LITE_ENSURE_EQ(context, input_to_forget_weights->dims->data[0], n_cell);
  TF_LITE_ENSURE_EQ(context, input_to_forget_weights->dims->data[1], n_input);
  const TfLiteEvalTensor* input_to_cell_weights = tflite::micro::GetEvalInput(
      context, node, kLstmInputToCellWeightsTensor);

  TF_LITE_ENSURE_EQ(context, input_to_cell_weights->dims->size, 2);
  TF_LITE_ENSURE_EQ(context, input_to_cell_weights->dims->data[0], n_cell);
  TF_LITE_ENSURE_EQ(context, input_to_cell_weights->dims->data[1], n_input);
  const TfLiteEvalTensor* recurrent_to_input_weights =
      tflite::micro::GetEvalInput(
          context, node, kLstmRecurrentToInputWeightsTensor);
  if (recurrent_to_input_weights != nullptr) {
    TF_LITE_ENSURE_EQ(context, recurrent_to_input_weights->dims->size, 2);
    TF_LITE_ENSURE_EQ(context, recurrent_to_input_weights->dims->data[0],
                      n_cell);
    TF_LITE_ENSURE_EQ(context, recurrent_to_input_weights->dims->data[1],
                      n_output);
  }
  const TfLiteEvalTensor* recurrent_to_forget_weights =
      tflite::micro::GetEvalInput(
          context, node, kLstmRecurrentToForgetWeightsTensor);

  TF_LITE_ENSURE_EQ(context, recurrent_to_forget_weights->dims->size, 2);
  TF_LITE_ENSURE_EQ(context, recurrent_to_forget_weights->dims->data[0],
                    n_cell);
  TF_LITE_ENSURE_EQ(context, recurrent_to_forget_weights->dims->data[1],
                    n_output);
  const TfLiteEvalTensor* recurrent_to_cell_weights =
      tflite::micro::GetEvalInput(
          context, node, kLstmRecurrentToCellWeightsTensor);

  TF_LITE_ENSURE_EQ(context, recurrent_to_cell_weights->dims->size, 2);
  TF_LITE_ENSURE_EQ(context, recurrent_to_cell_weights->dims->data[0], n_cell);
  TF_LITE_ENSURE_EQ(context, recurrent_to_cell_weights->dims->data[1],
                    n_output);

  // We make sure the input-gate's parameters are either both present (regular
  // LSTM) or not at all (CIFG-LSTM).
  const bool cifg_weights_all_or_none =
      ((input_to_input_weights != nullptr) &&
       (recurrent_to_input_weights != nullptr)) ||
      ((input_to_input_weights == nullptr) &&
       (recurrent_to_input_weights == nullptr));
  TF_LITE_ENSURE(context, cifg_weights_all_or_none == true);

  TfLiteTensor* cell_to_input_weights = micro_context->AllocateTempInputTensor(
      node, kLstmCellToInputWeightsTensor);
  // GetOptionalInputTensor(
  // context, node, kLstmCellToInputWeightsTensor);
  if (cell_to_input_weights != nullptr) {
    TF_LITE_ENSURE_EQ(context, cell_to_input_weights->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, cell_to_input_weights->dims->data[0], n_cell);
    TF_LITE_ENSURE_TYPES_EQ(
        context, cell_to_input_weights->type,
        is_integer ? kTfLiteInt16 : input_to_forget_weights->type);
  }

  TfLiteTensor* cell_to_forget_weights = micro_context->AllocateTempInputTensor(
      node, kLstmCellToInputWeightsTensor);
  // GetOptionalInputTensor(
  //    context, node, lstm::full::kLstmCellToForgetWeightsTensor);
  if (cell_to_forget_weights != nullptr) {
    TF_LITE_ENSURE_EQ(context, cell_to_forget_weights->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, cell_to_forget_weights->dims->data[0], n_cell);
    TF_LITE_ENSURE_TYPES_EQ(
        context, cell_to_forget_weights->type,
        is_integer ? kTfLiteInt16 : input_to_forget_weights->type);
  }

  TfLiteTensor* cell_to_output_weights = micro_context->AllocateTempInputTensor(
      node, kLstmCellToInputWeightsTensor);
  // GetOptionalInputTensor(
  //    context, node, kLstmCellToOutputWeightsTensor);
  if (cell_to_output_weights != nullptr) {
    TF_LITE_ENSURE_EQ(context, cell_to_output_weights->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, cell_to_output_weights->dims->data[0], n_cell);
    TF_LITE_ENSURE_TYPES_EQ(
        context, cell_to_output_weights->type,
        is_integer ? kTfLiteInt16 : input_to_forget_weights->type);
  }

  // Making sure the peephole weights are there all or none.
  const bool use_cifg = (input_to_input_weights == nullptr);
  const bool peephole_weights_all_or_none =
      ((cell_to_input_weights != nullptr || use_cifg) &&
       (cell_to_forget_weights != nullptr) &&
       (cell_to_output_weights != nullptr)) ||
      ((cell_to_input_weights == nullptr) &&
       (cell_to_forget_weights == nullptr) &&
       (cell_to_output_weights == nullptr));
  TF_LITE_ENSURE(context, peephole_weights_all_or_none == true);
  const TfLiteEvalTensor* input_gate_bias = tflite::micro::GetEvalInput(
      context, node, kLstmInputGateBiasTensor);

  if (use_cifg) {
    TF_LITE_ENSURE_EQ(context, input_gate_bias, nullptr);
  } else {
    TF_LITE_ENSURE_EQ(context, input_gate_bias->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, input_gate_bias->dims->data[0], n_cell);
    if (is_integer) {
      TF_LITE_ENSURE_TYPES_EQ(context, input_gate_bias->type, kTfLiteInt32);
    } else {
      TF_LITE_ENSURE_TYPES_EQ(context, input_gate_bias->type, kTfLiteFloat32);
    }
  }
  const TfLiteEvalTensor* forget_gate_bias = tflite::micro::GetEvalInput(
      context, node, kLstmForgetGateBiasTensor);

  TF_LITE_ENSURE_EQ(context, forget_gate_bias->dims->size, 1);
  TF_LITE_ENSURE_EQ(context, forget_gate_bias->dims->data[0], n_cell);
  if (is_integer) {
    TF_LITE_ENSURE_TYPES_EQ(context, forget_gate_bias->type, kTfLiteInt32);
  } else {
    TF_LITE_ENSURE_TYPES_EQ(context, forget_gate_bias->type, kTfLiteFloat32);
  }
  const TfLiteEvalTensor* cell_gate_bias = tflite::micro::GetEvalInput(
      context, node, kLstmCellGateBiasTensor);

  TF_LITE_ENSURE_EQ(context, cell_gate_bias->dims->size, 1);
  TF_LITE_ENSURE_EQ(context, cell_gate_bias->dims->data[0], n_cell);
  if (is_integer) {
    TF_LITE_ENSURE_TYPES_EQ(context, cell_gate_bias->type, kTfLiteInt32);
  } else {
    TF_LITE_ENSURE_TYPES_EQ(context, cell_gate_bias->type, kTfLiteFloat32);
  }
  const TfLiteEvalTensor* output_gate_bias = tflite::micro::GetEvalInput(
      context, node, kLstmOutputGateBiasTensor);
  TF_LITE_ENSURE_EQ(context, output_gate_bias->dims->size, 1);
  TF_LITE_ENSURE_EQ(context, output_gate_bias->dims->data[0], n_cell);
  if (is_integer) {
    TF_LITE_ENSURE_TYPES_EQ(context, output_gate_bias->type, kTfLiteInt32);
  } else {
    TF_LITE_ENSURE_TYPES_EQ(context, output_gate_bias->type, kTfLiteFloat32);
  }

  TfLiteTensor* projection_weights = micro_context->AllocateTempInputTensor(
      node, kLstmCellToInputWeightsTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmProjectionWeightsTensor);
  if (projection_weights != nullptr) {
    TF_LITE_ENSURE_EQ(context, projection_weights->dims->size, 2);
    TF_LITE_ENSURE_EQ(context, projection_weights->dims->data[0], n_output);
    TF_LITE_ENSURE_EQ(context, projection_weights->dims->data[1], n_cell);
  }

  TfLiteTensor* projection_bias = micro_context->AllocateTempInputTensor(
      node, kLstmCellToInputWeightsTensor);
  // GetOptionalInputTensor(
  //     context, node, kLstmProjectionBiasTensor);
  if (projection_bias != nullptr) {
    TF_LITE_ENSURE_EQ(context, projection_bias->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, projection_bias->dims->data[0], n_output);
    if (is_integer) {
      TF_LITE_ENSURE_TYPES_EQ(context, projection_bias->type, kTfLiteInt32);
    } else {
      TF_LITE_ENSURE_TYPES_EQ(context, projection_bias->type, kTfLiteFloat32);
    }
  }

  // Making sure the projection tensors are consistent:
  // 1) If projection weight is not present, then projection bias should not be
  // present.
  // 2) If projection weight is present, then projection bias is optional.
  const bool projecton_tensors_consistent =
      ((projection_weights != nullptr) || (projection_bias == nullptr));
  TF_LITE_ENSURE(context, projecton_tensors_consistent == true);

  if (use_layer_norm) {
    const TfLiteEvalTensor* input_layer_norm_coefficients =
        tflite::micro::GetEvalInput(
            context, node,
            kLstmInputLayerNormCoefficientsTensor);
    if (use_cifg) {
      TF_LITE_ENSURE_EQ(context, input_layer_norm_coefficients, nullptr);
    } else {
      TF_LITE_ENSURE(context, input_layer_norm_coefficients != nullptr);
      TF_LITE_ENSURE_EQ(context, input_layer_norm_coefficients->dims->size, 1);
      TF_LITE_ENSURE_EQ(context, input_layer_norm_coefficients->dims->data[0],
                        n_cell);
      if (is_integer) {
        TF_LITE_ENSURE_TYPES_EQ(context, input_layer_norm_coefficients->type,
                                kTfLiteInt16);
      } else {
        TF_LITE_ENSURE_TYPES_EQ(context, input_layer_norm_coefficients->type,
                                kTfLiteFloat32);
      }
    }
    const TfLiteEvalTensor* forget_layer_norm_coefficients =
        tflite::micro::GetEvalInput(
            context, node,
            kLstmForgetLayerNormCoefficientsTensor);
    TF_LITE_ENSURE_EQ(context, forget_layer_norm_coefficients->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, forget_layer_norm_coefficients->dims->data[0],
                      n_cell);
    if (is_integer) {
      TF_LITE_ENSURE_TYPES_EQ(context, forget_layer_norm_coefficients->type,
                              kTfLiteInt16);
    } else {
      TF_LITE_ENSURE_TYPES_EQ(context, forget_layer_norm_coefficients->type,
                              kTfLiteFloat32);
    }
    const TfLiteEvalTensor* cell_layer_norm_coefficients =
        tflite::micro::GetEvalInput(
            context, node, kLstmCellLayerNormCoefficientsTensor);
    TF_LITE_ENSURE_EQ(context, cell_layer_norm_coefficients->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, cell_layer_norm_coefficients->dims->data[0],
                      n_cell);
    if (is_integer) {
      TF_LITE_ENSURE_TYPES_EQ(context, cell_layer_norm_coefficients->type,
                              kTfLiteInt16);
    } else {
      TF_LITE_ENSURE_TYPES_EQ(context, cell_layer_norm_coefficients->type,
                              kTfLiteFloat32);
    }
    const TfLiteEvalTensor* output_layer_norm_coefficients =
        tflite::micro::GetEvalInput(
            context, node,
            kLstmOutputLayerNormCoefficientsTensor);

    TF_LITE_ENSURE_EQ(context, output_layer_norm_coefficients->dims->size, 1);
    TF_LITE_ENSURE_EQ(context, output_layer_norm_coefficients->dims->data[0],
                      n_cell);
    if (is_integer) {
      TF_LITE_ENSURE_TYPES_EQ(context, output_layer_norm_coefficients->type,
                              kTfLiteInt16);
    } else {
      TF_LITE_ENSURE_TYPES_EQ(context, output_layer_norm_coefficients->type,
                              kTfLiteFloat32);
    }
  }
  DEALLOC_IF_VALID(cell_to_input_weights);
  DEALLOC_IF_VALID(cell_to_forget_weights);
  DEALLOC_IF_VALID(cell_to_output_weights);

  DEALLOC_IF_VALID(projection_weights);
  DEALLOC_IF_VALID(projection_bias);
  return kTfLiteOk;
}


TfLiteStatus PrecomputeZeroPointTimesWeightWithBias(
    TfLiteContext* context, int32_t zero_point,
    const TfLiteTensor* weight_tensor, const TfLiteTensor* bias_tensor,
    //std::unique_ptr<int32_t[]>* output
    int32_t **output
) {
  if (weight_tensor == nullptr) {
    return kTfLiteOk;
  }

  const RuntimeShape& weight_shape = GetTensorShape(weight_tensor);
  TF_LITE_ENSURE_EQ(context, weight_shape.DimensionsCount(), 2);
  const int row = weight_shape.Dims(0);
  const int col = weight_shape.Dims(1);

  KN_PRINTD(row);
  KN_PRINTD(col);
  KN_PRINTX(output);
  //int32_t* new_output_row = new int32_t[row];
  int32_t* new_output_row = (int32_t *)context->AllocatePersistentBuffer(context, row*sizeof(int32_t));
  //output = new_output_row;//new int32_t[row]);
  if (bias_tensor == nullptr) {
    memset(new_output_row, 0, row * sizeof(int32_t));
  } else {
    const int32_t* bias = GetTensorData<int32_t>(bias_tensor);
    memcpy(new_output_row, bias, row * sizeof(int32_t));
  }
  if (zero_point != 0) {
    const int8_t* weight = GetTensorData<int8_t>(weight_tensor);
    tensor_utils::PortableMatrixScalarMultiplyAccumulate(
        weight, zero_point, row, col, new_output_row);
  }
  *output = new_output_row;
  return kTfLiteOk;
}

TfLiteStatus PopulatePrecomputedZPTimesWeightsWithBias(TfLiteContext* context,
                                                       OpDataLSTMEx* op_data_ex,
                                                       TfLiteNode* node) {
  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input = micro_context->AllocateTempInputTensor(
      node, kLstmInputTensor);
  // TF_LITE_ENSURE_OK(
  //   context,
  //   GetInputSafe(context, node, kLstmInputTensor, &input));

  TfLiteTensor* output_state = micro_context->AllocateTempInputTensor(
      node, kLstmOutputStateTensor);  // GetInput(context, node,
                                                     // kLstmInputTensor);

  //      GetVariableInput(context, node,
  //      kLstmOutputStateTensor);
  TF_LITE_ENSURE(context, output_state != nullptr);

  const int32_t input_zero_point = -input->params.zero_point;
  const int32_t output_state_zero_point = -output_state->params.zero_point;

  TfLiteTensor* input_to_input_weights = micro_context->AllocateTempInputTensor(
      node, kLstmInputToInputWeightsTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmInputToInputWeightsTensor);
  TfLiteTensor* input_to_forget_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmInputToForgetWeightsTensor);
  // TF_LITE_ENSURE_OK(context,
  //                 GetInputSafe(context, node,
  //                               kLstmInputToForgetWeightsTensor,
  //                               &input_to_forget_weights));
  TfLiteTensor* input_to_cell_weights = micro_context->AllocateTempInputTensor(
      node, kLstmInputToCellWeightsTensor);
  // TF_LITE_ENSURE_OK(
  //  context,
  //  GetInputSafe(context, node, kLstmInputToCellWeightsTensor,
  //                &input_to_cell_weights));
  TfLiteTensor* input_to_output_weights =

      micro_context->AllocateTempInputTensor(
          node, kLstmInputToOutputWeightsTensor);
  // TF_LITE_ENSURE_OK(context,
  //                   GetInputSafe(context, node,
  //                                kLstmInputToOutputWeightsTensor,
  //                               &input_to_output_weights));

  TfLiteTensor* recurrent_to_input_weights =

      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToInputWeightsTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmRecurrentToInputWeightsTensor);
  TfLiteTensor* recurrent_to_forget_weights =

      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToForgetWeightsTensor);
  // TF_LITE_ENSURE_OK(
  //     context, GetInputSafe(context, node,
  //                           kLstmRecurrentToForgetWeightsTensor,
  //                           &recurrent_to_forget_weights));
  TfLiteTensor* recurrent_to_cell_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToCellWeightsTensor);
  // TF_LITE_ENSURE_OK(
  //     context, GetInputSafe(context, node,
  //                           kLstmRecurrentToCellWeightsTensor,
  //                           &recurrent_to_cell_weights));
  TfLiteTensor* recurrent_to_output_weights =
      micro_context->AllocateTempInputTensor(
          node, kLstmRecurrentToOutputWeightsTensor);
  // TF_LITE_ENSURE_OK(
  //    context, GetInputSafe(context, node,
  //                          kLstmRecurrentToOutputWeightsTensor,
  //                          &recurrent_to_output_weights));

  TfLiteTensor* projection_weights = micro_context->AllocateTempInputTensor(
      node, kLstmProjectionWeightsTensor);
  // GetOptionalInputTensor(
  //  context, node, lstm::full::kLstmProjectionWeightsTensor);
  TfLiteTensor* projection_bias = micro_context->AllocateTempInputTensor(
      node, kLstmProjectionBiasTensor);
  // GetOptionalInputTensor(
  //   context, node, kLstmProjectionBiasTensor);

  IntegerLstmParameter* integer_lstm_params =
      &op_data_ex->integer_lstm_param;

  KN_PRINTX(integer_lstm_params->input_to_forget_effective_bias);
  TfLiteTensor* intermediate =
      context->GetTensor(context, node->intermediates->data[4]);
  const auto* params =
      static_cast<TfLiteAffineQuantization*>(intermediate->quantization.params);
  const int32_t hidden_zp = params->zero_point->data[0];
  if (intermediate) micro_context->DeallocateTempTfLiteTensor(intermediate);
  // Get bias and perform zero point calculation.
  // When there is layer normalization, the gate bias does not apply to matmul
  // directly:
  //      y = ln(w * x + w * r + w * c) + b.
  const bool is_layer_norm = op_data_ex->use_layer_norm;

  // Forget gate.
  TfLiteTensor* forget_gate_bias =
      is_layer_norm ? nullptr
                    : micro_context->AllocateTempInputTensor(
                          node, kLstmForgetGateBiasTensor);
  // GetInput(context, node, kLstmForgetGateBiasTensor);
  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, input_zero_point, input_to_forget_weights, forget_gate_bias,
          &(integer_lstm_params->input_to_forget_effective_bias)));

  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, output_state_zero_point, recurrent_to_forget_weights,
          nullptr, &(integer_lstm_params->recurrent_to_forget_effective_bias)));

  // Modulation gate.
  TfLiteTensor* cell_gate_bias =
      is_layer_norm ? nullptr
                    : micro_context->AllocateTempInputTensor(
                          node, kLstmCellGateBiasTensor);
  // GetInput(context, node, kLstmCellGateBiasTensor);
  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, input_zero_point, input_to_cell_weights, cell_gate_bias,
          &(integer_lstm_params->input_to_cell_effective_bias)));
  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, output_state_zero_point, recurrent_to_cell_weights, nullptr,
          &(integer_lstm_params->recurrent_to_cell_effective_bias)));

  // Output gate.
  TfLiteTensor* output_gate_bias =
      is_layer_norm ? nullptr
                    : micro_context->AllocateTempInputTensor(
                          node, kLstmOutputGateBiasTensor);
  // GetInput(context, node, kLstmOutputGateBiasTensor);
  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, input_zero_point, input_to_output_weights, output_gate_bias,
          &(integer_lstm_params->input_to_output_effective_bias)));

  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, output_state_zero_point, recurrent_to_output_weights,
          nullptr, &(integer_lstm_params->recurrent_to_output_effective_bias)));

  // Input gate. The calculation is only meaningful for non-cifg case.
  TfLiteTensor* input_gate_bias =
      is_layer_norm ? nullptr
                    : micro_context->AllocateTempInputTensor(
                          node, kLstmInputGateBiasTensor);
  // GetInput(context, node, kLstmInputGateBiasTensor);
  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, input_zero_point, input_to_input_weights, input_gate_bias,
          &(integer_lstm_params->input_to_input_effective_bias)));
  TF_LITE_ENSURE_OK(
      context,
      PrecomputeZeroPointTimesWeightWithBias(
          context, output_state_zero_point, recurrent_to_input_weights, nullptr,
          &(integer_lstm_params->recurrent_to_input_effective_bias)));

  // Projection bias. The calculation is only meaningful for with projection.
  TF_LITE_ENSURE_OK(context,
                    PrecomputeZeroPointTimesWeightWithBias(
                        context, hidden_zp, projection_weights, projection_bias,
                        &(integer_lstm_params->projection_effective_bias)));

  DEALLOC_IF_VALID(input);
  DEALLOC_IF_VALID(output_state);

  DEALLOC_IF_VALID(input_to_input_weights);
  DEALLOC_IF_VALID(input_to_forget_weights);
  DEALLOC_IF_VALID(input_to_cell_weights);
  DEALLOC_IF_VALID(input_to_output_weights);

  DEALLOC_IF_VALID(recurrent_to_input_weights);
  DEALLOC_IF_VALID(recurrent_to_forget_weights);
  DEALLOC_IF_VALID(recurrent_to_cell_weights);
  DEALLOC_IF_VALID(recurrent_to_output_weights);

  DEALLOC_IF_VALID(projection_weights);
  DEALLOC_IF_VALID(projection_bias);
  DEALLOC_IF_VALID(forget_gate_bias);

  DEALLOC_IF_VALID(cell_gate_bias);
  DEALLOC_IF_VALID(output_gate_bias);
  DEALLOC_IF_VALID(input_gate_bias);
  return kTfLiteOk;
}
#endif
TfLiteStatus ValidateTensorSizeRemap(TfLiteNode* node, TfLiteContext* context,
                                     const LstmTensors& tensors,
                                     const LstmSizeInfo& size_info) {
  // input

  OpDataLSTMEx* op_data_ex = reinterpret_cast<OpDataLSTMEx*>(node->user_data);
  GET_TENSOR_DATA_REMAP(node, context, kLstmInputToInputWeightsTensor,
                        op_data_ex->mapped_i2i_w);
  GET_TENSOR_DATA_REMAP(node, context, kLstmInputToForgetWeightsTensor,
                        op_data_ex->mapped_i2f_w);
  GET_TENSOR_DATA_REMAP(node, context, kLstmInputToCellWeightsTensor,
                        op_data_ex->mapped_i2c_w);
  GET_TENSOR_DATA_REMAP(node, context, kLstmInputToOutputWeightsTensor,
                        op_data_ex->mapped_i2o_w);

  // Input FC weights
  for (size_t i = 1; i < 5; i++) {
    TF_LITE_ENSURE_OK(
        context, ValidateWeightTensorSize(context, tensors.GetInternalTensor(i),
                                          size_info.state_dimension,
                                          size_info.input_dimension));
  }

  // recurrent
  GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToInputWeightsTensor,
                        op_data_ex->mapped_r2i_w);
  GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToForgetWeightsTensor,
                        op_data_ex->mapped_r2f_w);
  GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToCellWeightsTensor,
                        op_data_ex->mapped_r2c_w);
  GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToOutputWeightsTensor,
                        op_data_ex->mapped_r2o_w);

  // Recurrent FC weights
  for (size_t i = 5; i < 9; i++) {
    TF_LITE_ENSURE_OK(
        context, ValidateWeightTensorSize(context, tensors.GetInternalTensor(i),
                                          size_info.state_dimension,
                                          size_info.state_dimension));
  }
  // Biases
  for (size_t i = 12; i < 16; i++) {
    TF_LITE_ENSURE_OK(
        context, ValidateBiasTensorSize(context, tensors.GetInternalTensor(i),
                                        size_info.state_dimension));
  }

  // Check the shape of input state tensors.
  // These tensor may be 1D or 2D. It's fine as long as the total size is
  // correct.
  TF_LITE_ENSURE_EQ(context, NumElements(tensors.HiddenStateTensor()),
                    size_info.batch_size * size_info.state_dimension);
  TF_LITE_ENSURE_EQ(context, NumElements(tensors.CellStateTensor()),
                    size_info.batch_size * size_info.state_dimension);

  // Check the shape of output tensor against that of input tensor
  TF_LITE_ENSURE_EQ(context, tensors.OutputTensor()->dims->size, 3);
  TF_LITE_ENSURE_EQ(context,
                    tensors.GetInternalTensor(kLstmInputTensor)->dims->data[0],
                    tensors.OutputTensor()->dims->data[0]);
  TF_LITE_ENSURE_EQ(context,
                    tensors.GetInternalTensor(kLstmInputTensor)->dims->data[1],
                    tensors.OutputTensor()->dims->data[1]);
  TF_LITE_ENSURE_EQ(context, tensors.OutputTensor()->dims->data[2],
                    size_info.state_dimension);
  return kTfLiteOk;
}
TfLiteStatus UnidirectionalSequenceLstmPrepare(TfLiteContext* context,
                                               TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, node->outputs->size, 1);
  TF_LITE_ENSURE_EQ(context, node->inputs->size, 24);

  TFLITE_DCHECK(node->builtin_data != nullptr);
  TFLITE_DCHECK(node->user_data != nullptr);

  OpDataLSTMEx* op_data_ex = reinterpret_cast<OpDataLSTMEx*>(node->user_data);
  OpDataLSTM* op_data = &op_data_ex->OpLSTM;
  const auto* builtin_data =
      static_cast<TfLiteUnidirectionalSequenceLSTMParams*>(node->builtin_data);
  // All TempTfLiteTensors will be deallocated through the destructor.

#if 1  // reference
  LstmTensors lstm_tensors(context, node);
  TF_LITE_ENSURE_OK(context, lstm_tensors.ValidateTensorStatus(context));

  op_data->cell_gate_nonlinear_type = builtin_data->activation;
  op_data->size_info =
      CreateLstmSizeInfo(builtin_data->time_major,
                         lstm_tensors.GetInternalTensor(kLstmInputTensor)->dims,
                         lstm_tensors.HiddenStateTensor()->dims);
  TF_LITE_ENSURE_OK(
      context,
      ValidateTensorSizeRemap(node, context, lstm_tensors, op_data->size_info));

  // Create cell state information and gate parameters (Fully Connected and Mul)
  auto cell_state_type =
      lstm_tensors.GetInternalTensor(kLstmCellStateTensor)->type;
  if (cell_state_type == kTfLiteFloat32) {
    op_data->cell_state_info =
        CreateLstmCellStateInfoFloat(builtin_data->cell_clip);
    TF_LITE_ENSURE_OK(
        context, PrepareGateParametersFloat(context, lstm_tensors, op_data));
  } else if (cell_state_type == kTfLiteInt16) {
    op_data->cell_state_info = CreateLstmCellStateInfo(
        lstm_tensors.CellStateTensor()->params.scale, builtin_data->cell_clip);
    TF_LITE_ENSURE_OK(
        context, PrepareGateParametersInteger(context, lstm_tensors, op_data));
  } else {
    MicroPrintf(
        "Cell state type %s (%d) not supported. The quantized Unidirectional "
        "Sequence LSTM Op only support int16 cell state",
        TfLiteTypeGetName(cell_state_type), cell_state_type);
    return kTfLiteError;
  }
  // request buffers (four buffers)
  for (size_t i = 0; i < 4; i++) {
    TF_LITE_ENSURE_OK(context, context->RequestScratchBufferInArena(
                                   context,
                                   op_data->size_info.batch_size *
                                       op_data->size_info.state_dimension *
                                       TfLiteTypeGetSize(cell_state_type),
                                   &(op_data->buffer_indices[i])));
    // KN_PRINTS("scratch");
    KN_PRINTD(op_data->buffer_indices[i]);
    KN_PRINTD(op_data->size_info.batch_size *
              op_data->size_info.state_dimension *
              TfLiteTypeGetSize(cell_state_type));
  }

#else
  // LstmTensors lstm_tensors(context, node);
  // TF_LITE_ENSURE_OK(context, lstm_tensors.ValidateTensorStatus(context));
  // Create cell state information and gate parameters (Fully Connected and Mul)
  // auto cell_state_type =
  //    lstm_tensors.GetInternalTensor(kLstmCellStateTensor)->type;
  // Check we have all the inputs and outputs we need.
  bool use_layer_norm = false;
  MicroContext* micro_context = GetMicroContext(context);
  KN_PRINTD(node->inputs->size);
  if (node->inputs->size == 24) {
    TfLiteTensor* forget_layer_norm_coefficients =
        micro_context->AllocateTempInputTensor(
            node,
            kLstmForgetLayerNormCoefficientsTensor);  // GetInput(context, node,
                                                      // kInputTensor);

    // GetOptionalInputTensor(
    //  context, node, kForgetLayerNormCoefficientsTensor);
    if (forget_layer_norm_coefficients == nullptr) {
      use_layer_norm = false;
    } else {
      use_layer_norm = true;
    }
    DEALLOC_IF_VALID(forget_layer_norm_coefficients);
  } else if (node->inputs->size == 20) {
    // This is deprecated and is only kept here for backward compatibility.
    use_layer_norm = false;
  } else {
    KN_PRINTS("iKERNEL input nodes");
    MicroPrintf("The LSTM Full kernel expects 20 or 24 inputs. Got %d inputs",
                node->inputs->size);
    KN_PRINTD(node->inputs->size);
    return kTfLiteError;
  }
  KN_PRINTD(use_layer_norm);  // use less? 25 only
  KN_PRINTD(node->outputs->size);
  TF_LITE_ENSURE_EQ(context, node->outputs->size, 1);
  op_data_ex->use_layer_norm = use_layer_norm;
  KN_PRINTD(use_layer_norm);
  // Inferring batch size, number of outputs and sequence length and
  // number of cells from the input tensors.
  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kLstmInputTensor);
  const bool is_integer = input->type == kTfLiteInt8;
  TF_LITE_ENSURE(context, input->dims->size > 1);
  const auto* params =
      reinterpret_cast<TfLiteUnidirectionalSequenceLSTMParams*>(
          node->builtin_data);
  const bool time_major = params->time_major;
  KN_PRINTD(time_major);
  const int n_batch = time_major ? input->dims->data[1] : input->dims->data[0];
  KN_PRINTD(n_batch);
  const int n_input = input->dims->data[2];
  KN_PRINTD(n_input);
  const TfLiteEvalTensor* input_to_output_weights = tflite::micro::GetEvalInput(
      context, node, kLstmInputToOutputWeightsTensor);
  const int n_cell = input_to_output_weights->dims->data[0];
  KN_PRINTD(n_cell);
  KN_PRINTD(input_to_output_weights->dims->size);

  TF_LITE_ENSURE_EQ(context, input_to_output_weights->dims->size, 2);
  TF_LITE_ENSURE_EQ(context, input_to_output_weights->dims->data[1], n_input);
  const TfLiteEvalTensor* recurrent_to_output_weights =
      tflite::micro::GetEvalInput(context, node,
                                  kLstmRecurrentToOutputWeightsTensor);

  TF_LITE_ENSURE_EQ(context, recurrent_to_output_weights->dims->size, 2);
  TF_LITE_ENSURE_EQ(context, recurrent_to_output_weights->dims->data[0],
                    n_cell);
  const int n_output = recurrent_to_output_weights->dims->data[1];

  // Check that input tensor dimensions matches with each other.

  TF_LITE_ENSURE_OK(
      context, CheckInputTensorDimensions(context, node, n_input, n_output,
                                          n_cell, use_layer_norm, is_integer));

  // Get the pointer to output, output_state and cell_state buffer tensors.
  //  TfLiteEvalTensor* output =
  //      tflite::micro::GetEvalOutput(context, node,
  //      kOutputTensor);
  KN_PRINTD(node->outputs->size);
  TfLiteEvalTensor* output_state =
      tflite::micro::GetMutableEvalInput(context, node, kLstmOutputStateTensor);
  TFLITE_DCHECK(output_state != nullptr);
  TfLiteEvalTensor* cell_state =
      tflite::micro::GetMutableEvalInput(context, node, kLstmCellStateTensor);
  TFLITE_DCHECK(cell_state != nullptr);
  // Check the shape of input state tensors.
  // These tensor may be 1D or 2D. It's fine as long as the total size is
  // correct.
  TF_LITE_ENSURE_EQ(context, NumElements(output_state->dims),
                    n_batch * n_output);
  TF_LITE_ENSURE_EQ(context, NumElements(cell_state->dims), n_batch * n_cell);

  if (is_integer) {
    // = node->intermediates
    // const int num_intermediate_tensors = node->intermediates->size;
    // TF_LITE_ENSURE(context, num_intermediate_tensors == 5);
  }

  if (is_integer) {
    // Integer UnidirectionalSequenceLSTM prepare function for 8x8->16.
    // This code path needs 5 intermediate tensors per Op.
    // Populate quantization parameters.
    PopulateQuantizedLstmParams8x8_16(context, node,
                                      &op_data_ex->integer_lstm_param);
    // Allocate scratch buffer. Need 6 16bit buffer with size n_batch * n_cell
    // and 1 8bit buffer with size n_batch * n_cell. We also need 1 32 bit
    // buffer with size n_batch * n_cell.
    //
    // Handle cifg case as well, which might save one buffer.
    KN_PRINTD(node->outputs->size);
    int scratch_idx = 0;

    context->RequestScratchBufferInArena(
        context, n_batch * n_cell * sizeof(int32_t), &(scratch_idx));
    op_data_ex->scratch_tensor_index = scratch_idx;

    for (int scratch_index = 1; scratch_index < 6; ++scratch_index) {
      // node->temporaries->data[scratch_index] = op_data->scratch_tensor_index
      // + scratch_index;
      context->RequestScratchBufferInArena(
          context, n_batch * n_cell * sizeof(int32_t), &(scratch_idx));
      TFLITE_DCHECK(scratch_idx ==
                    (op_data_ex->scratch_tensor_index + scratch_index));
    }
    KN_PRINTD(node->outputs->size);
    // Populate precomputed zp * weight.
    TF_LITE_ENSURE_OK(context, PopulatePrecomputedZPTimesWeightsWithBias(
                                   context, op_data_ex, node));
    KN_PRINTD(node->outputs->size);
  }

  op_data_ex->opt_constraint = is_integer && cell_state->type == kTfLiteInt16;

  if (op_data_ex->opt_constraint) {
    // check remap
    // int32_t* p_lstm_mapped_i2c_w = (int32_t*)op_data_ex->mapped_i2c_w;

    // MicroContext* micro_context = GetMicroContext(context);

    if (!tflite::is_coeffs_mapped(context)) {
      // input

      GET_TENSOR_DATA_REMAP(node, context, kLstmInputToInputWeightsTensor,
                            op_data_ex->mapped_i2i_w);
      GET_TENSOR_DATA_REMAP(node, context, kLstmInputToForgetWeightsTensor,
                            op_data_ex->mapped_i2f_w);
      GET_TENSOR_DATA_REMAP(node, context, kLstmInputToCellWeightsTensor,
                            op_data_ex->mapped_i2c_w);
      GET_TENSOR_DATA_REMAP(node, context, kLstmInputToOutputWeightsTensor,
                            op_data_ex->mapped_i2o_w);

      // recurrent
      GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToInputWeightsTensor,
                            op_data_ex->mapped_r2i_w);
      GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToForgetWeightsTensor,
                            op_data_ex->mapped_r2f_w);
      GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToCellWeightsTensor,
                            op_data_ex->mapped_r2c_w);
      GET_TENSOR_DATA_REMAP(node, context, kLstmRecurrentToOutputWeightsTensor,
                            op_data_ex->mapped_r2o_w);

      // KN_PRINT_Q7_SIZE(p_fc_mapped_filter, map_coeff_size);
    } else {
      // p_lstm_mapped_i2c_w = (int32_t*)filter_input;  // remapping
    }
  }

#endif
  return kTfLiteOk;
}

TfLiteStatus UnidirectionalSequenceLstmEval(TfLiteContext* context,
                                            TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  const OpDataLSTMEx& op_data_ex =
      *reinterpret_cast<OpDataLSTMEx*>(node->user_data);
  const OpDataLSTM& op_data = op_data_ex.OpLSTM;
  auto kernel_content = CreateLSTMKernelContent(context, node);

  const auto activation_type =
      kernel_content.internal_tensors[kLstmInputTensor]->type;
  const auto weight_type =
      kernel_content.internal_tensors[kLstmInputToInputWeightsTensor]->type;

  KN_PRINTD(activation_type);
  KN_PRINTD(weight_type);

  switch (activation_type) {
    case kTfLiteFloat32: {
      LSTMBuffers<float> buffers =
          CreateLSTMBuffers<float>(context, op_data.buffer_indices);
      EvalLstm<float, float, float, float>(op_data, kernel_content, buffers);
      break;
    }
    case kTfLiteInt8: {
      switch (weight_type) {
        case kTfLiteInt8: {
          // 8(activation)x8(weight)->16(cell) LSTM with 32 bits bias
          LSTMBuffers<int16_t> buffers =
              CreateLSTMBuffers<int16_t>(context, op_data.buffer_indices);
          EvalLstm<int8_t, int8_t, int16_t, int32_t>(op_data, kernel_content,
                                                     buffers);
          break;
        }
        default: {
          MicroPrintf("Filter type %s (%d) not supported.",
                      TfLiteTypeGetName(weight_type), activation_type);
          return kTfLiteError;
        }
      }
      break;
    }
    case kTfLiteInt16: {
      switch (weight_type) {
        case kTfLiteInt8: {
          // 16(activation)x8(weight)->16(cell) LSTM with 64 bits bias
          LSTMBuffers<int16_t> buffers =
              CreateLSTMBuffers<int16_t>(context, op_data.buffer_indices);
          EvalLstm<int16_t, int8_t, int16_t, int64_t>(op_data, kernel_content,
                                                      buffers);
          break;
        }
        default: {
          MicroPrintf("Filter type %s (%d) not supported.",
                      TfLiteTypeGetName(weight_type), weight_type);
          return kTfLiteError;
        }
      }
      break;
    }
    default: {
      MicroPrintf("Input type %s (%d) not supported.",
                  TfLiteTypeGetName(activation_type), activation_type);
      return kTfLiteError;
    }
  }
  return kTfLiteOk;
}

}  // namespace

TFLMRegistration Register_UNIDIRECTIONAL_SEQUENCE_LSTM() {
  return tflite::micro::RegisterOp(UnidirectionalSequenceLstmInit,
                                   UnidirectionalSequenceLstmPrepare,
                                   UnidirectionalSequenceLstmEval);
}
}  // namespace tflite
