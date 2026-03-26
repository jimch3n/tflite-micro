/************************************************************************//**
 * @file
 *
 * @brief   Long Short Term Memory interface (LSTM)
 *
 * $DateTime: 2023/09/03 21:25:38 $
 * $Revision: #1 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_LSTM_H__
#define __FILE_LSTM_H__

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
#include "Sigmoid.h"

/****************************************************************************
* Macros
****************************************************************************/
/**
* LSTM_MAX() return maximum of integer size
*/

#define LSTM_MAX(X, Y) ((X>Y)? (X):(Y))
/**
* ALIGNED_UP_4() alignment up 4 byte size
*/

#define ALIGNED_UP_4(X) (((X+3)>>2)<<2)
/**
* LSTM_AFLOAT_SCRATCH_MEMORY_REQUIRED_BYTE() return memory buffer for 
* invoking LSTMAfloat() in bytes
*/
#define LSTM_AFLOAT_SCRATCH_MEMORY_REQUIRED_BYTE(INPUT_SIZE, OUTPUT_SIZE)\
   (4* sizeof(fr32)* OUTPUT_SIZE)
 
/**
* LSTM_8bx8b_SCRATCH_MEMORY_REQUIRED_BYTE() return memory buffer for 
* invoking LSTM8bx8b() in bytes
*/
#define LSTM_8bx8b_SCRATCH_MEMORY_REQUIRED_BYTE( INPUT_SIZE, OUTPUT_SIZE) \
            ((4* sizeof(fr32)* OUTPUT_SIZE) + sizeof(int8_t)*(ALIGNED_UP_4(INPUT_SIZE) + ALIGNED_UP_4(OUTPUT_SIZE)))

/**
* LSTM_16bx8b_SCRATCH_MEMORY_REQUIRED_BYTE() return memory buffer for
* invoking LSTM16bx8b() in bytes
*/
#define LSTM_16bx8b_SCRATCH_MEMORY_REQUIRED_BYTE( INPUT_SIZE, OUTPUT_SIZE) \
            ((4 *sizeof(fr32)* OUTPUT_SIZE) + sizeof(int16_t)*(ALIGNED_UP_4(INPUT_SIZE) + ALIGNED_UP_4(OUTPUT_SIZE)+ALIGNED_UP_4(LSTM_MAX(INPUT_SIZE, OUTPUT_SIZE))))

/**
* LSTM_16bx16b_SCRATCH_MEMORY_REQUIRED_BYTE() return memory buffer for
* invoking LSTM16bx16b() in bytes
*/
#define LSTM_16bx16b_SCRATCH_MEMORY_REQUIRED_BYTE( INPUT_SIZE, OUTPUT_SIZE) \
            ((4 *sizeof(fr32)* OUTPUT_SIZE) + sizeof(int16_t)*(ALIGNED_UP_4(INPUT_SIZE) + ALIGNED_UP_4(OUTPUT_SIZE)))

/*****
* LSTMAflt_State() uses to saving LSTM information for afloat weights/biases
* input and recurrent afloat buffer pointer
* and its input and output size
*/
typedef struct _LSTMAflt_t
{
    fr32 *pInput;      /**< input buffer pointer */
    fr32 *pOutput;     /**< output buffer pointer */
    fr32 *pCell;       /**< cell state pointer */

    fr32 *pI2IWAflt;  /**< input to input weights       */
    fr32 *pI2CWAflt;  /**< input to cell weights        */
    fr32 *pI2FWAflt;  /**< input to forget weights      */
    fr32 *pI2OWAflt;  /**< input to output weights      */
                                                        
    fr32 *pR2IWAflt; /**< recurrent to input weights    */
    fr32 *pR2CWAflt; /**< recurrent to cell weights     */
    fr32 *pR2FWAflt; /**< recurrent to forget weights   */
    fr32 *pR2OWAflt; /**< recurrent to  output weights  */
                                     
    fr32 *pIBAflt;   /**<  recurrent to input biases    */
    fr32 *pCBAflt;   /**< recurrent to cell biases      */
    fr32 *pFBAflt;   /**< recurrent to forget biases    */
    fr32 *pOBAflt;   /**< recurrent to output biases    */

    uint16_t n_input;  /**< number of input size      */
    uint16_t n_output; /**< number of output size     */

	sigmoid_act_t sig_act; /**< Sigmoid activation function, Please refere @ref sigmoid_act_t */

    fr32 *scratch;     /**< scratch memory  */
}LSTMAflt_State;
/*****
* LSTM8b_State() uses to saving LSTM information for 8-bit quantized weights/biases
* input and recurrent afloat buffer pointer
* and its input and output size
*/
typedef struct _LSTM8b_t
{
    fr32 *pInput;    /**< input buffer pointer */
    fr32 *pOutput;   /**< output buffer pointer */
    fr32 *pCell;     /**< cell state pointer */

    int8_t *pI2IW8b;  /**< quantized 8-bit input to input weights       */
    int8_t *pI2CW8b;  /**< quantized 8-bit input to cell weights        */
    int8_t *pI2FW8b;  /**< quantized 8-bit input to forget weights      */
    int8_t *pI2OW8b;  /**< quantized 8-bit input to output weights      */

    int8_t *pR2IW8b; /**< quantized 8-bit recurrent to input weights    */
    int8_t *pR2CW8b; /**< quantized 8-bit recurrent to cell weights     */
    int8_t *pR2FW8b; /**< quantized 8-bit recurrent to forget weights   */
    int8_t *pR2OW8b; /**< quantized 8-bit recurrent to  output weights  */
 
    int8_t *pIB8b;  /**< quantized 8-bit recurrent to input biases    */
    int8_t *pCB8b;  /**< quantized 8-bit recurrent to cell biases      */
    int8_t *pFB8b;  /**< quantized 8-bit recurrent to forget biases    */
    int8_t *pOB8b;  /**< quantized 8-bit recurrent to output biases    */

    int I2IWexp;       /**< quantized 8-bit weights input to input gate maximum exponent */
    int I2FWexp;       /**< quantized 8-bit weights input to forget gate maximum exponent */
    int I2CWexp;       /**< quantized 8-bit weights input to cell state maximum exponent */
    int I2OWexp;       /**< quantized 8-bit weights input to output gate maximum exponent */

    int R2IWexp;     /**< quantized 8-bit weights recurrent to input gate maximum exponent */
    int R2FWexp;     /**< quantized 8-bit weights recurrent to forget gate maximum exponent */
    int R2CWexp;     /**< quantized 8-bit weights recurrent to cell state maximum exponent */
    int R2OWexp;     /**< quantized 8-bit weights recurrent to output gate maximum exponent */

    int BIexp;      /**< quantized 8-bit biases input gate maximum exponent */
    int BFexp;      /**< quantized 8-bit biases forget gate maximum exponent */
    int BCexp;      /**< quantized 8-bit biases cell state maximum exponent */
    int BOexp;      /**< quantized 8-bit biases output gate maximum exponent */
    uint16_t n_input;  /**< number of input size        */
    uint16_t n_output; /**< number of output size       */

	sigmoid_act_t sig_act; /**< Sigmoid activation function, Please refere @ref sigmoid_act_t */

    fr32 *scratch;     /**< scratch memory */
}LSTM8b_State;
/*****
* LSTM16b_State() uses to saving LSTM information for 16-bit quantized weights/biases
* input and recurrent afloat buffer pointer
* and its input and output size
*/
typedef struct _LSTM16b_t
{
    fr32 *pInput;          /**< input buffer pointer */
    fr32 *pOutput;         /**< output buffer pointer */
    fr32 *pCell;           /**< cell state pointer */

    int8_t *pI2IW8b;        /**< quantized 16-bit (lower 8-bits first and upper 8-bits next) input to input weights       */
    int8_t *pI2CW8b;        /**< quantized 16-bit (lower 8-bits first and upper 8-bits next) input to cell weights        */
    int8_t *pI2FW8b;        /**< quantized 16-bit (lower 8-bits first and upper 8-bits next) input to forget weights      */
    int8_t *pI2OW8b;        /**< quantized 16-bit (lower 8-bits first and upper 8-bits next) input to output weights      */

    int8_t *pR2IW8b;       /**< quantized 16-bit (lower 8-bits first and upper 8-bits next)  recurrent to input weights    */
    int8_t *pR2CW8b;       /**< quantized 16-bit (lower 8-bits first and upper 8-bits next)  recurrent to cell weights     */
    int8_t *pR2FW8b;       /**< quantized 16-bit (lower 8-bits first and upper 8-bits next)  recurrent to forget weights   */
    int8_t *pR2OW8b;       /**< quantized 16-bit (lower 8-bits first and upper 8-bits next)  recurrent to output weights   */
                                       
    int16_t *pIB16b;      /**< quantized  16-bit input biases    */
    int16_t *pFB16b;      /**< quantized  16-bit forget biases      */
    int16_t *pCB16b;      /**< quantized  16-bit cell  biases    */
    int16_t *pOB16b;      /**< quantized  16-bit output biases    */

    int I2IWexp;             /**< quantized 16-bit weights input to input gate maximum exponent */
    int I2FWexp;             /**< quantized 16-bit weights input to forget gate maximum exponent */
    int I2CWexp;             /**< quantized 16-bit weights input to cell state maximum exponent */
    int I2OWexp;             /**< quantized 16-bit weights input to output gate maximum exponent */

    int R2IWexp;           /**< quantized 16-bit weights recurrent to input gate maximum exponent */
    int R2FWexp;           /**< quantized 16-bit weights recurrent to forget gate maximum exponent */
    int R2CWexp;           /**< quantized 16-bit weights recurrent to cell state maximum exponent */
    int R2OWexp;           /**< quantized 16-bit weights recurrent to output gate maximum exponent */
                                         
    int BIexp;            /**< quantized 16-bit biases input gate maximum exponent */
    int BFexp;            /**< quantized 16-bit biases forget gate maximum exponent */
    int BCexp;            /**< quantized 16-bit biases cell state maximum exponent */
    int BOexp;            /**< quantized 16-bit biases output gate maximum exponent */
    uint16_t n_input;     /**< number of input size        */
    uint16_t n_output;    /**< number of output size       */

	sigmoid_act_t sig_act; /**< Sigmoid activation function, Please refere @ref sigmoid_act_t */

    fr32 *scratch;        /**< scratch memory */
}LSTM16b_State;
/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/************************************************************************//**
 * LSTMAfloat(LSTMAflt_State *LstmInst)
 ****************************************************************************
 * @brief       Long term short memory interface for Afloat type weights
 *
 * @details
 * <pre>    
 *   i(t) = sigmoid( x(t) &sdot; Wi + Ui &sdot; h(t-1) + bi)
 *   f(t) = sigmoid( x(t) &sdot; Wf + Uf &sdot; h(t-1) + bf)
 *   o(t) = sigmoid( x(t) &sdot; Wo + Uo &sdot; h(t-1) + bo)
 *   c(t) = f(t) &times; c(t-1) + i(t) &times; tanh( x(t) &sdot; Wc + Uc &sdot; h(t-1) + bc)
 *   h(t) = o(t) &times; tanh(c(t))
 * </pre>
 * \par Notation:
 * \par
 * \li \c  &sdot;  \c : matrix multiplication 
 * \li \c  &times; \c : vector product.
 * \li \c x(t)     \c : input vector.
 * \li \c c(t-1)   \c : previous cell state.
 * \li \c h(t-1)   \c : previous output vector.
 * \li \c Wi       \c : weights for input to input gate.
 * \li \c Ui       \c : weights for recurrent to input gate.
 * \li \c bi       \c : biases for input gate.
 * \li \c Wf       \c : weights for input to forget gate 
 * \li \c Uf       \c : weights for recurrent to forget gate.
 * \li \c bf       \c : biases for forget gate.
 * \li \c Wc       \c : weights for input to cell state.
 * \li \c Uc       \c : weights for recurrent to cell state.
 * \li \c bc       \c : biases for cell state.
 * \li \c Wo       \c : weights for input to output gate.
 * \li \c Uo       \c : weights for recurrent to output gate.
 * \li \c bo       \c : biases for output gate.
 * \li \c c(t)     \c : output cell state.
 * \li \c h(t)     \c : output vector.
 * \par Block Diagram:
 * \image html LSTM.PNG
 *
 * @param[in]      *pLSTMInst              pointer to LSTM instance 
 * @param[out]     *pLSTMInst              pointer to LSTM instance 
 *
 * @return     status of LSTM 
 *             sucesss: 0, fail: 1
 *
 * @note
 *         \li Input should be in AFLOAT format
 *         \li Cell state and output will be generated in AFLOAT format
 *         \li LSTM requires scratch memory of size returned by function macro LSTM_AFLOAT_SCRATCH_MEMORY_REQUIRED_BYTE
 *         \li Appropriate memory(4-byte aligned)  should be allocated to all the pointers before calling this function
 *         \li Null pointer validation is not done to avoid computation over head
 *         \li Cell state and output vector should be initialized to zeros before calling this function for the first time
 *
 * \par Computation time(For regular sigmoid):
 * \par
 * |    n_output   |    n_input   |   Cycles  |
 * |:-------------:|:------------:|:---------:|
 * |     32        |           32 |     12750 |
 * |     32        |           64 |     15822 |
 * |     32        |          128 |     21966 |
 * |     32        |          256 |     34254 |
 * |     32        |          512 |     58830 |
 * |     32        |         1024 |    107982 |
 * |     64        |           32 |     31022 |
 * |     64        |           64 |     37166 |
 * |     64        |          128 |     49454 |
 * |     64        |          256 |     77030 |
 * |     64        |          512 |    123182 |
 * |     64        |         1024 |    221486 |
 * |    128        |           32 |     85998 |
 * |    128        |           64 |     98286 |
 * |    128        |          128 |    122862 |
 * |    128        |          256 |    172014 |
 * |    128        |          512 |    270318 |
 * |    128        |         1024 |    466926 |
 * |    256        |           32 |    269678 |
 * |    256        |           64 |    294254 |
 * |    256        |          128 |    343406 |
 * |    256        |          256 |    441710 |
 * |    256        |          512 |    638318 |
 * |    256        |         1024 |   1031534 |
 * |    512        |           32 |    931950 |
 * |    512        |           64 |    981102 |
 * |    512        |          128 |   1079406 |
 * |    512        |          256 |   1276014 |
 * |    512        |          512 |   1669230 |
 * |    512        |         1024 |   2455662 |
 * |   1024        |           32 |   3436142 |
 * |   1024        |           64 |   3534446 |
 * |   1024        |          128 |   3731054 |
 * |   1024        |          256 |   4124270 |
 * |   1024        |          512 |   4910702 |
 * |   1024        |         1024 |   6483566 |
 *
 ****************************************************************************/
int        LSTMAfloat(LSTMAflt_State *pLSTMInst);



/************************************************************************//**
 * LSTM8bx8b(LSTM8b_State *LstmInst)
 ****************************************************************************
 * @brief       Long term short memory interface for 8-bit weights/biases, Input will be converted to 8-bit
 *
 * @details
 * <pre>    
 *   i(t) = sigmoid( x(t) &sdot; Wi + Ui &sdot; h(t-1) + bi)
 *   f(t) = sigmoid( x(t) &sdot; Wf + Uf &sdot; h(t-1) + bf)
 *   o(t) = sigmoid( x(t) &sdot; Wo + Uo &sdot; h(t-1) + bo)
 *   c(t) = f(t) &times; c(t-1) + i(t) &times; tanh( x(t) &sdot; Wc + Uc &sdot; h(t-1) + bc)
 *   h(t) = o(t) &times; tanh(c(t))
 * </pre>
 * \par Notation:
 * \par
 * \li \c  &sdot;  \c : matrix multiplication 
 * \li \c  &times; \c : vector product.
 * \li \c x(t)     \c : input vector.
 * \li \c c(t-1)   \c : previous cell state.
 * \li \c h(t-1)   \c : previous output vector.
 * \li \c Wi       \c : weights for input to input gate.
 * \li \c Ui       \c : weights for recurrent to input gate.
 * \li \c bi       \c : biases for input gate.
 * \li \c Wf       \c : weights for input to forget gate 
 * \li \c Uf       \c : weights for recurrent to forget gate.
 * \li \c bf       \c : biases for forget gate.
 * \li \c Wc       \c : weights for input to cell state.
 * \li \c Uc       \c : weights for recurrent to cell state.
 * \li \c bc       \c : biases for cell state.
 * \li \c Wo       \c : weights for input to output gate.
 * \li \c Uo       \c : weights for recurrent to output gate.
 * \li \c bo       \c : biases for output gate.
 * \li \c c(t)     \c : output cell state.
 * \li \c h(t)     \c : output vector.
 * \par Block Diagram:
 * \image html LSTM.PNG
 *
 * @param[in]      *pLSTMInst              pointer to LSTM instance 
 * @param[out]     *pLSTMInst              pointer to LSTM instance 
 *
 * @return     status of LSTM
 *             sucesss: 0, fail: 1
 *
 * @note
 *         \li Input should be in AFLOAT format
 *         \li Input AFLOAT data will be converted to 8-bit data before multiplying with weights
 *         \li Cell state and output will be generated in AFLOAT format
 *         \li LSTM requires scratch memory of size returned by function macro LSTM_8bx8b_SCRATCH_MEMORY_REQUIRED_BYTE
 *         \li Appropriate memory(4-byte aligned) should be allocated to all the pointers before calling this function
 *         \li Null pointer validation is not done to avoid computation over head
 *         \li Cell state and output vector should be initialized to zeros before calling this function for the first time
 *         \li All Weights should be mapped to specific format which can be obtained by calling the function Map8bitCoeffsForMVM
 *         \li More details of format can be found at Chapter 4 of "<install_dir>/Knowles_IA8508A_SDK/Docs/Knowles IA8508A Machine Learning Library User Guide.pdf"
 *         \li Function @ref MVMConvert can be used to convert AFLOAT data to 8-bit 
 *
 * \par Computation time(For regular sigmoid):
 * \par
 * |    n_output   |    n_input   |   Cycles  |
 * |:-------------:|:------------:|:---------:|
 * |     32        |           32 |      5747 |
 * |     32        |           64 |      6447 |
 * |     32        |          128 |      7847 |
 * |     32        |          256 |     10674 |
 * |     32        |          512 |     16247 |
 * |     32        |         1024 |     27447 |
 * |     64        |           32 |     11695 |
 * |     64        |           64 |     13035 |
 * |     64        |          128 |     15715 |
 * |     64        |          256 |     21075 |
 * |     64        |          512 |     31795 |
 * |     64        |         1024 |     53235 |
 * |    128        |           32 |     27431 |
 * |    128        |           64 |     30051 |
 * |    128        |          128 |     35291 |
 * |    128        |          256 |     45771 |
 * |    128        |          512 |     66731 |
 * |    128        |         1024 |    108651 |
 * |    256        |           32 |     74263 |
 * |    256        |           64 |     79443 |
 * |    256        |          128 |     89803 |
 * |    256        |          256 |    110523 |
 * |    256        |          512 |    151963 |
 * |    256        |         1024 |    234843 |
 * |    512        |           32 |    229367 |
 * |    512        |           64 |    239667 |
 * |    512        |          128 |    260267 |
 * |    512        |          256 |    301467 |
 * |    512        |          512 |    383867 |
 * |    512        |         1024 |    548667 |
 * |   1024        |           32 |    785335 |
 * |   1024        |           64 |    805875 |
 * |   1024        |          128 |    846955 |
 * |   1024        |          256 |    929115 |
 * |   1024        |          512 |   1093435 |
 * |   1024        |         1024 |   1422075 |
 *
 ****************************************************************************/
int        LSTM8bx8b(LSTM8b_State *pLSTMInst);



/************************************************************************//**
 * LSTM16bx8b(LSTM8b_State *LstmInst)
 ****************************************************************************
 * @brief       Long term short memory interface for 8-bit weights/biases, Input will be converted to 16-bit
 *
 * @details
 *   In side the LSTM using MVM16x8bFast for matMul
 * <pre>    
 *   i(t) = sigmoid( x(t) &sdot; Wi + Ui &sdot; h(t-1) + bi)
 *   f(t) = sigmoid( x(t) &sdot; Wf + Uf &sdot; h(t-1) + bf)
 *   o(t) = sigmoid( x(t) &sdot; Wo + Uo &sdot; h(t-1) + bo)
 *   c(t) = f(t) &times; c(t-1) + i(t) &times; tanh( x(t) &sdot; Wc + Uc &sdot; h(t-1) + bc)
 *   h(t) = o(t) &times; tanh(c(t))
 * </pre>
 * \par Notation:
 * \par
 * \li \c  &sdot;  \c : matrix multiplication 
 * \li \c  &times; \c : vector product.
 * \li \c x(t)     \c : input vector.
 * \li \c c(t-1)   \c : previous cell state.
 * \li \c h(t-1)   \c : previous output vector.
 * \li \c Wi       \c : weights for input to input gate.
 * \li \c Ui       \c : weights for recurrent to input gate.
 * \li \c bi       \c : biases for input gate.
 * \li \c Wf       \c : weights for input to forget gate 
 * \li \c Uf       \c : weights for recurrent to forget gate.
 * \li \c bf       \c : biases for forget gate.
 * \li \c Wc       \c : weights for input to cell state.
 * \li \c Uc       \c : weights for recurrent to cell state.
 * \li \c bc       \c : biases for cell state.
 * \li \c Wo       \c : weights for input to output gate.
 * \li \c Uo       \c : weights for recurrent to output gate.
 * \li \c bo       \c : biases for output gate.
 * \li \c c(t)     \c : output cell state.
 * \li \c h(t)     \c : output vector.
 * \par Block Diagram:
 * \image html LSTM.PNG
 *
 * @return     status of LSTM 
 *             sucesss: 0, fail: 1
 *
 * @param[in]     *pLSTMInst              pointer to LSTM instance 
 * @param[out]    *pLSTMInst              pointer to LSTM instance 
 * @note
 *         \li Input should be in AFLOAT format
 *         \li Input AFLOAT data will be converted to 16-bit data before multiplying with weights
 *         \li Cell state and output will be generated in AFLOAT format
 *         \li LSTM requires scratch memory of size returned by function macro LSTM_16bx8b_SCRATCH_MEMORY_REQUIRED_BYTE
 *         \li Appropriate memory(4-byte aligned) should be allocated to all the pointers before calling this function
 *         \li Null pointer validation is not done to avoid computation over head
 *         \li Cell state and output vector should be initialized to zeros before calling this function for the first time
 *         \li All Weights should be mapped to specific format which can be obtained by calling the function Map8bitCoeffsForMVM
 *         \li More details of format can be found at Chapter 4 of "<install_dir>/Knowles_IA8508A_SDK/Docs/Knowles IA8508A Machine Learning Library User Guide.pdf"
 *         \li Function @ref MVMConvert can be used to convert AFLOAT data to 16-bit
 *
 * \par Computation time(For regular sigmoid):
 * \par
 * |    n_output   |    n_input   |   Cycles  |
 * |:-------------:|:------------:|:---------:|
 * |     32        |           32 |     9547  |
 * |     32        |           64 |    11099  |
 * |     32        |          128 |    14203  |
 * |     32        |          256 |    20411  |
 * |     32        |          512 |    32827  |
 * |     32        |         1024 |    57659  |
 * |     64        |           32 |    20155  |
 * |     64        |           64 |    22987  |
 * |     64        |          128 |    28651  |
 * |     64        |          256 |    39979  |
 * |     64        |          512 |    62635  |
 * |     64        |         1024 |   107947  |
 * |    128        |           32 |    49051  |
 * |    128        |           64 |    54443  |
 * |    128        |          128 |    65227  |
 * |    128        |          256 |    86795  |
 * |    128        |          512 |   129931  |
 * |    128        |         1024 |   216203  |
 * |    256        |           32 |   137563  |
 * |    256        |           64 |   148075  |
 * |    256        |          128 |   169099  |
 * |    256        |          256 |   211147  |
 * |    256        |          512 |   295243  |
 * |    256        |         1024 |   463435  |
 * |    512        |           32 |   437467  |
 * |    512        |           64 |   458219  |
 * |    512        |          128 |   499723  |
 * |    512        |          256 |   582731  |
 * |    512        |          512 |   748747  |
 * |    512        |         1024 |  1080779  |
 * |   1024        |           32 |  1528795  |
 * |   1024        |           64 |  1570027  |
 * |   1024        |          128 |  1652491  |
 * |   1024        |          256 |  1817419  |
 * |   1024        |          512 |  2147275  |
 * |   1024        |         1024 |  2806987  |
 *
 ****************************************************************************/
int        LSTM16bx8b(LSTM8b_State *pLSTMInst);



/************************************************************************//**
 * LSTM16bx16b(LSTM16b_State *LstmInst)
 ****************************************************************************
 * @brief       Long term short memory interface for 16b weights/biases, Input will be converted to 16-bit
 *
 * @details
 * <pre>    
 *   i(t) = sigmoid( x(t) &sdot; Wi + Ui &sdot; h(t-1) + bi)
 *   f(t) = sigmoid( x(t) &sdot; Wf + Uf &sdot; h(t-1) + bf)
 *   o(t) = sigmoid( x(t) &sdot; Wo + Uo &sdot; h(t-1) + bo)
 *   c(t) = f(t) &times; c(t-1) + i(t) &times; tanh( x(t) &sdot; Wc + Uc &sdot; h(t-1) + bc)
 *   h(t) = o(t) &times; tanh(c(t))
 * </pre>
 * \par Notation:
 * \par
 * \li \c  &sdot;  \c : matrix multiplication 
 * \li \c  &times; \c : vector product.
 * \li \c x(t)     \c : input vector.
 * \li \c c(t-1)   \c : previous cell state.
 * \li \c h(t-1)   \c : previous output vector.
 * \li \c Wi       \c : weights for input to input gate.
 * \li \c Ui       \c : weights for recurrent to input gate.
 * \li \c bi       \c : biases for input gate.
 * \li \c Wf       \c : weights for input to forget gate 
 * \li \c Uf       \c : weights for recurrent to forget gate.
 * \li \c bf       \c : biases for forget gate.
 * \li \c Wc       \c : weights for input to cell state.
 * \li \c Uc       \c : weights for recurrent to cell state.
 * \li \c bc       \c : biases for cell state.
 * \li \c Wo       \c : weights for input to output gate.
 * \li \c Uo       \c : weights for recurrent to output gate.
 * \li \c bo       \c : biases for output gate.
 * \li \c c(t)     \c : output cell state.
 * \li \c h(t)     \c : output vector.
 * \par Block Diagram:
 * \image html LSTM.PNG 
 *
 * @param[in]      *pLSTMInst              pointer to LSTM instance 
 * @param[out]     *pLSTMInst              pointer to LSTM instance 
 *
 * @return     status of LSTM
 *             sucesss: 0, fail: 1
 *
 * @note
 *         \li Input should be in AFLOAT format
 *         \li Input AFLOAT data will be converted to 16-bit data before multiplying with weights
 *         \li Cell state and output will be generated in AFLOAT format
 *         \li LSTM requires scratch memory of size returned by function macro LSTM_16bx16b_SCRATCH_MEMORY_REQUIRED_BYTE
 *         \li Appropriate memory(4-byte aligned)  should be allocated to all the pointers before calling this function
 *         \li Null pointer validation is not done to avoid computation over head
 *         \li Cell state and output vector should be initialized to zeros before calling this function for the first time
 *         \li All Weights should be mapped to specific format which can be obtained by calling the function Map16bitCoeffsForMVM
 *         \li More details of format can be found at Chapter 4 of "<install_dir>/Knowles_IA8508A_SDK/Docs/Knowles IA8508A Machine Learning Library User Guide.pdf"
 *         \li Function @ref MVMConvert can be used to convert AFLOAT data to 16-bit
 *
 * \par Computation time(For regular sigmoid):
 * \par
 * |    n_output   |    n_input   |   Cycles  |
 * |:-------------:|:------------:|:---------:|
 * |     32        |           32 |     28151 |
 * |     32        |           64 |     31463 |
 * |     32        |          128 |     38087 |
 * |     32        |          256 |     51335 |
 * |     32        |          512 |     77831 |
 * |     32        |         1024 |    130823 |
 * |     64        |           32 |     58663 |
 * |     64        |           64 |     64535 |
 * |     64        |          128 |     76279 |
 * |     64        |          256 |     99767 |
 * |     64        |          512 |    146743 |
 * |     64        |         1024 |    240695 |
 * |    128        |           32 |    135047 |
 * |    128        |           64 |    146039 |
 * |    128        |          128 |    168023 |
 * |    128        |          256 |    211991 |
 * |    128        |          512 |    299927 |
 * |    128        |         1024 |    475799 |
 * |    256        |           32 |    349255 |
 * |    256        |           64 |    370487 |
 * |    256        |          128 |    412951 |
 * |    256        |          256 |    497879 |
 * |    256        |          512 |    667735 |
 * |    256        |         1024 |   1007447 |
 * |    512        |           32 |   1023431 |
 * |    512        |           64 |   1065143 |
 * |    512        |          128 |   1148567 |
 * |    512        |          256 |   1315415 |
 * |    512        |          512 |   1649111 |
 * |    512        |         1024 |   2316503 |
 * |   1024        |           32 |   3354823 |
 * |   1024        |           64 |   3437495 |
 * |   1024        |          128 |   3602839 |
 * |   1024        |          256 |   3933527 |
 * |   1024        |          512 |   4594903 |
 * |   1024        |         1024 |   5917655 |
 *
 ****************************************************************************/
int        LSTM16bx16b(LSTM16b_State *pLSTMInst);



#ifdef __cplusplus
};
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_LSTM_H__ */



/* End of File */

