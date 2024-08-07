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

#define KN_DEBUG
#include "tensorflow/lite/micro/kernels/ia8201/lstm_eval.h"

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor_utils.h"
#include "tensorflow/lite/kernels/internal/reference/portable_tensor_utils_impl.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"

#include "tensorflow/lite/micro/ia8201/debug_helper.h"
#include <limits>


namespace tflite {
#if defined(DMX1A_LSTM_OPT)
    static int MVMQuantizedInt8x8_16(int32_t *x, const int32_t *A,
                                    const int32_t *bias, int16_t *output, int m,
                                    int n, const int32_t outMultipler,
                                  //  const int32_t *inputOffsetWithW,  // xor 128
                                    const int32_t shift, int32_t outOffset,
                                    int signs) 
{
  int16_t *pY = output;

  const int32_t *pA = A;
  const int32_t *pX;
  const int32_t *pB = (const int32_t *)bias;
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
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0)
  {
      loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0)
  {
      return -1;
  }
  vr128 VR_A;
  vr128 VR_x;
  vr128 VR_y;
  //vr128 VR_inputOffset;
  xtbool2 signSpec = int_to_xt_bool2(signs);

  vr128 VR_outMult;
  //vr128 VR_outOffset;
  vr128 VR_b0 = vseta_vr(kConstTable_Zero, 0, 0);
  ulsr128 UR_out = align_16x4_store(pY);
  AScalar outMultiplerFr32;

  ConvertQ31ToAfloat(outMultipler, outMultiplerFr32, shift);

  replicate_ar(VR_outMult, 0xf, outMultiplerFr32.fr);
  //replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);
  //replicate_ar(VR_inputOffset, 0xf, input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {

    pX = x;
    ulsr128 UR_A = align_32x4_load(pA);
    ulsr128 UR_x = align_32x4_load(pX);
    ulsr128 UR_b;
    load_32x4_vr_a(VR_A, UR_A, pA);

    //if (pB) 
    {
      UR_b = align_32x4_load(pB);
      load_32x4_vr_a(VR_y, UR_b, pB);  // suppose not grate than 16 bit

      VR_y = shift32_arith(VR_y, 2, 0);
      load_32x4_vr_a(VR_b0, UR_b, pB); 

      VR_b0 = shift32_arith(VR_b0, 2, 0);

    }
    //VR_y = vexp_adji(VR_b0, 0); //vseta_vr(0, 0, 0);
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
      //VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      //vr128 VR_q7_out;

      vr128 VR_out;

     // VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      //VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);
     // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
      //VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
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
      //VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);

      //rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      //VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

      store_16x4_vr_a(VR_out, UR_out, pY);
      flush_16x4(UR_out, pY);
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      //vr128 VR_q7_out;

      vr128 VR_out;

      //VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      //VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);
      //rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      //VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      for (int32_t j = 0; j < (m & 0x7) && j < 4; j++) {
        store16x1_vr_postI(VR_out, pY, INC1, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }

      if ((m & 7) <= 4) {
        break;
      }
      VR_y = mov_vr_AccExtend();

      //if (pB) {
      //  load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
      //}

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      //VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
     // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1 - 8, 0);
      //rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      //VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);

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


void MVMBatchVectorCwiseProductAccumulate(
    const int16_t* vector, int v_size, const int16_t* batch_vector, int n_batch,
    int32_t multiplier, int shift, int16_t* result) {

  perm16 permX0 = set_perm16(0xC840);
  perm16 permX1 = set_perm16(0xC840);
  perm16 permX2 = set_perm16(0xC840);
  perm16 permX3 = set_perm16(0xC840);

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
    //replicate_ar(VR_result, 0xf, result);
    
    
    if (v_size4 > 0) {
      load_16x4_vr_a(VR_vector, UR_vector, pVector);
      convert_16I_to_32F_x4(VR_vector, 0);
      load_16x4_vr_a(VR_bvector, UR_bvector, pBVector);
      convert_16I_to_32F_x4(VR_bvector, 0);
       
        for (int v = 0; v < v_size4-1; v++) {
        load_16x4_vr_a(VR_result, UR_result1, pResult1);
          convert_16I_to_32F_x4(VR_result, 0);

        //VR_prod = vmacs_adj(VR_result, VR_vector, VR_bvector, 0, 0);
          VR_prod = vmuls( VR_vector, VR_bvector,  0);
          VR_prod = vmuls(VR_multipler, VR_prod, 0);

          vr128 VR_out = vadds(VR_prod, VR_result, 0);

          convert_32F_to_16I_x4(VR_out, 0, 0);
          store_16x4_vr_a(VR_out, UR_result2, pResult2);

          load_16x4_vr_a(VR_vector, UR_vector, pVector);
          convert_16I_to_32F_x4(VR_vector, 0);
          load_16x4_vr_a(VR_bvector, UR_bvector, pBVector);
          convert_16I_to_32F_x4(VR_bvector, 0);
        //int32_t prod = vector[v] * *batch_vector++;
      //prod = MultiplyByQuantizedMultiplier(prod, multiplier, shift);
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
#endif

// Calculates a single LSTM gate, int8x8_16 version.
// Implements the same functionality as CalculateLstmGateFloat.
void CalculateLstmGateInteger8x8_16(
    const OpDataLSTMEx *op_data_ex,
    // Input and weights
    const int8_t* input, const int8_t* input_to_gate_weights,
    const int32_t* input_to_gate_bias, 
    const int32_t input_to_gate_scale_a,
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
        (int32_t *)input_to_gate_bias, (int16_t*)gate, n_output,
        n_input, input_to_gate_scale_a, input_to_gate_scale_b, 0, 3);
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
      (int32_t*)output_state, (int32_t*)op_data_ex->mapped_r2i_w, //recurrent_to_gate_weights,
      (int32_t*)recurrent_to_gate_bias, (int16_t*)gate, n_output, n_cell,
      recurrent_to_gate_scale_a, recurrent_to_gate_scale_b, 0,
                        3);
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
      //scratch = MVMConvert();
      SigmoidV_Full(gate_flt, gate, n_cell);
#else
       tensor_utils::PortableApplySigmoid(gate, n_batch, n_cell, gate);

#endif  // !defined(DMX1A_LSTM_OPT)
      break;
    case kTfLiteActTanh:
#if defined(DMX1A_LSTM_OPT)
       //tanV(
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
void CalculateLstmOutputInteger8x8_16(
    int n_batch, int n_cell, int n_output, const int16_t* cell_state,
    int32_t cell_state_scale, const int16_t* output_gate,
    int32_t hidden_scale_a, int32_t hidden_scale_b, int32_t hidden_zp,
    const int8_t* projection_weights, int32_t proj_scale_a,
    int32_t proj_scale_b, const int32_t* projection_bias,
    int32_t output_state_zp, int8_t quantized_proj_clip, int8_t* output_state,
    int16_t* scratch0, int8_t* scratch1, int32_t* scratch2) {
// Note: unlike float/hybrid, the activation is always Tanh.
#if !defined(HIFI5)
  tensor_utils::PortableApplyTanh(15 + cell_state_scale, cell_state, n_batch,
                                  n_cell, scratch0);
#else
  xa_nn_vec_tanh_16_16(scratch0, cell_state, (15 + cell_state_scale),
                       n_batch * n_cell);
#endif  // !defined(HIFI5)

#if !defined(HIFI5)
  tensor_utils::PortableCwiseMul(output_gate, scratch0, hidden_scale_a,
                                 hidden_scale_b, n_batch, n_cell, hidden_zp,
                                 scratch1);
#else
  xa_nn_elm_mul_16x16_asym8s(scratch1, output_gate, scratch0, hidden_scale_a,
                             hidden_scale_b, hidden_zp, n_batch * n_cell);
#endif  // !defined(HIFI5)

  const bool use_projection = (projection_weights != nullptr);

  if (use_projection) {
    // Note: no bias like in float/hybrid
    std::fill_n(output_state, n_batch * n_output, 0);
    tensor_utils::PortableMatrixBatchVectorMultiplyAccumulate(
        scratch1, projection_bias, projection_weights, proj_scale_a,
        proj_scale_b, n_batch, n_cell, n_output, output_state_zp, scratch2,
        output_state, NULL);
    if (quantized_proj_clip > 0) {
      tensor_utils::PortableCwiseClipping(output_state, n_batch * n_output,
                                          quantized_proj_clip);
    }
  } else {
    std::copy_n(scratch1, n_batch * n_output, output_state);
  }
}

}  // namespace tflite
