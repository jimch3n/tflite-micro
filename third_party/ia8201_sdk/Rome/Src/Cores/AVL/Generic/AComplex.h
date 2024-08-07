////////////////////////////////////////////////////////////////////////////////
///
/// \file AComplex.h
///
/// AComplex wrapper for std::complex<float>
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ACOMPLEX_H
#define ACOMPLEX_H

#include <complex>

#include "AScalar.h"

struct AComplex
{
    std::complex<float> vr;

    _AI AComplex() {}
    _AI AComplex(const AComplex& a)                  : vr(a.vr)       {}
    _AI AComplex(const std::complex<float>& a)       : vr(a)          {}
    _AI AComplex(const AScalar& r)                   : vr(r.fr, 0)    {}
    _AI AComplex(const AScalar& r, const AScalar& i) : vr(r.fr, i.fr) {}
    _AI AComplex(float r, float i)                   : vr(r, i)       {}

    _AI static AComplex Zero() {return std::complex<float>(0, 0);}
    _AI static AComplex One()  {return std::complex<float>(1, 0);}
    _AI static AComplex I()    {return std::complex<float>(0, 1);}

    _AI bool operator== (const AComplex& x) const {return vr == x.vr;}
    _AI bool operator!= (const AComplex& x) const {return vr != x.vr;}

    _AI AComplex operator+ (const AComplex& x) const {return vr + x.vr;}
    _AI AComplex operator- (const AComplex& x) const {return vr - x.vr;}
    _AI AComplex operator- ()                  const {return -vr;}
    _AI AComplex operator* (const AComplex& x) const {return vr * x.vr;}
    _AI AComplex operator* (const AScalar& x)  const {return vr * x.fr;}
    _AI AComplex operator/ (const AComplex& x) const {return vr / x.vr;}

    _AI AComplex& operator+= (const AComplex& x) {return (*this = *this + x);}
    _AI AComplex& operator-= (const AComplex& x) {return (*this = *this - x);}
    _AI AComplex& operator*= (const AComplex& x) {return (*this = *this * x);}
    _AI AComplex& operator*= (const AScalar& x)  {return (*this = *this * x);}
    _AI AComplex& operator/= (const AComplex& x) {return (*this = *this / x);}

    _AI AComplex mul_add(const AComplex& x, const AComplex& y) const {
        return vr + x.vr * y.vr;
    }
    _AI AComplex mul_sub(const AComplex& x, const AComplex& y) const {
        return vr - x.vr * y.vr;
    }
    _AI AComplex& mul_acc(const AComplex& x, const AComplex& y) {
        vr += x.vr * y.vr;
        return *this;
    }

    _AI AScalar r() const {return vr.real();}
    _AI AScalar i() const {return vr.imag();}

    _AI AComplex& set_r(const AScalar& a) {
        vr = std::complex<float>(a.fr, vr.imag());
        return *this;
    }
    _AI AComplex& set_i(const AScalar& a) {
        vr = std::complex<float>(vr.real(), a.fr);
        return *this;
    }

    _AI AComplex conj() const {return std::conj(vr);}
    _AI AComplex mul_conj(const AComplex& y) const {return vr * std::conj(y.vr);}
    _AI AComplex mul_conj_add(const AComplex& x, const AComplex& y) const {
        return vr + x.vr * std::conj(y.vr);
    }
    _AI AComplex mul_conj_sub(const AComplex& x, const AComplex& y) const {
        return vr - x.vr * std::conj(y.vr);
    }
    _AI AComplex& mul_conj_acc(const AComplex& x, const AComplex& y) {
        vr += x.vr * std::conj(y.vr);
        return *this;
    }

    _AI AScalar dot(const AComplex& y) const {return mul_conj(y).r();}

    _AI AScalar   norm_sq() const {return r()*r() + i()*i();}
    _AI AScalar   norm()    const {return std::abs(vr);}
    _AI AComplex  inverse() const {return conj() * norm_sq().inverse();}

    _AI AComplex& normalize() {return (*this = *this * norm_sq().f_invsqrt());}
};

_AI AComplex AScalar::operator* (const struct AComplex& x) const {
    return x.vr * fr;
}

//
// Pointer to AComplex
//

struct PComplex
{
    AComplex* ptr;

    _AI PComplex(void* p) : ptr((AComplex*) p) {}

    _AI operator AComplex*() const {return  ptr;}
    _AI AComplex* operator->() const {return ptr;}
    _AI AComplex& operator[] (int i) const {return ptr[i];}

    _AI PComplex  operator+ (int index) const {return PComplex(ptr + index);}
    _AI PComplex  operator- (int index) const {return PComplex(ptr - index);}

    _AI PComplex& operator+= (int index) {ptr += index; return *this;}
    _AI PComplex& operator-= (int index) {ptr -= index; return *this;}

    _AI PComplex& operator++ ()    {++ptr; return *this;}
    _AI PComplex& operator-- ()    {--ptr; return *this;}
    _AI PComplex  operator++ (int) {PComplex p(*this); ++ptr; return p;}
    _AI PComplex  operator-- (int) {PComplex p(*this); --ptr; return p;}
};

struct PConstComplex
{
    const AComplex* ptr;

    _AI PConstComplex(const void* p) : ptr((const AComplex*) p) {}

    _AI operator const AComplex*() const {return ptr;}
    _AI const AComplex* operator->() const {return ptr;}
    _AI const AComplex& operator[] (int i) const {return ptr[i];}

    _AI PConstComplex  operator+ (int index) const {return PConstComplex(ptr + index);}
    _AI PConstComplex  operator- (int index) const {return PConstComplex(ptr - index);}

    _AI PConstComplex& operator+= (int index) {ptr += index; return *this;}
    _AI PConstComplex& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstComplex& operator++ ()    {++ptr; return *this;}
    _AI PConstComplex& operator-- ()    {--ptr; return *this;}
    _AI PConstComplex  operator++ (int) {PConstComplex p(*this); ++ptr; return p;}
    _AI PConstComplex  operator-- (int) {PConstComplex p(*this); --ptr; return p;}
};

#endif

/** \class AComplex
    \brief Wrapper for a vr64, vr128, or std::complex<float>

    \fn AComplex::AComplex(const AComplex& s)
    \brief Copy constructor

    \fn AComplex::AComplex(const AScalar& r)
    \brief Construct from an AScalar

    \fn AComplex::AComplex(const AScalar& r, const AScalar& i)
    \brief Construct from two AScalars

    \fn AComplex::AComplex(float r, float i)
    \brief Construct from two floats

    \fn static AComplex AComplex::Zero()
    \brief Returns (0.0 + 0.0i)

    \fn static AComplex AComplex::One()
    \brief Returns (1.0 + 0.0i)

    \fn static AComplex AComplex::I()
    \brief Returns (0.0 + 1.0i)

    \fn AComplex AComplex::mul_add(const AComplex& x, const AComplex& y)
    \brief Return *this + x * y

    \fn AComplex AComplex::mul_sub(const AComplex& x, const AComplex& y)
    \brief Return *this - x * y

    \fn AComplex& AComplex::mul_acc(const AComplex& x, const AComplex& y)
    \brief Return *this += x * y

    \fn AScalar AComplex::r()
    \brief Returns real part

    \fn AScalar AComplex::i()
    \brief Returns imaginary part

    \fn AComplex& AComplex::set_r(const AScalar& a)
    \brief Sets real part

    \fn AComplex& AComplex::set_i(const AScalar& a)
    \brief Sets imaginary part

    \fn AComplex AComplex::conj()
    \brief Returns complex conjugate

    \fn AComplex AComplex::mul_conj(const AComplex& y)
    \brief Returns *this * y.conj()

    \fn AComplex AComplex::mul_conj_add(const AComplex& x, const AComplex& y)
    \brief Return *this + x * y.conj()

    \fn AComplex AComplex::mul_conj_sub(const AComplex& x, const AComplex& y)
    \brief Return *this - x * y.conj()

    \fn AComplex& AComplex::mul_conj_acc(const AComplex& x, const AComplex& y)
    \brief Return *this += x * y.conj()

    \fn AScalar AComplex::dot(const AComplex& y)
    \brief Returns real part of *this * y.conj()

    \fn AScalar AComplex::norm_sq()
    \brief Returns r()**2 + i()**2

    \fn AScalar AComplex::norm()
    \brief Returns sqrt(r()**2 + i()**2)

    \fn AComplex AComplex::inverse()
    \brief Returns 1.0 / *this

    \fn AComplex& AComplex::normalize()
    \brief Returns *this *= 1.0 / sqrt(r()**2 + i()**2)
*/

/** \class PComplex
    \brief Abstract pointer to an AComplex

    \fn PComplex::PComplex(void* p)
    \brief Constructor

    \fn AComplex* PComplex::operator->()
    \brief Dereference

    \fn AComplex& PComplex::operator[] (int i)
    \brief Array reference
*/

/** \class PConstComplex
    \brief Abstract pointer to a const AComplex

    \fn PConstComplex::PConstComplex(const void* p)
    \brief Constructor

    \fn const AComplex* PComplex::operator->()
    \brief Dereference

    \fn const AComplex& PConstComplex::operator[] (int i)
    \brief Array reference
*/
