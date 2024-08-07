/************************************************************************//**
 * @file    AVL/DMX1A/AComplexVector.h
 *
 * @brief   Complex Vector wrapper for DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEXVECTOR_H
#define ACOMPLEXVECTOR_H

/**************************************************************************//**
 * @addtogroup dmx1a_avl
 * @{
 *****************************************************************************/

#include "AComplex.h"
#include "AVector.h"

template <int N>
struct AComplexVector
{
    static const int NV = (N + 1) / 2;

    vr128 a[NV];

    _AI AComplexVector() {}
    _AI AComplexVector(const AComplexVector& x) {copy(x);}
    _AI AComplexVector& operator= (const AComplexVector& x) {
        if (&x != this) copy(x);
        return *this;
    }
    _AI AComplexVector(const AVector<N>& x) {*this = x;}
    _AI AComplexVector& operator= (const AVector<N>& x) {
        perm16 perm = set_perm16(0x6160);
        vr128 V_src = vseta_vr(0, 0, 0);
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            load32x2_vr_postI(V_src, P_src, INC1, VRL);
            store32x4_vr_vr_postI_perm(V_src, V_src, P_dst, INC1, perm);
        }

        return *this;
    }

    _AI static int length() {return N;}

    _AI operator AComplex* () {return (AComplex*) a;}
    _AI operator const AComplex* () const {return (const AComplex*) a;}
    _AI AComplex& operator[] (int i) const {return ((AComplex*) a)[i];}
            
    static const int PAD_MASK = 12;

    _AI xtbool operator== (const AComplexVector& x) const {
        vr128 V_a, V_b;
        const vr128* P_a = a;
        const vr128* P_b = x.a;
        xtbool4 bx4 = int_to_xt_bool4(15);

        for (int i = 0; i < N/2; i++) {
            load32x4_vr_postI(V_a, P_a, INC1);
            load32x4_vr_postI(V_b, P_b, INC1);
            bx4 = andb4(bx4, veq(V_a, V_b));
        }
        if (N&1) {
            load32x4_vr_postI(V_a, P_a, INC1);
            load32x4_vr_postI(V_b, P_b, INC1);
            bx4 = andb4(bx4, orb4(veq(V_a, V_b), int_to_xt_bool4(PAD_MASK)));
        }

        return XT_ALL4(bx4);
    }

    _AI AComplexVector& fill(const AComplex& x) {
        vr128 V_src = vreplicate_hr(x.vr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(V_src, P_dst, INC1);

        return *this;
    }

    _AI AComplexVector& copy(const AComplexVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(V_src, P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& add(const AComplexVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(vadds(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& sub(const AComplexVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(vadds(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0xf0), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul(const AComplexVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(cmul_x2(load32x4_vr_idxI(P_dst, IDX0),
                                       V_src, CONJ_NONE), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_conj(const AComplexVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(cmul_x2(load32x4_vr_idxI(P_dst, IDX0),
                                       V_src, CONJ_Y), P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_acc(const AComplexVector& x, const AComplexVector& y) {
        const vr128* P_src_x = x.a;
        const vr128* P_src_y = y.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src_x, V_src_y;
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            load32x4_vr_postI(V_src_y, P_src_y, INC1);
            store32x4_vr_postI(cmac_adj_x2(load32x4_vr_idxI(P_dst, IDX0),
                                           V_src_x, V_src_y, CONJ_NONE, 0),
                               P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_conj_acc(const AComplexVector& x, const AComplexVector& y) {
        const vr128* P_src_x = x.a;
        const vr128* P_src_y = y.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src_x, V_src_y;
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            load32x4_vr_postI(V_src_y, P_src_y, INC1);
            store32x4_vr_postI(cmac_adj_x2(load32x4_vr_idxI(P_dst, IDX0),
                                           V_src_x, V_src_y, CONJ_Y, 0),
                               P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& mul_acc(const AComplexVector& x, const AComplex& y) {
        vr128 V_src_x;
        vr128 V_src_y = vreplicate_hr(y.vr);
        const vr128* P_src_x = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            store32x4_vr_postI(cmac_adj_x2(load32x4_vr_idxI(P_dst, IDX0),
                                           V_src_x, V_src_y, CONJ_NONE, 0),
                               P_dst, INC1);
        }
        return *this;
    }

    _AI AComplexVector& add(const AComplex& x) {
        vr128 V_src = vreplicate_hr(x.vr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(vadds(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        return *this;
    }

    _AI AComplexVector& sub(const AComplex& x) {
        vr128 V_src = vreplicate_hr(x.vr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(vadds(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0xf0), P_dst, INC1);
        return *this;
    }

    _AI AComplexVector& mul(const AComplex& x) {
        vr128 V_src = vreplicate_hr(x.vr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(cmul_x2(load32x4_vr_idxI(P_dst, IDX0),
                                       V_src, CONJ_NONE), P_dst, INC1);
        return *this;
    }

    _AI AComplexVector& mul(const AScalar& x) {
        vr128 V_src = vreplicate_fr(x.fr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(vmuls(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        return *this;
    }

    _AI AComplex sum() const {
        vr128 V_src;
        vr128 V_dst = vseta_vr(0, 0, 0);
        const vr128* P_src = a;

        for (int i = 0; i < N/2; i++) {
            load32x4_vr_postI(V_src, P_src, INC1);
            V_dst = vadds(V_dst, V_src, 0);
        }
        if (N&1) {
            load32x4_vr_postI(V_src, P_src, INC1);
            seta_vr(V_src, PAD_MASK, 0, 0, 0);
            V_dst = vadds(V_dst, V_src, 0);
        }

        csums_L(V_dst, V_dst, 0, 0);
        return get_VRL(V_dst);
    }

    _AI AScalar norm_sq() const {
        vr128 V_src;
        vr128 V_dst = vseta_vr(0, 0, 0);
        const vr128* P_src = a;

        for (int i = 0; i < N/2; i++) {
            load32x4_vr_postI(V_src, P_src, INC1);
            V_dst = cmac_adj_x2(V_dst, V_src, V_src, CONJ_Y, 0);
        }
        if (N&1) {
            load32x2_vr_postI(V_src, P_src, INC1, VRL);
            cmac_L(V_dst, V_src, V_src, CONJ_Y);
        }

        csums_L(V_dst, V_dst, 0, 0);
        return get_VRQ0(V_dst);
    }

    _AI AComplex dot(const AComplexVector& x) const {
        vr128 V_src;
        vr128 V_src_x;
        vr128 V_dst = vseta_vr(0, 0, 0);
        const vr128* P_src = a;
        const vr128* P_src_x = x.a;

        for (int i = 0; i < N/2; i++) {
            load32x4_vr_postI(V_src, P_src, INC1);
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            V_dst = cmac_adj_x2(V_dst, V_src, V_src_x, CONJ_Y, 0);
        }
        if (N&1) {
            load32x2_vr_postI(V_src, P_src, INC1, VRL);
            load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
            cmac_L(V_dst, V_src, V_src_x, CONJ_Y);
        }

        csums_L(V_dst, V_dst, 0, 0);
        return get_VRL(V_dst);
    }

    _AI AScalar norm() const        {return norm_sq().f_sqrt();}
    _AI AComplexVector& normalize() {return mul(norm_sq().f_invsqrt());}
};

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AComplexVector
    \brief Abstract fixed length vector of AComplex

    \fn AComplexVector::AComplexVector(const AComplexVector& x)
    \brief Copy constructor

    \fn static int AComplexVector::length()
    \brief Returns the number of elements

    \fn AComplexVector& AComplexVector::fill(const Acomplex& x)
    \brief Fills vector with copies of x

    \fn AComplexVector& AComplexVector::copy(const AComplexVector& x)
    \brief Copies vector from the elements of x

    \fn AComplexVector& AComplexVector::add(const AComplex& x)
    \brief Returns *this += x elementwise

    \fn AComplexVector& AComplexVector::add(const AComplexVector& x)
    \brief Returns *this += x elementwise

    \fn AComplexVector& AComplexVector::sub(const AComplex& x)
    \brief Returns *this -= x elementwise

    \fn AComplexVector& AComplexVector::sub(const AComplexVector& x)
    \brief Returns *this -= x elementwise

    \fn AComplexVector& AComplexVector::mul(const AScalar& x)
    \brief Returns *this *= x elementwise

    \fn AComplexVector& AComplexVector::mul(const AComplex& x)
    \brief Returns *this *= x elementwise

    \fn AComplexVector& AComplexVector::mul(const AComplexVector& x)
    \brief Returns *this *= x elementwise

    \fn AComplexVector& AComplexVector::mul_conj(const AComplexVector& x)
    \brief Returns *this *= x.conj() elementwise

    \fn AComplexVector& AComplexVector::mul_acc(const AComplexVector& x, const AComplex& y)
    \brief Returns *this += x * y elementwise

    \fn AComplexVector& AComplexVector::mul_acc(const AComplexVector& x, const AComplexVector& y)
    \brief Returns *this += x * y elementwise

    \fn AComplexVector& AComplexVector::mul_conj_acc(const AComplexVector& x, const AComplexVector& y)
    \brief Returns *this += x * y.conj() elementwise

    \fn AComplex AComplexVector::sum()
    \brief Returns the sum of the elements

    \fn AScalar AComplexVector::norm_sq()
    \brief Returns the sum of r()**2 + i()**2

    \fn AComplex AComplexVector::dot(const AComplexVector& x)
    \brief Returns the inner product with x

    \fn AScalar AComplexVector::norm()
    \brief Returns the sqrare root of the sum of r()**2 + i()**2

    \fn AComplexVector& AComplexVector::normalize()
    \brief Normalizes the vector
*/
