
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVL.h"
#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif
//#define AVL_HEMILITE
#define KWIO_DUMP_SELF
#define KN_DEBUG_DUMP_FILE
//#include "P:/AlgoSW/KSP/dmx1a/libs/ksp-common/inc/ksp_types.h"
//#include
//"P:/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Packages/FrontEnd/ksp_frontend/dmx1a/inc/ksp_types.h"

typedef int8_t ksp_int8_t;

typedef int32_t ksp_int32_t;

typedef int16_t ksp_int16_t;

typedef uint8_t ksp_uint8_t;

#if defined(ALGO_USE_VS)  // translate typedef for VQ
#include "Algo.h"
typedef AFLOAT_t AScalar;
typedef AFLOAT_t AScalar;
typedef ACOMPLEX_t AComplex;

typedef SHORT_t int16_t;
typedef INT_t int32_t;
typedef CHAR_t int8_t;
typedef UCHAR_t uint8_t;

//#define AVL_DELTAMAX

#else
//#include "ksp_common.h"
#endif

#include "kwio-dump.h"
int enable_kn_print = 0;
static int skip_dump = 0;
// static FILE *crc_file = NULL;
static char kn_dmp_subfolder[256] = {0};
static int kn_dmp_file_id = 0;
static unsigned int kn_status = 0;
// static unsigned int kn_dmp_componet_offset[KN_DUMP_NUM] = { 0 };

// for mod index translation
// unsigned int kn_dmp_mode_init[KN_DUMP_NUM] = { 0 };
// static unsigned int kn_dmp_mode_base[KN_DUMP_NUM] = { 0 };
static kwio_dmp_mode_st kn_dmp_mode[KN_DUMP_NUM];  // = { 0 };

// static kn_dmp_component kn_dmp_cur = KN_DUMP_NUM;

static const char *kn_dmp_mode_name[KN_DUMP_NUM + 1] = {
    "AGC",        "AEC_PREP",   "BNE",          "COMMON",
    "DELAY_EST",  "DELAY_LINE", "DRC",          "ECHO_SUP",
    "FD_ADAPT",   "FEAT_EXT",   "FFT",          "FILTERBANK",
    "FIR",        "IIR",        "MATH",         "MBC",
    "NN_FORWARD", "NOISE_SUP",  "NOISE_TRK",    "PEQ",
    "PROTO",      "SDE",        "SF",           "SF_BEST",
    "SF_GSC",     "SPX_AEC",    "SPX_AEC_CTRL", "SPX_AEC_FILTER",
    "SPX_MMSE",   "STFT",       "TE",           "TP",
    "VAD",        "VP",         "VP_HELPER",    "VP_CAL",
    "VR_DESIGN",  "VT",         "VT_FEAT",      "VT_DEC",
    "RESET",      "GMM",        "VT_3RDSTAGE",  NULL};
#ifdef ALGO_USE_VS  // use AFloat type
#ifndef TO_DOUBLE
#define TO_DOUBLE(a) a.toDouble()
#endif
#define TO_RAW(a) (unsigned int)a
#define RE(x) x.re
#define IM(x) x.im
#else
// ksp type
#ifndef TO_DOUBLE
#define TO_DOUBLE(a) ((AScalar)a).to_double()
#endif
#define TO_RAW(a) a.raw()
#define RE(x) x.r()
#define IM(x) x.i()

#endif

#define DUMP_2FILE_INT8(FP, OFFSET, DTYPE, BUF, SIZE)     \
  do {                                                    \
    int ii;                                               \
    DTYPE *pDump = (DTYPE *)BUF;                          \
    for (ii = 0; ii < SIZE; ii++) {                       \
      fprintf(FP, "%d (0x%02x)\n", pDump[ii], pDump[ii]); \
    }                                                     \
    fflush(FP);                                           \
  } while (0)
#define DUMP_2FILE_INT8_CTYPE(FP, OFFSET, DTYPE, BUF, SIZE)  \
  do {                                                       \
    int ii;                                                  \
    const int folding_len = 8;                               \
    DTYPE *pDump = (DTYPE *)BUF;                             \
    for (ii = 0; ii < SIZE; ii++) {                          \
      fprintf(FP, "0x%02x%c%c", pDump[ii] & 0xff,            \
              (ii == SIZE - 1) ? ' ' : ',',                  \
              (((ii + 1) % folding_len) == 0) ? '\n' : ' '); \
    }                                                        \
    fflush(FP);                                              \
  } while (0)
#define DUMP_2FILE_INT16(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                 \
    int ii;                                            \
    DTYPE *pDump = (DTYPE *)BUF;                       \
    for (ii = 0; ii < SIZE; ii++) {                    \
      fprintf(FP, "%d\n", pDump[ii]);                  \
    }                                                  \
    fflush(FP);                                        \
  } while (0)
#define DUMP_2FILE_INT32(FP, OFFSET, DTYPE, BUF, SIZE, FMT) \
  do {                                                      \
    int ii;                                                 \
    DTYPE *pDump = (DTYPE *)BUF;                            \
    for (ii = 0; ii < SIZE; ii++) {                         \
      fprintf(FP, FMT "\n", pDump[ii]);                     \
    }                                                       \
    fflush(FP);                                             \
  } while (0)

#define DUMP_2FILE_BIN(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                               \
    int ii;                                          \
    DTYPE *pDump = (DTYPE *)BUF;                     \
    for (ii = 0; ii < SIZE; ii++) {                  \
      DTYPE tmp = pDump[ii];                         \
      fwrite(&tmp, sizeof(DTYPE), 1, FP);            \
    }                                                \
    fflush(FP);                                      \
  } while (0)

#define DUMP_2FILE_INT8_Q7(FP, OFFSET, DTYPE, BUF, SIZE)          \
  do {                                                            \
    int ii;                                                       \
    DTYPE *pDump = (DTYPE *)BUF;                                  \
    const double powQ7 = 128.0f;                                  \
    for (ii = 0; ii < SIZE; ii++) {                               \
      if (dmp_mask & DMP_HEX_INFO)                                \
        fprintf(FP, "%11.10f (%d) \n", (double)pDump[ii] / powQ7, \
                pDump[ii] & 0xff);                                \
      else                                                        \
        fprintf(FP, "%11.10f\n", (double)pDump[ii] / powQ7);      \
    }                                                             \
    fflush(FP);                                                   \
  } while (0)

#define DUMP_2FILE_INT8_Q7_EXP(FP, OFFSET, DTYPE, BUF, SIZE, AEXP)    \
  do {                                                                \
    int ii;                                                           \
    DTYPE *pDump = (DTYPE *)BUF;                                      \
    const double powQ7 = powf(2.0f, -7 + AEXP);                       \
    for (ii = 0; ii < SIZE; ii++) {                                   \
      if (dmp_mask & DMP_HEX_INFO)                                    \
        fprintf(FP, "%11.10f (%02x) %d\n", (double)pDump[ii] * powQ7, \
                pDump[ii] & 0xff, AEXP);                              \
      else                                                            \
        fprintf(FP, "%11.10f\n", (double)pDump[ii] * powQ7);          \
    }                                                                 \
    fflush(FP);                                                       \
  } while (0)

#define DUMP_2FILE_UINT8_Q8_EXP(FP, OFFSET, DTYPE, BUF, SIZE, AEXP)   \
  do {                                                                \
    int ii;                                                           \
    DTYPE *pDump = (DTYPE *)BUF;                                      \
    const double powQ8 = pow(2.0f, -8 + AEXP);                        \
    for (ii = 0; ii < SIZE; ii++) {                                   \
      if (dmp_mask & DMP_HEX_INFO)                                    \
        fprintf(FP, "%11.10f (%02x) %d\n", (double)pDump[ii] * powQ8, \
                pDump[ii] & 0xff, AEXP);                              \
      else                                                            \
        fprintf(FP, "%11.10f\n", (double)pDump[ii] * powQ8);          \
    }                                                                 \
    fflush(FP);                                                       \
  } while (0)

#define DUMP_2FILE_INT32_EXP(FP, OFFSET, DTYPE, BUF, SIZE, AEXP)      \
  do {                                                                \
    int ii;                                                           \
    DTYPE *pDump = (DTYPE *)BUF;                                      \
    const double powQ7 = pow(2.0f, AEXP);                             \
    for (ii = 0; ii < SIZE; ii++) {                                   \
      if (dmp_mask & DMP_HEX_INFO)                                    \
        fprintf(FP, "%11.10f (%08x) %d\n", (double)pDump[ii] * powQ7, \
                pDump[ii], AEXP);                                     \
      else                                                            \
        fprintf(FP, "%11.10f\n", (double)pDump[ii] * powQ7);          \
    }                                                                 \
    fflush(FP);                                                       \
  } while (0)
#define DUMP_2FILE_COMPLEX_IEEE_G(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                          \
    int ii;                                                     \
    DTYPE *pDump = (DTYPE *)BUF;                                \
    for (ii = 0; ii < SIZE; ii++) {                             \
      fprintf(FP, "%g+%gj\n", TO_DOUBLE(RE(pDump[ii])),         \
              TO_DOUBLE(IM(pDump[ii])));                        \
    }                                                           \
    fflush(FP);                                                 \
  } while (0)

#define DUMP_2FILE_COMPLEX_IEEE(FP, OFFSET, DTYPE, BUF, SIZE)     \
  do {                                                            \
    int ii;                                                       \
    DTYPE *pDump = (DTYPE *)BUF;                                  \
    for (ii = 0; ii < SIZE; ii++) {                               \
      fprintf(FP, "%11.10f+%11.10fj\n", TO_DOUBLE(RE(pDump[ii])), \
              TO_DOUBLE(IM(pDump[ii])));                          \
    }                                                             \
    fflush(FP);                                                   \
  } while (0)
#define DUMP_2FILE_COMPLEX_G(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                     \
    int ii;                                                \
    DTYPE *pDump = (DTYPE *)BUF;                           \
    for (ii = 0; ii < SIZE; ii++) {                        \
      AScalar realC, imagC;                                \
      realC = pDump[ii].r();                               \
      imagC = pDump[ii].i();                               \
      fprintf(FP, "%g+%gj\n", TO_DOUBLE(RE(pDump[ii])),    \
              TO_DOUBLE(IM(pDump[ii])));                   \
    }                                                      \
    fflush(FP);                                            \
  } while (0)

#define DUMP_2FILE_2D_COMPLEX_G(FP, OFFSET, DTYPE, BUF, SIZE)          \
  do {                                                                 \
    int ii, jj;                                                        \
    DTYPE **ppDump = (DTYPE **)BUF;                                    \
    fprintf(FP, "[");                                                  \
    for (ii = 0; ii < SIZE; ii++) {                                    \
      fprintf(FP, "[");                                                \
      for (jj = 0; jj < SIZE; jj++) {                                  \
        DTYPE *pDump = ppDump[ii];                                     \
        fprintf(FP, "%g+%gi %c\t", TO_DOUBLE(RE(pDump[jj])),           \
                TO_DOUBLE(IM(pDump[jj])), jj == SIZE - 1 ? ' ' : ','); \
      }                                                                \
      fprintf(FP, "]%c\n", ii == SIZE - 1 ? ' ' : ',');                \
    }                                                                  \
    fprintf(FP, "]\n");                                                \
    fflush(FP);                                                        \
  } while (0)

#define DUMP_2FILE_2D_COMPLEX_SP_G(FP, OFFSET, DTYPE, BUF, SIZE)               \
  do {                                                                         \
    int ii, jj;                                                                \
    DTYPE *ppDump = (DTYPE *)BUF;                                              \
    for (ii = 0; ii < SIZE; ii++) {                                            \
      for (jj = 0; jj < SIZE; jj++) {                                          \
        DTYPE pDump = ppDump[ii * SIZE + jj];                                  \
        fprintf(FP, "[%g+%gj]\t", TO_DOUBLE(RE(pDump)), TO_DOUBLE(IM(pDump))); \
      }                                                                        \
      fprintf(FP, "\n");                                                       \
    }                                                                          \
    fflush(FP);                                                                \
  } while (0)

#define DUMP_2FILE_COMPLEX(FP, OFFSET, DTYPE, BUF, SIZE)          \
  do {                                                            \
    int ii;                                                       \
    DTYPE *pDump = (DTYPE *)BUF;                                  \
    for (ii = 0; ii < SIZE; ii++) {                               \
      fprintf(FP, "%11.10f+%11.10fj\n", TO_DOUBLE(RE(pDump[ii])), \
              TO_DOUBLE(IM(pDump[ii])));                          \
    }                                                             \
    fflush(FP);                                                   \
  } while (0)

#define DUMP_2FILE_COMPLEX_REAL(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                        \
    int ii;                                                   \
    DTYPE *pDump = (DTYPE *)BUF;                              \
    for (ii = 0; ii < SIZE; ii++) {                           \
      fprintf(FP, "%g\n", TO_DOUBLE(RE(pDump[ii])));          \
    }                                                         \
    fflush(FP);                                               \
  } while (0)
#define DUMP_2FILE_COMPLEX_IMAG(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                        \
    int ii;                                                   \
    DTYPE *pDump = (DTYPE *)BUF;                              \
    for (ii = 0; ii < SIZE; ii++) {                           \
      fprintf(FP, "%g\n", TO_DOUBLE(IM(pDump[ii])));          \
    }                                                         \
    fflush(FP);                                               \
  } while (0)
#define DUMP_2FILE_SCALAR_IEEE_G(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                         \
    int ii;                                                    \
    DTYPE *pDump = (DTYPE *)BUF;                               \
    for (ii = 0; ii < SIZE; ii++) {                            \
      fprintf(FP, "%g\n", TO_DOUBLE(pDump[ii]));               \
    }                                                          \
    fflush(FP);                                                \
  } while (0)

#define DUMP_2FILE_SCALAR_IEEE(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                       \
    int ii;                                                  \
    DTYPE *pDump = (DTYPE *)BUF;                             \
    for (ii = 0; ii < SIZE; ii++) {                          \
      fprintf(FP, "%11.10f\n", TO_DOUBLE(pDump[ii]));        \
    }                                                        \
    fflush(FP);                                              \
  } while (0)

#define DUMP_2FILE_SCALAR_IEEE_FLT(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                           \
    int ii;                                                      \
    DTYPE *pDump = (DTYPE *)BUF;                                 \
    for (ii = 0; ii < SIZE; ii++) {                              \
      fprintf(FP, "%11.10f\n", (double)(pDump[ii]));             \
    }                                                            \
    fflush(FP);                                                  \
  } while (0)
// dump G
#define DUMP_2FILE_SCALAR_G(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                    \
    int ii;                                               \
    DTYPE *pDump = (DTYPE *)BUF;                          \
    for (ii = 0; ii < SIZE; ii++) {                       \
      if (DMP_HEX_INFO & dmp_mask)                        \
        fprintf(FP, "%g\n", TO_DOUBLE(pDump[ii]));        \
      else                                                \
        fprintf(FP, "%g\n", TO_DOUBLE(pDump[ii]));        \
    }                                                     \
    fflush(FP);                                           \
  } while (0)

#define DUMP_2FILE_SCALAR(FP, OFFSET, DTYPE, BUF, SIZE)         \
  do {                                                          \
    int ii;                                                     \
    DTYPE *pDump = (DTYPE *)BUF;                                \
    for (ii = 0; ii < SIZE; ii++) {                             \
      if (DMP_HEX_INFO & dmp_mask)                              \
        fprintf(FP, "%11.10f (0x%08x)\n", TO_DOUBLE(pDump[ii]), \
                TO_RAW(pDump[ii]));                             \
      else                                                      \
        fprintf(FP, "%11.10f\n", TO_DOUBLE(pDump[ii]));         \
    }                                                           \
    fflush(FP);                                                 \
  } while (0)

#define DUMP_2FILE_SCALAR_CTYPE(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                                        \
    int ii;                                                   \
    DTYPE *pDump = (DTYPE *)BUF;                              \
    const int folding_len = 4;                                \
    for (ii = 0; ii < SIZE; ii++) {                           \
      fprintf(FP, "EVAL(%10.11f)%c%c", TO_DOUBLE(pDump[ii]),  \
              (ii == SIZE - 1) ? ' ' : ',',                   \
              ((ii + 1) % folding_len) == 0 ? '\n' : ' ');    \
    }                                                         \
    fflush(FP);                                               \
  } while (0)

#define DUMP_2FILE_PCM(FP, OFFSET, DTYPE, BUF, SIZE) \
  do {                                               \
    int ii;                                          \
    DTYPE *pDump = (DTYPE *)BUF;                     \
    for (ii = 0; ii < SIZE; ii++) {                  \
      AScalar pcm_int16;                             \
      ksp_int16_t pcm16;                             \
      pcm_int16 = (AScalar)32768.0f * pDump[ii];     \
      pcm16 = pcm_int16.to_int();                    \
      fwrite(&pcm16, sizeof(ksp_int16_t), 1, FP);    \
    }                                                \
    fflush(FP);                                      \
  } while (0)
// print VR128
double afloat2double(unsigned int &x) {
  double sign;
  int exp;
  int mantissa;
  double out;

  sign = (x & 0x80000000) ? -1 : 1;
  exp = ((x >> 25) & 0x3F) - 31;
  mantissa = x & 0x1FFFFFF;
  if ((exp != -31) || (mantissa != 0)) {
    mantissa |= 0x2000000;
  }

  out = (double)mantissa / 67108864.0;
  out = sign * out * pow(2.0, (double)exp);

  return out;
}

// return non usefull finename
char *buf_to_fn(const char *buf, char *out) {
  // char *p;
  int j = 0;
  for (unsigned int i = 0; i < strlen(buf); i++) {
    if ((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z') ||
        (buf[i] >= '0' && buf[i] <= '9') || buf[i] == '_') {
      out[j] = buf[i];
      j++;
    } else if (buf[i] == '-' || buf[i] == '.') {
      out[j] = '_';
      j++;
    } else if (buf[i] == '[' || buf[i] == ']') {
      // skip [ ]
    }
  }
  out[j] = 0;
  return out;
}
void kn_dmp_set_file_id_offset(int dmp_file_id) {
  kn_dmp_file_id = dmp_file_id;
}
void kn_dmp_set_subfolder(const char *subfolder) {
#ifndef __XTENSA__
  strncpy_s(kn_dmp_subfolder, subfolder, 256);
#else
  strncpy(kn_dmp_subfolder, subfolder, 256);
#endif
}
#ifdef DMX1A
void ConvertQ15ToAfloat(fr32 *output, int16_t *input, int size) {
  // TBD
}
#endif

#ifdef HMD1A
void ConvertQ15ToAfloat(fr32 *output, int16_t *input, int size, int exp) {
  // int loopLim = size>>1;
  vr64 VR_input;
  int16_t *pSrc = input;
  fr32 *pDst = output;
  for (int ii = 0; ii < size; ii++) {
    load16x1_vr_postI(VR_input, pSrc, INC1, VRQ0);
    //     load16x1_vr_postI(VR_input, pSrc, INC1, VRQ0);
    convert_16I_to_32F_x2(VR_input, exp);
    store32x1_vr_postI(VR_input, pDst, INC1, VRQ0);
  }
}
void ConvertQ31ToAfloat(fr32 *output, int32_t *input, int size, int exp) {
  // int loopLim = size>>1;
  vr64 VR_input;
  int32_t *pSrc = input;
  fr32 *pDst = output;
  for (int ii = 0; ii < size; ii++) {
    load32x1_vr_postI(VR_input, pSrc, INC1, VRQ0);
    //     load16x1_vr_postI(VR_input, pSrc, INC1, VRQ0);
    convert_32I_to_32F_x1(VR_input, exp, VRQ0);
    store32x1_vr_postI(VR_input, pDst, INC1, VRQ0);
  }
}
void ConvertQ63ToAfloat(fr32 *output, uint64_t *input, int size, int exp) {
  // int loopLim = size>>1;
  vr64 VR_input;
  uint64_t *pSrc = input;
  fr32 *pDst = output;
  for (int ii = 0; ii < size; ii++) {
    load32x2_vr_postI(VR_input, pSrc, INC1);
    //     load16x1_vr_postI(VR_input, pSrc, INC1, VRQ0);
    convert_32I_to_32F_x1(VR_input, exp, VRQ0);
    store32x1_vr_postI(VR_input, pDst, INC1, VRQ0);
  }
}
#endif
void switch_off_kn_dump() { skip_dump = 1; }
void switch_on_kn_dump() { skip_dump = 0; }
void switch_off_kn_print() {
  enable_kn_print = 0;
  // skip_dump = 1;
}
void switch_on_kn_print() { enable_kn_print = 1; }

int get_kn_print() { return enable_kn_print; }
int get_kn_skip_dump() { return skip_dump; }

// dump file extend
kwio_Dump_st gDump_file[KWIO_DUMP_MAX_IO];
int kn_df(int idx, const char *filename, const void *buf, int size, int type,
          int fixexp, unsigned int dmp_mask, const char *buffer_name,
          const char *func, const unsigned long line) {
  //	int i;
  FILE *fp;
  // AComplex *pFg_filter;
  int type_is_ctype = 0;
  int type_is_bintype = 0;
  static int init_fp = 0;
  // reindex by componet;
  // idx = kn_dmp_cur*16 + kn_dmp_componet_offset[kn_dmp_cur];
  type_is_ctype = (type == KSP_FLOAT_T_C_TYPE || type == KSP_INT8_T_C_TYPE);

  type_is_bintype = (type == KSP_BIN_1BYTE_T || type == KSP_BIN_2BYTE_T ||
                     type == KSP_BIN_4BYTE_T || type == KSP_PCM_T);
  if (skip_dump) {
    gDump_file[idx].idx++;
    gDump_file[idx].offset = size * gDump_file[idx].idx;
    return -3;
  }
  if (!init_fp) {
    memset(gDump_file, 0, sizeof(kwio_Dump_st) * KWIO_DUMP_MAX_IO);
    init_fp = 1;
  }
  idx += kn_dmp_file_id;
  if (idx < 0 || idx > KWIO_DUMP_MAX_IO) {
    fprintf(stderr, "idx error:y %d\n", idx);
    return -1;
  } else if (idx == KWIO_DUMP_MAX_IO) {
    fp = stderr;
    if (dmp_mask & DMP_HEADER_INFO && !type_is_ctype)
      fprintf(fp, "#%s: %ld buf %s: %d pointer: %p type: %d idx: %d\n\n", func,
              line, buffer_name, size, buf, type, idx);

  } else {
    if (gDump_file[idx].file_ptr != NULL) {
      fp = gDump_file[idx].file_ptr;
#ifdef _MSC_VER
      size_t len_func = strlen(gDump_file[idx].func_name);
      size_t len_var = strlen(gDump_file[idx].var_name);
      // do santy check source is from the same function line name
      if (0 != strncmp(gDump_file[idx].func_name, func, len_func) ||
          0 != strncmp(gDump_file[idx].var_name, buffer_name, len_var) ||
          line != gDump_file[idx].line) {
        fprintf(stderr, "dump ERROR: %s/%s/%d\n%s/%s/%d\n",
                gDump_file[idx].func_name, gDump_file[idx].var_name,
                gDump_file[idx].line, func, buffer_name, line);

        //				__debugbreak();
      }
#endif
    } else {
      char fullpath[256];

      // override .txt suffix filename.
      char *suffix = strchr((char *)filename, '.');
      if (suffix) {
        if (type == KSP_BIN_1BYTE_T || type == KSP_BIN_2BYTE_T ||
            type == KSP_BIN_4BYTE_T) {
          suffix[0] = '.';
          suffix[1] = 'b';
          suffix[2] = 'i';
          suffix[3] = 'n';
        }
        // else if
      }
#ifdef _MSC_VER

      _snprintf_s(fullpath, 256, "%s\\%s%s", KWIO_DUMP_PREFIX,
                  kn_dmp_subfolder ? kn_dmp_subfolder : "", filename);
      fopen_s(&fp, fullpath, "wb+");
#else
      snprintf(fullpath, 256, "%s\\%s", KWIO_DUMP_PREFIX, filename);
      fp = fopen(fullpath, "wb+");
#endif
      if (!fp) {
        fprintf(stderr, " cannot open %s for writing!\n", fullpath);
        return -2;
      }
      gDump_file[idx].file_ptr = fp;
      gDump_file[idx].size = size;
#ifdef _MSC_VER
      strncpy_s(gDump_file[idx].var_name, buffer_name, 100);
      strncpy_s(gDump_file[idx].func_name, func, 100);
#else
      strncpy(gDump_file[idx].var_name, buffer_name, 100);
      strncpy(gDump_file[idx].func_name, func, 100);

#endif
      gDump_file[idx].line = line;
      // if ()
      {
        if (dmp_mask & DMP_HEADER_INFO && !type_is_bintype && !type_is_ctype)
          fprintf(fp, "#%s: %ld buf %s: %d pointer: %p type: %d idx: %d\n\n",
                  func, line, buffer_name, size, buf, type, idx);
        else if (type_is_ctype)  // c-type-array table
        {
          char VAR_NAME[16];
          switch (type) {
            case KSP_FLOAT_T_C_TYPE:
              strncpy(VAR_NAME, "uint32_t", 10);
              break;
            case KSP_INT8_T_C_TYPE:
              // VAR_NAME = "unsigned char";
              strncpy(VAR_NAME, "unsigned char", 10);
              break;
            default:
              strncpy(VAR_NAME, "xxx char", 10);
              break;
          }
          fprintf(fp, "VAR_ALIGN_16 static const %s ",
                  VAR_NAME);  // including header
          fprintf(fp, "%s[%d] = { \n", buffer_name, size);
        }
      }
    }
  }
  switch (type) {
#if defined(AVL_DELTPLUS) || defined(AVL_DELTAMAX)
    case KSP_FLOAT_T:
      DUMP_2FILE_SCALAR(fp, gDump_file[idx].offset, AScalar, buf, size);
      break;
    case KSP_COMPLEX_REAL_T:
      DUMP_2FILE_COMPLEX_REAL(fp, gDump_file[idx].offset, AComplex, buf, size);
      break;
    case KSP_COMPLEX_IMAG_T:
      DUMP_2FILE_COMPLEX_IMAG(fp, gDump_file[idx].offset, AComplex, buf, size);
      break;

    case KSP_COMPLEX_T:
      DUMP_2FILE_COMPLEX_G(fp, gDump_file[idx].offset, AComplex, buf, size);
      break;
#define KSP_SPX_AEC_INT_SCALAR (pgKspSpxAecConsts->inScalingFactor)
    case KSP_PCM_T: {
      int ii;
      AScalar *pDump = (AScalar *)buf;
      for (ii = 0; ii < size; ii++) {
        float pcm_int16;
        int pcm32;
        ksp_int16_t pcm16;
        pcm_int16 = (float)32768.0f * TO_DOUBLE(pDump[ii]);  // inscaling factor
        pcm32 = (int)pcm_int16;                              // ();
        if (pcm32 >= 32768)
          pcm32 = 32767;
        else if (pcm32 < -32768)
          pcm32 = -32768;
        pcm16 = (ksp_int16_t)pcm32;
        // fprintf(stderr,"0x")
        // if (fp == stderr)
        //	fprintf(stderr, "%03d 0x[%04x]\n",ii, pcm16);
        // else
        fwrite(&pcm16, sizeof(ksp_int16_t), 1, fp);
      }
    }
    // DUMP_2FILE_PCM(fp, gDump_file[idx].offset, ksp_float_t, buf, size);
    break;

#else  // AVL_GENERIC
    case KSP_FLOAT_T:
      // DUMP_2FILE_SCALAR_IEEE(fp, gDump_file[idx].offset, AScalar, buf, size);
      DUMP_2FILE_SCALAR_IEEE(fp, gDump_file[idx].offset, AScalar, buf, size);
      break;

    case KSP_COMPLEX_REAL_T:
      DUMP_2FILE_COMPLEX_REAL(fp, gDump_file[idx].offset, AComplex, buf, size);
      break;
    case KSP_COMPLEX_IMAG_T:
      DUMP_2FILE_COMPLEX_IMAG(fp, gDump_file[idx].offset, AComplex, buf, size);
      break;

    case KSP_COMPLEX_T:
      DUMP_2FILE_COMPLEX_IEEE(fp, gDump_file[idx].offset, AComplex, buf, size);
      break;
#define KSP_SPX_AEC_INT_SCALAR (pgKspSpxAecConsts->inScalingFactor)
    case KSP_PCM_T:
#if 0
	{
		int ii;
		AScalar *pDump = (AScalar *)buf;
		for (ii = 0; ii < size; ii++) {

			float pcm_int16;
			int pcm32;
			ksp_int16_t pcm16;
			pcm_int16 = (float)32768.0f*pDump[ii]//.to_double() ; //inscaling factor
			pcm32 = (int)pcm_int16;// ();
			if (pcm32 >= 32768) pcm32 = 32767;
			else if (pcm32 < -32768) pcm32 = -32768;
			pcm16 = (ksp_int16_t)pcm32;
			//fprintf(stderr,"0x")
			//if (fp == stderr)
			//	fprintf(stderr, "%03d 0x[%04x]\n",ii, pcm16);
			//else
			fwrite(&pcm16, sizeof(ksp_int16_t), 1, fp);
		}
	}
#endif
      // DUMP_2FILE_PCM(fp, gDump_file[idx].offset, ksp_float_t, buf, size);
      break;

#endif
    case KSP_INT8_T:
      DUMP_2FILE_INT8(fp, gDump_file[idx].offset, ksp_int8_t, buf, size);
      break;
    case KSP_INT16_T:
      DUMP_2FILE_INT16(fp, gDump_file[idx].offset, ksp_int16_t, buf, size);
      break;
    case KSP_INT32_T:
      DUMP_2FILE_INT32(fp, gDump_file[idx].offset, ksp_int32_t, buf, size,
                       "%d");
      break;
      // case KSP_INT8_Q7_T:
      //	DUMP_2FILE_INT8_Q7(fp, gDump_file[idx].offset, ksp_int8_t, buf,
      //size); 	break;
#ifndef AVL_GENERIC
    // case KSP_INT8_Q7_EXP_T:
    //	DUMP_2FILE_INT8_Q7_EXP(fp, gDump_file[idx].offset, ksp_int8_t, buf,
    //size, fixexp); 	break;
    case KSP_UINT8_Q7_EXP_T:
      DUMP_2FILE_UINT8_Q8_EXP(fp, gDump_file[idx].offset, ksp_uint8_t, buf,
                              size, fixexp);
      break;
    case KSP_INT32_EXP_T:
      DUMP_2FILE_INT32_EXP(fp, gDump_file[idx].offset, ksp_int32_t, buf, size,
                           fixexp);
      break;
#endif
    case KSP_IEEE_FLT_T:
      DUMP_2FILE_SCALAR_IEEE_FLT(fp, gDump_file[idx].offset, float, buf, size);
      break;
    case KSP_IEEE_DBL_T:
      DUMP_2FILE_SCALAR_IEEE_FLT(fp, gDump_file[idx].offset, double, buf, size);
      break;
    case KSP_2D_COMPLEX_DP_T:
      DUMP_2FILE_2D_COMPLEX_G(fp, gpDump_file[idx].offset, AComplex, buf, size);
      break;
    case KSP_2D_COMPLEX_SP_T:  // single pointer
      DUMP_2FILE_2D_COMPLEX_SP_G(fp, gpDump_file[idx].offset, AComplex, buf,
                                 size);
      break;
    // case KSP_CRC:
    //	kn_crc(fp, buf, size , buffer_name, func, line );
    //	break;
    case KSP_INT8_T_C_TYPE:
      DUMP_2FILE_INT8_CTYPE(fp, gDump_file[idx].offset, ksp_int8_t, buf, size);
      break;
    case KSP_FLOAT_T_C_TYPE:
      DUMP_2FILE_SCALAR_CTYPE(fp, gDump_file[idx].offset, AScalar, buf, size);
      break;
    case KSP_BIN_4BYTE_T:
      DUMP_2FILE_BIN(fp, gDump_file[idx].offset, int32_t, buf, size);
      break;
    case KSP_BIN_2BYTE_T:
      DUMP_2FILE_BIN(fp, gDump_file[idx].offset, int16_t, buf, size);
      break;
    case KSP_BIN_1BYTE_T:
      DUMP_2FILE_BIN(fp, gDump_file[idx].offset, int8_t, buf, size);
      break;
    case KSP_INT32_HEX_T:
      DUMP_2FILE_INT32(fp, gDump_file[idx].offset, ksp_int32_t, buf, size,
                       "%08x");
      break;
#ifndef AVL_GENERIC
    case KSP_VR_2COMPLEX_T:

    {
      //        VAR_ALIGN_16 AComplex temp_complex[2];
      //      vr128 *vr_tmp = (vr128 *)buf;
      //    store32x4_vr_idxI(*vr_tmp, temp_complex, 0);
      //   fprintf(fp, "%g+%gj\n%g+%gj\n",
      //   temp_complex[0].r().to_double(),temp_complex[0].i().to_double(),
      //      temp_complex[1].r().to_double(), temp_complex[1].i().to_double()
      //      );
    } break;
#endif
    default:
      fprintf(stderr, "unknown type: %d", type);
  }
  gDump_file[idx].idx++;
  gDump_file[idx].offset = size * gDump_file[idx].idx;

  if (type_is_ctype) {
    fprintf(fp, "};// end of %s", buffer_name);
    fflush(fp);
  }
  return 0;
}
#if 0
void kn_crc(FILE* crc_file, const void *buf, int bytes, const char *buf_name, const char *func, const unsigned long line)
{
	if (crc_file == NULL)
	{
#ifdef __XTENSA__
		crc_file = fopen(CRC_FILE_PATH, "wb+");
#else
		 fopen_s(&crc_file, CRC_FILE_PATH, "wb+");
#endif
	}
		if (crc_file)
		{
			fprintf(crc_file, "%-10s:%u => %-20s: %04x (size: %d)\n", func,(unsigned int) line, buf_name,
				crc16_ccitt((unsigned char *)buf, bytes), bytes);
			fflush(crc_file); 
		}
		else {

			fprintf(stderr, "crc error !\n");
		}
}
#endif
void kn_df_close() {
  int i;
  for (i = 0; i < KWIO_DUMP_MAX_IO; i++)
    if (gDump_file[i].file_ptr != NULL) {
      fclose(gDump_file[i].file_ptr);
      gDump_file[i].file_ptr = NULL;
    }
}

int kn_dmp_get_status() { return kn_status; }

int kn_dmp_set_status(unsigned int status) {
  kn_status = status;
  return status;
}

// for debug in a loop
// target offset: dump offset difference place
// step: is a index in a loop
// stride: each iteration increment or decrement
//
int kn_debug_brkpt(int index, int target_offset, int step, int stride) {
  FILE *file_ptr;
  int offset;
  int up_offset, dn_offset;

  if (gDump_file[index].file_ptr == NULL) return -1;
  file_ptr = gDump_file[index].file_ptr;

  offset = gDump_file[index].offset;
  dn_offset = offset + stride * (step);
  up_offset = offset + stride * (step + 1);
  if (target_offset >= dn_offset && target_offset < up_offset) {
#ifdef _MSC_VER
    printf("stop! frm offset: %d\n", target_offset - offset);
    __debugbreak();
#endif
    return 1;
  }
  return 0;
}

// static int mode_stack[KN_DUMP_MODE_STACK_MAX] = { -1 };
int mode_stack_idx = -1;
static int push_mode(int mode, int index, void *buf_ptr, int line) {
  if (mode_stack_idx < KN_DUMP_NUM - 1) {
    mode_stack_idx++;
    kn_dmp_mode[mode_stack_idx].mod = mode;
    kn_dmp_mode[mode_stack_idx].index = index;
    kn_dmp_mode[mode_stack_idx].buf_ptr[0] = buf_ptr;
    kn_dmp_mode[mode_stack_idx].line[0] = line;

    // mode_stack[++mode_stack_idx] = mode;
  } else {
    // stack overflow!!
    fprintf(stderr, "stack overflow in mode: %d buf:%p line:%d\n", mode,
            buf_ptr, line);
    return -1;
  }
  return mode;
}

static int pop_mode(int mode) {
  // int mode = kn_dmp_mode[mode_stack_idx].mod;
  // keep pop the same mode from stack
  if (mode_stack_idx < 0) {
    fprintf(stderr, "stack under flow!\n");
  } else {
    for (int i = mode_stack_idx; i >= 0; i--) {
      kwio_dmp_mode_st *kn_dmp_cur = &kn_dmp_mode[i];

      if (mode == kn_dmp_cur->mod) {
        // make stack empty -1
        kn_dmp_mode[mode_stack_idx].mod = -1;
        for (int j = 0; j < KN_DUMP_MODE_MAX; j++) {
          kn_dmp_mode[mode_stack_idx].buf_ptr[j] = NULL;
          kn_dmp_mode[mode_stack_idx].line[j] = -1;
        }
        kn_dmp_mode[mode_stack_idx].index = -1;
        mode_stack_idx--;  // -1 at most
      }
    }
  }
  return mode;
}
static kwio_dmp_mode_st *get_kn_mode() {
  return mode_stack_idx >= 0 ? &kn_dmp_mode[mode_stack_idx] : NULL;
}
void kn_set_end_of_dmp()  // to reinit it
{
  // clean all line info
  kwio_dmp_mode_st *kn_dmp_cur = get_kn_mode();

  // for (int i = 0; i < KN_DUMP_MODE_MAX; i++)// reinit line number list to
  // next entry make index 	kn_dmp_mode[kn_dmp_cur].line[i] = 0;
  if (kn_dmp_cur) pop_mode(kn_dmp_cur->mod);
}
#ifndef __XTENSA__
#include <strsafe.h>
#include <tchar.h>
#include <windows.h>

#include "atlstr.h"
#endif
// wrapper to auto gen index and filename
int kn_df2(kn_dmp_component mod, void *buf, const char *buf_name, int size,
           int dtype, int aexp, const char *func, unsigned long line) {
  int idx_mod = 0;

  static int init_stack = 0;
  if (skip_dump) {
    // gDump_file[idx].idx++;
    // gDump_file[idx].offset = size* gDump_file[idx].idx;
    return -3;
  }
  if (!init_stack) {
    // push empty num
    // for (int i = 0; i < KN_DUMP_MODE_STACK_MAX; i++)
    //	mode_stack[i] = -1;
    init_stack = 1;
  }
  if (buf == NULL) {
    fprintf(stderr, "[+] cannot dump %s NULL ptr\n", buf_name);
    return -1;
  }
  kwio_dmp_mode_st *kn_dmp_cur = get_kn_mode();
  int MODE_DEBUG = 2;
  if (kn_dmp_cur == NULL || kn_dmp_cur->mod != (int)mod) {
    push_mode(mod, 0, buf, line);

    kn_dmp_cur = get_kn_mode();
    idx_mod = mod * KN_DUMP_MODE_MAX;
    MODE_DEBUG = 1;
  } else {
    MODE_DEBUG = 0;
    int found = 0;
    int dmp_idx = -1;
    kn_dmp_cur->mod = mod;
    //	kn_dmp_cur->mode_debug[dmp_idx] = 0;
    idx_mod =
        mod * KN_DUMP_MODE_MAX + kn_dmp_cur->index;  // kn_dmp_mode[mod].index;
    // if (gDump_file[idx_mod].file_ptr != NULL) // a index

    {
      //	int line_in_gf = gDump_file[idx_mod].line;
      // for (int i = mode_stack_idx; i >= 0; i--) // traferse
      for (int i = 0; i < KN_DUMP_MODE_MAX; i++) {
        //	kwio_dmp_mode_st *kn_dmp_trav = &kn_dmp_mode[i];
        if (kn_dmp_cur->line[i] == line
            //			&& //same line same pointer using same file,
            // kn_dmp_cur->buf_ptr[i] == buf // has exist in file
            // && (kn_dmp_trav->mod == mod)
            && (gDump_file[mod * KN_DUMP_MODE_MAX + i].file_ptr !=
                NULL))  // find the same mode in the stack
        {
          found = 1;
          dmp_idx = i;
          break;
        }
      }
    }
    if (!found)  // not found go next
    {
      kn_dmp_cur->index += 1;
      kn_dmp_cur->line[kn_dmp_cur->index] = line;
      kn_dmp_cur->buf_ptr[kn_dmp_cur->index] = buf;
      idx_mod = mod * KN_DUMP_MODE_MAX + kn_dmp_cur->index;
    } else {
      idx_mod = mod * KN_DUMP_MODE_MAX + dmp_idx;
    }
  }

  char filename[100];
  char buf2[100];
  if (kn_dmp_cur->index >= KN_DUMP_MODE_MAX) {
    fprintf(stderr,
            "%s exceed maximum index number line: %d index: %d mod_debug: %d\n",
            buf_name, kn_dmp_cur->line[0], kn_dmp_cur->index, MODE_DEBUG);
    for (int kk = 0; kk < KN_DUMP_MODE_MAX; kk++) {
      fprintf(stderr, "%d kn_dump_cur->line %d %p\n", kk, kn_dmp_cur->line[kk],
              kn_dmp_cur->buf_ptr[kk]);
    }
    //__debugbreak();
    return -1;
  }
#ifndef __XTENSA__  // create DIR only
  USES_CONVERSION;
  // check exstience of directory, and create dir
  TCHAR newPath[100];
  TCHAR szName[100];
  _tcscpy_s(szName, A2T(kn_dmp_mode_name[mod]));

  StringCchPrintf(newPath, sizeof(newPath) / sizeof(newPath[0]), TEXT("%s%s"),
                  TEXT(KWIO_DUMP_PREFIX), szName);
  //_sntprintf_s(newPath, 100, 100, "%s%s",
  //KWIO_DUMP_PREFIX,kn_dmp_mode_name[mod] );
  if (GetFileAttributes((newPath)) == INVALID_FILE_ATTRIBUTES) {
    BOOL ret = CreateDirectory((LPCTSTR)newPath, NULL);
  }

  _snprintf_s(filename, 100, "%s\\%02d_%s.txt", kn_dmp_mode_name[mod],
              kn_dmp_cur->index, buf_to_fn(buf_name, buf2));
#else
  snprintf(filename, 100, "%s\\%02d_%s.txt", kn_dmp_mode_name[mod],
           kn_dmp_cur->index, buf_to_fn(buf_name, buf2));

#endif
  // fprintf(stderr, "%s %s @ idx: %d \n",filename,  buf_name, idx_mod);
  kn_df(idx_mod, filename, buf, size, dtype, aexp, 1, buf_name, func, line);

  return 0;
}
int kn_debug_on_frm(int index, int target_offset_dn,
                    int target_offset_up)  //, int step, int stride)
{
  FILE *file_ptr;
  int offset;
  //	int up_offset, dn_offset;

  if (gDump_file[index].file_ptr == NULL) return -1;
  file_ptr = gDump_file[index].file_ptr;

  offset = gDump_file[index].offset;
  //	dn_offset = offset; //+stride*(step);
  //	up_offset = offset + gDump_file[index].size; // +stride*(step + 1);
  if (offset >= target_offset_dn && offset < target_offset_up) {
    switch_on_kn_dump();
    return 1;
  } else {
    switch_off_kn_dump();
    return 0;
  }
  return 0;
}

/*
 * Copyright 2001-2010 Georges Menie (www.menie.org)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of California, Berkeley nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright 2001-2010 Georges Menie (www.menie.org)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of California, Berkeley nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if 0


/* CRC16 implementation acording to CCITT standards */

static const unsigned short crc16tab[256] = {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

unsigned short crc16_ccitt(const unsigned char *buf, int len)
{
	 int counter;
	 unsigned short crc = 0;
	if (NULL == buf)
		return 0x7788;

	for (counter = 0; counter < len; counter++)
		crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ *(char *)buf++) & 0x00FF];
	return crc;
}

#define RMUL 1664525
#define RINC 1013904223
static int32_t globalRandSeed = 0;

#define AFLOAT_NEG_ONE ((fr32)(0xC0000000))
#define AFLOAT_ONE ((fr32)(0x40000000))
static int32_t RandQ31()
{
	globalRandSeed = globalRandSeed * RMUL + RINC;
	return (globalRandSeed & 0x7FFFFFFF);
}

static fr32 RandAfloat()
{
	int32_t iRand = RandQ31();
	vr128 VR_rand;

	WUR_JammingBit(JAMMING);
	replicate_ar(VR_rand, 1, iRand);
	convert_32I_to_32F_x1(VR_rand, 0, VRQ0);
	return get_VRQ0(VR_rand);
}

static fr32 RandAfloatRange(fr32 min, fr32 max)
{
	uint32_t rand = (uint32_t)move_ar_fr(RandAfloat());
	vr128 VR_Tmp;

	WUR_JammingBit(JAMMING);
	replicate_ar(VR_Tmp, 8, rand);

	// Calculate the span.
	replicate_ar(VR_Tmp, 1, move_ar_fr(min));
	replicate_ar(VR_Tmp, 4, move_ar_fr(max));
	fadds(VR_Tmp, VRQ1, VR_Tmp, VRQ2, VR_Tmp, VRQ0, 0x10);

	//FIX: this multiplication costs us precision in the final byte that in
	//turn reduces our randomness.  Figure out how to fill that vacancy.
	// Multiply our random Afloat by the span, then add it to the base.
	fmacs(VR_Tmp, VRQ0, VR_Tmp, VRQ3, VR_Tmp, VRQ1, 0);
	replicate_ar(VR_Tmp, 8, move_ar_fr(min));
	fclamp(VR_Tmp, VRQ0, VR_Tmp, VRQ3, VR_Tmp, VRQ2);
	return get_VRQ0(VR_Tmp);
}

int random_afloat(void *pIn, int size)
{
	fr32 *pInAflt = (fr32 *)pIn;
	for (int i = 0; i < size; i++)
	{
		pInAflt[i] = RandAfloatRange(AFLOAT_NEG_ONE, AFLOAT_ONE);
	}
	return 0;
}
#endif
