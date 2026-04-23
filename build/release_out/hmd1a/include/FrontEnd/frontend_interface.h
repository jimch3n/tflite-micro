/************************************************************************//**
* @file  frontend.h
*
 * @brief A one-line description
*
 * The full description goes here
 *
 * @sa
 * Put references to (names of) other relevant files here
*
* @info
* $Author: jimchen $
* $DateTime: 2022/07/13 02:57:03 $
* $Revision: #1 $
* $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Cores/Core_Hmd1a/TFLu/Include/FrontEnd/frontend_interface.h#1 $
*
* @copyright
 * Copyright (c) 2021 by Knowles Corporation. All rights reserved.
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

#ifndef FRONTEND_INTERFACE_H //
#define FRONTEND_INTERFACE_H //

/******************  External/default library includes  *********************/
/******************  Knowles support includes  ******************************/
#include "kmm.h"
//#include "../../FrontendParams.h"
//#include "tensorflow/lite/c/common.h"
/******************  Local typedefs *****************************************/

// return status
typedef enum {
	SUCCESS = 0,
	FAILURE = 1,  // generic failure
	MEMORY_FAILURE = 2,
	UNRELIABLE = 3
	// etc...
} status_t;


/**
* Handle for object, keeping internals hidden -- all KSP modules must have an
* instance handle in their public interface. The state object itself is
* defined in a private interface file.
*/
typedef void* frontend_Handle_t;

/**
* frontend_CreateParams_t defines parameters that impact the allocation
* requirements of a module. These parameters generally control the max sizes
* supported by the object instance.
*/
#if 0 // replace
typedef struct {
    int32_t               empty;
} frontend_CreateParams_t;
#endif

typedef enum {
	FRONT_END_LOGMELSPEC = 1,
	FRONT_END_MFCC = 2,
	FRONT_END_UNKOWN = 3
} front_end_feature_select_t;

/**
* frontend_ResetParams_t define parameters that control the operation but
* require a module reset. Continuous flow of output is not possible when
* changing these parameters.
*/
typedef struct {
	int32_t             stftWinType;

	AScalar         lower_freq_band;
	AScalar         upper_freq_band;

	front_end_feature_select_t featureSelect;
} frontend_ResetParams_t;

/**
* frontend_Runtime_t defines parameters that control operation of the object
* that may be changed during runtime without interrupting output flow.
*/
typedef struct {
    char empty;
} frontend_RuntimeParams_t;

/**
* frontend_ControlParams_t control operation of the module and consist
* of ResetParams and RuntimeParams.
*/
typedef struct {
    frontend_ResetParams_t     reset;
    frontend_RuntimeParams_t   runtime;
} frontend_ControlParams_t;

/**
* Defines data elements that users can get from the module. Scalars will be
* copied, pointers to other data will be returned
*/

/**
* frontend_ProcessArgs_t contains the input and parameters that are
* required by the process function to produce an output. The ouput is also
* returned through the same structure.
*/
typedef struct {
    AScalar                *pIn;           ///< Input data for process function
	float                  *pOut;          ///< Output data from process, float or int8_t
} frontend_ProcessArgs_t;


/******************  Public Functions ***************************************/

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

    /*****************************************************************************
    * frontend_create
    *************************************************************************//**
    * Allocates and returns a handle to frontend state. This function
    * must be called once for a given instance and called before any other
    * functions that operate on the instance.
    *
    * @param[in]   hKmm            KMM instance used for allocation.
    * @param[in]   *pCreateParams  parameters that control object creation
    *
    * @returns  hInst  Returns valid handle instance on successful creation.
    *****************************************************************************/
    frontend_Handle_t frontend_create(
        kmm_Handle_t hKmm,
        const frontend_config_t *pCreateParams
    );


    /*****************************************************************************
    * frontend_reset
    *************************************************************************//**
    * Resets object and changes control parameters, which generally means
    * continuous output flow is not possible -- i.e., the next ouput from
    * frontend_process may glitch.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pControlParams parameters that reset the objects
    *
    * @returns status      Returns KSP_SUCCESS or status_t type value for the
    error.
    *****************************************************************************/
    status_t frontend_reset(
        frontend_Handle_t hInst,
		const frontend_config_t *pControlParams
    );


    /*****************************************************************************
    * frontend_process
    *************************************************************************//**
    * Generates output based on input, object state and specified params
    *
    * @param[in]   hInst           Handle instance.
    * @param       *pProcessArgs   Pointer to the I/O struct containing the input
    *                              and other information for the module to produce
    *                              an output
    *
    * @returns status      Returns KSP_SUCCESS or status_t type value for the
    error.
    *****************************************************************************/
    status_t frontend_process(
        frontend_Handle_t hInst,
        frontend_ProcessArgs_t *pArgs
    );

    /*****************************************************************************
    * frontend_get_memory_required
    *************************************************************************//**
    * Provides the number of bytes a frontend (including all modules
    * called by frontend) require for its instance handle.
    *
    * @param[in]   *pCreateParams      Parameters that control memory required
    * @param[out]  *pPersistByteCount  persist memory required for the given config
    *                                  (createParams)
    * @param[out]  *pScratchByteCount  scratch memory required for the given config
    *
    * @returns status      Returns KSP_SUCCESS or status_t type value for the
    error.
    *****************************************************************************/
    status_t frontend_get_memory_required(
		frontend_config_t *pCreateParams,
        size_t *pPersistByteCount,
        size_t *pScratchByteCount
    );


#ifdef  __cplusplus
}
#endif  //  __cplusplus

#endif // FRONTEND_INTERFACE_H
