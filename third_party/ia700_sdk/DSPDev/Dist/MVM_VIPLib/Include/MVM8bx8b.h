/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVM8bx8b.h
 *
 * @brief   Matrix vector multiplication interface: 8 bits x 8 bits
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MVM_8BX8B_H__
#define __FILE_MVM_8BX8B_H__

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
 * MVM8bx8b()
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
 * |     32 |     32 |       504 |
 * |     32 |     64 |       664 |
 * |     32 |    128 |       984 |
 * |     32 |    256 |      1624 |
 * |     32 |    512 |      2904 |
 * |     32 |   1024 |      5464 |
 * |     64 |     32 |       968 |
 * |     64 |     64 |      1288 |
 * |     64 |    128 |      1928 |
 * |     64 |    256 |      3208 |
 * |     64 |    512 |      5768 |
 * |     64 |   1024 |     10888 |
 * |    128 |     32 |      1896 |
 * |    128 |     64 |      2536 |
 * |    128 |    128 |      3816 |
 * |    128 |    256 |      6376 |
 * |    128 |    512 |     11496 |
 * |    128 |   1024 |     21736 |
 * |    256 |     32 |      3752 |
 * |    256 |     64 |      5032 |
 * |    256 |    128 |      7592 |
 * |    256 |    256 |     12712 |
 * |    256 |    512 |     22952 |
 * |    256 |   1024 |     43432 |
 * |    512 |     32 |      7464 |
 * |    512 |     64 |     10024 |
 * |    512 |    128 |     15144 |
 * |    512 |    256 |     25384 |
 * |    512 |    512 |     45864 |
 * |    512 |   1024 |     86824 |
 * |   1024 |     32 |     14888 |
 * |   1024 |     64 |     20008 |
 * |   1024 |    128 |     30248 |
 * |   1024 |    256 |     50728 |
 * |   1024 |    512 |     91688 |
 * |   1024 |   1024 |    173608 |
 *
 * @param[out]      *yAflt          pointer to m-element afloat result of Ax
 * @param[in]       *x              8-bit samples (Q7 if signed, Q8 otherwise), 4-byte aligned pointer
 * @param[in]       *A              8-bit coefficients (Q7 if signed, Q8 otherwise), 4-byte aligned pointer
 * @param[in]       m               number of rows in A. MORE EFFICIENT if multiple of 8
 * @param[in]       n               n: number of columns in A (number of elements in x). MORE EFFICIENT if multiple of 8
 * @param[in]       signs           indicates if input is in signed or unsigned format
 *
 * @note
 *              Only signs bit0, bit1 is considered as below; rest all bits are ignored\n
 *              if signs bit0 is set : The coefficients are signed;
 *              otherwise : The coefficients are unsigned\n
 *              if signs bit1 is set : The samples are signed;
 *              otherwise : The samples are unsigned\n
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *
 ****************************************************************************/
int MVM8bx8b(AFLOAT_t *yAflt, const int8v4_aligned4 *x, const int8v4_aligned4 *A, int m, int n, int signs);
int MVM8bx8bAccumulate(fr32 *y, const fr32 *yIn, const int8v4_aligned4 *x, const int8v4_aligned4 *A, int m, int n, int signs, int yInExp, int AxExp);

#ifdef __cplusplus
};
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_8BX8B_H__ */



/* End of File */

