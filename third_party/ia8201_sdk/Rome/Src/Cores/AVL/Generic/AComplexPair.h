///////////////////////////////////////////////////////////////////////////////
///
/// \file AComplexPair.h
///
/// AComplexPair wrapper for std::complex<float>[2]
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ACOMPLEXPAIR_H
#define ACOMPLEXPAIR_H

#include "AComplex.h"
#include "APair.h"

struct AComplexPair
{
    std::complex<float> vr[2];

    _AI AComplexPair() {}
    _AI AComplexPair(const AComplexPair& x) {copy(x);}
    _AI AComplexPair& operator= (const AComplexPair& x) {copy(x); return *this;}
    _AI AComplexPair(const APair& x) {*this = x;}
    _AI AComplexPair& operator= (const APair& x) {vr[0] = x.vr[0]; vr[1] = x.vr[1]; return *this;}

    _AI static int length() {return 2;}
    _AI static AComplexPair Zero() {return AComplexPair(std::complex<float>(0, 0),
                                                        std::complex<float>(0, 0));}

    _AI const AComplex operator[] (int i) const {return vr[i];}

    _AI bool operator== (const AComplexPair& x) const {
        return vr[0] == x.vr[0] && vr[1] == x.vr[1];
    }
    _AI bool operator!= (const AComplexPair& x) const {
        return vr[0] != x.vr[0] || vr[1] != x.vr[1];
    }

    _AI AComplexPair& fill(const AComplex& x)     {vr[0] = vr[1] = x.vr;             return *this;}
    _AI AComplexPair& copy(const AComplexPair& x) {vr[0] = x.vr[0]; vr[1] = x.vr[1]; return *this;}

    _AI AComplexPair& add(const AComplexPair& x) {vr[0] += x.vr[0]; vr[1] += x.vr[1]; return *this;}
    _AI AComplexPair& sub(const AComplexPair& x) {vr[0] -= x.vr[0]; vr[1] -= x.vr[1]; return *this;}
    _AI AComplexPair& mul(const AComplexPair& x) {vr[0] *= x.vr[0]; vr[1] *= x.vr[1]; return *this;}

    _AI AComplexPair& mul_conj(const AComplexPair& x) {
        vr[0] *= std::conj(x.vr[0]);
        vr[1] *= std::conj(x.vr[1]);
        return *this;
    }
    _AI AComplexPair& mul_acc(const AComplexPair& x, const AComplexPair& y) {
        vr[0] += x.vr[0] * y.vr[0];
        vr[1] += x.vr[1] * y.vr[1];
        return *this;
    }
    _AI AComplexPair& mul_conj_acc(const AComplexPair& x, const AComplexPair& y) {
        vr[0] += x.vr[0] * std::conj(y.vr[0]);
        vr[1] += x.vr[1] * std::conj(y.vr[1]);
        return *this;
    }
    _AI AComplexPair& mul_acc(const AComplexPair& x, const AComplex& y) {
        vr[0] += x.vr[0] * y.vr;
        vr[1] += x.vr[1] * y.vr;
        return *this;
    }

    _AI AComplexPair& add(const AComplex& x) {vr[0] += x.vr; vr[1] += x.vr; return *this;}
    _AI AComplexPair& sub(const AComplex& x) {vr[0] -= x.vr; vr[1] -= x.vr; return *this;}
    _AI AComplexPair& mul(const AComplex& x) {vr[0] *= x.vr; vr[1] *= x.vr; return *this;}
    _AI AComplexPair& mul(const AScalar& x)  {vr[0] *= x.fr; vr[1] *= x.fr; return *this;}

    _AI AComplex sum() const {return vr[0] + vr[1];}
    _AI AComplex dot(const AComplexPair& x) const {
        return vr[0] * std::conj(x.vr[0]) + vr[1] * std::conj(x.vr[1]);
    }
    _AI AScalar norm_sq()   const {return std::norm(vr[0]) + std::norm(vr[1]);}
    _AI AScalar norm()      const {return norm_sq().f_sqrt();}
    _AI AComplexPair& normalize() {return mul(norm_sq().f_invsqrt());}

    //
    // Additional methods not in AComplexVector<N>
    //

    _AI AComplexPair(const AComplex &c0, const AComplex &c1) {
        vr[0] = c0.vr; vr[1] = c1.vr;
    }
    _AI AComplexPair(std::complex<float> c0, std::complex<float> c1) {
        vr[0] = c0; vr[1] = c1;
    }

    _AI AComplexPair operator* (const AComplexPair& x) const {
        return AComplexPair(vr[0] * x.vr[0], vr[1] * x.vr[1]);
    }
    _AI AComplexPair operator+ (const AComplexPair& x) const {
        return AComplexPair(vr[0] + x.vr[0], vr[1] + x.vr[1]);
    }
    _AI AComplexPair operator- (const AComplexPair& x) const {
        return AComplexPair(vr[0] - x.vr[0], vr[1] - x.vr[1]);
    }
    _AI AComplexPair operator- () const {
        return AComplexPair(-vr[0], -vr[1]);
    }

    _AI AComplexPair& operator*= (const AComplexPair& x) {mul(x); return *this;}
    _AI AComplexPair& operator+= (const AComplexPair& x) {add(x); return *this;}
    _AI AComplexPair& operator-= (const AComplexPair& x) {sub(x); return *this;}

    _AI AComplexPair operator* (const AScalar& x) const {
        return AComplexPair(vr[0] * x.fr, vr[1] * x.fr);
    }

    _AI AComplexPair& operator*= (const AScalar& x) {mul(x); return *this;}

    _AI AComplexPair mul_add(const AComplexPair& x, const AComplexPair& y) const {
        return AComplexPair(vr[0] + x.vr[0] * y.vr[0], vr[1] + x.vr[1] * y.vr[1]);
    }
    _AI AComplexPair mul_sub(const AComplexPair& x, const AComplexPair& y) const {
        return AComplexPair(vr[0] - x.vr[0] * y.vr[0], vr[1] - x.vr[1] * y.vr[1]);
    }
    _AI AComplexPair mul_conj_add(const AComplexPair& x, const AComplexPair& y) const {
        return AComplexPair(vr[0] + x.vr[0] * std::conj(y.vr[0]),
                            vr[1] + x.vr[1] * std::conj(y.vr[1]));
    }
    _AI AComplexPair mul_conj_sub(const AComplexPair& x, const AComplexPair& y) const {
        return AComplexPair(vr[0] - x.vr[0] * std::conj(y.vr[0]),
                            vr[1] - x.vr[1] * std::conj(y.vr[1]));
    }

    _AI AComplex c0() const {return vr[0];}
    _AI AComplex c1() const {return vr[1];}

    _AI AComplexPair& set_c0(const AComplex& a) {vr[0] = a.vr; return *this;}
    _AI AComplexPair& set_c1(const AComplex& a) {vr[1] = a.vr; return *this;}
};

_AI AComplexPair AScalar::operator* (const struct AComplexPair& x) const {
    return AComplexPair(fr * x.vr[0], fr * x.vr[1]);
}

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

    \fn AComplexPair::AComplexPair(std::complex<float> c0, std::complex<float> c1)
    \brief Construct from two std::complex<float>s

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
