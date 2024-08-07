/************************************************************************//**
 * @file    AVL/Hemi/AComplexArray.h
 *
 * @brief   ComplexArray wrapper for HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

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

    _AI void init(int n, AComplex* ptr)    {a = ptr; N = n;}
    _AI int length() {return N;}

    _AI AComplexArray& operator= (const AComplexArray& x) {
        if (&x != this)
            copy(x);
        return *this;
    }

    _AI operator AComplex* () {return a;}
    _AI operator const AComplex* () const {return a;}
    _AI AComplex& operator[] (int i) const {return a[i];}

    _AI bool operator== (const AComplexArray& x) const {
        AVL_ASSERT(N == x.N);
        atbool bx2 = 0;

        for (int i = 0; i < N; i++)
            bx2 = orb2(bx2, vne(a[i], x[i]));

        return !move_ar_bbr(bx2);
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
            a[i]= x[i];
    }

    _AI void conj(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i]= x[i].conj();
    }

    _AI void add(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = vadds(x[i], y, 0);
    }

    _AI void add(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = vadds(x[i], y[i], 0);
    }

    _AI void sub(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = vadds(x[i], y, 10);
    }

    _AI void sub(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = vadds(x[i], y[i], 10);
    }

    _AI void mul(const AComplexArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = vmulf(x[i], y, 0);
    }

    _AI void mul(const AComplexArray& x, const AComplex& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = cmul(x[i], y, CONJ_NONE);
    }

    _AI void mul(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = cmul(x[i], y[i], CONJ_NONE);
    }

    _AI void mul_conj(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = cmul(x[i], y[i], CONJ_Y);
    }

    _AI void mul_acc(const AComplexArray& x, const AScalar& y) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = vmacf(a[i], x[i], y, 0, 0);
    }

    _AI void mul_acc(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = cmac(a[i], x[i], y[i], CONJ_NONE);
    }

    _AI void mul_conj_acc(const AComplexArray& x, const AComplexArray& y) {
        AVL_ASSERT(N == x.N && N == y.N);
        for (int i = 0; i < N; i++)
            a[i] = cmac(a[i], x[i], y[i], CONJ_Y);
    }

    _AI AComplex sum() const {
        vr64 V_dst = vseta_vr(0, 0);

        for (int i = 0; i < N; i++)
            V_dst = vadds(V_dst, a[i], 0);

        return V_dst;
    }

    _AI AScalar norm_sq() const {
        vr64 V_dst = vseta_vr(0, 0);

        for (int i = 0; i < N; i++)
            V_dst = cmac(V_dst, a[i], a[i], CONJ_Y);

        return get_VRL(V_dst);
    }

    _AI AComplex dot(const AComplexArray& x) const {
        AVL_ASSERT(N == x.N);
        vr64 V_dst = vseta_vr(0, 0);

        for (int i = 0; i < N; i++)
            V_dst = cmac(V_dst, a[i], x[i], CONJ_Y);

        return V_dst;
    }

    _AI AScalar norm() const {return norm_sq().f_sqrt();}

    _AI void normalize(const AComplexArray& x) {mul(x, x.norm_sq().f_invsqrt());}
    
    _AI void inverse(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = x[i].inverse();
    }

    // Matrix operations

    _AI void column(const struct AComplexMatrix& x, int col);

    void mul(const AComplexArray& x, const struct AComplexMatrix& y);
    void mul(const struct AComplexMatrix& x, const AComplexArray& y);
    void mul_conj(const struct AComplexMatrix& x, const AComplexArray& y);
};

_AI void AScalarArray::norm_sq(const AComplexArray& x) {
        AVL_ASSERT(N == x.N);
        for (int i = 0; i < N; i++)
            a[i] = get_VRL(cmul(x[i], x[i], CONJ_Y));
}

#endif
