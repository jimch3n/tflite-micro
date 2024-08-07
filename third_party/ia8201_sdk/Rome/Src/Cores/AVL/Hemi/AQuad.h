/************************************************************************//**
 * @file    AVL/Hemi/AQuad.h
 *
 * @brief   AQuad wrapper for two vr64s on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef AQUAD_H
#define AQUAD_H

#include "AComplex.h"

struct AQuad
{
    vr64 vr0;
    vr64 vr1;

    _AI AQuad() {}
    _AI AQuad(const AQuad& x) : vr0(x.vr0), vr1(x.vr1) {}

    _AI AQuad& operator= (const AQuad& x) {
        vr0 = x.vr0;
        vr1 = x.vr1;
        return *this;
    }

    _AI static int length() {return 4;}
    _AI static AQuad Zero() {AQuad z; z.vr0 = z.vr1 = vseta_vr(0, 0); return z;}

    _AI const AScalar operator[] (int i) const {
        vr64 V_src = vr64_pair(move32_fr_vr_idx(vr1, i),
                               move32_fr_vr_idx(vr0, i));
        return move32_fr_vr_idx(V_src, i >> 1);
    }

    _AI bool operator== (const AQuad& x) const {
        return !move_ar_bbr(orb2(vne(vr0, x.vr0), vne(vr1, x.vr1)));
    }
    _AI bool operator!= (const AQuad& x) const {
        return !(*this == x);
    }

    _AI AQuad& fill(const AScalar& x) {vr0 = vr1 = vreplicate_fr(x.fr); return *this;}
    _AI AQuad& copy(const AQuad& x)   {*this = x; return *this;}

    _AI AQuad& add(const AQuad& x) {
        vr0 = vadds(vr0, x.vr0, 0);
        vr1 = vadds(vr1, x.vr1, 0);
        return *this;
    }
    _AI AQuad& sub(const AQuad& x) {
        vr0 = vadds(vr0, x.vr0, 10);
        vr1 = vadds(vr1, x.vr1, 10);
        return *this;
    }
    _AI AQuad& mul(const AQuad& x) {
        vr0 = vmuls(vr0, x.vr0, 0);
        vr1 = vmuls(vr1, x.vr1, 0);
        return *this;
    }
    _AI AQuad& div(const AQuad& x) {
        // One iteration of Newton's method
        vr64 V_2 = vseta_vr(2, 0);
        vr64 V_inv, V_dst;
        V_inv = vr64_pair(inv(get_VRH(x.vr0)), inv(get_VRL(x.vr0)));
        V_dst = vmuls(V_inv, vmacs(V_2, V_inv, x.vr0, 3, 0), 0);
        vr0 = vmuls(vr0, V_dst, 0);
        V_inv = vr64_pair(inv(get_VRH(x.vr1)), inv(get_VRL(x.vr1)));
        V_dst = vmuls(V_inv, vmacs(V_2, V_inv, x.vr1, 3, 0), 0);
        vr1 = vmuls(vr1, V_dst, 0);
        return *this;
    }

    _AI AQuad& mul_acc(const AQuad& x, const AQuad& y) {
        vr0 = vmacs(vr0, x.vr0, y.vr0, 0, 0);
        vr1 = vmacs(vr1, x.vr1, y.vr1, 0, 0);
        return *this;
    }
    _AI AQuad& mul_acc(const AQuad& x, const AScalar& y) {
        vr0 = vmacf(vr0, x.vr0, y.fr, 0, 0);
        vr1 = vmacf(vr1, x.vr1, y.fr, 0, 0);
        return *this;
    }

    _AI AQuad& add(const AScalar& x) {
        vr64 V_src = vreplicate_fr(x.fr);
        vr0 = vadds(vr0, V_src, 0);
        vr1 = vadds(vr1, V_src, 0);
        return *this;
    }
    _AI AQuad& sub(const AScalar& x) {
        vr64 V_src = vreplicate_fr(x.fr);
        vr0 = vadds(vr0, V_src, 10);
        vr1 = vadds(vr1, V_src, 10);
        return *this;
    }
    _AI AQuad& mul(const AScalar& x) {
        vr0 = vmulf(vr0, x.fr, 0);
        vr1 = vmulf(vr1, x.fr, 0);
        return *this;
    }
    _AI AQuad& div(const AScalar& x) {
        return mul(x.inverse());
    }

    _AI AQuad& abs() {
        vr0 = vabs(vr0);
        vr1 = vabs(vr1);
        return *this;
    }
    _AI AQuad& max(const AQuad& x) {
        vr0 = vmax(vr0, x.vr0);
        vr1 = vmax(vr1, x.vr1);
        return *this;
    }
    _AI AQuad& min(const AQuad& x) {
        vr0 = vmin(vr0, x.vr0);
        vr1 = vmin(vr1, x.vr1);
        return *this;
    }

    _AI AQuad& clamp(const AScalar& low, const AScalar& high) {
        vr64 V_low = vreplicate_fr(low.fr);
        vr64 V_high= vreplicate_fr(high.fr);
        vr0 = vmin(vmax(vr0, V_low), V_high);
        vr1 = vmin(vmax(vr1, V_low), V_high);
        return *this;
    }

    _AI AScalar sum() const {
        vr64 V_dst = vadds(vr0, vr1, 0);
        return fadds(get_VRH(V_dst), get_VRL(V_dst), 0);
    }

    _AI AScalar sum_sq() const {
        vr64 V_dst = cmul(vr0, vr0, CONJ_Y);
        return get_VRL(cmac(V_dst, vr1, vr1, CONJ_Y));
    }

    _AI AScalar dot(const AQuad& x) const {
        vr64 V_dst = vblend(vr0, x.vr0, VB_ZERO, VB_YHXH_YLXL, 0, 0);
        return get_VRL(vblend_add(V_dst, vr1, x.vr1, VB_ZERO, VB_YHXH_YLXL, 0, 0, 0, 0));
    }

    _AI AScalar max_abs() const {
        vr64 V_dst;
        fr32 F_dst;
        unsigned int ar;
        mir18 mir;
        vmaxmin_init(V_dst,V_dst,mir);

        V_dst = vmax(vabs(vr0), vabs(vr1));
        rmax_idx(ar, F_dst, V_dst, mir);
	ar = ar + 1; // Temporary fix for 'unused-but-set-variable' warning
        return F_dst;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}
    _AI AQuad& normalize()   {return mul(sum_sq().f_invsqrt());}

    //
    // Additional methods not in AVector<N>
    //

    _AI AQuad(const AScalar& q0, const AScalar& q1, const AScalar& q2, const AScalar& q3) {
        vr0 = vr64_pair(q1.fr, q0.fr);
        vr1 = vr64_pair(q3.fr, q2.fr);
    }
    _AI AQuad(float q0, float q1, float q2, float q3) {
        move32_vr_ar(vr0, VRQ0, *(int*) &q0);
        move32_vr_ar(vr0, VRQ1, *(int*) &q1);
        convert_IEEE_float_to_32F_x2(vr0);
        move32_vr_ar(vr1, VRQ0, *(int*) &q2);
        move32_vr_ar(vr1, VRQ1, *(int*) &q3);
        convert_IEEE_float_to_32F_x2(vr1);
    }

    _AI AQuad operator* (const AQuad& x) const {
        AQuad z;
        z.vr0 = vmuls(vr0, x.vr0, 0);
        z.vr1 = vmuls(vr1, x.vr1, 0);
        return z;
    }
    _AI AQuad operator+ (const AQuad& x) const {
        AQuad z;
        z.vr0 = vadds(vr0, x.vr0, 0);
        z.vr1 = vadds(vr1, x.vr1, 0);
        return z;
    }
    _AI AQuad operator- (const AQuad& x) const {
        AQuad z;
        z.vr0 = vadds(vr0, x.vr0, 10);
        z.vr1 = vadds(vr1, x.vr1, 10);
        return z;
    }
    _AI AQuad operator- () const {
        AQuad z;
        z.vr0 = s_vneg(vr0);
        z.vr1 = s_vneg(vr1);
        return z;
    }

    _AI AQuad& operator*= (const AQuad& x) {
        vr0 = vmuls(vr0, x.vr0, 0);
        vr1 = vmuls(vr1, x.vr1, 0);
        return *this;
    }
    _AI AQuad& operator+= (const AQuad& x) {
        vr0 = vadds(vr0, x.vr0, 0);
        vr1 = vadds(vr1, x.vr1, 0);
        return *this;
    }
    _AI AQuad& operator-= (const AQuad& x) {
        vr0 = vadds(vr0, x.vr0, 10);
        vr1 = vadds(vr1, x.vr1, 10);
        return *this;
    }

    _AI AQuad operator* (const AScalar& x) const {
        AQuad z;
        z.vr0 = vmuls(vr0, vreplicate_fr(x.fr), 0);
        z.vr1 = vmuls(vr1, vreplicate_fr(x.fr), 0);
        return z;
    }
    _AI AQuad& operator*= (const AScalar& x) {
        vr0 = vmuls(vr0, vreplicate_fr(x.fr), 0);
        vr1 = vmuls(vr1, vreplicate_fr(x.fr), 0);
        return *this;
    }

    _AI AQuad mul_add(const AQuad& x, const AQuad& y) const {
        AQuad z;
        z.vr0 = vmacs(vr0, x.vr0, y.vr0,  0, 0);
        z.vr1 = vmacs(vr1, x.vr1, y.vr1,  0, 0);
        return z;
    }
    _AI AQuad mul_sub(const AQuad& x, const AQuad& y) const {
        AQuad z;
        z.vr0 = vmacs(vr0, x.vr0, y.vr0,  3, 0);
        z.vr1 = vmacs(vr1, x.vr1, y.vr1,  3, 0);
        return z;
    }

    _AI AScalar q0() const {return get_VRL(vr0);}
    _AI AScalar q1() const {return get_VRH(vr0);}
    _AI AScalar q2() const {return get_VRL(vr1);}
    _AI AScalar q3() const {return get_VRH(vr1);}

    _AI AQuad& set_q0(const AScalar& a) {set_VRL(vr0, a.fr); return *this;}
    _AI AQuad& set_q1(const AScalar& a) {set_VRH(vr0, a.fr); return *this;}
    _AI AQuad& set_q2(const AScalar& a) {set_VRL(vr1, a.fr); return *this;}
    _AI AQuad& set_q3(const AScalar& a) {set_VRH(vr1, a.fr); return *this;}

    _AI AComplex h0() const {return vr0;}
    _AI AComplex h1() const {return vr1;}

    _AI AQuad& set_h0(const AComplex& a) {vr0 = a.vr; return *this;}
    _AI AQuad& set_h1(const AComplex& a) {vr1 = a.vr; return *this;}
};

_AI AQuad AScalar::operator* (const AQuad& x) const {
    AQuad z;
    z.vr0 = vmulf(x.vr0, fr, 0);
    z.vr1 = vmulf(x.vr1, fr, 0);
    return z;
}

//
// Pointer to AQuad
//

struct PQuad
{
    AQuad* ptr;

    _AI PQuad(void* p) : ptr((AQuad*) p) {}

    _AI PQuad& operator= (void* p) {ptr = (AQuad*) p; return *this;}

    _AI operator AQuad*() const {return ptr;}
    _AI AQuad* operator->() const {return ptr;}
    _AI AQuad& operator[] (int i) const {return ptr[i];}

    _AI PQuad  operator+ (int index) const {return PQuad(ptr + index);}
    _AI PQuad  operator- (int index) const {return PQuad(ptr - index);}

    _AI PQuad& operator+= (int index) {ptr += index; return *this;}
    _AI PQuad& operator-= (int index) {ptr -= index; return *this;}

    _AI PQuad& operator++ ()    {++ptr; return *this;}
    _AI PQuad& operator-- ()    {--ptr; return *this;}
    _AI PQuad  operator++ (int) {PQuad p(*this); ++ptr; return p;}
    _AI PQuad  operator-- (int) {PQuad p(*this); --ptr; return p;}
};

struct PConstQuad
{
    const AQuad* ptr;

    _AI PConstQuad(const void* p) : ptr((AQuad*) p) {}

    _AI PConstQuad& operator= (void* p) {ptr = (AQuad*) p; return *this;}

    _AI operator const AQuad*() const {return ptr;}
    _AI const AQuad* operator->() const {return ptr;}
    _AI const AQuad& operator[] (int i) const {return ptr[i];}

    _AI PConstQuad  operator+ (int index) const {return PConstQuad(ptr + index);}
    _AI PConstQuad  operator- (int index) const {return PConstQuad(ptr - index);}

    _AI PConstQuad& operator+= (int index) {ptr += index; return *this;}
    _AI PConstQuad& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstQuad& operator++ ()    {++ptr; return *this;}
    _AI PConstQuad& operator-- ()    {--ptr; return *this;}
    _AI PConstQuad  operator++ (int) {PConstQuad p(*this); ++ptr; return p;}
    _AI PConstQuad  operator-- (int) {PConstQuad p(*this); --ptr; return p;}
};

//
// Unaligned Quad Pointers
//

struct UnalignedQuadLoadPointer
{
    const AScalar* ptr;
    ulsr32 ur;

    _AI UnalignedQuadLoadPointer(const void* p) : ptr((const AScalar*) p) {
        ur = align_32x2_load(ptr);
    }

    _AI UnalignedQuadLoadPointer& operator= (const void* p) {
        ptr = (const AScalar*) p;
        ur = align_32x2_load(ptr);
        return *this;
    }

    _AI operator PConstScalar() const {return PConstScalar(ptr);}
    _AI operator const AScalar*() const {return ptr;}
    _AI const AScalar& operator*() const {return *ptr;}
    _AI const AScalar* operator->() const {return ptr;}

    _AI AQuad load_post() {
        AQuad q;
        load_32x2_vr_a(q.vr0, ur, ptr);
        load_32x2_vr_a(q.vr1, ur, ptr);
        return q;
    }
};

struct UnalignedQuadStorePointer
{
    AScalar* ptr;
    ulsr32 ur;

    _AI UnalignedQuadStorePointer(void* p) : ptr((AScalar*) p) {
        ur = align_32x2_store(ptr);
    }

    _AI void flush() {
        flush_32x2(ur, ptr);
    }

    _AI UnalignedQuadStorePointer& operator= (void* p) {
        ptr = (AScalar*) p;
        ur = align_32x2_store(ptr);
        return *this;
    }

    _AI operator PScalar() const {return PScalar(ptr);}
    _AI operator AScalar*() const {return ptr;}
    _AI AScalar& operator*() const {return *ptr;}
    _AI AScalar* operator->() const {return ptr;}

    _AI void store_post(const AQuad& q) {
        store_32x2_vr_a(q.vr0, ur, ptr);
        store_32x2_vr_a(q.vr1, ur, ptr);
    }
};

#endif
