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
#ifndef TENSORFLOW_LITE_KERNELS_MVM_HELPER_H_
#define TENSORFLOW_LITE_KERNELS_MVM_HELPER_H_
//#include <math.h> //prevent AVL macro override
#include "AVL.h"
//#include "TIE_DSPInternal.h"  // from ROME dsp include
#include "DeltaPlatform.h"
//#include "TIE_defs.h"
//#include "TIE_include.h"
#include "tensorflow/lite/c/builtin_op_data.h"

// enumute depthwise conv optimization type
typedef enum _DEPTHWISE_OPT_TYPE {
  DEPTHWISE_CONV_OPT_NONE = 0,
  DEPTHWISE_CONV_OPT_MAC8Bx8B = 1,         // channel multiplier != 1
  DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE = 2,  // VIP channel_mutiplier = 1
  // DEPTHWISE_CONV_OPT_MAC8Bx8B_INPUT_OFFSET = 3,
  // DEPTHWISE_CONV_OPT_MAC8Bx8B_SPARSE_INPUT_OFFSET = 4,
} DEPTHWISE_OPT_TYPE;
//#define SYMETRIC_ROUNDING
#ifndef MIN
#define MIN(a, b) (a) < (b) ? (a) : (b);
#endif
#ifndef MAX
#define MAX(a, b) (a) > (b) ? (a) : (b);
#endif

#ifdef HEMILITE

/// alternate names for vr64 half-register selects

typedef enum { VRL = 0, VRH } REG_HALF_t;
#ifdef HEMILITE
#define BLOCK_SIZE 8
#define LOG2_ROWS_PER_GROUP 2
#define ROWS_PER_GROUP (1 << LOG2_ROWS_PER_GROUP)
#define LOG2_COLS_PER_BLOCK 1
#define COLS_PER_BLOCK (1 << LOG2_COLS_PER_BLOCK)

// float depthwise map
#define BLOCK_SIZE_FLT 8
#define LOG2_ROWS_PER_GROUP_FLT 1
#define ROWS_PER_GROUP_FLT (1 << LOG2_ROWS_PER_GROUP_FLT)
#define LOG2_COLS_PER_BLOCK_FLT 1
#define COLS_PER_BLOCK_FLT (1 << LOG2_COLS_PER_BLOCK_FLT)

#endif

#endif
// move this to somewhere header
#include "tensorflow/lite/micro/ia700/debug_helper.h"
#include "tensorflow/lite/micro/ia700/platform.h"

#ifdef HEMILITE
#define load8x2_vr_postI_unalign(VRX, ADDR, POSTI) \
  load8x1_vr_postI(VRX, ADDR, POSTI, VRQ0);        \
  load8x1_vr_postI(VRX, ADDR, POSTI, VRQ1);

#define load16x2_vr_postI_unalign(VRX, ADDR, POSTI) \
  load16x1_vr_postI(VRX, ADDR, POSTI, VRQ0);        \
  load16x1_vr_postI(VRX, ADDR, POSTI, VRQ1);
#define COPY_BLK_BYTES(DST, SRC, BLKCNT)         \
  do {                                           \
    vr64 vr_im;                                  \
    for (int ii = 0; ii < BLKCNT; ii++) {        \
      load8x1_vr_postI(vr_im, SRC, INC1, VRQ0);  \
      store8x1_vr_postI(vr_im, DST, INC1, VRQ0); \
    }                                            \
  } while (0)

#define COPY_BLK_BYTES_XOR(DST, SRC, BLKCNT, OFFSET) \
  do {                                               \
    vr64 vr_im;                                      \
    vr64 vr_offset, vr_out;                          \
    load8x1_vr_postI(vr_im, SRC, INC1, VRQ0);        \
    replicate_ar(vr_offset, 0x3, OFFSET);            \
    for (int ii = 0; ii < BLKCNT - 1; ii++) {        \
      vr_out = vbool(vr_im, vr_offset, 0x6);         \
      load8x1_vr_postI(vr_im, SRC, INC1, VRQ0);      \
      store8x1_vr_postI(vr_out, DST, INC1, VRQ0);    \
    }                                                \
    vr_out = vbool(vr_im, vr_offset, 0x6);           \
    store8x1_vr_postI(vr_out, DST, INC1, VRQ0);      \
  } while (0)
#define COPY_BLK_BYTES_ALIGN4(DST, SRC, BYTECNT)          \
  do {                                                    \
    ulsr32 UR_src = align_32x2_load(SRC);                 \
    ulsr32 UR_des = align_32x2_store(DST);                \
    int loopLim = BYTECNT >> 3;                           \
    if (loopLim > 0) {                                    \
      vr64 VR_S0;                                         \
      load_32x2_vr_a(VR_S0, UR_src, SRC);                 \
      for (int32_t ii = 0; ii < (loopLim - 1); ii++) {    \
        store_32x2_vr_a(VR_S0, UR_des, DST);              \
        load_32x2_vr_a(VR_S0, UR_src, SRC);               \
      }                                                   \
      store_32x2_vr_a(VR_S0, UR_des, DST);                \
      flush_32x2(UR_des, DST);                            \
    }                                                     \
    for (int32_t ii = loopLim << 3; ii < BYTECNT; ii++) { \
      vr64 VR_S0;                                         \
      load8x1_vr_postI(VR_S0, SRC, INC1, VRQ0);           \
      store8x1_vr_postI(VR_S0, DST, INC1, VRQ0);          \
    }                                                     \
  } while (false)
#define COPY_BLK_BYTES_XOR_ALIGN4(DST, SRC, BYTECNT, OFFSET) \
  do {                                                       \
    ulsr32 UR_src = align_32x2_load(SRC);                    \
    ulsr32 UR_des = align_32x2_store(DST);                   \
    vr64 VR_offset, VR_out;                                  \
    replicate_ar(VR_offset, 0x3, OFFSET);                    \
    int loopLim = BYTECNT >> 3;                              \
    if (loopLim > 0) {                                       \
      vr64 VR_S0;                                            \
      load_32x2_vr_a(VR_S0, UR_src, SRC);                    \
      for (int32_t ii = 0; ii < (loopLim - 1); ii++) {       \
        VR_out = vbool(VR_S0, VR_offset, 0x6);               \
        load_32x2_vr_a(VR_S0, UR_src, SRC);                  \
        store_32x2_vr_a(VR_out, UR_des, DST);                \
      }                                                      \
      VR_out = vbool(VR_S0, VR_offset, 0x6);                 \
      store_32x2_vr_a(VR_out, UR_des, DST);                  \
      flush_32x2(UR_des, DST);                               \
    }                                                        \
    for (int32_t ii = loopLim << 3; ii < BYTECNT; ii++) {    \
      vr64 VR_S0;                                            \
      load8x1_vr_postI(VR_S0, SRC, INC1, VRQ0);              \
      VR_out = vbool(VR_S0, VR_offset, 0x6);                 \
      store8x1_vr_postI(VR_out, DST, INC1, VRQ0);            \
    }                                                        \
  } while (false)
#endif
//#define BLK_FILL_16BYTES_ZERO(pBUF, SIZE) tflite::block_fill_bytes((char
//*)pBUF, 0, SIZE*16)

#define SATURATE_INT32_VR_IDX(VR_OUT, VR_IN, MIN, MAX, IDX) \
  do {                                                      \
    int outInt32 = move32_ar_vr(VR_IN, IDX);                \
    outInt32 = XT_MIN(MAX, outInt32);                       \
    outInt32 = XT_MAX(MIN, outInt32);                       \
    replicate_ar(VR_OUT, 1 << IDX, outInt32);               \
  } while (false)

#define SATURATE_INT32_VR128(VR_OUT, VR_IN, MIN, MAX) \
  do {                                                \
    int outInt32 = move32_ar_vr(VR_IN, VRQ0);         \
    outInt32 = XT_MIN(MAX, outInt32);                 \
    outInt32 = XT_MAX(MIN, outInt32);                 \
    replicate_ar(VR_OUT, 0x1, outInt32);              \
    outInt32 = move32_ar_vr(VR_IN, VRQ1);             \
    outInt32 = XT_MIN(MAX, outInt32);                 \
    outInt32 = XT_MAX(MIN, outInt32);                 \
    replicate_ar(VR_OUT, 0x2, outInt32);              \
    outInt32 = move32_ar_vr(VR_IN, VRQ2);             \
    outInt32 = XT_MIN(MAX, outInt32);                 \
    outInt32 = XT_MAX(MIN, outInt32);                 \
    replicate_ar(VR_OUT, 0x4, outInt32);              \
    outInt32 = move32_ar_vr(VR_IN, VRQ3);             \
    outInt32 = XT_MIN(MAX, outInt32);                 \
    outInt32 = XT_MAX(MIN, outInt32);                 \
    replicate_ar(VR_OUT, 0x8, outInt32);              \
  } while (false)
#define SATURATE_INT32_VR64(VR_OUT, VR_IN, MIN, MAX) \
  do {                                               \
    int outInt32 = move32_ar_vr(VR_IN, VRQ0);        \
    outInt32 = XT_MIN(MAX, outInt32);                \
    outInt32 = XT_MAX(MIN, outInt32);                \
    replicate_ar(VR_OUT, 0x1, outInt32);             \
    outInt32 = move32_ar_vr(VR_IN, VRQ1);            \
    outInt32 = XT_MIN(MAX, outInt32);                \
    outInt32 = XT_MAX(MIN, outInt32);                \
    replicate_ar(VR_OUT, 0x2, outInt32);             \
  } while (false)
typedef struct {
  uint16_t ker_y; /**< kernel height */
  uint16_t ker_x; /**< kernel width */

  uint16_t in_ch; /**< number of input channels */
  uint16_t in_y;  /**< input height */
  uint16_t in_x;  /**< input width */

  uint16_t out_ch; /**< number of input channels */
  uint16_t out_y;  /**< output height */
  uint16_t out_x;  /**< output width  */

  uint16_t stride_y;  /**< stride of height */
  uint16_t stride_x;  /**< stride of width */
  uint16_t padding_y; /**< padding of height */
  uint16_t padding_x; /**< padding of width */

  // dilation factor
  uint16_t dilation_y;
  uint16_t dilation_x;
  uint32_t ch_mult;  // depth multipler
  int32_t input_offset;
  // int8_t filter_offset;
  int32_t* pIm2Col;  // scratch buffer flatten im2col
  int32_t* pOutput;  // scratch buffer output 32bit fixpoint accumation
                     //	Padding paddingType; /**< padding of type */
} ds_conv2d_layer_t;

typedef struct im2col_index_t {
  uint32_t im_src_offset;
  uint16_t im_dst_offset;  // fiter*filter_y <=255
  uint16_t cpy_len_x;      // filter_x
  uint16_t cpy_len_y;      // filter_y
} im2col_idx;

typedef struct im2col_index_ex_t {
  uint16_t cpy_len_y;  // filter_y
  uint16_t src_offset_wo_ch;
  uint16_t dst_offset_wo_ch;
  uint16_t len_wo_ch;
} im2col_ex_idx;

namespace tflite {
void block_copy_bytes(int8_t* pDes, const int8_t* pSrc, int32_t nBytes);
void ConvertQ31ToAfloat(const int32_t* input, AScalar* output, int size,
                        int32_t bexp);
void ConvertQ31ToAfloat(const int32_t* input, AScalar* output, int size,
                        int32_t* pShift, int32_t baseExp);  // PerShift
void ConvertQ15ToAfloat(const int16_t* input, AScalar* output, int size,
                        int32_t bexp);

int MVMFloatInt8Kernel(float* y, const float* x, const int32_t* A,
                       const float* bias, int m, int n, int32_t* x_in_tmp,
                       const AScalar& act_min, const AScalar& act_max,
                       const AScalar& scale, AScalar* scale_ptr = nullptr);
#ifdef MVM_FLOATxINT16
int MVMFloatInt16Kernel(float* y, const float* x, const int32_t* A,
                        const float* bias, int m, int n, int32_t* x_in_tmp,
                        const AScalar& act_min, const AScalar& act_max,
                        const AScalar& scale, AScalar* scale_ptr = nullptr);
#endif
void ConvertIEEEFloatToAfloat(const float* input, AScalar* output, int size);
// void ConvertQ15ToAfloat(const int16_t *input, AScalar *output, int size,
// int32_t* pShift, int32_t baseExp); //PerShift
int AddConstQuantizedInt8(int8_t* input, int32_t const_offset, uint8_t* output,
                          int size);
int AddConstQuantizedInt8Fast128(int32_t* input, uint32_t* output, int size);

int FullyConnectedMap8bitCoeffs(int8_t* pMapped, int8_t* pCoeffs, int m, int n);

int DepthWiseConvMap8bitCoeffs(int8_t* pMapped, int32_t mvmMatrix,
                               int filter_height, int filter_widht,
                               const int8_t* filter_data, int depth_multi,
                               int input_depth);
void MVMInputOffsetPrepare(const int32_t* A, int32_t* output, int m, int n,
                           uint32_t input_offset);

void convert_ieee_float_to_afloat16(const float* input, uint16_t* out_float16,
                                    int size);
void convert_ieee_float_to_int8_scale(const float* input, int8_t* out_int8,
                                      float* scale_out, int size);

int ConvMap8bitCoeffs(int8_t* pMapped, int filter_height, int filter_width,
                      const int8_t* filter_data, int output_depth,
                      int input_depth);
// only able to produce unsigned int8, exceed range is error.

void DepthWiseConvIm2ColIndexGen(const ds_conv2d_layer_t& ds_conv2d,
                                 im2col_idx* im2col_tab, uint16_t* im2Col_ysrc);

void ConvIm2ColIndexGen(const ds_conv2d_layer_t& conv2d, im2col_idx* im2col_tab,
                        uint16_t* im2Col_ysrc);
void CalculateActivationRangeAflt(TfLiteFusedActivation activation,
                                  AScalar* activation_min,
                                  AScalar* activation_max);
int ConvIm2ColIndex(const ds_conv2d_layer_t& conv2d, int i_out_x, int i_out_y,
                    im2col_idx* im2col_tab);

int ConvIm2ColIndex(const ds_conv2d_layer_t& conv2d, int i_out_x, int i_out_y,
                    im2col_ex_idx* im2col_tab);

static inline void im2col_padding(int8_t* dst, const int8_t* src, int32_t im_x,
                                  int filter_width, int32_t len_x,
                                  int32_t len_y, int32_t in_channel,
                                  uint16_t dilation_y = 1,
                                  uint16_t dilation_x = 1) {
  // if(1== in_channel)
  {
#ifdef __XTENSA__
#pragma concurrent
#endif
    if (dilation_y != 1 || dilation_x != 1) {
      int l_wo_ch = len_x / in_channel;  // REMOVEME
      for (int yy = 0; yy < len_y; yy += dilation_y) {
        int8_t* dst2 = dst;
        for (int xx = 0; xx < l_wo_ch; xx += dilation_x) {
          const int8_t* src2 = src + xx * in_channel;
          // in_y_origin + dilation_height_factor * filter_y;

          COPY_BLK_BYTES(dst2, src2, in_channel);  // TODO circ Idx
          // dst2 += in_channel; //src += (dilation_x * in_channel);
        }
        dst += filter_width * in_channel;
        src += im_x * (dilation_y * in_channel);
      }

    } else {
      for (int yy = 0; yy < len_y; yy++) {
        // for(int xx = 0; xx < len_x; xx++)
        {
          int8_t* dst2 = dst;
          const int8_t* src2 = src;
          COPY_BLK_BYTES(dst2, src2, len_x);  // TODO circ Idx
        }
        dst += filter_width * in_channel;
        src += im_x * in_channel;
      }
    }
  }
}

static inline void im2col_padding_offset(int8_t* dst, const int8_t* src,
                                         int32_t im_x, int filter_width,
                                         int32_t len_x, int32_t len_y,
                                         int32_t in_channel, uint32_t offset,
                                         uint16_t dilation_y = 1,
                                         uint16_t dilation_x = 1) {
#ifdef __XTENSA__
#pragma concurrent
#endif
  if (dilation_y != 1 || dilation_x != 1) {
    int l_wo_ch = len_x / in_channel;  // REMOVEME
    for (int yy = 0; yy < len_y; yy += dilation_y) {
      int8_t* dst2 = dst;
      for (int xx = 0; xx < l_wo_ch; xx += dilation_x) {
        const int8_t* src2 = src + xx * in_channel;
        // in_y_origin + dilation_height_factor * filter_y;

        COPY_BLK_BYTES_XOR(dst2, src2, in_channel, offset);  // TODO circ Idx
        // dst2 += in_channel; //src += (dilation_x * in_channel);
      }
      dst += filter_width * in_channel;
      src += im_x * (dilation_y * in_channel);
    }

  } else {
    for (int yy = 0; yy < len_y; yy++) {
      // for(int xx = 0; xx < len_x; xx++)
      {
        int8_t* dst2 = dst;
        const int8_t* src2 = src;
        COPY_BLK_BYTES_XOR(dst2, src2, len_x, offset);  // TODO circ Idx
      }
      dst += filter_width * in_channel;
      src += im_x * in_channel;
    }
  }
}
// data type: int8_t, float32
static inline void im2colex_padding_offset_align4(
    int8_t* dst, int32_t dst_offset, const int8_t* src, int32_t src_offset,
    int32_t im_x, int filter_width, int32_t len_x, int32_t len_y,
    int32_t in_channel, uint32_t offset, uint16_t dilation_y = 1,
    uint16_t dilation_x = 1) {
  //
  if (1 != dilation_y || 1 != dilation_x) {
    dst += dst_offset * in_channel;
    src += src_offset * in_channel;
    int l_wo_ch = len_x;  // LENX always without channel in im2colEx
    for (int yy = 0; yy < len_y; yy += dilation_y) {
      int8_t* dst2 = dst;
      for (int xx = 0; xx < l_wo_ch; xx += dilation_x) {
        const int8_t* src2 = src + xx * in_channel;
        COPY_BLK_BYTES_XOR_ALIGN4(dst2, src2, in_channel,
                                  offset);  // TODO circ Idx
      }
      dst += filter_width * in_channel;
      src += im_x * (dilation_y * in_channel);
    }
  } else {
#ifdef __XTENSA__
#pragma concurrent
#endif
    dst += dst_offset * in_channel;
    src += src_offset * in_channel;
    for (int yy = 0; yy < len_y; yy++) {
      // for(int xx = 0; xx < len_x; xx++)
      {
        int8_t* dst2 = dst;
        const int8_t* src2 = src;
        COPY_BLK_BYTES_XOR_ALIGN4(dst2, src2, len_x * in_channel,
                                  offset);  // TODO circ Idx
      }
      dst += filter_width * in_channel;
      src += im_x * in_channel;
    }
  }
}
static inline void im2col_padding_unalign(
    int8_t* dst, int32_t dst_offset, const int8_t* src, int32_t src_offset,
    int32_t im_x, int filter_width, int32_t len_x, int32_t len_y,
    int32_t src_channel, int32_t dst_channel, uint32_t offset,
    uint16_t dilation_y = 1, uint16_t dilation_x = 1) {
  if (1 != dilation_y || 1 != dilation_x) {
    dst += dst_offset * dst_channel;
    src += src_offset * src_channel;
    int padding_bytes = dst_channel - src_channel;
    int l_wo_ch = len_x;  // im2col_tab_2.len_wo_ch; / src_channel;
    for (int yy = 0; yy < len_y; yy += dilation_y) {
      int8_t* dst2 = dst;

      for (int xx = 0; xx < l_wo_ch; xx += dilation_x) {
        const int8_t* src2 = src + xx * src_channel;
        COPY_BLK_BYTES_XOR(dst2, src2, src_channel, offset);  // TODO circ Idx
        dst2 += padding_bytes;
      }
      dst += filter_width * dst_channel;
      src += im_x * dilation_y * src_channel;
    }
  } else {
#ifdef __XTENSA__
#pragma concurrent
#endif
    dst += dst_offset * dst_channel;
    src += src_offset * src_channel;
    int padding_bytes = dst_channel - src_channel;
    for (int yy = 0; yy < len_y; yy++) {
      int8_t* dst2 = dst;
      const int8_t* src2 = src;
      for (int xx = 0; xx < len_x; xx++) {
        COPY_BLK_BYTES_XOR(dst2, src2, src_channel, offset);  // TODO circ Idx
        dst2 += padding_bytes;
        // src2 += src_channel;
      }
      // dst += filter_width;
      // src += im_x;
      dst += filter_width * dst_channel;
      src += im_x * src_channel;
    }
  }
}
template <typename T>
static inline void im2col_padding_align4(T* dst, const T* src, int32_t im_x,
                                         int filter_width, int32_t len_x,
                                         int32_t len_y, int32_t in_channel,
                                         uint16_t dilation_y = 1,
                                         uint16_t dilation_x = 1) {
  // if(1== in_channel)

#ifdef __XTENSA__
#pragma concurrent
#endif
  // int cpy_byte_len = len_x * sizeof(T);
  int in_channel_bytes = in_channel * sizeof(T);
  if (dilation_y != 1 || dilation_x != 1) {
    int l_wo_ch = len_x / in_channel;  // REMOVEME
    for (int yy = 0; yy < len_y; yy += dilation_y) {
      T* dst2 = dst;
      for (int xx = 0; xx < l_wo_ch; xx += dilation_x) {
        const T* src2 = src + xx * in_channel;
        // in_y_origin + dilation_height_factor * filter_y;

        COPY_BLK_BYTES_ALIGN4(dst2, src2, in_channel_bytes);  // TODO circ Idx
        // dst2 += in_channel; //src += (dilation_x * in_channel);
      }
      dst += filter_width * in_channel;
      src += im_x * (dilation_y * in_channel);
    }

  } else {
    int cpy_byte_len = len_x * sizeof(T);
    for (int yy = 0; yy < len_y; yy++) {
      // for(int xx = 0; xx < len_x; xx++)
      {
        T* dst2 = dst;
        const T* src2 = src;
        COPY_BLK_BYTES_ALIGN4(dst2, src2, cpy_byte_len);  // TODO circ Idx
      }
      dst += filter_width * in_channel;
      src += im_x * in_channel;
    }
  }
}

static inline void im2col_padding_offset_align4(
    int8_t* dst, const int8_t* src, int32_t im_x, int filter_width,
    int32_t len_x, int32_t len_y, int32_t in_channel, uint32_t offset,
    uint16_t dilation_y = 1, uint16_t dilation_x = 1) {
  // if(1== in_channel)

#ifdef __XTENSA__
#pragma concurrent
#endif
  if (1 != dilation_y || 1 != dilation_x) {
    int l_wo_ch = len_x / in_channel;  // REMOVEME
    for (int yy = 0; yy < len_y; yy += dilation_y) {
      int8_t* dst2 = dst;
      for (int xx = 0; xx < l_wo_ch; xx += dilation_x) {
        const int8_t* src2 = src + xx * in_channel;
        COPY_BLK_BYTES_XOR_ALIGN4(dst2, src2, in_channel,
                                  offset);  // TODO circ Idx
      }
      dst += filter_width * in_channel;
      src += im_x * dilation_y * in_channel;
    }
  } else {
    for (int yy = 0; yy < len_y; yy++) {
      // for(int xx = 0; xx < len_x; xx++)
      {
        int8_t* dst2 = dst;
        const int8_t* src2 = src;
        COPY_BLK_BYTES_XOR_ALIGN4(dst2, src2, len_x, offset);  // TODO circ Idx
      }
      dst += filter_width * in_channel;
      src += im_x * in_channel;
    }
  }
}

#ifdef HEMILITE

static inline void block_fill_words(int32_t* dst, const int32_t filler,
                                    int count) {
  ulsr32 ur_dst = align_32x2_store(dst);
  vr64 src = vseta_vr(0, 0);

  replicate_ar(src, 3, filler);

  for (int i = 0; i < (count >> 1); i++) {
    store_32x2_vr_a(src, ur_dst, dst);
  }
  flush_32x2(ur_dst, dst);

  if (count & 1) {
    store32x1_vr_postI(src, dst, INC1, VRQ0);
  }
}

static inline void block_fill_bytes(char* dst, const char filler, int count) {
  int32_t src;
  if ((((int)dst | count) & 3) == 0) {
    src = (unsigned char)filler;
    src = (src << 8) | src;
    src = (src << 16) | src;
    block_fill_words((int32_t*)dst, src, count >> 2);
    return;
  }

  for (int i = 0; i < count; i++) {
    *dst++ = filler;
  }
}

static inline void ConvertQ31ToAfloat(const int32_t& input, AScalar& output,
                                      int32_t bexp) {
  vr64 vr_tmp;
  replicate_ar(vr_tmp, 0x1, input);
  convert_32I_to_32F_x1(vr_tmp, bexp, VRQ0);
  output.fr = move32_fr_vr_idx(vr_tmp, VRQ0);
}
#endif
}  // namespace tflite
#endif
