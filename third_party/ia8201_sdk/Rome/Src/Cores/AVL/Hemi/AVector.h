/************************************************************************//**
 * @file    AVL/Hemi/AVector.h
 *
 * @brief   Vector wrapper for HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef AVECTOR_H
#define AVECTOR_H

#include "AComplex.h"

template <int N>
struct AVector
{
    static const int NV = (N + 1) / 2;

    vr64 a[NV];

    _AI AVector() {}
    _AI AVector(const AVector& x) {copy(x);}
    _AI AVector& operator= (const AVector& x) {if (&x != this) copy(x); return *this;}

    _AI static int length() {return N;}

    _AI operator AScalar* () {return (AScalar*) a;}
    _AI operator const AScalar* () const {return (const AScalar*) a;}
    _AI AScalar& operator[] (int i) const {return ((AScalar*) a)[i];}

    _AI bool operator== (const AVector& x) const {
        vr64 V_a, V_b;
        const vr64* P_a = a;
        const vr64* P_b = x.a;
        atbool bx2 = 0;

        for (int i = 0; i < N/2; i++) {
            load32x2_vr_postI(V_a, P_a, INC1);
            load32x2_vr_postI(V_b, P_b, INC1);
            bx2 = orb2(bx2, vne(V_a, V_b));
        }
        unsigned ne2 = move_ar_bbr(bx2);

        if (N&1)
            ne2 |= ne_fr(*(fr32*) P_a, *(fr32*) P_b);

        return ne2 == 0;
    }

    _AI bool operator!= (const AVector& x) const {
        return !(*this == x);
    }

    _AI AVector& fill(const AScalar& x) {
        vr64 V_src = vreplicate_fr(x.fr);
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(V_src, P_dst, INC1);

        return *this;
    }

    _AI AVector& copy(const AVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(V_src, P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& add(const AVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(vadds(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& sub(const AVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(vadds(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src, 10), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& mul(const AVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(vmuls(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& div(const AVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;
        vr64 V_2 = vseta_vr(2, 0);

        for (int i = 0; i < NV; i++) {
            // One iteration of Newton's method
            vr64 V_src, V_inv;
            load32x2_vr_postI(V_src, P_src, INC1);
            V_inv = vr64_pair(inv(get_VRH(V_src)), inv(get_VRL(V_src)));
            V_src = vmuls(V_inv, vmacs(V_2, V_inv, V_src, 3, 0), 0);
            store32x2_vr_postI(vmuls(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& mul_acc(const AVector& x, const AVector& y) {
        const vr64* P_src_x = x.a;
        const vr64* P_src_y = y.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src_x, V_src_y;
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            load32x2_vr_postI(V_src_y, P_src_y, INC1);
            store32x2_vr_postI(vmacs(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src_x, V_src_y, 0, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& mul_acc(const AVector& x, const AScalar& y) {
        vr64 V_src_x;
        const vr64* P_src_x = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            store32x2_vr_postI(vmacf(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src_x, y.fr, 0, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& add(const AScalar& x) {
        vr64 V_src = vreplicate_fr(x.fr);
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(vadds(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        return *this;
    }

    _AI AVector& sub(const AScalar& x) {
        vr64 V_src = vreplicate_fr(x.fr);
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(vadds(load32x2_vr_idxI(P_dst, IDX0),
                                     V_src, 10), P_dst, INC1);
        return *this;
    }

    _AI AVector& mul(const AScalar& x) {
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(vmulf(load32x2_vr_idxI(P_dst, IDX0),
                                     x.fr, 0), P_dst, INC1);
        return *this;
    }

    _AI AVector& div(const AScalar& x) {return mul(x.inverse());}

    _AI AVector& abs() {
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
           store32x2_vr_postI(vabs(load32x2_vr_idxI(P_dst, IDX0)),
                              P_dst, INC1);

        return *this;
    }

    _AI AVector& max(const AVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(vmax(load32x2_vr_idxI(P_dst, IDX0), V_src), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& min(const AVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(vmin(load32x2_vr_idxI(P_dst, IDX0), V_src), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& clamp(const AScalar& low, const AScalar& high) {
        vr64 V_low = vreplicate_fr(low.fr);
        vr64 V_high= vreplicate_fr(high.fr);
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(vmax(V_low, vmin(V_high, load32x2_vr_idxI(P_dst, IDX0))),
                               P_dst, INC1);
        return *this;
    }

    _AI AScalar sum() const {
        vr64 V_src;
        vr64 V_dst = vseta_vr(0, 0);
        const vr64* P_src = a;

        for (int i = 0; i < N/2; i++) {
            load32x2_vr_postI(V_src, P_src, INC1);
            V_dst = vsum_perm(V_dst, V_src, V_src, VSEL_ZERO, VSEL_YH_XL, 0, 0);
        }
        if (N&1)
            return fadds(get_VRL(V_dst), *(fr32*) P_src, 0);

        return get_VRL(V_dst);
    }

    _AI AScalar sum_sq() const {
        vr64 V_src;
        vr64 V_dst = vseta_vr(0, 0);
        const vr64* P_src = a;

        for (int i = 0; i < N/2; i++) {
            load32x2_vr_postI(V_src, P_src, INC1);
            V_dst = cmac(V_dst, V_src, V_src, CONJ_Y);
        }
        if (N&1) {
            fr32 F_src = *(fr32*) P_src;
            return fmacs(get_VRL(V_dst), F_src, F_src, 0);
        }

        return get_VRL(V_dst);
    }

    _AI AScalar dot(const AVector& x) const {
        vr64 V_src;
        vr64 V_src_x;
        vr64 V_dst = vseta_vr(0, 0);
        const vr64* P_src = a;
        const vr64* P_src_x = x.a;

        for (int i = 0; i < N/2; i++) {
            load32x2_vr_postI(V_src, P_src, INC1);
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            V_dst = vblend_add(V_dst, V_src, V_src_x, VB_ZERO, VB_YHXH_YLXL, 0, 0, 0, 0);
        }
        if (N&1) {
            load32x2_vr_postI(V_src, P_src, INC1);
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            V_dst = vmac_perm(V_dst, V_src, V_src_x, VSEL_ZERO, VSEL_YL_XL, 0, 0, 0, 0);
        }

        return get_VRL(V_dst);
    }

    _AI AScalar max_abs() const {
        vr64 V_src;
        vr64 V_dst = vseta_vr(0, 0);
        fr32 F_dst;
        const vr64* P_src = a;
        unsigned int ar;
        mir18 mir;

        for (int i = 0; i < N/2; i++) {
            load32x2_vr_postI(V_src, P_src, INC1);
            V_dst = vmax(V_dst, vabs(V_src));
        }
        if (N&1) {
            load32x2_vr_postI(V_src, P_src, INC1);
            seta_vr(V_src, 2, 0, 0);
            V_dst = vmax(V_dst, vabs(V_src));
        }

        rmax_idx(ar, F_dst, V_dst, mir);
        return F_dst;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}
    _AI AVector& normalize() {return mul(sum_sq().f_invsqrt());}
};

#endif
