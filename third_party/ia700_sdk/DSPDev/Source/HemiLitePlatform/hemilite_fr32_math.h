/************************************************************************//**
 * File: hemilite_fr32_math.h
 *
 * Description: Approximations to C Library math.h functions
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

#ifndef HEMILITE_FR32_MATH_H
#define HEMILITE_FR32_MATH_H

#ifdef __XTENSA__
#include <xtensa/tie/xt_misc.h>
#endif

#include "hemilite_fr32_utils.h"

_AI fr32 fr32_fabsf(fr32 x)
{
    return abs_fr(x);
}

_AI fr32 fr32_fminf(fr32 x, fr32 y)
{
    return min_fr(x, y);
}

_AI fr32 fr32_fmaxf(fr32 x, fr32 y)
{
    return max_fr(x, y);
}

_AI fr32 fr32_fdimf(fr32 x, fr32 y)
{
    return max_fr(FR32_ZERO, fadds(x, y, 2));
}

_AI fr32 fr32_expf(fr32 x)
{
    return pow2(fmuls(x, FR32_LOG2_e, 0));
}

_AI fr32 fr32_logf(fr32 x)
{
    return fmuls(log2(x), FR32_LOGe_TWO, 0);
}

_AI fr32 fr32_exp10f(fr32 x)
{
    return pow2(fmuls(x, FR32_LOG2_TEN, 0));
}

_AI fr32 fr32_log10f(fr32 x)
{
    return fmuls(log2(x), FR32_LOG10_TWO, 0);
}

_AI fr32 fr32_exp2f(fr32 x)
{
    return pow2(x);
}

_AI fr32 fr32_log2f(fr32 x)
{
    return log2(x);
}

_AI fr32 fr32_powf(fr32 x, fr32 y)
{
    atbool flag;
    fr32 tmp;

    log2mul(tmp, x, y, flag);
    return cspow2(tmp, flag);
}

_AI fr32 fr32_tanf(fr32 x)
{
    fr32 turns = fmuls(x, seta_fr(14, 6), 0);

    return fmuls(sine(turns), inv(cosine(turns)), 0);
}

_AI fr32 fr32_sinf(fr32 x)
{
    return sine(fmuls(x, seta_fr(14, 6), 0));
}

_AI fr32 fr32_cosf(fr32 x)
{
    return cosine(fmuls(x, seta_fr(14, 6), 0));
}

_AI fr32 fr32_atan2f(fr32 y, fr32 x)
{
    atbool flags;
    fr32 tmp;

    ratio(tmp, x, y, flags);
    return fmuls(atanratio(tmp, flags), FR32_TWO_PI, 0);
}

_AI fr32 fr32_atanf(fr32 x)
{
    return fr32_atan2f(x, FR32_ONE);
}

_AI fr32 fr32_asinf(fr32 x)
{
    fr32 s = fmacs(FR32_ONE, x, x, 1); // 1 - x^2
    fr32 z = fmuls(s, invsqrt(s), 0);  // sqrt(1 - x^2)

    return fr32_atan2f(x, z);
}

_AI fr32 fr32_acosf(fr32 x)
{
    fr32 s = fmacs(FR32_ONE, x, x, 1); // 1 - x^2
    fr32 z = fmuls(s, invsqrt(s), 0);  // sqrt(1 - x^2)

    return fr32_atan2f(z, x);
}

_AI fr32 fr32_tanhf(fr32 x)
{
    vr64 tmp = vmulf(vseta_vr(9, 0), x, 2);
    fr32 pexp = pow2(get_VRL(tmp));    // exp(x)
    fr32 nexp = pow2(get_VRH(tmp));    // exp(-x)

    return fmuls(fadds(pexp, nexp, 2), inv(fadds(pexp, nexp, 0)), 0);
}

_AI fr32 fr32_sinhf(fr32 x)
{
    vr64 tmp = vmulf(vseta_vr(9, 0), x, 2);
    vr64 exps = vr64_pair(pow2(get_VRH(tmp)), pow2(get_VRL(tmp)));

    return get_VRL(vadd_perm(exps, exps, 15, 12, 2, 1));
}

_AI fr32 fr32_coshf(fr32 x)
{
    vr64 tmp = vmulf(vseta_vr(9, 0), x, 2);
    vr64 exps = vr64_pair(pow2(get_VRH(tmp)), pow2(get_VRL(tmp)));

    return get_VRL(vadd_perm(exps, exps, 15, 12, 0, 1));
}

_AI fr32 fr32_sqrtf(fr32 x)
{
    fr32 y = invsqrt(x);

    // One iteration of Newton's method (optional)
    // fr32 half_x = exp_adji_fr(x, 0x7f);
    // y = fmuls(y, fmacs(seta_fr(28, 7), y, fmuls(y, half_x, 0), 1), 0);
    return fmuls(x, y, 0);
}

_AI fr32 fr32_truncf(fr32 x)
{
    int ax = move_ar_fr(x);
    int exp = (ax >> 25) & 0x3f;
    int frac_bits = XT_MAX(0, XT_MIN(26, 57 - exp));
    int mask_bit = ((frac_bits - 26) >> 31) << frac_bits;

    return move_fr_ar(ax & mask_bit);
}

_AI fr32 fr32_floorf(fr32 x)
{
    fr32 trunc_x = fr32_truncf(x);
    fr32 tmp = fadds(trunc_x, FR32_ONE, 2);

    move_fr_gez(tmp, trunc_x, x);
    return sel_ar(tmp, trunc_x, ne_fr(x, trunc_x));
}

_AI fr32 fr32_ceilf(fr32 x)
{
    fr32 trunc_x = fr32_truncf(x);
    fr32 tmp = fadds(trunc_x, FR32_ONE, 0);

    move_fr_lez(tmp, trunc_x, x);
    return sel_ar(tmp, trunc_x, ne_fr(x, trunc_x));
}

_AI fr32 fr32_modff(fr32 x, fr32 *ipart)
{
    fr32 trunc_x = fr32_truncf(x);

    *ipart = trunc_x;
    return fadds(x, trunc_x, 2);
}

_AI fr32 fr32_fmodf(fr32 x, fr32 y)
{
    fr32 tmp = inv(y);

    // One iteration of Newton's method
    tmp = fmuls(tmp, fmacs(FR32_TWO, tmp, y, 1), 0);
    tmp = fmuls(x, tmp, 0);
    return fmuls(y, fadds(tmp, fr32_truncf(tmp), 2), 0);
}

_AI fr32 fr32_ldexpf(fr32 x, int exp)
{
    return exp_adj_fr(x, XT_CLAMPS(exp << 1, 7) >> 1);
}

_AI fr32 fr32_frexpf(fr32 x, int *exp)
{
    int ax = move_ar_fr(x);
    int mant = 0x2000000 | (ax & 0x1ffffff);
    vr64 tmp;

    *exp = ((ax >> 25) & 0x3f) - 31;
    move32_vr_ar(tmp, 0, mant);
    convert_32I_to_32F_x1(tmp, 5, 0);
    return sel_ar(neg_fr(get_VRL(tmp)), get_VRL(tmp), ax >> 31);
}

#endif
