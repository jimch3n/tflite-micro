/************************************************************************//**
* @file  ksp_stft_state.h
*
* @brief Maintains the internal state of STFT
*
* Maintains the overlap buffer and allocates memory for any scratch buffers
* that may be needed by the module
*
* @seealso
* Put references to (names of) other relevant files here
*
* @info
* $Author: rmatcha $
* $DateTime: 2021/03/26 02:38:54 $
* $Revision: #1 $
* $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Packages/FrontEnd/ksp_frontend/generic/inc/ksp_stft_state.h#1 $
*
* @copyright
* Copyright (c) 2016 by Knowles Corporation. All rights reserved.
*
* This software is the confidential and proprietary information of Knowles
* Corporation. ("Confidential Information"). You shall not disclose such
* Confidential Information and shall use it only in accordance with the Terms
* of Sale of Knowles Corporation products and the terms of any license
* agreement you entered into with Knowles Corporation for such products.
*
* KNOWLES CORPORATION SOURCE CODE STRICTLY "AS IS" WITHOUT ANY WARRANTY
* WHATSOEVER, AND KNOWLES CORPORATION EXPRESSLY DISCLAIMS ALL WARRANTIES,
* EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE IMPLIED
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR
* NON-INFRINGEMENT OF THIRD PARTY RIGHTS. KNOWLES CORPORATION SHALL NOT BE
* LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF USING, MODIFYING OR
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
****************************************************************************/

#ifndef KSP_STFT_STATE_H
#define KSP_STFT_STATE_H

#include "ksp_stft.h"
#include "ksp_math.h"

typedef struct ksp_stft_Scratch {
    ksp_float_t                 *pWinInput;
                                ///< forward FFT only
} ksp_stft_Scratch_t;

typedef struct ksp_stft_State {
    ksp_float_t                 fftScale;
                                ///< Scaling for inverse FFT
    ksp_fft_Handle_t            fftHandle;
                                ///< Pointer to FFT instance
    ksp_float_t                 *pOverlapBuf;
                                ///< Output of overlap add
    ksp_uint16_t                windowSize;
                                /**< Number of samples for FFT before zero 
                                padding                                     */
    ksp_stft_Scratch_t          scratch;
                                ///< Scratch memory for the module
    ksp_stft_ControlParams_t    controlParams;
                                ///< Copy of control params
    ksp_stft_CreateParams_t     createParams;
                                ///< Copy of create params
    ksp_uint16_t                readyToRunFlag;
                                /**< Ensure calling reset function before 
                                process function                            */
} ksp_stft_State_t;

#endif // KSP_STFT_STATE_H
