/************************************************************************//**
 * @file    FFT.h
 *
 * @brief   FFT interface file
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #7 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_FFT_H__
#define __FILE_FFT_H__

/**************************************************************************//**
 * @addtogroup hml_core_dsp
 * @{
 *****************************************************************************/

/****************************************************************************
 * Includes
 ****************************************************************************/
#ifdef __XTENSA__
#include "TIE_include.h"
#else
#include "cstubs.h"
#endif

#include <stdint.h>
#include "TIE_defs.h"



/****************************************************************************
 * Constants
 ****************************************************************************/
#define MAX_COMPLEX_FFT_LOG2_SIZE 16
#define MAX_REAL_FFT_LOG2_SIZE (MAX_COMPLEX_FFT_LOG2_SIZE + 1)
#define MAX_COMPLEX_FFT_SIZE  (1 << MAX_COMPLEX_FFT_LOG2_SIZE)
#define MAX_REAL_FFT_SIZE  (1 << MAX_REAL_FFT_LOG2_SIZE)
#define MIN_COMPLEX_FFT_LOG2_SIZE 3
#define MIN_REAL_FFT_LOG2_SIZE (MIN_COMPLEX_FFT_LOG2_SIZE + 1)

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * FFTComplex()
 ****************************************************************************
 * @brief        Computes forward complex FFT.
 *
 * @details
 *       Supported range 3 <= log2_N <= 16,
 *       Here, log2_N is Base-2 log of number of FFT points, N.
 *
 * Computation time:
 *
 * |log2_N |    N     |  Cycles  |
 * |:-----:|:--------:|:--------:|
 * |     3 |        8 |      143 |
 * |     4 |       16 |      268 |
 * |     5 |       32 |      421 |
 * |     6 |       64 |      879 |
 * |     7 |      128 |     1748 |
 * |     8 |      256 |     3614 |
 * |     9 |      512 |     7688 |
 * |    10 |     1024 |    16024 |
 * |    11 |     2048 |    34409 |
 * |    12 |     4096 |    71697 |
 * |    13 |     8192 |   153416 |
 * |    14 |    16384 |   318800 |
 * |    15 |    32768 |   678323 |
 * |    16 |    65536 |  1405243 |
 *
 * @param[out]   *pOutput    Pointer to output buffer.
 * @param[in]    *pInput     Pointer to input buffer(Complex input). Can be same as output buffer.
 * @param[in]    log2N       Base-2 log of number of FFT points, N. 
 *
 * @return       true for success or false for failure
 *
 * @Note         pOutput and pInput must be 8-byte aligned.
 *
 ****************************************************************************/
bool FFTComplex(AFLOAT_t *pOutput, const AFLOAT_t *pInput, int log2N);

/************************************************************************//**
 * IFFTComplex()
 ****************************************************************************
 * @brief        Computes inverse complex FFT.
 *
 * @details
 *       Supported range 3 <= log2_N <= 16,
 *       Here, log2_N is Base-2 log of number of FFT points, N.
 *
 * Computation time:
 *
 * |log2_N |    N     |  Cycles  |
 * |:-----:|:--------:|:--------:|
 * |     3 |        8 |      141 |
 * |     4 |       16 |      267 |
 * |     5 |       32 |      420 |
 * |     6 |       64 |      878 |
 * |     7 |      128 |     1747 |
 * |     8 |      256 |     3613 |
 * |     9 |      512 |     7687 |
 * |    10 |     1024 |    16023 |
 * |    11 |     2048 |    34408 |
 * |    12 |     4096 |    71696 |
 * |    13 |     8192 |   153415 |
 * |    14 |    16384 |   318799 |
 * |    15 |    32768 |   678322 |
 * |    16 |    65536 |  1405242 |
 *
 * @param[out]   *pOutput    Pointer to output buffer.
 * @param[in]    *pInput     Pointer to input buffer.  Can be same as output buffer.
 * @param[in]    log2N       Base-2 log of number of FFT points, N.
 *
 * @return       true for success or false for failure
 *
 * @Note         pOutput and pInput must be 8-byte aligned.
 *
 ****************************************************************************/
bool IFFTComplex(AFLOAT_t *pOutput, const AFLOAT_t *pInput, int log2N);

/************************************************************************//**
 * FFTReal()
 ****************************************************************************
 * @brief        Computes  forward FFT on a real-only input.
 *
 * @details
 *       Supported range 4 <= log2_N <= 17,
 *       Here, log2_N is Base-2 log of number of FFT points, N.
 *
 * Computation time:
 *
 * |log2_N |    N     |  Cycles  |
 * |:-----:|:--------:|:--------:|
 * |     4 |       16 |      216 |
 * |     5 |       32 |      369 |
 * |     6 |       64 |      578 |
 * |     7 |      128 |     1148 |
 * |     8 |      256 |     2241 |
 * |     9 |      512 |     4555 |
 * |    10 |     1024 |     9525 |
 * |    11 |     2048 |    19653 |
 * |    12 |     4096 |    41622 |
 * |    13 |     8192 |    86078 |
 * |    14 |    16384 |   182133 |
 * |    15 |    32768 |   376189 |
 * |    16 |    65536 |   793056 |
 * |    17 |   131072 |  1634664 |
 *
 * @param[out]   *pOutput    Pointer to output buffer.
 *                           The complex conjugate symmetric output is formatted as:
 *                           pOutput[0] = real-only bin 0 (ie, DC)
 *                           pOutput[1] = real-only bin N/2 (ie, Nyquist)
 *                           pOutput[2] = real part of bin 1
 *                           pOutput[3] = imag part of bin 1
 *                              :
 *                              :
 *                           pOutput[N-2] = real part of bin N/2-1
 *                           pOutput[N-1] = imag part of bin N/2-1
 * @param[in]    *pInput     Pointer to input buffer.  Can be same as output buffer.
 *                           Real input should be provided as it is.
 *                           Input should not be interleaved.
 * @param[in]    log2N       Base-2 log of number of FFT points, N.
 *
 * @return       true for success or false for failure
 *
 * @Note         pOutput and pInput must be 8-byte aligned.
 *
 ****************************************************************************/
bool FFTReal(AFLOAT_t *pOutput, const AFLOAT_t *pInput, int log2N);

/************************************************************************//**
 * IFFTReal()
 ****************************************************************************
 * Computes inverse FFT on complex conjugate symmetric input, resulting in
 * real-only output.
 *
 * @details
 *       Supported range 4 <= log2_N <= 17,
 *       Here, log2_N is Base-2 log of number of FFT points, N.
 *
 * Computation time:
 *
 * |log2_N |    N     |  Cycles  |
 * |:-----:|:--------:|:--------:|
 * |     4 |       16 |      221 |
 * |     5 |       32 |      375 |
 * |     6 |       64 |      584 |
 * |     7 |      128 |     1154 |
 * |     8 |      256 |     2247 |
 * |     9 |      512 |     4561 |
 * |    10 |     1024 |     9531 |
 * |    11 |     2048 |    19659 |
 * |    12 |     4096 |    41628 |
 * |    13 |     8192 |    86084 |
 * |    14 |    16384 |   182139 |
 * |    15 |    32768 |   376195 |
 * |    16 |    65536 |   793062 |
 * |    17 |   131072 |  1634670 |
 *
 * @param[out]   *pOutput    Pointer to output buffer.
 * @param[in]    *pInput     Pointer to input buffer.  Can be same as output buffer.
 *                           The input is assumed to be formatted as:
 *                           pInput[0] = real-only bin 0 (ie, DC)
 *                           pInput[1] = real-only bin N/2 (ie, Nyquist)
 *                           pInput[2] = real part of bin 1
 *                           pInput[3] = imag part of bin 1
 *                              :
 *                              :
 *                           pInput[N-2] = real part of bin N/2-1
 *                           pInput[N-1] = imag part of bin N/2-1
 * @param[in]    log2N       Base-2 log of number of FFT points, N.
 *
 * @return       true for success or false for failure
 *
 * @Note         pOutput and pInput must be 8-byte aligned.
 *
 ****************************************************************************/
bool IFFTReal(AFLOAT_t *pOutput, const AFLOAT_t *pInput, int log2N);


#ifdef __cplusplus
}
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_FFT_H__ */



/* End of File */

