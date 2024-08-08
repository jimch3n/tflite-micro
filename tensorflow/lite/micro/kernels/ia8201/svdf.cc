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

#include "tensorflow/lite/micro/kernels/svdf.h"

#include <cmath>
#include <cstdint>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"
#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/micro/kernels/activation_utils.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/svdf.h"
#include "tensorflow/lite/micro/micro_utils.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
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
  int32_t input_offset_int8;
  // int32_t input_offset_int8_neg;
};

// Input tensors.
constexpr int kInputTensor = 0;
constexpr int kWeightsFeatureTensor = 1;
constexpr int kWeightsTimeTensor = 2;
constexpr int kBiasTensor = 3;
// This is a variable tensor, and will be modified by this op.
constexpr int kInputActivationStateTensor = 4;

// Output tensor.
constexpr int kOutputTensor = 0;

/**
 * This version of SVDF is specific to TFLite Micro. It contains the following
 * differences between the TFLite version:
 *
 * 1.) Scratch tensor allocation - scratch tensors must be known ahead of time
 * for the Micro interpreter.
 * 2.) Output dimensions - the TFLite version determines output size and runtime
 * and resizes the output tensor. Micro runtime does not support tensor
 * resizing.
 */
#ifndef REMOVE_FLOAT_SUPPORT
static inline void ApplyTimeWeightsBiasAndActivation(
    int batch_size, int memory_size, int num_filters, int num_units, int rank,
    const float* const weights_time_ptr, const float* const bias_ptr,
    TfLiteFusedActivation activation, float* const state_ptr,
    float* const scratch_ptr, float* const output_ptr) {
  // Compute matmul(activation_state, weights_time).
  for (int b = 0; b < batch_size; ++b) {
    // Perform batched vector dot product:
    float* scratch_ptr_batch = scratch_ptr + b * num_filters;
    const float* vector1_ptr = weights_time_ptr;
    const float* vector2_ptr = state_ptr + b * memory_size * num_filters;
    for (int i = 0; i < num_filters; ++i) {
      *scratch_ptr_batch = 0.f;
      for (int j = 0; j < memory_size; ++j) {
        *scratch_ptr_batch += *vector1_ptr++ * *vector2_ptr++;
      }
      scratch_ptr_batch++;
    }
  }

  // Initialize output with bias if provided.
  if (bias_ptr) {
    // VectorBatchVectorAssign
    for (int i = 0; i < batch_size; ++i) {
      float* output_data = output_ptr + i * num_units;
      const float* bias_data = bias_ptr;
      for (int j = 0; j < num_units; ++j) {
        *output_data++ = *bias_data++;
      }
    }
  } else {
    float* output_data = output_ptr;
    for (int i = 0; i < batch_size * num_units; ++i) {
      *output_data++ = 0.0f;
    }
  }

  // Reduction sum.
  for (int b = 0; b < batch_size; ++b) {
    float* output_ptr_batch = output_ptr + b * num_units;
    float* scratch_ptr_batch = scratch_ptr + b * num_filters;

    // Reduction sum vector
    for (int i = 0; i < num_units; ++i) {
      for (int j = 0; j < rank; j++) {
        output_ptr_batch[i] += *scratch_ptr_batch++;
      }
    }
  }

  // Apply activation.
  for (int b = 0; b < batch_size; ++b) {
    float* output_ptr_batch = output_ptr + b * num_units;
    for (int i = 0; i < num_units; ++i) {
      *output_ptr_batch =
          tflite::ops::micro::ActivationValFloat(activation, *output_ptr_batch);
      ++output_ptr_batch;
    }
  }
}
#endif

#ifndef REMOVE_FLOAT_SUPPORT
inline void EvalFloatSVDF(
    TfLiteContext* context, TfLiteNode* node, const TfLiteEvalTensor* input,
    const TfLiteEvalTensor* weights_feature,
    const TfLiteEvalTensor* weights_time, const TfLiteEvalTensor* bias,
    const TfLiteSVDFParams* params, int scratch_tensor_index,
    TfLiteEvalTensor* activation_state, TfLiteEvalTensor* output) {
  const int rank = params->rank;
  const int batch_size = input->dims->data[0];
  const int input_size = input->dims->data[1];
  const int num_filters = weights_feature->dims->data[0];
  const int num_units = num_filters / rank;
  const int memory_size = weights_time->dims->data[1];

  const float* weights_feature_ptr =
      tflite::micro::GetTensorData<float>(weights_feature);
  const float* weights_time_ptr =
      tflite::micro::GetTensorData<float>(weights_time);
  const float* bias_ptr = tflite::micro::GetTensorData<float>(bias);
  const float* input_ptr = tflite::micro::GetTensorData<float>(input);

  float* state_ptr = tflite::micro::GetTensorData<float>(activation_state);

  TFLITE_DCHECK(context != nullptr);
  TFLITE_DCHECK(context->GetScratchBuffer != nullptr);

  float* scratch_ptr = static_cast<float*>(
      context->GetScratchBuffer(context, scratch_tensor_index));

  float* output_ptr = tflite::micro::GetTensorData<float>(output);

  // Left shift the activation_state.
  {
    float* new_state_start = state_ptr;
    const float* old_state_start = state_ptr + 1;
    const float* old_state_end =
        state_ptr + batch_size * num_filters * memory_size;
    while (old_state_start != old_state_end) {
      *new_state_start++ = *old_state_start++;
    }
  }

  // Note: no need to clear the latest activation, matmul is not accumulative.

  // Compute conv1d(inputs, weights_feature).
  // The activation_state's rightmost column is used to save current cycle
  // activation. This is achieved by starting at state_ptr[memory_size - 1] and
  // having the stride equal to memory_size.

  // Perform batched matrix vector multiply operation:
  {
    const float* matrix = weights_feature_ptr;
    const float* vector = input_ptr;
    float* result = &state_ptr[memory_size - 1];
    float* result_in_batch = result;
    for (int i = 0; i < batch_size; ++i) {
      const float* matrix_ptr = matrix;
      for (int j = 0; j < num_filters; ++j) {
        float dot_prod = 0.0f;
        const float* vector_in_batch = vector + i * input_size;
        for (int k = 0; k < input_size; ++k) {
          dot_prod += *matrix_ptr++ * *vector_in_batch++;
        }
        *result_in_batch = dot_prod;
        result_in_batch += memory_size;
      }
    }
  }

  ApplyTimeWeightsBiasAndActivation(
      batch_size, memory_size, num_filters, num_units, rank, weights_time_ptr,
      bias_ptr, params->activation, state_ptr, scratch_ptr, output_ptr);
}
#endif

#ifdef DMX1A_SVDF_OPT
// input MVM8bx8b with , output mutlipler,shift
int SVDFFeatMatInt8InputOffset(int32_t* x, const int32_t* A,
                               // const AScalar *bias,
                               int inputOffset, int16_t* output, int n_filter,
                               int n_input, int n_memory,
                               // const AScalar &outOffsetFr32,
                               const AScalar& outMultiplerFr32, int signs) {
  int16_t* pY = (int16_t*)output;  // act
  int m = n_filter;
  int n = n_input;
  const int32_t* pA = A;
  const int32_t* pX;
  // const int32_t *pB = (  const int32_t *)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 3);  // block 16
  int loopLimRow = ((m + 7) >> 3);         // group 8 alignment
  int processLastLoop = ((m & 7) != 0);

  vr128 VR_A;
  vr128 VR_x;
  vr128 VR_y;
  xtbool2 signSpec = int_to_xt_bool2(signs);
  xtbool2 signSpecInput = int_to_xt_bool2(3);

  vr128 VR_outMult;
  vr128 VR_inputOffset;
  // vr128 VR_outOffset;
  replicate_ar(VR_outMult, 0xf, outMultiplerFr32.fr);
  replicate_ar(VR_inputOffset, 0xf, inputOffset);

  // replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);
  for (int i = 0; i < loopLimRow; i++) {
    VR_y = vseta_vr(0, 0, 0);
    mov_AccExtend_vr(VR_y);
    pX = x;
    ulsr128 UR_A = align_32x4_load(pA);
    ulsr128 UR_x = align_32x4_load(pX);
    // ulsr128 UR_b = align_32x4_load(pB);
    load_32x4_vr_a(VR_A, UR_A, pA);

    // vr128 VR_b0, VR_b1;
    // load_32x4_vr_a(VR_b0, UR_b, pB); // suppose not grate than 16 bit

    for (int j = 0; j < loopLimCol; j++) {
      load_32x4_vr_a(VR_x, UR_x, pX);
      WUR_MvmAux(0);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(0);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(1);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(2);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(3);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(4);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);

      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(5);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(6);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(7);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 3); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      //   KN_PRINTX_VR128(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x4_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      //					vr128 VR_q7_out;

      vr128 VR_out;

      // VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);

      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      // convert_32F_to_16I_x4(VR_out, (unsigned int)1, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
      // load_32x4_vr_a(VR_b1, UR_b, pB);
      convert_32F_to_16I_x4(VR_out, 1, 1);  // no rounding

      store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ1);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ2);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ3);

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      // VR_out = vadds(VR_y, VR_b1, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);

      // rnd_sat_pack(VR_q7_out, VRQ1, VR_out, 1);

      store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ1);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ2);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ3);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      vr128 VR_out;

      VR_out = vmuls(VR_y, VR_outMult, 0);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);

      for (int32_t j = 0; j < (m & 0x7) && j < 4; j++) {
        store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }

      if ((m & 7) <= 4) {
        break;
      }
      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

      VR_out = vmuls(VR_y, VR_outMult, 0);
      convert_32F_to_16I_x4(VR_out, (unsigned int)1, 1);

      for (int32_t j = 4; j < (m & 0x7) && j < 8; j++) {
        store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
        VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 4;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}
// BatchVectorBatchVectorDotProduct
void SVDFTimeInt16(OpData* data, const int16_t* weight_time,
                   const int16_t* activation_state, int feature_batch,
                   int time_batches, int32_t* output) {
  int loopLim = time_batches >> 2;
  vr128 vr_weight, vr_state;
  vr128 vr_sum, vr_out;  //, vr_bias;
  const int16_t* pWeight = weight_time;
  const int16_t* pState = activation_state;
  //   const AScalar *pBias = bias;
  ulsr128 UR_w, UR_state;

  for (int ii = 0; ii < feature_batch; ii++) {
    UR_w = align_16x4_load(pWeight);
    UR_state = align_16x4_load(pState);

    // convert to 32F from 16I is faster,
    load_16x4_vr_a(vr_weight, UR_w, pWeight);
    load_16x4_vr_a(vr_state, UR_state, pState);
    vr_sum = vseta_vr(kConstTable_Zero, 0, 0);
    for (int j = 0; j < loopLim - 1; j++) {
      convert_16I_to_32F_x4(vr_weight, 0);
      convert_16I_to_32F_x4(vr_state, 0);
      vr_sum = vmacs_adj(vr_sum, vr_weight, vr_state, 0, 0);
      //  sum += *v1 * *v2;
      load_16x4_vr_a(vr_weight, UR_w, pWeight);
      load_16x4_vr_a(vr_state, UR_state, pState);
    }
    convert_16I_to_32F_x4(vr_weight, 0);
    convert_16I_to_32F_x4(vr_state, 0);

    vr_sum = vmacs_adj(vr_sum, vr_weight, vr_state, 0, 0);

    if (time_batches & 3) {
      for (int jj = 0; jj < (time_batches & 3); jj++) {
        load16x1_vr_postI(vr_weight, pWeight, INC1, VRQ0);
        load16x1_vr_postI(vr_state, pState, INC1, VRQ0);

        convert_16I_to_32F_x1(vr_weight, 0, VRQ0);
        convert_16I_to_32F_x1(vr_state, 0, VRQ0);

        fmacs(vr_sum, VRQ0, vr_weight, VRQ0, vr_state, VRQ0, 0);
        vr_weight = vpermsi(vr_weight, vr_weight, 0, SHR_BY_1_ELEM);
        vr_state = vpermsi(vr_state, vr_state, 0, SHR_BY_1_ELEM);
      }
    }
    dsums_L(vr_sum, vr_sum, 0, 0);
    fadds(vr_out, VRQ0, vr_sum, VRQ0, vr_sum, VRQ1, 0);
    // convert to fix-point ?
    store32x1_vr_postI(vr_out, output, INC1, VRQ0);
  }
}

void SVDFBiasReduceScale(OpData* data, const int32_t* bias, int input_batches,
                         int feature_batches, int unit_count, int rank,
                         int8_t* Q7output) {
  int loopLim = (input_batches * unit_count) >> 2;
  int remain = (input_batches * unit_count) & 3;
  int32_t* pScratchInput = data->pScratch;
  int32_t* pScratchOutput = data->pScratchOutput;
  vr128 vr_input;
  vr128 vr_out, vr_q7_out;
  vr128 vr_outputMultipler;
  vr128 vr_outputOffset;  //+ zero_point
  const int32_t* pBias = bias;
  const int32_t* pInput = pScratchInput;
  const int32_t* pOutput = pScratchOutput;
  int8_t* pQ7Output = Q7output;

#ifdef KN_DEBUG
  // CHECK_ALIGN_4(  input_batches* unit_count);

#endif
  // TFLITE_CHECK_EQ(rank, 2); // optimized for rank=2
  replicate_ar(vr_outputMultipler, 0xf, data->scaleAct.fr);
  replicate_ar(vr_outputOffset, 0xf, data->outputOffset.fr);

  // scalar operation
  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    pInput = pScratchInput + i_batch * feature_batches;
    pOutput = pScratchOutput + i_batch * unit_count;
    pBias = bias;
    for (int ii = 0; ii < unit_count; ii++) {
      load32x1_vr_postI(vr_out, pBias, INC1, VRQ0);

      convert_32I_to_32F_x1(vr_out, 1, VRQ0);  // Q30

      for (int kk = 0; kk < rank; kk++) {
        load32x1_vr_postI(vr_input, pInput, INC1, VRQ0);
        fadds(vr_out, VRQ0, vr_out, VRQ0, vr_input, VRQ0, 0);
      }
      store32x1_vr_postI(vr_out, pOutput, INC1, VRQ0);
    }
  }
  // scale
  pInput = pScratchOutput;
  load32x4_vr_postI(vr_input, pInput, INC1);  // aligned 16 bytes
  for (int ii = 0; ii < loopLim - 1; ii++) {
    vr_out = vmacs(vr_outputOffset, vr_input, vr_outputMultipler, 0);
    convert_32F_to_16I_x4(vr_out, 1 - 8, 1);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_out, 1);
    store32x1_vr_postI(vr_q7_out, pQ7Output, INC1, VRQ0);
    load32x4_vr_postI(vr_input, pInput, INC1);
  }
  // convert to 16I rnsat_pack
  vr_out = vmacs(vr_outputOffset, vr_input, vr_outputMultipler, 0);
  convert_32F_to_16I_x4(vr_out, 1 - 8, 1);
  rnd_sat_pack(vr_q7_out, VRQ0, vr_out, 1);
  store32x1_vr_postI(vr_q7_out, pQ7Output, INC1, VRQ0);
  if (remain) {
    load32x4_vr_postI(vr_input, pInput, INC1);
    vr_out = vmacs(vr_outputOffset, vr_input, vr_outputMultipler, 0);
    convert_32F_to_16I_x4(vr_out, 1 - 8, 1);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_out, 1);
    vr_q7_out = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0);

    for (int i = 0; i < remain; i++) {
      store8x1_vr_postI(vr_q7_out, pQ7Output, INC1, VRQ0);
      vr_q7_out = vpermsi(vr_q7_out, vr_q7_out, 0, 0);
    }
  }
}

void SVDFQauntizedInt8(OpData* data, const TfLiteSVDFParams* params,
                       const int8_t* input, const int32_t input_batches,
                       const int32_t input_height, const int8_t* weight_feature,
                       const int32_t feature_batches,
                       const int16_t* weight_time, const int32_t time_batches,
                       int n_memory, const int32_t* bias, int16_t* state_data,
                       int8_t* output) {
  const int16_t rank = params->rank;
  const int32_t unit_count = feature_batches / rank;

  memmove((int16_t*)state_data, (int16_t*)state_data + 1,
          (size_t)(input_batches * feature_batches * time_batches *
                   (int32_t)sizeof(int16_t)));

  int16_t* result_in_batch = state_data + (n_memory - 1);

  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    //    const int8_t *buffer_1 = weight_feature;

    // MVM8bx8b with input offset
    const int8_t* input_data_batch = input + i_batch * input_height;
    int16_t* output_data_batch =
        result_in_batch + i_batch * n_memory * feature_batches;
    // SVDFKernel8xn((const int32_t *)input_data_batch, (int32_t
    // *)weight_feature,(int32_t *) res_ptr,
    //     feature_batches,
    //     input_height, n_memory, 3);

    SVDFFeatMatInt8InputOffset(
        (int32_t*)input_data_batch, (const int32_t*)data->map_weight_feat,
        data->input_offset_int8, output_data_batch, feature_batches,
        input_height, n_memory, data->scaleFeat, 3);
  }

  // time
  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    int32_t* outputScratch = data->pScratch + i_batch * feature_batches;

    // const int16_t *v1 = weights_time_data;
    const int16_t* activation_state_batch =
        state_data + i_batch * time_batches * feature_batches;

    SVDFTimeInt16(data, weight_time, activation_state_batch, feature_batches,
                  time_batches, outputScratch);
  }

  // add bias, reduce, and rescale
  {
    SVDFBiasReduceScale(data, bias, input_batches, feature_batches, unit_count,
                        rank, output);
  }
}

#endif
#ifdef HMD1A_SVDF_OPT
// input MVM8bx8b with , output mutlipler,shift
int SVDFFeatMatInt8InputOffset(int32_t* x, const int32_t* A,
                               // const AScalar *bias,
                               int inputOffset, int16_t* output, int n_filter,
                               int n_input, int n_memory,
                               // const AScalar &outOffsetFr32,
                               const AScalar& outMultiplerFr32, int signs) {
  int16_t* pY = (int16_t*)output;  // act
  int m = n_filter;
  int n = n_input;
  const int32_t* pA = A;
  const int32_t* pX;
  // const int32_t *pB = (  const int32_t *)bias;
  int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2), 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 8
  int loopLimRow = ((m + 3) >> 2);         // group 4 alignment
  int processLastLoop = ((m & 3) != 0);

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  atbool signSpec = (atbool)signs;
  atbool signSpecInput = (atbool)3;

  vr64 VR_outMult;
  vr64 VR_inputOffset;
  // vr64 VR_outOffset;
  replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  replicate_ar(VR_inputOffset, 0x3, inputOffset);

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
      WUR_MvmAux(0);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(0);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(1);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(2);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      WUR_MvmAux(3);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 2); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      //   KN_PRINTX_VR128(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpecInput);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpec);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out;

      // VR_out = vadds(VR_y, VR_b0, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);

      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      // convert_32F_to_16I_x4(VR_out, (unsigned int)1, 0);
      // rnd_sat_pack(VR_q7_out, VRQ0, VR_out, 1);
      // VR_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      // accExt
      // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ0);
      // load_32x4_vr_a(VR_b1, UR_b, pB);

      convert_32F_to_16I_x2(VR_out, 1, 1);  // no rounding

      store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ1);

      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      // VR_out = vadds(VR_y, VR_b1, 0x0);
      VR_out = vmuls(VR_y, VR_outMult, 0);
      // VR_out = vadds(VR_out, VR_outOffset, 0);
      // VR_out = vexp_adji(VR_out, 8);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);

      // rnd_sat_pack(VR_q7_out, VRQ1, VR_out, 1);

      store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
      store16x1_vr_postR(VR_out, pY, n_memory, VRQ1);
    } else {
      // Convert and store outputs
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      vr64 VR_out;

      VR_out = vmuls(VR_y, VR_outMult, 0);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);

      for (int32_t j = 0; j < (m & 0x3) && j < 2; j++) {
        store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
        VR_out = vpermi(VR_out, VR_out, VSEL_YH_XH);
      }

      if ((m & 3) <= 2) {
        break;
      }
      VR_y = mov_vr_AccExtend();

      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
      convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

      VR_out = vmuls(VR_y, VR_outMult, 0);
      convert_32F_to_16I_x2(VR_out, (unsigned int)1, 1);

      for (int32_t j = 2; j < (m & 0x3) && j < 4; j++) {
        store16x1_vr_postR(VR_out, pY, n_memory, VRQ0);
        VR_out = vpermi(VR_out, VR_out, VSEL_YH_XH);
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}
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
    st_FR_postI(fr_out, output, 4);
  }
}

void SVDFBiasReduceScale(OpData* data, const int32_t* bias, int input_batches,
                         int feature_batches, int unit_count, int rank,
                         int8_t* Q7output) {
  int loopLim = (input_batches * unit_count) >> 1;
  int remain = (input_batches * unit_count) & 1;
  int32_t* pScratchInput = data->pScratch;
  int32_t* pScratchOutput = data->pScratchOutput;
  vr64 vr_input;
  vr64 vr_out, vr_q7_out;
  vr64 vr_outputMultipler;
  vr64 vr_outputOffset;  //+ zero_point
  const int32_t* pBias = bias;
  const int32_t* pInput = pScratchInput;
  const int32_t* pOutput = pScratchOutput;
  int8_t* pQ7Output = Q7output;
  fr32 fr_out = seta_fr(0, 0);

#ifdef KN_DEBUG
  // CHECK_ALIGN_4(  input_batches* unit_count);

#endif
  // TFLITE_CHECK_EQ(rank, 2); // optimized for rank=2
  replicate_ar(vr_outputMultipler, 0x3, data->scaleAct.fr);
  replicate_ar(vr_outputOffset, 0x3, data->outputOffset.fr);

  // scalar operation
  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    pInput = pScratchInput + i_batch * feature_batches;
    pOutput = pScratchOutput + i_batch * unit_count;
    pBias = bias;
    for (int ii = 0; ii < unit_count; ii++) {
      load32x1_vr_postI(vr_out, pBias, INC1, VRQ0);

      convert_32I_to_32F_x1(vr_out, 1, VRQ0);  // Q30
      fr_out = get_VRL(vr_out);
      for (int kk = 0; kk < rank; kk++) {
        load32x1_vr_postI(vr_input, pInput, INC1, VRQ0);
        // fadds(vr_out, VRQ0, vr_out, VRQ0,  vr_input, VRQ0, 0);
        fr_out = fadds(fr_out, get_VRL(vr_input), 0);
      }
      // store32x1_vr_postI(vr_out, pOutput, INC1, VRQ0);
      st_FR_postI(fr_out, pOutput, 4);
    }
  }
  // scale
  pInput = pScratchOutput;
  load32x2_vr_postI(vr_input, pInput, INC1);  // aligned 16 bytes
  for (int ii = 0; ii < loopLim - 1; ii++) {
    vr_out = vmacs(vr_outputOffset, vr_input, vr_outputMultipler, 0, 0);
    convert_32F_to_16I_x2(vr_out, 1 - 8, 1);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_out, vr_out, 1);
    store16x1_vr_postI(vr_q7_out, pQ7Output, INC1, VRQ0);
    load32x2_vr_postI(vr_input, pInput, INC1);
  }
  // convert to 16I rnsat_pack
  vr_out = vmacs(vr_outputOffset, vr_input, vr_outputMultipler, 0, 0);
  convert_32F_to_16I_x2(vr_out, 1 - 8, 1);
  rnd_sat_pack(vr_q7_out, VRQ0, vr_out, vr_out, 1);
  store16x1_vr_postI(vr_q7_out, pQ7Output, INC1, VRQ0);
  if (remain) {
    load32x1_vr_postI(vr_input, pInput, INC1, VRQ0);
    vr_out = vmacs(vr_outputOffset, vr_input, vr_outputMultipler, 0, 0);
    convert_32F_to_16I_x1(vr_out, 1 - 8, 1, VRQ0);
    rnd_sat_pack(vr_q7_out, VRQ0, vr_out, vr_out, 1);
    vr_q7_out = shift8_into32_arith(vr_q7_out, 24, 0, VRQ0, VRL);

    // for (int i = 0; i < remain; i++)
    // {
    store8x1_vr_postI(vr_q7_out, pQ7Output, INC1, VRQ0);
    // vr_q7_out = vpermsi(vr_q7_out, vr_q7_out, 0, 0);
    // }
  }
}

void SVDFQauntizedInt8(OpData* data, const TfLiteSVDFParams* params,
                       const int8_t* input, const int32_t input_batches,
                       const int32_t input_height, const int8_t* weight_feature,
                       const int32_t feature_batches,
                       const int16_t* weight_time, const int32_t time_batches,
                       int n_memory, const int32_t* bias, int16_t* state_data,
                       int8_t* output) {
  const int16_t rank = params->rank;
  const int32_t unit_count = feature_batches / rank;

  memmove((int16_t*)state_data, (int16_t*)state_data + 1,
          (size_t)(input_batches * feature_batches * time_batches *
                   (int32_t)sizeof(int16_t)));

  int16_t* result_in_batch = state_data + (n_memory - 1);

  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    //    const int8_t *buffer_1 = weight_feature;

    // MVM8bx8b with input offset
    const int8_t* input_data_batch = input + i_batch * input_height;
    int16_t* output_data_batch =
        result_in_batch + i_batch * n_memory * feature_batches;
    // SVDFKernel8xn((const int32_t *)input_data_batch, (int32_t
    // *)weight_feature,(int32_t *) res_ptr,
    //     feature_batches,
    //     input_height, n_memory, 3);

    SVDFFeatMatInt8InputOffset(
        (int32_t*)input_data_batch, (const int32_t*)data->map_weight_feat,
        data->input_offset_int8, output_data_batch, feature_batches,
        input_height, n_memory, data->scaleFeat, 3);
  }

  // time
  for (int i_batch = 0; i_batch < input_batches; i_batch++) {
    int32_t* outputScratch = data->pScratch + i_batch * feature_batches;

    // const int16_t *v1 = weights_time_data;
    const int16_t* activation_state_batch =
        state_data + i_batch * time_batches * feature_batches;

    SVDFTimeInt16(data, weight_time, activation_state_batch, feature_batches,
                  time_batches, outputScratch);
  }

  // add bias, reduce, and rescale
  {
    SVDFBiasReduceScale(data, bias, input_batches, feature_batches, unit_count,
                        rank, output);
  }
}

#endif
void EvalIntegerSVDFRef(TfLiteContext* context, TfLiteNode* node,
                        const TfLiteEvalTensor* input_tensor,
                        const TfLiteEvalTensor* weights_feature_tensor,
                        const TfLiteEvalTensor* weights_time_tensor,
                        const TfLiteEvalTensor* bias_tensor,
                        const TfLiteSVDFParams* params,
                        TfLiteEvalTensor* activation_state_tensor,
                        TfLiteEvalTensor* output_tensor,
                        const OpData& data_ex) {
  const int n_rank = params->rank;
  const int n_batch = input_tensor->dims->data[0];
  const int n_input = input_tensor->dims->data[1];
  const int n_filter = weights_feature_tensor->dims->data[0];
  const int n_unit = n_filter / n_rank;
  const int n_memory = weights_time_tensor->dims->data[1];
  const OpDataSvdf& data = data_ex.SvdfOp;

  TFLITE_DCHECK(context != nullptr);
  TFLITE_DCHECK(context->GetScratchBuffer != nullptr);

  int32_t* scratch_tensor = static_cast<int32_t*>(
      context->GetScratchBuffer(context, data.scratch_tensor_index));
  int32_t* scratch_output_tensor = static_cast<int32_t*>(
      context->GetScratchBuffer(context, data.scratch_output_tensor_index));

  // Shift states.
  int16_t* const state_ptr =
      tflite::micro::GetTensorData<int16_t>(activation_state_tensor);
  // memory move
  KN_PRINT_Q15_SIZE(state_ptr, n_batch * n_filter * n_memory);
  // Left shift the activation_state.
  {
    int16_t* new_state_start = state_ptr;
    const int16_t* old_state_start = state_ptr + 1;
    const int16_t* old_state_end = state_ptr + n_batch * n_filter * n_memory;
    while (old_state_start != old_state_end) {
      *new_state_start++ = *old_state_start++;
    }
  }
  // new activation state tensor

  // Note: no need to clear the latest activation, matmul is not accumulative.

  // Feature matmul.
  {
    int16_t* state =
        tflite::micro::GetTensorData<int16_t>(activation_state_tensor);
    const int8_t* input = tflite::micro::GetTensorData<int8_t>(input_tensor);
    const int8_t* weight_feature =
        tflite::micro::GetTensorData<int8_t>(weights_feature_tensor);
    const int32_t output_max = std::numeric_limits<int16_t>::max();
    const int32_t output_min = std::numeric_limits<int16_t>::min();
    int16_t* result_in_batch = state + (n_memory - 1);
    for (int b = 0; b < n_batch; b++) {
      const int8_t* matrix_ptr = weight_feature;
      for (int r = 0; r < n_filter; r++) {
        int32_t dot_prod = 0;
        const int8_t* vector_in_batch = input + b * n_input;
        for (int c = 0; c < n_input; c++) {
          dot_prod +=
              *matrix_ptr++ * (*vector_in_batch++ - data.input_zero_point);
        }

        dot_prod = MultiplyByQuantizedMultiplier(
            dot_prod, data.effective_scale_1_a, data.effective_scale_1_b);

        dot_prod = std::min(std::max(output_min, dot_prod), output_max);

        // This assumes state is symmetrically quantized. Otherwise last bit of
        // state should be initialized to its zero point and accumulate the
        // dot_prod.
        // Equivalent as the following:
        //     result_in_batch = zero point, which happens to be zero.
        //     result_in_batch += dot_prod_56.
        *result_in_batch = dot_prod;
        result_in_batch += n_memory;
      }
    }
  }
  // Time.

  {
    for (int b = 0; b < n_batch; ++b) {
      int32_t* scratch_ptr_batch = scratch_tensor + b * n_filter;

      // Perform batched vector dot product:
      const int16_t* vector1_ptr =
          tflite::micro::GetTensorData<int16_t>(weights_time_tensor);
      const int16_t* vector2_ptr =
          tflite::micro::GetTensorData<int16_t>(activation_state_tensor) +
          b * n_memory * n_filter;

      for (int i = 0; i < n_filter; i++) {
        *scratch_ptr_batch = 0;
        for (int j = 0; j < n_memory; j++) {
          *scratch_ptr_batch += *vector1_ptr++ * *vector2_ptr++;
        }
        scratch_ptr_batch++;
      }
    }
  }

  // Reduce, add bias, rescale, activation.
  {
    // Add bias.
    if (bias_tensor) {
      // Vector batch assign:
      const int32_t* bias_data =
          tflite::micro::GetTensorData<int32_t>(bias_tensor);
      for (int i = 0; i < n_batch; ++i) {
        int32_t* output_ptr = scratch_output_tensor + i * n_unit;
        const int32_t* bias_ptr = bias_data;
        for (int j = 0; j < n_unit; ++j) {
          *output_ptr++ = *bias_ptr++;
        }
      }
    } else {
      int32_t* output_ptr = scratch_output_tensor;
      for (int i = 0; i < n_batch * n_unit; ++i) {
        *output_ptr++ = 0;
      }
    }
    // Reduce.
    for (int b = 0; b < n_batch; ++b) {
      int32_t* output_temp_ptr = scratch_output_tensor + b * n_unit;
      int32_t* scratch_ptr_batch = scratch_tensor + b * n_filter;

      // Reduction sum vector
      for (int i = 0; i < n_unit; ++i) {
        for (int j = 0; j < n_rank; ++j) {
          output_temp_ptr[i] += *scratch_ptr_batch++;
        }
      }
    }
    // Rescale.
    const int32_t output_max = std::numeric_limits<int8_t>::max();
    const int32_t output_min = std::numeric_limits<int8_t>::min();
    for (int i = 0; i < n_batch * n_unit; ++i) {
      int32_t x1 = scratch_output_tensor[i];

      int32_t x2 = MultiplyByQuantizedMultiplier(x1, data.effective_scale_2_a,
                                                 data.effective_scale_2_b);

      int32_t x3 = x2 + data.output_zero_point;

      int32_t x4 = std::min(std::max(output_min, x3), output_max);

      tflite::micro::GetTensorData<int8_t>(output_tensor)[i] =
          static_cast<int8_t>(x4);
    }
  }
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
#if defined(DMX1A_SVDF_OPT) || defined(HMD1A_SVDF_OPT)

  OpDataSvdf* data = static_cast<OpDataSvdf*>(&data_ex->SvdfOp);
  if (data_ex->opt_constraint == 1) {
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

  } else
#endif
  {

    EvalIntegerSVDFRef(context, node, input_tensor, weights_feature_tensor,
                       weights_time_tensor, bias_tensor, params,
                       activation_state_tensor, output_tensor, *data_ex);
  }
}

void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus Prepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->builtin_data != nullptr);

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
#if !(defined(DMX1A_SVDF_OPT) || defined(HMD1A_SVDF_OPT))
    data_ex->opt_constraint = 0;
    // check able to optimized  input as multiple of 8 ~ 64
    //   int input_length = input->dims->data[0];
#else
    // if(input_size <=64 && (input_size &3)==0)
    {
      data_ex->opt_constraint = 1;

      if (data_ex->opt_constraint) {
        int32_t* p_dmx1a_fc_mapped_filter = nullptr;

        const TfLiteEvalTensor* filterEval =
            tflite::micro::GetEvalInput(context, node, kWeightsFeatureTensor);
        const int8_t* filter_input =
            tflite::micro::GetTensorData<int8_t>(filterEval);
        const int32_t map_coeff_size = tflite::FullyConnectedMap8bitCoeffs(
            NULL, NULL, num_filters, input_size);

        // if(params->weights_format ==
        // kTfLiteFullyConnectedWeightsFormatDefault)
        KN_PRINTD(map_coeff_size);
        if (!tflite::is_coeffs_mapped(context)) {
          KN_PRINTD(map_coeff_size);
          // KN_TFLM_PRINT_Q7_SIZE(context, filter_input, (output_depth
          // *accum_depth));

          p_dmx1a_fc_mapped_filter =
              (int32_t*)context->AllocatePersistentBuffer(context,
                                                          map_coeff_size);
          if (p_dmx1a_fc_mapped_filter) {
            tflite::FullyConnectedMap8bitCoeffs(
                (int8_t*)p_dmx1a_fc_mapped_filter, (int8_t*)filter_input,
                num_filters, input_size);
          }
          KN_PRINT_Q7_SIZE(p_dmx1a_fc_mapped_filter, map_coeff_size);
        } else {
          p_dmx1a_fc_mapped_filter = (int32_t*)filter_input;  // remapping
          // KN_PRINT_Q7_SIZE( p_dmx1a_fc_mapped_filter,map_coeff_size);
        }

        data_ex->map_weight_feat = (int32_t*)p_dmx1a_fc_mapped_filter;
        // const TfLiteEvalTensor* biasEval =
        // tflite::micro::GetEvalInput(context, node, kBiasTensor); 	const
        // int32_t
        //*bias_input =  tflite::micro::GetTensorData<int32_t>(biasEval);
        //
        // tflite::ConvertQ31ToAfloat(bias_input,(AScalar*) bias_input, , 17);
        tflite::ConvertQ31ToAfloat(data->effective_scale_1_a,
                                   data_ex->scaleFeat,
                                   data->effective_scale_1_b);
        tflite::ConvertQ31ToAfloat(data->effective_scale_2_a, data_ex->scaleAct,
                                   data->effective_scale_2_b + 16);
        uint8_t offsetInput = -(data->input_zero_point & 0xff);
        KN_PRINTD(data->input_zero_point);
        // uint32_t offsetVR=offsetInput;
        data_ex->input_offset_int8 = (offsetInput << 24) | (offsetInput << 16) |
                                     (offsetInput << 8) | offsetInput;
        //			offsetInput = ( data->input_zero_point&0xff);
        //				data->input_offset_int8_neg =
        //(offsetInput<<24)|(offsetInput<<16)|(offsetInput<<8)|offsetInput;
        KN_PRINTD(data_ex->input_offset_int8);
        tflite::ConvertQ31ToAfloat(data->output_zero_point,
                                   data_ex->outputOffset, 17);
        KN_PRINTAFLT(data_ex->outputOffset);
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

TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteSVDFParams*>(node->builtin_data);
  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data_ex = *(static_cast<const OpData*>(node->user_data));
  const OpDataSvdf& data = static_cast<const OpDataSvdf>(data_ex.SvdfOp);
  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  const TfLiteEvalTensor* weights_feature =
      tflite::micro::GetEvalInput(context, node, kWeightsFeatureTensor);
  const TfLiteEvalTensor* weights_time =
      tflite::micro::GetEvalInput(context, node, kWeightsTimeTensor);
  const TfLiteEvalTensor* bias =
      (NumInputs(node) == 5)
          ? tflite::micro::GetEvalInput(context, node, kBiasTensor)
          : nullptr;
  TfLiteEvalTensor* activation_state = tflite::micro::GetMutableEvalInput(
      context, node, kInputActivationStateTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  switch (weights_feature->type) {
#ifndef REMOVE_FLOAT_SUPPORT
    case kTfLiteFloat32: {
      EvalFloatSVDF(context, node, input, weights_feature, weights_time, bias,
                    params, data.scratch_tensor_index, activation_state,
                    output);

      break;
    }
#endif

    case kTfLiteInt8: {
      switch (weights_time->type) {
        case kTfLiteInt16: {
          EvalInt16SvdfReference(context, node, input, weights_feature,
                                 weights_time, bias, params, activation_state,
                                 output, data);
          break;
        }
        case kTfLiteInt8: {
          EvalInt8SvdfReference(context, node, input, weights_feature,
                                weights_time, bias, params, activation_state,
                                output, data);
          break;
        }
        default:
          TF_LITE_KERNEL_LOG(context, "Type %s not currently supported.",
                             TfLiteTypeGetName(weights_time->type));
          return kTfLiteError;
      }

      KN_PRINT_Q7_SIZE(output->data.int8, ElementCount(*output->dims));

      break;
    }

    default:
      TF_LITE_KERNEL_LOG(context, "Type %s not currently supported.",
                         TfLiteTypeGetName(weights_feature->type));
      return kTfLiteError;
  }
  return kTfLiteOk;
}

TfLiteStatus EvalInt8(TfLiteContext* context, TfLiteNode* node) {
  auto* params = reinterpret_cast<TfLiteSVDFParams*>(node->builtin_data);
  TFLITE_DCHECK(node->user_data != nullptr);
  const OpData& data = *(static_cast<const OpData*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kInputTensor);
  const TfLiteEvalTensor* weights_feature =
      tflite::micro::GetEvalInput(context, node, kWeightsFeatureTensor);
  const TfLiteEvalTensor* weights_time =
      tflite::micro::GetEvalInput(context, node, kWeightsTimeTensor);
  const TfLiteEvalTensor* bias =
      (NumInputs(node) == 5)
          ? tflite::micro::GetEvalInput(context, node, kBiasTensor)
          : nullptr;
  TfLiteEvalTensor* activation_state = tflite::micro::GetMutableEvalInput(
      context, node, kInputActivationStateTensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kOutputTensor);

  if (weights_feature->type != kTfLiteInt8) {
    TF_LITE_KERNEL_LOG(context, "Type %s not currently supported.",
                       TfLiteTypeGetName(weights_feature->type));
    return kTfLiteError;
  }
  EvalIntegerSVDF(context, node, input, weights_feature, weights_time, bias,
                  params, activation_state, output, (OpData*)&data);

  return kTfLiteOk;
}
}  // namespace

TFLMRegistration Register_SVDF() {
  return tflite::micro::RegisterOp(Init,
                                   /*prepare=*/Prepare,
                                   /*invoke=*/Eval);
}
TFLMRegistration Register_SVDF_INT8() {
  return tflite::micro::RegisterOp(Init,
                                   /*prepare=*/Prepare,
                                   /*invoke=*/EvalInt8);
}
}  // namespace tflite
