///////////////////////////////////////////////////////////////////////////////
///
/// \file AScalar.h
///
/// AScalar wrapper for float
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ASCALAR_H
#define ASCALAR_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "AFloatLiteral.h"

/// Generate a compile-time AScalar

#define CONST_ASCALAR(D) AScalar(float(D))

/// Generate a compile-time integer in the native float format

#define RAW_LITERAL(D) CFLOAT_LITERAL(D)

/// Encourage inlining

#define _AI AVL_ALWAYS_INLINE

#if defined(__GNUC__)
 #define AVL_ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
 #define AVL_ALWAYS_INLINE __forceinline
#else
 #define AVL_ALWAYS_INLINE inline
#endif

#ifdef  AVL_DEBUG
 #define AVL_ASSERT(A) do { \
    if(!(A)) printf("%s:%d: Assertion failed: %s\n", __FILE__, __LINE__, #A); \
    } while(0)
#else
 #define AVL_ASSERT(A)
#endif

#if defined(_MSC_VER)
 #include <algorithm>
 #define fmaxf(A,B) std::max(A,B)
 #define fminf(A,B) std::min(A,B)
#endif

#if !defined(M_TWOPI)
 #define M_TWOPI (2 * M_PI)
#endif

////////////////////////////////////////////////////////////////////////////////
//
// This example fills an array of AScalars with the first ten natural numbers
// and computes the sum of the array:
// \code
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
// \endcode
//
////////////////////////////////////////////////////////////////////////////////

struct AScalar
{
    float fr;

    _AI AScalar() {}
    _AI AScalar(const AScalar& s) : fr(s.fr)  {}

    _AI AScalar(int32_t i, uint32_t fractional_bits = 0) {
        fr = i * powf(2, -(float) fractional_bits);
    }
    _AI AScalar(uint32_t i, uint32_t fractional_bits) {
        fr = i * powf(2, -(float) fractional_bits);
    }

    _AI AScalar(double d) : fr((float) d) {}
    _AI AScalar(float f)  : fr(f) {}

    _AI AScalar(const struct ADouble& d);

private:
    // The uint32_t constructor is private to avoid accidentally converting a raw
    // literal. If the argument is a compile-time constant use CONST_ASCALAR(),
    // otherwise convert it to an int32_t or use the two-argument constructor.

    _AI AScalar(uint32_t i) : fr((float) i) {}
public:

    _AI int to_int(uint32_t fractional_bits = 0) const {
        float x = fr * powf(2, (float) fractional_bits);
        return (int) ((x >= 0) ? floorf(x + 0.5f) : ceilf(x - 0.5f));
    }
    _AI int floor() const {return (int) floorf(fr);}
    _AI int ceil()  const {return (int) ceilf(fr);}

    _AI struct AComplex     operator* (const struct AComplex& x)     const;
    _AI struct AQuaternion  operator* (const struct AQuaternion& x)  const;
    _AI struct AQuad        operator* (const struct AQuad& x)        const;
    _AI struct ATriple      operator* (const struct ATriple& x)      const;
    _AI struct APair        operator* (const struct APair& x)        const;
    _AI struct AComplexPair operator* (const struct AComplexPair& x) const;
    
    _AI AScalar operator* (const AScalar& x) const {return fr * x.fr;}
    _AI AScalar operator+ (const AScalar& x) const {return fr + x.fr;}
    _AI AScalar operator- (const AScalar& x) const {return fr - x.fr;}
    _AI AScalar operator- ()                 const {return -fr;}
    _AI AScalar operator/ (const AScalar& x) const {return fr / x.fr;}

    _AI AScalar& operator*= (const AScalar& x) {return (*this = *this * x);}
    _AI AScalar& operator/= (const AScalar& x) {return (*this = *this / x);}
    _AI AScalar& operator+= (const AScalar& x) {return (*this = *this + x);}
    _AI AScalar& operator-= (const AScalar& x) {return (*this = *this - x);}

    _AI bool operator== (const AScalar& x) const {return fr == x.fr;}
    _AI bool operator>= (const AScalar& x) const {return fr >= x.fr;}
    _AI bool operator>  (const AScalar& x) const {return fr >  x.fr;}
    _AI bool operator<= (const AScalar& x) const {return fr <= x.fr;}
    _AI bool operator<  (const AScalar& x) const {return fr <  x.fr;}
    _AI bool operator!= (const AScalar& x) const {return fr != x.fr;}

    _AI AScalar operator<< (int x) const {return fr * powf(2, (float) x);}
    _AI AScalar operator>> (int x) const {return fr * powf(2, (float)-x);}

    _AI AScalar& operator<<= (int x) {fr = fr * powf(2, (float) x); return *this;}
    _AI AScalar& operator>>= (int x) {fr = fr * powf(2, (float)-x); return *this;}

    _AI AScalar inverse() const {return 1.0 / fr;}

    _AI AScalar mul_add(const AScalar& x, const AScalar& y) const {
        return fr + x.fr * y.fr;
    }
    _AI AScalar mul_sub(const AScalar& x, const AScalar& y) const {
        return fr - x.fr * y.fr;
    }
    _AI AScalar& mul_acc(const AScalar& x, const AScalar& y) {
        fr += x.fr * y.fr;
        return *this;
    }

    _AI AScalar f_max(const AScalar& x) const {
        return fmaxf(fr, x.fr);
    }

    _AI AScalar f_min(const AScalar& x) const {
        return fminf(fr, x.fr);
    }

    _AI AScalar f_clamp(const AScalar& low, const AScalar& high) const {
        return f_max(low).f_min(high);
    }

    _AI AScalar abs()          const {return fabsf(fr);}
    _AI AScalar f_inv()        const {return 1.0 / fr;}
    _AI AScalar f_invsqrt()    const {return 1.0 / sqrtf(fr);}
    _AI AScalar f_sigmoid()    const {return fr < 0 ? powf(2.0, fr - 1)
                                                    : 1 - powf(2.0, -fr - 1);}
    _AI AScalar f_log2()       const {return logf(fr) / M_LN2;}
    _AI AScalar f_pow2()       const {return powf(2.0, fr);}
    _AI AScalar f_sqrt()       const {return sqrtf(fr);}

    _AI AScalar sine_turns()   const {return sinf(fr * (float) M_TWOPI);}
    _AI AScalar cosine_turns() const {return cosf(fr * (float) M_TWOPI);}

    _AI AScalar sine_rads()    const {return sinf(fr);}
    _AI AScalar cosine_rads()  const {return cosf(fr);}

    _AI AScalar f_pow(const AScalar& power) const {return powf(fr, power.fr);}

    _AI static AScalar atan2_turns(const AScalar& y, const AScalar& x) {
        return atan2f(y.fr, x.fr) / M_TWOPI;
    }

    _AI static AScalar atan2_rads(const AScalar& y, const AScalar& x) {
        return atan2f(y.fr, x.fr);
    }

    _AI AScalar arcsine_turns() const {return asinf(fr) / M_TWOPI;}
    _AI AScalar arcsine_rads()  const {return asinf(fr);}

    _AI AScalar f_exp() const {return expf(fr);}
    _AI AScalar f_log() const {return logf(fr);}

    _AI static AScalar MinusOne()  {return -1.0;}
    _AI static AScalar Zero()      {return 0.0;}
    _AI static AScalar One()       {return 1.0;}
    _AI static AScalar Two()       {return 2.0;}
    _AI static AScalar Three()     {return 3.0;}
    _AI static AScalar Ten()       {return 10.0;}
    _AI static AScalar Twenty()    {return 20.0;}
    _AI static AScalar Half()      {return 0.5;}
    _AI static AScalar Sqrt2()     {return M_SQRT2;}
    _AI static AScalar HalfSqrt2() {return M_SQRT1_2;}
    _AI static AScalar Pi()        {return M_PI;}
    _AI static AScalar TwoPi()     {return M_TWOPI;}
    _AI static AScalar HalfPi()    {return M_PI_2;}
    _AI static AScalar E()         {return M_E;}
    _AI static AScalar HalfE()     {return M_E / 2;}
    _AI static AScalar log2ten()   {return M_LN10 / M_LN2;}
    _AI static AScalar log10two()  {return M_LN2 / M_LN10;}
    _AI static AScalar log2e()     {return M_LOG2E;}
    _AI static AScalar ln2()       {return M_LN2;}
    _AI static AScalar MaxAFloat() {return 4294967040.0;}
    _AI static AScalar MinAFloat() {return -4294967040.0;}

    // For debugging:

    _AI float  to_float()  const {return fr;}
    _AI double to_double() const {return fr;}

    _AI uint32_t raw() const {
        int i;
        memcpy(&i, &fr, 4);
        return i;
    }
    _AI uint32_t raw_float() const {return raw();}
    _AI uint32_t raw_afloat() const {
        int a;
        memcpy(&a, &fr, 4);
        int sign = a & 0x80000000;
        int exp  = a & 0x7f800000;
        int mant = a & 0x007fffff;

        exp = exp - (95 << 23);
        if (exp > 0x1f800000)
            return sign | 0x7fffffff;
        if (exp < 0)
            return 0;

        return sign | ((exp | mant) << 2);
    }
};

//
// Pointer to AScalar
//

struct PScalar
{
    float* ptr;

    _AI PScalar(void* p) : ptr((float*) p) {}

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
    const float* ptr;

    _AI PConstScalar(const void* p) : ptr((const float*) p) {}

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

    \fn AScalar::AScalar(const struct ADouble& d)
    \brief Construct from ADouble

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
