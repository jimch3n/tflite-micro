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


#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
#ifndef DEALLOC_IF_VALID
#define DEALLOC_IF_VALID(x)                              \
  do {                                                   \
    if (x) micro_context->DeallocateTempTfLiteTensor(x); \
  } while (0)
#endif

#define GET_TENSOR_DATA_REMAP(NODE, CONTEXT, KINDEX, D_OUT, M, N)            \
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
    M = GetTensorShape(w).Dims(0);                                           \
    N = GetTensorShape(w).Dims(1);                                           \
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
  return context->AllocatePersistentBuffer(context, sizeof(OpDataLSTM));
}

TfLiteStatus ValidateTensorSize(TfLiteNode* node, TfLiteContext* context,
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
TfLiteStatus UnidirectionalSequenceLstmPrepare(TfLiteContext* context,
                                               TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, node->outputs->size, 1);
  TF_LITE_ENSURE_EQ(context, node->inputs->size, 24);

  TFLITE_DCHECK(node->builtin_data != nullptr);
  TFLITE_DCHECK(node->user_data != nullptr);

  OpDataLSTM* op_data = reinterpret_cast<OpDataLSTM*>(node->user_data);

  const auto* builtin_data =
      static_cast<TfLiteUnidirectionalSequenceLSTMParams*>(node->builtin_data);
  // All TempTfLiteTensors will be deallocated through the destructor.

  LstmTensors lstm_tensors(context, node);
  TF_LITE_ENSURE_OK(context, lstm_tensors.ValidateTensorStatus(context));

  op_data->cell_gate_nonlinear_type = builtin_data->activation;
  op_data->size_info =
      CreateLstmSizeInfo(builtin_data->time_major,
                         lstm_tensors.GetInternalTensor(kLstmInputTensor)->dims,
                         lstm_tensors.HiddenStateTensor()->dims);
  TF_LITE_ENSURE_OK(context, ValidateTensorSize(node, context, lstm_tensors,
                                                op_data->size_info));

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
    TF_LITE_ENSURE_OK(context, PrepareGateParametersInteger(
                                   context, node, lstm_tensors, op_data));
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

  }


  return kTfLiteOk;
}

TfLiteStatus UnidirectionalSequenceLstmEval(TfLiteContext* context,
                                            TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);

  const OpDataLSTM& op_data = *reinterpret_cast<OpDataLSTM*>(node->user_data);

  auto kernel_content = CreateLSTMKernelContent(context, node);

  const auto activation_type =
      kernel_content.internal_tensors[kLstmInputTensor]->type;
  const auto weight_type =
      kernel_content.internal_tensors[kLstmInputToInputWeightsTensor]->type;

  KN_PRINTD(activation_type);
  KN_PRINTD(weight_type);
  KN_PRINTX(&op_data);
  KN_PRINTX(&op_data.input_gate_parameters.input_fc_params);
  KN_PRINTX(op_data.input_gate_parameters.input_fc_params.mapped_filter);
  KN_PRINTD(sizeof(op_data.input_gate_parameters.input_fc_params));
  switch (activation_type) {
#if !defined(DMX1A_LSTM_OPT) && !defined(HMD1A_LSTM_OPT) // temp disable float type
    case kTfLiteFloat32: {
      LSTMBuffers<float> buffers =
          CreateLSTMBuffers<float>(context, op_data.buffer_indices);
      EvalLstm<float, float, float, float>(op_data, kernel_content, buffers);
      break;
    }
#endif
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
#if !defined(DMX1A_LSTM_OPT) && !defined(HMD1A_LSTM_OPT)
    case kTfLiteInt16: {
      switch (weight_type) {
        case kTfLiteInt8: {
          // 16(activation)x8(weight)->16(cell) LSTM with 64 bits bias
          LSTMBuffers<int16_t> buffers =
              CreateLSTMBuffers<int16_t>(context, op_data.buffer_indices);
          EvalLstm<int16_t, int8_t, int16_t, int64_t>(op_data,
                                                      kernel_content, buffers);
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
#endif
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
