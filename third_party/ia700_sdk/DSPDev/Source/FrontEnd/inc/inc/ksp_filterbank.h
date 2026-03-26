#pragma once
/************************************************************************//**
* @file  ksp_filterbank.h
*
* @brief This module implements a Bark domain filterbank
*
* This module provides two options:<br>
* 1. Convert linear frequency contents to bark frequency
* 2. Convert bark frequency contents to linear frequency
*
*
* @info
* $Author: rmatcha $
* $DateTime: 2021/03/26 02:38:54 $
* $Revision: #1 $
* $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Packages/FrontEnd/ksp_frontend/generic/inc/ksp_filterbank.h#1 $
*
* @copyright
* Copyright (c) 2016 by Knowles Corporation. All rights reserved.
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

#ifndef KSP_FILTERBANK_H // Change to upper case and delete comment
#define KSP_FILTERBANK_H // Change to upper case and delete comment

/******************  External/default library includes  *********************/
#include <string.h>

/******************  Knowles support includes  ******************************/
#include "kmm.h"
#include "ksp_types.h"


/******************  Local typedefs *****************************************/
/**
* ksp_filterbank_set_params() uses ksp_filterbank_ParamId_t to control
* which parameters to set. All ksp modules must implement ALL_PARAMS.
*/
typedef enum {
    KSP_FILTERBANK_ALL_PARAMS = 0,

    KSP_FILTERBANK_PARAMS_CNT
} ksp_filterbank_ParamId_t;


/**
* Allows to select between computing filter bank outputs of PSD for the
* filterbank processed output
*/
typedef enum {
    KSP_FILTERBANK_COMPUTE_BARK_SPEC = 0, ///< Convert to bark domain
    KSP_FILTERBANK_COMPUTE_LIN_SPEC         ///< Convert to linear freq domain
} ksp_filterbank_Compute_t;

/**
* Handle for object, keeping internals hidden -- all KSP modules must have an
* instance handle in their public interface. The state object itself is
* defined in a private interface file.
*/
typedef struct ksp_filterbank_State *ksp_filterbank_Handle_t;

/**
* ksp_filterbank_CreateParams_t defines parameters that impact the allocation
* requirements of a module. These parameters generally control the max sizes
* supported by the object instance.
*/
typedef struct {
    ksp_int32_t         maxNBands;      /**< Maximum number of bands in the
                                        filterbank                          */
    ksp_int32_t         maxFftSize;     ///< Maximum supported FFT size
} ksp_filterbank_CreateParams_t;

/**
* ksp_filterbank_ResetParams_t define parameters that control the operation but
* require a module reset. Continuous flow of output is not possible when
* changing these parameters.
*/
typedef struct {
    ksp_uint16_t        nBands;         /**< Maximum number of bands in the filterbank */
    ksp_int32_t         fftSize;        ///< System FFT size
    ksp_int32_t         fs;             ///< Maximum sample rate
#ifndef REF_CODE	
    ksp_float_t         lower_freq_band;
    ksp_float_t         upper_freq_band;
#endif
} ksp_filterbank_ResetParams_t;

/**
* ksp_filterbank_Runtime_t defines parameters that control operation of the object
* that may be changed during runtime without interrupting output flow.
*/
typedef struct {
    char empty;
} ksp_filterbank_RuntimeParams_t;

/**
* ksp_filterbank_ControlParams_t control operation of the module and consist
* of ResetParams and RuntimeParams.
*/
typedef struct {
    ksp_filterbank_ResetParams_t     reset;
    ksp_filterbank_RuntimeParams_t   runtime;
} ksp_filterbank_ControlParams_t;

/**
* Defines data elements that users can get from the module. Scalars will be
* copied, pointers to other data will be returned
*/
typedef struct {
    ksp_int32_t     nBins;
    const ksp_int32_t     *pLeftBank;
    const ksp_int32_t     *pRightBank;
    const ksp_float_t     *pLeftFilter;
    const ksp_float_t     *pRightFilter;
} ksp_filterbank_ModuleData_t;

/**
* ksp_filterbank_ProcessArgs_t contains the input and parameters that are
* required by the process function to produce an output. The ouput is also
* returned through the same structure.
*/
typedef struct {
    ksp_float_t         *pInp;          ///< Input data for process function
    ksp_float_t         *pOut;          ///< Output from process function
    ksp_filterbank_Compute_t
        compute;        /**< Flag to select whether to compute
                        PSD or Banks                        */
} ksp_filterbank_ProcessArgs_t;


/******************  Public Functions ***************************************/

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

    /*****************************************************************************
    * ksp_filterbank_create
    *************************************************************************//**
    * Allocates and returns a handle to ksp_filterbank state. This function
    * must be called once for a given instance and called before any other
    * functions that operate on the instance.
    *
    * @param[in]   hKmm            KMM instance used for allocation.
    * @param[in]   *pCreateParams  parameters that control object creation
    *
    * @returns  hInst  Returns valid handle instance on successful creation.
    *****************************************************************************/
    ksp_filterbank_Handle_t ksp_filterbank_create(
        kmm_Handle_t hKmm,
        const ksp_filterbank_CreateParams_t *pCreateParams
    );


    /*****************************************************************************
    * ksp_filterbank_reset
    *************************************************************************//**
    * Resets object and changes control parameters, which generally means
    * continuous output flow is not possible -- i.e., the next ouput from
    * ksp_filterbank_process may glitch.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pControlParams parameters that reset the objects
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_filterbank_reset(
        ksp_filterbank_Handle_t hInst,
        const ksp_filterbank_ControlParams_t *pControlParams
    );


    /*****************************************************************************
    * ksp_filterbank_set_params
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
    ksp_status_t ksp_filterbank_set_params(
        ksp_filterbank_Handle_t hInst,
        const ksp_filterbank_RuntimeParams_t *pRuntimeParams,
        ksp_filterbank_ParamId_t param
    );


    /*****************************************************************************
    * ksp_filterbank_process
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
    ksp_status_t ksp_filterbank_process(
        ksp_filterbank_Handle_t hInst,
        ksp_filterbank_ProcessArgs_t *pArgs
    );


    /*****************************************************************************
    * ksp_filterbank_get_params
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
    ksp_status_t ksp_filterbank_get_params(
        ksp_filterbank_Handle_t hInst,
        ksp_filterbank_ControlParams_t *pControlParams
    );


    /*****************************************************************************
    * ksp_filterbank_get_data
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
    ksp_status_t ksp_filterbank_get_data(
        ksp_filterbank_Handle_t hInst,
        ksp_filterbank_ModuleData_t *pModuleData
    );


    /*****************************************************************************
    * ksp_filterbank_get_memory_required
    *************************************************************************//**
    * Provides the number of bytes a ksp_filterbank (including all modules
    * called by ksp_filterbank) require for its instance handle.
    *
    * @param[in]   *pCreateParams      Parameters that control memory required
    * @param[out]  *pPersistByteCount  persist memory required for the given config
    *                                  (createParams)
    * @param[out]  *pScratchByteCount  scratch memory required for the given config
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_filterbank_get_memory_required(
        ksp_filterbank_CreateParams_t *pCreateParams,
        size_t *pPersistByteCount,
        size_t *pScratchByteCount
    );


    /*****************************************************************************
    * ksp_filterbank_close
    *************************************************************************//**
    * Closes the object including freeing any memory
    *
    * @param[in]   hInst   Handle instance.

    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_filterbank_close(
        ksp_filterbank_Handle_t hInst
    );


#ifdef  __cplusplus
}
#endif  //  __cplusplus


#endif // ksp_filterbank_H
