/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVM16bx8b.h
 *
 * @brief   Matrix vector multiplication interface: 16 bits x 8 bits
 *
 * $DateTime: 2019/04/17 20:42:30 $
 * $Revision: #6 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MVM_16BX8B_H__
#define __FILE_MVM_16BX8B_H__

/**************************************************************************//**
 * @addtogroup hml_ml
 * @{
 *****************************************************************************/

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
#define MVM16BX8B_MAXSAMPLES 1024   // Maximum number of samples supported
#define MVM16BX8B_ERR_RETURN -1000

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * MVM16bx8b()
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
 * |     32 |     32 |      2892 |
 * |     32 |     64 |      3580 |
 * |     32 |    128 |      4940 |
 * |     32 |    256 |      7756 |
 * |     32 |    512 |     13324 |
 * |     32 |   1024 |     24460 |
 * |     64 |     32 |      5428 |
 * |     64 |     64 |      6620 |
 * |     64 |    128 |      8972 |
 * |     64 |    256 |     13868 |
 * |     64 |    512 |     23532 |
 * |     64 |   1024 |     42860 |
 * |    128 |     32 |     10500 |
 * |    128 |     64 |     12700 |
 * |    128 |    128 |     17036 |
 * |    128 |    256 |     26092 |
 * |    128 |    512 |     43948 |
 * |    128 |   1024 |     79660 |
 * |    256 |     32 |     20644 |
 * |    256 |     64 |     24860 |
 * |    256 |    128 |     33164 |
 * |    256 |    256 |     50540 |
 * |    256 |    512 |     84780 |
 * |    256 |   1024 |    153260 |
 * |    512 |     32 |     40932 |
 * |    512 |     64 |     49180 |
 * |    512 |    128 |     65420 |
 * |    512 |    256 |     99436 |
 * |    512 |    512 |    166444 |
 * |    512 |   1024 |    300460 |
 * |   1024 |     32 |     81508 |
 * |   1024 |     64 |     97820 |
 * |   1024 |    128 |    129932 |
 * |   1024 |    256 |    197228 |
 * |   1024 |    512 |    329772 |
 * |   1024 |   1024 |    594860 |
 *
 * @param[out]      *yAflt          pointer to m-element afloat result of Ax
 * @param[in]       *x              16-bit samples (Q15), 4-byte aligned pointer
 * @param[in]       *A              8-bit coefficients (Q7 if signed, Q8 otherwise), 4-byte aligned pointer
 * @param[in]       m               number of rows in A. MORE EFFICIENT if multiple of 8
 * @param[in]       n               number of columns in A (number of elements in x). MORE EFFICIENT if multiple of 8
 * @param[in]       sign            coefficient sign format. 0: unsigned, 1: signed
 *
 * @note
 *              IF N > MVM16BX8B_MAXSAMPLES NO OUTPUT IS GENERATED
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *              IF n > MVM16BX8B_MAXSAMPLES THE RETURNED VALUE IS MVM16BX8B_ERR_RETURN
 *
 ****************************************************************************/
int MVM16bx8b(AFLOAT_t *yAflt, const int16v2_aligned4 *x, const int8v4_aligned4 *A, int m, int n, int sign);
int MVM16bx8bAccumulateFast(fr32 *y, const fr32 *yIn, int16v2_aligned4 *tmp, const int16v2_aligned4 *x, const int8v4_aligned4 *A, int m, int n, int yInExp, int AxExp);

#ifdef __cplusplus
};
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_16BX8B_H__ */



/* End of File */

