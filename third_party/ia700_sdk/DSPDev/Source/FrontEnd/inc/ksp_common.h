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
#define ALIGNED(x,y)        x __attribute__((aligned(y)))
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
#ifndef AVL_DMX1A
#define KSP_COMPLEX_ONE  (AComplex(KSP_ONE,KSP_ZERO))
#else
#define KSP_COMPLEX_ONE  (AComplex::One())
#define KSP_COMPLEX_I    (AComplex::I())
#endif

#define KSP_PI		(AScalar::Pi())
#define KSP_TWO_PI	(AScalar::TwoPi())
#ifndef AVL_DMX1A
#define KSP_HALF_PI	(KSP_HALF*KSP_PI)
#else
#define KSP_HALF_PI (AScalar::HalfPi())
#endif
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
#ifdef AVL_DMX1A
#define TO_DOUBLE(a)	a.to_double()
#endif
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

// assert function for debug
#ifndef ASSERT
#if defined(_DEBUG) || defined(DEBUG)
/* Visual Studio includes and macros */
#ifdef _MSC_VER
//    __declspec(dllimport) void __stdcall __debugbreak(); //DebugBreak();
#define ASSERT(f)   (void) ((f) || (__debugbreak(), 0)) // DebugBreak()
#else
#include <assert.h>
#define ASSERT(A)   assert(A)
#endif
#else /* DEBUG is not defined */
#define ASSERT(f)
#endif /* #ifdef DEBUG */

#endif /* #ifndef ASSERT */

/* For asserts you only want on Windows */
#ifdef _MSC_VER
#define ASSERT_WIN(A) ASSERT(A)
#else
#define ASSERT_WIN(A)
#endif

#define REMOVE_TDSTFTIO //frontend scratch buffer, shared with mic specturm
#define USE_STFT_TO_MEL_OPT // use packed melfilter which multiple of 4.

#ifdef AVL_HEMI

// Optimization flags used in various modules

/// Common modules
#define USE_HEMIDELTA_COMMON_OPT
#define USE_HEMIDELTA_MATH_OPT
#define USE_HEMIDELTA_STFT_OPT

#define USE_HEMIDELTA_FRONTEND_OPT
/// FFT
#define USE_HEMIDELTA_FFT_OPT 

#endif

#ifdef AVL_DMX1A

/// Common modules
#define USE_DELTAMAX_COMMON_OPT
#define USE_DELTAMAX_MATH_OPT
#define USE_DELTAMAX_STFT_OPT


#define USE_DELTAMAX_FRONTEND_OPT
/// FFT
#define USE_DELTAMAX_FFT_OPT 




#endif

//#define USE_DELTAMAX_VPVUI_SLIM_SET_PARAM   /// USE_DELTAMAX_VPVUI_SLIM_SET_PARAM: Due to no runtime tuning, for product package,
                                              ///   _set_param can be consider to always set all params to avoid paramId judgement,
                                              ///   and parameter should be set in proper range (or move range check to blockgen before make a valid dat).
                                              /// Reminder-1, Default off until it's need.
                                              /// Reminder-2, Need to update if ksp module set_param code base is changed (parameter increase / decrease).

// TODO, below Macro were added long time ago, might need to check or remove for current code base.
/// Memory Optimizations
// Note USE_DELTAMAX_MEM_OPT is relative to memory using and share.
// thus may need to check again when flow / memory condition is changed.
//#define USE_DELTAMAX_MEM_OPT // Enable when needed
#define USE_DELTAMAX_MEM_UNUSED_REMOVED	// Enable when needed

#ifdef USE_DELTAMAX_EXTERNAL_TB_MINIFLT
/* Exponents used for minifloat to afloat conversion */
enum
{
    EXP2 = 2,
    EXP3,
    EXP4,
    EXP5,
    EXP6
};
#endif

//#define WUR_JammingBit(...) ((void)0)


#endif // KSP_COMMON_H
