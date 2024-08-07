/*
*/

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
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"

#include "tensorflow/lite/micro/micro_utils.h"  //@elementcount
namespace tflite {
	namespace {

        int ConvFloatInt8Kernelx2(float* y1, const float* x2,
            float* y2, const float* x1, const int8_t* A, const float* bias,
            int m, int n, const AScalar& act_min,
            const AScalar& act_max, const AScalar& scale, AScalar* scale_ptr = nullptr // optional scale is per output channel
        ) {
            int loopGroupLim = (m >> 2);
            int loopBlockLim2 = (n >> 2);
            //  int jammingBit = RUR_JammingBit();
            const int8_t* pW = A;
            //  int maxExp;
            int ii, jj;

            float* pActOut;
            const float* pBiasLocal;
            //   WUR_JammingBit(1);
            int8_t* pWa0;
            int8_t* pWa1;
            int8_t* pWa2;
            int8_t* pWa3;

            vr128 VR_w0;
            vr128 VR_act_max, VR_act_min;
            vr128 VR_scale;
            const int wBlkExp = 7;
            // mir30 mirIdx;
            // vr128 VR_exp;
            ulsr128 UR_w0, UR_w1, UR_w2, UR_w3;
            ulsr128 UR_blk;
            ulsr128 UR_actOut, UR_bias;
            // unsigned Maxidx;

            replicate_ar(VR_act_max, 0xf, act_max.fr);
            replicate_ar(VR_act_min, 0xf, act_min.fr);
            AScalar* pScalePerCh = scale_ptr;
            replicate_ar(VR_scale, 0xf, scale.fr);
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
                    //vr128 VR_out2 = VR_blk;
                    //vr128 VR_out3 = VR_blk;
                    vr128 VR_bias;
                    vr128 VR_actOut = VR_blk;

                    pWa3 = pWa2 = pWa1 = pWa0 = (int8_t*)pW;
                    load8x1_vr_postR(VR_out0, pWa1, n, VRQ0);
                    load8x1_vr_postR(VR_out0, pWa2, n * 2, VRQ0);
                    load8x1_vr_postR(VR_out1, pWa3, n * 3, VRQ0);  // dummy load

                    VR_out0 = vadds(VR_out0, VR_out0, 0xf0);
                    VR_out1 = vadds(VR_out1, VR_out1, 0xf0);
                    // VR_out2 = vadds(VR_out2, VR_out2, 0xf0);
                    // VR_out3 = vexp_adji(VR_out1, 0);
                    float* pIn0 = (float*)x;
                    if (loopBlockLim2 > 0) {
                        // register vr128 VR_act;
                        UR_w0 = align_8x4_load(pWa0);
                        UR_w1 = align_8x4_load(pWa1);
                        UR_w2 = align_8x4_load(pWa2);
                        UR_w3 = align_8x4_load(pWa3);
                        UR_blk = align_32x4_load(pIn0);
                        load_32x4_vr_a(VR_blk, UR_blk, pIn0);
                        convert_IEEE_float_to_32F_x4(VR_blk);
                        load_8x4_vr_a(VR_w0, UR_w0, pWa0);
                        // convert IEEE to afloat
                        convert_16I_to_32F_x4(VR_w0, wBlkExp);
                        for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
                        {
                            // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
                            affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
                            //    KN_PRINT_VR128(VR_out0);
                            load_8x4_vr_a(VR_w0, UR_w1, pWa1);
                            convert_16I_to_32F_x4(VR_w0, wBlkExp);
                            affine_adj_H(VR_out0, VR_w0, VR_blk, 0, 0);
                            load_8x4_vr_a(VR_w0, UR_w2, pWa2);
                            convert_16I_to_32F_x4(VR_w0, wBlkExp);
                            affine_adj_L(VR_out1, VR_w0, VR_blk, 0, 0);
                            load_8x4_vr_a(VR_w0, UR_w3, pWa3);
                            convert_16I_to_32F_x4(VR_w0, wBlkExp);
                            affine_adj_H(VR_out1, VR_w0, VR_blk, 0, 0);

                            load_32x4_vr_a(VR_blk, UR_blk, pIn0);  // next for block

                            convert_IEEE_float_to_32F_x4(VR_blk);
                            load_8x4_vr_a(VR_w0, UR_w0, pWa0);
                            convert_16I_to_32F_x4(VR_w0, wBlkExp);
                        }
                        // KN_PRINT_VR128(VR_blk);  KN_PRINT_VR128(VR_w0);
                        affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
                        //   KN_PRINT_VR128(VR_out0);
                        load_8x4_vr_a(VR_w0, UR_w1, pWa1);
                        convert_16I_to_32F_x4(VR_w0, wBlkExp);
                        affine_adj_H(VR_out0, VR_w0, VR_blk, 0, 0);
                        load_8x4_vr_a(VR_w0, UR_w2, pWa2);
                        convert_16I_to_32F_x4(VR_w0, wBlkExp);
                        affine_adj_L(VR_out1, VR_w0, VR_blk, 0, 0);
                        load_8x4_vr_a(VR_w0, UR_w3, pWa3);
                        convert_16I_to_32F_x4(VR_w0, wBlkExp);
                        affine_adj_H(VR_out1, VR_w0, VR_blk, 0, 0);
                    }

                    if (n & 3) {
                        load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
                        convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0);
                        load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

                        convert_IEEE_float_to_32F_x4(VR_blk);
                        for (ii = loopBlockLim2 << 2; ii < n; ii++) {
                            fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);
                            load8x1_vr_postI(VR_w0, pWa1, INC1, VRQ0);
                            convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0);

                            fmacs(VR_out0, VRQ2, VR_w0, VRQ0, VR_blk, VRQ0, 0);

                            load8x1_vr_postI(VR_w0, pWa2, INC1, VRQ0);
                            convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0);

                            fmacs(VR_out1, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);

                            load8x1_vr_postI(VR_w0, pWa3, INC1, VRQ0);
                            convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0);

                            fmacs(VR_out1, VRQ2, VR_w0, VRQ0, VR_blk, VRQ0, 0);

                            load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
                            load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
                            convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0);
                            convert_IEEE_float_to_32F_x4(VR_blk);

                        }
                    }
                    // KN_PRINT_VR128(VR_out0);
                    dsums_L(VR_actOut, VR_out0, 0, 0);
                    dsums_H(VR_actOut, VR_out1, 0, 0);
                    if (scale_ptr)
                        load32x4_vr_postI(VR_scale, pScalePerCh, INC1);

                    VR_actOut = vmuls(VR_actOut, VR_scale, 0);
                    //   KN_PRINT_VR128(VR_actOut);
                    //  if (pBiasLocal) {
                    load_32x4_vr_a(VR_bias, UR_bias, pBiasLocal);
                    //  } else {
                    //    VR_bias = vseta_vr(kConstTable_Zero, 0, 0);
                    //  }
                    //convert_IEEE_float_to_32F_x4(VR_bias);
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

                pWa0 = (int8_t*)pW;  // 1st group

                VR_out0 = vexp_adji(VR_actOut, 0x0);

                float* pIn0 = (float*)x;
                if (loopBlockLim2 > 0) {
                    UR_w0 = align_8x4_load(pWa0);

                    UR_blk = align_32x4_load(pIn0);
                    load_32x4_vr_a(VR_blk, UR_blk, pIn0);
                    load_8x4_vr_a(VR_w0, UR_w0, pWa0);
                    convert_16I_to_32F_x4(VR_w0, wBlkExp);
                    convert_IEEE_float_to_32F_x4(VR_blk);

                    for (ii = 0; ii < loopBlockLim2 - 1; ii++)  // group
                    {
                        affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
                        load_8x4_vr_a(VR_w0, UR_w0, pWa0);
                        convert_16I_to_32F_x4(VR_w0, wBlkExp);

                        load_32x4_vr_a(VR_blk, UR_blk, pIn0);  // next for block
                        convert_IEEE_float_to_32F_x4(VR_blk);
                    }

                    affine_adj_L(VR_out0, VR_w0, VR_blk, 0, 0);
                }

                if (n & 3) {
                    load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
                    convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0);
                    //  VR_blk = vpermsi(VR_blk, VR_blk, 0, SHR_BY_1_ELEM);
                    load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);

                    convert_IEEE_float_to_32F_x4(VR_blk);
                    //convert_IEEE_float_to_32F_x4(VR_w0);

                    for (ii = loopBlockLim2 << 2; ii < n; ii++) {
                        fmacs(VR_out0, VRQ0, VR_w0, VRQ0, VR_blk, VRQ0, 0);

                        load32x1_vr_postI(VR_blk, pIn0, INC1, VRQ0);
                        load8x1_vr_postI(VR_w0, pWa0, INC1, VRQ0);
                        convert_16I_to_32F_x1(VR_w0, wBlkExp, VRQ0);

                        convert_IEEE_float_to_32F_x4(VR_blk);
                        //convert_IEEE_float_to_32F_x4(VR_w0);
                    }
                }
                dsums_L(VR_actOut, VR_out0, 0, 0);
                if (scale_ptr)
                    load32x1_vr_postI(VR_scale, pScalePerCh, INC1, VRQ0);
                VR_actOut = vmuls(VR_actOut, VR_scale, 0);
                //fadds(VR_actOut, VRQ0, VR_out0, VRQ1, VR_out0, VRQ0, 0);
                // VR_exp = afloat_exp_extract(VR_actOut);
                // fmax(VR_maxExp, VRQ0, VR_maxExp, VRQ0, VR_exp, VRQ0);
                // if (pBiasLocal) {
                load32x1_vr_postI(VR_bias, pBiasLocal, INC1, VRQ0);
                //  } else {
                //   VR_bias = vseta_vr(kConstTable_Zero, 0, 0);
                //  }
                //convert_IEEE_float_to_32F_x4(VR_bias);
                VR_actOut = vadds(VR_actOut, VR_bias, 0);
                VR_actOut = vmax(VR_actOut, VR_act_min);
                VR_actOut = vmin(VR_actOut, VR_act_max);

                convert_32F_to_IEEE_float_x4(VR_actOut);
                store32x1_vr_postI(VR_actOut, pActOut, INC1, VRQ0);

                pW += n;  // add to next group
            }
            return 0;  //(maxExp-31);
        }
TfLiteStatus
PWConvFloatInt8Kernel(float* y, const float* x, const int8_t* A, const float* bias,
	int m, int n, const AScalar& act_min,
	const AScalar& act_max, const AScalar& scale, AScalar* scale_ptr = nullptr)
{
    ds_conv2d_layer_t conv2d = data_ex.conv2d;
    // AScalar act_min = AScalar(convParam.float_activation_max);
    //  AScalar act_max = AScalar (convParam.float_activation_max);
    //  const AScalar *per_channel_output_multiplier =
    //    (const AScalar *)(data_ex.ConvOp.per_channel_output_multiplier);
    int inFCM = conv2d.out_ch;
    int inFCN = conv2d.ker_x * conv2d.ker_y * conv2d.in_ch;

    // int inFCNA4 = (((inFCN + 3) >> 2) << 2);
    // int inFCN16Size = ((inFCNA4) + 15) / 16;

    float* pBuffer = (float*)conv2d.pIm2Col;

    float* outBuf = output_data;
    int32_t outBufIdx = 0;
    int32_t dim_kernel_x = conv2d.ker_x;
    int32_t dim_im_in_x = conv2d.in_x;
    int32_t ch_im_in = conv2d.in_ch;
    uint16_t dilation_y = conv2d.dilation_y;
    uint16_t dilation_x = conv2d.dilation_x;
    const AScalar scale = data_ex.filter_scale;
    AScalar* scale_per_channel = (AScalar*)data_ex.ConvOp.per_channel_output_multiplier;
    // KN_PRINTD(inFCM);
    // KN_PRINTD(inFCN);
    //         KN_PRINTF(convParam.float_activation_max);
    //      KN_PRINTF(convParam.float_activation_min);

    // KN_PRINTAFLT(act_min);
    // KN_PRINTAFLT(act_max);
    //  uint32_t input_offset = (conv2d.input_offset == 128) ? 0x80808080 : 0;  //
    for (int i_out_y = 0; i_out_y < conv2d.out_y; ++i_out_y) {
        for (int i_out_x = 0; i_out_x < conv2d.out_x; ++i_out_x) {
            // HACK padding with input negative offset, and inputhe mac8bx8b will
            // compensate to zero

            int offset_im_src, offset_im_dst;
            int len_cpy_x, len_cpy_y;
            im2col_idx im2col_tab_2;
            int padding =
                tflite::ConvIm2ColIndex(conv2d, i_out_x, i_out_y, &im2col_tab_2);
            len_cpy_y = im2col_tab_2.cpy_len_y;
            len_cpy_x = im2col_tab_2.cpy_len_x;
            offset_im_dst = im2col_tab_2.im_dst_offset;
            offset_im_src = im2col_tab_2.im_src_offset;

            if (!padding) {
                tflite::block_fill_words((int32_t*)pBuffer, 0, inFCN);
            }

            tflite::im2col_padding_align4<float>(
                pBuffer + offset_im_dst, (const float*)input_data + offset_im_src,
                dim_im_in_x, dim_kernel_x, len_cpy_x, len_cpy_y, ch_im_in, dilation_y, dilation_x);

            // TODO:unrollx4
#if 1
      // KN_PRINT_FLOAT(pBuffer, inFCN);
            {
                ConvFloatInt8Kernelx2(&outBuf[outBufIdx * inFCM], (float*)pBuffer,
                    (const int8_t*)filter_data, (const float*)bias_data,
                    inFCM, inFCN, act_min, act_max, scale, scale_per_channel);
                // KN_PRINT_FLOAT(&outBuf[outBufIdx * inFCM], inFCM);
                outBufIdx += 1;
            }
#endif
            // i_out_x_prev = i_out_x;
        }
        // i_out_y_prev = i_out_y;
    }
	return kTfLiteOk;
}
    }
}