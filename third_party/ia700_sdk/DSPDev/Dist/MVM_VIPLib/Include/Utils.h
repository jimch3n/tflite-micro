/************************************************************************//**
 * @file
 *
 * @brief    Utility functions for Machine Learning
 *
 * $DateTime: 2023/09/03 21:25:38 $
 * $Revision: #1 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MVM_UTILS_H__
#define __FILE_MVM_UTILS_H__

/**************************************************************************//**
 * @addtogroup hmd_ml
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
#include "MachineLearningDefs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/************************************************************************//**
 * VectorProduct
 ****************************************************************************
 * @brief       Vector Element-wise Product
 *
 * @details
 *       input two vectors x, y, and output = x*y, length of nLen
 *
 * \par Computation time:
 * \par
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |     65    |
 * |    32  |    105    |
 * |    64  |    185    |
 * |   128  |    345    |
 * |   256  |    665    |
 *
 *
 * @param[out]      pOutput           Pointer to output vector
 * @param[in]       pInputX           Pointer to input vector X
 * @param[in]       pInputY           Pointer to input vector Y
 * @param[in]       nLen              Length of Vectors
 *
 *
 * @return     None
 *
 ****************************************************************************/
void VectorProduct(fr32 *pOutput, fr32 *pInputX, fr32 *pInputY, uint32_t nLen);


/************************************************************************//**
 * VectorProductAccumulate
 ****************************************************************************
 * @brief       Vector Product and Accumulate
 *
 * @details
 *       input two vectors x, y, and acc = acc+x*y, length of nLen
 *
 * \par Computation time:
 * \par
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |        76 |
 * |    32  |       124 |
 * |    64  |       220 |
 * |   128  |       412 |
 * |   256  |       796 |
 *
 *
 * @param[out]      pAcc              Pointer to output vector
 * @param[in]       pInputX           Pointer to input vector X
 * @param[in]       pInputY           Pointer to input vector Y
 * @param[in]       nLen              Length of Vectors
 *
 *
 * @return     None
 *
 ****************************************************************************/
void VectorProductAccumulate(fr32 *pAcc, fr32 *pInputX, fr32 *pInputY, uint32_t nLen);


/************************************************************************//**
 * VectorSub1
 ****************************************************************************
 * @brief       Vector Subtract 1
 *
 * @details
 *       input the vectors x, and output = 1-x, length of nLen
 *
 * \par Computation time:
 * \par
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |       58  |
 * |    32  |       90  |
 * |    64  |      154  |
 * |   128  |      282  |
 * |   256  |      538  |
 *
 *
 * @param[out]      pOutput           Pointer to output vector
 * @param[in]       pInputX           Pointer to input vector X
 * @param[in]       nLen              Length of Vectors
 *
 *
 * @return     None
 *
 ****************************************************************************/
void VectorSub1(fr32 *pOutput,  const fr32 *pInputX, uint32_t nLen);


/************************************************************************//**
 * VectorCopyWords
 ****************************************************************************
 * @brief       Vector Copy Words
 *
 * @details
 *       input the vectors x, and output = x, length of nLen
 *
 * \par Computation time:
 * \par
 * |    n   |   Cycles  |
 * |:------:|:---------:|
 * |    16  |     51    |
 * |    32  |     67    |
 * |    64  |     99    |
 * |   128  |    163    |
 * |   256  |    291    |
 *
 *
 * @param[out]      pDst           Pointer to output vector
 * @param[in]       pSrc           Pointer to input vector X
 * @param[in]       nLen           Length of Vectors
 *
 *
 * @return     None
 *
 ****************************************************************************/
void VectorCopyWords(fr32 *pDst, const fr32 *pSrc, uint32_t nLen);

#ifdef __cplusplus
};
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_UTILS_H__ */



/* End of File */

