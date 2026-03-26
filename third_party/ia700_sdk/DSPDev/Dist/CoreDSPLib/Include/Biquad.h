/************************************************************************//**
 * @file    Biquad.h
 *
 * @brief   Biquad and cascaded biquad filter interface file
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #7 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_BIQUAD_H__
#define __FILE_BIQUAD_H__

/**************************************************************************//**
 * @addtogroup hml_core_dsp
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
#include "TIE_defs.h"

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/****************************************************************************
 * Types
 ****************************************************************************/

/************************************************************************//**
 * BiquadCascadeState_t
 ****************************************************************************
 structure of the Cascaded Biquads filter.
 ****************************************************************************/
typedef struct
{
    int N;              //!< Number of Biquad to be cascaded
    AFLOAT_t *pCoeff;       //!< Points to 8-bytes aligned coefficent array of length 6*N
    AFLOAT_t *pState;       //!< Points to 8-bytes aligned delay/state array of length 2*N
} BiquadCascadeState_t;



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * InitBiquadCascade()
 ****************************************************************************
 * @brief       Initialize the state & coefficients of cascaded biquad filters
 *
 * @param[out]      *pInst          pointer for maintaining delay and coefficients
 * @param[in]       N               Number of biquads to be cascaded
 * @param[in]       *pCoeff         pointer to the 8-Byte aligned buffer of 6*N AFLOAT_t format coefficients
 * @param[in]       *pState         pointer to the 8-Byte aligned buffer of 2*N AFLOAT_t format delays
 *
 * @note
 *          Pass filter coefficient as : [for 1st Biquad, for 2nd Biquad, ...]\n
 *          ie [b00 b01 b02 a00 a01 a02,    b10 b11 b12 a10 a11 a12 ...]\n
 *          This function updates the coefficient in required format as :
 *          [-a02 (b02/b00-a02) -a01 (b01/b00-a01) b00 b00 , -a12 (b12/b10-a12) -a11 (b11/b10-a11) b10 b10]\n
 *
 * @return      Nothing
 *
 ****************************************************************************/
void InitBiquadCascade(BiquadCascadeState_t *pInst, AFLOAT_t *pCoeff, AFLOAT_t *pState, int N);

/************************************************************************//**
 * BiquadCascade()
 ****************************************************************************
 * @brief       Calculates a higher order IIR filter on real data and real coefficients by cascading Biquad filters
 *
 * @details
 *      Higher order IIR filter can be designed by cascading Biquad filters
 *      This function will work as higher order(multiple of 2) IIR filter
 *      Example:
 *              To design 6th order IIR filter, 3 biquads to be cascaded
 *
 *      Design:
 *              A single Biquad Filter is a 2nd order IIR Filter
 *              The filter is implemented with Direct Form - 2
 *              Equation: y(n) = b(0)*x(n) + b(1)*x(n-1) + b(2)*x(n-2) - a(1)*y(n-1) -a(2)*y(n-2)
 *              coef[] = {b0 b1 b2 a0 a1 a2}
 *              states[] = {x(n-1) x(n-2) y(n-1) y(n-2)}
 *
 *                                   Wn              B0
 *              Xn---------(-)----------------------->-------(+)---------> Yn
 *                          |                |                |
 *                          |                V                |
 *                          |             +-----+             |
 *                          |             |  -1 |             |
 *                          |             | Z   |             |
 *                          |             +-----+             |
 *                          |                |                |
 *                          |        A1      |       B1       |
 *                         (+)-------<--------------->-------(+)
 *                          |                |                |
 *                          |                V                |
 *                          |             +-----+             |
 *                          |             |  -1 |             |
 *                          |             | Z   |             |
 *                          |             +-----+             |
 *                          |                |                |
 *                          |        A2      |       B2       |
 *                         (+)-------<--------------->-------(+)
 *
 * Computation time:
 *
 * |         | frame size |   8   |  16   |   32   |   64   |  128   |  256   |   512   |  1024   |  2048  |
 * |:-------:|:----------:|:-----:|:-----:|:------:|:------:|:------:|:------:|: ----- :|:------ :|:------:|
 * |IIR order| Biquad Num |       |       |        |        |        |        |         |         |        |
 * |      2  |         1  |   86  |  107  |   147  |   227  |   387  |   707  |   1347  |   2627  |   5187 |
 * |      4  |         2  |  147  |  189  |   269  |   429  |   749  |  1389  |   2669  |   5229  |  10349 |
 * |      6  |         3  |  214  |  277  |   397  |   637  |  1117  |  2077  |   3997  |   7837  |  15517 |
 * |      8  |         4  |  281  |  365  |   525  |   845  |  1485  |  2765  |   5325  |  10445  |  20685 |
 * |     10  |         5  |  348  |  453  |   653  |  1053  |  1853  |  3453  |   6653  |  13053  |  25853 |
 * |     12  |         6  |  415  |  541  |   781  |  1261  |  2221  |  4141  |   7981  |  15661  |  31021 |
 * |     14  |         7  |  482  |  629  |   909  |  1469  |  2589  |  4829  |   9309  |  18269  |  36189 |
 * |     16  |         8  |  549  |  717  |  1037  |  1677  |  2957  |  5517  |  10637  |  20877  |  41357 |
 * |     18  |         9  |  616  |  805  |  1165  |  1885  |  3325  |  6205  |  11965  |  23485  |  46525 |
 * |     20  |        10  |  683  |  893  |  1293  |  2093  |  3693  |  6893  |  13293  |  26093  |  51693 |
 *
 * @param[in,out]   *pInst          pointer for maintaining delay and coefficients
 * @param[out]      *pOut           pointer to the 8-Byte aligned buffer of output
 * @param[in]       *pIn            pointer to the 4-Byte aligned buffer of input
 * @param[in]       size            number of the input samples, should be multiple of 4
 *
 * @note
 *          Pass coefficients as below format (ie use InitBiquadCascade() to convert them):\n
 *              [-a02 (b02/b00-a02) -a01 (b01/b00-a01) b00 b00 , -a12 (b12/b10-a12) -a11 (b11/b10-a11) b10 b10]\n
 *          pInst should have 8-Byte aligned 6*Number of biquads Coeffients\n
 *          pInst should have 8-Byte aligned 2*Number of biquads States/delays\n
 *
 * @return      true on success or false on failure
 *
 ****************************************************************************/
bool BiquadCascade(BiquadCascadeState_t *pInst, AFLOAT_t *pOut, AFLOAT_t *pIn, int size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif /* __FILE_BIQUAD_H__ */



/* End of File */

