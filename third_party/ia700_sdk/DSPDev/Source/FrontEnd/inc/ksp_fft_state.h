/************************************************************************//**
 * @file  ksp_fft_state.h
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
 * $DateTime: 2021/11/08 03:50:51 $
 * $Revision: #1 $
 * $Id: //AudEngr/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Knowles_IA700_SDK/DSPDev/Source/FrontEnd/inc/ksp_fft_state.h#1 $
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

#ifndef __KSP_FFT_STATE_HEADER__
#define __KSP_FFT_STATE_HEADER__

#include "ksp_fft.h"

typedef struct ksp_fft_State {
    ksp_int32_t fftSize;        // fftSize, must be a power of 2
    ksp_int32_t Log2N;          // Log2N = log2(fftSize), for convenient purpose.
    ksp_fft_input_t fftType;    // fft input type
    ksp_fft_direction_t fftDirection;   // fft or ifft
   // ksp_float_t *pTwiddle;	    // points into twiddle 'data', must be 16-byte aligned

    // local copies of parameters
    ksp_fft_CreateParams_t    createParams;
} ksp_fft_State_t;



#endif // __KSP_FFT_STATE_HEADER__
