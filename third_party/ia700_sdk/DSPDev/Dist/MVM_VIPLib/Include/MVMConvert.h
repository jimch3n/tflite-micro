/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVMConvert.h
 *
 * @brief   MVMConvert interface.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_MVM_CONVERT_H__
#define __FILE_MVM_CONVERT_H__

/**************************************************************************//**
 * @addtogroup hml_ml
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
#include "MVMLayer.h"
 /****************************************************************************
 * Definitions
 ****************************************************************************/

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




/****************************************************************************
 * Public Functions
 ****************************************************************************/


/************************************************************************//**
 * MVMConvert()
 ****************************************************************************
 * @brief        Convert input for MVM functions, from Afloat type to 16/8 bit fixed-point
 *
 * @param[out]   *pOut           Pointer to Output vector
 * @param[in]    typeMVM         Type of MVM convert output - 8bit fixed-point/16bit fixed-point/afloat
 * @param[in]    *pInAfl         Pointer to input Afloat data
 * @param[in]    inputLen        Number of elements in pInAfl(equal to no.of elements in pOut)
 *
 * @return    Maximum output exponent
 *
 * @note
 * 1.In-place computation is not supported.\n
 * 2.Computation time:\n
 *
 * |    bit |inputLen|   Cycles  |
 * |:------:|:------:|:---------:|
 * |       8|      32|       123 |
 * |       8|      64|       183 |
 * |       8|     128|       303 |
 * |       8|     256|       543 |
 * |       8|     512|      1023 |
 * |       8|    1024|      1983 |
 * |      16|      32|       143 |
 * |      16|      64|       223 |
 * |      16|     128|       383 |
 * |      16|     256|       703 |
 * |      16|     512|      1343 |
 * |      16|    1024|      2623 |
 *
 ****************************************************************************/
int32_t MVMConvert(void *pOut, int typeMVM, AFLOAT_t *pInAfl,  uint32_t inputLen);

#ifdef __cplusplus
};
#endif /* __cplusplus */
/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_CONVERT_H__ */
