/************************************************************************//**
 * @file    AVL\DeltaMax\AComplexArray.h
 *
 * @brief   ComplexArray wrapper for DeltaMax
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEXARRAY_H
#define ACOMPLEXARRAY_H

/**************************************************************************//**
 * @addtogroup dmx_avl
 * @{
 *****************************************************************************/

#include "AScalarArray.h"
#include "AComplex.h"

struct AComplexArray
{
    AComplex* a;
    int N;

    _AI AComplexArray() {}
    _AI AComplexArray(int n, AComplex* ptr) : a(ptr), N(n) {}

    _AI void init(int n, AComplex* ptr) {a = ptr; N = n;}
    _AI int length() {return N;}

    _AI AComplexArray& operator= (const AComplexArray& x) {
        if (&x != this)
            copy(x);
        return *this;
    }

    _AI operator AComplex* () {return a;}
    _AI operator const AComplex* () const {return a;}
    _AI AComplex& operator[] (int i) {return a[i];}
    _AI const AComplex operator[] (int i) const {
        vr128 tmp;
        load32x2_vr_idxR(tmp, a, i, VRL);

        AComplex z;
        z.fr0 = get_VRQ0(tmp);
        z.fr1 = get_VRQ1(tmp);
        return z;
    }

    _AI bool operator== (const AComplexArray& x) const {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer LP_a((const AScalar*) a);
        UnalignedQuadLoadPointer LP_b((const AScalar*) x.a);
        xtbool4 bx4 = (xtbool4) 15;

        for (int i = 0; i < (N >> 1); i++)
            bx4 = andb4(bx4, veq(LP_a.load_post(), LP_b.load_post()));

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            bx4 = andb4(bx4, orb4(veq(LP_a.load_post(), LP_b.load_post()),
                                  (xtbool4) 12));
        }

        return XT_ALL4(bx4);
    }

    _AI bool operator!= (const AComplexArray& x) const {
        return !(*this == x);
    }

    _AI void fill(const AComplex& x) {
        UnalignedQuadStorePointer SP_dst((AScalar*) a);
        vr128 V_src = vpermsi(vreplicate_fr(x.fr0), vreplicate_fr(x.fr1), 0, 4);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(V_src);
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            store32x2_vr_idxI(V_src, SP_dst.ptr, 0, VRL);
        }
    }

    _AI void copy(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(LP_src.load_post());
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            store32x2_vr_idxI(V_tmp, (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void conj(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++) {
            vr128 V_dst = LP_src.load_post().vr;
            s_neg(V_dst, VRQ1, V_dst, VRQ1);
            s_neg(V_dst, VRQ3, V_dst, VRQ3);
            SP_dst.store_post(V_dst);
        }
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            s_neg(V_tmp, VRQ1, V_tmp, VRQ1);
            store32x2_vr_idxI(V_tmp, (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void add(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);
        vr128 V_src = vpermsi(vreplicate_fr(y.fr0), vreplicate_fr(y.fr1), 0, 4);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src.load_post(), V_src, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            store32x2_vr_idxI(vadds(V_tmp, V_src, 0),
                              (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void add(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x((const AScalar*) x.a);
        UnalignedQuadLoadPointer  LP_src_y((const AScalar*) y.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_src_x, V_src_y;
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
            store32x2_vr_idxI(vadds(V_src_x, V_src_y, 0),
                              (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void sub(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);
        vr128 V_src = vpermsi(vreplicate_fr(y.fr0), vreplicate_fr(y.fr1), 0, 4);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src.load_post(), V_src, 0xf0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            store32x2_vr_idxI(vadds(V_tmp, V_src, 0xf0),
                              (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void sub(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x((const AScalar*) x.a);
        UnalignedQuadLoadPointer  LP_src_y((const AScalar*) y.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vadds(LP_src_x.load_post(),
                                    LP_src_y.load_post(), 0xf0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_src_x, V_src_y;
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
            store32x2_vr_idxI(vadds(V_src_x, V_src_y, 0xf0),
                              (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void mul(const AComplexArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);
        vr128 V_src = vreplicate_fr(y.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmuls(LP_src.load_post(), V_src, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            store32x2_vr_idxI(vmuls(V_tmp, V_src, 0),
                              (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void mul(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);
        vr128 V_src = vpermsi(vreplicate_fr(y.fr0), vreplicate_fr(y.fr1), 0, 4);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(cmul_x2(LP_src.load_post(), V_src, CONJ_NONE));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            cmul_L(V_tmp, V_tmp, V_src, CONJ_NONE);
            store32x2_vr_idxI(V_tmp, (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void mul(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x((const AScalar*) x.a);
        UnalignedQuadLoadPointer  LP_src_y((const AScalar*) y.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(cmul_x2(LP_src_x.load_post(),
                                      LP_src_y.load_post(), CONJ_NONE));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_src_x, V_src_y, V_dst;
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
            cmul_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
            store32x2_vr_idxI(V_dst, (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void mul_conj(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x((const AScalar*) x.a);
        UnalignedQuadLoadPointer  LP_src_y((const AScalar*) y.a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(cmul_x2(LP_src_x.load_post(),
                                      LP_src_y.load_post(), CONJ_Y));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_src_x, V_src_y, V_dst;
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
            cmul_L(V_dst, V_src_x, V_src_y, CONJ_Y);
            store32x2_vr_idxI(V_dst, (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void mul_acc(const AComplexArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
        UnalignedQuadLoadPointer  LP_dst((const AScalar*) a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);
        vr128 V_src_y = vreplicate_fr(y.fr);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(vmacs_adj(LP_dst.load_post(),
                                        LP_src.load_post(),
                                        V_src_y, 0, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp, V_dst;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            load32x2_vr_idxI(V_dst, (const AScalar*) LP_dst, IDX0, VRL);
            store32x2_vr_idxI(vmacs_adj(V_dst, V_tmp, V_src_y, 0, 0),
                              (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI void mul_acc(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x((const AScalar*) x.a);
        UnalignedQuadLoadPointer  LP_src_y((const AScalar*) y.a);
        UnalignedQuadLoadPointer  LP_dst((const AScalar*) a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(cmac_adj_x2(LP_dst.load_post(),
                                          LP_src_x.load_post(),
                                          LP_src_y.load_post(),
                                          CONJ_NONE, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_src_x, V_src_y, V_dst;
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
            load32x2_vr_idxI(V_dst,   (const AScalar*) LP_dst,   IDX0, VRL);
            cmac_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
            store32x2_vr_idxI(V_dst, (AScalar*) SP_dst, IDX0, VRL);
        }

    }

    _AI void mul_conj_acc(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        UnalignedQuadLoadPointer  LP_src_x((const AScalar*) x.a);
        UnalignedQuadLoadPointer  LP_src_y((const AScalar*) y.a);
        UnalignedQuadLoadPointer  LP_dst((const AScalar*) a);
        UnalignedQuadStorePointer SP_dst((AScalar*) a);

        for (int i = 0; i < (N >> 1); i++)
            SP_dst.store_post(cmac_adj_x2(LP_dst.load_post(),
                                          LP_src_x.load_post(),
                                          LP_src_y.load_post(),
                                          CONJ_Y, 0));
        SP_dst.flush();

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_src_x, V_src_y, V_dst;
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
            load32x2_vr_idxI(V_dst,   (const AScalar*) LP_dst,   IDX0, VRL);
            cmac_L(V_dst, V_src_x, V_src_y, CONJ_Y);
            store32x2_vr_idxI(V_dst, (AScalar*) SP_dst, IDX0, VRL);
        }
    }

    _AI AComplex sum() const {
        UnalignedQuadLoadPointer LP_src((const AScalar*) a);
        vr128 V_dst = vseta_vr(0, 0, 0);

        for (int i = 0; i < (N >> 1); i++)
            V_dst = vadds(V_dst, LP_src.load_post(), 0);
        csums_L(V_dst, V_dst, 0, 0);

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            V_dst = vadds(V_dst, V_tmp, 0);
        }

        AComplex z;
        z.fr0 = get_VRQ0(V_dst);
        z.fr1 = get_VRQ0(V_dst);
        return z;
    }

    _AI AScalar norm_sq() const {
        UnalignedQuadLoadPointer LP_src((const AScalar*) a);
        vr128 V_dst = vseta_vr(0, 0, 0);

        for (int i = 0; i < (N >> 1); i++) {
            vr128 V_src = LP_src.load_post().vr;
            V_dst = cmac_adj_x2(V_dst, V_src, V_src, CONJ_Y, 0);
        }
        csums_L(V_dst, V_dst, 0, 0);

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_tmp;
            load32x2_vr_idxI(V_tmp, (const AScalar*) LP_src, IDX0, VRL);
            cmac_L(V_dst, V_tmp, V_tmp, CONJ_Y);
        }

        return get_VRQ0(V_dst);
    }

    _AI AComplex dot(const AComplexArray& x) const {
        AVL_ASSERT(N == x.N);
        UnalignedQuadLoadPointer LP_src((const AScalar*) a);
        UnalignedQuadLoadPointer LP_src_x((const AScalar*) x.a);
        vr128 V_dst = vseta_vr(0, 0, 0);

        for (int i = 0; i < (N >> 1); i++)
            V_dst = cmac_adj_x2(V_dst, LP_src.load_post(), LP_src_x.load_post(),
                                CONJ_Y, 0);
        csums_L(V_dst, V_dst, 0, 0);

        if (N & 1) {
            #ifdef __XTENSA__
            #pragma frequency_hint NEVER
            #endif
            vr128 V_src, V_src_x;
            load32x2_vr_idxI(V_src, (const AScalar*) LP_src, IDX0, VRL);
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            cmac_L(V_dst, V_src, V_src_x, CONJ_Y);
        }

        AComplex z;
        z.fr0 = get_VRQ0(V_dst);
        z.fr1 = get_VRQ1(V_dst);
        return z;
    }

    _AI AScalar norm() const {return norm_sq().f_sqrt();}

    _AI void normalize(const AComplexArray& x) {mul(x, x.norm_sq().f_invsqrt());}
    
    _AI void inverse(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        PConstComplex  P_src(x.a);
        PComplex       P_dst(a);

        for (int i = 0; i < N; i++)
            P_dst[i] = P_src[i].inverse();
    }

    // Matrix operations

    _AI void column(const struct AComplexMatrix& x, int col);

    void mul(const AComplexArray& x, const struct AComplexMatrix& y);
    void mul(const struct AComplexMatrix& x, const AComplexArray& y);
    void mul_conj(const struct AComplexMatrix& x, const AComplexArray& y);
};

_AI void AScalarArray::norm_sq(const struct AComplexArray& x) {
    AVL_ASSERT(N == x.N);
    UnalignedQuadLoadPointer  LP_src((const AScalar*) x.a);
    UnalignedQuadStorePointer SP_dst((AScalar*) a);
    perm16 perm = set_perm16(0x6420);
    int loops = N >> 2;

    for (int i = 0; i < loops; i++) {
        AQuad src0 = LP_src.load_post().vr;
        AQuad src1 = LP_src.load_post().vr;

        SP_dst.store_post(vperm(cmul_x2(src0, src0, CONJ_Y),
                                cmul_x2(src1, src1, CONJ_Y), perm));
    }
    loops = N & 3;
    SP_dst.flush();

    PConstComplex P_src = (const AScalar*) LP_src;
    PScalar       P_dst = SP_dst;

    for (int i = 0; i < loops; i++)
        P_dst[i]= P_src[i].norm_sq();
}

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AComplexArray
    \brief Wraps an abstract pointer to an AComplex and a length

    \fn AComplexArray::AComplexArray(int n, AComplex* ptr)
    \brief Constructor taking a length and a pointer

    \fn void AComplexArray::init(int n, AComplex* ptr)
    \brief Reinitialize with a length and a pointer

    \fn int AComplexArray::length()
    \brief Returns the number of elements

    \fn void AComplexArray::fill(const AComplex& x)
    \brief Fills array with copies of x

    \fn void AComplexArray::copy(const AComplexArray& x)
    \brief Copies array from the elements of x

    \fn void AComplexArray::conj(const AComplexArray& x)
    \brief *this = conj(x) elementwise

    \fn void AComplexArray::add(const AComplexArray& x, const AComplex& y)
    \brief *this = x + y elementwise

    \fn void AComplexArray::add(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x + y elementwise

    \fn void AComplexArray::sub(const AComplexArray& x, const AComplex& y)
    \brief *this = x - y elementwise

    \fn void AComplexArray::sub(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x - y elementwise

    \fn void AComplexArray::mul(const AComplexArray& x, const AScalar& y)
    \brief *this = x * y elementwise

    \fn void AComplexArray::mul(const AComplexArray& x, const AComplex& y)
    \brief *this = x * y elementwise

    \fn void AComplexArray::mul(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x * y elementwise

    \fn void AComplexArray::mul_conj(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x * y.conj() elementwise

    \fn void AComplexArray::mul_acc(const AComplexArray& x, const AScalar& y)
    \brief *this += x * y elementwise

    \fn void AComplexArray::mul_acc(const AComplexArray& x, const AComplexArray& y)
    \brief *this += x * y elementwise

    \fn void AComplexArray::mul_conj_acc(const AComplexArray& x, const AComplexArray& y)
    \brief *this += x * y.conj() elementwise

    \fn AComplex AComplexArray::sum()
    \brief Returns the sum of the elements

    \fn AComplex AComplexArray::norm_sq()
    \brief Returns the sum of (r()**2 + i()**2) for each element

    \fn AComplexArray AComplexArray::dot(const AComplexArray& x)
    \brief Returns the inner product with x

    \fn AComplex AComplexArray::norm()
    \brief Returns the Euclidean norm of the vector

    \fn void AComplexArray::normalize()
    \brief Normalizes the vector

    \fn void AComplexArray::inverse(const AComplexArray& x)
    \brief *this = (1.0 / x) elementwise

    \fn void AComplexArray::column(const struct AComplexMatrix& x, int col);
    \brief *this = x[:, col]

    \fn void AComplexArray::mul(const AComplexArray& x, const struct AComplexMatrix& y)
    \brief *this = x * y

    \fn void AComplexArray::mul(const struct AComplexMatrix& x, const AComplexArray& y)
    \brief *this = x * y

    \fn void AComplexArray::mul_conj(const struct AComplexMatrix& x, const AComplexArray& y)
    \brief *this = x * y.conj()
*/
