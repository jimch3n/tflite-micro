/************************************************************************//**
 * @file    AVL/Hemi/ATriple.h
 *
 * @brief   ATriple wrapper for two vr64s on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ATRIPLE_H
#define ATRIPLE_H

#include "AScalar.h"

struct ATriple
{
    vr64 vr0;
    vr64 vr1;

    _AI ATriple() {}
    _AI ATriple(const ATriple& x) : vr0(x.vr0), vr1(x.vr1) {}

    _AI ATriple& operator= (const ATriple& x) {
        vr0 = x.vr0;
        vr1 = x.vr1;
        return *this;
    }

    _AI static int length() {return 3;}
    _AI static ATriple Zero() {ATriple z; z.vr0 = z.vr1 = vseta_vr(0, 0); return z;}

    _AI const AScalar operator[] (int i) const {
        vr64 V_src = vr64_pair(get_VRL(vr1),
                               move32_fr_vr_idx(vr0, i));
        return move32_fr_vr_idx(V_src, i >> 1);
    }

    _AI bool operator== (const ATriple& x) const {
        return !(move_ar_bbr(vne(vr0, x.vr0)) | ne_fr(get_VRL(vr1), get_VRL(x.vr1)));
    }
    _AI bool operator!= (const ATriple& x) const {
        return !(*this == x);
    }

    _AI ATriple& fill(const AScalar& x) {vr0 = vr1 = vreplicate_fr(x.fr); return *this;}
    _AI ATriple& copy(const ATriple& x) {*this = x; return *this;}

    _AI ATriple& add(const ATriple& x) {
        vr0 = vadds(vr0, x.vr0, 0);
        vr1 = vadds(vr1, x.vr1, 0);
        return *this;
    }
    _AI ATriple& sub(const ATriple& x) {
        vr0 = vadds(vr0, x.vr0, 10);
        vr1 = vadds(vr1, x.vr1, 10);
        return *this;
    }
    _AI ATriple& mul(const ATriple& x) {
        vr0 = vmuls(vr0, x.vr0, 0);
        vr1 = vmuls(vr1, x.vr1, 0);
        return *this;
    }
    _AI ATriple& div(const ATriple& x) {
        // One iteration of Newton's method
        vr64 V_2 = vseta_vr(2, 0);
        vr64 V_inv, V_dst;
        V_inv = vr64_pair(inv(get_VRH(x.vr0)), inv(get_VRL(x.vr0)));
        V_dst = vmuls(V_inv, vmacs(V_2, V_inv, x.vr0, 3, 0), 0);
        vr0 = vmuls(vr0, V_dst, 0);
        set_VRL(V_inv, inv(get_VRL(x.vr1)));
        V_dst = vmuls(V_inv, vmacs(V_2, V_inv, x.vr1, 3, 0), 0);
        vr1 = vmuls(vr1, V_dst, 0);
        return *this;
    }

    _AI ATriple& mul_acc(const ATriple& x, const ATriple& y) {
        vr0 = vmacs(vr0, x.vr0, y.vr0, 0, 0);
        vr1 = vmacs(vr1, x.vr1, y.vr1, 0, 0);
        return *this;
    }
    _AI ATriple& mul_acc(const ATriple& x, const AScalar& y) {
        vr0 = vmacf(vr0, x.vr0, y.fr, 0, 0);
        vr1 = vmacf(vr1, x.vr1, y.fr, 0, 0);
        return *this;
    }

    _AI ATriple& add(const AScalar& x) {
        vr64 V_src = vreplicate_fr(x.fr);
        vr0 = vadds(vr0, V_src, 0);
        vr1 = vadds(vr1, V_src, 0);
        return *this;
    }
    _AI ATriple& sub(const AScalar& x) {
        vr64 V_src = vreplicate_fr(x.fr);
        vr0 = vadds(vr0, V_src, 10);
        vr1 = vadds(vr1, V_src, 10);
        return *this;
    }
    _AI ATriple& mul(const AScalar& x) {
        vr0 = vmulf(vr0, x.fr, 0);
        vr1 = vmulf(vr1, x.fr, 0);
        return *this;
    }
    _AI ATriple& div(const AScalar& x) {
        return mul(x.inverse());
    }

    _AI ATriple& abs() {
        vr0 = vabs(vr0);
        vr1 = vabs(vr1);
        return *this;
    }
    _AI ATriple& max(const ATriple& x) {
        vr0 = vmax(vr0, x.vr0);
        vr1 = vmax(vr1, x.vr1);
        return *this;
    }
    _AI ATriple& min(const ATriple& x) {
        vr0 = vmin(vr0, x.vr0);
        vr1 = vmin(vr1, x.vr1);
        return *this;
    }

    _AI ATriple& clamp(const AScalar& low, const AScalar& high) {
        vr64 V_low = vreplicate_fr(low.fr);
        vr64 V_high= vreplicate_fr(high.fr);
        vr0 = vmin(vmax(vr0, V_low), V_high);
        vr1 = vmin(vmax(vr1, V_low), V_high);
        return *this;
    }

    _AI AScalar sum() const {
        return get_VRL(vsum_perm(vr1, vr0, vr0, VSEL_ZERO, VSEL_YH_XL, 0, 0));
    }

    _AI AScalar dot(const ATriple& x) const {
        vr64 V_dst = vblend(vr0, x.vr0, VB_ZERO, VB_YHXH_YLXL, 0, 0);
        return fmacs(get_VRL(V_dst), get_VRL(vr1), get_VRL(x.vr1), 0);
    }

    _AI AScalar max_abs() const {
        vr64 V_dst = vabs(vr1);
        fr32 F_dst;
        unsigned int ar;
        mir18 mir;
        vmaxmin_init(V_dst,V_dst,mir);

        seta_vr(V_dst, 2, 0, 0);
        V_dst = vmax(vabs(vr0), V_dst);
        rmax_idx(ar, F_dst, V_dst, mir);
	ar = ar + 1; // Temporary fix for 'unused-but-set-variable' warning
        return F_dst;
    }

    _AI AScalar sum_sq() const {return dot(*this);}
    _AI AScalar norm()   const {return sum_sq().f_sqrt();}
    _AI ATriple& normalize()   {return mul(sum_sq().f_invsqrt());}

    //
    // Additional methods not in AVector<N>
    //

    _AI ATriple(const AScalar& x, const AScalar& y, const AScalar& z) {
        vr0 = vr64_pair(y.fr, x.fr);
        set_VRL(vr1, z.fr);
    }
    _AI ATriple(float x, float y, float z) {
        move32_vr_ar(vr0, VRQ0, *(int*) &x);
        move32_vr_ar(vr0, VRQ1, *(int*) &y);
        convert_IEEE_float_to_32F_x2(vr0);
        move32_vr_ar(vr1, VRQ0, *(int*) &z);
        convert_IEEE_float_to_32F_x2(vr1);
    }

    _AI ATriple operator* (const ATriple& x) const {
        ATriple z;
        z.vr0 = vmuls(vr0, x.vr0, 0);
        z.vr1 = vmuls(vr1, x.vr1, 0);
        return z;
    }
    _AI ATriple operator+ (const ATriple& x) const {
        ATriple z;
        z.vr0 = vadds(vr0, x.vr0, 0);
        z.vr1 = vadds(vr1, x.vr1, 0);
        return z;
    }
    _AI ATriple operator- (const ATriple& x) const {
        ATriple z;
        z.vr0 = vadds(vr0, x.vr0, 10);
        z.vr1 = vadds(vr1, x.vr1, 10);
        return z;
    }
    _AI ATriple operator- () const {
        ATriple z;
        z.vr0 = s_vneg(vr0);
        z.vr1 = s_vneg(vr1);
        return z;
    }

    _AI ATriple& operator*= (const ATriple& x) {
        vr0 = vmuls(vr0, x.vr0, 0);
        vr1 = vmuls(vr1, x.vr1, 0);
        return *this;
    }
    _AI ATriple& operator+= (const ATriple& x) {
        vr0 = vadds(vr0, x.vr0, 0);
        vr1 = vadds(vr1, x.vr1, 0);
        return *this;
    }
    _AI ATriple& operator-= (const ATriple& x) {
        vr0 = vadds(vr0, x.vr0, 10);
        vr1 = vadds(vr1, x.vr1, 10);
        return *this;
    }

    _AI ATriple operator* (const AScalar& x) const {
        ATriple z;
        z.vr0 = vmuls(vr0, vreplicate_fr(x.fr), 0);
        z.vr1 = vmuls(vr1, vreplicate_fr(x.fr), 0);
        return z;
    }
    _AI ATriple& operator*= (const AScalar& x) {
        vr0 = vmuls(vr0, vreplicate_fr(x.fr), 0);
        vr1 = vmuls(vr1, vreplicate_fr(x.fr), 0);
        return *this;
    }

    _AI ATriple mul_add(const ATriple& x, const ATriple& y) const {
        ATriple z;
        z.vr0 = vmacs(vr0, x.vr0, y.vr0,  0, 0);
        z.vr1 = vmacs(vr1, x.vr1, y.vr1,  0, 0);
        return z;
    }
    _AI ATriple mul_sub(const ATriple& x, const ATriple& y) const {
        ATriple z;
        z.vr0 = vmacs(vr0, x.vr0, y.vr0,  3, 0);
        z.vr1 = vmacs(vr1, x.vr1, y.vr1,  3, 0);
        return z;
    }
    _AI AScalar x() const {return get_VRL(vr0);}
    _AI AScalar y() const {return get_VRH(vr0);}
    _AI AScalar z() const {return get_VRL(vr1);}

    _AI ATriple& set_x(const AScalar& a) {set_VRL(vr0, a.fr); return *this;}
    _AI ATriple& set_y(const AScalar& a) {set_VRH(vr0, a.fr); return *this;}
    _AI ATriple& set_z(const AScalar& a) {set_VRL(vr1, a.fr); return *this;}
};

_AI ATriple AScalar::operator* (const ATriple& x) const {
    ATriple z;
    z.vr0 = vmulf(x.vr0, fr, 0);
    z.vr1 = vmulf(x.vr1, fr, 0);
    return z;
}

#endif
