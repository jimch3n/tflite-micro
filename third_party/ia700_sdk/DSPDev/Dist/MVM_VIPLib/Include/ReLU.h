/************************************************************************//**
 * @file    MVM_VIPLib/Include/ReLU.h
 *
 * @brief   ReLU interface.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_RELU_H__
#define __FILE_RELU_H__

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
#define ReluConstTable_Zero 0


#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * Relu1
 ****************************************************************************
 * @brief        Scalar computation of ReLU (retified linear unit) function 
 *               \f$ f(x) = max(0, x) \f$
 *
 * @param[in]    x           Scalar input
 *
 * @return       Relu result
 *
 ****************************************************************************/
#ifdef _MSC_VER
#pragma warning( disable : 4190)
#endif
_AI fr32 Relu1(fr32 x)
{
    fr32 zero = seta_fr(ReluConstTable_Zero,  0);

	x = max_fr(zero, x);

    return x;
}
#ifdef _MSC_VER
#pragma warning( default : 4190)
#endif

/************************************************************************//**
 * ReluV
 ****************************************************************************
 * @brief        Vector computation of ReLU (rectified linear unit) function 
 *               \f$ f(x) = max(0, x) \f$
 *
 * Computation time:
 *
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |     52    |
 * |    32  |     68    |
 * |    64  |    100    |
 * |   128  |    164    |
 * |   256  |    292    |
 *
 * @param[out]   *yAflt      n-element afloat output vector.
 * @param[in]    *xAflt      n-element afloat input vector.
 * @param[in]    n           Number of elements in x and y.
 *
 ****************************************************************************/
void ReLUV(AFLOAT_t *yAflt, AFLOAT_t *xAflt, int n);

#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_RELU_H__ */
