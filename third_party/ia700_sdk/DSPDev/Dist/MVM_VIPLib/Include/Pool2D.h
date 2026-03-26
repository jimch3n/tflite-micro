/************************************************************************//**
 * @file
 *
 * @brief   Pooling
 *
 * $DateTime: 2023/09/03 21:25:38 $
 * $Revision: #1 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_POOL2D_H__
#define __FILE_POOL2D_H__

/**************************************************************************//**
 * @addtogroup hmd1a_ml
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
#include "Conv2D.h"

typedef  conv2d_layer_t pool2d_layer_t;
#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************//**
* MaxPool2D()
****************************************************************************
* @brief        Max POOL2D interface
* @param[in]    *pool_layer     pointer to conv2d_layer_t instances
* @param[in]    *Im_in          pointer to input image NHWC format
* @param[out]   *Im_out         pointer to output image
* @return          0
*
* note:
* 1. pool_layer instance initialize Pool2DInit()
* 2. output channel must equal to input channel
* 3. To get the best perfromance
*    3.1 kernel size = (2,2)
*    3.2 stride size = (2,2)
*    3.3 output dims are even
*    3.4 padding VALID
****************************************************************************/
void MaxPool2D(conv2d_layer_t *pool_layer,
	fr32 * Im_in,
	fr32 * Im_out);
/************************************************************************//**
* AvgPool2D()
****************************************************************************
* @brief        Average POOL2D interface for Afloat reference   
* @param[in]    *pool_layer     pointer to conv2d_layer_t instances
* @param[in]    *Im_in          pointer to input image NHWC format
* @param[out]   *Im_out         pointer to output image
*
* @return          0
*
* note:
* 1. pool_layer instance initialize Pool2DInit()
* 2. output channel must equal to input channel
****************************************************************************/
void AvgPool2D(conv2d_layer_t *pool_layer,
	fr32 * Im_in,
	fr32 * Im_out);

/************************************************************************//**
* Pool2DInit()
****************************************************************************
* @brief        POOL2D initialization interface 
* @param[in]    *pool_layer          pointer to pool layer instances
* @param[in]    in_y                 Pool2D dim of input height
* @param[in]    in_x                 Pool2D dim of input width
* @param[in]    in_ch                Pool2D dim of input channel
* @param[in]    ker_y                Pool2D dim of kernel filter height
* @param[in]    ker_x                Pool2D dim of kernel filter width
* @param[in]    out_ch               Pool2D dim of output channel
* @param[in]    stride_y             Pool2D dim of stride of y
* @param[in]    stride_x             Pool2D dim of stride of x
* @param[in]    paddingType          Pool2D dim of padding type: same or valid
* note:
*
* @return          0
*
****************************************************************************/
int Pool2DInit(conv2d_layer_t *pool_layer,
	uint16_t in_y, uint16_t in_x, uint16_t in_ch,
	uint16_t ker_y, uint16_t ker_x, uint16_t out_ch,
	uint16_t stride_y, uint16_t stride_x, Padding paddingType
);
#ifdef __cplusplus
}
#endif
/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  // _FILE_POOL2D_H_
