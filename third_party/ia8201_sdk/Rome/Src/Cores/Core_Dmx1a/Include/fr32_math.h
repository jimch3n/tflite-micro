/************************************************************************//**
 * @file    fr32_math.h
 *
 * @brief   DMX1A fr32 version of math.h
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
    return max_fr(FR32_ZERO, fpadd(x, y, 2));
}

_AI fr32 fr32_expf(fr32 x)
{
    return pow2_fr(fpmul(x, FR32_LOG2_e, 0));
}

_AI fr32 fr32_logf(fr32 x)
{
    return fpmul(log2_fr(x), FR32_LOGe_TWO, 0);
}

_AI fr32 fr32_exp10f(fr32 x)
{
    return pow2_fr(fpmul(x, FR32_LOG2_TEN, 0));
}

_AI fr32 fr32_log10f(fr32 x)
{
    return fpmul(log2_fr(x), FR32_LOG10_TWO, 0);
}

_AI fr32 fr32_exp2f(fr32 x)
{
    return pow2_fr(x);
}

_AI fr32 fr32_log2f(fr32 x)
{
    return log2_fr(x);
}

_AI fr32 fr32_powf(fr32 x, fr32 y)
{
    vr128 z = vpermsi(vreplicate_fr(x), vreplicate_fr(y), 0, 4);
    xtbool flag;

    log2mul(z, 0, z, 0, z, 1, flag);
    cspow2(z, 0, z, 0, flag);
    {
        // Handle negative number to even power (optional):
        // vr128 tmp = vreplicate_fr(abs_fr(y));
        // unsigned odd;
        //
        // floorp_frac(odd, tmp, 0, tmp, 0, 0);
        // replicate_ar(tmp, 1, -(int) odd);
        // s_and(z, 0, z, 0, tmp, 0);
    }
    return get_VRQ0(z);
}

_AI fr32 fr32_tanf(fr32 x)
{
    fr32 turns = fpmul(x, seta_fr(14, 6, 0), 0);

    return fpmul(sine_fr(turns), inv_fr(cosine_fr(turns)), 0);
}

_AI fr32 fr32_sinf(fr32 x)
{
    return sine_fr(fpmul(x, seta_fr(14, 6, 0), 0));
}

_AI fr32 fr32_cosf(fr32 x)
{
    return cosine_fr(fpmul(x, seta_fr(14, 6, 0), 0));
}

_AI fr32 fr32_atan2f(fr32 y, fr32 x)
{
    vr128 z = vpermsi(vreplicate_fr(x), vreplicate_fr(y), 0, 4);
    xtbool4 flags;

    ratio(z, 0, z, 0, z, 1, flags);
    atanratio(z, 0, z, 0, flags);
    return fpmul(get_VRQ0(z), FR32_TWO_PI, 0);
}

_AI fr32 fr32_atanf(fr32 x)
{
    return fr32_atan2f(x, FR32_ONE);
}

_AI fr32 fr32_asinf(fr32 x)
{
    fr32 s = FR32_ONE;
    fr32 z;

    fpmac(s, x, x, 1);               // 1 - x^2
    z = fpmul(s, invsqrt_fr(s), 0);  // sqrt(1 - x^2)
    return fr32_atan2f(x, z);
}

_AI fr32 fr32_acosf(fr32 x)
{
    fr32 s = FR32_ONE;
    fr32 z;

    fpmac(s, x, x, 1);               // 1 - x^2
    z = fpmul(s, invsqrt_fr(s), 0);  // sqrt(1 - x^2)
    return fr32_atan2f(z, x);
}

_AI fr32 fr32_tanhf(fr32 x)
{
    fr32 tmp = fpmul(FR32_LOG2_e, x, 0);
    fr32 pexp = pow2_fr(tmp);            // exp(x)
    fr32 nexp = pow2_fr(neg_fr(tmp));    // exp(-x)

    return fpmul(fpadd(pexp, nexp, 2), inv_fr(fpadd(pexp, nexp, 0)), 0);
}

_AI fr32 fr32_sinhf(fr32 x)
{
    fr32 tmp = fpmul(FR32_LOG2_e, x, 0);
    fr32 pexp = pow2_fr(tmp);            // exp(x)
    fr32 nexp = pow2_fr(neg_fr(tmp));    // exp(-x)

    return exp_adj_fr(fpadd(pexp, nexp, 2), 0x7f);
}

_AI fr32 fr32_coshf(fr32 x)
{
    fr32 tmp = fpmul(FR32_LOG2_e, x, 0);
    fr32 pexp = pow2_fr(tmp);            // exp(x)
    fr32 nexp = pow2_fr(neg_fr(tmp));    // exp(-x)

    return exp_adj_fr(fpadd(pexp, nexp, 0), 0x7f);
}

_AI fr32 fr32_sqrtf(fr32 x)
{
    fr32 y = invsqrt_fr(x);

    // One iteration of Newton's method
    fr32 tmp = seta_fr(28, 0, 0);
    fpmac(tmp, y, fpmul(x, y, 0), 1);
    y = fpmul(exp_adji_fr(y, 0x7f), tmp, 0);

    return fpmul(x, y, 0);
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
    vr128 vtrunc_x = vreplicate_fr(trunc_x);
    vr128 z = vadds(vtrunc_x, vseta_vr(17, 0, 0), 0);
    
    sel(z, 0, vtrunc_x, 0, z, 0, ge_fr(x, FR32_ZERO));
    sel(z, 0, vtrunc_x, 0, z, 0, eq_fr(x, trunc_x));
    return get_VRQ0(z);
}

_AI fr32 fr32_ceilf(fr32 x)
{
    fr32 trunc_x = fr32_truncf(x);
    vr128 vtrunc_x = vreplicate_fr(trunc_x);
    vr128 z = vadds(vtrunc_x, vseta_vr(1, 0, 0), 0);
    
    sel(z, 0, vtrunc_x, 0, z, 0, le_fr(x, FR32_ZERO));
    sel(z, 0, vtrunc_x, 0, z, 0, eq_fr(x, trunc_x));
    return get_VRQ0(z);
}

_AI fr32 fr32_modff(fr32 x, fr32 *ipart)
{
    fr32 trunc_x = fr32_truncf(x);

    *ipart = trunc_x;
    return fpadd(x, trunc_x, 2);
}

_AI fr32 fr32_fmodf(fr32 x, fr32 y)
{
    fr32 inv_y = inv_fr(y);
    fr32 tmp = FR32_TWO;

    // One iteration of Newton's method
    fpmac(tmp, inv_y, y, 1);
    inv_y = fpmul(inv_y, tmp, 0);

    tmp = fpmul(x, inv_y, 0);
    return fpmul(y, fpadd(tmp, fr32_truncf(tmp), 2), 0);
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
    vr128 z  = vseta_vr(0, 0, 0);

    if (ne_fr(x, FR32_ZERO))
        exp -= 31;
    *exp_out = exp;

    replicate_ar(z, 1, mant | 0x2000000);
    replicate_ar(z, 2, ax);
    convert_32I_to_32F_x1(z, 5, 0);
    s_copy(z, 0, z, 0, z, 1);
    move_vr_eqz(z, 0, z, 2, z, 1);
    return get_VRQ0(z);
}

#endif



/* End of File */

