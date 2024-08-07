///////////////////////////////////////////////////////////////////////////////
///
/// \file AQuad.h
///
/// AQuad wrapper for float[4]
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef AQUAD_H
#define AQUAD_H
    
#include "AComplex.h"

struct AQuad
{
    float a[4];

    _AI AQuad() {}
    _AI AQuad(const AQuad& x) {copy(x);}
    _AI AQuad& operator= (const AQuad& x) {if (&x != this) copy(x); return *this;}

    _AI static int length() {return 4;}
    _AI static AQuad Zero() {return AQuad(0, 0, 0, 0);}

    _AI const AScalar& operator[] (int i) const {return ((const AScalar*) a)[i];}

    _AI bool operator== (const AQuad& x) const {
        bool b = true;

        for (int i = 0; i < 4; i++)
            b = b && (a[i] == x.a[i]);

        return b;
    }

    _AI bool operator!= (const AQuad& x) const {
        return !(*this == x);
    }

    _AI AQuad& fill(const AScalar& x) {
        for (int i = 0; i < 4; i++)
            a[i] = x.fr;

        return *this;
    }

    _AI AQuad& copy(const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] = x.a[i];

        return *this;
    }

    _AI AQuad& add(const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] += x.a[i];

        return *this;
    }

    _AI AQuad& sub(const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] -= x.a[i];

        return *this;
    }

    _AI AQuad& mul(const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] *= x.a[i];

        return *this;
    }

    _AI AQuad& div(const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] /= x.a[i];

        return *this;
    }

    _AI AQuad& mul_acc(const AQuad& x, const AQuad& y) {
        for (int i = 0; i < 4; i++)
            a[i] += x.a[i] * y.a[i];

        return *this;
    }

    _AI AQuad& mul_acc(const AQuad& x, const AScalar& y) {
        for (int i = 0; i < 4; i++)
            a[i] += x.a[i] * y.fr;

        return *this;
    }

    _AI AQuad& add(const AScalar& x) {
        for (int i = 0; i < 4; i++)
            a[i] += x.fr;

        return *this;
    }

    _AI AQuad& sub(const AScalar& x) {
        for (int i = 0; i < 4; i++)
            a[i] -= x.fr;

        return *this;
    }

    _AI AQuad& mul(const AScalar& x) {
        for (int i = 0; i < 4; i++)
            a[i] *= x.fr;

        return *this;
    }

    _AI AQuad& div(const AScalar& x) {
        for (int i = 0; i < 4; i++)
            a[i] /= x.fr;

        return *this;
    }

    _AI AQuad& abs() {
        for (int i = 0; i < 4; i++)
            a[i] = fabsf(a[i]);

        return *this;
    }

    _AI AQuad& max(const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] = fmaxf(a[i], x.a[i]);

        return *this;
    }

    _AI AQuad& min(const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] = fminf(a[i], x.a[i]);

        return *this;
    }

    _AI AQuad& clamp(const AScalar& low, const AScalar& high) {
        for (int i = 0; i < 4; i++)
            a[i] = fminf(fmaxf(a[i], low.fr), high.fr);

        return *this;
    }

    _AI AScalar sum() const {
        float sum = 0;

        for (int i = 0; i < 4; i++)
            sum += a[i];

        return sum;
    }

    _AI AScalar sum_sq() const {
        float sum = 0;

        for (int i = 0; i < 4; i++)
            sum += a[i] * a[i];

        return sum;
    }

    _AI AScalar dot(const AQuad& x) const {
        float sum = 0;

        for (int i = 0; i < 4; i++)
            sum += a[i] * x.a[i];

        return sum;
    }

    _AI AScalar max_abs() const {
        float x = 0;

        for (int i = 0; i < 4; i++)
            x = fmaxf(x, fabsf(a[i]));

        return x;
    }

    _AI AScalar norm() const {return sum_sq().f_sqrt();}
    _AI AQuad& normalize() {return mul(sum_sq().f_invsqrt());}


    //
    // Additional methods not in AVector<N>
    //

    _AI AQuad(const AScalar& q0, const AScalar& q1, const AScalar& q2, const AScalar& q3) {
        a[0] = q0.fr;
        a[1] = q1.fr;
        a[2] = q2.fr;
        a[3] = q3.fr;
    }
    _AI AQuad(float q0, float q1, float q2, float q3) {
        a[0] = q0;
        a[1] = q1;
        a[2] = q2;
        a[3] = q3;
    }

    _AI AQuad operator* (const AQuad& x) const {
        AQuad z;

        for (int i = 0; i < 4; i++)
            z.a[i] = a[i] * x.a[i];

        return z;
    }
    _AI AQuad operator+ (const AQuad& x) const {
        AQuad z;

        for (int i = 0; i < 4; i++)
            z.a[i] = a[i] + x.a[i];

        return z;
    }
    _AI AQuad operator- (const AQuad& x) const {
        AQuad z;

        for (int i = 0; i < 4; i++)
            z.a[i] = a[i] - x.a[i];

        return z;
    }
    _AI AQuad operator- () const {
        AQuad z;

        for (int i = 0; i < 4; i++)
            z.a[i] = -a[i];

        return z;
    }

    _AI AQuad& operator*= (const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] *= x.a[i];

        return *this;
    }
    _AI AQuad& operator+= (const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] += x.a[i];

        return *this;
    }
    _AI AQuad& operator-= (const AQuad& x) {
        for (int i = 0; i < 4; i++)
            a[i] -= x.a[i];

        return *this;
    }

    _AI AQuad operator* (const AScalar& x) const {
        AQuad z;

        for (int i = 0; i < 4; i++)
            z.a[i] = a[i] * x.fr;

        return z;
    }
    _AI AQuad& operator*= (const AScalar& x) {
        for (int i = 0; i < 4; i++)
            a[i] *= x.fr;

        return *this;
    }

    _AI AQuad mul_add(const AQuad& x, const AQuad& y) const {
        AQuad z;
        for (int i = 0; i < 4; i++)
            z.a[i] = a[i] + x.a[i] * y.a[i];

        return z;
    }
    _AI AQuad mul_sub(const AQuad& x, const AQuad& y) const {
        AQuad z;
        for (int i = 0; i < 4; i++)
            z.a[i] = a[i] - x.a[i] * y.a[i];

        return z;
    }

    _AI AScalar q0() const {return a[0];}
    _AI AScalar q1() const {return a[1];}
    _AI AScalar q2() const {return a[2];}
    _AI AScalar q3() const {return a[3];}

    _AI AQuad& set_q0(const AScalar& x) {a[0] = x.fr; return *this;}
    _AI AQuad& set_q1(const AScalar& x) {a[1] = x.fr; return *this;}
    _AI AQuad& set_q2(const AScalar& x) {a[2] = x.fr; return *this;}
    _AI AQuad& set_q3(const AScalar& x) {a[3] = x.fr; return *this;}

    _AI AComplex h0() const {return AComplex(a[0], a[1]);}
    _AI AComplex h1() const {return AComplex(a[2], a[3]);}

    _AI AQuad& set_h0(const AComplex& x) {a[0] = x.r().fr; a[1] = x.i().fr; return *this;}
    _AI AQuad& set_h1(const AComplex& x) {a[2] = x.r().fr; a[3] = x.i().fr; return *this;}
};

_AI AQuad AScalar::operator* (const struct AQuad& x) const {
    AQuad z;
    for (int i = 0; i < 4; i++)
        z.a[i] = fr * x.a[i];

    return z;
}

//
// Pointer to AQuad
//

struct PQuad
{
    AQuad* ptr;

    _AI PQuad(void* p) : ptr((AQuad*) p) {}

    _AI PQuad& operator= (void* p) {ptr = (AQuad*) p; return *this;}

    _AI operator AQuad*() const {return ptr;}
    _AI AQuad* operator->() const {return ptr;}
    _AI AQuad& operator[] (int i) const {return ptr[i];}

    _AI PQuad  operator+ (int index) const {return PQuad(ptr + index);}
    _AI PQuad  operator- (int index) const {return PQuad(ptr - index);}

    _AI PQuad& operator+= (int index) {ptr += index; return *this;}
    _AI PQuad& operator-= (int index) {ptr -= index; return *this;}

    _AI PQuad& operator++ ()    {++ptr; return *this;}
    _AI PQuad& operator-- ()    {--ptr; return *this;}
    _AI PQuad  operator++ (int) {PQuad p(*this); ++ptr; return p;}
    _AI PQuad  operator-- (int) {PQuad p(*this); --ptr; return p;}
};

struct PConstQuad
{
    const AQuad* ptr;

    _AI PConstQuad(const void* p) : ptr((const AQuad*) p) {}

    _AI PConstQuad& operator= (void* p) {ptr = (const AQuad*) p; return *this;}

    _AI operator const AQuad*() const {return ptr;}
    _AI const AQuad* operator->() const {return ptr;}
    _AI const AQuad& operator[] (int i) const {return ptr[i];}

    _AI PConstQuad  operator+ (int index) const {return PConstQuad(ptr + index);}
    _AI PConstQuad  operator- (int index) const {return PConstQuad(ptr - index);}

    _AI PConstQuad& operator+= (int index) {ptr += index; return *this;}
    _AI PConstQuad& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstQuad& operator++ ()    {++ptr; return *this;}
    _AI PConstQuad& operator-- ()    {--ptr; return *this;}
    _AI PConstQuad  operator++ (int) {PConstQuad p(*this); ++ptr; return p;}
    _AI PConstQuad  operator-- (int) {PConstQuad p(*this); --ptr; return p;}
};

//
// Unaligned Quad Pointers
//

struct UnalignedQuadLoadPointer
{
    const AScalar* ptr;

    _AI UnalignedQuadLoadPointer(const void* p) : ptr((const AScalar*) p) {}

    _AI UnalignedQuadLoadPointer& operator= (const void* p) {
        ptr = (const AScalar*) p;
        return *this;
    }

    _AI operator PConstScalar() const {return PConstScalar(ptr);}
    _AI operator const AScalar*() const {return ptr;}
    _AI const AScalar& operator*() const {return *ptr;}
    _AI const AScalar* operator->() const {return ptr;}

    _AI AQuad load_post() {AQuad z = *(AQuad*) ptr; ptr += 4; return z;}
};

struct UnalignedQuadStorePointer
{
    AScalar* ptr;

    _AI UnalignedQuadStorePointer(void* p) : ptr((AScalar*) p) {}

    _AI void flush() {}

    _AI UnalignedQuadStorePointer& operator= (void* p) {
        ptr = (AScalar*) p;
        return *this;
    }

    _AI operator PScalar() const {return PScalar(ptr);}
    _AI operator AScalar*() const {return ptr;}
    _AI AScalar& operator*() const {return *ptr;}
    _AI AScalar* operator->() const {return ptr;}

    _AI void store_post(const AQuad& a) {*(AQuad*) ptr = a; ptr += 4;}
};

#endif

/** \class AQuad
    \brief Wrapper for a vr128, two vr64s, or float[4]

    \fn AQuad::AQuad(const AQuad& x)
    \brief Copy constructor

    \fn static int AQuad::length()
    \brief Returns 4

    \fn static AQuad AQuad::Zero()
    \brief Returns an AQuad filled with 0.0

    \fn AQuad& AQuad::fill(const AScalar& x)
    \brief Fills four elements with x

    \fn AQuad& AQuad::copy(const AQuad& x)
    \brief Copies four elements from the elements of x

    \fn AQuad& AQuad::add(const AQuad& x)
    \brief Returns *this += x elementwise

    \fn AQuad& AQuad::sub(const AQuad& x)
    \brief Returns *this += x elementwise

    \fn AQuad& AQuad::mul(const AQuad& x)
    \brief Returns *this *= x elementwise

    \fn AQuad& AQuad::div(const AQuad& x)
    \brief Returns *this /= x elementwise

    \fn AQuad& AQuad::mul_acc(const AQuad& x, const AQuad& y)
    \brief Returns *this += x * y elementwise

    \fn AQuad& AQuad::mul_acc(const AQuad& x, const AScalar& y)
    \brief Returns *this += x * y elementwise

    \fn AQuad& AQuad::add(const AScalar& x)
    \brief Adds x to each element

    \fn AQuad& AQuad::sub(const AScalar& x)
    \brief Subtracts x from each element

    \fn AQuad& AQuad::mul(const AScalar& x)
    \brief Multiplies each element by x

    \fn AQuad& AQuad::div(const AScalar& x)
    \brief Divides each element by x

    \fn AQuad& AQuad::abs()
    \brief Replaces each element by its absolute value

    \fn AQuad& AQuad::max(const AQuad& x)
    \brief Returns *this = max(*this, x) elementwise

    \fn AQuad& AQuad::min(const AQuad& x)
    \brief Returns *this = min(*this, x) elementwise

    \fn AQuad& AQuad::clamp(const AScalar& low, const AScalar& high)
    \brief Returns *this = max(min(*this, high), low) elementwise

    \fn AScalar AQuad::sum()
    \brief Returns the sum of the elements

    \fn AScalar AQuad::sum_sq()
    \brief Returns the sum of the squares of the elements

    \fn AQuad AQuad::dot(const AQuad& x)
    \brief Returns the inner product with x

    \fn AScalar AQuad::max_abs()
    \brief Returns the maximum absolute value of the elements

    \fn AScalar AQuad::norm()
    \brief Returns the Euclidean norm of the 4-element vector

    \fn AScalar AQuad::normalize()
    \brief Normalizes the 4-element vector

    \fn AQuad::AQuad(const AScalar& q0, const AScalar& q1, const AScalar& q2, const AScalar& q3)
    \brief Construct from four AScalars

    \fn AQuad::AQuad(float q0, float q1, float q2, float q3)
    \brief Construct from four floats

    \fn AQuad AQuad::mul_add(const AQuad& x, const AQuad& y)
    \brief Returns *this + x * y

    \fn AQuad AQuad::mul_sub(const AQuad& x, const AQuad& y)
    \brief Returns *this - x * y

    \fn AScalar AQuad::q0()
    \brief Returns first element

    \fn AScalar AQuad::q1()
    \brief Returns second element

    \fn AScalar AQuad::q2()
    \brief Returns third element

    \fn AScalar AQuad::q3()
    \brief Returns fourth element

    \fn AQuad& AQuad::set_q0(const AScalar& a)
    \brief Sets first element

    \fn AQuad& AQuad::set_q1(const AScalar& a)
    \brief Sets second element

    \fn AQuad& AQuad::set_q2(const AScalar& a)
    \brief Sets third element

    \fn AQuad& AQuad::set_q3(const AScalar& a)
    \brief Sets fourth element

    \fn AComplex AQuad::h0()
    \brief Returns first half

    \fn AComplex AQuad::h1()
    \brief Returns second half

    \fn AQuad& AQuad::set_h0(const AComplex& a)
    \brief Sets first half

    \fn AQuad& AQuad::set_h1(const AComplex& a)
    \brief Sets second half
*/

/** \class PQuad
    \brief Abstract pointer to an AQuad

    \fn PQuad::PQuad(void* p)
    \brief Constructor

    \fn AQuad* PQuad::operator->()
    \brief Dereference

    \fn AQuad& PQuad::operator[] (int i)
    \brief Array reference
*/

/** \class PConstQuad
    \brief Abstract pointer to a const AQuad

    \fn PConstQuad::PConstQuad(const void* p)
    \brief Constructor

    \fn const AQuad* PQuad::operator->()
    \brief Dereference

    \fn const AQuad& PConstQuad::operator[] (int i)
    \brief Array reference
*/

/** \class UnalignedQuadLoadPointer
    \brief Abstract pointer to an AQuad requiring only 4-byte alignment

    \fn UnalignedQuadLoadPointer::UnalignedQuadLoadPointer(const void* p)
    \brief Constructor

    \fn AQuad UnalignedQuadLoadPointer::load_post()
    \brief Read an AQuad requiring only 4-byte alignment
*/

/** \class UnalignedQuadStorePointer
    \brief Abstract pointer to an AQuad requiring only 4-byte alignment

    \fn UnalignedQuadStorePointer::UnalignedQuadStorePointer(void* p)
    \brief Constructor

    \fn void UnalignedQuadStorePointer::store_post(const AQuad& a)
    \brief Write an AQuad requiring only 4-byte alignment

    \fn void UnalignedQuadStorePointer::flush()
    \brief Call flush() after one or more store_post() calls to complete the write
*/
