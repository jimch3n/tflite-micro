///////////////////////////////////////////////////////////////////////////////
///
/// \file ADouble.h
///
/// ADouble wrapper for double
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ADOUBLE_H
#define ADOUBLE_H

#include "AScalar.h"

#if defined(_MSC_VER)
 #define fmax(A,B) std::max(A,B)
 #define fmin(A,B) std::min(A,B)
#endif

struct ADouble
{
    double vr;

    _AI ADouble() {}
    _AI ADouble(const ADouble& d) : vr(d.vr) {}
    _AI ADouble(const AScalar& s) : vr(s.fr) {}
    _AI ADouble(double a)         : vr(a) {}
    _AI ADouble(int32_t i)        : vr(i) {}

    _AI ADouble& operator= (const ADouble& d) {vr = d.vr; return *this;}
    _AI ADouble& operator= (double d)         {vr = d;    return *this;}
    _AI ADouble& operator= (int32_t i)        {vr = i;    return *this;}

    _AI int to_int() const {return (int) vr;}

    _AI ADouble operator* (const ADouble& x) const {return vr * x.vr;}
    _AI ADouble operator+ (const ADouble& x) const {return vr + x.vr;}
    _AI ADouble operator- (const ADouble& x) const {return vr - x.vr;}
    _AI ADouble operator- ()                 const {return -vr;}
    _AI ADouble operator/ (const ADouble& x) const {return vr / x.vr;}

    _AI ADouble& operator*= (const ADouble& x) {vr *= x.vr; return *this;}
    _AI ADouble& operator/= (const ADouble& x) {vr /= x.vr; return *this;}
    _AI ADouble& operator+= (const ADouble& x) {vr += x.vr; return *this;}
    _AI ADouble& operator-= (const ADouble& x) {vr -= x.vr; return *this;}

    _AI unsigned operator== (const ADouble& x) const {return vr == x.vr;}
    _AI unsigned operator>= (const ADouble& x) const {return vr >= x.vr;}
    _AI unsigned operator>  (const ADouble& x) const {return vr >  x.vr;}
    _AI unsigned operator<= (const ADouble& x) const {return vr <= x.vr;}
    _AI unsigned operator<  (const ADouble& x) const {return vr <  x.vr;}
    _AI unsigned operator!= (const ADouble& x) const {return vr != x.vr;}

    _AI ADouble operator<< (int x) const {return vr * pow(2.0, x);}
    _AI ADouble operator>> (int x) const {return vr * pow(2.0, -x);}

    _AI ADouble& operator<<= (int x) {vr = vr * pow(2.0, x);  return *this;}
    _AI ADouble& operator>>= (int x) {vr = vr * pow(2.0, -x); return *this;}

    _AI ADouble inverse()   const {return 1.0 / vr;}
    _AI ADouble d_invsqrt() const {return sqrt(1.0 / vr);}

    _AI ADouble mul_add(const ADouble& x, const ADouble& y) const {
        return vr + x.vr * y.vr;
    }
    _AI ADouble mul_sub(const ADouble& x, const ADouble& y) const {
        return vr - x.vr * y.vr;
    }
    _AI ADouble& mul_acc(const ADouble& x, const ADouble& y) {
        vr += x.vr * y.vr;
        return *this;
    }
    _AI ADouble& mul_dec(const ADouble& x, const ADouble& y) {
        vr -= x.vr * y.vr;
        return *this;
    }

    _AI ADouble abs() const                 {return fabs(vr);}
    _AI ADouble max(const ADouble& x) const {return fmax(vr, x.vr);}
    _AI ADouble min(const ADouble& x) const {return fmin(vr, x.vr);}
    _AI ADouble clamp(const ADouble& low, const ADouble& high) const {
        return max(low).min(high);
    }

    _AI static ADouble MinusOne()  {return -1.0;}
    _AI static ADouble Zero()      {return 0.0;}
    _AI static ADouble One()       {return 1.0;}
    _AI static ADouble Two()       {return 2.0;}
    _AI static ADouble Three()     {return 3.0;}
    _AI static ADouble Half()      {return 0.5;}

    // For debugging:

    _AI double to_double() const {return vr;}
};

_AI AScalar::AScalar(const struct ADouble& d) : fr(d.vr) {}

#endif

/** \class ADouble
    \brief Wrapper for a vr64 or a double

    \fn ADouble::ADouble(const ADouble& d)
    \brief Copy constructor

    \fn ADouble::ADouble(const double a)
    \brief Construct from a double

    \fn ADouble::ADouble(const AScalar& s)
    \brief Construct from an AScalar

    \fn ADouble::ADouble(int32_t i)
    \brief Construct from 32-bit integer

    \fn ADouble& ADouble::operator=(int32_t i)
    \brief Convert from 32-bit integer

    \fn ADouble& ADouble::operator=(double d)
    \brief Convert from double

    \fn int ADouble::to_int()
    \brief Convert to 32-bit integer

    \fn ADouble ADouble::inverse()
    \brief Returns 1.0 / *this

    \fn ADouble ADouble::d_invsqrt()
    \brief Returns sqrt(1.0 / *this)

    \fn ADouble ADouble::mul_add(const ADouble& x, const ADouble& y)
    \brief Returns *this + x * y

    \fn ADouble ADouble::mul_sub(const ADouble& x, const ADouble& y)
    \brief Returns *this - x * y

    \fn ADouble& ADouble::mul_acc(const ADouble& x, const ADouble& y)
    \brief Returns *this += x * y

    \fn ADouble& ADouble::mul_dec(const ADouble& x, const ADouble& y)
    \brief Returns *this -= x * y

    \fn ADouble ADouble::abs()
    \brief Returns abs(*this)

    \fn ADouble ADouble::max(const ADouble& x)
    \brief Returns max(*this, x)

    \fn ADouble ADouble::min(const ADouble& x)
    \brief Returns min(*this, x)

    \fn ADouble ADouble::clamp(const ADouble& low, const ADouble& high)
    \brief Returns max(min(*this, high), low)

    \fn static ADouble ADouble::MinusOne()
    \brief Returns -1.0

    \fn static ADouble ADouble::Zero()
    \brief Returns 0.0

    \fn static ADouble ADouble::One()
    \brief Returns 1.0

    \fn static ADouble ADouble::Two()
    \brief Returns 2.0

    \fn static ADouble ADouble::Three()
    \brief Returns 3.0

    \fn static ADouble ADouble::Half()
    \brief Returns 0.5

    \fn double ADouble::to_double()
    \brief Converts to double
*/
