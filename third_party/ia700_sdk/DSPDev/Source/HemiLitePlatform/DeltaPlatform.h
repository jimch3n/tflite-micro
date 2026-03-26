/************************************************************************//**
 * File: DeltaPlatform.h
 *
 * Description: HemiLite platform definitions
 *
 * Copyright 2018 Knowles Corporation. All rights reserved.
 *
 * All information, including software, contained herein is and remains
 * the property of Knowles Corporation. The intellectual and technical 
 * concepts contained herein are proprietary to Knowles Corporation
 * and may be covered by U.S. and foreign patents, patents in process,
 * and/or are protected by trade secret and/or copyright law. 
 * This information may only be used in accordance with the applicable
 * Knowles SDK License. Dissemination of this information or distribution
 * of this material is strictly forbidden unless in accordance with the 
 * applicable Knowles SDK License.   
 * 
 *
 * KNOWLES SOURCE CODE IS STRICTLY PROVIDED "AS IS" WITHOUT ANY WARRANTY
 * WHATSOEVER, AND KNOWLES EXPRESSLY DISCLAIMS ALL WARRANTIES,
 * EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE OR NON-INFRINGEMENT OF THIRD PARTY RIGHTS. KNOWLES
 * SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF
 * USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 * IN CERTAIN STATES, THE LAW MAY NOT ALLOW KNOWLES TO DISCLAIM OR EXCLUDE
 * WARRANTIES OR DISCLAIM DAMAGES, SO THE ABOVE DISCLAIMERS MAY NOT APPLY.
 * IN SUCH EVENT, KNOWLES' AGGREGATE LIABILITY SHALL NOT EXCEED 
 * FIFTY DOLLARS ($50.00).
 *
 ****************************************************************************/
#ifndef _FILE_DELTA_PLATFORM_H_
#define _FILE_DELTA_PLATFORM_H_

#include "TIE_defs.h"

#ifdef __XTENSA__
#include "TIE_include.h"
#include <xtensa/tie/xt_misc.h>
#else
#include "cstubs.h"
#endif

#include "DeltaTypes.h"

#ifdef _MSC_VER
#define VAR_ALIGN_4 __declspec(align(4)) 
#define VAR_ALIGN_8 __declspec(align(8)) 
#define VAR_ALIGN_16 __declspec(align(16)) 
#else
#define VAR_ALIGN_4 __attribute__ ( (aligned(4)) )
#define VAR_ALIGN_8 __attribute__ ( (aligned(8)) )
#define VAR_ALIGN_16 __attribute__ ( (aligned(16)) )
#endif


#endif  //  #ifndef _FILE_DELTA_PLATFORM_H_
