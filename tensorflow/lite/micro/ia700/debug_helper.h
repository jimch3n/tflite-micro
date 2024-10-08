
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

#ifndef TENSORFLOW_LITE_DEBUG_HELPER_H_
#define TENSORFLOW_LITE_DEBUG_HELPER_H_
#define KN_PRINT_Q7_SIZE_FORCE(BUF, SIZE)                                     \
  do {                                                                        \
    int8_t *pBuf = (int8_t *)BUF;                                             \
    int print_size = (SIZE);                                                  \
    printf("%s: %p size:%d %s:%d\n", #BUF, pBuf, SIZE, __FUNCTION__,          \
           __LINE__);                                                         \
    for (int ii = 0; (ii < print_size); ii++) {                               \
      if ((ii & 7) == 0) printf("%3d\t", ii);                                 \
      printf("[%02x] %c", pBuf[ii] & 0xff, ((ii + 1) & 7) == 0 ? '\n' : ' '); \
    }                                                                         \
    putchar('\n');                                                            \
  } while (0)
#define KN_PRINTD_FORCE(INTD, PREFIX)            \
  do {                                           \
    printf("%s %s = %d\n", PREFIX, #INTD, INTD); \
  } while (0)

#define KN_MODEL_WRITE_FILE(MODEL, SIZE)                          \
  do {                                                            \
    FILE *fp = fopen(#MODEL ".tflite", "wb+");                    \
    if (!fp) {                                                    \
      printf("cannot write model file: %s", #MODEL);              \
      break;                                                      \
    }                                                             \
    fwrite(MODEL, sizeof(unsigned char), SIZE, fp);               \
    fclose(fp);                                                   \
    printf("%s.tflite write successfully.!\n", #MODEL ".tflite"); \
  } while (false)
#if defined(KN_DEBUG)  //&& !defined(NDEBUG)
#include <stdio.h>
#define KN_TFLM_PRINT(CNTX, INTD)                           \
  do {                                                      \
    (CNTX)->ReportError((CNTX), "%s = %d;\n", #INTD, INTD); \
  } while (0)
#define KN_TFLM_PRINTX(CNTX, INTD)                                    \
  do {                                                                \
    (CNTX)->ReportError((CNTX), "%s = %x;\n", #INTD, (unsigned)INTD); \
  } while (0)

#define KN_PRINT_Q7_SIZE(BUF, SIZE)                                           \
  do {                                                                        \
    int8_t *pBuf = (int8_t *)BUF;                                             \
    int print_size = (SIZE);                                                  \
    printf("%s: %p size:%d %s:%d\n", #BUF, pBuf, SIZE, __FUNCTION__,          \
           __LINE__);                                                         \
    for (int ii = 0; (ii < print_size); ii++) {                               \
      if ((ii & 7) == 0) printf("%3d\t", ii);                                 \
      printf("[%02x] %c", pBuf[ii] & 0xff, ((ii + 1) & 7) == 0 ? '\n' : ' '); \
    }                                                                         \
    putchar('\n');                                                            \
  } while (0)

#define KN_PRINT_Q7_SIZE_CTABLE(BUF, SIZE)                                     \
  do {                                                                         \
    int8_t *pBuf = (int8_t *)BUF;                                              \
    int print_size = (SIZE);                                                   \
    printf("static const unsigned char %s[%d] = { //%p: %s:%d\n", #BUF, SIZE,  \
           pBuf, __FUNCTION__, __LINE__);                                      \
    for (int ii = 0; (ii < print_size); ii++) {                                \
      if ((ii & 7) == 0) printf("/*%3d*/\t", ii);                              \
      printf("0x%02x, %c", pBuf[ii] & 0xff, ((ii + 1) & 7) == 0 ? '\n' : ' '); \
    }                                                                          \
    printf("};\n");                                                            \
  } while (0)

#define KN_PRINT_Q15_SIZE(BUF, SIZE)                                 \
  do {                                                               \
    int16_t *pBuf = (int16_t *)BUF;                                  \
    int print_size = (SIZE);                                         \
    printf("%s: %p size:%d %s:%d\n", #BUF, pBuf, SIZE, __FUNCTION__, \
           __LINE__);                                                \
    for (int ii = 0; (ii < print_size); ii++) {                      \
      if ((ii & 7) == 0) printf("%3d\t", ii);                        \
      printf("0x%04x, %c", pBuf[ii] & 0xffff,                        \
             ((ii + 1) & 7) == 0 ? '\n' : ' ');                      \
    }                                                                \
    putchar('\n');                                                   \
  } while (0)
#define KN_PRINT_Q8_SIZE(BUF, SIZE)                                  \
  do {                                                               \
    int8_t *pBuf = (int8_t *)BUF;                                    \
    int print_size = (SIZE);                                         \
    printf("%s: %p size:%d %s:%d\n", #BUF, pBuf, SIZE, __FUNCTION__, \
           __LINE__);                                                \
    for (int ii = 0; (ii < print_size); ii++) {                      \
      printf("[%3d]: %-3u %c", ii, pBuf[ii] & 0xff,                  \
             ((ii + 1) & 7) == 0 ? '\n' : ' ');                      \
    }                                                                \
    putchar('\n');                                                   \
  } while (0)

#define KN_PRINTD(INTD)                                                   \
  do {                                                                    \
    printf("%-10s: %6d\t%s = %d\n", __FUNCTION__, __LINE__, #INTD, INTD); \
  } while (0)

#define KN_PRINTX(INTD)                                            \
  do {                                                             \
    printf("%s: %5d %s = 0x%08x\n", __FUNCTION__, __LINE__, #INTD, \
           (unsigned int)INTD);                                    \
  } while (0)

#define KN_PRINT_FXP(INTD, EXP)                                             \
  do {                                                                      \
    float exp_fxp = powf(2.0, EXP);                                         \
    float flt_result = (float)INTD * exp_fxp;                               \
    printf("%s: %5d %s = 0x%08x (exp: %d) %.10f\n", __FUNCTION__, __LINE__, \
           #INTD, (unsigned int)INTD, EXP, flt_result);                     \
  } while (0)
#define KN_PRINTDBL(INTD)                                             \
  do {                                                                \
    printf("%s: %5d %s = %f\n", __FUNCTION__, __LINE__, #INTD, INTD); \
  } while (0)

#define KN_PRINTINT64(INTD)                                             \
  do {                                                                  \
    printf("%s: %5d %s = %lld\n", __FUNCTION__, __LINE__, #INTD, INTD); \
  } while (0)

#define KN_PRINTF(INTD)                                                    \
  do {                                                                     \
    float a = *(float *)&INTD;                                             \
    printf("%s: %5d %s = %f\n", __FUNCTION__, __LINE__, #INTD, (double)a); \
  } while (0)

#define KN_PRINTAFLT(FTL)                                                      \
  do {                                                                         \
    AScalar *tmpAflt = (AScalar *)&(FTL);                                      \
    printf("%s = %10d %.10f\n", #FTL, __LINE__, (double)tmpAflt->to_double()); \
  } while (0)
#define KN_PRINT_CRC(BUF, SIZE)                                               \
  do {                                                                        \
    uint16_t crc_out = tflite::dmx1a::gen_crc16((const uint8_t *)BUF, SIZE);  \
    printf("%s: %5d, crc: 0x%04x %s:%d\n", #BUF, SIZE, crc_out, __FUNCTION__, \
           __LINE__);                                                         \
  } while (0)
#define KN_PRINT_Q31_SIZE(BUF, SIZE)                                 \
  do {                                                               \
    int32_t *pBuf = (int32_t *)BUF;                                  \
    printf("%s: %p size:%d %s:%d\n", #BUF, pBuf, SIZE, __FUNCTION__, \
           __LINE__);                                                \
    for (int ii = 0; ii < (int)SIZE; ii++) {                         \
      printf("[%3d]: %08x %c", ii, pBuf[ii],                         \
             ((ii + 1) & 7) == 0 ? '\n' : ' ');                      \
    }                                                                \
    putchar('\n');                                                   \
  } while (0)
#ifdef DMX1A

#define KN_PRINT_VR128(VR_IN)                                              \
  do {                                                                     \
    VAR_ALIGN_16 AScalar temp_dmp[4];                                      \
    store32x4_vr_idxI(VR_IN, temp_dmp, 0);                                 \
    printf("%-16s: %d\t0: %.11f\t1: %.11f\t2: %.11f\t3: %.11f\n", #VR_IN,  \
           __LINE__, (double)temp_dmp[0].to_float(),                       \
           (double)temp_dmp[1].to_float(), (double)temp_dmp[2].to_float(), \
           (double)temp_dmp[3].to_float());                                \
  } while (0)
#define KN_PRINTX_VR128(VR_IN)                                            \
  do {                                                                    \
    VAR_ALIGN_16 int32_t temp_dmp[4];                                     \
    store32x4_vr_idxI(VR_IN, temp_dmp, 0);                                \
    printf("%-16s: %d\t0: %08x\t1:  %08x\t2:  %08x\t3:  %08x\n", #VR_IN,  \
           __LINE__, temp_dmp[0], temp_dmp[1], temp_dmp[2], temp_dmp[3]); \
  } while (0)

#define KN_PRINT_VR(X) KN_PRINT_VR128(X)
#define KN_PRINTX_VR(X) KN_PRINTX_VR128(X)

#endif

#ifdef HEMILITE

#define KN_PRINT_VR64(VR_IN)                                                \
  do {                                                                      \
    VAR_ALIGN_8 AScalar temp_dmp[2];                                        \
    store32x2_vr_idxI(VR_IN, temp_dmp, 0);                                  \
    printf("%-16s: %d\t0: %.11f\t1: %.11f\n", #VR_IN, __LINE__,             \
           (double)temp_dmp[0].to_float(), (double)temp_dmp[1].to_float()); \
  } while (0)
#define KN_PRINTX_VR64(VR_IN)                                               \
  do {                                                                      \
    VAR_ALIGN_8 int32_t temp_dmp[2];                                        \
    store32x2_vr_idxI(VR_IN, temp_dmp, 0);                                  \
    printf("%-16s: %d\t0: %08x\t1:  %08x\n", #VR_IN, __LINE__, temp_dmp[0], \
           temp_dmp[1]);                                                    \
  } while (0)

#define KN_PRINT_VR(X) KN_PRINT_VR64(X)
#define KN_PRINTX_VR(X) KN_PRINTX_VR64(X)
#endif
#define KN_PRINT_AFLOAT(IN, SIZE)                                      \
  do {                                                                 \
    AScalar *pTmp = (AScalar *)IN;                                     \
    printf("%s: %4d: %-16s: %d\n", __FUNCTION__, __LINE__, #IN, SIZE); \
    for (int ii = 0; ii < (int)SIZE; ii++) {                           \
      printf("[%3d] %.11f %c", ii, (double)pTmp[ii].to_float(),        \
             ((ii + 1) & 3) == 0 ? '\n' : ' ');                        \
    }                                                                  \
    printf(">\n");                                                     \
  } while (0)

#define KN_PRINT_AFLOAT16(IN, SIZE)                                        \
  do {                                                                     \
    uint16_t *pTmp = (uint16_t *)IN;                                       \
    AScalar aflt;                                                          \
    printf("%s: %4d: %-16s: %d (AFLOAT16)\n", __FUNCTION__, __LINE__, #IN, \
           SIZE);                                                          \
    for (int ii = 0; ii < (int)SIZE; ii++) {                               \
      vr64 vr_flt;                                                         \
      load16x1_vr_postI(vr_flt, pTmp, INC1, VRQ0);                         \
      convert_16F_to_32F_x1(vr_flt, TF_FLT16_SIGN, TF_FLT16_EXP,           \
                            TF_FLT16_BIAS, VRQ0);                          \
      aflt.fr = move32_fr_vr_idx(vr_flt, VRQ0);                            \
      printf("[%3d] %.11f %c", ii, (double)aflt.to_float(),                \
             ((ii + 1) & 3) == 0 ? '\n' : ' ');                            \
    }                                                                      \
    printf(">\n");                                                         \
  } while (0)

#define KN_PRINT_FLOAT(IN, SIZE)                                             \
  do {                                                                       \
    float *pTmp = (float *)IN;                                               \
    printf("%s: %4d: %-16s: %d PTR:%p\n", __FUNCTION__, __LINE__, #IN, SIZE, \
           IN);                                                              \
    for (int ii = 0; ii < (int)SIZE; ii++) {                                 \
      printf("[%3d] %.11f %c", ii, (double)pTmp[ii],                         \
             ((ii + 1) & 3) == 0 ? '\n' : ' ');                              \
    }                                                                        \
    printf(">\n");                                                           \
  } while (0)
#define KN_PRINT_SHAPE(SHAPE)                              \
  do {                                                     \
    printf("%s <", #SHAPE);                                \
    for (int ii = 0; ii < SHAPE.DimensionsCount(); ++ii) { \
      int32_t dim = SHAPE.Dims(ii);                        \
      printf("%2d,", dim);                                 \
    }                                                      \
    printf(">\n");                                         \
  } while (0)
#define KN_PRINTS(S)    \
  do {                  \
    printf("%s \n", S); \
  } while (0)

#else
// empy
#define KN_TFLM_PRINT(CNTX, INTD) (static_cast<void>(0))
#define KN_TFLM_PRINTX(CNTX, INTD) (static_cast<void>(0))
#define KN_PRINTD(INTD)
#define KN_PRINTX(INTD)
#define KN_PRINTDBL(INTD)
#define KN_PRINTINT64(INTD)
#define KN_PRINTF(INTD)
#define KN_PRINT_Q7_SIZE(BUF, SIZE) (static_cast<void>(0))
#define KN_PRINT_Q7_SIZE_CTABLE(BUF, SIZE)
#define KN_PRINT_Q15_SIZE(BUF, SIZE)
#define KN_PRINT_CRC(BUF, SIZE)
#define KN_PRINT_Q31_SIZE(BUF, SIZE)
#define KN_TFLM_PRINTF(CNTX, INTD) (static_cast<void>(0))
#define KN_PRINTAFLT(FTL)
#define KN_TFLM_PRINT_Q7_SIZE(CNTX, BUF, SIZE) (static_cast<void>(0))
#define KN_TFLM_PRINT_Q31_SIZE(CNTX, BUF, SIZE) (static_cast<void>(0))
#define KN_TLFM_PRINT_VR128(VR_IN) (static_cast<void>(0))
#define KN_PRINT_AFLOAT(IN, SIZE) (static_cast<void>(0))
#define KN_PRINT_AFLOAT16(IN, SIZE) (static_cast<void>(0))
#define KN_PRINT_SHAPE(SHAPE) (static_cast<void>(0))
#define KN_PRINTX_VR128(VR_IN) (static_cast<void>(0))
#define KN_PRINT_VR128(VR_IN) (static_cast<void>(0))
#define KN_PRINTX_VR64(VR_IN) (static_cast<void>(0))
#define KN_PRINT_VR64(VR_IN) (static_cast<void>(0))
#define KN_PRINT_VR(X)
#define KN_PRINTX_VR(X)
#define KN_PRINT_FLOAT(IN, SIZE)
#define KN_PRINT_Q8_SIZE(BUF, SIZE)
#define KN_PRINTS(STR)
#endif
#define CHECK_ALIGN_2(ADDR)                                                   \
  do {                                                                        \
    if (((unsigned)ADDR & 0x1) != 0) {                                        \
      printf("not align 2: %s %p %s: %d\n", #ADDR, ADDR, __FILE__, __LINE__); \
    }                                                                         \
  } while (0);
#define CHECK_ALIGN_16(ADDR)                                                   \
  do {                                                                         \
    if (((unsigned)ADDR & 0x7) != 0) {                                         \
      printf("not align 16: %s %p %s: %d\n", #ADDR, ADDR, __FILE__, __LINE__); \
    }                                                                          \
  } while (0);

#define CHECK_ALIGN_4(ADDR)                                                   \
  do {                                                                        \
    if (((unsigned)ADDR & 0x3) != 0) {                                        \
      printf("not align 4: %s %p %s: %d\n", #ADDR, ADDR, __FILE__, __LINE__); \
    }                                                                         \
  } while (0);

#define CHECK_ALIGN_8(ADDR)                                                   \
  do {                                                                        \
    if (((unsigned)ADDR & 0x7) != 0) {                                        \
      printf("not align 8: %s %p %s: %d\n", #ADDR, ADDR, __FILE__, __LINE__); \
    }                                                                         \
  } while (0);

#endif
