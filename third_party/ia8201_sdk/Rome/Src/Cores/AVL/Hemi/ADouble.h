/************************************************************************//**
 * @file    AVL/Hemi/ADouble.h
 *
 * @brief   ADouble wrapper for vr64 on HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ADOUBLE_H
#define ADOUBLE_H

#include "AScalar.h"

struct ADouble
{
    vr64 vr;

    _AI ADouble() {}
    _AI ADouble(const ADouble& d) : vr(d.vr) {}
    _AI ADouble(const AScalar& s) : vr(convert_32F_to_64F(s.fr)) {}
    _AI ADouble(const vr64& a)    : vr(a) {}
    _AI ADouble(int32_t i)        : vr(convert_32I_to_64F(i)) {}
#ifdef _MSC_VER
    _AI ADouble(double d) {
        __declspec(align(8)) double dd = d;
        vr = vr64_loadi((vr64*) &dd, 0);
        convert_IEEE_double_to_64F(vr);
    }
#else
    _AI ADouble(double d) {
        vr = vr64_loadi((vr64*) &d, 0);
        convert_IEEE_double_to_64F(vr);
    }
#endif

    _AI ADouble& operator= (const ADouble& d) {vr = d.vr; return *this;}
    _AI ADouble& operator= (const vr64& a)    {vr = a;    return *this;}
    _AI ADouble& operator= (double d)         {*this = ADouble(d); return *this;}
    _AI ADouble& operator= (int32_t i)        {*this = ADouble(i); return *this;}

    _AI operator vr64() const {return vr;}

    _AI int to_int() const {return convert_64F_to_32I(vr, 1);}

    _AI ADouble operator* (const ADouble& x) const {return dmuls(vr, x.vr, 0);}
    _AI ADouble operator+ (const ADouble& x) const {return dadds(vr, x.vr, 0);}
    _AI ADouble operator- (const ADouble& x) const {return dadds(vr, x.vr, 1);}
    _AI ADouble operator- ()                 const {return dadds(vr, vseta_vr(0, 0), 2);}
    _AI ADouble operator/ (const ADouble& x) const {return *this * x.inverse();}

    _AI ADouble& operator*= (const ADouble& x) {return (*this = *this * x);}
    _AI ADouble& operator/= (const ADouble& x) {return (*this = *this / x);}
    _AI ADouble& operator+= (const ADouble& x) {return (*this = *this + x);}
    _AI ADouble& operator-= (const ADouble& x) {return (*this = *this - x);}

    _AI unsigned operator== (const ADouble& x) const {return deqz(dadds(vr, x.vr, 1));}
    _AI unsigned operator>= (const ADouble& x) const {return dgez(dadds(vr, x.vr, 1));}
    _AI unsigned operator>  (const ADouble& x) const {return dgtz(dadds(vr, x.vr, 1));}
    _AI unsigned operator<= (const ADouble& x) const {return dlez(dadds(vr, x.vr, 1));}
    _AI unsigned operator<  (const ADouble& x) const {return dltz(dadds(vr, x.vr, 1));}
    _AI unsigned operator!= (const ADouble& x) const {return dnez(dadds(vr, x.vr, 1));}

    _AI ADouble operator<< (int x) const {return *this * (AScalar::One() << x);}
    _AI ADouble operator>> (int x) const {return *this * (AScalar::One() >> x);}

    _AI ADouble& operator<<= (int x) {return (*this = *this << x);}
    _AI ADouble& operator>>= (int x) {return (*this = *this >> x);}

    _AI ADouble inverse() const {
        vr64 V_abs = vr64_pair(abs_fr(get_VRH(vr)), get_VRL(vr));
        uint64_t abs;
        vr64_storei(V_abs, (vr64*) &abs, 0);
        uint64_t est = 0x5fe6eb50c7b537a9ULL - (abs >> 1);
        vr64 V_isqrt = vr64_loadi((vr64*) &est, 0);
        vr64 V_dst   = dmuls(V_isqrt, V_isqrt, 0);
        vr64 V_2     = convert_32F_to_64F(seta_fr(2,  0));

        // Four iterations of Newton's method
        for (int i = 0; i < 4; i++)
            V_dst = dmuls(V_dst, dmacs(V_2, V_dst, V_abs, 1), 0);

        // Copy original sign bit
        set_VRH(V_dst, s_copy(get_VRH(V_dst), get_VRH(vr)));
        return V_dst;
    }

    _AI ADouble d_invsqrt() const {
        uint64_t x;
        vr64_storei(vr, (vr64*) &x, 0);
        uint64_t est = 0x5fe6eb50c7b537a9ULL - (x >> 1);
        vr64 V_isqrt = vr64_loadi((vr64*) &est, 0);
        vr64 V_half  = convert_32F_to_64F(seta_fr(3,  0));
        vr64 V_3     = convert_32F_to_64F(seta_fr(28, 0));

        // Four iterations of Newton's method
        for (int i = 0; i < 4; i++)
            V_isqrt = dmuls(dmuls(V_half, V_isqrt, 0),
                            dmacs(V_3, V_isqrt, dmuls(V_isqrt, vr, 0), 1),
                            0);
        return V_isqrt;
    }

    _AI ADouble mul_add(const ADouble& x, const ADouble& y) const {
        return dmacs(vr, x.vr, y.vr, 0);
    }
    _AI ADouble mul_sub(const ADouble& x, const ADouble& y) const {
        return dmacs(vr, x.vr, y.vr, 1);
    }
    _AI ADouble& mul_acc(const ADouble& x, const ADouble& y) {
        vr = dmacs(vr, x.vr, y.vr, 0);
        return *this;
    }
    _AI ADouble& mul_dec(const ADouble& x, const ADouble& y) {
        vr = dmacs(vr, x.vr, y.vr, 1);
        return *this;
    }

    _AI ADouble abs() const {
        return vr64_pair(abs_fr(get_VRH(vr)), get_VRL(vr));
    }

#ifdef vsel_ar
    _AI ADouble max(const ADouble& x) const {
        return vsel_ar(vr, x.vr, dgez(dadds(vr, x.vr, 1)));
    }
    _AI ADouble min(const ADouble& x) const {
        return vsel_ar(vr, x.vr, dlez(dadds(vr, x.vr, 1)));
    }
#else
    _AI ADouble max(const ADouble& x) const {
        return vsel(vr, x.vr, 3 * dgez(dadds(vr, x.vr, 1)));
    }
    _AI ADouble min(const ADouble& x) const {
        return vsel(vr, x.vr, 3 * dlez(dadds(vr, x.vr, 1)));
    }
#endif

    _AI ADouble clamp(const ADouble& low, const ADouble& high) const {
        return max(low).min(high);
    }

    _AI static ADouble MinusOne()  {return convert_32F_to_64F(seta_fr(17, 0));}
    _AI static ADouble Zero()      {return vseta_vr(0,  0);}
    _AI static ADouble One()       {return convert_32F_to_64F(seta_fr(1,  0));}
    _AI static ADouble Two()       {return convert_32F_to_64F(seta_fr(2,  0));}
    _AI static ADouble Three()     {return convert_32F_to_64F(seta_fr(28, 0));}
    _AI static ADouble Half()      {return convert_32F_to_64F(seta_fr(3,  0));}

    // For debugging:

    _AI double to_double() const {
        vr64 V_tmp = vr;
        convert_64F_to_IEEE_double(V_tmp);
        double z;
        vr64_storei(V_tmp, (vr64*) &z, 0);
        return z;
    }
};

//AScalar::AScalar(const ADouble &d) : fr(convert_64F_to_32F(d.vr)) {}

#endif
