/************************************************************************//**
 * @file    VIP.h
 *
 * @brief   Vector Inner Product (VIP) Library Functions Header file
 *
 * $DateTime: 2018/09/13 23:50:32 $
 * $Revision: #3 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_VIP_H__
#define __FILE_VIP_H__

/**************************************************************************//**
 * @defgroup hml_ml HemiLite Machine Learning library 
 * @{
 *****************************************************************************/

/****************************************************************************
 * Includes
 ****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * This header file contains the function prototypes to perform a Vector Inner Product (VIP). 
 * The main inputs are a sample vector and a coefficient vector (VIP).
 * Note the distinction between samples and coefficients:
 *  1. There is no reordering of the samples within the sample vector prior to function invocation.
 *  2. The coefficients need to be reordered prior to function invocation to enable efficient computation.
 *     The expectation is that the reordering is done once offline or infrequently at runtime.
 ****************************************************************************/


/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * VIP8bitSamples8bitCoeffsAFL()
 ****************************************************************************
 * @brief   Afloat Vector Inner Product (VIP): 8 bits x 8 bits
 *
 * @details
 *          Afloat Vector Inner Product on Matrix of [1 x n] with Vector of [n x 1]
 *
 * Computation time:
 * 
 * |    n   | Cycles |
 * |:------:|:------:|
 * |     32 |     49 |
 * |     64 |     58 |
 * |     96 |     66 |
 * |    128 |     74 |
 * |    160 |     82 |
 * |    192 |     90 |
 * |    224 |     98 |
 * |    256 |    106 |
 * |    288 |    114 |
 * |    320 |    122 |
 * |    352 |    130 |
 * |    384 |    138 |
 * |    416 |    146 |
 * |    448 |    154 |
 * |    480 |    162 |
 * |    512 |    170 |
 * |    544 |    178 |
 * |    576 |    186 |
 * |    608 |    194 |
 * |    640 |    202 |
 * |    672 |    210 |
 * |    704 |    218 |
 * |    736 |    226 |
 * |    768 |    234 |
 * |    800 |    242 |
 * |    832 |    250 |
 * |    864 |    258 |
 * |    896 |    266 |
 * |    928 |    274 |
 * |    960 |    282 |
 * |    992 |    290 |
 * |   1024 |    298 |
 *
 * @param[out]      *output         pointer to afloat result.
 * @param[in]       *samples        8-bit samples (Q7 if signed, Q8 otherwise), 8-byte aligned pointer to CHAR_t for 8-bit samples.
 * @param[in]       *coeffs         8-bit coefficients (Q7 if signed, Q8 otherwise), 8-byte aligned pointer to CHAR_t whether the
 *                                  input coefficients are 8 or 16 bits due to coefficient reordering has been done at the byte level.
 * @param[in]       n               n: number of columns in samples (number of elements in coeffs). Must be a multiple of 32.
 * @param[in]       signs           indicates if input is in signed or unsigned format, signs = (sign of Samples) << 1) | sign of coeffs.
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *
 ****************************************************************************/
INT_t VIP8bitSamples8bitCoeffsAFL(AFLOAT_t *output, CHAR_t *samples, CHAR_t *coeffs, INT_t n, INT_t signs);

/************************************************************************//**
 * VIP8bitSamples8bitCoeffsFXP()
 ****************************************************************************
 * @brief   Fixed point Vector Inner Product (VIP): 8 bits x 8 bits
 *
 * @details
 *          Fixed point Vector Inner Product on Matrix of [1 x n] with Vector of [n x 1]
 *
 * Computation time:
 * 
 * |    n   | Cycles |
 * |:------:|:------:|
 * |     32 |     43 |
 * |     64 |     52 |
 * |     96 |     60 |
 * |    128 |     68 |
 * |    160 |     76 |
 * |    192 |     84 |
 * |    224 |     92 |
 * |    256 |    100 |
 * |    288 |    108 |
 * |    320 |    116 |
 * |    352 |    124 |
 * |    384 |    132 |
 * |    416 |    140 |
 * |    448 |    148 |
 * |    480 |    156 |
 * |    512 |    164 |
 * |    544 |    172 |
 * |    576 |    180 |
 * |    608 |    188 |
 * |    640 |    196 |
 * |    672 |    204 |
 * |    704 |    212 |
 * |    736 |    220 |
 * |    768 |    228 |
 * |    800 |    236 |
 * |    832 |    244 |
 * |    864 |    252 |
 * |    896 |    260 |
 * |    928 |    268 |
 * |    960 |    276 |
 * |    992 |    284 |
 * |   1024 |    292 |
 *
 * @param[out]      *output         pointer to fixed point result, Q15.16.
 * @param[in]       *samples        8-bit samples (Q7 if signed, Q8 otherwise), 8-byte aligned pointer to CHAR_t for 8-bit samples.
 * @param[in]       *coeffs         8-bit coefficients (Q7 if signed, Q8 otherwise), 8-byte aligned pointer to CHAR_t whether the
 *                                  input coefficients are 8 or 16 bits due to coefficient reordering has been done at the byte level.
 * @param[in]       n               n: number of columns in samples (number of elements in coeffs). Must be a multiple of 32.
 * @param[in]       signs           indicates if input is in signed or unsigned format, signs = (sign of Samples) << 1) | sign of coeffs.
 *
 * @return      Minimum output headroom that could be used in subsequent scaling
 *
 ****************************************************************************/
INT_t VIP8bitSamples8bitCoeffsFXP(INT_t *output, CHAR_t *samples, CHAR_t *coeffs, INT_t n, INT_t signs);

/************************************************************************//**
 * VIP16bitSamples8bitCoeffsAFL()
 ****************************************************************************
 * @brief   Afloat Vector Inner Product (VIP): 16 bits x 8 bits
 *
 * @details
 *          Afloat Vector Inner Product on Matrix of [1 x n] with Vector of [n x 1]
 *
 * Computation time:
 * 
 * |    n   | Cycles |
 * |:------:|:------:|
 * |     32 |    108 |
 * |     64 |    132 |
 * |     96 |    155 |
 * |    128 |    178 |
 * |    160 |    201 |
 * |    192 |    224 |
 * |    224 |    247 |
 * |    256 |    270 |
 * |    288 |    293 |
 * |    320 |    316 |
 * |    352 |    339 |
 * |    384 |    362 |
 * |    416 |    385 |
 * |    448 |    408 |
 * |    480 |    431 |
 * |    512 |    454 |
 * |    544 |    477 |
 * |    576 |    500 |
 * |    608 |    523 |
 * |    640 |    546 |
 * |    672 |    569 |
 * |    704 |    592 |
 * |    736 |    615 |
 * |    768 |    638 |
 * |    800 |    661 |
 * |    832 |    684 |
 * |    864 |    707 |
 * |    896 |    730 |
 * |    928 |    753 |
 * |    960 |    776 |
 * |    992 |    799 |
 * |   1024 |    822 |
 *
 * @param[out]      *output         pointer to afloat result.
 * @param[in]       *samples        16-bit samples (Q15 if signed, Q16 otherwise), 8-byte aligned pointer to SHORT_t for 16-bit samples.
 * @param[in]       *coeffs         8-bit coefficients (Q7 if signed, Q8 otherwise), 8-byte aligned pointer to CHAR_t whether the
 *                                  input coefficients are 8 or 16 bits due to coefficient reordering has been done at the byte level.
 * @param[in]       n               n: number of columns in samples (number of elements in coeffs). Must be a multiple of 32.
 * @param[in]       signs           indicates if input is in signed or unsigned format, signs = (sign of Samples) << 1) | sign of coeffs.
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *
 ****************************************************************************/
INT_t VIP16bitSamples8bitCoeffsAFL(AFLOAT_t *output, SHORT_t *samples, CHAR_t *coeffs, INT_t n, INT_t signs);

/************************************************************************//**
 * VIP16bitSamples8bitCoeffsFXP()
 ****************************************************************************
 * @brief   Fixed point Vector Inner Product (VIP): 16 bits x 8 bits
 *
 * @details
 *          Fixed point Vector Inner Product on Matrix of [1 x n] with Vector of [n x 1]
 *
 * Computation time:
 * 
 * |    n   | Cycles |
 * |:------:|:------:|
 * |     32 |    102 |
 * |     64 |    126 |
 * |     96 |    149 |
 * |    128 |    172 |
 * |    160 |    195 |
 * |    192 |    218 |
 * |    224 |    241 |
 * |    256 |    264 |
 * |    288 |    287 |
 * |    320 |    310 |
 * |    352 |    333 |
 * |    384 |    356 |
 * |    416 |    379 |
 * |    448 |    402 |
 * |    480 |    425 |
 * |    512 |    448 |
 * |    544 |    471 |
 * |    576 |    494 |
 * |    608 |    517 |
 * |    640 |    540 |
 * |    672 |    563 |
 * |    704 |    586 |
 * |    736 |    609 |
 * |    768 |    632 |
 * |    800 |    655 |
 * |    832 |    678 |
 * |    864 |    701 |
 * |    896 |    724 |
 * |    928 |    747 |
 * |    960 |    770 |
 * |    992 |    793 |
 * |   1024 |    816 |
 *
 * @param[out]      *output         pointer to fixed point result. The number of fractional bits is determined based on the number of terms
 *                                  in the inner product(s), but does not exceed 24.
 * @param[in]       *samples        16-bit samples (Q15 if signed, Q16 otherwise), 8-byte aligned pointer to SHORT_t for 16-bit samples.
 * @param[in]       *coeffs         8-bit coefficients (Q15 if signed, Q16 otherwise), 8-byte aligned pointer to CHAR_t whether the
 *                                  input coefficients are 8 or 16 bits due to coefficient reordering has been done at the byte level.
 * @param[in]       n               n: number of columns in samples (number of elements in coeffs). Must be a multiple of 32.
 * @param[in]       signs           indicates if input is in signed or unsigned format, signs = (sign of Samples) << 1) | sign of coeffs.
 *
 * @return      Minimum output headroom that could be used in subsequent scaling
 *
 ****************************************************************************/
INT_t VIP16bitSamples8bitCoeffsFXP(INT_t *output, SHORT_t *samples, CHAR_t *coeffs, INT_t n, INT_t signs);

/************************************************************************//**
 * VIP16bitSamples16bitCoeffsAFL()
 ****************************************************************************
 * @brief   Afloat Vector Inner Product (VIP): 16 bits x 16 bits
 *
 * @details
 *          Afloat Vector Inner Product on Matrix of [1 x n] with Vector of [n x 1]
 *
 * Computation time:
 * 
 * |    n   | Cycles |
 * |:------:|:------:|
 * |     32 |    235 |
 * |     64 |    308 |
 * |     96 |    381 |
 * |    128 |    454 |
 * |    160 |    527 |
 * |    192 |    600 |
 * |    224 |    673 |
 * |    256 |    746 |
 * |    288 |    819 |
 * |    320 |    892 |
 * |    352 |    965 |
 * |    384 |   1038 |
 * |    416 |   1111 |
 * |    448 |   1184 |
 * |    480 |   1257 |
 * |    512 |   1330 |
 * |    544 |   1403 |
 * |    576 |   1476 |
 * |    608 |   1549 |
 * |    640 |   1622 |
 * |    672 |   1695 |
 * |    704 |   1768 |
 * |    736 |   1841 |
 * |    768 |   1914 |
 * |    800 |   1987 |
 * |    832 |   2060 |
 * |    864 |   2133 |
 * |    896 |   2206 |
 * |    928 |   2279 |
 * |    960 |   2352 |
 * |    992 |   2425 |
 * |   1024 |   2498 |
 *
 * @param[out]      *output         pointer to afloat result.
 * @param[in]       *samples        16-bit samples (Q15 if signed, Q16 otherwise), 8-byte aligned pointer to SHORT_t for 16-bit samples.
 * @param[in]       *coeffs         16-bit coefficients (Q15 if signed, Q16 otherwise), 8-byte aligned pointer to CHAR_t whether the
 *                                  input coefficients are 8 or 16 bits due to coefficient reordering has been done at the byte level.
 * @param[in]       n               n: number of columns in samples (number of elements in coeffs). Must be a multiple of 32.
 * @param[in]       signs           indicates if input is in signed or unsigned format, signs = (sign of Samples) << 1) | sign of coeffs.
 *
 * @return      Maximum output exponent that could be used in subsequent scaling
 *
 ****************************************************************************/
INT_t VIP16bitSamples16bitCoeffsAFL(AFLOAT_t *output, SHORT_t *samples, CHAR_t *coeffs, INT_t n, INT_t signs);

/************************************************************************//**
 * VIP16bitSamples16bitCoeffsFXP()
 ****************************************************************************
 * @brief   Fixed point Vector Inner Product (VIP): 16 bits x 16 bits
 *
 * @details
 *          Fixed point Vector Inner Product on Matrix of [1 x n] with Vector of [n x 1]
 *
 * Computation time:
 * 
 * |    n   | Cycles |
 * |:------:|:------:|
 * |     32 |    228 |
 * |     64 |    304 |
 * |     96 |    380 |
 * |    128 |    456 |
 * |    160 |    532 |
 * |    192 |    608 |
 * |    224 |    684 |
 * |    256 |    760 |
 * |    288 |    836 |
 * |    320 |    912 |
 * |    352 |    988 |
 * |    384 |   1064 |
 * |    416 |   1141 |
 * |    448 |   1217 |
 * |    480 |   1293 |
 * |    512 |   1369 |
 * |    544 |   1444 |
 * |    576 |   1520 |
 * |    608 |   1597 |
 * |    640 |   1673 |
 * |    672 |   1749 |
 * |    704 |   1825 |
 * |    736 |   1901 |
 * |    768 |   1976 |
 * |    800 |   2053 |
 * |    832 |   2129 |
 * |    864 |   2205 |
 * |    896 |   2281 |
 * |    928 |   2357 |
 * |    960 |   2433 |
 * |    992 |   2509 |
 * |   1024 |   2585 |
 *
 * @param[out]      *output         pointer to fixed point result. The number of fractional bits is determined based on the number of terms
 *                                  in the inner product(s)..
 * @param[in]       *samples        16-bit samples (Q15 if signed, Q16 otherwise), 8-byte aligned pointer to SHORT_t for 16-bit samples.
 * @param[in]       *coeffs         16-bit coefficients (Q15 if signed, Q16 otherwise), 8-byte aligned pointer to CHAR_t whether the
 *                                  input coefficients are 8 or 16 bits due to coefficient reordering has been done at the byte level.
 * @param[in]       n               n: number of columns in samples (number of elements in coeffs). Must be a multiple of 32.
 * @param[in]       signs           indicates if input is in signed or unsigned format, signs = (sign of Samples) << 1) | sign of coeffs.
 *
 * @return      Minimum output headroom that could be used in subsequent scaling
 *
 ****************************************************************************/
INT_t VIP16bitSamples16bitCoeffsFXP(INT_t *output, SHORT_t *samples, CHAR_t *coeffs, INT_t n, INT_t signs);


#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_VIP_H__ */



/* End of File */
