/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVM8bx4b.h
 *
 * @brief   Matrix vector multiplication interface: 8 bits x 4 bits.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_MVM_8BX4B_H__
#define __FILE_MVM_8BX4B_H__

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

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * MVM8bx4b
 ****************************************************************************
 * @brief        Performs 8-bit matrix x 4-bit vector
 *
 * Computation time:
 *
 * |    n   |    m   |   Cycles |
 * |:------:|:------:|:--------:|
 * |    32  |    32  |     529  |
 * |    32  |    64  |     753  |
 * |    32  |   128  |    1201  |
 * |    32  |   256  |    2097  |
 * |    32  |   512  |    3889  |
 * |    32  |  1024  |    7473  |
 * |    64  |    32  |    1017  |
 * |    64  |    64  |    1465  |
 * |    64  |   128  |    2361  |
 * |    64  |   256  |    4153  |
 * |    64  |   512  |    7737  |
 * |    64  |  1024  |   14905  |
 * |   128  |    32  |    1993  |
 * |   128  |    64  |    2889  |
 * |   128  |   128  |    4681  |
 * |   128  |   256  |    8265  |
 * |   128  |   512  |   15433  |
 * |   128  |  1024  |   29769  |
 * |   256  |    32  |    3945  |
 * |   256  |    64  |    5737  |
 * |   256  |   128  |    9321  |
 * |   256  |   256  |   16489  |
 * |   256  |   512  |   30825  |
 * |   256  |  1024  |   59497  |
 * |   512  |    32  |    7849  |
 * |   512  |    64  |   11433  |
 * |   512  |   128  |   18601  |
 * |   512  |   256  |   32937  |
 * |   512  |   512  |   61609  |
 * |   512  |  1024  |  118953  |
 * |  1024  |    32  |   15657  |
 * |  1024  |    64  |   22825  |
 * |  1024  |   128  |   37161  |
 * |  1024  |   256  |   65833  |
 * |  1024  |   512  |  123177  |
 * |  1024  |  1024  |  237865  | 
 *
 * @param[out]   *yAflt      pointer to m-element afloat result of Ax
 * @param[in]    *x          8-bit samples (Q7 if signed, Q8 otherwise),
 *                           4-byte aligned pointer
 * @param[in]    *A          Coefficient matrix, 4-byte aligned pointer.
 *                           Each of two sets of 8 4-bit coefficients is
 *                           interleaved to take up 8 bytes.
 * @param[in]    m           Number of rows in A: multiple of 4.
 * @param[in]    n           Number of columns in A: multiple of 4.
 * @param[in]    sign        0: unsigned format
 *                           1: signed format
 *
 * @return       Maximum output exponent that could be used in subsequent scaling.
 *
 ****************************************************************************/
int MVM8bx4b(AFLOAT_t *yAflt, const int8v4_aligned4 *x, const int8v4_aligned4 *A, int m, int n, int sign);

#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_8BX4B_H__ */
