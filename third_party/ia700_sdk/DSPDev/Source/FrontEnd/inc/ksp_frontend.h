/************************************************************************//**
* @file  ksp_frontend.h
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
* $DateTime: 2021/11/17 21:05:30 $
* $Revision: #2 $
* $Id: //AudEngr/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Knowles_IA700_SDK/DSPDev/Source/FrontEnd/inc/ksp_frontend.h#2 $
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

#ifndef KSP_FRONTEND_H // Change to upper case and delete comment
#define KSP_FRONTEND_H // Change to upper case and delete comment

/******************  External/default library includes  *********************/
/******************  Knowles support includes  ******************************/
#include "ksp_types.h"
#include "ksp_vp_front_end.h"
#include "ksp_filterbank.h"
#include "tensorflow/lite/c/common.h"
 // convert to 16F
#define MELFBNK_SIGN 1
#define MELFBNK_EXP 2
#define MELFBNK_BIAS 3



/******************  Local typedefs *****************************************/
/**
* ksp_frontend_set_params() uses ksp_frontend_ParamId_t to control
* which parameters to set. All ksp modules must implement ALL_PARAMS.
*/
typedef enum {
    KSP_FRONTEND_ALL_PARAMS = 0,

    KSP_FRONTEND_PARAMS_CNT
} ksp_frontend_ParamId_t;


/**
* Allows to select between computing filter bank outputs of PSD for the
* filterbank processed output
*/
typedef enum {
    ksp_frontend_ENUM_ENTRY_1 = 0, ///< 
    ksp_frontend_ENUM_ENTRY_2      ///< 
} ksp_frontend_EnumName_t;
/**
* Allows to select between logmelSpec or mfcc
*/
typedef enum {
	KSP_FRONT_END_LOGMELSPEC = 1,
	KSP_FRONT_END_MFCC = 2,
	KSP_FRONT_END_UNKOWN = 3
} ksp_front_end_feature_select_t;
/**
* Handle for object, keeping internals hidden -- all KSP modules must have an
* instance handle in their public interface. The state object itself is
* defined in a private interface file.
*/
typedef struct ksp_frontend_State *ksp_frontend_Handle_t;

/**
* ksp_frontend_CreateParams_t defines parameters that impact the allocation
* requirements of a module. These parameters generally control the max sizes
* supported by the object instance.
*/
typedef struct {
    AScalar               frameSize_ms;               /**< Maximum supported frame size */
#ifdef REF_CODE
    ksp_math_OverlapPct_t overlapPct;
#else
    AScalar               windowSize_ms;              /**< Maximum supported window size */
#endif
    int32_t               sampleRate_Hz;              /**< Maximum sampling rate */
    int32_t               maxBands;
    int32_t               mfccCoeffs;                   /*mfcc coefficients*/
#ifdef USE_STFT_TO_MEL_OPT
    ksp_float_t         lower_freq_band;
    ksp_float_t         upper_freq_band;
#endif
} ksp_frontend_CreateParams_t;

/**
* ksp_frontend_ResetParams_t define parameters that control the operation but
* require a module reset. Continuous flow of output is not possible when
* changing these parameters.
*/
typedef struct {
    int32_t             stftWinType;
#ifndef USE_DELTAMAX_STFT_TO_MEL_OPT // move to create
    ksp_float_t         lower_freq_band;
    ksp_float_t         upper_freq_band;
#endif
	// log mel parameters
	ksp_float_t         log_mel_offset;
	ksp_float_t         log_mel_clip_min;
	// quanization params
	ksp_uint16_t         quantize; //flag to enable quantize
	ksp_float_t         quantize_inv_scale;
	ksp_float_t         quantize_zero_point;
	ksp_front_end_feature_select_t featureSelect;
} ksp_frontend_ResetParams_t;

/**
* ksp_frontend_Runtime_t defines parameters that control operation of the object
* that may be changed during runtime without interrupting output flow.
*/
typedef struct {
    char empty;
} ksp_frontend_RuntimeParams_t;

/**
* ksp_frontend_ControlParams_t control operation of the module and consist
* of ResetParams and RuntimeParams.
*/
typedef struct {
    ksp_frontend_ResetParams_t     reset;
    ksp_frontend_RuntimeParams_t   runtime;
} ksp_frontend_ControlParams_t;

/**
* Defines data elements that users can get from the module. Scalars will be
* copied, pointers to other data will be returned
*/
typedef struct {
    const ksp_float_t   *pBuffer1;
} ksp_frontend_ModuleData_t;

/**
* ksp_frontend_ProcessArgs_t contains the input and parameters that are
* required by the process function to produce an output. The ouput is also
* returned through the same structure.
*/
typedef struct {
    ksp_float_t         *pIn;           ///< Input data for process function
	TfLitePtrUnion      pOut;          ///< Output from process function
   // ksp_front_end_feature_select_t feature; ///< output feature select
} ksp_frontend_ProcessArgs_t;


/******************  Public Functions ***************************************/

#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus

    /*****************************************************************************
    * ksp_frontend_create
    *************************************************************************//**
    * Allocates and returns a handle to ksp_frontend state. This function
    * must be called once for a given instance and called before any other
    * functions that operate on the instance.
    *
    * @param[in]   hKmm            KMM instance used for allocation.
    * @param[in]   *pCreateParams  parameters that control object creation
    *
    * @returns  hInst  Returns valid handle instance on successful creation.
    *****************************************************************************/
    ksp_frontend_Handle_t ksp_frontend_create(
        kmm_Handle_t hKmm,
        const ksp_frontend_CreateParams_t *pCreateParams
    );


    /*****************************************************************************
    * ksp_frontend_reset
    *************************************************************************//**
    * Resets object and changes control parameters, which generally means
    * continuous output flow is not possible -- i.e., the next ouput from
    * ksp_frontend_process may glitch.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pControlParams parameters that reset the objects
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_frontend_reset(
        ksp_frontend_Handle_t hInst,
        const ksp_frontend_ControlParams_t *pControlParams
    );


    /*****************************************************************************
    * ksp_frontend_set_params
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
    ksp_status_t ksp_frontend_set_params(
        ksp_frontend_Handle_t hInst,
        const ksp_frontend_RuntimeParams_t *pRuntimeParams,
        ksp_frontend_ParamId_t param
    );


    /*****************************************************************************
    * ksp_frontend_process
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
    ksp_status_t ksp_frontend_process(
        ksp_frontend_Handle_t hInst,
        ksp_frontend_ProcessArgs_t *pArgs
    );


    /*****************************************************************************
    * ksp_frontend_get_params
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
    ksp_status_t ksp_frontend_get_params(
        ksp_frontend_Handle_t hInst,
        ksp_frontend_ControlParams_t *pControlParams
    );


    /*****************************************************************************
    * ksp_frontend_get_data
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
    ksp_status_t ksp_frontend_get_data(
        ksp_frontend_Handle_t hInst,
        ksp_frontend_ModuleData_t *pModuleData
    );


    /*****************************************************************************
    * ksp_frontend_get_memory_required
    *************************************************************************//**
    * Provides the number of bytes a ksp_frontend (including all modules
    * called by ksp_frontend) require for its instance handle.
    *
    * @param[in]   *pCreateParams      Parameters that control memory required
    * @param[out]  *pPersistByteCount  persist memory required for the given config
    *                                  (createParams)
    * @param[out]  *pScratchByteCount  scratch memory required for the given config
    *
    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_frontend_get_memory_required(
        ksp_frontend_CreateParams_t *pCreateParams,
        size_t *pPersistByteCount,
        size_t *pScratchByteCount
    );


    /*****************************************************************************
    * ksp_frontend_close
    *************************************************************************//**
    * Closes the object including freeing any memory
    *
    * @param[in]   hInst   Handle instance.

    * @returns status      Returns KSP_SUCCESS or ksp_status_t type value for the
    error.
    *****************************************************************************/
    ksp_status_t ksp_frontend_close(
        ksp_frontend_Handle_t hInst
    );


#ifdef  __cplusplus
}
#endif  //  __cplusplus


#endif // KSP_FRONTEND_H
