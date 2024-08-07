/************************************************************************//**
 * @file    fr32_utils.h
 *
 * @brief   HMD1A fr32 utilities
 *          Miscellaneous fr32 constants and conversion functions
 *
 * $DateTime: 2021/03/09 09:01:05 $
 * $Revision: #1 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef FR32_UTILS_H
#define FR32_UTILS_H

#include <stdint.h>

#if defined(__XTENSA__)
 #include "TIE_include.h"
#else
 #include "cstubs.h"
#endif

// _AI (Always Inline) is used to encourage inlining
#ifndef _AI
 #ifdef __cplusplus
  #if defined(__GNUC__)
   #define _AI __attribute__((always_inline)) inline
  #elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
   #define _AI __forceinline
  #else
   #define _AI inline
  #endif
 #else
  #if defined(__GNUC__)
   #define _AI __attribute__((always_inline)) static inline
  #elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
   #define _AI static __forceinline
  #else
   #define _AI static inline
  #endif
 #endif
#endif

/* fr32 constants */

#define FR32_MINUS_TWO  seta_fr(17, 1)
#define FR32_MINUS_ONE  seta_fr(17, 0)
#define FR32_ZERO       seta_fr(0,  0)
#define FR32_ONE        seta_fr(1,  0)
#define FR32_TWO        seta_fr(2,  0)
#define FR32_THREE      seta_fr(28, 0)
#define FR32_FOUR       seta_fr(2,  1)
#define FR32_FIVE       seta_fr(30, 7)
#define FR32_SIX        seta_fr(28, 1)
#define FR32_EIGHT      seta_fr(2,  2)
#define FR32_TEN        seta_fr(30, 0)
#define FR32_TWELVE     seta_fr(28, 2)
#define FR32_TWENTY     seta_fr(30, 1)

#define FR32_HALF       seta_fr(3,  0)
#define FR32_SQRT2      seta_fr(15, 0)
#define FR32_HALF_SQRT2 seta_fr(16, 0)
#define FR32_PI         seta_fr(5,  0)
#define FR32_TWO_PI     seta_fr(11, 0)
#define FR32_HALF_PI    seta_fr(5,  7)
#define FR32_e          seta_fr(6,  0)
#define FR32_HALF_e     seta_fr(6,  7)
#define FR32_LOG2_TEN   seta_fr(7,  0)
#define FR32_LOG10_TWO  seta_fr(8,  0)
#define FR32_LOG2_e     seta_fr(9,  0)
#define FR32_LOGe_TWO   seta_fr(10, 0)
#define FR32_MAX_AFLOAT seta_fr(1,  3)
#define FR32_MIN_AFLOAT seta_fr(17, 3)

/* Conversion functions */

_AI fr32 float_to_afloat(float x)
{
    vr64 tmp=vseta_vr(0,0);

    load32x1_vr_idxI(tmp, (uint32_t*) &x, 0, 0);
    convert_IEEE_float_to_32F_x2(tmp);
    return get_VRL(tmp);
}

_AI float afloat_to_float(fr32 x)
{
    vr64 tmp = vreplicate_fr(x);
    float val;

    convert_32F_to_IEEE_float_x2(tmp);
    fr32_storei(get_VRL(tmp), (fr32*) &val, 0);
    return val;
}

_AI fr32 double_to_afloat(double x)
{
    vr64 tmp = vr64_loadi((vr64*) &x, 0);

    convert_IEEE_double_to_64F(tmp);
    return convert_64F_to_32F(tmp);
}

_AI double afloat_to_double(fr32 x)
{
    vr64 tmp = convert_32F_to_64F(x);
    double val;

    vr64_storei(tmp, (vr64*) &val, 0);
    return val;
}

_AI fr32 int_to_afloat(int x)
{
    vr64 tmp=vseta_vr(0,0);

    move32_vr_ar(tmp, 0, x);
    convert_32I_to_32F_x1(tmp, 31, 0);
    return get_VRL(tmp);
}

_AI int afloat_to_int(fr32 x)
{
    vr64 tmp = vreplicate_fr(x);

    convert_32F_to_32I_x1(tmp, 31, 1, 0);
    return move32_ar_vr(tmp, 0);
}

_AI fr32 Q15_to_afloat(int16_t x)
{
    vr64 tmp=vseta_vr(0,0);

    move32_vr_ar(tmp, 0, (int32_t) x);
    convert_32I_to_32F_x1(tmp, 16, 0);
    return get_VRL(tmp);
}

_AI int16_t afloat_to_Q15(fr32 x)
{
    vr64 tmp = vreplicate_fr(x);

    convert_32F_to_16I_x1(tmp, 0, 1, 0);
    return move32_ar_vr(tmp, 0) >> 16;
}

_AI fr32 Q31_to_afloat(int32_t x)
{
    vr64 tmp=vseta_vr(0,0);

    move32_vr_ar(tmp, 0, x);
    convert_32I_to_32F_x1(tmp, 0, 0);
    return get_VRL(tmp);
}

_AI int32_t afloat_to_Q31(fr32 x)
{
    vr64 tmp = vreplicate_fr(x);

    convert_32F_to_32I_x1(tmp, 0, 1, 0);
    return move32_ar_vr(tmp, 0);
}

_AI fr32 fr32_to_dB20(fr32 x)     // 20 * log10(x)
{
    atbool tmp;

    log2mul(x, x, seta_fr(29, 0), tmp);
    return x;
}

_AI fr32 fr32_from_dB20(fr32 x)   // 10^(x/20)
{
    return pow2(fmuls(x, seta_fr(24, 7), 0));
}

_AI fr32 fr32_to_dB10(fr32 x)   // 10 * log10(x)
{
    atbool tmp;

    log2mul(x, x, seta_fr(29, 7), tmp);
    return x;
}

_AI fr32 fr32_from_dB10(fr32 x) // 10^(x/10)
{
    return pow2(fmuls(x, seta_fr(24, 0), 0));
}

#endif



/* End of File */

