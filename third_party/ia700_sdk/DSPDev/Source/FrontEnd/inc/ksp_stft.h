/************************************************************************//**
* @file  ksp_stft.h
*
* @brief Provides the public interface for the STFT module
*
* Contains definitions of public types and functions that can be used by
* applications using this module
*
* @info
* $Author: rmatcha $
* $DateTime : 2016 / 05 / 04 13 : 44 : 27 $
* $Revision : #2 $
* $Id: //AudEngr/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Knowles_IA700_SDK/DSPDev/Source/FrontEnd/inc/ksp_stft.h#1 $
*
* @copyright
* Copyright(c) 2016 by Knowles Corporation.All rights reserved.
*
* This software is the confidential and proprietary information of Knowles
* Corporation. ("Confidential Information").You shall not disclose such
* Confidential Information and shall use it only in accordance with the Terms
* of Sale of Knowles Corporation products and the terms of any license
* agreement you entered into with Knowles Corporation for such products.
* <br>
* KNOWLES CORPORATION SOURCE CODE STRICTLY "AS IS" WITHOUT ANY WARRANTY
* WHATSOEVER, AND KNOWLES CORPORATION EXPRESSLY DISCLAIMS ALL WARRANTIES,
* EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE IMPLIED
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR
* NON - INFRINGEMENT OF THIRD PARTY RIGHTS.KNOWLES CORPORATION SHALL NOT BE
* LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF USING, MODIFYING OR
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
*****************************************************************************/

#ifndef KSP_STFT_H
#define KSP_STFT_H

/******************  Knowles support includes  ******************************/
#include "kmm.h"
#include "ksp_math.h"
#include "ksp_fft.h"


/******************  Self includes  *****************************************/


/******************  Local typedefs *****************************************/

/// List of settable parameters
typedef enum {

    KSP_STFT_ALL_PARAMS           ///< Set all params
} ksp_stft_ParamId_t;

/**
* Handle for object, keeping internals hidden -- all KSP modules must have an
* instance handle in their public interface. The state object itself is
* defined in a privite interface file.
*/
typedef struct ksp_stft_State *ksp_stft_Handle_t;

/**
* ksp_stft_CreateParams_t defines parameters that impact the allocation
* requirements of a module.  These parameters generally control the max sizes
* supported by the object instance.
*/
typedef struct {
    ksp_uint16_t        maxFftSize;     ///< Size of the FFT
    ksp_fft_direction_t fftDirection;   ///< Forward or backward FFT
} ksp_stft_CreateParams_t;

/**
* ksp_stft_ResetParams_t define parameters that control the operation but
* require a module reset. Continuous flow of output is not possible when
* changing these parameters.
*/
typedef struct {
    ksp_uint16_t        fftSize;        ///< Size of the FFT
    ksp_uint16_t        frameSize;      ///< Number of samples in TD frame
#ifdef REF_CODE
    ksp_math_OverlapPct_t
                        overlap;        ///< Percentage overlap
#else
    ksp_uint16_t        windowSize;
#endif
    ksp_math_Window_t   windowType;     ///< Type of window to be used
#ifndef USE_WINDOW_FLT16
    ksp_float_t         *pWin;          ///< Window to be used for forward FFT
#else
    ksp_uint16_t        *pWin; 
#endif
} ksp_stft_ResetParams_t;

/**
* ksp_stft_Runtime_t defines parameters that control operation of the object
* that may be changed during runtime without interrupting output flow.  This
* structure may contain simple types such as int or ksp_float_t, but may also
* include pointers.  In the later case, this module will NOT allocate memory
* for this, the user will own or have access to the underlying object and
* provide this module access via functions described below.
*/
typedef struct {
    char empty;
} ksp_stft_RuntimeParams_t;

/**
* Paramaters that control operation of the object that consists of ResetParams
* and RuntimeParams.
*/
typedef struct {
    ksp_stft_ResetParams_t reset;
    ksp_stft_RuntimeParams_t runtime;
} ksp_stft_ControlParams_t;

/**
* Defines data elements that users can get from the module.  Scalars will be
* copied, pointers to other data will be returned
*/
typedef struct {
    const ksp_float_t *pDataPtr;    ///< Pointer to internal overlap buffer
    ksp_uint16_t dataLen;           ///< Length of overlap buffer
} ksp_stft_ModuleData_t;

/**
* ksp_stft_ProcessArgs_t contains the input and parameters that are
* required by the process function to produce an output. The ouput is also
* returned through the same structure.
*/
typedef struct {
    ksp_complex_t   *pFdBuf;    /**< This is a pointer to the a 
                        buffer that contains frequency domain data. For 
                        forward FFT, this is output and for backward FFT this 
                        is input                                            */
    ksp_float_t		*pTdBuf;    /**< This is a pointer to a buffer
                       that contains time domain data. For forward FFT, this 
                       is input and for backward FFT this is output         */
} ksp_stft_ProcessArgs_t;


/******************  Public Functions ***************************************/

/******************  Public Functions ***************************************/
#ifdef  __cplusplus
extern "C" {
#endif  // __cplusplus
    /*****************************************************************************
    * ksp_stft_create
    *************************************************************************//**
    * Allocates and returns a handle to ksp_stft state. This function must be
    * must be called once for a given instance and called before any other
    * functions that operate on the instance.
    *
    * @param[in]   hKmm            KMM instance used for allocation.
    * @param[in]   *pCreateParams  parameters that control object creation
    *
    * @returns  hInst  Returns valid handle instance on successful creation.
    *****************************************************************************/
    ksp_stft_Handle_t ksp_stft_create(
        kmm_Handle_t hKmm,
        const ksp_stft_CreateParams_t *pCreateParams
        );


    /*****************************************************************************
    * ksp_stft_reset
    *************************************************************************//**
    * Resets object and changes control parameters, which generally means
    * continuous output flow is not possible -- i.e., the next ouput from
    * ksp_stft_process may glitch.
    *
    * @param[in]   hInst            Handle instance.
    * @param[in]   *pControlParams  Parameters that reset the objects
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
                        for the error.
    *****************************************************************************/
    ksp_status_t ksp_stft_reset(
        ksp_stft_Handle_t hInst,
        const ksp_stft_ControlParams_t *pControlParams
        );


    /*****************************************************************************
    * ksp_stft_set_params
    *************************************************************************//**
    * Sets RuntimeParams on the fly while maintaining continuous output flow.
    *
    * @param[in]   hInst            Handle instance.
    * @param[in]   *pRuntimeParams  Pointer to struct containing value of the
                            param to be set
    * @param[in]   param            Parameter to be set
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
                        for the error.
    *****************************************************************************/
    ksp_status_t ksp_stft_set_params(
        ksp_stft_Handle_t hInst,
        const ksp_stft_ParamId_t param,
        const ksp_stft_RuntimeParams_t *pRuntimeParams
        );


    /*****************************************************************************
    * ksp_stft_process
    *************************************************************************//**
    * Generates output based on input, object state and specified params
    *
    * @param[in]    hInst           Handle instance.
    * @param        *pProcessArgs   Pointer to the I/O struct containing the input
    *                               and other information for the module to produce
    *                               an output
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
                        for the error.
    *****************************************************************************/
    ksp_status_t ksp_stft_process(
        ksp_stft_Handle_t hInst,
        ksp_stft_ProcessArgs_t *io
        );


    /*****************************************************************************
    * ksp_stft_get_params
    *************************************************************************//**
    * Reads the requested control parameters from the state instance and copies
    * (shallow copy) them into the supplied control parameter structure.
    *
    * @param[in]   hInst           Handle instance.
    * @param[in]   *pControlParams Parameters that reset the objects
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
                        for the error.
    *****************************************************************************/
    ksp_status_t ksp_stft_get_params(
        ksp_stft_Handle_t hInst,
        ksp_stft_ControlParams_t *pControlParams
        );


    /*****************************************************************************
    * ksp_stft_get_data
    *************************************************************************//**
    * Gets data internal to the the module. This should only be used in debug
    * builds. This should be compiled out in Release builds
    *
    * @param[in]   hInst            Handle instance.
    * @param[out]  *pModuleData     Pointer to the data requested
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
                        for the error.
    *****************************************************************************/
    ksp_status_t ksp_stft_get_data(
        ksp_stft_Handle_t hInst,
        ksp_stft_ModuleData_t *moduleData
        );


    /*****************************************************************************
    * ksp_stft_get_memory_required
    *************************************************************************//**
    * Provides the number of bytes a ksp_stft (including all modules
    * called by ksp_stft) require for its instance handle.


    * @param[in]   *pCreateParams      Parameters that control memory required
    * @param[out]  *pPersistByteCount  persist memory required for the given config
    *                                  (createParams)
    * @param[out]  *pScratchByteCount  scratch memory required for the given config
    *
    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
    for the error.
    *****************************************************************************/
    ksp_status_t ksp_stft_get_memory_required(
        ksp_stft_CreateParams_t *pCreateParams,
        size_t *pPersistByteCount,
        size_t *pScratchByteCount
        );

    /*****************************************************************************
    * ksp_stft_close
    *************************************************************************//**
    * Closes the object including freeing any memory
    *
    * @param[in]    hInst           Handle instance.

    * @returns  ksp_status_t    Returns KSP_SUCCESS or ksp_status_t type value
                        for the error.
    *****************************************************************************/
    ksp_status_t ksp_stft_close(
        ksp_stft_Handle_t hInst
        );

#ifdef  __cplusplus
}
#endif  //  __cplusplus


#endif /* KSP_STFT_H */
