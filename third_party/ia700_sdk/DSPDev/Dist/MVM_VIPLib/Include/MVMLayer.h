/************************************************************************//**
 * @file    MVM_VIPLib/Include/MVMLayer.h
 *
 * @brief   Mutiplile Layers of Full connected Neural Network defined MVM interface.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_MVM_LAYER_H__
#define __FILE_MVM_LAYER_H__
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


#define MVM_LAYER_ERROR_TYPE  (-2) // unsupport mvm type
#define MVM_LAYER_ERROR_ACT   (-1) // unknown actication function
#define MVM_LAYER_ERROR_NONE  (0)

/**
* Enum used to decide which MVM mutliplication type is used in layers
*/
typedef enum
{
    MVM_8X8_TYPE = 0,        /*input x: 8bit,   coefficients: 8bit*/
    MVM_16X8_TYPE = 1,       /*input x: 16bit,  coefficients: 8bit*/
    MVM_16X16_TYPE = 2,      /*input x: 16bit,  coefficients: 16bit*/
    MVM_AFLOATXAFLOAT_TYPE   /*input x: afloat, coefficients: afloat*/
}mvm_mul_t;

/**
* Enum used to decide which activation function is used in each layer
*/
typedef enum {
    ML_ACT_LINEAR = 0,
    ML_ACT_RELU = 1,
    ML_ACT_SIGMOID,
    ML_ACT_TANH,
    ML_ACT_SOFTMAX,

}mvm_act_t;

/**
* mvm_layer_t() uses to saving MVM layer information
* fixed-pointer exponent input size (block)/ output size(group)
* table pointer and type output activation function
*/
typedef struct
{
    uint32_t      nGroups;     /**< size of output  */
    uint32_t      nBlocks;     /**< size of input  */
    int8_t        expA;        /**< exponent of hidden weights */
    int8_t        expc;        /**< exponent of biases */
    const uint8_t   *A;        /**< pointer to hidden weights */
    const uint8_t   *c;        /**< pointer to biases */
    mvm_act_t     typeAct;     /**< output of activation function type */
} mvm_layer_t;

/**
* mvm_layer_scratch_t() keep scratch memory pointer
*/
typedef struct
{
    void *pAct;    /**< scratch for input buffer */
    void *pPing;   /**< scratch for output buffer */
    void *pInterLeave;  /**< scratch to store de-interleaved (1024*2 Bytes with 4-byte alignment ) */
}mvm_layer_scratch_t;

/**
* mvm_nn_layers_t() uses keep Mutlilayer Neural Network information
*/
typedef struct
{
    int          numLayers;         /**< number of layers*/
    mvm_layer_t *layer;             /**< pointers of mvm layers*/
    AFLOAT_t    *pInputAfloat;      /**< pointer to input */
    AFLOAT_t    *pOutputAfloat;     /**< pointer to output */
    mvm_mul_t    typeMVM;           /**< type of MVM multiplication */
    uint32_t     inputLen;          /**< length of pInputAfloat */
    uint32_t     outputLen;         /**< length of pOutputAfloat */
    mvm_layer_scratch_t scratchMemory; /**< Activation Ping-Pong Buffer */

}mvm_nn_layers_t;
/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************//**
 * MVMLayer
 ****************************************************************************
 * @brief        Multi-layers full-connected Neural Network for MVM
 *
 * Computation time and coefficients profiling:
 * Example contains 5 layers:
 * 4 hidden layers size are 360, 175, 85, 120, 90
 * activation functions: relu, sigmod, tanh, softmax
 * 
 * |    Type   |    coeffs (W) |  biase(B)| Cycles |
 * |:---------:|:-------------:|:--------:|:-------|
 * |  8x8      |  100208       |  470     |  26098 |
 * |  16x8     |  100208       |  470     |  92086 |
 * |  16x16    |  200416       |  940     | 151363 |
 * |  Afloat   |  395500       |  1880    | 118444 |
 *
 *
 * @param[in]    *pMvmNNLayerInst          pointer to mvm nn layers instances
 * @param[out]   *pMvmNNLayerInst          pointer to mvm nn layers instances
 *
 * @return       0 if successful, else error
 *
 ****************************************************************************/
 
int MVMLayer(mvm_nn_layers_t *pMvmNNLayerInst);

#ifdef __cplusplus
};
#endif /* __cplusplus */
/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_LAYER_H__ */
