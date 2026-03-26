/************************************************************************//**
 * @file    CoreUtils.h
 *
 * @brief   utils interface file.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #6 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_COREUTILS_H__ 
#define __FILE_COREUTILS_H__ 

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
/************************************************************************//**
 * VectorInnerProduct()
 ****************************************************************************
 * @brief        This function performs Dot Product of two vectors
 *               The input and output data format type is 32-bit fr32
 *
 * @details
 * Computation time:   For few input lengths are provided below for reference
 *
 * | length | Cycles |
 * |:------:|:------:|
 * |     64 |    100 |
 * |    128 |    164 |
 * |    256 |    292 |
 * |    512 |    548 |
 * |   1024 |   1060 |
 *
 * @param[out]  *pOut        Dot product of input vectors
 * @param[in]   *pVec0       Input vector pointer 0
 * @param[in]   *pVec1       Input vector pointer 1 
 * @param[in]    Length      Number of elements
 *
 * @see
 *       Length of input vectors should same
 *       Minimum length : 4
 *
 * @return      true on success or false on failure
 *
 ****************************************************************************/
bool VectorInnerProduct(AFLOAT_t *pOut, AFLOAT_t *pVec0, AFLOAT_t *pVec1, int Length);

/************************************************************************//**
 * FindPeak()
 ****************************************************************************
 * @brief        Find the Absolute Peak of one dimentional array
 * 
 * @details
 * Computation time:   For few input lengths are provided below for reference
 *
 * | length | Cycles |
 * |:------:|:------:|
 * |     64 |    104 |
 * |    128 |    168 |
 * |    256 |    296 |
 * |    512 |    552 |
 * |   1024 |   1064 |
 *
 * @param[in]    *xIn        pointer to input sample data to be measured.
 *                           The buffer must be 8 byte aligned.
 * @param[in]    length      The buffer length in samples
 * @param[out]   *peak       Points to peak value
 *
 * @return      true on success or false on failure
 *
 ****************************************************************************/
bool FindPeak(const AFLOAT_t *xIn, unsigned int length, AFLOAT_t *peak);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif /* __FILE_COREUTILS_H__ */



/* End of File */
