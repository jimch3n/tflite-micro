/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVMAfloat.h
 *
 * @brief   Matrix vector multiplication interface: Afloat
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MVM_AFLOAT_H__
#define __FILE_MVM_AFLOAT_H__

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
 * MVMAfloat()
 ****************************************************************************
 * @brief       matrix vector multiply for afloat type
 *
 * @details
 *       Multiplication on Matrix of [m x n] with Vector of [n x 1]
 *
 * Computation time:
 *
 * |    m   |    n   |   Cycles  |
 * |:------:|:------:|:---------:|
 * |     32 |     32 |      1779 |
 * |     32 |     64 |      3427 |
 * |     32 |    128 |      6723 |
 * |     32 |    256 |     13315 |
 * |     32 |    512 |     26499 |
 * |     32 |   1024 |     52867 |
 * |     64 |     32 |      2851 |
 * |     64 |     64 |      5523 |
 * |     64 |    128 |     10867 |
 * |     64 |    256 |     21555 |
 * |     64 |    512 |     42931 |
 * |     64 |   1024 |     85683 |
 * |    128 |     32 |      4995 |
 * |    128 |     64 |      9715 |
 * |    128 |    128 |     19155 |
 * |    128 |    256 |     38035 |
 * |    128 |    512 |     75795 |
 * |    128 |   1024 |    151315 |
 * |    256 |     32 |      9283 |
 * |    256 |     64 |     18099 |
 * |    256 |    128 |     35731 |
 * |    256 |    256 |     70995 |
 * |    256 |    512 |    141523 |
 * |    256 |   1024 |    282579 |
 * |    512 |     32 |     17859 |
 * |    512 |     64 |     34867 |
 * |    512 |    128 |     68883 |
 * |    512 |    256 |    136915 |
 * |    512 |    512 |    272979 |
 * |    512 |   1024 |    545107 |
 * |   1024 |     32 |     35011 |
 * |   1024 |     64 |     68403 |
 * |   1024 |    128 |    135187 |
 * |   1024 |    256 |    268755 |
 * |   1024 |    512 |    535891 |
 * |   1024 |   1024 |   1070163 |
 *
 * @param[out]      *yAflt          pointer to m-element afloat result of Ax
 * @param[in]       *xAflt          pointer to afloat samples within size n
 * @param[in]       *AAflt          pointer to afloat coefficients within size m*n
 * @param[in]       m               number of rows in A. MORE EFFICIENT if multiple of 4
 * @param[in]       n               n: number of columns in A (number of elements in x). MORE EFFICIENT if multiple of 4
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *
 ****************************************************************************/
int MVMAfloat(AFLOAT_t *y, const AFLOAT_t *x, const AFLOAT_t *A, int m, int n);


/************************************************************************//**
 * MVMAfloatAccumulate()
 ****************************************************************************
 * @brief       matrix vector multiply and Accumulate for afloat type
 *
 * @details
 *       Multiplication on Matrix of [m x n] with Vector of [n x 1]
 *
 * Computation time:
 *
 * |    m   |    n   |   Cycles  |
 * |:------:|:------:|:---------:|
 * |     32 |     32 |       746 |
 * |     32 |     64 |      1046 |
 * |     32 |    128 |      1686 |
 * |     32 |    256 |      2966 |
 * |     32 |    512 |      5526 |
 * |     32 |   1024 |     10646 |
 * |     64 |     32 |      1398 |
 * |     64 |     64 |      2038 |
 * |     64 |    128 |      3318 |
 * |     64 |    256 |      5878 |
 * |     64 |    512 |     10998 |
 * |     64 |   1024 |     21238 |
 * |    128 |     32 |      2742 |
 * |    128 |     64 |      4022 |
 * |    128 |    128 |      6582 |
 * |    128 |    256 |     11702 |
 * |    128 |    512 |     21942 |
 * |    128 |   1024 |     42422 |
 * |    256 |     32 |      5430 |
 * |    256 |     64 |      7990 |
 * |    256 |    128 |     13110 |
 * |    256 |    256 |     23350 |
 * |    256 |    512 |     43830 |
 * |    256 |   1024 |     84790 |
 * |    512 |     32 |     10806 |
 * |    512 |     64 |     15926 |
 * |    512 |    128 |     26166 |
 * |    512 |    256 |     46646 |
 * |    512 |    512 |     87606 |
 * |    512 |   1024 |    169526 |
 * |   1024 |     32 |     21558 |
 * |   1024 |     64 |     31798 |
 * |   1024 |    128 |     52278 |
 * |   1024 |    256 |     93238 |
 * |   1024 |    512 |    175158 |
 * |   1024 |   1024 |    338998 |
 *
 * @param[out]      *yOut           pointer to m-element fr32 result of Ax
 * @param[in]       *yIn            pointer to m-element fr32 int of Ax
 * @param[in]       *x              pointer to afloat samples within size n
 * @param[in]       *A              pointer to afloat coefficients within size m*n
 * @param[in]       m               number of rows in A. MORE EFFICIENT if multiple of 4
 * @param[in]       n               n: number of columns in A (number of elements in x). MORE EFFICIENT if multiple of 4
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *
 ****************************************************************************/
void MVMAfloatAccumulate(fr32* yOut, const fr32* yIn, const fr32* x, const fr32* A, int m, int n);
#ifdef __cplusplus
};
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_AFLOAT_H__ */



/* End of File */

