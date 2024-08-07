/************************************************************************//**
 * @file    AVL/Hemi/APair.h
 *
 * @brief   APair wrapper for vr64 on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef APAIR_H
#define APAIR_H

#include "AScalar.h"

struct APair;

struct APair
{
    vr64 vr;

    _AI APair() {}
    _AI APair(const APair& x) : vr(x.vr) {}

    _AI static int length() {return 2;}
    _AI static APair Zero() {return vseta_vr(0, 0);}

    _AI const AScalar operator[] (int i) const {return move32_fr_vr_idx(vr, i);}
    _AI bool operator== (const APair& x) const {return !move_ar_bbr(vne(vr, x.vr));}
    _AI bool operator!= (const APair& x) const {return !(*this == x);}

    _AI APair& fill(const AScalar& x) {vr = vreplicate_fr(x.fr); return *this;}
    _AI APair& copy(const APair& x)   {vr = x.vr;                return *this;}

    _AI APair& add(const APair& x) {vr = vadds(vr, x.vr, 0);    return *this;}
    _AI APair& sub(const APair& x) {vr = vadds(vr, x.vr, 10);   return *this;}
    _AI APair& mul(const APair& x) {vr = vmuls(vr, x.vr, 0);    return *this;}
    _AI APair& div(const APair& x) {
        // One iteration of Newton's method
        vr64 V_2 = vseta_vr(2, 0);
        vr64 V_inv, V_dst;
        V_inv = vr64_pair(inv(get_VRH(x.vr)), inv(get_VRL(x.vr)));
        V_dst = vmuls(V_inv, vmacs(V_2, V_inv, x.vr, 3, 0), 0);
        vr = vmuls(vr, V_dst, 0);
        return *this;
    }

    _AI APair& mul_acc(const APair& x, const APair& y) {
        vr = vmacs(vr, x.vr, y.vr, 0, 0);
        return *this;
    }
    _AI APair& mul_acc(const APair& x, const AScalar& y) {
        vr = vmacs(vr, x.vr, vreplicate_fr(y.fr), 0, 0);
        return *this;
    }

    _AI APair& add(const AScalar& x) {
        vr = vadds(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }
    _AI APair& sub(const AScalar& x) {
        vr = vadds(vr, vreplicate_fr(x.fr), 10);
        return *this;
    }
    _AI APair& mul(const AScalar& x) {
        vr = vmulf(vr, x.fr, 0);
        return *this;
    }
    _AI APair& div(const AScalar& x) {
        return mul(x.inverse());
    }

    _AI APair& abs()               {vr = vabs(vr);       return *this;}
    _AI APair& max(const APair& x) {vr = vmax(vr, x.vr); return *this;}
    _AI APair& min(const APair& x) {vr = vmin(vr, x.vr); return *this;}

    _AI APair& clamp(const AScalar& low, const AScalar& high) {
        vr64 V_low = vreplicate_fr(low.fr);
        vr64 V_high= vreplicate_fr(high.fr);
        vr = vmin(vmax(vr, V_low), V_high);
        return *this;
    }

    _AI AScalar sum() const {
        return fadds(get_VRH(vr), get_VRL(vr), 0);
    }

    _AI AScalar sum_sq() const {
        return get_VRL(cmul(vr, vr, CONJ_Y));
    }

    _AI AScalar dot(const APair& x) const {
        return get_VRL(vblend(vr, x.vr, VB_ZERO, VB_YHXH_YLXL, 0, 0));
    }

    _AI AScalar max_abs() const {
        fr32 F_dst;
        unsigned int ar;
        mir18 mir;
        vr64 vTemp = vabs(vr);
        vmaxmin_init(vTemp,vTemp,mir);

        rmax_idx(ar, F_dst, vTemp, mir);
	ar = ar + 1; // Temporary fix for 'unused-but-set-variable' warning
        return F_dst;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}
    _AI APair& normalize()   {return mul(sum_sq().f_invsqrt());}

    //
    // Additional methods not in AVector<N>
    //

    _AI APair(const vr64& a) : vr(a) {}
    _AI APair(const AScalar& h0, const AScalar& h1) : vr(vr64_pair(h1.fr, h0.fr)) {}
    _AI APair(float h0, float h1) {
        move32_vr_ar(vr, VRQ0, *(int*) &h0);
        move32_vr_ar(vr, VRQ1, *(int*) &h1);
        convert_IEEE_float_to_32F_x2(vr);
    }

    _AI operator vr64()     const {return vr;}

    _AI APair operator* (const APair& x) const {return vmuls(vr, x.vr, 0);}
    _AI APair operator+ (const APair& x) const {return vadds(vr, x.vr, 0);}
    _AI APair operator- (const APair& x) const {return vadds(vr, x.vr, 10);}
    _AI APair operator- ()               const {return s_vneg(vr);}

    _AI APair& operator*= (const APair& x) {vr = vmuls(vr, x.vr, 0);  return *this;}
    _AI APair& operator+= (const APair& x) {vr = vadds(vr, x.vr, 0);  return *this;}
    _AI APair& operator-= (const APair& x) {vr = vadds(vr, x.vr, 10); return *this;}

    _AI APair operator* (const AScalar& x) const {return vmuls(vr, vreplicate_fr(x.fr), 0);}

    _AI APair& operator*= (const AScalar& x) {
        vr = vmuls(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }

    _AI APair mul_add(const APair& x, const APair& y) const {
        return vmacs(vr, x.vr, y.vr,  0, 0);
    }
    _AI APair mul_sub(const APair& x, const APair& y) const {
        return vmacs(vr, x.vr, y.vr, 3, 0);
    }

    _AI AScalar h0() const {return get_VRL(vr);}
    _AI AScalar h1() const {return get_VRH(vr);}

    _AI APair& set_h0(const AScalar& a) {set_VRL(vr, a.fr); return *this;}
    _AI APair& set_h1(const AScalar& a) {set_VRH(vr, a.fr); return *this;}
};

_AI APair AScalar::operator* (const APair& x) const {
    return vmulf(x.vr, fr, 0);
}

//
// Pointer to APair
//

struct PPair
{
    APair* ptr;

    _AI PPair(void* p) : ptr((APair*) p) {}

    _AI operator APair*() const {return ptr;}
    _AI APair* operator->() const {return ptr;}
    _AI APair& operator[] (int i) const {return ptr[i];}

    _AI PPair  operator+ (int index) const {return PPair(ptr + index);}
    _AI PPair  operator- (int index) const {return PPair(ptr - index);}

    _AI PPair& operator+= (int index) {ptr += index; return *this;}
    _AI PPair& operator-= (int index) {ptr -= index; return *this;}

    _AI PPair& operator++ ()    {++ptr; return *this;}
    _AI PPair& operator-- ()    {--ptr; return *this;}
    _AI PPair  operator++ (int) {PPair p(*this); ++ptr; return p;}
    _AI PPair  operator-- (int) {PPair p(*this); --ptr; return p;}
};

struct PConstPair
{
    const APair* ptr;

    _AI PConstPair(const void* p) : ptr((const APair*) p) {}

    _AI operator const APair*() const {return ptr;}
    _AI const APair* operator->() const {return ptr;}
    _AI const APair& operator[] (int i) const {return ptr[i];}

    _AI PConstPair  operator+ (int index) const {return PConstPair(ptr + index);}
    _AI PConstPair  operator- (int index) const {return PConstPair(ptr - index);}

    _AI PConstPair& operator+= (int index) {ptr += index; return *this;}
    _AI PConstPair& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstPair& operator++ ()    {++ptr; return *this;}
    _AI PConstPair& operator-- ()    {--ptr; return *this;}
    _AI PConstPair  operator++ (int) {PConstPair p(*this); ++ptr; return p;}
    _AI PConstPair  operator-- (int) {PConstPair p(*this); --ptr; return p;}
};

//
// Unaligned Pair Pointers
//

struct UnalignedPairLoadPointer
{
    const AScalar* ptr;
    ulsr32 ur;

    _AI UnalignedPairLoadPointer(const void* p) : ptr((const AScalar*) p) {
        ur = align_32x2_load(ptr);
    }

    _AI operator PConstScalar() const {return PConstScalar(ptr);}
    _AI operator const AScalar*() const {return ptr;}
    _AI const AScalar& operator*() const {return *ptr;}
    _AI const AScalar* operator->() const {return ptr;}

    _AI APair load_post() {
        vr64 v;
        load_32x2_vr_a(v, ur, ptr);
        return v;
    }
};

struct UnalignedPairStorePointer
{
    AScalar* ptr;
    ulsr32 ur;

    _AI UnalignedPairStorePointer(void* p) : ptr((AScalar*) p) {
        ur = align_32x2_store(ptr);
    }

    _AI void flush() {
        flush_32x2(ur, ptr);
    }

    _AI operator PScalar() const {return PScalar(ptr);}
    _AI operator AScalar*() const {return ptr;}
    _AI AScalar& operator*() const {return *ptr;}
    _AI AScalar* operator->() const {return ptr;}

    _AI void store_post(const APair& a) {
        store_32x2_vr_a(a.vr, ur, ptr);
    }
};

#endif
