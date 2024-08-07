/************************************************************************//**
 * @file    AVL/Hemi/AComplex.h
 *
 * @brief   AComplex wrapper for vr64 on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEX_H
#define ACOMPLEX_H

#include "AScalar.h"

struct AComplex;

struct AComplex
{
    vr64 vr;

    _AI AComplex() {}
    _AI AComplex(const AComplex& a) : vr(a.vr) {}
    _AI AComplex(const vr64& a)     : vr(a)    {}

    _AI operator vr64() const {return vr;}

    _AI AComplex(const AScalar& r, const AScalar& i = AScalar::Zero()) {
        set_VRL(vr, r.fr);
        set_VRH(vr, i.fr);
    }
    _AI AComplex(float r, float i) {
        move32_vr_ar(vr, VRQ0, *(int*) &r);
        move32_vr_ar(vr, VRQ1, *(int*) &i);
        convert_IEEE_float_to_32F_x2(vr);
    }

    _AI static AComplex Zero() {return vseta_vr(0, 0);}
    _AI static AComplex One() {vr64 z = vseta_vr(0, 0); seta_vr(z, 1, 1, 0); return z;}
    _AI static AComplex I()   {vr64 z = vseta_vr(0, 0); seta_vr(z, 2, 1, 0); return z;}

    _AI bool operator== (const AComplex& x) const {
        return !move_ar_bbr(vne(vr, x.vr));
    }
    _AI bool operator!= (const AComplex& x) const {
        return !(*this == x);
    }

    _AI AComplex operator+ (const AComplex& x) const {return vadds(vr, x.vr, 0);}
    _AI AComplex operator- (const AComplex& x) const {return vadds(vr, x.vr, 10);}
    _AI AComplex operator- ()                  const {return s_vneg(vr);}
    _AI AComplex operator* (const AComplex& x) const {return cmul(vr, x.vr, CONJ_NONE);}
    _AI AComplex operator* (const AScalar&  x) const {return vmulf(vr, x.fr, 0);}
    _AI AComplex operator/ (const AComplex& x) const {return *this * x.inverse();}

    _AI AComplex& operator+= (const AComplex& x) {return (*this = *this + x);}
    _AI AComplex& operator-= (const AComplex& x) {return (*this = *this - x);}
    _AI AComplex& operator*= (const AComplex& x) {return (*this = *this * x);}
    _AI AComplex& operator*= (const AScalar&  x) {return (*this = *this * x);}
    _AI AComplex& operator/= (const AComplex& x) {return (*this = *this / x);}

    _AI AComplex mul_add(const AComplex& x, const AComplex& y) const {
        return cmac(vr, x.vr, y.vr, CONJ_NONE);
    }
    _AI AComplex mul_sub(const AComplex& x, const AComplex& y) const {
        return cmas(vr, x.vr, y.vr, CONJ_NONE);
    }
    _AI AComplex& mul_acc(const AComplex& x, const AComplex& y) {
        vr = cmac(vr, x.vr, y.vr, CONJ_NONE);
        return *this;
    }

    _AI AScalar r() const {return get_VRL(vr);}
    _AI AScalar i() const {return get_VRH(vr);}

    _AI AComplex& set_r(const AScalar& a) {set_VRL(vr, a.fr); return *this;}
    _AI AComplex& set_i(const AScalar& a) {set_VRH(vr, a.fr); return *this;}

    _AI AComplex conj() const {return vr64_pair(neg_fr(get_VRH(vr)), get_VRL(vr));}
    _AI AComplex mul_conj(const AComplex& y) const {return cmul(vr, y.vr, CONJ_Y);}
    _AI AComplex mul_conj_add(const AComplex& x, const AComplex& y) const {
        return cmac(vr, x.vr, y.vr, CONJ_Y);
    }
    _AI AComplex mul_conj_sub(const AComplex& x, const AComplex& y) const {
        return cmas(vr, x.vr, y.vr, CONJ_Y);
    }
    _AI AComplex& mul_conj_acc(const AComplex& x, const AComplex& y) {
        vr = cmac(vr, x.vr, y.vr, CONJ_Y);
        return *this;
    }

    _AI AScalar dot(const AComplex& x) const {return get_VRL(cmul(vr, x.vr, CONJ_Y));}

    _AI AScalar   norm_sq() const {return dot(*this);}
    _AI AScalar   norm()    const {return norm_sq().f_sqrt();}
    _AI AComplex  inverse() const {return conj() * norm_sq().inverse();}

    _AI AComplex& normalize() {return (*this = *this * norm_sq().f_invsqrt());}
};

_AI AComplex AScalar::operator* (const AComplex& x) const {
    return vmulf(x.vr, fr, 0);
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

#endif
