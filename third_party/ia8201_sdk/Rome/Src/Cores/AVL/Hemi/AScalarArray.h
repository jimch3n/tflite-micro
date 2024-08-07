/************************************************************************//**
 * @file    AVL/Hemi/AScalarArray.h
 *
 * @brief   ScalarArray wrapper for HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ASCALARARRAY_H
#define ASCALARARRAY_H

#include "APair.h"

struct AScalarArray
{
    AScalar* a;
    int N;

    _AI AScalarArray() {}
    _AI AScalarArray(int n, AScalar* ptr) : a(ptr), N(n) {}

    _AI void init(int n, AScalar* ptr) {a = ptr; N = n;}
    _AI int length() {return N;}

    _AI AScalarArray& operator= (const AScalarArray& x) {
        if (&x != this)
            copy(x);
        return *this;
    }

    _AI operator AScalar* () {return a;}
    _AI operator const AScalar* () const {return a;}
    _AI AScalar& operator[] (int i) const {return ((AScalar*) a)[i];}

    _AI bool operator== (const AScalarArray& x) const {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer LP_a(a);
        UnalignedPairLoadPointer LP_b(x.a);
        atbool bx2 = 0;

        for (int i = 0; i < (N >> 1); i++)
            bx2 = orb2(bx2, vne(LP_a.load_post(), LP_b.load_post()));

        unsigned ne2 = move_ar_bbr(bx2);
        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            ne2 |= ne_fr(*LP_a, *LP_b);
        }

        return ne2 == 0;
    }

    _AI bool operator!= (const AScalarArray& x) const {
        return !(*this == x);
    }

    _AI void fill(const AScalar& x) {
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_src = vreplicate_fr(x.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(V_src);
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(x.fr, (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void copy(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        
        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(LP_src.load_post());
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fr32_loadi((fr32*) LP_src.ptr, 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void add(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_src_y = vreplicate_fr(y.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src.load_post(), V_src_y, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fadds(*LP_src, y.fr, 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void add(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fadds(*LP_src_x, *LP_src_y, 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void sub(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_src_y = vreplicate_fr(y.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src.load_post(), V_src_y, 10));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fadds(*LP_src, y.fr, 2),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void sub(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 10));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fadds(*LP_src_x, *LP_src_y, 2),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void mul(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmulf(LP_src.load_post(), y.fr, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fmuls(*LP_src, y.fr, 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void mul(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmuls(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fmuls(*LP_src_x, *LP_src_y, 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void div(const AScalarArray& x, const AScalar& y) {mul(x, y.inverse());}

    _AI void div(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_2 = vseta_vr(2, 0);

        for (int i = 0; i < (N >> 1); i++) {
            // One iteration of Newton's method
            vr64 V_src = LP_src_y.load_post().vr;
            vr64 V_inv = vr64_pair(inv(get_VRH(V_src)), inv(get_VRL(V_src)));
            V_inv = vmuls(V_inv, vmacs(V_2, V_inv, V_src, 3, 0), 0);
            SP_dst.store_post(vmuls(LP_src_x.load_post(), V_inv, 0));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fmuls(*LP_src_x, LP_src_y->inverse(), 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void mul_acc(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairLoadPointer  LP_dst(a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmacf(LP_dst.load_post(),
                                    LP_src.load_post(), y.fr, 0, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fmacs(*LP_dst, *LP_src, y.fr, 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void mul_acc(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairLoadPointer  LP_dst(a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmacs(LP_dst.load_post(),
                                    LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fmacs(*LP_dst.ptr, *LP_src_x, *LP_src_y, 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void max(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmax(LP_src_x.load_post(),
                                   LP_src_y.load_post()));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(max_fr(*LP_src_x, *LP_src_y),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void min(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmin(LP_src_x.load_post(),
                                   LP_src_y.load_post()));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(min_fr(*LP_src_x, *LP_src_y),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void clamp(const AScalarArray& x, const AScalar& low, const AScalar& high) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_low = vreplicate_fr(low.fr);
        vr64 V_high = vreplicate_fr(high.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmax(V_low, vmin(V_high, LP_src.load_post())));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(max_fr(low.fr, min_fr(high.fr, *LP_src)),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void abs(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vabs(LP_src.load_post()));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(abs_fr(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void f_inv(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vr64_pair(inv(get_VRH(V_src)),
                                        inv(get_VRL(V_src))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(inv(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void f_invsqrt(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vr64_pair(invsqrt(get_VRH(V_src)),
                                        invsqrt(get_VRL(V_src))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(invsqrt(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void f_sigmoid(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vr64_pair(sigmoid(get_VRH(V_src)),
                                        sigmoid(get_VRL(V_src))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(sigmoid(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void f_log2(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vr64_pair(log2(get_VRH(V_src)),
                                        log2(get_VRL(V_src))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(log2(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void f_pow2(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vr64_pair(pow2(get_VRH(V_src)),
                                        pow2(get_VRL(V_src))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(pow2(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void f_sqrt(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            vr64 V_tmp = vr64_pair(invsqrt(get_VRH(V_src)),
                                   invsqrt(get_VRL(V_src)));
            SP_dst.store_post(vmuls(V_src, V_tmp, 0));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32 F_src = LP_src->fr;
            fr32_storei(fmuls(F_src, invsqrt(F_src), 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void sine_turns(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vr64_pair(sine(get_VRH(V_src)),
                                        sine(get_VRL(V_src))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(sine(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void cosine_turns(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vr64_pair(cosine(get_VRH(V_src)),
                                        cosine(get_VRL(V_src))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(cosine(*LP_src),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void sine_rads(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_inv2pi = vseta_vr(14, 6);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_tmp = vmuls(LP_src.load_post(), V_inv2pi, 0);
            SP_dst.store_post(vr64_pair(sine(get_VRH(V_tmp)),
                                        sine(get_VRL(V_tmp))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(sine(fmuls(*LP_src.ptr, seta_fr(14, 6), 0)),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void cosine_rads(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_inv2pi = vseta_vr(14, 6);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_tmp = vmuls(LP_src.load_post(), V_inv2pi, 0);
            SP_dst.store_post(vr64_pair(cosine(get_VRH(V_tmp)),
                                        cosine(get_VRL(V_tmp))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(cosine(fmuls(*LP_src.ptr, seta_fr(14, 6), 0)),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void f_exp(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_log2e = vseta_vr(9, 0);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_tmp = vmuls(LP_src.load_post(), V_log2e, 0);
            SP_dst.store_post(vr64_pair(pow2(get_VRH(V_tmp)),
                                        pow2(get_VRL(V_tmp))));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(pow2(fmuls(*LP_src, seta_fr(9, 0), 0)),
                        (fr32*) SP_dst.ptr, 0);
        }
    }
    
    _AI void f_log(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_ln2 = vseta_vr(10, 0);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            SP_dst.store_post(vmuls(V_ln2,
                                    vr64_pair(log2(get_VRH(V_src)),
                                              log2(get_VRL(V_src))), 0));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(fmuls(log2(*LP_src), seta_fr(10, 0), 0),
                        (fr32*) SP_dst.ptr, 0);
        }
    }
    
    _AI void inverse(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_2 = vseta_vr(2, 0);

        for (int i = 0; i < (N >> 1); i++) {
            // One iteration of Newton's method
            vr64 V_src = LP_src.load_post().vr;
            vr64 V_inv = vr64_pair(inv(get_VRH(V_src)), inv(get_VRL(V_src)));
            SP_dst.store_post(vmuls(V_inv, vmacs(V_2, V_inv, V_src, 3, 0), 0));
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(LP_src->inverse(),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI AScalar sum() const {
        UnalignedPairLoadPointer LP_src(a);
        vr64 V_dst = vseta_vr(0, 0);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            V_dst = vsum_perm(V_dst, V_src, V_src, VSEL_ZERO, VSEL_YH_XL, 0, 0);
        }

        if (N&1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            return fadds(get_VRL(V_dst), *LP_src, 0);
        }

        return get_VRL(V_dst);
    }

    _AI AScalar sum_sq() const {
        UnalignedPairLoadPointer LP_src(a);
        vr64 V_dst = vseta_vr(0, 0);

        for (int i = 0; i < (N >> 1); i++) {
            vr64 V_src = LP_src.load_post().vr;
            V_dst = cmac(V_dst, V_src, V_src, CONJ_Y);
        }

        if (N&1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32 F_src = LP_src->fr;
            return fmacs(get_VRL(V_dst), F_src, F_src, 0);
        }

        return get_VRL(V_dst);
    }

    _AI AScalar dot(const AScalarArray& x) const {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer LP_src(x.a);
        UnalignedPairLoadPointer LP_src_x(a);
        vr64 V_dst = vseta_vr(0, 0);

        for (int i = 0; i < (N >> 1); i++)
            V_dst = vblend_add(V_dst, LP_src.load_post(), LP_src_x.load_post(),
                               VB_ZERO, VB_YHXH_YLXL, 0, 0, 0, 0);

        if (N&1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            return fmacs(get_VRL(V_dst), *LP_src, *LP_src_x, 0);
        }

        return get_VRL(V_dst);
    }

    _AI AScalar max_abs() const {
        UnalignedPairLoadPointer LP_src(a);
        vr64 V_dst = vseta_vr(0, 0);
        fr32 F_dst;
        unsigned int ar;
        mir18 mir;
        vmaxmin_init(V_dst,V_dst,mir);

        for (int i = 0; i < (N >> 1); i++)
            V_dst = vmax(V_dst, vabs(LP_src.load_post()));

        rmax_idx(ar, F_dst, V_dst, mir);
	ar = ar + 1; // Temporary fix for 'unused-but-set-variable' warning

        if (N&1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            return max_fr(F_dst, abs_fr(*LP_src));
        }

        return F_dst;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}

    _AI void normalize(const AScalarArray& x) {mul(x, x.sum_sq().f_invsqrt());}
    
    _AI void norm_sq(const struct AComplexArray& x);

    // out = x > y ? a : b;

    _AI void compGt(const AScalarArray& x, const AScalar& y,
                    const AScalar& aa,     const AScalar& bb) {
        AVL_ASSERT(N == x.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_src_y = vreplicate_fr(y.fr);
        vr64 V_aa = vreplicate_fr(aa.fr);
        vr64 V_bb = vreplicate_fr(bb.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vsel(V_aa, V_bb,
                                   vgt(LP_src_x.load_post(), V_src_y)));
        SP_dst.flush();

        if (N&1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(get_VRL(vsel(V_aa, V_bb,
                                     vgt(vreplicate_fr(*LP_src_x), V_src_y))),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    _AI void compGt(const AScalarArray& x, const AScalarArray& y,
                    const AScalar& aa,     const AScalar& bb) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedPairLoadPointer  LP_src_x(x.a);
        UnalignedPairLoadPointer  LP_src_y(y.a);
        UnalignedPairStorePointer SP_dst(a);
        vr64 V_aa = vreplicate_fr(aa.fr);
        vr64 V_bb = vreplicate_fr(bb.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vsel(V_aa, V_bb,
                                   vgt(LP_src_x.load_post(),
                                       LP_src_y.load_post())));
        SP_dst.flush();

        if (N&1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            fr32_storei(get_VRL(vsel(V_aa, V_bb,
                                     vgt(vreplicate_fr(*LP_src_x),
                                         vreplicate_fr(*LP_src_y)))),
                        (fr32*) SP_dst.ptr, 0);
        }
    }

    // Matrix operations

    _AI void column(const struct AScalarMatrix& x, int col);

    void mul(const AScalarArray& x, const struct AScalarMatrix& y);
    void mul(const struct AScalarMatrix& x, const AScalarArray& y);

#if COMPILER_BECOMES_GOOD_ENOUGH_TO_INLINE_THESE_CALLS
    _AI void map(AScalar (AScalar::* fun)() const) {
        for (int i = 0; i < N; i++)
            a[i] = (a[i].*fun)();
    }
#endif
};

#endif
