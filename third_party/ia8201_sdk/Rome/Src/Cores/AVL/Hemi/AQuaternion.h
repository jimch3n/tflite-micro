/************************************************************************//**
 * @file    AVL/Hemi/AQuaternion.h
 *
 * @brief   AQuaternion wrapper for vr64 on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef AQUATERNION_H
#define AQUATERNION_H

#include "AScalar.h"

struct AQuaternion
{
    vr64 vr0;
    vr64 vr1;

    _AI AQuaternion() {}
    _AI AQuaternion(const AQuaternion& a) {vr0 = a.vr0; vr1 = a.vr1;}

    _AI AQuaternion& operator= (const AQuaternion& x) {vr0 = x.vr0; vr1 = x.vr1; return *this;}

    _AI AQuaternion(const AScalar& r, const AScalar& i, const AScalar& j, const AScalar& k) {
        vr0 = vr64_pair(i.fr, r.fr);
        vr1 = vr64_pair(k.fr, j.fr);
    }
    _AI AQuaternion(float r, float i, float j, float k) {
        move32_vr_ar(vr0, VRQ0, *(int*) &r);
        move32_vr_ar(vr0, VRQ1, *(int*) &i);
        convert_IEEE_float_to_32F_x2(vr0);
        move32_vr_ar(vr1, VRQ0, *(int*) &j);
        move32_vr_ar(vr1, VRQ1, *(int*) &k);
        convert_IEEE_float_to_32F_x2(vr1);
    }

    _AI bool operator== (const AQuaternion& x) const {
        return !move_ar_bbr(orb2(vne(vr0, x.vr0), vne(vr1, x.vr1)));
    }
    _AI bool operator!= (const AQuaternion& x) const {
        return !(*this == x);
    }

    _AI AQuaternion operator* (const AQuaternion& y) const {
        AQuaternion z;
        z.vr0 = cmul(vr0, y.vr0, CONJ_NONE);
        z.vr1 = cmul(vr0, y.vr1, CONJ_NONE);
        z.vr0 = vblend_add(z.vr0, vr1, y.vr1, VB_YHXL_YLXH, VB_YHXH_YLXL, 7, 0, 0, 0);
        z.vr1 = vblend_add(z.vr1, vr1, y.vr0, VB_YHXL_YLXH, VB_YHXH_YLXL, 8, 0, 0, 0);
        return z;
    }
    _AI AQuaternion operator+ (const AQuaternion& x) const {
        AQuaternion z;
        z.vr0 = vadds(vr0, x.vr0, 0);
        z.vr1 = vadds(vr1, x.vr1, 0);
        return z;
    }
    _AI AQuaternion operator- (const AQuaternion& x) const {
        AQuaternion z;
        z.vr0 = vadds(vr0, x.vr0, 10);
        z.vr1 = vadds(vr1, x.vr1, 10);
        return z;
    }
    _AI AQuaternion operator- () const {
        AQuaternion z;
        z.vr0 = s_vneg(vr0);
        z.vr1 = s_vneg(vr1);
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
        z.vr0 = vmulf(vr0, x.fr, 0);
        z.vr1 = vmulf(vr1, x.fr, 0);
        return z;
    }
    _AI AQuaternion& operator*= (const AScalar& x) {
        vr0 = vmulf(vr0, x.fr, 0);
        vr1 = vmulf(vr1, x.fr, 0);
        return *this;
    }

    _AI AScalar r() const {return get_VRL(vr0);}
    _AI AScalar i() const {return get_VRH(vr0);}
    _AI AScalar j() const {return get_VRL(vr1);}
    _AI AScalar k() const {return get_VRH(vr1);}

    _AI AQuaternion& set_r(const AScalar& a) {set_VRL(vr0, a.fr); return *this;}
    _AI AQuaternion& set_i(const AScalar& a) {set_VRH(vr0, a.fr); return *this;}
    _AI AQuaternion& set_j(const AScalar& a) {set_VRL(vr1, a.fr); return *this;}
    _AI AQuaternion& set_k(const AScalar& a) {set_VRH(vr1, a.fr); return *this;}

    _AI AScalar dot(const AQuaternion& x) const {
        vr64 z = cmul(vr0, x.vr0, CONJ_Y);
        return get_VRL(cmac(z, vr1, x.vr1, CONJ_Y));
    }

    _AI AQuaternion conj() const {
        AQuaternion z;
        z.vr0 = vr64_pair(neg_fr(get_VRH(vr0)), get_VRL(vr0));
        z.vr1 = s_vneg(vr1);
        return z;
    }

    _AI AQuaternion mul_conj(const AQuaternion& y) const {
        AQuaternion z;
        z.vr0 = cmul(             vr0, y.vr0, CONJ_Y);
        z.vr1 = vblend(           vr0, y.vr1, VB_YHXL_YLXH, VB_YHXH_YLXL, 13, 0);
        z.vr0 = vblend_add(z.vr0, vr1, y.vr1, VB_YHXL_YLXH, VB_YHXH_YLXL,  8, 0, 0, 0);
        z.vr1 = vblend_add(z.vr1, vr1, y.vr0, VB_YHXL_YLXH, VB_YHXH_YLXL,  2, 0, 0, 0);
        return z;
    }

    _AI AScalar     norm_sq() const {return dot(*this);}
    _AI AScalar     norm()    const {return norm_sq().f_sqrt();}
    _AI AQuaternion inverse() const {return conj() * norm_sq().inverse();}

    _AI AQuaternion& normalize() {return (*this = *this * norm_sq().f_invsqrt());}
};

_AI AQuaternion AScalar::operator* (const AQuaternion& x) const {
    AQuaternion z;
    z.vr0 = vmulf(x.vr0, fr, 0);
    z.vr1 = vmulf(x.vr1, fr, 0);
    return z;
}

_AI AQuaternion nLerp(const AQuaternion& x, const AQuaternion& y, const AScalar& t)
{
    AQuaternion z;
    vr64 oneMinusT = vreplicate_fr(fadds(seta_fr(1, 0), t.fr, 2));

    z.vr0 = vmulf(y.vr0, t.fr, 0);
    z.vr1 = vmulf(y.vr1, t.fr, 0);
    z.vr0 = vmacs(z.vr0, x.vr0, oneMinusT, 0, 0);
    z.vr1 = vmacs(z.vr1, x.vr1, oneMinusT, 0, 0);

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

#endif
