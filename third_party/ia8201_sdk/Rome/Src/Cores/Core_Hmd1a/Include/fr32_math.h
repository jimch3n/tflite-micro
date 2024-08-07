/************************************************************************//**
 * @file    fr32_math.h
 *
 * @brief   HMD1A fr32 version of math.h
 *          These are inline approximations to the functions in <math.h>
 *          Most of these functions are limited to 18-bit precision
 *
 * $DateTime: 2021/03/09 09:01:05 $
 * $Revision: #1 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef FR32_MATH_H
#define FR32_MATH_H

#if defined(__XTENSA__)
 #include <xtensa/tie/xt_misc.h>
#endif

#include "fr32_utils.h"

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
    fr32 z;

    log2mul(z, x, y, flag);
    z = cspow2(z, flag);
    {
        // Handle negative number to even power (optional):
        // vr64 tmp = vreplicate_fr(abs_fr(y));
        // unsigned odd;
        //
        // floorp_frac(odd, tmp, 0, tmp, 0, 0);
        // z = s_and(z, move_fr_ar(-(int) odd));
    }
    return z;
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
    fr32 pexp = pow2(get_VRL(tmp));    // exp(x)
    fr32 nexp = pow2(get_VRH(tmp));    // exp(-x)

    return exp_adj_fr(fadds(pexp, nexp, 2), 0x7f);
}

_AI fr32 fr32_coshf(fr32 x)
{
    vr64 tmp = vmulf(vseta_vr(9, 0), x, 2);
    fr32 pexp = pow2(get_VRL(tmp));    // exp(x)
    fr32 nexp = pow2(get_VRH(tmp));    // exp(-x)

    return exp_adj_fr(fadds(pexp, nexp, 0), 0x7f);
}

_AI fr32 fr32_sqrtf(fr32 x)
{
    fr32 y = invsqrt(x);

    // One iteration of Newton's method
    y = fmuls(exp_adji_fr(y, 0x7f),
              fmacs(seta_fr(28, 0), y, fmuls(x, y, 0), 1), 0);

    return fmuls(x, y, 0);
}

_AI fr32 fr32_truncf(fr32 x)
{
#ifdef truncate_fr
    return truncate_fr(x);
#else
    int ax = move_ar_fr(x);
    int exp = (ax >> 25) & 0x3f;
    int frac_bits = XT_MAX(0, XT_MIN(26, 57 - exp));
    int mask_tmp = ((frac_bits - 26) >> 31) << frac_bits;

    return move_fr_ar(ax & mask_tmp);
#endif
}

_AI fr32 fr32_floorf(fr32 x)
{
    fr32 trunc_x = fr32_truncf(x);
    fr32 z = fadds(trunc_x, FR32_MINUS_ONE, 0);

    move_fr_gez(z, trunc_x, x);
    move_fr_arnz(z, trunc_x, eq_fr(x, trunc_x));
    return z;
}

_AI fr32 fr32_ceilf(fr32 x)
{
    fr32 trunc_x = fr32_truncf(x);
    fr32 z = fadds(trunc_x, FR32_ONE, 0);

    move_fr_lez(z, trunc_x, x);
    move_fr_arnz(z, trunc_x, eq_fr(x, trunc_x));
    return z;
}

_AI fr32 fr32_modff(fr32 x, fr32 *ipart)
{
    fr32 trunc_x = fr32_truncf(x);

    *ipart = trunc_x;
    return fadds(x, trunc_x, 2);
}

_AI fr32 fr32_fmodf(fr32 x, fr32 y)
{
    fr32 inv_y = inv(y);
    fr32 tmp;

    // One iteration of Newton's method
    inv_y = fmuls(inv_y, fmacs(FR32_TWO, inv_y, y, 1), 0);

    tmp = fmuls(x, inv_y, 0);
    return fmuls(y, fadds(tmp, fr32_truncf(tmp), 2), 0);
}

_AI fr32 fr32_ldexpf(fr32 x, int exp)
{
    return exp_adj_fr(x, XT_CLAMPS(exp << 1, 7) >> 1);
}

_AI fr32 fr32_frexpf(fr32 x, int *exp_out)
{
    int ax   = move_ar_fr(x);
    int mant = ax & 0x1ffffff;
    int exp  = (ax >> 25) & 0x3f;
    vr64 tmp=vseta_vr(0,0);
    fr32 z;

    if (ne_fr(x, FR32_ZERO))
        exp -= 31;
    *exp_out = exp;

    replicate_ar(tmp, 1, mant | 0x2000000);
    convert_32I_to_32F_x1(tmp, 5, 0);
    z = s_copy(get_VRL(tmp), x);
    move_fr_eqz(z, FR32_ZERO, x);
    return z;
}

#endif



/* End of File */

