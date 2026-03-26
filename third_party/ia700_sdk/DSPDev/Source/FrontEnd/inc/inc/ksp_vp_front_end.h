/************************************************************************//**
* @file  ksp_vp_front_end.h
*
* @brief Provides the public interface for the VP Front End module
*
* Contains definitions of public types and functions that can be used by
* applications using this module
*
* @sa
* Put references to (names of) other relevant files here
*
* @info
* $Author: rmatcha $
* $DateTime: 2021/03/26 02:38:54 $
* $Revision: #1 $
* $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Packages/FrontEnd/ksp_frontend/generic/inc/ksp_vp_front_end.h#1 $
*
* @copyright
 * Copyright (c) 2018 by Knowles Corporation. All rights reserved.
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

#ifndef ksp_vp_front_end_H // Change to upper case and delete comment
#define ksp_vp_front_end_H // Change to upper case and delete comment

/******************  External/default library includes  *********************/
#include <string.h>

/******************  Knowles support includes  ******************************/
#include "kmm.h"
#include "ksp_math.h"
#include "ksp_types.h"

/******************  Module includes  ***************************************/

/******************  Local typedefs *****************************************/

/**
* Defines function selection modes of operation in ksp_vp_front_end
*/
typedef enum {
    KSP_VP_FRONT_END_STFT = 1, 
    KSP_VP_FRONT_END_COVARIANCE = 2, 
    KSP_VP_FRONT_END_STFT_AND_COVARIANCE = 3,
    KSP_VP_FRONT_END_STFT_SINGLE_CHANNEL = 4
} ksp_vp_front_end_process_select_t;

/**
* Handle for object, keeping internals hidden -- all KSP modules must have an
* instance handle in their public interface. The state object itself is
* defined in a private interface file.
*/
typedef struct ksp_vp_front_end_State *ksp_vp_front_end_Handle_t;

/**
* ksp_vp_front_end_CreateParams_t defines parameters that impact the allocation
* requirements of a module. These parameters generally control the max sizes
* supported by the object instance.
*/
typedef struct {
    AScalar               frameSize_ms;               /**< Maximum supported frame size */
#ifdef REF_CODE
    ksp_math_OverlapPct_t overlapPct;                 ///< Percentage overlap
#else
    AScalar               windowSize_ms;              /**< Maximum supported window size */
#endif
    ksp_int32_t           nSigs;                      /**< Maximum  number of signals (Mic signal or reference channels for AEC) supported */
    int32_t               sampleRate_Hz;              /**< Maximum sampling rate */
} ksp_vp_front_end_CreateParams_t;

/**
* ksp_vp_front_end_ResetParams_t define parameters that control the operation but
* require a module reset. Continuous flow of output is not possible when
* changing these parameters.
*/
typedef struct {
    int32_t              stftWinType;                    /**< Window type to be used for forward STFT */
} ksp_vp_front_end_ResetParams_t;

/**
* ksp_vp_front_end_ControlParams_t control operation of the module and consist
* of ResetParams and RuntimeParams.
*/
typedef struct {
    ksp_vp_front_end_ResetParams_t     reset;
} ksp_vp_front_end_ControlParams_t;

/**
* ksp_vp_front_end_ProcessArgs_t contains the input and parameters that are
* required by the process function to produce an output. The ouput is also
* returned through the same structure.
*/
typedef struct {
    ksp_float_vector_scaled_t   SigVec;
    ksp_float_t                 *pTdStftIo;
    ksp_complex_t               **pSigSpecBuf;
    ksp_complex_t               *pCov;              ///< covariance matrix for multi-channel STFT frames
    ksp_int32_t                 chanIdx;
    ksp_vp_front_end_process_select_t feProcessSelect;
} ksp_vp_front_end_ProcessArgs_t;


/******************  Public Functions ***************************************/

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

    /*****************************************************************************
    * ksp_vp_front_end_create
    *************************************************************************//**
    * Allocates and returns a handle to ksp_vp_front_end state. This function
    * must be called once for a given instance and called before any other
    * functions that operate on the instance.
    *
    * @param[in]   hKmm            KMM instance used for allocation.
    * @param[in]   *pCreateParams  parameters that control object creation
    *
    * @returns  hInst  Returns valid handle instance on successful creation.
    *****************************************************************************/
    ksp_vp_front_end_Handle_t ksp_vp_front_end_create(
        kmm_Handle_t hKmm,
        const ksp_vp_front_end_CreateParams_t *pCreateParams
    );


    /*****************************************************************************
    * ksp_vp_front_end_reset
    *************************************************************************//**
    * Resets object and changes control parameters, which generally means
    * continuous output flow is not possible -- i.e., the next ouput from
    * ksp_vp_front_end_process may glitch.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pControlParams parameters that reset the objects
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_vp_front_end_reset(
        ksp_vp_front_end_Handle_t hInst,
        const ksp_vp_front_end_ControlParams_t *pControlParams
    );


    /*****************************************************************************
    * ksp_vp_front_end_set_params
    *************************************************************************//**
    * Sets RuntimeParams on the fly while maintaining continuous output flow.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pRuntimeParams pointer to struct containing value of the
    param to be set
    * @param[in]   param           parameter to be set
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    /*ksp_status_t ksp_vp_front_end_set_params(
        ksp_vp_front_end_Handle_t hInst,
        const ksp_vp_front_end_RuntimeParams_t *pRuntimeParams,
        ksp_vp_front_end_ParamId_t param
    );*/


    /*****************************************************************************
    * ksp_vp_front_end_process
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
    ksp_status_t ksp_vp_front_end_process(
        ksp_vp_front_end_Handle_t hInst,
        ksp_vp_front_end_ProcessArgs_t *pArgs
    );


    /*****************************************************************************
    * ksp_vp_front_end_get_params
    *************************************************************************//**
    * Reads the requested control parameters from the state instance and copies
    * (shallow copy) them into the supplied control parameter structure.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pControlParams Parameters that reset the objects
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    /*ksp_status_t ksp_vp_front_end_get_params(
        ksp_vp_front_end_Handle_t hInst,
        ksp_vp_front_end_ControlParams_t *pControlParams
    );*/


    /*****************************************************************************
    * ksp_vp_front_end_get_data
    *************************************************************************//**
    * Gets data internal to the the module. This should only be used in debug
    * builds. This should be compiled out in Release builds
    *
    * @param[in]   hInst           Handle instance.
    * @param[out]  *pModuleData    Pointer to the data requested
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    /*ksp_status_t ksp_vp_front_end_get_data(
        ksp_vp_front_end_Handle_t hInst,
        ksp_vp_front_end_ModuleData_t *pModuleData
    );*/


    /*****************************************************************************
    * ksp_vp_front_end_get_memory_required
    *************************************************************************//**
    * Provides the number of bytes a ksp_vp_front_end (including all modules
    * called by ksp_vp_front_end) require for its instance handle.
    *
    * @param[in]   *pCreateParams      Parameters that control memory required
    * @param[out]  *pPersistByteCount  persist memory required for the given config
    *                                  (createParams)
    * @param[out]  *pScratchByteCount  scratch memory required for the given config
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_vp_front_end_get_memory_required(
        ksp_vp_front_end_CreateParams_t *pCreateParams,
        size_t *pPersistByteCount,
        size_t *pScratchByteCount
    );


    /*****************************************************************************
    * ksp_vp_front_end_close
    *************************************************************************//**
    * Closes the object including freeing any memory
    *
    * @param[in]   hInst   Handle instance.

    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_vp_front_end_close(
        ksp_vp_front_end_Handle_t hInst
    );


#ifdef  __cplusplus
}
#endif  //  __cplusplus


#endif // ksp_vp_front_end_H
