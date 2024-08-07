/************************************************************************//**
 * @file    AVL\DeltaMax\ATriple.h
 *
 * @brief   ATriple wrapper for vr128 on DeltaMax
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ATRIPLE_H
#define ATRIPLE_H

/**************************************************************************//**
 * @addtogroup dmx_avl
 * @{
 *****************************************************************************/

#include "AScalar.h"

struct ATriple
{
    vr128 vr;

    _AI ATriple() {}
    _AI ATriple(const ATriple& x) : vr(x.vr) {}
    _AI ATriple& operator= (const ATriple& x) {vr = x.vr; return *this;}

    _AI static int length() {return 3;}
    _AI static ATriple Zero() {return vseta_vr(0, 0, 0);}

    _AI const AScalar operator[] (int i) const {return move32_fr_vr_idx(vr, i);}

    static const int PAD_MASK = 8;

    _AI xtbool operator== (const ATriple& x) const {
        return XT_ALL4(orb4(int_to_xt_bool4(8), veq(vr, x.vr)));
    }
    _AI xtbool operator!= (const ATriple& x) const {
        return XT_ANY4(andb4(int_to_xt_bool4(7), vne(vr, x.vr)));
    }

    _AI ATriple& fill(const AScalar& x) {vr = vreplicate_fr(x.fr); return *this;}
    _AI ATriple& copy(const ATriple& x) {vr = x.vr;                return *this;}

    _AI ATriple& add(const ATriple& x) {vr = vadds(vr, x.vr, 0);    return *this;}
    _AI ATriple& sub(const ATriple& x) {vr = vadds(vr, x.vr, 0xf0); return *this;}
    _AI ATriple& mul(const ATriple& x) {vr = vmuls(vr, x.vr, 0);    return *this;}
    _AI ATriple& div(const ATriple& x) {
        // One iteration of Newton's method
        vr128 V_2 = vseta_vr(2, 0, 0);
        vr128 V_inv, V_dst;
        inv(V_inv, VRQ0, x.vr, VRQ0);
        inv(V_inv, VRQ1, x.vr, VRQ1);
        inv(V_inv, VRQ2, x.vr, VRQ2);
        V_dst = vmuls(V_inv, vmacs_adj(V_2, V_inv, x.vr, 15, 0), 0);
        vr = vmuls(vr, V_dst, 0);
        return *this;
    }

    _AI ATriple& mul_acc(const ATriple& x, const ATriple& y) {
        vr = vmacs_adj(vr, x.vr, y.vr, 0, 0);
        return *this;
    }
    _AI ATriple& mul_acc(const ATriple& x, const AScalar& y) {
        vr = vmacs_adj(vr, x.vr, vreplicate_fr(y.fr), 0, 0);
        return *this;
    }

    _AI ATriple& add(const AScalar& x) {
        vr = vadds(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }
    _AI ATriple& sub(const AScalar& x) {
        vr = vadds(vr, vreplicate_fr(x.fr), 0xf0);
        return *this;
    }
    _AI ATriple& mul(const AScalar& x) {
        vr = vmuls(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }
    _AI ATriple& div(const AScalar& x) {
        return mul(x.inverse());
    }

    _AI ATriple& abs()                 {vr = vabs(vr);       return *this;}
    _AI ATriple& max(const ATriple& x) {vr = vmax(vr, x.vr); return *this;}
    _AI ATriple& min(const ATriple& x) {vr = vmin(vr, x.vr); return *this;}

    _AI ATriple& clamp(const AScalar& low, const AScalar& high) {
        vr128 V_low = vreplicate_fr(low.fr);
        vr128 V_high= vreplicate_fr(high.fr);
        vr = vmin(vmax(vr, V_low), V_high);
        return *this;
    }

    _AI AScalar sum() const {
        vr128 V_dst = vr;
        seta_vr(V_dst, PAD_MASK, 0, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);
        return get_VRQ0(V_dst);
    }

    _AI AScalar dot(const ATriple& x) const {
        vr128 V_dst;
        fmul_sum3(V_dst, VRQ0, vr, x.vr, 0, set_perm16(0x005a));
        return get_VRQ0(V_dst);
    }

    _AI AScalar max_abs() const {
        vr128 V_dst = vabs(vr);
        unsigned int ar;
        mir30 mir;
        seta_vr(V_dst, PAD_MASK, 0, 0, 0);
        rmax_idx(ar, V_dst, VRQ0, V_dst, mir);
        return get_VRQ0(V_dst);
    }

    _AI AScalar sum_sq() const {return dot(*this);}
    _AI AScalar norm()   const {return sum_sq().f_sqrt();}
    _AI ATriple& normalize()   {return mul(sum_sq().f_invsqrt());}

    //
    // Additional methods not in AVector<N>
    //

    _AI ATriple(const vr128& a) : vr(a) {}
    _AI ATriple(const AScalar& x, const AScalar& y, const AScalar& z) {
        set_VRQ0(vr, x.fr);
        set_VRQ1(vr, y.fr);
        set_VRQ2(vr, z.fr);
    }
    _AI ATriple(float q0, float q1, float q2) {
        replicate_ar(vr, 1, *(int*) &q0);
        replicate_ar(vr, 2, *(int*) &q1);
        replicate_ar(vr, 4, *(int*) &q2);
        convert_IEEE_float_to_32F_x4(vr);
    }

    _AI ATriple operator* (const ATriple& x) const {return vmuls(vr, x.vr, 0);}
    _AI ATriple operator+ (const ATriple& x) const {return vadds(vr, x.vr, 0);}
    _AI ATriple operator- (const ATriple& x) const {return vadds(vr, x.vr, 0xf0);}
    _AI ATriple operator- ()                 const {return s_vnegs(vr, 0xf);}

    _AI ATriple& operator*= (const ATriple& x) {vr = vmuls(vr, x.vr, 0);    return *this;}
    _AI ATriple& operator+= (const ATriple& x) {vr = vadds(vr, x.vr, 0);    return *this;}
    _AI ATriple& operator-= (const ATriple& x) {vr = vadds(vr, x.vr, 0xf0); return *this;}

    _AI ATriple operator* (const AScalar& x) const {
        return vmuls(vr, vreplicate_fr(x.fr), 0);
    }
    _AI ATriple& operator*= (const AScalar& x) {
        vr = vmuls(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }

    _AI ATriple mul_add(const ATriple& x, const ATriple& y) const {
        return vmacs_adj(vr, x.vr, y.vr,  0, 0);
    }
    _AI ATriple mul_sub(const ATriple& x, const ATriple& y) const {
        return vmacs_adj(vr, x.vr, y.vr, 15, 0);
    }

    _AI AScalar x() const {return get_VRQ0(vr);}
    _AI AScalar y() const {return get_VRQ1(vr);}
    _AI AScalar z() const {return get_VRQ2(vr);}

    _AI ATriple& set_x(const AScalar& a) {set_VRQ0(vr, a.fr); return *this;}
    _AI ATriple& set_y(const AScalar& a) {set_VRQ1(vr, a.fr); return *this;}
    _AI ATriple& set_z(const AScalar& a) {set_VRQ2(vr, a.fr); return *this;}
};

_AI ATriple AScalar::operator* (const struct ATriple& x) const {
    return vmuls(x.vr, vreplicate_fr(fr), 0);
}

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class ATriple
    \brief Wrapper for a vr128, two vr64s, or float[4]

    \fn ATriple::ATriple(const ATriple& x)
    \brief Copy constructor

    \fn static int ATriple::length()
    \brief Returns 3

    \fn static ATriple ATriple::Zero()
    \brief Returns an ATriple filled with 0.0

    \fn ATriple& ATriple::fill(const AScalar& x)
    \brief Fills three elements with x

    \fn ATriple& ATriple::copy(const ATriple& x)
    \brief Copies three elements from the elements of x

    \fn ATriple& ATriple::add(const ATriple& x)
    \brief Returns *this += x elementwise

    \fn ATriple& ATriple::sub(const ATriple& x)
    \brief Returns *this += x elementwise

    \fn ATriple& ATriple::mul(const ATriple& x)
    \brief Returns *this *= x elementwise

    \fn ATriple& ATriple::div(const ATriple& x)
    \brief Returns *this /= x elementwise

    \fn ATriple& ATriple::mul_acc(const ATriple& x, const ATriple& y)
    \brief Returns *this += x * y elementwise

    \fn ATriple& ATriple::mul_acc(const ATriple& x, const AScalar& y)
    \brief Returns *this += x * y elementwise

    \fn ATriple& ATriple::add(const AScalar& x)
    \brief Adds x to each element

    \fn ATriple& ATriple::sub(const AScalar& x)
    \brief Subtracts x from each element

    \fn ATriple& ATriple::mul(const AScalar& x)
    \brief Multiplies each element by x

    \fn ATriple& ATriple::div(const AScalar& x)
    \brief Divides each element by x

    \fn ATriple& ATriple::abs()
    \brief Replaces each element by its absolute value

    \fn ATriple& ATriple::max(const ATriple& x)
    \brief Returns *this = max(*this, x) elementwise

    \fn ATriple& ATriple::min(const ATriple& x)
    \brief Returns *this = min(*this, x) elementwise

    \fn ATriple& ATriple::clamp(const AScalar& low, const AScalar& high)
    \brief Returns *this = max(min(*this, high), low) elementwise

    \fn AScalar ATriple::sum()
    \brief Returns the sum of the elements

    \fn AScalar ATriple::sum_sq()
    \brief Returns the sum of the squares of the elements

    \fn ATriple ATriple::dot(const ATriple& x)
    \brief Returns the inner product with x

    \fn AScalar ATriple::max_abs()
    \brief Returns the maximum absolute value of the elements

    \fn AScalar ATriple::norm()
    \brief Returns the Euclidean norm of the 3-element vector

    \fn AScalar ATriple::normalize()
    \brief Normalizes the 3-element vector

    \fn ATriple::ATriple(const AScalar& x, const AScalar& y, const AScalar& z)
    \brief Construct from three AScalars

    \fn ATriple::ATriple(float x, float y, float z)
    \brief Construct from three floats

    \fn ATriple ATriple::mul_add(const ATriple& x, const ATriple& y)
    \brief Returns *this + x * y

    \fn ATriple ATriple::mul_sub(const ATriple& x, const ATriple& y)
    \brief Returns *this - x * y

    \fn AScalar ATriple::x()
    \brief Returns first element

    \fn AScalar ATriple::y()
    \brief Returns second element

    \fn AScalar ATriple::z()
    \brief Returns third element

    \fn ATriple& ATriple::set_x(const AScalar& a)
    \brief Sets first element

    \fn ATriple& ATriple::set_y(const AScalar& a)
    \brief Sets second element

    \fn ATriple& ATriple::set_z(const AScalar& a)
    \brief Sets third element
*/
