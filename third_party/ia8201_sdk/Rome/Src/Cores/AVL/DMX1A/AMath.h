/************************************************************************//**
 * @file    AVL/DMX1A/AMath.h
 *
 * @brief   AScalar Math function wrapper for fr32 on DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef DMX1A_AMATH_H
#define DMX1A_AMATH_H
// DMX1A
_AI AScalar sqrt(AScalar x) { return x.f_sqrt(); }
_AI AScalar sqrtf(AScalar x) { return x.f_sqrt(); }
_AI AScalar log10(AScalar x) { return  fpmul(log2_fr(x), AScalar::log10two().fr, 0); } //fpmul(log2_fr(fr), log10two().fr, 0); 
_AI AScalar log(AScalar x) { return fpmul(log2_fr(x), AScalar::ln2().fr, 0);}
_AI AScalar logf(AScalar x) { return fpmul(log2_fr(x), AScalar::ln2().fr, 0); }
_AI AScalar pow(AScalar x, AScalar y) { return x.f_pow(y) ; }
_AI AScalar powf(AScalar x, AScalar y) { return x.f_pow(y); }
_AI AScalar exp(AScalar x) { return x.f_exp(); }
_AI AScalar expf(AScalar x) { return x.f_exp();}
// sine cosine

_AI AScalar sin(AScalar x) { return x.sine_rads(); }
_AI AScalar cos(AScalar x) { return x.cosine_rads(); }

_AI AScalar sinf(AScalar x) { return x.sine_rads(); }
_AI AScalar cosf(AScalar x) { return x.cosine_rads(); }

_AI AScalar atan(AScalar y, AScalar x) {	return x.atan2_rads(y, x);}
// abs
_AI AScalar fabs(AScalar x) { return x.abs(); }
_AI AScalar fabsf(AScalar x) { return x.abs(); }
//floor
_AI AScalar floor(AScalar x) { return x.floor(); }
//ceil
_AI AScalar ceil(AScalar x) { return x.ceil(); }
// fmaf
_AI AScalar fmaf(AScalar x, AScalar y, AScalar z)
{
	return (x * y) + z;
}
#endif
