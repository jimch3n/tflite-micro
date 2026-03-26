/************************************************************************//**
* @file  ksp_math.h
*
* @brief This is the KSP equivalent of math to provide useful math functions
*
* Contains definitions of public types and functions that can be used by
* applications using this module
*
* @sa
* Put references to (names of) other relevant files here
*
* @info
* $Author: rmatcha $
* $DateTime: 2021/11/08 03:50:51 $
* $Revision: #1 $
* $Id: //AudEngr/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Knowles_IA700_SDK/DSPDev/Source/FrontEnd/inc/ksp_math.h#1 $
*
* @copyright
* Copyright (c) 2016 by Knowles Corporation. All rights reserved.
*
* This software is the confidential and proprietary information of Knowles
* Corporation. ("Confidential Information"). You shall not disclose such
* Confidential Information and shall use it only in accordance with the Terms
* of Sale of Knowles Corporation products and the terms of any license
* agreement you entered into with Knowles Corporation for such products.
* <br>
* KNOWLES CORPORATION SOURCE CODE STRICTLY "AS IS" WITHOUT ANY WARRANTY
* WHATSOEVER, AND KNOWLES CORPORATION EXPRESSLY DISCLAIMS ALL WARRANTIES,
* EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE IMPLIED
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR
* NON-INFRINGEMENT OF THIRD PARTY RIGHTS. KNOWLES CORPORATION SHALL NOT BE
* LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF USING, MODIFYING OR
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
****************************************************************************/


#pragma once
#ifndef KSP_MATH_H
#define KSP_MATH_H

/**********  External/default library includes  *********************/

/**********  Knowles support includes  ******************************/
#include "ksp_types.h"
#include "ksp_common.h"

/**********  Self includes  *****************************************/

/**********  Local typedefs *****************************************/

#if defined(AVL_GENERIC) || defined(AVL_DELTAMAX) || defined(AVL_DMX1A) || defined(AVL_HEMI)
#define     LOG2_OF_10      (KSP_FLOAT_CONST(3.321928094887362))
#define     INV_LOG2_OF_10  (KSP_FLOAT_CONST(0.301029995663981))

#define NO_SCALING      0

_AI AScalar fp_multiply(const AScalar& x, const AScalar& y) {return x * y;}
//_AI AScalar fp_inverse(const AScalar& x) {return x.inverse();}

INLINE ksp_float_reg_t  ksp_inverse(const ksp_float_reg_t &x)
{ return x.inverse(); }
INLINE ksp_float_reg_t  ksp_fp_inverse(const ksp_float_reg_t &x)
{return x.inverse(); }
INLINE ksp_int32_t      ksp_floor(const ksp_float_reg_t &x)
{ return x.floor();}
INLINE ksp_int32_t      ksp_ceil(const ksp_float_reg_t &x)
{ return x.ceil(); }
INLINE ksp_float_reg_t  ksp_sqrt(const ksp_float_reg_t &x)
{ return x.f_sqrt(); }
INLINE ksp_float_reg_t  ksp_isqrt(const ksp_float_reg_t &x)
{ return x.f_invsqrt(); }
INLINE ksp_float_reg_t  ksp_log2(const ksp_float_reg_t &x)
{ return x.f_log2(); }
INLINE ksp_float_reg_t  ksp_log10(const ksp_float_reg_t &x)
{ return x.f_log2() * INV_LOG2_OF_10; }// / LOG2_OF_10; }
INLINE ksp_float_reg_t  ksp_ln(const ksp_float_reg_t &x)
{ return x.f_log(); }
INLINE ksp_float_reg_t  ksp_pow2(const ksp_float_reg_t &x)
{ return x.f_pow2(); }
INLINE ksp_float_reg_t  ksp_pow(const ksp_float_reg_t &x, const ksp_float_reg_t &pow)
{ return x.f_pow(pow); }
INLINE ksp_float_reg_t  ksp_sin(const ksp_float_reg_t &x)
{ return x.sine_rads(); }
INLINE ksp_float_reg_t  ksp_cos(const ksp_float_reg_t &x)
{ return x.cosine_rads(); }
INLINE ksp_float_reg_t  ksp_atan2(const ksp_float_reg_t &x)
{ return x.atan2_rads(x, KSP_ONE); }
INLINE ksp_float_reg_t  ksp_exp(const ksp_float_reg_t &x)
{ return x.f_exp(); }
INLINE ksp_float_reg_t  ksp_abs(const ksp_float_reg_t &x)
{ return x.abs(); }
INLINE ksp_float_reg_t  ksp_tanh(const ksp_float_reg_t &x)
{ ksp_float_reg_t e2x = (KSP_TWO*(ksp_float_reg_t)x).f_exp(); return (e2x - KSP_ONE) / (e2x + KSP_ONE); }
INLINE ksp_float_reg_t  ksp_cosh(const ksp_float_reg_t &x)
{ ksp_float_reg_t epx = ((ksp_float_reg_t)x).f_exp(); ksp_float_reg_t emx = (-(ksp_float_reg_t)x).f_exp(); return (epx + emx) / (KSP_TWO); }
INLINE ksp_float_reg_t ksp_frexp(const ksp_float_reg_t &x, int *exp)
{
#if defined(AVL_DELTAMAX) || defined(AVL_DMX1A) 
    int  ax = move_ar_fr(x.fr);
    fr32 y  = seta_fr(0, 0, 0);
#endif
#if defined (AVL_HEMI)
    int  ax = move_ar_fr(x.fr);
    fr32 y  = seta_fr(0, 0);
#endif
    {
        int expT = (ax >> 25) & 0x3f;
        if (ne_fr(x.fr, y))
            { expT -= 31; }
        *exp = expT;
    }
    {
        int   mant = ax & 0x1ffffff;
#if defined(AVL_DELTAMAX) || defined(AVL_DMX1A)
        vr128 z    = vseta_vr(0, 0, 0);
        replicate_ar(z, 1, mant | 0x2000000);
        replicate_ar(z, 2, ax);
        convert_32I_to_32F_x1(z, 5, 0);
        s_copy(z, 0, z, 0, z, 1);
        move_vr_eqz(z, 0, z, 2, z, 1);
        return get_VRQ0(z);
#else  // AVL_HEMI
        vr64 z;
        fr32 z0;
        replicate_ar(z, 1, mant | 0x2000000);
        convert_32I_to_32F_x1(z, 5, 0);
        z0 = s_copy(get_VRL(z), x);
        move_fr_eqz(z0, y, x);
        return z0;
#endif
    }

}
INLINE ksp_float_reg_t ksp_time_const_to_lambda(const ksp_float_reg_t &timeConst_ms, const ksp_float_reg_t &frameSize_ms)
{ /*    lambda = exp(1./(fs_Hz*tc_s)) - 1; */
    ksp_float_reg_t lambda = ksp_exp(frameSize_ms * ksp_inverse(timeConst_ms)) - KSP_ONE; return lambda;
};
INLINE ksp_float_reg_t ksp_linear_to_dB(const ksp_float_reg_t &linVal)
{ return CONST_ASCALAR(20.0) * ksp_log10(linVal); }
INLINE ksp_float_reg_t ksp_dB_to_linear(const ksp_float_reg_t &dBVal)
{
    ksp_float_reg_t twentyInverse = CONST_ASCALAR(0.05);//1.0 / 20.0);
    return ksp_pow(CONST_ASCALAR(10.0), dBVal * twentyInverse);
}
INLINE ksp_float_reg_t ksp_modulo_div(const ksp_float_reg_t &a, const ksp_float_reg_t &m)
{/* modulo division a % m = a - m*floor(a/m) */
    return (a - m * (ksp_float_reg_t)ksp_floor(a / m));
}
#endif

typedef enum {
    KSP_MATH_WIN_NONE = 0,    ///< Rectangular (No) window
    KSP_MATH_WIN_HANN,        ///< Hann window
    KSP_MATH_WIN_HAMMING,     ///< Hamming window
    KSP_MATH_WIN_SPX_MMSE,    ///< Window used by spx mmse

    KSP_MATH_WIN_HANN_SQRT,   ///< square-root of Hann window

    KSP_MATH_WINDOW_CNT
} ksp_math_Window_t;

typedef enum {
    KSP_MATH_OVERLAP_PCT_0 = 0,    ///< No overlap
    KSP_MATH_OVERLAP_PCT_50,       ///< 50% overlap
    KSP_MATH_OVERLAP_PCT_75,       ///< 75% overlap
    KSP_MATH_OVERLAP_PCT_87_5,     ///< 87.5% overlap

    KSP_MATH_OVERLAP_PCT_CNT
} ksp_math_OverlapPct_t;


typedef enum {
    KSP_CROSSFADE_FADEDIN,      ///< The signal is already faded in. No need to run cross fade
    KSP_CROSSFADE_ISFADING,     ///< cross fade is in progress
    KSP_CROSSFADE_FADEDOUT,     ///< The signal has been faded out. Just pass through the input.
} ksp_crossfade_stage_t;

typedef struct ksp_crossfade_State {
    ksp_float_t g;              ///< current gain
    ksp_float_t inc;            ///< current gain increment setting
    ksp_float_t defInc;         ///< default gain increment setting

    ksp_crossfade_stage_t processStage; ///< current cross fade processing stage
    ksp_int16_t lastEnable;     ///< "enable" means the signal will be faded in. "disable" means the signal will be faded out.
                                ///< Here, it tracks the caller's last "enable" status.

} ksp_crossfade_State_t;

/**********  Local Macros  **************************************************/





/******************  Public Functions ***************************************/
#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

    /*****************************************************************************
    * ksp_math_mem_copy()
    *****************************************************************************
    * Copy specified number of bytes from source to destination.  Bytes are
    * copied in order from low to high addresses, so if the buffers overlap,
    * the source starting address should be higher than the destination starting
    * address.
    *
    * @param[out] pDst          Pointer to output buffer.
    * @param[in]  pSrc          Pointer to input buffer.
    * @param[in]  nBytes        Bytes to transfer.
    ****************************************************************************/
    void ksp_math_mem_copy(void *pDst, void *pSrc, ksp_int32_t nBytes);

    /*****************************************************************************
    * ksp_math_mem_zero()
    *****************************************************************************
    * Set the specified number of bytes to 0 in the destination buffer.
    *
    * @param[out] pDst          Pointer to output buffer.
    * @param[in]  nBytes        Bytes to zero.
    ****************************************************************************/
    void ksp_math_mem_zero(void *pDst, ksp_int32_t nBytes);

    /*****************************************************************************
    * ksp_math_mem_fill()
    *****************************************************************************
    * Copy the given source pattern to the destination buffer the specified
    * number of times.  The pattern must be 1, 2, or 4 bytes, and the source
    * and destination buffers must be aligned to 'size' bytes.
    *
    * @param[out] pDst          Pointer to output buffer.
    * @param[in]  pSrc          Pointer to buffer with source pattern.
    * @param[in]  size          Size of pattern (1, 2, or 4 bytes).
    * @param[in]  nItems        Number of times to write the pattern.
    ****************************************************************************/
    void ksp_math_mem_fill(void *pDst, void *pSrc, ksp_int32_t size, ksp_int32_t nItems);

    /*****************************************************************************
    * ksp_math_mem_fill_float()
    *****************************************************************************
    * Copy the given ksp_float_t value the specified number of times to the
    * destination buffer.
    *
    * @param[out] pDst          Pointer to output buffer.
    * @param[in]  Src           Source ksp_float_t value.
    * @param[in]  nItems        Number of times to write the value to the destination.
    ****************************************************************************/
    void ksp_math_mem_fill_float(void *pDst, ksp_float_t Src, ksp_int32_t nItems);

	/*****************************************************************************
	* ksp_math_vector_cpy
	*************************************************************************//**
	* Vector Copy
	*
	* @param[in]    pSrc        pointer to the source buffer
	* @param[out]   pDes        pointer to the destination buffer; pDes[ii] = pSrc[ii];
	*
	*****************************************************************************/
	void ksp_math_vector_cpy(
	    ksp_float_t *pDes,
	    const ksp_float_t *pSrc,
	    ksp_int32_t N);

    /****************************************************************************
    * ksp_math_vector_total
    *************************************************************************//**
    *
    * Computes the sum of the elements in floating point vector X and Y and puts the
    * result in the supplied output buffer.
    *
    * @param[out] pOut      Output.
    * @param[in]  pX        Input vector.
    * @param[in]  length    Length of the vector.
    *
    ****************************************************************************/
    void ksp_math_vector_total(
        ksp_float_t *pOut,
        const ksp_float_t *pX,
        ksp_int32_t length
        );

    /****************************************************************************
    * ksp_math_vector_add
    *************************************************************************//**
    *
    * Adds floating point vectors X and Y and puts the result in the supplied
    * output buffer.  This can operate in place.
    *
    * @param[out] pOut      Output vector.
    * @param[in]  pX        Input vector 1.
    * @param[in]  pY        Input vector 2.
    * @param[in]  length    Length of the vectors.
    *
    ****************************************************************************/
    void ksp_math_vector_add(
        ksp_float_t *pOut,
        const ksp_float_t *pX,
        const ksp_float_t *pY,
        ksp_int32_t length
        );

    /****************************************************************************
    * ksp_math_vector_sub
    *************************************************************************//**
    *
    * Subtracts floating point vector Y from X and puts the result in
    * the supplied output buffer.  This can operate in place.
    *
    * @param[out] pOut      Output vector.
    * @param[in]  pX        Input vector 1.
    * @param[in]  pY        Input vector 2, which is subtracted from input vector 1.
    * @param[in]  length    Length of the vectors.
    *
    ****************************************************************************/
    void ksp_math_vector_sub(
        ksp_float_t *pOut,
        const ksp_float_t *pX,
        const ksp_float_t *pY,
        ksp_int32_t length
        );

    /****************************************************************************
    * ksp_math_vector_mul
    *************************************************************************//**
    *
    * Multiplies floating point vectors X and Y and puts the result in the
    * supplied output buffer.  This can operate in place.
    *
    * @param[out] pOut      Output vector.
    * @param[in]  pX        Input vector 1.
    * @param[in]  pY        Input vector 2.
    * @param[in]  length    Length of the vectors.
    *
    ****************************************************************************/
    void ksp_math_vector_mul(
        ksp_float_t *pOut,
        const ksp_float_t *pX,
        const ksp_float_t *pY,
        ksp_int32_t length
        );

	/****************************************************************************
	* ksp_math_vector_mul_complexWithReal
	*************************************************************************//**
	*
	* Multiplies complex floating point vector X and real floating vector Y and puts the result in the
	* supplied complex floating point output buffer.  This can operate in place.
	*
	* @param[out] pOut      Complex Output vector.
	* @param[in]  pX        Complex Input vector 1.
	* @param[in]  pY        Real Input vector 2.
	* @param[in]  length    Length of the vectors.
	*
	****************************************************************************/
	void ksp_math_vector_mul_complexWithReal(
		ksp_complex_t *pOut,
		ksp_complex_t *pX,
		const ksp_float_t *pY,
		ksp_int32_t length
	);


    /*****************************************************************************
    * ksp_math_vector_mac
    *************************************************************************//**
    *
    * Multiplies two floating point vectors, adds the result to another vector,
    * and puts the result in the supplied output buffer.  This can operate in
    * place.
    *
    * @param[out] pOut      Output vector = Z + X*Y.
    * @param[in]  pZ        Input vector Z.
    * @param[in]  pX        Input vector X.
    * @param[in]  pY        Input vector Y.
    * @param[in]  length    Length of the vectors.
    *
    ****************************************************************************/
    void ksp_math_vector_mac(
        ksp_float_t *pOut,
        const ksp_float_t *pZ,
        const ksp_float_t *pX,
        const ksp_float_t *pY,
        ksp_int32_t length
        );

    /*****************************************************************************
	* ksp_math_vector_addI
	*************************************************************************//**
	* Array Addition
	*
	* @param[in]    pX        pointer to the augend buffer
	* @param[in]    pY        addend
	* @param[out]   pZ        pointer to the sum buffer; Z[ii] = X[ii] + Y;
	*****************************************************************************/
	void ksp_math_vector_addI(
		ksp_float_t *pZ,
		const ksp_float_t *pX,
		const ksp_float_t Y,
		ksp_int32_t N);

	/*****************************************************************************
	* ksp_math_vector_subI
	*************************************************************************//**
	* Array Subtraction
	*
	* @param[in]    pX        pointer to the minuend buffer
	* @param[in]    pY        subtrahend
	* @param[out]   pZ        pointer to the diffrence buffer; Z[ii] = X[ii] - Y;
	*
	*****************************************************************************/
	void ksp_math_vector_subI(
		ksp_float_t *pZ,
		const ksp_float_t *pX,
		const ksp_float_t Y,
		ksp_int32_t N);

	/*****************************************************************************
	* ksp_math_vector_mulI
	*************************************************************************//**
	* Array Multiplication
	*
	* @param[in]    pX        pointer to the mulitplicand buffer
	* @param[in]    pY        multiplier
	* @param[out]   pZ        pointer to the product buffer; Z[ii] = X[ii] * Y;
	*
	*****************************************************************************/
	void ksp_math_vector_mulI(
		ksp_float_t *pZ,
		const ksp_float_t *pX,
		const ksp_float_t Y,
		ksp_int32_t N);

	/*****************************************************************************
	ksp_math_vector_sqrt()
	\brief Vector square root
	*****************************************************************************/
	/*****************************************************************************
	* ksp_math_vector_sqrt
	*************************************************************************//**
	* Array square root
	*
	* @param[in]    pX        pointer to the input buffer
	* @param[out]   pZ        pointer to the output buffer; Z[ii] = sqrt(X[ii]);
	*
	*****************************************************************************/
	void ksp_math_vector_sqrt(
		ksp_float_t *pZ,
		const ksp_float_t *pX,
		ksp_int32_t N);

    /*****************************************************************************
    * ksp_math_inner_prod_real
    *************************************************************************//**
    * Inner product of two real vectors.
    *
    * @param[in]   *px             Vector for inner product
    * @param[in]   *py             Vector for inner product
    * @param[in]   len             Length of the vector for inner product
    * @param[out]  *pOut           Pointer to output of inner product
    * @returns     status          Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    ****************************************************************************/
    ksp_status_t  ksp_math_inner_prod_real(
        const ksp_float_t     *px,
        const ksp_float_t     *py,
        ksp_int32_t            len,
        ksp_float_t           *pOut
    );


	/*****************************************************************************
	* ksp_math_vector_interp
	*************************************************************************//**
	* Vector Interpolation
	*
	* @param[in]    pX        pointer to the source buffer
	* @param[in]    rx        interpolation ration for X
	* @param[in]    pY        pointer to the source buffer
	* @param[in]    ry        interpolation ration for Y
	* @param[out]   pZ        pointer to the destination buffer; Z[ii] = X[ii]*rx + Y[ii]*ry;
	*****************************************************************************/

	void ksp_math_vector_interp(
		ksp_float_t *pZ,
		const ksp_float_t *pX,
		const ksp_float_t *pY,
		const ksp_float_t rx,
		const ksp_float_t ry,
		ksp_int32_t N);



	/*****************************************************************************
	* ksp_math_vector_min
	*************************************************************************//**
	* Array Min
	*
	* @param[in]    pX        pointer to the X buffer
	* @param[in]    pY        pointer to the Y buffer
	* @param[out]   pZ        pointer to the result buffer; Z[ii] = (X[ii] < Y[ii])?X[ii]:Y[ii];
	*
	*****************************************************************************/
	void ksp_math_vector_min(
		ksp_float_t *pZ,
		const ksp_float_t *pX,
		const ksp_float_t *pY,
		ksp_int32_t N);

	/*****************************************************************************
	* ksp_math_vector_max
	*************************************************************************//**
	* Array Min
	*
	* @param[in]    pX        pointer to the X buffer
	* @param[in]    pY        pointer to the Y buffer
	* @param[out]   pZ        pointer to the result buffer; Z[ii] = (X[ii] > Y[ii])?X[ii]:Y[ii];
	* 
	*****************************************************************************/
	void ksp_math_vector_max(
		ksp_float_t *pZ,
		const ksp_float_t *pX,
		const ksp_float_t *pY,
		ksp_int32_t N);

    /*****************************************************************************
    * ksp_math_power_spectrum
    *************************************************************************//**
    * Compute power spectrum of a half-complex (packed) vector
    *
    * @param[in]   *pX             Pointer to input complex vector
    * @param[in]    fftSize        FFT size.
    * @param[out]  *pOut           Pointer to output vector of power spectrum
    * @param[in]    useAccum       Logic of computing accumulated Stats.
    * @returns     status          Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    ****************************************************************************/
    ksp_status_t ksp_math_power_spectrum(
        const ksp_complex_t     *pX,
        ksp_int32_t              fftSize,
        ksp_float_t             *pOut,
        ksp_int32_t              useAccum
    );
ksp_status_t ksp_math_norm(
	const ksp_complex_t  *pX,
	ksp_int32_t           fftSize,
	ksp_float_t          *pOut,
	ksp_int32_t           useAccum);
	/*****************************************************************************
	* ksp_math_norm
	*************************************************************************//**
	* Compute power spectrum of a half-complex (packed) vector and 
	* compute the square root of the result
	*
	* @param[in]   *pX             Pointer to input complex vector
	* @param[in]    fftSize        FFT size.
	* @param[out]  *pOut           Pointer to output vector of power spectrum
	* @param[in]    useAccum       Logic of computing accumulated Stats.
	* @returns     status          Returns KSP_SUCCESS or ksp_status_t type value
	for the error.
	****************************************************************************/
	ksp_status_t ksp_math_norm(
		const ksp_complex_t     *pX,
		ksp_int32_t              fftSize,
		ksp_float_t             *pOut,
		ksp_int32_t              useAccum
	);

    /*****************************************************************************
    * ksp_math_fd_energy
    *************************************************************************//**
    * Compute energy of a power spectrum vector
    *
    * @param[in]   *ps             Pointer to input vector of power spectrum
    * @param[in]    fftSize        Size of the FFT
    * @param[out]  *pOut           Pointer to output of energy
    * @returns     status          Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    ****************************************************************************/
    ksp_status_t ksp_math_fd_energy(
        const ksp_float_t      *ps,
        ksp_int32_t             fftSize,
        ksp_float_t            *pOut
    );

    /*****************************************************************************
    * ksp_math_fd_modifier
    *************************************************************************//**
    * Compute element wise multiplication of a half-complex (packed) vectors
    * pOut = pX_i .* pY_i or pOut = pX_i .* conj(pY_i)
    *
    * @param[in]   *pX             Pointer to input complex vector
    * @param[in]   *pY             Pointer to input complex vector
    * @param[in]    fftSize        Size of the FFT
    * @param[in]    useConj        Logic of conjugate multiply.
    *                              If useConj = 1, pOut = pX_i .* conj(pY_i)
    * @param[out]  *pOut           Pointer to output of element wise multiplication
    *                              of two vectors
    * @returns     status          Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_fd_modifier(
        const ksp_complex_t           *pX,
        const ksp_complex_t           *pY,
        ksp_int32_t                    fftSize,
        ksp_int32_t                    useConj,
        ksp_complex_t                 *pOut
    );

    /*****************************************************************************
    * ksp_math_get_window
    *************************************************************************//**
    * Calculates the window to be applied. Safe to assume that window size is
    * even since window size and FFT size are always same. Returns window of size
    * fftSize/2 + 1.
    *
    * @param[out]   *pWindow        Contains the generated window
    * @param[in]    windowType      Specifies the type of window
    * @param[in]    windowSize      Specifies the size of the window
    * @param[in]    overlap         Number of overlapping samples
    * @param[out]   *pWindowScale   Scaling applied to window
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_get_window(
        ksp_float_t            *pWindow,
        ksp_math_Window_t       windowType,
        ksp_int32_t             windowSize,
#ifdef REF_CODE
        ksp_math_OverlapPct_t   overlapPct,
#else
        ksp_int32_t             frameSize,
#endif
        ksp_float_t&            windowScale
    );

#ifdef USE_WINDOW_FLT16
ksp_status_t ksp_math_get_window_hanning16(
    ksp_uint16_t             *pWindow,
    ksp_math_Window_t       windowType,
    ksp_int32_t             windowSize,
    ksp_int32_t             frameSize,
    ksp_float_t&            windowScale       // passing 'by reference' (C++)
);

#define WINDOW_SIGN 1
#define WINDOW_EXP 2
#define WINDOW_BIAS 3

#endif
    /*****************************************************************************
    * ksp_math_get_overlap_pct
    *************************************************************************//**
    *  Takes fftSize and frameSize and returns a enum representing the overlap
    * percentage that can be used to create/reset STFT instances
    *
    * @param[in]    windowSize      Specifies the size of the window
    * @param[in]    frameSize       Specifies the number of samples in each frame
    * @param[out]   overlapPct      Overlap percent enum
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_get_overlap_pct(
        ksp_int32_t              fftSize,
        ksp_int32_t              frameSize,
        ksp_math_OverlapPct_t   *overlapPct
    );

    /*****************************************************************************
    * ksp_math_get_overlap_samples
    *************************************************************************//**
    * Takes windowSize and overlap percentage and returns the number of
    * overlapping samples.
    *
    * @param[in]    windowSize      Specifies the size of the window
    * @param[in]    overlapPct      Specifies the percentage overlap
    * @param[out]   overlapSamples  Number of overlapping samples
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_get_overlap_samples(
        ksp_int32_t            windowSize,
        ksp_math_OverlapPct_t   overlapPct,
        ksp_int32_t            *overlapSamples
    );

    /*****************************************************************************
    * ksp_math_get_window_size
    *************************************************************************//**
    * Takes frames size and overlap percentage and returns the window size to
    * be used.
    *
    * @param[in]    frameSize       Specifies the number of samples in the input
    *                               frame.
    * @param[in]    overlapPct      Specifies the percentage overlap
    * @param[out]   windowSize      Size of the window. This is the sum of
    *                               frame size and number of overlapping samples
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_get_window_size(
        ksp_int32_t             frameSize,
        ksp_math_OverlapPct_t   overlapPct,
        ksp_int32_t             *windowSize
    );

    /*****************************************************************************
    * ksp_math_nn_linear()
    *************************************************************************//**
    * Compute Linear fuction
    * \f$ f(x) = x \f$
    *
    * @param[in]    *pX              Neural network layer of units
    * @param[in]    len              Size of the layer
    * @param[out]   *pOut            Neural network layer of units after activation
    * @returns status                Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_nn_linear(
        ksp_float_t *pX,
        ksp_int32_t len,
        ksp_float_t *pOut
    );

    /*****************************************************************************
    * ksp_math_nn_sigmoid()
    *************************************************************************//**
    * Compute Sigmoid fuction
    * \f$ f(x) = \frac{1}{1 + exp(-x)} \f$
    *
    * @param[in]    *pX              Neural network layer of units
    * @param[in]    len              Size of the layer
    * @param[out]   *pOut            Neural network layer of units after activation
    * @returns status                Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_nn_sigmoid(
        ksp_float_t  *pX,
        ksp_int32_t len,
        ksp_float_t  *pOut
    );

    /*****************************************************************************
    * ksp_math_nn_tanh()
    *************************************************************************//**
    * Compute hyperbolic tangent fuction
    * \f$ f(x) = \frac{1 + exp(-2x)}{1 - exp(-2x)} \f$
    *
    * @param[in]    *pX              Neural network layer of units
    * @param[in]    len              Size of the layer
    * @param[out]   *pOut            Neural network layer of units after activation
    * @returns status                Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_nn_tanh(
        ksp_float_t  *pX,
        ksp_int32_t  len,
        ksp_float_t  *pOut
    );

    /*****************************************************************************
    * ksp_math_nn_relu()
    *************************************************************************//**
    * Compute rectified linear unit (RELU) fuction
    * \f$ f(x) = max(0, x) \f$
    *
    * @param[in]    *pX              Neural network layer of units
    * @param[in]    len              Size of the layer
    * @param[out]   *pOut            Neural network layer of units after activation
    * @returns status                Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_nn_relu(
        ksp_float_t  *pX,
        ksp_int32_t  len,
        ksp_float_t  *pOut
    );

    /*****************************************************************************
    * ksp_math_nn_softmax()
    *************************************************************************//**
    * Compute Softmax fuction
    * \f$ f(x)_j = \frac{e(x_j)}{\sum_{k=1}^{K}exp(x_k)} for j = 1, ..., K\f$
    *
    * @param[in]    *pX              Neural network layer of units
    * @param[in]    len              Size of the layer
    * @param[out]   *pOut            Neural network layer of units after activation
    * @returns status                Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_nn_softmax(
        ksp_float_t  *pX,
        ksp_int32_t  len,
        ksp_float_t  *pOut
    );

    /*****************************************************************************
    * ksp_math_nn_softmax2()
    *************************************************************************//**
    * Compute Softmax fuction
    * \f$ f(x)_j = \log{\frac{e(x_j)}{\sum_{k=1}^{K}exp(x_k)} for j = 1, ..., K}\f$
    *
    * @param[in]    *pX              Neural network layer of units
    * @param[in]    len              Size of the layer
    * @param[out]   *pOut            Neural network layer of units after activation
    * @returns status                Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_nn_softmax2(
        ksp_float_t  *pX,
        ksp_int32_t  len,
        ksp_float_t  *pOut
    );

    /*****************************************************************************
    * ksp_math_covariance()
    *************************************************************************//**
    * Calculates the spatial covariance between two multi-channel signals x and y.
    *
    * \f$ pCov_{xy}(f) = E[x(f) {y(f)}^H] for f = 0, ..., nBins-1\f$
    *
    * pCov is a pointer to a 1-D array of dimension nBins x nChanX x nChanY
    *
    * Note the covariance terms are stacked as follows -
    * [ pCov(0), pCov(1), ... pCov(nBins - 1) ]
    * where nBins is the number of bins = (fftSize / 2 + 1)
    *
    * Each pCov(f) is further stacked as follows -
    * [ pCov(0, 0), ..., pCov(0, nChanY - 1),
    *   pCov(1, 0), ..., pCov(1, nChanY - 1),
    *   ...,
    *   pCov(nChanX - 1, 0), ..., pCov(nChanX - 1, nChanY - 1) ]
    * where nChanX is num. of channels of x and nChanY is num. of channels of y.

    * @param[in]   *pX[]        Array of nChanX pointers to inputs
                                (FFT coefficients of multi-channel signal x)
    * @param[in]   *pY[]        Array of nChanY pointers to inputs
                                (FFT coefficients of multi-channel signal y)
    * @param[in]    nChanX      Number of channels in signal x
    * @param[in]    nChanY      Number of channels in signal y
    * @param[in]    fftSize     Size of the FFT
    * @param[in]    scaleLog2   scale factor in 2^(scaleLog2),
                                so set "0" (NO_SCALING) to bypass scaling,
    * @param[in]    sigScaleLog2
                                Applied as 2^sigScaleLog2 to regularization term
                                during covariance calculation
    * @param[out]   *pCov       Pointer to a 1-D array of
                                fftSize/2+1 x nChanX x nChanY covariance terms
    *
    * @returns      status      Returns KSP_SUCCESS or ksp_status_t type value
    *****************************************************************************/
    ksp_status_t ksp_math_covariance(
        const ksp_complex_t  *pX[],
        const ksp_complex_t  *pY[],
        ksp_int32_t           nChanX,
        ksp_int32_t           nChanY,
        ksp_int32_t           fftSize,
        ksp_int32_t           scaleLog2,
        ksp_int32_t           sigScaleLog2,
        ksp_complex_t        *pCov
    );

    /*****************************************************************************
    * ksp_math_coherence()
    *************************************************************************//**
    * Calculates coherence between two spectra
    * \f$ coh_{xy}(f) = \frac{cov_{xy}(f)}{\sqrt{|cov_{xx}(f)*cov_{yy}(f)|}}\f$
    * @param[in]    *pRxx         Covariance of signal x
    * @param[in]    *pRyy         Covariance of signal y
    * @param[in]    *pRxy         Covariance signal x and signal y
    * @param[in]    fftSize       Size of the FFT
    * @param[in]    scaleLog2     scale factor in 2^(scaleLog2)
                                  so set "0" (NO_SCALING) to bypass scaling,
    * @param[out]   *pCoh         Estimated coherence
    *
    * @returns status               Returns KSP_SUCCESS or ksp_status_t type value
                                    for the coherence.
    *****************************************************************************/
    ksp_status_t ksp_math_coherence(
        const ksp_float_t    *pRxx,
        const ksp_float_t    *pRyy,
        const ksp_complex_t  *pRxy,
        ksp_int32_t          fftSize,
        ksp_int32_t          scaleLog2,
        ksp_float_t          *pCoh,
        ksp_int32_t          sqrtFlag
    );

    /*****************************************************************************
    * leaky_integrator()
    *************************************************************************//**
    * Computes leaky integrator across multiple frames
    *
    * @param[in]    *pX              1D array of quantity to smooth
    *                                (typically energy)
    * @param[in]    lenX             Length of input X
    * @param[in]    timeStepSec      Time step in seconds
    *                                (nFft-nOverlap)/sampleRate_Hz
    * @param[in]    timeConstSec     Time constant in seconds
    * @param[out]   *pXsmoothed      Smoothed quantity (until the previous frame
    *                                and will be overwritten for the current frame)
    *
    * @returns status                Returns KSP_SUCCESS or ksp_status_t type value
    for the smoothed quantity.
    *****************************************************************************/
    ksp_status_t ksp_math_leaky_integrator(
        const ksp_float_t   *pX,
        ksp_int32_t         lenX,
        ksp_float_reg_t     &timeStepSec,
        ksp_float_reg_t     &timeConstSec,
        ksp_float_t         *pXsmoothed
    );

	/*****************************************************************************
	* ksp_float_sqrt_add()
	*************************************************************************//**
    * Calculates the square-root version of add
    *
	* x & y are square root inputs
    * The true augend and addend are sign(x)*x^2, sign(y)*y^2 (the input maybe negative)
    * out = sign(x)*x^2 + sign(y)*y^2
	* To prevent overflow, here we return out = sign(out)*sqrt(out)
	*
	* In code, in case of internal overflow, Do:
	* if abs(x)>=abs(y), out = sign(x+y)*sqrt(abs(sign(x)+sign(y)*(y/abs(x))^2))*abs(x)
	* if abs(x)<abs(y), out = sign(x+y)*sqrt(abs(sign(y)+sign(x)*(x/abs(y))^2))*abs(y)
	*
    * @param[in]    &x			augend (input is square-root in advance)
    * @param[in]    &y	        addend (input is square-root in advance)
    *
    * @returns      out		    return the calcualtes result
	*****************************************************************************/
	void ksp_float_sqrt_add(
		const ksp_float_reg_t &x,
		const ksp_float_reg_t &y,
		ksp_float_t *z
	);

    /*****************************************************************************
    * ksp_crossfade_init
    *************************************************************************//**
    * Initialize the "kut_crossfade_State_t" structure.
    * Typical usage to be embedded into the signal processing module is as follows:
    * 1. In the init or reset time: call ksp_crossfade_init() to let the cross fade structure in
    *    an known initial state.
    * 2. During the run time, if the caller (signal processing module) wants to
    *    switch the signal source and a cross fade is desired, it can call
    *    ksp_crossfade_update() to choose which eventual signal source is.
    * 3. Depending on the cross fade stage, the caller has to check every process
    *    call to determine which function to call. [See ksp_peq module for an example]
    *
    * @param[in]   pCF              the ksp_crossfade_State_t structure to be initialized.
    * @param[in]   init_enable      the initial "enable" state meaning if the signal needed to be faded in(enable)/out(disable)
    * @param[in]   fs_Hz            the sample rate of the system
    * @param[in]   cf_time_s        the cross fade time in seconds
    *
    * @returns  nothing
    *****************************************************************************/
    void ksp_crossfade_init(
        ksp_crossfade_State_t* pCF,
        ksp_int16_t init_enable,
        ksp_float_t fs_Hz,
        ksp_float_t cf_time_s
        );

    /*****************************************************************************
    * ksp_crossfade_update
    *************************************************************************//**
    * Update the cross fade to determine how the cross fade should work.
    * The typical usage is:
    *                                          (wet)
    *            +--------------------------+  yOut0   +------------+
    * xIn -+---> | signal processing module | -------> | cross fade | ---> yOut1
    *      |     +--------------------------+          +------------+
    *      |                                             ^ xIn (dry)
    *      |                                             |
    *      +---------------------------------------------+
    *
    * When "enable", yOut1 will choose yOut0 (wet signal)
    * When "disable", yOut1 will choose xIn (dry signal)
    *
    * @param[in]   pCF              the ksp_crossfade_State_t structure to be updated.
    * @param[in]   enable           the output signal needed to be faded in or not.
    *                               1 - mean output chooses the wet signal
    *                               0 - mean output chooses the dry signal
    *
    * @returns  nothing
    *****************************************************************************/
    void ksp_crossfade_update(
        ksp_crossfade_State_t* pCF,
        ksp_int16_t enable
        );

    /*****************************************************************************
    * ksp_crossfade_process
    *************************************************************************//**
    * run the cross fade process
    *
    * @param[in]   pCF              the kut_crossfade_State_t structure to be updated.
    * @param[in,out] pWet           the input is the wet signal, the output is dry,
    *                               wet, or mixed signal.
    * @param[in]   pDry             the dry signal
    * @param[in]   frameSize        the number of the samples to be processed
    *
    * @returns none
    *****************************************************************************/
    void ksp_crossfade_process(
        ksp_crossfade_State_t* pCF,
        ksp_float_t* pWet,
        ksp_float_t* pDry,
        ksp_int16_t frameSize
        );

    /*****************************************************************************
    * ksp_math_get_target_idx
    *************************************************************************//**
    **  For a given target angle and target direction width, get the correpondings
    **  offsets in full response
    *
    * @param[in]    targetDirection Target angle requested by host
    * @param[in]    targetDirectionElevation Target elevation angle requested by host
	* @param[in]    targetDirectionWidth
	Full beam width requested by host
	* @param[in]    targetDirectionWidthElevation elevation width requested by host
    * @param[in]    nAngles         Number of angles in full response
    * @param[in]   *pSdeCalPosAzi   list of Azimuth angles as from calibration set
    * @param[in]   *pSdeCalPosEle   list of elevation angles as from calibration set
    * @param[out]  *index         returns indices of pSdeCalPosAzi/Ele which fall in the user set direction
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/

	void ksp_math_get_target_idx(
		ksp_int32_t             targetDirection,
		ksp_int32_t             targetDirectionElevation,
		ksp_int32_t             targetDirectionWidth,
		ksp_int32_t             targetDirectionWidthElevation,
		ksp_int32_t             nAngles,
		ksp_float_t             *pSdeCalPosAzi,
		ksp_float_t             *pSdeCalPosEle,
		ksp_int32_t             *index);

    /*****************************************************************************
    * ksp_math_set_matrix
    *************************************************************************//**
    * initializer for ksp_matrix_float_t
    *
    * @param[in]   *A              pointer to the matrix stuct to be initialized
    * @param[in]   *M              poiter to ksp_float_t array where the matrix lives
    * @param[in]   *maxrows        max rows that A can have
    * @param[in]   *maxcols        max cols that A can have
    * @param[in]   *rows           num rows that A has when initialized
    * @param[in]   *cols           num cols that A has when initialized
    ************************************************************************/
    void ksp_math_set_matrix(ksp_matrix_float_t *A, ksp_float_t *Mat, int16_t rows, int16_t cols);

    /*****************************************************************************
    * ksp_math_matmul
    *************************************************************************//**
    **  Computes Out = A*B
    *
    * @param[in]    A
    * @param[in]    B
    * @param[out]   Out = A*B
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_matmul(ksp_matrix_float_t *A, ksp_matrix_float_t *B, ksp_matrix_float_t * Out);

    /*****************************************************************************
    * ksp_math_matmultranspose
    *************************************************************************//**
    **  Computes Out = A*B'
    *
    * @param[in]    A
    * @param[in]    B
    * @param[out]   Out = A*B'
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_matmultranspose(ksp_matrix_float_t *A, ksp_matrix_float_t *B, ksp_matrix_float_t * Out);

    /*****************************************************************************
    * ksp_math_matadd
    *************************************************************************//**
    **  Computes Out = A+B
    *
    * @param[in]    A
    * @param[in]    B
    * @param[out]   Out = A+B
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_matadd(ksp_matrix_float_t *A, ksp_matrix_float_t *B, ksp_matrix_float_t *Out);

    /*****************************************************************************
    * ksp_math_matmulscalar
    *************************************************************************//**
    **  Computes Out = A*b
    *
    * @param[in]    A
    * @param[in]    b
    * @param[out]   Out = A+b
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_matmulscalar(ksp_matrix_float_t *A, ksp_float_t b, ksp_matrix_float_t * Out);

    /*****************************************************************************
    * ksp_math_matsetidentity
    *************************************************************************//**
    **  Sets A to identity matrix
    *
    * @param[in]    A
    * @param[out]   A
    *
    * @returns  void
    *****************************************************************************/
    void ksp_math_matsetidentity(ksp_matrix_float_t *A);

    /*****************************************************************************
    * ksp_math_matsetidentity
    *************************************************************************//**
    **  Copies A to B
    *
    * @param[in]    A
    * @param[out]   B
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_math_matcopy(ksp_matrix_float_t *A, ksp_matrix_float_t *B);
	/*****************************************************************************
	* ksp_median_filter_1d
	*************************************************************************//**
	**  Median filter 1 dimension windowSize < 256, and odd
	*
	* @param[in]    *pInData
	* @param[in]    dataSize
	* @param[in]    windowSize
	* @param[out]   *pOutData
	* @param[in]    filteringFlag
	*
	* @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
	for the error.
	*****************************************************************************/
	ksp_status_t ksp_math_median_filter_1d(
		ksp_float_t *pInData,
		ksp_int32_t dataSize,
		ksp_int32_t windowSize,
		ksp_float_t *pOutData,
		ksp_int32_t filteringFlag);

#ifdef  __cplusplus
}
#endif  // __cplusplus
/****************KSP MATH functions that don't support C linkage*****************/

/*****************************************************************************
* ksp_math_vt_feature_limiter()
*************************************************************************//**
* Compute VT feature limiting
* \f$ f(x) = \ 1 - \2^{-x-1} & \text{if $x>=0$}
*   f(x) = \2^{x-1} & \text{if $x<0$}\f$
*
* @param[in]    pX              single raw feature value
* @returns limited feature      Returns limited feature value
for the error.
*****************************************************************************/
ksp_float_t ksp_math_vt_feature_limiter(
    ksp_float_t  pX
);

/*****************************************************************************
* ksp_math_vt_inv_feature_limiter()
*************************************************************************//**
* Compute inverse VT Feature limiting
*\f$ f(x) = \ -1 - \log _{2} {1-x} & \text{if $x>=0.5$}
*   f(x) = 1 + \log _{2} {x} & \text{if $x<0.5$} \f$
*
* @param[in]    pX              single limited feature value
* @returns raw feature      Returns raw feature value
for the error.
*****************************************************************************/
ksp_float_t ksp_math_vt_inv_feature_limiter(
    ksp_float_t  pX
);

#endif /* ksp_math_H */
