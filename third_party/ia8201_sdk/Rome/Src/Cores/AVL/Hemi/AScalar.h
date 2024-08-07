/************************************************************************//**
 * @file    AVL/Hemi/AScalar.h
 *
 * @brief   AScalar wrapper for fr32 on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ASCALAR_H
#define ASCALAR_H

#include <stdint.h>

#ifdef __XTENSA__
 #include "TIE_include.h"
#else 
 #include "cstubs.h"
#endif

#include "TIE_defs.h"
#include "AFloatLiteral.h"

#define RAW_LITERAL(D) AFLOAT_LITERAL(D)

#define CONST_ASCALAR(D) AScalar(AScalar::Raw(AFLOAT_LITERAL(D)))

// AVL_ALWAYS_INLINE (aka _AI) is used to encourage inlining:

#if defined(__GNUC__)
 #define AVL_ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
 #define AVL_ALWAYS_INLINE __forceinline
#else
 #define AVL_ALWAYS_INLINE inline
#endif

#define _AI AVL_ALWAYS_INLINE

#ifdef  AVL_DEBUG
 #define AVL_ASSERT(A) do { \
    if(!(A)) printf("%s:%d: Assertion failed: %s\n", __FILE__, __LINE__, #A); \
    } while(0)
#else
 #define AVL_ASSERT(A)
#endif

////////////////////////////////////////////////////////////////////////////////
//
// This example fills an array of AScalars with the first ten natural numbers
// and computes the sum of the array:
//
//    AScalar array[10];
//    PScalar ptr(array);
//
//    for (int i = 0; i < 10; i++)
//        ptr[i] = AScalar(i + 1, 0);
//
//    AScalar sum = 0;
//    for (int i = 0; i < 10; i++)
//        sum += ptr[i];
//
//    printf("%f\n", sum.to_double());
//
////////////////////////////////////////////////////////////////////////////////

struct AScalar
{
    fr32 fr;

    _AI AScalar() {}
    _AI AScalar(const AScalar& s) : fr(s.fr) {}
    _AI AScalar(const fr32& f)    : fr(f) {}

    _AI operator fr32() const {return fr;}

    _AI AScalar(int32_t i, uint32_t fractional_bits = 0) {
        vr64 z=vseta_vr(0,0);
        move32_vr_ar(z, VRQ0, i);
        convert_32I_to_32F_x1(z, 31 - fractional_bits, VRQ0);
        fr = get_VRL(z);
    }
    // float16 -> afloat
    _AI AScalar(int16_t i16) {
        vr64 z = vseta_vr(0,  0);
        int i32 = (int)i16 << 16;
        move32_vr_ar(z, VRQ0, i32);
        convert_16F_to_32F_x1(z, FLT16_SIGN, FLT16_EXP, FLT16_BIAS, VRQ0);
        fr = get_VRL(z);
    }
    _AI AScalar(uint32_t i, uint32_t fractional_bits) {
        vr64 z=vseta_vr(0,0);
        vr64 lsb=z;
        move32_vr_ar(z, VRQ0, i >> 1);                          // i/2
        move32_vr_ar(lsb, VRQ0, i & 1);                         // i&1
        convert_32I_to_32F_x1(z, 31 - fractional_bits, VRQ0);   // (afloat)(i/2)
        convert_32I_to_32F_x1(lsb, 31 - fractional_bits, VRQ0); // (afloat)(i&1)
        exp_adji(z, VRQ0, z, VRQ0, 1);                          // 2*(afloat)(i/2)
        fr = fadds(get_VRL(z), get_VRL(lsb), 0);                // 2*(afloat)(i/2)+(afloat)(i&1)
    }

    // AScalar::AScalar(double) loses 2 bits of precision because
    // IEEE single float has a 23(+1) bit mantissa but AFloat has 25(+1).
    // If full precision is required use CONST_ASCALAR() for a compile-time constant
    // or use the AScalar::AScalar(ADouble&) constructor for runtime conversion.

    _AI AScalar(double d) {*this = AScalar((float) d);}

   // _AI AScalar(const struct ADouble& d);

    _AI AScalar(float f) {
        vr64 z=vseta_vr(0,0);
        move32_vr_ar(z, 0, *(int*) &f);
        convert_IEEE_float_to_32F_x2(z);
        fr = get_VRL(z);
    }

private:
    // The uint32_t constructor is private to avoid accidentally converting a raw
    // literal. If the argument is a compile-time constant use CONST_ASCALAR(),
    // otherwise convert it to an int32_t or use the two-argument constructor.

    _AI AScalar(uint32_t i) : fr(AScalar(i, 0).fr) {}
public:

    // AScalar::Raw is used by CONST_ASCALAR()
    struct Raw {
        uint32_t f;
        _AI Raw(uint32_t raw) : f(raw) {}
    };
    _AI AScalar(const Raw& s) : fr(s.f) {}

    _AI int to_int(uint32_t fractional_bits = 0) const {
        vr64 v=vseta_vr(0,0);
        set_VRL(v, fr);
        convert_32F_to_32I_x1(v, 31 - fractional_bits, 1, VRQ0);
        return move32_ar_vr(v, VRQ0);
    }

    _AI int floor() const {
        vr64 v = vmax(vreplicate_fr(fr),
                      vexp_adji(vseta_vr(17, 0), 31));
        convert_32F_to_32I_x1(v, 31, 0, VRQ0);
        int trunc = move32_ar_vr(v, VRQ0);
        convert_32I_to_32F_x1(v, 31, VRQ0);
        uint32_t decrement = lt_fr(fr, seta_fr(0, 0)) & ne(v, VRQ0, v, VRQ1);
        return trunc - decrement;
    }

    _AI int ceil() const {
        vr64 v = vreplicate_fr(fr);
        convert_32F_to_32I_x1(v, 31, 0, VRQ0);
        int trunc = move32_ar_vr(v, VRQ0);
        convert_32I_to_32F_x1(v, 31, VRQ0);
        uint32_t increment = gt_fr(fr, seta_fr(0, 0)) & ne(v, VRQ0, v, VRQ1);
        int ceiling = trunc + increment;
        return ceiling - (increment & (ceiling >> 31));
    }

    _AI struct AComplex     operator* (const struct AComplex& x)     const;
    _AI struct AQuaternion  operator* (const struct AQuaternion& x)  const;
    _AI struct AQuad        operator* (const struct AQuad& x)        const;
    _AI struct ATriple      operator* (const struct ATriple& x)      const;
    _AI struct APair        operator* (const struct APair& x)        const;
    _AI struct AComplexPair operator* (const struct AComplexPair& x) const;
    
    _AI AScalar operator* (const AScalar& x) const {return fmuls(fr, x.fr, 0);}
    _AI AScalar operator+ (const AScalar& x) const {return fadds(fr, x.fr, 0);}
    _AI AScalar operator- (const AScalar& x) const {return fadds(fr, x.fr, 2);}
    _AI AScalar operator- ()                 const {return neg_fr(fr);}
    _AI AScalar operator/ (const AScalar& x) const {return *this * x.inverse();}

    _AI AScalar& operator*= (const AScalar& x) {return (*this = *this * x);}
    _AI AScalar& operator/= (const AScalar& x) {return (*this = *this / x);}
    _AI AScalar& operator+= (const AScalar& x) {return (*this = *this + x);}
    _AI AScalar& operator-= (const AScalar& x) {return (*this = *this - x);}

    _AI unsigned operator== (const AScalar& x) const {return eq_fr(fr, x.fr);}
    _AI unsigned operator>= (const AScalar& x) const {return ge_fr(fr, x.fr);}
    _AI unsigned operator>  (const AScalar& x) const {return gt_fr(fr, x.fr);}
    _AI unsigned operator<= (const AScalar& x) const {return le_fr(fr, x.fr);}
    _AI unsigned operator<  (const AScalar& x) const {return lt_fr(fr, x.fr);}
    _AI unsigned operator!= (const AScalar& x) const {return ne_fr(fr, x.fr);}

    _AI AScalar operator<< (int x) const {return exp_adj_fr(fr, x);}
    _AI AScalar operator>> (int x) const {return exp_adj_fr(fr, -x);}

    _AI AScalar& operator<<= (int x) {fr = exp_adj_fr(fr, x); return *this;}
    _AI AScalar& operator>>= (int x) {fr = exp_adj_fr(fr, -x); return *this;}

    _AI AScalar inverse() const {
        fr32 F_inv = inv(fr);
        // One iteration of Newton's method
        return fmuls(F_inv, fmacs(seta_fr(2, 0), F_inv, fr, 1), 0);
    }

    _AI AScalar mul_add(const AScalar& x, const AScalar& y) const {
        return fmacs(fr, x.fr, y.fr, 0);
    }
    _AI AScalar mul_sub(const AScalar& x, const AScalar& y) const {
        return fmacs(fr, x.fr, y.fr, 1);
    }
    _AI AScalar& mul_acc(const AScalar& x, const AScalar& y) {
        fr = fmacs(fr, x.fr, y.fr, 0);
        return *this;
    }

    _AI AScalar f_max(const AScalar& x) const {
        return max_fr(fr, x.fr);
    }

    _AI AScalar f_min(const AScalar& x) const {
        return min_fr(fr, x.fr);
    }

    _AI AScalar f_clamp(const AScalar& low, const AScalar& high) const {
        return f_max(low).f_min(high);
    }

    _AI AScalar abs()          const {return abs_fr(fr);}
    _AI AScalar f_inv()        const {return inv(fr);}
    _AI AScalar f_invsqrt()    const {return invsqrt(fr);}
    _AI AScalar f_sigmoid()    const {return sigmoid(fr);}
    _AI AScalar f_log2()       const {return log2(fr);}
    _AI AScalar f_pow2()       const {return pow2(fr);}
    _AI AScalar f_sqrt()       const {return fmuls(invsqrt(fr), fr, 0);}

    _AI AScalar sine_turns()   const {return sine(fr);}
    _AI AScalar cosine_turns() const {return cosine(fr);}

    _AI AScalar sine_rads()    const {return sine(fmuls(fr, seta_fr(14, 6), 0));}
    _AI AScalar cosine_rads()  const {return cosine(fmuls(fr, seta_fr(14, 6), 0));}

    _AI AScalar f_pow(const AScalar& power) const {
        fr32 z;
        vr64 tmp=vseta_vr(0,0);
        atbool flag;
        uint32_t odd;
        log2mul(z, fr, power.fr, flag);
        // Handle negative number to even power:
        set_VRL(tmp, abs_fr(power.fr));
        floorp_frac(odd, tmp, VRQ0, tmp, VRQ0, 0);
        return s_and(cspow2(z, flag), move_fr_ar(-(int) odd));
    }

    _AI static AScalar atan2_turns(const AScalar& y, const AScalar& x) {
        atbool flags;
        fr32 z;
        ratio(z, x.fr, y.fr, flags);
        return atanratio(z, flags);
    }

    _AI static AScalar atan2_rads(const AScalar& y, const AScalar& x) {
        return fmuls(atan2_turns(y, x).fr, seta_fr(11, 0), 0);
    }

    _AI AScalar arcsine_turns() const {
        atbool flags;
        fr32 s = fmacs(seta_fr(1, 0), fr, fr, 1); // 1 - x^2
        fr32 z = fmuls(s, invsqrt(s), 0);         // sqrt(1 - x^2)
        ratio(z, z, fr, flags);
        return atanratio(z, flags);
    }

    _AI AScalar arcsine_rads() const {
        return fmuls(arcsine_turns().fr, seta_fr(11, 0), 0);
    }

    _AI AScalar f_exp() const {return pow2(fmuls(fr, log2e().fr, 0));}
    _AI AScalar f_log() const {return fmuls(log2(fr), ln2().fr, 0);}

    _AI static AScalar MinusOne()  {return seta_fr(17, 0);}
    _AI static AScalar Zero()      {return seta_fr(0,  0);}
    _AI static AScalar One()       {return seta_fr(1,  0);}
    _AI static AScalar Two()       {return seta_fr(2,  0);}
    _AI static AScalar Three()     {return seta_fr(28, 0);}
    _AI static AScalar Ten()       {return seta_fr(30, 0);}
    _AI static AScalar Twenty()    {return seta_fr(30, 1);}
    _AI static AScalar Half()      {return seta_fr(3,  0);}
    _AI static AScalar Sqrt2()     {return seta_fr(15, 0);}
    _AI static AScalar HalfSqrt2() {return seta_fr(16, 0);}
    _AI static AScalar Pi()        {return seta_fr(5,  0);}
    _AI static AScalar TwoPi()     {return seta_fr(11, 0);}
    _AI static AScalar HalfPi()    {return seta_fr(5,  7);}
    _AI static AScalar E()         {return seta_fr(6,  0);}
    _AI static AScalar HalfE()     {return seta_fr(6,  7);}
    _AI static AScalar log2ten()   {return seta_fr(7,  0);}
    _AI static AScalar log10two()  {return seta_fr(8,  0);}
    _AI static AScalar log2e()     {return seta_fr(9,  0);}
    _AI static AScalar ln2()       {return seta_fr(10, 0);}
    _AI static AScalar MaxAFloat() {return seta_fr(1,  3);}
    _AI static AScalar MinAFloat() {return seta_fr(17, 3);}

    // For debugging:

    _AI uint32_t raw()        const {return move_ar_fr(fr);}
    _AI uint32_t raw_afloat() const {return move_ar_fr(fr);}
    _AI uint32_t raw_float()  const {
        vr64 v=vseta_vr(0,0);
        set_VRL(v, fr);
        convert_32F_to_IEEE_float_x2(v);
        return move32_ar_vr(v, VRQ0);
    }

    _AI float to_float() const {
        int i = raw_float();
        return *(float*) &i;
    }

    _AI double to_double() const {
        vr64 tmp = convert_32F_to_64F(fr);
        return *(double*) &tmp;
    }

    _AI int16_t to_float16(int SIGN=1, int EXP=5, int BIAS=14) const {
        vr64 tmp ; 
        set_VRL(tmp, fr);
        convert_32F_to_16F_x1(tmp, FLT16_SIGN, FLT16_EXP, FLT16_BIAS, 1, VRQ0);
        int16_t tmp16 = (int16_t)(move32_ar_vr(tmp, VRQ0)>>16);
        return tmp16;
    }

};

//
// Pointer to AScalar
//

struct PScalar
{
    fr32* ptr;

    _AI PScalar(void* p) : ptr((fr32*) p) {}

    _AI operator AScalar*() const {return (AScalar*) ptr;}
    _AI AScalar* operator->() const {return (AScalar*) ptr;}
    _AI AScalar& operator[] (int i) const {return ((AScalar*) ptr)[i];}

    _AI PScalar  operator+ (int index) const {return PScalar(ptr + index);}
    _AI PScalar  operator- (int index) const {return PScalar(ptr - index);}

    _AI PScalar& operator+= (int index) {ptr += index; return *this;}
    _AI PScalar& operator-= (int index) {ptr -= index; return *this;}

    _AI PScalar& operator++ ()    {++ptr; return *this;}
    _AI PScalar& operator-- ()    {--ptr; return *this;}
    _AI PScalar  operator++ (int) {PScalar p(*this); ++ptr; return p;}
    _AI PScalar  operator-- (int) {PScalar p(*this); --ptr; return p;}
};

struct PConstScalar
{
    const fr32* ptr;

    _AI PConstScalar(const void* p) : ptr((const fr32*) p) {}

    _AI operator const AScalar*() const {return (const AScalar*) ptr;}
    _AI const AScalar* operator->() const {return (const AScalar*) ptr;}
    _AI const AScalar& operator[] (int i) const {return ((const AScalar*) ptr)[i];}

    _AI PConstScalar  operator+ (int index) const {return PConstScalar(ptr + index);}
    _AI PConstScalar  operator- (int index) const {return PConstScalar(ptr - index);}

    _AI PConstScalar& operator+= (int index) {ptr += index; return *this;}
    _AI PConstScalar& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstScalar& operator++ ()    {++ptr; return *this;}
    _AI PConstScalar& operator-- ()    {--ptr; return *this;}
    _AI PConstScalar  operator++ (int) {PConstScalar p(*this); ++ptr; return p;}
    _AI PConstScalar  operator-- (int) {PConstScalar p(*this); --ptr; return p;}
};

#endif
