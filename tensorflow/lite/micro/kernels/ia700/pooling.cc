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

#include "tensorflow/lite/micro/ia700/config.h"

//#include "flatbuffers/base.h"  // from @flatbuffers
#include "tensorflow/lite/c/builtin_op_data.h"
#ifndef REMOVE_REFOP_SUPPORT
#include "tensorflow/lite/kernels/internal/reference/integer_ops/pooling.h"
#include "tensorflow/lite/kernels/internal/reference/pooling.h"
#endif
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/padding.h"
#include "tensorflow/lite/micro/kernels/ia700/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
namespace tflite {
// namespace ops {
// namespace micro {
//		namespace pooling {

//		namespace {

constexpr int kPoolingInputTensor = 0;
constexpr int kPoolingOutputTensor = 0;

struct OpData {
  TfLitePaddingValues padding;
  // Index to buffer for optimizations if applicable.
  int buffer_idx;

  int32_t activation_min;
  int32_t activation_max;
  ds_conv2d_layer_t conv2d;
  uint32_t im2col_scratch_bytes;
  uint32_t output_scratch_bytes;
  int32_t opt_constraint;
  // int32_t is_activation_q7;
};

TfLiteStatus CalculateOpData(TfLiteContext *context,
                             const TfLitePoolParams *params,
                             const TfLiteTensor *input, TfLiteTensor *output,
                             OpData *data) {
  // input: batch, height, width, channel
  int height = SizeOfDimension(input, 1);
  int width = SizeOfDimension(input, 2);

  int out_height, out_width;

  data->padding = ComputePaddingHeightWidth(
      params->stride_height, params->stride_width,
      /*dilation_rate_height=*/1,
      /*dilation_rate_width=*/1, height, width, params->filter_height,
      params->filter_width, params->padding, &out_height, &out_width);

  if (input->type != kTfLiteFloat32) {
    TF_LITE_ENSURE_STATUS(CalculateActivationRangeQuantized(
        context, params->activation, output, &data->activation_min,
        &data->activation_max));
    TFLITE_DCHECK_LE(data->activation_min, data->activation_max);
  }

  // Set buffer index to a reset value
  data->buffer_idx = -1;

  return kTfLiteOk;
}

static TfLiteStatus AverageEvalFloat(const TfLiteContext *context,
                                     const TfLiteNode *node,
                                     const TfLitePoolParams *params,
                                     const OpData &data,
                                     const TfLiteEvalTensor *input,
                                     TfLiteEvalTensor *output) {
#ifndef REMOVE_REFOP_SUPPORT
  float activation_min, activation_max;
  CalculateActivationRange(params->activation, &activation_min,
                           &activation_max);

  PoolParams op_params;
  op_params.stride_height = params->stride_height;
  op_params.stride_width = params->stride_width;
  op_params.filter_height = params->filter_height;
  op_params.filter_width = params->filter_width;
  op_params.padding_values.height = data.padding.height;
  op_params.padding_values.width = data.padding.width;
  op_params.float_activation_min = activation_min;
  op_params.float_activation_max = activation_max;
  reference_ops::AveragePool(op_params, tflite::micro::GetTensorShape(input),
                             tflite::micro::GetTensorData<float>(input),
                             tflite::micro::GetTensorShape(output),
                             tflite::micro::GetTensorData<float>(output));
  return kTfLiteOk;
#else
  return kTfLiteError;
#endif
}

#ifdef HEMILITE_POOL_OPT
static VAR_ALIGN_8 const unsigned int bytearray_hmd[] = {

    0x44444444,
    0x88888888,
    0x11111111,
    0x22222222,

};

int AvgPoolQuantizedKernelInt8(const OpData &data, const int32_t *x,
                               int8_t *pOut, int32_t *pScratchOuput, int n,
                               int depth, int filter_count, int sign) {
#ifdef KN_DEBUG
  CHECK_ALIGN_8(x);
#endif
  static VAR_ALIGN_8 uint32_t tempVB[4 * 4] = {
      0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101,
      0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101,
      0x01010101, 0x01010101, 0x01010101, 0x01010101,
  };
  const int8_t *pX = (int8_t *)x;
  const int8_t *pXGroup8 = (int8_t *)x;
  // const int8_t *pAct2 = (int8_t*)x +m;
  int8_t *pY = pOut;
  uint32_t *pTempVBPtr = tempVB;
  int m2 = (depth + 3) >> 2;  // 32x2 8

  int32_t *pDst = pScratchOuput;
  uint32_t *pBitArrays2 = (uint32_t *)bytearray_hmd;

  vr64 VR_out, VR_invFilterCount;
  vr64 VR_const1;  // , VR_x2;
  vr64 VR_acc, VR_coeff;
  atbool signSpec = (atbool)(sign);
  int exp_fxp = (sign == 2) ? 31 - 1 : 31 - 2;

  int n8 = (n / depth) >> 3;
  int n8R = (((n / depth) & 7));

  replicate_ar(VR_coeff, 0x3, 0x01010101);

  // KN_PRINTD(m2);

  // KN_PRINTD(n8);KN_PRINTD(n8R);
  set_BB_vrVB67_zero();
  VR_const1 = load32x2_vr_idxI(pTempVBPtr, IDX0);
  load_VB1_postI(pTempVBPtr, INC1);
  load_VB2_postI(pTempVBPtr, INC1);
  load_VB3_postI(pTempVBPtr, INC1);

  for (int jj = 0; jj < m2; jj++) {
    //
    VR_acc = vseta_vr(0, 0);
    mov_AccExtend_vr(VR_acc);
    pX = pXGroup8;
    // KN_PRINTX(((unsigned)pX-(unsigned)x));
    for (int ii = 0; ii < n8; ii++) {
      vr64 VR_coeff2, VR_coeff3, VR_coeff4;
      // pTempVBPtr = tempVB;

      WUR_MvmAux(0);

      pBitArrays2 = (uint32_t *)bytearray_hmd;
      load_BB0_postI(pBitArrays2, INC1);
      load_BB1_postI(pBitArrays2, INC1);

      // 16*4 = 64
      load32x1_vr_postR(VR_coeff, pX, m2,
                        VRL);  // load Y Temp, move in the loop boday
      load32x1_vr_postR(VR_coeff, pX, m2, VRH);  // VR16

      mac8bx8b_sparse(VR_acc, VR_coeff, VR_const1, signSpec);
      load32x1_vr_postR(VR_coeff2, pX, m2,
                        VRL);  // load Y Temp, move in the loop boday
      load32x1_vr_postR(VR_coeff2, pX, m2, VRH);  // VR16

      mac8bx8b_sparse(VR_acc, VR_coeff2, VR_const1, signSpec);

      load32x1_vr_postR(VR_coeff3, pX, m2,
                        VRL);  // load Y Temp, move in the loop boday
      load32x1_vr_postR(VR_coeff3, pX, m2, VRH);  // VR16

      mac8bx8b_sparse(VR_acc, VR_coeff3, VR_const1, signSpec);

      load32x1_vr_postR(VR_coeff4, pX, m2,
                        VRL);  // load Y Temp, move in the loop boday
      load32x1_vr_postR(VR_coeff4, pX, m2, VRH);  // VR16

      mac8bx8b_sparse(VR_acc, VR_coeff4, VR_const1, signSpec);
    }
    VR_coeff = vseta_vr(0, 0);
    for (int kk = 0; kk < n8R; kk++) {
      WUR_MvmAux(0);

      set_BB_vrVB67_zero();
      load32x1_vr_postR(VR_coeff, pX, m2, VRL);  // load column 8
      pBitArrays2 = (uint32_t *)bytearray_hmd;
      load_BB0_postI(pBitArrays2, INC1);
      load_BB1_postI(pBitArrays2, INC1);

      mac8bx8b_sparse(VR_acc, VR_coeff, VR_const1, signSpec);
    }
    pXGroup8 += 4;
    store32x2_vr_postI(VR_acc, pDst, INC1);
    store_AccExtend_postI(pDst, INC1);
  }

  AScalar inverse_n = AScalar(filter_count).inverse();
  replicate_ar(VR_invFilterCount, 0x3, inverse_n.fr);

  pDst = pScratchOuput;
  int m4 = depth >> 1;
  if (m4 > 0) {
    //   load32x4_vr_postI(VR_x0, pDst, INC1);
    for (int jj = 0; jj < m4; jj++) {
      load32x2_vr_postI(VR_acc, pDst, INC1);
      convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ0);  // 17, Q7 + Q7 , 14+2 , 16
      convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ1);
      // convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ2 );
      // convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ3 );

      VR_out = vmuls(VR_acc, VR_invFilterCount, 0);  // VR_out[0] = total/n
      convert_32F_to_16I_x2(VR_out, 15, 1);          // rounding
      VR_out = shift32_arith(VR_out, (unsigned)-16, 0);

      SATURATE_INT32_VR64(VR_out, VR_out, data.activation_min,
                          data.activation_max);

      // VR_out = shift8_into32_arith(VR_out, 24, 0, VRQ0);
      VR_out = shift32_arith(VR_out, 24, 0);

      // store8x2_vr_postI(VR_out, pY, INC1);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
    }
  }
  if (depth & 1) {
    load32x2_vr_postI(VR_acc, pDst, INC1);
    //   load32x4_vr_postI(VR_x0, pDst, INC1);

    convert_32I_to_32F_x1(VR_acc, exp_fxp, VRQ0);  // 17, Q7 + Q7 , 14+2 , 16

    VR_out = vmuls(VR_acc, VR_invFilterCount, 0);  // VR_out[0] = total/n
    convert_32F_to_16I_x2(VR_out, 15, 1);          // rounding
    VR_out = shift32_arith(VR_out, (unsigned)-16, 0);

    SATURATE_INT32_VR64(VR_out, VR_out, data.activation_min,
                        data.activation_max);

    // VR_out = shift8_into32_arith(VR_out, 24, 0, VRQ0);
    VR_out = shift32_arith(VR_out, 24, 0);

    store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
  }

  return 0;  // (unsigned)pA1 - (unsigned)pAinput; //stride of A
}

// align

int MaxPoolKernelQuantizedUInt8(
    const OpData &data,
    const int8_t *x,  // align up16 buffer, zero paddding
    int8_t *pOut, int32_t *pScratchOuput, int n, int depth) {
  // int n4 = (n)>>2; // align-up 4 padding 16 byte zero
  vr64 VR_data, VR_max, VR_out;
  vr64 VR_mask;
  int m2 = (depth + 1) >> 1;
  const int8_t *pData = x;
  int8_t *pDataGroup = (int8_t *)pData;
  int32_t *pDst = pScratchOuput;
  int8_t *pY = pOut;
  mir18 mir_idx;
  int n4 = (n / depth);  // >> 2;
  int cvt_32f = 15;
  int depthInc = (depth + 1) >> 1;

  replicate_ar(VR_mask, 0x3, 0x00ff0000);
#ifdef KN_DEBUG
  CHECK_ALIGN_4(pData);
#endif

  for (int jj = 0; jj < m2; jj++) {
    pData = pDataGroup;
    load8x2_vr_postR(VR_data, pData, depthInc);

    VR_out = shift32_arith(VR_data, -8, 0);
    VR_out = vbool(VR_mask, VR_out, 0x8);

    convert_16I_to_32F_x2(VR_out, cvt_32f);
    vmaxmin_init(VR_max, VR_out, mir_idx);

    for (int ii = 0; ii < n4 - 1; ii++) {
      load8x2_vr_postR(VR_data, pData, depthInc);
      VR_out = shift32_arith(VR_data, -8, 0);
      VR_out = vbool(VR_mask, VR_out, 0x8);

      convert_16I_to_32F_x2(VR_out, cvt_32f);

      vmax_idx(VR_max, VR_out, mir_idx);
    }

    convert_32F_to_16I_x2(VR_max, 15, 1);  // rounding
    VR_max = shift32_arith(VR_max, (unsigned)-16, 0);

    store32x2_vr_postI(VR_max, pDst, INC1);
    pDataGroup += 2;  // byte ?
  }
  int loopLim = depth >> 1;
  pDst = pScratchOuput;
  if (loopLim > 0) {
    for (int ii = 0; ii < loopLim; ii++) {
      load32x2_vr_postI(VR_max, pDst, INC1);
      SATURATE_INT32_VR64(VR_max, VR_max, data.activation_min,
                          data.activation_max);
      VR_out = shift32_arith(VR_max, 24, 0);

      // store8x2_vr_postI(VR_out, pY, INC1);

      store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
      store8x1_vr_postI(VR_out, pY, INC1, VRQ1);
    }
  }

  if (depth & 1) {
    load32x1_vr_postI(VR_max, pDst, INC1, VRQ0);
    SATURATE_INT32_VR_IDX(VR_max, VR_max, data.activation_min,
                          data.activation_max, VRQ0);
    VR_out = shift32_arith(VR_max, 24, 0);

    store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
  }

  return 0;
}

int MaxPoolKernelQuantizedInt8(
    const OpData &data,
    const int8_t *x,  // align up16 buffer, zero paddding
    int8_t *pOut, int32_t *pScratchOuput, int n, int depth) {
  // int n4 = (n)>>2; // align-up 4 padding 16 byte zero
  vr64 VR_data, VR_max, VR_out;
  // vr128 VR_mask;
  int m2 = (depth + 1) >> 1;
  const int8_t *pData = x;
  int8_t *pDataGroup = (int8_t *)pData;
  int32_t *pDst = pScratchOuput;
  int8_t *pY = pOut;
  // int idx;
  mir18 mir_idx;
  int n4 = (n / depth);  // >> 2;
  int cvt_32f = 7;
  int depthInc = (depth + 1) >> 1;
#ifdef KN_DEBUG
  CHECK_ALIGN_4(pData);
#endif

  for (int jj = 0; jj < m2; jj++) {
    pData = pDataGroup;
    load16x1_vr_postR(VR_data, pData, depthInc, VRQ0);

    VR_out = shift8_into32_arith(VR_data, 24, 0, VRQ0, 1);

    convert_16I_to_32F_x2(VR_out, cvt_32f);
    vmaxmin_init(VR_max, VR_out, mir_idx);

    for (int ii = 0; ii < n4 - 1; ii++) {
      load16x1_vr_postR(VR_data, pData, depthInc, VRQ0);

      VR_out = shift8_into32_arith(VR_data, 24, 0, VRQ0, 1);

      convert_16I_to_32F_x2(VR_out, cvt_32f);
      vmax_idx(VR_max, VR_out, mir_idx);
    }

    convert_32F_to_16I_x2(VR_max, 15, 1);  // rounding
    VR_max = shift32_arith(VR_max, (unsigned)-16, 0);

    store32x2_vr_postI(VR_max, pDst, INC1);
    pDataGroup += 2;  // byte ?
  }

  int loopLim = depth >> 1;
  pDst = pScratchOuput;
  if (loopLim > 0) {
    for (int ii = 0; ii < loopLim; ii++) {
      load32x2_vr_postI(VR_max, pDst, INC1);
      SATURATE_INT32_VR64(VR_max, VR_max, data.activation_min,
                          data.activation_max);
      VR_out = shift32_arith(VR_max, 24, 0);

      store8x1_vr_postI(VR_out, pY, INC1, VRL);
      store8x1_vr_postI(VR_out, pY, INC1, VRH);
    }
  }

  if (depth & 1) {
    load32x1_vr_postI(VR_max, pDst, INC1, VRQ0);
    SATURATE_INT32_VR_IDX(VR_max, VR_max, data.activation_min,
                          data.activation_max, VRQ0);
    VR_out = shift32_arith(VR_max, 24, 0);

    store8x1_vr_postI(VR_out, pY, INC1, VRQ0);
  }
  return 0;
}

void AvgPoolQuantized(const OpData &data, const int8_t *input_data,
                      int8_t *output_data, int signs)

{
  ds_conv2d_layer_t conv2d = data.conv2d;

  int inFCM = conv2d.out_ch;
  int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

  // int inFCNA8 = (((inFCN + 7) >> 3) << 3);
  int inFCN16Size = (data.im2col_scratch_bytes) >> 4;

  int8_t *pIm2ColBuf = (int8_t *)conv2d.pIm2Col;
  int32_t *pOutputBuf = (int32_t *)conv2d.pOutput;
  int8_t *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = conv2d.ker_x;
  int32_t dim_im_in_x = conv2d.in_x;
  int32_t ch_im_in = conv2d.in_ch;
#if defined(HEMILITE_POOL_OPT)
  constexpr int group = 4;
  constexpr int shift = 2;
#endif
  int in_ch_align = (conv2d.in_ch & (group - 1)) == 0;
  int ch_align = (((conv2d.out_ch + group - 1) >> shift) << shift);
  // FIXME:
  int input_offset = 0;
  for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
    for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
      // HACK padding with input negative offset, and inputhe mac8bx8b will
      // compensate to zero

      int offset_im_src, offset_im_dst;
      int len_cpy_x, len_cpy_y;

      im2col_ex_idx im2col_tab_3;
      int padding =
          tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_3);
      len_cpy_y = im2col_tab_3.cpy_len_y;
      len_cpy_x = im2col_tab_3.len_wo_ch;
      offset_im_dst = im2col_tab_3.dst_offset_wo_ch;
      offset_im_src = im2col_tab_3.src_offset_wo_ch;

      if (!padding) {
        tflite::block_fill_words((int32_t *)pIm2ColBuf, 0, inFCN16Size * 4);
      }

#ifdef KN_DEBUG
      //  printf("tab[%3d][%3d] offset: dst: %4d src:%4d, len_y, len_x: %4d
      //  %4d\n",
      //        i_out_y, i_out_x, offset_im_dst, offset_im_src, len_cpy_y,
      //        len_cpy_x);
#endif

      if (in_ch_align) {
        tflite::im2colex_padding_offset_align4(
            pIm2ColBuf, offset_im_dst, (const int8_t *)input_data,
            offset_im_src, dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y,
            ch_im_in, input_offset);
      } else {
        // not align 8 copy
        // destination offset is multplie of 4
        // KN_ASSERT(input_offset == 0 );
        tflite::im2col_padding_unalign(
            pIm2ColBuf, offset_im_dst, (const int8_t *)input_data,
            offset_im_src, dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y,
            ch_im_in, ch_align, input_offset);
      }

      int filter_count =
          len_cpy_y * (len_cpy_x);  // actual valid input without padding inputs

      {
        AvgPoolQuantizedKernelInt8(
            data, (int32_t *)pIm2ColBuf, (int8_t *)&outBuf[outBufIdx * inFCM],
            pOutputBuf, inFCN, inFCM, filter_count, signs);
        outBufIdx += 1;
      }
      // i_out_x_prev = i_out_x;
    }
    // i_out_y_prev = i_out_y;
  }
}

void MaxPoolQuantizedInt8(const OpData &data, const int8_t *input_data,
                          int8_t *output_data, int sign = 1)

{
  ds_conv2d_layer_t conv2d = data.conv2d;

  int inFCM = conv2d.out_ch;
  int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

  int inFCNA4 = (((inFCN + 3) >> 2) << 2);
  int inFCN16Size = ((inFCNA4) + 15) / 16;

  int8_t *pIm2ColBuf = (int8_t *)conv2d.pIm2Col;
  int32_t *pOutputBuf = (int32_t *)conv2d.pOutput;
  int8_t *outBuf = output_data;
  int32_t outBufIdx = 0;
  int32_t dim_kernel_x = conv2d.ker_x;
  int32_t dim_im_in_x = conv2d.in_x;
  int32_t ch_im_in = conv2d.in_ch;

  constexpr int group = 2;
  constexpr int shift = 1;
  //#endif
  int in_ch_align = (conv2d.in_ch & (group - 1)) == 0;
  int ch_align = (((conv2d.out_ch + group - 1) >> shift) << shift);
  // FIXME:
  int init_val = sign ? 0x80808080 : 0;  // default minimum value
  int input_offset = 0;
  KN_PRINTD(inFCN);
  KN_PRINTD(inFCM);
  KN_PRINTX(pIm2ColBuf);
  KN_PRINTX(pOutputBuf);

  for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
    for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
      // HACK padding with input negative offset, and inputhe mac8bx8b will
      // compensate to zero

      int offset_im_src, offset_im_dst;
      int len_cpy_x, len_cpy_y;

      im2col_ex_idx im2col_tab_3;
      int padding =
          tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_3);
      len_cpy_y = im2col_tab_3.cpy_len_y;
      len_cpy_x = im2col_tab_3.len_wo_ch;
      offset_im_dst = im2col_tab_3.dst_offset_wo_ch;
      offset_im_src = im2col_tab_3.src_offset_wo_ch;

      if (!padding) {
        tflite::block_fill_words((int32_t *)pIm2ColBuf, init_val,
                                 inFCN16Size * 4);
      }
      if (in_ch_align) {
        tflite::im2colex_padding_offset_align4(
            pIm2ColBuf, offset_im_dst, (const int8_t *)input_data,
            offset_im_src, dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y,
            ch_im_in, input_offset);
      } else {
        // not align 8 copy
        // destination offset is multplie of 4
        // KN_ASSERT(input_offset == 0 );
        tflite::im2col_padding_unalign(
            pIm2ColBuf, offset_im_dst, (const int8_t *)input_data,
            offset_im_src, dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y,
            ch_im_in, ch_align, input_offset);
      }

      {
        if (sign) {
          MaxPoolKernelQuantizedInt8(data, (int8_t *)pIm2ColBuf,
                                     (int8_t *)&outBuf[outBufIdx * inFCM],
                                     pOutputBuf, inFCN, inFCM);
        } else {
          MaxPoolKernelQuantizedUInt8(data, (int8_t *)pIm2ColBuf,
                                      (int8_t *)&outBuf[outBufIdx * inFCM],
                                      pOutputBuf, inFCN, inFCM);
        }

        outBufIdx += 1;
      }

      // i_out_x_prev = i_out_x;
    }
    // i_out_y_prev = i_out_y;
  }
}

#endif

static TfLiteStatus AverageEvalQuantized(TfLiteContext *context,
                                         const TfLiteNode *node,
                                         const TfLitePoolParams *params,
                                         const OpData &data,
                                         const TfLiteEvalTensor *input,
                                         TfLiteEvalTensor *output) {
  TFLITE_DCHECK(input->type == kTfLiteInt16 || input->type == kTfLiteInt8);

  PoolParams op_params;
  op_params.stride_height = params->stride_height;
  op_params.stride_width = params->stride_width;
  op_params.filter_height = params->filter_height;
  op_params.filter_width = params->filter_width;
  op_params.padding_values.height = data.padding.height;
  op_params.padding_values.width = data.padding.width;
  op_params.quantized_activation_min = data.activation_min;
  op_params.quantized_activation_max = data.activation_max;

  RuntimeShape input_shape = tflite::micro::GetTensorShape(input);
  TFLITE_DCHECK_EQ(input_shape.DimensionsCount(), 4);

  RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
  TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 4);

  //    const int depth = MatchingDim(input_shape, 3, output_shape, 3);
#if defined(HEMILITE_POOL_OPT)
  if (data.opt_constraint == 1) {
    int8_t *p_aligned_scratch = nullptr;

    int sign =
        (input->type == kTfLiteUInt8) ? 2 : 3;  // Y: is unsigned or unsigned
    if (data.buffer_idx > -1) {
      p_aligned_scratch =
          (int8_t *)context->GetScratchBuffer(context, data.buffer_idx);
    }
    ds_conv2d_layer_t *conv2d = (ds_conv2d_layer_t *)&data.conv2d;

    conv2d->pIm2Col = (int32_t *)p_aligned_scratch;
    conv2d->pOutput =
        (int32_t *)((int8_t *)p_aligned_scratch + data.im2col_scratch_bytes);
    // Optimization

    AvgPoolQuantized(
        data, (const int8_t *)tflite::micro::GetTensorData<int8_t>(input),
        tflite::micro::GetTensorData<int8_t>(output), sign);

  }

  else
#endif

  {
#ifndef REMOVE_REFOP_SUPPORT
    if (input->type == kTfLiteInt16) {
      reference_integer_ops::AveragePool(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int16_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int16_t>(output));
    } else {
      reference_integer_ops::AveragePool(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int8_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int8_t>(output));
    }
#else
    return kTfLiteError;
#endif
  }
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                   ElementCount(*output->dims));
  return kTfLiteOk;
}

static TfLiteStatus MaxEvalFloat(TfLiteContext *context, TfLiteNode *node,
                                 TfLitePoolParams *params, const OpData &data,
                                 const TfLiteEvalTensor *input,
                                 TfLiteEvalTensor *output) {
  float activation_min, activation_max;
  CalculateActivationRange(params->activation, &activation_min,
                           &activation_max);
#ifndef REMOVE_REFOP_SUPPORT
  tflite::PoolParams op_params;
  op_params.stride_height = params->stride_height;
  op_params.stride_width = params->stride_width;
  op_params.filter_height = params->filter_height;
  op_params.filter_width = params->filter_width;
  op_params.padding_values.height = data.padding.height;
  op_params.padding_values.width = data.padding.width;
  op_params.float_activation_min = activation_min;
  op_params.float_activation_max = activation_max;
  reference_ops::MaxPool(op_params, tflite::micro::GetTensorShape(input),
                         tflite::micro::GetTensorData<float>(input),
                         tflite::micro::GetTensorShape(output),
                         tflite::micro::GetTensorData<float>(output));
  return kTfLiteOk;
#else
  return kTfLiteError;
#endif
}

static TfLiteStatus MaxEvalQuantized(TfLiteContext *context,
                                     const TfLiteNode *node,
                                     const TfLitePoolParams *params,
                                     const OpData &data,
                                     const TfLiteEvalTensor *input,
                                     TfLiteEvalTensor *output) {
  RuntimeShape input_shape = tflite::micro::GetTensorShape(input);
  RuntimeShape output_shape = tflite::micro::GetTensorShape(output);
  // const int depth = MatchingDim(input_shape, 3, output_shape, 3);

  tflite::PoolParams op_params;
  op_params.stride_height = params->stride_height;
  op_params.stride_width = params->stride_width;
  op_params.filter_height = params->filter_height;
  op_params.filter_width = params->filter_width;
  op_params.padding_values.height = data.padding.height;
  op_params.padding_values.width = data.padding.width;
  op_params.quantized_activation_min = data.activation_min;
  op_params.quantized_activation_max = data.activation_max;
  // check uint8
#if defined(HEMILITE_POOL_OPT)
  if (data.opt_constraint == 1) {
    int8_t *p_aligned_scratch = nullptr;

    if (data.buffer_idx > -1) {
      p_aligned_scratch =
          (int8_t *)context->GetScratchBuffer(context, data.buffer_idx);
    }
    ds_conv2d_layer_t *conv2d = (ds_conv2d_layer_t *)&data.conv2d;
    conv2d->pIm2Col = (int32_t *)p_aligned_scratch;
    conv2d->pOutput =
        (int32_t *)((int8_t *)p_aligned_scratch + data.im2col_scratch_bytes);
    // Optimization
    MaxPoolQuantizedInt8(
        data, (const int8_t *)tflite::micro::GetTensorData<int8_t>(input),
        tflite::micro::GetTensorData<int8_t>(output));
  } else
#endif
  {
#ifndef REMOVE_REFOP_SUPPORT
    if (input->type == kTfLiteInt8) {
      reference_integer_ops::MaxPool(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int8_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int8_t>(output));
    } else if (input->type == kTfLiteInt16) {
      reference_integer_ops::MaxPool(
          op_params, tflite::micro::GetTensorShape(input),
          tflite::micro::GetTensorData<int16_t>(input),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int16_t>(output));
    }
#else
    return kTfLiteError;
#endif
  }
  KN_PRINT_Q7_SIZE(tflite::micro::GetTensorData<int8_t>(output),
                   ElementCount(*output->dims));

  return kTfLiteOk;
}

//}  // namespace

void *Init(TfLiteContext *context, const char *buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(OpData));
}

TfLiteStatus MaxPrepare(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  OpData *data = static_cast<OpData *>(node->user_data);
  auto *params = reinterpret_cast<TfLitePoolParams *>(node->builtin_data);

  MicroContext *micro_context = GetMicroContext(context);

  TfLiteTensor *input =
      micro_context->AllocateTempInputTensor(node, kPoolingInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor *output =
      micro_context->AllocateTempOutputTensor(node, kPoolingOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE_STATUS(CalculateOpData(context, params, input, output, data));
  ds_conv2d_layer_t &conv2d = data->conv2d;

  RuntimeShape input_shape = GetTensorShape(input);
  TFLITE_DCHECK_EQ(input_shape.DimensionsCount(), 4);

  RuntimeShape output_shape = GetTensorShape(output);
  TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 4);

  conv2d.in_y = input_shape.Dims(1);
  conv2d.in_x = input_shape.Dims(2);
  conv2d.in_ch = input_shape.Dims(3);

  conv2d.ker_y = params->filter_height;  // filter_shape.Dims(1);
  conv2d.ker_x = params->filter_width;   // filter_shape.Dims(2);

  conv2d.out_y = output_shape.Dims(1);
  conv2d.out_x = output_shape.Dims(2);
  conv2d.out_ch = output_shape.Dims(3);

  conv2d.dilation_y = 1;
  conv2d.dilation_x = 1;
  conv2d.stride_y = params->stride_height;
  conv2d.stride_x = params->stride_width;
  conv2d.padding_y = data->padding.height;
  conv2d.padding_x = data->padding.width;

  data->opt_constraint = 0;
#if defined(HEMILITE_POOL_OPT)
  if (input->type == kTfLiteInt8) {
    if (conv2d.out_ch == conv2d.in_ch) {  // && (conv2d.out_ch&3)==0) {
      data->opt_constraint = 1;
    }

    KN_PRINTD(data->opt_constraint);
    if (data->opt_constraint) {
      int ch_align_up_4 = (((conv2d.in_ch + 3) >> 2) << 2);

      data->im2col_scratch_bytes =
          ((((ch_align_up_4 * conv2d.ker_x * conv2d.ker_y) + 15) >> 4)
           << 4);  // get scratch buffer size for optimization
      int32_t buf_size_scratch = 0;
      int buf_size_im2col =
          data->im2col_scratch_bytes;  //  data->input_scratch_bytes ;
      int32_t buf_size_output =
          (((conv2d.out_ch + 7) >> 3) << 3) *
          sizeof(int32_t);  // output store 8 multiple align

      buf_size_scratch = buf_size_im2col + buf_size_output;
      data->im2col_scratch_bytes = buf_size_im2col;
      data->output_scratch_bytes = buf_size_output;
      KN_PRINTD(data->im2col_scratch_bytes);
      KN_PRINTD(data->output_scratch_bytes);
      KN_PRINTD(buf_size_scratch);
      if (buf_size_scratch > 0) {
        TF_LITE_ENSURE_STATUS(context->RequestScratchBufferInArena(
            context, buf_size_scratch, &data->buffer_idx));

      } else {
        data->buffer_idx = -1;
      }
    }
  }
#endif

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus AveragePrepare(TfLiteContext *context, TfLiteNode *node) {
  TFLITE_DCHECK(node->user_data != nullptr);
  TFLITE_DCHECK(node->builtin_data != nullptr);

  OpData *data = static_cast<OpData *>(node->user_data);
  auto *params = reinterpret_cast<TfLitePoolParams *>(node->builtin_data);

  MicroContext *micro_context = GetMicroContext(context);

  TfLiteTensor *input =
      micro_context->AllocateTempInputTensor(node, kPoolingInputTensor);
  TF_LITE_ENSURE(context, input != nullptr);
  TfLiteTensor *output =
      micro_context->AllocateTempOutputTensor(node, kPoolingOutputTensor);
  TF_LITE_ENSURE(context, output != nullptr);

  TF_LITE_ENSURE_STATUS(CalculateOpData(context, params, input, output, data));

  data->opt_constraint = 0;
  if (input->type == kTfLiteInt8) {
    RuntimeShape input_shape = GetTensorShape(input);
    TFLITE_DCHECK_EQ(input_shape.DimensionsCount(), 4);

    RuntimeShape output_shape = GetTensorShape(output);
    TFLITE_DCHECK_EQ(output_shape.DimensionsCount(), 4);

    //    const int depth = MatchingDim(input_shape, 3, output_shape, 3);
    //  const int output_width = output_shape.Dims(2);
    ds_conv2d_layer_t &conv2d = data->conv2d;

    conv2d.in_y = input_shape.Dims(1);
    conv2d.in_x = input_shape.Dims(2);
    conv2d.in_ch = input_shape.Dims(3);

    conv2d.ker_y = params->filter_height;  // filter_shape.Dims(1);
    conv2d.ker_x = params->filter_width;   // filter_shape.Dims(2);

    conv2d.out_y = output_shape.Dims(1);
    conv2d.out_x = output_shape.Dims(2);
    conv2d.out_ch = output_shape.Dims(3);

    conv2d.dilation_x = 1;
    conv2d.dilation_y = 1;
    conv2d.stride_y = params->stride_height;
    conv2d.stride_x = params->stride_width;
    conv2d.padding_y = data->padding.height;
    conv2d.padding_x = data->padding.width;
    // conv2d.input_offset = -data->input_zero_point;

#if defined(HEMILITE_POOL_OPT)
    if (conv2d.out_ch == conv2d.in_ch) {
      data->opt_constraint = 1;
    }

    if (data->opt_constraint) {
      int ch_align_up_8 = (((conv2d.in_ch + 7) >> 3) << 3);
      data->im2col_scratch_bytes =
          ((((ch_align_up_8 * conv2d.ker_x * conv2d.ker_y) + 15) >> 4)
           << 4);  // get scratch buffer size for optimization
      int32_t buf_size_scratch = 0;
      int buf_size_im2col =
          data->im2col_scratch_bytes;  //  data->input_scratch_bytes ;
      int32_t buf_size_output =
          (((ch_align_up_8 + 7) >> 3) << 3) *
          sizeof(int32_t);  // output store 8 multiple align

      buf_size_scratch = buf_size_im2col + buf_size_output;
      data->im2col_scratch_bytes = buf_size_im2col;
      data->output_scratch_bytes = buf_size_output;

      if (buf_size_scratch > 0) {
        TF_LITE_ENSURE_STATUS(context->RequestScratchBufferInArena(
            context, buf_size_scratch, &data->buffer_idx));

      } else {
        data->buffer_idx = -1;
      }
    }
#endif
  }

  micro_context->DeallocateTempTfLiteTensor(input);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus AverageEval(TfLiteContext *context, TfLiteNode *node) {
  auto *params = reinterpret_cast<TfLitePoolParams *>(node->builtin_data);

  const OpData &data = *(static_cast<const OpData *>(node->user_data));

  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kPoolingInputTensor);
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kPoolingOutputTensor);
  TfLiteStatus status = kTfLiteOk;
  // Inputs and outputs share the same type, guaranteed by the converter.
  switch (input->type) {
    case kTfLiteFloat32:
      status = AverageEvalFloat(context, node, params, data, input, output);
      break;

    case kTfLiteInt16:
    case kTfLiteInt8:
      status = AverageEvalQuantized(context, node, params, data, input, output);
      break;
    default:
      TF_LITE_KERNEL_LOG(context, "Input type %s is not currently supported",
                         TfLiteTypeGetName(input->type));
      return kTfLiteError;
  }
  return status;
}
TfLiteStatus AverageEvalInt8(TfLiteContext *context, TfLiteNode *node) {
  auto *params = reinterpret_cast<TfLitePoolParams *>(node->builtin_data);

  const OpData &data = *(static_cast<const OpData *>(node->user_data));

  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kPoolingInputTensor);
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kPoolingOutputTensor);

  // Inputs and outputs share the same type, guaranteed by the converter.
  if (input->type != kTfLiteInt8) {
    TF_LITE_KERNEL_LOG(context, "Input type %s is not currently supported",
                       TfLiteTypeGetName(input->type));
    return kTfLiteError;
  }

  AverageEvalQuantized(context, node, params, data, input, output);

  return kTfLiteOk;
}
TfLiteStatus MaxEval(TfLiteContext *context, TfLiteNode *node) {
  auto *params = reinterpret_cast<TfLitePoolParams *>(node->builtin_data);

  const OpData &data = *(static_cast<const OpData *>(node->user_data));

  TfLiteStatus status = kTfLiteOk;
  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kPoolingInputTensor);
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kPoolingOutputTensor);

  switch (input->type) {
    case kTfLiteFloat32:
      status = MaxEvalFloat(context, node, params, data, input, output);
      break;

    // case kTfLiteUInt8:
    //  status =
    //      MaxEvalQuantizedUInt8(context, node, params, data, input, output);
    //  break;
    case kTfLiteInt16:
    case kTfLiteInt8:
      status = MaxEvalQuantized(context, node, params, data, input, output);
      break;
    default:
      TF_LITE_KERNEL_LOG(context, "Type %s not currently supported.",
                         TfLiteTypeGetName(input->type));
      return kTfLiteError;
  }
  return status;
}

TfLiteStatus EvalMaxInt8(TfLiteContext *context, TfLiteNode *node) {
  auto *params = reinterpret_cast<TfLitePoolParams *>(node->builtin_data);

  const OpData &data = *(static_cast<const OpData *>(node->user_data));

  const TfLiteEvalTensor *input =
      tflite::micro::GetEvalInput(context, node, kPoolingInputTensor);
  TfLiteEvalTensor *output =
      tflite::micro::GetEvalOutput(context, node, kPoolingOutputTensor);

  if (input->type != kTfLiteInt8) {
    TF_LITE_KERNEL_LOG(context, "Type %s not currently supported.",
                       TfLiteTypeGetName(input->type));
    return kTfLiteError;
  }

  return MaxEvalQuantized(context, node, params, data, input, output);
}
//	}  // namespace pooling

TFLMRegistration Register_AVERAGE_POOL_2D() {
  return tflite::micro::RegisterOp(Init,
                                   /*prepare=*/AveragePrepare,
                                   /*invoke=*/AverageEval);
}
TFLMRegistration Register_AVERAGE_POOL_2D_INT8() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/AveragePrepare,
                                   /*invoke=*/AverageEvalInt8);
}
TFLMRegistration Register_MAX_POOL_2D() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/MaxPrepare,
                                   /*invoke=*/MaxEval);
}

TFLMRegistration Register_MAX_POOL_2D_INT8() {
  return tflite::micro::RegisterOp(Init,

                                   /*prepare=*/MaxPrepare,
                                   /*invoke=*/EvalMaxInt8);
}
//}  // namespace micro
//}  // namespace ops

}  // namespace tflite
