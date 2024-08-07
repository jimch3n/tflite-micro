/************************************************************************//**
 * @file fr32_xcc_ops.h
 *
 * @brief HMD1A fr32 operator overloads
 *
 * Operator overloads for the fr32 type
 * These require the xcc compiler
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef FR32_XCC_OPS_H
#define FR32_XCC_OPS_H

#ifndef __XCC__
 #error fr32_xcc_ops.h requires xcc compiler.
#endif

#include <xtensa/tie/xt_misc.h>

#include "fr32_utils.h"

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

_AI fr32 __xt_operator_LSHIFT(fr32 x, int y)
{
    return exp_adj_fr(x, XT_CLAMPS(y << 1, 7) >> 1);
}

_AI fr32 __xt_operator_RSHIFT(fr32 x, int y)
{
    return exp_adj_fr(x, XT_CLAMPS((-y) << 1, 7) >> 1);
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
