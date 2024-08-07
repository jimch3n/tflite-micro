/************************************************************************//**
 * @file    AVL/Hemi/AComplexVector.h
 *
 * @brief   Complex Vector wrapper for HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEXVECTOR_H
#define ACOMPLEXVECTOR_H

#include "AComplex.h"
#include "AVector.h"

template <int N>
struct AComplexVector
{
    static const int NV = N;

    vr64 a[NV];

    _AI AComplexVector() {}
    _AI AComplexVector(const AComplexVector& x) {copy(x);}
    _AI AComplexVector& operator= (const AComplexVector& x) {
        if (&x != this) copy(x);
        return *this;
    }
    _AI AComplexVector(const AVector<N>& x) {*this = x;}
    _AI AComplexVector& operator= (const AVector<N>& x) {
        vr64 V_src = vseta_vr(0, 0);
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            load32x1_vr_postI(V_src, P_src, INC1, VRQ0);
            store32x2_vr_postI(V_src, P_dst, INC1);
        }

        return *this;
    }

    _AI static int length() {return N;}

    _AI operator AComplex* () {return (AComplex*) a;}
    _AI operator const AComplex* () const {return (const AComplex*) a;}
    _AI AComplex& operator[] (int i) const {return ((AComplex*) a)[i];}

    _AI bool operator== (const AComplexVector& x) const {
        vr64 V_a, V_b;
        const vr64* P_a = a;
        const vr64* P_b = x.a;
        atbool bx2 = 0;

        for (int i = 0; i < N; i++) {
            load32x2_vr_postI(V_a, P_a, INC1);
            load32x2_vr_postI(V_b, P_b, INC1);
            bx2 = orb2(bx2, vne(V_a, V_b));
        }

        return !move_ar_bbr(bx2);
    }

    _AI bool operator!= (const AComplexVector& x) const {
        return !(*this == x);
    }

    _AI AComplexVector& fill(const AComplex& x) {
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(x.vr, P_dst, INC1);

        return *this;
    }

    _AI AComplexVector& copy(const AComplexVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(V_src, P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& add(const AComplexVector& x) {
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

    _AI AComplexVector& sub(const AComplexVector& x) {
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

    _AI AComplexVector& mul(const AComplexVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(cmul(load32x2_vr_idxI(P_dst, IDX0),
                                    V_src, CONJ_NONE), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_conj(const AComplexVector& x) {
        const vr64* P_src = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src;
            load32x2_vr_postI(V_src, P_src, INC1);
            store32x2_vr_postI(cmul(load32x2_vr_idxI(P_dst, IDX0),
                                    V_src, CONJ_Y), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_acc(const AComplexVector& x, const AComplexVector& y) {
        const vr64* P_src_x = x.a;
        const vr64* P_src_y = y.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src_x, V_src_y;
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            load32x2_vr_postI(V_src_y, P_src_y, INC1);
            store32x2_vr_postI(cmac(load32x2_vr_idxI(P_dst, IDX0),
                                    V_src_x, V_src_y, CONJ_NONE), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_acc(const AComplexVector& x, const AComplex& y) {
        vr64 V_src_x;
        const vr64* P_src_x = x.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            store32x2_vr_postI(cmac(load32x2_vr_idxI(P_dst, IDX0),
                                    V_src_x, y.vr, CONJ_NONE), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_conj_acc(const AComplexVector& x, const AComplexVector& y) {
        const vr64* P_src_x = x.a;
        const vr64* P_src_y = y.a;
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr64 V_src_x, V_src_y;
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            load32x2_vr_postI(V_src_y, P_src_y, INC1);
            store32x2_vr_postI(cmac(load32x2_vr_idxI(P_dst, IDX0),
                                    V_src_x, V_src_y, CONJ_Y), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& add(const AComplex& x) {
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(vadds(load32x2_vr_idxI(P_dst, IDX0),
                                     x.vr, 0), P_dst, INC1);
        return *this;
    }

    _AI AComplexVector& sub(const AComplex& x) {
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(vadds(load32x2_vr_idxI(P_dst, IDX0),
                                     x.vr, 10), P_dst, INC1);
        return *this;
    }

    _AI AComplexVector& mul(const AComplex& x) {
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(cmul(load32x2_vr_idxI(P_dst, IDX0),
                                    x.vr, CONJ_NONE), P_dst, INC1);
        return *this;
    }

    _AI AComplexVector& mul(const AScalar& x) {
        vr64* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x2_vr_postI(vmulf(load32x2_vr_idxI(P_dst, IDX0),
                                     x.fr, 0), P_dst, INC1);
        return *this;
    }

    _AI AComplex sum() const {
        vr64 V_src;
        vr64 V_dst = vseta_vr(0, 0);
        const vr64* P_src = a;

        for (int i = 0; i < N; i++) {
            load32x2_vr_postI(V_src, P_src, INC1);
            V_dst = vadds(V_dst, V_src, 0);
        }

        return V_dst;
    }

    _AI AScalar norm_sq() const {
        vr64 V_src;
        vr64 V_dst = vseta_vr(0, 0);
        const vr64* P_src = a;

        for (int i = 0; i < N; i++) {
            load32x2_vr_postI(V_src, P_src, INC1);
            V_dst = cmac(V_dst, V_src, V_src, CONJ_Y);
        }

        return get_VRL(V_dst);
    }

    _AI AComplex dot(const AComplexVector& x) const {
        vr64 V_src;
        vr64 V_src_x;
        vr64 V_dst = vseta_vr(0, 0);
        const vr64* P_src = a;
        const vr64* P_src_x = x.a;

        for (int i = 0; i < N; i++) {
            load32x2_vr_postI(V_src, P_src, INC1);
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            V_dst = cmac(V_dst, V_src, V_src_x, CONJ_Y);
        }

        return V_dst;
    }

    _AI AScalar norm() const        {return norm_sq().f_sqrt();}
    _AI AComplexVector& normalize() {return mul(norm_sq().f_invsqrt());}
};

#endif
