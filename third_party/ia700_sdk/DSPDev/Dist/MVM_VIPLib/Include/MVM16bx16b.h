/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVM16bx16b.h
 *
 * @brief   Matrix vector multiplication interface: 16 bits x 16 bits
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MVM_16BX16B_H__
#define __FILE_MVM_16BX16B_H__

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



/****************************************************************************
 * Constants
 ****************************************************************************/
#define MVM16BX16B_MAXSAMPLES 1024   // Maximum number of samples supported
#define MVM16BX16B_ERR_RETURN -1000

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * MVM16bx16b()
 ****************************************************************************
 * @brief       matrix vector multiply
 *
 * @details
 *       Multiplication on Matrix of [m x n] with Vector of [n x 1]
 *
 * Computation time:
 *
 * |    m   |    n   |   Cycles  |
 * |:------:|:------:|:---------:|
 * |     32 |     32 |      3918 |
 * |     32 |     64 |      5122 |
 * |     32 |    128 |      7530 |
 * |     32 |    256 |     12346 |
 * |     32 |    512 |     22010 |
 * |     32 |   1024 |     41338 |
 * |     64 |     32 |      7490 |
 * |     64 |     64 |      9714 |
 * |     64 |    128 |     14162 |
 * |     64 |    256 |     23058 |
 * |     64 |    512 |     40916 |
 * |     64 |   1024 |     76626 |
 * |    128 |     32 |     14634 |
 * |    128 |     64 |     18896 |
 * |    128 |    128 |     27428 |
 * |    128 |    256 |     44482 |
 * |    128 |    512 |     78724 |
 * |    128 |   1024 |    147204 |
 * |    256 |     32 |     28918 |
 * |    256 |     64 |     37262 |
 * |    256 |    128 |     53956 |
 * |    256 |    256 |     87330 |
 * |    256 |    512 |    154340 |
 * |    256 |   1024 |    288360 |
 * |    512 |     32 |     57490 |
 * |    512 |     64 |     74000 |
 * |    512 |    128 |    107012 |
 * |    512 |    256 |    173028 |
 * |    512 |    512 |    305572 |
 * |    512 |   1024 |    570670 |
 * |   1024 |     32 |    114644 |
 * |   1024 |     64 |    147468 |
 * |   1024 |    128 |    213128 |
 * |   1024 |    256 |    344420 |
 * |   1024 |    512 |    608038 |
 * |   1024 |   1024 |   1135292 |
 *
 * @param[out]      *yAflt          pointer to m-element afloat result of Ax
 * @param[in]       *x              16-bit samples (Q15), 4-byte aligned pointer
 * @param[in]       *A              16-bit coefficients (Q15), 4-byte aligned pointer
 * @param[in]       m               number of rows in A. MORE EFFICIENT if multiple of 8
 * @param[in]       n               n: number of columns in A (number of elements in x). MORE EFFICIENT if multiple of 8
 *
 * @note
 *              IF N > MVM16BX16B_MAXSAMPLES NO OUTPUT IS GENERATED\n
 *              *A Shown as pointing to 8 bits because byte deinterleaving occurs with coefficient mapping
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *              IF n > MVM16BX16B_MAXSAMPLES THE RETURNED VALUE IS MVM16BX16B_ERR_RETURN
 *
 ****************************************************************************/
int MVM16bx16b(AFLOAT_t *yAflt, const int16v2_aligned4 *x, const int8v4_aligned4 *A, int m, int n);
int MVM16bx16bAccumulate(fr32 *y, const fr32 *yIn, const int16v2_aligned4 *x, const int8v4_aligned4 *A, int m, int n, int yInExp, int AxExp);

#ifdef __cplusplus
};
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_16BX16B_H__ */



/* End of File */

