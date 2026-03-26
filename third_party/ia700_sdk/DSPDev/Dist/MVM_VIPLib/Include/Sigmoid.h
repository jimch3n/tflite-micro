/************************************************************************//**
 * @file    MVM_VIPLib/Include/Sigmoid.h
 *
 * @brief   Sigmoid interface.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_SIGMOID_H__
#define __FILE_SIGMOID_H__

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
#define SigmoidConstTable_One 1
#define SigmoidConstTable_Log2_Of_e 9

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Enum used to decide which activation function is used in sigmoid
 ****************************************************************************/
typedef enum
{
	SIGMOID_REG = 0,		/*!< Regular sigmoid, Please refere @ref SigmoidV_Full for activation function */
	SIGMOID_HARD = 1,		/*!< Hard sigmoid, Please refere @ref SigmoidV_Hard for activation function */
	NUM_SIGMOID_ACTIVATIONS,
} sigmoid_act_t;


/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * Sigmoid1
 ****************************************************************************
 * @brief        Scalar computation of logistic function 
 *               \f$ f(x) = \frac{1}{1 + exp(-x)} \f$
 *
 * @param[in]    x           Scalar input
 *
 * @return       Sigmoid (logistic function)
 *
 ****************************************************************************/
#ifdef _MSC_VER
#pragma warning( disable : 4190)
#endif
_AI fr32 Sigmoid1(fr32 x)
{
    fr32 fac = seta_fr(SigmoidConstTable_Log2_Of_e, 0);
    fr32 one = seta_fr(SigmoidConstTable_One, 0);
    x = fmuls(fac, x, 1);
    x = pow2(x);
    x = fadds(one, x, 0);
    x = inv(x);

    return x;
}
#ifdef _MSC_VER
#pragma warning( default : 4190)
#endif

/************************************************************************//**
 * SigmoidV_Full()
 ****************************************************************************
 * @brief        Vector computation of logistic function, 
 *               \f$ f(x) = \frac{1}{1 + exp(-x)} \f$
 *
 * @param[out]   *y          n-element fr32 output vector.
 * @param[in]    *x          n-element fr32 input vector.
 * @param[in]    n           Number of elements in x and y.
 *
 * @note
 * Computation time:\n
 *
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |     79    |
 * |    32  |    127    |
 * |    64  |    223    |
 * |   128  |    415    |
 * |   256  |    799    |
 *
 ****************************************************************************/
void SigmoidV_Full(fr32 *y, fr32 *x, int n);



/************************************************************************//**
 * SigmoidV_Hard()
 ****************************************************************************
 * @brief        Vector computation of logistic function <br>
 *               \f$ y = 0.2 * x + 0.5 \f$<br>
 *               \f$ y = max(0, (min(1, x))) \f$
 *
 * @param[out]   *y          n-element fr32 output vector.
 * @param[in]    *x          n-element fr32 input vector.
 * @param[in]    n           Number of elements in x and y.
 *
 * @note
 * Computation time:\n
 *
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |     65    |
 * |    32  |     93    |
 * |    64  |    149    |
 * |   128  |    261    |
 * |   256  |    485    |
 *
 ****************************************************************************/
void SigmoidV_Hard(fr32 *y, fr32 *x, int n);



/************************************************************************//**
 * SigmoidV()
 ****************************************************************************
 * @brief        Vector computation of sigmoid function (Activation function is based on sig_act)
 *
 * @param[out]   *y          n-element fr32 output vector.
 * @param[in]    *x          n-element fr32 input vector.
 * @param[in]    n           Number of elements in x and y.
 * @param[in]    sig_act     Sigmoid activation function to be used, Please refere @ref sigmoid_act_t
 *
 * @return       0 if successful, else error
 ****************************************************************************/
int SigmoidV(fr32 *y, fr32 *x, int n, sigmoid_act_t sig_act);


#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_SIGMOID_H__ */
