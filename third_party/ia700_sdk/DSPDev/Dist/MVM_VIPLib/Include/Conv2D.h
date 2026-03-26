/************************************************************************//**
 * @file
 *
 * @brief  Convolution Neural Network 2D
 *
 * $DateTime: 2023/09/03 21:25:38 $
 * $Revision: #1 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_CONV2D_H__
#define __FILE_CONV2D_H__

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
#include "DeltaPlatform.h"
#include "TIE_defs.h"
#include "MachineLearningDefs.h"
#ifdef __XTENSA__
#define MAXI(x,y) XT_MAX(x,y)
#define MINI(x,y) XT_MIN(x,y)
#else
#define MAXI(x,y)         ((x) > (y) ? (x) : (y))
#define MINI(x,y)         ((x) < (y) ? (x) : (y))
#endif

 /**
 * Enum used to padding type
 */
typedef enum  {
	PaddingUnknown = 0,  /**< Reserved unknown padding type*/
	PaddingSame = 1,    /**< Padding same algorithm, Please refere tensorflow's definition */
	PaddingValid =2     /**< Padding valid algorithm, Please refere tensorflow's definition */
}Padding;

/**
* Enum used to indicate quanztion type
*/
typedef enum {
	QuantizedUnknown = 0,    /**< quantized unknown type */
	Quantized8Bit = 1,       /**< quantized 8bit type */
	QuantizedAfloat = 4      /**< quantized afloat type */
}QuantizedType;

#ifdef __cplusplus
extern "C" {
#endif

/*****
conv2d_layer_t() store the convolution layer information
*/
typedef struct {
	uint16_t ker_y;      /**< kernel height */
	uint16_t ker_x;      /**< kernel width */

	uint16_t in_ch;      /**< number of input channels */
	uint16_t in_y;       /**< input height */
	uint16_t in_x;       /**< input width */

	uint16_t out_ch;     /**< number of input channels */
	uint16_t out_y;      /**< output height */
	uint16_t out_x;      /**< output width  */

	uint16_t stride_y;   /**< stride of height */
	uint16_t stride_x;   /**< stride of width */
	uint16_t padding_y;  /**< padding of height */
	uint16_t padding_x;  /**< padding of width */
	Padding paddingType; /**< padding of type */
}conv2d_layer_t;

/************************************************************************//**
* Conv2DInit()
****************************************************************************
* @brief        Conv2D layer instance configuration, input dimemnsion, and padding type
*               configurate output width and height, padding length size
* @param[out]   *cnn_layer    Conv2D layer instance of output dim, and padding size
* @param[in]    in_y          Conv2D dim of input height
* @param[in]    in_x          Conv2D dim of input width
* @param[in]    in_ch         Conv2D dim of input channel
* @param[in]    ker_y         Conv2D dim of kernel filter height 
* @param[in]    ker_x         Conv2D dim of kernel filter width 
* @param[in]    out_ch        Conv2D dim of output channel 
* @param[in]    stride_y      Conv2D dim of stride of y 
* @param[in]    stride_x      Conv2D dim of stride of x 
* @param[in]    paddingType   Conv2D dim of padding type: same or valid
* @param[in]    quantized     Conv2D quantized data type
* note:
* 
*
* @return          scratch memory size required for convolution neural network
*
****************************************************************************/
int Conv2DInit(conv2d_layer_t *cnn_layer,
	uint16_t in_y, uint16_t in_x, uint16_t in_ch,
	uint16_t ker_y, uint16_t ker_x, uint16_t out_ch,
	uint16_t stride_y, uint16_t stride_x, Padding paddingType, 
	QuantizedType quantized
);
/************************************************************************//**
* Conv2D8bx8b()
****************************************************************************
* @brief        Conv2D interface for 8bx8b   
* @param[in]    *cnn_layer       Pointer to conv2d_layer_t instances
* @param[in]    *Im_in           8bit (Q7) quantized 2-D input, size in_ch*in_x*in_y, HWC
* @param[in]    in_exp           Exponet of input
* @param[in]    *wt              8bit (Q7) quantized weights, size ker_x*ker_y*in_ch*out_ch 
* @param[in]    wt_exp           exponent of weights
* @param[in]    *bias            8bit (Q7) quantize biases, size out_ch
* @param[in]    b_exp            exponent of biases
* @param[out]   *Im_out          afloat output  buffer  out_ch*out_x*out_y
* @param[in]    *pScratchBuffer  pointer scratch buffer: aligned 16 bytes
*
* @return   return status 
*           0: success
*           1: failure
* @note:
* 1. *wt buffer required re-mapping by Map8bCoeffsForMVM with aligned buffer.
* 2. scrach buffer size gets from Conv2DInit()
* 3. To get the best perfromance 
*    3.1 padding type is VALID (which padding size zero), 
*    3.2 input and kernel size are same odd or even
*    3.3 input channel times input image width (x) is multiple of 4
****************************************************************************/
int Conv2D8bx8b(conv2d_layer_t *cnn_layer,
			int8_t *Im_in, int in_exp, 
			const int8_t * wt, int16_t wt_exp,
			const int8_t * bias, int16_t b_exp,
			fr32 * Im_out, int32v4_aligned16 *pScratchBuffer);

/************************************************************************//**
* Conv2DAfloat()
****************************************************************************
* @brief        Conv2D interface for Afloat
* @param[in]    *cnn_layer       pointer to conv2d_layer_t instances
* @param[in]    *Im_in           Afloat 2-d input, size in_ch*in_x*in_y
* @param[in]    *wt              Afloat weight, size ker_x*ker_y*in_ch*out_ch
* @param[in]    *bias            Afloat biases, size out_ch
* @param[out]   *Im_out          afloat output  buffer  out_ch*out_x*out_y
* @param[in]    *pScratchBuffer  pointer scratch buffer: aligned 16 bytes
*
* @return   return status
*           0: success
*           1: failure
* note:
* 1. scrach buffer size gets from Conv2DInit()
* 2. To get the best perfromance
*    2.1 padding type is VALID (which padding size zero),
*    2.2 input and kernel size are same odd or even
****************************************************************************/
int Conv2DAfloat(conv2d_layer_t *cnn_layer,
	fr32 *Im_in,
	const fr32 * wt,
	const fr32 * bias,
	fr32 * Im_out, int *pScratchBuffer);
#ifdef __cplusplus
}
#endif
/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  // _FILE_CONV2D_H_
