/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVM16bx4b.h
 *
 * @brief   Matrix vector multiplication interface: 16 bits x 4 bits.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_MVM_16BX4B_H__
#define __FILE_MVM_16BX4B_H__

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
 * Definitions
 ****************************************************************************/
#define MVM16BX4B_MAXSAMPLES 1024   // Maximum number of samples supported
#define MVM16BX4B_ERR_RETURN -1000

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * MVM16bx4b
 ****************************************************************************
 * @brief        Performs 16-bit matrix x 4-bit vector
 *
 * Computation time:
 *
 * |    n   |    m   |   Cycles |
 * |:------:|:------:|:--------:|
 * |    32  |    32  |    1195  |
 * |    32  |    64  |    1819  |
 * |    32  |   128  |    3067  |
 * |    32  |   256  |    5563  |
 * |    32  |   512  |   10555  |
 * |    32  |  1024  |   20539  |
 * |    64  |    32  |    2139  |
 * |    64  |    64  |    3211  |
 * |    64  |   128  |    5355  |
 * |    64  |   256  |    9643  |
 * |    64  |   512  |   18219  |
 * |    64  |  1024  |   35371  |
 * |   128  |    32  |    4027  |
 * |   128  |    64  |    5995  |
 * |   128  |   128  |    9931  |
 * |   128  |   256  |   17803  |
 * |   128  |   512  |   33547  |
 * |   128  |  1024  |   65035  |
 * |   256  |    32  |    7803  |
 * |   256  |    64  |   11563  |
 * |   256  |   128  |   19083  |
 * |   256  |   256  |   34123  |
 * |   256  |   512  |   64203  |
 * |   256  |  1024  |  124363  |
 * |   512  |    32  |   15355  |
 * |   512  |    64  |   22699  |
 * |   512  |   128  |   37387  |
 * |   512  |   256  |   66763  |
 * |   512  |   512  |  125515  |
 * |   512  |  1024  |  243019  |
 * |  1024  |    32  |   30459  |
 * |  1024  |    64  |   44971  |
 * |  1024  |   128  |   73995  |
 * |  1024  |   256  |  132043  |
 * |  1024  |   512  |  248139  |
 * |  1024  |  1024  |  480331  |
 *
 * @param[out]   *yAflt      pointer to m-element afloat result of Ax
 *                           IF n > MVM16BX4B_MAXSAMPLES NO OUTPUT IS GENERATED.
 * @param[in]    *x          16-bit samples (Q15), 4-byte aligned pointer
 * @param[in]    *A          Coefficient matrix, 4-byte aligned pointer.
 *                           Each of two sets of 8 4-bit coefficients is
 *                           interleaved to take up 8 bytes.
 * @param[in]    m           Number of rows in A: multiple of 4.
 * @param[in]    n           Number of columns in A: multiple of 4.
 *
 * @return       Maximum output exponent that could be used in subsequent scaling.
 *               IF n > MVM16BX4B_MAXSAMPLES THE RETURNED VALUE IS MVM16BX4B_ERR_RETURN.
 *
 ****************************************************************************/
int MVM16bx4b(AFLOAT_t *yAflt, const int16v2_aligned4 *x, const int8v4_aligned4 *A, int m, int n);

#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_16BX4B_H__ */
