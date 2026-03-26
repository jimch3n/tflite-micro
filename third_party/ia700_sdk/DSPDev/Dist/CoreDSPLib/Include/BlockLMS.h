/************************************************************************//**
 * @file    BlockLMS.h
 *
 * @brief   BlockLMS interface file.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #7 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_BLOCKLMS_H__
#define __FILE_BLOCKLMS_H__

/**************************************************************************//**
 * @addtogroup hml_core_dsp
 * @{
 *****************************************************************************/

#ifdef __XTENSA__
#include "TIE_include.h"
#else
#include "cstubs.h"
#endif

#include <stdint.h>
#include "TIE_defs.h"

#ifdef __cplusplus
extern "C" {
#endif



 /****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * BlockLMS()
 ****************************************************************************
 * @brief        Computes the LMS of a Real valued input signals 
 *               and places the result in output buffer
 *
 * @details
 *
 * Design:
 *     Normalized learning rate
 *          mu_norm = mu / (sum(d*d) + norm)
 *
 *     Error estimation
 *         for i=0:N-1
 *             e(i) = d(i)
 *             for j=0:M-1
 *                 e(i) = e(i) - w(M-1-j) * x(i+j)
 *             end
 *         end
 *
 *     Filter tap update
 *         for j=0:M-1
 *             sum = 0;
 *             for i=0:N-1
 *                 sum = sum + e(i) * x(i+j)
 *             end
 *             w(M-1-j) = w(M-1-j) + mu_norm * sum
 *         end
 *
 * Computation time:   For few input lengths are provided below for reference
 * 
 * |    N  |    M  | Cycles |
 * |:-----:|:-----:|:------:|
 * |   256 |    16 |   6711 |
 * |   256 |    32 |  11171 |
 * |   256 |    64 |  20091 |
 *
 * @param[out]     *pE    Estimated error, size N.
 * @param[inout]   *pW    Original and updated filter weights. Size M and reverse sequence.
 * @param[in]      *pD    Desired filter output, size N.
 * @param[in]      *pX    Filter tap inputs vector, size (N + M - 1). MUST BE 8-BYTE ALIGNED.
 * @param[in]      norm   Normalization parameter. (sum(d*d) + norm).
 * @param[in]      mu     Adaptation coefficient(step size).
 * @param[in]      N      Size of filter output. Must be multiple of 8.
 * @param[in]      M      Size of weights. Must be multiple of 8.
 *
 * @return      None
 *
 ****************************************************************************/
void BlockLMS(AFLOAT_t *pE, AFLOAT_t *pW, AFLOAT_t *pD, AFLOAT_t *pX, AFLOAT_t norm, AFLOAT_t mu, int N, int M);

#ifdef __cplusplus
}
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif /* __FILE_BLOCKLMS_H__ */



/* End of File */

