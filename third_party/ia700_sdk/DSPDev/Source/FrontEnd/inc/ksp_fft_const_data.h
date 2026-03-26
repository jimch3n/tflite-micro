/************************************************************************//**
 * @file  ksp_fft_const_data.h
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
 * $Id: //AudEngr/AlgoSW/Product/shapiro-sdk-support-TFLu-dev/SDK/Knowles_IA700_SDK/DSPDev/Source/FrontEnd/inc/ksp_fft_const_data.h#1 $
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

#ifndef __KSP_FFT_CONST_DATA_HEADER__
#define __KSP_FFT_CONST_DATA_HEADER__

#ifdef USE_DELTAMAX_FFT_OPT
VAR_ALIGN_8 static  const unsigned int sin_cos_forward[MAX_REAL_FFT_LOG2_SIZE_LUT * 2] = {
    0xc0000000, 0x00000000, //1
    0x00000000, 0xc0000000, //2
    0x3ED413CD, 0xBED413CD, //3
    0x3FB20D7A, 0xBd0fbc55, //4
    0x3FEC52FA, 0xBB1F1708, //5
    0x3FFB11B4, 0xB922F4D8, //6
    0x3FFEC43C, 0xB723ECBE, //7
    0x3FFFB10C, 0xB5242ABF, //8
    0x3FFFEC43, 0xB3243A40, //9
    0x3FFFFB11, 0xB1243E20, //10
    0x3FFFFEC4, 0xAF243F18, //11
    0x3FFFFFB1, 0xAD243F56, //12
    0x3FFFFFEC, 0xAB243F65, //13
    0x3FFFFFFB, 0xA9243F69, //14
    0x3FFFFFFF, 0xA7243F6A, //15
    0x40000000, 0xA5243F6A  //16
};
#endif

#endif // __KSP_FFT_CONST_DATA_HEADER__
