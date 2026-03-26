/************************************************************************//**
 * @file    HMD1A/MachineLearning/Include/MVM16bx8bFast.h
 *
 * @brief   Matrix vector multiplication interface: 16 bits x 8 bits
 *
 * $DateTime: 2021/05/25 05:34:21 $
 * $Revision: #4 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MVM_16BX8B_FAST_H__
#define __FILE_MVM_16BX8B_FAST_H__

/**************************************************************************//**
 * @addtogroup hml_ml
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
#include "DeltaPlatform.h"
#include "TIE_defs.h"
#include "MachineLearningDefs.h"




/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * MVM16bx8bFast()
 ****************************************************************************
 * @brief       Matrix Vector Multiplication ( faster version of MVM16bx8b() )
 *
 * @details     Performs multiplication on 16-bit Matrix A(m x n) with 8-bit Vector x(n x 1)\n
 *              The samples(bytes) of the input vector x are de-interleaved and placed in tmp.\n
 *
 * @param[out]      *y              Pointer to m-element fr32 - result of A*x
 * @param[in]       *tmp            Temporary buffer to store de-interleaved x, 4-byte aligned pointer.
 * @param[in]       *x              16-bit samples (Q15), 4-byte aligned pointer.
 * @param[in]       *A              Coefficient matrix with 8-bit coefficients (Q7), 4-byte aligned pointer.
 * @param[in]       m               Number of rows in A. MORE EFFICIENT if the number is multiple of 8.
 * @param[in]       n               Number of columns in A (equal to number of elements in x). MORE EFFICIENT if the number is multiple of 8.
 *
 * @return
 * Maximum output exponent that could be used in subsequent scaling.
 *
 * @note
 * 1.This function expects Coefficient matrix A to be in a specific order which can be obtained by calling the function 'Map8bitCoeffsForMVM()'\n
 * 2.DO NOT SET ANY COEFFICIENT TO 0x80\n
 * 3.Signed 0x80 x 0x80 multiplication is non-saturating. Therefore it will produce incorrect results.\n
 * 4.ONE OF THE FOLLOWING CONSTRAINTS MUST BE CHOSEN AND ADHERED TO, PRIOR TO CALLING THIS FUNCTION (THE SECOND ONE IS LOOSER BUT MORE COMPLICATED):\n
 *   i.  n <= 512\n
 *   ii. 64K > maximum sum over i of |Ai0| + |Ai1| + |Ai2| ...\n
 *       In other words, using Matlab notation: 64K > norm(A, Inf)\n
 * 5.In-place computation is not supported.\n
 * 6.No.of mac operations this function can handle is - TBU.\n
 * 7.Profile information (Computation time):\n
 *
 * |    m   |    n   |   Cycles  |
 * |:------:|:------:|:---------:|
 * |     32 |     32 |       897 |
 * |     32 |     64 |      1265 |
 * |     32 |    128 |      2001 |
 * |     32 |    256 |      3473 |
 * |     32 |    512 |      6417 |
 * |     64 |     32 |      1681 |
 * |     64 |     64 |      2369 |
 * |     64 |    128 |      3745 |
 * |     64 |    256 |      6497 |
 * |     64 |    512 |     12001 |
 * |    128 |     32 |      3249 |
 * |    128 |     64 |      4577 |
 * |    128 |    128 |      7233 |
 * |    128 |    256 |     12545 |
 * |    128 |    512 |     23169 |
 * |    256 |     32 |      6386 |
 * |    256 |     64 |      8994 |
 * |    256 |    128 |     14210 |
 * |    256 |    256 |     24642 |
 * |    256 |    512 |     45506 |
 * |    512 |     32 |     12658 |
 * |    512 |     64 |     17826 |
 * |    512 |    128 |     28162 |
 * |    512 |    256 |     48834 |
 * |    512 |    512 |     90178 |
 * |   1024 |     32 |     25202 |
 * |   1024 |     64 |     35490 |
 * |   1024 |    128 |     56066 |
 * |   1024 |    256 |     97218 |
 * |   1024 |    512 |    179522 |
 *
 ****************************************************************************/
int MVM16bx8bFast(fr32 *y, int16v2_aligned4 *tmp, const int16v2_aligned4 *x, const int8v4_aligned4 *A, int m, int n);
int MVM16bx8bAccumulateFast(fr32 *y, const fr32 *yIn, int16v2_aligned4 *tmp, const int16v2_aligned4 *x, const int8v4_aligned4 *A, int m, int n, int yInExp, int AxExp);

#ifdef __cplusplus
};
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_16BX8B_FAST_H__ */



/* End of File */

