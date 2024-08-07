/************************************************************************//**
 * @file    AVL\DeltaMax\AScalar.h
 *
 * @brief   AScalar wrapper for fr32 on DeltaMax
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ASCALAR_H
#define ASCALAR_H

/**************************************************************************//**
 * @defgroup dmx_avl DeltaMax (Dmx) Audience Vector Library 
 * @{
 *****************************************************************************/

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
        vr128 z;
        replicate_ar(z, 1, i);
        convert_32I_to_32F_x1(z, 31 - fractional_bits, VRQ0);
        fr = get_VRQ0(z);
    }

    _AI AScalar(uint32_t i, uint32_t fractional_bits) {
        vr128 z;
        vr128 lsb;
        replicate_ar(z, 1, i >> 1);                             // i/2
        replicate_ar(lsb, 1, i & 1);                            // i&1
        convert_32I_to_32F_x1(z, 31 - fractional_bits, VRQ0);   // (afloat)(i/2)
        convert_32I_to_32F_x1(lsb, 31 - fractional_bits, VRQ0); // (afloat)(i&1)
        exp_adji(z, VRQ0, z, VRQ0, 1);                          // 2*(afloat)(i/2)
        fadds(z, VRQ0, z, VRQ0, lsb, VRQ0, 0);                  // 2*(afloat)(i/2)+(afloat)(i&1)
        fr = get_VRQ0(z);
    }

    // AScalar::AScalar(double) loses 2 bits of precision because
    // IEEE single float has a 23(+1) bit mantissa but AFloat has 25(+1).
    // If full precision is required for a compile-time constant use CONST_ASCALAR().
    _AI AScalar(double d) {*this = AScalar((float) d);}

    _AI AScalar(float f) : fr(convert_IEEE_float_to_32F(*(int*) &f)) {}

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
        vr128 v;
        set_VRQ0(v, fr);
        convert_32F_to_32I_x1(v, 31 - fractional_bits, 1, VRQ0);
        return move32_ar_vr(v, VRQ0);
    }

    _AI int floor() const {
        vr128 v = vmax(vreplicate_fr(fr),
                       vexp_adji(vseta_vr(17, 0, 0), 31));
        convert_32F_to_32I_x1(v, 31, 0, VRQ0);
        int trunc = move32_ar_vr(v, VRQ0);
        convert_32I_to_32F_x1(v, 31, VRQ0);
        uint32_t decrement = XT_ANDB(lt_fr(fr, seta_fr(0, 0, 0)),
                                     ne(v, VRQ0, v, VRQ1));
        return trunc - decrement;
    }

    _AI int ceil() const {
        vr128 v = vreplicate_fr(fr);
        convert_32F_to_32I_x1(v, 31, 0, VRQ0);
        int trunc = move32_ar_vr(v, VRQ0);
        convert_32I_to_32F_x1(v, 31, VRQ0);
        uint32_t increment = XT_ANDB(gt_fr(fr, seta_fr(0, 0, 0)),
                                     ne(v, VRQ0, v, VRQ1));
        int ceiling = trunc + increment;
        return ceiling - (increment & (ceiling >> 31));
    }

    _AI struct AComplex      operator* (const struct AComplex& x)     const;
    _AI struct AQuaternion   operator* (const struct AQuaternion& x)  const;
    _AI struct AQuad         operator* (const struct AQuad& x)        const;
    _AI struct ATriple       operator* (const struct ATriple& x)      const;
    _AI struct APair         operator* (const struct APair& x)        const;
    _AI struct AComplexPair  operator* (const struct AComplexPair& x) const;
    
    _AI AScalar operator* (const AScalar& x) const {return fpmul(fr, x.fr, 0);}
    _AI AScalar operator+ (const AScalar& x) const {return fpadd(fr, x.fr, 0);}
    _AI AScalar operator- (const AScalar& x) const {return fpadd(fr, x.fr, 2);}
    _AI AScalar operator- ()                 const {return neg_fr(fr);}
    _AI AScalar operator/ (const AScalar& x) const {return *this * x.inverse();}

    _AI AScalar& operator*= (const AScalar& x) {return (*this = *this * x);}
    _AI AScalar& operator/= (const AScalar& x) {return (*this = *this / x);}
    _AI AScalar& operator+= (const AScalar& x) {return (*this = *this + x);}
    _AI AScalar& operator-= (const AScalar& x) {return (*this = *this - x);}

    _AI xtbool operator== (const AScalar& x) const {return eq_fr(fr, x.fr);}
    _AI xtbool operator>= (const AScalar& x) const {return ge_fr(fr, x.fr);}
    _AI xtbool operator>  (const AScalar& x) const {return gt_fr(fr, x.fr);}
    _AI xtbool operator<= (const AScalar& x) const {return le_fr(fr, x.fr);}
    _AI xtbool operator<  (const AScalar& x) const {return lt_fr(fr, x.fr);}
    _AI xtbool operator!= (const AScalar& x) const {return ne_fr(fr, x.fr);}

    _AI AScalar operator<< (int x) const {return exp_adj_fr(fr, x);}
    _AI AScalar operator>> (int x) const {return exp_adj_fr(fr, -x);}

    _AI AScalar& operator<<= (int x) {fr = exp_adj_fr(fr, x); return *this;}
    _AI AScalar& operator>>= (int x) {fr = exp_adj_fr(fr, -x); return *this;}

    _AI AScalar inverse() const {
        // One iteration of Newton's method
        fr32 inv = inv_fr(fr);
        fr32 z = seta_fr(2, 0, 0);
        fpmac(z, inv, fr, 1);
        return fpmul(z, inv, 0);
    }

    _AI AScalar mul_add(const AScalar& x, const AScalar& y) const {
        fr32 z = fr;
        fpmac(z, x.fr, y.fr, 0);
        return z;
    }
    _AI AScalar mul_sub(const AScalar& x, const AScalar& y) const {
        fr32 z = fr;
        fpmac(z, x.fr, y.fr, 1);
        return z;
    }
    _AI AScalar& mul_acc(const AScalar& x, const AScalar& y) {
        fpmac(fr, x.fr, y.fr, 0);
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
    _AI AScalar f_inv()        const {return inv_fr(fr);}
    _AI AScalar f_invsqrt()    const {return invsqrt_fr(fr);}
    _AI AScalar f_sigmoid()    const {return sigmoid_fr(fr);}
    _AI AScalar f_log2()       const {return log2_fr(fr);}
    _AI AScalar f_pow2()       const {return pow2_fr(fr);}
    _AI AScalar f_sqrt()       const {return fpmul(fr, invsqrt_fr(fr), 0);}

    _AI AScalar sine_turns()   const {return sine_fr(fr);}
    _AI AScalar cosine_turns() const {return cosine_fr(fr);}

    _AI AScalar sine_rads()   const {return sine_fr(fpmul(fr, seta_fr(14, 6, 0), 0));}
    _AI AScalar cosine_rads() const {return cosine_fr(fpmul(fr, seta_fr(14, 6, 0), 0));}

    _AI AScalar f_pow(const AScalar& power) const {
        vr128 z;
        vr128 tmp;
        xtbool flag;
        uint32_t odd;
        set_VRQ0(z, fr);
        set_VRQ1(z, power.fr);
        log2mul(z, VRQ0, z, VRQ0, z, VRQ1, flag);
        // Handle negative number to even power:
        f_abs(tmp, VRQ0, z, VRQ1);
        floorp_frac(odd, tmp, VRQ0, tmp, VRQ0, 0);
        cspow2(z, VRQ0, z, VRQ0, XT_ORBC(flag, int_to_xt_bool((int) odd)));
        return get_VRQ0(z);
    }

    _AI static AScalar atan2_turns(const AScalar& y, const AScalar& x) {
        vr128 z;
        xtbool4 flags;
        set_VRQ0(z, x.fr);
        set_VRQ1(z, y.fr);
        ratio(z, VRQ0, z, VRQ0, z, VRQ1, flags);
        atanratio(z, VRQ0, z, VRQ0, flags);
        return get_VRQ0(z);
    }

    _AI static AScalar atan2_rads(const AScalar& y, const AScalar& x) {
        return fpmul(atan2_turns(y, x).fr, seta_fr(11, 0, 0), 0);
    }

    _AI AScalar arcsine_turns() const {
        fr32 s = seta_fr(1, 0, 0);                // s = 1
        vr128 z;
        xtbool4 flags;
        fpmac(s, fr, fr, 1);                      // 1 - x^2
        set_VRQ0(z, fpmul(s, invsqrt_fr(s), 0));  // sqrt(1 - x^2)
        set_VRQ1(z, fr);
        ratio(z, VRQ0, z, VRQ0, z, VRQ1, flags);
        atanratio(z, VRQ0, z, VRQ0, flags);
        return get_VRQ0(z);
    }

    _AI AScalar arcsine_rads() const {
        return fpmul(arcsine_turns().fr, seta_fr(11, 0, 0), 0);
    }

    _AI AScalar f_exp() const {return pow2_fr(fpmul(fr, log2e().fr, 0));}
    _AI AScalar f_log() const {return fpmul(log2_fr(fr), ln2().fr, 0);}

    _AI static AScalar MinusOne()  {return seta_fr(17, 0, 0);}
    _AI static AScalar Zero()      {return seta_fr(0,  0, 0);}
    _AI static AScalar One()       {return seta_fr(1,  0, 0);}
    _AI static AScalar Two()       {return seta_fr(2,  0, 0);}
    _AI static AScalar Three()     {return seta_fr(28, 0, 0);}
    _AI static AScalar Ten()       {return seta_fr(30, 0, 0);}
    _AI static AScalar Twenty()    {return seta_fr(30, 1, 0);}
    _AI static AScalar Half()      {return seta_fr(3,  0, 0);}
    _AI static AScalar Sqrt2()     {return seta_fr(15, 0, 0);}
    _AI static AScalar HalfSqrt2() {return seta_fr(16, 0, 0);}
    _AI static AScalar Pi()        {return seta_fr(5,  0, 0);}
    _AI static AScalar TwoPi()     {return seta_fr(11, 0, 0);}
    _AI static AScalar HalfPi()    {return seta_fr(5,  7, 0);}
    _AI static AScalar E()         {return seta_fr(6,  0, 0);}
    _AI static AScalar HalfE()     {return seta_fr(6,  7, 0);}
    _AI static AScalar log2ten()   {return seta_fr(7,  0, 0);}
    _AI static AScalar log10two()  {return seta_fr(8,  0, 0);}
    _AI static AScalar log2e()     {return seta_fr(9,  0, 0);}
    _AI static AScalar ln2()       {return seta_fr(10, 0, 0);}
    _AI static AScalar MaxAFloat() {return seta_fr(1,  3, 0);}
    _AI static AScalar MinAFloat() {return seta_fr(17, 3, 0);}

    // For debugging:

    _AI uint32_t raw()        const {return move_ar_fr(fr);}
    _AI uint32_t raw_afloat() const {return move_ar_fr(fr);}
    _AI uint32_t raw_float()  const {
        return move_ar_fr(convert_32F_to_IEEE_float(fr));
    }

    _AI float to_float() const {
        int i = raw_float();
        return *(float*) &i;
    }

    _AI double to_double() const {
        uint32_t u32  = move_ar_fr(fr);
        uint32_t sign = u32 & 0x80000000;
        uint32_t exp  = u32 & 0x7e000000;
        uint32_t mant = u32 & 0x01ffffff;
        uint64_t u64  = ((uint64_t) sign << 32) | ((uint64_t) mant << 27);

        if (exp | mant)
            u64 |= (uint64_t) ((exp >> 25) + 991) << 52;

        return *(double*) &u64;
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

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AScalar
    \brief Wrapper for an fr32 or a float

    \fn AScalar::AScalar(const AScalar& s)
    \brief Copy constructor

    \fn AScalar::AScalar(int32_t i,  uint32_t fractional_bits = 0)
    \brief Construct from signed fixed-point

    \fn AScalar::AScalar(uint32_t i, uint32_t fractional_bits)
    \brief Construct from unsigned fixed-point

    \fn AScalar::AScalar(float f)
    \brief Construct from a float

    \fn AScalar::AScalar(double d)
    \brief Construct from double

    \fn int AScalar::to_int(uint32_t fractional_bits = 0)
    \brief Convert to fixed-point with rounding

    \fn int AScalar::floor()
    \brief Convert to integer

    \fn int AScalar::ceil()
    \brief Convert to integer

    \fn AScalar AScalar::inverse()
    \brief Returns 1.0 / *this

    \fn AScalar AScalar::mul_add(const AScalar& x, const AScalar& y)
    \brief Returns *this + x * y (non-destructive, the destructive version is mul_acc)

    \fn AScalar AScalar::mul_sub(const AScalar& x, const AScalar& y)
    \brief Returns *this - x * y (non-destructive)

    \fn AScalar& AScalar::mul_acc(const AScalar& x, const AScalar& y)
    \brief Returns *this += x * y

    \fn AScalar AScalar::f_max(const AScalar& x)
    \brief Returns max(*this, x)

    \fn AScalar AScalar::f_min(const AScalar& x)
    \brief Returns min(*this, x)

    \fn AScalar AScalar::f_clamp(const AScalar& low, const AScalar& high)
    \brief Returns max(min(*this, high), low)

    \fn AScalar AScalar::abs()
    \brief Returns abs(*this)

    \fn AScalar AScalar::f_inv()
    \brief Returns 1.0 / *this

    \fn AScalar AScalar::f_invsqrt()
    \brief Returns 1.0 / sqrt(*this)

    \fn AScalar AScalar::f_sigmoid()
    \brief Returns (*this < 0) ? 2**(*this - 1) : 1 - 2**(-*this - 1)

    \fn AScalar AScalar::f_log2()
    \brief Returns log2(*this)

    \fn AScalar AScalar::f_pow2()
    \brief Returns 2**(*this)

    \fn AScalar AScalar::f_sqrt()
    \brief Returns sqrt(*this)

    \fn AScalar AScalar::sine_turns()
    \brief Returns sin(2π * (*this))

    \fn AScalar AScalar::cosine_turns()
    \brief Returns cos(2π * (*this))

    \fn AScalar AScalar::sine_rads()
    \brief Returns sin(*this)

    \fn AScalar AScalar::cosine_rads()
    \brief Returns cos(*this)

    \fn AScalar AScalar::f_pow(const AScalar& power)
    \brief Returns (*this)**power

    \fn static AScalar AScalar::atan2_turns(const AScalar& y, const AScalar& x)
    \brief Returns atan(y/x) / 2π

    \fn static AScalar AScalar::atan2_rads(const AScalar& y, const AScalar& x)
    \brief Returns atan(y/x)

    \fn AScalar AScalar::arcsine_turns()
    \brief Returns arcsine(*this) / 2π

    \fn AScalar AScalar::arcsine_rads()
    \brief Returns arcsine(*this)

    \fn AScalar AScalar::f_exp()
    \brief Returns exp(*this)

    \fn AScalar AScalar::f_log()
    \brief Returns log(*this)

    \fn static AScalar AScalar::MinusOne()
    \brief Returns -1.0

    \fn static AScalar AScalar::Zero()
    \brief Returns 0.0

    \fn static AScalar AScalar::One()
    \brief Returns 1.0

    \fn static AScalar AScalar::Two()
    \brief Returns 2.0

    \fn static AScalar AScalar::Three()
    \brief Returns 3.0

    \fn static AScalar AScalar::Half()
    \brief Returns 0.5

    \fn static AScalar AScalar::Sqrt2()
    \brief Returns sqrt(2.0)

    \fn static AScalar AScalar::HalfSqrt2()
    \brief Returns 1.0 / sqrt(2.0)

    \fn static AScalar AScalar::Pi()
    \brief Returns π

    \fn static AScalar AScalar::TwoPi()
    \brief Returns 2π

    \fn static AScalar AScalar::HalfPi()
    \brief Returns π / 2.0

    \fn static AScalar AScalar::E()
    \brief Returns exp(1.0)

    \fn static AScalar AScalar::HalfE()
    \brief Returns exp(1.0) / 2.0

    \fn static AScalar AScalar::log2ten()
    \brief Returns log2(10.0)

    \fn static AScalr AScalar::log10two()
    \brief Returns log10(2.0)

    \fn static AScalar AScalar::log2e()
    \brief Returns 1.0 / log(2.0)

    \fn static AScalar AScalar::ln2()
    \brief Returns log(2.0)

    \fn static AScalar AScalar::MaxAFloat()
    \brief Returns the largest AFloat value converted to a native float

    \fn static AScalar AScalar::MinAFloat()
    \brief Returns the smallest AFloat value converted to a native float

    \fn float AScalar::to_float()
    \brief Converts to float

    \fn double AScalar::to_double()
    \brief Converts to double

    \fn uint32_t AScalar::raw()
    \brief Converts to an integer representation of a native float

    \fn uint32_t AScalar::raw_float()
    \brief Converts to an integer representation of a float

    \fn uint32_t AScalar::raw_afloat()
    \brief Converts to an integer representation of an AFloat
*/

/** \class PScalar
    \brief Abstract pointer to an AScalar

    \fn PScalar::PScalar(void* p)
    \brief Constructor

    \fn AScalar* PScalar::operator->()
    \brief Dereference

    \fn AScalar& PScalar::operator[] (int i)
    \brief Array reference
*/

/** \class PConstScalar
    \brief Abstract pointer to a const AScalar

    \fn PConstScalar::PConstScalar(const void* p)
    \brief Constructor

    \fn const AScalar* PScalar::operator->()
    \brief Dereference

    \fn const AScalar& PConstScalar::operator[] (int i)
    \brief Array reference
*/
