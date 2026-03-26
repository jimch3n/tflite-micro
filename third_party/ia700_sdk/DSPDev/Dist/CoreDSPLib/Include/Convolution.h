/************************************************************************//**
 * @file    Convolution.h
 *
 * @brief   Convolution interface file.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #7 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_CONVOLUTION_H__
#define __FILE_CONVOLUTION_H__

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
 * Convolution()
 ****************************************************************************
 * @brief        Computes the convolution of two one dimentional input signals 
 *               and places the result in output buffer
 *
 * @details
 * Computation time:   For few input lengths are provided below for reference
 *
 * | xLen0 | xLen1 | Cycles  |
 * |:-----:|:-----:|:-------:|
 * |    64 |    64 |    4805 |
 * |   128 |   128 |   17637 |
 * |   256 |   256 |   67877 |
 * |   512 |   512 |  266661 |
 * |  1024 |  1024 | 1057445 |
 *
 * @param[in]   *pX0         Pointer to input vector 0
 * @param[in]   *pX1         Pointer to input vector 1
 * @param[in]    xLen0       Number of elements in vector 0
 * @param[in]    xLen1       Number of elements in vector 1
 * @param[out]  *pY          Pointer to output vector of size (xLen0+xLen1-1)*4 Bytes
 * @param[in]   *pScratch    Pointer to scratch of size ((((xLen0+2*xLen1+3)>>2)<<2)+2) Bytes
                             Pointer must be 8-byte aligned
 *
 * @return      true on success or false on failure
 *
 ****************************************************************************/
bool Convolution(AFLOAT_t *pY, const AFLOAT_t *pX0, const AFLOAT_t *pX1, unsigned int xLen0, unsigned int xLen1, AFLOAT_t *pScratch);

#ifdef __cplusplus
}
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif /* __FILE_CONVOLUTION_H__ */



/* End of File */

