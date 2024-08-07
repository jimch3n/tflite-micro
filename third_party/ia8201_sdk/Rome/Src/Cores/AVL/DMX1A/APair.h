/************************************************************************//**
 * @file    AVL/DMX1A/APair.h
 *
 * @brief   APair wrapper for vr64 on DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef APAIR_H
#define APAIR_H

/**************************************************************************//**
 * @addtogroup dmx1a_avl
 * @{
 *****************************************************************************/

#include "AScalar.h"

struct APair
{
    vr64 vr;

    _AI APair() {}
    _AI APair(const APair& x) : vr(x.vr) {}

    _AI static int length() {return 2;}
    _AI static APair Zero() {return get_VRL(vseta_vr(0, 0, 0));}

    _AI const AScalar operator[] (int i) const {
        return move32_fr_vr_idx(vreplicate_hr(vr), i);
    }

    static const int PAD_MASK = 12;

    _AI xtbool operator== (const APair& x) const {
        return andb1(eq_fr(get_HRL(vr), get_HRL(x.vr)),
                     eq_fr(get_HRH(vr), get_HRH(x.vr)));
    }
    _AI xtbool operator!= (const APair& x) const {
        return orb1(ne_fr(get_HRL(vr), get_HRL(x.vr)),
                    ne_fr(get_HRH(vr), get_HRH(x.vr)));
    }

    _AI APair& fill(const AScalar& x) {vr = hreplicate_fr(x.fr); return *this;}
    _AI APair& copy(const APair& x)   {vr = x.vr;                return *this;}

    _AI APair& add(const APair& x) {vr = vadd_hr(vr, x.vr); return *this;}
    _AI APair& sub(const APair& x) {vr = vsub_hr(vr, x.vr); return *this;}
    _AI APair& mul(const APair& x) {vr = vmul_hr(vr, x.vr); return *this;}
    _AI APair& div(const APair& x) {
        // One iteration of Newton's method
        vr128 V_2 = vseta_vr(2, 0, 0);
        vr128 V_x=vseta_vr(0,0,0);
        vr128 V_inv=V_x;
        vr128 V_dst;
        set_VRL(V_x, x.vr);
        inv(V_inv, VRQ0, V_x, VRQ0);
        inv(V_inv, VRQ1, V_x, VRQ1);
        V_dst = vmuls(V_inv, vmacs_adj(V_2, V_inv, V_x, 15, 0), 0);
        vr = vmul_hr(vr, get_VRL(V_dst));
        return *this;
    }

    _AI APair& mul_acc(const APair& x, const APair& y) {
        vr = vmac_hr(vr, x.vr, y.vr);
        return *this;
    }
    _AI APair& mul_acc(const APair& x, const AScalar& y) {
        vr = vmac_hr(vr, x.vr, hreplicate_fr(y.fr));
        return *this;
    }

    _AI APair& add(const AScalar& x) {
        vr = vadd_hr(vr, hreplicate_fr(x.fr));
        return *this;
    }
    _AI APair& sub(const AScalar& x) {
        vr = vsub_hr(vr, hreplicate_fr(x.fr));
        return *this;
    }
    _AI APair& mul(const AScalar& x) {
        vr = vmul_hr(vr, hreplicate_fr(x.fr));
        return *this;
    }
    _AI APair& div(const AScalar& x) {
        return mul(x.inverse());
    }

    _AI APair& abs() {
        vr = get_VRL(vabs(vreplicate_hr(vr)));
        return *this;
    }
    _AI APair& max(const APair& x) {
        vr = get_VRL(vmax(vreplicate_hr(vr), vreplicate_hr(x.vr)));
        return *this;
    }
    _AI APair& min(const APair& x) {
        vr = get_VRL(vmin(vreplicate_hr(vr), vreplicate_hr(x.vr)));
        return *this;
    }

    _AI APair& clamp(const AScalar& low, const AScalar& high) {
        vr128 V_low = vreplicate_fr(low.fr);
        vr128 V_high= vreplicate_fr(high.fr);
        vr = get_VRL(vmin(vmax(vreplicate_hr(vr), V_low), V_high));
        return *this;
    }

    _AI AScalar sum() const {
        return fpadd(get_HRH(vr), get_HRL(vr), 0);
    }

    _AI AScalar dot(const APair& x) const {
        return get_HRL(cmul_conj(vr, x.vr));
    }

    _AI AScalar max_abs() const {
        vr128 V_dst = vabs(vreplicate_hr(vr));
        unsigned int ar;
        mir30 mir;
        vmaxmin_init(V_dst,V_dst,mir);
        seta_vr(V_dst, PAD_MASK, 0, 0, 0);
        rmax_idx(ar, V_dst, VRQ0, V_dst, mir);
	ar = ar + 1; // Temporary fix for 'unused-but-set-variable' warning
        return get_VRQ0(V_dst);
    }

    _AI AScalar sum_sq() const {return dot(*this);}
    _AI AScalar norm()   const {return sum_sq().f_sqrt();}
    _AI APair& normalize()     {return mul(sum_sq().f_invsqrt());}

    //
    // Additional methods not in AVector<N>
    //

    _AI APair(const vr64& a) : vr(a) {}
    _AI APair(const AScalar& h0, const AScalar& h1) : vr(vr64_pair(h1.fr, h0.fr)) {}
    _AI APair(float h0, float h1) {
        vr = vr64_pair(convert_IEEE_float_to_32F(*(int*) &h1),
                       convert_IEEE_float_to_32F(*(int*) &h0));
    }

    _AI operator vr64() const {return vr;}

    _AI APair operator* (const APair& x) const {return vmul_hr(vr, x.vr);}
    _AI APair operator+ (const APair& x) const {return vadd_hr(vr, x.vr);}
    _AI APair operator- (const APair& x) const {return vsub_hr(vr, x.vr);}
    _AI APair operator- ()               const {return s_vnegs_hr(vr, 3);}

    _AI APair& operator*= (const APair& x) {vr = vmul_hr(vr, x.vr); return *this;}
    _AI APair& operator+= (const APair& x) {vr = vadd_hr(vr, x.vr); return *this;}
    _AI APair& operator-= (const APair& x) {vr = vsub_hr(vr, x.vr); return *this;}

    _AI APair operator* (const AScalar& x) const {
        return vmul_hr(vr, hreplicate_fr(x.fr));
    }
    _AI APair& operator*= (const AScalar& x) {
        vr = vmul_hr(vr, hreplicate_fr(x.fr));
        return *this;
    }

    _AI APair mul_add(const APair& x, const APair& y) const {
        return vmac_hr(vr, x.vr, y.vr);
    }
    _AI APair mul_sub(const APair& x, const APair& y) const {
        return vmac_hr(vr, x.vr, s_vnegs_hr(y.vr, 3));
    }

    _AI AScalar h0() const {return get_HRL(vr);}
    _AI AScalar h1() const {return get_HRH(vr);}

    _AI APair& set_h0(const AScalar& a) {set_HRL(vr, a.fr); return *this;}
    _AI APair& set_h1(const AScalar& a) {set_HRH(vr, a.fr); return *this;}
};

_AI APair AScalar::operator* (const struct APair& x) const {
    return vmul_hr(x.vr, hreplicate_fr(fr));
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

    _AI operator const APair*() const {return ptr;}
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

    _AI operator PConstScalar() const {return PConstScalar(ptr);}
    _AI operator const AScalar*() const {return ptr;}
    _AI const AScalar& operator*() const {return *ptr;}
    _AI const AScalar* operator->() const {return ptr;}

    _AI APair load_post() {
        vr128 v=vseta_vr(0,0,0);
        load32x1_vr_postI(v, ptr, INC1, VRQ0);
        load32x1_vr_postI(v, ptr, INC1, VRQ1);
        return get_VRL(v);
    }
};

struct UnalignedPairStorePointer
{
    fr32* ptr;

    _AI UnalignedPairStorePointer(void* p) : ptr((fr32*) p) {}

    _AI void flush() {}

    _AI operator PScalar() const {return PScalar(ptr);}
    _AI operator AScalar*() const {return (AScalar*) ptr;}
    _AI AScalar& operator*() const {return *(AScalar*) ptr;}
    _AI AScalar* operator->() const {return (AScalar*) ptr;}

    _AI void store_post(const APair& q) {
        fr32_storeip(get_HRL(q.vr), ptr, 4);
        fr32_storeip(get_HRH(q.vr), ptr, 4);
    }
};

/**************************************************************************//**
 * @}
 *****************************************************************************/

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
