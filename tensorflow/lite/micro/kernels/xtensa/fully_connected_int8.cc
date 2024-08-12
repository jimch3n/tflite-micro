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
#define REMOVE_INPLACE_BIAS  // for avoid twice prepare overritten it

#define UNALIGNED_OPERATOR  // support that operator's weight cannot convert to
                            // aligned mode

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/portable_tensor_utils.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/fully_connected.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/xtensa/xtensa.h"
#include "tensorflow/lite/micro/kernels/xtensa/xtensa_fully_connected.h"
#include "tensorflow/lite/micro/micro_utils.h"

// for hifi
#include <xtensa/config/core-isa.h>
#include "xtensa/tie/xt_hifi2.h"
#include "xa_nnlib_common_macros.h"
#include "xa_nnlib_hifi_isa_compat.h"
namespace tflite {

TfLiteStatus XtensaEvalFullyConnectedQuantizedInt8(
    TfLiteContext* context, TfLiteNode* node, const OpDataFullyConnected& data,
    const TfLiteEvalTensor* input, const TfLiteEvalTensor* filter,
    const TfLiteEvalTensor* bias, TfLiteEvalTensor* output) {
#if !defined(VISION_P6)
  const int32_t* bias_data =
      tflite::micro::GetOptionalTensorData<int32_t>(bias);

  // P6 Vision will handle INT4 filters as a reference operation.
  // For all other architectures, unpack INT4 here.
  const int8_t* filter_data = tflite::micro::GetTensorData<int8_t>(filter);
  if (filter->type == kTfLiteInt4) {
    int8_t* unpacked_filter_data = static_cast<int8_t*>(
        context->GetScratchBuffer(context, data.filter_buffer_index));

    tflite::tensor_utils::UnpackDenseInt4IntoInt8(
        tflite::micro::GetTensorData<int8_t>(filter),
        tflite::micro::GetTensorShape(filter).FlatSize(), unpacked_filter_data);
    filter_data = unpacked_filter_data;
  }
#endif  // !defined(VISION_P6)

#if defined(HIFIMINI)
  FullyConnectedEvalHifimini(FullyConnectedParamsQuantized(data),
                             tflite::micro::GetTensorShape(input),
                             tflite::micro::GetTensorData<int8_t>(input),
                             tflite::micro::GetTensorShape(filter), filter_data,
                             tflite::micro::GetTensorShape(bias), bias_data,
                             tflite::micro::GetTensorShape(output),
                             tflite::micro::GetTensorData<int8_t>(output));
#elif defined(HIFI3) || defined(HIFI4) || defined(HIFI5)
  const RuntimeShape& output_shape = tflite::micro::GetTensorShape(output);
  const int num_batches =
      FlatSizeSkipDim(output_shape, output_shape.DimensionsCount() - 1);
  const int output_depth =
      output_shape.Dims(output_shape.DimensionsCount() - 1);

  const RuntimeShape& filter_shape = tflite::micro::GetTensorShape(filter);
  const int filter_dim_count = filter_shape.DimensionsCount();
  const int accum_depth = filter_shape.Dims(filter_dim_count - 1);

  FullyConnectedParams op_params = FullyConnectedParamsQuantized(data);
  for (int b = 0; b < num_batches; ++b) {
    TF_LITE_ENSURE_EQ(
        context,
        xa_nn_fully_connected_sym8sxasym8s_asym8s(
            (tflite::micro::GetTensorData<int8_t>(output) + b * output_depth),
            filter_data,
            (tflite::micro::GetTensorData<int8_t>(input) + b * accum_depth),
            bias_data, accum_depth, output_depth, op_params.input_offset,
            op_params.output_multiplier, op_params.output_shift,
            op_params.output_offset),
        0);
  }

  int8_t* output_arr = tflite::micro::GetTensorData<int8_t>(output);
  TF_LITE_ENSURE_EQ(context,
                    xa_nn_vec_activation_min_max_8_8(
                        output_arr, output_arr, data.output_activation_min,
                        data.output_activation_max, num_batches * output_depth),
                    0);
#elif defined(VISION_P6)
  const auto& params =
      *(reinterpret_cast<TfLiteConvParams*>(node->builtin_data));
  const auto& op_data =
      *(reinterpret_cast<XtensaFullyConnectedOpData*>(node->user_data));
  FullyConnectedEvalVision(context, node, params, op_data, input, filter, bias,
                           output);
#else
  reference_integer_ops::FullyConnected(
      FullyConnectedParamsQuantized(data), tflite::micro::GetTensorShape(input),
      tflite::micro::GetTensorData<int8_t>(input),
      tflite::micro::GetTensorShape(filter), filter_data,
      tflite::micro::GetTensorShape(bias), bias_data,
      tflite::micro::GetTensorShape(output),
      tflite::micro::GetTensorData<int8_t>(output));
#endif  // defined(HIFI3) || defined(HIFI4) || defined(HIFI5)

  return kTfLiteOk;
}

namespace {

TfLiteStatus EvalInt8(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->user_data != nullptr);
#ifndef USE_HMD_MVM_OPT
  const auto& data =
      *(static_cast<const OpDataFullyConnected*>(node->user_data));

  const TfLiteEvalTensor* input =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
  const TfLiteEvalTensor* filter =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);
  const TfLiteEvalTensor* bias =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);

  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

  return XtensaEvalFullyConnectedQuantizedInt8(context, node, data, input,
                                               filter, bias, output);
#else
  TfLiteStatus status = kTfLiteOk;
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedInputTensor);
  const TfLiteEvalTensor *filter =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedWeightsTensor);
  const TfLiteEvalTensor *bias =
      tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kFullyConnectedOutputTensor);

  TFLITE_DCHECK(node->user_data != nullptr);
  const OpDataFullyConnectedEx &data_ex =
      *(static_cast<const OpDataFullyConnectedEx *>(node->user_data));

  status = HmdEvalFullyConnectedQuantizedInt8(context, node, data_ex, input,
                                              filter, bias, output);
  return status;
#endif
}

}  // namespace

//#else
//// HMD MVM_OP

void *HmdInitFullyConnected(TfLiteContext *context, const char *buffer,
                            size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context,
                                           sizeof(OpDataFullyConnectedEx));
}

void MVMInputOffsetPrepareWithBias(const int32_t *A, int32_t *output, int m,
                                   int n, uint32_t input_offset,
                                   const int32_t *bias, int bias_shift) {
  // int32_t *pY = output;

  const int32_t *pA = A;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
                                    // int processLastLoop = ((m & 3) != 0);
  const int32_t *pB = bias;

  int32_t *pOutput = output;
  vr64 VR_A;

  vr64 VR_y, VR_x;
  atbool signSpecInput = atbool(3);
  ulsr32 UR_b = align_32x2_load(pB);
  vr64 VR_inputOffset;
  replicate_ar(
      VR_inputOffset, 0x3,
      input_offset);  // -1 ~ -127
                      // replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);

  for (int i = 0; i < loopLimRow; i++) {
    // const int32_t *pA1 = pA;
    // VR_y = vseta_vr(0, 0);

    load_32x2_vr_a(VR_y, UR_b, pB);
    VR_y = shift32_arith(VR_y, bias_shift, 0);
    load_32x2_vr_a(VR_x, UR_b, pB);
    VR_x = shift32_arith(VR_x, bias_shift, 0);
    mov_AccExtend_vr(VR_x);

    // pA = pA1;
    ulsr32 UR_A = align_32x2_load(pA);
    load_32x2_vr_a(VR_A, UR_A, pA);

    for (int j = 0; j < loopLimCol; j++) {
      // WUR_MvmAux(0);
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
      load_32x2_vr_a(VR_A, UR_A, pA);

      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }
    for (int32_t j = (loopLimCol << 2); j < nBlockAligned2; j++) {
      mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }
    // if(processLastLoop)
    store32x2_vr_postI(VR_y, pOutput, INC1);
    store_AccExtend_postI(pOutput, INC1);

    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
}

int FullyConnectedKernel(int32_t *x, const int32_t *A, const AScalar *bias,
                         int8_t *output, int m, int n,
                         // const AScalar &outOffsetFr32,
                         const uint32_t input_offset_int8x4,  // xor 128
                         // const AScalar &outMultiplerFr32,
                         int signs, int b_shift, int output_offset,
                         int32_t out_multiplier, int out_shift) {
  int8_t *pY = output;

  const int32_t *pA = A;
  const int32_t *pX;
  const int32_t *pB = (const int32_t *)bias;
  // int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2),
  // 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
  int processLastLoop = ((m & 3) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x2_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }

  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  vr64 VR_inputOffset;
  atbool signSpec = atbool(signs);

  int left_shift, right_shift;
  left_shift = out_shift < 0 ? 0 : out_shift;
  right_shift = out_shift > 0 ? 0 : -out_shift;
  // vr64 VR_outMult;
  // vr64 VR_outOffset;
  vr64 VR_b0 = vseta_vr(kConstTable_Zero, 0);

  ae_int32x2 ae_out_multiplier = AE_MOVDA32(out_multiplier);
  ae_int32x2 ae_output_offset = AE_MOVDA32(output_offset);
  // replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  // replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);
  KN_PRINTD(signs);
  KN_PRINTD(output_offset);
  KN_PRINTX(out_multiplier);
  KN_PRINTD(out_shift);
  KN_PRINTD(loopLimRow);
  KN_PRINTD(loopLimCol);
  replicate_ar(VR_inputOffset, 0x3, input_offset_int8x4);
  ae_int32x2 max_int8 = AE_MOVDA32(127);
  ae_int32x2 min_int8 = AE_MOVDA32(-128);
  for (int i = 0; i < loopLimRow; i++) {
    pX = x;
    ulsr32 UR_A = align_32x2_load(pA);
    ulsr32 UR_x = align_32x2_load(pX);
    ulsr32 UR_b;
    load_32x2_vr_a(VR_A, UR_A, pA);

    if (pB) {
      UR_b = align_32x2_load(pB);
      load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
#ifdef REMOVE_INPLACE_BIAS
      // convert_32I_to_32F_x1(VR_b0, 17, VRQ0);
      // convert_32I_to_32F_x1(VR_b0, 17, VRQ1);
#endif
      VR_y = shift32_arith(VR_b0, b_shift, 0);
      // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_b0, UR_b, pB);
      VR_b0 = shift32_arith(VR_b0, b_shift, 0);
      // KN_PRINTX_VR64(VR_b0);
      mov_AccExtend_vr(VR_b0);
    } else {
      VR_y = vseta_vr(0, 0);
      mov_AccExtend_vr(VR_y);
    }

    for (int j = 0; j < loopLimCol; j++) {
      load_32x2_vr_a(VR_x, UR_x, pX);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(0);
      // KN_PRINTX_VR64(VR_y);  KN_PRINTX_VR64(VR_x);//KN_PRINTX_VR64(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
      // KN_PRINTX_VR64(VR_x);KN_PRINTX_VR64(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
      // KN_PRINTX_VR64(VR_x);KN_PRINTX_VR64(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
      // KN_PRINTX_VR64(VR_x);KN_PRINTX_VR64(VR_A);
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);  // KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    for (int32_t j = (loopLimCol << 2); j < nBlockAligned2; j++) {
      load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
      KN_PRINTX_VR64(VR_x);
      KN_PRINTX_VR64(VR_A);
      VR_x = vbool(VR_x, VR_inputOffset, 0x6);
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);
      KN_PRINTX_VR64(VR_y);
      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      // KN_PRINTX_VR64(VR_y);
      VR_y = shift32_arith(VR_y, -b_shift, 0);
      // KN_PRINTX_VR64(VR_y);

      ae_int32x2 ae_in =
          AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));
      KN_PRINTX_AE32X2(ae_in);
      ae_int32x2 ae_out0 = AE_SLAA32S(ae_in, left_shift);
      ae_out0 = AE_MULFP32X2RAS(ae_out0, ae_out_multiplier);
      ae_out0 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out0), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out0), right_shift));
      KN_PRINTX_AE32X2(ae_out0);
      VR_y = mov_vr_AccExtend();
      VR_y = shift32_arith(VR_y, -b_shift, 0);
      // AE_L32X2_IP(d_bias, (ae_int32x2 *)pB, 2*sizeof(WORD32));

      ae_in = AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));

      //  d_out32 = AE_ADD32S(ae_in, d_bias);

      ae_int32x2 ae_out1 = AE_SLAA32S(ae_in, left_shift);
      ae_out1 = AE_MULFP32X2RAS(ae_out1, ae_out_multiplier);
      ae_out1 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out1), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out1), right_shift));
      ae_out0 = AE_ADD32S(ae_out0, ae_output_offset);
      ae_out0 = AE_MAX32(ae_out0, min_int8);
      ae_out0 = AE_MIN32(ae_out0, max_int8);
      vr64 VR_out;
      set_VRL(VR_out, AE_MOVAD32_L(ae_out0));
      set_VRH(VR_out, AE_MOVAD32_H(ae_out0));
      VR_out = shift32_arith(VR_out, 24, 0);

      store8x2_vr_postI(VR_out, pY, INC1);

      ae_out1 = AE_ADD32S(ae_out1, ae_output_offset);

      ae_out1 = AE_MAX32(ae_out1, min_int8);
      ae_out1 = AE_MIN32(ae_out1, max_int8);

      KN_PRINTX_AE32X2(ae_out0);
      KN_PRINTX_AE32X2(ae_out1);

      set_VRL(VR_out, AE_MOVAD32_L(ae_out1));
      set_VRH(VR_out, AE_MOVAD32_H(ae_out1));
      VR_out = shift32_arith(VR_out, 24, 0);

      store8x2_vr_postI(VR_out, pY, INC1);

    } else {
      VR_y = shift32_arith(VR_y, -b_shift, 0);
      KN_PRINTX_VR64(VR_y);

      ae_int32x2 ae_in =
          AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));
      // KN_PRINTX_AE32X2(ae_in);

      ae_int32x2 ae_out0 = AE_SLAA32S(ae_in, left_shift);
      ae_out0 = AE_MULFP32X2RAS(ae_out0, ae_out_multiplier);
      ae_out0 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out0), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out0), right_shift));
      // KN_PRINTX_AE32X2(ae_out0);
      VR_y = mov_vr_AccExtend();
      VR_y = shift32_arith(VR_y, -b_shift, 0);

      ae_in = AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));

      ae_int32x2 ae_out1 = AE_SLAA32S(ae_in, left_shift);
      ae_out1 = AE_MULFP32X2RAS(ae_out1, ae_out_multiplier);
      ae_out1 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out1), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out1), right_shift));
      ae_out0 = AE_ADD32S(ae_out0, ae_output_offset);
      ae_out1 = AE_ADD32S(ae_out1, ae_output_offset);
      ae_out0 = AE_MAX32(ae_out0, min_int8);
      ae_out0 = AE_MIN32(ae_out0, max_int8);

      ae_out1 = AE_MAX32(ae_out1, min_int8);
      ae_out1 = AE_MIN32(ae_out1, max_int8);

      KN_PRINTX_AE32X2(ae_out0);
      KN_PRINTX_AE32X2(ae_out1);

      vr64 VR_out, VR_out2;
      set_VRL(VR_out, AE_MOVAD32_L(ae_out0));
      set_VRH(VR_out, AE_MOVAD32_H(ae_out0));
      VR_out = shift32_arith(VR_out, 24, 0);

      set_VRL(VR_out2, AE_MOVAD32_L(ae_out1));
      //   set_VRH(VR_out, AE_MOVAD32_H(ae_out1));
      VR_out2 = shift32_arith(VR_out2, 24, 0);

      switch (m & 0x3) {
        case 3:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          store8x1_vr_postI(VR_out2, pY, INC1, VRQ0);
          break;
        case 2:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          break;
        case 1:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}
int FullyConnectedKernelInputOffset(int32_t *x, const int32_t *A,
                                    // const AScalar *bias,
                                    int8_t *output, int m,
                                    int n,  // const AScalar &outOffsetFr32,
                                    const int32_t *inputOffsetWithW,  // xor 128
                                    // const AScalar &outMultiplerFr32,
                                    int signs, int b_shift, int output_offset,
                                    int32_t out_multiplier, int out_shift) {
  int8_t *pY = output;

  const int32_t *pA = A;
  const int32_t *pX;
  // const int32_t *pB = (const int32_t *)bias;
  // int exp_fxp = (signs == 3) ? 15 : ((signs == 1) ? 16 : 17);  // 31-(14+2),
  // 31-
  // const int bias_exp = 17;
  // const int output_offset_exp = 17;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
  int processLastLoop = ((m & 3) != 0);

  // FIX for input size pointer is not align 4 bytes  and  loopLimCol != 0
  // prevent using load_32x2_vr_a unalign,
  // nBlockAlign2 loopLimCol = 0, using load16x2 loop to run iteration
  if (((unsigned int)x & 3) != 0 && loopLimCol != 0) {
    loopLimCol = 0;
  }

  if (((unsigned int)x & 1) != 0) {
    return -1;
  }
  vr64 VR_A;
  vr64 VR_x;
  vr64 VR_y;
  // vr64 VR_inputOffset;
  atbool signSpec = atbool(signs);

  // vr64 VR_outMult;
  // vr64 VR_outOffset;
  // vr64 VR_b0 = vseta_vr(kConstTable_Zero, 0);
  const int32_t *inputOffsetW = inputOffsetWithW;
  // replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
  // replicate_ar(VR_outOffset, 0x3, outOffsetFr32.fr);

  int left_shift, right_shift;
  left_shift = out_shift < 0 ? 0 : out_shift;
  right_shift = out_shift > 0 ? 0 : -out_shift;
  ae_int32x2 max_int8 = AE_MOVDA32(127);
  ae_int32x2 min_int8 = AE_MOVDA32(-128);

  // replicate_ar(VR_inputOffset, 0x3, input_offset_int8x4);
  for (int i = 0; i < loopLimRow; i++) {
    if (inputOffsetW) {
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
    // ulsr32 UR_b;
    load_32x2_vr_a(VR_A, UR_A, pA);

    for (int j = 0; j < loopLimCol; j++) {
      load_32x2_vr_a(VR_x, UR_x, pX);
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
      WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
      mac8bx8b(VR_y, VR_A, VR_x, signSpec);

      load_32x2_vr_a(VR_A, UR_A, pA);
    }

    if (i != (loopLimRow - 1) || !processLastLoop) {
      KN_PRINTX_VR64(VR_y);
      VR_y = shift32_arith(VR_y, -b_shift, 0);
      KN_PRINTX_VR64(VR_y);

      ae_int32x2 ae_in =
          AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));
      KN_PRINTX_AE32X2(ae_in);
      ae_int32x2 ae_out0 = AE_SLAA32S(ae_in, left_shift);

      ae_out0 = AE_MULFP32X2RAS(ae_out0, AE_MOVDA32(out_multiplier));
      ae_out0 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out0), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out0), right_shift));
      KN_PRINTX_AE32X2(ae_out0);
      VR_y = mov_vr_AccExtend();
      VR_y = shift32_arith(VR_y, -b_shift, 0);
      // AE_L32X2_IP(d_bias, (ae_int32x2 *)pB, 2*sizeof(WORD32));

      ae_in = AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));

      //  d_out32 = AE_ADD32S(ae_in, d_bias);

      ae_int32x2 ae_out1 = AE_SLAA32S(ae_in, left_shift);
      ae_out1 = AE_MULFP32X2RAS(ae_out1, AE_MOVDA32(out_multiplier));
      ae_out1 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out1), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out1), right_shift));
      ae_out0 = AE_ADD32S(ae_out0, AE_MOVDA32(output_offset));

      ae_out1 = AE_ADD32S(ae_out1, AE_MOVDA32(output_offset));
      ae_out0 = AE_MAX32(ae_out0, min_int8);
      ae_out0 = AE_MIN32(ae_out0, max_int8);

      ae_out1 = AE_MAX32(ae_out1, min_int8);
      ae_out1 = AE_MIN32(ae_out1, max_int8);

      KN_PRINTX_AE32X2(ae_out0);
      KN_PRINTX_AE32X2(ae_out1);
      // KN_PRINTX_AE32X2(ae_out1);
      //   ae_int16x4     out16_0 = AE_SAT16X4(ae_out0, ae_out1);
      vr64 VR_out;
      set_VRL(VR_out, AE_MOVAD32_L(ae_out0));
      set_VRH(VR_out, AE_MOVAD32_H(ae_out0));
      VR_out = shift32_arith(VR_out, 24, 0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ1);

      set_VRL(VR_out, AE_MOVAD32_L(ae_out1));
      set_VRH(VR_out, AE_MOVAD32_H(ae_out1));
      VR_out = shift32_arith(VR_out, 24, 0);

      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
    } else {
      VR_y = shift32_arith(VR_y, -b_shift, 0);
      KN_PRINTX_VR64(VR_y);

      ae_int32x2 ae_in =
          AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));
      // KN_PRINTX_AE32X2(ae_in);

      ae_int32x2 ae_out0 = AE_SLAA32S(ae_in, left_shift);
      ae_out0 = AE_MULFP32X2RAS(ae_out0, AE_MOVDA32(out_multiplier));
      ae_out0 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out0), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out0), right_shift));
      // KN_PRINTX_AE32X2(ae_out0);
      VR_y = mov_vr_AccExtend();
      VR_y = shift32_arith(VR_y, -b_shift, 0);

      ae_in = AE_MOVDA32X2(move32_ar_vr(VR_y, VRQ1), move32_ar_vr(VR_y, VRQ0));

      ae_int32x2 ae_out1 = AE_SLAA32S(ae_in, left_shift);
      ae_out1 = AE_MULFP32X2RAS(ae_out1, AE_MOVDA32(out_multiplier));
      ae_out1 =
          AE_ROUND32X2F64SSYM(AE_SRAA64(AE_CVT64F32_H(ae_out1), right_shift),
                              AE_SRAA64(AE_CVT64F32_L(ae_out1), right_shift));
      ae_out0 = AE_ADD32S(ae_out0, AE_MOVDA32(output_offset));
      ae_out1 = AE_ADD32S(ae_out1, AE_MOVDA32(output_offset));
      ae_out0 = AE_MAX32(ae_out0, min_int8);
      ae_out0 = AE_MIN32(ae_out0, max_int8);

      ae_out1 = AE_MAX32(ae_out1, min_int8);
      ae_out1 = AE_MIN32(ae_out1, max_int8);

      KN_PRINTX_AE32X2(ae_out0);
      KN_PRINTX_AE32X2(ae_out1);

      vr64 VR_out, VR_out2;
      set_VRL(VR_out, AE_MOVAD32_L(ae_out0));
      set_VRH(VR_out, AE_MOVAD32_H(ae_out0));
      VR_out = shift32_arith(VR_out, 24, 0);

      set_VRL(VR_out2, AE_MOVAD32_L(ae_out1));
      //   set_VRH(VR_out, AE_MOVAD32_H(ae_out1));
      VR_out2 = shift32_arith(VR_out2, 24, 0);

      switch (m & 0x3) {
        case 3:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          store8x1_vr_postI(VR_out2, pY, INC1, VRQ0);
          break;
        case 2:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
          break;
        case 1:
          store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
          break;
      }
    }
    // Adjust pointer to compensate for loop priming
    pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
  }
  return 0;
}

static void FullyConnectedQuantizedInt8(
    TfLiteContext *context, tflite::FullyConnectedParams &op_params,
    const OpDataFullyConnectedEx &data, const int8_t *inputLocal,
    const int8_t *filterMVM, const int32_t *baisMVM, const int8_t *outputLocal,
    const int batches, const int accum_depth, const int output_depth,
    TfLiteType type) {
  int8_t *p_fc_mapped_filter = (int8_t *)data.mapped_filter;
  // int8_t *p_dmx1a_fc_aligned_input  = nullptr;

  // if (data.buffer_idx > -1) {
  //	p_dmx1a_fc_aligned_input = (int8_t *)context->GetScratchBuffer(context,
  // data.buffer_idx);
  //}
  // KN_PRINT_Q31_SIZE(baisMVM, output_depth);
  int sign = 3;
  //			int input_aligned4 = data.is_input_align_4;
  sign = (128 == op_params.input_offset)
             ? 1
             : sign;  // assumption: 128 + sign 8bit = unsigned

  int batch = batches;
  int b_shift = (sign == 1) ? 1 : 2;
  // KN_PRINTD(batch);
  // KN_PRINTD(op_params.input_offset);
  // KN_PRINTX(data.input_offset_int8);
  int status = 0;
  while (batch) {
    if (data.opt_constraint == 2) {
      status = FullyConnectedKernel(
          (int32_t *)inputLocal, (int32_t *)p_fc_mapped_filter,
          (AScalar *)baisMVM, (int8_t *)outputLocal, output_depth, accum_depth,
          // data.outputOffset,
          data.input_offset_int8, sign, b_shift, op_params.output_offset,
          op_params.output_multiplier, op_params.output_shift);
    } else {
      // KN_PRINTF("ERROR!");
      status = FullyConnectedKernelInputOffset(
          (int32_t *)inputLocal, (int32_t *)p_fc_mapped_filter,
          // (AScalar *)baisMVM,
          (int8_t *)outputLocal, output_depth, accum_depth,
          // data.outputOffset,
          data.inputOffsetWithW,
          // data.outputMultipler,
          sign, b_shift, op_params.output_offset, op_params.output_multiplier,
          op_params.output_shift);
    }
    if (status != 0) {
      TFLITE_DCHECK(status == 0);
      break;
    }
    // KN_PRINT_Q7_SIZE(outputLocal, output_depth);
    inputLocal += accum_depth;
    outputLocal += output_depth;
    batch--;
  }
}

TfLiteStatus CalculateOpData(TfLiteContext *context,
                             TfLiteFusedActivation activation,
                             TfLiteType data_type, const TfLiteTensor *input,
                             const TfLiteTensor *filter,
                             const TfLiteTensor *bias, TfLiteTensor *output,
                             OpDataFullyConnectedEx *data_ex) {
  TfLiteStatus status = kTfLiteOk;
  OpDataFullyConnected *data = &data_ex->FcOp;
  // Set buffer index to a reset value
  data_ex->buffer_idx = -1;
  if (data_type != kTfLiteFloat32) {
    double real_multiplier = 0.0;
    TF_LITE_ENSURE_STATUS(GetQuantizedConvolutionMultipler(
        context, input, filter, bias, output, &real_multiplier));
    int exponent;
    data_ex->outputMultipler = AScalar(real_multiplier);  // convert to afloat
    QuantizeMultiplier(real_multiplier, &data->output_multiplier, &exponent);

    // Work around for Int16 use reference ops
    data->output_shift = exponent;  //-exponent;
    TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
        context, activation, output, &data->output_activation_min,
        &data->output_activation_max));

    data->input_zero_point = input->params.zero_point;
    data->filter_zero_point = filter->params.zero_point;
    data->output_zero_point = output->params.zero_point;

    return CalculateActivationRangeQuantized(context, activation, output,
                                             &data->output_activation_min,
                                             &data->output_activation_max);
  }
  return status;
}

TfLiteStatus HmdPrepareFullyConnectedInt8(TfLiteContext *context,
                                          TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);
  bool use_internal_persist_weight = false;
  OpDataFullyConnectedEx *data_ex =
      static_cast<OpDataFullyConnectedEx *>(node->user_data);

  OpDataFullyConnected *data =
      static_cast<OpDataFullyConnected *>(&data_ex->FcOp);
  const auto params =
      static_cast<const TfLiteFullyConnectedParams *>(node->builtin_data);
  // new memory allocation
  MicroContext *micro_context = GetMicroContext(context);

  TfLiteTensor *input = micro_context->AllocateTempInputTensor(
      node,
      kFullyConnectedInputTensor);  // GetInput(context, node, kInputTensor);
  TfLiteTensor *filter = micro_context->AllocateTempInputTensor(
      node, kFullyConnectedWeightsTensor);  // GetInput(context, node,
                                            // kWeightsTensor);
  TfLiteTensor *bias = micro_context->AllocateTempInputTensor(
      node, kFullyConnectedBiasTensor);  // GetOptionalInputTensor(context,
                                         // node, kBiasTensor);
  TfLiteTensor *output = micro_context->AllocateTempOutputTensor(
      node,
      kFullyConnectedOutputTensor);  // GetOutput(context, node, kOutputTensor);
  TF_LITE_ENSURE_TYPES_EQ(context, input->type, output->type);
  // TF_LITE_ENSURE_MSG(context,  input->type == filter->type,
  //                   "kernel Int8 Hybrid models are not supported on TFLite
  //                   Micro.");
  TF_LITE_ENSURE_STATUS(CalculateOpData(context, params->activation,
                                        input->type, input, filter, bias,
                                        output, data_ex));
  RuntimeShape filter_shape = GetTensorShape(filter);
  RuntimeShape output_shape = GetTensorShape(output);

  TFLITE_DCHECK_GE(output_shape.DimensionsCount(), 1);

  data_ex->opt_constraint = 0;
  // data_ex->opt_constraint_float = false;

  const int filter_dim_count = filter_shape.DimensionsCount();
  const int output_dim_count = output_shape.DimensionsCount();
  const int output_depth = output_shape.Dims(output_dim_count - 1);
  const int accum_depth = filter_shape.Dims(filter_dim_count - 1);
  // KN_PRINTD( data->filter_zero_point);
  data_ex->opt_constraint =
      //(output_dim_count == 2) &&
      input->type ==
          kTfLiteInt8 &&  // nullptr != GetTensorData<int32_t>(bias) &&
      (data->filter_zero_point == 0 && data->output_activation_min == -128 &&
       data->output_activation_max == 127);

#ifdef UNALIGNED_OPERATOR
  if ((output_depth & ((1 << LOG2_ROWS_PER_GROUP) - 1)) != 0 ||
      (accum_depth & ((1 << LOG2_COLS_PER_BLOCK) - 1)) != 0) {
    KN_PRINTD(output_depth);
    KN_PRINTD(accum_depth);
    use_internal_persist_weight = true;
  }
#else

#endif
#if 0
  data_ex->opt_constraint_float =  //(output_dim_count == 2) &&
      (filter->type == kTfLiteFloat32 || filter->type == kTfLiteFloat16 || filter->type == kTfLiteInt8) 
      && (input->type == kTfLiteFloat32) && (output->type == kTfLiteFloat32);
  // disable for testing kernel script
#endif

  KN_PRINTD(filter->type);
  KN_PRINTD(input->type);
  // KN_PRINTX(GetTensorData<float>(bias));
  KN_PRINTD(data_ex->opt_constraint);
  KN_PRINTD(data->filter_zero_point);
  KN_PRINTD(data->output_activation_min);
  KN_PRINTD(data->output_activation_max);
  KN_PRINTD(use_internal_persist_weight);
  if (data_ex->opt_constraint) {
    // remove scratch
    data_ex->buffer_idx = -1;

    int32_t *p_fc_mapped_filter = nullptr;

    const TfLiteEvalTensor *filterEval = tflite::micro::GetEvalInput(
        context, node, kFullyConnectedWeightsTensor);
    const int8_t *filter_input =
        tflite::micro::GetTensorData<int8_t>(filterEval);
    const int32_t map_coeff_size = tflite::FullyConnectedMap8bitCoeffs(
        NULL, NULL, output_depth, accum_depth);

    // if(params->weights_format == kTfLiteFullyConnectedWeightsFormatDefault)
    KN_PRINTD(output_depth);
    KN_PRINTD(accum_depth);
    // KN_PRINT_Q7_SIZE(filter_input, output_depth * accum_depth);
#ifdef KERNEL_COEFF_MAP_ENABLE
    if (true)
#else
    if (use_internal_persist_weight)  // intergrate Google Hotword lib to
                                      // default remap weight
#endif
    {
      KN_PRINTD(map_coeff_size);
      KN_PRINT_Q7_SIZE(filter_input, (output_depth * accum_depth));

      p_fc_mapped_filter =
          (int32_t *)context->AllocatePersistentBuffer(context, map_coeff_size);
      if (p_fc_mapped_filter) {
        tflite::FullyConnectedMap8bitCoeffs((int8_t *)p_fc_mapped_filter,
                                            (int8_t *)filter_input,
                                            output_depth, accum_depth);
      }
      KN_PRINT_Q7_SIZE(p_fc_mapped_filter, map_coeff_size);
    } else {
      p_fc_mapped_filter = (int32_t *)filter_input;  // remapping
    }
    // KN_PRINT_Q7_SIZE(p_dmx1a_fc_mapped_filter, map_coeff_size);
    uint8_t offsetInput = (-data->input_zero_point) & 0xff;
    // uint32_t offsetVR=offsetInput;
    data_ex->input_offset_int8 = (offsetInput << 24) | (offsetInput << 16) |
                                 (offsetInput << 8) | offsetInput;

    data_ex->mapped_filter = (int32_t *)p_fc_mapped_filter;
    if (data_ex->input_offset_int8 == 0x80808080 ||
        data_ex->input_offset_int8 == 0x0) {
      data_ex->opt_constraint = 2;  // faster without input offset
      data_ex->inputOffsetWithW = nullptr;
    } else {
      int inFCMA8 = (((output_depth + 7) >> 3) << 3);
      int32_t *inputOffsetWithW = (int32_t *)context->AllocatePersistentBuffer(
          context, inFCMA8 * sizeof(int32_t));
      data_ex->inputOffsetWithW = inputOffsetWithW;
      if (!bias) {
        MVMInputOffsetPrepare(data_ex->mapped_filter, inputOffsetWithW,
                              output_depth, accum_depth,
                              data_ex->input_offset_int8);
      } else {
        const TfLiteEvalTensor *biasEval = tflite::micro::GetEvalInput(
            context, node, kFullyConnectedBiasTensor);
        const int32_t *bias_input =
            tflite::micro::GetTensorData<int32_t>(biasEval);
        MVMInputOffsetPrepareWithBias(
            data_ex->mapped_filter, inputOffsetWithW, output_depth, accum_depth,
            data_ex->input_offset_int8, bias_input, 2);  // sign=3, left 2
      }
      KN_PRINT_Q31_SIZE(data_ex->inputOffsetWithW, inFCMA8);
    }
#ifndef REMOVE_INPLACE_BIAS
    if (bias) {
      const TfLiteEvalTensor *biasEval =
          tflite::micro::GetEvalInput(context, node, kFullyConnectedBiasTensor);
      const int32_t *bias_input =
          tflite::micro::GetTensorData<int32_t>(biasEval);
      KN_PRINT_Q31_SIZE(bias_input, output_depth);

      tflite::ConvertQ31ToAfloat(bias_input, (AScalar *)bias_input,
                                 output_depth, 17);
      KN_PRINT_AFLOAT(bias_input, output_depth);
    }
#endif
    tflite::ConvertQ31ToAfloat(data->output_zero_point, data_ex->outputOffset,
                               17);
    KN_PRINTAFLT(data_ex->outputOffset);
  }

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(filter);
  if (bias) micro_context->DeallocateTempTfLiteTensor(bias);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus HmdEvalFullyConnectedQuantizedInt8(
    TfLiteContext *context, TfLiteNode *node,
    const OpDataFullyConnectedEx &data_ex, const TfLiteEvalTensor *input,
    const TfLiteEvalTensor *filter, const TfLiteEvalTensor *bias,
    TfLiteEvalTensor *output) {
  // The 'if' condition can be removed when null handling of bias is added to

  const OpDataFullyConnected &data =
      static_cast<OpDataFullyConnected>(data_ex.FcOp);
  tflite::FullyConnectedParams op_params;
  op_params.input_offset = -data.input_zero_point;
  op_params.weights_offset = -data.filter_zero_point;
  op_params.output_offset = data.output_zero_point;
  op_params.output_multiplier = data.output_multiplier;
  // TODO(b/138810107): Figure out whether output shift should be inverted
  op_params.output_shift = data.output_shift;
  op_params.quantized_activation_min = data.output_activation_min;
  op_params.quantized_activation_max = data.output_activation_max;

  const RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
  // TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 2);

  const RuntimeShape input_shape = tflite::micro::GetTensorShape(input);
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input),
                   ElementCount(*input->dims));

  if (data_ex.opt_constraint) {
    const int8_t *inputLocal = tflite::micro::GetTensorData<int8_t>(input);
    const int8_t *outputLocal = tflite::micro::GetTensorData<int8_t>(output);
    const int8_t *filterMVM = tflite::micro::GetTensorData<int8_t>(filter);
    const int32_t *baisMVM =
        (bias) ? tflite::micro::GetTensorData<int32_t>(bias) : nullptr;
    const int output_dim_count = output_shape.DimensionsCount();
    const int output_depth = output_shape.Dims(output_dim_count - 1);
    const RuntimeShape filter_shape = tflite::micro::GetTensorShape(filter);
    const int filter_dim_count = filter_shape.DimensionsCount();
    int accum_depth = filter_shape.Dims(filter_dim_count - 1);
    int32_t inputCount = ElementCount(*input->dims);

    accum_depth =
        XT_MIN(accum_depth,
               inputCount);  // real input dim  and aligned input filter shape
    const int batches = FlatSizeSkipDim(output_shape, output_dim_count - 1);

    FullyConnectedQuantizedInt8(context, op_params, data_ex, inputLocal,
                                filterMVM, baisMVM, outputLocal, batches,
                                accum_depth, output_depth, kTfLiteInt8);

  } else {
    return kTfLiteError;

    //   KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
    //   ElementCount(*output->dims));
  }
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                   ElementCount(*output->dims));
  return kTfLiteOk;
}

//#endif

#ifndef USE_HMD_MVM_OPT
TFLMRegistration Register_FULLY_CONNECTED_INT8() {
  return tflite::micro::RegisterOp(XtensaInitFullyConnected,
                                   XtensaPrepareFullyConnected, EvalInt8);
}
#else
TFLMRegistration Register_FULLY_CONNECTED_INT8() {
  return tflite::micro::RegisterOp(HmdInitFullyConnected,
                                   HmdPrepareFullyConnectedInt8, EvalInt8);
}
#endif
}  // namespace tflite
