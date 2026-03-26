/************************************************************************//**
 * @file
 *
 * @brief MVMBiasAdd interface.
 *
 * $DateTime: 2023/09/03 21:25:38 $
 * $Revision: #1 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MVM_BIASADD_H__
#define __FILE_MVM_BIASADD_H__

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

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




/****************************************************************************
 * Public Functions
 ****************************************************************************/


/************************************************************************//**
* MVMBiasAdd8b()
****************************************************************************
* @brief       Performing add 8-bit biases (b) with MVM output (Ax) 
* Computation time:
*
* |    n   |   Cycles  |
* |:------:|:---------:|
* |      32|      144  |
* |      64|      256  |
* |     128|      480  |
* |     256|      928  |
* |     512|     1824  |
* |    1024|     3616  |
*
* @param[out]   *pOutAflAxb          Pointer to output Ax+b.
* @param[in]    pInAflAx             Pointer to input Ax
* @param[in]    *pIn8bBias           Pointer to input 8-bit Q7 biases
* @param[in]    axExp                Exponent of MVM output (Ax)
* @param[in]    bExp                 Exponent of biases
* @param[in]    iLen                 Number of elements in biase and MVM output (Ax)
*
* @return       None
****************************************************************************/
void MVMBiasAdd8b(fr32 *pOutAflAxb,
        const fr32 *pInAflAx,
        const int8_t *pIn8bBias,
        int32_t axExp,
        int32_t bExp,
        uint32_t iLen
    );
	
	
	
/************************************************************************//**
* MVMBiasAdd16b()
****************************************************************************
* @brief       Performing add 16-bit biases (b) with MVM output (Ax) 
* Computation time:
*
* |    n   |   Cycles  |
* |:------:|:---------:|
* |      32|      128  |
* |      64|      224  |
* |     128|      416  |
* |     256|      800  |
* |     512|     1568  |
* |    1024|     3104  |
*
* @param[out]   *pOutAflAxb          Pointer to output Ax+b.
* @param[in]    pInAflAx             Pointer to input Ax
* @param[in]    *pIn16bBias          Pointer to input 16-bit Q15 biases
* @param[in]    axExp                Exponent of MVM output (Ax)
* @param[in]    bExp                 Exponent of biases
* @param[in]    iLen                 Number of elements in biase and MVM output (Ax)
*
* @return       None
****************************************************************************/
void MVMBiasAdd16b(fr32 *pOutAflAxb,
    const fr32 *pInAflAx,
    const int16_t *pIn16bBias,
    int32_t axExp,
    int32_t bExp,
    uint32_t iLen
);



/************************************************************************//**
* MVMBiasAddAfloat()
****************************************************************************
* @brief       Performing add Afloat biases (b) with MVM output (Ax) 
* Computation time:
*
* |    n   |   Cycles  |
* |:------:|:---------:|
* |      32|      129  |
* |      64|      225  |
* |     128|      417  |
* |     256|      801  |
* |     512|     1569  |
* |    1024|     3105  |
*
* @param[out]   *pOutAflAxb          Pointer to output Ax+b.
* @param[in]    pInAflAx             Pointer to input Ax
* @param[in]    *pInAfltBias         Pointer to input Afloat biases
* @param[in]    axExp                Exponent of MVM output (Ax)
* @param[in]    bExp                 Exponent of biases
* @param[in]    iLen                 Number of elements in biase and MVM output (Ax)
*
* @return       None
****************************************************************************/
void MVMBiasAddAfloat(fr32 *pOutAflAxb,
    const fr32 *pInAflAx,
    const fr32 *pInAfltBias,
    int32_t axExp,
    int32_t bExp,
    uint32_t iLen
);



#ifdef __cplusplus
};
#endif /* __cplusplus */
/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MVM_BIASADD_H__ */



/* End of File */

