/************************************************************************//**
 * @file  ksp_vp_front_end_state.h
 *
 * @brief Maintains the internal state of VP Front End
 *
 * Maintains the overlap buffer and allocates memory for buffers
 * that may be needed by the module
 *
 * @sa
 * Put references to (names of) other relevant files here
 *
 * @info
 * $Author: rmatcha $
 * $DateTime: 2021/03/26 02:38:54 $
 * $Revision: #1 $
 * $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Packages/FrontEnd/ksp_frontend/generic/inc/ksp_vp_front_end_state.h#1 $
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

#ifndef ksp_vp_front_end_STATE_H 
#define ksp_vp_front_end_STATE_H 

#include "ksp_vp_front_end.h"
#include "ksp_stft.h"

// Data structure for circular buffered delay line - ALWAYS READ FIRST
typedef struct {
    ksp_float_t             **pBuf;
    ///< Overlap management buffer for input
    ksp_int32_t             nChans;
    ///< Number of channels in the input
    ksp_int32_t             nOverlapSamples;
    ///< length of delay line (number of samples)
    ksp_int32_t             writeIdx;
    ///< write index into buffered delay line
} ksp_vp_front_end_BufferedDelayLine_t;

typedef struct ksp_vp_front_end_State {
    ksp_vp_front_end_CreateParams_t         createParams;
    ksp_vp_front_end_ControlParams_t        controlParams;
    
    ksp_vp_front_end_BufferedDelayLine_t    sigOvlpBuffer;
                                            /***< Overlap buf book-keeping for multi-mic
                                            input                                       */
    ksp_float_t                             *pStftWindow;
                                            ///< Window for forward STFT
    ksp_int32_t                             fftSize;
                                            /// Size of FFT
    ksp_int32_t                             nOverlapSamples;
                                            ///< Number of samples of overlap
    ksp_int32_t                             frameSize;
                                            ///< frameSize in samples
    ksp_int32_t                             windowSize;
    ksp_int16_t                             readyToRunFlag;
                                            ///< Ensure successful reset() before process()
    // Included submodules

    ksp_stft_Handle_t                       hStftFwd;  
                                            ///< Forward STFT instance                              
    
} ksp_vp_front_end_State_t;

#endif // ksp_vp_front_end_STATE_H
