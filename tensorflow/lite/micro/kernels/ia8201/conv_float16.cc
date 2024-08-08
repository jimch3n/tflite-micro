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

#define ENABLE_DILATION_OPT  // enable dialtion optimization
#include "tensorflow/lite/micro/ia8201/config.h"
//#include "AVL.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/conv.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/integer_ops/conv.h"
#endif
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/padding.h"
#include "tensorflow/lite/micro/kernels/conv.h"
#include "tensorflow/lite/micro/kernels/ia8201/conv.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
namespace tflite {
namespace {

// Conv is quantized along dimension 0:
// https://www.tensorflow.org/lite/performance/quantization_spec

#if defined(DMX1A_CONV_OPT)
int ConvFloatKernel16(float *y, const float *x, const TfLiteFloat16 *A,
                      const float *bias, int m, int n, const AScalar &act_min,
                      const AScalar &act_max) {
  int loopGroupLim = (m >> 2);
  int loopBlockLim2 = (n >> 2);
  //  int jammingBit = RUR_JammingBit();
  const TfLiteFloat16 *pW = A;
  //  int maxExp;
  int ii, jj;

  float *pActOut;
  const float *pBiasLocal;
  //   WUR_JammingBit(1);
  TfLiteFloat16 *pWa0;
  TfLiteFloat16 *pWa1;
  TfLiteFloat16 *pWa2;
  TfLiteFloat16 *pWa3;

  vr128 VR_w0;
  vr128 VR_act_max, VR_act_min;

  // vr128 VR_maxExp = vseta_vr(0, 0, 0);
  // mir30 mirIdx;
  // vr128 VR_exp;
  ulsr128 UR_w0, UR_w1, UR_w2, UR_w3;
  ulsr128 UR_blk;
  ulsr128 UR_actOut, UR_bias;
  // unsigned Maxidx;

  replicate_ar(VR_act_max, 0xf, act_max.fr);
  replicate_ar(VR_act_min, 0xf, act_min.fr);
  pActOut = y;

  pBiasLocal = bias;
  UR_actOut = align_32x4_store(pActOut);
  // if (pBiasLocal) {
  UR_bias = align_32x4_load(pBiasLocal);
  //}
  if (loopGroupLim > 0) {
    for (jj = 0; jj < loopGroupLim; jj++)  // group
    {
      vr128 VR_blk = vseta_vr(0, 0, 0);
      vr128 VR_out0 = VR_blk;
      vr128 VR_out1 = VR_blk;
      // vr128 VR_out2 = VR_blk;
      // vr128 VR_out3 = VR_blk;
      vr128 VR_bias;
      vr128 VR_actOut = VR_blk;

      pWa3 = pWa2 = pWa1 = pWa0 = (TfLiteFloat16 *)pW;
      load16x1_vr_postR(VR_out0, pWa1, n, VRQ0);
      load16x1_vr_postR(VR_out0, pWa2, n * 2, VRQ0);
      load16x1_vr_postR(VR_out1, pWa3, n * 3, VRQ0);  // dummy load

      VR_out0 = vadds(VR_out0, VR_out0, 0xf0);
      VR_out1 = vadds(VR_out1, VR_out1, 0xf0);
      // VR_out2 = vadds(VR_out2, VR_out2, 0xf0);
      // VR_out3 = vexp_adji(VR_out1, 0);
      float *pIn0 = (float *)x;
      if (loopBlockLim2 > 0) {
        // register vr128 VR_act;
        UR_w0 = align_16x4_load(pWa0);
        UR_w1 = align_16x4_load(pWa1);
        UR_w2 = align_16x4_load(pWa2);
        UR_w3 = align_16x4_load(pWa3);
        UR_blk = align_32x4_load(pIn0);
        load_32x4_vr_a(VR_blk, UR_blk, pIn0);
        convert_IEEE_float_to_32F_x4(VR_blk);
        load_16x4_vr_a(VR_w0, UR_w0, pWa0);
        // convert IEEE to afloat
        convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                              TF_FLT16_BIAS);
        // convert_IEEE_float_to_32F_x4(VR_w0);
        for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
        {
          // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
          affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
          //    KN_PRINT_VR128(VR_out0);
          load_16x4_vr_a(VR_w0, UR_w1, pWa1);
          convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS);
          // convert_IEEE_float_to_32F_x4(VR_w0);
          affine_adj_H(VR_out0, VR_w0, VR_blk, 0, 0);
          load_16x4_vr_a(VR_w0, UR_w2, pWa2);
          convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS);

          affine_adj_L(VR_out1, VR_w0, VR_blk, 0, 0);
          load_16x4_vr_a(VR_w0, UR_w3, pWa3);
          convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS);
          affine_adj_H(VR_out1, VR_w0, VR_blk, 0, 0);

          load_32x4_vr_a(VR_blk, UR_blk, pIn0);  // next for block
          // convert_IEEE_float_to_32F_x4(VR_w0);
          convert_IEEE_float_to_32F_x4(VR_blk);
          load_16x4_vr_a(VR_w0, UR_w0, pWa0);
          convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS);
        }
        // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
        affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
        //   KN_PRINT_VR128(VR_out0);
        load_16x4_vr_a(VR_w0, UR_w1, pWa1);
        convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                              TF_FLT16_BIAS);
        // convert_IEEE_float_to_32F_x4(VR_w0);
        affine_adj_H(VR_out0, VR_w0, VR_blk, 0, 0);
        load_16x4_vr_a(VR_w0, UR_w2, pWa2);
        convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                              TF_FLT16_BIAS);
        // convert_IEEE_float_to_32F_x4(VR_w0);
        affine_adj_L(VR_out1, VR_w0, VR_blk, 0, 0);
        load_16x4_vr_a(VR_w0, UR_w3, pWa3);
        convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                              TF_FLT16_BIAS);
        // convert_IEEE_float_to_32F_x4(VR_w0);
        affine_adj_H(VR_out1, VR_w0, VR_blk, 0, 0);
      }

      if (n & 3) {
        load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
        convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS,
                              VRQ0);
        load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
        // convert_IEEE_float_to_32F_x4(VR_w0);
        convert_IEEE_float_to_32F_x4(VR_blk);
        for (ii = loopBlockLim2 << 2; ii < n; ii++) {
          fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
          load16x1_vr_postI(VR_w0, pWa1, INC1, VRQ0);
          convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS, VRQ0);
          // convert_IEEE_float_to_32F_x4(VR_w0);
          fmacs(VR_out0, VRQ2, VR_w0, VRQ0, VR_blk, VRQ0, 0);

          load16x1_vr_postI(VR_w0, pWa2, INC1, VRQ0);
          convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS, VRQ0);
          // convert_IEEE_float_to_32F_x4(VR_w0);
          fmacs(VR_out1, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);

          load16x1_vr_postI(VR_w0, pWa3, INC1, VRQ0);
          convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS, VRQ0);
          // convert_IEEE_float_to_32F_x4(VR_w0);
          fmacs(VR_out1, VRQ2, VR_w0, VRQ0, VR_blk, VRQ0, 0);

          load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
          load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
          convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                                TF_FLT16_BIAS, VRQ0);
          convert_IEEE_float_to_32F_x4(VR_blk);
          // convert_IEEE_float_to_32F_x4(VR_w0);
        }
      }
      // KN_PRINT_VR128(VR_out0);
      dsums_L(VR_actOut, VR_out0, 0, 0);
      dsums_H(VR_actOut, VR_out1, 0, 0);

      //   KN_PRINT_VR128(VR_actOut);
      //  if (pBiasLocal) {
      load_32x4_vr_a(VR_bias, UR_bias, pBiasLocal);
      //  } else {
      //    VR_bias = vseta_vr(kConstTable_Zero, 0, 0);
      //  }
      // convert_IEEE_float_to_32F_x4(VR_bias);
      //      KN_PRINT_VR128(VR_bias);
      VR_actOut = vadds(VR_actOut, VR_bias, 0);

      //         KN_PRINT_VR128(VR_actOut);

      VR_actOut = vmax(VR_actOut, VR_act_min);
      VR_actOut = vmin(VR_actOut, VR_act_max);
      //    KN_PRINT_VR128(VR_actOut);
      convert_32F_to_IEEE_float_x4(VR_actOut);

      //                      KN_PRINT_VR128(VR_actOut);
      store_32x4_vr_a(VR_actOut, UR_actOut, pActOut);
      pW += 4 * n;  // add to next block
    }
    flush_32x4(UR_actOut, pActOut);
  }

  for (jj = loopGroupLim << 2; jj < m; jj++)  // group
  {
    vr128 VR_actOut = vseta_vr(0, 0, 0);
    vr128 VR_blk;
    vr128 VR_out0, VR_bias;

    pWa0 = (TfLiteFloat16 *)pW;  // 1st group

    VR_out0 = vexp_adji(VR_actOut, 0x0);

    float *pIn0 = (float *)x;
    if (loopBlockLim2 > 0) {
      UR_w0 = align_16x4_load(pWa0);

      UR_blk = align_32x4_load(pIn0);
      load_32x4_vr_a(VR_blk, UR_blk, pIn0);
      load_16x4_vr_a(VR_w0, UR_w0, pWa0);
      convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS);
      convert_IEEE_float_to_32F_x4(VR_blk);
      // convert_IEEE_float_to_32F_x4(VR_w0);

      for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
      {
        affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
        load_16x4_vr_a(VR_w0, UR_w0, pWa0);
        convert_16F_to_32F_x4(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP,
                              TF_FLT16_BIAS);
        load_32x4_vr_a(VR_blk, UR_blk, pIn0);  // next for block
        convert_IEEE_float_to_32F_x4(VR_blk);
        // convert_IEEE_float_to_32F_x4(VR_w0);
      }

      affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
    }

    if (n & 3) {
      load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
      convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS,
                            VRQ0);
      //  VR_blk = vpermsi(VR_blk, VR_blk, 0, SHR_BY_1_ELEM);
      load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

      convert_IEEE_float_to_32F_x4(VR_blk);
      // convert_IEEE_float_to_32F_x4(VR_w0);

      for (ii = loopBlockLim2 << 2; ii < n; ii++) {
        fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);

        load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
        load16x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
        convert_16F_to_32F_x1(VR_w0, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS,
                              VRQ0);
        convert_IEEE_float_to_32F_x4(VR_blk);
        // convert_IEEE_float_to_32F_x4(VR_w0);
      }
    }
    dsums_L(VR_actOut, VR_out0, 0, 0);
    // fadds(VR_actOut, VRQ0, VR_out0, VRQ1, VR_out0, VRQ0, 0);
    // VR_exp = afloat_exp_extract(VR_actOut);
    // fmax(VR_maxExp, VRQ0, VR_maxExp, VRQ0, VR_exp, VRQ0);
    // if (pBiasLocal) {
    load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);
    //  } else {
    //   VR_bias = vseta_vr(kConstTable_Zero, 0, 0);
    //  }
    // convert_IEEE_float_to_32F_x4(VR_bias);
    VR_actOut = vadds(VR_actOut, VR_bias, 0);
    VR_actOut = vmax(VR_actOut, VR_act_min);
    VR_actOut = vmin(VR_actOut, VR_act_max);

    convert_32F_to_IEEE_float_x4(VR_actOut);
    store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

    pW += n;  // add to next group
  }
  return 0;  //(maxExp-31);
}

// input offset is carried, and sign, split two mac
// (input+input_offset)*filter
// = input*filter+ input_offset*filter
//

#endif

}  // namespace

}  // namespace tflite
