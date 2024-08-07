////////////////////////////////////////////////////////////////////////////////
///
/// \file AQuaternion.h
///
/// AQuaternion wrapper for two std::complex<float>s
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef AQUATERNION_H
#define AQUATERNION_H

#include <complex>

#include "AScalar.h"

struct AQuaternion
{
    std::complex<float> vr0;
    std::complex<float> vr1;

    _AI AQuaternion() {}
    _AI AQuaternion(const AQuaternion& a) : vr0(a.vr0), vr1(a.vr1) {}

    _AI AQuaternion& operator= (const AQuaternion& x) {vr0 = x.vr0; vr1 = x.vr1; return *this;}

    _AI AQuaternion(const AScalar& r, const AScalar& i,
                    const AScalar& j, const AScalar& k) : vr0(r.fr, i.fr), vr1(j.fr, k.fr) {}

    _AI AQuaternion(float r, float i, float j, float k) : vr0(r, i), vr1(j, k) {}

    _AI bool operator== (const AQuaternion& x) const {
        return vr0 == x.vr0 && vr1 == x.vr1;
    }
    _AI bool operator!= (const AQuaternion& x) const {
        return vr0 != x.vr0 || vr1 != x.vr1;
    }

    _AI AQuaternion operator* (const AQuaternion& y) const {
        AQuaternion z;
        z.vr0 = vr0 * y.vr0 - vr1 * std::conj(y.vr1);
        z.vr1 = vr0 * y.vr1 + vr1 * std::conj(y.vr0);
        return z;
    }
    _AI AQuaternion operator+ (const AQuaternion& x) const {
        AQuaternion z;
        z.vr0 = vr0 + x.vr0;
        z.vr1 = vr1 + x.vr1;
        return z;
    }
    _AI AQuaternion operator- (const AQuaternion& x) const {
        AQuaternion z;
        z.vr0 = vr0 - x.vr0;
        z.vr1 = vr1 - x.vr1;
        return z;
    }
    _AI AQuaternion operator- () const {
        AQuaternion z;
        z.vr0 = -vr0;
        z.vr1 = -vr1;
        return z;
    }
    _AI AQuaternion operator/ (const AQuaternion& x) const {
        return *this * x.inverse();
    }

    _AI AQuaternion& operator*= (const AQuaternion& x) {return (*this = *this * x);}
    _AI AQuaternion& operator/= (const AQuaternion& x) {return (*this = *this / x);}
    _AI AQuaternion& operator+= (const AQuaternion& x) {return (*this = *this + x);}
    _AI AQuaternion& operator-= (const AQuaternion& x) {return (*this = *this - x);}

    _AI AQuaternion operator* (const AScalar& x) const {
        AQuaternion z;
        z.vr0 = vr0 * x.fr;
        z.vr1 = vr1 * x.fr;
        return z;
    }
    _AI AQuaternion& operator*= (const AScalar& x) {
        vr0 *= x.fr;
        vr1 *= x.fr;
        return *this;
    }

    _AI AScalar r() const {return vr0.real();}
    _AI AScalar i() const {return vr0.imag();}
    _AI AScalar j() const {return vr1.real();}
    _AI AScalar k() const {return vr1.imag();}

    _AI AQuaternion& set_r(const AScalar& a) {vr0 = std::complex<float>(a.fr, vr0.imag()); return *this;}
    _AI AQuaternion& set_i(const AScalar& a) {vr0 = std::complex<float>(vr0.real(), a.fr); return *this;}
    _AI AQuaternion& set_j(const AScalar& a) {vr1 = std::complex<float>(a.fr, vr1.imag()); return *this;}
    _AI AQuaternion& set_k(const AScalar& a) {vr1 = std::complex<float>(vr1.real(), a.fr); return *this;}

    _AI AScalar dot(const AQuaternion& x) const {
        return vr0.real() * x.vr0.real() + vr0.imag() * x.vr0.imag()
             + vr1.real() * x.vr1.real() + vr1.imag() * x.vr1.imag();
    }

    _AI AQuaternion conj() const {
        AQuaternion z;
        z.vr0 = std::conj(vr0);
        z.vr1 = -vr1;
        return z;
    }

    _AI AQuaternion mul_conj(const AQuaternion& y) const {
        AQuaternion z;
        z.vr0 =  vr0 * std::conj(y.vr0) + vr1 * std::conj(y.vr1);
        z.vr1 =  vr1 * y.vr0            - vr0 * y.vr1;
        return z;
    }

    _AI AScalar     norm_sq() const {return std::norm(vr0) + std::norm(vr1);}
    _AI AScalar     norm()    const {return norm_sq().f_sqrt();}
    _AI AQuaternion inverse() const {return conj() * norm_sq().inverse();}

    _AI AQuaternion& normalize() {return (*this = *this * norm_sq().f_invsqrt());}
};

_AI AQuaternion AScalar::operator* (const struct AQuaternion& x) const {
    AQuaternion z;
    z.vr0 = fr * x.vr0;
    z.vr1 = fr * x.vr1;
    return z;
}

/// \brief Normalized linear interpolation
///

_AI AQuaternion nLerp(const AQuaternion& x, const AQuaternion& y, const AScalar& t)
{
    return ((AScalar::One() - t) * x + t * y).normalize();
}

//
// Pointer to AQuaternion
//

struct PQuaternion
{
    AQuaternion* ptr;

    _AI PQuaternion(void* p) : ptr((AQuaternion*) p) {}

    _AI PQuaternion& operator= (void* p) {ptr = (AQuaternion*) p; return *this;}

    _AI operator AQuaternion*() const {return ptr;}
    _AI AQuaternion* operator->() const {return ptr;}
    _AI AQuaternion& operator[] (int i) const {return ptr[i];}

    _AI PQuaternion  operator+ (int index) const {return PQuaternion(ptr + index);}
    _AI PQuaternion  operator- (int index) const {return PQuaternion(ptr - index);}

    _AI PQuaternion& operator+= (int index) {ptr += index; return *this;}
    _AI PQuaternion& operator-= (int index) {ptr -= index; return *this;}

    _AI PQuaternion& operator++ ()    {++ptr; return *this;}
    _AI PQuaternion& operator-- ()    {--ptr; return *this;}
    _AI PQuaternion  operator++ (int) {PQuaternion p(*this); ++ptr; return p;}
    _AI PQuaternion  operator-- (int) {PQuaternion p(*this); --ptr; return p;}
};

struct PConstQuaternion
{
    const AQuaternion* ptr;

    _AI PConstQuaternion(const void* p) : ptr((const AQuaternion*) p) {}

    _AI PConstQuaternion& operator= (void* p) {ptr = (const AQuaternion*) p; return *this;}

    _AI operator const AQuaternion*() const {return ptr;}
    _AI const AQuaternion* operator->() const {return ptr;}
    _AI const AQuaternion& operator[] (int i) const {return ptr[i];}

    _AI PConstQuaternion  operator+ (int index) const {return PConstQuaternion(ptr + index);}
    _AI PConstQuaternion  operator- (int index) const {return PConstQuaternion(ptr - index);}

    _AI PConstQuaternion& operator+= (int index) {ptr += index; return *this;}
    _AI PConstQuaternion& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstQuaternion& operator++ ()    {++ptr; return *this;}
    _AI PConstQuaternion& operator-- ()    {--ptr; return *this;}
    _AI PConstQuaternion  operator++ (int) {PConstQuaternion p(*this); ++ptr; return p;}
    _AI PConstQuaternion  operator-- (int) {PConstQuaternion p(*this); --ptr; return p;}
};

#endif

/** \class AQuaternion
    \brief Wrapper for a vr128 or two vr64s or two std::complex<float>s

    \fn AQuaternion::AQuaternion(const AQuaternion& s)
    \brief Copy constructor

    \fn AQuaternion::AQuaternion(const AScalar& r, const AScalar& i, const AScalar& j, const AScalar& k)
    \brief Construct from four AScalars

    \fn AQuaternion::AQuaternion(float r, float i, float j, float k)
    \brief Construct from four floats

    \fn AScalar AQuaternion::r()
    \brief Returns real part

    \fn AScalar AQuaternion::i()
    \brief Returns first imaginary part

    \fn AScalar AQuaternion::j()
    \brief Returns second imaginary part

    \fn AScalar AQuaternion::k()
    \brief Returns third imaginary part

    \fn AQuaternion& AQuaternion::set_r(const AScalar& a)
    \brief Sets real part

    \fn AQuaternion& AQuaternion::set_i(const AScalar& a)
    \brief Sets first imaginary part

    \fn AQuaternion& AQuaternion::set_j(const AScalar& a)
    \brief Sets second imaginary part

    \fn AQuaternion& AQuaternion::set_k(const AScalar& a)
    \brief Sets third imaginary part

    \fn AQuaternion AQuaternion::conj()
    \brief Returns quaternion conjugate

    \fn AQuaternion AQuaternion::mul_conj(const AQuaternion& y)
    \brief Returns *this * y.conj()

    \fn AScalar AQuaternion::dot(const AQuaternion& y)
    \brief Returns real part of *this * y.conj()

    \fn AScalar AQuaternion::norm_sq()
    \brief Returns r()**2 + i()**2 + j()**2 + k()**2

    \fn AScalar AQuaternion::norm()
    \brief Returns sqrt(r()**2 + i()**2 + j()**2 + k()**2)

    \fn AQuaternion AQuaternion::inverse()
    \brief Returns 1.0 / *this

    \fn AQuaternion& AQuaternion::normalize()
    \brief Returns *this *= 1.0 / sqrt(r()**2 + i()**2 + j()**2 + k()**2)
*/

/** \class PQuaternion
    \brief Abstract pointer to an AQuaternion

    \fn PQuaternion::PQuaternion(void* p)
    \brief Constructor

    \fn AQuaternion* PQuaternion::operator->()
    \brief Dereference

    \fn AQuaternion& PQuaternion::operator[] (int i)
    \brief Array reference
*/

/** \class PConstQuaternion
    \brief Abstract pointer to a const AQuaternion

    \fn PConstQuaternion::PConstQuaternion(const void* p)
    \brief Constructor

    \fn const AQuaternion* PQuaternion::operator->()
    \brief Dereference

    \fn const AQuaternion& PConstQuaternion::operator[] (int i)
    \brief Array reference
*/
