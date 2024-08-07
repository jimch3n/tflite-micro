////////////////////////////////////////////////////////////////////////////////
///
/// \file AComplexVector.h
///
/// Complex Vector wrapper for std::complex<float>[N]
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ACOMPLEXVECTOR_H
#define ACOMPLEXVECTOR_H

#include "AComplex.h"
#include "AVector.h"

template <int N>
struct AComplexVector
{
    std::complex<float> a[N];

    _AI AComplexVector() {}
    _AI AComplexVector(const AComplexVector& x) {copy(x);}
    _AI AComplexVector& operator= (const AComplexVector& x) {
        if (&x != this) copy(x);
        return *this;
    }
    _AI AComplexVector(const AVector<N>& x) {*this = x;}
    _AI AComplexVector& operator= (const AVector<N>& x) {
        for (int i = 0; i < N; i++)
            a[i] = x.a[i];

        return *this;
    }

    _AI static int length() {return N;}

    _AI operator AComplex* () {return (AComplex*) a;}
    _AI operator const AComplex* () const {return (const AComplex*) a;}
    _AI AComplex& operator[] (int i) const {return ((AComplex*) a)[i];}

    _AI bool operator== (const AComplexVector& x) const {
        bool b = true;

        for (int i = 0; i < N; i++)
            b = b && (a[i] == x.a[i]);

        return b;
    }

    _AI bool operator!= (const AComplexVector& x) const {
        return !(*this == x);
    }

    _AI AComplexVector& fill(const AComplex& x) {
        for (int i = 0; i < N; i++)
            a[i] = x.vr;

        return *this;
    }

    _AI AComplexVector& copy(const AComplexVector& x) {
        for (int i = 0; i < N; i++)
            a[i] = x.a[i];

        return *this;
    }

    _AI AComplexVector& add(const AComplex& x) {
        for (int i = 0; i < N; i++)
            a[i] += x.vr;

        return *this;
    }

    _AI AComplexVector& add(const AComplexVector& x) {
        for (int i = 0; i < N; i++)
            a[i] += x.a[i];

        return *this;
    }

    _AI AComplexVector& sub(const AComplex& x) {
        for (int i = 0; i < N; i++)
            a[i] -= x.vr;

        return *this;
    }

    _AI AComplexVector& sub(const AComplexVector& x) {
        for (int i = 0; i < N; i++)
            a[i] -= x.a[i];

        return *this;
    }

    _AI AComplexVector& mul(const AScalar& x) {
        for (int i = 0; i < N; i++)
            a[i] *= x.fr;

        return *this;
    }

    _AI AComplexVector& mul(const AComplex& x) {
        for (int i = 0; i < N; i++)
            a[i] *= x.vr;

        return *this;
    }

    _AI AComplexVector& mul(const AComplexVector& x) {
        for (int i = 0; i < N; i++)
            a[i] *= x.a[i];

        return *this;
    }

    _AI AComplexVector& mul_conj(const AComplexVector& x) {
        for (int i = 0; i < N; i++)
            a[i] *= std::conj(x.a[i]);

        return *this;
    }

    _AI AComplexVector& mul_acc(const AComplexVector& x, const AComplex& y) {
        for (int i = 0; i < N; i++)
            a[i] += x.a[i] * y.vr;

        return *this;
    }

    _AI AComplexVector& mul_acc(const AComplexVector& x, const AComplexVector& y) {
        for (int i = 0; i < N; i++)
            a[i] += x.a[i] * y.a[i];

        return *this;
    }

    _AI AComplexVector& mul_conj_acc(const AComplexVector& x, const AComplexVector& y) {
        for (int i = 0; i < N; i++)
            a[i] += x.a[i] * std::conj(y.a[i]);

        return *this;
    }

    _AI AComplex sum() const {
        std::complex<float> sum(0, 0);

        for (int i = 0; i < N; i++)
            sum += a[i];

        return sum;
    }

    _AI AScalar norm_sq() const {
        float sum(0);

        for (int i = 0; i < N; i++)
            sum += std::norm(a[i]);

        return sum;
    }

    _AI AComplex dot(const AComplexVector& x) const {
        std::complex<float> sum(0, 0);

        for (int i = 0; i < N; i++)
            sum += a[i] * std::conj(x.a[i]);

        return sum;
    }

    _AI AScalar norm() const        {return norm_sq().f_sqrt();}
    _AI AComplexVector& normalize() {return mul(norm_sq().f_invsqrt());}
};

/** \class AComplexVector
    \brief Abstract fixed length vector of AComplex

    \fn AComplexVector::AComplexVector(const AComplexVector& x)
    \brief Copy constructor

    \fn static int AComplexVector::length()
    \brief Returns the number of elements

    \fn AComplexVector& AComplexVector::fill(const Acomplex& x)
    \brief Fills vector with copies of x

    \fn AComplexVector& AComplexVector::copy(const AComplexVector& x)
    \brief Copies vector from the elements of x

    \fn AComplexVector& AComplexVector::add(const AComplex& x)
    \brief Returns *this += x elementwise

    \fn AComplexVector& AComplexVector::add(const AComplexVector& x)
    \brief Returns *this += x elementwise

    \fn AComplexVector& AComplexVector::sub(const AComplex& x)
    \brief Returns *this -= x elementwise

    \fn AComplexVector& AComplexVector::sub(const AComplexVector& x)
    \brief Returns *this -= x elementwise

    \fn AComplexVector& AComplexVector::mul(const AScalar& x)
    \brief Returns *this *= x elementwise

    \fn AComplexVector& AComplexVector::mul(const AComplex& x)
    \brief Returns *this *= x elementwise

    \fn AComplexVector& AComplexVector::mul(const AComplexVector& x)
    \brief Returns *this *= x elementwise

    \fn AComplexVector& AComplexVector::mul_conj(const AComplexVector& x)
    \brief Returns *this *= x.conj() elementwise

    \fn AComplexVector& AComplexVector::mul_acc(const AComplexVector& x, const AComplex& y)
    \brief Returns *this += x * y elementwise

    \fn AComplexVector& AComplexVector::mul_acc(const AComplexVector& x, const AComplexVector& y)
    \brief Returns *this += x * y elementwise

    \fn AComplexVector& AComplexVector::mul_conj_acc(const AComplexVector& x, const AComplexVector& y)
    \brief Returns *this += x * y.conj() elementwise

    \fn AComplex AComplexVector::sum()
    \brief Returns the sum of the elements

    \fn AScalar AComplexVector::norm_sq()
    \brief Returns the sum of r()**2 + i()**2

    \fn AComplex AComplexVector::dot(const AComplexVector& x)
    \brief Returns the inner product with x

    \fn AScalar AComplexVector::norm()
    \brief Returns the sqrare root of the sum of r()**2 + i()**2

    \fn AComplexVector& AComplexVector::normalize()
    \brief Normalizes the vector
*/

#endif
