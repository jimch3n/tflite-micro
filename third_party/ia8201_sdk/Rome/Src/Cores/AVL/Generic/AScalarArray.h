////////////////////////////////////////////////////////////////////////////////
///
/// \file AScalarArray.h
///
/// ScalarArray wrapper for generic C++
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ASCALARARRAY_H
#define ASCALARARRAY_H

#include "AScalar.h"

struct AScalarArray
{
    AScalar* a;
    int N;

    _AI AScalarArray() {}
    _AI AScalarArray(int n, AScalar* ptr) : a(ptr), N(n) {}

    _AI void init(int n, AScalar* ptr) {N = n; a = ptr;}
    _AI int length() const {return N;}

    _AI AScalarArray& operator= (const AScalarArray& x) {
        if (&x != this)
            copy(x);
        return *this;
    }

    _AI operator AScalar* () {return (AScalar*) a;}
    _AI operator const AScalar* () const {return (const AScalar*) a;}
    _AI AScalar& operator[] (int i) const {return ((AScalar*) a)[i];}

    _AI bool operator== (const AScalarArray& x) const {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            if (a[i] != x[i])
                return false;
        return true;
    }

    _AI bool operator!= (const AScalarArray& x) const {
        return !(*this == x);
    }

    _AI void fill(const AScalar& x) {
        for (int i = 0; i < N; i++)
            a[i] = x;
    }
    _AI void copy(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i];
    }

    _AI void add(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] + y;
    }
    _AI void add(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] + y[i];
    }
    _AI void sub(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] - y;
    }
    _AI void sub(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] - y[i];
    }
    _AI void mul(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] * y;
    }
    _AI void mul(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] * y[i];
    }
    _AI void div(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] / y;
    }
    _AI void div(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] / y[i];
    }

    _AI void mul_acc(const AScalarArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] += x[i] * y;
    }
    _AI void mul_acc(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] += x[i] * y[i];
    }

    _AI void max(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_max(y[i]);
    }
    _AI void min(const AScalarArray& x, const AScalarArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_min(y[i]);
    }
    _AI void clamp(const AScalarArray& x, const AScalar& low, const AScalar& high) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = AScalar(fmaxf(fminf(x[i].fr, high.fr), low.fr));
    }

    _AI void abs(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].abs();
    }
    _AI void f_inv(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_inv();
    }
    _AI void f_invsqrt(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_invsqrt();
    }
    _AI void f_sigmoid(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_sigmoid();
    }
    _AI void f_log2(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_log2();
    }
    _AI void f_pow2(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_pow2();
    }
    _AI void f_sqrt(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].f_sqrt();
    }

    _AI void sine_turns(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].sine_turns();
    }
    _AI void cosine_turns(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].cosine_turns();
    }
    _AI void sine_rads(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].sine_rads();
    }
    _AI void cosine_rads(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].cosine_rads();
    }
    
    _AI void f_exp(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = AScalar(expf(x.a[i].fr));
    }
    
    _AI void f_log(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = AScalar(logf(x.a[i].fr));
    }
    
    _AI void inverse(const AScalarArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].inverse();
    }

    _AI AScalar sum() const {
        float sum = 0;

        for (int i = 0; i < N; i++)
            sum += a[i].fr;

        return sum;
    }

    _AI AScalar sum_sq() const {
        float sum = 0;

        for (int i = 0; i < N; i++)
            sum += a[i].fr * a[i].fr;

        return sum;
    }

    _AI AScalar dot(const AScalarArray& x) const {
        AVL_ASSERT(N == x.N);
        float sum = 0;

        for (int i = 0; i < N; i++)
            sum += a[i].fr * x[i].fr;

        return sum;
    }

    _AI AScalar max_abs() const {
        float x = 0;

        for (int i = 0; i < N; i++)
            x = fmaxf(x, fabsf(a[i].fr));

        return x;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}

    _AI void normalize(const AScalarArray& x) {mul(x, x.sum_sq().f_invsqrt());}
    
    _AI void norm_sq(const struct AComplexArray& x);

    // out[i] = x[i] > y ? a : b;

    _AI void compGt(const AScalarArray& x, const AScalar& y,
                    const AScalar& aa,     const AScalar& bb) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] > y ? aa : bb;
    }

    // out[i] = x[i] > y[i] ? a : b;

    _AI void compGt(const AScalarArray& x, const AScalarArray& y,
                    const AScalar& aa,     const AScalar& bb) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i] > y[i] ? aa : bb;
    }

    // Matrix operations

    _AI void column(const struct AScalarMatrix& x, int col);

    _AI void mul(const AScalarArray& x, const struct AScalarMatrix& y);
    _AI void mul(const struct AScalarMatrix& x, const AScalarArray& y);
};

#endif

/** \class AScalarArray
    \brief Wraps an abstract pointer to an AScalar and a length

    \fn AScalarArray::AScalarArray(int n, AScalar* ptr)
    \brief Constructor taking a length and a pointer

    \fn void AScalarArray::init(int n, AScalar* ptr)
    \brief Reinitialize with a length and a pointer

    \fn int AScalarArray::length()
    \brief Returns the number of elements

    \fn void AScalarArray::fill(const AScalar& x)
    \brief Fills array with copies of x

    \fn void AScalarArray::copy(const AScalarArray& x)
    \brief Copies array from the elements of x

    \fn void AScalarArray::add(const AScalarArray& x, const AScalar& y)
    \brief *this = x + y elementwise

    \fn void AScalarArray::add(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x + y elementwise

    \fn void AScalarArray::sub(const AScalarArray& x, const AScalar& y)
    \brief *this = x - y elementwise

    \fn void AScalarArray::sub(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x - y elementwise

    \fn void AScalarArray::mul(const AScalarArray& x, const AScalar& y)
    \brief *this = x * y elementwise

    \fn void AScalarArray::mul(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x * y elementwise

    \fn void AScalarArray::div(const AScalarArray& x, const AScalar& y)
    \brief *this = x / y elementwise

    \fn void AScalarArray::div(const AScalarArray& x, const AScalarArray& y)
    \brief *this = x / y elementwise

    \fn void AScalarArray::mul_acc(const AScalarArray& x, const AScalar& y)
    \brief *this += x * y elementwise

    \fn void AScalarArray::mul_acc(const AScalarArray& x, const AScalarArray& y)
    \brief *this += x * y elementwise

    \fn void AScalarArray::max(const AScalarArray& x, const AScalarArray& y)
    \brief *this = max(x, y) elementwise

    \fn void AScalarArray::min(const AScalarArray& x, const AScalarArray& y)
    \brief *this = min(x, y) elementwise

    \fn void AScalarArray::clamp(const AScalarArray& x, const AScalar& low, const AScalar& high)
    \brief *this = max(min(x, high), low) elementwise

    \fn void AScalarArray::abs(const AScalarArray& x)
    \brief *this = abs(x) elementwise

    \fn void AScalarArray::f_inv(const AScalarArray& x)
    \brief *this = (1.0 / x) elementwise

    \fn void AScalarArray::f_invsqrt(const AScalarArray& x)
    \brief *this = (1.0 / sqrt(x)) elementwise

    \fn void AScalarArray::f_sigmoid(const AScalarArray& x)
    \brief *this = (x < 0 ? 2**(x - 1) : 1 - 2**(-x - 1)) elementwise

    \fn void AScalarArray::f_log2(const AScalarArray& x)
    \brief *this = log2(x) elementwise

    \fn void AScalarArray::f_pow2(const AScalarArray& x)
    \brief *this = 2**x elementwise

    \fn void AScalarArray::f_sqrt(const AScalarArray& x)
    \brief *this = sqrt(x) elementwise

    \fn void AScalarArray::sine_turns(const AScalarArray& x)
    \brief *this = sin(2π * x) elementwise

    \fn void AScalarArray::cosine_turns(const AScalarArray& x)
    \brief *this = cos(2π * x) elementwise

    \fn void AScalarArray::sine_rads(const AScalarArray& x)
    \brief *this = sin(x) elementwise

    \fn void AScalarArray::cosine_rads(const AScalarArray& x)
    \brief *this = cos(x) elementwise

    \fn void AScalarArray::f_exp(const AScalarArray& x)
    \brief *this = exp(x) elementwise

    \fn void AScalarArray::f_log(const AScalarArray& x)
    \brief *this = log(x) elementwise

    \fn void AScalarArray::inverse(const AScalarArray& x)
    \brief *this = (1.0 / x) elementwise

    \fn AScalar AScalarArray::sum()
    \brief Returns the sum of the elements

    \fn AScalar AScalarArray::sum_sq()
    \brief Returns the sum of the squares of the elements

    \fn AScalarArray AScalarArray::dot(const AScalarArray& x)
    \brief Returns the inner product with x

    \fn AScalar AScalarArray::max_abs()
    \brief Returns the maximum absolute value of the elements

    \fn AScalar AScalarArray::norm()
    \brief Returns the Euclidean norm of the vector

    \fn void AScalarArray::normalize()
    \brief Normalizes the vector

    \fn void AScalarArray::norm_sq(const AComplexArray& x)
    \brief *this = (x.r()**2 + x.i()**2) elementwise

    \fn void AScalarArray::compGt(const AScalarArray& x, const AScalar& y, const AScalar& aa, const AScalar& bb)
    \brief *this = (x > y ? aa : bb) elementwise

    \fn void AScalarArray::compGt(const AScalarArray& x, const AScalarArray& y, const AScalar& aa, const AScalar& bb)
    \brief *this = (x > y ? aa : bb) elementwise

    \fn void AScalarArray::column(const struct AScalarMatrix& x, int col);
    \brief *this = x[:, col]

    \fn void AScalarArray::mul(const AScalarArray& x, const struct AScalarMatrix& y)
    \brief *this = x * y

    \fn void AScalarArray::mul(const struct AScalarMatrix& x, const AScalarArray& y)
    \brief *this = x * y
*/
