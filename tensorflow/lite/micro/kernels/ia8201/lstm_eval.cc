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

#include "tensorflow/lite/micro/kernels/ia8201/lstm_eval.h"

#include <limits>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor_utils.h"
#include "tensorflow/lite/kernels/internal/reference/fully_connected.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/fully_connected.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/logistic.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/mul.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/tanh.h"
#include "tensorflow/lite/kernels/internal/reference/logistic.h"
#include "tensorflow/lite/kernels/internal/reference/mul.h"
#include "tensorflow/lite/kernels/internal/reference/portable_tensor_utils_impl.h"
#include "tensorflow/lite/kernels/internal/reference/tanh.h"
#include "tensorflow/lite/micro/ia8201/debug_helper.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
namespace tflite {

LstmTensors::LstmTensors(TfLiteContext* context, TfLiteNode* node) {
  micro_context_ = GetMicroContext(context);
  // 24 internal tensors. see lstm_shared.h for tensor names
  for (size_t i = 0; i < 24; i++) {
    internal_tensors_[i] = micro_context_->AllocateTempInputTensor(node, i);
  }
  output_tensor_ =
      micro_context_->AllocateTempOutputTensor(node, kLstmOutputTensor);
}

LstmTensors::~LstmTensors() {
  for (size_t i = 0; i < 24; i++) {
    if (internal_tensors_[i] != nullptr) {
      micro_context_->DeallocateTempTfLiteTensor(internal_tensors_[i]);
    }
  }
  micro_context_->DeallocateTempTfLiteTensor(output_tensor_);
}

// Verify the LSTM internal tensor properties (e.g., type checks)
// Input/output/states/fc weights tensors are required for kernel evaulation.
// The state tensors should be variables. Variants of the standard LSTM
// are not supported here, therefore their corresponding tensors should be
// invalid
TfLiteStatus LstmTensors::ValidateTensorStatus(TfLiteContext* context) const {
  // Verify certain tensor properties
  // input tensor
  TF_LITE_ENSURE(context, internal_tensors_[kLstmInputTensor] != nullptr);
  // hidden state
  TF_LITE_ENSURE(context, internal_tensors_[kLstmOutputStateTensor] != nullptr);
  TF_LITE_ENSURE(context,
                 internal_tensors_[kLstmOutputStateTensor]->is_variable);
  // hidden state becomes input so they must have the same type
  TF_LITE_ENSURE_EQ(context, internal_tensors_[kLstmOutputStateTensor]->type,
                    internal_tensors_[kLstmInputTensor]->type);
  // cell state
  TF_LITE_ENSURE(context, internal_tensors_[kLstmCellStateTensor] != nullptr);
  TF_LITE_ENSURE(context, internal_tensors_[kLstmCellStateTensor]->is_variable);
  // output
  TF_LITE_ENSURE(context, output_tensor_ != nullptr);
  // output type is the same as the input type (activations)
  TF_LITE_ENSURE_EQ(context, output_tensor_->type,
                    internal_tensors_[kLstmInputTensor]->type);

  // weight tensors (1-9, see lstm_shared for index definition)
  const auto weight_type =
      internal_tensors_[kLstmInputToForgetWeightsTensor]->type;
  for (size_t i = 1; i < 9; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] != nullptr);
    TF_LITE_ENSURE_EQ(context, internal_tensors_[i]->type, weight_type);
  }

  // bias tensors (12-15, see lstm_shared for index definition)
  const auto bias_type = internal_tensors_[kLstmForgetGateBiasTensor]->type;
  for (size_t i = 12; i < 16; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] != nullptr);
    TF_LITE_ENSURE_EQ(context, internal_tensors_[i]->type, bias_type);
  }
  // Tensors from LSTM variants are invalid
  // No peephole
  for (size_t i = 9; i < 12; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] == nullptr);
  }
  // No projection
  for (size_t i = 16; i < 18; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] == nullptr);
  }
  // No internal layer norm
  for (size_t i = 20; i < 24; i++) {
    TF_LITE_ENSURE(context, internal_tensors_[i] == nullptr);
  }
  return kTfLiteOk;
}
namespace lstm_internal {

#if !(defined(HIFI3) || defined(HIFI4) || defined(HIFI5))
const int32_t kInt16Max = std::numeric_limits<int16_t>::max();
const int32_t kInt16Min = std::numeric_limits<int16_t>::min();
#endif

void AddElementWise(const int16_t* input_1, const int16_t* input_2, int n_batch,
                    int n_input, int16_t* output) {
#if !(defined(HIFI3) || defined(HIFI4) || defined(HIFI5))
  for (int batch = 0; batch < n_batch; ++batch) {
    for (int i = 0; i < n_input; ++i) {
      const int index = batch * n_input + i;
      int32_t sum = input_1[index] + input_2[index];
      const int32_t sum_clamped = std::min(kInt16Max, std::max(kInt16Min, sum));
      output[index] = static_cast<int16_t>(sum_clamped);
    }
  }
#else
  xa_nn_elm_add_16x16_16(output, input_1, input_2, n_batch * n_input);
#endif
}

void AddElementWise(const float* input_1, const float* input_2, int n_batch,
                    int n_input, float* output) {
  for (int batch = 0; batch < n_batch; ++batch) {
    for (int i = 0; i < n_input; ++i) {
      const int index = batch * n_input + i;
      output[index] = input_1[index] + input_2[index];
    }
  }
}

#if defined(DMX1A_LSTM_OPT)

int MVMQuantizedInt8x8_16(int32_t* x, const int32_t* A, const int32_t* bias,
                          int16_t* output, int m, int n,
                          const int32_t outMultipler,
                          //  const int32_t *inputOffsetWithW,  // xor 128
                          const int32_t shift, int32_t outOffset, int signs) {
  int16_t* pY = output;

  const int32_t* pA = A;
  const int32_t* pX;
  const int32_t* pB = (const int32_t*)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 3);  // block 16
  int loopLimRow = ((m + 7) >> 3);         // group 8 alignment
  int processLastLoop = ((m & 7) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x4_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }
  vr128 VR_A;
  vr128 VR_x;
  vr128 VR_y;
  // vr128 VR_inputOffset;
  xtbool2 signSpec = int_to_xt_bool2(signs);

  vr128 VR_outMult;
  // vr128 VR_outOffset;
  vr128 VR_b0 = vseta_vr(kConstTable_Zero, 0, 0);
  ulsr128 UR_out = align_16x4_store(pY);
  AScalar outMultiplerFr32;

  ConvertQ31ToAfloat(outMultipler, outMultiplerFr32, shift);

  replicate_ar(VR_outMult, 0xf, outMultiplerFr32.fr);
  // replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);
  // replicate_ar(VR_inputOffset, 0xf, input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    pX = x;
    ulsr128 UR_A = align_32x4_load(pA);
    ulsr128 UR_x = align_32x4_load(pX);
    ulsr128 UR_b;
    load_32x4_vr_a(VR_A, UR_A, pA);

    // if (pB)
    {
      UR_b = align_32x4_load(pB);
      load_32x4_vr_a(VR_y, UR_b, pB);  // suppose not grate than 16 bit

      VR_y = shift32_arith(VR_y, 2, 0);
      load_32x4_vr_a(VR_b0, UR_b, pB);

      VR_b0 = shift32_arith(VR_b0, 2, 0);
    }
    // VR_y = vexp_adji(VR_b0, 0); //vseta_vr(0, 0, 0);
    mov_AccExtend_vr(VR_b0);

    for (int j = 0; j < loopLimCol; j++) {
      load_32x4_vr_a(VR_x, UR_x, pX);
      // VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(0);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 3); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      // VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // vr128 VR_q7_out;

      vr128 VR_out;

      // VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store_16x4_vr_a(VR_out, UR_out, pY);

      // if (pB) {
      //  load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      // }

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);

      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      store_16x4_vr_a(VR_out, UR_out, pY);
      flush_16x4(UR_out, pY);
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // vr128 VR_q7_out;

      vr128 VR_out;

      // VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      for (int32_t j = 0; j < (m & 0x7) && j < 4; j++) {
        store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }

      if ((m & 7) <= 4) {
        break;
      }
      VR_y = mov_vr_AccExtend();

      // if (pB) {
      //  load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      //}

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      for (int32_t j = 4; j < (m & 0x7) && j < 8; j++) {
        store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 4;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

void MVMBatchVectorCwiseProductAccumulate(const int16_t* vector, int v_size,
                                          const int16_t* batch_vector,
                                          int n_batch, int32_t multiplier,
                                          int shift, int16_t* result) {
  //  perm16 permX0 = set_perm16(0xC840);
  // perm16 permX1 = set_perm16(0xC840);
  // perm16 permX2 = set_perm16(0xC840);
  // perm16 permX3 = set_perm16(0xC840);

  vr128 VR_multipler;
  AScalar multiplierFr32;

  ConvertQ31ToAfloat(multiplier, multiplierFr32, shift);

  replicate_ar(VR_multipler, 0xf, multiplierFr32.fr);

  for (int b = 0; b < n_batch; b++) {
    vr128 VR_vector, VR_bvector;
    const int16_t* pVector = vector;
    const int16_t* pBVector = batch_vector;
    int16_t* pResult1 = result;
    int16_t* pResult2 = result;

    ulsr128 UR_vector = align_16x4_load(pVector);
    ulsr128 UR_bvector = align_16x4_load(pBVector);
    ulsr128 UR_result1 = align_16x4_load(pResult1);
    ulsr128 UR_result2 = align_16x4_store(pResult2);

    vr128 VR_prod, VR_result;
    int v_size4 = v_size >> 2;
    // replicate_ar(VR_result, 0xf, result);

    if (v_size4 > 0) {
      load_16x4_vr_a(VR_vector, UR_vector, pVector);
      convert_16I_to_32F_x4(VR_vector, 0);
      load_16x4_vr_a(VR_bvector, UR_bvector, pBVector);
      convert_16I_to_32F_x4(VR_bvector, 0);

      for (int v = 0; v < v_size4 - 1; v++) {
        load_16x4_vr_a(VR_result, UR_result1, pResult1);
        convert_16I_to_32F_x4(VR_result, 0);

        // VR_prod = vmacs_adj(VR_result, VR_vector, VR_bvector, 0, 0);
        VR_prod = vmuls(VR_vector, VR_bvector, 0);
        VR_prod = vmuls(VR_multipler, VR_prod, 0);

        vr128 VR_out = vadds(VR_prod, VR_result, 0);

        convert_32F_to_16I_x4(VR_out, 0, 0);
        store_16x4_vr_a(VR_out, UR_result2, pResult2);

        load_16x4_vr_a(VR_vector, UR_vector, pVector);
        convert_16I_to_32F_x4(VR_vector, 0);
        load_16x4_vr_a(VR_bvector, UR_bvector, pBVector);
        convert_16I_to_32F_x4(VR_bvector, 0);
        // int32_t prod = vector[v] * *batch_vector++;
        // prod = MultiplyByQuantizedMultiplier(prod, multiplier, shift);
        // int32_t output = prod + *result;
        // output = std::max(std::min(static_cast<int32_t>(32767), output),
        //                  static_cast<int32_t>(-32768));
        //*result++ = output;
      }
      load_16x4_vr_a(VR_result, UR_result1, pResult1);
      convert_16I_to_32F_x4(VR_result, 0);

      // VR_prod = vmacs_adj(VR_result, VR_vector, VR_bvector, 0, 0);
      VR_prod = vmuls(VR_vector, VR_bvector, 0);
      VR_prod = vmuls(VR_multipler, VR_prod, 0);

      vr128 VR_out = vadds(VR_prod, VR_result, 0);

      convert_32F_to_16I_x4(VR_out, 0, 0);
      store_16x4_vr_a(VR_out, UR_result2, pResult2);
      flush_16x4(UR_result2, pResult2);
    }

    // reminder
  }
}

void Sigmoid(int16_t* data, int32_t data_size) {
  // xa_nn_vec_sigmoid_sym16s_sym16s(data, data, 0, 0, data_size);
}

void Sigmoid(float* data, int32_t data_size) {
  int data_dims[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(data_dims));
  // reference_ops::Logistic(data_shape, data, data_shape, data);
}

void Tanh(int32_t cell_state_scale_power, int16_t* input_data,
          int16_t* output_data, int32_t data_size) {
  int32_t tanh_input_left_shift = (15 + cell_state_scale_power) - 3;
  int32_t input_multiplier = 0;
  if (tanh_input_left_shift < 0) /* handling negative shift value */
  {
    tanh_input_left_shift = -tanh_input_left_shift;
#if (defined(USE_HIFI_ACT_TIE) && \
     (defined(AE_TANH16X4X2) || defined(AE_TANH16X4)))
    input_multiplier = 1;
#else
    input_multiplier = 3;
#endif
  }
  // xa_nn_vec_tanh_sym16s_sym16s(output_data, input_data, input_multiplier,
  //                             tanh_input_left_shift, data_size);
}

void Tanh(int32_t cell_state_scale_power, float* input_data, float* output_data,
          int32_t data_size) {
  int data_dims[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(data_dims));
  // reference_ops::Tanh(data_shape, input_data, data_shape, output_data);
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const int16_t* input1_data,
         const int16_t* input2_data, int8_t* output_data, int32_t data_size) {
  // xa_nn_elm_mul_sym16sxsym16s_asym8s(
  //    output_data, params.output_offset, params.output_shift,
  //    params.output_multiplier, params.quantized_activation_min,
  //   params.quantized_activation_max, input1_data, input2_data, data_size);
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const int16_t* input1_data,
         const int16_t* input2_data, int16_t* output_data, int32_t data_size) {
  // int dims_4D[4] = {1, 1, 1, data_size};
  // xa_nn_elm_mul_broadcast_4D_sym16sxsym16s_sym16s(
  //     output_data, dims_4D, params.output_shift, params.output_multiplier,
  //     params.quantized_activation_min, params.quantized_activation_max,
  //     input1_data, dims_4D, input2_data, dims_4D);
  return;
}

// Input and output have the same shape in LSTM
void Mul(const ArithmeticParams& params, const float* input1_data,
         const float* input2_data, float* output_data, int32_t data_size) {
  int dims_2D[2] = {1, data_size};
  RuntimeShape data_shape(2, reinterpret_cast<const int32_t*>(dims_2D));
  return reference_ops::Mul(params, data_shape, input1_data, data_shape,
                            input2_data, data_shape, output_data);
}

void FullyConnected(const FullyConnectedParams& params,
                    const int8_t* input_data, const int8_t* filter_data,
                    const int32_t* bias_data, int16_t* output_data,
                    const int num_batches, const int output_depth,
                    const int accum_depth) {
#pragma loop_count min = 1
  for (int b = 0; b < num_batches; b++) {
    // xa_nn_matXvec_out_stride_sym8sxasym8s_16(
    //     output_data + b * output_depth, filter_data,
    //      input_data + b * accum_depth, bias_data, output_depth, accum_depth,
    //      accum_depth, 1, params.input_offset, params.output_multiplier,
    //      params.output_shift);

    MVMQuantizedInt8x8_16((int32_t*)input_data, (int32_t*)filter_data,
                          bias_data, output_data, output_depth, accum_depth,
                          params.output_multiplier, params.output_shift,
                          params.output_offset, 3);
  }
  return;
}

void FullyConnected(const FullyConnectedParams& params,
                    const int16_t* input_data, const int8_t* filter_data,
                    const int64_t* bias_data, int16_t* output_data,
                    const int num_batches, const int output_depth,
                    const int accum_depth) {
  // xa_nn_matmul_sym8sxsym16s_sym16s(
  //    output_data, filter_data, input_data, bias_data, output_depth,
  //    accum_depth, accum_depth, num_batches, accum_depth, output_depth, 1,
  //    params.input_offset, params.output_multiplier, params.output_shift,
  //    params.output_offset);

  // 16x8
  return;
}

void FullyConnected(const FullyConnectedParams& params, const float* input_data,
                    const float* filter_data, const float* bias_data,
                    float* output_data, const int num_batches,
                    const int output_depth, const int accum_depth) {
  int input_dims[2] = {num_batches, output_depth};
  RuntimeShape input_shape(2, reinterpret_cast<const int32_t*>(input_dims));
  RuntimeShape bias_shape(1, bias_data == NULL ? 0 : output_depth);
  int filter_dims[2] = {output_depth, accum_depth};
  RuntimeShape filter_shape(2, reinterpret_cast<const int32_t*>(filter_dims));
  int output_dims[2] = {num_batches, output_depth};
  RuntimeShape output_shape(2, reinterpret_cast<const int32_t*>(output_dims));
  return tflite::reference_ops::FullyConnected(
      params, input_shape, input_data, filter_shape, filter_data, bias_shape,
      bias_data, output_shape, output_data);
}
#else
// ref ops

void Sigmoid(const RuntimeShape& data_shape, int16_t* data) {
  reference_integer_ops::Logistic(
      0 /*data->input_multiplier*/, 0 /*data->input_left_shift */,
      data_shape.FlatSize() /*NumElements(input->dims)*/,
      data /* tflite::micro::GetTensorData<int16_t>(input) */,
      data /*tflite::micro::GetTensorData<int16_t>(output) */);
}

void Sigmoid(const RuntimeShape& data_shape, float* data) {
  reference_ops::Logistic(data_shape, data, data_shape, data);
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          int16_t* input_data, const RuntimeShape& output_data_shape,
          int16_t* output_data) {
  int32_t tanh_input_left_shift = (15 + cell_state_scale_power) - 3;
  int32_t input_multiplier = 0;
  if (tanh_input_left_shift < 0) /* handling negative shift value */
  {
    tanh_input_left_shift = -tanh_input_left_shift;
    input_multiplier = 3;
  }
  reference_integer_ops::Tanh(input_multiplier, tanh_input_left_shift,
                              input_data_shape, input_data, output_data_shape,
                              output_data);
}

void Tanh(int32_t cell_state_scale_power, const RuntimeShape& input_data_shape,
          float* input_data, const RuntimeShape& output_data_shape,
          float* output_data) {
  reference_ops::Tanh(input_data_shape, input_data, output_data_shape,
                      output_data);
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int8_t* output_data) {
  return reference_integer_ops::MulElementwise(
      shape.FlatSize(), params, input1_data, input2_data, output_data);
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const int16_t* input1_data, const int16_t* input2_data,
         int16_t* output_data) {
  return reference_integer_ops::MulElementwise(
      shape.FlatSize(), params, input1_data, input2_data, output_data);
}

// Input and output have the same shape in LSTM
void Mul(const RuntimeShape& shape, const ArithmeticParams& params,
         const float* input1_data, const float* input2_data,
         float* output_data) {
  return reference_ops::Mul(params, shape, input1_data, shape, input2_data,
                            shape, output_data);
}

void FullyConnected(const FullyConnectedParams& params,
                    const RuntimeShape& input_shape, const int8_t* input_data,
                    const RuntimeShape& filter_shape, const int8_t* filter_data,
                    const RuntimeShape& bias_shape, const int32_t* bias_data,
                    const RuntimeShape& output_shape, int16_t* output_data) {
  //
  KN_PRINT_Q7_SIZE(input_data, input_shape.FlatSize());

  tflite::reference_integer_ops::FullyConnected(
      params, input_shape, input_data, filter_shape, filter_data, bias_shape,
      bias_data, output_shape, output_data);

  //    MVMQuantizedInt8x8_16((int32_t*)input_data,
  //    (int32_t*)op_data_ex->mapped_i2i_w,
  //        (int32_t *)input_to_gate_bias, (int16_t*)gate, n_output,
  //        n_input, input_to_gate_scale_a, input_to_gate_scale_b, 0, 3);

  KN_PRINT_Q15_SIZE(output_data, output_shape.FlatSize());
}

void FullyConnected(const FullyConnectedParams& params,
                    const RuntimeShape& input_shape, const int16_t* input_data,
                    const RuntimeShape& filter_shape, const int8_t* filter_data,
                    const RuntimeShape& bias_shape, const int64_t* bias_data,
                    const RuntimeShape& output_shape, int16_t* output_data) {
  return tflite::reference_integer_ops::FullyConnected(
      params, input_shape, input_data, filter_shape, filter_data, bias_shape,
      bias_data, output_shape, output_data);
}

void FullyConnected(const FullyConnectedParams& params,
                    const RuntimeShape& input_shape, const float* input_data,
                    const RuntimeShape& filter_shape, const float* filter_data,
                    const RuntimeShape& bias_shape, const float* bias_data,
                    const RuntimeShape& output_shape, float* output_data) {
  return tflite::reference_ops::FullyConnected(
      params, input_shape, input_data, filter_shape, filter_data, bias_shape,
      bias_data, output_shape, output_data);
}
#endif

void Clipping(const int v_size, const CellStateInfo& cell_state_info,
              int16_t* vector) {
  for (int i = 0; i < v_size; i++) {
    vector[i] =
        std::max(std::min(cell_state_info.quantized_cell_clip, vector[i]),
                 static_cast<int16_t>(-cell_state_info.quantized_cell_clip));
  }
}

void Clipping(const int v_size, const CellStateInfo& cell_state_info,
              float* vector) {
  for (int i = 0; i < v_size; i++) {
    vector[i] = std::max(std::min(cell_state_info.cell_clip, vector[i]),
                         -cell_state_info.cell_clip);
  }
}
#if defined(DMX1A_LSTM_OPT)

void UpdateLstmCell(const LstmStepManager& step_info,
                    TfLiteEvalTensor* cell_state,
                    // Gate outputs
                    int16_t* forget_gate_output,
                    const int16_t* input_gate_output,
                    const int16_t* cell_gate_output,
                    // Mul parameters
                    const ArithmeticParams& forget_cell_mul_params,
                    const ArithmeticParams& input_mul_params,
                    const CellStateInfo& cell_state_info, int16_t* buffer) {
  auto cell_state_shape = step_info.StateShape();
  // Check offset validity to avoid memory overflow
  TFLITE_DCHECK_LE(step_info.CellStateOffset() + cell_state_shape.FlatSize(),
                   tflite::micro::GetTensorShape(cell_state).FlatSize());

  // Multiplier is equivalent to 0.5 here so adding 1 to shifts
  // xa_nn_lstm_cell_state_update_16(
  //     tflite::micro::GetTensorData<int16_t>(cell_state) +
  //        step_info.CellStateOffset(),
  //    forget_gate_output, cell_gate_output, input_gate_output,
  //    forget_cell_mul_params.output_shift - 1,
  //    input_mul_params.output_shift - 1, cell_state_info.quantized_cell_clip,
  //    cell_state_shape.FlatSize());
}

void UpdateLstmCell(const LstmStepManager& step_info,
                    TfLiteEvalTensor* cell_state,
                    // Gate outputs
                    float* forget_gate_output, const float* input_gate_output,
                    const float* cell_gate_output,
                    // Mul parameters
                    const ArithmeticParams& forget_cell_mul_params,
                    const ArithmeticParams& input_mul_params,
                    const CellStateInfo& cell_state_info, float* buffer) {
  // Check offset validity to avoid memory overflow
  TFLITE_DCHECK_LE(
      step_info.CellStateOffset() + step_info.StateShape().FlatSize(),
      tflite::micro::GetTensorShape(cell_state).FlatSize());

  auto cell_state_shape = step_info.StateShape();
  // Forget Gate x Cell State
  Mul(forget_cell_mul_params, forget_gate_output,
      tflite::micro::GetTensorData<float>(cell_state) +
          step_info.CellStateOffset(),
      tflite::micro::GetTensorData<float>(cell_state) +
          step_info.CellStateOffset(),
      cell_state_shape.FlatSize());
  // Input Gate x Cell Gate
  Mul(input_mul_params, input_gate_output, cell_gate_output, buffer,
      cell_state_shape.FlatSize());

  // Update the cell state
  AddElementWise(tflite::micro::GetTensorData<float>(cell_state) +
                     step_info.CellStateOffset(),
                 buffer,
                 /*n_batch=*/cell_state_shape.DimsData()[0],
                 /*n_state=*/cell_state_shape.DimsData()[1],
                 tflite::micro::GetTensorData<float>(cell_state) +
                     step_info.CellStateOffset());

  if (cell_state_info.cell_clip > 0) {
    Clipping(cell_state_shape.FlatSize(), cell_state_info,
             tflite::micro::GetTensorData<float>(cell_state) +
                 step_info.CellStateOffset());
  }
}
#endif
// Calculates a single LSTM gate, int8x8_16 version.
// Implements the same functionality as CalculateLstmGateFloat.
void CalculateLstmGateInteger8x8_16(
    const OpDataLSTMEx* op_data_ex,
    // Input and weights
    const int8_t* input, const int8_t* input_to_gate_weights,
    const int32_t* input_to_gate_bias, const int32_t input_to_gate_scale_a,
    const int32_t input_to_gate_scale_b,
    // Output state and weights
    const int8_t* output_state, const int8_t* recurrent_to_gate_weights,
    const int32_t* recurrent_to_gate_bias,
    const int32_t recurrent_to_gate_scale_a,
    const int32_t recurrent_to_gate_scale_b,
    // Cell state and weights
    const int16_t* cell_state, const int16_t* cell_to_gate_weights,
    const int32_t cell_to_gate_scale_a, const int32_t cell_to_gate_scale_b,
    // Layer normalization parameters (layer norm LSTM)
    const int16_t* layer_norm_coefficients, const int32_t* layer_norm_bias,
    const int32_t layer_norm_input_scale_a,
    const int32_t layer_norm_input_scale_b,
    const int32_t layer_norm_variance_guard,
    // Array sizes
    const int n_batch, const int n_input, const int n_output, const int n_cell,
    const TfLiteFusedActivation activation,
    // Output
    int16_t* gate,
    // Parameters for performance optimizations
    // CpuBackendContext* context,
    // Scratch arrays
    int32_t* scratch5) {
  const bool use_peephole = (cell_to_gate_weights != nullptr);
  const bool use_layer_norm = (layer_norm_coefficients != nullptr);

  // Initialize scratch buffers with zeros. Note that unlike float and hybrid
  // versions, bias is only used in layer normalization.
  std::fill_n(gate, n_batch * n_cell, 0);
#if defined(DMX1A_LSTM_OPT)

  MVMQuantizedInt8x8_16((int32_t*)input, (int32_t*)op_data_ex->mapped_i2i_w,
                        (int32_t*)input_to_gate_bias, (int16_t*)gate, n_output,
                        n_input, input_to_gate_scale_a, input_to_gate_scale_b,
                        0, 3);
#else
  // For each batch and cell: compute input_weight * input.
  tensor_utils::PortableMatrixBatchVectorMultiplyAccumulate(
      input, input_to_gate_bias, input_to_gate_weights, input_to_gate_scale_a,
      input_to_gate_scale_b, n_batch, n_input, n_cell, 0, scratch5, gate, NULL);
#endif

  KN_PRINT_Q15_SIZE(gate, n_output);
// Note: no aux_input.

// For each batch and cell: compute recurrent_weight * output_state.
#if defined(DMX1A_LSTM_OPT)

  MVMQuantizedInt8x8_16(
      (int32_t*)output_state,
      (int32_t*)op_data_ex->mapped_r2i_w,  // recurrent_to_gate_weights,
      (int32_t*)recurrent_to_gate_bias, (int16_t*)gate, n_output, n_cell,
      recurrent_to_gate_scale_a, recurrent_to_gate_scale_b, 0, 3);
#else
  tensor_utils::PortableMatrixBatchVectorMultiplyAccumulate(
      output_state, recurrent_to_gate_bias, recurrent_to_gate_weights,
      recurrent_to_gate_scale_a, recurrent_to_gate_scale_b, n_batch, n_output,
      n_cell, 0, scratch5, gate, NULL);
#endif
  KN_PRINT_Q15_SIZE(gate, n_output);
  // For each batch and cell: compute cell_weight * cell_state (peephole LSTM)
  if (use_peephole) {
#if defined(DMX1A_LSTM_OPT)

    MVMBatchVectorCwiseProductAccumulate(
        cell_to_gate_weights, n_output, cell_state, n_batch,
        cell_to_gate_scale_a, cell_to_gate_scale_b, gate);
#else
    tensor_utils::PortableVectorBatchVectorCwiseProductAccumulate(
        cell_to_gate_weights, n_output, cell_state, n_batch,
        cell_to_gate_scale_a, cell_to_gate_scale_b, gate);
#endif
  }
  // Do layer normalization (if layer norm LSTM)
  if (use_layer_norm) {
    tensor_utils::PortableApplyLayerNorm(
        gate, layer_norm_coefficients, layer_norm_bias,
        layer_norm_input_scale_a, layer_norm_input_scale_b,
        layer_norm_variance_guard, n_batch, n_cell, gate);
  }
  // Apply activation
  switch (activation) {
    case kTfLiteActSigmoid:
#if defined(DMX1A_LSTM_OPT)
      // scratch = MVMConvert();
      SigmoidV_Full(gate_flt, gate, n_cell);
#else
      tensor_utils::PortableApplySigmoid(gate, n_batch, n_cell, gate);

#endif  // !defined(DMX1A_LSTM_OPT)
      break;
    case kTfLiteActTanh:
#if defined(DMX1A_LSTM_OPT)
      // tanV(
#else
      tensor_utils::PortableApplyTanh(3, gate, n_batch, n_cell, gate);

#endif  // !defined(DMX1A_LSTM_OPT)
      break;
    default:
      // Only Sigmoid or Tanh is used.
      TFLITE_ASSERT_FALSE;
  }
}

void UpdateLstmCellInteger(int n_batch, int n_cell, int16_t* cell_state,
                           int32_t cell_state_scale, const int16_t* input_gate,
                           int16_t* forget_gate, const int16_t* cell_gate,
                           bool use_cifg, int16_t clip) {
#if !defined(HIFI5)
  // Use the forget_gate array as scratch, as input_gate array is not allocated
  // in CIFG case. (Be careful not to write to the scratch before reading the
  // forget gate data.)
  int16_t* scratch = forget_gate;

  tensor_utils::PortableCwiseMul(forget_gate, cell_state, n_batch, n_cell, 15,
                                 cell_state);
  if (use_cifg) {
    tensor_utils::PortableSub1Vector(forget_gate, n_batch * n_cell, scratch);
    tensor_utils::PortableCwiseMul(scratch, cell_gate, n_batch, n_cell,
                                   30 + cell_state_scale, scratch);
  } else {
    tensor_utils::PortableCwiseMul(input_gate, cell_gate, n_batch, n_cell,
                                   30 + cell_state_scale, scratch);
  }

  tensor_utils::PortableCwiseAdd(cell_state, scratch, n_batch, n_cell,
                                 cell_state);

  if (clip > 0) {
    tensor_utils::PortableCwiseClipping(cell_state, n_batch * n_cell, clip);
  }
#else
  if (use_cifg) {
    calc_cell_state_with_cifg(cell_state, forget_gate, cell_gate, 15,
                              30 + cell_state_scale, clip, n_batch * n_cell);
  } else {
    calc_cell_state_without_cifg(cell_state, forget_gate, cell_gate, input_gate,
                                 15, 30 + cell_state_scale, clip,
                                 n_batch * n_cell);
  }

#endif  // !defined(HIFI5)
}

// Increment the data offset so the sigle time step invocation call can access
// the corresponding input/output tensor data at the time step
void LstmStepManager::UpdateTime() {
  current_time_ += 1;
  TFLITE_DCHECK_LE(current_time_, size_info_.time_steps);
  // default as one batch per inference
  int input_step = size_info_.input_dimension;
  int output_step = size_info_.state_dimension;
  // time major: batch inference
  if (size_info_.time_major) {
    input_step = input_step * size_info_.batch_size;
    output_step = output_step * size_info_.batch_size;
  }

  input_offset_ += input_step;
  output_offset_ += output_step;
}

// Increment the data offset so the sigle time step invocation call can access
// the corresponding hidden/cell state tensor data at the time step (for single
// batch inference only)
void LstmStepManager::UpdateBatch() {
  current_batch_ += 1;
  TFLITE_DCHECK_LE(current_batch_, size_info_.batch_size);
  // batch inference for time major: no action needed
  if (size_info_.time_major) {
    return;
  }
  // otherwise: singe batch inference, go to the next batch
  hidden_state_offset_ += size_info_.state_dimension;
  cell_state_offset_ += size_info_.state_dimension;
}

// Input shape for each single time LSTM invocation.
// Multi-batch for time_major input
RuntimeShape LstmStepManager::InputShape() const {
  int batch_size = 1;
  if (size_info_.time_major) {
    batch_size = size_info_.batch_size;
  }
  const int dims[2] = {batch_size, size_info_.input_dimension};
  const int32_t* dims_data = reinterpret_cast<const int32_t*>(dims);
  return RuntimeShape(2, dims_data);
}

// State shape (both hidden and cell) for each single time LSTM invocation.
// Multi-batch for time_major input
RuntimeShape LstmStepManager::StateShape() const {
  int batch_size = 1;
  if (size_info_.time_major) {
    batch_size = size_info_.batch_size;
  }
  const int dims[2] = {batch_size, size_info_.state_dimension};
  const int32_t* dims_data = reinterpret_cast<const int32_t*>(dims);
  return RuntimeShape(2, dims_data);
}
}  // namespace lstm_internal
}  // namespace tflite
