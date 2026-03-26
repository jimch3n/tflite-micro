/************************************************************************//**
 * @file  ksp_frontend_state.h
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
 * $Id: //AudEngr/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Knowles_IA700_SDK/DSPDev/Source/FrontEnd/inc/ksp_frontend_state.h#2 $
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

#ifndef KSP_FRONTEND_STATE_H // Change to upper case and delete comment
#define KSP_FRONTEND_STATE_H // Change to upper case and delete comment

#include "ksp_frontend.h"

// Module intrinsic constant data declaration 
// ksp_frontend_Consts_t, and ksp_frontend_Consts_l_t,
// the version of it needed during static initialization,
// to avoid the creation of constructor text by the compiler.
// NOTE: DELETE IF YOUR MODULE DOES NOT REQUIRE CONST DATA
#define ksp_frontend_CONSTS_M(ksp_float_t, ksp_frontend_Consts) \
typedef struct ksp_frontend_Consts {                                 \
    ksp_float_t     c1;                                                   \
    ksp_float_t     c2;                                                   \
    ksp_int32_t     c3;                                                   \
} ksp_frontend_Consts ## _t; 
ksp_frontend_CONSTS_M(ksp_float_t, ksp_frontend_Consts)
ksp_frontend_CONSTS_M(ksp_float_literal_t, ksp_frontend_Consts_l)


// Module scratch - Delete if your module does not use scratch
typedef struct ksp_frontend_Scratch{
    ksp_float_t                     *pTdStftIo;
    ksp_float_t                     *pPowerSpec; //share with MicSpec
    ksp_float_vector_scaled_t       micSigVec;
    ksp_float_t *pLogMelSpec;
	ksp_float_t *pFeat;
	ksp_uint32_t *pMelBuf; // temp buffer for building coeffs 
} ksp_frontend_Scratch_t;

typedef struct ksp_frontend_State {
    // Module state buffers and variables
    ksp_complex_t                   **pMicSpecBuf;
    ksp_int16_t                     frameSize;
    ksp_int16_t                     fftSize;
    ksp_int16_t                     nBins;
    
    // submodule instances (if any)
    ksp_vp_front_end_Handle_t		hFe;
    ksp_filterbank_Handle_t         hFb;
	//ksp_float_t           *dct_matrix; // for coefficients

	ksp_uint16_t        *melFilterIdx;
	ksp_uint16_t        *melFilterLen;
	ksp_float_t         *melFilterPacked;


    // scratch
    ksp_frontend_Scratch_t         	scratch;
    
    // local copies of parameters
    ksp_frontend_CreateParams_t    	createParams;
    ksp_frontend_ControlParams_t    controlParams;
    
    // pointer to consts. Assign in create()
    const ksp_frontend_Consts      	*pConsts;
    
    // other items the module needs
    ksp_int16_t                   	readyToRunFlag;
                                        ///< Ensure successful reset() before process()

    ksp_frontend_ModuleData_t      	moduleData;
                                        ///< solely for ksp_frontend_get_data()
    
} ksp_frontend_State_t;

#endif // KSP_FRONTEND_STATE_H
