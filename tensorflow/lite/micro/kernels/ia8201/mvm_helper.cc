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
#include <stdint.h>
//#define KN_DEBUG
#include <math.h>
#include "tensorflow/lite/micro/ia8201/config.h"
#include "tensorflow/lite/micro/kernels/ia8201/mvm_helper.h"


#define LO_SHIFT -1
#define HI_SHIFT 6
#define MVM16BX8B_FAST_Q 23
#define MVM16BX8B_FAST_EXP_FXP (32 - MVM16BX8B_FAST_Q)


namespace tflite {

#if defined(DMX1A)
    // namespace dmx1a{

    void ConvertQ15ToAfloat(const int16_t* input, AScalar* output, int size,
        int32_t bexp) {
        int size4 = size >> 2;
        const int16_t* pInput = input;
        AScalar* pOutput = output;
        if (size4 > 0) {
            vr128 vr_data;
            ulsr128 ur_in = align_16x4_load(pInput);
            ulsr128 ur_out = align_32x4_store(pOutput);
            load_16x4_vr_a(vr_data, ur_in, pInput);
            for (int ii = 0; ii < size4 - 1; ii++) {
                convert_16I_to_32F_x4(vr_data, bexp);

                store_32x4_vr_a(vr_data, ur_out, pOutput);
                load_16x4_vr_a(vr_data, ur_in, pInput);
            }
            convert_16I_to_32F_x4(vr_data, bexp);
            store_32x4_vr_a(vr_data, ur_out, pOutput);
            flush_32x4(ur_out, pOutput);
        }

        {
            for (int ii = 0; ii < (size & 3); ii++) {
                vr128 vr_data;
                load16x1_vr_postI(vr_data, pInput, INC1, VRQ0);
                convert_16I_to_32F_x1(vr_data, bexp, VRQ0);
                store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
            }
        }
    }

    void ConvertIEEEFloatToAfloat(const float* input, AScalar* output, int size) {
        int size4 = size >> 2;
        const float* pInput = input;
        AScalar* pOutput = output;
        if (size4 > 0) {
            vr128 vr_data;
            ulsr128 ur_in = align_32x4_load(pInput);
            ulsr128 ur_out = align_32x4_store(pOutput);
            load_32x4_vr_a(vr_data, ur_in, pInput);
            for (int ii = 0; ii < size4 - 1; ii++) {
                convert_IEEE_float_to_32F_x4(vr_data);

                store_32x4_vr_a(vr_data, ur_out, pOutput);
                load_32x4_vr_a(vr_data, ur_in, pInput);
            }
            convert_IEEE_float_to_32F_x4(vr_data);
            store_32x4_vr_a(vr_data, ur_out, pOutput);
            flush_32x4(ur_out, pOutput);
        }

        {
            for (int ii = 0; ii < (size & 3); ii++) {
                vr128 vr_data;
                load32x1_vr_postI(vr_data, pInput, INC1, VRQ0);
                convert_IEEE_float_to_32F_x4(vr_data);
                store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
            }
        }
    }

    void block_copy_bytes(int8_t* pDes, const int8_t* pSrc,
        int32_t nBytes) {
        int32_t ii, loopLim;
        const uint32_t* uint_Src;
        uint32_t* uint_Des;
        uint_Src = (const uint32_t*)pSrc;
        uint_Des = (uint32_t*)pDes;

        vr128 VR_S0;
        ulsr128 UR_des;
        ulsr128 UR_src;
        if ((((uint32_t)pDes & 0x3) == 0) && ((uint32_t)pSrc & 0x3) == 0) {
            uint_Src = (const uint32_t*)pSrc;
            uint_Des = (uint32_t*)pDes;
            // IMPORTANT: NOTE
            // unalignment need to alignment 32x4 NEEDS: 4 byte alignment
            UR_src = align_32x4_load(uint_Src);
            UR_des = align_32x4_store(uint_Des);

            // 16 byte copy
            loopLim = nBytes >> 4;
            if (loopLim > 0) {
                load_32x4_vr_a(VR_S0, UR_src, uint_Src);
                for (ii = 0; ii < (loopLim - 1); ii++) {
                    store_32x4_vr_a(VR_S0, UR_des, uint_Des);
                    load_32x4_vr_a(VR_S0, UR_src, uint_Src);
                }
                store_32x4_vr_a(VR_S0, UR_des, uint_Des);
                flush_32x4(UR_des, uint_Des);
            }
            for (int32_t i = loopLim << 4; i < nBytes; i++) {
                load8x1_vr_postI(VR_S0, uint_Src, INC1, VRQ0);
                store8x1_vr_postI(VR_S0, uint_Des, INC1, VRQ0);
            }
        }
        else if ((((uint32_t)pDes & 0x1) == 0) && ((uint32_t)pSrc & 0x1) == 0) {
            // for some input only 2 byte alignment
            UR_src = align_16x4_load(uint_Src);
            UR_des = align_16x4_store(uint_Des);

            // 16 byte copy
            loopLim = nBytes >> 3;
            if (loopLim > 0) {
                load_16x4_vr_a(VR_S0, UR_src, uint_Src);
                for (ii = 0; ii < (loopLim - 1); ii++) {
                    store_16x4_vr_a(VR_S0, UR_des, uint_Des);
                    load_16x4_vr_a(VR_S0, UR_src, uint_Src);
                }
                store_16x4_vr_a(VR_S0, UR_des, uint_Des);
                flush_16x4(UR_des, uint_Des);
            }
            for (int32_t i = loopLim << 3; i < nBytes; i++) {
                load8x1_vr_postI(VR_S0, uint_Src, INC1, VRQ0);
                store8x1_vr_postI(VR_S0, uint_Des, INC1, VRQ0);
            }
        }
        else {
            // byte copy
            const int kern_x_loop = (nBytes) >> 2;
            if (kern_x_loop) {
                ulsr128 ur_buf2 = align_8x4_store(uint_Des);
                ulsr128 ur_im = align_8x4_load(uint_Src);
                for (ii = 0; ii < kern_x_loop; ii++) {
                    load_8x4_vr_a(VR_S0, ur_im, uint_Src);
                    store_8x4_vr_a(VR_S0, ur_buf2, uint_Des);
                }
                flush_8x4(ur_buf2, uint_Des);
            }

            for (ii = 0; ii < (nBytes & 3); ii++) {
                load8x1_vr_postI(VR_S0, uint_Src, INC1, VRQ0);
                store8x1_vr_postI(VR_S0, uint_Des, INC1, VRQ0);
            }
        }
    }

    void ConvertQ31ToAfloat(const int32_t* input, AScalar* output, int size,
        int32_t bexp) {
        int size4 = size >> 2;
        const int32_t* pInput = input;
        AScalar* pOutput = output;
        if (size4 > 0) {
            vr128 vr_data;
            ulsr128 ur_in = align_32x4_load(pInput);
            ulsr128 ur_out = align_32x4_store(pOutput);
            load_32x4_vr_a(vr_data, ur_in, pInput);
            for (int ii = 0; ii < size4 - 1; ii++) {
                convert_32I_to_32F_x1(vr_data, bexp, VRQ0);
                convert_32I_to_32F_x1(vr_data, bexp, VRQ1);
                convert_32I_to_32F_x1(vr_data, bexp, VRQ2);
                convert_32I_to_32F_x1(vr_data, bexp, VRQ3);
                store_32x4_vr_a(vr_data, ur_out, pOutput);
                load_32x4_vr_a(vr_data, ur_in, pInput);
            }
            convert_32I_to_32F_x1(vr_data, bexp, VRQ0);
            convert_32I_to_32F_x1(vr_data, bexp, VRQ1);
            convert_32I_to_32F_x1(vr_data, bexp, VRQ2);
            convert_32I_to_32F_x1(vr_data, bexp, VRQ3);
            store_32x4_vr_a(vr_data, ur_out, pOutput);
            flush_32x4(ur_out, pOutput);
        }
        {
            for (int ii = 0; ii < (size & 3); ii++) {
                vr128 vr_data;
                load32x1_vr_postI(vr_data, pInput, INC1, VRQ0);
                convert_32I_to_32F_x1(vr_data, bexp, VRQ0);
                store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
            }
        }
    }

    void ConvertQ31ToAfloat(const int32_t* input, AScalar* output, int size,
        int32_t* pShift, int32_t baseExp) {
        int size4 = size >> 2;
        const int32_t* pInput = input;
        AScalar* pOutput = output;
        int32_t* pBexp = pShift;
        VAR_ALIGN_16 int32_t bexp[4];

        if (size4 > 0) {
            vr128 vr_data, vr_bexp;
            ulsr128 ur_in = align_32x4_load(pInput);
            ulsr128 ur_bexp = align_32x4_load(pBexp);
            ulsr128 ur_out = align_32x4_store(pOutput);
            load_32x4_vr_a(vr_data, ur_in, pInput);
            load_32x4_vr_a(vr_bexp, ur_bexp, pBexp);
            store32x4_vr_idxI(vr_bexp, bexp, IDX0);
            for (int ii = 0; ii < size4 - 1; ii++) {
                convert_32I_to_32F_x1(vr_data, baseExp + bexp[0], VRQ0);
                convert_32I_to_32F_x1(vr_data, baseExp + bexp[1], VRQ1);
                convert_32I_to_32F_x1(vr_data, baseExp + bexp[2], VRQ2);
                convert_32I_to_32F_x1(vr_data, baseExp + bexp[3], VRQ3);
                load_32x4_vr_a(vr_bexp, ur_bexp, pBexp);
                store32x4_vr_idxI(vr_bexp, bexp, IDX0);
                store_32x4_vr_a(vr_data, ur_out, pOutput);
                load_32x4_vr_a(vr_data, ur_in, pInput);
            }
            convert_32I_to_32F_x1(vr_data, baseExp + bexp[0], VRQ0);
            convert_32I_to_32F_x1(vr_data, baseExp + bexp[1], VRQ1);
            convert_32I_to_32F_x1(vr_data, baseExp + bexp[2], VRQ2);
            convert_32I_to_32F_x1(vr_data, baseExp + bexp[3], VRQ3);
            store_32x4_vr_a(vr_data, ur_out, pOutput);
            flush_32x4(ur_out, pOutput);
        }

        for (int ii = 0; ii < (size & 3); ii++) {
            vr128 vr_data, vr_bexp;
            load32x1_vr_postI(vr_data, pInput, INC1, VRQ0);
            load32x1_vr_postI(vr_bexp, pBexp, INC1, VRQ0);
            store32x1_vr_idxI(vr_bexp, bexp, IDX0, VRQ0);
            convert_32I_to_32F_x1(vr_data, baseExp + bexp[0], VRQ0);
            store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
        }
    }

    // a+ const(integer) =c
    // float 32 out
    int AddConstQuantizedInt8(int8_t* input, int32_t const_offset, uint8_t* output,
        int size) {
        int ii;  // convert to 1 to afloat and vadd return int32
        int s4 = size >> 2;

        int8_t* pA = input;
        uint8_t* pC = output;

        vr128 vr_b;

        // return error if const offset >= 128 || < -128
        int b16 = const_offset << 16;
        replicate_ar(vr_b, 0xf, b16);
        convert_16I_to_32F_x4(vr_b, 8);
        if (s4 > 0) {
            ulsr128 ur_a = align_8x4_load(pA);
            ulsr128 ur_c = align_8x4_store(pC);

            vr128 vr_a, vr_c;

            load_8x4_vr_a(vr_a, ur_a, pA);
            for (ii = 0; ii < s4 - 1; ii++) {
                convert_16I_to_32F_x4(vr_a, 0);
                vr_c = vadds(vr_a, vr_b, 0);
                load_8x4_vr_a(vr_a, ur_a, pA);
                convert_32F_to_16I_x4(vr_c, 1, 0);
                vr_c = shift32_arith(vr_c, 1, 0);
                store_8x4_vr_a(vr_c, ur_c, pC);
            }
            convert_16I_to_32F_x4(vr_a, 0);
            vr_c = vadds(vr_a, vr_b, 0);
            convert_32F_to_16I_x4(vr_c, 1, 0);
            vr_c = shift32_arith(vr_c, 1, 0);
            store_8x4_vr_a(vr_c, ur_c, pC);
            flush_8x4(ur_c, pC);
        }
        if (size & 3) {
            vr128 vr_a, vr_c;
            for (ii = 0; ii < (size & 3); ii++) {
                load8x1_vr_postI(vr_a, pA, INC1, VRQ0);
                convert_16I_to_32F_x1(vr_a, 0, VRQ0);
                vr_c = vadds(vr_a, vr_b, 0);
                convert_32F_to_16I_x4(vr_c, 1, 0);
                vr_c = shift32_arith(vr_c, 1, 0);
                store8x1_vr_postI(vr_c, pC, INC1, VRQ0);
            }
        }
        return 0;
    }

    int AddConstQuantizedInt8Fast128(int32_t* input, uint32_t* output, int size) {
        int ii;  // convert to 1 to afloat and vadd return int32
        int s4 = size >> 4;

        int32_t* pA = input;
        uint32_t* pC = output;

        vr128 vr_b;

        // return error if const offset >= 128 || < -128
        // int b16 = 0x80 << 16;
        replicate_ar(vr_b, 0xf, 0x80808080);
#ifdef KN_DEBUG
        CHECK_ALIGN_4(input);
        CHECK_ALIGN_4(output);
#endif
        // convert_16I_to_32F_x4(vr_b, 8);
        if (s4 > 0) {
            ulsr128 ur_a = align_32x4_load(pA);
            ulsr128 ur_c = align_32x4_store(pC);

            vr128 vr_a, vr_c;

            load_32x4_vr_a(vr_a, ur_a, pA);
            for (ii = 0; ii < s4 - 1; ii++) {
                vr_c = vbool(vr_a, vr_b, 0x6);  // s_vxor(vr_a, vr_b);
                load_32x4_vr_a(vr_a, ur_a, pA);
                store_32x4_vr_a(vr_c, ur_c, pC);
            }
            vr_c = vbool(vr_a, vr_b, 0x6);  // s_vxor(vr_a, vr_b);

            store_32x4_vr_a(vr_c, ur_c, pC);
            flush_32x4(ur_c, pC);
        }
        if (size & 15) {
            vr128 vr_a, vr_c;
            for (ii = 0; ii < (size & 15); ii++) {
                load8x1_vr_postI(vr_a, pA, INC1, VRQ0);
                vr_c = vbool(vr_a, vr_b, 0x6);  // s_vxor(vr_a, vr_b);
                store8x1_vr_postI(vr_c, pC, INC1, VRQ0);
            }
        }
        return 0;
    }

    void MVMInputOffsetPrepare(const int32_t* A, int32_t* output, int m, int n,
        uint32_t input_offset) {
        // int32_t *pY = output;

        const int32_t* pA = A;
        int nBlockAligned2 = ((n + 1) >> 1);
        int loopLimCol = (nBlockAligned2 >> 3);  // block 16
        int loopLimRow = ((m + 7) >> 3);         // group 8 alignment
                                          // int processLastLoop = ((m & 7) != 0);
        int32_t* pOutput = output;
        vr128 VR_A;

        vr128 VR_y;
        xtbool2 signSpecInput = int_to_xt_bool2(3);

        vr128 VR_inputOffset;
        replicate_ar(
            VR_inputOffset, 0xf,
            input_offset);  // -1 ~ -127
                            // replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);

        for (int i = 0; i < loopLimRow; i++) {
            const int32_t* pA1 = pA;
            VR_y = vseta_vr(0, 0, 0);
            mov_AccExtend_vr(VR_y);

            pA = pA1;
            ulsr128 UR_A = align_32x4_load(pA);
            load_32x4_vr_a(VR_A, UR_A, pA);
            for (int j = 0; j < loopLimCol; j++) {
                // WUR_MvmAux(0);
                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);
            }

            for (int32_t j = (loopLimCol << 3); j < nBlockAligned2; j++) {
                mac8bx8b(VR_y, VR_A, VR_inputOffset, signSpecInput);
                load_32x4_vr_a(VR_A, UR_A, pA);
            }
            // if(processLastLoop)
            store32x4_vr_postI(VR_y, pOutput, INC1);
            store_AccExtend_postI(pOutput, INC1);

            // Adjust pointer to compensate for loop priming
            pA -= 4;  // NOTE pointer type int8v4, => 16/4 = 4;
        }
    }

    //helper function for testing not for runtime
    void convert_ieee_float_to_afloat16(const float* input, uint16_t* out_float16, int size)
    {
        const float* pIn = input;
        uint16_t* pOut = out_float16;
        for (int ii = 0; ii < size;ii++)
        {
            vr128 VR_flt;
            load32x1_vr_postI(VR_flt, pIn, INC1, VRQ0);
            convert_IEEE_float_to_32F_x4(VR_flt);
            convert_32F_to_16F_x4(VR_flt, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS, 1);
            store16x1_vr_postI(VR_flt, pOut, INC1, VRQ0);
        }
    }
    //helper function for testing not for runtime
    void convert_ieee_float_to_int8_scale(const float* input, int8_t* out_int8, float* scale_out, int size)
    {
        const float* pIn = input;
        int8_t* pOut = out_int8;


        //find maximum abs val
        AScalar min = AScalar::MinAFloat();
        float max_abs_val = min.to_float();
        for (int ii = 0; ii < size; ii++)
        {
            float absval = fabsf(input[ii]);
            if (absval > max_abs_val)
                max_abs_val = absval;
        }
        AScalar scale = AScalar(max_abs_val).inverse();
        AScalar fac = CONST_ASCALAR(128.0);
        vr128 VR_scale;
        replicate_ar(VR_scale, 0xf, (scale * fac).fr);
        for (int ii = 0; ii < size;ii++)
        {
            vr128 VR_flt, VR_rndq7;
            load32x1_vr_postI(VR_flt, pIn, INC1, VRQ0);
            convert_IEEE_float_to_32F_x4(VR_flt);
            vr128 VR_out = vmuls(VR_flt, VR_scale, 0);
            convert_32F_to_16I_x4(VR_out, 7, 1);

            rnd_sat_pack(VR_rndq7, VRQ0, VR_out, 1);
            VR_out = shift32_arith(VR_rndq7, 24, 0);
            store8x1_vr_postI(VR_out, pOut, INC1, VRQ0);
        }
        if (scale_out)
            *scale_out = (CONST_ASCALAR(1.) / fac / scale).to_float();
    }
    int32_t MVMInt8ExpFloat32(const float* pInAfl, uint32_t inputLen)
    {

        float* pIn = (float*)pInAfl;
        int32_t exp_fxp = 0;
        int32_t exp_x;
        mir30 dummy;
        //uint32_t maxIdx;
        vr128 VR_exp;
        vr128 VR_max = vseta_vr(kConstTable_Zero, 0, 0);
        vr128 VR_x;
        uint32_t maxIdx;
        ulsr128 UR_In;
        // Initialization
        uint32_t nBlocks4 = inputLen >> 2;


        vmaxmin_init(VR_max, VR_max, dummy);

        // Find maximum exponent
        UR_In = align_32x4_load(pIn);
        load_32x4_vr_a(VR_x, UR_In, pIn);
        for (uint32_t i = 0; i < (nBlocks4); i++)
        {
            convert_IEEE_float_to_32F_x4(VR_x);
            VR_exp = afloat_exp_extract(VR_x);
            VR_max = vmax(VR_max, VR_exp);
            load_32x4_vr_a(VR_x, UR_In, pIn);
        }
        rmax_idx(maxIdx, VR_max, VRQ0, VR_max, dummy);

        //uint32_t i = (uint32_t)maxIdx; // This line is not required, just a temporary fix for linux build error

        if (inputLen & 3)
        {
            pIn -= 4;

            for (uint32_t i = (nBlocks4 << 2); i < inputLen; i++)
            {
                load32x1_vr_postI(VR_x, pIn, INC1, VRQ0);
                convert_IEEE_float_to_32F_x4(VR_x);
                VR_exp = afloat_exp_extract(VR_x);
                fmax(VR_max, VRQ0, VR_max, VRQ0, VR_exp, VRQ0);
            }

        }
        exp_x = move32_ar_vr(VR_max, VRQ0);
        if (exp_x == 0) //prevent vector all zero return exp = -31 
            exp_x = 0;
        else
            exp_x -= 31;

        exp_fxp = exp_x;
        return exp_fxp;
    }

    static void MVM_ConvertInput8(int32_t* in8b,
        const float* pInAfl,
        int32_t exp_fxp,
        uint32_t inputLen)
    {
        float* pIn = (float *)pInAfl;

        vr128 VR_x;
        vr128 VR_z = vseta_vr(0, 0, 0);
        ulsr128 UR_In;
        ulsr128 UR_Out;

        int32_t* pOutLocal = in8b;
        // Initialization
        uint32_t nBlocks4 = inputLen >> 2;
        uint32_t nBlocks16;

        // Perform conversion
        nBlocks16 = nBlocks4 >> 2;

        if (nBlocks16 > 0)
        {
            UR_In = align_32x4_load(pIn);
            UR_Out = align_32x4_store(pOutLocal);

            load_32x4_vr_a(VR_x, UR_In, pIn);
            convert_IEEE_float_to_32F_x4(VR_x);
            for (uint32_t i = 0; i < nBlocks16; i++)
            {
                convert_32F_to_16I_x4(VR_x, exp_fxp, 0);
                rnd_sat_pack(VR_z, VRQ0, VR_x, 1);
                load_32x4_vr_a(VR_x, UR_In, pIn);
                convert_IEEE_float_to_32F_x4(VR_x);
                convert_32F_to_16I_x4(VR_x, exp_fxp, 0);
                rnd_sat_pack(VR_z, VRQ1, VR_x, 1);
                load_32x4_vr_a(VR_x, UR_In, pIn);

                convert_IEEE_float_to_32F_x4(VR_x);
                convert_32F_to_16I_x4(VR_x, exp_fxp, 0);
                rnd_sat_pack(VR_z, VRQ2, VR_x, 1);
                
                load_32x4_vr_a(VR_x, UR_In, pIn);
                convert_IEEE_float_to_32F_x4(VR_x);

                convert_32F_to_16I_x4(VR_x, exp_fxp, 0);
                rnd_sat_pack(VR_z, VRQ3, VR_x, 1);
                load_32x4_vr_a(VR_x, UR_In, pIn);
                convert_IEEE_float_to_32F_x4(VR_x);
                store_32x4_vr_a(VR_z, UR_Out, pOutLocal);
            }
            flush_32x4(UR_Out, pOutLocal);
        }
        for (uint32_t i = (nBlocks16 << 2); i < (nBlocks4); i++)
        {
            convert_32F_to_16I_x4(VR_x, exp_fxp, 0);
            rnd_sat_pack(VR_z, VRQ0, VR_x, 1);
            load_32x4_vr_a(VR_x, UR_In, pIn);
            store32x1_vr_postI(VR_z, pOutLocal, INC1, VRQ0);
        }

        if (inputLen & 3)
        {
            pIn -= 4;
            load32x1_vr_postI(VR_x, pIn, INC1, VRQ3);

            convert_IEEE_float_to_32F_x4(VR_x);
            for (uint32_t i = ((inputLen >> 2) << 2); i < inputLen; i++)
            {
                convert_32F_to_16I_x1(VR_x, exp_fxp, 0, VRQ3); //MSB: use VRQ3
                rnd_sat_pack(VR_z, VRQ0, VR_x, 1);
                load32x1_vr_postI(VR_x, pIn, INC1, VRQ3);

                convert_IEEE_float_to_32F_x4(VR_x);
                store8x1_vr_postI(VR_z, pOutLocal, INC1, VRQ0);
            }
        }
    }

#ifdef MVM_FLOATxINT16
    // convert IEEE float to HI-LO for MVM
    static void MVM_ConvertInput16Interleaved(int32_t* in16b,
        const float* pInAfl,
        int32_t exp_fxp,
        uint32_t inputLen)
    {
        float* pIn = (float*)pInAfl;

        vr128 VR_x;
        vr128 VR_z = vseta_vr(0, 0, 0);
        vr128 VR_zLo;
        ulsr128 UR_In;
        ulsr128 UR_OutHi, UR_OutLo;
        uint32_t nBlocks4 = (inputLen+3) >> 2;

        uint8_t* pOutLo = (uint8_t*)in16b;
        uint8_t* pOutHi = (uint8_t*)in16b + (nBlocks4<<2);
        // Initialization
        
        

        if (nBlocks4 > 0)
        {
            UR_In = align_32x4_load(pIn);
            UR_OutHi = align_8x4_store(pOutHi);
            UR_OutLo = align_8x4_store(pOutLo);

            load_32x4_vr_a(VR_x, UR_In, pIn);
            convert_IEEE_float_to_32F_x4(VR_x);
            for (uint32_t i = 0; i < nBlocks4-1; i++)
            {
                VR_z = vexp_adji(VR_x, 0);
                convert_32F_to_16I_x4(VR_z, exp_fxp, 0);
               
                load_32x4_vr_a(VR_x, UR_In, pIn);
                convert_IEEE_float_to_32F_x4(VR_x);
                 VR_zLo = shift32_arith(VR_z, 8, 0);
                store_8x4_vr_a(VR_z, UR_OutHi, pOutHi);
                store_8x4_vr_a(VR_zLo, UR_OutLo, pOutLo);
            }
            VR_z = vexp_adji(VR_x, 0);
            convert_32F_to_16I_x4(VR_z, exp_fxp, 0);
            VR_zLo = shift32_arith(VR_z, 8, 0);
            store_8x4_vr_a(VR_z, UR_OutHi, pOutHi);
            store_8x4_vr_a(VR_zLo, UR_OutLo, pOutLo);
            flush_8x4(UR_OutHi, pOutHi);
            flush_8x4(UR_OutLo, pOutLo);
        }

        if (inputLen & 3)
        {
            for (uint32_t i =0; i < (inputLen & 3); i++)
            {
                load32x1_vr_postI(VR_x, pIn, INC1, VRQ0);
                convert_IEEE_float_to_32F_x4(VR_x);

                convert_32F_to_16I_x1(VR_x, exp_fxp, 0, VRQ0); //MSB: use VRQ3
                
                VR_zLo = shift32_arith(VR_x, 8, 0);
                store8x1_vr_postI(VR_x,  pOutHi, INC1, VRQ0);
                store8x1_vr_postI(VR_zLo,  pOutLo, INC1, VRQ0);
            }
        }
    }
#endif
    // enable act_min/max for acivation fused
    int MVMFloatInt8Kernel(float* y, const float* x, const int32_t* A, const float* bias,
        int m, int n, int32_t* x_in_tmp, const AScalar& act_min,
        const AScalar& act_max, const AScalar& scale, AScalar* scale_ptr ) {
        float* pY = y;

        const int32_t* pA = A;
        const int32_t* pX;
        const int32_t* pB = (const int32_t*)bias;
        int exp_fxp = 15+7;  // 31-(14+2), 31-
        // const int bias_exp = 17;
        // const int output_offset_exp = 17;
        int nBlockAligned2 = ((n + 1) >> 1);
        int loopLimCol = (nBlockAligned2 >> 3);  // block 16
        int loopLimRow = ((m + 7) >> 3);         // group 8 alignment
        int processLastLoop = ((m & 7) != 0);
        if (((unsigned int)x_in_tmp & 3) != 0 && loopLimCol != 0)
        {
            loopLimCol = 0;
        }

        if (((unsigned int)x_in_tmp & 1) != 0)
        {
            return -1;
        }
        vr128 VR_A;
        vr128 VR_x;
        vr128 VR_y;
        vr128 VR_act_max, VR_act_min;

        xtbool2 signSpec = int_to_xt_bool2(3);

        replicate_ar(VR_act_max, 0xf, act_max.fr);
        replicate_ar(VR_act_min, 0xf, act_min.fr);

        vr128 VR_wScale;
        AScalar* pScale = scale_ptr;
        vr128 VR_b0 = vseta_vr(kConstTable_Zero, 0, 0);
        ulsr128 UR_out = align_32x4_store(pY);

        int inExp = MVMInt8ExpFloat32(x, n);
        KN_PRINTD(inExp); KN_PRINTAFLT(scale);
        exp_fxp += inExp;
        MVM_ConvertInput8(x_in_tmp, x, inExp, n);

        replicate_ar(VR_wScale, 0xf, scale.fr);
        for (int i = 0; i < loopLimRow; i++) {
            VR_y = vseta_vr(0, 0, 0);
            mov_AccExtend_vr(VR_y);
            pX = x_in_tmp;
            ulsr128 UR_A = align_32x4_load(pA);
            ulsr128 UR_x = align_32x4_load(pX);
            ulsr128 UR_b;
            load_32x4_vr_a(VR_A, UR_A, pA);

            if (pB) {
                UR_b = align_32x4_load(pB);
                load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
            }

            for (int j = 0; j < loopLimCol; j++) {
                load_32x4_vr_a(VR_x, UR_x, pX);
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
                WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
                mac8bx8b(VR_y, VR_A, VR_x, signSpec);
                load_32x4_vr_a(VR_A, UR_A, pA);
            }

            if (i != (loopLimRow - 1) || !processLastLoop) {
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);


                vr128 VR_out;
                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);


                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                // VR_out = vexp_adji(VR_out, 8);
                convert_32F_to_IEEE_float_x4(VR_out);
                store_32x4_vr_a(VR_out, UR_out, pY);
                if (pB) {
                    load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
                }

                VR_y = mov_vr_AccExtend();

                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);


                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);
                // VR_out = vexp_adji(VR_out, 8);

                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                convert_32F_to_IEEE_float_x4(VR_out);

                store_32x4_vr_a(VR_out, UR_out, pY);
                flush_32x4(UR_out, pY);
            }
            else {
                // Convert and store outputs
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);


                vr128 VR_out;

                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);
                // VR_out = vexp_adji(VR_out, 8);

                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                convert_32F_to_IEEE_float_x4(VR_out);
                for (int32_t j = 0; j < (m & 0x7) && j < 4; j++) {
                    store32x1_vr_postI(VR_out, pY, INC1, VRQ0);
                    VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
                }

                if ((m & 7) <= 4) {
                    break;
                }
                VR_y = mov_vr_AccExtend();

                if (pB) {
                    load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
                }

                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ2);
                convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ3);

                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);
                
                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                convert_32F_to_IEEE_float_x4(VR_out);
                for (int32_t j = 4; j < (m & 0x7) && j < 8; j++) {
                    store32x1_vr_postI(VR_out, pY, INC1, VRQ0);
                    VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
                }
            }
            // Adjust pointer to compensate for loop priming
            pA -= 4;  // NOTE pointer type int8v4, => 16/4 = 4;
        }
        KN_PRINT_FLOAT(y, m);
        return 0;
    }
#ifdef MVM_FLOATxINT16
    // enable act_min/max for acivation fused
    int MVMFloatInt16Kernel(float* y, const float* x, const int32_t* A, const float* bias,
        int m, int n, int32_t* x_in_tmp, const AScalar& act_min,
        const AScalar& act_max, const AScalar& scale, AScalar* scale_ptr) {
        float* pY = y;

        const int32_t* pA = A;
        const int32_t* pX;
        const int32_t* pB = (const int32_t*)bias;
        int exp_fxp = 15 + 7;  // 31-(14+2), 31-
        // const int bias_exp = 17;
        // const int output_offset_exp = 17;
        int nBlockAligned2 = ((n + 1) >> 1);
        int nBlockAligned4 = ((n + 3) >> 2);
        int loopLimCol = (nBlockAligned2 >> 3);  // block 16
        int loopLimRow = ((m + 7) >> 3);         // group 8 alignment
        int processLastLoop = ((m & 7) != 0);

        if (((unsigned int)x_in_tmp & 3) != 0 && loopLimCol != 0)
        {
            loopLimCol = 0;
        }

        if (((unsigned int)x_in_tmp & 1) != 0)
        {
            return -1;
        }
        vr128 VR_A;
        vr128 VR_x;
        vr128 VR_y;
        vr128 VR_act_max, VR_act_min;


        xtbool2 signSpecLo = int_to_xt_bool2(1);
        xtbool2 signSpecHi = int_to_xt_bool2(3);

        replicate_ar(VR_act_max, 0xf, act_max.fr);
        replicate_ar(VR_act_min, 0xf, act_min.fr);

        vr128 VR_wScale;
        AScalar* pScale = scale_ptr;
        vr128 VR_b0 = vseta_vr(kConstTable_Zero, 0, 0);
        ulsr128 UR_out = align_32x4_store(pY);

        int inExp = MVMInt8ExpFloat32(x, n);
        KN_PRINTD(inExp); KN_PRINTAFLT(scale);
        exp_fxp += inExp;
        MVM_ConvertInput16Interleaved(x_in_tmp, x, inExp, n);
        int8_t* xLo = (int8_t*) x_in_tmp ;
        int8_t* xHi = (int8_t*)x_in_tmp + (nBlockAligned4 << 2);
        replicate_ar(VR_wScale, 0xf, scale.fr);
        for (int i = 0; i < loopLimRow; i++) {
            vr128 VR_LoAcc = vseta_vr(0, 0, 0);
            mov_AccExtend_vr(VR_LoAcc);
            pX = (int32_t *)xLo;
            ulsr128 UR_A = align_32x4_load(pA);
            ulsr128 UR_x = align_32x4_load(pX);
            ulsr128 UR_b;
            load_32x4_vr_a(VR_A, UR_A, pA);

            if (pB) {
                UR_b = align_32x4_load(pB);
                load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
            }
            // Lo -part MAC
            for (int j = 0; j < loopLimCol; j++) {
                load_32x4_vr_a(VR_x, UR_x, pX);
                WUR_MvmAux(0);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);
            }

            for (int32_t j = (loopLimCol << 3); j < nBlockAligned2; j++) {
                load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
                WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
                mac8bx8b(VR_LoAcc, VR_A, VR_x, signSpecLo);
                load_32x4_vr_a(VR_A, UR_A, pA);
            }


            convert_32I_to_32F_x1(VR_LoAcc, 16 + LO_SHIFT, VRQ0);
            convert_32I_to_32F_x1(VR_LoAcc, 16 + LO_SHIFT, VRQ1);
            convert_32I_to_32F_x1(VR_LoAcc, 16 + LO_SHIFT, VRQ2);
            convert_32I_to_32F_x1(VR_LoAcc, 16 + LO_SHIFT, VRQ3);

            vr128 VR_LoAccExtend = mov_vr_AccExtend();

            convert_32I_to_32F_x1(VR_LoAccExtend, 16 + LO_SHIFT, VRQ0);
            convert_32I_to_32F_x1(VR_LoAccExtend, 16 + LO_SHIFT, VRQ1);
            convert_32I_to_32F_x1(VR_LoAccExtend, 16 + LO_SHIFT, VRQ2);
            convert_32I_to_32F_x1(VR_LoAccExtend, 16 + LO_SHIFT, VRQ3);

            vr128 VR_HiAcc = vseta_vr(0, 0, 0);
            mov_AccExtend_vr(VR_HiAcc);
            // Hi
            pX = (int32_t*)xHi;
            pA = A;

            UR_A = align_32x4_load(pA);
            UR_x = align_32x4_load(pX);


            load_32x4_vr_a(VR_A, UR_A, pA);
            for (int j = 0; j < loopLimCol; j++) {
                load_32x4_vr_a(VR_x, UR_x, pX);
                WUR_MvmAux(0);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);

                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);
            }

            for (int32_t j = (loopLimCol << 3); j < nBlockAligned2; j++) {
                load16x1_vr_postI(VR_x, pX, INC1, VRQ0);
                WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
                mac8bx8b(VR_HiAcc, VR_A, VR_x, signSpecHi);
                load_32x4_vr_a(VR_A, UR_A, pA);
            }
            convert_32I_to_32F_x1(VR_HiAcc, 16 + HI_SHIFT, VRQ0);
            convert_32I_to_32F_x1(VR_HiAcc, 16 + HI_SHIFT, VRQ1);
            convert_32I_to_32F_x1(VR_HiAcc, 16 + HI_SHIFT, VRQ2);
            convert_32I_to_32F_x1(VR_HiAcc, 16 + HI_SHIFT, VRQ3);

            if (i != (loopLimRow - 1) || !processLastLoop) {
                VR_y = vadds(VR_LoAcc, VR_HiAcc, 0);


                vr128 VR_out;
                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);


                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                // VR_out = vexp_adji(VR_out, 8);
                convert_32F_to_IEEE_float_x4(VR_out);
                store_32x4_vr_a(VR_out, UR_out, pY);
                if (pB) {
                    load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
                }
                vr128 VR_HiAccExtend = mov_vr_AccExtend();

                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ0);
                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ1);
                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ2);
                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ3);
                VR_y = vadds(VR_LoAccExtend, VR_HiAccExtend, 0);


                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);
                // VR_out = vexp_adji(VR_out, 8);

                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                convert_32F_to_IEEE_float_x4(VR_out);

                store_32x4_vr_a(VR_out, UR_out, pY);
                flush_32x4(UR_out, pY);
            }
            else {
                // Convert and store outputs
                VR_y = vadds(VR_LoAcc, VR_HiAcc, 0);


                vr128 VR_out;

                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);
                // VR_out = vexp_adji(VR_out, 8);

                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                convert_32F_to_IEEE_float_x4(VR_out);
                for (int32_t j = 0; j < (m & 0x7) && j < 4; j++) {
                    store32x1_vr_postI(VR_out, pY, INC1, VRQ0);
                    VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
                }

                if ((m & 7) <= 4) {
                    break;
                }
                VR_y = mov_vr_AccExtend();

                if (pB) {
                    load_32x4_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
                }

                vr128 VR_HiAccExtend = mov_vr_AccExtend();

                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ0);
                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ1);
                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ2);
                convert_32I_to_32F_x1(VR_HiAccExtend, 16 + HI_SHIFT, VRQ3);
                VR_y = vadds(VR_LoAccExtend, VR_HiAccExtend, 0);

                if (scale_ptr)
                    load32x4_vr_postI(VR_wScale, pScale, INC1);
                VR_y = vmuls(VR_y, VR_wScale, 0);
                VR_out = vadds(VR_y, VR_b0, 0x0);

                VR_out = vmax(VR_out, VR_act_min);
                VR_out = vmin(VR_out, VR_act_max);

                convert_32F_to_IEEE_float_x4(VR_out);
                for (int32_t j = 4; j < (m & 0x7) && j < 8; j++) {
                    store32x1_vr_postI(VR_out, pY, INC1, VRQ0);
                    VR_out = vpermsi(VR_out, VR_out, 0, SHR_BY_1_ELEM);
                }
            }
            // Adjust pointer to compensate for loop priming
            pA -= 4;  // NOTE pointer type int8v4, => 16/4 = 4;
        }
        KN_PRINT_FLOAT(y, m);
        return 0;
    }
#endif //#ifdef MVM_FLOATxINT16
#endif
#if defined(HMD1A)
    // convert to input 8 with exp and 
int32_t MVMInt8ExpFloat32(const float* pInAfl, uint32_t inputLen)
{

    float* pIn = (float*) pInAfl;
    int32_t exp_fxp = 0;
    int32_t exp_x;
    mir18 dummy;
    uint32_t maxIdx;
    vr64 VR_exp;
    vr64 VR_max = vseta_vr(kConstTable_Zero, 0);
    vr64 VR_x;
    fr32 fr_max;
    ulsr32 UR_In;
    // Initialization
    uint32_t nBlocks2 = inputLen >> 1;


    vmaxmin_init(VR_max, VR_max, dummy);

    // Find maximum exponent
    UR_In = align_32x2_load(pIn);
    load_32x2_vr_a(VR_x, UR_In, pIn);
    for (uint32_t i = 0; i < (nBlocks2); i++)
    {
        convert_IEEE_float_to_32F_x2(VR_x);
        VR_exp = afloat_exp_extract(VR_x);
        VR_max = vmax(VR_max, VR_exp);
        load_32x2_vr_a(VR_x, UR_In, pIn);
    }

    if (inputLen & 1)
    {
        pIn -= 2;

        load32x1_vr_postI(VR_x, pIn, INC1, VRL);
        convert_IEEE_float_to_32F_x2(VR_x);
        VR_exp = afloat_exp_extract(VR_x);

        fmax(VR_max, VRL, VR_max, VRL, VR_exp, VRL);

    }
    rmax_idx(maxIdx, fr_max, VR_max, dummy);


    exp_x = (int32_t)maxIdx; // This line is not required, just a temporary fix for linux build error

#ifdef __XTENSA__
    exp_x = fr_max;
#else
    exp_x = fr_max._[0];
#endif
    if (exp_x == 0) //prevent vector all zero return exp = -31 
        exp_x = 0;
    else
        exp_x -= 31;

    exp_fxp = exp_x;

    return exp_fxp;
}
static void MVM_ConvertInput8(int32_t* in8b,
    const float* pInAfl,
    int32_t exp_fxp,
    uint32_t inputLen)
{
    float* pIn = (float *)pInAfl;

    vr64 VR_x;
    vr64 VR_y;
    vr64 VR_z = vseta_vr(0, 0);
    ulsr32 UR_In;
    ulsr32 UR_Out;

    // Initialization
    int32_t nBlocks2 = inputLen >> 1;
    int32_t nBlocks8;
    int32_t* pOutLocal = in8b;
    // Perform conversion
    nBlocks8 = nBlocks2 >> 2;

    UR_In = align_32x2_load(pIn);
    UR_Out = align_32x2_store(pOutLocal);

    load_32x2_vr_a(VR_x, UR_In, pIn);
    convert_IEEE_float_to_32F_x2(VR_x);
    if (nBlocks8 > 0)
    {
        for (int32_t i = 0; i < nBlocks8; i++)
        {

            convert_32F_to_16I_x2(VR_x, exp_fxp, 0);

            load_32x2_vr_a(VR_y, UR_In, pIn);
            convert_IEEE_float_to_32F_x2(VR_y);
            convert_32F_to_16I_x2(VR_y, exp_fxp, 0);
            rnd_sat_pack(VR_z, VRL, VR_x, VR_y, 1);

            load_32x2_vr_a(VR_x, UR_In, pIn);
            convert_IEEE_float_to_32F_x2(VR_x);
            convert_32F_to_16I_x2(VR_x, exp_fxp, 0);

            load_32x2_vr_a(VR_y, UR_In, pIn);
            convert_IEEE_float_to_32F_x2(VR_y);
            convert_32F_to_16I_x2(VR_y, exp_fxp, 0);
            rnd_sat_pack(VR_z, VRQ1, VR_x, VR_y, 1);
            load_32x2_vr_a(VR_x, UR_In, pIn);
            convert_IEEE_float_to_32F_x2(VR_x);
            store_32x2_vr_a(VR_z, UR_Out, pOutLocal);
        }
        flush_32x2(UR_Out, pOutLocal);
    }
    for (int32_t i = (nBlocks8 << 2); i < (nBlocks2); i++)
    {
        convert_32F_to_16I_x2(VR_x, exp_fxp, 0);
        rnd_sat_pack(VR_z, VRL, VR_x, VR_x, 1);
        load_32x2_vr_a(VR_x, UR_In, pIn);

        store16x1_vr_postI(VR_z, pOutLocal, INC1, VRL);
    }

    if (inputLen & 1)
    {
        pIn -= 2;
        load32x1_vr_postI(VR_x, pIn, INC1, VRH);// store 8 bit in MSB
        convert_IEEE_float_to_32F_x2(VR_x);
        convert_32F_to_16I_x1(VR_x, exp_fxp, 0, VRH);
        rnd_sat_pack(VR_z, VRL, VR_x, VR_x, 1);
        store8x1_vr_postI(VR_z, pOutLocal, INC1, VRL);

    }
}

int  MVMFloatInt8Kernel(float* y, const float* x, const int32_t* A, const float* bias,
    int m, int n, int32_t* x_in_tmp, const AScalar& act_min,
    const AScalar& act_max, const AScalar& scale, AScalar* scale_ptr) 
{

    float* pY = y;

    const int32_t* pA = A;
    const int32_t* pX;
    const int32_t* pB = (const int32_t*)bias;
    int exp_fxp =  15+7; 
    // const int bias_exp = 17;
    // const int output_offset_exp = 17;
    int nBlockAligned2 = ((n + 1) >> 1);
    int loopLimCol = (nBlockAligned2 >> 2);  // block 16
    int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
    int processLastLoop = ((m & 3) != 0);
    if (((unsigned int)x_in_tmp & 3) != 0 && loopLimCol != 0)
    {
        loopLimCol = 0;
    }

    if (((unsigned int)x_in_tmp & 1) != 0)
    {
        return -1;
    }
    vr64 VR_A;
    vr64 VR_x;
    vr64 VR_y;
    vr64 VR_act_max, VR_act_min;
    atbool signSpec = atbool(3);
    replicate_ar(VR_act_max, 0x3, act_max.fr);
    replicate_ar(VR_act_min, 0x3, act_min.fr);
    vr64 VR_wScale;
    //vr64 VR_outOffset;
    AScalar* pScale = scale_ptr;
    ulsr32 UR_scale;
    if (pScale)
    {
        UR_scale = align_32x2_load(pScale);
    }
    vr64 VR_b0 = vseta_vr(kConstTable_Zero, 0);
    //replicate_ar(VR_outMult, 0x3, outMultiplerFr32.fr);
    int inExp=MVMInt8ExpFloat32(x, n);

    KN_PRINTD(inExp); KN_PRINTAFLT(scale);
    exp_fxp += inExp;
    MVM_ConvertInput8(x_in_tmp, x, inExp, n);
    //replicate_ar(VR_inScale, 0x3, scale.fr);
    replicate_ar(VR_wScale, 0x3, scale.fr);
    for (int i = 0; i < loopLimRow; i++) {
        VR_y = vseta_vr(0, 0);
        mov_AccExtend_vr(VR_y);
        pX = x_in_tmp;
        ulsr32 UR_A = align_32x2_load(pA);
        ulsr32 UR_x = align_32x2_load(pX);
        ulsr32 UR_y = align_32x2_store(pY);
        ulsr32 UR_b;
        load_32x2_vr_a(VR_A, UR_A, pA);

        if (pB) {
            UR_b = align_32x2_load(pB);
            load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
        }

        for (int j = 0; j < loopLimCol; j++) {
            load_32x2_vr_a(VR_x, UR_x, pX);
            //VR_x = vbool(VR_x, VR_inputOffset, 0x6);
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
            //VR_x = vbool(VR_x, VR_inputOffset, 0x6);
            WUR_MvmAux(1);  // select low part, due to load16x1 load in high of 32bit
            mac8bx8b(VR_y, VR_A, VR_x, signSpec);
            load_32x2_vr_a(VR_A, UR_A, pA);
        }

        if (i != (loopLimRow - 1) || !processLastLoop) {
            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

            vr64 VR_out;

            if (scale_ptr) {
                load_32x2_vr_a(VR_wScale, UR_scale, pScale); //, INC1);
            }
            VR_y = vmuls(VR_y, VR_wScale, 0);

            VR_out = vadds(VR_y, VR_b0, 0x0);
            VR_out = vmax(VR_out, VR_act_min);
            VR_out = vmin(VR_out, VR_act_max);
            // VR_out = vexp_adji(VR_out, 8);
            convert_32F_to_IEEE_float_x2(VR_out);//, (unsigned int)1 - 8, 0);
            store_32x2_vr_a(VR_out, UR_y, pY);
            if (pB) {
                load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
            }
            VR_y = mov_vr_AccExtend();

            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
            if (scale_ptr) {
                load_32x2_vr_a(VR_wScale, UR_scale, pScale);//, INC1);
            }
            VR_y = vmuls(VR_y, VR_wScale, 0);
            VR_out = vadds(VR_y, VR_b0, 0x0);

            VR_out = vmax(VR_out, VR_act_min);
            VR_out = vmin(VR_out, VR_act_max);

            convert_32F_to_IEEE_float_x2(VR_out); //, (unsigned int)1 - 8, 0);


            store_32x2_vr_a(VR_out, UR_y, pY);//, INC1);
            flush_32x2(UR_y, pY);
            // store32x1_vr_postI(VR_q7_out, pY, INC1, VRQ1);
        }
        else {
            // Convert and store outputs
            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);

            //vr64 VR_q7_out;
            if (scale_ptr) {
                load_32x2_vr_a(VR_wScale, UR_scale, pScale);
            }
            vr64 VR_out;

            VR_y = vmuls(VR_y, VR_wScale, 0);

            VR_out = vadds(VR_y, VR_b0, 0x0);
            VR_out = vmax(VR_out, VR_act_min);
            VR_out = vmin(VR_out, VR_act_max);
            convert_32F_to_IEEE_float_x2(VR_out);

            VR_y = mov_vr_AccExtend();

            if (pB) {
                load_32x2_vr_a(VR_b0, UR_b, pB);  // suppose not grate than 16 bit
            }

            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ0);
            convert_32I_to_32F_x1(VR_y, exp_fxp, VRQ1);
            if (scale_ptr) {
                load_32x2_vr_a(VR_wScale, UR_scale, pScale);
            }
            vr64 VR_out2 = vadds(VR_y, VR_b0, 0x0);
            VR_out2 = vmuls(VR_out2, VR_wScale, 0);
            VR_out2 = vadds(VR_out2, VR_b0, 0);

            VR_out2 = vmax(VR_out2, VR_act_min);
            VR_out2 = vmin(VR_out2, VR_act_max);

            convert_32F_to_IEEE_float_x2(VR_out2);
            switch (m & 0x3) {
            case 3:
                store32x1_vr_postI(VR_out, pY, INC1, VRQ0);
                store32x1_vr_postI(VR_out, pY, INC1, VRQ1);
                store32x1_vr_postI(VR_out2, pY, INC1, VRQ0);
                break;
            case 2:
                store32x1_vr_postI(VR_out, pY, INC1, VRQ0);
                store32x1_vr_postI(VR_out, pY, INC1, VRQ1);
                break;
            case 1:
                store32x1_vr_postI(VR_out, pY, INC1, VRQ0);
                break;
            }
        }
        // Adjust pointer to compensate for loop priming
        pA -= 2;  // NOTE pointer type int8v4, => 16/4 = 4;
    }

    KN_PRINT_FLOAT(y, m);
    return 0;
}

//helper function for testing not for runtime
void convert_ieee_float_to_int8_scale(const float* input, int8_t* out_int8, float* scale_out, int size)
{
    const float* pIn = input;
    int8_t* pOut = out_int8;


    //find maximum abs val
    AScalar min = AScalar::MinAFloat();
    float max_abs_val = min.to_float();
    for (int ii = 0; ii < size; ii++)
    {
        float absval = fabsf(input[ii]);
        if (absval > max_abs_val)
            max_abs_val = absval;
    }
    AScalar scale = AScalar(max_abs_val).inverse();
    AScalar fac = CONST_ASCALAR(128.0);
    vr64 VR_scale;
    replicate_ar(VR_scale, 0x3, (scale * fac).fr);
    for (int ii = 0; ii < size;ii++)
    {
        vr64 VR_flt, VR_rndq7;
        load32x1_vr_postI(VR_flt, pIn, INC1, VRQ0);
        convert_IEEE_float_to_32F_x2(VR_flt);
        vr64 VR_out = vmuls(VR_flt, VR_scale, 0);
        convert_32F_to_16I_x2(VR_out, 7, 1);

        rnd_sat_pack(VR_rndq7, VRQ0, VR_out, VR_out, 1);
        VR_out = shift32_arith(VR_rndq7, 24, 0);
        store8x1_vr_postI(VR_out, pOut, INC1, VRQ0);
    }
    if (scale_out)
        *scale_out = (CONST_ASCALAR(1.) / fac / scale).to_float();
}
void MVMInputOffsetPrepare(const int32_t *A, int32_t *output, int m, int n,
                           uint32_t input_offset) {
  // int32_t *pY = output;

  const int32_t *pA = A;
  int nBlockAligned2 = ((n + 1) >> 1);
  int loopLimCol = (nBlockAligned2 >> 2);  // block 16
  int loopLimRow = ((m + 3) >> 2);         // group 8 alignment
                                    // int processLastLoop = ((m & 3) != 0);

  int32_t *pOutput = output;
  vr64 VR_A;

  vr64 VR_y;
  atbool signSpecInput = atbool(3);

  vr64 VR_inputOffset;
  replicate_ar(
      VR_inputOffset, 0x3,
      input_offset);  // -1 ~ -127
                      // replicate_ar(VR_outOffset, 0xf, outOffsetFr32.fr);

  for (int i = 0; i < loopLimRow; i++) {
    // const int32_t *pA1 = pA;
    VR_y = vseta_vr(0, 0);
    mov_AccExtend_vr(VR_y);

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

void block_copy_bytes(int8_t* pDes, const int8_t* pSrc,
    int32_t nBytes) {
    int32_t ii, loopLim;
    const uint32_t* uint_Src;
    uint32_t* uint_Des;
    uint_Src = (const uint32_t*)pSrc;
    uint_Des = (uint32_t*)pDes;

    vr64 VR_S0;
    ulsr32 UR_des;
    ulsr32 UR_src;
    if ((((uint32_t)pDes & 0x3) == 0) && ((uint32_t)pSrc & 0x3) == 0) {
        uint_Src = (const uint32_t*)pSrc;
        uint_Des = (uint32_t*)pDes;
        // IMPORTANT: NOTE
        // unalignment need to alignment 32x4 NEEDS: 4 byte alignment
        UR_src = align_32x2_load(uint_Src);
        UR_des = align_32x2_store(uint_Des);

        // 8 byte copy
        loopLim = nBytes >> 3;
        if (loopLim > 0) {
            load_32x2_vr_a(VR_S0, UR_src, uint_Src);
            for (ii = 0; ii < (loopLim - 1); ii++) {
                store_32x2_vr_a(VR_S0, UR_des, uint_Des);
                load_32x2_vr_a(VR_S0, UR_src, uint_Src);
            }
            store_32x2_vr_a(VR_S0, UR_des, uint_Des);
            flush_32x2(UR_des, uint_Des);
        }
        for (int32_t i = loopLim << 3; i < nBytes; i++) {
            load8x1_vr_postI(VR_S0, uint_Src, INC1, VRQ0);
            store8x1_vr_postI(VR_S0, uint_Des, INC1, VRQ0);
        }
    }

    else {
        // byte copy

        for (ii = 0; ii < (nBytes); ii++) {
            load8x1_vr_postI(VR_S0, uint_Src, INC1, VRQ0);
            store8x1_vr_postI(VR_S0, uint_Des, INC1, VRQ0);
        }
    }
}

void ConvertQ15ToAfloat(const int16_t *input, AScalar *output, int size,
                        int32_t bexp) {
  int size2 = size >> 1;
  const int16_t *pInput = input;
  AScalar *pOutput = output;

#ifdef KN_DEBUG
  CHECK_ALIGN_4(pInput);
#endif
  if (size2 > 0) {
    vr64 vr_data;
    // ulsr32 ur_in = align_16x2_load(pInput);
    ulsr32 ur_out = align_32x2_store(pOutput);
    load16x2_vr_postI(vr_data, pInput, INC1);
    for (int ii = 0; ii < size2 - 1; ii++) {
      convert_16I_to_32F_x2(vr_data, bexp);
      store_32x2_vr_a(vr_data, ur_out, pOutput);
      load16x2_vr_postI(vr_data, pInput, INC1);
    }
    convert_16I_to_32F_x2(vr_data, bexp);
    store_32x2_vr_a(vr_data, ur_out, pOutput);
    flush_32x2(ur_out, pOutput);
  }

  {
    // for(int ii =0; ii < (size&3); ii++)
    if (1 & size) {
      vr64 vr_data;
      load16x1_vr_postI(vr_data, pInput, INC1, VRQ0);
      convert_16I_to_32F_x1(vr_data, bexp, VRQ0);
      store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
    }
  }
}

void ConvertQ31ToAfloat(const int32_t *input, AScalar *output, int size,
                        int32_t bexp) {
  int size2 = size >> 1;
  const int32_t *pInput = input;
  AScalar *pOutput = output;
  if (size2 > 0) {
    vr64 vr_data;
    ulsr32 ur_in = align_32x2_load(pInput);
    ulsr32 ur_out = align_32x2_store(pOutput);
    load_32x2_vr_a(vr_data, ur_in, pInput);
    for (int ii = 0; ii < size2 - 1; ii++) {
      convert_32I_to_32F_x1(vr_data, bexp, VRQ0);
      convert_32I_to_32F_x1(vr_data, bexp, VRQ1);
      store_32x2_vr_a(vr_data, ur_out, pOutput);
      load_32x2_vr_a(vr_data, ur_in, pInput);
    }
    convert_32I_to_32F_x1(vr_data, bexp, VRQ0);
    convert_32I_to_32F_x1(vr_data, bexp, VRQ1);

    store_32x2_vr_a(vr_data, ur_out, pOutput);
    flush_32x2(ur_out, pOutput);
  }
  {
    if (1 & size) {
      vr64 vr_data;
      load32x1_vr_postI(vr_data, pInput, INC1, VRQ0);
      convert_32I_to_32F_x1(vr_data, bexp, VRQ0);
      store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
    }
  }
}
void ConvertIEEEFloatToAfloat(const float* input, AScalar* output, int size) {
    int size2= size >> 1;
    const float* pInput = input;
    AScalar* pOutput = output;
    if (size2 > 0) {
        vr64 vr_data;
        ulsr32 ur_in = align_32x2_load(pInput);
        ulsr32 ur_out = align_32x2_store(pOutput);
        load_32x2_vr_a(vr_data, ur_in, pInput);
        for (int ii = 0; ii < size2 - 1; ii++) {
            convert_IEEE_float_to_32F_x2(vr_data);

            store_32x2_vr_a(vr_data, ur_out, pOutput);
            load_32x2_vr_a(vr_data, ur_in, pInput);
        }
        convert_IEEE_float_to_32F_x2(vr_data);
        store_32x2_vr_a(vr_data, ur_out, pOutput);
        flush_32x2(ur_out, pOutput);
    }

    
    if (size & 1) {
        vr64 vr_data;
        load32x1_vr_postI(vr_data, pInput, INC1, VRQ0);
        convert_IEEE_float_to_32F_x2(vr_data);
        store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
    }
    
}

void ConvertQ31ToAfloat(const int32_t *input, AScalar *output, int size,
                        int32_t *pShift, int32_t baseExp) {
  int size2 = size >> 1;
  const int32_t *pInput = input;
  AScalar *pOutput = output;
  // int32_t *pBexp = pShift;
  // VAR_ALIGN_8 int32_t bexp[4];

  if (size2 > 0) {
    int ii = 0;
    vr64 vr_data;  //, vr_bexp;
    ulsr32 ur_in = align_32x2_load(pInput);
    // ulsr32 ur_bexp = align_32x2_load(pBexp);
    ulsr32 ur_out = align_32x2_store(pOutput);
    load_32x2_vr_a(vr_data, ur_in, pInput);
    // load_32x2_vr_a(vr_bexp,ur_bexp, pBexp);
    // store32x2_vr_idxI(vr_bexp, bexp, IDX0);
    for (ii = 0; ii < size2 - 1; ii++) {
      convert_32I_to_32F_x1(vr_data, baseExp + pShift[ii * 2 + 0], VRQ0);
      convert_32I_to_32F_x1(vr_data, baseExp + pShift[ii * 2 + 1], VRQ1);
      //  convert_32I_to_32F_x1(vr_data,baseExp +bexp[2], VRQ2);
      // convert_32I_to_32F_x1(vr_data,baseExp +bexp[3], VRQ3);
      // load_32x2_vr_a(vr_bexp,ur_bexp, pBexp);
      // store32x2_vr_idxI(vr_bexp, bexp, IDX0);
      store_32x2_vr_a(vr_data, ur_out, pOutput);
      load_32x2_vr_a(vr_data, ur_in, pInput);
    }
    convert_32I_to_32F_x1(vr_data, baseExp + pShift[ii * 2 + 0], VRQ0);
    convert_32I_to_32F_x1(vr_data, baseExp + pShift[ii * 2 + 1], VRQ1);
    store_32x2_vr_a(vr_data, ur_out, pOutput);
    flush_32x2(ur_out, pOutput);
  }

  if (1 & size) {
    vr64 vr_data;
    load32x1_vr_postI(vr_data, pInput, INC1, VRQ0);
    convert_32I_to_32F_x1(vr_data, baseExp + pShift[size2 * 2 + 0], VRQ0);
    store32x1_vr_postI(vr_data, pOutput, INC1, VRQ0);
  }
}

// a+ const(integer) =c
// float 32 out
int AddConstQuantizedInt8(int8_t *input, int32_t const_offset, uint8_t *output,
                          int size) {
  int ii;  // convert to 1 to afloat and vadd return int32
  int s2 = size >> 1;

  int8_t *pA = input;
  uint8_t *pC = output;

  vr64 vr_b;

  // return error if const offset >= 128 || < -128
  int b16 = const_offset << 16;
  replicate_ar(vr_b, 0x3, b16);
  convert_16I_to_32F_x2(vr_b, 8);

#ifdef KN_DEBUG
  CHECK_ALIGN_2(pA);
  CHECK_ALIGN_2(pC);
#endif
  if (s2 > 0) {
    // ulsr32 ur_a = align_8x2_load(pA);
    // ulsr32 ur_c = align_8x4_store(pC);

    vr64 vr_a, vr_c;

    load8x2_vr_postI(vr_a, pA, INC1);
    for (ii = 0; ii < s2 - 1; ii++) {
      convert_16I_to_32F_x2(vr_a, 0);
      vr_c = vadds(vr_a, vr_b, 0);
      load8x2_vr_postI(vr_a, pA, INC1);
      convert_32F_to_16I_x2(vr_c, 1, 0);
      vr_c = shift32_arith(vr_c, 1, 0);
      store8x2_vr_postI(vr_c, pC, INC1);
    }
    convert_16I_to_32F_x2(vr_a, 0);
    vr_c = vadds(vr_a, vr_b, 0);
    convert_32F_to_16I_x2(vr_c, 1, 0);
    vr_c = shift32_arith(vr_c, 1, 0);
    store8x2_vr_postI(vr_c, pC, INC1);
  }
  if (size & 1) {
    vr64 vr_a, vr_c;
    {
      load8x1_vr_postI(vr_a, pA, INC1, VRQ0);
      convert_16I_to_32F_x1(vr_a, 0, VRQ0);
      vr_c = vadds(vr_a, vr_b, 0);
      convert_32F_to_16I_x2(vr_c, 1, 0);
      vr_c = shift32_arith(vr_c, 1, 0);
      store8x1_vr_postI(vr_c, pC, INC1, VRQ0);
    }
  }
  return 0;
}

int AddConstQuantizedInt8Fast128(int32_t *input, uint32_t *output, int size) {
  int ii;                     // convert to 1 to afloat and vadd return int32
  int s2 = (size >> 2) >> 1;  //

  int32_t *pA = input;
  uint32_t *pC = output;

  vr64 vr_b;

  // return error if const offset >= 128 || < -128
  // int b16 = 0x80 << 16;
  replicate_ar(vr_b, 0x3, 0x80808080);
#ifdef KN_DEBUG
  CHECK_ALIGN_4(input);
  CHECK_ALIGN_4(output);
#endif
  //    KN_PRINTX(input);
  // KN_PRINTX(output);
  // KN_PRINTD(s2);
  if (s2 > 0) {
    ulsr32 ur_a = align_32x2_load(pA);
    ulsr32 ur_c = align_32x2_store(pC);

    vr64 vr_a, vr_c;

    load_32x2_vr_a(vr_a, ur_a, pA);
    for (ii = 0; ii < s2 - 1; ii++) {
      vr_c = vbool(vr_a, vr_b, 0x6);  // s_vxor(vr_a, vr_b);
      load_32x2_vr_a(vr_a, ur_a, pA);
      store_32x2_vr_a(vr_c, ur_c, pC);
    }
    vr_c = vbool(vr_a, vr_b, 0x6);  // s_vxor(vr_a, vr_b);

    store_32x2_vr_a(vr_c, ur_c, pC);
    flush_32x2(ur_c, pC);
  }
  if (size & 7) {
    vr64 vr_a, vr_c;
    for (ii = 0; ii < (size & 7); ii++) {
      load8x1_vr_postI(vr_a, pA, INC1, VRQ0);
      vr_c = vbool(vr_a, vr_b, 0x6);  // s_vxor(vr_a, vr_b);
      store8x1_vr_postI(vr_c, pC, INC1, VRQ0);
    }
  }
  return 0;
}
//TODO: move some where
void convert_ieee_float_to_afloat16(const float* input, uint16_t* out_float16, int size)
{
    const float* pIn = input;
    uint16_t* pOut = out_float16;
    for (int ii = 0; ii < size;ii++)
    {
        vr64 VR_flt;
        load32x1_vr_postI(VR_flt, pIn, INC1, VRQ0);
        convert_IEEE_float_to_32F_x2(VR_flt);
        convert_32F_to_16F_x2(VR_flt, TF_FLT16_SIGN, TF_FLT16_EXP, TF_FLT16_BIAS, 1);
        store16x1_vr_postI(VR_flt, pOut, INC1, VRQ0);
    }
}

#endif
// optimize me
// input pCoeffs order is  filter_val = filter_data[out_c * accum_depth + d];
int FullyConnectedMap8bitCoeffs(int8_t *pMapped, int8_t *pCoeffs, int m,
                                int n) {
  int nFullRowGroups =
      (m + (1 << LOG2_ROWS_PER_GROUP) - 1) >> LOG2_ROWS_PER_GROUP;

  int nFullColBlocks = (n + 1) >> LOG2_COLS_PER_BLOCK;
  int nFullBlockColsAligned2 = nFullColBlocks << LOG2_COLS_PER_BLOCK;

  int8_t *src = pCoeffs;
  int8_t *dst = pMapped;

  int mappedSize = nFullRowGroups * nFullColBlocks * BLOCK_SIZE;
  // int weightSize = m*n;
  if (pMapped && pCoeffs) {
    // Half column blocks from full row groups
    for (int group = 0; group < nFullRowGroups; group++) {
      for (int block = 0; block < nFullBlockColsAligned2; block++) {
        for (int j = 0; j < ROWS_PER_GROUP; j++) {
          int blkIdx = block;
          int grpIdx = group * ROWS_PER_GROUP + j;

          int dstIdx = group * ROWS_PER_GROUP * nFullBlockColsAligned2 +
                       block * ROWS_PER_GROUP + j;

          if (block < n && grpIdx < m) {
            dst[dstIdx] = src[grpIdx * n + blkIdx];

          } else {
            dst[dstIdx] = 0;
          }
        }
      }
    }
  }
  return mappedSize;
}

// split by in_channel

int DepthWiseConvMap8bitCoeffs(
    int8_t *pMapped,
    int32_t mvmMatrix,  // matrix type, big or smaller for mvm_sparse
    int filter_height, int filter_width, const int8_t *filter_data,
    int depth_multi, int input_depth) {
  // type-1 mac8bx8b
  // type-2 mac8bx8b_sparse VIP
  // type-3 mac8bx8b with input offset
  // type-4 mac8bx8b_sparse VIP
  int nInput = (mvmMatrix != DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE)
                   ? filter_height * filter_width * input_depth
                   : filter_height * filter_width;
  int nOutput = input_depth * depth_multi;

  int nFullRowGroups =
      (nOutput + ((1 << LOG2_ROWS_PER_GROUP) - 1)) >> LOG2_ROWS_PER_GROUP;

  int nFullColBlocks = (nInput + 1) >> LOG2_COLS_PER_BLOCK;
  int nFullBlockColsAligned2 = nFullColBlocks << LOG2_COLS_PER_BLOCK;

  const int8_t *src = filter_data;
  int8_t *dst = pMapped;
  int mappedSize = nFullRowGroups * nFullColBlocks * BLOCK_SIZE;
  if (pMapped && filter_data) {
    tflite::block_fill_bytes((char *)pMapped, 0, mappedSize);

    for (int dm = 0; dm < depth_multi; dm++) {
      for (int fy = 0; fy < filter_height; fy++) {
        for (int fx = 0; fx < filter_width; fx++) {
          for (int in_ch = 0; in_ch < input_depth; in_ch++) {
            int out_channel = (in_ch * depth_multi) + dm;
            int inputIdx = (fy * filter_width + fx);

            int filter_srcIdx =
                inputIdx * depth_multi * input_depth + out_channel;

            int input_srcIdx =
                (mvmMatrix != DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE)
                    ? (fy * filter_width + fx) * input_depth + in_ch
                    : inputIdx;

            // convert to mvm's matrix order
            int group = out_channel / ROWS_PER_GROUP;
            int j = out_channel % ROWS_PER_GROUP;
            int block = input_srcIdx;
            int dstIdx;

            dstIdx = (group * ROWS_PER_GROUP * nFullBlockColsAligned2) +
                     (block * ROWS_PER_GROUP) + j;

#ifdef KN_DEBUG
            //  if(32 == input_depth)
            {
              printf(
                  "srcIdx: %d input: %d (fy: %d fx: %d in_ch: %d ) dstIdx: %d  "
                  "src[srcIdx]: %d outch: %d nFullBlockColsAligned2: %d grp: "
                  "%d j: %d\n",
                  filter_srcIdx, input_srcIdx, fy, fx, in_ch, dstIdx,
                  src[filter_srcIdx], out_channel, nFullBlockColsAligned2,
                  group, j);
            }
#endif
            dst[dstIdx] = src[filter_srcIdx];
          }
        }
      }
    }
  }
  return mappedSize;
}



int ConvMap8bitCoeffs(int8_t *pMapped, int filter_height, int filter_width,
                      const int8_t *filter_data, int output_depth,
                      int input_depth) {
  int nInput = filter_height * filter_width * input_depth;
  int nOutput = output_depth;

  int nFullRowGroups =
      (nOutput + ((1 << LOG2_ROWS_PER_GROUP) - 1)) >> LOG2_ROWS_PER_GROUP;

  int nFullColBlocks = (nInput + 1) >> LOG2_COLS_PER_BLOCK;
  int nFullBlockColsAligned2 = nFullColBlocks << LOG2_COLS_PER_BLOCK;

  const int8_t *src = filter_data;
  int8_t *dst = pMapped;

  if (pMapped && filter_data) {
    block_fill_bytes((char *)pMapped, 0,
                     nFullRowGroups * nFullColBlocks * BLOCK_SIZE);
    for (int out_ch = 0; out_ch < output_depth; out_ch++) {
      for (int fy = 0; fy < filter_height; fy++) {
        for (int fx = 0; fx < filter_width; fx++) {
          for (int in_ch = 0; in_ch < input_depth; in_ch++) {
            int out_channel = out_ch;
            int inputIdx = (fy * filter_width + fx);

            int input_srcIdx = inputIdx * input_depth + in_ch;

            int filter_srcIdx =
                out_ch * filter_width * filter_height * input_depth +
                input_srcIdx;

            // convert to mvm's matrix order
            int group = out_channel / ROWS_PER_GROUP;
            int j = out_channel % ROWS_PER_GROUP;
            int block = input_srcIdx;
            int dstIdx = group * ROWS_PER_GROUP * nFullBlockColsAligned2 +
                         block * ROWS_PER_GROUP + j;

#ifdef KN_DEBUG
            printf(
                "srcIdx: %d input: %d (fy: %d fx: %d in_ch: %d ) dstIdx: %d  "
                "src[srcIdx]: %d outch: %d\n",
                filter_srcIdx, input_srcIdx, fy, fx, in_ch, dstIdx,
                src[filter_srcIdx], out_channel);
#endif
            dst[dstIdx] = src[filter_srcIdx];
          }
        }
      }
    }
  }
  return nFullRowGroups * nFullColBlocks * BLOCK_SIZE;
}

int ConvIm2ColIndex(const ds_conv2d_layer_t& conv2d, int i_out_x,
    int i_out_y, im2col_idx* im2col_tab) 
{
    int i_out_y_beg = i_out_y * conv2d.stride_y - conv2d.padding_y;
    int i_out_y_end = i_out_y * conv2d.stride_y - conv2d.padding_y + conv2d.ker_y * conv2d.dilation_y;

    int ker_y_start = XT_MAX(0, i_out_y_beg);
    int ker_y_end = XT_MIN(conv2d.in_y, i_out_y_end);

    int i_out_x_beg = i_out_x * conv2d.stride_x - conv2d.padding_x;
    int i_out_x_end = i_out_x * conv2d.stride_x - conv2d.padding_x + conv2d.ker_x * conv2d.dilation_x;


    int ker_x_start = XT_MAX(0, i_out_x_beg);
    int ker_x_end = XT_MIN(conv2d.in_x, i_out_x_end);

    int len_y = (ker_y_end - ker_y_start);
    int len_x = (ker_x_end - ker_x_start);

    int dst_y = 0; 
    if (i_out_y_beg < 0)
        dst_y = (0 - i_out_y_beg);
    else if (i_out_y_beg >= conv2d.in_y)
        dst_y = (i_out_y_beg - conv2d.in_y);

    int dst_x = 0;
    if (i_out_x_beg < 0)
        dst_x = (0 - i_out_x_beg);
    else if (i_out_x_beg >= conv2d.in_x)
        dst_x = (i_out_x_beg - conv2d.in_x);

    int offset_im_src_0 =
        (ker_y_start * conv2d.in_x + ker_x_start) * conv2d.in_ch;
    int offset_im_dst_0 =
        (dst_y * conv2d.ker_x + dst_x) * conv2d.in_ch;  // + len_x;

    im2col_tab->im_dst_offset = offset_im_dst_0;
    im2col_tab->cpy_len_x = len_x * conv2d.in_ch;
    im2col_tab->cpy_len_y = len_y;
    im2col_tab->im_src_offset = offset_im_src_0;

    return (len_x == conv2d.ker_x * conv2d.dilation_x && len_y == conv2d.ker_y * conv2d.dilation_y);
}

int ConvIm2ColIndex(const ds_conv2d_layer_t& conv2d, int i_out_x,
    int i_out_y, im2col_ex_idx* im2col_tab) {
    int i_out_y_beg = i_out_y * conv2d.stride_y - conv2d.padding_y;
    int i_out_y_end = i_out_y * conv2d.stride_y - conv2d.padding_y + conv2d.ker_y * conv2d.dilation_y;

    int ker_y_start = XT_MAX(0, i_out_y_beg);
    int ker_y_end = XT_MIN(conv2d.in_y, i_out_y_end);

    int i_out_x_beg = i_out_x * conv2d.stride_x - conv2d.padding_x;
    int i_out_x_end = i_out_x * conv2d.stride_x - conv2d.padding_x + conv2d.ker_x * conv2d.dilation_x;
    int ker_x_start = XT_MAX(0, i_out_x_beg);
    int ker_x_end = XT_MIN(conv2d.in_x, i_out_x_end);

    int len_y = (ker_y_end - ker_y_start);
    int len_x = (ker_x_end - ker_x_start);

    int dst_y = 0;
    if (i_out_y_beg < 0)
        dst_y = (0 - i_out_y_beg);
    else if (i_out_y_beg >= conv2d.in_y)
        dst_y = (i_out_y_beg - conv2d.in_y);

    int dst_x = 0;
    if (i_out_x_beg < 0)
        dst_x = (0 - i_out_x_beg);
    else if (i_out_x_beg >= conv2d.in_x)
        dst_x = (i_out_x_beg - conv2d.in_x);

    im2col_tab->cpy_len_y = len_y;
    //im2col_tab->im_src_offset = offset_im_src_0;

    im2col_tab->src_offset_wo_ch = (ker_y_start * conv2d.in_x + ker_x_start);
    im2col_tab->dst_offset_wo_ch = (dst_y * conv2d.ker_x + dst_x);
    im2col_tab->len_wo_ch = len_x;
    return (len_x == conv2d.ker_x * conv2d.dilation_x && len_y == conv2d.ker_y * conv2d.dilation_y);
}



// for afloat
void CalculateActivationRangeAflt(TfLiteFusedActivation activation,
                                  AScalar *activation_min,
                                  AScalar *activation_max) {
  if (activation == kTfLiteActRelu) {
    *activation_min = CONST_ASCALAR(0);
    *activation_max = AScalar::MaxAFloat();  // std::numeric_limits<T>::max();
  } else if (activation == kTfLiteActRelu6) {
    *activation_min = CONST_ASCALAR(0);
    *activation_max = CONST_ASCALAR(6);
  } else if (activation == kTfLiteActReluN1To1) {
    *activation_min = CONST_ASCALAR(-1);
    *activation_max = CONST_ASCALAR(1);
  } else {
    *activation_min =
        -(AScalar::MaxAFloat());  // std::numeric_limits<T>::lowest();
    *activation_max = AScalar::MaxAFloat();
  }
}

}  // namespace tflite
