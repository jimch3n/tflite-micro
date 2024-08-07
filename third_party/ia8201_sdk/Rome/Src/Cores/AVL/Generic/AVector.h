////////////////////////////////////////////////////////////////////////////////
///
/// \file AVector.h
///
/// AVector wrapper for float[N]
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef AVECTOR_H
#define AVECTOR_H

#include "AComplex.h"

template <int N>
struct AVector
{
    float a[N];

    _AI AVector() {}
    _AI AVector(const AVector& x) {copy(x);}
    _AI AVector& operator= (const AVector& x) {if (&x != this) copy(x); return *this;}

    _AI static int length() {return N;}

    _AI operator AScalar* () {return (AScalar*) a;}
    _AI operator const AScalar* () const {return (const AScalar*) a;}
    _AI AScalar& operator[] (int i) const {return ((AScalar*) a)[i];}

    _AI bool operator== (const AVector& x) const {
        for (int i = 0; i < N; i++)
            if (a[i] != x.a[i])
                return false;
        return true;
    }

    _AI bool operator!= (const AVector& x) const {
        return !(*this == x);
    }

    _AI AVector& fill(const AScalar& x) {
        for (int i = 0; i < N; i++)
            a[i] = x.fr;

        return *this;
    }

    _AI AVector& copy(const AVector& x) {
        for (int i = 0; i < N; i++)
            a[i] = x.a[i];

        return *this;
    }

    _AI AVector& add(const AVector& x) {
        for (int i = 0; i < N; i++)
            a[i] += x.a[i];

        return *this;
    }

    _AI AVector& sub(const AVector& x) {
        for (int i = 0; i < N; i++)
            a[i] -= x.a[i];

        return *this;
    }

    _AI AVector& mul(const AVector& x) {
        for (int i = 0; i < N; i++)
            a[i] *= x.a[i];

        return *this;
    }

    _AI AVector& div(const AVector& x) {
        for (int i = 0; i < N; i++)
            a[i] /= x.a[i];

        return *this;
    }

    _AI AVector& mul_acc(const AVector& x, const AVector& y) {
        for (int i = 0; i < N; i++)
            a[i] += x.a[i] * y.a[i];

        return *this;
    }

    _AI AVector& mul_acc(const AVector& x, const AScalar& y) {
        for (int i = 0; i < N; i++)
            a[i] += x.a[i] * y.fr;

        return *this;
    }

    _AI AVector& add(const AScalar& x) {
        for (int i = 0; i < N; i++)
            a[i] += x.fr;

        return *this;
    }

    _AI AVector& sub(const AScalar& x) {
        for (int i = 0; i < N; i++)
            a[i] -= x.fr;

        return *this;
    }

    _AI AVector& mul(const AScalar& x) {
        for (int i = 0; i < N; i++)
            a[i] *= x.fr;

        return *this;
    }

    _AI AVector& div(const AScalar& x) {
        for (int i = 0; i < N; i++)
            a[i] /= x.fr;

        return *this;
    }

    _AI AVector& abs() {
        for (int i = 0; i < N; i++)
            a[i] = fabsf(a[i]);

        return *this;
    }

    _AI AVector& max(const AVector& x) {
        for (int i = 0; i < N; i++)
            a[i] = fmaxf(a[i], x.a[i]);

        return *this;
    }

    _AI AVector& min(const AVector& x) {
        for (int i = 0; i < N; i++)
            a[i] = fminf(a[i], x.a[i]);

        return *this;
    }

    _AI AVector& clamp(const AScalar& low, const AScalar& high) {
        for (int i = 0; i < N; i++)
            a[i] = fminf(fmaxf(a[i], low.fr), high.fr);

        return *this;
    }

    _AI AScalar sum() const {
        float sum = 0;

        for (int i = 0; i < N; i++)
            sum += a[i];

        return sum;
    }

    _AI AScalar sum_sq() const {
        float sum = 0;

        for (int i = 0; i < N; i++)
            sum += a[i] * a[i];

        return sum;
    }

    _AI AScalar dot(const AVector& x) const {
        float sum = 0;

        for (int i = 0; i < N; i++)
            sum += a[i] * x.a[i];

        return sum;
    }

    _AI AScalar max_abs() const {
        float x = 0;

        for (int i = 0; i < N; i++)
            x = fmaxf(x, fabsf(a[i]));

        return x;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}
    _AI AVector& normalize() {return mul(sum_sq().f_invsqrt());}
};

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
