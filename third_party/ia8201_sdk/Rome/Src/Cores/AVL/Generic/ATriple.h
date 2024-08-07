///////////////////////////////////////////////////////////////////////////////
///
/// \file ATriple.h
///
/// ATriple wrapper for float[4]
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ATRIPLE_H
#define ATRIPLE_H
    
#include "AScalar.h"

struct ATriple
{
    float a[4];

    _AI ATriple() {}
    _AI ATriple(const ATriple& x) {copy(x);}
    _AI ATriple& operator= (const ATriple& x) {if (&x != this) copy(x); return *this;}

    _AI static int length() {return 3;}
    _AI static ATriple Zero() {return ATriple(0, 0, 0);}

    _AI const AScalar& operator[] (int i) const {return ((const AScalar*) a)[i];}

    _AI bool operator== (const ATriple& x) const {
        bool b = true;

        for (int i = 0; i < 3; i++)
            b = b && (a[i] == x.a[i]);

        return b;
    }

    _AI bool operator!= (const ATriple& x) const {
        return !(*this == x);
    }

    _AI ATriple& fill(const AScalar& x) {
        for (int i = 0; i < 3; i++)
            a[i] = x.fr;

        return *this;
    }

    _AI ATriple& copy(const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] = x.a[i];

        return *this;
    }

    _AI ATriple& add(const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] += x.a[i];

        return *this;
    }

    _AI ATriple& sub(const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] -= x.a[i];

        return *this;
    }

    _AI ATriple& mul(const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] *= x.a[i];

        return *this;
    }

    _AI ATriple& div(const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] /= x.a[i];

        return *this;
    }

    _AI ATriple& mul_acc(const ATriple& x, const ATriple& y) {
        for (int i = 0; i < 3; i++)
            a[i] += x.a[i] * y.a[i];

        return *this;
    }

    _AI ATriple& mul_acc(const ATriple& x, const AScalar& y) {
        for (int i = 0; i < 3; i++)
            a[i] += x.a[i] * y.fr;

        return *this;
    }

    _AI ATriple& add(const AScalar& x) {
        for (int i = 0; i < 3; i++)
            a[i] += x.fr;

        return *this;
    }

    _AI ATriple& sub(const AScalar& x) {
        for (int i = 0; i < 3; i++)
            a[i] -= x.fr;

        return *this;
    }

    _AI ATriple& mul(const AScalar& x) {
        for (int i = 0; i < 3; i++)
            a[i] *= x.fr;

        return *this;
    }

    _AI ATriple& div(const AScalar& x) {
        for (int i = 0; i < 3; i++)
            a[i] /= x.fr;

        return *this;
    }

    _AI ATriple& abs() {
        for (int i = 0; i < 3; i++)
            a[i] = fabsf(a[i]);

        return *this;
    }

    _AI ATriple& max(const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] = fmaxf(a[i], x.a[i]);

        return *this;
    }

    _AI ATriple& min(const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] = fminf(a[i], x.a[i]);

        return *this;
    }

    _AI ATriple& clamp(const AScalar& low, const AScalar& high) {
        for (int i = 0; i < 3; i++)
            a[i] = fminf(fmaxf(a[i], low.fr), high.fr);

        return *this;
    }

    _AI AScalar sum() const {
        float sum = 0;

        for (int i = 0; i < 3; i++)
            sum += a[i];

        return sum;
    }

    _AI AScalar sum_sq() const {
        float sum = 0;

        for (int i = 0; i < 3; i++)
            sum += a[i] * a[i];

        return sum;
    }

    _AI AScalar dot(const ATriple& x) const {
        float sum = 0;

        for (int i = 0; i < 3; i++)
            sum += a[i] * x.a[i];

        return sum;
    }

    _AI AScalar max_abs() const {
        float x = 0;

        for (int i = 0; i < 3; i++)
            x = fmaxf(x, fabsf(a[i]));

        return x;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}
    _AI ATriple& normalize() {return mul(sum_sq().f_invsqrt());}


    //
    // Additional methods not in AVector<N>
    //

    _AI ATriple(const AScalar& x, const AScalar& y, const AScalar& z) {
        a[0] = x.fr;
        a[1] = y.fr;
        a[2] = z.fr;
    }
    _AI ATriple(float x, float y, float z) {
        a[0] = x;
        a[1] = y;
        a[2] = z;
    }

    _AI ATriple operator* (const ATriple& x) const {
        ATriple z;

        for (int i = 0; i < 3; i++)
            z.a[i] = a[i] * x.a[i];

        return z;
    }
    _AI ATriple operator+ (const ATriple& x) const {
        ATriple z;

        for (int i = 0; i < 3; i++)
            z.a[i] = a[i] + x.a[i];

        return z;
    }
    _AI ATriple operator- (const ATriple& x) const {
        ATriple z;

        for (int i = 0; i < 3; i++)
            z.a[i] = a[i] - x.a[i];

        return z;
    }
    _AI ATriple operator- () const {
        ATriple z;

        for (int i = 0; i < 3; i++)
            z.a[i] = -a[i];

        return z;
    }

    _AI ATriple& operator*= (const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] *= x.a[i];

        return *this;
    }
    _AI ATriple& operator+= (const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] += x.a[i];

        return *this;
    }
    _AI ATriple& operator-= (const ATriple& x) {
        for (int i = 0; i < 3; i++)
            a[i] -= x.a[i];

        return *this;
    }

    _AI ATriple operator* (const AScalar& x) const {
        ATriple z;

        for (int i = 0; i < 3; i++)
            z.a[i] = a[i] * x.fr;

        return z;
    }
    _AI ATriple& operator*= (const AScalar& x) {
        for (int i = 0; i < 3; i++)
            a[i] *= x.fr;

        return *this;
    }

    _AI ATriple mul_add(const ATriple& x, const ATriple& y) const {
        ATriple z;
        for (int i = 0; i < 3; i++)
            z.a[i] = a[i] + x.a[i] * y.a[i];

        return z;
    }
    _AI ATriple mul_sub(const ATriple& x, const ATriple& y) const {
        ATriple z;
        for (int i = 0; i < 3; i++)
            z.a[i] = a[i] - x.a[i] * y.a[i];

        return z;
    }

    _AI AScalar x() const {return a[0];}
    _AI AScalar y() const {return a[1];}
    _AI AScalar z() const {return a[2];}

    _AI ATriple& set_x(const AScalar& x) {a[0] = x.fr; return *this;}
    _AI ATriple& set_y(const AScalar& x) {a[1] = x.fr; return *this;}
    _AI ATriple& set_z(const AScalar& x) {a[2] = x.fr; return *this;}
};

_AI ATriple AScalar::operator* (const struct ATriple& x) const {
    ATriple z;
    for (int i = 0; i < 3; i++)
        z.a[i] = fr * x.a[i];

    return z;
}

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
