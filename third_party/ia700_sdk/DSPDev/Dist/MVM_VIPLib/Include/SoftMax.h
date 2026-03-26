/************************************************************************//**
 * @file    MVM_VIPLib/Include/SoftMax.h
 *
 * @brief   SoftMax interface.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_SOFTMAX_H__
#define __FILE_SOFTMAX_H__

/**************************************************************************//**
 * @addtogroup hml_ml
 * @{
 *****************************************************************************/

/****************************************************************************
 * Includes
 ****************************************************************************/
#include "DeltaPlatform.h"
#include "hemilite_fr32_utils.h"
#include "TIE_defs.h"

/****************************************************************************
 * Definitions
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/
/************************************************************************//**
* SoftMax1
****************************************************************************
* @brief        Scalar computation of softmax function  for known sum factor
*               \f$ f(x)_j = \frac{e(x_j)}{\sum_{k=1}^{K}exp(x_k)} for j = 1, ..., K\f$
* @param[in]    x           Scalar input
* @param[in]    sum         Scalar input sum
*
* @return       Softmax (exp(x+sum))
*
****************************************************************************/
#ifdef _MSC_VER
#pragma warning( disable : 4190)
#endif
_AI fr32 SoftMax1(fr32 x, fr32 sum)
{
	fr32 y;
	x = fadds(x, sum, 0); // x + sum
	y = fmuls(x, FR32_LOG2_e, 0);
	y = pow2(y);
	return y;
}
#ifdef _MSC_VER
#pragma warning( default : 4190)
#endif

	
/************************************************************************//**
 * SoftMaxV
 ****************************************************************************
 * @brief        Vector computation of softmax 
 *               \f$ f(x)_j = \frac{e(x_j)}{\sum_{k=1}^{K}exp(x_k)} for j = 1, ..., K\f$
 *
 * Computation time:
 *
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |     180   |
 * |    32  |     280   |
 * |    64  |     480   |
 * |   128  |     880   |
 * |   256  |    1680   |
 *
 * @param[out]   *yAflt      n-element afloat output vector.
 * @param[in]    *xAflt      n-element afloat input vector.
 * @param[in]    n           Number of elements in x and y.
 *
 ****************************************************************************/
void SoftMaxV(AFLOAT_t *yAflt, AFLOAT_t *xAflt, int n);

#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_SOFTMAX_H__ */
