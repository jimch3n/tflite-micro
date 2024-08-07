/************************************************************************//**
 * @file    AVL/DMX1A/AComplexPair.h
 *
 * @brief   AComplexPair wrapper for vr128 on DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEXPAIR_H
#define ACOMPLEXPAIR_H

/**************************************************************************//**
 * @addtogroup dmx1a_avl
 * @{
 *****************************************************************************/

#include "AComplex.h"
#include "APair.h"

struct AComplexPair
{
    vr128 vr;

    _AI AComplexPair() {}
    _AI AComplexPair(const AComplexPair& x) : vr(x.vr) {}
    _AI AComplexPair(const APair& x) {*this = x;}

    _AI AComplexPair& operator= (const AComplexPair& x) {vr = x.vr; return *this;}
    _AI AComplexPair& operator= (const APair& x) {
        vr = vperm(vreplicate_hr(x.vr), vseta_vr(0, 0, 0), set_perm16(0x6160));
        return *this;
    }

    _AI static int length() {return 2;}
    _AI static AComplexPair Zero() {return vseta_vr(0, 0, 0);}

    _AI const AComplex operator[] (int i) const {return (i & 1) ? get_VRH(vr) : get_VRL(vr);}

    _AI xtbool operator== (const AComplexPair& x) const {return XT_ALL4(veq(vr, x.vr));}
    _AI xtbool operator!= (const AComplexPair& x) const {return XT_ANY4(vne(vr, x.vr));}

    _AI AComplexPair& fill(const AComplex& x)     {vr = vreplicate_hr(x.vr); return *this;}
    _AI AComplexPair& copy(const AComplexPair& x) {vr = mv_VR(x.vr);         return *this;}

    _AI AComplexPair& add(const AComplexPair& x) {vr = vadds(vr, x.vr, 0);    return *this;}
    _AI AComplexPair& sub(const AComplexPair& x) {vr = vadds(vr, x.vr, 0xf0); return *this;}

    _AI AComplexPair& mul(const AComplexPair& x) {
        vr = cmul_x2(vr, x.vr, CONJ_NONE);
        return *this;
    }
    _AI AComplexPair& mul_conj(const AComplexPair& x) {
        vr = cmul_x2(vr, x.vr, CONJ_Y);
        return *this;
    }
    _AI AComplexPair& mul_acc(const AComplexPair& x, const AComplexPair& y) {
        vr = cmac_adj_x2(vr, x.vr, y.vr, CONJ_NONE, 0);
        return *this;
    }
    _AI AComplexPair& mul_conj_acc(const AComplexPair& x, const AComplexPair& y) {
        vr = cmac_adj_x2(vr, x.vr, y.vr, CONJ_Y, 0);
        return *this;
    }
    _AI AComplexPair& mul_acc(const AComplexPair& x, const AComplex& y) {
        vr128 V_src_y = vreplicate_hr(y.vr);
        vr = cmac_adj_x2(vr, x.vr, V_src_y, CONJ_NONE, 0);
        return *this;
    }

    _AI AComplexPair& add(const AComplex& x) {
        vr128 V_src = vreplicate_hr(x.vr);
        vr = vadds(vr, V_src, 0);
        return *this;
    }
    _AI AComplexPair& sub(const AComplex& x) {
        vr128 V_src = vreplicate_hr(x.vr);
        vr = vadds(vr, V_src, 0xf0);
        return *this;
    }
    _AI AComplexPair& mul(const AComplex& x) {
        vr128 V_src = vreplicate_hr(x.vr);
        vr = cmul_x2(vr, V_src, CONJ_NONE);
        return *this;
    }
    _AI AComplexPair& mul(const AScalar& x) {
        vr128 V_src = vreplicate_fr(x.fr);
        vr = vmuls(vr, V_src, 0);
        return *this;
    }

    _AI AComplex sum() const {
        vr128 V_dst=vseta_vr(0,0,0);
        csums_L(V_dst, vr, 0, 0);
        return get_VRL(V_dst);
    }

    _AI AComplex dot(const AComplexPair& x) const {
        vr128 V_dst = cmul_x2(vr, x.vr, CONJ_Y);
        csums_L(V_dst, V_dst, 0, 0);
        return get_VRL(V_dst);
    }

    _AI AScalar  norm_sq() const  {return dot(*this).r();}
    _AI AScalar  norm()    const  {return norm_sq().f_sqrt();}
    _AI AComplexPair& normalize() {return mul(norm_sq().f_invsqrt());}

    //
    // Additional methods not in AComplexVector<N>
    //

    _AI AComplexPair(const vr128& a) : vr(a) {}
    _AI AComplexPair(const AComplex& c0, const AComplex& c1) {
        vr = vr128_pair(c1.vr, c0.vr);
    }

    _AI AComplexPair operator* (const AComplexPair& x) const {
        return cmul_x2(vr, x.vr, 0);
    }
    _AI AComplexPair operator+ (const AComplexPair& x) const {
        return vadds(vr, x.vr, 0);
    }
    _AI AComplexPair operator- (const AComplexPair& x) const {
        return vadds(vr, x.vr, 0xf0);
    }
    _AI AComplexPair operator- () const {
        return s_vnegs(vr, 0xf);
    }

    _AI AComplexPair& operator*= (const AComplexPair& x) {vr = cmul_x2(vr, x.vr, 0);  return *this;}
    _AI AComplexPair& operator+= (const AComplexPair& x) {vr = vadds(vr, x.vr, 0);    return *this;}
    _AI AComplexPair& operator-= (const AComplexPair& x) {vr = vadds(vr, x.vr, 0xf0); return *this;}

    _AI AComplexPair operator* (const AScalar& x) const {
        return vmuls(vr, vreplicate_fr(x.fr), 0);
    }
    _AI AComplexPair& operator*= (const AScalar& x) {
        vr = vmuls(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }

    _AI AComplexPair mul_add(const AComplexPair& x, const AComplexPair& y) const {
        return cmac_adj_x2(vr, x.vr, y.vr, CONJ_NONE, 0);
    }
    _AI AComplexPair mul_sub(const AComplexPair& x, const AComplexPair& y) const {
        return cmas_adj_x2(vr, x.vr, y.vr, CONJ_NONE, 0);
    }
    _AI AComplexPair mul_conj_add(const AComplexPair& x, const AComplexPair& y) const {
        return cmac_adj_x2(vr, x.vr, y.vr, CONJ_Y, 0);
    }
    _AI AComplexPair mul_conj_sub(const AComplexPair& x, const AComplexPair& y) const {
        return cmas_adj_x2(vr, x.vr, y.vr, CONJ_Y, 0);
    }

    _AI AComplex c0() const {return get_VRL(vr);}
    _AI AComplex c1() const {return get_VRH(vr);}

    _AI AComplexPair& set_c0(const AComplex& a) {set_VRL(vr, a.vr); return *this;}
    _AI AComplexPair& set_c1(const AComplex& a) {set_VRH(vr, a.vr); return *this;}
};

_AI AComplexPair AScalar::operator* (const struct AComplexPair& x) const {
    return vmuls(x.vr, vreplicate_fr(fr), 0);
}

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AComplexPair
    \brief Wrapper for a vr128, two vr64s, or std::complex<float>[2]

    \fn AComplexPair::AComplexPair(const AComplexPair& x)
    \brief Copy constructor

    \fn static int AComplexPair::length()
    \brief Returns 2

    \fn static AComplexPair AComplexPair::Zero()
    \brief Returns an AComplexPair filled with 0.0

    \fn AComplexPair& AComplexPair::fill(const AComplex& x)
    \brief Fills both elements with x

    \fn AComplexPair& AComplexPair::copy(const AComplexPair& x)
    \brief Copies both elements from the elements of x

    \fn AComplexPair& AComplexPair::add(const AComplexPair& x)
    \brief Returns *this += x elementwise

    \fn AComplexPair& AComplexPair::sub(const AComplexPair& x)
    \brief Returns *this += x elementwise

    \fn AComplexPair& AComplexPair::mul(const AComplexPair& x)
    \brief Returns *this *= x elementwise

    \fn AComplexPair& AComplexPair::mul_conj(const AComplexPair& x)
    \brief Returns *this *= x.conj() elementwise

    \fn AComplexPair& AComplexPair::mul_acc(const AComplexPair& x, const AComplexPair& y)
    \brief Returns *this += x * y elementwise

    \fn AComplexPair& AComplexPair::mul_conj_acc(const AComplexPair& x, const AComplexPair& y)
    \brief Returns *this += x * y.conj() elementwise

    \fn AComplexPair& AComplexPair::mul_acc(const AComplexPair& x, const AComplex& y)
    \brief Returns *this += x * y elementwise

    \fn AComplexPair& AComplexPair::add(const AComplex& x)
    \brief Adds x to each element

    \fn AComplexPair& AComplexPair::sub(const AComplex& x)
    \brief Subtracts x from each element

    \fn AComplexPair& AComplexPair::mul(const AComplex& x)
    \brief Multiplies each element by x

    \fn AComplexPair& AComplexPair::mul(const AScalar& x)
    \brief Multiplies each element by x

    \fn AComplex AComplexPair::sum()
    \brief Returns the sum of the elements

    \fn AComplex AComplexPair::dot(const AComplexPair& x)
    \brief Returns the inner product with x

    \fn AScalar AComplexPair::norm_sq()
    \brief Returns the sum of r()**2 + i()**2

    \fn AScalar AComplexPair::norm()
    \brief Returns the sqrare root of the sum of r()**2 + i()**2

    \fn AComplex AComplexPair::normalize()
    \brief Normalizes the 2-element vector

    \fn AComplexPair::AComplexPair(const AComplex& h0, const AComplex& h1)
    \brief Construct from two AComplexs

    \fn AComplexPair AComplexPair::mul_add(const AComplexPair& x, const AComplexPair& y)
    \brief Returns *this + x * y

    \fn AComplexPair AComplexPair::mul_sub(const AComplexPair& x, const AComplexPair& y)
    \brief Returns *this - x * y

    \fn AComplexPair AComplexPair::mul_conj_add(const AComplexPair& x, const AComplexPair& y)
    \brief Returns *this + x * y.conj()

    \fn AComplexPair AComplexPair::mul_conj_sub(const AComplexPair& x, const AComplexPair& y)
    \brief Returns *this - x * y.conj()

    \fn AComplex AComplexPair::c0()
    \brief Returns first element

    \fn AComplex AComplexPair::c1()
    \brief Returns second element

    \fn AComplexPair& AComplexPair::set_c0(const AComplex& a)
    \brief Sets first element

    \fn AComplexPair& AComplexPair::set_c1(const AComplex& a)
    \brief Sets second element
*/
