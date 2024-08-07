/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

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
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/softmax.h"
#endif
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/common.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/op_macros.h"

#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/softmax.h"  //prepare init
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/micro_utils.h"
namespace tflite {
namespace {


#ifdef DMX1A_SOFTMAX_OPT

_AI fr32 SoftMax1(fr32 x, fr32 sum) {
  fr32 y;
  x = fpadd(x, sum, 0);  // x + sum
  y = fpmul(x, seta_fr(kConstTable_Log2_Of_e, 0, 0), 0);
  y = pow2_fr(y);
  return y;
}
void SoftMaxV(float* y, const float* x, int n) {
  int jammingBit = RUR_JammingBit();
  WUR_JammingBit(1);
  int loopLim = n >> 3;  // Includes loop unrolling count of 2
  int remain = n & 3;
  int jj;
  unsigned tmpAR;
  mir30 tmpMir30;
  ulsr128 UR_x;
  ulsr128 UR_y;

  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0, 0);

  vr128 VR_x0;
  vr128 VR_x1;
  vr128 VR_y0;
  vr128 VR_y1;
  vr128 VR_z0;
  vr128 VR_z1;

  vr128 VR_max = vseta_vr(0, 0, 0);
  vr128 VR_sum;

  const float* xLocal;
  float* yLocal;
  // find Maximum in X and normalize
  loopLim = n >> 2;

  // 1. Subtract max value from each unit to avoid overflow of exponential
  // function
  load32x1_vr_idxR(VR_max, x, 0, VRQ0);
  convert_IEEE_float_to_32F_x4(VR_max);
  replicate(VR_max, 0xE, VR_max, VRQ0);
  xLocal = x;
  if (loopLim > 0) {
    UR_x = align_32x4_load(xLocal);
    load_32x4_vr_a(VR_x0, UR_x, xLocal);
    for (jj = 0; jj < loopLim - 1; jj++) {
      convert_IEEE_float_to_32F_x4(VR_x0);
      VR_max = vmax(VR_x0, VR_max);
      load_32x4_vr_a(VR_x0, UR_x, xLocal);
    }
    VR_max = vmax(VR_x0, VR_max);
  }
  for (jj = loopLim << 2; jj < n; jj++) {
    load32x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
    convert_IEEE_float_to_32F_x4(VR_x0);
    fmax(VR_max, VRQ0, VR_x0, VRQ0, VR_max, VRQ0);
  }

  vmaxmin_init(VR_max, VR_max, tmpMir30);
  rmax_idx(tmpAR, VR_max, VRQ0, VR_max, tmpMir30);
  replicate(VR_max, 0xE, VR_max, VRQ0);

  xLocal = (float*)tmpAR;  // This line is not required, just a temporary fix
                           // for linux build error

  xLocal = x;
  UR_x = align_32x4_load(xLocal);

  load_32x4_vr_a(VR_x0, UR_x, xLocal);
  convert_IEEE_float_to_32F_x4(VR_x0);
  load_32x4_vr_a(VR_x1, UR_x, xLocal);
  convert_IEEE_float_to_32F_x4(VR_x1);
  // 2. for(i = 0; i < n; i++)
  //   sum += exp(x[i]-max)
  // Groups of 8
  loopLim = n >> 3;
  VR_sum = vseta_vr(kConstTable_Zero, 0, 0);
  for (int i = 0; i < loopLim; i++) {
    VR_y0 = vadds(VR_x0, VR_max, 0xf0);
    VR_z0 = vmuls(VR_y0, VR_fac, 0);

    VR_y1 = vadds(VR_x1, VR_max, 0xf0);
    VR_z1 = vmuls(VR_y1, VR_fac, 0);

    pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    pow2(VR_y1, VRQ0, VR_z1, VRQ0);

    pow2(VR_y0, VRQ1, VR_z0, VRQ1);
    pow2(VR_y1, VRQ1, VR_z1, VRQ1);
    pow2(VR_y0, VRQ2, VR_z0, VRQ2);
    pow2(VR_y1, VRQ2, VR_z1, VRQ2);
    pow2(VR_y0, VRQ3, VR_z0, VRQ3);
    pow2(VR_y1, VRQ3, VR_z1, VRQ3);

    load_32x4_vr_a(VR_x0, UR_x, xLocal);
    load_32x4_vr_a(VR_x1, UR_x, xLocal);
    convert_IEEE_float_to_32F_x4(VR_x0);
    convert_IEEE_float_to_32F_x4(VR_x1);
    VR_sum = vadds(VR_sum, VR_y0, 0);
    VR_sum = vadds(VR_sum, VR_y1, 0);
  }
  xLocal -= 8;  // Compensate for loop priming
  if (n & 4) {
    // Group of 4
    VR_y0 = vadds(VR_x0, VR_max, 0xf0);
    VR_z0 = vmuls(VR_y0, VR_fac, 0);
    xLocal += 4;

    pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    pow2(VR_y0, VRQ1, VR_z0, VRQ1);
    pow2(VR_y0, VRQ2, VR_z0, VRQ2);
    pow2(VR_y0, VRQ3, VR_z0, VRQ3);

    VR_sum = vadds(VR_sum, VR_y0, 0);
  }

  // Remaining
  for (int i = 0; i < remain; i++) {
    fr32 frx, fry;
    fr32 frmax = get_VRQ0(VR_max);
    fr32 fr_sum = get_VRQ0(VR_sum);
    fr32 fr_log2e = seta_fr(kConstTable_Log2_Of_e, 0, 0);
    load32x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);

    convert_IEEE_float_to_32F_x4(VR_x0);
	frx = get_VRQ0(VR_x0);
    frx = fpadd(frx, frmax, 2);  // exp(x - max)
    fry = fpmul(frx, fr_log2e, 0);

    fry = pow2_fr(fry);

    fr_sum = fpadd(fry, fr_sum, 0);
    set_VRQ0(VR_sum, fr_sum);
  }
  dsums_L(VR_sum, VR_sum, 0, 0);
  dsums_L(VR_sum, VR_sum, 0, 0);

  fr32 fr_ln2 = seta_fr(kConstTable_Loge_Of_2, 0, 0);
  fr32 fr_max = get_VRQ0(VR_max);
  fr32 fr_sum;

  fr_sum = fpadd(fr_max, fpmul(log2_fr(get_VRQ0(VR_sum)), fr_ln2, 0),
                 0x3);  // -max-ln(sum)
                        // 3. sum= -(max + ksp_ln(sum))
                        // access internal unsigned int

  replicate_ar(VR_sum, 0xf, fr_sum);

  //  for( i = 0; i < n; i++)
  //        y[i] = ksp_exp(x[i]+sum)
  loopLim = n >> 3;
  xLocal = x;
  yLocal = y;
  UR_x = align_32x4_load(xLocal);
  UR_y = align_32x4_store(yLocal);
  load_32x4_vr_a(VR_x0, UR_x, xLocal);
  convert_IEEE_float_to_32F_x4(VR_x0);
  load_32x4_vr_a(VR_x1, UR_x, xLocal);
  convert_IEEE_float_to_32F_x4(VR_x1);
  for (int i = 0; i < loopLim; i++) {
    VR_y0 = vadds(VR_x0, VR_sum, 0);
    VR_z0 = vmuls(VR_y0, VR_fac, 0);

    VR_y1 = vadds(VR_x1, VR_sum, 0);
    VR_z1 = vmuls(VR_y1, VR_fac, 0);

    pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    pow2(VR_y1, VRQ0, VR_z1, VRQ0);

    pow2(VR_y0, VRQ1, VR_z0, VRQ1);
    pow2(VR_y1, VRQ1, VR_z1, VRQ1);
    pow2(VR_y0, VRQ2, VR_z0, VRQ2);
    pow2(VR_y1, VRQ2, VR_z1, VRQ2);
    pow2(VR_y0, VRQ3, VR_z0, VRQ3);
    pow2(VR_y1, VRQ3, VR_z1, VRQ3);

    load_32x4_vr_a(VR_x0, UR_x, xLocal);
    load_32x4_vr_a(VR_x1, UR_x, xLocal);
    convert_IEEE_float_to_32F_x4(VR_x0);
    convert_IEEE_float_to_32F_x4(VR_x1);
    convert_32F_to_IEEE_float_x4(VR_y0);
    convert_32F_to_IEEE_float_x4(VR_y1);
    store_32x4_vr_a(VR_y0, UR_y, yLocal);
    store_32x4_vr_a(VR_y1, UR_y, yLocal);
  }

  xLocal -= 8;  // Compensate for loop priming
  if (n & 4) {
    // Group of 4
    VR_y0 = vadds(VR_x0, VR_sum, 0);
    VR_z0 = vmuls(VR_y0, VR_fac, 0);
    xLocal += 4;

    pow2(VR_y0, VRQ0, VR_z0, VRQ0);
    pow2(VR_y0, VRQ1, VR_z0, VRQ1);
    pow2(VR_y0, VRQ2, VR_z0, VRQ2);
    pow2(VR_y0, VRQ3, VR_z0, VRQ3);
    convert_32F_to_IEEE_float_x4(VR_y0);
    store_32x4_vr_a(VR_y0, UR_y, yLocal);
  }
  flush_32x4(UR_y, yLocal);
  // Remaining
  for (int i = 0; i < remain; i++) {
    fr32 frx, fry, sum;
    sum = get_VRQ0(VR_sum);

    load32x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
    convert_IEEE_float_to_32F_x4(VR_x0);
	frx = get_VRQ0(VR_x0);
    fry = SoftMax1(frx, sum);  // scalar input with sum
	set_VRQ0(VR_y0, fry);
	convert_32F_to_IEEE_float_x4(VR_y0);
    store32x1_vr_postI(VR_y0, yLocal, INC1, VRQ0);
  }

  WUR_JammingBit(jammingBit);
}

void SoftMaxQuantizedInt8(const AScalar& diffMin, const AScalar& inputMultipler,
                          int8_t* y, const int8_t* x, int depth) {
  int loopLim = depth >> 2;  // Includes loop unrolling count of 2
  int remain = depth & 3;
  int jj;
  unsigned tmpAR;
  mir30 tmpMir30;
  ulsr128 UR_x, UR_y;

  vr128 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0, 0);
  vr128 VR_x0;
  vr128 VR_y0;
  vr128 VR_z0;
  vr128 VR_NegSat;
  //
  vr128 VR_max;
  vr128 VR_sum;
  vr128 VR_diffMin;
  vr128 VR_inputMulti;
  vr128 VR_q7_out;
  vr128 VR_minMax;
  vr128 VR_zero = vseta_vr(0, 0, 0);
  int8_t* xLocal;
  int8_t* yLocal;

  replicate_ar(VR_diffMin, 0xf, diffMin.fr);
  replicate_ar(VR_inputMulti, 0xf, inputMultipler.fr);
  replicate_ar(VR_NegSat, 0xf, 0x80000000);  // negative fixpoint saturate -128
  replicate_ar(VR_minMax, 0xf, CONST_ASCALAR(128.0).fr);
  // find Maximum in X and normalize
  loopLim = depth >> 2;

  // 1. Subtract max value from each unit to avoid overflow of exponential
  // function
  replicate_ar(VR_max, 0xf, 0xffffffff);// init - max
  xLocal = (int8_t*)x;
  if (loopLim > 0)
  {
      UR_x = align_8x4_load(xLocal);
      load_8x4_vr_a(VR_x0, UR_x, xLocal);

      // conver int_8_to afloat
      convert_16I_to_32F_x4(VR_x0, 0);
      vmaxmin_init(VR_max, VR_x0, tmpMir30);

      for (jj = 0; jj < loopLim - 1; jj++) {
          VR_max = vmax(VR_x0, VR_max);
          load_8x4_vr_a(VR_x0, UR_x, xLocal);
          convert_16I_to_32F_x4(VR_x0, 0);
      }
      VR_max = vmax(VR_x0, VR_max);
  }
  for (jj = 0; jj < remain; jj++) {
    load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
    convert_16I_to_32F_x1(VR_x0, 0, VRQ0);
    fmax(VR_max, VRQ0, VR_x0, VRQ0, VR_max, VRQ0);
  }
  rmax_idx(tmpAR, VR_max, VRQ0, VR_max, tmpMir30);
  replicate(VR_max, 0xE, VR_max, VRQ0);

  xLocal = (int8_t*)tmpAR;  // This line is not required, just a temporary fix
                            // for linux build error

  xLocal = (int8_t*)x;
  VR_sum = vseta_vr(kConstTable_Zero, 0, 0);
  vr128 VR_diff;
  xtbool4 xt_inputDiff;
  if (loopLim > 0)
  {
      UR_x = align_8x4_load(xLocal);

      load_8x4_vr_a(VR_x0, UR_x, xLocal);
      convert_16I_to_32F_x4(VR_x0, 0);
      

      for (int i = 0; i < loopLim - 1; i++) {
          VR_diff = vadds(VR_x0, VR_max, 0xf0);

          xt_inputDiff = vge(VR_diff, VR_diffMin);
          // input_beta;
          VR_diff = vmuls(VR_diff, VR_inputMulti, 0);

          VR_z0 = vmuls(VR_diff, VR_fac, 0);

          pow2(VR_y0, VRQ0, VR_z0, VRQ0);
          pow2(VR_y0, VRQ1, VR_z0, VRQ1);
          pow2(VR_y0, VRQ2, VR_z0, VRQ2);
          pow2(VR_y0, VRQ3, VR_z0, VRQ3);

          VR_y0 = vsel(VR_y0, VR_zero, xt_inputDiff);

          load_8x4_vr_a(VR_x0, UR_x, xLocal);
          convert_16I_to_32F_x4(VR_x0, 0);
          VR_sum = vadds(VR_sum, VR_y0, 0);
      }
      VR_diff = vadds(VR_x0, VR_max, 0xf0);

      xt_inputDiff = vge(VR_diff, VR_diffMin);  // diff >= diffmin
      VR_diff = vmuls(VR_diff, VR_inputMulti, 0);
      VR_z0 = vmuls(VR_diff, VR_fac, 0);
      pow2(VR_y0, VRQ0, VR_z0, VRQ0);
      pow2(VR_y0, VRQ1, VR_z0, VRQ1);
      pow2(VR_y0, VRQ2, VR_z0, VRQ2);
      pow2(VR_y0, VRQ3, VR_z0, VRQ3);
      VR_y0 = vsel(VR_y0, VR_zero, xt_inputDiff);
      VR_sum = vadds(VR_sum, VR_y0, 0);
  }

  if (depth & 3) {
    VR_y0 = vexp_adji(VR_zero, 0);  // reset Y1,2,3 zero, prevent add
    // Remaining
    for (int i = 0; i < remain; i++) {
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);

      convert_16I_to_32F_x1(VR_x0, 0, VRQ0);
      VR_diff = vadds(VR_x0, VR_max, 0xf0);

      xtbool xt_inputDiff0 =
          ge(VR_diff, VRQ0, VR_diffMin, VRQ0);  // diff >= diffmin

      fmuls(VR_diff, VRQ0, VR_diff, VRQ0, VR_inputMulti, VRQ0, 0);
      fmuls(VR_z0, VRQ0, VR_diff, VRQ0, VR_fac, VRQ0, 0);
      pow2(VR_y0, VRQ0, VR_z0, VRQ0);
      sel(VR_y0, VRQ0, VR_y0, VRQ0, VR_zero, VRQ0, xt_inputDiff0);
      fadds(VR_sum, VRQ0, VR_sum, VRQ0, VR_y0, VRQ0, 0);
    }
  }
  dsums_L(VR_sum, VR_sum, 0, 0);
  dsums_L(VR_sum, VR_sum, 0, 0);

  fr32 fr_sum = get_VRQ0(VR_sum);
  // recipral;
  AScalar invSum = AScalar(fr_sum).inverse();
  replicate_ar(VR_sum, 0xf, invSum.fr);

  //  for( i = 0; i < n; i++)
  //        y[i] = ksp_exp(x[i]+sum)

  xLocal = (int8_t*)x;
  yLocal = y;
  if (loopLim > 0)
  {
      UR_x = align_8x4_load(xLocal);
      UR_y = align_8x4_store(yLocal);
      load_8x4_vr_a(VR_x0, UR_x, xLocal);
      convert_16I_to_32F_x4(VR_x0, 0);
      for (int i = 0; i < loopLim - 1; i++) {
          VR_diff = vadds(VR_x0, VR_max, 0xf0);
          xt_inputDiff = vge(VR_diff, VR_diffMin);
          VR_diff = vmuls(VR_diff, VR_inputMulti, 0);
          VR_z0 = vmuls(VR_diff, VR_fac, 0);
          pow2(VR_y0, VRQ0, VR_z0, VRQ0);
          pow2(VR_y0, VRQ1, VR_z0, VRQ1);
          pow2(VR_y0, VRQ2, VR_z0, VRQ2);
          pow2(VR_y0, VRQ3, VR_z0, VRQ3);

          VR_y0 = vmuls(VR_y0, VR_sum, 0);        // /sum - 0.1
          VR_y0 = vexp_adji(VR_y0, 8);            // shift 8 bit??
          VR_z0 = vadds(VR_y0, VR_minMax, 0xf0);  // -128
          convert_32F_to_16I_x4(VR_z0, 7, 1);
          VR_z0 = vsel(VR_z0, VR_NegSat, xt_inputDiff);
          rnd_sat_pack(VR_q7_out, VRQ0, VR_z0, 1);  // ronding
          VR_z0 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
          store_8x4_vr_a(VR_z0, UR_y, yLocal);
          load_8x4_vr_a(VR_x0, UR_x, xLocal);
          convert_16I_to_32F_x4(VR_x0, 0);
      }
      // VR_y0 = vadds(VR_x0, VR_sum, 0);

      VR_diff = vadds(VR_x0, VR_max, 0xf0);
      xt_inputDiff = vge(VR_diff, VR_diffMin);
      VR_diff = vmuls(VR_diff, VR_inputMulti, 0);
      VR_z0 = vmuls(VR_diff, VR_fac, 0);
      pow2(VR_y0, VRQ0, VR_z0, VRQ0);
      pow2(VR_y0, VRQ1, VR_z0, VRQ1);
      pow2(VR_y0, VRQ2, VR_z0, VRQ2);
      pow2(VR_y0, VRQ3, VR_z0, VRQ3);

      VR_y0 = vmuls(VR_y0, VR_sum, 0);        // /sum - 0.1
      VR_y0 = vexp_adji(VR_y0, 8);            // shift 8 bit??
      VR_z0 = vadds(VR_y0, VR_minMax, 0xf0);  // -128
      convert_32F_to_16I_x4(VR_z0, 7, 1);
      VR_z0 = vsel(VR_z0, VR_NegSat, xt_inputDiff);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_z0, 1);  // ronding
      VR_z0 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store_8x4_vr_a(VR_z0, UR_y, yLocal);
      flush_8x4(UR_y, yLocal);
  }
  if (remain) {
    for (int i = 0; i < remain; i++) {
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);

      convert_16I_to_32F_x1(VR_x0, 0, VRQ0);
      // VR_diff = vadds(VR_x0, VR_max, 0xf0);
      fadds(VR_diff, VRQ0, VR_x0, VRQ0, VR_max, VRQ0, 0x10);
      xtbool xt_inputDiff0 = ge(VR_diff, VRQ0, VR_diffMin, VRQ0);
      fmuls(VR_diff, VRQ0, VR_diff, VRQ0, VR_inputMulti, VRQ0, 0);
      fmuls(VR_z0, VRQ0, VR_diff, VRQ0, VR_fac, VRQ0, 0);
      pow2(VR_y0, VRQ0, VR_z0, VRQ0);
      fmuls(VR_y0, VRQ0, VR_y0, VRQ0, VR_sum, VRQ0, 0);  // /sum - 0.1

      VR_y0 = vexp_adji(VR_y0, 8);                             // shift 8 bit??
      fadds(VR_z0, VRQ0, VR_y0, VRQ0, VR_minMax, VRQ0, 0x10);  // -128
      convert_32F_to_16I_x1(VR_z0, 7, 1, VRQ0);
      sel(VR_z0, VRQ0, VR_z0, VRQ0, VR_NegSat, VRQ0, xt_inputDiff0);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_z0, 1);  // ronding
      VR_q7_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0);
      store8x1_vr_postI(VR_q7_out, yLocal, INC1, VRQ0);
    }
  }
//  WUR_JammingBit(jammingBit);
}
#endif

#ifdef HMD1A_SOFTMAX_OPT

_AI fr32 SoftMax1(fr32 x, fr32 sum) {
  fr32 y;
  x = fadds(x, sum, 0);  // x + sum
  y = fmuls(x, seta_fr(kConstTable_Log2_Of_e, 0), 0);
  y = pow2(y);
  return y;
}
void SoftMaxV(float* y, const float* x, int n) {
  int jammingBit = RUR_JammingBit();
  WUR_JammingBit(1);
  int loopLim = n >> 2;  // Includes loop unrolling count of 2
  int remain = n & 1;
  int jj;
  unsigned tmpAR;
  mir18 tmpMir18;
  ulsr32 UR_x;
  ulsr32 UR_y;

  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0);

  vr64 VR_x0;
  vr64 VR_x1;
  vr64 VR_y0;
  vr64 VR_y1;
  vr64 VR_z0;
  vr64 VR_z1;

  vr64 VR_max = vseta_vr(0, 0);
  vr64 VR_sum;

  const float* xLocal;
  float* yLocal;
  fr32 max;
  // find Maximum in X and normalize
  loopLim = n >> 1;

  // 1. Subtract max value from each unit to avoid overflow of exponential
  // function
  load32x1_vr_idxR(VR_max, x, 0, VRQ0);
  convert_IEEE_float_to_32F_x2(VR_max);
  replicate(VR_max, 0x3, VR_max, VRQ0);
  xLocal = x;
  if (loopLim > 0) {
    UR_x = align_32x2_load(xLocal);
    load_32x2_vr_a(VR_x0, UR_x, xLocal);

    for (jj = 0; jj < loopLim - 1; jj++) {
      convert_IEEE_float_to_32F_x2(VR_x0);
      VR_max = vmax(VR_x0, VR_max);
      load_32x2_vr_a(VR_x0, UR_x, xLocal);
    }
    VR_max = vmax(VR_x0, VR_max);
  }
  for (jj = loopLim << 1; jj < n; jj++) {
    load32x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_x0);
    fmax(VR_max, VRQ0, VR_x0, VRQ0, VR_max, VRQ0);
  }
  vmaxmin_init(VR_max, VR_max, tmpMir18);
  rmax_idx(tmpAR, max, VR_max, tmpMir18);

  xLocal = (float*)tmpAR;  // This line is not required, just a temporary fix
                           // for linux build error

  replicate_ar(VR_max, 0x3, max);

  xLocal = x;
  UR_x = align_32x2_load(xLocal);

  load_32x2_vr_a(VR_x0, UR_x, xLocal);
  convert_IEEE_float_to_32F_x2(VR_x0);
  load_32x2_vr_a(VR_x1, UR_x, xLocal);
  convert_IEEE_float_to_32F_x2(VR_x1);
  // 2. for(i = 0; i < n; i++)
  //   sum += exp(x[i]-max)
  // Groups of 4
  loopLim = n >> 2;
  VR_sum = vseta_vr(kConstTable_Zero, 0);
  for (int i = 0; i < loopLim; i++) {
    VR_y0 = vadds(VR_x0, VR_max, 0xA);

    VR_z0 = vmuls(VR_y0, VR_fac, 0);

    VR_y1 = vadds(VR_x1, VR_max, 0xA);
    VR_z1 = vmuls(VR_y1, VR_fac, 0);

    set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
    set_VRL(VR_y1, pow2(get_VRL(VR_z1)));

    set_VRH(VR_y0, pow2(get_VRH(VR_z0)));
    set_VRH(VR_y1, pow2(get_VRH(VR_z1)));

    load_32x2_vr_a(VR_x0, UR_x, xLocal);
    load_32x2_vr_a(VR_x1, UR_x, xLocal);
    convert_IEEE_float_to_32F_x2(VR_x0);
    convert_IEEE_float_to_32F_x2(VR_x1);
    VR_sum = vadds(VR_sum, VR_y0, 0);
    VR_sum = vadds(VR_sum, VR_y1, 0);
  }
  xLocal -= 4;  // Compensate for loop priming
  if (n & 2) {
    // Group of 2
    VR_y0 = vadds(VR_x0, VR_max, 0xA);

    VR_z0 = vmuls(VR_y0, VR_fac, 0);
    xLocal += 2;

    set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
    set_VRH(VR_y0, pow2(get_VRH(VR_z0)));

    VR_sum = vadds(VR_sum, VR_y0, 0);
  }

  // Remaining
  if (remain) {
    fr32 frx, fry;
    fr32 frmax = get_VRL(VR_max);
    fr32 fr_sum = get_VRL(VR_sum);
    fr32 fr_log2e = seta_fr(kConstTable_Log2_Of_e, 0);
    load32x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);

    convert_IEEE_float_to_32F_x2(VR_x0);
    frx = get_VRL(VR_x0);
    frx = fadds(frx, frmax, 2);  // exp(x - max)
    fry = fmuls(frx, fr_log2e, 0);

    fry = pow2(fry);

    fr_sum = fadds(fry, fr_sum, 0);
    set_VRL(VR_sum, fr_sum);
  }

  VR_sum = vadd_perm(VR_sum, VR_sum, VSEL_YH_XL, VSEL_YL_XH, 0, 0);
  fr32 fr_ln2 = seta_fr(kConstTable_Loge_Of_2, 0);
  fr32 fr_max = get_VRL(VR_max);
  fr32 fr_sum;

  fr_sum = fadds(fr_max, fmuls(log2(get_VRL(VR_sum)), fr_ln2, 0),
                 0x3);  // -max-ln(sum)
  // 3. sum= -(max + ksp_ln(sum))

  replicate_ar(VR_sum, 0x3, fr_sum);

  //  for( i = 0; i < n; i++)
  //        y[i] = ksp_exp(x[i]+sum)
  loopLim = n >> 2;
  xLocal = x;
  yLocal = y;
  UR_x = align_32x2_load(xLocal);
  UR_y = align_32x2_store(yLocal);
  load_32x2_vr_a(VR_x0, UR_x, xLocal);
  convert_IEEE_float_to_32F_x2(VR_x0);
  load_32x2_vr_a(VR_x1, UR_x, xLocal);
  convert_IEEE_float_to_32F_x2(VR_x1);
  for (int i = 0; i < loopLim; i++) {
    VR_y0 = vadds(VR_x0, VR_sum, 0);
    VR_z0 = vmuls(VR_y0, VR_fac, 0);

    VR_y1 = vadds(VR_x1, VR_sum, 0);
    VR_z1 = vmuls(VR_y1, VR_fac, 0);

    set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
    set_VRL(VR_y1, pow2(get_VRL(VR_z1)));

    set_VRH(VR_y0, pow2(get_VRH(VR_z0)));
    set_VRH(VR_y1, pow2(get_VRH(VR_z1)));

    load_32x2_vr_a(VR_x0, UR_x, xLocal);
    load_32x2_vr_a(VR_x1, UR_x, xLocal);
    convert_IEEE_float_to_32F_x2(VR_x0);
    convert_IEEE_float_to_32F_x2(VR_x1);
    convert_32F_to_IEEE_float_x2(VR_y0);
    convert_32F_to_IEEE_float_x2(VR_y1);
    store_32x2_vr_a(VR_y0, UR_y, yLocal);
    store_32x2_vr_a(VR_y1, UR_y, yLocal);
  }

  xLocal -= 4;  // Compensate for loop priming
  if (n & 2) {
    // Group of 4
    VR_y0 = vadds(VR_x0, VR_sum, 0);
    VR_z0 = vmuls(VR_y0, VR_fac, 0);
    xLocal += 2;

    set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
    set_VRH(VR_y0, pow2(get_VRH(VR_z0)));
    convert_32F_to_IEEE_float_x2(VR_y0);
    store_32x2_vr_a(VR_y0, UR_y, yLocal);
  }
  flush_32x2(UR_y, yLocal);
  // Remaining
  if (remain) {
    fr32 frx, fry;
    fr32 sum = get_VRL(VR_sum);

    load32x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
    convert_IEEE_float_to_32F_x2(VR_x0);
    frx = get_VRL(VR_x0);
    fry = SoftMax1(frx, sum);  // scalar input with sum
    set_VRL(VR_y0, fry);
    // store_fr_postI(fry, yLocal, INC1);
    convert_32F_to_IEEE_float_x2(VR_y0);
    store32x1_vr_postI(VR_y0, yLocal, INC1, VRQ0);
  }

  WUR_JammingBit(jammingBit);
}

void SoftMaxQuantizedInt8(const AScalar& diffMin, const AScalar& inputMultipler,
                          int8_t* y, const int8_t* x, int depth) {
  int loopLim = depth >> 1;  // Includes loop unrolling count of 2
  int remain = depth & 1;
  int jj;
  unsigned tmpAR;
  mir18 tmpMir18;
  // ulsr32 UR_x, UR_y;
#ifdef KN_DEBUG
  CHECK_ALIGN_2(x);
  CHECK_ALIGN_2(y);
#endif
  vr64 VR_fac = vseta_vr(kConstTable_Log2_Of_e, 0);
  vr64 VR_x0;
  vr64 VR_y0;
  vr64 VR_z0;
  vr64 VR_NegSat;
  //
  vr64 VR_max;
  vr64 VR_sum;
  vr64 VR_diffMin;
  vr64 VR_inputMulti;
  vr64 VR_q7_out;
  vr64 VR_minMax;
  vr64 VR_zero = vseta_vr(0, 0);
  int8_t* xLocal;
  int8_t* yLocal;

  replicate_ar(VR_diffMin, 0x3, diffMin.fr);
  replicate_ar(VR_inputMulti, 0x3, inputMultipler.fr);
  replicate_ar(VR_NegSat, 0x3, 0x80000000);  // negative fixpoint saturate -128
  replicate_ar(VR_minMax, 0x3, CONST_ASCALAR(128.0).fr);
  // find Maximum in X and normalize

  // 1. Subtract max value from each unit to avoid overflow of exponential
  // function
  //int align2_input = ((unsigned)x & 1) == 0;
  //int align2_output = ((unsigned)y & 1) == 0;

  xLocal = (int8_t*)x;
  // UR_x = align_8x2_load(xLocal);

  // conver int_8_to afloat
  replicate_ar(VR_max, 0x3, 0xffffffff);
  //tmpMir18 = 0;
  vmaxmin_init(VR_max, VR_max, tmpMir18);
  if (loopLim > 0)
  {
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRL);
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRH);

      convert_16I_to_32F_x2(VR_x0, 0);
      
      vmaxmin_init(VR_max, VR_x0, tmpMir18);
      for (jj = 0; jj < loopLim - 1; jj++) {
          vmax_idx(VR_x0, VR_max, tmpMir18);
        
        load8x1_vr_postI(VR_x0, xLocal, INC1, VRL);
        load8x1_vr_postI(VR_x0, xLocal, INC1, VRH);
          
          convert_16I_to_32F_x2(VR_x0, 0);
      }
      vmax_idx(VR_x0, VR_max, tmpMir18);
  }
  if (remain) {
    load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
    convert_16I_to_32F_x1(VR_x0, 0, VRQ0);
    fmax(VR_max, VRQ0, VR_x0, VRQ0, VR_max, VRQ0);
  }
  fr32 fr_max;
  rmax_idx(tmpAR, fr_max, VR_max, tmpMir18);
  VR_max = vreplicate_fr(fr_max);
  // KN_PRINT_VR(VR_max);
  xLocal = (int8_t*)x;
  VR_sum = vseta_vr(kConstTable_Zero, 0);
  vr64 VR_diff;
  atbool xt_inputDiff;
  if (loopLim > 0)
  {

      load8x1_vr_postI(VR_x0, xLocal, INC1, VRL);
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRH);
      convert_16I_to_32F_x2(VR_x0, 0);
      for (int i = 0; i < loopLim - 1; i++) {
          VR_diff = vadds(VR_x0, VR_max, 0xa);
          xt_inputDiff = vge(VR_diff, VR_diffMin);
          // input_beta;
          VR_diff = vmuls(VR_diff, VR_inputMulti, 0);
          VR_z0 = vmuls(VR_diff, VR_fac, 0);

          set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
          set_VRH(VR_y0, pow2(get_VRH(VR_z0)));
          VR_z0 = vsel(VR_y0, VR_zero, xt_inputDiff);

           
            load8x1_vr_postI(VR_x0, xLocal, INC1, VRL);
            load8x1_vr_postI(VR_x0, xLocal, INC1, VRH);
          
          convert_16I_to_32F_x2(VR_x0, 0);
          VR_sum = vadds(VR_sum, VR_z0, 0);
      }
      VR_diff = vadds(VR_x0, VR_max, 0xa);

      xt_inputDiff = vge(VR_diff, VR_diffMin);  // diff >= diffmin
      VR_diff = vmuls(VR_diff, VR_inputMulti, 0);
      VR_z0 = vmuls(VR_diff, VR_fac, 0);

      set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
      set_VRH(VR_y0, pow2(get_VRH(VR_z0)));

      VR_z0 = vsel(VR_y0, VR_zero, xt_inputDiff);
      VR_sum = vadds(VR_sum, VR_z0, 0);
  }
  if (remain) {
    VR_y0 = vexp_adji(VR_zero, 0);  // reset Y1,2,3 zero, prevent add
    // Remaining
    // for (int i=0; i < remain; i++)
    {
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
      convert_16I_to_32F_x1(VR_x0, 0, VRQ0);
      VR_diff = vadds(VR_x0, VR_max, 0xa);
      unsigned xt_inputDiff0 =
          ge(VR_diff, VRQ0, VR_diffMin, VRQ0);  // diff >= diffmin
      fr32 fr_diff = fmuls(get_VRL(VR_diff), get_VRL(VR_inputMulti), 0);
      fr32 fr_z0 = fmuls(fr_diff, get_VRL(VR_fac), 0);
      fr32 fr_y0 = pow2(fr_z0);
      fr_z0 = sel_ar(fr_y0, get_VRL(VR_zero), xt_inputDiff0);
      set_VRL(VR_sum, fadds(get_VRL(VR_sum), fr_z0, 0));
    }
  }
  fr32 fr_sum = fadds(get_VRL(VR_sum), get_VRH(VR_sum), 0);
  // get_VRL(VR_sum);
  // recipral;
  AScalar invSum = AScalar(fr_sum).inverse();
  replicate_ar(VR_sum, 0x3, invSum.fr);
  //  for( i = 0; i < n; i++)
  //        y[i] = ksp_exp(x[i]+sum)

  xLocal = (int8_t*)x;
  yLocal = y;
  

  if (loopLim > 0)
  {
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRL);
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRH);

      convert_16I_to_32F_x2(VR_x0, 0);
      for (int i = 0; i < loopLim - 1; i++) {
          VR_diff = vadds(VR_x0, VR_max, 0xa);

          xt_inputDiff = vge(VR_diff, VR_diffMin);
          VR_x0 = vmuls(VR_diff, VR_inputMulti, 0);
          VR_z0 = vmuls(VR_x0, VR_fac, 0);
          set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
          set_VRH(VR_y0, pow2(get_VRH(VR_z0)));
          // next load
           
              load8x1_vr_postI(VR_x0, xLocal, INC1, VRL);
              load8x1_vr_postI(VR_x0, xLocal, INC1, VRH);
          
          convert_16I_to_32F_x2(VR_x0, 0);

          VR_z0 = vmuls(VR_y0, VR_sum, 0);       // /sum - 0.1
          VR_y0 = vexp_adji(VR_z0, 8);           // shift 8 bit??
          VR_z0 = vadds(VR_y0, VR_minMax, 0xa);  // -128
          convert_32F_to_16I_x2(VR_z0, 7, 1);

          VR_y0 = vsel(VR_z0, VR_NegSat, xt_inputDiff);
          rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, VR_zero, 1);  // ronding
          VR_z0 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);

          
        store8x1_vr_postI(VR_z0, yLocal, INC1, VRL);
        store8x1_vr_postI(VR_z0, yLocal, INC1, VRH);
          
      }
      VR_diff = vadds(VR_x0, VR_max, 0xa);
      xt_inputDiff = vge(VR_diff, VR_diffMin);
      VR_x0 = vmuls(VR_diff, VR_inputMulti, 0);
      VR_z0 = vmuls(VR_x0, VR_fac, 0);

      set_VRL(VR_y0, pow2(get_VRL(VR_z0)));
      set_VRH(VR_y0, pow2(get_VRH(VR_z0)));

      VR_z0 = vmuls(VR_y0, VR_sum, 0);       // /sum - 0.1
      VR_y0 = vexp_adji(VR_z0, 8);           // shift 8 bit??
      VR_z0 = vadds(VR_y0, VR_minMax, 0xa);  // -128
      convert_32F_to_16I_x2(VR_z0, 7, 1);

      VR_y0 = vsel(VR_z0, VR_NegSat, xt_inputDiff);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_y0, VR_zero, 1);  // ronding
      VR_z0 = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);

      
    store8x1_vr_postI(VR_z0, yLocal, INC1, VRL);
    store8x1_vr_postI(VR_z0, yLocal, INC1, VRH);
      
  }
  if (remain) {
    // for (int i = 0; i < remain; i++)
    {
      load8x1_vr_postI(VR_x0, xLocal, INC1, VRQ0);
      convert_16I_to_32F_x1(VR_x0, 0, VRQ0);
      fr32 fr_diff = fadds(get_VRL(VR_x0), get_VRL(VR_max), 0x2);
      unsigned xt_inputDiff0 = ge_fr(fr_diff, get_VRL(VR_diffMin));
      fr_diff = fmuls(fr_diff, get_VRL(VR_inputMulti), 0);
      fr32 fr_z0 = fmuls(fr_diff, get_VRL(VR_fac), 0);
      fr32 fr_y0 = pow2(fr_z0);
      fr_y0 = fmuls(fr_y0, get_VRL(VR_sum), 0);
      fr_y0 = exp_adji_fr(fr_y0, 8);  // shift 8 bit??
      fr_z0 = fadds(fr_y0, get_VRL(VR_minMax), 2);
      set_VRL(VR_z0, fr_z0);
      convert_32F_to_16I_x1(VR_z0, 7, 1, VRQ0);
      fr_z0 = sel_ar(get_VRL(VR_z0), get_VRL(VR_NegSat), xt_inputDiff0);
      set_VRL(VR_z0, fr_z0);
      rnd_sat_pack(VR_q7_out, VRQ0, VR_z0, VR_z0, 1);  // ronding
      VR_q7_out = shift8_into32_arith(VR_q7_out, 24, 0, VRQ0, VRL);
      store8x1_vr_postI(VR_q7_out, yLocal, INC1, VRL);
    }
  }
}
#endif

// Takes a tensor and performs softmax along the last dimension.
static void SoftmaxFloat(const TfLiteEvalTensor* input,
                         TfLiteEvalTensor* output,
                         const SoftmaxParams& op_data) {
#if defined(DMX1A_SOFTMAX_OPT) || defined(HMD1A_SOFTMAX_OPT)
  const auto input_shape = tflite::micro::GetTensorShape(input);
  const auto output_shape = tflite::micro::GetTensorShape(output);
  const int trailing_dim = input_shape.DimensionsCount() - 1;
  const int outer_size =
      MatchingFlatSizeSkipDim(input_shape, trailing_dim, output_shape);
  const int depth =
      MatchingDim(input_shape, trailing_dim, output_shape, trailing_dim);
  KN_PRINTD(outer_size);
  KN_PRINTD(depth);
  // int flat_size = MatchingFlatSize(tflite::micro::GetTensorShape(output),
  //                                  tflite::micro::GetTensorShape(input));

  const float* pInput =
      (const float*)tflite::micro::GetTensorData<float>(input);
  float* pOutput = (float*)tflite::micro::GetTensorData<float>(output);
  for (int out = 0; out < outer_size; out++) {
    SoftMaxV(pOutput, pInput, depth);
    pOutput += depth;
    pInput += depth;
  }

#else
  tflite::reference_ops::Softmax(op_data, tflite::micro::GetTensorShape(input),
                                 tflite::micro::GetTensorData<float>(input),
                                 tflite::micro::GetTensorShape(output),
                                 tflite::micro::GetTensorData<float>(output));
#endif
  KN_PRINT_FLOAT(tflite::micro::GetTensorData<float>(output),
                 ElementCount(*output->dims));
}
#if defined(DMX1A_SOFTMAX_OPT) || defined(HMD1A_SOFTMAX_OPT)
static TfLiteStatus SoftmaxQuantizedInt8Int8(const TfLiteEvalTensor* input,
                                             TfLiteEvalTensor* output,
                                             const SoftmaxParams& op_data) {
  const auto input_shape = tflite::micro::GetTensorShape(input);
  const auto output_shape = tflite::micro::GetTensorShape(output);
  const int trailing_dim = input_shape.DimensionsCount() - 1;
  const int outer_size =
      MatchingFlatSizeSkipDim(input_shape, trailing_dim, output_shape);
  const int depth =
      MatchingDim(input_shape, trailing_dim, output_shape, trailing_dim);
  KN_PRINTD(outer_size);

  AScalar diffMin;
  AScalar inputMultipler;
  tflite::ConvertQ31ToAfloat(op_data.diff_min, diffMin, 24);  // Q7
  // scale = 5
  tflite::ConvertQ31ToAfloat(
      op_data.input_multiplier, inputMultipler,
      op_data.input_left_shift -
          19);  // Q7* Qx() >> 31-shift32- op_data.input_left_shift-5
   KN_PRINT_Q7_SIZE( tflite::micro::GetTensorData<int8_t>(input),
  	ElementCount(*input->dims));
  const int8_t* pInput =
      (const int8_t*)tflite::micro::GetTensorData<int8_t>(input);
  int8_t* pOutput = (int8_t*)tflite::micro::GetTensorData<int8_t>(output);
  for (int out = 0; out < outer_size; out++) {
    SoftMaxQuantizedInt8(diffMin, inputMultipler, pOutput, pInput, depth);

    pOutput += depth;
    pInput += depth;
  }
   KN_PRINT_Q7_SIZE( tflite::micro::GetTensorData<int8_t>(output),
 	ElementCount(*output->dims));
  return kTfLiteOk;
}
#endif
static TfLiteStatus SoftmaxQuantized(const TfLiteEvalTensor* input,
	TfLiteEvalTensor* output,
	const SoftmaxParams& op_data) {
	const auto input_shape = tflite::micro::GetTensorShape(input);
	const auto output_shape = tflite::micro::GetTensorShape(output);
#if defined(DMX1A_SOFTMAX_OPT) || defined(HMD1A_SOFTMAX_OPT)
	if (input->type == kTfLiteInt8 && output->type == kTfLiteInt8)
	{
		SoftmaxQuantizedInt8Int8(input, output, op_data);
	}
	else
#endif

#ifndef REMOVE_REFOP_SUPPORT
	{
		if (input->type == kTfLiteUInt8) {
			tflite::reference_ops::Softmax(
				op_data, input_shape, tflite::micro::GetTensorData<uint8_t>(input),
				output_shape, tflite::micro::GetTensorData<uint8_t>(output));
		}
		else if (input->type == kTfLiteInt8) {
			if (output->type == kTfLiteInt16) {
				tflite::reference_ops::Softmax(
					op_data, input_shape, tflite::micro::GetTensorData<int8_t>(input),
					output_shape, tflite::micro::GetTensorData<int16_t>(output));
			}
			else if (input->type == kTfLiteInt8)

			{
                KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(input),
                    ElementCount(*input->dims));
				tflite::reference_ops::Softmax(
					op_data, tflite::micro::GetTensorShape(input),
					tflite::micro::GetTensorData<int8_t>(input),
					tflite::micro::GetTensorShape(output),
					tflite::micro::GetTensorData<int8_t>(output));
                KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                    ElementCount(*output->dims));
			}
		}
		else {
			tflite::reference_ops::SoftmaxInt16(
				op_data, input_shape, tflite::micro::GetTensorData<int16_t>(input),
				output_shape, tflite::micro::GetTensorData<int16_t>(output));
		}
	}
#else
	{
		return kTfLiteError;
	}
#endif
  return kTfLiteOk;
}

TfLiteStatus SoftmaxEval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);
  TfLiteStatus status = kTfLiteOk;
  TFLITE_DCHECK(node->user_data != nullptr);
  SoftmaxParams op_data = *static_cast<SoftmaxParams*>(node->user_data);

  switch (input->type) {
    case kTfLiteFloat32: {
      SoftmaxFloat(input, output, op_data);
      return kTfLiteOk;
    }
    case kTfLiteInt8:
    case kTfLiteUInt8:
    case kTfLiteInt16:

    {
      status = SoftmaxQuantized(input, output, op_data);
      return status;
    }
    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                         TfLiteTypeGetName(input->type), input->type);
      return kTfLiteError;
  }
}
#if defined(DMX1A_SOFTMAX_OPT) || defined(HMD1A_SOFTMAX_OPT)
TfLiteStatus SoftmaxEvalInt8(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);
  TfLiteStatus status = kTfLiteOk;
  TFLITE_DCHECK(node->user_data != nullptr);
  SoftmaxParams op_data = *static_cast<SoftmaxParams*>(node->user_data);

  if (input->type != kTfLiteInt8 && output->type != kTfLiteInt8) {
    TF_LITE_KERNEL_LOG(context, "Type in %s (%d)/out%s (%d)  not supported.",
                       TfLiteTypeGetName(input->type), input->type,
                       TfLiteTypeGetName(output->type), output->type);
    return kTfLiteError;
  }

  status = SoftmaxQuantizedInt8Int8(input, output, op_data);
  return status;
}
#endif
TfLiteStatus SoftmaxEvalFloat32(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteEvalTensor* input = tflite::micro::GetEvalInput(context, node, 0);
  TfLiteEvalTensor* output = tflite::micro::GetEvalOutput(context, node, 0);
  TfLiteStatus status = kTfLiteOk;
  TFLITE_DCHECK(node->user_data != nullptr);
  SoftmaxParams op_data = *static_cast<SoftmaxParams*>(node->user_data);

  if (input->type != kTfLiteFloat32 && output->type != kTfLiteFloat32) {
    TF_LITE_KERNEL_LOG(context, "Type in %s (%d)/out%s (%d)  not supported.",
                       TfLiteTypeGetName(input->type), input->type,
                       TfLiteTypeGetName(output->type), output->type);
    return kTfLiteError;
  }
  SoftmaxFloat(input, output, op_data);
  return status;
}
}  // namespace

TFLMRegistration Register_SOFTMAX() {
  return tflite::micro::RegisterOp(SoftmaxInit,
          /*prepare=*/SoftmaxPrepare,
          /*invoke=*/SoftmaxEval);
}
#if defined(DMX1A_SOFTMAX_OPT) || defined(HMD1A_SOFTMAX_OPT)
TFLMRegistration Register_SOFTMAX_INT8_INT8() {
  return tflite::micro::RegisterOp(SoftmaxInit,
          /*prepare=*/SoftmaxPrepareInt8,
          /*invoke=*/SoftmaxEvalInt8);
}
#endif
TFLMRegistration Register_SOFTMAX_FLOAT32_FLOAT32() {
  return tflite::micro::RegisterOp(SoftmaxInit,

          /*prepare=*/SoftmaxPrepare,
          /*invoke=*/SoftmaxEvalFloat32);
}
}  // namespace tflite
