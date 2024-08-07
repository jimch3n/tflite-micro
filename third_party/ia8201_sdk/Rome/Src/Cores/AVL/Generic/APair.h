///////////////////////////////////////////////////////////////////////////////
///
/// \file APair.h
///
/// APair wrapper for float[2]
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef APAIR_H
#define APAIR_H

#include "AScalar.h"

struct APair
{
    float vr[2];

    _AI APair() {}
    _AI APair(const APair& x) {copy(x);}

    _AI static int length() {return 2;}
    _AI static APair Zero() {return APair(0, 0);}

    _AI const AScalar operator[] (int i) const {return vr[i];}

    _AI bool operator== (const APair& x) const {
        return vr[0] == x.vr[0] && vr[1] == x.vr[1];
    }
    _AI bool operator!= (const APair& x) const {
        return vr[0] != x.vr[0] || vr[1] != x.vr[1];
    }

    _AI APair& fill(const AScalar& x) {vr[0] = vr[1] = x.fr;             return *this;}
    _AI APair& copy(const APair& x)   {vr[0] = x.vr[0]; vr[1] = x.vr[1]; return *this;}

    _AI APair& add(const APair& x) {vr[0] += x.vr[0]; vr[1] += x.vr[1]; return *this;}
    _AI APair& sub(const APair& x) {vr[0] -= x.vr[0]; vr[1] -= x.vr[1]; return *this;}
    _AI APair& mul(const APair& x) {vr[0] *= x.vr[0]; vr[1] *= x.vr[1]; return *this;}
    _AI APair& div(const APair& x) {vr[0] /= x.vr[0]; vr[1] /= x.vr[1]; return *this;}

    _AI APair& mul_acc(const APair& x, const APair& y) {
        vr[0] += x.vr[0] * y.vr[0];
        vr[1] += x.vr[1] * y.vr[1];
        return *this;
    }
    _AI APair& mul_acc(const APair& x, const AScalar& y) {
        vr[0] += x.vr[0] * y.fr;
        vr[1] += x.vr[1] * y.fr;
        return *this;
    }

    _AI APair& add(const AScalar& x) {vr[0] += x.fr; vr[1] += x.fr; return *this;}
    _AI APair& sub(const AScalar& x) {vr[0] -= x.fr; vr[1] -= x.fr; return *this;}
    _AI APair& mul(const AScalar& x) {vr[0] *= x.fr; vr[1] *= x.fr; return *this;}
    _AI APair& div(const AScalar& x) {vr[0] /= x.fr; vr[1] /= x.fr; return *this;}

    _AI APair& abs() {
        vr[0] = fabsf(vr[0]);
        vr[1] = fabsf(vr[1]);
        return *this;
    }
    _AI APair& max(const APair& x) {
        vr[0] = fmaxf(vr[0], x.vr[0]);
        vr[1] = fmaxf(vr[1], x.vr[1]);
        return *this;}
    _AI APair& min(const APair& x) {
        vr[0] = fminf(vr[0], x.vr[0]);
        vr[1] = fminf(vr[1], x.vr[1]);
        return *this;
    }
    _AI APair& clamp(const AScalar& low, const AScalar& high) {
        vr[0] = fminf(fmaxf(vr[0], low.fr), high.fr);
        vr[1] = fminf(fmaxf(vr[1], low.fr), high.fr);
        return *this;
    }

    _AI AScalar sum()               const {return vr[0] + vr[1];}
    _AI AScalar sum_sq()            const {return vr[0] * vr[0] + vr[1] * vr[1];}
    _AI AScalar dot(const APair& x) const {return vr[0] * x.vr[0] + vr[1] * x.vr[1];}
    _AI AScalar max_abs()           const {return fmaxf(fabsf(vr[0]), fabsf(vr[1]));}
    _AI AScalar norm()              const {return sum_sq().f_sqrt();}

    _AI APair& normalize() {return mul(sum_sq().f_invsqrt());}

    //
    // Additional methods not in AVector<N>
    //

    _AI APair(float a[2]) {vr[0] = a[0]; vr[1] = a[1];}
    _AI APair(const AScalar& h0, const AScalar& h1) {vr[0] = h0.fr; vr[1] = h1.fr;}
    _AI APair(float h0, float h1) {vr[0] = h0; vr[1] = h1;}

    _AI APair operator* (const APair& x) const {
        return APair(vr[0] * x.vr[0], vr[1] * x.vr[1]);
    }
    _AI APair operator+ (const APair& x) const {
        return APair(vr[0] + x.vr[0], vr[1] + x.vr[1]);
    }
    _AI APair operator- (const APair& x) const {
        return APair(vr[0] - x.vr[0], vr[1] - x.vr[1]);
    }
    _AI APair operator- () const {
        return APair(-vr[0], -vr[1]);
    }

    _AI APair& operator*= (const APair& x) {mul(x); return *this;}
    _AI APair& operator+= (const APair& x) {add(x); return *this;}
    _AI APair& operator-= (const APair& x) {sub(x); return *this;}

    _AI APair operator* (const AScalar& x) const {
        return APair(vr[0] * x.fr, vr[1] * x.fr);
    }

    _AI APair& operator*= (const AScalar& x) {mul(x); return *this;}

    _AI APair mul_add(const APair& x, const APair& y) const {
        return APair(vr[0] + x.vr[0] * y.vr[0], vr[1] + x.vr[1] * y.vr[1]);
    }
    _AI APair mul_sub(const APair& x, const APair& y) const {
        return APair(vr[0] - x.vr[0] * y.vr[0], vr[1] - x.vr[1] * y.vr[1]);
    }

    _AI AScalar h0() const {return vr[0];}
    _AI AScalar h1() const {return vr[1];}

    _AI APair& set_h0(const AScalar& a) {vr[0] = a.fr; return *this;}
    _AI APair& set_h1(const AScalar& a) {vr[1] = a.fr; return *this;}
};

_AI APair AScalar::operator* (const struct APair& x) const {
    return APair(fr * x.vr[0], fr * x.vr[1]);
}

//
// Pointer to APair
//

struct PPair
{
    APair* ptr;

    _AI PPair(void* p) : ptr((APair*) p) {}

    _AI operator APair*() const {return ptr;}
    _AI APair* operator->() const {return ptr;}
    _AI APair& operator[] (int i) const {return ptr[i];}

    _AI PPair  operator+ (int index) const {return PPair(ptr + index);}
    _AI PPair  operator- (int index) const {return PPair(ptr - index);}

    _AI PPair& operator+= (int index) {ptr += index; return *this;}
    _AI PPair& operator-= (int index) {ptr -= index; return *this;}

    _AI PPair& operator++ ()    {++ptr; return *this;}
    _AI PPair& operator-- ()    {--ptr; return *this;}
    _AI PPair  operator++ (int) {PPair p(*this); ++ptr; return p;}
    _AI PPair  operator-- (int) {PPair p(*this); --ptr; return p;}
};

struct PConstPair
{
    const APair* ptr;

    _AI PConstPair(const void* p) : ptr((const APair*) p) {}

    _AI operator const APair*() const {return  ptr;}
    _AI const APair* operator->() const {return ptr;}
    _AI const APair& operator[] (int i) const {return ptr[i];}

    _AI PConstPair  operator+ (int index) const {return PConstPair(ptr + index);}
    _AI PConstPair  operator- (int index) const {return PConstPair(ptr - index);}

    _AI PConstPair& operator+= (int index) {ptr += index; return *this;}
    _AI PConstPair& operator-= (int index) {ptr -= index; return *this;}

    _AI PConstPair& operator++ ()    {++ptr; return *this;}
    _AI PConstPair& operator-- ()    {--ptr; return *this;}
    _AI PConstPair  operator++ (int) {PConstPair p(*this); ++ptr; return p;}
    _AI PConstPair  operator-- (int) {PConstPair p(*this); --ptr; return p;}
};

//
// Unaligned Pair Pointers
//

struct UnalignedPairLoadPointer
{
    const AScalar* ptr;

    _AI UnalignedPairLoadPointer(const void* p) : ptr((const AScalar*) p) {}

    _AI operator const AScalar*() const {return (const AScalar*) ptr;}
    _AI const AScalar& operator*() const {return *ptr;}
    _AI const AScalar* operator->() const {return ptr;}

    _AI APair load_post() {APair z = *(APair*) ptr; ptr += 2; return z;}
};

struct UnalignedPairStorePointer
{
    AScalar* ptr;

    _AI UnalignedPairStorePointer(void* p) : ptr((AScalar*) p) {}

    _AI void flush() {}

    _AI operator AScalar*() const {return (AScalar*) ptr;}
    _AI AScalar& operator*() const {return *ptr;}
    _AI AScalar* operator->() const {return ptr;}

    _AI void store_post(const APair& a) {*(APair*) ptr = a; ptr += 2;}
};

#endif

/** \class APair
    \brief Wrapper for a vr64, vr128, or float[2]

    \fn APair::APair(const APair& x)
    \brief Copy constructor

    \fn static int APair::length()
    \brief Returns 2

    \fn static APair APair::Zero()
    \brief Returns an APair filled with 0.0

    \fn APair& APair::fill(const AScalar& x)
    \brief Fills both elements with x

    \fn APair& APair::copy(const APair& x)
    \brief Copies both elements from the elements of x

    \fn APair& APair::add(const APair& x)
    \brief Returns *this += x elementwise

    \fn APair& APair::sub(const APair& x)
    \brief Returns *this += x elementwise

    \fn APair& APair::mul(const APair& x)
    \brief Returns *this *= x elementwise

    \fn APair& APair::div(const APair& x)
    \brief Returns *this /= x elementwise

    \fn APair& APair::mul_acc(const APair& x, const APair& y)
    \brief Returns *this += x * y elementwise

    \fn APair& APair::mul_acc(const APair& x, const AScalar& y)
    \brief Returns *this += x * y elementwise

    \fn APair& APair::add(const AScalar& x)
    \brief Adds x to each element

    \fn APair& APair::sub(const AScalar& x)
    \brief Subtracts x from each element

    \fn APair& APair::mul(const AScalar& x)
    \brief Multiplies each element by x

    \fn APair& APair::div(const AScalar& x)
    \brief Divides each element by x

    \fn APair& APair::abs()
    \brief Replaces each element by its absolute value

    \fn APair& APair::min(const APair& x)
    \brief Returns *this = min(*this, x) elementwise

    \fn APair& APair::max(const APair& x)
    \brief Returns *this = max(*this, x) elementwise

    \fn APair& APair::clamp(const AScalar& low, const AScalar& high)
    \brief Returns *this = max(min(*this, high), low) elementwise

    \fn AScalar APair::sum()
    \brief Returns the sum of the elements

    \fn AScalar APair::sum_sq()
    \brief Returns the sum of the squares of the elements

    \fn APair APair::dot(const APair& x)
    \brief Returns the inner product with x

    \fn AScalar APair::max_abs()
    \brief Returns the maximum absolute value of the elements

    \fn AScalar APair::norm()
    \brief Returns the Euclidean norm of the 2-element vector

    \fn AScalar APair::normalize()
    \brief Normalizes the 2-element vector

    \fn APair::APair(const AScalar& h0, const AScalar& h1)
    \brief Construct from two AScalars

    \fn APair::APair(float h0, float h1)
    \brief Construct from two floats

    \fn APair APair::mul_add(const APair& x, const APair& y)
    \brief Returns *this + x * y

    \fn APair APair::mul_sub(const APair& x, const APair& y)
    \brief Returns *this - x * y

    \fn AScalar APair::h0()
    \brief Returns first element

    \fn AScalar APair::h1()
    \brief Returns second element

    \fn APair& APair::set_h0(const AScalar& a)
    \brief Sets first element

    \fn APair& APair::set_h1(const AScalar& a)
    \brief Sets second element
*/

/** \class PPair
    \brief Abstract pointer to an APair

    \fn PPair::PPair(void* p)
    \brief Constructor

    \fn APair* PPair::operator->()
    \brief Dereference

    \fn APair& PPair::operator[] (int i)
    \brief Array reference
*/

/** \class PConstPair
    \brief Abstract pointer to a const APair

    \fn PConstPair::PConstPair(const void* p)
    \brief Constructor

    \fn const APair* PPair::operator->()
    \brief Dereference

    \fn const APair& PConstPair::operator[] (int i)
    \brief Array reference
*/

/** \class UnalignedPairLoadPointer
    \brief Abstract pointer to an APair requiring only 4-byte alignment

    \fn UnalignedPairLoadPointer::UnalignedPairLoadPointer(const void* p)
    \brief Constructor

    \fn APair UnalignedPairLoadPointer::load_post()
    \brief Read an APair requiring only 4-byte alignment
*/

/** \class UnalignedPairStorePointer
    \brief Abstract pointer to an APair requiring only 4-byte alignment

    \fn UnalignedPairStorePointer::UnalignedPairStorePointer(void* p)
    \brief Constructor

    \fn void UnalignedPairStorePointer::store_post(const APair& a)
    \brief Write an APair requiring only 4-byte alignment

    \fn void UnalignedPairStorePointer::flush()
    \brief Call flush() after one or more store_post() calls to complete the write
*/
