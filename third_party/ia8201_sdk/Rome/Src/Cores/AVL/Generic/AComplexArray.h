////////////////////////////////////////////////////////////////////////////////
///
/// \file AComplexArray.h
///
/// ComplexArray wrapper for generic C++
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ACOMPLEXARRAY_H
#define ACOMPLEXARRAY_H

#include "AScalarArray.h"
#include "AComplex.h"

struct AComplexArray
{
    AComplex* a;
    int N;

    _AI AComplexArray() {}
    _AI AComplexArray(int n, AComplex* ptr)    : a(ptr), N(n) {}

    _AI void init(int n, AComplex* ptr)    {N = n; a = ptr;}
    _AI int length() {return N;}

    _AI AComplexArray& operator= (const AComplexArray& x) {
        if (&x != this)
            copy(x);
        return *this;
    }

    _AI operator AComplex* () {return (AComplex*) a;}
    _AI operator const AComplex* () const {return (const AComplex*) a;}
    _AI AComplex& operator[] (int i) const {return ((AComplex*) a)[i];}

    _AI bool operator== (const AComplexArray& x) const {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            if (a[i] != x[i])
                return false;
        return true;
    }

    _AI bool operator!= (const AComplexArray& x) const {
        return !(*this == x);
    }

    _AI void fill(const AComplex& x) {
        for (int i = 0; i < N; i++)
            a[i] = x;
    }
    _AI void copy(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i];
    }
    _AI void conj(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = std::conj(x[i].vr);
    }

    _AI void add(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] + y;
    }
    _AI void add(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] + y[i];
    }
    _AI void sub(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] - y;
    }
    _AI void sub(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] - y[i];
    }
    _AI void mul(const AComplexArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] * y;
    }
    _AI void mul(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] * y;
    }
    _AI void mul(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] * y[i];
    }
    _AI void mul_conj(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] * std::conj(y[i].vr);
    }
    _AI void mul_acc(const AComplexArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] += x[i] * y;
    }
    _AI void mul_acc(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] += x[i] * y[i];
    }
    _AI void mul_conj_acc(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] += x[i] * std::conj(y[i].vr);
    }

    _AI AComplex sum() const {
        AComplex sum(0, 0);

        for (int i = 0; i < N; i++)
            sum += a[i];

        return sum;
    }

    _AI AScalar norm_sq() const {
        float sum = 0;

        for (int i = 0; i < N; i++)
            sum += a[i].norm_sq().fr;

        return sum;
    }

    _AI AComplex dot(const AComplexArray& x) const {
        AVL_ASSERT(N == x.N);
        AComplex sum(0, 0);

        for (int i = 0; i < N; i++)
            sum += a[i].mul_conj(x[i]);

        return sum;
    }

    _AI AScalar norm() const {return norm_sq().f_sqrt();}

    _AI void normalize(const AComplexArray& x) {
        mul(x, x.norm_sq().f_invsqrt());
    }
    
    _AI void inverse(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].inverse();
    }

    // Matrix operations

    _AI void column(const struct AComplexMatrix& x, int col);

    _AI void mul(const AComplexArray& x, const struct AComplexMatrix& y);
    _AI void mul(const struct AComplexMatrix& x, const AComplexArray& y);
    _AI void mul_conj(const struct AComplexMatrix& x, const AComplexArray& y);
};

_AI void AScalarArray::norm_sq(const struct AComplexArray& x) {
    AVL_ASSERT(N == x.N);
    for (int i = 0; i < N; i++)
        a[i] = x[i].norm_sq();
}

#endif

/** \class AComplexArray
    \brief Wraps an abstract pointer to an AComplex and a length

    \fn AComplexArray::AComplexArray(int n, AComplex* ptr)
    \brief Constructor taking a length and a pointer

    \fn void AComplexArray::init(int n, AComplex* ptr)
    \brief Reinitialize with a length and a pointer

    \fn int AComplexArray::length()
    \brief Returns the number of elements

    \fn void AComplexArray::fill(const AComplex& x)
    \brief Fills array with copies of x

    \fn void AComplexArray::copy(const AComplexArray& x)
    \brief Copies array from the elements of x

    \fn void AComplexArray::conj(const AComplexArray& x)
    \brief *this = conj(x) elementwise

    \fn void AComplexArray::add(const AComplexArray& x, const AComplex& y)
    \brief *this = x + y elementwise

    \fn void AComplexArray::add(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x + y elementwise

    \fn void AComplexArray::sub(const AComplexArray& x, const AComplex& y)
    \brief *this = x - y elementwise

    \fn void AComplexArray::sub(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x - y elementwise

    \fn void AComplexArray::mul(const AComplexArray& x, const AScalar& y)
    \brief *this = x * y elementwise

    \fn void AComplexArray::mul(const AComplexArray& x, const AComplex& y)
    \brief *this = x * y elementwise

    \fn void AComplexArray::mul(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x * y elementwise

    \fn void AComplexArray::mul_conj(const AComplexArray& x, const AComplexArray& y)
    \brief *this = x * y.conj() elementwise

    \fn void AComplexArray::mul_acc(const AComplexArray& x, const AScalar& y)
    \brief *this += x * y elementwise

    \fn void AComplexArray::mul_acc(const AComplexArray& x, const AComplexArray& y)
    \brief *this += x * y elementwise

    \fn void AComplexArray::mul_conj_acc(const AComplexArray& x, const AComplexArray& y)
    \brief *this += x * y.conj() elementwise

    \fn AComplex AComplexArray::sum()
    \brief Returns the sum of the elements

    \fn AComplex AComplexArray::norm_sq()
    \brief Returns the sum of (r()**2 + i()**2) for each element

    \fn AComplexArray AComplexArray::dot(const AComplexArray& x)
    \brief Returns the inner product with x

    \fn AComplex AComplexArray::norm()
    \brief Returns the Euclidean norm of the vector

    \fn void AComplexArray::normalize()
    \brief Normalizes the vector

    \fn void AComplexArray::inverse(const AComplexArray& x)
    \brief *this = (1.0 / x) elementwise

    \fn void AComplexArray::column(const struct AComplexMatrix& x, int col);
    \brief *this = x[:, col]

    \fn void AComplexArray::mul(const AComplexArray& x, const struct AComplexMatrix& y)
    \brief *this = x * y

    \fn void AComplexArray::mul(const struct AComplexMatrix& x, const AComplexArray& y)
    \brief *this = x * y

    \fn void AComplexArray::mul_conj(const struct AComplexMatrix& x, const AComplexArray& y)
    \brief *this = x * y.conj()
*/
