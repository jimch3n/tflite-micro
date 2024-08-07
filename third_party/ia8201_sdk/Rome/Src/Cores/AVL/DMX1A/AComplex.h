/************************************************************************//**
 * @file    AVL/DMX1A/AComplex.h
 *
 * @brief   AComplex wrapper for vr64 on DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEX_H
#define ACOMPLEX_H

/**************************************************************************//**
 * @addtogroup dmx1a_avl
 * @{
 *****************************************************************************/

#include "AScalar.h"

struct AComplex
{
    vr64 vr;

    _AI AComplex() {}
    _AI AComplex(const AComplex& a) : vr(a.vr) {}
    _AI AComplex(const vr64& a)     : vr(a) {}

    _AI operator vr64() const {return vr;}

    _AI AComplex(const AScalar& r) : vr(vr64_pair(seta_fr(0, 0, 0), r.fr)) {}
    _AI AComplex(const AScalar& r, const AScalar& i) : vr(vr64_pair(i.fr, r.fr)) {}

    _AI AComplex(float r, float i) {
        vr = vr64_pair(convert_IEEE_float_to_32F(*(int*) &i),
                       convert_IEEE_float_to_32F(*(int*) &r));
    }

    _AI static AComplex Zero() {return get_VRL(vseta_vr(0, 0, 0));}
    _AI static AComplex One() {
        vr128 z = vseta_vr(0, 0, 0);
        seta_vr(z, 1, 1, 0, 0);
        return get_VRL(z);
    }
    _AI static AComplex I() {
        vr128 z = vseta_vr(0, 0, 0);
        seta_vr(z, 2, 1, 0, 0);
        return get_VRL(z);
    }

    _AI xtbool operator== (const AComplex& x) const {
        return andb1(eq_fr(get_HRL(vr), get_HRL(x.vr)),
                     eq_fr(get_HRH(vr), get_HRH(x.vr)));
    }
    _AI xtbool operator!= (const AComplex& x) const {
        return orb1(ne_fr(get_HRL(vr), get_HRL(x.vr)),
                    ne_fr(get_HRH(vr), get_HRH(x.vr)));
    }

    _AI AComplex operator* (const AComplex& x) const {return cmul(vr, x.vr);}
    _AI AComplex operator+ (const AComplex& x) const {return vadd_hr(vr, x.vr);}
    _AI AComplex operator- (const AComplex& x) const {return vsub_hr(vr, x.vr);}
    _AI AComplex operator- ()                  const {return s_vnegs_hr(vr, 3);}
    _AI AComplex operator/ (const AComplex& x) const {return *this * x.inverse();}

    _AI AComplex& operator*= (const AComplex& x) {return (*this = *this * x);}
    _AI AComplex& operator/= (const AComplex& x) {return (*this = *this / x);}
    _AI AComplex& operator+= (const AComplex& x) {return (*this = *this + x);}
    _AI AComplex& operator-= (const AComplex& x) {return (*this = *this - x);}

    _AI AComplex operator* (const AScalar& x) const {
        return vmul_hr(vr, hreplicate_fr(x.fr));
    }
    _AI AComplex& operator*= (const AScalar& x) {
        vr = vmul_hr(vr, hreplicate_fr(x.fr));
        return *this;
    }

    _AI AComplex mul_add(const AComplex& x, const AComplex& y) const {
        return cmac(vr, x.vr, y.vr);
    }
    _AI AComplex mul_sub(const AComplex& x, const AComplex& y) const {
        return cmas(vr, x.vr, y.vr);
    }
    _AI AComplex& mul_acc(const AComplex& x, const AComplex& y) {
        vr = cmac(vr, x.vr, y.vr);
        return *this;
    }

    _AI AScalar r() const {return get_HRL(vr);}
    _AI AScalar i() const {return get_HRH(vr);}

    _AI AComplex& set_r(const AScalar& a) {set_HRL(vr, a.fr); return *this;}
    _AI AComplex& set_i(const AScalar& a) {set_HRH(vr, a.fr); return *this;}

    _AI AComplex conj() const {return s_vnegs_hr(vr, 2);}
    _AI AComplex mul_conj(const AComplex& y) const {return cmul_conj(vr, y.vr);}
    _AI AComplex mul_conj_add(const AComplex& x, const AComplex& y) const {
        return cmac_conj(vr, x.vr, y.vr);
    }
    _AI AComplex mul_conj_sub(const AComplex& x, const AComplex& y) const {
        return cmas_conj(vr, x.vr, y.vr);
    }
    _AI AComplex& mul_conj_acc(const AComplex& x, const AComplex& y) {
        vr = cmac_conj(vr, x.vr, y.vr);
        return *this;
    }

    _AI AScalar dot(const AComplex& x) const {
        return get_HRL(cmul_conj(vr, x.vr));
    }

    _AI AScalar   norm_sq() const {return dot(*this);}
    _AI AScalar   norm()    const {return norm_sq().f_sqrt();}
    _AI AComplex  inverse() const {return conj() * norm_sq().inverse();}
    _AI AComplex safe_inverse() const {
        //a+ib inverse
        // real = a/a^2+b^2
        // imag = b/a^2+b^2
        int rexp = this->r().fr_exp();
        int iexp = this->i().fr_exp();
        int max_exp = XT_MAX(rexp, iexp);
        int adj_exp = (max_exp | 1) - (31 +6);
        adj_exp >>= 1;
        //adj_exp = -adj_exp;
        AComplex adj_cmplex = AComplex(this->r() >> adj_exp, this->i() >> adj_exp);
        AScalar denom = adj_cmplex.r() * adj_cmplex.r() + adj_cmplex.i() * adj_cmplex.i();
        #ifdef _MSC_VER
		if (denom.raw() == 0x7fffffff)
        {
            printf("overflow!: please check: %f",denom.to_double());
            getchar();
        }
		#endif
        AScalar inv_denom = denom.inverse();
        AComplex out;
        out.set_r((adj_cmplex.r() >> adj_exp) * inv_denom);
        out.set_i(((-adj_cmplex.i()) >> adj_exp) * inv_denom);
        return out;
    }
    _AI AComplex& normalize() {return (*this = *this * norm_sq().f_invsqrt());}
};

_AI AComplex AScalar::operator* (const struct AComplex& x) const {
    return vmul_hr(x.vr, hreplicate_fr(fr));
}

//
// Pointer to AComplex
//

struct PComplex
{
    AComplex* ptr;

    _AI PComplex(void* p) : ptr((AComplex*) p) {}

    _AI operator AComplex*() const {return ptr;}
    _AI AComplex* operator->() const {return ptr;}
    _AI AComplex& operator[] (int i) const {return ptr[i];}

    _AI PComplex  operator+ (int index) const {return PComplex(ptr + index);}
    _AI PComplex  operator- (int index) const {return PComplex(ptr - index);}

    _AI PComplex& operator+= (int index) {ptr += index; return *this;}
    _AI PComplex& operator-= (int index) {ptr -= index; return *this;}

    _AI PComplex& operator++ ()    {++ptr; return *this;}
    _AI PComplex& operator-- ()    {--ptr; return *this;}
    _AI PComplex  operator++ (int) {PComplex p(*this); ++ptr; return p;}
    _AI PComplex  operator-- (int) {PComplex p(*this); --ptr; return p;}
};

struct PConstComplex
{
    const AComplex* ptr;

    _AI PConstComplex(const void* p) : ptr((const AComplex*) p) {}

    _AI operator const AComplex*() const {return ptr;}
    _AI const AComplex* operator->() const {return ptr;}
    _AI const AComplex& operator[] (int i) const {return ptr[i];}

    _AI PConstComplex  operator+ (int index) const {return PConstComplex(ptr + index);}
    _AI PConstComplex  operator- (int index) const {return PConstComplex(ptr - index);}

    _AI PConstComplex& operator+= (int index) {ptr += index; return *this;}
    _AI PConstComplex& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstComplex& operator++ ()    {++ptr; return *this;}
    _AI PConstComplex& operator-- ()    {--ptr; return *this;}
    _AI PConstComplex  operator++ (int) {PConstComplex p(*this); ++ptr; return p;}
    _AI PConstComplex  operator-- (int) {PConstComplex p(*this); --ptr; return p;}
};

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AComplex
    \brief Wrapper for a vr64, vr128, or std::complex<float>

    \fn AComplex::AComplex(const AComplex& s)
    \brief Copy constructor

    \fn AComplex::AComplex(const AScalar& r)
    \brief Construct from an AScalar

    \fn AComplex::AComplex(const AScalar& r, const AScalar& i)
    \brief Construct from two AScalars

    \fn AComplex::AComplex(float r, float i)
    \brief Construct from two floats

    \fn static AComplex AComplex::Zero()
    \brief Returns (0.0 + 0.0i)

    \fn static AComplex AComplex::One()
    \brief Returns (1.0 + 0.0i)

    \fn static AComplex AComplex::I()
    \brief Returns (0.0 + 1.0i)

    \fn AComplex AComplex::mul_add(const AComplex& x, const AComplex& y)
    \brief Return *this + x * y

    \fn AComplex AComplex::mul_sub(const AComplex& x, const AComplex& y)
    \brief Return *this - x * y

    \fn AComplex& AComplex::mul_acc(const AComplex& x, const AComplex& y)
    \brief Return *this += x * y

    \fn AScalar AComplex::r()
    \brief Returns real part

    \fn AScalar AComplex::i()
    \brief Returns imaginary part

    \fn AComplex& AComplex::set_r(const AScalar& a)
    \brief Sets real part

    \fn AComplex& AComplex::set_i(const AScalar& a)
    \brief Sets imaginary part

    \fn AComplex AComplex::conj()
    \brief Returns complex conjugate

    \fn AComplex AComplex::mul_conj(const AComplex& y)
    \brief Returns *this * y.conj()

    \fn AComplex AComplex::mul_conj_add(const AComplex& x, const AComplex& y)
    \brief Return *this + x * y.conj()

    \fn AComplex AComplex::mul_conj_sub(const AComplex& x, const AComplex& y)
    \brief Return *this - x * y.conj()

    \fn AComplex& AComplex::mul_conj_acc(const AComplex& x, const AComplex& y)
    \brief Return *this += x * y.conj()

    \fn AScalar AComplex::dot(const AComplex& y)
    \brief Returns real part of *this * y.conj()

    \fn AScalar AComplex::norm_sq()
    \brief Returns r()**2 + i()**2

    \fn AScalar AComplex::norm()
    \brief Returns sqrt(r()**2 + i()**2)

    \fn AComplex AComplex::inverse()
    \brief Returns 1.0 / *this

    \fn AComplex& AComplex::normalize()
    \brief Returns *this *= 1.0 / sqrt(r()**2 + i()**2)
*/

/** \class PComplex
    \brief Abstract pointer to an AComplex

    \fn PComplex::PComplex(void* p)
    \brief Constructor

    \fn AComplex* PComplex::operator->()
    \brief Dereference

    \fn AComplex& PComplex::operator[] (int i)
    \brief Array reference
*/

/** \class PConstComplex
    \brief Abstract pointer to a const AComplex

    \fn PConstComplex::PConstComplex(const void* p)
    \brief Constructor

    \fn const AComplex* PComplex::operator->()
    \brief Dereference

    \fn const AComplex& PConstComplex::operator[] (int i)
    \brief Array reference
*/
