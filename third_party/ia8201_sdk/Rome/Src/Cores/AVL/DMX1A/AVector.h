/************************************************************************//**
 * @file    AVL/DMX1A/AVector.h
 *
 * @brief   Vector wrapper for DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef AVECTOR_H
#define AVECTOR_H

/**************************************************************************//**
 * @addtogroup dmx1a_avl
 * @{
 *****************************************************************************/

#include "AScalar.h"

template <int N>
struct AVector
{
    static const int NV = (N + 3) / 4;

    vr128 a[NV];

    _AI AVector() {}
    _AI AVector(const AVector& x) {copy(x);}
    _AI AVector& operator= (const AVector& x) {if (&x != this) copy(x); return *this;}

    _AI static int length() {return N;}

    _AI operator AScalar* () const {return (AScalar*) a;}
    _AI AScalar& operator[] (int i) const {return ((AScalar*) a)[i];}

    static const int PAD_MASK = (N&3) ? 15 & (15 << (N&3)) : 0;

    _AI xtbool operator== (const AVector& x) const {
        vr128 V_a, V_b;
        const vr128* P_a = a;
        const vr128* P_b = x.a;
        xtbool4 bx4 = int_to_xt_bool4(15);

        for (int i = 0; i < N/4; i++) {
            load32x4_vr_postI(V_a, P_a, INC1);
            load32x4_vr_postI(V_b, P_b, INC1);
            bx4 = andb4(bx4, veq(V_a, V_b));
        }
        if (N&3) {
            load32x4_vr_postI(V_a, P_a, INC1);
            load32x4_vr_postI(V_b, P_b, INC1);
            bx4 = andb4(bx4, orb4(veq(V_a, V_b), int_to_xt_bool4(PAD_MASK)));
        }

        return XT_ALL4(bx4);
    }

    _AI bool operator!= (const AVector& x) const {
        return !(*this == x);
    }

    _AI AVector& fill(const AScalar& x) {
        vr128 V_src = vreplicate_fr(x.fr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(V_src, P_dst, INC1);

        return *this;
    }

    _AI AVector& copy(const AVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(V_src, P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& add(const AVector& x) {
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

    _AI AVector& sub(const AVector& x) {
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

    _AI AVector& mul(const AVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(vmuls(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& div(const AVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;
        vr128 V_2 = vseta_vr(2, 0, 0);

        for (int i = 0; i < NV; i++) {
            // One iteration of Newton's method
            vr128 V_src, V_inv;
            load32x4_vr_postI(V_src, P_src, INC1);
            inv(V_inv, VRQ0, V_src, VRQ0);
            inv(V_inv, VRQ1, V_src, VRQ1);
            inv(V_inv, VRQ2, V_src, VRQ2);
            inv(V_inv, VRQ3, V_src, VRQ3);
            V_src = vmuls(V_inv, vmacs_adj(V_2, V_inv, V_src, 15, 0), 0);
            store32x4_vr_postI(vmuls(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& mul_acc(const AVector& x, const AVector& y) {
        const vr128* P_src_x = x.a;
        const vr128* P_src_y = y.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src_x, V_src_y;
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            load32x4_vr_postI(V_src_y, P_src_y, INC1);
            store32x4_vr_postI(vmacs_adj(load32x4_vr_idxI(P_dst, IDX0),
                                         V_src_x, V_src_y, 0, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& mul_acc(const AVector& x, const AScalar& y) {
        vr128 V_src_x;
        vr128 V_src_y = vreplicate_fr(y.fr);
        const vr128* P_src_x = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            store32x4_vr_postI(vmacs_adj(load32x4_vr_idxI(P_dst, IDX0),
                                         V_src_x, V_src_y, 0, 0), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& add(const AScalar& x) {
        vr128 V_src = vreplicate_fr(x.fr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(vadds(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        return *this;
    }

    _AI AVector& sub(const AScalar& x) {
        vr128 V_src = vreplicate_fr(x.fr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(vadds(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0xf0), P_dst, INC1);
        return *this;
    }

    _AI AVector& mul(const AScalar& x) {
        vr128 V_src = vreplicate_fr(x.fr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(vmuls(load32x4_vr_idxI(P_dst, IDX0),
                                     V_src, 0), P_dst, INC1);
        return *this;
    }

    _AI AVector& div(const AScalar& x) {return mul(x.inverse());}

    _AI AVector& abs() {
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
           store32x4_vr_postI(vabs(load32x4_vr_idxI(P_dst, IDX0)),
                              P_dst, INC1);

        return *this;
    }

    _AI AVector& max(const AVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(vmax(load32x4_vr_idxI(P_dst, IDX0), V_src), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& min(const AVector& x) {
        const vr128* P_src = x.a;
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++) {
            vr128 V_src;
            load32x4_vr_postI(V_src, P_src, INC1);
            store32x4_vr_postI(vmin(load32x4_vr_idxI(P_dst, IDX0), V_src), P_dst, INC1);
        }
        return *this;
    }

    _AI AVector& clamp(const AScalar& low, const AScalar& high) {
        vr128 V_low = vreplicate_fr(low.fr);
        vr128 V_high= vreplicate_fr(high.fr);
        vr128* P_dst = a;

        for (int i = 0; i < NV; i++)
            store32x4_vr_postI(vmax(V_low, vmin(V_high, load32x4_vr_idxI(P_dst, IDX0))),
                               P_dst, INC1);
        return *this;
    }

    _AI AScalar sum() const {
        vr128 V_src;
        vr128 V_dst = vseta_vr(0, 0, 0);
        const vr128* P_src = a;

        for (int i = 0; i < N/4; i++) {
            load32x4_vr_postI(V_src, P_src, INC1);
            V_dst = vadds(V_dst, V_src, 0);
        }
        if (N&3) {
            load32x4_vr_postI(V_src, P_src, INC1);
            seta_vr(V_src, PAD_MASK, 0, 0, 0);
            V_dst = vadds(V_dst, V_src, 0);
        }

        dsums_L(V_dst, V_dst, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);
        return get_VRQ0(V_dst);
    }

    _AI AScalar sum_sq() const {
        vr128 V_src;
        vr128 V_dst = vseta_vr(0, 0, 0);
        const vr128* P_src = a;

        for (int i = 0; i < N/4; i++) {
            load32x4_vr_postI(V_src, P_src, INC1);
            V_dst = vmacs_adj(V_dst, V_src, V_src, 0, 0);
        }
        if (N&3) {
            load32x4_vr_postI(V_src, P_src, INC1);
            seta_vr(V_src, PAD_MASK, 0, 0, 0);
            V_dst = vmacs_adj(V_dst, V_src, V_src, 0, 0);
        }

        dsums_L(V_dst, V_dst, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);
        return get_VRQ0(V_dst);
    }

    _AI AScalar dot(const AVector& x) const {
        vr128 V_src;
        vr128 V_src_x;
        vr128 V_dst = vseta_vr(0, 0, 0);
        const vr128* P_src = a;
        const vr128* P_src_x = x.a;

        for (int i = 0; i < N/4; i++) {
            load32x4_vr_postI(V_src, P_src, INC1);
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            V_dst = vmacs_adj(V_dst, V_src, V_src_x, 0, 0);
        }
        if (N&3) {
            load32x4_vr_postI(V_src, P_src, INC1);
            load32x4_vr_postI(V_src_x, P_src_x, INC1);
            seta_vr(V_src, PAD_MASK, 0, 0, 0);
            V_dst = vmacs_adj(V_dst, V_src, V_src_x, 0, 0);
        }

        dsums_L(V_dst, V_dst, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);
        return get_VRQ0(V_dst);
    }

    _AI AScalar max_abs() const {
        vr128 V_src;
        vr128 V_dst = vseta_vr(0, 0, 0);
        const vr128* P_src = a;
        unsigned int ar;
        mir30 mir;

        for (int i = 0; i < N/4; i++) {
            load32x4_vr_postI(V_src, P_src, INC1);
            V_dst = vmax(V_dst, vabs(V_src));
        }
        if (N&3) {
            load32x4_vr_postI(V_src, P_src, INC1);
            seta_vr(V_src, PAD_MASK, 0, 0, 0);
            V_dst = vmax(V_dst, vabs(V_src));
        }

        rmax_idx(ar, V_dst, VRQ0, V_dst, mir);
        return get_VRQ0(V_dst);
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}
    _AI AVector& normalize() {return mul(sum_sq().f_invsqrt());}
};

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AVector
    \brief Abstract fixed length vector of AScalar

    \fn AVector::AVector(const AVector& x)
    \brief Copy constructor

    \fn static int AVector::length()
    \brief Returns the number of elements

    \fn AVector& AVector::fill(const AScalar& x)
    \brief Fills vector with copies of x

    \fn AVector& AVector::copy(const AVector& x)
    \brief Copies vector from the elements of x

    \fn AVector& AVector::add(const AVector& x)
    \brief Returns *this += x elementwise

    \fn AVector& AVector::sub(const AVector& x)
    \brief Returns *this += x elementwise

    \fn AVector& AVector::mul(const AVector& x)
    \brief Returns *this *= x elementwise

    \fn AVector& AVector::div(const AVector& x)
    \brief Returns *this /= x elementwise

    \fn AVector& AVector::mul_acc(const AVector& x, const AVector& y)
    \brief Returns *this += x * y elementwise

    \fn AVector& AVector::add(const AScalar& x)
    \brief Adds x to each element

    \fn AVector& AVector::sub(const AScalar& x)
    \brief Subtracts x from each element

    \fn AVector& AVector::mul(const AScalar& x)
    \brief Multiplies each element by x

    \fn AVector& AVector::div(const AScalar& x)
    \brief Divides each element by x

    \fn AVector& AVector::abs()
    \brief Replaces each element by its absolute value

    \fn AVector& AVector::min(const AVector& x)
    \brief Returns *this = min(*this, x) elementwise

    \fn AVector& AVector::max(const AVector& x)
    \brief Returns *this = max(*this, x) elementwise

    \fn AVector& AVector::clamp(const AScalar& low, const AScalar& high)
    \brief Returns *this = max(min(*this, high), low) elementwise

    \fn AScalar AVector::sum()
    \brief Returns the sum of the elements

    \fn AScalar AVector::sum_sq()
    \brief Returns the sum of the squares of the elements

    \fn AVector AVector::dot(const AVector& x)
    \brief Returns the inner product with x

    \fn AScalar AVector::max_abs()
    \brief Returns the maximum absolute value of the elements

    \fn AScalar AVector::norm()
    \brief Returns the Euclidean norm of the vector

    \fn AScalar AVector::normalize()
    \brief Normalizes the vector
*/
