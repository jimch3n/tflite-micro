/************************************************************************//**
 * @file    AVL/Hemi/AComplexPair.h
 *
 * @brief   AComplexPair wrapper for vr64 on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEXPAIR_H
#define ACOMPLEXPAIR_H

#include "AComplex.h"
#include "APair.h"

struct AComplexPair
{
    vr64 vr0;
    vr64 vr1;

    _AI AComplexPair() {}
    _AI AComplexPair(const AComplexPair& x) : vr0(x.vr0), vr1(x.vr1) {}
    _AI AComplexPair(const APair& x) {*this = x;}

    _AI AComplexPair& operator= (const AComplexPair& x) {
        vr0 = x.vr0;
        vr1 = x.vr1;
        return *this;
    }
    _AI AComplexPair& operator= (const APair& x) {
        vr0 = vseta_vr(0, 0);
        vr0 = vpermi(x.vr, vr0, 12);
        vr1 = vpermi(x.vr, vr0, 13);
        return *this;
    }

    _AI static int length() {return 2;}
    _AI static AComplexPair Zero() {return AComplexPair(AComplex::Zero(),
                                                        AComplex::Zero());}

    _AI const AComplex operator[] (int i) const {return (i & 1) ? vr1 : vr0;}

    _AI bool operator== (const AComplexPair& x) const {
        return !move_ar_bbr(orb2(vne(vr0, x.vr0), vne(vr1, x.vr1)));
    }
    _AI bool operator!= (const AComplexPair& x) const {
        return !(*this == x);
    }

    _AI AComplexPair& fill(const AComplex& x)     {vr0 = vr1 = x.vr; return *this;}
    _AI AComplexPair& copy(const AComplexPair& x) {*this = x; return *this;}

    _AI AComplexPair& add(const AComplexPair& x) {
        vr0 = vadds(vr0, x.vr0, 0);
        vr1 = vadds(vr1, x.vr1, 0);
        return *this;
    }
    _AI AComplexPair& sub(const AComplexPair& x) {
        vr0 = vadds(vr0, x.vr0, 10);
        vr1 = vadds(vr1, x.vr1, 10);
        return *this;
    }
    _AI AComplexPair& mul(const AComplexPair& x) {
        vr0 = cmul(vr0, x.vr0, CONJ_NONE);
        vr1 = cmul(vr1, x.vr1, CONJ_NONE);
        return *this;
    }
    _AI AComplexPair& mul_conj(const AComplexPair& x) {
        vr0 = cmul(vr0, x.vr0, CONJ_Y);
        vr1 = cmul(vr1, x.vr1, CONJ_Y);
        return *this;
    }

    _AI AComplexPair& mul_acc(const AComplexPair& x, const AComplexPair& y) {
        vr0 = cmac(vr0, x.vr0, y.vr0, CONJ_NONE);
        vr1 = cmac(vr1, x.vr1, y.vr1, CONJ_NONE);
        return *this;
    }
    _AI AComplexPair& mul_conj_acc(const AComplexPair& x, const AComplexPair& y) {
        vr0 = cmac(vr0, x.vr0, y.vr0, CONJ_Y);
        vr1 = cmac(vr1, x.vr1, y.vr1, CONJ_Y);
        return *this;
    }
    _AI AComplexPair& mul_acc(const AComplexPair& x, const AComplex& y) {
        vr0 = cmac(vr0, x.vr0, y.vr, CONJ_NONE);
        vr1 = cmac(vr1, x.vr1, y.vr, CONJ_NONE);
        return *this;
    }

    _AI AComplexPair& add(const AComplex& x) {
        vr0 = vadds(vr0, x.vr, 0);
        vr1 = vadds(vr1, x.vr, 0);
        return *this;
    }
    _AI AComplexPair& sub(const AComplex& x) {
        vr0 = vadds(vr0, x.vr, 10);
        vr1 = vadds(vr1, x.vr, 10);
        return *this;
    }
    _AI AComplexPair& mul(const AComplex& x) {
        vr0 = cmul(vr0, x.vr, CONJ_NONE);
        vr1 = cmul(vr1, x.vr, CONJ_NONE);
        return *this;
    }
    _AI AComplexPair& mul(const AScalar& x) {
        vr0 = vmulf(vr0, x.fr, 0);
        vr1 = vmulf(vr1, x.fr, 0);
        return *this;
    }

    _AI AComplex sum() const {
        return vadds(vr0, vr1, 0);
    }

    _AI AComplex dot(const AComplexPair& x) const {
        return cmac(cmul(vr0, x.vr0, CONJ_Y), vr1, x.vr1, CONJ_Y);
    }

    _AI AScalar norm_sq() const   {return dot(*this).r();}
    _AI AScalar norm()    const   {return norm_sq().f_sqrt();}
    _AI AComplexPair& normalize() {return mul(norm_sq().f_invsqrt());}

    //
    // Additional methods not in AComplexVector<N>
    //

    _AI AComplexPair(const AComplex& c0, const AComplex& c1) {
        vr0 = c0.vr;
        vr1 = c1.vr;
    }

    _AI AComplexPair operator* (const AComplexPair& x) const {
        AComplexPair z;
        z.vr0 = cmul(vr0, x.vr0, 0);
        z.vr1 = cmul(vr1, x.vr1, 0);
        return z;
    }
    _AI AComplexPair operator+ (const AComplexPair& x) const {
        AComplexPair z;
        z.vr0 = vadds(vr0, x.vr0, 0);
        z.vr1 = vadds(vr1, x.vr1, 0);
        return z;
    }
    _AI AComplexPair operator- (const AComplexPair& x) const {
        AComplexPair z;
        z.vr0 = vadds(vr0, x.vr0, 10);
        z.vr1 = vadds(vr1, x.vr1, 10);
        return z;
    }
    _AI AComplexPair operator- () const {
        AComplexPair z;
        z.vr0 = s_vneg(vr0);
        z.vr1 = s_vneg(vr1);
        return z;
    }

    _AI AComplexPair& operator*= (const AComplexPair& x) {
        vr0 = cmul(vr0, x.vr0, 0);
        vr1 = cmul(vr1, x.vr1, 0);
        return *this;
    }
    _AI AComplexPair& operator+= (const AComplexPair& x) {
        vr0 = vadds(vr0, x.vr0, 0);
        vr1 = vadds(vr1, x.vr1, 0);
        return *this;
    }
    _AI AComplexPair& operator-= (const AComplexPair& x) {
        vr0 = vadds(vr0, x.vr0, 10);
        vr1 = vadds(vr1, x.vr1, 10);
        return *this;
    }

    _AI AComplexPair operator* (const AScalar& x) const {
        AComplexPair z;
        z.vr0 = vmulf(vr0, x.fr, 0);
        z.vr1 = vmulf(vr1, x.fr, 0);
        return z;
    }
    _AI AComplexPair& operator*= (const AScalar& x) {
        vr0 = vmulf(vr0, x.fr, 0);
        vr1 = vmulf(vr1, x.fr, 0);
        return *this;
    }

    _AI AComplexPair mul_add(const AComplexPair& x, const AComplexPair& y) const {
        AComplexPair z;
        z.vr0 = cmac(vr0, x.vr0, y.vr0, CONJ_NONE);
        z.vr1 = cmac(vr1, x.vr1, y.vr1, CONJ_NONE);
        return z;
    }
    _AI AComplexPair mul_sub(const AComplexPair& x, const AComplexPair& y) const {
        AComplexPair z;
        z.vr0 = cmas(vr0, x.vr0, y.vr0, CONJ_NONE);
        z.vr1 = cmas(vr1, x.vr1, y.vr1, CONJ_NONE);
        return z;
    }
    _AI AComplexPair mul_conj_add(const AComplexPair& x, const AComplexPair& y) const {
        AComplexPair z;
        z.vr0 = cmac(vr0, x.vr0, y.vr0, CONJ_Y);
        z.vr1 = cmac(vr1, x.vr1, y.vr1, CONJ_Y);
        return z;
    }
    _AI AComplexPair mul_conj_sub(const AComplexPair& x, const AComplexPair& y) const {
        AComplexPair z;
        z.vr0 = cmas(vr0, x.vr0, y.vr0, CONJ_Y);
        z.vr1 = cmas(vr1, x.vr1, y.vr1, CONJ_Y);
        return z;
    }

    _AI AComplex c0() const {return vr0;}
    _AI AComplex c1() const {return vr1;}

    _AI AComplexPair& set_c0(const AComplex& a) {vr0 = a.vr; return *this;}
    _AI AComplexPair& set_c1(const AComplex& a) {vr1 = a.vr; return *this;}
};

_AI AComplexPair AScalar::operator* (const AComplexPair& x) const {
    AComplexPair z;
    z.vr0 = vmulf(x.vr0, fr, 0);
    z.vr1 = vmulf(x.vr1, fr, 0);
    return z;
}
#endif
