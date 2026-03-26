/************************************************************************//**
 * @file  ksp_filterbank_state.h
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
 * $DateTime: 2021/03/26 02:38:54 $
 * $Revision: #1 $
 * $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Packages/FrontEnd/ksp_frontend/generic/inc/ksp_filterbank_state.h#1 $
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

#ifndef KSP_FILTERBANK_STATE_H
#define KSP_FILTERBANK_STATE_H

#include "ksp_filterbank.h"

typedef struct ksp_filterbank_State {
    ksp_filterbank_CreateParams_t createParams;
    ksp_filterbank_ControlParams_t controlParams;
#ifndef REF_CODE
    ksp_int16_t     startIdx;
    ksp_int16_t     endIdx;
#endif
    // other items the module needs
    ksp_int32_t     nBins;
                    ///< Number of bins in the linear spectrum
    ksp_int32_t     *pLeftBank;
                    /**< Mapping of bin numbers from the linear spectrum to
                    the Mel spectrum for the left half of the triangular
                    filters                                                 */
    ksp_int32_t     *pRightBank;
                    /**< Mapping of bin numbers from the linear spectrum to
                    the Mel spectrum for the right half of the triangular
                    filters                                                 */
    ksp_float_t     *pLeftFilter;
                    /**< Filter  coefficients corresponding to the mapping 
                    for the left half of the triangular filters             */
    ksp_float_t     *pRightFilter;
                    /**< Filter  coefficients corresponding to the mapping
                    for the right half of the triangular filters            */

    ksp_uint16_t    readyToRunFlag;
                    ///< Ensure calling reset function before process function

    // moduleData solely for ksp_filterbank_get_data() -- items will be allocated
    ksp_filterbank_ModuleData_t moduleData;
    
} ksp_filterbank_State_t;

#endif // KSP_FILTERBANK_STATE_H
