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
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/ia8201/debug_helper.h"

#include "tensorflow/lite/micro/kernels/ia8201/lstm_eval.h"
#include "tensorflow/lite/micro/kernels/ia8201/fully_connected.h"
#include "tensorflow/lite/micro/micro_utils.h"
namespace tflite {

// Deduce the size information (Batch (B), Time Steps (T), Input dimension (I),
// State dimension (S)) that defines the LSTM using the input and hidden state
// tensor
LstmSizeInfo CreateLstmSizeInfo(
    const bool time_major, const TfLiteIntArray* input_tensor_shape,
    const TfLiteIntArray* hidden_state_tensor_shape) {
  LstmSizeInfo size_info;
  size_info.time_major = time_major;
  size_info.batch_size =
      time_major ? input_tensor_shape->data[1] : input_tensor_shape->data[0];
  size_info.time_steps =
      time_major ? input_tensor_shape->data[0] : input_tensor_shape->data[1];
  size_info.input_dimension = input_tensor_shape->data[2];
  size_info.state_dimension = hidden_state_tensor_shape->data[1];
  return size_info;
}

TfLiteStatus ValidateWeightTensorSize(TfLiteContext* context,
                                      const TfLiteTensor* tensor, int dim1_size,
                                      int dim2_size) {
  TF_LITE_ENSURE_EQ(context, tensor->dims->size, 2);
  TF_LITE_ENSURE_EQ(context, tensor->dims->data[0], dim1_size);
  TF_LITE_ENSURE_EQ(context, tensor->dims->data[1], dim2_size);
  return kTfLiteOk;
}

TfLiteStatus ValidateBiasTensorSize(TfLiteContext* context,
                                    const TfLiteTensor* tensor, int size) {
  TF_LITE_ENSURE_EQ(context, tensor->dims->size, 1);
  TF_LITE_ENSURE_EQ(context, tensor->dims->data[0], size);
  return kTfLiteOk;
}

// Go through every tensors and make sure their shape match the kernel
// configuration
TfLiteStatus ValidateTensorSize(TfLiteContext* context,
                                const LstmTensors& tensors,
                                const LstmSizeInfo& size_info) {
  // Input FC weights
  for (size_t i = 1; i < 5; i++) {
    TF_LITE_ENSURE_OK(
        context, ValidateWeightTensorSize(context, tensors.GetInternalTensor(i),
                                          size_info.state_dimension,
                                          size_info.input_dimension));
  }
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

// Wrapper function to create gate parameters for the four internal LSTM gates
TfLiteStatus CreateGateParams(
    TfLiteContext* context,
    /*Input tensors*/
    TfLiteNode* node, const LstmTensors& lstm_tensors,
    const TfLiteTensor* input, const TfLiteTensor* input_weight,
    const TfLiteTensor* input_bias,
    /*Hidden state tensors*/
    const TfLiteTensor* hidden_state, const TfLiteTensor* hidden_state_weight,
    const TfLiteTensor* hidden_state_bias,
    /*Scale of the fc output (input to non-linear activation)*/
    const float nonlinear_activation_input_scale, const TfLiteType cell_type,
    tflite::GateParameters& gate_params, int opt_constraint = 0) {
  // A temp tflite tensor to represent the output of fc operation. Only the data
  // type and quantization parameters are set since it is only used for
  // parameter calculations
  TfLiteTensor fc_output_temp;
  fc_output_temp.type = cell_type;
  fc_output_temp.params.scale = nonlinear_activation_input_scale;
  fc_output_temp.params.zero_point = 0;  // symmetrical quantized

  // A temp fc opdata to reuse the helper function on creating fc parameters
  tflite::OpDataFullyConnectedEx fc_data_temp_ex;

  tflite::OpDataFullyConnected* fc_data_temp = &fc_data_temp_ex.FcOp;

  // TODO(b/265853320): due to the lack of precision for the float scale,
  // scale_diff / output_scale <= 0.02 (potentially requires 1e-8 precision) can
  // not be satisified for the bias. Here we rely on the correctiveness of the
  // conversion process (set input_bias=nullptr to avoid checking) for
  // tensor scales
  //
  TF_LITE_ENSURE_STATUS(CalculateOpDataFullyConnected(
      context, kTfLiteActNone, input->type, input, input_weight,
      /*input_bias=*/nullptr, &fc_output_temp, &fc_data_temp_ex));
  gate_params.input_fc_params =
      FullyConnectedParamsQuantized(fc_data_temp_ex.FcOp);

#if 1  // defined(DMX1A_LSTM_OPT)
  if (opt_constraint) {
    int32_t* p_input_mapped_filter = nullptr;

    RuntimeShape input_weight_shape = GetTensorShape(input_weight);
    int n_input = input_weight_shape.Dims(1);
    int m_input = input_weight_shape.Dims(0);
    KN_PRINTD(m_input);
    KN_PRINTD(n_input);

    int input_idx = lstm_tensors.GetTensorIndex(input_weight);
    const int32_t input_coeff_size =
        tflite::FullyConnectedMap8bitCoeffs(NULL, NULL, m_input, n_input);

    const TfLiteEvalTensor* evalInputTensor =
        tflite::micro::GetEvalInput(context, node, input_idx);
    const int8_t* input_w =
        tflite::micro::GetTensorData<int8_t>(evalInputTensor);

    // bias if avaible;
    int inputb_idx = lstm_tensors.GetTensorIndex(input_bias);
    KN_PRINTD(inputb_idx);
    const TfLiteEvalTensor* evalBiasTensor =
        tflite::micro::GetEvalInput(context, node, inputb_idx);
    const int32_t* pB = tflite::micro::GetTensorData<int32_t>(evalBiasTensor);

    if (!tflite::is_coeffs_mapped(
            context))  // get  tflite::is_coeffs_mapped(context) == true
    {
      // allocate new persist tensor data
      p_input_mapped_filter = (int32_t*)context->AllocatePersistentBuffer(
          context, input_coeff_size);
      if (p_input_mapped_filter) {
        tflite::FullyConnectedMap8bitCoeffs((int8_t*)p_input_mapped_filter,
                                            (int8_t*)input_w, m_input, n_input);
      }

      KN_PRINT_Q7_SIZE_ATMOST(p_input_mapped_filter, m_input * n_input, 64);

    } else {
      // input  w has remapped
      p_input_mapped_filter = (int32_t*)input_w;
    }
    // KN_PRINT_Q7_SIZE(p_fc_mapped_filter, map_coeff_size);
    uint8_t offsetInput = (-fc_data_temp->input_zero_point) & 0xff;

    fc_data_temp_ex.input_offset_int8 = (offsetInput << 24) |
                                        (offsetInput << 16) |
                                        (offsetInput << 8) | offsetInput;

    KN_PRINTX(fc_data_temp_ex.input_offset_int8);
    if (fc_data_temp_ex.input_offset_int8 == 0x80808080 ||
        fc_data_temp_ex.input_offset_int8 == 0x0) {
      fc_data_temp_ex.opt_constraint = 2;  // faster without input offset
      fc_data_temp_ex.inputOffsetWithW = nullptr;
    } else {
      fc_data_temp_ex.opt_constraint = 1;  // kept 1 and prevent no clean
      int inFCMA8 = (((m_input + 7) >> 3) << 3);
      int32_t* inputOffsetWithW = (int32_t*)context->AllocatePersistentBuffer(
          context, inFCMA8 * sizeof(int32_t));
      fc_data_temp_ex.inputOffsetWithW = inputOffsetWithW;

      MVMInputOffsetPrepare(p_input_mapped_filter, inputOffsetWithW, m_input,
                            n_input, fc_data_temp_ex.input_offset_int8);
      KN_PRINT_Q31_SIZE(fc_data_temp_ex.inputOffsetWithW, inFCMA8);
    }
    if (input_bias) {
      size_t bias_size = ElementCount(*evalBiasTensor->dims);
      // Allocate tensor weight
      AScalar* bias_aflt = (AScalar*)context->AllocatePersistentBuffer(
          context, sizeof(AScalar) * bias_size);

      tflite::ConvertQ31ToAfloat(pB, (AScalar*)bias_aflt, bias_size, 17);
      // KN_PRINT_AFLOAT(bias_aflt, bias_size);
      fc_data_temp_ex.bias_aflt = bias_aflt;
    } else {
      fc_data_temp_ex.bias_aflt = NULL;
    }

    tflite::ConvertQ31ToAfloat(fc_data_temp->output_zero_point,
                               fc_data_temp_ex.outputOffset, 17);

    KN_PRINTAFLT(fc_data_temp_ex.outputOffset);
    fc_data_temp_ex.mapped_filter = p_input_mapped_filter;

  }  // opt_constraint
#endif
  FullyConnectedParamsQuantized(fc_data_temp_ex, &gate_params.input_fc_params);

  double real_multiplier = 0.0;
  GetQuantizedConvolutionMultipler(context, input, input_weight, nullptr,
                                   &fc_output_temp, &real_multiplier);
  TF_LITE_ENSURE_STATUS(CalculateOpDataFullyConnected(
      context, kTfLiteActNone, hidden_state->type, hidden_state,
      hidden_state_weight, hidden_state_bias, &fc_output_temp,
      &fc_data_temp_ex));
  gate_params.recurrent_fc_params =
      FullyConnectedParamsQuantized(fc_data_temp_ex.FcOp);
#if 1  // defined(DMX1A_LSTM_OPT)
  if (opt_constraint) {
    int32_t* p_hidden_mapped_filter = nullptr;
    RuntimeShape hidden_state_weight_shape =
        GetTensorShape(hidden_state_weight);

    int n_hidden = hidden_state_weight_shape.Dims(1);
    int m_hidden = hidden_state_weight_shape.Dims(0);

    KN_PRINTD(n_hidden);
    KN_PRINTD(m_hidden);

    int hidden_idx = lstm_tensors.GetTensorIndex(hidden_state_weight);

    const int32_t hidden_coeff_size =
        tflite::FullyConnectedMap8bitCoeffs(NULL, NULL, m_hidden, n_hidden);
    const TfLiteEvalTensor* evalHiddenTensor =
        tflite::micro::GetEvalInput(context, node, hidden_idx);

    const int8_t* hidden_w =
        tflite::micro::GetTensorData<int8_t>(evalHiddenTensor);

    int hiddenb_idx = lstm_tensors.GetTensorIndex(hidden_state_bias);
    KN_PRINTD(hiddenb_idx);
    const TfLiteEvalTensor* evalHBiasTensor =
        tflite::micro::GetEvalInput(context, node, hiddenb_idx);
    KN_PRINTX(evalHBiasTensor);
    const int32_t* pB = nullptr;
    if (evalHBiasTensor)
      pB = tflite::micro::GetTensorData<int32_t>(evalHBiasTensor);
    KN_PRINTX(pB);
    // KN_PRINT_Q31_SIZE(pB, m_hidden);
    if (!tflite::is_coeffs_mapped(
            context))  // get  tflite::is_coeffs_mapped(context) == true
    {
      KN_PRINTD(hidden_coeff_size);
      p_hidden_mapped_filter = (int32_t*)context->AllocatePersistentBuffer(
          context, hidden_coeff_size);
      KN_PRINTX(p_hidden_mapped_filter);
      KN_PRINTX(hidden_w);
      if (p_hidden_mapped_filter)

      {
        tflite::FullyConnectedMap8bitCoeffs((int8_t*)p_hidden_mapped_filter,
                                            (int8_t*)hidden_w, m_hidden,
                                            n_hidden);
        KN_PRINT_Q7_SIZE_ATMOST(p_hidden_mapped_filter, m_hidden * n_hidden,
                                64);
      }
    } else {
      // input  w has remapped
      p_hidden_mapped_filter = (int32_t*)hidden_w;
    }

    KN_PRINTX(fc_data_temp->input_zero_point);
    uint8_t offsetInput = (-fc_data_temp->input_zero_point) & 0xff;
    // uint32_t offsetVR=offsetInput;
    fc_data_temp_ex.input_offset_int8 = (offsetInput << 24) |
                                        (offsetInput << 16) |
                                        (offsetInput << 8) | offsetInput;
    KN_PRINTX(fc_data_temp_ex.input_offset_int8);

    // data_ex->mapped_filter = (int32_t *)p_input_mapped_filter;
    if (fc_data_temp_ex.input_offset_int8 == 0x80808080 ||
        fc_data_temp_ex.input_offset_int8 == 0x0) {
      fc_data_temp_ex.opt_constraint = 2;  // faster without input offset
      fc_data_temp_ex.inputOffsetWithW = nullptr;
    } else {
      fc_data_temp_ex.opt_constraint = 1;  // kept 1 and prevent no clean
      int inFCMA8 = (((m_hidden + 7) >> 3) << 3);
      int32_t* inputOffsetWithW = (int32_t*)context->AllocatePersistentBuffer(
          context, inFCMA8 * sizeof(int32_t));
      fc_data_temp_ex.inputOffsetWithW = inputOffsetWithW;

      MVMInputOffsetPrepare(p_hidden_mapped_filter, inputOffsetWithW, m_hidden,
                            n_hidden, fc_data_temp_ex.input_offset_int8);
      KN_PRINT_Q31_SIZE(fc_data_temp_ex.inputOffsetWithW, inFCMA8);
    }
    if (hidden_state_bias) {
      size_t bias_size = ElementCount(*evalHBiasTensor->dims);
      // Allocate tensor weight
      AScalar* bias_aflt = (AScalar*)context->AllocatePersistentBuffer(
          context, sizeof(AScalar) * bias_size);

      tflite::ConvertQ31ToAfloat(pB, (AScalar*)bias_aflt, bias_size, 17);
      fc_data_temp_ex.bias_aflt = bias_aflt;
      KN_PRINT_AFLOAT(bias_aflt, bias_size);
    } else {
      fc_data_temp_ex.bias_aflt = NULL;
    }
    tflite::ConvertQ31ToAfloat(fc_data_temp->output_zero_point,
                               fc_data_temp_ex.outputOffset, 17);

    fc_data_temp_ex.mapped_filter = p_hidden_mapped_filter;

  }  // if (opt_constraint)
#endif
  FullyConnectedParamsQuantized(fc_data_temp_ex,
                                &gate_params.recurrent_fc_params);
  return kTfLiteOk;
}

// Create parameters for element wise multiplication that happens in a) cell
// state update ; b) hidden state update
// Note that all the output of gates are symmetrically quantized so only scales
// are required for input. However, during the hidden state update phase, the
// output is the updated hidden state, which is asymmetrically quantized. Thus
// output may require zero point
tflite::ArithmeticParams CreateInterGateMulParams(const float input1_scale,
                                                  const float input2_scale,
                                                  const float output_scale,
                                                  const TfLiteType output_type,
                                                  const int output_zp) {
  tflite::ArithmeticParams op_params = {};
  if (output_type == kTfLiteInt16) {
    op_params.quantized_activation_min = std::numeric_limits<int16_t>::min();
    op_params.quantized_activation_max = std::numeric_limits<int16_t>::max();
  } else if (output_type == kTfLiteInt8) {
    op_params.quantized_activation_min = std::numeric_limits<int8_t>::min();
    op_params.quantized_activation_max = std::numeric_limits<int8_t>::max();
  }

  op_params.input1_offset = 0;  // symmetric
  op_params.input2_offset = 0;  // symmetric
  op_params.output_offset = output_zp;

  const double input_product_scale =
      static_cast<double>(input1_scale) * static_cast<double>(input2_scale);
  double effective_scale =
      input_product_scale / static_cast<double>(output_scale);

  QuantizeMultiplier(effective_scale, &op_params.output_multiplier,
                     &op_params.output_shift);

  // REMAP here ?
  return op_params;
}

// Create the additional information about the cell state, which include:
// cell_state_scale_power: used in integer nonlinear function (e.g., tanh)
// quantized_cell_clip: quantized cell clip range
CellStateInfo CreateLstmCellStateInfo(const float cell_state_scale,
                                      const float cell_clip) {
  CellStateInfo cell_state_info;
  // cell_state_scale_power: 2^-cell_state_scale_power = cell state scale
  int buffer;
  tflite::CheckedLog2(cell_state_scale, &buffer);
  cell_state_info.cell_state_scale_power = buffer;
  // Cell state specifics
  cell_state_info.cell_clip = cell_clip;
  cell_state_info.quantized_cell_clip = static_cast<int16_t>(
      std::min(std::max(static_cast<double>(cell_clip) /
                            static_cast<double>(cell_state_scale),
                        -32768.0),
               32767.0));

  return cell_state_info;
}

CellStateInfo CreateLstmCellStateInfoFloat(const float cell_clip) {
  CellStateInfo cell_state_info;
  cell_state_info.cell_clip = cell_clip;
  cell_state_info.cell_state_scale_power = 0;  // no quantization
  cell_state_info.quantized_cell_clip = 0;     // no quantization
  return cell_state_info;
}

tflite::FullyConnectedParams CreateFCParamsFloat() {
  FullyConnectedParams op_params;
  CalculateActivationRange(kTfLiteActNone, &op_params.float_activation_min,
                           &op_params.float_activation_max);
  return op_params;
}

tflite::GateParameters CreateGateParamsFloat() {
  tflite::GateParameters gate_params = {};
  gate_params.input_fc_params = CreateFCParamsFloat();
  gate_params.recurrent_fc_params = CreateFCParamsFloat();
  return gate_params;
}

tflite::ArithmeticParams CreateInterGateMulParamsFloat() {
  tflite::ArithmeticParams op_params = {};
  CalculateActivationRange(kTfLiteActNone, &op_params.float_activation_min,
                           &op_params.float_activation_max);
  return op_params;
}

TfLiteStatus PrepareGateParametersFloat(TfLiteContext* context,
                                        const LstmTensors& lstm_tensors,
                                        OpDataLSTM* op_data_lstm) {
  // Gate Parameters
  op_data_lstm->forget_gate_parameters = CreateGateParamsFloat();
  op_data_lstm->input_gate_parameters = CreateGateParamsFloat();
  op_data_lstm->cell_gate_parameters = CreateGateParamsFloat();
  op_data_lstm->output_gate_parameters = CreateGateParamsFloat();
  // Inter gate multiplication parameters
  op_data_lstm->inter_gate_parameters.forget_cell_mul_params =
      CreateInterGateMulParamsFloat();
  op_data_lstm->inter_gate_parameters.input_mul_params =
      CreateInterGateMulParamsFloat();
  op_data_lstm->inter_gate_parameters.output_mul_params =
      CreateInterGateMulParamsFloat();
  return kTfLiteOk;
}

TfLiteStatus PrepareGateParametersInteger(TfLiteContext* context,
                                          TfLiteNode* node,
                                          const LstmTensors& lstm_tensors,
                                          OpDataLSTM* op_data_lstm) {
  // check opt_constraint input type is 8bit, output 1s 0but

#if defined(DMX1A_LSTM_OPT) || defined(HMD1A_LSTM_OPT)
  auto kernel_content = CreateLSTMKernelContent(context, node);
  const auto activation_type =
      kernel_content.internal_tensors[kLstmInputTensor]->type;
  KN_PRINTD(activation_type);
  const auto weight_type =
      kernel_content.internal_tensors[kLstmInputToInputWeightsTensor]->type;
  KN_PRINTD(weight_type);
  int opt_constraint =
      activation_type == kTfLiteInt8 && weight_type == kTfLiteInt8;
#else
  int opt_constraint = 0;
#endif
  float nonlinear_input_scale = 0.000244140625;  // 2^-12 Q3.12 -> Q0.15

  TF_LITE_ENSURE_OK(
      context,
      CreateGateParams(
          context, node, lstm_tensors,
          lstm_tensors.GetInternalTensor(kLstmInputTensor),
          lstm_tensors.GetInternalTensor(kLstmInputToForgetWeightsTensor),
          lstm_tensors.GetInternalTensor(kLstmForgetGateBiasTensor),
          lstm_tensors.GetInternalTensor(kLstmOutputStateTensor),
          lstm_tensors.GetInternalTensor(kLstmRecurrentToForgetWeightsTensor),
          /*hidden_state_bias=*/nullptr, nonlinear_input_scale, kTfLiteInt16,
          op_data_lstm->forget_gate_parameters, opt_constraint));

  TF_LITE_ENSURE_OK(
      context,
      CreateGateParams(
          context, node, lstm_tensors,
          lstm_tensors.GetInternalTensor(kLstmInputTensor),
          lstm_tensors.GetInternalTensor(kLstmInputToInputWeightsTensor),
          lstm_tensors.GetInternalTensor(kLstmInputGateBiasTensor),
          lstm_tensors.GetInternalTensor(kLstmOutputStateTensor),
          lstm_tensors.GetInternalTensor(kLstmRecurrentToInputWeightsTensor),
          /*hidden_state_bias=*/nullptr, nonlinear_input_scale, kTfLiteInt16,
          op_data_lstm->input_gate_parameters, opt_constraint));

  TF_LITE_ENSURE_OK(
      context,
      CreateGateParams(
          context, node, lstm_tensors,
          lstm_tensors.GetInternalTensor(kLstmInputTensor),
          lstm_tensors.GetInternalTensor(kLstmInputToCellWeightsTensor),
          lstm_tensors.GetInternalTensor(kLstmCellGateBiasTensor),
          lstm_tensors.GetInternalTensor(kLstmOutputStateTensor),
          lstm_tensors.GetInternalTensor(kLstmRecurrentToCellWeightsTensor),
          /*hidden_state_bias=*/nullptr, nonlinear_input_scale, kTfLiteInt16,
          op_data_lstm->cell_gate_parameters, opt_constraint));

  TF_LITE_ENSURE_OK(
      context,
      CreateGateParams(
          context, node, lstm_tensors,
          lstm_tensors.GetInternalTensor(kLstmInputTensor),
          lstm_tensors.GetInternalTensor(kLstmInputToOutputWeightsTensor),
          lstm_tensors.GetInternalTensor(kLstmOutputGateBiasTensor),
          lstm_tensors.GetInternalTensor(kLstmOutputStateTensor),
          lstm_tensors.GetInternalTensor(kLstmRecurrentToOutputWeightsTensor),
          /*hidden_state_bias=*/nullptr, nonlinear_input_scale, kTfLiteInt16,
          op_data_lstm->output_gate_parameters, opt_constraint));
  // do remake here ?

  // Inter gate multiplication parameters
  float nonlinear_output_scale = 0.000030517578125;  // 2^-15 Q3.12 -> Q0.15
  float cell_state_scale = lstm_tensors.CellStateTensor()->params.scale;
  // forget gate output (nonlinear output) x cell state -> cell state
  op_data_lstm->inter_gate_parameters.forget_cell_mul_params =
      CreateInterGateMulParams(nonlinear_output_scale, cell_state_scale,
                               cell_state_scale, kTfLiteInt16);
  // input gate output x cell gate output -> cell state
  op_data_lstm->inter_gate_parameters.input_mul_params =
      CreateInterGateMulParams(nonlinear_output_scale, nonlinear_output_scale,
                               cell_state_scale, kTfLiteInt16);
  // tanh output x output gate output -> hidden state (potentially asymmetric)
  op_data_lstm->inter_gate_parameters.output_mul_params =
      CreateInterGateMulParams(
          nonlinear_output_scale, nonlinear_output_scale,
          lstm_tensors.HiddenStateTensor()->params.scale,
          lstm_tensors.HiddenStateTensor()->type,
          lstm_tensors.HiddenStateTensor()->params.zero_point);

  return kTfLiteOk;
}

LSTMKernelContents CreateLSTMKernelContent(TfLiteContext* context,
                                           TfLiteNode* node) {
  LSTMKernelContents kernel_content;
  // Point to correct tensors
  // KN_PRINTX(context);  KN_PRINTX(node);
  for (size_t i = 0; i < 24; i++) {
    // KN_PRINTD(i);
    kernel_content.internal_tensors[i] =
        tflite::micro::GetMutableEvalInput(context, node, i);
  }
  // Output tensor
  kernel_content.output_tensor = tflite::micro::GetEvalOutput(context, node, 0);
  return kernel_content;
}

}  // namespace tflite
