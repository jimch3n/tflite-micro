#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <math.h>

#if defined(DMX1A) || defined(HMD1A)
#include "AVL.h"
#endif
// macro to dump/read from binary
#define KN_READ_FP(FILENAME, BUF, DATA_SIZE, ELE_SIZE)do {\
    FILE *fp = fopen(FILENAME, "rb");\
    if (NULL == fp) {\
    	printf( " cannot open %s for read\n", FILENAME);\
    break;\
    }\
    int elemSize = fread(BUF, DATA_SIZE, ELE_SIZE, fp);\
    if(elemSize != ELE_SIZE){\
    	printf("read size error: return: %d input: %d dsize: %d\n",\
elemSize, ELE_SIZE, DATA_SIZE);\
    break;\
        }\
    fclose(fp);\
}while(0)

#define KN_WRITE_FP(FILENAME, BUF,   DATA_SIZE, ELE_SIZE)do {\
    FILE *fp = fopen(FILENAME, "wb");\
    if (NULL == fp) {\
            printf( " cannot open %s for write\n", FILENAME);\
    break;\
    }\
    int elemSize = fwrite(BUF, DATA_SIZE, ELE_SIZE, fp);\
    if(elemSize != ELE_SIZE){\
    	printf("read size error: %d\n", elemSize);\
    break;\
        }\
    fclose(fp);\
}while(0)
#ifdef __cplusplus
extern "C" {
#endif

	enum {
		KSP_DUMP_MATH = 0, // common
		KSP_DUMP_SPX_AEC = 70,
		KSP_DUMP_SPX_AEC_FILTER = 80,
		KSP_DUMP_SPX_AEC_CTRL = 90,

	};
	enum {
		DMP_HEADER_INFO = 1,
		DMP_HEX_INFO = 2,
		DMP_PURE_FLOAT = 4
	};

typedef	enum {
		KN_DUMP_AGC = 0,
KN_DUMP_AEC_PREP,
KN_DUMP_BNE,
KN_DUMP_COMMON,
KN_DUMP_DELAY_EST,
KN_DUMP_DELAY_LINE,
KN_DUMP_DRC,
KN_DUMP_ECHO_SUP,
KN_DUMP_FD_ADAPT,
KN_DUMP_FEAT_EXT,
KN_DUMP_FFT,
KN_DUMP_FILTERBANK,
KN_DUMP_FIR,
KN_DUMP_IIR,
KN_DUMP_MATH,
KN_DUMP_MBC,
KN_DUMP_NN_FORWARD,
KN_DUMP_NOISE_SUP,
KN_DUMP_NOISE_TRK,
KN_DUMP_PEQ,
KN_DUMP_PROTO,
KN_DUMP_SDE,
KN_DUMP_SF,
KN_DUMP_SF_BEST,
KN_DUMP_SF_GSC,
KN_DUMP_SPX_AEC,
KN_DUMP_SPX_AEC_CTRL,
KN_DUMP_SPX_AEC_FILTER,
KN_DUMP_SPX_MMSE,
KN_DUMP_STFT,
KN_DUMP_TP_ENH,
KN_DUMP_TP_PRESENCE,
KN_DUMP_VAD,
KN_DUMP_VP,
KN_DUMP_VP_HELPER,
KN_DUMP_VP_CAL,
KN_DUMP_VP_DESIGN,
KN_DUMP_VT,
KN_DUMP_VT_FEATURE,
KN_DUMP_VT_DECODER,
KN_DUMP_RESET, // reset special
KN_DUMP_GMM,
KN_DUMP_VT_VID3RDSTAGE,
KN_DUMP_NUM // keep_last_one
}kn_dmp_component;

#define KN_DUMP_MODE_MAX (40) // each dump number
#define KN_DUMP_MODE_STACK_MAX 100
#ifdef __XTENSA__
#define CRC_FILE_PATH "D:\\temp\\xt_crc.txt"
#else
#define CRC_FILE_PATH "D:\\temp\\msvc_crc.txt"
#endif
#ifdef _MSC_VER
#if !defined(AVL_GENERIC)
#define KWIO_DUMP_PREFIX "D:\\temp\\DMX\\"

#else
#define KWIO_DUMP_PREFIX "D:\\temp\\AScalar\\"
#endif
#else
#ifdef DMX1A
#define KWIO_DUMP_PREFIX "D:\\temp\\xtensa\\"
#endif
#ifdef HMD1A
#define KWIO_DUMP_PREFIX "D:\\temp\\xtensa_hmd\\"
#endif

#endif
#define KWIO_DUMP_MAX_IO (KN_DUMP_NUM*KN_DUMP_MODE_MAX) // each componet has 16 i/o




#if defined(KN_DEBUG_DUMP_FILE) //&& !defined(__XTENSA__) //&& !defined(_DEBUG)
#define KN_DUMP(IDX, FILENAME, BUF, SIZE, DTYPE) do { \
int ret = kn_df(IDX,\
FILENAME,\
BUF,\
SIZE,\
DTYPE,\
0,\
0xFFFFFFFF,\
#BUF,\
__FUNCTION__,\
__LINE__);\
}while(0)

#define KN_DUMP2(IDX, FILENAME, BUF, SIZE, AEXP, DTYPE) do { \
int ret = kn_df(IDX,\
FILENAME,\
BUF,\
SIZE,\
DTYPE,\
AEXP,\
0xFFFFFFFF,\
#BUF,\
__FUNCTION__,\
__LINE__);\
}while(0)

#define KN_DUMP3(IDX, FILENAME, BUF, SIZE, AEXP, MASK, DTYPE) do { \
kn_df(IDX,\
FILENAME,\
BUF,\
SIZE,\
DTYPE,\
AEXP,\
1,\
#BUF,\
__FUNCTION__,\
__LINE__);\
}while(0)
#define KN_DUMP4_VR128_COMPLEX(MOD, VR_BUF) do { \
	VAR_ALIGN_16 ksp_int32_t a##VR_BUF[4];\
	store32x4_vr_idxI(VR_BUF,a##VR_BUF, 0);\
	kn_df2(MOD,\
		a##VR_BUF, #VR_BUF,\
		2, 0, KSP_COMPLEX_T, 0,\
		__FUNCTION__, __LINE__);\
}while(0)

#define KN_DUMP4(MOD, BUF, SIZE, DTYPE) do { \
	kn_df2(MOD,\
	(void *)BUF, #BUF,\
		SIZE, DTYPE , 0,\
		__FUNCTION__, __LINE__);\
}while(0)

#define KN_DUMP6_CRC(MOD, BUF, ALIAS_BUF, SIZE, DTYPE) do { \
void *ALIAS_BUF = (void *)BUF;\
kn_df2(MOD,\
	(void *)ALIAS_BUF, #ALIAS_BUF,\
		SIZE*sizeof(BUF[0]), KSP_CRC , 0,\
		__FUNCTION__, __LINE__);\
}while(0)

#define KN_DUMP6(MOD, BUF, ALIAS_BUF, SIZE, DTYPE) do { \
	void *ALIAS_BUF = (void *)BUF;\
kn_df2(MOD,\
	(void *)ALIAS_BUF, #ALIAS_BUF,\
		SIZE, DTYPE , 0,\
		__FUNCTION__, __LINE__);\
}while(0)
#define KN_DUMP4_CRC(MOD, BUF, SIZE, DTYPE) do { \
	kn_df2(MOD,\
	(void *)BUF, #BUF,\
		SIZE*sizeof(BUF[0]), KSP_CRC , 0,\
		__FUNCTION__, __LINE__);\
}while(0)
#define KN_DUMP5(MOD, BUF, SIZE, AEXP, DTYPE) do { \
	kn_df2(MOD,\
	(void *)BUF, #BUF,\
		SIZE, DTYPE , AEXP,\
		__FUNCTION__, __LINE__);\
}while(0)

//#define KN_CRC(BUF,BYTE_SIZE) do {\
//	kn_crc(BUF, BYTE_SIZE, #BUF, __FUNCTION__, __LINE__);\
//}while(0)
#define KN_DUMP_VR_Q7_EXP_T(F_IDX, FILE_NAME, VR_INPUT, EXPA) do{\
VAR_ALIGN_16 AScalar tmp16[4];\
AScalar *pt = tmp16;\
store32x4_vr_idxI(VR_INPUT, pt, 0); \
KN_DUMP3(F_IDX, FILE_NAME, &tmp16, 16, EXPA, 0x0, KSP_INT8_Q7_EXP_T);\
}while(0)


#define KN_DUMP_VR16X1_Q7_EXP_T(F_IDX, FILE_NAME, VR_INPUT, EXPA) do{\
VAR_ALIGN_16 AScalar tmp16[4];\
AScalar *pt = tmp16;\
store16x1_vr_idxI(VR_INPUT, pt, 0, VRQ0); \
KN_DUMP3(F_IDX, FILE_NAME, &tmp16, 2, EXPA, 0x0, KSP_INT8_Q7_EXP_T);\
}while(0)

#define KN_DUMP_VR_ACC_EXP_T(F_IDX, FILE_NAME, VR_ACC, VR_EXT_ACC, EXPA) do{\
VAR_ALIGN_16 AScalar tmp_acc[4];\
AScalar *pt = tmp_acc;\
store32x4_vr_idxI(VR_ACC, pt, 0); \
KN_DUMP3(F_IDX, FILE_NAME, &tmp_acc, 4, -7+EXPA, 0, KSP_INT32_EXP_T);\
VR_EXT_ACC = mov_vr_AccExtend();\
store32x4_vr_idxI(VR_EXT_ACC, pt, 0); \
KN_DUMP3(F_IDX, FILE_NAME, &tmp_acc, 4, -7+EXPA, 0, KSP_INT32_EXP_T);\
}while(0)

#define KN_PRINT_ON(X) do{\
    (X != 0 )? switch_on_kn_print(): switch_off_kn_print();\
}while(0)

#define KN_DUMP_ON(X) do{ \
	if(X)\
	switch_on_kn_dump();\
	else\
	switch_off_kn_dump();\
 }while(0) // null
//#define KN_DUMP_OFF() do{ switch_off_kn_dump(); }while(0) // null
#define KN_DUMP_END() do {\
kn_set_end_of_dmp();\
}while(0)

#else

#define KN_DUMP(IDX, FILENAME, BUF, SIZE, DTYPE)
#define KN_DUMP2(IDX, FILENAME, BUF, SIZE, AEXP, DTYPE) 
#define KN_DUMP3(IDX, FILENAME, BUF, SIZE, AEXP, MASK, DTYPE)
#define KN_DUMP4(MOD, BUF, SIZE, DTYPE)
#define KN_DUMP6_CRC(MOD, BUF, ALIAS_BUF, SIZE, DTYPE) 
#define KN_DUMP6(MOD, BUF, ALIAS_BUF, SIZE, DTYPE)
#define KN_DUMP4_CRC(MOD, BUF, SIZE, DTYPE)
#define KN_DUMP4_VR(MOD, BUF, SIZE, DTYPE)
#define KN_DUMP5(MOD, BUF, SIZE, AEXP, DTYPE) 
#define KN_DUMP_VR_Q7_EXP_T(F_IDX, FILE_NAME, VR_INPUT, EXPA)
#define KN_DUMP_VR16X1_Q7_EXP_T(F_IDX, FILE_NAME, VR_INPUT, EXPA)
#define KN_DUMP_VR_ACC_EXP_T(F_IDX, FILE_NAME, VR_ACC, VR_EXT_ACC, EXPA)
#define KN_CRC(BUF,BYTE_SIZE)
#define KN_DUMP_ON(X)
#define KN_DUMP_END()
//#define kn_debug_on_frm(index, target_offset_dn, target_offset_up)

//#define kn_set_end_of_dmp(X)
#endif

#if defined( KN_DEBUG_PRINT) //&& !defined(__XTENSA__)
//#ifndef TO_DOUBLE

//#define TO_DOUBLE(X) (X).to_double()

//#endif

#define KN_PRINT_VR128_CC(VR_IN) do{\
if(get_kn_print())\
{\
	VAR_ALIGN_16 AScalar temp_dmp[4];\
	store32x4_vr_idxI(VR_IN, temp_dmp, 0);\
	printf("%-16s: %d\t0: %.11f\t1: %.11f\t2: %.11f\t3: %.11f\n", \
    #VR_IN, __LINE__, AScalar(temp_dmp[0]).to_double(),\
    AScalar(temp_dmp[1]).to_double(),\
    AScalar(temp_dmp[2]).to_double(),\
    AScalar(temp_dmp[3]).to_double());\
}\
}while(0)

#define KN_PRINT_VR128(VR_IN) do {\
	VAR_ALIGN_16 AScalar temp_dmp[4];\
	store32x4_vr_idxI(VR_IN, temp_dmp, 0);\
	printf("%-16s: %d\t0: %.11f\t1: %.11f\t2: %.11f\t3: %.11f\n", \
    #VR_IN, __LINE__, AScalar(temp_dmp[0]).to_double(),\
AScalar(temp_dmp[1]).to_double(),\
AScalar(temp_dmp[2]).to_double(),\
AScalar(temp_dmp[3]).to_double());\
}while(0)

// for those has no ksp_type_t to conversion double
#define KN_PRINT_VR128X(VR_IN, PREFIX) do {\
	VAR_ALIGN_16 int temp_dmp[4];\
	vr128 VR_tmp2 = mv_VR(VR_IN);\
	VAR_ALIGN_16 float tmp_float[4];\
	store32x4_vr_idxI(VR_IN, temp_dmp, 0);\
	convert_32F_to_IEEE_float_x4(VR_tmp2);\
	store32x4_vr_idxI(VR_tmp2, tmp_float, 0);\
	printf("%-10s %-10s: %d\n0: %.10f[0x%08x] \t1: %.10f[0x%08x]\n2: %.10f[0x%08x]\t3: %.10f[0x%08x]\n", \
    PREFIX, #VR_IN, __LINE__, tmp_float[0],temp_dmp[0],\
tmp_float[1],temp_dmp[1],\
tmp_float[2],temp_dmp[2],\
tmp_float[3],temp_dmp[3]);\
}while(0)

#define KN_PRINT_VR128X_IDX(VR_IN, PREFIX, IDX) do {\
	VAR_ALIGN_16 int temp_dmp[4];\
    int index = IDX;\
	vr128 VR_tmp2 = mv_VR(VR_IN);\
	VAR_ALIGN_16 float tmp_float[4];\
	store32x4_vr_idxI(VR_IN, temp_dmp, 0);\
	convert_32F_to_IEEE_float_x4(VR_tmp2);\
	store32x4_vr_idxI(VR_tmp2, tmp_float, 0);\
    if( index < 4  && index >= 0){\
	printf("%-10s %-10s: %d\n%d: %.10f[0x%08x] \n", \
    PREFIX, #VR_IN, __LINE__, IDX, tmp_float[IDX], temp_dmp[IDX]);\
    }\
}while(0)

#define KN_PRINT_VR64X(VR_IN, PREFIX) do {\
	VAR_ALIGN_16 int temp_dmp[4];\
	vr64 VR_tmp2 = mv_VR(VR_IN);\
	VAR_ALIGN_16 float tmp_float[4];\
	store32x2_vr_idxI(VR_IN, temp_dmp, 0);\
	convert_32F_to_IEEE_float_x2(VR_tmp2);\
	store32x2_vr_idxI(VR_tmp2, tmp_float, 0);\
	printf("%-10s %-10s: %d\n0: %.10f[0x%08x] \t1: %.10f[0x%08x]\n", \
    PREFIX, #VR_IN, __LINE__, tmp_float[0],temp_dmp[0],\
tmp_float[1],temp_dmp[1]);\
}while(0)


#define KN_PRINT_FR32X(VR_IN, PREFIX) do {\
	VAR_ALIGN_16 int temp_dmp[4];\
	vr64 VR_tmp2;\
	set_VRL(VR_tmp2, VR_IN);\
	VAR_ALIGN_16 float tmp_float[4];\
	store32x2_vr_idxI(VR_tmp2, temp_dmp, 0);\
	convert_32F_to_IEEE_float_x2(VR_tmp2);\
	store32x2_vr_idxI(VR_tmp2, tmp_float, 0);\
	printf("%-10s %-10s: %d\n0: %.10f[0x%08x]\n", \
    PREFIX, #VR_IN, __LINE__, tmp_float[0],temp_dmp[0]);\
}while(0)

#define KN_PRINT_Q15_EXP(I32, EXP) do {\
	printf("%-8s: %3.6f M: 0x%02x Q: %d %s:%d\n",\
    #I32,  (float)I32*pow(2.0f, -15+EXP), I32, EXP, __FUNCTION__, __LINE__);\
}while(0)
#define KN_PRINT_VR64(VR_IN) do {\
	vr64 Tmp;\
	Tmp = mv_VR(VR_IN);\
	convert_32F_to_IEEE_float_x2(Tmp);\
	VAR_ALIGN_16 float temp_dmp[4];\
	store32x2_vr_idxI(Tmp, temp_dmp, 0);\
	printf("%-12s: %4d\t0: %g (%08x)\t1: %g (%08x)\n", \
    #VR_IN, __LINE__, temp_dmp[0],*(uint32_t *) &temp_dmp[0],\
		temp_dmp[1], *(uint32_t *)&temp_dmp[1]);\
}while(0)

	// afloat print
#define KN_PRINT(BUF, SIZE, DTYPE) do { \
	int ret = kn_df(KWIO_DUMP_MAX_IO,\
"XXX_out",\
BUF,\
SIZE,\
DTYPE,\
0x1,\
0xFFFFFFFF,\
#BUF,\
__FUNCTION__,\
__LINE__);\
}while(0)

#define KN_PRINT_VR_Q7(VR_X, EXP) do {\
	__declspec(align(16)) int tmp_buf[4];\
	int qq;\
	store32x4_vr_idxI(VR_X, tmp_buf, 0);\
	for(qq = 0;qq < 4; qq++){\
	printf("%s[%d]: %f M: %x Q: %d %s:%d\n",\
    #VR_X, qq, (float)tmp_buf[qq]*pow(2.0f, -7+EXP), tmp_buf[qq], EXP,\
    __FUNCTION__, __LINE__);\
}\
}while(0)

#define KN_PRINT_VR_Q7_8x8(VR_X, EXP) do {\
	__declspec(align(16)) int tmp_buf[4];\
	int i,j;\
	store32x4_vr_idxI(VR_X, tmp_buf, 0);\
	for(i = 0; i < 4; i++){\
		int tmp8 = tmp_buf[i]; \
		for(j = 0; j < 4; j++){\
			char tt = (char)(tmp8 >> (j*8));\
			printf("%-8s[%-2d]: %3.6f M: 0x%02x Q: %d %s:%d\n",\
           #VR_X, 4*i+j, (float)tt*pow(2.0f, -7+EXP),tt&0xff, EXP,\
              __FUNCTION__, __LINE__);\
	}\
}\
}while(0)
#define KN_PRINT_VR_Q8_8x8(VR_X, EXP) do {\
	__declspec(align(16)) int tmp_buf[4];\
	int i,j;\
	store32x4_vr_idxI(VR_X, tmp_buf, 0);\
	for(i = 0; i < 4; i++){\
		int tmp8 = tmp_buf[i]; \
		for(j = 0; j < 4; j++){\
			char tt = (char)(tmp8 >> (j*8));\
			printf("%-8s[%-2d]: %3.6f M: 0x%02x Q: %d %s:%d\n",\
           #VR_X, 4*i+j, (float)tt*pow(2.0f, -8+EXP),tt&0xff, EXP,\
              __FUNCTION__, __LINE__);\
	}\
}\
}while(0)
//// HIFI AE////
#define KN_PRINT_AE64Q_X(AE_IN,QEXP) do {\
	VAR_ALIGN_16 int temp_dmp[4];\
    int64_t INT64 = AE_IN;\
    double FLT_OUT = powf(2.0f,QEXP)*float(INT64);\
	AE_S64_I(AE_IN, (ae_int64 *)temp_dmp, 0);\
	printf("%s: %d\t0: [0x%08x%08x]\t1: %g\n", \
    #AE_IN, __LINE__, temp_dmp[0], temp_dmp[1], FLT_OUT);\
}while(0)

#define KN_PRINTF_F(A) do {\
	AScalar aflt = (AScalar)A;\
   fprintf(stdout,"%s: %f @%s:%d\n",#A,aflt.to_double(),__FUNCTION__, __LINE__);\
}while(0)

#define KN_PRINTF_F_SIZE(A, SIZE) do {\
if(A== NULL )break;\
	int i;\
	for(i = 0; i < SIZE; i ++){\
		AScalar aflt = (AScalar)*(A+i);\
		fprintf(stdout,"%s [%d]: %11.10f\n",#A,i, aflt.to_double());\
	}\
}while(0)
#define KN_PRINTF_C_SIZE(A, SIZE) do {\
if(A== NULL )break;\
	unsigned int i;\
	for(i = 0; i < SIZE; i ++){\
		ksp_complex_reg_t aflt = (ksp_complex_reg_t)*(A+i);\
		fprintf(stdout,"%s [%d]: %f+%fj\n",#A,i, aflt.r().to_double(), aflt.i().to_double());\
	}\
}while(0)
#define KN_PRINTF_I(A) do {\
   fprintf(stdout,"%s : %6d (0x%08x) line: %d\n",#A,A,A,__LINE__);\
}while(0)
#define KN_PRINTF_I8(A) do {\
   fprintf(stdout,"%s : %6d (0x%02x) line: %d\n",#A,A,A&0xff,__LINE__);\
}while(0)

#define KN_PRINTF_IX(A, PREFIX) do {\
   fprintf(stdout,"%s : %s %6d (0x%08x) line: %d\n",#A,PREFIX, A,A,__LINE__);\
}while(0)
#define KN_PRINTF_I8_SIZE(A,SIZE) do {\
if(A== NULL )break;\
	for(int i = 0; i < SIZE; i++){\
	if(((ksp_int8_t*)A+i) != NULL){\
	ksp_int8_t a = *((ksp_int8_t *)A+i);\
   fprintf(stdout,"%s[%d]: %d\n",#A,i, a);\
}\
}\
}while(0)
#define KN_PRINTF_I32_SIZE(A,SIZE) do {\
if(A== NULL )break;\
	for(int i = 0; i < SIZE; i++){\
	if(((ksp_int32_t*)A+i) != NULL){\
	ksp_int32_t a = *((int32_t*)A+i);\
   fprintf(stdout,"%s[%d]: %d\n",#A,i, a);\
}\
}\
}while(0)

#define KN_PRINTF_I16_SIZE(A, SIZE) do {\
if(A== NULL )break;\
  for(int i = 0; i < SIZE; i++){\
	ksp_int16_t a = *((ksp_int16_t *)A+i);\
   fprintf(stdout,"%s[%d]: %d\n",#A,i, a);\
}\
}while(0)

#else
#if 0
#define KN_PRINT_VR128(x)
#define KN_PRINT_FR32X(VR_IN, PREFIX)
#define KN_PRINT_VR64X(VR_IN, PREFIX)
#define KN_PRINT_VR128X_IDX(VR_IN, PREFIX, IDX)
#define KN_PRINT_VR128X(VR_IN, PREFIX) 
#define KN_PRINT_Q15_EXP(I32, EXP)
#define KN_PRINT_VR64(VR_IN)
#define KN_PRINT(BUF, SIZE, DTYPE)
#define KN_PRINT_VR_Q7(VR_X, EXP)
#define KN_PRINT_VR_Q7_8x8(VR_X, EXP)
#define KN_PRINT_VR_Q8_8x8(VR_X, EXP)
#define KN_PRINTF_F(A)
#define KN_PRINTF_F_SIZE(A, SIZE)
#define KN_PRINTF_C_SIZE(A, SIZE)
#define KN_PRINTF_I(A)
#define KN_PRINTF_I8(A)
#define KN_PRINTF_IX(A, X)
#define KN_PRINTF_I32_SIZE(A,SIZE)
#define KN_PRINTF_I16_SIZE(A, SIZE)
#endif

#endif


//extern int enable_kn_print;
typedef struct kwio_Dump_t {
	FILE *file_ptr;
	int idx;
	int size;
	unsigned int offset;
	// side info
	char func_name[100];
	unsigned int line;
	char var_name[100];
} kwio_Dump_st;

typedef struct kwio_dmp_mode_t{
	int index; // current index
	unsigned int line[KN_DUMP_MODE_MAX];
	void *buf_ptr[KN_DUMP_MODE_MAX];
	int mod;
	int mode_debug[KN_DUMP_MODE_MAX];
}kwio_dmp_mode_st;
struct cstub_vr128x {
	unsigned int x0;
	unsigned int x1;
	unsigned int x2;
	unsigned int x3;
};
typedef	enum {

	KSP_FLOAT_T = 0,
	KSP_COMPLEX_T,
	KSP_COMPLEX_REAL_T,
	KSP_COMPLEX_IMAG_T,
	KSP_INT32_T,
	KSP_INT16_T,
	KSP_INT8_T,
	
	KSP_PCM_T,
	KSP_INT8_Q7_T,
	KSP_INT8_Q7_EXP_T,
	KSP_UINT8_Q7_EXP_T,
	KSP_INT32_EXP_T,
	KSP_IEEE_FLT_T,
    KSP_IEEE_DBL_T,
	// 2d array
	KSP_2D_COMPLEX_DP_T,
	KSP_2D_COMPLEX_SP_T,
	KSP_2D_FLOAT_T, //TBD
	//VR_type 128
	KSP_VR_2COMPLEX_T,
	KSP_VR_4FLOAT_T,
	KSP_CRC,
	KSP_INT8_T_C_TYPE, // c-array format out
	KSP_FLOAT_T_C_TYPE, // c-array format
	KSP_BIN_4BYTE_T,
	KSP_BIN_2BYTE_T,
	KSP_BIN_1BYTE_T,
    KSP_INT32_HEX_T
}kwio_Dump_type_t;
int kn_df(int idx,
	const char *filename,
	const void *buf,
	int size,
	int type,
	int fixexp,
	unsigned int dmp_mask,
	const char *buffer_name,
	const char *func,
	const unsigned long line);
unsigned short crc16_ccitt(const unsigned char *buf, int len);
int kn_debug_brkpt(int index, int target_offset, int step, int stride);
double afloat2double(unsigned int& x);
void switch_off_kn_dump();
void switch_on_kn_dump();

void switch_off_kn_print();
void switch_on_kn_print();
int get_kn_print();
//void kn_crc(FILE* crc_file, const void *buf, int bytes, const char *buf_name, const char *func, const unsigned long line);
void kn_dmp_set_subfolder(const char *subfolder);
int kn_dmp_get_status();
int kn_dmp_set_status(unsigned int);
void kn_dmp_set_file_id_offset(int dmp_file_id);

int kn_df2(kn_dmp_component mod,
	void *buf,const char *buf_name,
	int size, int dtype, int aexp,
	const char *func, unsigned long line);
void kn_set_end_of_dmp();
int get_kn_skip_dump();
int kn_debug_on_frm(int index, int target_offset_dn, int target_offset_up);

int random_afloat(void *pIn, int size);

void ConvertQ15ToAfloat(fr32 *output, int16_t *input, int size, int exp);
void ConvertQ31ToAfloat(fr32 *output, int32_t *input, int size, int exp);
void ConvertQ63ToAfloat(fr32 *output, uint64_t *input, int size, int exp);
#ifdef __cplusplus
}
#endif
#if defined( KN_DEBUG_DUMP_FILE) && !defined(KWIO_DUMP_SELF)
#if defined( _MSC_VER) && !defined(UNLINK_KSP_MATH)

#ifdef _WIN64
#pragma comment (lib,"P:\\AlgoSW\\KSP\\dmx1a\\libs\\kwio-dump\\lib\\DebugDll-Generic-x64\\kwio-dump.lib")
#else
#pragma comment (lib,"P:\\AlgoSW\\KSP\\dmx1a\\libs\\kwio-dump\\lib\\DebugDll-DeltaMax-Win32\\kwio-dump.lib")
#endif
#endif
#endif
