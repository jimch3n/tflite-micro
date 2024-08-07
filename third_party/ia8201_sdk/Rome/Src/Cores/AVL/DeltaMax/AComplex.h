/************************************************************************//**
 * @file    AVL\DeltaMax\AComplex.h
 *
 * @brief   AComplex wrapper for two fr32s on DeltaMax
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEX_H
#define ACOMPLEX_H

/**************************************************************************//**
 * @addtogroup dmx_avl
 * @{
 *****************************************************************************/

#include "AScalar.h"

struct AComplex
{
    VAR_ALIGN_8

    fr32 fr0;
    fr32 fr1;

    _AI AComplex() {}
    _AI AComplex(const AComplex& a) : fr0(a.fr0), fr1(a.fr1) {}
    _AI AComplex(const AScalar& r)  : fr0(r.fr), fr1(seta_fr(0, 0, 0)) {}
    _AI AComplex(const AScalar& r, const AScalar& i) : fr0(r.fr), fr1(i.fr) {}

    _AI AComplex(float r, float i) {
        fr0 = convert_IEEE_float_to_32F(*(int*) &r);
        fr1 = convert_IEEE_float_to_32F(*(int*) &i);
    }

    _AI AScalar r() const {return fr0;}
    _AI AScalar i() const {return fr1;}

    _AI AComplex& set_r(const AScalar& a) {fr0 = a.fr; return *this;}
    _AI AComplex& set_i(const AScalar& a) {fr1 = a.fr; return *this;}

    _AI static AComplex Zero() {
        AComplex z;
        z.fr0 = seta_fr(0, 0, 0);
        z.fr1 = seta_fr(0, 0, 0);
        return z;
    }
    _AI static AComplex One() {
        AComplex z;
        z.fr0 = seta_fr(1, 0, 0);
        z.fr1 = seta_fr(0, 0, 0);
        return z;
    }
    _AI static AComplex I() {
        AComplex z;
        z.fr0 = seta_fr(0, 0, 0);
        z.fr1 = seta_fr(1, 0, 0);
        return z;
    }

    _AI xtbool operator== (const AComplex& x) const {
        return andb1(eq_fr(fr0, x.fr0), eq_fr(fr1, x.fr1));
    }
    _AI xtbool operator!= (const AComplex& x) const {
        return orb1(ne_fr(fr0, x.fr0), ne_fr(fr1, x.fr1));
    }

    _AI AComplex operator+ (const AComplex& x) const {
        AComplex z;
        z.fr0 = fpadd(fr0, x.fr0, 0);
        z.fr1 = fpadd(fr1, x.fr1, 0);
        return z;
    }
    _AI AComplex operator- (const AComplex& x) const {
        AComplex z;
        z.fr0 = fpadd(fr0, x.fr0, 2);
        z.fr1 = fpadd(fr1, x.fr1, 2);
        return z;
    }
    _AI AComplex operator* (const AComplex& x) const {
        AComplex z;
        z.fr0 = fpmul(fr0, x.fr0, 0);
        z.fr1 = fpmul(fr0, x.fr1, 0);
        fpmac(z.fr0, fr1, x.fr1, 1);
        fpmac(z.fr1, fr1, x.fr0, 0);
        return z;
    }
    _AI AComplex operator* (const AScalar& x) const {
        AComplex z;
        z.fr0 = fpmul(fr0, x.fr, 0);
        z.fr1 = fpmul(fr1, x.fr, 0);
        return z;
    }
    _AI AComplex operator- () const {
        AComplex z;
        z.fr0 = neg_fr(fr0);
        z.fr1 = neg_fr(fr1);
        return z;
    }
    _AI AComplex operator/ (const AComplex& x) const {
        return *this * x.inverse();
    }

    _AI AComplex& operator+= (const AComplex& x) {return *this = *this + x;}
    _AI AComplex& operator-= (const AComplex& x) {return *this = *this - x;}
    _AI AComplex& operator*= (const AComplex& x) {return *this = *this * x;}
    _AI AComplex& operator/= (const AComplex& x) {return *this = *this / x;}
    _AI AComplex& operator*= (const AScalar& x)  {return *this = *this * x;}

    _AI AComplex mul_add(const AComplex& x, const AComplex& y) const {
        AComplex z;
        z.fr0 = fpmul(x.fr0, y.fr0, 0);
        z.fr1 = fpmul(x.fr0, y.fr1, 0);
        fpmac(z.fr0, x.fr1, y.fr1, 1);
        fpmac(z.fr1, x.fr1, y.fr0, 0);
        z.fr0 = fpadd(z.fr0, fr0, 0);
        z.fr1 = fpadd(z.fr1, fr1, 0);
        return z;
    }
    _AI AComplex mul_sub(const AComplex& x, const AComplex& y) const {
        AComplex z;
        z.fr0 = fpmul(x.fr0, y.fr0, 0);
        z.fr1 = fpmul(x.fr0, y.fr1, 0);
        fpmac(z.fr0, x.fr1, y.fr1, 1);
        fpmac(z.fr1, x.fr1, y.fr0, 0);
        z.fr0 = fpadd(z.fr0, fr0, 1);
        z.fr1 = fpadd(z.fr1, fr1, 1);
        return z;
    }
    _AI AComplex& mul_acc(const AComplex& x, const AComplex& y) {
        fr32 tmp0, tmp1;
        tmp0 = fpmul(x.fr0, y.fr0, 0);
        tmp1 = fpmul(x.fr0, y.fr1, 0);
        fpmac(tmp0, x.fr1, y.fr1, 1);
        fpmac(tmp1, x.fr1, y.fr0, 0);
        fr0 = fpadd(tmp0, fr0, 0);
        fr1 = fpadd(tmp1, fr1, 0);
        return *this;
    }

    _AI AComplex conj() const {
        AComplex z;
        z.fr0 = fr0;
        z.fr1 = neg_fr(fr1);
        return z;
    }
    _AI AComplex mul_conj(const AComplex& y) const {
        AComplex z;
        z.fr0 = fpmul(fr0, y.fr0, 0);
        z.fr1 = fpmul(fr0, y.fr1, 1);
        fpmac(z.fr0, fr1, y.fr1, 0);
        fpmac(z.fr1, fr1, y.fr0, 0);
        return z;
    }
    _AI AComplex mul_conj_add(const AComplex& x, const AComplex& y) const {
        AComplex z;
        z.fr0 = fpmul(x.fr0, y.fr0, 0);
        z.fr1 = fpmul(x.fr0, y.fr1, 1);
        fpmac(z.fr0, x.fr1, y.fr1, 0);
        fpmac(z.fr1, x.fr1, y.fr0, 0);
        z.fr0 = fpadd(z.fr0, fr0, 0);
        z.fr1 = fpadd(z.fr1, fr1, 0);
        return z;
    }
    _AI AComplex mul_conj_sub(const AComplex& x, const AComplex& y) const {
        AComplex z;
        z.fr0 = fpmul(x.fr0, y.fr0, 0);
        z.fr1 = fpmul(x.fr0, y.fr1, 1);
        fpmac(z.fr0, x.fr1, y.fr1, 0);
        fpmac(z.fr1, x.fr1, y.fr0, 0);
        z.fr0 = fpadd(z.fr0, fr0, 1);
        z.fr1 = fpadd(z.fr1, fr1, 1);
        return z;
    }
    _AI AComplex& mul_conj_acc(const AComplex& x, const AComplex& y) {
        fr32 tmp0, tmp1;
        tmp0 = fpmul(x.fr0, y.fr0, 0);
        tmp1 = fpmul(x.fr0, y.fr1, 1);
        fpmac(tmp0, x.fr1, y.fr1, 0);
        fpmac(tmp1, x.fr1, y.fr0, 0);
        fr0 = fpadd(tmp0, fr0, 0);
        fr1 = fpadd(tmp1, fr1, 0);
        return *this;
    }

    _AI AScalar dot(const AComplex& y) const {
        fr32 z = fpmul(fr0, y.fr0, 0);
        fpmac(z, fr1, y.fr1, 0);
        return z;
    }
    _AI AScalar norm_sq() const  {return dot(*this);}
    _AI AScalar norm() const     {return norm_sq().f_sqrt();}
    _AI AComplex inverse() const {return conj() * norm_sq().inverse();}

    _AI AComplex& normalize() {return *this = *this * norm_sq().f_invsqrt();}
};

_AI AComplex AScalar::operator* (const struct AComplex& x) const {
    AComplex z;
    z.fr0 = fpmul(fr, x.fr0, 0);
    z.fr1 = fpmul(fr, x.fr1, 0);
    return z;
}

//
// Pointer to AComplex
//

struct PComplex
{
    AComplex* ptr;

    _AI PComplex(void* p) : ptr((AComplex*) p) {}

    _AI operator AComplex*() const {return ptr;}
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

/**************************************************************************//**
 * @}
 *****************************************************************************/

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
