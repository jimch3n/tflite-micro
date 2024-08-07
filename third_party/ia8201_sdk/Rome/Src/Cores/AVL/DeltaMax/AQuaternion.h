/************************************************************************//**
 * @file    AVL\DeltaMax\AQuaternion.h
 *
 * @brief   AQuaternion wrapper for vr128 on DeltaMax
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef AQUATERNION_H
#define AQUATERNION_H

/**************************************************************************//**
 * @addtogroup dmx_avl
 * @{
 *****************************************************************************/

#include "AScalar.h"

struct AQuaternion
{
    vr128 vr;

    _AI AQuaternion() {}
    _AI AQuaternion(const vr128& a) : vr(a) {}
    _AI AQuaternion(const AQuaternion& a) : vr(a.vr) {}
    _AI AQuaternion(const AScalar& r, const AScalar& i, const AScalar& j, const AScalar& k) {
        set_VRQ0(vr, r.fr);
        set_VRQ1(vr, i.fr);
        set_VRQ2(vr, j.fr);
        set_VRQ3(vr, k.fr);
    }
    _AI AQuaternion(float r, float i, float j, float k) {
        replicate_ar(vr, 1, *(int*) &r);
        replicate_ar(vr, 2, *(int*) &i);
        replicate_ar(vr, 4, *(int*) &j);
        replicate_ar(vr, 8, *(int*) &k);
        convert_IEEE_float_to_32F_x4(vr);
    }

    _AI operator vr128() const {return vr;}
    _AI AQuaternion& operator= (const vr128& a)       {vr = a; return *this;}
    _AI AQuaternion& operator= (const AQuaternion& x) {vr = x.vr; return *this;}

    _AI xtbool operator== (const AQuaternion& x) const {return XT_ALL4(veq(vr, x.vr));}
    _AI xtbool operator!= (const AQuaternion& x) const {return XT_ANY4(vne(vr, x.vr));}

    _AI AQuaternion operator* (const AQuaternion& x) const {
        AQuaternion z(qmul_1(vr, x.vr, CONJ_NONE));
        qmul_2(z.vr, vr, x.vr, CONJ_NONE);
        return z;
    }
    _AI AQuaternion operator+ (const AQuaternion& x) const {return vadds(vr, x.vr, 0);}
    _AI AQuaternion operator- (const AQuaternion& x) const {return vadds(vr, x.vr, 0xf0);}
    _AI AQuaternion operator- ()                     const {return s_vnegs(vr, 0xf);}
    _AI AQuaternion operator/ (const AQuaternion& x) const {return *this * x.inverse();}

    _AI AQuaternion& operator*= (const AQuaternion& x) {return (*this = *this * x);}
    _AI AQuaternion& operator/= (const AQuaternion& x) {return (*this = *this / x);}
    _AI AQuaternion& operator+= (const AQuaternion& x) {return (*this = *this + x);}
    _AI AQuaternion& operator-= (const AQuaternion& x) {return (*this = *this - x);}

    _AI AQuaternion operator* (const AScalar& x) const {
        return vmuls(vr, vreplicate_fr(x.fr), 0);
    }
    _AI AQuaternion& operator*= (const AScalar& x) {
        vr = vmuls(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }

    _AI AScalar r() const {return get_VRQ0(vr);}
    _AI AScalar i() const {return get_VRQ1(vr);}
    _AI AScalar j() const {return get_VRQ2(vr);}
    _AI AScalar k() const {return get_VRQ3(vr);}

    _AI AQuaternion& set_r(const AScalar& a) {set_VRQ0(vr, a.fr); return *this;}
    _AI AQuaternion& set_i(const AScalar& a) {set_VRQ1(vr, a.fr); return *this;}
    _AI AQuaternion& set_j(const AScalar& a) {set_VRQ2(vr, a.fr); return *this;}
    _AI AQuaternion& set_k(const AScalar& a) {set_VRQ3(vr, a.fr); return *this;}

    _AI AScalar dot(const AQuaternion& x) const {
        fr32 z = fpmul_sum3(vr, x.vr, 0, set_perm16(0x05af));
        fpmac(z, get_VRQ0(vr), get_VRQ0(x.vr), 0);
        return z;
    }

    _AI AQuaternion conj() const {
        return s_vnegs(vr, 14);
    }

    _AI AQuaternion mul_conj(const AQuaternion& y) const {
        AQuaternion z(qmul_1(vr, y.vr, CONJ_Y));
        qmul_2(z.vr, vr, y.vr, CONJ_Y);
        return z;
    }

    _AI AScalar     norm_sq() const {return dot(*this);}
    _AI AScalar     norm()    const {return norm_sq().f_sqrt();}
    _AI AQuaternion inverse() const {return conj() * norm_sq().inverse();}

    _AI AQuaternion& normalize() {return (*this = *this * norm_sq().f_invsqrt());}
};

_AI AQuaternion AScalar::operator* (const struct AQuaternion& x) const {
    return vmuls(x.vr, vreplicate_fr(fr), 0);
}

_AI AQuaternion nLerp(const AQuaternion& x, const AQuaternion& y, const AScalar& t)
{
    AQuaternion z(vreplicate_fr(t.fr));
    z = vinterp_x2(y.vr, x.vr, move32_wr_vr(z.vr, VRQ0));

    // return (1-t)*x + t*y normalized
    return z.normalize();
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

/**************************************************************************//**
 * @}
 *****************************************************************************/

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
