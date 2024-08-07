/************************************************************************//**
 * @file    AVL/DMX1A/AQuad.h
 *
 * @brief   AQuad wrapper for vr128 on DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef AQUAD_H
#define AQUAD_H

/**************************************************************************//**
 * @addtogroup dmx1a_avl
 * @{
 *****************************************************************************/

#include "AComplex.h"

struct AQuad
{
    vr128 vr;

    _AI AQuad() {}
    _AI AQuad(const AQuad& x) : vr(x.vr) {}
    _AI AQuad& operator= (const AQuad& x) {vr = x.vr; return *this;}

    _AI static int length() {return 4;}
    _AI static AQuad Zero() {return vseta_vr(0, 0, 0);}

    _AI const AScalar operator[] (int i) const {return move32_fr_vr_idx(vr, i);}

    _AI xtbool operator== (const AQuad& x) const {return XT_ALL4(veq(vr, x.vr));}
    _AI xtbool operator!= (const AQuad& x) const {return XT_ANY4(vne(vr, x.vr));}

    _AI AQuad& fill(const AScalar& x) {vr = vreplicate_fr(x.fr); return *this;}
    _AI AQuad& copy(const AQuad& x)   {vr = x.vr;                return *this;}

    _AI AQuad& add(const AQuad& x) {vr = vadds(vr, x.vr, 0);    return *this;}
    _AI AQuad& sub(const AQuad& x) {vr = vadds(vr, x.vr, 0xf0); return *this;}
    _AI AQuad& mul(const AQuad& x) {vr = vmuls(vr, x.vr, 0);    return *this;}
    _AI AQuad& div(const AQuad& x) {
        // One iteration of Newton's method
        vr128 V_2 = vseta_vr(2, 0, 0);
        vr128 V_inv=vseta_vr(0,0,0);
        vr128 V_dst;
        inv(V_inv, VRQ0, x.vr, VRQ0);
        inv(V_inv, VRQ1, x.vr, VRQ1);
        inv(V_inv, VRQ2, x.vr, VRQ2);
        inv(V_inv, VRQ3, x.vr, VRQ3);
        V_dst = vmuls(V_inv, vmacs_adj(V_2, V_inv, x.vr, 15, 0), 0);
        vr = vmuls(vr, V_dst, 0);
        return *this;
    }

    _AI AQuad& mul_acc(const AQuad& x, const AQuad& y) {
        vr = vmacs_adj(vr, x.vr, y.vr, 0, 0);
        return *this;
    }
    _AI AQuad& mul_acc(const AQuad& x, const AScalar& y) {
        vr = vmacs_adj(vr, x.vr, vreplicate_fr(y.fr), 0, 0);
        return *this;
    }

    _AI AQuad& add(const AScalar& x) {
        vr = vadds(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }
    _AI AQuad& sub(const AScalar& x) {
        vr = vadds(vr, vreplicate_fr(x.fr), 0xf0);
        return *this;
    }
    _AI AQuad& mul(const AScalar& x) {
        vr = vmuls(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }
    _AI AQuad& div(const AScalar& x) {
        return mul(x.inverse());
    }

    _AI AQuad& abs()               {vr = vabs(vr);       return *this;}
    _AI AQuad& max(const AQuad& x) {vr = vmax(vr, x.vr); return *this;}
    _AI AQuad& min(const AQuad& x) {vr = vmin(vr, x.vr); return *this;}

    _AI AQuad& clamp(const AScalar& low, const AScalar& high) {
        vr128 V_low = vreplicate_fr(low.fr);
        vr128 V_high= vreplicate_fr(high.fr);
        vr = vmin(vmax(vr, V_low), V_high);
        return *this;
    }

    _AI AScalar sum() const {
        vr128 V_dst=vseta_vr(0,0,0);
        dsums_L(V_dst, vr, 0, 0);
        dsums_L(V_dst, V_dst, 0, 0);
        return get_VRQ0(V_dst);
    }

    _AI AScalar dot(const AQuad& x) const {
        vr128 V_dst=vseta_vr(0,0,0);
        fmul_sum3(V_dst, VRQ0, vr, x.vr, 0, set_perm16(0x05af));
        return get_VRQ0(vmacs_adj(V_dst, vr, x.vr, 0, 0));
    }

    _AI AScalar max_abs() const {
        vr128 V_dst=vseta_vr(0,0,0);
        unsigned int ar;
        mir30 mir;
        vmaxmin_init(V_dst,V_dst,mir);
        rmax_idx(ar, V_dst, VRQ0, vabs(vr), mir);
	ar = ar + 1; // Temporary fix for 'unused-but-set-variable' warning
        return get_VRQ0(V_dst);
    }

    _AI AScalar sum_sq() const {return dot(*this);}
    _AI AScalar norm()   const {return sum_sq().f_sqrt();}
    _AI AQuad&  normalize()    {return mul(sum_sq().f_invsqrt());}

    //
    // Additional methods not in AVector<N>
    //

    _AI AQuad(const vr128& a) : vr(a) {}
    _AI AQuad(const AScalar& q0, const AScalar& q1, const AScalar& q2, const AScalar& q3) {
        vr = vr128_quad(q3.fr, q2.fr, q1.fr, q0.fr);
    }
    _AI AQuad(float q0, float q1, float q2, float q3) {
        replicate_ar(vr, 1, *(int*) &q0);
        replicate_ar(vr, 2, *(int*) &q1);
        replicate_ar(vr, 4, *(int*) &q2);
        replicate_ar(vr, 8, *(int*) &q3);
        convert_IEEE_float_to_32F_x4(vr);
    }
    _AI operator vr128() const {return vr;}
    _AI AQuad& operator= (const vr128& a) {vr = a; return *this;}

    _AI AQuad operator* (const AQuad& x) const {return vmuls(vr, x.vr, 0);}
    _AI AQuad operator+ (const AQuad& x) const {return vadds(vr, x.vr, 0);}
    _AI AQuad operator- (const AQuad& x) const {return vadds(vr, x.vr, 0xf0);}
    _AI AQuad operator- ()               const {return s_vnegs(vr, 0xf);}

    _AI AQuad& operator*= (const AQuad& x) {vr = vmuls(vr, x.vr, 0);    return *this;}
    _AI AQuad& operator+= (const AQuad& x) {vr = vadds(vr, x.vr, 0);    return *this;}
    _AI AQuad& operator-= (const AQuad& x) {vr = vadds(vr, x.vr, 0xf0); return *this;}

    _AI AQuad operator* (const AScalar& x) const {return vmuls(vr, vreplicate_fr(x.fr), 0);}

    _AI AQuad& operator*= (const AScalar& x) {
        vr = vmuls(vr, vreplicate_fr(x.fr), 0);
        return *this;
    }

    _AI AQuad mul_add(const AQuad& x, const AQuad& y) const {
        return vmacs_adj(vr, x.vr, y.vr,  0, 0);
    }
    _AI AQuad mul_sub(const AQuad& x, const AQuad& y) const {
        return vmacs_adj(vr, x.vr, y.vr, 15, 0);
    }

    _AI AScalar q0() const {return get_VRQ0(vr);}
    _AI AScalar q1() const {return get_VRQ1(vr);}
    _AI AScalar q2() const {return get_VRQ2(vr);}
    _AI AScalar q3() const {return get_VRQ3(vr);}

    _AI AQuad& set_q0(const AScalar& a) {set_VRQ0(vr, a.fr); return *this;}
    _AI AQuad& set_q1(const AScalar& a) {set_VRQ1(vr, a.fr); return *this;}
    _AI AQuad& set_q2(const AScalar& a) {set_VRQ2(vr, a.fr); return *this;}
    _AI AQuad& set_q3(const AScalar& a) {set_VRQ3(vr, a.fr); return *this;}

    _AI AComplex h0() const {return get_VRL(vr);}
    _AI AComplex h1() const {return get_VRH(vr);}

    _AI AQuad& set_h0(const AComplex& a) {set_VRL(vr, a.vr); return *this;}
    _AI AQuad& set_h1(const AComplex& a) {set_VRH(vr, a.vr); return *this;}
};

_AI AQuad AScalar::operator* (const struct AQuad& x) const {
    return vmuls(x.vr, vreplicate_fr(fr), 0);
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
    ulsr128 ur;

    _AI UnalignedQuadLoadPointer(const void* p) : ptr((const AScalar*) p) {
        ur = align_32x4_load(ptr);
    }

    _AI UnalignedQuadLoadPointer& operator= (const void* p) {
        ptr = (const AScalar*) p;
        ur = align_32x4_load(ptr);
        return *this;
    }

    _AI operator PConstScalar() const {return PConstScalar(ptr);}
    _AI operator const AScalar*() const {return ptr;}
    _AI const AScalar& operator*() const {return *ptr;}
    _AI const AScalar* operator->() const {return ptr;}

    _AI AQuad load_post() {
        vr128 v;
        load_32x4_vr_a(v, ur, ptr);
        return v;
    }
};

struct UnalignedQuadStorePointer
{
    AScalar* ptr;
    ulsr128 ur;

    _AI UnalignedQuadStorePointer(void* p) : ptr((AScalar*) p) {
        ur = align_32x4_store(ptr);
    }

    _AI void flush() {
        flush_32x4(ur, ptr);
    }

    _AI UnalignedQuadStorePointer& operator= (void* p) {
        ptr = (AScalar*) p;
        ur = align_32x4_store(ptr);
        return *this;
    }

    _AI operator PScalar() const {return PScalar(ptr);}
    _AI operator AScalar*() const {return ptr;}
    _AI AScalar& operator*() const {return *ptr;}
    _AI AScalar* operator->() const {return ptr;}

    _AI void store_post(const AQuad& q) {
        store_32x4_vr_a(q.vr, ur, ptr);
    }
};

/**************************************************************************//**
 * @}
 *****************************************************************************/

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
