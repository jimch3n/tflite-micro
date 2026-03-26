/************************************************************************//**
* @file  ksp_fft.h
*
* @brief A one-line description
*
* The full description goes here
*
* @sa
* Put references to (names of) other relevant files here
*
* @info
* $Author: rmatcha $
* $DateTime: 2021/03/26 02:38:54 $
* $Revision: #1 $
* $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Packages/FrontEnd/ksp_frontend/generic/inc/ksp_fft.h#1 $
*
* @copyright
* Copyright (c) 2017 by Knowles Corporation. All rights reserved.
* <br>
* This software is the confidential and proprietary information of Knowles
* Corporation. ("Confidential Information"). You shall not disclose such
* Confidential Information and shall use it only in accordance with the Terms
* of Sale of Knowles Corporation products and the terms of any license
* agreement you entered into with Knowles Corporation for such products.
* <br>
* KNOWLES CORPORATION SOURCE CODE STRICTLY "AS IS" WITHOUT ANY WARRANTY
* WHATSOEVER, AND KNOWLES CORPORATION EXPRESSLY DISCLAIMS ALL WARRANTIES,
* EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE IMPLIED
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR
* NON-INFRINGEMENT OF THIRD PARTY RIGHTS. KNOWLES CORPORATION SHALL NOT BE
* LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF USING, MODIFYING OR
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
****************************************************************************/

#ifndef __KSP_FFT_HEADER__
#define __KSP_FFT_HEADER__

/******************  External/default library includes  *********************/
#include <string.h>

/******************  Knowles support includes  ******************************/
#include "kmm.h"
#include "ksp_types.h"


/******************  Local typedefs *****************************************/
/**
* Allows to select if the twiddle table is to be generated or provided.
* The twiddle table is in the format of:
*    for(ii=0;ii<(MAX_FFT_SIZE/2);ii++)
*    {
*        angle = ii*2*PI/MAX_FFT_SIZE;
*        TwiddleTable[2*ii] = cos(angle);
*        TwiddleTable[2*ii+1] = -sin(angle);
*    }
*
*/
typedef enum {
    KSP_FFT_TWIDDLE_WANTED = 0,     ///< the module will provide the twiddle table
    KSP_FFT_TWIDDLE_PROVIDED        ///< the caller will provide the twiddle table
} ksp_fft_twiddle_t;

/**
* FFT input type. So far, only real FFT is supported.
*/
typedef enum {
    KSP_FFT_REAL = 0,    /**< For FFT: the input is real
                         For IFFT: the output is real          */
    KSP_FFT_COMPLEX,     /**< For FFT: the input is complex
                         For IFFT: the output is complex       */
} ksp_fft_input_t;

/**
* FFT input type.
*/
typedef enum {
    KSP_FFT_FORWARD = 0,    ///< Perform FFT
    KSP_FFT_BACKWARD,       ///< Perform IFFT
} ksp_fft_direction_t;


/**
* Handle for object, keeping internals hidden -- all KSP modules must have an
* instance handle in their public interface. The state object itself is
* defined in a private interface file.
*/
typedef struct ksp_fft_State *ksp_fft_Handle_t;

/**
* ksp_fft_CreateParams_t defines parameters that impact the allocation
* requirements of a module. These parameters generally control the max sizes
* supported by the object instance.
*/
typedef struct {
    ksp_int32_t maxFftSize;             /**< fft size                   */
    ksp_fft_input_t fftType;            /**< fft input type             */
    ksp_fft_direction_t fftDirection;   /**< fft or ifft                */
    ksp_fft_twiddle_t twiddleWanted;    /**< twiddel wanted or provided */
    ksp_float_t *pTwiddle;	            /**< points into 'data', must be 16-byte aligned */
} ksp_fft_CreateParams_t;


/**
* ksp_fft_ResetParams_t define parameters that control the operation but
* require a module reset. Continuous flow of output is not possible when
* changing these parameters.
*/
typedef struct {
    ksp_int32_t fftSize;                /**< fft size                                    */
    ksp_float_t *pTwiddle;	            /**< points into 'data', must be 16-byte aligned */
} ksp_fft_ResetParams_t;

/**
* ksp_fft_ProcessArgs_t contains the input and parameters that are
* required by the process function to produce an output. The ouput is also
* returned through the same structure.
*/
typedef struct {
    ksp_float_t         *pInp;          ///< Input data for process function
    ksp_float_t         *pOut;          ///< Output from process function
} ksp_fft_ProcessArgs_t;

/******************  Public Functions ***************************************/

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

    /*****************************************************************************
    * ksp_fft_create
    *************************************************************************//**
    * Allocates and returns a handle to ksp_fft state. This function
    * must be called once for a given instance and called before any other
    * functions that operate on the instance.
    *
    * @param[in]   hKmm            KMM instance used for allocation.
    * @param[in]   *pCreateParams  parameters that control object creation
    *
    * @returns  hInst  Returns valid handle instance on successful creation.
    *****************************************************************************/
    ksp_fft_Handle_t ksp_fft_create(
        kmm_Handle_t hKmm,
        const ksp_fft_CreateParams_t *pCreateParams
        );


    /*****************************************************************************
    * ksp_fft_reset
    *************************************************************************//**
    * Resets object and changes control parameters, which generally means
    * continuous output flow is not possible -- i.e., the next ouput from
    * ksp_fft_process may glitch.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pResetParams  Parameters that reset the objects
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_fft_reset(
        ksp_fft_Handle_t hInst,
        ksp_fft_ResetParams_t *pResetParams
        );


    /*****************************************************************************
    * ksp_fft_process
    *************************************************************************//**
    * Generates output based on input, object state and specified params
    *
    * @param[in]   hInst           Handle instance.
    * @param       *pProcessArgs   Pointer to the I/O struct containing the input
    *                              and other information for the module to produce
    *                              an output
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_fft_process(
        ksp_fft_Handle_t hInst,
        ksp_fft_ProcessArgs_t *pArgs
        );

    /*****************************************************************************
    * ksp_fft_get_memory_required
    *************************************************************************//**
    * Provides the number of bytes a ksp_fft (including all modules
    * called by ksp_fft) require for its instance handle.
    *
    * @param[in]   *pCreateParams      Parameters that control memory required
    * @param[out]  *pPersistByteCount  persist memory required for the given config
    *                                  (createParams)
    * @param[out]  *pScratchByteCount  scratch memory required for the given config
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_fft_get_memory_required(
        ksp_fft_CreateParams_t *pCreateParams,
        size_t *pPersistByteCount,
        size_t *pScratchByteCount
        );


    /*****************************************************************************
    * ksp_fft_close
    *************************************************************************//**
    * Closes the object including freeing any memory
    *
    * @param[in]   hInst   Handle instance.

    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_fft_close(
        ksp_fft_Handle_t hInst
        );


#ifdef  __cplusplus
}
#endif  //  __cplusplus


#endif // __KSP_FFT_HEADER__
