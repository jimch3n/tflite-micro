/************************************************************************//**
 * @file    MVM_VIPLib/Include/Tanh.h
 *
 * @brief   Tanh interface.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_TANH_H__
#define __FILE_TANH_H__

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
#define TanhConstTable_One 1
#define TanhConstTable_Two 2
#define TanhConstTable_Log2_Of_e 9

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * Tanh1
 ****************************************************************************
 * @brief        Scalar computation of hyperbolic tangent  
 *               \f$ f(x) = \frac{1 + exp(-2x)}{1 - exp(-2x)} \f$
 *
 * @param[in]    x           Scalar input
 *
 * @return       Tanh (hyperbolic tangent )
 *
 ****************************************************************************/
#ifdef _MSC_VER
#pragma warning( disable : 4190)
#endif
_AI fr32 Tanh1(fr32 x)
{
    fr32 fac = seta_fr(TanhConstTable_Log2_Of_e, 0);
    fr32 one = seta_fr(TanhConstTable_One, 0);
	fr32 two = seta_fr(TanhConstTable_Two, 0);
	fr32 denumer, numer, inv1;

	fac = fmuls(two, fac, 0);
	x = fmuls(fac, x, 0);
    x = pow2(x);
	denumer = fadds(one, x, 0);   // exp(2*x) +1
	numer = fadds(one, x, 1);     // exp(2*x) -1
	inv1 = inv(denumer);
	// Newton's method
	two = fmacs(two, inv1, denumer, 1); // 2 - (x/x)
	inv1 = fmuls(two, inv1, 0);
	x = fmuls(inv1, numer, 0);

    return x;
}
#ifdef _MSC_VER
#pragma warning( default : 4190)
#endif

/************************************************************************//**
 * TanhV
 ****************************************************************************
 * @brief        Vector computation of hyperbolic tangent 
 *               \f$ f(x) = \frac{1 + exp(-2x)}{1 - exp(-2x)} \f$
 *
 * Computation time:
 *
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |     127   |
 * |    32  |     211   |
 * |    64  |     379   |
 * |   128  |     715   |
 * |   256  |    1387   |
 *
 * @param[out]   *yAflt      n-element afloat output vector.
 * @param[in]    *xAflt      n-element afloat input vector.
 * @param[in]    n           Number of elements in x and y.
 *
 ****************************************************************************/
void TanhV(AFLOAT_t *yAflt, AFLOAT_t *xAflt, int n);

#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_TANH_H__ */
