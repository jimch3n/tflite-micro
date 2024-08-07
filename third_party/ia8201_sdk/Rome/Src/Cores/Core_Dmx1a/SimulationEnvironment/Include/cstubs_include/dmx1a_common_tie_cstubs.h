// Machine generated file - DO NOT EDIT!

/*
 * Customer ID=11582; Build=0x766de; Copyright (c) 2006-2010 by Tensilica Inc.  ALL RIGHTS RESERVED.
 * These coded instructions, statements, and computer programs are the.
 * copyrighted works and confidential proprietary information of Tensilica Inc..
 * They may not be modified, copied, reproduced, distributed, or disclosed to.
 * third parties in any manner, medium, or form, in whole or in part, without.
 * the prior written consent of Tensilica Inc..
 */

/* Do not modify. This is automatically generated.*/

#ifndef CSTUB_Xm_dmx1a_HEADER
#define CSTUB_Xm_dmx1a_HEADER

#include <string.h>
#include "cstub-extif.h"

/* Cstub definitions */

#if defined(__GNUC__)
#define CSTUB_MSC_ALIGN(x) 
#define CSTUB_GCC_ALIGN(x) __attribute__((aligned(x))) 
#define CSTUB_EXPLICIT explicit
#define CSTUB_MAY_ALIAS __attribute__((__may_alias__)) 
#define CSTUB_EXTERN extern
#elif defined(_MSC_VER)
#define CSTUB_MSC_ALIGN(x) _declspec(align(x)) 
#define CSTUB_GCC_ALIGN(x) 
#define CSTUB_EXPLICIT explicit
#define CSTUB_MAY_ALIAS 
#if defined(CSTUB_DLLEXPORT)
#define CSTUB_EXTERN __declspec(dllexport)
#elif defined(CSTUB_DLLIMPORT)
#define CSTUB_EXTERN __declspec(dllimport)
#else
#define CSTUB_EXTERN extern
#endif
#else 
#error "Error: Only GCC/G++ and Visual C++ are supported"
#endif

#define CSTUB_(X) cstub_Xm_dmx1a_##X

/* Ctype macros */
#define xtbool CSTUB_(xtbool)
#define xtbool2 CSTUB_(xtbool2)
#define xtbool4 CSTUB_(xtbool4)
#define xtbool8 CSTUB_(xtbool8)
#define xtbool16 CSTUB_(xtbool16)
#define fr32 CSTUB_(fr32)
#define vr64 CSTUB_(vr64)
#define vr128 CSTUB_(vr128)
#define wr64 CSTUB_(wr64)
#define cr64 CSTUB_(cr64)
#define mir30 CSTUB_(mir30)
#define ulsr128 CSTUB_(ulsr128)
#define perm16 CSTUB_(perm16)

#if defined(__cplusplus)
/* Ctype declarations */
typedef int immediate;
#define DECLARE_CTYPE(s) \
    namespace s##_space { \
    class s##_; \
    } \
    typedef s##_space::s##_ s;

DECLARE_CTYPE(xtbool);
DECLARE_CTYPE(xtbool2);
DECLARE_CTYPE(xtbool4);
DECLARE_CTYPE(xtbool8);
DECLARE_CTYPE(xtbool16);
DECLARE_CTYPE(fr32);
DECLARE_CTYPE(vr64);
DECLARE_CTYPE(vr128);
DECLARE_CTYPE(wr64);
DECLARE_CTYPE(cr64);
DECLARE_CTYPE(mir30);
DECLARE_CTYPE(ulsr128);
DECLARE_CTYPE(perm16);

/* Ctype definitions */
namespace xtbool_space {
CSTUB_MSC_ALIGN(1) class xtbool_ {
public:
unsigned char  _[1];
xtbool_ () {}
template <typename T_> inline operator T_() const;
inline xtbool_ (const int src) { _[0] = src & 0x1;}
inline operator int() { return _[0]; }
inline xtbool_ (const unsigned int src) { _[0] = src & 0x1;}
inline operator unsigned int() { return _[0]; }
inline xtbool_ (const short src) { _[0] = src & 0x1;}
inline operator short() { return _[0]; }
inline xtbool_ (const unsigned short src) { _[0] = src & 0x1;}
inline operator unsigned short() { return _[0]; }
inline xtbool_ (const char src) { _[0] = src & 0x1;}
inline operator char() { return _[0]; }
inline xtbool_ (const unsigned char src) { _[0] = src & 0x1;}
inline operator unsigned char() { return _[0]; }
inline xtbool_ (const bool src) { _[0] = (unsigned char)src;}
inline operator bool() { return (bool)(_[0] & 0x1);} 
} CSTUB_GCC_ALIGN(1);
}

namespace xtbool2_space {
CSTUB_MSC_ALIGN(1) class xtbool2_ {
public:
unsigned char  _[1];
xtbool2_ () {}
template <typename T_> inline operator T_() const;
inline xtbool2_ (const int src) { _[0] = src & 0x3;}
inline operator int() { return _[0]; }
inline xtbool2_ (const unsigned int src) { _[0] = src & 0x3;}
inline operator unsigned int() { return _[0]; }
inline xtbool2_ (const short src) { _[0] = src & 0x3;}
inline operator short() { return _[0]; }
inline xtbool2_ (const unsigned short src) { _[0] = src & 0x3;}
inline operator unsigned short() { return _[0]; }
inline xtbool2_ (const char src) { _[0] = src & 0x3;}
inline operator char() { return _[0]; }
inline xtbool2_ (const unsigned char src) { _[0] = src & 0x3;}
inline operator unsigned char() { return _[0]; }
} CSTUB_GCC_ALIGN(1);
}

namespace xtbool4_space {
CSTUB_MSC_ALIGN(1) class xtbool4_ {
public:
unsigned char  _[1];
xtbool4_ () {}
template <typename T_> inline operator T_() const;
inline xtbool4_ (const int src) { _[0] = src & 0xf;}
inline operator int() { return _[0]; }
inline xtbool4_ (const unsigned int src) { _[0] = src & 0xf;}
inline operator unsigned int() { return _[0]; }
inline xtbool4_ (const short src) { _[0] = src & 0xf;}
inline operator short() { return _[0]; }
inline xtbool4_ (const unsigned short src) { _[0] = src & 0xf;}
inline operator unsigned short() { return _[0]; }
inline xtbool4_ (const char src) { _[0] = src & 0xf;}
inline operator char() { return _[0]; }
inline xtbool4_ (const unsigned char src) { _[0] = src & 0xf;}
inline operator unsigned char() { return _[0]; }
} CSTUB_GCC_ALIGN(1);
}

namespace xtbool8_space {
CSTUB_MSC_ALIGN(1) class xtbool8_ {
public:
unsigned char  _[1];
xtbool8_ () {}
template <typename T_> inline operator T_() const;
inline xtbool8_ (const int src) { _[0] = src & 0xff;}
inline operator int() { return _[0]; }
inline xtbool8_ (const unsigned int src) { _[0] = src & 0xff;}
inline operator unsigned int() { return _[0]; }
inline xtbool8_ (const short src) { _[0] = src & 0xff;}
inline operator short() { return _[0]; }
inline xtbool8_ (const unsigned short src) { _[0] = src & 0xff;}
inline operator unsigned short() { return _[0]; }
inline xtbool8_ (const char src) { _[0] = src & 0xff;}
inline operator char() { return _[0]; }
inline xtbool8_ (const unsigned char src) { _[0] = src & 0xff;}
inline operator unsigned char() { return _[0]; }
} CSTUB_GCC_ALIGN(1);
}

namespace xtbool16_space {
CSTUB_MSC_ALIGN(2) class xtbool16_ {
public:
unsigned short  _[1];
xtbool16_ () {}
template <typename T_> inline operator T_() const;
inline xtbool16_ (const int src) { _[0] = src & 0xffff;}
inline operator int() { return _[0]; }
inline xtbool16_ (const unsigned int src) { _[0] = src & 0xffff;}
inline operator unsigned int() { return _[0]; }
inline xtbool16_ (const short src) { _[0] = src & 0xffff;}
inline operator short() { return _[0]; }
inline xtbool16_ (const unsigned short src) { _[0] = src & 0xffff;}
inline operator unsigned short() { return _[0]; }
} CSTUB_GCC_ALIGN(2);
}

namespace fr32_space {
CSTUB_MSC_ALIGN(4) class fr32_ {
public:
unsigned int _[1];
fr32_ () {}
inline fr32_& operator= (const fr32_ &src);
inline fr32_ (const unsigned int &src);
inline fr32_& operator= (const unsigned int &src);
inline fr32_ (const int &src);
inline fr32_& operator= (const int &src);
template <typename T_> inline operator T_() const;
inline operator int () const;
inline operator unsigned int () const;
} CSTUB_GCC_ALIGN(4);
}

namespace vr64_space {
CSTUB_MSC_ALIGN(8) class vr64_ {
public:
unsigned int _[2];
vr64_ () {}
inline vr64_& operator= (const vr64_ &src);
inline vr64_ (const unsigned long long &src);
inline vr64_& operator= (const unsigned long long &src);
inline vr64_ (const long long &src);
inline vr64_& operator= (const long long &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(8);
}

namespace vr128_space {
CSTUB_MSC_ALIGN(16) class vr128_ {
public:
unsigned int _[4];
vr128_ () {}
inline vr128_& operator= (const vr128_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(16);
}

namespace wr64_space {
CSTUB_MSC_ALIGN(8) class wr64_ {
public:
unsigned int _[2];
wr64_ () {}
inline wr64_& operator= (const wr64_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(8);
}

namespace cr64_space {
CSTUB_MSC_ALIGN(8) class cr64_ {
public:
unsigned int _[2];
cr64_ () {}
inline cr64_& operator= (const cr64_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(8);
}

namespace mir30_space {
CSTUB_MSC_ALIGN(4) class mir30_ {
public:
unsigned int _[1];
mir30_ () {}
inline mir30_& operator= (const mir30_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(4);
}

namespace ulsr128_space {
CSTUB_MSC_ALIGN(16) class ulsr128_ {
public:
unsigned int _[4];
ulsr128_ () {}
inline ulsr128_& operator= (const ulsr128_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(16);
}

namespace perm16_space {
CSTUB_MSC_ALIGN(2) class perm16_ {
public:
unsigned short  _[1];
perm16_ () {}
inline perm16_& operator= (const perm16_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(2);
}

/* Proto declarations */
CSTUB_EXTERN void CSTUB_(_TIE_xt_density_NOP_N)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_NOP)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_DEPBITS)(unsigned int& art /*inout*/, const unsigned int ars /*in*/, immediate low_depbits /*in*/, immediate lngth_depbits /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_XORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVT)(unsigned int& arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVF)(unsigned int& arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(const unsigned int art /*in*/, const unsigned int ars /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_L32I_N)(const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_density_S32I_N)(const int t /*in*/, const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_ADD_N)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_ADDI_N)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_MOV_N)(const int s /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_MOVI_N)(immediate i /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_uint32_loadi)(const unsigned int * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_uint32_storei)(const unsigned int c /*in*/, const unsigned int * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_uint32_move)(const unsigned int b /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDI)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_OR)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_L32I)(const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S32I)(const int r /*in*/, const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S32NB)(const int r /*in*/, const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned char CSTUB_(_TIE_xt_core_L8UI)(const unsigned char * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S8I)(const signed char r /*in*/, const signed char * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned short CSTUB_(_TIE_xt_core_L16UI)(const unsigned short * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN short CSTUB_(_TIE_xt_core_L16SI)(const short * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S16I)(const short r /*in*/, const short * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDMI)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADD)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDX2)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDX4)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDX8)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUB)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUBX2)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUBX4)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUBX8)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SALT)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SALTU)(const unsigned int s /*in*/, const unsigned int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_AND)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_XOR)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_EXTUI)(const unsigned int t /*in*/, immediate i /*in*/, immediate o /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_MOVI)(immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVEQZ)(int& r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVNEZ)(int& r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVLTZ)(int& r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVGEZ)(int& r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_NEG)(const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ABS)(const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSR)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSL)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSA8L)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSA8B)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSAI)(immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SLL)(const int s /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SRC)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SRL)(const unsigned int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SRA)(const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SLLI)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SRAI)(const int t /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SRLI)(const unsigned int t /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSAI_SRC)(const int src1 /*in*/, const int src2 /*in*/, immediate amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSR_SRC)(const int src1 /*in*/, const int src2 /*in*/, const int amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSR_SRA)(const int src /*in*/, const int amount /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SSR_SRL)(const unsigned int src /*in*/, const int amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSL_SLL)(const int src /*in*/, const int amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_CLAMPS)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_MIN)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_MAX)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_misc_MINU)(const unsigned int s /*in*/, const unsigned int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_misc_MAXU)(const unsigned int s /*in*/, const unsigned int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_NSA)(const int s /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_misc_NSAU)(const unsigned int s /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_SEXT)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_READ_IPQ)(void);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_CHECK_IPQ)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WRITE_OPQ)(const unsigned int a /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_CHECK_OPQ)(void);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_RUR_EXPSTATE)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WUR_EXPSTATE)(const unsigned int v /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_PERM)(const perm16 a /*in*/, const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_ld_PERM)(const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_ULSR)(const ulsr128& a /*in*/, const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_ld_ULSR)(const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_MIR)(const mir30& a /*in*/, const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_ld_MIR)(const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_CR)(const cr64& a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_ld_CR)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_WR)(const wr64& a /*in*/, const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_ld_WR)(const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr)(vr128& r /*out*/, const vr128& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_set_perm16)(immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_perm16_cond)(perm16& z /*inout*/, immediate perm /*in*/, const xtbool bx /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postR)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postI)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_circI)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxR)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxI)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postR)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_circI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxR)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxI)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postR)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_circI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postR)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postI)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_circI)(vr128& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxR)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxI)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postR)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_circI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxR)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxI)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postR)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_circI)(vr128& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_32x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_24x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_16x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_8x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a)(vr128& z /*out*/, ulsr128& buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_24x4_vr_a)(vr128& z /*out*/, ulsr128& buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_16x4_vr_a)(vr128& z /*out*/, ulsr128& buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_8x4_vr_a)(vr128& z /*out*/, ulsr128& buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_circ)(vr128& z /*out*/, ulsr128& buf /*inout*/, const unsigned int ** ptr /*inout*/, const cr64& c /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postR)(wr64& w /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postI)(wr64& w /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxR)(const vr128& z /*in*/, const xtbool4 bx4 /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxI)(const vr128& z /*in*/, const xtbool4 bx4 /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postR)(const vr128& z /*in*/, const xtbool4 bx4 /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postI)(const vr128& z /*in*/, const xtbool4 bx4 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_circI)(const vr128& z /*in*/, const xtbool4 bx4 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxR)(const vr128& z /*in*/, const xtbool2 bx2 /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxI)(const vr128& z /*in*/, const xtbool2 bx2 /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postR)(const vr128& z /*in*/, const xtbool2 bx2 /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postI)(const vr128& z /*in*/, const xtbool2 bx2 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_circI)(const vr128& z /*in*/, const xtbool2 bx2 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxR)(const vr128& z /*in*/, const xtbool bx /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxI)(const vr128& z /*in*/, const xtbool bx /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postR)(const vr128& z /*in*/, const xtbool bx /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postI)(const vr128& z /*in*/, const xtbool bx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_circI)(const vr128& z /*in*/, const xtbool bx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm)(const vr128& z /*in*/, const vr128& y /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm)(const vr128& z /*in*/, const vr128& y /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm)(const vr128& z /*in*/, const vr128& y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm)(const vr128& z /*in*/, const vr128& y /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm)(const vr128& z /*in*/, const vr128& y /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxR)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxI)(const vr128& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postR)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_circI)(const vr128& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_32x4_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_16x4_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_8x4_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a)(const vr128& z /*in*/, ulsr128& buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_24x4_vr_a)(const vr128& z /*in*/, ulsr128& buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_16x4_vr_a)(const vr128& z /*in*/, ulsr128& buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_8x4_vr_a)(const vr128& z /*in*/, ulsr128& buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_circ)(const vr128& z /*in*/, ulsr128& buf /*inout*/, unsigned int ** ptr /*inout*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_32x4)(const ulsr128& buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_24x4)(const ulsr128& buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_16x4)(const ulsr128& buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_8x4)(const ulsr128& buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_2_5)(const unsigned int ar32x /*in*/, const xtbool four /*in*/, immediate odd /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_6_13)(const unsigned int ar32x /*in*/, const xtbool2 idx_spec /*in*/, const xtbool2 ext_size /*in*/, immediate odd /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_next_odd)(const unsigned int ar32x /*in*/, const xtbool4 nbits /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_upd_idx_spec)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_build_palindrome)(const unsigned int ar32x /*in*/, const xtbool4 nbits /*in*/, immediate odd /*in*/, immediate shift_type /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load_vr_bdir)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load_vr_brev)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_bdir)(const vr128& z /*in*/, const wr64& w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_bdir)(const vr128& z /*in*/, const wr64& w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_brev)(const vr128& z /*in*/, const wr64& w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_brev)(const vr128& z /*in*/, const wr64& w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_vrl_postR)(const vr128& z /*in*/, const vr128& y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_vrh_postR)(const vr128& z /*in*/, const vr128& y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_postR)(const vr128& z /*in*/, const wr64& w /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrl_postR)(const wr64& w /*in*/, const vr128& y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_postR)(const vr128& z /*in*/, const wr64& w /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrh_postR)(const wr64& w /*in*/, const vr128& y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_fr_postI)(fr32& fx /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_fr_postI)(const fr32 fx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_move32_wr_vr)(const vr128& x /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_move32_wr_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_move64_wr_vr)(const vr128& x /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move64_vr_wr)(vr128& z /*inout*/, const wr64& w /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr)(const vr128& x /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr_idx)(const vr128& x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_move32_fr_vr_idx)(const vr128& x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN xtbool2 CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool2)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool4)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_eqz)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_gez)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_gtz)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_lez)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_ltz)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_nez)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_sat)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_eqz)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gez)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gtz)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_lez)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_ltz)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_nez)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_sat)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_replicate)(vr128& z /*inout*/, immediate sel_code /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_replicate_ar)(vr128& z /*inout*/, immediate sel_code /*in*/, const unsigned int ar /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_creplicate_H)(const vr128& x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_creplicate_L)(const vr128& x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vreplicate)(const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vreplicate_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vreplicate_hr)(const vr64& hx /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_hreplicate_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x1)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x2)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x4)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x1)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x2)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x4)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x1)(vr128& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x2)(vr128& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x4)(vr128& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x1)(vr128& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x2)(vr128& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x4)(vr128& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_32F_x1)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_32I_x1)(vr128& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4)(vr128& z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4)(vr128& z /*inout*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F)(const unsigned int ar /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float)(const fr32 fx /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_64F)(const unsigned int x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32I)(const vr64& x /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_64F)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32F)(const vr64& x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_double_to_64F)(vr64& z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_IEEE_double)(vr64& z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_adj_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_adj_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_perm_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_perm_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_adj_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_adj_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_perm_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_perm_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xl_wr)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xh_wr)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xl_wr)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xh_wr)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yl)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yl)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yh)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yh)(const wr64& w /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh)(vr128& z /*inout*/, wr64& w1 /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmul)(const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmul_conj)(const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmac)(const vr64& hz /*in*/, const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmac_conj)(const vr64& hz /*in*/, const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmas)(const vr64& hz /*in*/, const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmas_conj)(const vr64& hz /*in*/, const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmul_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmul_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmac_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmac_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmas_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmas_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmac_Lx2)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmac_Hx2)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmul_x2)(const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmac_adj_x2)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmas_adj_x2)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_xcorr)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_xconv)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_qmul_1)(const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_qmul_2)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_matmul_2x2)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vadds)(const vr128& x /*in*/, const vr128& y /*in*/, immediate signs8 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmidp)(const vr128& x /*in*/, const vr128& y /*in*/, immediate signs8 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmuls)(const vr128& x /*in*/, const vr128& y /*in*/, immediate signs8 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmacs_adj)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs8 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmuls_perm)(const vr128& x /*in*/, const vr128& y /*in*/, immediate signs8 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmacs_perm)(const vr128& z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs8 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vssub_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, const wr64& w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vssub_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, const wr64& w /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vssub_x2)(const vr128& x /*in*/, const vr128& y /*in*/, const wr64& w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vinterp_L)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, const wr64& w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vinterp_H)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, const wr64& w /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vinterp_x2)(const vr128& x /*in*/, const vr128& y /*in*/, const wr64& w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_csums_L)(vr128& z /*inout*/, const vr128& x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_csums_H)(vr128& z /*inout*/, const vr128& x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_dsums_L)(vr128& z /*inout*/, const vr128& x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_dsums_H)(vr128& z /*inout*/, const vr128& x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vadd_hr)(const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vsub_hr)(const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vmul_hr)(const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vmac_hr)(const vr64& hz /*in*/, const vr64& hx /*in*/, const vr64& hy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fpadd)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fpmul)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fpmac)(fr32& fz /*inout*/, const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fpmul_sum3)(const vr128& x /*in*/, const vr128& y /*in*/, immediate signs3 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vscale)(const fr32 fx /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vscale_adds)(const vr128& z /*in*/, const fr32 fx /*in*/, const vr128& y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fadds)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, immediate signs5 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmacs)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, immediate signs5 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmuls)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, immediate signs5 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmul_sum3)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate signs3 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_dadds)(const vr64& z /*in*/, const vr64& x /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_dmuls)(const vr64& x /*in*/, const vr64& y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_dmacs)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vabs)(const vr128& x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vexp_adj)(const vr128& x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vexp_adji)(const vr128& x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vperm)(const vr128& x /*in*/, const vr128& y /*in*/, const perm16 sel /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vperms)(const vr128& x /*in*/, const vr128& y /*in*/, const perm16 sel /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vpermsi)(const vr128& x /*in*/, const vr128& y /*in*/, immediate signs /*in*/, immediate sel3 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_seta_vr)(vr128& z /*inout*/, immediate sel_code /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vseta_vr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_seta_ar)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_seta_fr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_f_abs)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fclamp)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fclamp_bp)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fclamp_one)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmax)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmin)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_max_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_min_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_log2)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_pow2)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sigmoid)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_inv)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ratio)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, xtbool4& bz4 /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_atanratio)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const xtbool4 bx4 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_invsqrt)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sine)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cosine)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_log2mul)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, xtbool& bz /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cspow2)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const xtbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_log2_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_pow2_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_sigmoid_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_inv_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_invsqrt_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_sine_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_cosine_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN xtbool2 CSTUB_(_TIE_dmx1a_common_tie_comp)(const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_eq)(const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ge)(const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_gt)(const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_le)(const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_lt)(const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ne)(const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool2 CSTUB_(_TIE_dmx1a_common_tie_comp_const)(const vr128& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_eq_const)(const vr128& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ge_const)(const vr128& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_gt_const)(const vr128& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_le_const)(const vr128& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_lt_const)(const vr128& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ne_const)(const vr128& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_eq_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ge_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_gt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_le_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_lt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ne_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_neg_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_abs_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_deqz)(const vr64& x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dgez)(const vr64& x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dgtz)(const vr64& x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dlez)(const vr64& x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dltz)(const vr64& x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dnez)(const vr64& x /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_veq)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vge)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vgt)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vle)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vlt)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vne)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_veq_const)(const vr128& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vge_const)(const vr128& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vgt_const)(const vr128& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vle_const)(const vr128& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vlt_const)(const vr128& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vne_const)(const vr128& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool bx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_1b4)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool4 bx4 /*in*/, immediate el_bx4 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_eq)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_ge)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_gt)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_le)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_lt)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_ne)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vsel)(const vr128& x /*in*/, const vr128& y /*in*/, const xtbool4 bx4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_andb1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_andbc1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_orb1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_orbc1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_xorb1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_andb4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_andbc4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_orb4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_orbc4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_xorb4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast0_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast0_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast1_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast1_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_bgetI)(const xtbool4 bx4 /*in*/, immediate ipos /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_bgetR)(const xtbool4 bx4 /*in*/, const unsigned int rpos /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_bsetI)(const xtbool4 bx4 /*in*/, const unsigned int rpos /*in*/, immediate ibit /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_bsetR)(const xtbool4 bx4 /*in*/, const unsigned int rpos /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_exp_adj)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_exp_adji)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_exp_adj_fr)(const fr32 fx /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_exp_adji_fr)(const fr32 fx /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_neg)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_copy)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_and)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_andc)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_or)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_orc)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_xor)(vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vnegs)(const vr128& x /*in*/, immediate signs /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vcopy)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vand)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vandc)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vor)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vorc)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vxor)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_s_vnegs_hr)(const vr64& hx /*in*/, immediate hr_signs /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_floorp_frac)(unsigned int& floor /*out*/, vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, immediate el_x /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_idx_frac)(unsigned int& floor /*out*/, vr128& z /*inout*/, immediate el_z /*in*/, const unsigned int input /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_truncate_fr)(const fr32 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rmax_idx)(unsigned int& a /*out*/, vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, const mir30& idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rmin_idx)(unsigned int& a /*out*/, vr128& z /*inout*/, immediate el_z /*in*/, const vr128& x /*in*/, const mir30& idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmaxmin_init)(vr128& z /*out*/, const vr128& x /*in*/, mir30& idx /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmax_idx)(vr128& z /*inout*/, const vr128& x /*in*/, mir30& idx /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmin_idx)(vr128& z /*inout*/, const vr128& x /*in*/, mir30& idx /*inout*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmax)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmin)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_vr)(unsigned int& a /*out*/, vr128& z /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_vr)(unsigned int& a /*out*/, vr128& z /*out*/, const vr128& x /*in*/, const vr128& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_ar)(unsigned int& a /*inout*/, vr128& z /*out*/, const vr128& x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_ar)(unsigned int& a /*inout*/, vr128& z /*out*/, const vr128& x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vbool)(const vr128& x /*in*/, const vr128& y /*in*/, immediate op /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_align_up)(const unsigned int val /*in*/, const unsigned int option /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_range_init)(const unsigned int low /*in*/, const unsigned int high /*in*/, immediate startOp /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_range_check)(xtbool4& bz4 /*out*/, mir30& idx /*inout*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_afloat_exp_extract)(const vr128& x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_exp_shift_amount)(const vr128& input /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_32x4_bounded)(const ulsr128& buf /*in*/, unsigned int ** ptr /*inout*/, mir30& count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_AccExtend_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB0_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30& parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB1_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30& parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB2_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30& parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB3_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30& parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB4_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30& parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB5_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30& parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB6_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30& parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB7_flex)(const unsigned int ** ptr /*inout*/, const unsigned int remBlock /*in*/, mir30& parms /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB0_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB4_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB5_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB6_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB7_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BBx_a_bounded)(ulsr128& buf /*inout*/, const unsigned int ** ptr /*inout*/, mir30& count /*inout*/, const unsigned int sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB4_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB5_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB6_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB7_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_bounded)(vr128& z /*out*/, ulsr128& buf /*inout*/, const unsigned int ** ptr /*inout*/, mir30& count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_lookup_AccExtend_postI)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load_lookup_vr_postI)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr)(const vr128& vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr)(vr128& z /*inout*/, const vr128& vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idx16vr)(vr128& z /*inout*/, const unsigned int * ptr /*in*/, const vr128& vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool2 signed_xy /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_conv)(vr128& z /*inout*/, const vr128& x /*in*/, const xtbool2 signed_xy /*in*/, immediate shift_in /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_sparse)(vr128& z /*inout*/, const vr128& x /*in*/, const vr128& y /*in*/, const xtbool2 signed_xy /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mir_init)(const unsigned int low /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mov_AccExtend_vr)(const vr128& x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mov_BB_vrVB)(const vr128& x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_mov_vr_AccExtend)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_mov_vrVB_BB)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_next_lookup_load)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_next_lookup_store)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_precess_16bits)(const vr128& x /*in*/, const vr128& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rectify32_into8)(vr128& z /*inout*/, const vr128& x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rnd_sat_pack)(vr128& z /*inout*/, immediate el32 /*in*/, const vr128& x /*in*/, const xtbool sgn /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_BB_zero)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_shift8_into32_arith)(const vr128& x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_shift32_arith)(const vr128& x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_bounded)(const vr128& z /*in*/, ulsr128& buf /*inout*/, unsigned int ** ptr /*inout*/, mir30& count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_AccExtend_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB0_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB4_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB5_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB6_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB7_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB4_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB5_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB6_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB7_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_lookup_AccExtend_postI)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_lookup_vr_postI)(const vr128& z /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_mv_WR)(const wr64& b /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_mv_PERM)(const perm16 b /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mv_MIR)(const mir30& b /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_mv_ULSR)(const ulsr128& b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_mv_CR)(const cr64& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_ld_FR)(const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_ld_FR_idxR)(const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR_idxR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postI)(fr32& fregout /*out*/, const fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR_postI)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postR)(fr32& fregout /*out*/, const fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR_postR)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_ld_HR)(const vr64 * addr /*in*/, immediate himm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR)(const vr64& hregin /*in*/, const vr64 * addr /*in*/, immediate himm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_ld_HR_idxR)(const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR_idxR)(const vr64& hregin /*in*/, const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postI)(vr64& hregout /*out*/, const vr64 ** addr /*inout*/, immediate himm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR_postI)(const vr64& hregin /*in*/, vr64 ** addr /*inout*/, immediate himm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postR)(vr64& hregout /*out*/, const vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR_postR)(const vr64& hregin /*in*/, vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_ld_VR)(const vr128 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR)(const vr128& vregin /*in*/, const vr128 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_ld_VR_idxR)(const vr128 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR_idxR)(const vr128& vregin /*in*/, const vr128 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postI)(vr128& vregout /*out*/, const vr128 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR_postI)(const vr128& vregin /*in*/, vr128 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postR)(vr128& vregout /*out*/, const vr128 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR_postR)(const vr128& vregin /*in*/, vr128 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_mv_FR)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_move_ar_fr)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_move_fr_ar)(const unsigned int b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_mv_HR)(const vr64& b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_mv_VR)(const vr128& b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_pair)(const vr64& hi /*in*/, const vr64& lo /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRL)(vr128& v /*inout*/, const vr64& lo /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRH)(vr128& v /*inout*/, const vr64& hi /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_get_VRL)(const vr128& b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_get_VRH)(const vr128& b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_ar_x2)(unsigned int& a1_out /*out*/, unsigned int& a0_out /*out*/, const void * ptr /*in*/, immediate idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_ar_x2)(const void * ptr /*in*/, immediate idx /*in*/, const unsigned int a1_in /*in*/, const unsigned int a0_in /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_perm16_storei)(const perm16 a /*in*/, const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_perm16_loadi)(const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ulsr128_storei)(const ulsr128& a /*in*/, const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_ulsr128_loadi)(const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mir30_storei)(const mir30& a /*in*/, const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mir30_loadi)(const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cr64_storei)(const cr64& a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_cr64_loadi)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_wr64_storei)(const wr64& a /*in*/, const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_wr64_loadi)(const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_JammingBit)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_JammingBit)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_MvmAux)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_MvmAux)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_look_state)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_look_state)(const unsigned int v /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_wr64_move)(const wr64& b /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_perm16_move)(const perm16 b /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mir30_move)(const mir30& b /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_ulsr128_move)(const ulsr128& b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_cr64_move)(const cr64& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fr32_move)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fr32_loadi)(const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storei)(const fr32 v /*in*/, const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fr32_loadx)(const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storex)(const fr32 v /*in*/, const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_loadip)(fr32& v /*out*/, const fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storeip)(const fr32 v /*in*/, fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_loadxp)(fr32& v /*out*/, const fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storexp)(const fr32 v /*in*/, fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_int32)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_uint32)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_int32_rtor_fr32)(const int a /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_uint32_rtor_fr32)(const unsigned int a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_move)(const vr64& b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_loadi)(const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storei)(const vr64& v /*in*/, const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_loadx)(const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storex)(const vr64& v /*in*/, const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_loadip)(vr64& v /*out*/, const vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storeip)(const vr64& v /*in*/, vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_loadxp)(vr64& v /*out*/, const vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storexp)(const vr64& v /*in*/, vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN long long CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_int64)(const vr64& b /*in*/);
CSTUB_EXTERN unsigned long long CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_uint64)(const vr64& b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_int64_rtor_vr64)(const long long& a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_uint64_rtor_vr64)(const unsigned long long& a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_pair)(const fr32 hi /*in*/, const fr32 lo /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_HRL)(const vr64& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_HRH)(const vr64& b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_HRL)(vr64& a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_HRH)(vr64& a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_move)(const vr128& b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_loadi)(const vr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storei)(const vr128& a /*in*/, const vr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_loadx)(const vr128 * b /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storex)(const vr128& a /*in*/, const vr128 * b /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_loadip)(vr128& a /*out*/, const vr128 ** b /*inout*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storeip)(const vr128& a /*in*/, vr128 ** b /*inout*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_loadxp)(vr128& a /*out*/, const vr128 ** b /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storexp)(const vr128& a /*in*/, vr128 ** b /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_quad)(const fr32 q3 /*in*/, const fr32 q2 /*in*/, const fr32 q1 /*in*/, const fr32 q0 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ0)(const vr128& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ1)(const vr128& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ2)(const vr128& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ3)(const vr128& b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ0)(vr128& a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ1)(vr128& a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ2)(vr128& a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ3)(vr128& a /*inout*/, const fr32 b /*in*/);

CSTUB_EXTERN unsigned CSTUB_(_TIE_xt_core_RSR_SAR)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_WSR_SAR)(unsigned t);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_XSR_SAR)(unsigned& t /*inout*/);
/* Ctype convertion functions */
namespace xtbool_space {

}

namespace xtbool2_space {

}

namespace xtbool4_space {

}

namespace xtbool8_space {

}

namespace xtbool16_space {

}

namespace fr32_space {
inline fr32& fr32::operator= (const fr32 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_fr32_storei)(src, this, 0);
  }
  return *this;
}
inline fr32::fr32_(const unsigned int &src) {
  *this = CSTUB_(_TIE_dmx1a_common_tie_uint32_rtor_fr32)(src);
}
inline fr32& fr32::operator= (const unsigned int &src_in) {
  unsigned int src = (unsigned int) src_in;
  *this = CSTUB_(_TIE_dmx1a_common_tie_uint32_rtor_fr32)(src);
  return *this;
}
inline fr32::fr32_(const int &src) {
  *this = CSTUB_(_TIE_dmx1a_common_tie_int32_rtor_fr32)(src);
}
inline fr32& fr32::operator= (const int &src_in) {
  int src = (int) src_in;
  *this = CSTUB_(_TIE_dmx1a_common_tie_int32_rtor_fr32)(src);
  return *this;
}
#if 0 //ndef _MSC_VER
template<>
#endif
inline fr32::fr32_::operator unsigned int () const {
  return CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_uint32) (*this);
}
#if 0
template<>
#endif
inline fr32::fr32_::operator int () const {
  return CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_int32) (*this);
}

}

namespace vr64_space {
inline vr64& vr64::operator= (const vr64 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_vr64_storei)(src, this, 0);
  }
  return *this;
}
inline vr64::vr64_(const unsigned long long &src) {
  *this = CSTUB_(_TIE_dmx1a_common_tie_uint64_rtor_vr64)(src);
}
inline vr64& vr64::operator= (const unsigned long long &src_in) {
  unsigned long long src = (unsigned long long) src_in;
  *this = CSTUB_(_TIE_dmx1a_common_tie_uint64_rtor_vr64)(src);
  return *this;
}
inline vr64::vr64_(const long long &src) {
  *this = CSTUB_(_TIE_dmx1a_common_tie_int64_rtor_vr64)(src);
}
inline vr64& vr64::operator= (const long long &src_in) {
  long long src = (long long) src_in;
  *this = CSTUB_(_TIE_dmx1a_common_tie_int64_rtor_vr64)(src);
  return *this;
}
#ifndef _MSC_VER
template<>
#endif
inline vr64::operator unsigned long long () const {
  return CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_uint64) (*this);
}
#ifndef _MSC_VER
template<>
#endif
inline vr64::operator long long () const {
  return CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_int64) (*this);
}

}

namespace vr128_space {
inline vr128& vr128::operator= (const vr128 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_vr128_storei)(src, this, 0);
  }
  return *this;
}

}

namespace wr64_space {
inline wr64& wr64::operator= (const wr64 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_wr64_storei)(src, this, 0);
  }
  return *this;
}

}

namespace cr64_space {
inline cr64& cr64::operator= (const cr64 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_cr64_storei)(src, this, 0);
  }
  return *this;
}

}

namespace mir30_space {
inline mir30& mir30::operator= (const mir30 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_mir30_storei)(src, this, 0);
  }
  return *this;
}

}

namespace ulsr128_space {
inline ulsr128& ulsr128::operator= (const ulsr128 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_ulsr128_storei)(src, this, 0);
  }
  return *this;
}

}

namespace perm16_space {
inline perm16& perm16::operator= (const perm16 &src) {
  if (this != &src) {
    CSTUB_(_TIE_dmx1a_common_tie_perm16_storei)(src, this, 0);
  }
  return *this;
}

}


/* Proto macros */
#ifdef _STRICT_ARG_TYPE
#define XT_NOP_N() \
	CSTUB_(_TIE_xt_density_NOP_N)()
#else
#define XT_NOP_N() \
	CSTUB_(_TIE_xt_density_NOP_N)()
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_NOP() \
	CSTUB_(_TIE_xt_core_NOP)()
#else
#define XT_NOP() \
	CSTUB_(_TIE_xt_core_NOP)()
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_DEPBITS(art, ars, low_depbits, lngth_depbits) \
	CSTUB_(_TIE_xt_core_DEPBITS)(art, ars, low_depbits, lngth_depbits)
#else
#define XT_DEPBITS(art, ars, low_depbits, lngth_depbits) { \
	unsigned int __art = art; \
	CSTUB_(_TIE_xt_core_DEPBITS)(__art, ars, low_depbits, lngth_depbits); \
	(art) = __art; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_XORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_XORB)(bs, bt)
#else
#define XT_XORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_XORB)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ORBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORBC)(bs, bt)
#else
#define XT_ORBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORBC)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORB)(bs, bt)
#else
#define XT_ORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORB)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ANDBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDBC)(bs, bt)
#else
#define XT_ANDBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDBC)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ANDB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDB)(bs, bt)
#else
#define XT_ANDB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDB)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ALL4(bs4) \
	CSTUB_(_TIE_xt_booleans_ALL4)(bs4)
#else
#define XT_ALL4(bs4) \
	CSTUB_(_TIE_xt_booleans_ALL4)(bs4)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ANY4(bs4) \
	CSTUB_(_TIE_xt_booleans_ANY4)(bs4)
#else
#define XT_ANY4(bs4) \
	CSTUB_(_TIE_xt_booleans_ANY4)(bs4)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ALL8(bs8) \
	CSTUB_(_TIE_xt_booleans_ALL8)(bs8)
#else
#define XT_ALL8(bs8) \
	CSTUB_(_TIE_xt_booleans_ALL8)(bs8)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ANY8(bs8) \
	CSTUB_(_TIE_xt_booleans_ANY8)(bs8)
#else
#define XT_ANY8(bs8) \
	CSTUB_(_TIE_xt_booleans_ANY8)(bs8)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVT(arr, ars, bt) \
	CSTUB_(_TIE_xt_booleans_MOVT)(arr, ars, bt)
#else
#define XT_MOVT(arr, ars, bt) { \
	unsigned int __arr = arr; \
	CSTUB_(_TIE_xt_booleans_MOVT)(__arr, ars, bt); \
	(arr) = __arr; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVF(arr, ars, bt) \
	CSTUB_(_TIE_xt_booleans_MOVF)(arr, ars, bt)
#else
#define XT_MOVF(arr, ars, bt) { \
	unsigned int __arr = arr; \
	CSTUB_(_TIE_xt_booleans_MOVF)(__arr, ars, bt); \
	(arr) = __arr; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define READ_IMPWIRE() \
	CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)()
#else
#define READ_IMPWIRE() \
	CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)()
#endif

#ifdef _STRICT_ARG_TYPE
#define SETB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(bitindex)
#else
#define SETB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(bitindex)
#endif

#ifdef _STRICT_ARG_TYPE
#define CLRB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(bitindex)
#else
#define CLRB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(bitindex)
#endif

#ifdef _STRICT_ARG_TYPE
#define WRMSK_EXPSTATE(art, ars) \
	CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(art, ars)
#else
#define WRMSK_EXPSTATE(art, ars) \
	CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(art, ars)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_L32I_N(p, i) \
	CSTUB_(_TIE_xt_density_L32I_N)(p, i)
#else
#define XT_L32I_N(p, i) \
	CSTUB_(_TIE_xt_density_L32I_N)(p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_S32I_N(t, p, i) \
	CSTUB_(_TIE_xt_density_S32I_N)(t, p, i)
#else
#define XT_S32I_N(t, p, i) \
	CSTUB_(_TIE_xt_density_S32I_N)(t, p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADD_N(s, t) \
	CSTUB_(_TIE_xt_density_ADD_N)(s, t)
#else
#define XT_ADD_N(s, t) \
	CSTUB_(_TIE_xt_density_ADD_N)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADDI_N(s, i) \
	CSTUB_(_TIE_xt_density_ADDI_N)(s, i)
#else
#define XT_ADDI_N(s, i) \
	CSTUB_(_TIE_xt_density_ADDI_N)(s, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOV_N(s) \
	CSTUB_(_TIE_xt_density_MOV_N)(s)
#else
#define XT_MOV_N(s) \
	CSTUB_(_TIE_xt_density_MOV_N)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVI_N(i) \
	CSTUB_(_TIE_xt_density_MOVI_N)(i)
#else
#define XT_MOVI_N(i) \
	CSTUB_(_TIE_xt_density_MOVI_N)(i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_uint32_loadi(p, o) \
	CSTUB_(_TIE_xt_core_uint32_loadi)(p, o)
#else
#define XT_uint32_loadi(p, o) \
	CSTUB_(_TIE_xt_core_uint32_loadi)(p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_uint32_storei(c, p, o) \
	CSTUB_(_TIE_xt_core_uint32_storei)(c, p, o)
#else
#define XT_uint32_storei(c, p, o) \
	CSTUB_(_TIE_xt_core_uint32_storei)(c, p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_uint32_move(b) \
	CSTUB_(_TIE_xt_core_uint32_move)(b)
#else
#define XT_uint32_move(b) \
	CSTUB_(_TIE_xt_core_uint32_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADDI(s, i) \
	CSTUB_(_TIE_xt_core_ADDI)(s, i)
#else
#define XT_ADDI(s, i) \
	CSTUB_(_TIE_xt_core_ADDI)(s, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_OR(s, t) \
	CSTUB_(_TIE_xt_core_OR)(s, t)
#else
#define XT_OR(s, t) \
	CSTUB_(_TIE_xt_core_OR)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_L32I(p, i) \
	CSTUB_(_TIE_xt_core_L32I)(p, i)
#else
#define XT_L32I(p, i) \
	CSTUB_(_TIE_xt_core_L32I)(p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_S32I(r, p, i) \
	CSTUB_(_TIE_xt_core_S32I)(r, p, i)
#else
#define XT_S32I(r, p, i) \
	CSTUB_(_TIE_xt_core_S32I)(r, p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_S32NB(r, p, i) \
	CSTUB_(_TIE_xt_core_S32NB)(r, p, i)
#else
#define XT_S32NB(r, p, i) \
	CSTUB_(_TIE_xt_core_S32NB)(r, p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_L8UI(p, i) \
	CSTUB_(_TIE_xt_core_L8UI)(p, i)
#else
#define XT_L8UI(p, i) \
	CSTUB_(_TIE_xt_core_L8UI)(p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_S8I(r, p, i) \
	CSTUB_(_TIE_xt_core_S8I)(r, p, i)
#else
#define XT_S8I(r, p, i) \
	CSTUB_(_TIE_xt_core_S8I)(r, p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_L16UI(p, i) \
	CSTUB_(_TIE_xt_core_L16UI)(p, i)
#else
#define XT_L16UI(p, i) \
	CSTUB_(_TIE_xt_core_L16UI)(p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_L16SI(p, i) \
	CSTUB_(_TIE_xt_core_L16SI)(p, i)
#else
#define XT_L16SI(p, i) \
	CSTUB_(_TIE_xt_core_L16SI)(p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_S16I(r, p, i) \
	CSTUB_(_TIE_xt_core_S16I)(r, p, i)
#else
#define XT_S16I(r, p, i) \
	CSTUB_(_TIE_xt_core_S16I)(r, p, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADDMI(s, i) \
	CSTUB_(_TIE_xt_core_ADDMI)(s, i)
#else
#define XT_ADDMI(s, i) \
	CSTUB_(_TIE_xt_core_ADDMI)(s, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADD(s, t) \
	CSTUB_(_TIE_xt_core_ADD)(s, t)
#else
#define XT_ADD(s, t) \
	CSTUB_(_TIE_xt_core_ADD)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADDX2(s, t) \
	CSTUB_(_TIE_xt_core_ADDX2)(s, t)
#else
#define XT_ADDX2(s, t) \
	CSTUB_(_TIE_xt_core_ADDX2)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADDX4(s, t) \
	CSTUB_(_TIE_xt_core_ADDX4)(s, t)
#else
#define XT_ADDX4(s, t) \
	CSTUB_(_TIE_xt_core_ADDX4)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ADDX8(s, t) \
	CSTUB_(_TIE_xt_core_ADDX8)(s, t)
#else
#define XT_ADDX8(s, t) \
	CSTUB_(_TIE_xt_core_ADDX8)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SUB(s, t) \
	CSTUB_(_TIE_xt_core_SUB)(s, t)
#else
#define XT_SUB(s, t) \
	CSTUB_(_TIE_xt_core_SUB)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SUBX2(s, t) \
	CSTUB_(_TIE_xt_core_SUBX2)(s, t)
#else
#define XT_SUBX2(s, t) \
	CSTUB_(_TIE_xt_core_SUBX2)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SUBX4(s, t) \
	CSTUB_(_TIE_xt_core_SUBX4)(s, t)
#else
#define XT_SUBX4(s, t) \
	CSTUB_(_TIE_xt_core_SUBX4)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SUBX8(s, t) \
	CSTUB_(_TIE_xt_core_SUBX8)(s, t)
#else
#define XT_SUBX8(s, t) \
	CSTUB_(_TIE_xt_core_SUBX8)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SALT(s, t) \
	CSTUB_(_TIE_xt_core_SALT)(s, t)
#else
#define XT_SALT(s, t) \
	CSTUB_(_TIE_xt_core_SALT)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SALTU(s, t) \
	CSTUB_(_TIE_xt_core_SALTU)(s, t)
#else
#define XT_SALTU(s, t) \
	CSTUB_(_TIE_xt_core_SALTU)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_AND(s, t) \
	CSTUB_(_TIE_xt_core_AND)(s, t)
#else
#define XT_AND(s, t) \
	CSTUB_(_TIE_xt_core_AND)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_XOR(s, t) \
	CSTUB_(_TIE_xt_core_XOR)(s, t)
#else
#define XT_XOR(s, t) \
	CSTUB_(_TIE_xt_core_XOR)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_EXTUI(t, i, o) \
	CSTUB_(_TIE_xt_core_EXTUI)(t, i, o)
#else
#define XT_EXTUI(t, i, o) \
	CSTUB_(_TIE_xt_core_EXTUI)(t, i, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVI(i) \
	CSTUB_(_TIE_xt_core_MOVI)(i)
#else
#define XT_MOVI(i) \
	CSTUB_(_TIE_xt_core_MOVI)(i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVEQZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVEQZ)(r, s, t)
#else
#define XT_MOVEQZ(r, s, t) { \
	int __r = r; \
	CSTUB_(_TIE_xt_core_MOVEQZ)(__r, s, t); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVNEZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVNEZ)(r, s, t)
#else
#define XT_MOVNEZ(r, s, t) { \
	int __r = r; \
	CSTUB_(_TIE_xt_core_MOVNEZ)(__r, s, t); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVLTZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVLTZ)(r, s, t)
#else
#define XT_MOVLTZ(r, s, t) { \
	int __r = r; \
	CSTUB_(_TIE_xt_core_MOVLTZ)(__r, s, t); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MOVGEZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVGEZ)(r, s, t)
#else
#define XT_MOVGEZ(r, s, t) { \
	int __r = r; \
	CSTUB_(_TIE_xt_core_MOVGEZ)(__r, s, t); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_NEG(t) \
	CSTUB_(_TIE_xt_core_NEG)(t)
#else
#define XT_NEG(t) \
	CSTUB_(_TIE_xt_core_NEG)(t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ABS(t) \
	CSTUB_(_TIE_xt_core_ABS)(t)
#else
#define XT_ABS(t) \
	CSTUB_(_TIE_xt_core_ABS)(t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSR(s) \
	CSTUB_(_TIE_xt_core_SSR)(s)
#else
#define XT_SSR(s) \
	CSTUB_(_TIE_xt_core_SSR)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSL(s) \
	CSTUB_(_TIE_xt_core_SSL)(s)
#else
#define XT_SSL(s) \
	CSTUB_(_TIE_xt_core_SSL)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSA8L(s) \
	CSTUB_(_TIE_xt_core_SSA8L)(s)
#else
#define XT_SSA8L(s) \
	CSTUB_(_TIE_xt_core_SSA8L)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSA8B(s) \
	CSTUB_(_TIE_xt_core_SSA8B)(s)
#else
#define XT_SSA8B(s) \
	CSTUB_(_TIE_xt_core_SSA8B)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSAI(i) \
	CSTUB_(_TIE_xt_core_SSAI)(i)
#else
#define XT_SSAI(i) \
	CSTUB_(_TIE_xt_core_SSAI)(i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SLL(s) \
	CSTUB_(_TIE_xt_core_SLL)(s)
#else
#define XT_SLL(s) \
	CSTUB_(_TIE_xt_core_SLL)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SRC(s, t) \
	CSTUB_(_TIE_xt_core_SRC)(s, t)
#else
#define XT_SRC(s, t) \
	CSTUB_(_TIE_xt_core_SRC)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SRL(t) \
	CSTUB_(_TIE_xt_core_SRL)(t)
#else
#define XT_SRL(t) \
	CSTUB_(_TIE_xt_core_SRL)(t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SRA(t) \
	CSTUB_(_TIE_xt_core_SRA)(t)
#else
#define XT_SRA(t) \
	CSTUB_(_TIE_xt_core_SRA)(t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SLLI(s, i) \
	CSTUB_(_TIE_xt_core_SLLI)(s, i)
#else
#define XT_SLLI(s, i) \
	CSTUB_(_TIE_xt_core_SLLI)(s, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SRAI(t, i) \
	CSTUB_(_TIE_xt_core_SRAI)(t, i)
#else
#define XT_SRAI(t, i) \
	CSTUB_(_TIE_xt_core_SRAI)(t, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SRLI(t, i) \
	CSTUB_(_TIE_xt_core_SRLI)(t, i)
#else
#define XT_SRLI(t, i) \
	CSTUB_(_TIE_xt_core_SRLI)(t, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSAI_SRC(src1, src2, amount) \
	CSTUB_(_TIE_xt_core_SSAI_SRC)(src1, src2, amount)
#else
#define XT_SSAI_SRC(src1, src2, amount) \
	CSTUB_(_TIE_xt_core_SSAI_SRC)(src1, src2, amount)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSR_SRC(src1, src2, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRC)(src1, src2, amount)
#else
#define XT_SSR_SRC(src1, src2, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRC)(src1, src2, amount)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSR_SRA(src, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRA)(src, amount)
#else
#define XT_SSR_SRA(src, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRA)(src, amount)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSR_SRL(src, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRL)(src, amount)
#else
#define XT_SSR_SRL(src, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRL)(src, amount)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SSL_SLL(src, amount) \
	CSTUB_(_TIE_xt_core_SSL_SLL)(src, amount)
#else
#define XT_SSL_SLL(src, amount) \
	CSTUB_(_TIE_xt_core_SSL_SLL)(src, amount)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_CLAMPS(s, i) \
	CSTUB_(_TIE_xt_misc_CLAMPS)(s, i)
#else
#define XT_CLAMPS(s, i) \
	CSTUB_(_TIE_xt_misc_CLAMPS)(s, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MIN(s, t) \
	CSTUB_(_TIE_xt_misc_MIN)(s, t)
#else
#define XT_MIN(s, t) \
	CSTUB_(_TIE_xt_misc_MIN)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MAX(s, t) \
	CSTUB_(_TIE_xt_misc_MAX)(s, t)
#else
#define XT_MAX(s, t) \
	CSTUB_(_TIE_xt_misc_MAX)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MINU(s, t) \
	CSTUB_(_TIE_xt_misc_MINU)(s, t)
#else
#define XT_MINU(s, t) \
	CSTUB_(_TIE_xt_misc_MINU)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_MAXU(s, t) \
	CSTUB_(_TIE_xt_misc_MAXU)(s, t)
#else
#define XT_MAXU(s, t) \
	CSTUB_(_TIE_xt_misc_MAXU)(s, t)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_NSA(s) \
	CSTUB_(_TIE_xt_misc_NSA)(s)
#else
#define XT_NSA(s) \
	CSTUB_(_TIE_xt_misc_NSA)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_NSAU(s) \
	CSTUB_(_TIE_xt_misc_NSAU)(s)
#else
#define XT_NSAU(s) \
	CSTUB_(_TIE_xt_misc_NSAU)(s)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_SEXT(s, i) \
	CSTUB_(_TIE_xt_misc_SEXT)(s, i)
#else
#define XT_SEXT(s, i) \
	CSTUB_(_TIE_xt_misc_SEXT)(s, i)
#endif

#ifdef _STRICT_ARG_TYPE
#define READ_IPQ() \
	CSTUB_(_TIE_xt_ioports_READ_IPQ)()
#else
#define READ_IPQ() \
	CSTUB_(_TIE_xt_ioports_READ_IPQ)()
#endif

#ifdef _STRICT_ARG_TYPE
#define CHECK_IPQ() \
	CSTUB_(_TIE_xt_ioports_CHECK_IPQ)()
#else
#define CHECK_IPQ() \
	CSTUB_(_TIE_xt_ioports_CHECK_IPQ)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WRITE_OPQ(a) \
	CSTUB_(_TIE_xt_ioports_WRITE_OPQ)(a)
#else
#define WRITE_OPQ(a) \
	CSTUB_(_TIE_xt_ioports_WRITE_OPQ)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define CHECK_OPQ() \
	CSTUB_(_TIE_xt_ioports_CHECK_OPQ)()
#else
#define CHECK_OPQ() \
	CSTUB_(_TIE_xt_ioports_CHECK_OPQ)()
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_EXPSTATE() \
	CSTUB_(_TIE_xt_ioports_RUR_EXPSTATE)()
#else
#define RUR_EXPSTATE() \
	CSTUB_(_TIE_xt_ioports_RUR_EXPSTATE)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_EXPSTATE(v) \
	CSTUB_(_TIE_xt_ioports_WUR_EXPSTATE)(v)
#else
#define WUR_EXPSTATE(v) \
	CSTUB_(_TIE_xt_ioports_WUR_EXPSTATE)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_PERM(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_PERM)(a, b, c)
#else
#define st_PERM(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_PERM)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_PERM(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_PERM)(b, c)
#else
#define ld_PERM(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_PERM)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_ULSR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_ULSR)(a, b, c)
#else
#define st_ULSR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_ULSR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_ULSR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_ULSR)(b, c)
#else
#define ld_ULSR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_ULSR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_MIR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_MIR)(a, b, c)
#else
#define st_MIR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_MIR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_MIR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_MIR)(b, c)
#else
#define ld_MIR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_MIR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_CR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_CR)(a, b, c)
#else
#define st_CR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_CR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_CR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_CR)(b, c)
#else
#define ld_CR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_CR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_WR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_WR)(a, b, c)
#else
#define st_WR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_WR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_WR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_WR)(b, c)
#else
#define ld_WR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_WR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR)((unsigned *)(ptr), ofst)
#else
#define load32x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR)((unsigned *)(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI)((unsigned *)(ptr), ofst2)
#else
#define load32x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI)((unsigned *)(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR)(z, (const unsigned int **)&(ptr), ofst)
#else
#define load32x4_vr_postR(z, ptr, ofst) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR)(__z, (const unsigned int **)&(ptr), ofst); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI)(z, (const unsigned int **)&(ptr), ofst2)
#else
#define load32x4_vr_postI(z, ptr, ofst2) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c)
#else
#define load32x4_vr_circI(z, ptr, ofst1, c) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#else
#define load32x2_vr_idxR(z, ptr, ofst, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR)(__z,(unsigned *)( ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#else
#define load32x2_vr_idxI(z, ptr, ofst2, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI)(__z,(unsigned *)( ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel1)
#else
#define load32x2_vr_postR(z, ptr, ofst, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel1)
#else
#define load32x2_vr_postI(z, ptr, ofst2, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define load32x2_vr_circI(z, ptr, ofst1, c, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#else
#define load32x1_vr_idxR(z, ptr, ofst, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR)(__z,(unsigned *)( ptr), ofst, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#else
#define load32x1_vr_idxI(z, ptr, ofst2, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI)(__z,(unsigned *)( ptr), ofst2, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel2)
#else
#define load32x1_vr_postR(z, ptr, ofst, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel2)
#else
#define load32x1_vr_postI(z, ptr, ofst2, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel2)
#else
#define load32x1_vr_circI(z, ptr, ofst1, c, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#else
#define load32x4_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#else
#define load32x4_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_postR_perm_vr(r, z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst, perm)
#else
#define load32x4_vr_postR_perm_vr(r, z, ptr, ofst, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst2, perm)
#else
#define load32x4_vr_postI_perm_vr(r, z, ptr, ofst2, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst2, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x4_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst1, c, perm)
#else
#define load32x4_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst1, c, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#else
#define load32x2_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#else
#define load32x2_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postR_perm_vr(r, z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst, perm)
#else
#define load32x2_vr_postR_perm_vr(r, z, ptr, ofst, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst2, perm)
#else
#define load32x2_vr_postI_perm_vr(r, z, ptr, ofst2, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst2, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst1, c, perm)
#else
#define load32x2_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst1, c, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#else
#define load32x1_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#else
#define load32x1_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postR_perm_vr(r, z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst, perm)
#else
#define load32x1_vr_postR_perm_vr(r, z, ptr, ofst, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst2, perm)
#else
#define load32x1_vr_postI_perm_vr(r, z, ptr, ofst2, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst2, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst1, c, perm)
#else
#define load32x1_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) { \
	vr128 __r; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst1, c, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_perm16(perm) \
	CSTUB_(_TIE_dmx1a_common_tie_set_perm16)(perm)
#else
#define set_perm16(perm) \
	CSTUB_(_TIE_dmx1a_common_tie_set_perm16)(perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define set_perm16_cond(z, perm, bx) \
	CSTUB_(_TIE_dmx1a_common_tie_set_perm16_cond)(z, perm, bx)
#else
#define set_perm16_cond(z, perm, bx) { \
	perm16 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_set_perm16_cond)(__z, perm, bx); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxR)((unsigned *)(ptr), ofst)
#else
#define load16x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxR)((unsigned *)(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxI)((unsigned *)(ptr), ofst2)
#else
#define load16x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxI)((unsigned *)(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postR)(z, (const unsigned int **)&(ptr), ofst)
#else
#define load16x4_vr_postR(z, ptr, ofst) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postR)(__z, (const unsigned int **)&(ptr), ofst); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postI)(z, (const unsigned int **)&(ptr), ofst2)
#else
#define load16x4_vr_postI(z, ptr, ofst2) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c)
#else
#define load16x4_vr_circI(z, ptr, ofst1, c) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#else
#define load16x2_vr_idxR(z, ptr, ofst, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxR)(__z,(unsigned *)( ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#else
#define load16x2_vr_idxI(z, ptr, ofst2, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxI)(__z,(unsigned *)( ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel1)
#else
#define load16x2_vr_postR(z, ptr, ofst, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel1)
#else
#define load16x2_vr_postI(z, ptr, ofst2, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define load16x2_vr_circI(z, ptr, ofst1, c, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#else
#define load16x1_vr_idxR(z, ptr, ofst, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxR)(__z,(unsigned *)( ptr), ofst, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#else
#define load16x1_vr_idxI(z, ptr, ofst2, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxI)(__z,(unsigned *)( ptr), ofst2, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel2)
#else
#define load16x1_vr_postR(z, ptr, ofst, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel2)
#else
#define load16x1_vr_postI(z, ptr, ofst2, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel2)
#else
#define load16x1_vr_circI(z, ptr, ofst1, c, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxR)((unsigned *)(ptr), ofst)
#else
#define load8x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxR)((unsigned *)(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxI)((unsigned *)(ptr), ofst2)
#else
#define load8x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxI)((unsigned *)(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postR)(z, (const unsigned int **)&(ptr), ofst)
#else
#define load8x4_vr_postR(z, ptr, ofst) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postR)(__z, (const unsigned int **)&(ptr), ofst); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postI)(z, (const unsigned int **)&(ptr), ofst2)
#else
#define load8x4_vr_postI(z, ptr, ofst2) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c)
#else
#define load8x4_vr_circI(z, ptr, ofst1, c) { \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#else
#define load8x2_vr_idxR(z, ptr, ofst, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxR)(__z,(unsigned *)( ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#else
#define load8x2_vr_idxI(z, ptr, ofst2, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxI)(__z,(unsigned *)( ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel1)
#else
#define load8x2_vr_postR(z, ptr, ofst, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel1)
#else
#define load8x2_vr_postI(z, ptr, ofst2, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define load8x2_vr_circI(z, ptr, ofst1, c, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxR)(z, ptr, ofst, sel2)
#else
#define load8x1_vr_idxR(z, ptr, ofst, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxR)(__z, ptr, ofst, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#else
#define load8x1_vr_idxI(z, ptr, ofst2, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxI)(__z,(unsigned *)( ptr), ofst2, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel2)
#else
#define load8x1_vr_postR(z, ptr, ofst, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel2)
#else
#define load8x1_vr_postI(z, ptr, ofst2, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel2)
#else
#define load8x1_vr_circI(z, ptr, ofst1, c, sel2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define align_32x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_32x4_load)((unsigned *)(ptr))
#else
#define align_32x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_32x4_load)((unsigned *)(ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define align_24x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_24x4_load)((unsigned *)(ptr))
#else
#define align_24x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_24x4_load)((unsigned *)(ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define align_16x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_16x4_load)((unsigned *)(ptr))
#else
#define align_16x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_16x4_load)((unsigned *)(ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define align_8x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_8x4_load)((unsigned *)(ptr))
#else
#define align_8x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_8x4_load)((unsigned *)(ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define load_32x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a)(z, buf, (const unsigned int **)&(ptr))
#else
#define load_32x4_vr_a(z, buf, ptr) { \
	vr128 __z; \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a)(__z, __buf, (const unsigned int **)&(ptr)); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_24x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_24x4_vr_a)(z, buf, (const unsigned int **)&(ptr))
#else
#define load_24x4_vr_a(z, buf, ptr) { \
	vr128 __z; \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_load_24x4_vr_a)(__z, __buf, (const unsigned int **)&(ptr)); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_16x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_16x4_vr_a)(z, buf, (const unsigned int **)&(ptr))
#else
#define load_16x4_vr_a(z, buf, ptr) { \
	vr128 __z; \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_load_16x4_vr_a)(__z, __buf, (const unsigned int **)&(ptr)); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_8x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_8x4_vr_a)(z, buf, (const unsigned int **)&(ptr))
#else
#define load_8x4_vr_a(z, buf, ptr) { \
	vr128 __z; \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_load_8x4_vr_a)(__z, __buf, (const unsigned int **)&(ptr)); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_32x4_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_circ)(z, buf, (const unsigned int **)&(ptr), c)
#else
#define load_32x4_vr_a_circ(z, buf, ptr, c) { \
	vr128 __z; \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_circ)(__z, __buf, (const unsigned int **)&(ptr), c); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_wr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxR)((unsigned *)(ptr), ofst)
#else
#define load32x2_wr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxR)((unsigned *)(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_wr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxI)((unsigned *)(ptr), ofst2)
#else
#define load32x2_wr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxI)((unsigned *)(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_wr_postR(w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postR)(w, (const unsigned int **)&(ptr), ofst)
#else
#define load32x2_wr_postR(w, ptr, ofst) { \
	wr64 __w; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postR)(__w, (const unsigned int **)&(ptr), ofst); \
	(w) = __w; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_wr_postI(w, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postI)(w, (const unsigned int **)&(ptr), ofst2)
#else
#define load32x2_wr_postI(w, ptr, ofst2) { \
	wr64 __w; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postI)(__w, (const unsigned int **)&(ptr), ofst2); \
	(w) = __w; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#else
#define store32x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#else
#define store32x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#else
#define store32x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#else
#define store32x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#else
#define store32x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#else
#define store32x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#else
#define store32x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store32x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store32x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store32x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#else
#define store32x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#else
#define store32x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#else
#define store32x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#else
#define store32x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#else
#define store32x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_br_idxR(z, bx4, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxR)(z, bx4, ptr, ofst)
#else
#define store32x4_vr_br_idxR(z, bx4, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxR)(z, bx4, ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_br_idxI(z, bx4, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxI)(z, bx4, ptr, ofst2)
#else
#define store32x4_vr_br_idxI(z, bx4, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxI)(z, bx4, ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_br_postR(z, bx4, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postR)(z, bx4, (unsigned int **)&(ptr), ofst)
#else
#define store32x4_vr_br_postR(z, bx4, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postR)(z, bx4, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_br_postI(z, bx4, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postI)(z, bx4, (unsigned int **)&(ptr), ofst2)
#else
#define store32x4_vr_br_postI(z, bx4, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postI)(z, bx4, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_br_circI(z, bx4, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_circI)(z, bx4, (unsigned int **)&(ptr), ofst1, c)
#else
#define store32x4_vr_br_circI(z, bx4, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_circI)(z, bx4, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_idxR(z, bx2, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxR)(z, bx2, ptr, ofst, sel1)
#else
#define store32x2_vr_br_idxR(z, bx2, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxR)(z, bx2, ptr, ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_idxI(z, bx2, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxI)(z, bx2, ptr, ofst2, sel1)
#else
#define store32x2_vr_br_idxI(z, bx2, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxI)(z, bx2, ptr, ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_postR(z, bx2, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postR)(z, bx2, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store32x2_vr_br_postR(z, bx2, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postR)(z, bx2, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_postI(z, bx2, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postI)(z, bx2, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store32x2_vr_br_postI(z, bx2, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postI)(z, bx2, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_circI(z, bx2, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_circI)(z, bx2, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store32x2_vr_br_circI(z, bx2, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_circI)(z, bx2, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_idxR(z, bx, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxR)(z, bx, ptr, ofst, sel2)
#else
#define store32x1_vr_br_idxR(z, bx, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxR)(z, bx, ptr, ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_idxI(z, bx, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxI)(z, bx, ptr, ofst2, sel2)
#else
#define store32x1_vr_br_idxI(z, bx, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxI)(z, bx, ptr, ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_postR(z, bx, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postR)(z, bx, (unsigned int **)&(ptr), ofst, sel2)
#else
#define store32x1_vr_br_postR(z, bx, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postR)(z, bx, (unsigned int **)&(ptr), ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_postI(z, bx, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postI)(z, bx, (unsigned int **)&(ptr), ofst2, sel2)
#else
#define store32x1_vr_br_postI(z, bx, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postI)(z, bx, (unsigned int **)&(ptr), ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_circI(z, bx, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_circI)(z, bx, (unsigned int **)&(ptr), ofst1, c, sel2)
#else
#define store32x1_vr_br_circI(z, bx, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_circI)(z, bx, (unsigned int **)&(ptr), ofst1, c, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_vr_idxR_perm(z, y, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm)(z, y,(unsigned *)( ptr), ofst, perm)
#else
#define store32x4_vr_vr_idxR_perm(z, y, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm)(z, y,(unsigned *)( ptr), ofst, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_vr_idxI_perm(z, y, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm)(z, y,(unsigned *)( ptr), ofst2, perm)
#else
#define store32x4_vr_vr_idxI_perm(z, y, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm)(z, y,(unsigned *)( ptr), ofst2, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_vr_postR_perm(z, y, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm)(z, y, (unsigned int **)&(ptr), ofst, perm)
#else
#define store32x4_vr_vr_postR_perm(z, y, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm)(z, y, (unsigned int **)&(ptr), ofst, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_vr_postI_perm(z, y, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm)(z, y, (unsigned int **)&(ptr), ofst2, perm)
#else
#define store32x4_vr_vr_postI_perm(z, y, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm)(z, y, (unsigned int **)&(ptr), ofst2, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x4_vr_vr_circI_perm(z, y, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm)(z, y, (unsigned int **)&(ptr), ofst1, c, perm)
#else
#define store32x4_vr_vr_circI_perm(z, y, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm)(z, y, (unsigned int **)&(ptr), ofst1, c, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#else
#define store16x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#else
#define store16x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#else
#define store16x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#else
#define store16x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#else
#define store16x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#else
#define store16x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#else
#define store16x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store16x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store16x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store16x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#else
#define store16x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#else
#define store16x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#else
#define store16x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#else
#define store16x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#else
#define store16x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#else
#define store8x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#else
#define store8x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#else
#define store8x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#else
#define store8x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#else
#define store8x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#else
#define store8x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#else
#define store8x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store8x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store8x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store8x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxR)(z, ptr, ofst, sel2)
#else
#define store8x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxR)(z, ptr, ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#else
#define store8x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#else
#define store8x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#else
#define store8x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#else
#define store8x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define align_32x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_32x4_store)((unsigned *)(ptr))
#else
#define align_32x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_32x4_store)((unsigned *)(ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define align_16x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_16x4_store)((unsigned *)(ptr))
#else
#define align_16x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_16x4_store)((unsigned *)(ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define align_8x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_8x4_store)((unsigned *)(ptr))
#else
#define align_8x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_8x4_store)((unsigned *)(ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define store_32x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a)(z, buf, (unsigned int **)&(ptr))
#else
#define store_32x4_vr_a(z, buf, ptr) { \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a)(z, __buf, (unsigned int **)&(ptr)); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_24x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_24x4_vr_a)(z, buf, (unsigned int **)&(ptr))
#else
#define store_24x4_vr_a(z, buf, ptr) { \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_store_24x4_vr_a)(z, __buf, (unsigned int **)&(ptr)); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_16x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_16x4_vr_a)(z, buf, (unsigned int **)&(ptr))
#else
#define store_16x4_vr_a(z, buf, ptr) { \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_store_16x4_vr_a)(z, __buf, (unsigned int **)&(ptr)); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_8x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_8x4_vr_a)(z, buf, (unsigned int **)&(ptr))
#else
#define store_8x4_vr_a(z, buf, ptr) { \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_store_8x4_vr_a)(z, __buf, (unsigned int **)&(ptr)); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_32x4_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_circ)(z, buf, (unsigned int **)&(ptr), c)
#else
#define store_32x4_vr_a_circ(z, buf, ptr, c) { \
	ulsr128 __buf = buf; \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_circ)(z, __buf, (unsigned int **)&(ptr), c); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define flush_32x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_32x4)(buf,(unsigned *)( ptr))
#else
#define flush_32x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_32x4)(buf,(unsigned *)( ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define flush_24x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_24x4)(buf,(unsigned *)( ptr))
#else
#define flush_24x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_24x4)(buf,(unsigned *)( ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define flush_16x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_16x4)(buf,(unsigned *)( ptr))
#else
#define flush_16x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_16x4)(buf,(unsigned *)( ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define flush_8x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_8x4)(buf,(unsigned *)( ptr))
#else
#define flush_8x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_8x4)(buf,(unsigned *)( ptr))
#endif

#ifdef _STRICT_ARG_TYPE
#define br_get_idx_2_5(ar32x, four, odd) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_2_5)(ar32x, four, odd)
#else
#define br_get_idx_2_5(ar32x, four, odd) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_2_5)(ar32x, four, odd)
#endif

#ifdef _STRICT_ARG_TYPE
#define br_get_idx_6_13(ar32x, idx_spec, ext_size, odd) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_6_13)(ar32x, idx_spec, ext_size, odd)
#else
#define br_get_idx_6_13(ar32x, idx_spec, ext_size, odd) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_6_13)(ar32x, idx_spec, ext_size, odd)
#endif

#ifdef _STRICT_ARG_TYPE
#define br_get_idx_next_odd(ar32x, nbits) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_next_odd)(ar32x, nbits)
#else
#define br_get_idx_next_odd(ar32x, nbits) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_next_odd)(ar32x, nbits)
#endif

#ifdef _STRICT_ARG_TYPE
#define br_upd_idx_spec(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_br_upd_idx_spec)(ar32x)
#else
#define br_upd_idx_spec(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_br_upd_idx_spec)(ar32x)
#endif

#ifdef _STRICT_ARG_TYPE
#define build_palindrome(ar32x, nbits, odd, shift_type) \
	CSTUB_(_TIE_dmx1a_common_tie_build_palindrome)(ar32x, nbits, odd, shift_type)
#else
#define build_palindrome(ar32x, nbits, odd, shift_type) \
	CSTUB_(_TIE_dmx1a_common_tie_build_palindrome)(ar32x, nbits, odd, shift_type)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_vr_bdir(ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_load_vr_bdir)((unsigned *)(ptr), ofst, br_len, msb)
#else
#define load_vr_bdir(ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_load_vr_bdir)((unsigned *)(ptr), ofst, br_len, msb)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_vr_brev(ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_load_vr_brev)((unsigned *)(ptr), ofst, br_len, msb)
#else
#define load_vr_brev(ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_load_vr_brev)((unsigned *)(ptr), ofst, br_len, msb)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrl_wr_bdir(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_bdir)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#else
#define store_vrl_wr_bdir(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_bdir)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrh_wr_bdir(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_bdir)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#else
#define store_vrh_wr_bdir(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_bdir)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrl_wr_brev(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_brev)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#else
#define store_vrl_wr_brev(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_brev)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrh_wr_brev(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_brev)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#else
#define store_vrh_wr_brev(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_brev)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrl_vrl_postR(z, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_vrl_postR)(z, y, (unsigned int **)&(ptr), ofst)
#else
#define store_vrl_vrl_postR(z, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_vrl_postR)(z, y, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrh_vrh_postR(z, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_vrh_postR)(z, y, (unsigned int **)&(ptr), ofst)
#else
#define store_vrh_vrh_postR(z, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_vrh_postR)(z, y, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrl_wr_postR(z, w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_postR)(z, w, (unsigned int **)&(ptr), ofst)
#else
#define store_vrl_wr_postR(z, w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_postR)(z, w, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_wr_vrl_postR(w, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrl_postR)(w, y, (unsigned int **)&(ptr), ofst)
#else
#define store_wr_vrl_postR(w, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrl_postR)(w, y, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_vrh_wr_postR(z, w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_postR)(z, w, (unsigned int **)&(ptr), ofst)
#else
#define store_vrh_wr_postR(z, w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_postR)(z, w, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_wr_vrh_postR(w, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrh_postR)(w, y, (unsigned int **)&(ptr), ofst)
#else
#define store_wr_vrh_postR(w, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrh_postR)(w, y, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_fr_postI)(fx, (const unsigned int **)&(ptr), ofst2)
#else
#define load_fr_postI(fx, ptr, ofst2) { \
	fr32 __fx; \
	CSTUB_(_TIE_dmx1a_common_tie_load_fr_postI)(__fx, (const unsigned int **)&(ptr), ofst2); \
	(fx) = __fx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_fr_postI)(fx, (unsigned int **)&(ptr), ofst2)
#else
#define store_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_fr_postI)(fx, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_wr_vr(x, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_wr_vr)(x, sel2)
#else
#define move32_wr_vr(x, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_wr_vr)(x, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_wr_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_wr_fr)(fx)
#else
#define move32_wr_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_wr_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define move64_wr_vr(x, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_move64_wr_vr)(x, sel1)
#else
#define move64_wr_vr(x, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_move64_wr_vr)(x, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define move64_vr_wr(z, w, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_move64_vr_wr)(z, w, sel1)
#else
#define move64_vr_wr(z, w, sel1) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move64_vr_wr)(__z, w, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_ar_vr(x, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr)(x, sel2)
#else
#define move32_ar_vr(x, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr)(x, sel2)
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_ar_vr_idx(x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr_idx)(x, idx)
#else
#define move32_ar_vr_idx(x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr_idx)(x, idx)
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_fr_vr_idx(x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_fr_vr_idx)(x, idx)
#else
#define move32_fr_vr_idx(x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_fr_vr_idx)(x, idx)
#endif

#ifdef _STRICT_ARG_TYPE
#define int_to_xt_bool(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool)(ar32x)
#else
#define int_to_xt_bool(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool)(ar32x)
#endif

#ifdef _STRICT_ARG_TYPE
#define int_to_xt_bool2(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool2)(ar32x)
#else
#define int_to_xt_bool2(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool2)(ar32x)
#endif

#ifdef _STRICT_ARG_TYPE
#define int_to_xt_bool4(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool4)(ar32x)
#else
#define int_to_xt_bool4(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool4)(ar32x)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_vr_eqz(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_eqz)(z, el_z, x, el_x, y, el_y)
#else
#define move_vr_eqz(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_eqz)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_vr_gez(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_gez)(z, el_z, x, el_x, y, el_y)
#else
#define move_vr_gez(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_gez)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_vr_gtz(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_gtz)(z, el_z, x, el_x, y, el_y)
#else
#define move_vr_gtz(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_gtz)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_vr_lez(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_lez)(z, el_z, x, el_x, y, el_y)
#else
#define move_vr_lez(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_lez)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_vr_ltz(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_ltz)(z, el_z, x, el_x, y, el_y)
#else
#define move_vr_ltz(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_ltz)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_vr_nez(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_nez)(z, el_z, x, el_x, y, el_y)
#else
#define move_vr_nez(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_nez)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_vr_sat(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_sat)(z, el_z, x, el_x, y, el_y)
#else
#define move_vr_sat(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_sat)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_eqz(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_eqz)(z, x, y)
#else
#define vmove_vr_eqz(z, x, y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_eqz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_gez(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gez)(z, x, y)
#else
#define vmove_vr_gez(z, x, y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_gtz(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gtz)(z, x, y)
#else
#define vmove_vr_gtz(z, x, y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gtz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_lez(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_lez)(z, x, y)
#else
#define vmove_vr_lez(z, x, y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_lez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_ltz(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_ltz)(z, x, y)
#else
#define vmove_vr_ltz(z, x, y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_ltz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_nez(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_nez)(z, x, y)
#else
#define vmove_vr_nez(z, x, y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_nez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_sat(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_sat)(z, x, y)
#else
#define vmove_vr_sat(z, x, y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_sat)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define replicate(z, sel_code, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_replicate)(z, sel_code, x, el_x)
#else
#define replicate(z, sel_code, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_replicate)(__z, sel_code, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define replicate_ar(z, sel_code, ar) \
	CSTUB_(_TIE_dmx1a_common_tie_replicate_ar)(z, sel_code, ar)
#else
#define replicate_ar(z, sel_code, ar) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_replicate_ar)(__z, sel_code, ar); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define creplicate_H(x) \
	CSTUB_(_TIE_dmx1a_common_tie_creplicate_H)(x)
#else
#define creplicate_H(x) \
	CSTUB_(_TIE_dmx1a_common_tie_creplicate_H)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define creplicate_L(x) \
	CSTUB_(_TIE_dmx1a_common_tie_creplicate_L)(x)
#else
#define creplicate_L(x) \
	CSTUB_(_TIE_dmx1a_common_tie_creplicate_L)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vreplicate(x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate)(x, el_x)
#else
#define vreplicate(x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate)(x, el_x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vreplicate_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate_fr)(fx)
#else
#define vreplicate_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define vreplicate_hr(hx) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate_hr)(hx)
#else
#define vreplicate_hr(hx) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate_hr)(hx)
#endif

#ifdef _STRICT_ARG_TYPE
#define hreplicate_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_hreplicate_fr)(fx)
#else
#define hreplicate_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_hreplicate_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x1)(z, exp_fxp, el)
#else
#define convert_16I_to_32F_x1(z, exp_fxp, el) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x1)(__z, exp_fxp, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16I_to_32F_x2(z, exp_fxp, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x2)(z, exp_fxp, half)
#else
#define convert_16I_to_32F_x2(z, exp_fxp, half) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x2)(__z, exp_fxp, half); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16I_to_32F_x4(z, exp_fxp) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x4)(z, exp_fxp)
#else
#define convert_16I_to_32F_x4(z, exp_fxp) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x4)(__z, exp_fxp); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x1)(z, exp_fxp, rnd, el)
#else
#define convert_32F_to_16I_x1(z, exp_fxp, rnd, el) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x1)(__z, exp_fxp, rnd, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16I_x2(z, exp_fxp, rnd, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x2)(z, exp_fxp, rnd, half)
#else
#define convert_32F_to_16I_x2(z, exp_fxp, rnd, half) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x2)(__z, exp_fxp, rnd, half); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16I_x4(z, exp_fxp, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x4)(z, exp_fxp, rnd)
#else
#define convert_32F_to_16I_x4(z, exp_fxp, rnd) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x4)(__z, exp_fxp, rnd); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16F_x1(z, is_signed, exp_bits, bias, round, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x1)(z, is_signed, exp_bits, bias, round, el)
#else
#define convert_32F_to_16F_x1(z, is_signed, exp_bits, bias, round, el) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x1)(__z, is_signed, exp_bits, bias, round, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16F_x2(z, is_signed, exp_bits, bias, round, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x2)(z, is_signed, exp_bits, bias, round, half)
#else
#define convert_32F_to_16F_x2(z, is_signed, exp_bits, bias, round, half) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x2)(__z, is_signed, exp_bits, bias, round, half); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16F_x4(z, is_signed, exp_bits, bias, round) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x4)(z, is_signed, exp_bits, bias, round)
#else
#define convert_32F_to_16F_x4(z, is_signed, exp_bits, bias, round) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x4)(__z, is_signed, exp_bits, bias, round); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16F_to_32F_x1(z, is_signed, exp_bits, bias, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x1)(z, is_signed, exp_bits, bias, el)
#else
#define convert_16F_to_32F_x1(z, is_signed, exp_bits, bias, el) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x1)(__z, is_signed, exp_bits, bias, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16F_to_32F_x2(z, is_signed, exp_bits, bias, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x2)(z, is_signed, exp_bits, bias, half)
#else
#define convert_16F_to_32F_x2(z, is_signed, exp_bits, bias, half) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x2)(__z, is_signed, exp_bits, bias, half); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16F_to_32F_x4(z, is_signed, exp_bits, bias) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x4)(z, is_signed, exp_bits, bias)
#else
#define convert_16F_to_32F_x4(z, is_signed, exp_bits, bias) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x4)(__z, is_signed, exp_bits, bias); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_32F_x1)(z, exp_fxp, el)
#else
#define convert_32I_to_32F_x1(z, exp_fxp, el) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_32F_x1)(__z, exp_fxp, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_32I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_32I_x1)(z, exp_fxp, rnd, el)
#else
#define convert_32F_to_32I_x1(z, exp_fxp, rnd, el) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_32I_x1)(__z, exp_fxp, rnd, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_IEEE_float_to_32F_x4(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4)(z)
#else
#define convert_IEEE_float_to_32F_x4(z) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_IEEE_float_x4(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4)(z)
#else
#define convert_32F_to_IEEE_float_x4(z) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_IEEE_float_to_32F(ar) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F)(ar)
#else
#define convert_IEEE_float_to_32F(ar) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F)(ar)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_IEEE_float(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float)(fx)
#else
#define convert_32F_to_IEEE_float(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32I_to_64F(x) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_64F)(x)
#else
#define convert_32I_to_64F(x) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_64F)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_64F_to_32I(x, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32I)(x, rnd)
#else
#define convert_64F_to_32I(x, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32I)(x, rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_64F(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_64F)(fx)
#else
#define convert_32F_to_64F(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_64F)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_64F_to_32F(x) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32F)(x)
#else
#define convert_64F_to_32F(x) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32F)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_IEEE_double_to_64F(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_double_to_64F)(z)
#else
#define convert_IEEE_double_to_64F(z) { \
	vr64 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_double_to_64F)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_64F_to_IEEE_double(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_IEEE_double)(z)
#else
#define convert_64F_to_IEEE_double(z) { \
	vr64 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_IEEE_double)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define affine_adj_L(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_adj_L)(z, x, y, signs6, boost)
#else
#define affine_adj_L(z, x, y, signs6, boost) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_affine_adj_L)(__z, x, y, signs6, boost); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define affine_adj_H(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_adj_H)(z, x, y, signs6, boost)
#else
#define affine_adj_H(z, x, y, signs6, boost) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_affine_adj_H)(__z, x, y, signs6, boost); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define affine_perm_L(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_perm_L)(z, x, y, signs6, perm)
#else
#define affine_perm_L(z, x, y, signs6, perm) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_affine_perm_L)(__z, x, y, signs6, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define affine_perm_H(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_perm_H)(z, x, y, signs6, perm)
#else
#define affine_perm_H(z, x, y, signs6, perm) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_affine_perm_H)(__z, x, y, signs6, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define linear_adj_L(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_adj_L)(z, x, y, signs6, boost)
#else
#define linear_adj_L(z, x, y, signs6, boost) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_linear_adj_L)(__z, x, y, signs6, boost); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define linear_adj_H(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_adj_H)(z, x, y, signs6, boost)
#else
#define linear_adj_H(z, x, y, signs6, boost) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_linear_adj_H)(__z, x, y, signs6, boost); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define linear_perm_L(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_perm_L)(z, x, y, signs6, perm)
#else
#define linear_perm_L(z, x, y, signs6, perm) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_linear_perm_L)(__z, x, y, signs6, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define linear_perm_H(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_perm_H)(z, x, y, signs6, perm)
#else
#define linear_perm_H(z, x, y, signs6, perm) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_linear_perm_H)(__z, x, y, signs6, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_yl_xl_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xl_wr)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_yl_xl_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xl_wr)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_yl_xh_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xh_wr)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_yl_xh_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xh_wr)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_yh_xl_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xl_wr)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_yh_xl_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xl_wr)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_yh_xh_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xh_wr)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_yh_xh_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xh_wr)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_wr_xl_yl(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yl)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_wr_xl_yl(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yl)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_wr_xh_yl(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yl)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_wr_xh_yl(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yl)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_wr_xl_yh(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yh)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_wr_xl_yh(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yh)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_z_wr_xh_yh(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yh)(w, x, y, inv, conjX_swap)
#else
#define bfly_z_wr_xh_yh(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yh)(w, x, y, inv, conjX_swap)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_zl_zl_xl_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_zl_zl_xl_yl(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_zl_zl_xh_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_zl_zl_xh_yl(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_zh_zh_xl_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_zh_zh_xl_yh(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_zh_zh_xh_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_zh_zh_xh_yh(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_wr_zl_xl_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_wr_zl_xl_yl(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_wr_zl_xh_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_wr_zl_xh_yl(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_wr_zh_xl_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_wr_zh_xl_yh(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define bfly_wr_zh_xh_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh)(z, w1, x, y, inv, conjX_swap)
#else
#define bfly_wr_zh_xh_yh(z, w1, x, y, inv, conjX_swap) { \
	vr128 __z = z; \
	wr64 __w1; \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh)(__z, __w1, x, y, inv, conjX_swap); \
	(z) = __z; \
	(w1) = __w1; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cmul(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul)(hx, hy)
#else
#define cmul(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul)(hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmul_conj(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_conj)(hx, hy)
#else
#define cmul_conj(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_conj)(hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac)(hz, hx, hy)
#else
#define cmac(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac)(hz, hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac_conj(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_conj)(hz, hx, hy)
#else
#define cmac_conj(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_conj)(hz, hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmas(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas)(hz, hx, hy)
#else
#define cmas(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas)(hz, hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmas_conj(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_conj)(hz, hx, hy)
#else
#define cmas_conj(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_conj)(hz, hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmul_L(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_L)(z, x, y, mode)
#else
#define cmul_L(z, x, y, mode) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_L)(__z, x, y, mode); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cmul_H(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_H)(z, x, y, mode)
#else
#define cmul_H(z, x, y, mode) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_H)(__z, x, y, mode); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac_L(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_L)(z, x, y, mode)
#else
#define cmac_L(z, x, y, mode) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_L)(__z, x, y, mode); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac_H(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_H)(z, x, y, mode)
#else
#define cmac_H(z, x, y, mode) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_H)(__z, x, y, mode); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cmas_L(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_L)(z, x, y, mode)
#else
#define cmas_L(z, x, y, mode) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_L)(__z, x, y, mode); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cmas_H(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_H)(z, x, y, mode)
#else
#define cmas_H(z, x, y, mode) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_H)(__z, x, y, mode); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac_Lx2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_Lx2)(z, x, y, mode)
#else
#define cmac_Lx2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_Lx2)(z, x, y, mode)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac_Hx2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_Hx2)(z, x, y, mode)
#else
#define cmac_Hx2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_Hx2)(z, x, y, mode)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmul_x2(x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_x2)(x, y, mode)
#else
#define cmul_x2(x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_x2)(x, y, mode)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac_adj_x2(z, x, y, mode, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_adj_x2)(z, x, y, mode, boost)
#else
#define cmac_adj_x2(z, x, y, mode, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_adj_x2)(z, x, y, mode, boost)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmas_adj_x2(z, x, y, mode, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_adj_x2)(z, x, y, mode, boost)
#else
#define cmas_adj_x2(z, x, y, mode, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_adj_x2)(z, x, y, mode, boost)
#endif

#ifdef _STRICT_ARG_TYPE
#define xcorr(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_xcorr)(z, x, y)
#else
#define xcorr(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_xcorr)(z, x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define xconv(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_xconv)(z, x, y)
#else
#define xconv(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_xconv)(z, x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define qmul_1(x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_qmul_1)(x, y, mode)
#else
#define qmul_1(x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_qmul_1)(x, y, mode)
#endif

#ifdef _STRICT_ARG_TYPE
#define qmul_2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_qmul_2)(z, x, y, mode)
#else
#define qmul_2(z, x, y, mode) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_qmul_2)(__z, x, y, mode); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define matmul_2x2(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_matmul_2x2)(z, x, y)
#else
#define matmul_2x2(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_matmul_2x2)(z, x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vadds(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vadds)(x, y, signs8)
#else
#define vadds(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vadds)(x, y, signs8)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmidp(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vmidp)(x, y, signs8)
#else
#define vmidp(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vmidp)(x, y, signs8)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmuls(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vmuls)(x, y, signs8)
#else
#define vmuls(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vmuls)(x, y, signs8)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmacs_adj(z, x, y, signs8, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_vmacs_adj)(z, x, y, signs8, boost)
#else
#define vmacs_adj(z, x, y, signs8, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_vmacs_adj)(z, x, y, signs8, boost)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmuls_perm(x, y, signs8, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_vmuls_perm)(x, y, signs8, perm)
#else
#define vmuls_perm(x, y, signs8, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_vmuls_perm)(x, y, signs8, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmacs_perm(z, x, y, signs8, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_vmacs_perm)(z, x, y, signs8, perm)
#else
#define vmacs_perm(z, x, y, signs8, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_vmacs_perm)(z, x, y, signs8, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define vssub_L(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_L)(z, x, y, w)
#else
#define vssub_L(z, x, y, w) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_L)(__z, x, y, w); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vssub_H(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_H)(z, x, y, w)
#else
#define vssub_H(z, x, y, w) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_H)(__z, x, y, w); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vssub_x2(x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_x2)(x, y, w)
#else
#define vssub_x2(x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_x2)(x, y, w)
#endif

#ifdef _STRICT_ARG_TYPE
#define vinterp_L(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_L)(z, x, y, w)
#else
#define vinterp_L(z, x, y, w) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_L)(__z, x, y, w); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vinterp_H(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_H)(z, x, y, w)
#else
#define vinterp_H(z, x, y, w) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_H)(__z, x, y, w); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vinterp_x2(x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_x2)(x, y, w)
#else
#define vinterp_x2(x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_x2)(x, y, w)
#endif

#ifdef _STRICT_ARG_TYPE
#define csums_L(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_csums_L)(z, x, signs6, div_by_2_op)
#else
#define csums_L(z, x, signs6, div_by_2_op) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_csums_L)(__z, x, signs6, div_by_2_op); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define csums_H(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_csums_H)(z, x, signs6, div_by_2_op)
#else
#define csums_H(z, x, signs6, div_by_2_op) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_csums_H)(__z, x, signs6, div_by_2_op); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define dsums_L(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_dsums_L)(z, x, signs6, div_by_2_op)
#else
#define dsums_L(z, x, signs6, div_by_2_op) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_dsums_L)(__z, x, signs6, div_by_2_op); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define dsums_H(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_dsums_H)(z, x, signs6, div_by_2_op)
#else
#define dsums_H(z, x, signs6, div_by_2_op) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_dsums_H)(__z, x, signs6, div_by_2_op); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vadd_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vadd_hr)(hx, hy)
#else
#define vadd_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vadd_hr)(hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define vsub_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vsub_hr)(hx, hy)
#else
#define vsub_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vsub_hr)(hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmul_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vmul_hr)(hx, hy)
#else
#define vmul_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vmul_hr)(hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmac_hr(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vmac_hr)(hz, hx, hy)
#else
#define vmac_hr(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vmac_hr)(hz, hx, hy)
#endif

#ifdef _STRICT_ARG_TYPE
#define fpadd(fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpadd)(fx, fy, signs2)
#else
#define fpadd(fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpadd)(fx, fy, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define fpmul(fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmul)(fx, fy, signs2)
#else
#define fpmul(fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmul)(fx, fy, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define fpmac(fz, fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmac)(fz, fx, fy, signs2)
#else
#define fpmac(fz, fx, fy, signs2) { \
	fr32 __fz = fz; \
	CSTUB_(_TIE_dmx1a_common_tie_fpmac)(__fz, fx, fy, signs2); \
	(fz) = __fz; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fpmul_sum3(x, y, signs3, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmul_sum3)(x, y, signs3, perm)
#else
#define fpmul_sum3(x, y, signs3, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmul_sum3)(x, y, signs3, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define vscale(fx, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vscale)(fx, y)
#else
#define vscale(fx, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vscale)(fx, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vscale_adds(z, fx, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_vscale_adds)(z, fx, y, signs2)
#else
#define vscale_adds(z, fx, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_vscale_adds)(z, fx, y, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define fadds(z, el_z, x, el_x, y, el_y, signs5) \
	CSTUB_(_TIE_dmx1a_common_tie_fadds)(z, el_z, x, el_x, y, el_y, signs5)
#else
#define fadds(z, el_z, x, el_x, y, el_y, signs5) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fadds)(__z, el_z, x, el_x, y, el_y, signs5); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fmacs(z, el_z, x, el_x, y, el_y, signs5) \
	CSTUB_(_TIE_dmx1a_common_tie_fmacs)(z, el_z, x, el_x, y, el_y, signs5)
#else
#define fmacs(z, el_z, x, el_x, y, el_y, signs5) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fmacs)(__z, el_z, x, el_x, y, el_y, signs5); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fmuls(z, el_z, x, el_x, y, el_y, signs5) \
	CSTUB_(_TIE_dmx1a_common_tie_fmuls)(z, el_z, x, el_x, y, el_y, signs5)
#else
#define fmuls(z, el_z, x, el_x, y, el_y, signs5) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fmuls)(__z, el_z, x, el_x, y, el_y, signs5); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fmul_sum3(z, el_z, x, y, signs3, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_fmul_sum3)(z, el_z, x, y, signs3, perm)
#else
#define fmul_sum3(z, el_z, x, y, signs3, perm) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fmul_sum3)(__z, el_z, x, y, signs3, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define dadds(z, x, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dadds)(z, x, signs2)
#else
#define dadds(z, x, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dadds)(z, x, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define dmuls(x, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dmuls)(x, y, signs2)
#else
#define dmuls(x, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dmuls)(x, y, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define dmacs(z, x, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dmacs)(z, x, y, signs2)
#else
#define dmacs(z, x, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dmacs)(z, x, y, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define vabs(x) \
	CSTUB_(_TIE_dmx1a_common_tie_vabs)(x)
#else
#define vabs(x) \
	CSTUB_(_TIE_dmx1a_common_tie_vabs)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vexp_adj(x, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_vexp_adj)(x, exp_adj_ar)
#else
#define vexp_adj(x, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_vexp_adj)(x, exp_adj_ar)
#endif

#ifdef _STRICT_ARG_TYPE
#define vexp_adji(x, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_vexp_adji)(x, exp_adj_imm)
#else
#define vexp_adji(x, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_vexp_adji)(x, exp_adj_imm)
#endif

#ifdef _STRICT_ARG_TYPE
#define vperm(x, y, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_vperm)(x, y, sel)
#else
#define vperm(x, y, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_vperm)(x, y, sel)
#endif

#ifdef _STRICT_ARG_TYPE
#define vperms(x, y, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_vperms)(x, y, sel)
#else
#define vperms(x, y, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_vperms)(x, y, sel)
#endif

#ifdef _STRICT_ARG_TYPE
#define vpermsi(x, y, signs, sel3) \
	CSTUB_(_TIE_dmx1a_common_tie_vpermsi)(x, y, signs, sel3)
#else
#define vpermsi(x, y, signs, sel3) \
	CSTUB_(_TIE_dmx1a_common_tie_vpermsi)(x, y, signs, sel3)
#endif

#ifdef _STRICT_ARG_TYPE
#define seta_vr(z, sel_code, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_vr)(z, sel_code, const_idx, exp_adj_const, mul_rnd)
#else
#define seta_vr(z, sel_code, const_idx, exp_adj_const, mul_rnd) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_seta_vr)(__z, sel_code, const_idx, exp_adj_const, mul_rnd); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vseta_vr(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vseta_vr)(const_idx, exp_adj_const, mul_rnd)
#else
#define vseta_vr(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vseta_vr)(const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define seta_ar(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_ar)(const_idx, exp_adj_const, mul_rnd)
#else
#define seta_ar(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_ar)(const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define seta_fr(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_fr)(const_idx, exp_adj_const, mul_rnd)
#else
#define seta_fr(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_fr)(const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define f_abs(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_f_abs)(z, el_z, x, el_x)
#else
#define f_abs(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_f_abs)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fclamp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp)(z, el_z, x, el_x, y, el_y)
#else
#define fclamp(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fclamp_bp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp_bp)(z, el_z, x, el_x, y, el_y)
#else
#define fclamp_bp(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp_bp)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fclamp_one(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp_one)(z, el_z, x, el_x)
#else
#define fclamp_one(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp_one)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fmax(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fmax)(z, el_z, x, el_x, y, el_y)
#else
#define fmax(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fmax)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fmin(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fmin)(z, el_z, x, el_x, y, el_y)
#else
#define fmin(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_fmin)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define max_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_max_fr)(fx, fy)
#else
#define max_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_max_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define min_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_min_fr)(fx, fy)
#else
#define min_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_min_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define log2(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_log2)(z, el_z, x, el_x)
#else
#define log2(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_log2)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define pow2(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_pow2)(z, el_z, x, el_x)
#else
#define pow2(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_pow2)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sigmoid(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_sigmoid)(z, el_z, x, el_x)
#else
#define sigmoid(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sigmoid)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define inv(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_inv)(z, el_z, x, el_x)
#else
#define inv(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_inv)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define ratio(z, el_z, x, el_x, y, el_y, bz4) \
	CSTUB_(_TIE_dmx1a_common_tie_ratio)(z, el_z, x, el_x, y, el_y, bz4)
#else
#define ratio(z, el_z, x, el_x, y, el_y, bz4) { \
	vr128 __z = z; \
	xtbool4 __bz4; \
	CSTUB_(_TIE_dmx1a_common_tie_ratio)(__z, el_z, x, el_x, y, el_y, __bz4); \
	(z) = __z; \
	(bz4) = __bz4; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define atanratio(z, el_z, x, el_x, bx4) \
	CSTUB_(_TIE_dmx1a_common_tie_atanratio)(z, el_z, x, el_x, bx4)
#else
#define atanratio(z, el_z, x, el_x, bx4) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_atanratio)(__z, el_z, x, el_x, bx4); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define invsqrt(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_invsqrt)(z, el_z, x, el_x)
#else
#define invsqrt(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_invsqrt)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sine(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_sine)(z, el_z, x, el_x)
#else
#define sine(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sine)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cosine(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_cosine)(z, el_z, x, el_x)
#else
#define cosine(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cosine)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define log2mul(z, el_z, x, el_x, y, el_y, bz) \
	CSTUB_(_TIE_dmx1a_common_tie_log2mul)(z, el_z, x, el_x, y, el_y, bz)
#else
#define log2mul(z, el_z, x, el_x, y, el_y, bz) { \
	vr128 __z = z; \
	xtbool __bz; \
	CSTUB_(_TIE_dmx1a_common_tie_log2mul)(__z, el_z, x, el_x, y, el_y, __bz); \
	(z) = __z; \
	(bz) = __bz; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cspow2(z, el_z, x, el_x, bx) \
	CSTUB_(_TIE_dmx1a_common_tie_cspow2)(z, el_z, x, el_x, bx)
#else
#define cspow2(z, el_z, x, el_x, bx) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_cspow2)(__z, el_z, x, el_x, bx); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define log2_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_log2_fr)(fx)
#else
#define log2_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_log2_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define pow2_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_pow2_fr)(fx)
#else
#define pow2_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_pow2_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sigmoid_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_sigmoid_fr)(fx)
#else
#define sigmoid_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_sigmoid_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define inv_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_inv_fr)(fx)
#else
#define inv_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_inv_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define invsqrt_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_invsqrt_fr)(fx)
#else
#define invsqrt_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_invsqrt_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sine_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_sine_fr)(fx)
#else
#define sine_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_sine_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define cosine_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_cosine_fr)(fx)
#else
#define cosine_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_cosine_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define comp(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_comp)(x, el_x, y, el_y)
#else
#define comp(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_comp)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define eq(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_eq)(x, el_x, y, el_y)
#else
#define eq(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_eq)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define ge(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_ge)(x, el_x, y, el_y)
#else
#define ge(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_ge)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define gt(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_gt)(x, el_x, y, el_y)
#else
#define gt(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_gt)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define le(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_le)(x, el_x, y, el_y)
#else
#define le(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_le)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define lt(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_lt)(x, el_x, y, el_y)
#else
#define lt(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_lt)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define ne(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_ne)(x, el_x, y, el_y)
#else
#define ne(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_ne)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define comp_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_comp_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#else
#define comp_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_comp_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define eq_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_eq_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#else
#define eq_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_eq_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define ge_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_ge_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#else
#define ge_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_ge_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define gt_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_gt_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#else
#define gt_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_gt_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define le_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_le_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#else
#define le_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_le_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define lt_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_lt_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#else
#define lt_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_lt_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define ne_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_ne_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#else
#define ne_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_ne_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define eq_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_eq_fr)(fx, fy)
#else
#define eq_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_eq_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define ge_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_ge_fr)(fx, fy)
#else
#define ge_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_ge_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define gt_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_gt_fr)(fx, fy)
#else
#define gt_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_gt_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define le_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_le_fr)(fx, fy)
#else
#define le_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_le_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define lt_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_lt_fr)(fx, fy)
#else
#define lt_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_lt_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define ne_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_ne_fr)(fx, fy)
#else
#define ne_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_ne_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define neg_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_neg_fr)(fx)
#else
#define neg_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_neg_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define abs_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_abs_fr)(fx)
#else
#define abs_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_abs_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define deqz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_deqz)(x)
#else
#define deqz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_deqz)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dgez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dgez)(x)
#else
#define dgez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dgez)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dgtz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dgtz)(x)
#else
#define dgtz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dgtz)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dlez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dlez)(x)
#else
#define dlez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dlez)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dltz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dltz)(x)
#else
#define dltz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dltz)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dnez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dnez)(x)
#else
#define dnez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dnez)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define veq(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_veq)(x, y)
#else
#define veq(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_veq)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vge(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vge)(x, y)
#else
#define vge(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vge)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vgt(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vgt)(x, y)
#else
#define vgt(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vgt)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vle(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vle)(x, y)
#else
#define vle(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vle)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vlt(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vlt)(x, y)
#else
#define vlt(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vlt)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vne(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vne)(x, y)
#else
#define vne(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vne)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define veq_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_veq_const)(x, const_idx, exp_adj_const, mul_rnd)
#else
#define veq_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_veq_const)(x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define vge_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vge_const)(x, const_idx, exp_adj_const, mul_rnd)
#else
#define vge_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vge_const)(x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define vgt_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vgt_const)(x, const_idx, exp_adj_const, mul_rnd)
#else
#define vgt_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vgt_const)(x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define vle_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vle_const)(x, const_idx, exp_adj_const, mul_rnd)
#else
#define vle_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vle_const)(x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define vlt_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vlt_const)(x, const_idx, exp_adj_const, mul_rnd)
#else
#define vlt_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vlt_const)(x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define vne_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vne_const)(x, const_idx, exp_adj_const, mul_rnd)
#else
#define vne_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vne_const)(x, const_idx, exp_adj_const, mul_rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel(z, el_z, x, el_x, y, el_y, bx) \
	CSTUB_(_TIE_dmx1a_common_tie_sel)(z, el_z, x, el_x, y, el_y, bx)
#else
#define sel(z, el_z, x, el_x, y, el_y, bx) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel)(__z, el_z, x, el_x, y, el_y, bx); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_1b4(z, el_z, x, el_x, y, el_y, bx4, el_bx4) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_1b4)(z, el_z, x, el_x, y, el_y, bx4, el_bx4)
#else
#define sel_1b4(z, el_z, x, el_x, y, el_y, bx4, el_bx4) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel_1b4)(__z, el_z, x, el_x, y, el_y, bx4, el_bx4); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_eq(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_eq)(z, el_z, x, el_x, y, el_y, bx2)
#else
#define sel_eq(z, el_z, x, el_x, y, el_y, bx2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel_eq)(__z, el_z, x, el_x, y, el_y, bx2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_ge(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_ge)(z, el_z, x, el_x, y, el_y, bx2)
#else
#define sel_ge(z, el_z, x, el_x, y, el_y, bx2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel_ge)(__z, el_z, x, el_x, y, el_y, bx2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_gt(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_gt)(z, el_z, x, el_x, y, el_y, bx2)
#else
#define sel_gt(z, el_z, x, el_x, y, el_y, bx2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel_gt)(__z, el_z, x, el_x, y, el_y, bx2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_le(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_le)(z, el_z, x, el_x, y, el_y, bx2)
#else
#define sel_le(z, el_z, x, el_x, y, el_y, bx2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel_le)(__z, el_z, x, el_x, y, el_y, bx2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_lt(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_lt)(z, el_z, x, el_x, y, el_y, bx2)
#else
#define sel_lt(z, el_z, x, el_x, y, el_y, bx2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel_lt)(__z, el_z, x, el_x, y, el_y, bx2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_ne(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_ne)(z, el_z, x, el_x, y, el_y, bx2)
#else
#define sel_ne(z, el_z, x, el_x, y, el_y, bx2) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_sel_ne)(__z, el_z, x, el_x, y, el_y, bx2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vsel(x, y, bx4) \
	CSTUB_(_TIE_dmx1a_common_tie_vsel)(x, y, bx4)
#else
#define vsel(x, y, bx4) \
	CSTUB_(_TIE_dmx1a_common_tie_vsel)(x, y, bx4)
#endif

#ifdef _STRICT_ARG_TYPE
#define andb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_andb1)(bx, by)
#else
#define andb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_andb1)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define andbc1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_andbc1)(bx, by)
#else
#define andbc1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_andbc1)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define orb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_orb1)(bx, by)
#else
#define orb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_orb1)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define orbc1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_orbc1)(bx, by)
#else
#define orbc1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_orbc1)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define xorb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_xorb1)(bx, by)
#else
#define xorb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_xorb1)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define andb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_andb4)(bx4, by4)
#else
#define andb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_andb4)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define andbc4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_andbc4)(bx4, by4)
#else
#define andbc4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_andbc4)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define orb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_orb4)(bx4, by4)
#else
#define orb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_orb4)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define orbc4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_orbc4)(bx4, by4)
#else
#define orbc4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_orbc4)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define xorb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_xorb4)(bx4, by4)
#else
#define xorb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_xorb4)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskI)(bx4, imask)
#else
#define bcount0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskI)(bx4, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskR)(bx4, by4)
#else
#define bcount0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskR)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskI)(bx4, imask)
#else
#define bcount1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskI)(bx4, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskR)(bx4, by4)
#else
#define bcount1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskR)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskI)(bx4, imask)
#else
#define bfirst0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskI)(bx4, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskR)(bx4, by4)
#else
#define bfirst0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskR)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskI)(bx4, imask)
#else
#define bfirst1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskI)(bx4, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskR)(bx4, by4)
#else
#define bfirst1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskR)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_blast0_maskI)(bx4, imask)
#else
#define blast0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_blast0_maskI)(bx4, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_blast0_maskR)(bx4, by4)
#else
#define blast0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_blast0_maskR)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_blast1_maskI)(bx4, imask)
#else
#define blast1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_blast1_maskI)(bx4, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_blast1_maskR)(bx4, by4)
#else
#define blast1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_blast1_maskR)(bx4, by4)
#endif

#ifdef _STRICT_ARG_TYPE
#define bgetI(bx4, ipos) \
	CSTUB_(_TIE_dmx1a_common_tie_bgetI)(bx4, ipos)
#else
#define bgetI(bx4, ipos) \
	CSTUB_(_TIE_dmx1a_common_tie_bgetI)(bx4, ipos)
#endif

#ifdef _STRICT_ARG_TYPE
#define bgetR(bx4, rpos) \
	CSTUB_(_TIE_dmx1a_common_tie_bgetR)(bx4, rpos)
#else
#define bgetR(bx4, rpos) \
	CSTUB_(_TIE_dmx1a_common_tie_bgetR)(bx4, rpos)
#endif

#ifdef _STRICT_ARG_TYPE
#define bsetI(bx4, rpos, ibit) \
	CSTUB_(_TIE_dmx1a_common_tie_bsetI)(bx4, rpos, ibit)
#else
#define bsetI(bx4, rpos, ibit) \
	CSTUB_(_TIE_dmx1a_common_tie_bsetI)(bx4, rpos, ibit)
#endif

#ifdef _STRICT_ARG_TYPE
#define bsetR(bx4, rpos, by) \
	CSTUB_(_TIE_dmx1a_common_tie_bsetR)(bx4, rpos, by)
#else
#define bsetR(bx4, rpos, by) \
	CSTUB_(_TIE_dmx1a_common_tie_bsetR)(bx4, rpos, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adj(z, el_z, x, el_x, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adj)(z, el_z, x, el_x, exp_adj_ar)
#else
#define exp_adj(z, el_z, x, el_x, exp_adj_ar) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adj)(__z, el_z, x, el_x, exp_adj_ar); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adji(z, el_z, x, el_x, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adji)(z, el_z, x, el_x, exp_adj_imm)
#else
#define exp_adji(z, el_z, x, el_x, exp_adj_imm) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adji)(__z, el_z, x, el_x, exp_adj_imm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adj_fr(fx, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adj_fr)(fx, exp_adj_ar)
#else
#define exp_adj_fr(fx, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adj_fr)(fx, exp_adj_ar)
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adji_fr(fx, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adji_fr)(fx, exp_adj_imm)
#else
#define exp_adji_fr(fx, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adji_fr)(fx, exp_adj_imm)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_neg(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_s_neg)(z, el_z, x, el_x)
#else
#define s_neg(z, el_z, x, el_x) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_s_neg)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define s_copy(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_copy)(z, el_z, x, el_x, y, el_y)
#else
#define s_copy(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_s_copy)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define s_and(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_and)(z, el_z, x, el_x, y, el_y)
#else
#define s_and(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_s_and)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define s_andc(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_andc)(z, el_z, x, el_x, y, el_y)
#else
#define s_andc(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_s_andc)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define s_or(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_or)(z, el_z, x, el_x, y, el_y)
#else
#define s_or(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_s_or)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define s_orc(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_orc)(z, el_z, x, el_x, y, el_y)
#else
#define s_orc(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_s_orc)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define s_xor(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_xor)(z, el_z, x, el_x, y, el_y)
#else
#define s_xor(z, el_z, x, el_x, y, el_y) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_s_xor)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vnegs(x, signs) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vnegs)(x, signs)
#else
#define s_vnegs(x, signs) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vnegs)(x, signs)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vcopy(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vcopy)(x, y)
#else
#define s_vcopy(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vcopy)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vand(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vand)(x, y)
#else
#define s_vand(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vand)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vandc(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vandc)(x, y)
#else
#define s_vandc(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vandc)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vor(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vor)(x, y)
#else
#define s_vor(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vor)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vorc(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vorc)(x, y)
#else
#define s_vorc(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vorc)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vxor(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vxor)(x, y)
#else
#define s_vxor(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vxor)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vnegs_hr(hx, hr_signs) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vnegs_hr)(hx, hr_signs)
#else
#define s_vnegs_hr(hx, hr_signs) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vnegs_hr)(hx, hr_signs)
#endif

#ifdef _STRICT_ARG_TYPE
#define floorp_frac(floor, z, el_z, x, el_x, nbits) \
	CSTUB_(_TIE_dmx1a_common_tie_floorp_frac)(floor, z, el_z, x, el_x, nbits)
#else
#define floorp_frac(floor, z, el_z, x, el_x, nbits) { \
	unsigned int __floor; \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_floorp_frac)(__floor, __z, el_z, x, el_x, nbits); \
	(floor) = __floor; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define idx_frac(floor, z, el_z, input, nbits) \
	CSTUB_(_TIE_dmx1a_common_tie_idx_frac)(floor, z, el_z, input, nbits)
#else
#define idx_frac(floor, z, el_z, input, nbits) { \
	unsigned int __floor; \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_idx_frac)(__floor, __z, el_z, input, nbits); \
	(floor) = __floor; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define truncate_fr(x) \
	CSTUB_(_TIE_dmx1a_common_tie_truncate_fr)(x)
#else
#define truncate_fr(x) \
	CSTUB_(_TIE_dmx1a_common_tie_truncate_fr)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define rmax_idx(a, z, el_z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_rmax_idx)(a, z, el_z, x, idx)
#else
#define rmax_idx(a, z, el_z, x, idx) { \
	unsigned int __a; \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_rmax_idx)(__a, __z, el_z, x, idx); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define rmin_idx(a, z, el_z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_rmin_idx)(a, z, el_z, x, idx)
#else
#define rmin_idx(a, z, el_z, x, idx) { \
	unsigned int __a; \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_rmin_idx)(__a, __z, el_z, x, idx); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmaxmin_init(z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_vmaxmin_init)(z, x, idx)
#else
#define vmaxmin_init(z, x, idx) { \
	vr128 __z; \
	mir30 __idx; \
	CSTUB_(_TIE_dmx1a_common_tie_vmaxmin_init)(__z, x, __idx); \
	(z) = __z; \
	(idx) = __idx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmax_idx(z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_vmax_idx)(z, x, idx)
#else
#define vmax_idx(z, x, idx) { \
	vr128 __z = z; \
	mir30 __idx = idx; \
	CSTUB_(_TIE_dmx1a_common_tie_vmax_idx)(__z, x, __idx); \
	(z) = __z; \
	(idx) = __idx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmin_idx(z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_vmin_idx)(z, x, idx)
#else
#define vmin_idx(z, x, idx) { \
	vr128 __z = z; \
	mir30 __idx = idx; \
	CSTUB_(_TIE_dmx1a_common_tie_vmin_idx)(__z, x, __idx); \
	(z) = __z; \
	(idx) = __idx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmax(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmax)(x, y)
#else
#define vmax(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmax)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmin(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmin)(x, y)
#else
#define vmin(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmin)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_asc_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_vr)(a, z, x, y, el_y)
#else
#define sortupd_asc_vr(a, z, x, y, el_y) { \
	unsigned int __a; \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_vr)(__a, __z, x, y, el_y); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_des_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_vr)(a, z, x, y, el_y)
#else
#define sortupd_des_vr(a, z, x, y, el_y) { \
	unsigned int __a; \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_vr)(__a, __z, x, y, el_y); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_asc_ar(a, z, x) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_ar)(a, z, x)
#else
#define sortupd_asc_ar(a, z, x) { \
	unsigned int __a = a; \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_ar)(__a, __z, x); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_des_ar(a, z, x) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_ar)(a, z, x)
#else
#define sortupd_des_ar(a, z, x) { \
	unsigned int __a = a; \
	vr128 __z; \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_ar)(__a, __z, x); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vbool(x, y, op) \
	CSTUB_(_TIE_dmx1a_common_tie_vbool)(x, y, op)
#else
#define vbool(x, y, op) \
	CSTUB_(_TIE_dmx1a_common_tie_vbool)(x, y, op)
#endif

#ifdef _STRICT_ARG_TYPE
#define align_up(val, option) \
	CSTUB_(_TIE_dmx1a_common_tie_align_up)((unsigned)(val), option)
#else
#define align_up(val, option) \
	CSTUB_(_TIE_dmx1a_common_tie_align_up)((unsigned)(val), option)
#endif

#ifdef _STRICT_ARG_TYPE
#define range_init(low, high, startOp) \
	CSTUB_(_TIE_dmx1a_common_tie_range_init)(low, high, startOp)
#else
#define range_init(low, high, startOp) \
	CSTUB_(_TIE_dmx1a_common_tie_range_init)(low, high, startOp)
#endif

#ifdef _STRICT_ARG_TYPE
#define range_check(bz4, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_range_check)(bz4, idx)
#else
#define range_check(bz4, idx) { \
	xtbool4 __bz4; \
	mir30 __idx = idx; \
	CSTUB_(_TIE_dmx1a_common_tie_range_check)(__bz4, __idx); \
	(bz4) = __bz4; \
	(idx) = __idx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define afloat_exp_extract(x) \
	CSTUB_(_TIE_dmx1a_common_tie_afloat_exp_extract)(x)
#else
#define afloat_exp_extract(x) \
	CSTUB_(_TIE_dmx1a_common_tie_afloat_exp_extract)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_shift_amount(input) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_shift_amount)(input)
#else
#define exp_shift_amount(input) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_shift_amount)(input)
#endif

#ifdef _STRICT_ARG_TYPE
#define flush_32x4_bounded(buf, ptr, count) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_32x4_bounded)(buf, (unsigned int **)&(ptr), count)
#else
#define flush_32x4_bounded(buf, ptr, count) { \
	mir30 __count = count; \
	CSTUB_(_TIE_dmx1a_common_tie_flush_32x4_bounded)(buf, (unsigned int **)&(ptr), __count); \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_AccExtend_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_AccExtend_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB0_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB0_flex)(ptr, remBlock, parms)
#else
#define load_BB0_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB0_flex)(ptr, remBlock, parms)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB1_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB1_flex)(ptr, remBlock, parms)
#else
#define load_BB1_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB1_flex)(ptr, remBlock, parms)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB2_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB2_flex)(ptr, remBlock, parms)
#else
#define load_BB2_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB2_flex)(ptr, remBlock, parms)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB3_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB3_flex)(ptr, remBlock, parms)
#else
#define load_BB3_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB3_flex)(ptr, remBlock, parms)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB4_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB4_flex)(ptr, remBlock, parms)
#else
#define load_BB4_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB4_flex)(ptr, remBlock, parms)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB5_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB5_flex)(ptr, remBlock, parms)
#else
#define load_BB5_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB5_flex)(ptr, remBlock, parms)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB6_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB6_flex)(ptr, remBlock, parms)
#else
#define load_BB6_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB6_flex)(ptr, remBlock, parms)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB7_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB7_flex)((const unsigned int **)&(ptr), remBlock, parms)
#else
#define load_BB7_flex(ptr, remBlock, parms) { \
	mir30 __parms = parms; \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB7_flex)((const unsigned int **)&(ptr), remBlock, __parms); \
	(parms) = __parms; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB0_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB0_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB1_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB1_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB2_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB2_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB3_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB3_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB4_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB4_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB5_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB5_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB6_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB6_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB7_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB7_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BBx_a_bounded(buf, ptr, count, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BBx_a_bounded)(buf, (const unsigned int **)&(ptr), count, sel)
#else
#define load_BBx_a_bounded(buf, ptr, count, sel) { \
	ulsr128 __buf = buf; \
	mir30 __count = count; \
	CSTUB_(_TIE_dmx1a_common_tie_load_BBx_a_bounded)(__buf, (const unsigned int **)&(ptr), __count, sel); \
	(buf) = __buf; \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB1_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB1_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB2_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB2_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB3_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB3_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB4_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB4_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB5_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB5_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB6_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB6_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB7_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB7_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_32x4_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_bounded)(z, buf, (const unsigned int **)&(ptr), count)
#else
#define load_32x4_vr_a_bounded(z, buf, ptr, count) { \
	vr128 __z; \
	ulsr128 __buf = buf; \
	mir30 __count = count; \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_bounded)(__z, __buf, (const unsigned int **)&(ptr), __count); \
	(z) = __z; \
	(buf) = __buf; \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_lookup_AccExtend_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_load_lookup_AccExtend_postI)()
#else
#define load_lookup_AccExtend_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_load_lookup_AccExtend_postI)()
#endif

#ifdef _STRICT_ARG_TYPE
#define load_lookup_vr_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_load_lookup_vr_postI)()
#else
#define load_lookup_vr_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_load_lookup_vr_postI)()
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_lookup_AccExtend_idx16vr(vidx16, ptr_sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr)(vidx16, ptr_sel)
#else
#define load32x1_lookup_AccExtend_idx16vr(vidx16, ptr_sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr)(vidx16, ptr_sel)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_lookup_vr_idx16vr(z, vidx16, ptr_sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr)(z, vidx16, ptr_sel)
#else
#define load32x1_lookup_vr_idx16vr(z, vidx16, ptr_sel) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr)(__z, vidx16, ptr_sel); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idx16vr(z, ptr, vidx16, ptr_sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idx16vr)(z,(unsigned *)( ptr), vidx16, ptr_sel)
#else
#define load32x1_vr_idx16vr(z, ptr, vidx16, ptr_sel) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idx16vr)(__z,(unsigned *)( ptr), vidx16, ptr_sel); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define mac8bx8b(z, x, y, signed_xy) \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b)(z, x, y, signed_xy)
#else
#define mac8bx8b(z, x, y, signed_xy) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b)(__z, x, y, signed_xy); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define mac8bx8b_conv(z, x, signed_xy, shift_in) \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_conv)(z, x, signed_xy, shift_in)
#else
#define mac8bx8b_conv(z, x, signed_xy, shift_in) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_conv)(__z, x, signed_xy, shift_in); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define mac8bx8b_sparse(z, x, y, signed_xy) \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_sparse)(z, x, y, signed_xy)
#else
#define mac8bx8b_sparse(z, x, y, signed_xy) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_sparse)(__z, x, y, signed_xy); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define mir_init(low) \
	CSTUB_(_TIE_dmx1a_common_tie_mir_init)(low)
#else
#define mir_init(low) \
	CSTUB_(_TIE_dmx1a_common_tie_mir_init)(low)
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_AccExtend_vr(x) \
	CSTUB_(_TIE_dmx1a_common_tie_mov_AccExtend_vr)(x)
#else
#define mov_AccExtend_vr(x) \
	CSTUB_(_TIE_dmx1a_common_tie_mov_AccExtend_vr)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_BB_vrVB(x) \
	CSTUB_(_TIE_dmx1a_common_tie_mov_BB_vrVB)(x)
#else
#define mov_BB_vrVB(x) \
	CSTUB_(_TIE_dmx1a_common_tie_mov_BB_vrVB)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_vr_AccExtend() \
	CSTUB_(_TIE_dmx1a_common_tie_mov_vr_AccExtend)()
#else
#define mov_vr_AccExtend() \
	CSTUB_(_TIE_dmx1a_common_tie_mov_vr_AccExtend)()
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_vrVB_BB() \
	CSTUB_(_TIE_dmx1a_common_tie_mov_vrVB_BB)()
#else
#define mov_vrVB_BB() \
	CSTUB_(_TIE_dmx1a_common_tie_mov_vrVB_BB)()
#endif

#ifdef _STRICT_ARG_TYPE
#define next_lookup_load() \
	CSTUB_(_TIE_dmx1a_common_tie_next_lookup_load)()
#else
#define next_lookup_load() \
	CSTUB_(_TIE_dmx1a_common_tie_next_lookup_load)()
#endif

#ifdef _STRICT_ARG_TYPE
#define next_lookup_store() \
	CSTUB_(_TIE_dmx1a_common_tie_next_lookup_store)()
#else
#define next_lookup_store() \
	CSTUB_(_TIE_dmx1a_common_tie_next_lookup_store)()
#endif

#ifdef _STRICT_ARG_TYPE
#define precess_16bits(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_precess_16bits)(x, y)
#else
#define precess_16bits(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_precess_16bits)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define rectify32_into8(z, x, shift, rnd, el32) \
	CSTUB_(_TIE_dmx1a_common_tie_rectify32_into8)(z, x, shift, rnd, el32)
#else
#define rectify32_into8(z, x, shift, rnd, el32) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_rectify32_into8)(__z, x, shift, rnd, el32); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define rnd_sat_pack(z, el32, x, sgn) \
	CSTUB_(_TIE_dmx1a_common_tie_rnd_sat_pack)(z, el32, x, sgn)
#else
#define rnd_sat_pack(z, el32, x, sgn) { \
	vr128 __z = z; \
	CSTUB_(_TIE_dmx1a_common_tie_rnd_sat_pack)(__z, el32, x, sgn); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_BB_zero() \
	CSTUB_(_TIE_dmx1a_common_tie_set_BB_zero)()
#else
#define set_BB_zero() \
	CSTUB_(_TIE_dmx1a_common_tie_set_BB_zero)()
#endif

#ifdef _STRICT_ARG_TYPE
#define shift8_into32_arith(x, shift, rnd, el32) \
	CSTUB_(_TIE_dmx1a_common_tie_shift8_into32_arith)(x, shift, rnd, el32)
#else
#define shift8_into32_arith(x, shift, rnd, el32) \
	CSTUB_(_TIE_dmx1a_common_tie_shift8_into32_arith)(x, shift, rnd, el32)
#endif

#ifdef _STRICT_ARG_TYPE
#define shift32_arith(x, shift, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_shift32_arith)(x, shift, rnd)
#else
#define shift32_arith(x, shift, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_shift32_arith)(x, shift, rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_32x4_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_bounded)(z, buf, (unsigned int **)&(ptr), count)
#else
#define store_32x4_vr_a_bounded(z, buf, ptr, count) { \
	ulsr128 __buf = buf; \
	mir30 __count = count; \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_bounded)(z, __buf, (unsigned int **)&(ptr), __count); \
	(buf) = __buf; \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_AccExtend_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_AccExtend_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB0_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB0_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB1_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB1_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB2_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB2_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB3_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB3_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB4_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB4_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB5_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB5_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB6_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB6_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB7_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB7_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB1_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB1_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB2_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB2_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB3_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB3_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB4_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB4_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB5_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB5_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB6_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB6_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB7_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB7_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_lookup_AccExtend_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_store_lookup_AccExtend_postI)()
#else
#define store_lookup_AccExtend_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_store_lookup_AccExtend_postI)()
#endif

#ifdef _STRICT_ARG_TYPE
#define store_lookup_vr_postI(z) \
	CSTUB_(_TIE_dmx1a_common_tie_store_lookup_vr_postI)(z)
#else
#define store_lookup_vr_postI(z) \
	CSTUB_(_TIE_dmx1a_common_tie_store_lookup_vr_postI)(z)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_WR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_WR)(b)
#else
#define mv_WR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_WR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_PERM(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_PERM)(b)
#else
#define mv_PERM(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_PERM)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_MIR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_MIR)(b)
#else
#define mv_MIR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_MIR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_ULSR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_ULSR)(b)
#else
#define mv_ULSR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_ULSR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_CR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_CR)(b)
#else
#define mv_CR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_CR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR(addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR)(addr, fimm)
#else
#define ld_FR(addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR)(addr, fimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR(fregin, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR)(fregin, addr, fimm)
#else
#define st_FR(fregin, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR)(fregin, addr, fimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_idxR)(addr, x)
#else
#define ld_FR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_idxR)(addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR_idxR(fregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_idxR)(fregin, addr, x)
#else
#define st_FR_idxR(fregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_idxR)(fregin, addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR_postI(fregout, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postI)(fregout, (const fr32 **)&(addr), fimm)
#else
#define ld_FR_postI(fregout, addr, fimm) { \
	fr32 __fregout; \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postI)(__fregout, (const fr32 **)&(addr), fimm); \
	(fregout) = __fregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR_postI(fregin, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_postI)(fregin, (fr32 **)&(addr), fimm)
#else
#define st_FR_postI(fregin, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_postI)(fregin, (fr32 **)&(addr), fimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR_postR(fregout, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postR)(fregout, (const fr32 **)&(addr), x)
#else
#define ld_FR_postR(fregout, addr, x) { \
	fr32 __fregout; \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postR)(__fregout, (const fr32 **)&(addr), x); \
	(fregout) = __fregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR_postR(fregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_postR)(fregin, (fr32 **)&(addr), x)
#else
#define st_FR_postR(fregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_postR)(fregin, (fr32 **)&(addr), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_HR(addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR)(addr, himm)
#else
#define ld_HR(addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR)(addr, himm)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_HR(hregin, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR)(hregin, addr, himm)
#else
#define st_HR(hregin, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR)(hregin, addr, himm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_HR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_idxR)(addr, x)
#else
#define ld_HR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_idxR)(addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_HR_idxR(hregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_idxR)(hregin, addr, x)
#else
#define st_HR_idxR(hregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_idxR)(hregin, addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_HR_postI(hregout, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postI)(hregout, (const vr64 **)&(addr), himm)
#else
#define ld_HR_postI(hregout, addr, himm) { \
	vr64 __hregout; \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postI)(__hregout, (const vr64 **)&(addr), himm); \
	(hregout) = __hregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_HR_postI(hregin, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_postI)(hregin, (vr64 **)&(addr), himm)
#else
#define st_HR_postI(hregin, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_postI)(hregin, (vr64 **)&(addr), himm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_HR_postR(hregout, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postR)(hregout, (const vr64 **)&(addr), x)
#else
#define ld_HR_postR(hregout, addr, x) { \
	vr64 __hregout; \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postR)(__hregout, (const vr64 **)&(addr), x); \
	(hregout) = __hregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_HR_postR(hregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_postR)(hregin, (vr64 **)&(addr), x)
#else
#define st_HR_postR(hregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_postR)(hregin, (vr64 **)&(addr), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR(addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR)(addr, vimm)
#else
#define ld_VR(addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR)(addr, vimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR(vregin, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR)(vregin, addr, vimm)
#else
#define st_VR(vregin, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR)(vregin, addr, vimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_idxR)(addr, x)
#else
#define ld_VR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_idxR)(addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR_idxR(vregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_idxR)(vregin, addr, x)
#else
#define st_VR_idxR(vregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_idxR)(vregin, addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR_postI(vregout, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postI)(vregout, (const vr128 **)&(addr), vimm)
#else
#define ld_VR_postI(vregout, addr, vimm) { \
	vr128 __vregout; \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postI)(__vregout, (const vr128 **)&(addr), vimm); \
	(vregout) = __vregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR_postI(vregin, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_postI)(vregin, (vr128 **)&(addr), vimm)
#else
#define st_VR_postI(vregin, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_postI)(vregin, (vr128 **)&(addr), vimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR_postR(vregout, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postR)(vregout, (const vr128 **)&(addr), x)
#else
#define ld_VR_postR(vregout, addr, x) { \
	vr128 __vregout; \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postR)(__vregout, (const vr128 **)&(addr), x); \
	(vregout) = __vregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR_postR(vregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_postR)(vregin, (vr128 **)&(addr), x)
#else
#define st_VR_postR(vregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_postR)(vregin, (vr128 **)&(addr), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_FR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_FR)(b)
#else
#define mv_FR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_FR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_ar_fr(b) \
	CSTUB_(_TIE_dmx1a_common_tie_move_ar_fr)(b)
#else
#define move_ar_fr(b) \
	CSTUB_(_TIE_dmx1a_common_tie_move_ar_fr)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_ar(b) \
	CSTUB_(_TIE_dmx1a_common_tie_move_fr_ar)(b)
#else
#define move_fr_ar(b) \
	CSTUB_(_TIE_dmx1a_common_tie_move_fr_ar)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_HR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_HR)(b)
#else
#define mv_HR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_HR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_VR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_VR)(b)
#else
#define mv_VR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_VR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_pair(hi, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_pair)(hi, lo)
#else
#define vr128_pair(hi, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_pair)(hi, lo)
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRL(v, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRL)(v, lo)
#else
#define set_VRL(v, lo) { \
	vr128 __v = v; \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRL)(__v, lo); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRH(v, hi) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRH)(v, hi)
#else
#define set_VRH(v, hi) { \
	vr128 __v = v; \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRH)(__v, hi); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRL(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRL)(b)
#else
#define get_VRL(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRL)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRH(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRH)(b)
#else
#define get_VRH(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRH)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_ar_x2(a1_out, a0_out, ptr, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_ar_x2)(a1_out, a0_out, ptr, idx)
#else
#define ld_ar_x2(a1_out, a0_out, ptr, idx) { \
	unsigned int __a1_out; \
	unsigned int __a0_out; \
	CSTUB_(_TIE_dmx1a_common_tie_ld_ar_x2)(__a1_out, __a0_out, ptr, idx); \
	(a1_out) = __a1_out; \
	(a0_out) = __a0_out; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_ar_x2(ptr, idx, a1_in, a0_in) \
	CSTUB_(_TIE_dmx1a_common_tie_st_ar_x2)(ptr, idx, a1_in, a0_in)
#else
#define st_ar_x2(ptr, idx, a1_in, a0_in) \
	CSTUB_(_TIE_dmx1a_common_tie_st_ar_x2)(ptr, idx, a1_in, a0_in)
#endif

#ifdef _STRICT_ARG_TYPE
#define perm16_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_storei)(a, b, c)
#else
#define perm16_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define perm16_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_loadi)(b, c)
#else
#define perm16_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ulsr128_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_storei)(a, b, c)
#else
#define ulsr128_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ulsr128_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_loadi)(b, c)
#else
#define ulsr128_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define mir30_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_storei)(a, b, c)
#else
#define mir30_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define mir30_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_loadi)(b, c)
#else
#define mir30_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define cr64_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_storei)(a, b, c)
#else
#define cr64_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define cr64_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_loadi)(b, c)
#else
#define cr64_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define wr64_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_storei)(a, b, c)
#else
#define wr64_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define wr64_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_loadi)(b, c)
#else
#define wr64_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_JammingBit() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_JammingBit)()
#else
#define RUR_JammingBit() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_JammingBit)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_JammingBit(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_JammingBit)(v)
#else
#define WUR_JammingBit(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_JammingBit)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_AccExtend_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_0)()
#else
#define RUR_AccExtend_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_AccExtend_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_0)(v)
#else
#define WUR_AccExtend_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_AccExtend_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_1)()
#else
#define RUR_AccExtend_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_AccExtend_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_1)(v)
#else
#define WUR_AccExtend_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_AccExtend_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_2)()
#else
#define RUR_AccExtend_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_AccExtend_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_2)(v)
#else
#define WUR_AccExtend_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_AccExtend_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_3)()
#else
#define RUR_AccExtend_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_AccExtend_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_3)(v)
#else
#define WUR_AccExtend_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB0_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_0)()
#else
#define RUR_BB0_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB0_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_0)(v)
#else
#define WUR_BB0_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB0_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_1)()
#else
#define RUR_BB0_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB0_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_1)(v)
#else
#define WUR_BB0_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB0_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_2)()
#else
#define RUR_BB0_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB0_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_2)(v)
#else
#define WUR_BB0_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB0_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_3)()
#else
#define RUR_BB0_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB0_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_3)(v)
#else
#define WUR_BB0_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB1_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_0)()
#else
#define RUR_BB1_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB1_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_0)(v)
#else
#define WUR_BB1_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB1_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_1)()
#else
#define RUR_BB1_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB1_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_1)(v)
#else
#define WUR_BB1_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB1_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_2)()
#else
#define RUR_BB1_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB1_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_2)(v)
#else
#define WUR_BB1_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB1_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_3)()
#else
#define RUR_BB1_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB1_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_3)(v)
#else
#define WUR_BB1_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB2_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_0)()
#else
#define RUR_BB2_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB2_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_0)(v)
#else
#define WUR_BB2_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB2_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_1)()
#else
#define RUR_BB2_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB2_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_1)(v)
#else
#define WUR_BB2_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB2_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_2)()
#else
#define RUR_BB2_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB2_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_2)(v)
#else
#define WUR_BB2_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB2_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_3)()
#else
#define RUR_BB2_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB2_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_3)(v)
#else
#define WUR_BB2_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB3_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_0)()
#else
#define RUR_BB3_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB3_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_0)(v)
#else
#define WUR_BB3_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB3_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_1)()
#else
#define RUR_BB3_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB3_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_1)(v)
#else
#define WUR_BB3_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB3_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_2)()
#else
#define RUR_BB3_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB3_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_2)(v)
#else
#define WUR_BB3_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB3_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_3)()
#else
#define RUR_BB3_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB3_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_3)(v)
#else
#define WUR_BB3_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB4_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_0)()
#else
#define RUR_BB4_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB4_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_0)(v)
#else
#define WUR_BB4_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB4_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_1)()
#else
#define RUR_BB4_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB4_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_1)(v)
#else
#define WUR_BB4_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB4_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_2)()
#else
#define RUR_BB4_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB4_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_2)(v)
#else
#define WUR_BB4_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB4_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_3)()
#else
#define RUR_BB4_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB4_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_3)(v)
#else
#define WUR_BB4_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB5_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_0)()
#else
#define RUR_BB5_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB5_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_0)(v)
#else
#define WUR_BB5_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB5_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_1)()
#else
#define RUR_BB5_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB5_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_1)(v)
#else
#define WUR_BB5_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB5_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_2)()
#else
#define RUR_BB5_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB5_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_2)(v)
#else
#define WUR_BB5_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB5_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_3)()
#else
#define RUR_BB5_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB5_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_3)(v)
#else
#define WUR_BB5_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB6_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_0)()
#else
#define RUR_BB6_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB6_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_0)(v)
#else
#define WUR_BB6_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB6_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_1)()
#else
#define RUR_BB6_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB6_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_1)(v)
#else
#define WUR_BB6_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB6_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_2)()
#else
#define RUR_BB6_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB6_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_2)(v)
#else
#define WUR_BB6_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB6_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_3)()
#else
#define RUR_BB6_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB6_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_3)(v)
#else
#define WUR_BB6_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB7_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_0)()
#else
#define RUR_BB7_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB7_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_0)(v)
#else
#define WUR_BB7_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB7_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_1)()
#else
#define RUR_BB7_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB7_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_1)(v)
#else
#define WUR_BB7_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB7_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_2)()
#else
#define RUR_BB7_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB7_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_2)(v)
#else
#define WUR_BB7_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB7_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_3)()
#else
#define RUR_BB7_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB7_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_3)(v)
#else
#define WUR_BB7_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_MvmAux() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_MvmAux)()
#else
#define RUR_MvmAux() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_MvmAux)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_MvmAux(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_MvmAux)(v)
#else
#define WUR_MvmAux(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_MvmAux)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB1_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_0)()
#else
#define RUR_VB1_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB1_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_0)(v)
#else
#define WUR_VB1_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB1_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_1)()
#else
#define RUR_VB1_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB1_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_1)(v)
#else
#define WUR_VB1_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB1_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_2)()
#else
#define RUR_VB1_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB1_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_2)(v)
#else
#define WUR_VB1_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB1_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_3)()
#else
#define RUR_VB1_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB1_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_3)(v)
#else
#define WUR_VB1_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB2_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_0)()
#else
#define RUR_VB2_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB2_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_0)(v)
#else
#define WUR_VB2_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB2_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_1)()
#else
#define RUR_VB2_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB2_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_1)(v)
#else
#define WUR_VB2_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB2_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_2)()
#else
#define RUR_VB2_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB2_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_2)(v)
#else
#define WUR_VB2_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB2_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_3)()
#else
#define RUR_VB2_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB2_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_3)(v)
#else
#define WUR_VB2_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB3_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_0)()
#else
#define RUR_VB3_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB3_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_0)(v)
#else
#define WUR_VB3_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB3_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_1)()
#else
#define RUR_VB3_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB3_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_1)(v)
#else
#define WUR_VB3_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB3_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_2)()
#else
#define RUR_VB3_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB3_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_2)(v)
#else
#define WUR_VB3_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB3_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_3)()
#else
#define RUR_VB3_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB3_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_3)(v)
#else
#define WUR_VB3_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB4_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_0)()
#else
#define RUR_VB4_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB4_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_0)(v)
#else
#define WUR_VB4_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB4_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_1)()
#else
#define RUR_VB4_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB4_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_1)(v)
#else
#define WUR_VB4_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB4_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_2)()
#else
#define RUR_VB4_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB4_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_2)(v)
#else
#define WUR_VB4_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB4_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_3)()
#else
#define RUR_VB4_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB4_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_3)(v)
#else
#define WUR_VB4_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB5_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_0)()
#else
#define RUR_VB5_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB5_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_0)(v)
#else
#define WUR_VB5_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB5_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_1)()
#else
#define RUR_VB5_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB5_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_1)(v)
#else
#define WUR_VB5_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB5_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_2)()
#else
#define RUR_VB5_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB5_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_2)(v)
#else
#define WUR_VB5_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB5_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_3)()
#else
#define RUR_VB5_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB5_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_3)(v)
#else
#define WUR_VB5_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB6_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_0)()
#else
#define RUR_VB6_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB6_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_0)(v)
#else
#define WUR_VB6_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB6_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_1)()
#else
#define RUR_VB6_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB6_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_1)(v)
#else
#define WUR_VB6_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB6_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_2)()
#else
#define RUR_VB6_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB6_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_2)(v)
#else
#define WUR_VB6_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB6_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_3)()
#else
#define RUR_VB6_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB6_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_3)(v)
#else
#define WUR_VB6_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB7_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_0)()
#else
#define RUR_VB7_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB7_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_0)(v)
#else
#define WUR_VB7_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB7_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_1)()
#else
#define RUR_VB7_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB7_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_1)(v)
#else
#define WUR_VB7_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB7_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_2)()
#else
#define RUR_VB7_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_2)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB7_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_2)(v)
#else
#define WUR_VB7_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_2)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB7_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_3)()
#else
#define RUR_VB7_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_3)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB7_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_3)(v)
#else
#define WUR_VB7_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_3)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_look_state() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_look_state)()
#else
#define RUR_look_state() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_look_state)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_look_state(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_look_state)(v)
#else
#define WUR_look_state(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_look_state)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define wr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_move)(b)
#else
#define wr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define perm16_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_move)(b)
#else
#define perm16_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mir30_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_move)(b)
#else
#define mir30_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define ulsr128_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_move)(b)
#else
#define ulsr128_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define cr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_move)(b)
#else
#define cr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_move)(b)
#else
#define fr32_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadi(p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadi)(p, o)
#else
#define fr32_loadi(p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadi)(p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storei(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storei)(v, p, o)
#else
#define fr32_storei(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storei)(v, p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadx(p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadx)(p, x)
#else
#define fr32_loadx(p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadx)(p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storex(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storex)(v, p, x)
#else
#define fr32_storex(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storex)(v, p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadip)(v, (const fr32 **)&(p), o)
#else
#define fr32_loadip(v, p, o) { \
	fr32 __v; \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadip)(__v, (const fr32 **)&(p), o); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storeip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storeip)(v, (fr32 **)&(p), o)
#else
#define fr32_storeip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storeip)(v, (fr32 **)&(p), o)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadxp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadxp)(v, (const fr32 **)&(p), x)
#else
#define fr32_loadxp(v, p, x) { \
	fr32 __v; \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadxp)(__v, (const fr32 **)&(p), x); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storexp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storexp)(v, (fr32 **)&(p), x)
#else
#define fr32_storexp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storexp)(v, (fr32 **)&(p), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_rtor_int32(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_int32)(b)
#else
#define fr32_rtor_int32(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_int32)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_rtor_uint32(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_uint32)(b)
#else
#define fr32_rtor_uint32(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_uint32)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define int32_rtor_fr32(a) \
	CSTUB_(_TIE_dmx1a_common_tie_int32_rtor_fr32)(a)
#else
#define int32_rtor_fr32(a) \
	CSTUB_(_TIE_dmx1a_common_tie_int32_rtor_fr32)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define uint32_rtor_fr32(a) \
	CSTUB_(_TIE_dmx1a_common_tie_uint32_rtor_fr32)(a)
#else
#define uint32_rtor_fr32(a) \
	CSTUB_(_TIE_dmx1a_common_tie_uint32_rtor_fr32)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_move)(b)
#else
#define vr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadi(p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadi)(p, o)
#else
#define vr64_loadi(p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadi)(p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storei(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storei)(v, p, o)
#else
#define vr64_storei(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storei)(v, p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadx(p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadx)(p, x)
#else
#define vr64_loadx(p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadx)(p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storex(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storex)(v, p, x)
#else
#define vr64_storex(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storex)(v, p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadip)(v, (const vr64 **)&(p), o)
#else
#define vr64_loadip(v, p, o) { \
	vr64 __v; \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadip)(__v, (const vr64 **)&(p), o); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storeip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storeip)(v, (vr64 **)&(p), o)
#else
#define vr64_storeip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storeip)(v, (vr64 **)&(p), o)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadxp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadxp)(v, (const vr64 **)&(p), x)
#else
#define vr64_loadxp(v, p, x) { \
	vr64 __v; \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadxp)(__v, (const vr64 **)&(p), x); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storexp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storexp)(v, (vr64 **)&(p), x)
#else
#define vr64_storexp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storexp)(v, (vr64 **)&(p), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_rtor_int64(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_int64)(b)
#else
#define vr64_rtor_int64(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_int64)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_rtor_uint64(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_uint64)(b)
#else
#define vr64_rtor_uint64(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_uint64)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define int64_rtor_vr64(a) \
	CSTUB_(_TIE_dmx1a_common_tie_int64_rtor_vr64)(a)
#else
#define int64_rtor_vr64(a) \
	CSTUB_(_TIE_dmx1a_common_tie_int64_rtor_vr64)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define uint64_rtor_vr64(a) \
	CSTUB_(_TIE_dmx1a_common_tie_uint64_rtor_vr64)(a)
#else
#define uint64_rtor_vr64(a) \
	CSTUB_(_TIE_dmx1a_common_tie_uint64_rtor_vr64)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_pair(hi, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_pair)(hi, lo)
#else
#define vr64_pair(hi, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_pair)(hi, lo)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_HRL(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_HRL)(b)
#else
#define get_HRL(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_HRL)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_HRH(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_HRH)(b)
#else
#define get_HRH(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_HRH)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define set_HRL(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_HRL)(a, b)
#else
#define set_HRL(a, b) { \
	vr64 __a = a; \
	CSTUB_(_TIE_dmx1a_common_tie_set_HRL)(__a, b); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_HRH(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_HRH)(a, b)
#else
#define set_HRH(a, b) { \
	vr64 __a = a; \
	CSTUB_(_TIE_dmx1a_common_tie_set_HRH)(__a, b); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_move)(b)
#else
#define vr128_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadi)(b, c)
#else
#define vr128_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storei)(a, b, c)
#else
#define vr128_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_loadx(b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadx)(b, x)
#else
#define vr128_loadx(b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadx)(b, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_storex(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storex)(a, b, x)
#else
#define vr128_storex(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storex)(a, b, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_loadip(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadip)(a, (const vr128 **)&(b), c)
#else
#define vr128_loadip(a, b, c) { \
	vr128 __a; \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadip)(__a, (const vr128 **)&(b), c); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_storeip(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storeip)(a, (vr128 **)&(b), c)
#else
#define vr128_storeip(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storeip)(a, (vr128 **)&(b), c)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_loadxp(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadxp)(a, (const vr128 **)&(b), x)
#else
#define vr128_loadxp(a, b, x) { \
	vr128 __a; \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadxp)(__a, (const vr128 **)&(b), x); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_storexp(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storexp)(a, (vr128 **)&(b), x)
#else
#define vr128_storexp(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storexp)(a, (vr128 **)&(b), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr128_quad(q3, q2, q1, q0) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_quad)(q3, q2, q1, q0)
#else
#define vr128_quad(q3, q2, q1, q0) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_quad)(q3, q2, q1, q0)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRQ0(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ0)(b)
#else
#define get_VRQ0(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ0)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRQ1(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ1)(b)
#else
#define get_VRQ1(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ1)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRQ2(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ2)(b)
#else
#define get_VRQ2(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ2)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRQ3(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ3)(b)
#else
#define get_VRQ3(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ3)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRQ0(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ0)(a, b)
#else
#define set_VRQ0(a, b) { \
	vr128 __a = a; \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ0)(__a, b); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRQ1(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ1)(a, b)
#else
#define set_VRQ1(a, b) { \
	vr128 __a = a; \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ1)(__a, b); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRQ2(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ2)(a, b)
#else
#define set_VRQ2(a, b) { \
	vr128 __a = a; \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ2)(__a, b); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRQ3(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ3)(a, b)
#else
#define set_VRQ3(a, b) { \
	vr128 __a = a; \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ3)(__a, b); \
	(a) = __a; \
}
#endif

#define XT_RSR_SAR() \
	CSTUB_(_TIE_xt_core_RSR_SAR)()

#define XT_WSR_SAR(t) \
	CSTUB_(_TIE_xt_core_WSR_SAR)(t)

#define XT_XSR_SAR(t) \
	CSTUB_(_TIE_xt_core_XSR_SAR)(t)

#else /* !__cplusplus */
/* Ctype declarations */
typedef int immediate;
typedef unsigned char xtbool;
typedef unsigned char xtbool2;
typedef unsigned char xtbool4;
typedef unsigned char xtbool8;
typedef unsigned short xtbool16;

/* Ctype definitions */
typedef CSTUB_MSC_ALIGN(4) struct fr32_struct {
unsigned int _[1];
} CSTUB_GCC_ALIGN(4) fr32;

typedef CSTUB_MSC_ALIGN(8) struct vr64_struct {
unsigned int _[2];
} CSTUB_GCC_ALIGN(8) vr64;

typedef CSTUB_MSC_ALIGN(16) struct vr128_struct {
unsigned int _[4];
} CSTUB_GCC_ALIGN(16) vr128;

typedef CSTUB_MSC_ALIGN(8) struct wr64_struct {
unsigned int _[2];
} CSTUB_GCC_ALIGN(8) wr64;

typedef CSTUB_MSC_ALIGN(8) struct cr64_struct {
unsigned int _[2];
} CSTUB_GCC_ALIGN(8) cr64;

typedef CSTUB_MSC_ALIGN(4) struct mir30_struct {
unsigned int _[1];
} CSTUB_GCC_ALIGN(4) mir30;

typedef CSTUB_MSC_ALIGN(16) struct ulsr128_struct {
unsigned int _[4];
} CSTUB_GCC_ALIGN(16) ulsr128;

typedef CSTUB_MSC_ALIGN(2) struct perm16_struct {
unsigned short  _[1];
} CSTUB_GCC_ALIGN(2) perm16;

/* Proto declarations */
CSTUB_EXTERN void CSTUB_(_TIE_xt_density_NOP_N)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_NOP)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_DEPBITS)(unsigned int* art /*inout*/, const unsigned int ars /*in*/, immediate low_depbits /*in*/, immediate lngth_depbits /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_XORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVT)(unsigned int* arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVF)(unsigned int* arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(const unsigned int art /*in*/, const unsigned int ars /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_L32I_N)(const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_density_S32I_N)(const int t /*in*/, const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_ADD_N)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_ADDI_N)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_MOV_N)(const int s /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_density_MOVI_N)(immediate i /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_uint32_loadi)(const unsigned int * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_uint32_storei)(const unsigned int c /*in*/, const unsigned int * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_uint32_move)(const unsigned int b /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDI)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_OR)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_L32I)(const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S32I)(const int r /*in*/, const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S32NB)(const int r /*in*/, const int * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned char CSTUB_(_TIE_xt_core_L8UI)(const unsigned char * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S8I)(const signed char r /*in*/, const signed char * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned short CSTUB_(_TIE_xt_core_L16UI)(const unsigned short * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN short CSTUB_(_TIE_xt_core_L16SI)(const short * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_S16I)(const short r /*in*/, const short * p /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDMI)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADD)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDX2)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDX4)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ADDX8)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUB)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUBX2)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUBX4)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SUBX8)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SALT)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SALTU)(const unsigned int s /*in*/, const unsigned int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_AND)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_XOR)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_EXTUI)(const unsigned int t /*in*/, immediate i /*in*/, immediate o /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_MOVI)(immediate i /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVEQZ)(int* r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVNEZ)(int* r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVLTZ)(int* r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_MOVGEZ)(int* r /*inout*/, const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_NEG)(const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_ABS)(const int t /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSR)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSL)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSA8L)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSA8B)(const int s /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_SSAI)(immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SLL)(const int s /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SRC)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SRL)(const unsigned int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SRA)(const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SLLI)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SRAI)(const int t /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SRLI)(const unsigned int t /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSAI_SRC)(const int src1 /*in*/, const int src2 /*in*/, immediate amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSR_SRC)(const int src1 /*in*/, const int src2 /*in*/, const int amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSR_SRA)(const int src /*in*/, const int amount /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_core_SSR_SRL)(const unsigned int src /*in*/, const int amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_core_SSL_SLL)(const int src /*in*/, const int amount /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_CLAMPS)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_MIN)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_MAX)(const int s /*in*/, const int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_misc_MINU)(const unsigned int s /*in*/, const unsigned int t /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_misc_MAXU)(const unsigned int s /*in*/, const unsigned int t /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_NSA)(const int s /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_misc_NSAU)(const unsigned int s /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_xt_misc_SEXT)(const int s /*in*/, immediate i /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_READ_IPQ)(void);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_CHECK_IPQ)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WRITE_OPQ)(const unsigned int a /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_CHECK_OPQ)(void);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_RUR_EXPSTATE)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WUR_EXPSTATE)(const unsigned int v /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_PERM)(const perm16 a /*in*/, const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_ld_PERM)(const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_ULSR)(const ulsr128 a /*in*/, const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_ld_ULSR)(const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_MIR)(const mir30 a /*in*/, const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_ld_MIR)(const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_CR)(const cr64 a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_ld_CR)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_WR)(const wr64 a /*in*/, const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_ld_WR)(const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr)(vr128* r /*out*/, const vr128 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_set_perm16)(immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_perm16_cond)(perm16* z /*inout*/, immediate perm /*in*/, const xtbool bx /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postR)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postI)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_circI)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxR)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxI)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postR)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_circI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxR)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxI)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postR)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_circI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postR)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postI)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_circI)(vr128* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxR)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxI)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postR)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_circI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxR)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxI)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postR)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_circI)(vr128* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_32x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_24x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_16x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_8x4_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a)(vr128* z /*out*/, ulsr128* buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_24x4_vr_a)(vr128* z /*out*/, ulsr128* buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_16x4_vr_a)(vr128* z /*out*/, ulsr128* buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_8x4_vr_a)(vr128* z /*out*/, ulsr128* buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_circ)(vr128* z /*out*/, ulsr128* buf /*inout*/, const unsigned int ** ptr /*inout*/, const cr64 c /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postR)(wr64* w /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postI)(wr64* w /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxR)(const vr128 z /*in*/, const xtbool4 bx4 /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxI)(const vr128 z /*in*/, const xtbool4 bx4 /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postR)(const vr128 z /*in*/, const xtbool4 bx4 /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postI)(const vr128 z /*in*/, const xtbool4 bx4 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_circI)(const vr128 z /*in*/, const xtbool4 bx4 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxR)(const vr128 z /*in*/, const xtbool2 bx2 /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxI)(const vr128 z /*in*/, const xtbool2 bx2 /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postR)(const vr128 z /*in*/, const xtbool2 bx2 /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postI)(const vr128 z /*in*/, const xtbool2 bx2 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_circI)(const vr128 z /*in*/, const xtbool2 bx2 /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxR)(const vr128 z /*in*/, const xtbool bx /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxI)(const vr128 z /*in*/, const xtbool bx /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postR)(const vr128 z /*in*/, const xtbool bx /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postI)(const vr128 z /*in*/, const xtbool bx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_circI)(const vr128 z /*in*/, const xtbool bx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm)(const vr128 z /*in*/, const vr128 y /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm)(const vr128 z /*in*/, const vr128 y /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm)(const vr128 z /*in*/, const vr128 y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm)(const vr128 z /*in*/, const vr128 y /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm)(const vr128 z /*in*/, const vr128 y /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxR)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxI)(const vr128 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postR)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_circI)(const vr128 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_32x4_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_16x4_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_align_8x4_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a)(const vr128 z /*in*/, ulsr128* buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_24x4_vr_a)(const vr128 z /*in*/, ulsr128* buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_16x4_vr_a)(const vr128 z /*in*/, ulsr128* buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_8x4_vr_a)(const vr128 z /*in*/, ulsr128* buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_circ)(const vr128 z /*in*/, ulsr128* buf /*inout*/, unsigned int ** ptr /*inout*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_32x4)(const ulsr128 buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_24x4)(const ulsr128 buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_16x4)(const ulsr128 buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_8x4)(const ulsr128 buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_2_5)(const unsigned int ar32x /*in*/, const xtbool four /*in*/, immediate odd /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_6_13)(const unsigned int ar32x /*in*/, const xtbool2 idx_spec /*in*/, const xtbool2 ext_size /*in*/, immediate odd /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_next_odd)(const unsigned int ar32x /*in*/, const xtbool4 nbits /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_br_upd_idx_spec)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_build_palindrome)(const unsigned int ar32x /*in*/, const xtbool4 nbits /*in*/, immediate odd /*in*/, immediate shift_type /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load_vr_bdir)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load_vr_brev)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_bdir)(const vr128 z /*in*/, const wr64 w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_bdir)(const vr128 z /*in*/, const wr64 w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_brev)(const vr128 z /*in*/, const wr64 w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_brev)(const vr128 z /*in*/, const wr64 w /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, const xtbool4 br_len /*in*/, immediate msb /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_vrl_postR)(const vr128 z /*in*/, const vr128 y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_vrh_postR)(const vr128 z /*in*/, const vr128 y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_postR)(const vr128 z /*in*/, const wr64 w /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrl_postR)(const wr64 w /*in*/, const vr128 y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_postR)(const vr128 z /*in*/, const wr64 w /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrh_postR)(const wr64 w /*in*/, const vr128 y /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_fr_postI)(fr32* fx /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_fr_postI)(const fr32 fx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_move32_wr_vr)(const vr128 x /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_move32_wr_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_move64_wr_vr)(const vr128 x /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move64_vr_wr)(vr128* z /*inout*/, const wr64 w /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr)(const vr128 x /*in*/, immediate sel2 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr_idx)(const vr128 x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_move32_fr_vr_idx)(const vr128 x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN xtbool2 CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool2)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool4)(const unsigned int ar32x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_eqz)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_gez)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_gtz)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_lez)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_ltz)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_nez)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_move_vr_sat)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_eqz)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gez)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gtz)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_lez)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_ltz)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_nez)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_sat)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_replicate)(vr128* z /*inout*/, immediate sel_code /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_replicate_ar)(vr128* z /*inout*/, immediate sel_code /*in*/, const unsigned int ar /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_creplicate_H)(const vr128 x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_creplicate_L)(const vr128 x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vreplicate)(const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vreplicate_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vreplicate_hr)(const vr64 hx /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_hreplicate_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x1)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x2)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x4)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x1)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x2)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x4)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x1)(vr128* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x2)(vr128* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x4)(vr128* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x1)(vr128* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x2)(vr128* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate half /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x4)(vr128* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_32F_x1)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_32I_x1)(vr128* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4)(vr128* z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4)(vr128* z /*inout*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F)(const unsigned int ar /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float)(const fr32 fx /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_64F)(const unsigned int x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32I)(const vr64 x /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_64F)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32F)(const vr64 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_double_to_64F)(vr64* z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_IEEE_double)(vr64* z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_adj_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_adj_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_perm_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_affine_perm_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_adj_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_adj_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_perm_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_linear_perm_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs6 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xl_wr)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xh_wr)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xl_wr)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xh_wr)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yl)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yl)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yh)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yh)(const wr64 w /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh)(vr128* z /*inout*/, wr64* w1 /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool inv /*in*/, immediate conjX_swap /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmul)(const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmul_conj)(const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmac)(const vr64 hz /*in*/, const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmac_conj)(const vr64 hz /*in*/, const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmas)(const vr64 hz /*in*/, const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_cmas_conj)(const vr64 hz /*in*/, const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmul_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmul_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmac_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmac_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmas_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cmas_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmac_Lx2)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmac_Hx2)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmul_x2)(const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmac_adj_x2)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_cmas_adj_x2)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_xcorr)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_xconv)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_qmul_1)(const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_qmul_2)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate mode /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_matmul_2x2)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vadds)(const vr128 x /*in*/, const vr128 y /*in*/, immediate signs8 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmidp)(const vr128 x /*in*/, const vr128 y /*in*/, immediate signs8 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmuls)(const vr128 x /*in*/, const vr128 y /*in*/, immediate signs8 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmacs_adj)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs8 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmuls_perm)(const vr128 x /*in*/, const vr128 y /*in*/, immediate signs8 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmacs_perm)(const vr128 z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs8 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vssub_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, const wr64 w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vssub_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, const wr64 w /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vssub_x2)(const vr128 x /*in*/, const vr128 y /*in*/, const wr64 w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vinterp_L)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, const wr64 w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vinterp_H)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, const wr64 w /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vinterp_x2)(const vr128 x /*in*/, const vr128 y /*in*/, const wr64 w /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_csums_L)(vr128* z /*inout*/, const vr128 x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_csums_H)(vr128* z /*inout*/, const vr128 x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_dsums_L)(vr128* z /*inout*/, const vr128 x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_dsums_H)(vr128* z /*inout*/, const vr128 x /*in*/, immediate signs6 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vadd_hr)(const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vsub_hr)(const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vmul_hr)(const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vmac_hr)(const vr64 hz /*in*/, const vr64 hx /*in*/, const vr64 hy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fpadd)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fpmul)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fpmac)(fr32* fz /*inout*/, const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fpmul_sum3)(const vr128 x /*in*/, const vr128 y /*in*/, immediate signs3 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vscale)(const fr32 fx /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vscale_adds)(const vr128 z /*in*/, const fr32 fx /*in*/, const vr128 y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fadds)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, immediate signs5 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmacs)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, immediate signs5 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmuls)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, immediate signs5 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmul_sum3)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate signs3 /*in*/, const perm16 perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_dadds)(const vr64 z /*in*/, const vr64 x /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_dmuls)(const vr64 x /*in*/, const vr64 y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_dmacs)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vabs)(const vr128 x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vexp_adj)(const vr128 x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vexp_adji)(const vr128 x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vperm)(const vr128 x /*in*/, const vr128 y /*in*/, const perm16 sel /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vperms)(const vr128 x /*in*/, const vr128 y /*in*/, const perm16 sel /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vpermsi)(const vr128 x /*in*/, const vr128 y /*in*/, immediate signs /*in*/, immediate sel3 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_seta_vr)(vr128* z /*inout*/, immediate sel_code /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vseta_vr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_seta_ar)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_seta_fr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_f_abs)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fclamp)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fclamp_bp)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fclamp_one)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmax)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fmin)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_max_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_min_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_log2)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_pow2)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sigmoid)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_inv)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ratio)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, xtbool4* bz4 /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_atanratio)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const xtbool4 bx4 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_invsqrt)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sine)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cosine)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_log2mul)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, xtbool* bz /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cspow2)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const xtbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_log2_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_pow2_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_sigmoid_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_inv_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_invsqrt_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_sine_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_cosine_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN xtbool2 CSTUB_(_TIE_dmx1a_common_tie_comp)(const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_eq)(const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ge)(const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_gt)(const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_le)(const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_lt)(const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ne)(const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN xtbool2 CSTUB_(_TIE_dmx1a_common_tie_comp_const)(const vr128 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_eq_const)(const vr128 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ge_const)(const vr128 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_gt_const)(const vr128 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_le_const)(const vr128 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_lt_const)(const vr128 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ne_const)(const vr128 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_eq_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ge_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_gt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_le_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_lt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_ne_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_neg_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_abs_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_deqz)(const vr64 x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dgez)(const vr64 x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dgtz)(const vr64 x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dlez)(const vr64 x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dltz)(const vr64 x /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_dnez)(const vr64 x /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_veq)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vge)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vgt)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vle)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vlt)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vne)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_veq_const)(const vr128 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vge_const)(const vr128 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vgt_const)(const vr128 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vle_const)(const vr128 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vlt_const)(const vr128 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_vne_const)(const vr128 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/, immediate mul_rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool bx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_1b4)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool4 bx4 /*in*/, immediate el_bx4 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_eq)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_ge)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_gt)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_le)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_lt)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sel_ne)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/, const xtbool2 bx2 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vsel)(const vr128 x /*in*/, const vr128 y /*in*/, const xtbool4 bx4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_andb1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_andbc1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_orb1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_orbc1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_xorb1)(const xtbool bx /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_andb4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_andbc4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_orb4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_orbc4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_xorb4)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast0_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast0_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast1_maskI)(const xtbool4 bx4 /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_blast1_maskR)(const xtbool4 bx4 /*in*/, const xtbool4 by4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_bgetI)(const xtbool4 bx4 /*in*/, immediate ipos /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_dmx1a_common_tie_bgetR)(const xtbool4 bx4 /*in*/, const unsigned int rpos /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_bsetI)(const xtbool4 bx4 /*in*/, const unsigned int rpos /*in*/, immediate ibit /*in*/);
CSTUB_EXTERN xtbool4 CSTUB_(_TIE_dmx1a_common_tie_bsetR)(const xtbool4 bx4 /*in*/, const unsigned int rpos /*in*/, const xtbool by /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_exp_adj)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_exp_adji)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_exp_adj_fr)(const fr32 fx /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_exp_adji_fr)(const fr32 fx /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_neg)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_copy)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_and)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_andc)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_or)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_orc)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_s_xor)(vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vnegs)(const vr128 x /*in*/, immediate signs /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vcopy)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vand)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vandc)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vor)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vorc)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_s_vxor)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_s_vnegs_hr)(const vr64 hx /*in*/, immediate hr_signs /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_floorp_frac)(unsigned int* floor /*out*/, vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, immediate el_x /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_idx_frac)(unsigned int* floor /*out*/, vr128* z /*inout*/, immediate el_z /*in*/, const unsigned int input /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_truncate_fr)(const fr32 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rmax_idx)(unsigned int* a /*out*/, vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, const mir30 idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rmin_idx)(unsigned int* a /*out*/, vr128* z /*inout*/, immediate el_z /*in*/, const vr128 x /*in*/, const mir30 idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmaxmin_init)(vr128* z /*out*/, const vr128 x /*in*/, mir30* idx /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmax_idx)(vr128* z /*inout*/, const vr128 x /*in*/, mir30* idx /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vmin_idx)(vr128* z /*inout*/, const vr128 x /*in*/, mir30* idx /*inout*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmax)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vmin)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_vr)(unsigned int* a /*out*/, vr128* z /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_vr)(unsigned int* a /*out*/, vr128* z /*out*/, const vr128 x /*in*/, const vr128 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_ar)(unsigned int* a /*inout*/, vr128* z /*out*/, const vr128 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_ar)(unsigned int* a /*inout*/, vr128* z /*out*/, const vr128 x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vbool)(const vr128 x /*in*/, const vr128 y /*in*/, immediate op /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_align_up)(const unsigned int val /*in*/, const unsigned int option /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_range_init)(const unsigned int low /*in*/, const unsigned int high /*in*/, immediate startOp /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_range_check)(xtbool4* bz4 /*out*/, mir30* idx /*inout*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_afloat_exp_extract)(const vr128 x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_exp_shift_amount)(const vr128 input /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_flush_32x4_bounded)(const ulsr128 buf /*in*/, unsigned int ** ptr /*inout*/, mir30* count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_AccExtend_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB0_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30 parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB1_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30 parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB2_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30 parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB3_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30 parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB4_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30 parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB5_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30 parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB6_flex)(const unsigned int * ptr /*in*/, const unsigned int remBlock /*in*/, const mir30 parms /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB7_flex)(const unsigned int ** ptr /*inout*/, const unsigned int remBlock /*in*/, mir30* parms /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB0_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB4_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB5_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB6_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BB7_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_BBx_a_bounded)(ulsr128* buf /*inout*/, const unsigned int ** ptr /*inout*/, mir30* count /*inout*/, const unsigned int sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB4_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB5_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB6_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_VB7_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_bounded)(vr128* z /*out*/, ulsr128* buf /*inout*/, const unsigned int ** ptr /*inout*/, mir30* count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load_lookup_AccExtend_postI)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_load_lookup_vr_postI)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr)(const vr128 vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr)(vr128* z /*inout*/, const vr128 vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idx16vr)(vr128* z /*inout*/, const unsigned int * ptr /*in*/, const vr128 vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool2 signed_xy /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_conv)(vr128* z /*inout*/, const vr128 x /*in*/, const xtbool2 signed_xy /*in*/, immediate shift_in /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_sparse)(vr128* z /*inout*/, const vr128 x /*in*/, const vr128 y /*in*/, const xtbool2 signed_xy /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mir_init)(const unsigned int low /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mov_AccExtend_vr)(const vr128 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mov_BB_vrVB)(const vr128 x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_mov_vr_AccExtend)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_mov_vrVB_BB)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_next_lookup_load)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_next_lookup_store)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_precess_16bits)(const vr128 x /*in*/, const vr128 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rectify32_into8)(vr128* z /*inout*/, const vr128 x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_rnd_sat_pack)(vr128* z /*inout*/, immediate el32 /*in*/, const vr128 x /*in*/, const xtbool sgn /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_BB_zero)(void);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_shift8_into32_arith)(const vr128 x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_shift32_arith)(const vr128 x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_bounded)(const vr128 z /*in*/, ulsr128* buf /*inout*/, unsigned int ** ptr /*inout*/, mir30* count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_AccExtend_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB0_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB4_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB5_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB6_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_BB7_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB4_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB5_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB6_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_VB7_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_lookup_AccExtend_postI)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_store_lookup_vr_postI)(const vr128 z /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_mv_WR)(const wr64 b /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_mv_PERM)(const perm16 b /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mv_MIR)(const mir30 b /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_mv_ULSR)(const ulsr128 b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_mv_CR)(const cr64 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_ld_FR)(const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_ld_FR_idxR)(const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR_idxR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postI)(fr32* fregout /*out*/, const fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR_postI)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postR)(fr32* fregout /*out*/, const fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_FR_postR)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_ld_HR)(const vr64 * addr /*in*/, immediate himm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR)(const vr64 hregin /*in*/, const vr64 * addr /*in*/, immediate himm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_ld_HR_idxR)(const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR_idxR)(const vr64 hregin /*in*/, const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postI)(vr64* hregout /*out*/, const vr64 ** addr /*inout*/, immediate himm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR_postI)(const vr64 hregin /*in*/, vr64 ** addr /*inout*/, immediate himm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postR)(vr64* hregout /*out*/, const vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_HR_postR)(const vr64 hregin /*in*/, vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_ld_VR)(const vr128 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR)(const vr128 vregin /*in*/, const vr128 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_ld_VR_idxR)(const vr128 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR_idxR)(const vr128 vregin /*in*/, const vr128 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postI)(vr128* vregout /*out*/, const vr128 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR_postI)(const vr128 vregin /*in*/, vr128 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postR)(vr128* vregout /*out*/, const vr128 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_VR_postR)(const vr128 vregin /*in*/, vr128 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_mv_FR)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_move_ar_fr)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_move_fr_ar)(const unsigned int b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_mv_HR)(const vr64 b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_mv_VR)(const vr128 b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_pair)(const vr64 hi /*in*/, const vr64 lo /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRL)(vr128* v /*inout*/, const vr64 lo /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRH)(vr128* v /*inout*/, const vr64 hi /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_get_VRL)(const vr128 b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_get_VRH)(const vr128 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ld_ar_x2)(unsigned int* a1_out /*out*/, unsigned int* a0_out /*out*/, const void * ptr /*in*/, immediate idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_st_ar_x2)(const void * ptr /*in*/, immediate idx /*in*/, const unsigned int a1_in /*in*/, const unsigned int a0_in /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_perm16_storei)(const perm16 a /*in*/, const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_perm16_loadi)(const perm16 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_ulsr128_storei)(const ulsr128 a /*in*/, const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_ulsr128_loadi)(const ulsr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_mir30_storei)(const mir30 a /*in*/, const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mir30_loadi)(const mir30 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_cr64_storei)(const cr64 a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_cr64_loadi)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_wr64_storei)(const wr64 a /*in*/, const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_wr64_loadi)(const wr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_JammingBit)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_JammingBit)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_MvmAux)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_MvmAux)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_2)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_2)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_3)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_3)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_RUR_look_state)(void);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_WUR_look_state)(const unsigned int v /*in*/);
CSTUB_EXTERN wr64 CSTUB_(_TIE_dmx1a_common_tie_wr64_move)(const wr64 b /*in*/);
CSTUB_EXTERN perm16 CSTUB_(_TIE_dmx1a_common_tie_perm16_move)(const perm16 b /*in*/);
CSTUB_EXTERN mir30 CSTUB_(_TIE_dmx1a_common_tie_mir30_move)(const mir30 b /*in*/);
CSTUB_EXTERN ulsr128 CSTUB_(_TIE_dmx1a_common_tie_ulsr128_move)(const ulsr128 b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_dmx1a_common_tie_cr64_move)(const cr64 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fr32_move)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fr32_loadi)(const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storei)(const fr32 v /*in*/, const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_fr32_loadx)(const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storex)(const fr32 v /*in*/, const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_loadip)(fr32* v /*out*/, const fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storeip)(const fr32 v /*in*/, fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_loadxp)(fr32* v /*out*/, const fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_fr32_storexp)(const fr32 v /*in*/, fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_int32)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_uint32)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_int32_rtor_fr32)(const int a /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_uint32_rtor_fr32)(const unsigned int a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_move)(const vr64 b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_loadi)(const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storei)(const vr64 v /*in*/, const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_loadx)(const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storex)(const vr64 v /*in*/, const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_loadip)(vr64* v /*out*/, const vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storeip)(const vr64 v /*in*/, vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_loadxp)(vr64* v /*out*/, const vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr64_storexp)(const vr64 v /*in*/, vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN long long CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_int64)(const vr64 b /*in*/);
CSTUB_EXTERN unsigned long long CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_uint64)(const vr64 b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_int64_rtor_vr64)(const long long a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_uint64_rtor_vr64)(const unsigned long long a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_dmx1a_common_tie_vr64_pair)(const fr32 hi /*in*/, const fr32 lo /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_HRL)(const vr64 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_HRH)(const vr64 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_HRL)(vr64* a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_HRH)(vr64* a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_move)(const vr128 b /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_loadi)(const vr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storei)(const vr128 a /*in*/, const vr128 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_loadx)(const vr128 * b /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storex)(const vr128 a /*in*/, const vr128 * b /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_loadip)(vr128* a /*out*/, const vr128 ** b /*inout*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storeip)(const vr128 a /*in*/, vr128 ** b /*inout*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_loadxp)(vr128* a /*out*/, const vr128 ** b /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_vr128_storexp)(const vr128 a /*in*/, vr128 ** b /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr128 CSTUB_(_TIE_dmx1a_common_tie_vr128_quad)(const fr32 q3 /*in*/, const fr32 q2 /*in*/, const fr32 q1 /*in*/, const fr32 q0 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ0)(const vr128 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ1)(const vr128 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ2)(const vr128 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_dmx1a_common_tie_get_VRQ3)(const vr128 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ0)(vr128* a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ1)(vr128* a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ2)(vr128* a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_dmx1a_common_tie_set_VRQ3)(vr128* a /*inout*/, const fr32 b /*in*/);

CSTUB_EXTERN unsigned CSTUB_(_TIE_xt_core_RSR_SAR)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_WSR_SAR)(unsigned t);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_XSR_SAR)(unsigned* t /*inout*/);
/* Proto macros */
#define XT_NOP_N() \
	CSTUB_(_TIE_xt_density_NOP_N)()
#define XT_NOP() \
	CSTUB_(_TIE_xt_core_NOP)()
#define XT_DEPBITS(art, ars, low_depbits, lngth_depbits) \
	CSTUB_(_TIE_xt_core_DEPBITS)(&art, ars, low_depbits, lngth_depbits)
#define XT_XORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_XORB)(bs, bt)
#define XT_ORBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORBC)(bs, bt)
#define XT_ORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORB)(bs, bt)
#define XT_ANDBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDBC)(bs, bt)
#define XT_ANDB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDB)(bs, bt)
#define XT_ALL4(bs4) \
	CSTUB_(_TIE_xt_booleans_ALL4)(bs4)
#define XT_ANY4(bs4) \
	CSTUB_(_TIE_xt_booleans_ANY4)(bs4)
#define XT_ALL8(bs8) \
	CSTUB_(_TIE_xt_booleans_ALL8)(bs8)
#define XT_ANY8(bs8) \
	CSTUB_(_TIE_xt_booleans_ANY8)(bs8)
#define XT_MOVT(arr, ars, bt) \
	CSTUB_(_TIE_xt_booleans_MOVT)(&arr, ars, bt)
#define XT_MOVF(arr, ars, bt) \
	CSTUB_(_TIE_xt_booleans_MOVF)(&arr, ars, bt)
#define READ_IMPWIRE() \
	CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)()
#define SETB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(bitindex)
#define CLRB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(bitindex)
#define WRMSK_EXPSTATE(art, ars) \
	CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(art, ars)
#define XT_L32I_N(p, i) \
	CSTUB_(_TIE_xt_density_L32I_N)(p, i)
#define XT_S32I_N(t, p, i) \
	CSTUB_(_TIE_xt_density_S32I_N)(t, p, i)
#define XT_ADD_N(s, t) \
	CSTUB_(_TIE_xt_density_ADD_N)(s, t)
#define XT_ADDI_N(s, i) \
	CSTUB_(_TIE_xt_density_ADDI_N)(s, i)
#define XT_MOV_N(s) \
	CSTUB_(_TIE_xt_density_MOV_N)(s)
#define XT_MOVI_N(i) \
	CSTUB_(_TIE_xt_density_MOVI_N)(i)
#define XT_uint32_loadi(p, o) \
	CSTUB_(_TIE_xt_core_uint32_loadi)(p, o)
#define XT_uint32_storei(c, p, o) \
	CSTUB_(_TIE_xt_core_uint32_storei)(c, p, o)
#define XT_uint32_move(b) \
	CSTUB_(_TIE_xt_core_uint32_move)(b)
#define XT_ADDI(s, i) \
	CSTUB_(_TIE_xt_core_ADDI)(s, i)
#define XT_OR(s, t) \
	CSTUB_(_TIE_xt_core_OR)(s, t)
#define XT_L32I(p, i) \
	CSTUB_(_TIE_xt_core_L32I)(p, i)
#define XT_S32I(r, p, i) \
	CSTUB_(_TIE_xt_core_S32I)(r, p, i)
#define XT_S32NB(r, p, i) \
	CSTUB_(_TIE_xt_core_S32NB)(r, p, i)
#define XT_L8UI(p, i) \
	CSTUB_(_TIE_xt_core_L8UI)(p, i)
#define XT_S8I(r, p, i) \
	CSTUB_(_TIE_xt_core_S8I)(r, p, i)
#define XT_L16UI(p, i) \
	CSTUB_(_TIE_xt_core_L16UI)(p, i)
#define XT_L16SI(p, i) \
	CSTUB_(_TIE_xt_core_L16SI)(p, i)
#define XT_S16I(r, p, i) \
	CSTUB_(_TIE_xt_core_S16I)(r, p, i)
#define XT_ADDMI(s, i) \
	CSTUB_(_TIE_xt_core_ADDMI)(s, i)
#define XT_ADD(s, t) \
	CSTUB_(_TIE_xt_core_ADD)(s, t)
#define XT_ADDX2(s, t) \
	CSTUB_(_TIE_xt_core_ADDX2)(s, t)
#define XT_ADDX4(s, t) \
	CSTUB_(_TIE_xt_core_ADDX4)(s, t)
#define XT_ADDX8(s, t) \
	CSTUB_(_TIE_xt_core_ADDX8)(s, t)
#define XT_SUB(s, t) \
	CSTUB_(_TIE_xt_core_SUB)(s, t)
#define XT_SUBX2(s, t) \
	CSTUB_(_TIE_xt_core_SUBX2)(s, t)
#define XT_SUBX4(s, t) \
	CSTUB_(_TIE_xt_core_SUBX4)(s, t)
#define XT_SUBX8(s, t) \
	CSTUB_(_TIE_xt_core_SUBX8)(s, t)
#define XT_SALT(s, t) \
	CSTUB_(_TIE_xt_core_SALT)(s, t)
#define XT_SALTU(s, t) \
	CSTUB_(_TIE_xt_core_SALTU)(s, t)
#define XT_AND(s, t) \
	CSTUB_(_TIE_xt_core_AND)(s, t)
#define XT_XOR(s, t) \
	CSTUB_(_TIE_xt_core_XOR)(s, t)
#define XT_EXTUI(t, i, o) \
	CSTUB_(_TIE_xt_core_EXTUI)(t, i, o)
#define XT_MOVI(i) \
	CSTUB_(_TIE_xt_core_MOVI)(i)
#define XT_MOVEQZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVEQZ)(&r, s, t)
#define XT_MOVNEZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVNEZ)(&r, s, t)
#define XT_MOVLTZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVLTZ)(&r, s, t)
#define XT_MOVGEZ(r, s, t) \
	CSTUB_(_TIE_xt_core_MOVGEZ)(&r, s, t)
#define XT_NEG(t) \
	CSTUB_(_TIE_xt_core_NEG)(t)
#define XT_ABS(t) \
	CSTUB_(_TIE_xt_core_ABS)(t)
#define XT_SSR(s) \
	CSTUB_(_TIE_xt_core_SSR)(s)
#define XT_SSL(s) \
	CSTUB_(_TIE_xt_core_SSL)(s)
#define XT_SSA8L(s) \
	CSTUB_(_TIE_xt_core_SSA8L)(s)
#define XT_SSA8B(s) \
	CSTUB_(_TIE_xt_core_SSA8B)(s)
#define XT_SSAI(i) \
	CSTUB_(_TIE_xt_core_SSAI)(i)
#define XT_SLL(s) \
	CSTUB_(_TIE_xt_core_SLL)(s)
#define XT_SRC(s, t) \
	CSTUB_(_TIE_xt_core_SRC)(s, t)
#define XT_SRL(t) \
	CSTUB_(_TIE_xt_core_SRL)(t)
#define XT_SRA(t) \
	CSTUB_(_TIE_xt_core_SRA)(t)
#define XT_SLLI(s, i) \
	CSTUB_(_TIE_xt_core_SLLI)(s, i)
#define XT_SRAI(t, i) \
	CSTUB_(_TIE_xt_core_SRAI)(t, i)
#define XT_SRLI(t, i) \
	CSTUB_(_TIE_xt_core_SRLI)(t, i)
#define XT_SSAI_SRC(src1, src2, amount) \
	CSTUB_(_TIE_xt_core_SSAI_SRC)(src1, src2, amount)
#define XT_SSR_SRC(src1, src2, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRC)(src1, src2, amount)
#define XT_SSR_SRA(src, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRA)(src, amount)
#define XT_SSR_SRL(src, amount) \
	CSTUB_(_TIE_xt_core_SSR_SRL)(src, amount)
#define XT_SSL_SLL(src, amount) \
	CSTUB_(_TIE_xt_core_SSL_SLL)(src, amount)
#define XT_CLAMPS(s, i) \
	CSTUB_(_TIE_xt_misc_CLAMPS)(s, i)
#define XT_MIN(s, t) \
	CSTUB_(_TIE_xt_misc_MIN)(s, t)
#define XT_MAX(s, t) \
	CSTUB_(_TIE_xt_misc_MAX)(s, t)
#define XT_MINU(s, t) \
	CSTUB_(_TIE_xt_misc_MINU)(s, t)
#define XT_MAXU(s, t) \
	CSTUB_(_TIE_xt_misc_MAXU)(s, t)
#define XT_NSA(s) \
	CSTUB_(_TIE_xt_misc_NSA)(s)
#define XT_NSAU(s) \
	CSTUB_(_TIE_xt_misc_NSAU)(s)
#define XT_SEXT(s, i) \
	CSTUB_(_TIE_xt_misc_SEXT)(s, i)
#define READ_IPQ() \
	CSTUB_(_TIE_xt_ioports_READ_IPQ)()
#define CHECK_IPQ() \
	CSTUB_(_TIE_xt_ioports_CHECK_IPQ)()
#define WRITE_OPQ(a) \
	CSTUB_(_TIE_xt_ioports_WRITE_OPQ)(a)
#define CHECK_OPQ() \
	CSTUB_(_TIE_xt_ioports_CHECK_OPQ)()
#define RUR_EXPSTATE() \
	CSTUB_(_TIE_xt_ioports_RUR_EXPSTATE)()
#define WUR_EXPSTATE(v) \
	CSTUB_(_TIE_xt_ioports_WUR_EXPSTATE)(v)
#define st_PERM(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_PERM)(a, b, c)
#define ld_PERM(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_PERM)(b, c)
#define st_ULSR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_ULSR)(a, b, c)
#define ld_ULSR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_ULSR)(b, c)
#define st_MIR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_MIR)(a, b, c)
#define ld_MIR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_MIR)(b, c)
#define st_CR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_CR)(a, b, c)
#define ld_CR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_CR)(b, c)
#define st_WR(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_st_WR)(a, b, c)
#define ld_WR(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_WR)(b, c)
#define load32x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR)((unsigned *)(ptr), ofst)
#define load32x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI)((unsigned *)(ptr), ofst2)
#define load32x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR)(&z, (const unsigned int **)&(ptr), ofst)
#define load32x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2)
#define load32x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c)
#define load32x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR)(&z,(unsigned *)( ptr), ofst, sel1)
#define load32x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI)(&z,(unsigned *)( ptr), ofst2, sel1)
#define load32x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel1)
#define load32x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel1)
#define load32x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#define load32x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR)(&z,(unsigned *)( ptr), ofst, sel2)
#define load32x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI)(&z,(unsigned *)( ptr), ofst2, sel2)
#define load32x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel2)
#define load32x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel2)
#define load32x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel2)
#define load32x4_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#define load32x4_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#define load32x4_vr_postR_perm_vr(r, z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst, perm)
#define load32x4_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst2, perm)
#define load32x4_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst1, c, perm)
#define load32x2_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#define load32x2_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#define load32x2_vr_postR_perm_vr(r, z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst, perm)
#define load32x2_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst2, perm)
#define load32x2_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst1, c, perm)
#define load32x1_vr_idxR_perm_vr(z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr)(z,(unsigned *)( ptr), ofst, perm)
#define load32x1_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr)(z,(unsigned *)( ptr), ofst2, perm)
#define load32x1_vr_postR_perm_vr(r, z, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst, perm)
#define load32x1_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst2, perm)
#define load32x1_vr_circI_perm_vr(r, z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst1, c, perm)
#define set_perm16(perm) \
	CSTUB_(_TIE_dmx1a_common_tie_set_perm16)(perm)
#define set_perm16_cond(z, perm, bx) \
	CSTUB_(_TIE_dmx1a_common_tie_set_perm16_cond)(&z, perm, bx)
#define load16x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxR)((unsigned *)(ptr), ofst)
#define load16x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_idxI)((unsigned *)(ptr), ofst2)
#define load16x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postR)(&z, (const unsigned int **)&(ptr), ofst)
#define load16x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2)
#define load16x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x4_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c)
#define load16x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxR)(&z,(unsigned *)( ptr), ofst, sel1)
#define load16x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_idxI)(&z,(unsigned *)( ptr), ofst2, sel1)
#define load16x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel1)
#define load16x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel1)
#define load16x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x2_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#define load16x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxR)(&z,(unsigned *)( ptr), ofst, sel2)
#define load16x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_idxI)(&z,(unsigned *)( ptr), ofst2, sel2)
#define load16x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel2)
#define load16x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel2)
#define load16x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load16x1_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel2)
#define load8x4_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxR)((unsigned *)(ptr), ofst)
#define load8x4_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_idxI)((unsigned *)(ptr), ofst2)
#define load8x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postR)(&z, (const unsigned int **)&(ptr), ofst)
#define load8x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2)
#define load8x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x4_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c)
#define load8x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxR)(&z,(unsigned *)( ptr), ofst, sel1)
#define load8x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_idxI)(&z,(unsigned *)( ptr), ofst2, sel1)
#define load8x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel1)
#define load8x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel1)
#define load8x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x2_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#define load8x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxR)(&z, ptr, ofst, sel2)
#define load8x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_idxI)(&z,(unsigned *)( ptr), ofst2, sel2)
#define load8x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel2)
#define load8x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel2)
#define load8x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_load8x1_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel2)
#define align_32x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_32x4_load)((unsigned *)(ptr))
#define align_24x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_24x4_load)((unsigned *)(ptr))
#define align_16x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_16x4_load)((unsigned *)(ptr))
#define align_8x4_load(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_8x4_load)((unsigned *)(ptr))
#define load_32x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a)(&z, &buf, (const unsigned int **)&(ptr))
#define load_24x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_24x4_vr_a)(&z, &buf, (const unsigned int **)&(ptr))
#define load_16x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_16x4_vr_a)(&z, &buf, (const unsigned int **)&(ptr))
#define load_8x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_load_8x4_vr_a)(&z, &buf, (const unsigned int **)&(ptr))
#define load_32x4_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_circ)(&z, &buf, (const unsigned int **)&(ptr), c)
#define load32x2_wr_idxR(ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxR)((unsigned *)(ptr), ofst)
#define load32x2_wr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_idxI)((unsigned *)(ptr), ofst2)
#define load32x2_wr_postR(w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postR)(&w, (const unsigned int **)&(ptr), ofst)
#define load32x2_wr_postI(w, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x2_wr_postI)(&w, (const unsigned int **)&(ptr), ofst2)
#define store32x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#define store32x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#define store32x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#define store32x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#define store32x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#define store32x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#define store32x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#define store32x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#define store32x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#define store32x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#define store32x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#define store32x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#define store32x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#define store32x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#define store32x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#define store32x4_vr_br_idxR(z, bx4, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxR)(z, bx4, ptr, ofst)
#define store32x4_vr_br_idxI(z, bx4, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_idxI)(z, bx4, ptr, ofst2)
#define store32x4_vr_br_postR(z, bx4, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postR)(z, bx4, (unsigned int **)&(ptr), ofst)
#define store32x4_vr_br_postI(z, bx4, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_postI)(z, bx4, (unsigned int **)&(ptr), ofst2)
#define store32x4_vr_br_circI(z, bx4, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_br_circI)(z, bx4, (unsigned int **)&(ptr), ofst1, c)
#define store32x2_vr_br_idxR(z, bx2, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxR)(z, bx2, ptr, ofst, sel1)
#define store32x2_vr_br_idxI(z, bx2, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_idxI)(z, bx2, ptr, ofst2, sel1)
#define store32x2_vr_br_postR(z, bx2, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postR)(z, bx2, (unsigned int **)&(ptr), ofst, sel1)
#define store32x2_vr_br_postI(z, bx2, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_postI)(z, bx2, (unsigned int **)&(ptr), ofst2, sel1)
#define store32x2_vr_br_circI(z, bx2, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x2_vr_br_circI)(z, bx2, (unsigned int **)&(ptr), ofst1, c, sel1)
#define store32x1_vr_br_idxR(z, bx, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxR)(z, bx, ptr, ofst, sel2)
#define store32x1_vr_br_idxI(z, bx, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_idxI)(z, bx, ptr, ofst2, sel2)
#define store32x1_vr_br_postR(z, bx, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postR)(z, bx, (unsigned int **)&(ptr), ofst, sel2)
#define store32x1_vr_br_postI(z, bx, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_postI)(z, bx, (unsigned int **)&(ptr), ofst2, sel2)
#define store32x1_vr_br_circI(z, bx, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x1_vr_br_circI)(z, bx, (unsigned int **)&(ptr), ofst1, c, sel2)
#define store32x4_vr_vr_idxR_perm(z, y, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm)(z, y,(unsigned *)( ptr), ofst, perm)
#define store32x4_vr_vr_idxI_perm(z, y, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm)(z, y,(unsigned *)( ptr), ofst2, perm)
#define store32x4_vr_vr_postR_perm(z, y, ptr, ofst, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm)(z, y, (unsigned int **)&(ptr), ofst, perm)
#define store32x4_vr_vr_postI_perm(z, y, ptr, ofst2, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm)(z, y, (unsigned int **)&(ptr), ofst2, perm)
#define store32x4_vr_vr_circI_perm(z, y, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm)(z, y, (unsigned int **)&(ptr), ofst1, c, perm)
#define store16x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#define store16x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#define store16x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#define store16x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#define store16x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#define store16x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#define store16x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#define store16x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#define store16x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#define store16x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#define store16x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxR)(z,(unsigned *)( ptr), ofst, sel2)
#define store16x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#define store16x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#define store16x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#define store16x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store16x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#define store8x4_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxR)(z,(unsigned *)( ptr), ofst)
#define store8x4_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_idxI)(z,(unsigned *)( ptr), ofst2)
#define store8x4_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#define store8x4_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#define store8x4_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x4_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#define store8x2_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxR)(z,(unsigned *)( ptr), ofst, sel1)
#define store8x2_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel1)
#define store8x2_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#define store8x2_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#define store8x2_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#define store8x1_vr_idxR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxR)(z, ptr, ofst, sel2)
#define store8x1_vr_idxI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_idxI)(z,(unsigned *)( ptr), ofst2, sel2)
#define store8x1_vr_postR(z, ptr, ofst, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel2)
#define store8x1_vr_postI(z, ptr, ofst2, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel2)
#define store8x1_vr_circI(z, ptr, ofst1, c, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_store8x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel2)
#define align_32x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_32x4_store)((unsigned *)(ptr))
#define align_16x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_16x4_store)((unsigned *)(ptr))
#define align_8x4_store(ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_align_8x4_store)((unsigned *)(ptr))
#define store_32x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a)(z, &buf, (unsigned int **)&(ptr))
#define store_24x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_24x4_vr_a)(z, &buf, (unsigned int **)&(ptr))
#define store_16x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_16x4_vr_a)(z, &buf, (unsigned int **)&(ptr))
#define store_8x4_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_store_8x4_vr_a)(z, &buf, (unsigned int **)&(ptr))
#define store_32x4_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_circ)(z, &buf, (unsigned int **)&(ptr), c)
#define flush_32x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_32x4)(buf,(unsigned *)( ptr))
#define flush_24x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_24x4)(buf,(unsigned *)( ptr))
#define flush_16x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_16x4)(buf,(unsigned *)( ptr))
#define flush_8x4(buf, ptr) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_8x4)(buf,(unsigned *)( ptr))
#define br_get_idx_2_5(ar32x, four, odd) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_2_5)(ar32x, four, odd)
#define br_get_idx_6_13(ar32x, idx_spec, ext_size, odd) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_6_13)(ar32x, idx_spec, ext_size, odd)
#define br_get_idx_next_odd(ar32x, nbits) \
	CSTUB_(_TIE_dmx1a_common_tie_br_get_idx_next_odd)(ar32x, nbits)
#define br_upd_idx_spec(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_br_upd_idx_spec)(ar32x)
#define build_palindrome(ar32x, nbits, odd, shift_type) \
	CSTUB_(_TIE_dmx1a_common_tie_build_palindrome)(ar32x, nbits, odd, shift_type)
#define load_vr_bdir(ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_load_vr_bdir)((unsigned *)(ptr), ofst, br_len, msb)
#define load_vr_brev(ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_load_vr_brev)((unsigned *)(ptr), ofst, br_len, msb)
#define store_vrl_wr_bdir(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_bdir)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#define store_vrh_wr_bdir(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_bdir)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#define store_vrl_wr_brev(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_brev)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#define store_vrh_wr_brev(z, w, ptr, ofst, br_len, msb) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_brev)(z, w,(unsigned *)( ptr), ofst, br_len, msb)
#define store_vrl_vrl_postR(z, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_vrl_postR)(z, y, (unsigned int **)&(ptr), ofst)
#define store_vrh_vrh_postR(z, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_vrh_postR)(z, y, (unsigned int **)&(ptr), ofst)
#define store_vrl_wr_postR(z, w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrl_wr_postR)(z, w, (unsigned int **)&(ptr), ofst)
#define store_wr_vrl_postR(w, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrl_postR)(w, y, (unsigned int **)&(ptr), ofst)
#define store_vrh_wr_postR(z, w, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_vrh_wr_postR)(z, w, (unsigned int **)&(ptr), ofst)
#define store_wr_vrh_postR(w, y, ptr, ofst) \
	CSTUB_(_TIE_dmx1a_common_tie_store_wr_vrh_postR)(w, y, (unsigned int **)&(ptr), ofst)
#define load_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_fr_postI)(&fx, (const unsigned int **)&(ptr), ofst2)
#define store_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_fr_postI)(fx, (unsigned int **)&(ptr), ofst2)
#define move32_wr_vr(x, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_wr_vr)(x, sel2)
#define move32_wr_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_wr_fr)(fx)
#define move64_wr_vr(x, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_move64_wr_vr)(x, sel1)
#define move64_vr_wr(z, w, sel1) \
	CSTUB_(_TIE_dmx1a_common_tie_move64_vr_wr)(&z, w, sel1)
#define move32_ar_vr(x, sel2) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr)(x, sel2)
#define move32_ar_vr_idx(x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_ar_vr_idx)(x, idx)
#define move32_fr_vr_idx(x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_move32_fr_vr_idx)(x, idx)
#define int_to_xt_bool(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool)(ar32x)
#define int_to_xt_bool2(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool2)(ar32x)
#define int_to_xt_bool4(ar32x) \
	CSTUB_(_TIE_dmx1a_common_tie_int_to_xt_bool4)(ar32x)
#define move_vr_eqz(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_eqz)(&z, el_z, x, el_x, y, el_y)
#define move_vr_gez(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_gez)(&z, el_z, x, el_x, y, el_y)
#define move_vr_gtz(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_gtz)(&z, el_z, x, el_x, y, el_y)
#define move_vr_lez(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_lez)(&z, el_z, x, el_x, y, el_y)
#define move_vr_ltz(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_ltz)(&z, el_z, x, el_x, y, el_y)
#define move_vr_nez(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_nez)(&z, el_z, x, el_x, y, el_y)
#define move_vr_sat(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_move_vr_sat)(&z, el_z, x, el_x, y, el_y)
#define vmove_vr_eqz(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_eqz)(&z, x, y)
#define vmove_vr_gez(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gez)(&z, x, y)
#define vmove_vr_gtz(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_gtz)(&z, x, y)
#define vmove_vr_lez(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_lez)(&z, x, y)
#define vmove_vr_ltz(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_ltz)(&z, x, y)
#define vmove_vr_nez(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_nez)(&z, x, y)
#define vmove_vr_sat(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmove_vr_sat)(&z, x, y)
#define replicate(z, sel_code, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_replicate)(&z, sel_code, x, el_x)
#define replicate_ar(z, sel_code, ar) \
	CSTUB_(_TIE_dmx1a_common_tie_replicate_ar)(&z, sel_code, ar)
#define creplicate_H(x) \
	CSTUB_(_TIE_dmx1a_common_tie_creplicate_H)(x)
#define creplicate_L(x) \
	CSTUB_(_TIE_dmx1a_common_tie_creplicate_L)(x)
#define vreplicate(x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate)(x, el_x)
#define vreplicate_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate_fr)(fx)
#define vreplicate_hr(hx) \
	CSTUB_(_TIE_dmx1a_common_tie_vreplicate_hr)(hx)
#define hreplicate_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_hreplicate_fr)(fx)
#define convert_16I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x1)(&z, exp_fxp, el)
#define convert_16I_to_32F_x2(z, exp_fxp, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x2)(&z, exp_fxp, half)
#define convert_16I_to_32F_x4(z, exp_fxp) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16I_to_32F_x4)(&z, exp_fxp)
#define convert_32F_to_16I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x1)(&z, exp_fxp, rnd, el)
#define convert_32F_to_16I_x2(z, exp_fxp, rnd, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x2)(&z, exp_fxp, rnd, half)
#define convert_32F_to_16I_x4(z, exp_fxp, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16I_x4)(&z, exp_fxp, rnd)
#define convert_32F_to_16F_x1(z, is_signed, exp_bits, bias, round, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x1)(&z, is_signed, exp_bits, bias, round, el)
#define convert_32F_to_16F_x2(z, is_signed, exp_bits, bias, round, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x2)(&z, is_signed, exp_bits, bias, round, half)
#define convert_32F_to_16F_x4(z, is_signed, exp_bits, bias, round) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_16F_x4)(&z, is_signed, exp_bits, bias, round)
#define convert_16F_to_32F_x1(z, is_signed, exp_bits, bias, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x1)(&z, is_signed, exp_bits, bias, el)
#define convert_16F_to_32F_x2(z, is_signed, exp_bits, bias, half) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x2)(&z, is_signed, exp_bits, bias, half)
#define convert_16F_to_32F_x4(z, is_signed, exp_bits, bias) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_16F_to_32F_x4)(&z, is_signed, exp_bits, bias)
#define convert_32I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_32F_x1)(&z, exp_fxp, el)
#define convert_32F_to_32I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_32I_x1)(&z, exp_fxp, rnd, el)
#define convert_IEEE_float_to_32F_x4(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4)(&z)
#define convert_32F_to_IEEE_float_x4(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4)(&z)
#define convert_IEEE_float_to_32F(ar) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_float_to_32F)(ar)
#define convert_32F_to_IEEE_float(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_IEEE_float)(fx)
#define convert_32I_to_64F(x) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32I_to_64F)(x)
#define convert_64F_to_32I(x, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32I)(x, rnd)
#define convert_32F_to_64F(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_32F_to_64F)(fx)
#define convert_64F_to_32F(x) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_32F)(x)
#define convert_IEEE_double_to_64F(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_IEEE_double_to_64F)(&z)
#define convert_64F_to_IEEE_double(z) \
	CSTUB_(_TIE_dmx1a_common_tie_convert_64F_to_IEEE_double)(&z)
#define affine_adj_L(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_adj_L)(&z, x, y, signs6, boost)
#define affine_adj_H(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_adj_H)(&z, x, y, signs6, boost)
#define affine_perm_L(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_perm_L)(&z, x, y, signs6, perm)
#define affine_perm_H(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_affine_perm_H)(&z, x, y, signs6, perm)
#define linear_adj_L(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_adj_L)(&z, x, y, signs6, boost)
#define linear_adj_H(z, x, y, signs6, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_adj_H)(&z, x, y, signs6, boost)
#define linear_perm_L(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_perm_L)(&z, x, y, signs6, perm)
#define linear_perm_H(z, x, y, signs6, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_linear_perm_H)(&z, x, y, signs6, perm)
#define bfly_z_yl_xl_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xl_wr)(w, x, y, inv, conjX_swap)
#define bfly_z_yl_xh_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yl_xh_wr)(w, x, y, inv, conjX_swap)
#define bfly_z_yh_xl_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xl_wr)(w, x, y, inv, conjX_swap)
#define bfly_z_yh_xh_wr(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_yh_xh_wr)(w, x, y, inv, conjX_swap)
#define bfly_z_wr_xl_yl(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yl)(w, x, y, inv, conjX_swap)
#define bfly_z_wr_xh_yl(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yl)(w, x, y, inv, conjX_swap)
#define bfly_z_wr_xl_yh(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xl_yh)(w, x, y, inv, conjX_swap)
#define bfly_z_wr_xh_yh(w, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_z_wr_xh_yh)(w, x, y, inv, conjX_swap)
#define bfly_zl_zl_xl_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl)(&z, &w1, x, y, inv, conjX_swap)
#define bfly_zl_zl_xh_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl)(&z, &w1, x, y, inv, conjX_swap)
#define bfly_zh_zh_xl_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh)(&z, &w1, x, y, inv, conjX_swap)
#define bfly_zh_zh_xh_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh)(&z, &w1, x, y, inv, conjX_swap)
#define bfly_wr_zl_xl_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl)(&z, &w1, x, y, inv, conjX_swap)
#define bfly_wr_zl_xh_yl(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl)(&z, &w1, x, y, inv, conjX_swap)
#define bfly_wr_zh_xl_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh)(&z, &w1, x, y, inv, conjX_swap)
#define bfly_wr_zh_xh_yh(z, w1, x, y, inv, conjX_swap) \
	CSTUB_(_TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh)(&z, &w1, x, y, inv, conjX_swap)
#define cmul(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul)(hx, hy)
#define cmul_conj(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_conj)(hx, hy)
#define cmac(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac)(hz, hx, hy)
#define cmac_conj(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_conj)(hz, hx, hy)
#define cmas(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas)(hz, hx, hy)
#define cmas_conj(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_conj)(hz, hx, hy)
#define cmul_L(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_L)(&z, x, y, mode)
#define cmul_H(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_H)(&z, x, y, mode)
#define cmac_L(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_L)(&z, x, y, mode)
#define cmac_H(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_H)(&z, x, y, mode)
#define cmas_L(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_L)(&z, x, y, mode)
#define cmas_H(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_H)(&z, x, y, mode)
#define cmac_Lx2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_Lx2)(z, x, y, mode)
#define cmac_Hx2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_Hx2)(z, x, y, mode)
#define cmul_x2(x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_cmul_x2)(x, y, mode)
#define cmac_adj_x2(z, x, y, mode, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_cmac_adj_x2)(z, x, y, mode, boost)
#define cmas_adj_x2(z, x, y, mode, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_cmas_adj_x2)(z, x, y, mode, boost)
#define xcorr(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_xcorr)(z, x, y)
#define xconv(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_xconv)(z, x, y)
#define qmul_1(x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_qmul_1)(x, y, mode)
#define qmul_2(z, x, y, mode) \
	CSTUB_(_TIE_dmx1a_common_tie_qmul_2)(&z, x, y, mode)
#define matmul_2x2(z, x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_matmul_2x2)(z, x, y)
#define vadds(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vadds)(x, y, signs8)
#define vmidp(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vmidp)(x, y, signs8)
#define vmuls(x, y, signs8) \
	CSTUB_(_TIE_dmx1a_common_tie_vmuls)(x, y, signs8)
#define vmacs_adj(z, x, y, signs8, boost) \
	CSTUB_(_TIE_dmx1a_common_tie_vmacs_adj)(z, x, y, signs8, boost)
#define vmuls_perm(x, y, signs8, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_vmuls_perm)(x, y, signs8, perm)
#define vmacs_perm(z, x, y, signs8, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_vmacs_perm)(z, x, y, signs8, perm)
#define vssub_L(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_L)(&z, x, y, w)
#define vssub_H(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_H)(&z, x, y, w)
#define vssub_x2(x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vssub_x2)(x, y, w)
#define vinterp_L(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_L)(&z, x, y, w)
#define vinterp_H(z, x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_H)(&z, x, y, w)
#define vinterp_x2(x, y, w) \
	CSTUB_(_TIE_dmx1a_common_tie_vinterp_x2)(x, y, w)
#define csums_L(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_csums_L)(&z, x, signs6, div_by_2_op)
#define csums_H(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_csums_H)(&z, x, signs6, div_by_2_op)
#define dsums_L(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_dsums_L)(&z, x, signs6, div_by_2_op)
#define dsums_H(z, x, signs6, div_by_2_op) \
	CSTUB_(_TIE_dmx1a_common_tie_dsums_H)(&z, x, signs6, div_by_2_op)
#define vadd_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vadd_hr)(hx, hy)
#define vsub_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vsub_hr)(hx, hy)
#define vmul_hr(hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vmul_hr)(hx, hy)
#define vmac_hr(hz, hx, hy) \
	CSTUB_(_TIE_dmx1a_common_tie_vmac_hr)(hz, hx, hy)
#define fpadd(fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpadd)(fx, fy, signs2)
#define fpmul(fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmul)(fx, fy, signs2)
#define fpmac(fz, fx, fy, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmac)(&fz, fx, fy, signs2)
#define fpmul_sum3(x, y, signs3, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_fpmul_sum3)(x, y, signs3, perm)
#define vscale(fx, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vscale)(fx, y)
#define vscale_adds(z, fx, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_vscale_adds)(z, fx, y, signs2)
#define fadds(z, el_z, x, el_x, y, el_y, signs5) \
	CSTUB_(_TIE_dmx1a_common_tie_fadds)(&z, el_z, x, el_x, y, el_y, signs5)
#define fmacs(z, el_z, x, el_x, y, el_y, signs5) \
	CSTUB_(_TIE_dmx1a_common_tie_fmacs)(&z, el_z, x, el_x, y, el_y, signs5)
#define fmuls(z, el_z, x, el_x, y, el_y, signs5) \
	CSTUB_(_TIE_dmx1a_common_tie_fmuls)(&z, el_z, x, el_x, y, el_y, signs5)
#define fmul_sum3(z, el_z, x, y, signs3, perm) \
	CSTUB_(_TIE_dmx1a_common_tie_fmul_sum3)(&z, el_z, x, y, signs3, perm)
#define dadds(z, x, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dadds)(z, x, signs2)
#define dmuls(x, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dmuls)(x, y, signs2)
#define dmacs(z, x, y, signs2) \
	CSTUB_(_TIE_dmx1a_common_tie_dmacs)(z, x, y, signs2)
#define vabs(x) \
	CSTUB_(_TIE_dmx1a_common_tie_vabs)(x)
#define vexp_adj(x, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_vexp_adj)(x, exp_adj_ar)
#define vexp_adji(x, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_vexp_adji)(x, exp_adj_imm)
#define vperm(x, y, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_vperm)(x, y, sel)
#define vperms(x, y, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_vperms)(x, y, sel)
#define vpermsi(x, y, signs, sel3) \
	CSTUB_(_TIE_dmx1a_common_tie_vpermsi)(x, y, signs, sel3)
#define seta_vr(z, sel_code, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_vr)(&z, sel_code, const_idx, exp_adj_const, mul_rnd)
#define vseta_vr(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vseta_vr)(const_idx, exp_adj_const, mul_rnd)
#define seta_ar(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_ar)(const_idx, exp_adj_const, mul_rnd)
#define seta_fr(const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_seta_fr)(const_idx, exp_adj_const, mul_rnd)
#define f_abs(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_f_abs)(&z, el_z, x, el_x)
#define fclamp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp)(&z, el_z, x, el_x, y, el_y)
#define fclamp_bp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp_bp)(&z, el_z, x, el_x, y, el_y)
#define fclamp_one(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_fclamp_one)(&z, el_z, x, el_x)
#define fmax(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fmax)(&z, el_z, x, el_x, y, el_y)
#define fmin(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_fmin)(&z, el_z, x, el_x, y, el_y)
#define max_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_max_fr)(fx, fy)
#define min_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_min_fr)(fx, fy)
#define log2(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_log2)(&z, el_z, x, el_x)
#define pow2(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_pow2)(&z, el_z, x, el_x)
#define sigmoid(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_sigmoid)(&z, el_z, x, el_x)
#define inv(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_inv)(&z, el_z, x, el_x)
#define ratio(z, el_z, x, el_x, y, el_y, bz4) \
	CSTUB_(_TIE_dmx1a_common_tie_ratio)(&z, el_z, x, el_x, y, el_y, &bz4)
#define atanratio(z, el_z, x, el_x, bx4) \
	CSTUB_(_TIE_dmx1a_common_tie_atanratio)(&z, el_z, x, el_x, bx4)
#define invsqrt(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_invsqrt)(&z, el_z, x, el_x)
#define sine(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_sine)(&z, el_z, x, el_x)
#define cosine(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_cosine)(&z, el_z, x, el_x)
#define log2mul(z, el_z, x, el_x, y, el_y, bz) \
	CSTUB_(_TIE_dmx1a_common_tie_log2mul)(&z, el_z, x, el_x, y, el_y, &bz)
#define cspow2(z, el_z, x, el_x, bx) \
	CSTUB_(_TIE_dmx1a_common_tie_cspow2)(&z, el_z, x, el_x, bx)
#define log2_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_log2_fr)(fx)
#define pow2_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_pow2_fr)(fx)
#define sigmoid_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_sigmoid_fr)(fx)
#define inv_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_inv_fr)(fx)
#define invsqrt_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_invsqrt_fr)(fx)
#define sine_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_sine_fr)(fx)
#define cosine_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_cosine_fr)(fx)
#define comp(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_comp)(x, el_x, y, el_y)
#define eq(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_eq)(x, el_x, y, el_y)
#define ge(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_ge)(x, el_x, y, el_y)
#define gt(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_gt)(x, el_x, y, el_y)
#define le(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_le)(x, el_x, y, el_y)
#define lt(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_lt)(x, el_x, y, el_y)
#define ne(x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_ne)(x, el_x, y, el_y)
#define comp_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_comp_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#define eq_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_eq_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#define ge_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_ge_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#define gt_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_gt_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#define le_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_le_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#define lt_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_lt_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#define ne_const(x, el_x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_ne_const)(x, el_x, const_idx, exp_adj_const, mul_rnd)
#define eq_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_eq_fr)(fx, fy)
#define ge_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_ge_fr)(fx, fy)
#define gt_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_gt_fr)(fx, fy)
#define le_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_le_fr)(fx, fy)
#define lt_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_lt_fr)(fx, fy)
#define ne_fr(fx, fy) \
	CSTUB_(_TIE_dmx1a_common_tie_ne_fr)(fx, fy)
#define neg_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_neg_fr)(fx)
#define abs_fr(fx) \
	CSTUB_(_TIE_dmx1a_common_tie_abs_fr)(fx)
#define deqz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_deqz)(x)
#define dgez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dgez)(x)
#define dgtz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dgtz)(x)
#define dlez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dlez)(x)
#define dltz(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dltz)(x)
#define dnez(x) \
	CSTUB_(_TIE_dmx1a_common_tie_dnez)(x)
#define veq(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_veq)(x, y)
#define vge(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vge)(x, y)
#define vgt(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vgt)(x, y)
#define vle(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vle)(x, y)
#define vlt(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vlt)(x, y)
#define vne(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vne)(x, y)
#define veq_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_veq_const)(x, const_idx, exp_adj_const, mul_rnd)
#define vge_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vge_const)(x, const_idx, exp_adj_const, mul_rnd)
#define vgt_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vgt_const)(x, const_idx, exp_adj_const, mul_rnd)
#define vle_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vle_const)(x, const_idx, exp_adj_const, mul_rnd)
#define vlt_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vlt_const)(x, const_idx, exp_adj_const, mul_rnd)
#define vne_const(x, const_idx, exp_adj_const, mul_rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_vne_const)(x, const_idx, exp_adj_const, mul_rnd)
#define sel(z, el_z, x, el_x, y, el_y, bx) \
	CSTUB_(_TIE_dmx1a_common_tie_sel)(&z, el_z, x, el_x, y, el_y, bx)
#define sel_1b4(z, el_z, x, el_x, y, el_y, bx4, el_bx4) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_1b4)(&z, el_z, x, el_x, y, el_y, bx4, el_bx4)
#define sel_eq(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_eq)(&z, el_z, x, el_x, y, el_y, bx2)
#define sel_ge(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_ge)(&z, el_z, x, el_x, y, el_y, bx2)
#define sel_gt(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_gt)(&z, el_z, x, el_x, y, el_y, bx2)
#define sel_le(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_le)(&z, el_z, x, el_x, y, el_y, bx2)
#define sel_lt(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_lt)(&z, el_z, x, el_x, y, el_y, bx2)
#define sel_ne(z, el_z, x, el_x, y, el_y, bx2) \
	CSTUB_(_TIE_dmx1a_common_tie_sel_ne)(&z, el_z, x, el_x, y, el_y, bx2)
#define vsel(x, y, bx4) \
	CSTUB_(_TIE_dmx1a_common_tie_vsel)(x, y, bx4)
#define andb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_andb1)(bx, by)
#define andbc1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_andbc1)(bx, by)
#define orb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_orb1)(bx, by)
#define orbc1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_orbc1)(bx, by)
#define xorb1(bx, by) \
	CSTUB_(_TIE_dmx1a_common_tie_xorb1)(bx, by)
#define andb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_andb4)(bx4, by4)
#define andbc4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_andbc4)(bx4, by4)
#define orb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_orb4)(bx4, by4)
#define orbc4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_orbc4)(bx4, by4)
#define xorb4(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_xorb4)(bx4, by4)
#define bcount0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskI)(bx4, imask)
#define bcount0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount0_maskR)(bx4, by4)
#define bcount1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskI)(bx4, imask)
#define bcount1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bcount1_maskR)(bx4, by4)
#define bfirst0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskI)(bx4, imask)
#define bfirst0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst0_maskR)(bx4, by4)
#define bfirst1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskI)(bx4, imask)
#define bfirst1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_bfirst1_maskR)(bx4, by4)
#define blast0_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_blast0_maskI)(bx4, imask)
#define blast0_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_blast0_maskR)(bx4, by4)
#define blast1_maskI(bx4, imask) \
	CSTUB_(_TIE_dmx1a_common_tie_blast1_maskI)(bx4, imask)
#define blast1_maskR(bx4, by4) \
	CSTUB_(_TIE_dmx1a_common_tie_blast1_maskR)(bx4, by4)
#define bgetI(bx4, ipos) \
	CSTUB_(_TIE_dmx1a_common_tie_bgetI)(bx4, ipos)
#define bgetR(bx4, rpos) \
	CSTUB_(_TIE_dmx1a_common_tie_bgetR)(bx4, rpos)
#define bsetI(bx4, rpos, ibit) \
	CSTUB_(_TIE_dmx1a_common_tie_bsetI)(bx4, rpos, ibit)
#define bsetR(bx4, rpos, by) \
	CSTUB_(_TIE_dmx1a_common_tie_bsetR)(bx4, rpos, by)
#define exp_adj(z, el_z, x, el_x, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adj)(&z, el_z, x, el_x, exp_adj_ar)
#define exp_adji(z, el_z, x, el_x, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adji)(&z, el_z, x, el_x, exp_adj_imm)
#define exp_adj_fr(fx, exp_adj_ar) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adj_fr)(fx, exp_adj_ar)
#define exp_adji_fr(fx, exp_adj_imm) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_adji_fr)(fx, exp_adj_imm)
#define s_neg(z, el_z, x, el_x) \
	CSTUB_(_TIE_dmx1a_common_tie_s_neg)(&z, el_z, x, el_x)
#define s_copy(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_copy)(&z, el_z, x, el_x, y, el_y)
#define s_and(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_and)(&z, el_z, x, el_x, y, el_y)
#define s_andc(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_andc)(&z, el_z, x, el_x, y, el_y)
#define s_or(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_or)(&z, el_z, x, el_x, y, el_y)
#define s_orc(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_orc)(&z, el_z, x, el_x, y, el_y)
#define s_xor(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_xor)(&z, el_z, x, el_x, y, el_y)
#define s_vnegs(x, signs) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vnegs)(x, signs)
#define s_vcopy(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vcopy)(x, y)
#define s_vand(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vand)(x, y)
#define s_vandc(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vandc)(x, y)
#define s_vor(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vor)(x, y)
#define s_vorc(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vorc)(x, y)
#define s_vxor(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vxor)(x, y)
#define s_vnegs_hr(hx, hr_signs) \
	CSTUB_(_TIE_dmx1a_common_tie_s_vnegs_hr)(hx, hr_signs)
#define floorp_frac(floor, z, el_z, x, el_x, nbits) \
	CSTUB_(_TIE_dmx1a_common_tie_floorp_frac)(&floor, &z, el_z, x, el_x, nbits)
#define idx_frac(floor, z, el_z, input, nbits) \
	CSTUB_(_TIE_dmx1a_common_tie_idx_frac)(&floor, &z, el_z, input, nbits)
#define truncate_fr(x) \
	CSTUB_(_TIE_dmx1a_common_tie_truncate_fr)(x)
#define rmax_idx(a, z, el_z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_rmax_idx)(&a, &z, el_z, x, idx)
#define rmin_idx(a, z, el_z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_rmin_idx)(&a, &z, el_z, x, idx)
#define vmaxmin_init(z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_vmaxmin_init)(&z, x, &idx)
#define vmax_idx(z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_vmax_idx)(&z, x, &idx)
#define vmin_idx(z, x, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_vmin_idx)(&z, x, &idx)
#define vmax(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmax)(x, y)
#define vmin(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_vmin)(x, y)
#define sortupd_asc_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_vr)(&a, &z, x, y, el_y)
#define sortupd_des_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_vr)(&a, &z, x, y, el_y)
#define sortupd_asc_ar(a, z, x) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_asc_ar)(&a, &z, x)
#define sortupd_des_ar(a, z, x) \
	CSTUB_(_TIE_dmx1a_common_tie_sortupd_des_ar)(&a, &z, x)
#define vbool(x, y, op) \
	CSTUB_(_TIE_dmx1a_common_tie_vbool)(x, y, op)
#define align_up(val, option) \
	CSTUB_(_TIE_dmx1a_common_tie_align_up)((unsigned)(val), option)
#define range_init(low, high, startOp) \
	CSTUB_(_TIE_dmx1a_common_tie_range_init)(low, high, startOp)
#define range_check(bz4, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_range_check)(&bz4, &idx)
#define afloat_exp_extract(x) \
	CSTUB_(_TIE_dmx1a_common_tie_afloat_exp_extract)(x)
#define exp_shift_amount(input) \
	CSTUB_(_TIE_dmx1a_common_tie_exp_shift_amount)(input)
#define flush_32x4_bounded(buf, ptr, count) \
	CSTUB_(_TIE_dmx1a_common_tie_flush_32x4_bounded)(buf, (unsigned int **)&(ptr), &count)
#define load_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_AccExtend_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB0_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB0_flex)(ptr, remBlock, parms)
#define load_BB1_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB1_flex)(ptr, remBlock, parms)
#define load_BB2_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB2_flex)(ptr, remBlock, parms)
#define load_BB3_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB3_flex)(ptr, remBlock, parms)
#define load_BB4_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB4_flex)(ptr, remBlock, parms)
#define load_BB5_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB5_flex)(ptr, remBlock, parms)
#define load_BB6_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB6_flex)(ptr, remBlock, parms)
#define load_BB7_flex(ptr, remBlock, parms) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB7_flex)((const unsigned int **)&(ptr), remBlock, &parms)
#define load_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB0_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB1_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB2_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB3_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB4_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB5_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB6_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BB7_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BBx_a_bounded(buf, ptr, count, sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load_BBx_a_bounded)(&buf, (const unsigned int **)&(ptr), &count, sel)
#define load_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB1_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB2_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB3_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB4_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB5_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB6_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_load_VB7_postI)((const unsigned int **)&(ptr), ofst2)
#define load_32x4_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_dmx1a_common_tie_load_32x4_vr_a_bounded)(&z, &buf, (const unsigned int **)&(ptr), &count)
#define load_lookup_AccExtend_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_load_lookup_AccExtend_postI)()
#define load_lookup_vr_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_load_lookup_vr_postI)()
#define load32x1_lookup_AccExtend_idx16vr(vidx16, ptr_sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr)(vidx16, ptr_sel)
#define load32x1_lookup_vr_idx16vr(z, vidx16, ptr_sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr)(&z, vidx16, ptr_sel)
#define load32x1_vr_idx16vr(z, ptr, vidx16, ptr_sel) \
	CSTUB_(_TIE_dmx1a_common_tie_load32x1_vr_idx16vr)(&z,(unsigned *)( ptr), vidx16, ptr_sel)
#define mac8bx8b(z, x, y, signed_xy) \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b)(&z, x, y, signed_xy)
#define mac8bx8b_conv(z, x, signed_xy, shift_in) \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_conv)(&z, x, signed_xy, shift_in)
#define mac8bx8b_sparse(z, x, y, signed_xy) \
	CSTUB_(_TIE_dmx1a_common_tie_mac8bx8b_sparse)(&z, x, y, signed_xy)
#define mir_init(low) \
	CSTUB_(_TIE_dmx1a_common_tie_mir_init)(low)
#define mov_AccExtend_vr(x) \
	CSTUB_(_TIE_dmx1a_common_tie_mov_AccExtend_vr)(x)
#define mov_BB_vrVB(x) \
	CSTUB_(_TIE_dmx1a_common_tie_mov_BB_vrVB)(x)
#define mov_vr_AccExtend() \
	CSTUB_(_TIE_dmx1a_common_tie_mov_vr_AccExtend)()
#define mov_vrVB_BB() \
	CSTUB_(_TIE_dmx1a_common_tie_mov_vrVB_BB)()
#define next_lookup_load() \
	CSTUB_(_TIE_dmx1a_common_tie_next_lookup_load)()
#define next_lookup_store() \
	CSTUB_(_TIE_dmx1a_common_tie_next_lookup_store)()
#define precess_16bits(x, y) \
	CSTUB_(_TIE_dmx1a_common_tie_precess_16bits)(x, y)
#define rectify32_into8(z, x, shift, rnd, el32) \
	CSTUB_(_TIE_dmx1a_common_tie_rectify32_into8)(&z, x, shift, rnd, el32)
#define rnd_sat_pack(z, el32, x, sgn) \
	CSTUB_(_TIE_dmx1a_common_tie_rnd_sat_pack)(&z, el32, x, sgn)
#define set_BB_zero() \
	CSTUB_(_TIE_dmx1a_common_tie_set_BB_zero)()
#define shift8_into32_arith(x, shift, rnd, el32) \
	CSTUB_(_TIE_dmx1a_common_tie_shift8_into32_arith)(x, shift, rnd, el32)
#define shift32_arith(x, shift, rnd) \
	CSTUB_(_TIE_dmx1a_common_tie_shift32_arith)(x, shift, rnd)
#define store_32x4_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_dmx1a_common_tie_store_32x4_vr_a_bounded)(z, &buf, (unsigned int **)&(ptr), &count)
#define store_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_AccExtend_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB0_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB1_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB2_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB3_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB4_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB5_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB6_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_BB7_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB1_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB2_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB3_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB4_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB5_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB6_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_dmx1a_common_tie_store_VB7_postI)((unsigned int **)&(ptr), ofst2)
#define store_lookup_AccExtend_postI() \
	CSTUB_(_TIE_dmx1a_common_tie_store_lookup_AccExtend_postI)()
#define store_lookup_vr_postI(z) \
	CSTUB_(_TIE_dmx1a_common_tie_store_lookup_vr_postI)(z)
#define mv_WR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_WR)(b)
#define mv_PERM(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_PERM)(b)
#define mv_MIR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_MIR)(b)
#define mv_ULSR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_ULSR)(b)
#define mv_CR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_CR)(b)
#define ld_FR(addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR)(addr, fimm)
#define st_FR(fregin, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR)(fregin, addr, fimm)
#define ld_FR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_idxR)(addr, x)
#define st_FR_idxR(fregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_idxR)(fregin, addr, x)
#define ld_FR_postI(fregout, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postI)(&fregout, (const fr32 **)&(addr), fimm)
#define st_FR_postI(fregin, addr, fimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_postI)(fregin, (fr32 **)&(addr), fimm)
#define ld_FR_postR(fregout, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_FR_postR)(&fregout, (const fr32 **)&(addr), x)
#define st_FR_postR(fregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_FR_postR)(fregin, (fr32 **)&(addr), x)
#define ld_HR(addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR)(addr, himm)
#define st_HR(hregin, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR)(hregin, addr, himm)
#define ld_HR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_idxR)(addr, x)
#define st_HR_idxR(hregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_idxR)(hregin, addr, x)
#define ld_HR_postI(hregout, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postI)(&hregout, (const vr64 **)&(addr), himm)
#define st_HR_postI(hregin, addr, himm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_postI)(hregin, (vr64 **)&(addr), himm)
#define ld_HR_postR(hregout, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_HR_postR)(&hregout, (const vr64 **)&(addr), x)
#define st_HR_postR(hregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_HR_postR)(hregin, (vr64 **)&(addr), x)
#define ld_VR(addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR)(addr, vimm)
#define st_VR(vregin, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR)(vregin, addr, vimm)
#define ld_VR_idxR(addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_idxR)(addr, x)
#define st_VR_idxR(vregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_idxR)(vregin, addr, x)
#define ld_VR_postI(vregout, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postI)(&vregout, (const vr128 **)&(addr), vimm)
#define st_VR_postI(vregin, addr, vimm) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_postI)(vregin, (vr128 **)&(addr), vimm)
#define ld_VR_postR(vregout, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_VR_postR)(&vregout, (const vr128 **)&(addr), x)
#define st_VR_postR(vregin, addr, x) \
	CSTUB_(_TIE_dmx1a_common_tie_st_VR_postR)(vregin, (vr128 **)&(addr), x)
#define mv_FR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_FR)(b)
#define move_ar_fr(b) \
	CSTUB_(_TIE_dmx1a_common_tie_move_ar_fr)(b)
#define move_fr_ar(b) \
	CSTUB_(_TIE_dmx1a_common_tie_move_fr_ar)(b)
#define mv_HR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_HR)(b)
#define mv_VR(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mv_VR)(b)
#define vr128_pair(hi, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_pair)(hi, lo)
#define set_VRL(v, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRL)(&v, lo)
#define set_VRH(v, hi) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRH)(&v, hi)
#define get_VRL(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRL)(b)
#define get_VRH(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRH)(b)
#define ld_ar_x2(a1_out, a0_out, ptr, idx) \
	CSTUB_(_TIE_dmx1a_common_tie_ld_ar_x2)(&a1_out, &a0_out, ptr, idx)
#define st_ar_x2(ptr, idx, a1_in, a0_in) \
	CSTUB_(_TIE_dmx1a_common_tie_st_ar_x2)(ptr, idx, a1_in, a0_in)
#define perm16_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_storei)(a, b, c)
#define perm16_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_loadi)(b, c)
#define ulsr128_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_storei)(a, b, c)
#define ulsr128_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_loadi)(b, c)
#define mir30_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_storei)(a, b, c)
#define mir30_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_loadi)(b, c)
#define cr64_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_storei)(a, b, c)
#define cr64_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_loadi)(b, c)
#define wr64_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_storei)(a, b, c)
#define wr64_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_loadi)(b, c)
#define RUR_JammingBit() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_JammingBit)()
#define WUR_JammingBit(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_JammingBit)(v)
#define RUR_AccExtend_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_0)()
#define WUR_AccExtend_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_0)(v)
#define RUR_AccExtend_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_1)()
#define WUR_AccExtend_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_1)(v)
#define RUR_AccExtend_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_2)()
#define WUR_AccExtend_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_2)(v)
#define RUR_AccExtend_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_AccExtend_3)()
#define WUR_AccExtend_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_AccExtend_3)(v)
#define RUR_BB0_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_0)()
#define WUR_BB0_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_0)(v)
#define RUR_BB0_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_1)()
#define WUR_BB0_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_1)(v)
#define RUR_BB0_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_2)()
#define WUR_BB0_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_2)(v)
#define RUR_BB0_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB0_3)()
#define WUR_BB0_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB0_3)(v)
#define RUR_BB1_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_0)()
#define WUR_BB1_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_0)(v)
#define RUR_BB1_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_1)()
#define WUR_BB1_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_1)(v)
#define RUR_BB1_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_2)()
#define WUR_BB1_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_2)(v)
#define RUR_BB1_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB1_3)()
#define WUR_BB1_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB1_3)(v)
#define RUR_BB2_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_0)()
#define WUR_BB2_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_0)(v)
#define RUR_BB2_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_1)()
#define WUR_BB2_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_1)(v)
#define RUR_BB2_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_2)()
#define WUR_BB2_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_2)(v)
#define RUR_BB2_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB2_3)()
#define WUR_BB2_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB2_3)(v)
#define RUR_BB3_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_0)()
#define WUR_BB3_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_0)(v)
#define RUR_BB3_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_1)()
#define WUR_BB3_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_1)(v)
#define RUR_BB3_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_2)()
#define WUR_BB3_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_2)(v)
#define RUR_BB3_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB3_3)()
#define WUR_BB3_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB3_3)(v)
#define RUR_BB4_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_0)()
#define WUR_BB4_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_0)(v)
#define RUR_BB4_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_1)()
#define WUR_BB4_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_1)(v)
#define RUR_BB4_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_2)()
#define WUR_BB4_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_2)(v)
#define RUR_BB4_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB4_3)()
#define WUR_BB4_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB4_3)(v)
#define RUR_BB5_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_0)()
#define WUR_BB5_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_0)(v)
#define RUR_BB5_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_1)()
#define WUR_BB5_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_1)(v)
#define RUR_BB5_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_2)()
#define WUR_BB5_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_2)(v)
#define RUR_BB5_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB5_3)()
#define WUR_BB5_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB5_3)(v)
#define RUR_BB6_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_0)()
#define WUR_BB6_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_0)(v)
#define RUR_BB6_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_1)()
#define WUR_BB6_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_1)(v)
#define RUR_BB6_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_2)()
#define WUR_BB6_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_2)(v)
#define RUR_BB6_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB6_3)()
#define WUR_BB6_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB6_3)(v)
#define RUR_BB7_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_0)()
#define WUR_BB7_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_0)(v)
#define RUR_BB7_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_1)()
#define WUR_BB7_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_1)(v)
#define RUR_BB7_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_2)()
#define WUR_BB7_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_2)(v)
#define RUR_BB7_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_BB7_3)()
#define WUR_BB7_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_BB7_3)(v)
#define RUR_MvmAux() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_MvmAux)()
#define WUR_MvmAux(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_MvmAux)(v)
#define RUR_VB1_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_0)()
#define WUR_VB1_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_0)(v)
#define RUR_VB1_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_1)()
#define WUR_VB1_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_1)(v)
#define RUR_VB1_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_2)()
#define WUR_VB1_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_2)(v)
#define RUR_VB1_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB1_3)()
#define WUR_VB1_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB1_3)(v)
#define RUR_VB2_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_0)()
#define WUR_VB2_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_0)(v)
#define RUR_VB2_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_1)()
#define WUR_VB2_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_1)(v)
#define RUR_VB2_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_2)()
#define WUR_VB2_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_2)(v)
#define RUR_VB2_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB2_3)()
#define WUR_VB2_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB2_3)(v)
#define RUR_VB3_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_0)()
#define WUR_VB3_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_0)(v)
#define RUR_VB3_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_1)()
#define WUR_VB3_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_1)(v)
#define RUR_VB3_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_2)()
#define WUR_VB3_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_2)(v)
#define RUR_VB3_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB3_3)()
#define WUR_VB3_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB3_3)(v)
#define RUR_VB4_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_0)()
#define WUR_VB4_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_0)(v)
#define RUR_VB4_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_1)()
#define WUR_VB4_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_1)(v)
#define RUR_VB4_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_2)()
#define WUR_VB4_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_2)(v)
#define RUR_VB4_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB4_3)()
#define WUR_VB4_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB4_3)(v)
#define RUR_VB5_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_0)()
#define WUR_VB5_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_0)(v)
#define RUR_VB5_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_1)()
#define WUR_VB5_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_1)(v)
#define RUR_VB5_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_2)()
#define WUR_VB5_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_2)(v)
#define RUR_VB5_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB5_3)()
#define WUR_VB5_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB5_3)(v)
#define RUR_VB6_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_0)()
#define WUR_VB6_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_0)(v)
#define RUR_VB6_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_1)()
#define WUR_VB6_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_1)(v)
#define RUR_VB6_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_2)()
#define WUR_VB6_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_2)(v)
#define RUR_VB6_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB6_3)()
#define WUR_VB6_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB6_3)(v)
#define RUR_VB7_0() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_0)()
#define WUR_VB7_0(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_0)(v)
#define RUR_VB7_1() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_1)()
#define WUR_VB7_1(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_1)(v)
#define RUR_VB7_2() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_2)()
#define WUR_VB7_2(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_2)(v)
#define RUR_VB7_3() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_VB7_3)()
#define WUR_VB7_3(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_VB7_3)(v)
#define RUR_look_state() \
	CSTUB_(_TIE_dmx1a_common_tie_RUR_look_state)()
#define WUR_look_state(v) \
	CSTUB_(_TIE_dmx1a_common_tie_WUR_look_state)(v)
#define wr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_wr64_move)(b)
#define perm16_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_perm16_move)(b)
#define mir30_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_mir30_move)(b)
#define ulsr128_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_ulsr128_move)(b)
#define cr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_cr64_move)(b)
#define fr32_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_move)(b)
#define fr32_loadi(p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadi)(p, o)
#define fr32_storei(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storei)(v, p, o)
#define fr32_loadx(p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadx)(p, x)
#define fr32_storex(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storex)(v, p, x)
#define fr32_loadip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadip)(&v, (const fr32 **)&(p), o)
#define fr32_storeip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storeip)(v, (fr32 **)&(p), o)
#define fr32_loadxp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_loadxp)(&v, (const fr32 **)&(p), x)
#define fr32_storexp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_storexp)(v, (fr32 **)&(p), x)
#define fr32_rtor_int32(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_int32)(b)
#define fr32_rtor_uint32(b) \
	CSTUB_(_TIE_dmx1a_common_tie_fr32_rtor_uint32)(b)
#define int32_rtor_fr32(a) \
	CSTUB_(_TIE_dmx1a_common_tie_int32_rtor_fr32)(a)
#define uint32_rtor_fr32(a) \
	CSTUB_(_TIE_dmx1a_common_tie_uint32_rtor_fr32)(a)
#define vr64_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_move)(b)
#define vr64_loadi(p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadi)(p, o)
#define vr64_storei(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storei)(v, p, o)
#define vr64_loadx(p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadx)(p, x)
#define vr64_storex(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storex)(v, p, x)
#define vr64_loadip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadip)(&v, (const vr64 **)&(p), o)
#define vr64_storeip(v, p, o) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storeip)(v, (vr64 **)&(p), o)
#define vr64_loadxp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_loadxp)(&v, (const vr64 **)&(p), x)
#define vr64_storexp(v, p, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_storexp)(v, (vr64 **)&(p), x)
#define vr64_rtor_int64(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_int64)(b)
#define vr64_rtor_uint64(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_rtor_uint64)(b)
#define int64_rtor_vr64(a) \
	CSTUB_(_TIE_dmx1a_common_tie_int64_rtor_vr64)(a)
#define uint64_rtor_vr64(a) \
	CSTUB_(_TIE_dmx1a_common_tie_uint64_rtor_vr64)(a)
#define vr64_pair(hi, lo) \
	CSTUB_(_TIE_dmx1a_common_tie_vr64_pair)(hi, lo)
#define get_HRL(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_HRL)(b)
#define get_HRH(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_HRH)(b)
#define set_HRL(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_HRL)(&a, b)
#define set_HRH(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_HRH)(&a, b)
#define vr128_move(b) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_move)(b)
#define vr128_loadi(b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadi)(b, c)
#define vr128_storei(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storei)(a, b, c)
#define vr128_loadx(b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadx)(b, x)
#define vr128_storex(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storex)(a, b, x)
#define vr128_loadip(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadip)(&a, (const vr128 **)&(b), c)
#define vr128_storeip(a, b, c) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storeip)(a, (vr128 **)&(b), c)
#define vr128_loadxp(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_loadxp)(&a, (const vr128 **)&(b), x)
#define vr128_storexp(a, b, x) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_storexp)(a, (vr128 **)&(b), x)
#define vr128_quad(q3, q2, q1, q0) \
	CSTUB_(_TIE_dmx1a_common_tie_vr128_quad)(q3, q2, q1, q0)
#define get_VRQ0(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ0)(b)
#define get_VRQ1(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ1)(b)
#define get_VRQ2(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ2)(b)
#define get_VRQ3(b) \
	CSTUB_(_TIE_dmx1a_common_tie_get_VRQ3)(b)
#define set_VRQ0(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ0)(&a, b)
#define set_VRQ1(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ1)(&a, b)
#define set_VRQ2(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ2)(&a, b)
#define set_VRQ3(a, b) \
	CSTUB_(_TIE_dmx1a_common_tie_set_VRQ3)(&a, b)
#define XT_RSR_SAR() \
	CSTUB_(_TIE_xt_core_RSR_SAR)()

#define XT_WSR_SAR(t) \
	CSTUB_(_TIE_xt_core_WSR_SAR)(t)

#define XT_XSR_SAR(t) \
	CSTUB_(_TIE_xt_core_XSR_SAR)((unsigned *)&t)

#endif /* __cplusplus */

/* User register read/write functions */
#define RTHREADPTR RUR_THREADPTR
#define WTHREADPTR WUR_THREADPTR
#define RUR231 RUR_THREADPTR
#define WUR231 WUR_THREADPTR

#define REXPSTATE RUR_EXPSTATE
#define WEXPSTATE WUR_EXPSTATE
#define RUR230 RUR_EXPSTATE
#define WUR230 WUR_EXPSTATE

#define RJammingBit RUR_JammingBit
#define WJammingBit WUR_JammingBit
#define RUR0 RUR_JammingBit
#define WUR0 WUR_JammingBit

#define RAccExtend_0 RUR_AccExtend_0
#define WAccExtend_0 WUR_AccExtend_0
#define RUR1 RUR_AccExtend_0
#define WUR1 WUR_AccExtend_0

#define RAccExtend_1 RUR_AccExtend_1
#define WAccExtend_1 WUR_AccExtend_1
#define RUR2 RUR_AccExtend_1
#define WUR2 WUR_AccExtend_1

#define RAccExtend_2 RUR_AccExtend_2
#define WAccExtend_2 WUR_AccExtend_2
#define RUR3 RUR_AccExtend_2
#define WUR3 WUR_AccExtend_2

#define RAccExtend_3 RUR_AccExtend_3
#define WAccExtend_3 WUR_AccExtend_3
#define RUR4 RUR_AccExtend_3
#define WUR4 WUR_AccExtend_3

#define RBB0_0 RUR_BB0_0
#define WBB0_0 WUR_BB0_0
#define RUR5 RUR_BB0_0
#define WUR5 WUR_BB0_0

#define RBB0_1 RUR_BB0_1
#define WBB0_1 WUR_BB0_1
#define RUR6 RUR_BB0_1
#define WUR6 WUR_BB0_1

#define RBB0_2 RUR_BB0_2
#define WBB0_2 WUR_BB0_2
#define RUR7 RUR_BB0_2
#define WUR7 WUR_BB0_2

#define RBB0_3 RUR_BB0_3
#define WBB0_3 WUR_BB0_3
#define RUR8 RUR_BB0_3
#define WUR8 WUR_BB0_3

#define RBB1_0 RUR_BB1_0
#define WBB1_0 WUR_BB1_0
#define RUR9 RUR_BB1_0
#define WUR9 WUR_BB1_0

#define RBB1_1 RUR_BB1_1
#define WBB1_1 WUR_BB1_1
#define RUR10 RUR_BB1_1
#define WUR10 WUR_BB1_1

#define RBB1_2 RUR_BB1_2
#define WBB1_2 WUR_BB1_2
#define RUR11 RUR_BB1_2
#define WUR11 WUR_BB1_2

#define RBB1_3 RUR_BB1_3
#define WBB1_3 WUR_BB1_3
#define RUR12 RUR_BB1_3
#define WUR12 WUR_BB1_3

#define RBB2_0 RUR_BB2_0
#define WBB2_0 WUR_BB2_0
#define RUR13 RUR_BB2_0
#define WUR13 WUR_BB2_0

#define RBB2_1 RUR_BB2_1
#define WBB2_1 WUR_BB2_1
#define RUR14 RUR_BB2_1
#define WUR14 WUR_BB2_1

#define RBB2_2 RUR_BB2_2
#define WBB2_2 WUR_BB2_2
#define RUR15 RUR_BB2_2
#define WUR15 WUR_BB2_2

#define RBB2_3 RUR_BB2_3
#define WBB2_3 WUR_BB2_3
#define RUR16 RUR_BB2_3
#define WUR16 WUR_BB2_3

#define RBB3_0 RUR_BB3_0
#define WBB3_0 WUR_BB3_0
#define RUR17 RUR_BB3_0
#define WUR17 WUR_BB3_0

#define RBB3_1 RUR_BB3_1
#define WBB3_1 WUR_BB3_1
#define RUR18 RUR_BB3_1
#define WUR18 WUR_BB3_1

#define RBB3_2 RUR_BB3_2
#define WBB3_2 WUR_BB3_2
#define RUR19 RUR_BB3_2
#define WUR19 WUR_BB3_2

#define RBB3_3 RUR_BB3_3
#define WBB3_3 WUR_BB3_3
#define RUR20 RUR_BB3_3
#define WUR20 WUR_BB3_3

#define RBB4_0 RUR_BB4_0
#define WBB4_0 WUR_BB4_0
#define RUR21 RUR_BB4_0
#define WUR21 WUR_BB4_0

#define RBB4_1 RUR_BB4_1
#define WBB4_1 WUR_BB4_1
#define RUR22 RUR_BB4_1
#define WUR22 WUR_BB4_1

#define RBB4_2 RUR_BB4_2
#define WBB4_2 WUR_BB4_2
#define RUR23 RUR_BB4_2
#define WUR23 WUR_BB4_2

#define RBB4_3 RUR_BB4_3
#define WBB4_3 WUR_BB4_3
#define RUR24 RUR_BB4_3
#define WUR24 WUR_BB4_3

#define RBB5_0 RUR_BB5_0
#define WBB5_0 WUR_BB5_0
#define RUR25 RUR_BB5_0
#define WUR25 WUR_BB5_0

#define RBB5_1 RUR_BB5_1
#define WBB5_1 WUR_BB5_1
#define RUR26 RUR_BB5_1
#define WUR26 WUR_BB5_1

#define RBB5_2 RUR_BB5_2
#define WBB5_2 WUR_BB5_2
#define RUR27 RUR_BB5_2
#define WUR27 WUR_BB5_2

#define RBB5_3 RUR_BB5_3
#define WBB5_3 WUR_BB5_3
#define RUR28 RUR_BB5_3
#define WUR28 WUR_BB5_3

#define RBB6_0 RUR_BB6_0
#define WBB6_0 WUR_BB6_0
#define RUR29 RUR_BB6_0
#define WUR29 WUR_BB6_0

#define RBB6_1 RUR_BB6_1
#define WBB6_1 WUR_BB6_1
#define RUR30 RUR_BB6_1
#define WUR30 WUR_BB6_1

#define RBB6_2 RUR_BB6_2
#define WBB6_2 WUR_BB6_2
#define RUR31 RUR_BB6_2
#define WUR31 WUR_BB6_2

#define RBB6_3 RUR_BB6_3
#define WBB6_3 WUR_BB6_3
#define RUR32 RUR_BB6_3
#define WUR32 WUR_BB6_3

#define RBB7_0 RUR_BB7_0
#define WBB7_0 WUR_BB7_0
#define RUR33 RUR_BB7_0
#define WUR33 WUR_BB7_0

#define RBB7_1 RUR_BB7_1
#define WBB7_1 WUR_BB7_1
#define RUR34 RUR_BB7_1
#define WUR34 WUR_BB7_1

#define RBB7_2 RUR_BB7_2
#define WBB7_2 WUR_BB7_2
#define RUR35 RUR_BB7_2
#define WUR35 WUR_BB7_2

#define RBB7_3 RUR_BB7_3
#define WBB7_3 WUR_BB7_3
#define RUR36 RUR_BB7_3
#define WUR36 WUR_BB7_3

#define RMvmAux RUR_MvmAux
#define WMvmAux WUR_MvmAux
#define RUR37 RUR_MvmAux
#define WUR37 WUR_MvmAux

#define RVB1_0 RUR_VB1_0
#define WVB1_0 WUR_VB1_0
#define RUR38 RUR_VB1_0
#define WUR38 WUR_VB1_0

#define RVB1_1 RUR_VB1_1
#define WVB1_1 WUR_VB1_1
#define RUR39 RUR_VB1_1
#define WUR39 WUR_VB1_1

#define RVB1_2 RUR_VB1_2
#define WVB1_2 WUR_VB1_2
#define RUR40 RUR_VB1_2
#define WUR40 WUR_VB1_2

#define RVB1_3 RUR_VB1_3
#define WVB1_3 WUR_VB1_3
#define RUR41 RUR_VB1_3
#define WUR41 WUR_VB1_3

#define RVB2_0 RUR_VB2_0
#define WVB2_0 WUR_VB2_0
#define RUR42 RUR_VB2_0
#define WUR42 WUR_VB2_0

#define RVB2_1 RUR_VB2_1
#define WVB2_1 WUR_VB2_1
#define RUR43 RUR_VB2_1
#define WUR43 WUR_VB2_1

#define RVB2_2 RUR_VB2_2
#define WVB2_2 WUR_VB2_2
#define RUR44 RUR_VB2_2
#define WUR44 WUR_VB2_2

#define RVB2_3 RUR_VB2_3
#define WVB2_3 WUR_VB2_3
#define RUR45 RUR_VB2_3
#define WUR45 WUR_VB2_3

#define RVB3_0 RUR_VB3_0
#define WVB3_0 WUR_VB3_0
#define RUR46 RUR_VB3_0
#define WUR46 WUR_VB3_0

#define RVB3_1 RUR_VB3_1
#define WVB3_1 WUR_VB3_1
#define RUR47 RUR_VB3_1
#define WUR47 WUR_VB3_1

#define RVB3_2 RUR_VB3_2
#define WVB3_2 WUR_VB3_2
#define RUR48 RUR_VB3_2
#define WUR48 WUR_VB3_2

#define RVB3_3 RUR_VB3_3
#define WVB3_3 WUR_VB3_3
#define RUR49 RUR_VB3_3
#define WUR49 WUR_VB3_3

#define RVB4_0 RUR_VB4_0
#define WVB4_0 WUR_VB4_0
#define RUR50 RUR_VB4_0
#define WUR50 WUR_VB4_0

#define RVB4_1 RUR_VB4_1
#define WVB4_1 WUR_VB4_1
#define RUR51 RUR_VB4_1
#define WUR51 WUR_VB4_1

#define RVB4_2 RUR_VB4_2
#define WVB4_2 WUR_VB4_2
#define RUR52 RUR_VB4_2
#define WUR52 WUR_VB4_2

#define RVB4_3 RUR_VB4_3
#define WVB4_3 WUR_VB4_3
#define RUR53 RUR_VB4_3
#define WUR53 WUR_VB4_3

#define RVB5_0 RUR_VB5_0
#define WVB5_0 WUR_VB5_0
#define RUR54 RUR_VB5_0
#define WUR54 WUR_VB5_0

#define RVB5_1 RUR_VB5_1
#define WVB5_1 WUR_VB5_1
#define RUR55 RUR_VB5_1
#define WUR55 WUR_VB5_1

#define RVB5_2 RUR_VB5_2
#define WVB5_2 WUR_VB5_2
#define RUR56 RUR_VB5_2
#define WUR56 WUR_VB5_2

#define RVB5_3 RUR_VB5_3
#define WVB5_3 WUR_VB5_3
#define RUR57 RUR_VB5_3
#define WUR57 WUR_VB5_3

#define RVB6_0 RUR_VB6_0
#define WVB6_0 WUR_VB6_0
#define RUR58 RUR_VB6_0
#define WUR58 WUR_VB6_0

#define RVB6_1 RUR_VB6_1
#define WVB6_1 WUR_VB6_1
#define RUR59 RUR_VB6_1
#define WUR59 WUR_VB6_1

#define RVB6_2 RUR_VB6_2
#define WVB6_2 WUR_VB6_2
#define RUR60 RUR_VB6_2
#define WUR60 WUR_VB6_2

#define RVB6_3 RUR_VB6_3
#define WVB6_3 WUR_VB6_3
#define RUR61 RUR_VB6_3
#define WUR61 WUR_VB6_3

#define RVB7_0 RUR_VB7_0
#define WVB7_0 WUR_VB7_0
#define RUR62 RUR_VB7_0
#define WUR62 WUR_VB7_0

#define RVB7_1 RUR_VB7_1
#define WVB7_1 WUR_VB7_1
#define RUR63 RUR_VB7_1
#define WUR63 WUR_VB7_1

#define RVB7_2 RUR_VB7_2
#define WVB7_2 WUR_VB7_2
#define RUR64 RUR_VB7_2
#define WUR64 WUR_VB7_2

#define RVB7_3 RUR_VB7_3
#define WVB7_3 WUR_VB7_3
#define RUR65 RUR_VB7_3
#define WUR65 WUR_VB7_3

#define Rlook_state RUR_look_state
#define Wlook_state WUR_look_state
#define RUR66 RUR_look_state
#define WUR66 WUR_look_state

#ifndef RUR
#define RUR(NUM) RUR##NUM()
#endif /* RUR */

#ifndef WUR
#define WUR(VAL, NUM) WUR##NUM(VAL)
#endif /* WUR */

/* Registration functions for external interfaces */
CSTUB_EXTERN void CSTUB_(register_EXPSTATE)(void *user_object, cstub_ExportState_func_t callback);

CSTUB_EXTERN void CSTUB_(register_ERI_RD)(void *user_object, cstub_Lookup_func_t callback);

CSTUB_EXTERN void CSTUB_(register_ERI_WR)(void *user_object, cstub_Lookup_func_t callback);

CSTUB_EXTERN void CSTUB_(register_IPQ)(void *user_object, cstub_InputQueue_Empty_func_t empty_callback, cstub_InputQueue_Data_func_t data_callback);

CSTUB_EXTERN void CSTUB_(register_OPQ)(void *user_object, cstub_OutputQueue_Full_func_t full_callback, cstub_OutputQueue_Data_func_t data_callback);

CSTUB_EXTERN void CSTUB_(register_IMPWIRE)(void *user_object, cstub_ImportWire_func_t callback);

CSTUB_EXTERN void CSTUB_(register_lookup_ld)(void *user_object, cstub_Lookup_func_t callback);

CSTUB_EXTERN void CSTUB_(register_lookup_st)(void *user_object, cstub_Lookup_func_t callback);


#endif /* !CSTUB_Xm_dmx1a_HEADER */
