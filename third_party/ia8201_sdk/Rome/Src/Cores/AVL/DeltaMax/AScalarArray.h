/************************************************************************//**
 * @file    AVL\DeltaMax\AScalarArray.h
 *
 * @brief   ScalarArray wrapper for DeltaMax
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ASCALARARRAY_H
#define ASCALARARRAY_H

/**************************************************************************//**
 * @addtogroup dmx_avl
 * @{
 *****************************************************************************/

#include "AQuad.h"

struct AScalarArray
{
    AScalar* a;
    int N;

    _AI AScalarArray() {}
    _AI AScalarArray(int n, AScalar* ptr) : a(ptr), N(n) {}
    
    _AI void init(int n, AScalar* ptr) {a = ptr; N = n;}
    _AI int length() const {return N;}

    _AI AScalarArray& operator= (const AScalarArray& x) {
        if (&x != this)
            copy(x);
        return *this;
    }

    _AI operator AScalar* () const {return a;}
    _AI operator const AScalar* () const {return a;}
    _AI AScalar& operator[] (int i) const {return a[i];}

    _AI xtbool operator== (const AScalarArray& x) const {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer LP_a(a);
        UnalignedQuadLoadPointer LP_b(x.a);
        xtbool4 bx4 = (xtbool4) 15;
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            bx4 = andb4(bx4, veq(LP_a.load_post(), LP_b.load_post()));
        loops = N & 3;

        xtbool is_eq = XT_ALL4(bx4);
        PConstScalar P_a = LP_a;
        PConstScalar P_b = LP_b;

        for (int i = 0; i < loops; i++)
            is_eq = XT_ANDB(is_eq, eq_fr(P_a[i].fr, P_b[i].fr));

        return is_eq;
    }

    _AI bool operator!= (const AScalarArray& x) const {
        return !(*this == x);
    }

    _AI void fill(const AScalar& x) {
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_src = vreplicate_fr(x.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(V_src);
        loops = N & 3;
        SP_dst.flush();

        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++)
            store32x1_vr_postI(V_src, P_dst, INC1, VRQ0);
    }

    _AI void copy(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(LP_src.load_post());
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_src;
            load32x1_vr_postI(V_src,  P_src, INC1, VRQ0);
            store32x1_vr_postI(V_src, P_dst, INC1, VRQ0);
        }
    }

    _AI void add(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_src_y = vreplicate_fr(y.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vadds(LP_src.load_post(), V_src_y, 0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            fadds(V_tmp, VRQ0, V_tmp, VRQ0, V_src_y, VRQ0, 0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void add(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vadds(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src_x, INC1, VRQ0);
            load32x1_vr_postI(V_tmp,  P_src_y, INC1, VRQ1);
            fadds(V_tmp, VRQ0, V_tmp, VRQ0, V_tmp, VRQ1, 0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void sub(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_src_y = vreplicate_fr(y.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vadds(LP_src.load_post(), V_src_y, 0xf0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            fadds(V_tmp, VRQ0, V_tmp, VRQ0, V_src_y, VRQ0, 0x10);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void sub(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vadds(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0xf0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src_x, INC1, VRQ0);
            load32x1_vr_postI(V_tmp,  P_src_y, INC1, VRQ1);
            fadds(V_tmp, VRQ0, V_tmp, VRQ0, V_tmp, VRQ1, 0x10);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void mul(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_src_y = vreplicate_fr(y.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vmuls(LP_src_x.load_post(), V_src_y, 0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src_x;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            fmuls(V_tmp, VRQ0, V_tmp, VRQ0, V_src_y, VRQ0, 0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void mul(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vmuls(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src_x, INC1, VRQ0);
            load32x1_vr_postI(V_tmp,  P_src_y, INC1, VRQ1);
            fmuls(V_tmp, VRQ0, V_tmp, VRQ0, V_tmp, VRQ1, 0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void div(const AScalarArray& x, const AScalar& y) {mul(x, y.inverse());}

    _AI void div(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_2 = vseta_vr(2, 0, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            // One iteration of Newton's method
            vr128 V_src = LP_src_y.load_post().vr;
            vr128 V_inv;
            inv(V_inv, VRQ0, V_src, VRQ0);
            inv(V_inv, VRQ1, V_src, VRQ1);
            inv(V_inv, VRQ2, V_src, VRQ2);
            inv(V_inv, VRQ3, V_src, VRQ3);
            V_inv = vmuls(V_inv, vmacs_adj(V_2, V_inv, V_src, 15, 0), 0);
            SP_dst.store_post(vmuls(LP_src_x.load_post(), V_inv, 0));
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_src, V_inv, V_tmp;
            load32x1_vr_postI(V_src, P_src_y, INC1, VRQ0);
            load32x1_vr_postI(V_tmp, P_src_x, INC1, VRQ0);
            inv(V_inv, VRQ0, V_src, VRQ0);
            V_inv = vmuls(V_inv, vmacs_adj(V_2, V_inv, V_src, 15, 0), 0);
            store32x1_vr_postI(vmuls(V_tmp, V_inv, 0), P_dst, INC1, VRQ0);
        }
    }

    _AI void mul_acc(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_dst(a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_src_y = vreplicate_fr(y.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vmacs_adj(LP_dst.load_post(),
                                        LP_src_x.load_post(), V_src_y, 0, 0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src_x;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp, V_dst;
            load32x1_vr_postI(V_tmp, P_src, INC1, VRQ0);
            load32x1_vr_idxI(V_dst,  P_dst, IDX0, VRQ0);
            fmacs(V_dst, VRQ0, V_tmp, VRQ0, V_src_y, VRQ0, 0);
            store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
        }
    }

    _AI void mul_acc(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadLoadPointer  LP_dst(a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vmacs_adj(LP_dst.load_post(),
                                        LP_src_x.load_post(),
                                        LP_src_y.load_post(), 0, 0));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp, V_dst;
            load32x1_vr_postI(V_tmp,  P_src_x, INC1, VRQ0);
            load32x1_vr_postI(V_tmp,  P_src_y, INC1, VRQ1);
            load32x1_vr_idxI(V_dst,   P_dst,   IDX0, VRQ0);
            fmacs(V_dst, VRQ0, V_tmp, VRQ0, V_tmp, VRQ1, 0);
            store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
        }
    }

    _AI void max(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vmax(LP_src_x.load_post(),
                                   LP_src_y.load_post()));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src_x, INC1, VRQ0);
            load32x1_vr_postI(V_tmp,  P_src_y, INC1, VRQ1);
            fmax(V_tmp, VRQ0, V_tmp, VRQ0, V_tmp, VRQ1);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void min(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vmin(LP_src_x.load_post(),
                                   LP_src_y.load_post()));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src_x, INC1, VRQ0);
            load32x1_vr_postI(V_tmp,  P_src_y, INC1, VRQ1);
            fmin(V_tmp, VRQ0, V_tmp, VRQ0, V_tmp, VRQ1);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void clamp(const AScalarArray& x, const AScalar& low, const AScalar& high) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_low = vreplicate_fr(low.fr);
        vr128 V_high = vreplicate_fr(high.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vmax(V_low, vmin(V_high, LP_src.load_post())));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            fmin(V_tmp, VRQ0, V_tmp, VRQ0, V_high, VRQ0);
            fmax(V_tmp, VRQ0, V_tmp, VRQ0, V_low,  VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void abs(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            SP_dst.store_post(vabs(LP_src.load_post()));
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            f_abs(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_inv(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            inv(V_tmp, VRQ0, V_src, VRQ0);
            inv(V_tmp, VRQ1, V_src, VRQ1);
            inv(V_tmp, VRQ2, V_src, VRQ2);
            inv(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            inv(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_invsqrt(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            invsqrt(V_tmp, VRQ0, V_src, VRQ0);
            invsqrt(V_tmp, VRQ1, V_src, VRQ1);
            invsqrt(V_tmp, VRQ2, V_src, VRQ2);
            invsqrt(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            invsqrt(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_sigmoid(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            sigmoid(V_tmp, VRQ0, V_src, VRQ0);
            sigmoid(V_tmp, VRQ1, V_src, VRQ1);
            sigmoid(V_tmp, VRQ2, V_src, VRQ2);
            sigmoid(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            sigmoid(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_log2(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            log2(V_tmp, VRQ0, V_src, VRQ0);
            log2(V_tmp, VRQ1, V_src, VRQ1);
            log2(V_tmp, VRQ2, V_src, VRQ2);
            log2(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            log2(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_pow2(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            pow2(V_tmp, VRQ0, V_src, VRQ0);
            pow2(V_tmp, VRQ1, V_src, VRQ1);
            pow2(V_tmp, VRQ2, V_src, VRQ2);
            pow2(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            pow2(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_sqrt(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            invsqrt(V_tmp, VRQ0, V_src, VRQ0);
            invsqrt(V_tmp, VRQ1, V_src, VRQ1);
            invsqrt(V_tmp, VRQ2, V_src, VRQ2);
            invsqrt(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(vmuls(V_src, V_tmp, 0));
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            invsqrt(V_tmp, VRQ1, V_tmp, VRQ0);
            fmuls(V_tmp, VRQ0, V_tmp, VRQ0, V_tmp, VRQ1, 0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void sine_turns(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            sine(V_tmp, VRQ0, V_src, VRQ0);
            sine(V_tmp, VRQ1, V_src, VRQ1);
            sine(V_tmp, VRQ2, V_src, VRQ2);
            sine(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            sine(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void cosine_turns(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_tmp;
            cosine(V_tmp, VRQ0, V_src, VRQ0);
            cosine(V_tmp, VRQ1, V_src, VRQ1);
            cosine(V_tmp, VRQ2, V_src, VRQ2);
            cosine(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            cosine(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void sine_rads(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_inv2pi = vseta_vr(14, 6, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = vmuls(LP_src.load_post(), V_inv2pi, 0);
            vr128 V_tmp;
            sine(V_tmp, VRQ0, V_src, VRQ0);
            sine(V_tmp, VRQ1, V_src, VRQ1);
            sine(V_tmp, VRQ2, V_src, VRQ2);
            sine(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            fmuls(V_tmp, VRQ0, V_tmp, VRQ0, V_inv2pi, VRQ0, 0);
            sine(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void cosine_rads(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_inv2pi = vseta_vr(14, 6, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = vmuls(LP_src.load_post(), V_inv2pi, 0);
            vr128 V_tmp;
            cosine(V_tmp, VRQ0, V_src, VRQ0);
            cosine(V_tmp, VRQ1, V_src, VRQ1);
            cosine(V_tmp, VRQ2, V_src, VRQ2);
            cosine(V_tmp, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_tmp);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            fmuls(V_tmp, VRQ0, V_tmp, VRQ0, V_inv2pi, VRQ0, 0);
            cosine(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_exp(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_log2e = vseta_vr(9, 0, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = vmuls(LP_src.load_post(), V_log2e, 0);
            vr128 V_dst;
            pow2(V_dst, VRQ0, V_src, VRQ0);
            pow2(V_dst, VRQ1, V_src, VRQ1);
            pow2(V_dst, VRQ2, V_src, VRQ2);
            pow2(V_dst, VRQ3, V_src, VRQ3);
            SP_dst.store_post(V_dst);
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            fmuls(V_tmp, VRQ0, V_tmp, VRQ0, V_log2e, VRQ0, 0);
            pow2(V_tmp, VRQ0, V_tmp, VRQ0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void f_log(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_ln2 = vseta_vr(10, 0, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_dst;
            log2(V_dst, VRQ0, V_src, VRQ0);
            log2(V_dst, VRQ1, V_src, VRQ1);
            log2(V_dst, VRQ2, V_src, VRQ2);
            log2(V_dst, VRQ3, V_src, VRQ3);
            SP_dst.store_post(vmuls(V_ln2, V_dst, 0));
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp,  P_src, INC1, VRQ0);
            log2(V_tmp, VRQ0, V_tmp, VRQ0);
            fmuls(V_tmp, VRQ0, V_tmp, VRQ0, V_ln2, VRQ0, 0);
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void inverse(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_2 = vseta_vr(2, 0, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            // One iteration of Newton's method
            vr128 V_src = LP_src.load_post().vr;
            vr128 V_inv;
            inv(V_inv, VRQ0, V_src, VRQ0);
            inv(V_inv, VRQ1, V_src, VRQ1);
            inv(V_inv, VRQ2, V_src, VRQ2);
            inv(V_inv, VRQ3, V_src, VRQ3);
            SP_dst.store_post(vmuls(V_inv, vmacs_adj(V_2, V_inv, V_src, 15, 0), 0));
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src = LP_src;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_src, V_inv;
            load32x1_vr_postI(V_src, P_src, INC1, VRQ0);
            inv(V_inv, VRQ0, V_src, VRQ0);
            V_inv = vmuls(V_inv, vmacs_adj(V_2, V_inv, V_src, 15, 0), 0);
            store32x1_vr_postI(V_inv, P_dst, INC1, VRQ0);
        }
    }

    _AI AScalar sum() const {
        UnalignedQuadLoadPointer LP_src(a);
        vr128 V_dst = vseta_vr(0, 0, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            V_dst = vadds(V_dst, LP_src.load_post(), 0);
        loops = N & 3;
        dsums_L(V_dst, V_dst, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);

        PConstScalar P_src = LP_src;
        fr32 F_dst = get_VRQ0(V_dst);
        for (int i = 0; i < loops; i++)
            F_dst = fpadd(F_dst, P_src[i].fr, 0);

        return F_dst;
    }

    _AI AScalar sum_sq() const {
        UnalignedQuadLoadPointer LP_src(a);
        vr128 V_dst = vseta_vr(0, 0, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src = LP_src.load_post().vr;
            V_dst = vmacs_adj(V_dst, V_src, V_src, 0, 0);
        }
        loops = N & 3;
        dsums_L(V_dst, V_dst, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);

        PConstScalar P_src = LP_src;
        fr32 F_dst = get_VRQ0(V_dst);
        for (int i = 0; i < loops; i++)
            fpmac(F_dst, P_src[i].fr, P_src[i].fr, 0);

        return F_dst;
    }

    _AI AScalar dot(const AScalarArray& x) const {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer LP_src(x.a);
        UnalignedQuadLoadPointer LP_src_x(a);
        vr128 V_dst = vseta_vr(0, 0, 0);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++)
            V_dst = vmacs_adj(V_dst, LP_src.load_post(), LP_src_x.load_post(), 0, 0);
        loops = N & 3;
        dsums_L(V_dst, V_dst, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);

        PConstScalar P_src = LP_src;
        PConstScalar P_src_x = LP_src_x;
        fr32 F_dst = get_VRQ0(V_dst);
        for (int i = 0; i < loops; i++)
            fpmac(F_dst, P_src[i].fr, P_src_x[i].fr, 0);

        return F_dst;
    }

    _AI AScalar max_abs() const {
        UnalignedQuadLoadPointer LP_src(a);
        vr128 V_dst = vseta_vr(0, 0, 0);
        int loops = N >> 2;
        unsigned int ar;
        mir30 mir;

        for (int i = 0; i < loops; i++)
            V_dst = vmax(V_dst, vabs(LP_src.load_post()));
        loops = N & 3;
        rmax_idx(ar, V_dst, VRQ0, V_dst, mir);

        PConstScalar P_src = LP_src;
        fr32 F_dst = get_VRQ0(V_dst);
        for (int i = 0; i < loops; i++)
            F_dst = max_fr(F_dst, abs_fr(P_src[i].fr));;

        return F_dst;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}

    _AI void normalize(const AScalarArray& x) {mul(x, x.sum_sq().f_invsqrt());}

    _AI void norm_sq(const struct AComplexArray& x);

    // out = x > y ? a : b;

    _AI void compGt(const AScalarArray& x, const AScalar& y,
                    const AScalar& aa,     const AScalar& bb) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_src_y = vreplicate_fr(y.fr);
        vr128 V_aa = vreplicate_fr(aa.fr);
        vr128 V_bb = vreplicate_fr(bb.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src_x = LP_src_x.load_post().vr;
            SP_dst.store_post(vsel(V_aa, V_bb, vgt(V_src_x, V_src_y)));
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp, P_src_x, INC1, VRQ0);
            sel(V_tmp, VRQ0, V_aa, VRQ0, V_bb, VRQ0, gt(V_tmp, VRQ0, V_src_y, VRQ0));
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    _AI void compGt(const AScalarArray& x, const AScalarArray& y,
                    const AScalar& aa,     const AScalar& bb) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x(x.a);
        UnalignedQuadLoadPointer  LP_src_y(y.a);
        UnalignedQuadStorePointer SP_dst(a);
        vr128 V_aa = vreplicate_fr(aa.fr);
        vr128 V_bb = vreplicate_fr(bb.fr);
        int loops = N >> 2;

        for (int i = 0; i < loops; i++) {
            vr128 V_src_x = LP_src_x.load_post().vr;
            vr128 V_src_y = LP_src_y.load_post().vr;
            SP_dst.store_post(vsel(V_aa, V_bb, vgt(V_src_x, V_src_y)));
        }
        loops = N & 3;
        SP_dst.flush();

        const AScalar* P_src_x = LP_src_x;
        const AScalar* P_src_y = LP_src_y;
        AScalar* P_dst = SP_dst;
        for (int i = 0; i < loops; i++) {
            vr128 V_tmp;
            load32x1_vr_postI(V_tmp, P_src_x, INC1, VRQ0);
            load32x1_vr_postI(V_tmp, P_src_y, INC1, VRQ1);
            sel(V_tmp, VRQ0, V_aa, VRQ0, V_bb, VRQ0, gt(V_tmp, VRQ0, V_tmp, VRQ1));
            store32x1_vr_postI(V_tmp, P_dst, INC1, VRQ0);
        }
    }

    // Matrix operations

    _AI void column(const struct AScalarMatrix& x, int col);

    void mul(const AScalarArray& x, const struct AScalarMatrix& y);
    void mul(const struct AScalarMatrix& x, const AScalarArray& y);
};

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AScalarArray
    \brief Wraps an abstract pointer to an AScalar and a length

    \fn AScalarArray::AScalarArray(int n, AScalar* ptr)
    \brief Constructor taking a length and a pointer

    \fn void AScalarArray::init(int n, AScalar* ptr)
    \brief Reinitialize with a length and a pointer

    \fn int AScalarArray::length()
    \brief Returns the number of elements

    \fn void AScalarArray::fill(const AScalar& x)
    \brief Fills array with copies of x

    \fn void AScalarArray::copy(const AScalarArray& x)
    \brief Copies array from the elements of x

    \fn void AScalarArray::add(const AScalarArray& x, const AScalar& y)
    \brief *this = x + y elementwise

    \fn void AScalarArray::add(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x + y elementwise

    \fn void AScalarArray::sub(const AScalarArray& x, const AScalar& y)
    \brief *this = x - y elementwise

    \fn void AScalarArray::sub(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x - y elementwise

    \fn void AScalarArray::mul(const AScalarArray& x, const AScalar& y)
    \brief *this = x * y elementwise

    \fn void AScalarArray::mul(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x * y elementwise

    \fn void AScalarArray::div(const AScalarArray& x, const AScalar& y)
    \brief *this = x / y elementwise

    \fn void AScalarArray::div(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x / y elementwise

    \fn void AScalarArray::mul_acc(const AScalarArray& x, const AScalar& y)
    \brief *this += x * y elementwise

    \fn void AScalarArray::mul_acc(const AScalarArray& x, const AScalarArray& y)
    \brief *this += x * y elementwise

    \fn void AScalarArray::max(const AScalarArray& x, const AScalarArray& y)
    \brief *this = max(x, y) elementwise

    \fn void AScalarArray::min(const AScalarArray& x, const AScalarArray& y)
    \brief *this = min(x, y) elementwise

    \fn void AScalarArray::clamp(const AScalarArray& x, const AScalar& low, const AScalar& high)
    \brief *this = max(min(x, high), low) elementwise

    \fn void AScalarArray::abs(const AScalarArray& x)
    \brief *this = abs(x) elementwise

    \fn void AScalarArray::f_inv(const AScalarArray& x)
    \brief *this = (1.0 / x) elementwise

    \fn void AScalarArray::f_invsqrt(const AScalarArray& x)
    \brief *this = (1.0 / sqrt(x)) elementwise

    \fn void AScalarArray::f_sigmoid(const AScalarArray& x)
    \brief *this = (x < 0 ? 2**(x - 1) : 1 - 2**(-x - 1)) elementwise

    \fn void AScalarArray::f_log2(const AScalarArray& x)
    \brief *this = log2(x) elementwise

    \fn void AScalarArray::f_pow2(const AScalarArray& x)
    \brief *this = 2**x elementwise

    \fn void AScalarArray::f_sqrt(const AScalarArray& x)
    \brief *this = sqrt(x) elementwise

    \fn void AScalarArray::sine_turns(const AScalarArray& x)
    \brief *this = sin(2π * x) elementwise

    \fn void AScalarArray::cosine_turns(const AScalarArray& x)
    \brief *this = cos(2π * x) elementwise

    \fn void AScalarArray::sine_rads(const AScalarArray& x)
    \brief *this = sin(x) elementwise

    \fn void AScalarArray::cosine_rads(const AScalarArray& x)
    \brief *this = cos(x) elementwise

    \fn void AScalarArray::f_exp(const AScalarArray& x)
    \brief *this = exp(x) elementwise

    \fn void AScalarArray::f_log(const AScalarArray& x)
    \brief *this = log(x) elementwise

    \fn void AScalarArray::inverse(const AScalarArray& x)
    \brief *this = (1.0 / x) elementwise

    \fn AScalar AScalarArray::sum()
    \brief Returns the sum of the elements

    \fn AScalar AScalarArray::sum_sq()
    \brief Returns the sum of the squares of the elements

    \fn AScalarArray AScalarArray::dot(const AScalarArray& x)
    \brief Returns the inner product with x

    \fn AScalar AScalarArray::max_abs()
    \brief Returns the maximum absolute value of the elements

    \fn AScalar AScalarArray::norm()
    \brief Returns the Euclidean norm of the vector

    \fn void AScalarArray::normalize()
    \brief Normalizes the vector

    \fn void AScalarArray::norm_sq(const AComplexArray& x)
    \brief *this = (x.r()**2 + x.i()**2) elementwise

    \fn void AScalarArray::compGt(const AScalarArray& x, const AScalar& y, const AScalar& aa, const AScalar& bb)
    \brief *this = (x > y ? aa : bb) elementwise

    \fn void AScalarArray::compGt(const AScalarArray& x, const AScalarArray& y, const AScalar& aa, const AScalar& bb)
    \brief *this = (x > y ? aa : bb) elementwise

    \fn void AScalarArray::column(const struct AScalarMatrix& x, int col);
    \brief *this = x[:, col]

    \fn void AScalarArray::mul(const AScalarArray& x, const struct AScalarMatrix& y)
    \brief *this = x * y

    \fn void AScalarArray::mul(const struct AScalarMatrix& x, const AScalarArray& y)
    \brief *this = x * y
*/
