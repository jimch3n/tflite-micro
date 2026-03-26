#ifndef KSP_COMMON_H
#define KSP_COMMON_H

#include <float.h>
#include <string.h>
#include "ksp_types.h"

/******************** MACROS  ***************************************/
#ifdef _MSC_VER
#define ALLOC(x)            malloc(x)
#define ALIGNED(x,y)        __declspec(align(y)) x
#define ALIGNED_ALLOC(x,y)  _aligned_malloc(x,y)
#define ALIGNED_FREE(x)     _aligned_free(x)
#define OPEN_FILE(x,y,z)    fopen_s(&x,y,z)
#else
#ifdef __GNUC__
#define ALLOC(x)            malloc(x)
#define ALIGNED(x,y)        x __attribute__((aligned(y)));
#define ALIGNED_ALLOC(x,y)  aligned_alloc(y,x)
#define ALIGNED_FREE(x)     free(x)
#define OPEN_FILE(x,y,z)    x = fopen(y,z)
#endif
#endif

#define KSP_ZERO    (AScalar::Zero())
#define KSP_ONE     (AScalar::One())
#define KSP_TWO     (AScalar::Two())
#define KSP_THREE   (AScalar::Three())
#define KSP_TEN     (AScalar::Ten())
#define KSP_TWENTY  (AScalar::Twenty())
#define KSP_HALF    (AScalar::Half())
#define KSP_FLT_MAX (AScalar::MaxAFloat())
#define KSP_FLT_MIN (AScalar::MinAFloat())

#define KSP_COMPLEX_ZERO (AComplex::Zero())
#define KSP_COMPLEX_ONE  (AComplex(KSP_ONE,KSP_ZERO))

#define KSP_PI		(AScalar::Pi())
#define KSP_TWO_PI	(AScalar::TwoPi())
#define KSP_HALF_PI	(KSP_HALF*KSP_PI)
#define KSP_LN2     (AScalar::ln2())

INLINE ksp_float_reg_t re(const ksp_complex_reg_t &x) { return x.r(); }
INLINE ksp_float_reg_t im(const ksp_complex_reg_t &x) { return x.i(); }
INLINE ksp_float_reg_t norm(const ksp_complex_reg_t &x) { return x.norm(); }
INLINE ksp_float_reg_t normsq(const ksp_complex_reg_t &x) { return x.norm_sq(); }
INLINE ksp_complex_reg_t complex(const ksp_float_reg_t &x, const ksp_float_reg_t &y) { return AComplex(x, y); }
INLINE ksp_complex_reg_t conj(const ksp_complex_reg_t &x) { return x.conj(); }

INLINE ksp_float_reg_t ksp_float_min(const ksp_float_reg_t&x, const ksp_float_reg_t&y) { return x < y ? x : y; }
INLINE ksp_float_reg_t ksp_float_max(const ksp_float_reg_t&x, const ksp_float_reg_t&y) { return x > y ? x : y; }

/// Epsilon values
#define KN_FLT_EPS_16_BIT       (KSP_FLOAT_CONST(FLT_EPSILON))
#define KSP_AFLOAT_REAL_MIN     (KSP_FLOAT_CONST(2.3283065059276353e-010))
//#define KN_FLT_EPS_32_BIT       (KSP_FLOAT_CONST(DBL_EPSILON))

// Miscellaneous operations
#define KN_MAX(x,y)         ((x) > (y) ? (x) : (y))
#define KN_MIN(x,y)         ((x) < (y) ? (x) : (y))
#define KSP_ISPOWER_OF_2(x) (!((x) == 0) && !((x) & ((x) - 1))) 

#define	NO_CLIPPING_WHILE_SCALING 0
#define USE_CLIPPING_WHILE_SCALING 1

//
//	Generate pointers to rows in a 2D array. pFloatRows/pCxRows must be nRows long, and 
//	their first element must containg the pointer to the array buffer
//
ksp_complex_t* ksp_rows_of_cx_array(ksp_complex_t **pCxRows, ksp_int32_t nRows, ksp_int32_t nCols);
ksp_float_t* ksp_rows_of_float_array(ksp_float_t **pFloatRows, ksp_int32_t nRows, ksp_int32_t nCols);

void ksp_scale_float_vector(ksp_float_vector_scaled_t *pDst, ksp_float_vector_scaled_t *pSrc, ksp_int32_t nChannels, ksp_int32_t nElem, ksp_int32_t targetScf, ksp_int32_t useClipping);
void ksp_scale_complex_vector(ksp_complex_vector_scaled_t *pDst, ksp_complex_vector_scaled_t *pSrc, ksp_int32_t nElem, ksp_int32_t targetScf);

/*
* Debug levels -- the enumerated values below are generally used as the
* condition (first argurement) kp_debug statements.  Set the value to 0 to
* suppress kp_debug() prints at that level.
*/
enum {
	KSP_DBG0 = 1,
	KSP_DBG1 = 0,
	KSP_DBG2 = 0
};

#endif // KSP_COMMON_H
