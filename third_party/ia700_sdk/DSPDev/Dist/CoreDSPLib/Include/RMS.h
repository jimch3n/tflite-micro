/************************************************************************//**
 * @file    RMS.h
 *
 * @brief   RMSution interface file.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #7 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_RMS_H__
#define __FILE_RMS_H__

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
 * RMSReal()
 ****************************************************************************
 * @brief        Computes the RMS of a Real valued input signals 
 *               and places the result in output buffer
 *
 * @details
 * Computation time:   For few input lengths are provided below for reference
 *
 * |  xLen | Cycles |
 * |:-----:|:------:|
 * |    64 |    100 |
 * |   128 |    164 |
 * |   256 |    292 |
 * |   512 |    548 |
 * |  1024 |   1060 |
 *
 * @param[in]   *pX     Pointer to input buffer of real value.
 * @param[in]    xLen   Length of the input buffer. Must be a multiple of 4.
 * @param[out]  *rms    Pointer to output AFLOAT_t rms value (4 bytes). 
 *
 * @return      true on success or false on failure
 *
 ****************************************************************************/
bool RMSReal(AFLOAT_t *rms, AFLOAT_t *pX, unsigned int xLen);

/************************************************************************//**
 * RMSComplex()
 ****************************************************************************
 * @brief        Computes the RMS of a Complex valued input signals 
 *               and places the result in output buffer
 *
 * @details
 * Computation time:   For few input lengths are provided below for reference
 *
 * |  xLen | Cycles |
 * |:-----:|:------:|
 * |    64 |     98 |
 * |   128 |    162 |
 * |   256 |    290 |
 * |   512 |    546 |
 * |  1024 |   1058 |
 *
 * @param[in]   *pX     Pointer to input buffer of complex value.
 *                      Real and imaginary parts are interleaved.
 * @param[in]    xLen   Length of the input buffer, sum of real and imaginary, 
 *                      Must be a multiple of 4. 
 * @param[out]  *rms    Pointer to output rms value.
 *
 * @return      true on success or false on failure
 *
 ****************************************************************************/
bool RMSComplex(AFLOAT_t *rms, AFLOAT_t *pX, unsigned int xLen);

#ifdef __cplusplus
}
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif /* __FILE_RMS_H__ */



/* End of File */

