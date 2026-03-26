/************************************************************************//**
 * File: hemilite_fr32_ops.h
 *
 * Description: fr32 operators on HemiLite
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

#ifndef HEMILITE_FR32_OPS_H
#define HEMILITE_FR32_OPS_H

#ifndef __XTENSA__
 #error hemilite_fr32_ops.h requires xcc compiler.
#endif

#include "hemilite_fr32_utils.h"

_AI fr32 __xt_operator_NEGATE(fr32 x)
{
    return neg_fr(x);
}

_AI fr32 __xt_operator_PLUS(fr32 x, fr32 y)
{
    return fadds(x, y, 0);
}

_AI fr32 __xt_operator_MINUS(fr32 x, fr32 y)
{
    return fadds(x, y, 2);
}

_AI fr32 __xt_operator_MULT(fr32 x, fr32 y)
{
    return fmuls(x, y, 0);
}

_AI fr32 __xt_operator_TRUNC_DIV(fr32 x, fr32 y)
{
    fr32 inv_y = inv(y);

    // One iteration of Newton's method
    inv_y = fmuls(inv_y, fmacs(FR32_TWO, inv_y, y, 1), 0);

    return fmuls(x, inv_y, 0);
}

_AI fr32 __xt_operator_LSHIFT(fr32 x, unsigned y)
{
    return exp_adj_fr(x, y);
}

_AI fr32 __xt_operator_RSHIFT(fr32 x, unsigned y)
{
    return exp_adj_fr(x, -y);
}

_AI unsigned __xt_operator_LT(fr32 x, fr32 y)
{
    return lt_fr(x, y);
}

_AI unsigned __xt_operator_LE(fr32 x, fr32 y)
{
    return le_fr(x, y);
}

_AI unsigned __xt_operator_GT(fr32 x, fr32 y)
{
    return gt_fr(x, y);
}

_AI unsigned __xt_operator_GE(fr32 x, fr32 y)
{
    return ge_fr(x, y);
}

_AI unsigned __xt_operator_EQ(fr32 x, fr32 y)
{
    return eq_fr(x, y);
}

_AI unsigned __xt_operator_NE(fr32 x, fr32 y)
{
    return ne_fr(x, y);
}

#endif
