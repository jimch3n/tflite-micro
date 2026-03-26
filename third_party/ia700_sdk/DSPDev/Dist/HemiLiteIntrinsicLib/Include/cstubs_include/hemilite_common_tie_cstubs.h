/*
 * Customer ID=7864; Build=0x90949; Copyright (c) 2006-2010 by Tensilica Inc.  ALL RIGHTS RESERVED.
 * These coded instructions, statements, and computer programs are the.
 * copyrighted works and confidential proprietary information of Tensilica Inc..
 * They may not be modified, copied, reproduced, distributed, or disclosed to.
 * third parties in any manner, medium, or form, in whole or in part, without.
 * the prior written consent of Tensilica Inc..
 */

/* Do not modify. This is automatically generated.*/

#ifndef CSTUB_Xm_hemilite_shapiro_RI04_HEADER
#define CSTUB_Xm_hemilite_shapiro_RI04_HEADER

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

#define CSTUB_(X) cstub_##X

/* Ctype macros */
#define xtbool CSTUB_(xtbool)
#define xtbool2 CSTUB_(xtbool2)
#define xtbool4 CSTUB_(xtbool4)
#define xtbool8 CSTUB_(xtbool8)
#define xtbool16 CSTUB_(xtbool16)
#define fr32 CSTUB_(fr32)
#define vr64 CSTUB_(vr64)
#define cr64 CSTUB_(cr64)
#define mir18 CSTUB_(mir18)
#define ulsr32 CSTUB_(ulsr32)
#define atbool CSTUB_(atbool)

#if defined(__cplusplus)
/* Ctype declarations */
typedef int immediate;
#define DECLARE_CTYPE(s) \
    namespace s##_space { \
    class s##_; \
    } \
    typedef s##_space::s##_ s;

DECLARE_CTYPE(xtbool)
DECLARE_CTYPE(xtbool2)
DECLARE_CTYPE(xtbool4)
DECLARE_CTYPE(xtbool8)
DECLARE_CTYPE(xtbool16)
DECLARE_CTYPE(fr32)
DECLARE_CTYPE(vr64)
DECLARE_CTYPE(cr64)
DECLARE_CTYPE(mir18)
DECLARE_CTYPE(ulsr32)
DECLARE_CTYPE(atbool)

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
} CSTUB_GCC_ALIGN(4);
}

namespace vr64_space {
CSTUB_MSC_ALIGN(8) class vr64_ {
public:
unsigned int _[2];
vr64_ () {}
inline vr64_& operator= (const vr64_ &src);
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

namespace mir18_space {
CSTUB_MSC_ALIGN(4) class mir18_ {
public:
unsigned int _[1];
mir18_ () {}
inline mir18_& operator= (const mir18_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(4);
}

namespace ulsr32_space {
CSTUB_MSC_ALIGN(4) class ulsr32_ {
public:
unsigned int _[1];
ulsr32_ () {}
inline ulsr32_& operator= (const ulsr32_ &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(4);
}

namespace atbool_space {
CSTUB_MSC_ALIGN(1) class atbool_ {
public:
unsigned char  _[1];
atbool_ () {}
inline atbool_& operator= (const atbool_ &src);
inline atbool_ (const unsigned int &src);
inline atbool_& operator= (const unsigned int &src);
inline atbool_ (const int &src);
inline atbool_& operator= (const int &src);
template <typename T_> inline operator T_() const;
} CSTUB_GCC_ALIGN(1);
}

/* Proto declarations */
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
CSTUB_EXTERN void CSTUB_(_TIE_xt_density_NOP_N)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_NOP)(void);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_XORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVF)(unsigned int& arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVT)(unsigned int& arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(const unsigned int art /*in*/, const unsigned int ars /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_atbool_storei)(const atbool& a /*in*/, const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_atbool_loadi)(const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_atbool_move)(const atbool& b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ulsr32_storei)(const ulsr32 a /*in*/, const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_ulsr32_loadi)(const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mir18_storei)(const mir18& a /*in*/, const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mir18_loadi)(const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_cr64_storei)(const cr64& a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_cr64_loadi)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_JammingBit)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_JammingBit)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_MvmAux)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_MvmAux)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_1)(const unsigned int v /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mir18_move)(const mir18& b /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_ulsr32_move)(const ulsr32 b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_cr64_move)(const cr64& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fr32_move)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fr32_loadi)(const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storei)(const fr32 v /*in*/, const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fr32_loadx)(const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storex)(const fr32 v /*in*/, const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_loadip)(fr32& v /*out*/, const fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storeip)(const fr32 v /*in*/, fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_loadxp)(fr32& v /*out*/, const fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storexp)(const fr32 v /*in*/, fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_int32)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_uint32)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_int32_rtor_fr32)(const int a /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_fr32)(const unsigned int a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_move)(const vr64& b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_loadi)(const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storei)(const vr64& v /*in*/, const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_loadx)(const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storex)(const vr64& v /*in*/, const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_loadip)(vr64& v /*out*/, const vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storeip)(const vr64& v /*in*/, vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_loadxp)(vr64& v /*out*/, const vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storexp)(const vr64& v /*in*/, vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_get_VRH)(const vr64& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_get_VRL)(const vr64& b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_set_VRH)(vr64& a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_set_VRL)(vr64& a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_pair)(const fr32 hi /*in*/, const fr32 lo /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_int32)(const atbool& b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_uint32)(const atbool& b /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_int32_rtor_atbool)(const int a /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_atbool)(const unsigned int a /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_BBR)(const atbool& a /*in*/, const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_ld_BBR)(const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_mv_BBR)(const atbool& b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_ULSR)(const ulsr32 a /*in*/, const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_ld_ULSR)(const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_MIR)(const mir18& a /*in*/, const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_ld_MIR)(const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_CR)(const cr64& a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_ld_CR)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_ld)(const unsigned int * src /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_align_ld)(const unsigned int ** src /*inout*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_ldu)(const unsigned int ** src /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_flush_ld)(const unsigned int ** src /*inout*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_st)(const unsigned int * src /*in*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_align_st)(const unsigned int * src /*in*/, unsigned int ** dst /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_stu)(const unsigned int * src /*in*/, unsigned int ** dst /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_flush_st)(const unsigned int * src /*in*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_buf_save)(unsigned int ** dst /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_bdir)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_brev)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR_perm)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI_perm_vr)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR_perm)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI_perm_vr)(vr64& r /*out*/, const vr64& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI_perm)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR_perm)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI_perm_vr)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR_perm)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI_perm_vr)(vr64& r /*out*/, const vr64& z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI_perm)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postR)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postI)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_circI)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxR)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxI)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postR)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postI)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_circI)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postR)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postI)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_circI)(vr64& z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxR)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxI)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postR)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postI)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_circI)(vr64& z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_align_32x2_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a)(vr64& z /*out*/, ulsr32& buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_24x2_vr_a)(vr64& z /*out*/, ulsr32& buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_circ)(vr64& z /*out*/, ulsr32& buf /*inout*/, const unsigned int ** ptr /*inout*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxR)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxI)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postR)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_circI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxR)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxI)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postR)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_circI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxR)(const vr64& z /*in*/, const atbool& gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxI)(const vr64& z /*in*/, const atbool& gate /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postR)(const vr64& z /*in*/, const atbool& gate /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postI)(const vr64& z /*in*/, const atbool& gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_circI)(const vr64& z /*in*/, const atbool& gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxR)(const vr64& z /*in*/, const atbool& gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxI)(const vr64& z /*in*/, const atbool& gate /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postR)(const vr64& z /*in*/, const atbool& gate /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postI)(const vr64& z /*in*/, const atbool& gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_circI)(const vr64& z /*in*/, const atbool& gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_bdir)(const vr64& z /*in*/, const atbool& gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_brev)(const vr64& z /*in*/, const atbool& gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxR)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxI)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postR)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_circI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxR)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxI)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postR)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_circI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxR)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxI)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postR)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_circI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxR)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxI)(const vr64& z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postR)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_circI)(const vr64& z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64& c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_align_32x2_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a)(const vr64& z /*in*/, ulsr32& buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_24x2_vr_a)(const vr64& z /*in*/, ulsr32& buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_circ)(const vr64& z /*in*/, ulsr32& buf /*inout*/, unsigned int ** ptr /*inout*/, const cr64& c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_flush_32x2)(const ulsr32 buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_fr_postI)(fr32& fx /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_fr_postI)(const fr32 fx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_brev_upd)(atbool& gate /*out*/, unsigned int& idx_out /*out*/, const unsigned int idx_in /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_brev_upd_ext)(atbool& gate /*inout*/, unsigned int& idx_out /*inout*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr)(const vr64& x /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move32_vr_ar)(vr64& z /*inout*/, immediate sel1 /*in*/, const unsigned int a /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr_idx)(const vr64& x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_move32_fr_vr_idx)(const vr64& x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_eqz)(fr32& z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_gez)(fr32& z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_gtz)(fr32& z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_lez)(fr32& z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_ltz)(fr32& z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_nez)(fr32& z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_sat)(fr32& z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_arnz)(fr32& z /*inout*/, const fr32 x /*in*/, const unsigned int ax /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_eqz)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gez)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gtz)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_lez)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_ltz)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_nez)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_sat)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_replicate)(vr64& z /*inout*/, immediate sel_code /*in*/, const vr64& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_replicate_ar)(vr64& z /*inout*/, immediate sel_code /*in*/, const unsigned int ar /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vreplicate)(const vr64& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vreplicate_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x1)(vr64& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x2)(vr64& z /*inout*/, const unsigned int exp_fxp /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x1)(vr64& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x2)(vr64& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x1)(vr64& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x2)(vr64& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x1)(vr64& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x2)(vr64& z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_32F_x1)(vr64& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_32I_x1)(vr64& z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_float_to_32F_x2)(vr64& z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_IEEE_float_x2)(vr64& z /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_64F)(const unsigned int x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32I)(const vr64& x /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_64F)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32F)(const vr64& x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_double_to_64F)(vr64& z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_IEEE_double)(vr64& z /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vadd_perm)(const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vsum_perm)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate sign_z /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmul_perm)(const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs2 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmac_perm)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs2 /*in*/, immediate sign_z /*in*/, immediate swap_z /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmac_boost)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs2 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vblend)(const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vblend_add)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate sign_z /*in*/, immediate swap_z /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vblend_boost)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fadds)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fmuls)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fmacs)(const fr32 fz /*in*/, const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_dadds)(const vr64& z /*in*/, const vr64& x /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_dmuls)(const vr64& x /*in*/, const vr64& y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_dmacs)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vadds)(const vr64& x /*in*/, const vr64& y /*in*/, immediate signs4 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmuls)(const vr64& x /*in*/, const vr64& y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmacs)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate signs2 /*in*/, immediate sign_z /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_cmul)(const vr64& x /*in*/, const vr64& y /*in*/, immediate conj /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_cmac)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate conj /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_cmas)(const vr64& z /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate conj /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmulf)(const vr64& x /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmacf)(const vr64& z /*in*/, const vr64& x /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/, immediate sign_z /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vabs)(const vr64& x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vexp_adj)(const vr64& x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vexp_adji)(const vr64& x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vpermi)(const vr64& x /*in*/, const vr64& y /*in*/, immediate sel4 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_seta_vr)(vr64& z /*inout*/, immediate sel_code /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vseta_vr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_seta_ar)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_seta_fr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_AccExtend_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idx16vr)(vr64& z /*inout*/, const unsigned int * ptr /*in*/, const vr64& vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB0_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB4_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB5_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB6_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB7_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_bounded)(vr64& z /*out*/, ulsr32& buf /*inout*/, const unsigned int ** ptr /*inout*/, mir18& count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BBx_VB67_a_bounded)(ulsr32& buf /*inout*/, const unsigned int ** ptr /*inout*/, mir18& count /*inout*/, const unsigned int sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_flush_32x2_bounded)(const ulsr32 buf /*in*/, unsigned int ** ptr /*inout*/, mir18& count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_bounded)(const vr64& z /*in*/, ulsr32& buf /*inout*/, unsigned int ** ptr /*inout*/, mir18& count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_AccExtend_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB0_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB4_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB5_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB6_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB7_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_afloat_exp_extract)(const vr64& x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mov_AccExtend_vr)(const vr64& x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_mov_vr_AccExtend)(void);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_mov_BB_VB67_to_vrVB_VB45)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mov_vrVB_VB45_to_BB_VB67)(const vr64& x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_precess_16bits)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_set_BB_vrVB67_zero)(void);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_exp_shift_amount)(const vr64& input1 /*in*/, const vr64& input2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rnd_sat_pack)(vr64& z /*inout*/, immediate el32 /*in*/, const vr64& x /*in*/, const vr64& y /*in*/, const atbool& sgn /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rectify32_into8)(vr64& z /*inout*/, const vr64& x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/, immediate half /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_shift8_into32_arith)(const vr64& x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/, immediate half /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_shift32_arith)(const vr64& x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mac8bx8b)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/, const atbool& bbrx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_sparse)(vr64& z /*inout*/, const vr64& x /*in*/, const vr64& y /*in*/, const atbool& bbrx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_conv)(vr64& z /*inout*/, const vr64& x /*in*/, const atbool& bbrx /*in*/, immediate shift_in /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mir_init)(const unsigned int low /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_f_abs)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fclamp)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fclamp_bp)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fclamp_one)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fmax)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fmin)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_max_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_min_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_log2)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_pow2)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sigmoid)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_inv)(const fr32 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ratio)(fr32& z /*out*/, const fr32 x /*in*/, const fr32 y /*in*/, atbool& bz /*out*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_atanratio)(const fr32 x /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_invsqrt)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sine)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_cosine)(const fr32 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_log2mul)(fr32& z /*out*/, const fr32 x /*in*/, const fr32 y /*in*/, atbool& bz /*out*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_cspow2)(const fr32 x /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_comp)(const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_eq)(const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ge)(const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_gt)(const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_le)(const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_lt)(const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ne)(const vr64& x /*in*/, immediate el_x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_comp_const)(const vr64& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_eq_const)(const vr64& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ge_const)(const vr64& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_gt_const)(const vr64& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_le_const)(const vr64& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_lt_const)(const vr64& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ne_const)(const vr64& x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_comp_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_eq_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ge_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_gt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_le_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_lt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ne_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_neg_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_abs_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_deqz)(const vr64& x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dgez)(const vr64& x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dgtz)(const vr64& x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dlez)(const vr64& x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dltz)(const vr64& x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dnez)(const vr64& x /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_veq)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vge)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vgt)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vle)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vlt)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vne)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_veq_const)(const vr64& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vge_const)(const vr64& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vgt_const)(const vr64& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vle_const)(const vr64& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vlt_const)(const vr64& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vne_const)(const vr64& x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_1b2)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool& bx /*in*/, immediate el_bx1 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_eq)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_ge)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_gt)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_le)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_lt)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_ne)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_ar)(const fr32 fx /*in*/, const fr32 fy /*in*/, const unsigned int sel /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vsel)(const vr64& x /*in*/, const vr64& y /*in*/, const atbool& bx /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vsel_ar)(const vr64& x /*in*/, const vr64& y /*in*/, const unsigned int sel /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_andb2)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_andbc2)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_orb2)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_orbc2)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_xorb2)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount0_maskI)(const atbool& bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount0_maskR)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount1_maskI)(const atbool& bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount1_maskR)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskI)(const atbool& bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskR)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskI)(const atbool& bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskR)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast0_maskI)(const atbool& bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast0_maskR)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast1_maskI)(const atbool& bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast1_maskR)(const atbool& bx /*in*/, const atbool& by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bgetI)(const atbool& bx /*in*/, immediate ipos /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bgetR)(const atbool& bx /*in*/, const unsigned int rpos /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_bsetI)(const atbool& bx /*in*/, const unsigned int rpos /*in*/, immediate ibit /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_bsetR)(const atbool& bx /*in*/, const unsigned int rpos /*in*/, const unsigned int by /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_exp_adj)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_exp_adji)(vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_exp_adj_fr)(const fr32 fx /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_exp_adji_fr)(const fr32 fx /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_neg)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_copy)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_and)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_andc)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_or)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_orc)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_xor)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vneg)(const vr64& x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vcopy)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vand)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vandc)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vor)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vorc)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vxor)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_floorp_frac)(unsigned int& floor /*out*/, vr64& z /*inout*/, immediate el_z /*in*/, const vr64& x /*in*/, immediate el_x /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_idx_frac)(unsigned int& floor /*out*/, vr64& z /*inout*/, immediate el_z /*in*/, const unsigned int input /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rmax_idx)(unsigned int& a /*out*/, fr32& fz /*out*/, const vr64& x /*in*/, const mir18& idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rmin_idx)(unsigned int& a /*out*/, fr32& fz /*out*/, const vr64& x /*in*/, const mir18& idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmaxmin_init)(vr64& z /*out*/, const vr64& x /*in*/, mir18& idx /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmax_idx)(vr64& z /*inout*/, const vr64& x /*in*/, mir18& idx /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmin_idx)(vr64& z /*inout*/, const vr64& x /*in*/, mir18& idx /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmax)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmin)(const vr64& x /*in*/, const vr64& y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_vr)(unsigned int& a /*out*/, vr64& z /*out*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_des_vr)(unsigned int& a /*out*/, vr64& z /*out*/, const vr64& x /*in*/, const vr64& y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_ar)(unsigned int& a /*inout*/, vr64& z /*out*/, const vr64& x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_des_ar)(unsigned int& a /*inout*/, vr64& z /*out*/, const vr64& x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vbool)(const vr64& x /*in*/, const vr64& y /*in*/, immediate op /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_align_up)(const unsigned int val /*in*/, const unsigned int option /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mv_MIR)(const mir18& b /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_mv_ULSR)(const ulsr32 b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_mv_CR)(const cr64& b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_ld_FR)(const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_ld_FR_idxR)(const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR_idxR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_FR_postI)(fr32& fregout /*out*/, const fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR_postI)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_FR_postR)(fr32& fregout /*out*/, const fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR_postR)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_ld_VR)(const vr64 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR)(const vr64& vregin /*in*/, const vr64 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_ld_VR_idxR)(const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR_idxR)(const vr64& vregin /*in*/, const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_VR_postI)(vr64& vregout /*out*/, const vr64 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR_postI)(const vr64& vregin /*in*/, vr64 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_VR_postR)(vr64& vregout /*out*/, const vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR_postR)(const vr64& vregin /*in*/, vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_mv_FR)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move_ar_fr)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_move_fr_ar)(const unsigned int b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_mv_VR)(const vr64& b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move_ar_bbr)(const atbool& b /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_move_bbr_ar)(const unsigned int a /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_shift_from_bbr)(unsigned int& a /*inout*/, const atbool& x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_shift_to_bbr)(unsigned int& a /*inout*/, atbool& z /*out*/);

CSTUB_EXTERN int CSTUB_(_TIE_xt_core_RSR_PRID)(void);
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
    CSTUB_(_TIE_hemilite_common_tie_fr32_storei)(src, this, 0);
  }
  return *this;
}
inline fr32::fr32_(const unsigned int &src) {
  *this = CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_fr32)(src);
}
inline fr32& fr32::operator= (const unsigned int &src_in) {
  unsigned int src = (unsigned int) src_in;
  *this = CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_fr32)(src);
  return *this;
}
inline fr32::fr32_(const int &src) {
  *this = CSTUB_(_TIE_hemilite_common_tie_int32_rtor_fr32)(src);
}
inline fr32& fr32::operator= (const int &src_in) {
  int src = (int) src_in;
  *this = CSTUB_(_TIE_hemilite_common_tie_int32_rtor_fr32)(src);
  return *this;
}
#ifndef _MSC_VER
template<>
#endif
inline fr32::operator unsigned int () const {
  return CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_uint32) (*this);
}
#ifndef _MSC_VER
template<>
#endif
inline fr32::operator int () const {
  return CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_int32) (*this);
}

}

namespace vr64_space {
inline vr64& vr64::operator= (const vr64 &src) {
  if (this != &src) {
    CSTUB_(_TIE_hemilite_common_tie_vr64_storei)(src, this, 0);
  }
  return *this;
}

}

namespace cr64_space {
inline cr64& cr64::operator= (const cr64 &src) {
  if (this != &src) {
    CSTUB_(_TIE_hemilite_common_tie_cr64_storei)(src, this, 0);
  }
  return *this;
}

}

namespace mir18_space {
inline mir18& mir18::operator= (const mir18 &src) {
  if (this != &src) {
    CSTUB_(_TIE_hemilite_common_tie_mir18_storei)(src, this, 0);
  }
  return *this;
}

}

namespace ulsr32_space {
inline ulsr32& ulsr32::operator= (const ulsr32 &src) {
  if (this != &src) {
    CSTUB_(_TIE_hemilite_common_tie_ulsr32_storei)(src, this, 0);
  }
  return *this;
}

}

namespace atbool_space {
inline atbool& atbool::operator= (const atbool &src) {
  if (this != &src) {
    CSTUB_(_TIE_hemilite_common_tie_atbool_storei)(src, this, 0);
  }
  return *this;
}
inline atbool::atbool_(const unsigned int &src) {
  *this = CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_atbool)(src);
}
inline atbool& atbool::operator= (const unsigned int &src_in) {
  unsigned int src = (unsigned int) src_in;
  *this = CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_atbool)(src);
  return *this;
}
inline atbool::atbool_(const int &src) {
  *this = CSTUB_(_TIE_hemilite_common_tie_int32_rtor_atbool)(src);
}
inline atbool& atbool::operator= (const int &src_in) {
  int src = (int) src_in;
  *this = CSTUB_(_TIE_hemilite_common_tie_int32_rtor_atbool)(src);
  return *this;
}
#ifndef _MSC_VER
template<>
#endif
inline atbool::operator unsigned int () const {
  return CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_uint32) (*this);
}
#ifndef _MSC_VER
template<>
#endif
inline atbool::operator int () const {
  return CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_int32) (*this);
}

}


/* Proto macros */
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
#define XT_ANDB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDB)(bs, bt)
#else
#define XT_ANDB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDB)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ANDBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDBC)(bs, bt)
#else
#define XT_ANDBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDBC)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORB)(bs, bt)
#else
#define XT_ORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORB)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_ORBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORBC)(bs, bt)
#else
#define XT_ORBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORBC)(bs, bt)
#endif

#ifdef _STRICT_ARG_TYPE
#define XT_XORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_XORB)(bs, bt)
#else
#define XT_XORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_XORB)(bs, bt)
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
#define atbool_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_storei)(a, b, c)
#else
#define atbool_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define atbool_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_loadi)(b, c)
#else
#define atbool_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define atbool_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_move)(b)
#else
#define atbool_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define ulsr32_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_storei)(a, b, c)
#else
#define ulsr32_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ulsr32_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_loadi)(b, c)
#else
#define ulsr32_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define mir18_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_storei)(a, b, c)
#else
#define mir18_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define mir18_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_loadi)(b, c)
#else
#define mir18_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define cr64_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_storei)(a, b, c)
#else
#define cr64_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_storei)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define cr64_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_loadi)(b, c)
#else
#define cr64_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_loadi)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_JammingBit() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_JammingBit)()
#else
#define RUR_JammingBit() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_JammingBit)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_JammingBit(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_JammingBit)(v)
#else
#define WUR_JammingBit(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_JammingBit)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_AccExtend_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_0)()
#else
#define RUR_AccExtend_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_AccExtend_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_0)(v)
#else
#define WUR_AccExtend_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_AccExtend_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_1)()
#else
#define RUR_AccExtend_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_AccExtend_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_1)(v)
#else
#define WUR_AccExtend_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB0_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_0)()
#else
#define RUR_BB0_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB0_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_0)(v)
#else
#define WUR_BB0_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB0_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_1)()
#else
#define RUR_BB0_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB0_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_1)(v)
#else
#define WUR_BB0_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB1_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_0)()
#else
#define RUR_BB1_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB1_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_0)(v)
#else
#define WUR_BB1_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB1_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_1)()
#else
#define RUR_BB1_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB1_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_1)(v)
#else
#define WUR_BB1_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB2_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_0)()
#else
#define RUR_BB2_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB2_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_0)(v)
#else
#define WUR_BB2_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB2_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_1)()
#else
#define RUR_BB2_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB2_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_1)(v)
#else
#define WUR_BB2_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB3_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_0)()
#else
#define RUR_BB3_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB3_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_0)(v)
#else
#define WUR_BB3_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_BB3_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_1)()
#else
#define RUR_BB3_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_BB3_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_1)(v)
#else
#define WUR_BB3_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_MvmAux() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_MvmAux)()
#else
#define RUR_MvmAux() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_MvmAux)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_MvmAux(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_MvmAux)(v)
#else
#define WUR_MvmAux(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_MvmAux)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB1_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_0)()
#else
#define RUR_VB1_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB1_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_0)(v)
#else
#define WUR_VB1_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB1_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_1)()
#else
#define RUR_VB1_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB1_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_1)(v)
#else
#define WUR_VB1_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB2_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_0)()
#else
#define RUR_VB2_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB2_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_0)(v)
#else
#define WUR_VB2_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB2_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_1)()
#else
#define RUR_VB2_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB2_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_1)(v)
#else
#define WUR_VB2_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB3_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_0)()
#else
#define RUR_VB3_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB3_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_0)(v)
#else
#define WUR_VB3_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB3_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_1)()
#else
#define RUR_VB3_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB3_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_1)(v)
#else
#define WUR_VB3_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB4_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_0)()
#else
#define RUR_VB4_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB4_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_0)(v)
#else
#define WUR_VB4_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB4_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_1)()
#else
#define RUR_VB4_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB4_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_1)(v)
#else
#define WUR_VB4_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB5_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_0)()
#else
#define RUR_VB5_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB5_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_0)(v)
#else
#define WUR_VB5_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB5_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_1)()
#else
#define RUR_VB5_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB5_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_1)(v)
#else
#define WUR_VB5_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB6_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_0)()
#else
#define RUR_VB6_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB6_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_0)(v)
#else
#define WUR_VB6_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB6_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_1)()
#else
#define RUR_VB6_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB6_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_1)(v)
#else
#define WUR_VB6_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB7_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_0)()
#else
#define RUR_VB7_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_0)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB7_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_0)(v)
#else
#define WUR_VB7_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_0)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define RUR_VB7_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_1)()
#else
#define RUR_VB7_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_1)()
#endif

#ifdef _STRICT_ARG_TYPE
#define WUR_VB7_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_1)(v)
#else
#define WUR_VB7_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_1)(v)
#endif

#ifdef _STRICT_ARG_TYPE
#define mir18_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_move)(b)
#else
#define mir18_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define ulsr32_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_move)(b)
#else
#define ulsr32_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define cr64_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_move)(b)
#else
#define cr64_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_move)(b)
#else
#define fr32_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadi(p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadi)(p, o)
#else
#define fr32_loadi(p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadi)(p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storei(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storei)(v, p, o)
#else
#define fr32_storei(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storei)(v, p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadx(p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadx)(p, x)
#else
#define fr32_loadx(p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadx)(p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storex(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storex)(v, p, x)
#else
#define fr32_storex(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storex)(v, p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadip)(v, (const fr32 **)&(p), o)
#else
#define fr32_loadip(v, p, o) { \
	fr32 __v; \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadip)(__v, (const fr32 **)&(p), o); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storeip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storeip)(v, (fr32 **)&(p), o)
#else
#define fr32_storeip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storeip)(v, (fr32 **)&(p), o)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_loadxp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadxp)(v, (const fr32 **)&(p), x)
#else
#define fr32_loadxp(v, p, x) { \
	fr32 __v; \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadxp)(__v, (const fr32 **)&(p), x); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_storexp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storexp)(v, (fr32 **)&(p), x)
#else
#define fr32_storexp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storexp)(v, (fr32 **)&(p), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_rtor_int32(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_int32)(b)
#else
#define fr32_rtor_int32(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_int32)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define fr32_rtor_uint32(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_uint32)(b)
#else
#define fr32_rtor_uint32(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_uint32)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define int32_rtor_fr32(a) \
	CSTUB_(_TIE_hemilite_common_tie_int32_rtor_fr32)(a)
#else
#define int32_rtor_fr32(a) \
	CSTUB_(_TIE_hemilite_common_tie_int32_rtor_fr32)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define uint32_rtor_fr32(a) \
	CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_fr32)(a)
#else
#define uint32_rtor_fr32(a) \
	CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_fr32)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_move)(b)
#else
#define vr64_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_move)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadi(p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadi)(p, o)
#else
#define vr64_loadi(p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadi)(p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storei(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storei)(v, p, o)
#else
#define vr64_storei(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storei)(v, p, o)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadx(p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadx)(p, x)
#else
#define vr64_loadx(p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadx)(p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storex(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storex)(v, p, x)
#else
#define vr64_storex(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storex)(v, p, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadip)(v, (const vr64 **)&(p), o)
#else
#define vr64_loadip(v, p, o) { \
	vr64 __v; \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadip)(__v, (const vr64 **)&(p), o); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storeip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storeip)(v, (vr64 **)&(p), o)
#else
#define vr64_storeip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storeip)(v, (vr64 **)&(p), o)
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_loadxp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadxp)(v, (const vr64 **)&(p), x)
#else
#define vr64_loadxp(v, p, x) { \
	vr64 __v; \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadxp)(__v, (const vr64 **)&(p), x); \
	(v) = __v; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_storexp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storexp)(v, (vr64 **)&(p), x)
#else
#define vr64_storexp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storexp)(v, (vr64 **)&(p), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRH(b) \
	CSTUB_(_TIE_hemilite_common_tie_get_VRH)(b)
#else
#define get_VRH(b) \
	CSTUB_(_TIE_hemilite_common_tie_get_VRH)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define get_VRL(b) \
	CSTUB_(_TIE_hemilite_common_tie_get_VRL)(b)
#else
#define get_VRL(b) \
	CSTUB_(_TIE_hemilite_common_tie_get_VRL)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRH(a, b) \
	CSTUB_(_TIE_hemilite_common_tie_set_VRH)(a, b)
#else
#define set_VRH(a, b) { \
	vr64 __a = a; \
	CSTUB_(_TIE_hemilite_common_tie_set_VRH)(__a, b); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define set_VRL(a, b) \
	CSTUB_(_TIE_hemilite_common_tie_set_VRL)(a, b)
#else
#define set_VRL(a, b) { \
	vr64 __a = a; \
	CSTUB_(_TIE_hemilite_common_tie_set_VRL)(__a, b); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vr64_pair(hi, lo) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_pair)(hi, lo)
#else
#define vr64_pair(hi, lo) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_pair)(hi, lo)
#endif

#ifdef _STRICT_ARG_TYPE
#define atbool_rtor_int32(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_int32)(b)
#else
#define atbool_rtor_int32(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_int32)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define atbool_rtor_uint32(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_uint32)(b)
#else
#define atbool_rtor_uint32(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_uint32)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define int32_rtor_atbool(a) \
	CSTUB_(_TIE_hemilite_common_tie_int32_rtor_atbool)(a)
#else
#define int32_rtor_atbool(a) \
	CSTUB_(_TIE_hemilite_common_tie_int32_rtor_atbool)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define uint32_rtor_atbool(a) \
	CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_atbool)(a)
#else
#define uint32_rtor_atbool(a) \
	CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_atbool)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_BBR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_BBR)(a, b, c)
#else
#define st_BBR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_BBR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_BBR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_BBR)(b, c)
#else
#define ld_BBR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_BBR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_BBR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_BBR)(b)
#else
#define mv_BBR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_BBR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_ULSR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_ULSR)(a, b, c)
#else
#define st_ULSR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_ULSR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_ULSR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_ULSR)(b, c)
#else
#define ld_ULSR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_ULSR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_MIR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_MIR)(a, b, c)
#else
#define st_MIR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_MIR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_MIR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_MIR)(b, c)
#else
#define ld_MIR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_MIR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_CR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_CR)(a, b, c)
#else
#define st_CR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_CR)(a, b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_CR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_CR)(b, c)
#else
#define ld_CR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_CR)(b, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_ld(src) \
	CSTUB_(_TIE_hemilite_common_tie_dma_ld)(src)
#else
#define dma_ld(src) \
	CSTUB_(_TIE_hemilite_common_tie_dma_ld)(src)
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_align_ld(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_align_ld)((const unsigned int **)&(src), dst)
#else
#define dma_align_ld(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_align_ld)((const unsigned int **)&(src), dst)
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_ldu(src) \
	CSTUB_(_TIE_hemilite_common_tie_dma_ldu)((const unsigned int **)&(src))
#else
#define dma_ldu(src) \
	CSTUB_(_TIE_hemilite_common_tie_dma_ldu)((const unsigned int **)&(src))
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_flush_ld(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_flush_ld)((const unsigned int **)&(src), dst)
#else
#define dma_flush_ld(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_flush_ld)((const unsigned int **)&(src), dst)
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_st)(src, dst)
#else
#define dma_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_st)(src, dst)
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_align_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_align_st)(src, (unsigned int **)&(dst))
#else
#define dma_align_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_align_st)(src, (unsigned int **)&(dst))
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_stu(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_stu)(src, (unsigned int **)&(dst))
#else
#define dma_stu(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_stu)(src, (unsigned int **)&(dst))
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_flush_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_flush_st)(src, dst)
#else
#define dma_flush_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_flush_st)(src, dst)
#endif

#ifdef _STRICT_ARG_TYPE
#define dma_buf_save(dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_buf_save)((unsigned int **)&(dst))
#else
#define dma_buf_save(dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_buf_save)((unsigned int **)&(dst))
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR)(ptr, ofst)
#else
#define load32x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR)(ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI)(ptr, ofst2)
#else
#define load32x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI)((const unsigned int *)ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR)(z, (const unsigned int **)&(ptr), ofst)
#else
#define load32x2_vr_postR(z, ptr, ofst) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR)(__z, (const unsigned int **)&(ptr), ofst); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI)(z, (const unsigned int **)&(ptr), ofst2)
#else
#define load32x2_vr_postI(z, ptr, ofst2) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c)
#else
#define load32x2_vr_circI(z, ptr, ofst1, c) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR)(z, ptr, ofst, sel1)
#else
#define load32x1_vr_idxR(z, ptr, ofst, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR)(__z, ptr, ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI)(z, ptr, ofst2, sel1)
#else
#define load32x1_vr_idxI(z, ptr, ofst2, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI)(__z, ptr, ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel1)
#else
#define load32x1_vr_postR(z, ptr, ofst, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel1)
#else
#define load32x1_vr_postI(z, ptr, ofst2, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define load32x1_vr_circI(z, ptr, ofst1, c, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_bdir(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_bdir)(ptr, ofst)
#else
#define load32x2_vr_bdir(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_bdir)(ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_brev(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_brev)(ptr, ofst)
#else
#define load32x2_vr_brev(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_brev)(ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR_perm)(z, ptr, ofst, perm)
#else
#define load32x2_vr_idxR_perm(z, ptr, ofst, perm) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR_perm)(__z, ptr, ofst, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI_perm_vr)(z, ptr, ofst2, perm)
#else
#define load32x2_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI_perm_vr)(z, ptr, ofst2, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR_perm)(z, (const unsigned int **)&(ptr), ofst, perm)
#else
#define load32x2_vr_postR_perm(z, ptr, ofst, perm) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR_perm)(__z, (const unsigned int **)&(ptr), ofst, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst2, perm)
#else
#define load32x2_vr_postI_perm_vr(r, z, ptr, ofst2, perm) { \
	vr64 __r; \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst2, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x2_vr_circI_perm(z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI_perm)(z, (const unsigned int **)&(ptr), ofst1, c, perm)
#else
#define load32x2_vr_circI_perm(z, ptr, ofst1, c, perm) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI_perm)(__z, (const unsigned int **)&(ptr), ofst1, c, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR_perm)(z, ptr, ofst, perm)
#else
#define load32x1_vr_idxR_perm(z, ptr, ofst, perm) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR_perm)(__z, ptr, ofst, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI_perm_vr)(z, ptr, ofst2, perm)
#else
#define load32x1_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI_perm_vr)(z, ptr, ofst2, perm)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR_perm)(z, (const unsigned int **)&(ptr), ofst, perm)
#else
#define load32x1_vr_postR_perm(z, ptr, ofst, perm) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR_perm)(__z, (const unsigned int **)&(ptr), ofst, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI_perm_vr)(r, z, (const unsigned int **)&(ptr), ofst2, perm)
#else
#define load32x1_vr_postI_perm_vr(r, z, ptr, ofst2, perm) { \
	vr64 __r; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI_perm_vr)(__r, z, (const unsigned int **)&(ptr), ofst2, perm); \
	(r) = __r; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_circI_perm(z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI_perm)(z, (const unsigned int **)&(ptr), ofst1, c, perm)
#else
#define load32x1_vr_circI_perm(z, ptr, ofst1, c, perm) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI_perm)(__z, (const unsigned int **)&(ptr), ofst1, c, perm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxR)(ptr, ofst)
#else
#define load16x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxR)(ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxI)(ptr, ofst2)
#else
#define load16x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxI)(ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postR)(z, (const unsigned int **)&(ptr), ofst)
#else
#define load16x2_vr_postR(z, ptr, ofst) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postR)(__z, (const unsigned int **)&(ptr), ofst); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postI)(z, (const unsigned int **)&(ptr), ofst2)
#else
#define load16x2_vr_postI(z, ptr, ofst2) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c)
#else
#define load16x2_vr_circI(z, ptr, ofst1, c) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxR)(z, ptr, ofst, sel1)
#else
#define load16x1_vr_idxR(z, ptr, ofst, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxR)(__z, ptr, ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxI)(z, ptr, ofst2, sel1)
#else
#define load16x1_vr_idxI(z, ptr, ofst2, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxI)(__z, ptr, ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel1)
#else
#define load16x1_vr_postR(z, ptr, ofst, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel1)
#else
#define load16x1_vr_postI(z, ptr, ofst2, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load16x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define load16x1_vr_circI(z, ptr, ofst1, c, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxR)(ptr, ofst)
#else
#define load8x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxR)(ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxI)(ptr, ofst2)
#else
#define load8x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxI)(ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postR)(z, (const unsigned int **)&(ptr), ofst)
#else
#define load8x2_vr_postR(z, ptr, ofst) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postR)(__z, (const unsigned int **)&(ptr), ofst); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postI)(z, (const unsigned int **)&(ptr), ofst2)
#else
#define load8x2_vr_postI(z, ptr, ofst2) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c)
#else
#define load8x2_vr_circI(z, ptr, ofst1, c) { \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxR)(z, ptr, ofst, sel1)
#else
#define load8x1_vr_idxR(z, ptr, ofst, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxR)(__z, ptr, ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxI)(z, ptr, ofst2, sel1)
#else
#define load8x1_vr_idxI(z, ptr, ofst2, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxI)(__z, ptr, ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postR)(z, (const unsigned int **)&(ptr), ofst, sel1)
#else
#define load8x1_vr_postR(z, ptr, ofst, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postR)(__z, (const unsigned int **)&(ptr), ofst, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postI)(z, (const unsigned int **)&(ptr), ofst2, sel1)
#else
#define load8x1_vr_postI(z, ptr, ofst2, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postI)(__z, (const unsigned int **)&(ptr), ofst2, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load8x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_circI)(z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define load8x1_vr_circI(z, ptr, ofst1, c, sel1) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_circI)(__z, (const unsigned int **)&(ptr), ofst1, c, sel1); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define align_32x2_load(ptr) \
	CSTUB_(_TIE_hemilite_common_tie_align_32x2_load)(ptr)
#else
#define align_32x2_load(ptr) \
	CSTUB_(_TIE_hemilite_common_tie_align_32x2_load)((unsigned int *)ptr)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_32x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a)(z, buf, (const unsigned int **)&(ptr))
#else
#define load_32x2_vr_a(z, buf, ptr) { \
	vr64 __z; \
	ulsr32 __buf = buf; \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a)(__z, __buf, (const unsigned int **)&(ptr)); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_24x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_load_24x2_vr_a)(z, buf, (const unsigned int **)&(ptr))
#else
#define load_24x2_vr_a(z, buf, ptr) { \
	vr64 __z; \
	ulsr32 __buf = buf; \
	CSTUB_(_TIE_hemilite_common_tie_load_24x2_vr_a)(__z, __buf, (const unsigned int **)&(ptr)); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_32x2_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_circ)(z, buf, (const unsigned int **)&(ptr), c)
#else
#define load_32x2_vr_a_circ(z, buf, ptr, c) { \
	vr64 __z; \
	ulsr32 __buf = buf; \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_circ)(__z, __buf, (const unsigned int **)&(ptr), c); \
	(z) = __z; \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxR)(z, ptr, ofst)
#else
#define store32x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxR)(z, ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxI)(z, ptr, ofst2)
#else
#define store32x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxI)(z, ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#else
#define store32x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#else
#define store32x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#else
#define store32x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxR)(z, ptr, ofst, sel1)
#else
#define store32x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxR)(z, ptr, ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxI)(z, ptr, ofst2, sel1)
#else
#define store32x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxI)(z, ptr, ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store32x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store32x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store32x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_idxR(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxR)(z, gate, ptr, ofst)
#else
#define store32x2_vr_br_idxR(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxR)(z, gate, ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_idxI(z, gate, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxI)(z, gate, ptr, ofst2)
#else
#define store32x2_vr_br_idxI(z, gate, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxI)(z, gate, ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_postR(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postR)(z, gate, (unsigned int **)&(ptr), ofst)
#else
#define store32x2_vr_br_postR(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postR)(z, gate, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_postI(z, gate, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postI)(z, gate, (unsigned int **)&(ptr), ofst2)
#else
#define store32x2_vr_br_postI(z, gate, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postI)(z, gate, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_circI(z, gate, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_circI)(z, gate, (unsigned int **)&(ptr), ofst1, c)
#else
#define store32x2_vr_br_circI(z, gate, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_circI)(z, gate, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_idxR(z, gate, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxR)(z, gate, ptr, ofst, sel1)
#else
#define store32x1_vr_br_idxR(z, gate, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxR)(z, gate, ptr, ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_idxI(z, gate, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxI)(z, gate, ptr, ofst2, sel1)
#else
#define store32x1_vr_br_idxI(z, gate, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxI)(z, gate, ptr, ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_postR(z, gate, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postR)(z, gate, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store32x1_vr_br_postR(z, gate, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postR)(z, gate, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_postI(z, gate, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postI)(z, gate, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store32x1_vr_br_postI(z, gate, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postI)(z, gate, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x1_vr_br_circI(z, gate, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_circI)(z, gate, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store32x1_vr_br_circI(z, gate, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_circI)(z, gate, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_bdir(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_bdir)(z, gate, ptr, ofst)
#else
#define store32x2_vr_br_bdir(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_bdir)(z, gate, ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store32x2_vr_br_brev(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_brev)(z, gate, ptr, ofst)
#else
#define store32x2_vr_br_brev(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_brev)(z, gate, ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxR)(z, ptr, ofst)
#else
#define store16x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxR)(z, ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxI)(z, ptr, ofst2)
#else
#define store16x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxI)(z, ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#else
#define store16x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#else
#define store16x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#else
#define store16x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxR)(z, ptr, ofst, sel1)
#else
#define store16x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxR)(z, ptr, ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxI)(z, ptr, ofst2, sel1)
#else
#define store16x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxI)(z, ptr, ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store16x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store16x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store16x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store16x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxR)(z, ptr, ofst)
#else
#define store8x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxR)(z, ptr, ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxI)(z, ptr, ofst2)
#else
#define store8x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxI)(z, ptr, ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#else
#define store8x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#else
#define store8x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#else
#define store8x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxR)(z, ptr, ofst, sel1)
#else
#define store8x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxR)(z, ptr, ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxI)(z, ptr, ofst2, sel1)
#else
#define store8x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxI)(z, ptr, ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#else
#define store8x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#else
#define store8x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define store8x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#else
#define store8x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define align_32x2_store(ptr) \
	CSTUB_(_TIE_hemilite_common_tie_align_32x2_store)(ptr)
#else
#define align_32x2_store(ptr) \
	CSTUB_(_TIE_hemilite_common_tie_align_32x2_store)((unsigned int*)ptr)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_32x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a)(z, buf, (unsigned int **)&(ptr))
#else
#define store_32x2_vr_a(z, buf, ptr) { \
	ulsr32 __buf = buf; \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a)(z, __buf, (unsigned int **)&(ptr)); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_24x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_store_24x2_vr_a)(z, buf, (unsigned int **)&(ptr))
#else
#define store_24x2_vr_a(z, buf, ptr) { \
	ulsr32 __buf = buf; \
	CSTUB_(_TIE_hemilite_common_tie_store_24x2_vr_a)(z, __buf, (unsigned int **)&(ptr)); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_32x2_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_circ)(z, buf, (unsigned int **)&(ptr), c)
#else
#define store_32x2_vr_a_circ(z, buf, ptr, c) { \
	ulsr32 __buf = buf; \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_circ)(z, __buf, (unsigned int **)&(ptr), c); \
	(buf) = __buf; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define flush_32x2(buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_flush_32x2)(buf, ptr)
#else
#define flush_32x2(buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_flush_32x2)(buf, (unsigned int *)ptr)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_fr_postI)(fx, (const unsigned int **)&(ptr), ofst2)
#else
#define load_fr_postI(fx, ptr, ofst2) { \
	fr32 __fx; \
	CSTUB_(_TIE_hemilite_common_tie_load_fr_postI)(__fx, (const unsigned int **)&(ptr), ofst2); \
	(fx) = __fx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_fr_postI)(fx, (unsigned int **)&(ptr), ofst2)
#else
#define store_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_fr_postI)(fx, (unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define brev_upd(gate, idx_out, idx_in) \
	CSTUB_(_TIE_hemilite_common_tie_brev_upd)(gate, idx_out, idx_in)
#else
#define brev_upd(gate, idx_out, idx_in) { \
	atbool __gate; \
	unsigned int __idx_out; \
	CSTUB_(_TIE_hemilite_common_tie_brev_upd)(__gate, __idx_out, idx_in); \
	(gate) = __gate; \
	(idx_out) = __idx_out; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define brev_upd_ext(gate, idx_out) \
	CSTUB_(_TIE_hemilite_common_tie_brev_upd_ext)(gate, idx_out)
#else
#define brev_upd_ext(gate, idx_out) { \
	atbool __gate = gate; \
	unsigned int __idx_out = idx_out; \
	CSTUB_(_TIE_hemilite_common_tie_brev_upd_ext)(__gate, __idx_out); \
	(gate) = __gate; \
	(idx_out) = __idx_out; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_ar_vr(x, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr)(x, sel1)
#else
#define move32_ar_vr(x, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr)(x, sel1)
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_vr_ar(z, sel1, a) \
	CSTUB_(_TIE_hemilite_common_tie_move32_vr_ar)(z, sel1, a)
#else
#define move32_vr_ar(z, sel1, a) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move32_vr_ar)(__z, sel1, a); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_ar_vr_idx(x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr_idx)(x, idx)
#else
#define move32_ar_vr_idx(x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr_idx)(x, idx)
#endif

#ifdef _STRICT_ARG_TYPE
#define move32_fr_vr_idx(x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_move32_fr_vr_idx)(x, idx)
#else
#define move32_fr_vr_idx(x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_move32_fr_vr_idx)(x, idx)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_eqz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_eqz)(z, x, y)
#else
#define move_fr_eqz(z, x, y) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_eqz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_gez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_gez)(z, x, y)
#else
#define move_fr_gez(z, x, y) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_gez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_gtz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_gtz)(z, x, y)
#else
#define move_fr_gtz(z, x, y) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_gtz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_lez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_lez)(z, x, y)
#else
#define move_fr_lez(z, x, y) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_lez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_ltz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_ltz)(z, x, y)
#else
#define move_fr_ltz(z, x, y) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_ltz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_nez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_nez)(z, x, y)
#else
#define move_fr_nez(z, x, y) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_nez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_sat(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_sat)(z, x, y)
#else
#define move_fr_sat(z, x, y) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_sat)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_arnz(z, x, ax) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_arnz)(z, x, ax)
#else
#define move_fr_arnz(z, x, ax) { \
	fr32 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_arnz)(__z, x, ax); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_eqz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_eqz)(z, x, y)
#else
#define vmove_vr_eqz(z, x, y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_eqz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_gez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gez)(z, x, y)
#else
#define vmove_vr_gez(z, x, y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_gtz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gtz)(z, x, y)
#else
#define vmove_vr_gtz(z, x, y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gtz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_lez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_lez)(z, x, y)
#else
#define vmove_vr_lez(z, x, y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_lez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_ltz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_ltz)(z, x, y)
#else
#define vmove_vr_ltz(z, x, y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_ltz)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_nez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_nez)(z, x, y)
#else
#define vmove_vr_nez(z, x, y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_nez)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmove_vr_sat(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_sat)(z, x, y)
#else
#define vmove_vr_sat(z, x, y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_sat)(__z, x, y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define replicate(z, sel_code, x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_replicate)(z, sel_code, x, el_x)
#else
#define replicate(z, sel_code, x, el_x) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_replicate)(__z, sel_code, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define replicate_ar(z, sel_code, ar) \
	CSTUB_(_TIE_hemilite_common_tie_replicate_ar)(z, sel_code, ar)
#else
#define replicate_ar(z, sel_code, ar) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_replicate_ar)(__z, sel_code, ar); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vreplicate(x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_vreplicate)(x, el_x)
#else
#define vreplicate(x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_vreplicate)(x, el_x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vreplicate_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_vreplicate_fr)(fx)
#else
#define vreplicate_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_vreplicate_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x1)(z, exp_fxp, el)
#else
#define convert_16I_to_32F_x1(z, exp_fxp, el) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x1)(__z, exp_fxp, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16I_to_32F_x2(z, exp_fxp) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x2)(z, exp_fxp)
#else
#define convert_16I_to_32F_x2(z, exp_fxp) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x2)(__z, exp_fxp); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x1)(z, exp_fxp, rnd, el)
#else
#define convert_32F_to_16I_x1(z, exp_fxp, rnd, el) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x1)(__z, exp_fxp, rnd, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16I_x2(z, exp_fxp, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x2)(z, exp_fxp, rnd)
#else
#define convert_32F_to_16I_x2(z, exp_fxp, rnd) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x2)(__z, exp_fxp, rnd); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16F_x1(z, is_signed, exp_bits, bias, round, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x1)(z, is_signed, exp_bits, bias, round, el)
#else
#define convert_32F_to_16F_x1(z, is_signed, exp_bits, bias, round, el) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x1)(__z, is_signed, exp_bits, bias, round, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_16F_x2(z, is_signed, exp_bits, bias, round) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x2)(z, is_signed, exp_bits, bias, round)
#else
#define convert_32F_to_16F_x2(z, is_signed, exp_bits, bias, round) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x2)(__z, is_signed, exp_bits, bias, round); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16F_to_32F_x1(z, is_signed, exp_bits, bias, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x1)(z, is_signed, exp_bits, bias, el)
#else
#define convert_16F_to_32F_x1(z, is_signed, exp_bits, bias, el) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x1)(__z, is_signed, exp_bits, bias, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_16F_to_32F_x2(z, is_signed, exp_bits, bias) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x2)(z, is_signed, exp_bits, bias)
#else
#define convert_16F_to_32F_x2(z, is_signed, exp_bits, bias) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x2)(__z, is_signed, exp_bits, bias); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_32F_x1)(z, exp_fxp, el)
#else
#define convert_32I_to_32F_x1(z, exp_fxp, el) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_32F_x1)(__z, exp_fxp, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_32I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_32I_x1)(z, exp_fxp, rnd, el)
#else
#define convert_32F_to_32I_x1(z, exp_fxp, rnd, el) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_32I_x1)(__z, exp_fxp, rnd, el); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_IEEE_float_to_32F_x2(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_float_to_32F_x2)(z)
#else
#define convert_IEEE_float_to_32F_x2(z) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_float_to_32F_x2)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_IEEE_float_x2(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_IEEE_float_x2)(z)
#else
#define convert_32F_to_IEEE_float_x2(z) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_IEEE_float_x2)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32I_to_64F(x) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_64F)(x)
#else
#define convert_32I_to_64F(x) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_64F)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_64F_to_32I(x, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32I)(x, rnd)
#else
#define convert_64F_to_32I(x, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32I)(x, rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_32F_to_64F(fx) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_64F)(fx)
#else
#define convert_32F_to_64F(fx) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_64F)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_64F_to_32F(x) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32F)(x)
#else
#define convert_64F_to_32F(x) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32F)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_IEEE_double_to_64F(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_double_to_64F)(z)
#else
#define convert_IEEE_double_to_64F(z) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_double_to_64F)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define convert_64F_to_IEEE_double(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_IEEE_double)(z)
#else
#define convert_64F_to_IEEE_double(z) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_IEEE_double)(__z); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vadd_perm(x, y, selin_h, selin_l, signs4, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vadd_perm)(x, y, selin_h, selin_l, signs4, div_by_2_op)
#else
#define vadd_perm(x, y, selin_h, selin_l, signs4, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vadd_perm)(x, y, selin_h, selin_l, signs4, div_by_2_op)
#endif

#ifdef _STRICT_ARG_TYPE
#define vsum_perm(z, x, y, selin_h, selin_l, signs4, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vsum_perm)(z, x, y, selin_h, selin_l, signs4, sign_z)
#else
#define vsum_perm(z, x, y, selin_h, selin_l, signs4, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vsum_perm)(z, x, y, selin_h, selin_l, signs4, sign_z)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmul_perm(x, y, selin_h, selin_l, signs2, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vmul_perm)(x, y, selin_h, selin_l, signs2, div_by_2_op)
#else
#define vmul_perm(x, y, selin_h, selin_l, signs2, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vmul_perm)(x, y, selin_h, selin_l, signs2, div_by_2_op)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmac_perm(z, x, y, selin_h, selin_l, signs2, sign_z, swap_z, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vmac_perm)(z, x, y, selin_h, selin_l, signs2, sign_z, swap_z, div_by_2_op)
#else
#define vmac_perm(z, x, y, selin_h, selin_l, signs2, sign_z, swap_z, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vmac_perm)(z, x, y, selin_h, selin_l, signs2, sign_z, swap_z, div_by_2_op)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmac_boost(z, x, y, selin_h, selin_l, signs2, boost) \
	CSTUB_(_TIE_hemilite_common_tie_vmac_boost)(z, x, y, selin_h, selin_l, signs2, boost)
#else
#define vmac_boost(z, x, y, selin_h, selin_l, signs2, boost) \
	CSTUB_(_TIE_hemilite_common_tie_vmac_boost)(z, x, y, selin_h, selin_l, signs2, boost)
#endif

#ifdef _STRICT_ARG_TYPE
#define vblend(x, y, selin_h, selin_l, signs4, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vblend)(x, y, selin_h, selin_l, signs4, div_by_2_op)
#else
#define vblend(x, y, selin_h, selin_l, signs4, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vblend)(x, y, selin_h, selin_l, signs4, div_by_2_op)
#endif

#ifdef _STRICT_ARG_TYPE
#define vblend_add(z, x, y, selin_h, selin_l, signs4, sign_z, swap_z, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vblend_add)(z, x, y, selin_h, selin_l, signs4, sign_z, swap_z, div_by_2_op)
#else
#define vblend_add(z, x, y, selin_h, selin_l, signs4, sign_z, swap_z, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vblend_add)(z, x, y, selin_h, selin_l, signs4, sign_z, swap_z, div_by_2_op)
#endif

#ifdef _STRICT_ARG_TYPE
#define vblend_boost(z, x, y, selin_h, selin_l, signs4, boost) \
	CSTUB_(_TIE_hemilite_common_tie_vblend_boost)(z, x, y, selin_h, selin_l, signs4, boost)
#else
#define vblend_boost(z, x, y, selin_h, selin_l, signs4, boost) \
	CSTUB_(_TIE_hemilite_common_tie_vblend_boost)(z, x, y, selin_h, selin_l, signs4, boost)
#endif

#ifdef _STRICT_ARG_TYPE
#define fadds(fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fadds)(fx, fy, signs2)
#else
#define fadds(fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fadds)(fx, fy, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define fmuls(fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fmuls)(fx, fy, signs2)
#else
#define fmuls(fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fmuls)(fx, fy, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define fmacs(fz, fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fmacs)(fz, fx, fy, signs2)
#else
#define fmacs(fz, fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fmacs)(fz, fx, fy, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define dadds(z, x, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dadds)(z, x, signs2)
#else
#define dadds(z, x, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dadds)(z, x, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define dmuls(x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dmuls)(x, y, signs2)
#else
#define dmuls(x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dmuls)(x, y, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define dmacs(z, x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dmacs)(z, x, y, signs2)
#else
#define dmacs(z, x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dmacs)(z, x, y, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define vadds(x, y, signs4) \
	CSTUB_(_TIE_hemilite_common_tie_vadds)(x, y, signs4)
#else
#define vadds(x, y, signs4) \
	CSTUB_(_TIE_hemilite_common_tie_vadds)(x, y, signs4)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmuls(x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_vmuls)(x, y, signs2)
#else
#define vmuls(x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_vmuls)(x, y, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmacs(z, x, y, signs2, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vmacs)(z, x, y, signs2, sign_z)
#else
#define vmacs(z, x, y, signs2, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vmacs)(z, x, y, signs2, sign_z)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmul(x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmul)(x, y, conj)
#else
#define cmul(x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmul)(x, y, conj)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmac(z, x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmac)(z, x, y, conj)
#else
#define cmac(z, x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmac)(z, x, y, conj)
#endif

#ifdef _STRICT_ARG_TYPE
#define cmas(z, x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmas)(z, x, y, conj)
#else
#define cmas(z, x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmas)(z, x, y, conj)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmulf(x, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_vmulf)(x, fy, signs2)
#else
#define vmulf(x, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_vmulf)(x, fy, signs2)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmacf(z, x, fy, signs2, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vmacf)(z, x, fy, signs2, sign_z)
#else
#define vmacf(z, x, fy, signs2, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vmacf)(z, x, fy, signs2, sign_z)
#endif

#ifdef _STRICT_ARG_TYPE
#define vabs(x) \
	CSTUB_(_TIE_hemilite_common_tie_vabs)(x)
#else
#define vabs(x) \
	CSTUB_(_TIE_hemilite_common_tie_vabs)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define vexp_adj(x, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_vexp_adj)(x, exp_adj_ar)
#else
#define vexp_adj(x, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_vexp_adj)(x, exp_adj_ar)
#endif

#ifdef _STRICT_ARG_TYPE
#define vexp_adji(x, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_vexp_adji)(x, exp_adj_imm)
#else
#define vexp_adji(x, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_vexp_adji)(x, exp_adj_imm)
#endif

#ifdef _STRICT_ARG_TYPE
#define vpermi(x, y, sel4) \
	CSTUB_(_TIE_hemilite_common_tie_vpermi)(x, y, sel4)
#else
#define vpermi(x, y, sel4) \
	CSTUB_(_TIE_hemilite_common_tie_vpermi)(x, y, sel4)
#endif

#ifdef _STRICT_ARG_TYPE
#define seta_vr(z, sel_code, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_vr)(z, sel_code, const_idx, exp_adj_const)
#else
#define seta_vr(z, sel_code, const_idx, exp_adj_const) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_seta_vr)(__z, sel_code, const_idx, exp_adj_const); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vseta_vr(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vseta_vr)(const_idx, exp_adj_const)
#else
#define vseta_vr(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vseta_vr)(const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define seta_ar(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_ar)(const_idx, exp_adj_const)
#else
#define seta_ar(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_ar)(const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define seta_fr(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_fr)(const_idx, exp_adj_const)
#else
#define seta_fr(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_fr)(const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_AccExtend_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_AccExtend_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load32x1_vr_idx16vr(z, ptr, vidx16, ptr_sel) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idx16vr)(z, ptr, vidx16, ptr_sel)
#else
#define load32x1_vr_idx16vr(z, ptr, vidx16, ptr_sel) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idx16vr)(__z, ptr, vidx16, ptr_sel); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB0_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB0_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB1_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB1_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB2_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB2_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB3_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB3_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB1_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB1_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB2_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB2_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB3_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB3_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB4_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB4_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB5_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB5_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB6_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB6_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB7_postI)((const unsigned int **)&(ptr), ofst2)
#else
#define load_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB7_postI)((const unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define load_32x2_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_bounded)(z, buf, (const unsigned int **)&(ptr), count)
#else
#define load_32x2_vr_a_bounded(z, buf, ptr, count) { \
	vr64 __z; \
	ulsr32 __buf = buf; \
	mir18 __count = count; \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_bounded)(__z, __buf, (const unsigned int **)&(ptr), __count); \
	(z) = __z; \
	(buf) = __buf; \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define load_BBx_VB67_a_bounded(buf, ptr, count, sel) \
	CSTUB_(_TIE_hemilite_common_tie_load_BBx_VB67_a_bounded)(buf, (const unsigned int **)&(ptr), count, sel)
#else
#define load_BBx_VB67_a_bounded(buf, ptr, count, sel) { \
	ulsr32 __buf = buf; \
	mir18 __count = count; \
	CSTUB_(_TIE_hemilite_common_tie_load_BBx_VB67_a_bounded)(__buf, (const unsigned int **)&(ptr), __count, sel); \
	(buf) = __buf; \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define flush_32x2_bounded(buf, ptr, count) \
	CSTUB_(_TIE_hemilite_common_tie_flush_32x2_bounded)(buf, (unsigned int **)&(ptr), count)
#else
#define flush_32x2_bounded(buf, ptr, count) { \
	mir18 __count = count; \
	CSTUB_(_TIE_hemilite_common_tie_flush_32x2_bounded)(buf, (unsigned int **)&(ptr), __count); \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_32x2_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_bounded)(z, buf, (unsigned int **)&(ptr), count)
#else
#define store_32x2_vr_a_bounded(z, buf, ptr, count) { \
	ulsr32 __buf = buf; \
	mir18 __count = count; \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_bounded)(z, __buf, (unsigned int **)&(ptr), __count); \
	(buf) = __buf; \
	(count) = __count; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define store_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_AccExtend_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_AccExtend_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB0_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB0_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB1_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB1_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB2_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB2_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB3_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB3_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB1_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB1_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB2_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB2_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB3_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB3_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB4_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB4_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB5_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB5_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB6_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB6_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define store_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB7_postI)((unsigned int **)&(ptr), ofst2)
#else
#define store_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB7_postI)((unsigned int **)&(ptr), ofst2)
#endif

#ifdef _STRICT_ARG_TYPE
#define afloat_exp_extract(x) \
	CSTUB_(_TIE_hemilite_common_tie_afloat_exp_extract)(x)
#else
#define afloat_exp_extract(x) \
	CSTUB_(_TIE_hemilite_common_tie_afloat_exp_extract)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_AccExtend_vr(x) \
	CSTUB_(_TIE_hemilite_common_tie_mov_AccExtend_vr)(x)
#else
#define mov_AccExtend_vr(x) \
	CSTUB_(_TIE_hemilite_common_tie_mov_AccExtend_vr)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_vr_AccExtend() \
	CSTUB_(_TIE_hemilite_common_tie_mov_vr_AccExtend)()
#else
#define mov_vr_AccExtend() \
	CSTUB_(_TIE_hemilite_common_tie_mov_vr_AccExtend)()
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_BB_VB67_to_vrVB_VB45() \
	CSTUB_(_TIE_hemilite_common_tie_mov_BB_VB67_to_vrVB_VB45)()
#else
#define mov_BB_VB67_to_vrVB_VB45() \
	CSTUB_(_TIE_hemilite_common_tie_mov_BB_VB67_to_vrVB_VB45)()
#endif

#ifdef _STRICT_ARG_TYPE
#define mov_vrVB_VB45_to_BB_VB67(x) \
	CSTUB_(_TIE_hemilite_common_tie_mov_vrVB_VB45_to_BB_VB67)(x)
#else
#define mov_vrVB_VB45_to_BB_VB67(x) \
	CSTUB_(_TIE_hemilite_common_tie_mov_vrVB_VB45_to_BB_VB67)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define precess_16bits(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_precess_16bits)(x, y)
#else
#define precess_16bits(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_precess_16bits)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define set_BB_vrVB67_zero() \
	CSTUB_(_TIE_hemilite_common_tie_set_BB_vrVB67_zero)()
#else
#define set_BB_vrVB67_zero() \
	CSTUB_(_TIE_hemilite_common_tie_set_BB_vrVB67_zero)()
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_shift_amount(input1, input2) \
	CSTUB_(_TIE_hemilite_common_tie_exp_shift_amount)(input1, input2)
#else
#define exp_shift_amount(input1, input2) \
	CSTUB_(_TIE_hemilite_common_tie_exp_shift_amount)(input1, input2)
#endif

#ifdef _STRICT_ARG_TYPE
#define rnd_sat_pack(z, el32, x, y, sgn) \
	CSTUB_(_TIE_hemilite_common_tie_rnd_sat_pack)(z, el32, x, y, sgn)
#else
#define rnd_sat_pack(z, el32, x, y, sgn) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_rnd_sat_pack)(__z, el32, x, y, sgn); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define rectify32_into8(z, x, shift, rnd, el32, half) \
	CSTUB_(_TIE_hemilite_common_tie_rectify32_into8)(z, x, shift, rnd, el32, half)
#else
#define rectify32_into8(z, x, shift, rnd, el32, half) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_rectify32_into8)(__z, x, shift, rnd, el32, half); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define shift8_into32_arith(x, shift, rnd, el32, half) \
	CSTUB_(_TIE_hemilite_common_tie_shift8_into32_arith)(x, shift, rnd, el32, half)
#else
#define shift8_into32_arith(x, shift, rnd, el32, half) \
	CSTUB_(_TIE_hemilite_common_tie_shift8_into32_arith)(x, shift, rnd, el32, half)
#endif

#ifdef _STRICT_ARG_TYPE
#define shift32_arith(x, shift, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_shift32_arith)(x, shift, rnd)
#else
#define shift32_arith(x, shift, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_shift32_arith)(x, shift, rnd)
#endif

#ifdef _STRICT_ARG_TYPE
#define mac8bx8b(z, x, y, signed) \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b)(z, x, y, signed)
#else
#define mac8bx8b(z, x, y, signed) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b)(__z, x, y, signed); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define mac8bx8b_sparse(z, x, y, signed) \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_sparse)(z, x, y, signed)
#else
#define mac8bx8b_sparse(z, x, y, signed) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_sparse)(__z, x, y, signed); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define mac8bx8b_conv(z, x, signed, shift_in) \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_conv)(z, x, signed, shift_in)
#else
#define mac8bx8b_conv(z, x, signed, shift_in) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_conv)(__z, x, signed, shift_in); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define mir_init(low) \
	CSTUB_(_TIE_hemilite_common_tie_mir_init)(low)
#else
#define mir_init(low) \
	CSTUB_(_TIE_hemilite_common_tie_mir_init)(low)
#endif

#ifdef _STRICT_ARG_TYPE
#define f_abs(z, el_z, x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_f_abs)(z, el_z, x, el_x)
#else
#define f_abs(z, el_z, x, el_x) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_f_abs)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fclamp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fclamp)(z, el_z, x, el_x, y, el_y)
#else
#define fclamp(z, el_z, x, el_x, y, el_y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_fclamp)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fclamp_bp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fclamp_bp)(z, el_z, x, el_x, y, el_y)
#else
#define fclamp_bp(z, el_z, x, el_x, y, el_y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_fclamp_bp)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fclamp_one(z, el_z, x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_fclamp_one)(z, el_z, x, el_x)
#else
#define fclamp_one(z, el_z, x, el_x) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_fclamp_one)(__z, el_z, x, el_x); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fmax(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fmax)(z, el_z, x, el_x, y, el_y)
#else
#define fmax(z, el_z, x, el_x, y, el_y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_fmax)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define fmin(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fmin)(z, el_z, x, el_x, y, el_y)
#else
#define fmin(z, el_z, x, el_x, y, el_y) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_fmin)(__z, el_z, x, el_x, y, el_y); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define max_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_max_fr)(fx, fy)
#else
#define max_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_max_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define min_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_min_fr)(fx, fy)
#else
#define min_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_min_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define log2(x) \
	CSTUB_(_TIE_hemilite_common_tie_log2)(x)
#else
#define log2(x) \
	CSTUB_(_TIE_hemilite_common_tie_log2)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define pow2(x) \
	CSTUB_(_TIE_hemilite_common_tie_pow2)(x)
#else
#define pow2(x) \
	CSTUB_(_TIE_hemilite_common_tie_pow2)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define sigmoid(x) \
	CSTUB_(_TIE_hemilite_common_tie_sigmoid)(x)
#else
#define sigmoid(x) \
	CSTUB_(_TIE_hemilite_common_tie_sigmoid)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define inv(x) \
	CSTUB_(_TIE_hemilite_common_tie_inv)(x)
#else
#define inv(x) \
	CSTUB_(_TIE_hemilite_common_tie_inv)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ratio(z, x, y, bz) \
	CSTUB_(_TIE_hemilite_common_tie_ratio)(z, x, y, bz)
#else
#define ratio(z, x, y, bz) { \
	fr32 __z; \
	atbool __bz; \
	CSTUB_(_TIE_hemilite_common_tie_ratio)(__z, x, y, __bz); \
	(z) = __z; \
	(bz) = __bz; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define atanratio(x, bx) \
	CSTUB_(_TIE_hemilite_common_tie_atanratio)(x, bx)
#else
#define atanratio(x, bx) \
	CSTUB_(_TIE_hemilite_common_tie_atanratio)(x, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define invsqrt(x) \
	CSTUB_(_TIE_hemilite_common_tie_invsqrt)(x)
#else
#define invsqrt(x) \
	CSTUB_(_TIE_hemilite_common_tie_invsqrt)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define sine(x) \
	CSTUB_(_TIE_hemilite_common_tie_sine)(x)
#else
#define sine(x) \
	CSTUB_(_TIE_hemilite_common_tie_sine)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define cosine(x) \
	CSTUB_(_TIE_hemilite_common_tie_cosine)(x)
#else
#define cosine(x) \
	CSTUB_(_TIE_hemilite_common_tie_cosine)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define log2mul(z, x, y, bz) \
	CSTUB_(_TIE_hemilite_common_tie_log2mul)(z, x, y, bz)
#else
#define log2mul(z, x, y, bz) { \
	fr32 __z; \
	atbool __bz; \
	CSTUB_(_TIE_hemilite_common_tie_log2mul)(__z, x, y, __bz); \
	(z) = __z; \
	(bz) = __bz; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define cspow2(x, bx) \
	CSTUB_(_TIE_hemilite_common_tie_cspow2)(x, bx)
#else
#define cspow2(x, bx) \
	CSTUB_(_TIE_hemilite_common_tie_cspow2)(x, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define comp(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_comp)(x, el_x, y, el_y)
#else
#define comp(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_comp)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define eq(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_eq)(x, el_x, y, el_y)
#else
#define eq(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_eq)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define ge(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_ge)(x, el_x, y, el_y)
#else
#define ge(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_ge)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define gt(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_gt)(x, el_x, y, el_y)
#else
#define gt(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_gt)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define le(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_le)(x, el_x, y, el_y)
#else
#define le(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_le)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define lt(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_lt)(x, el_x, y, el_y)
#else
#define lt(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_lt)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define ne(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_ne)(x, el_x, y, el_y)
#else
#define ne(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_ne)(x, el_x, y, el_y)
#endif

#ifdef _STRICT_ARG_TYPE
#define comp_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_comp_const)(x, el_x, const_idx, exp_adj_const)
#else
#define comp_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_comp_const)(x, el_x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define eq_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_eq_const)(x, el_x, const_idx, exp_adj_const)
#else
#define eq_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_eq_const)(x, el_x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define ge_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_ge_const)(x, el_x, const_idx, exp_adj_const)
#else
#define ge_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_ge_const)(x, el_x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define gt_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_gt_const)(x, el_x, const_idx, exp_adj_const)
#else
#define gt_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_gt_const)(x, el_x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define le_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_le_const)(x, el_x, const_idx, exp_adj_const)
#else
#define le_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_le_const)(x, el_x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define lt_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_lt_const)(x, el_x, const_idx, exp_adj_const)
#else
#define lt_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_lt_const)(x, el_x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define ne_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_ne_const)(x, el_x, const_idx, exp_adj_const)
#else
#define ne_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_ne_const)(x, el_x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define comp_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_comp_fr)(fx, fy)
#else
#define comp_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_comp_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define eq_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_eq_fr)(fx, fy)
#else
#define eq_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_eq_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define ge_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_ge_fr)(fx, fy)
#else
#define ge_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_ge_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define gt_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_gt_fr)(fx, fy)
#else
#define gt_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_gt_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define le_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_le_fr)(fx, fy)
#else
#define le_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_le_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define lt_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_lt_fr)(fx, fy)
#else
#define lt_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_lt_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define ne_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_ne_fr)(fx, fy)
#else
#define ne_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_ne_fr)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define neg_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_neg_fr)(fx)
#else
#define neg_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_neg_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define abs_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_abs_fr)(fx)
#else
#define abs_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_abs_fr)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define deqz(x) \
	CSTUB_(_TIE_hemilite_common_tie_deqz)(x)
#else
#define deqz(x) \
	CSTUB_(_TIE_hemilite_common_tie_deqz)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dgez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dgez)(x)
#else
#define dgez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dgez)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dgtz(x) \
	CSTUB_(_TIE_hemilite_common_tie_dgtz)(x)
#else
#define dgtz(x) \
	CSTUB_(_TIE_hemilite_common_tie_dgtz)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dlez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dlez)(x)
#else
#define dlez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dlez)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dltz(x) \
	CSTUB_(_TIE_hemilite_common_tie_dltz)(x)
#else
#define dltz(x) \
	CSTUB_(_TIE_hemilite_common_tie_dltz)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define dnez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dnez)(x)
#else
#define dnez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dnez)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define veq(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_veq)(x, y)
#else
#define veq(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_veq)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vge(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vge)(x, y)
#else
#define vge(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vge)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vgt(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vgt)(x, y)
#else
#define vgt(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vgt)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vle(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vle)(x, y)
#else
#define vle(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vle)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vlt(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vlt)(x, y)
#else
#define vlt(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vlt)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vne(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vne)(x, y)
#else
#define vne(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vne)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define veq_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_veq_const)(x, const_idx, exp_adj_const)
#else
#define veq_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_veq_const)(x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define vge_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vge_const)(x, const_idx, exp_adj_const)
#else
#define vge_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vge_const)(x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define vgt_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vgt_const)(x, const_idx, exp_adj_const)
#else
#define vgt_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vgt_const)(x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define vle_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vle_const)(x, const_idx, exp_adj_const)
#else
#define vle_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vle_const)(x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define vlt_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vlt_const)(x, const_idx, exp_adj_const)
#else
#define vlt_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vlt_const)(x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define vne_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vne_const)(x, const_idx, exp_adj_const)
#else
#define vne_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vne_const)(x, const_idx, exp_adj_const)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_1b2(fx, fy, bx, el_bx1) \
	CSTUB_(_TIE_hemilite_common_tie_sel_1b2)(fx, fy, bx, el_bx1)
#else
#define sel_1b2(fx, fy, bx, el_bx1) \
	CSTUB_(_TIE_hemilite_common_tie_sel_1b2)(fx, fy, bx, el_bx1)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_eq(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_eq)(fx, fy, bx)
#else
#define sel_eq(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_eq)(fx, fy, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_ge(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ge)(fx, fy, bx)
#else
#define sel_ge(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ge)(fx, fy, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_gt(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_gt)(fx, fy, bx)
#else
#define sel_gt(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_gt)(fx, fy, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_le(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_le)(fx, fy, bx)
#else
#define sel_le(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_le)(fx, fy, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_lt(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_lt)(fx, fy, bx)
#else
#define sel_lt(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_lt)(fx, fy, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_ne(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ne)(fx, fy, bx)
#else
#define sel_ne(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ne)(fx, fy, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define sel_ar(fx, fy, sel) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ar)(fx, fy, sel)
#else
#define sel_ar(fx, fy, sel) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ar)(fx, fy, sel)
#endif

#ifdef _STRICT_ARG_TYPE
#define vsel(x, y, bx) \
	CSTUB_(_TIE_hemilite_common_tie_vsel)(x, y, bx)
#else
#define vsel(x, y, bx) \
	CSTUB_(_TIE_hemilite_common_tie_vsel)(x, y, bx)
#endif

#ifdef _STRICT_ARG_TYPE
#define vsel_ar(x, y, sel) \
	CSTUB_(_TIE_hemilite_common_tie_vsel_ar)(x, y, sel)
#else
#define vsel_ar(x, y, sel) \
	CSTUB_(_TIE_hemilite_common_tie_vsel_ar)(x, y, sel)
#endif

#ifdef _STRICT_ARG_TYPE
#define andb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_andb2)(bx, by)
#else
#define andb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_andb2)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define andbc2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_andbc2)(bx, by)
#else
#define andbc2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_andbc2)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define orb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_orb2)(bx, by)
#else
#define orb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_orb2)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define orbc2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_orbc2)(bx, by)
#else
#define orbc2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_orbc2)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define xorb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_xorb2)(bx, by)
#else
#define xorb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_xorb2)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bcount0_maskI)(bx, imask)
#else
#define bcount0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bcount0_maskI)(bx, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bcount0_maskR)(bx, by)
#else
#define bcount0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bcount0_maskR)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bcount1_maskI)(bx, imask)
#else
#define bcount1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bcount1_maskI)(bx, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bcount1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bcount1_maskR)(bx, by)
#else
#define bcount1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bcount1_maskR)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskI)(bx, imask)
#else
#define bfirst0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskI)(bx, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskR)(bx, by)
#else
#define bfirst0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskR)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskI)(bx, imask)
#else
#define bfirst1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskI)(bx, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define bfirst1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskR)(bx, by)
#else
#define bfirst1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskR)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_blast0_maskI)(bx, imask)
#else
#define blast0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_blast0_maskI)(bx, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_blast0_maskR)(bx, by)
#else
#define blast0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_blast0_maskR)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_blast1_maskI)(bx, imask)
#else
#define blast1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_blast1_maskI)(bx, imask)
#endif

#ifdef _STRICT_ARG_TYPE
#define blast1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_blast1_maskR)(bx, by)
#else
#define blast1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_blast1_maskR)(bx, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define bgetI(bx, ipos) \
	CSTUB_(_TIE_hemilite_common_tie_bgetI)(bx, ipos)
#else
#define bgetI(bx, ipos) \
	CSTUB_(_TIE_hemilite_common_tie_bgetI)(bx, ipos)
#endif

#ifdef _STRICT_ARG_TYPE
#define bgetR(bx, rpos) \
	CSTUB_(_TIE_hemilite_common_tie_bgetR)(bx, rpos)
#else
#define bgetR(bx, rpos) \
	CSTUB_(_TIE_hemilite_common_tie_bgetR)(bx, rpos)
#endif

#ifdef _STRICT_ARG_TYPE
#define bsetI(bx, rpos, ibit) \
	CSTUB_(_TIE_hemilite_common_tie_bsetI)(bx, rpos, ibit)
#else
#define bsetI(bx, rpos, ibit) \
	CSTUB_(_TIE_hemilite_common_tie_bsetI)(bx, rpos, ibit)
#endif

#ifdef _STRICT_ARG_TYPE
#define bsetR(bx, rpos, by) \
	CSTUB_(_TIE_hemilite_common_tie_bsetR)(bx, rpos, by)
#else
#define bsetR(bx, rpos, by) \
	CSTUB_(_TIE_hemilite_common_tie_bsetR)(bx, rpos, by)
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adj(z, el_z, x, el_x, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adj)(z, el_z, x, el_x, exp_adj_ar)
#else
#define exp_adj(z, el_z, x, el_x, exp_adj_ar) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_exp_adj)(__z, el_z, x, el_x, exp_adj_ar); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adji(z, el_z, x, el_x, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adji)(z, el_z, x, el_x, exp_adj_imm)
#else
#define exp_adji(z, el_z, x, el_x, exp_adj_imm) { \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_exp_adji)(__z, el_z, x, el_x, exp_adj_imm); \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adj_fr(fx, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adj_fr)(fx, exp_adj_ar)
#else
#define exp_adj_fr(fx, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adj_fr)(fx, exp_adj_ar)
#endif

#ifdef _STRICT_ARG_TYPE
#define exp_adji_fr(fx, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adji_fr)(fx, exp_adj_imm)
#else
#define exp_adji_fr(fx, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adji_fr)(fx, exp_adj_imm)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_neg(fx) \
	CSTUB_(_TIE_hemilite_common_tie_s_neg)(fx)
#else
#define s_neg(fx) \
	CSTUB_(_TIE_hemilite_common_tie_s_neg)(fx)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_copy(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_copy)(fx, fy)
#else
#define s_copy(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_copy)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_and(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_and)(fx, fy)
#else
#define s_and(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_and)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_andc(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_andc)(fx, fy)
#else
#define s_andc(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_andc)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_or(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_or)(fx, fy)
#else
#define s_or(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_or)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_orc(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_orc)(fx, fy)
#else
#define s_orc(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_orc)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_xor(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_xor)(fx, fy)
#else
#define s_xor(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_xor)(fx, fy)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vneg(x) \
	CSTUB_(_TIE_hemilite_common_tie_s_vneg)(x)
#else
#define s_vneg(x) \
	CSTUB_(_TIE_hemilite_common_tie_s_vneg)(x)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vcopy(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vcopy)(x, y)
#else
#define s_vcopy(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vcopy)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vand(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vand)(x, y)
#else
#define s_vand(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vand)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vandc(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vandc)(x, y)
#else
#define s_vandc(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vandc)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vor(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vor)(x, y)
#else
#define s_vor(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vor)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vorc(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vorc)(x, y)
#else
#define s_vorc(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vorc)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define s_vxor(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vxor)(x, y)
#else
#define s_vxor(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vxor)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define floorp_frac(floor, z, el_z, x, el_x, nbits) \
	CSTUB_(_TIE_hemilite_common_tie_floorp_frac)(floor, z, el_z, x, el_x, nbits)
#else
#define floorp_frac(floor, z, el_z, x, el_x, nbits) { \
	unsigned int __floor; \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_floorp_frac)(__floor, __z, el_z, x, el_x, nbits); \
	(floor) = __floor; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define idx_frac(floor, z, el_z, input, nbits) \
	CSTUB_(_TIE_hemilite_common_tie_idx_frac)(floor, z, el_z, input, nbits)
#else
#define idx_frac(floor, z, el_z, input, nbits) { \
	unsigned int __floor; \
	vr64 __z = z; \
	CSTUB_(_TIE_hemilite_common_tie_idx_frac)(__floor, __z, el_z, input, nbits); \
	(floor) = __floor; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define rmax_idx(a, fz, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_rmax_idx)(a, fz, x, idx)
#else
#define rmax_idx(a, fz, x, idx) { \
	unsigned int __a; \
	fr32 __fz; \
	CSTUB_(_TIE_hemilite_common_tie_rmax_idx)(__a, __fz, x, idx); \
	(a) = __a; \
	(fz) = __fz; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define rmin_idx(a, fz, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_rmin_idx)(a, fz, x, idx)
#else
#define rmin_idx(a, fz, x, idx) { \
	unsigned int __a; \
	fr32 __fz; \
	CSTUB_(_TIE_hemilite_common_tie_rmin_idx)(__a, __fz, x, idx); \
	(a) = __a; \
	(fz) = __fz; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmaxmin_init(z, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_vmaxmin_init)(z, x, idx)
#else
#define vmaxmin_init(z, x, idx) { \
	vr64 __z; \
	mir18 __idx; \
	CSTUB_(_TIE_hemilite_common_tie_vmaxmin_init)(__z, x, __idx); \
	(z) = __z; \
	(idx) = __idx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmax_idx(z, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_vmax_idx)(z, x, idx)
#else
#define vmax_idx(z, x, idx) { \
	vr64 __z = z; \
	mir18 __idx = idx; \
	CSTUB_(_TIE_hemilite_common_tie_vmax_idx)(__z, x, __idx); \
	(z) = __z; \
	(idx) = __idx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmin_idx(z, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_vmin_idx)(z, x, idx)
#else
#define vmin_idx(z, x, idx) { \
	vr64 __z = z; \
	mir18 __idx = idx; \
	CSTUB_(_TIE_hemilite_common_tie_vmin_idx)(__z, x, __idx); \
	(z) = __z; \
	(idx) = __idx; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vmax(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmax)(x, y)
#else
#define vmax(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmax)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define vmin(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmin)(x, y)
#else
#define vmin(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmin)(x, y)
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_asc_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_vr)(a, z, x, y, el_y)
#else
#define sortupd_asc_vr(a, z, x, y, el_y) { \
	unsigned int __a; \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_vr)(__a, __z, x, y, el_y); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_des_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_des_vr)(a, z, x, y, el_y)
#else
#define sortupd_des_vr(a, z, x, y, el_y) { \
	unsigned int __a; \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_des_vr)(__a, __z, x, y, el_y); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_asc_ar(a, z, x) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_ar)(a, z, x)
#else
#define sortupd_asc_ar(a, z, x) { \
	unsigned int __a = a; \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_ar)(__a, __z, x); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define sortupd_des_ar(a, z, x) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_des_ar)(a, z, x)
#else
#define sortupd_des_ar(a, z, x) { \
	unsigned int __a = a; \
	vr64 __z; \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_des_ar)(__a, __z, x); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define vbool(x, y, op) \
	CSTUB_(_TIE_hemilite_common_tie_vbool)(x, y, op)
#else
#define vbool(x, y, op) \
	CSTUB_(_TIE_hemilite_common_tie_vbool)(x, y, op)
#endif

#ifdef _STRICT_ARG_TYPE
#define align_up(val, option) \
	CSTUB_(_TIE_hemilite_common_tie_align_up)(val, option)
#else
#define align_up(val, option) \
	CSTUB_(_TIE_hemilite_common_tie_align_up)(val, option)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_MIR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_MIR)(b)
#else
#define mv_MIR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_MIR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_ULSR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_ULSR)(b)
#else
#define mv_ULSR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_ULSR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_CR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_CR)(b)
#else
#define mv_CR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_CR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR(addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR)(addr, fimm)
#else
#define ld_FR(addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR)(addr, fimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR(fregin, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR)(fregin, addr, fimm)
#else
#define st_FR(fregin, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR)(fregin, addr, fimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR_idxR(addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_idxR)(addr, x)
#else
#define ld_FR_idxR(addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_idxR)(addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR_idxR(fregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_idxR)(fregin, addr, x)
#else
#define st_FR_idxR(fregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_idxR)(fregin, addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR_postI(fregout, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_postI)(fregout, (const fr32 **)&(addr), fimm)
#else
#define ld_FR_postI(fregout, addr, fimm) { \
	fr32 __fregout; \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_postI)(__fregout, (const fr32 **)&(addr), fimm); \
	(fregout) = __fregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR_postI(fregin, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_postI)(fregin, (fr32 **)&(addr), fimm)
#else
#define st_FR_postI(fregin, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_postI)(fregin, (fr32 **)&(addr), fimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_FR_postR(fregout, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_postR)(fregout, (const fr32 **)&(addr), x)
#else
#define ld_FR_postR(fregout, addr, x) { \
	fr32 __fregout; \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_postR)(__fregout, (const fr32 **)&(addr), x); \
	(fregout) = __fregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_FR_postR(fregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_postR)(fregin, (fr32 **)&(addr), x)
#else
#define st_FR_postR(fregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_postR)(fregin, (fr32 **)&(addr), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR(addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR)(addr, vimm)
#else
#define ld_VR(addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR)(addr, vimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR(vregin, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR)(vregin, addr, vimm)
#else
#define st_VR(vregin, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR)(vregin, addr, vimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR_idxR(addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_idxR)(addr, x)
#else
#define ld_VR_idxR(addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_idxR)(addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR_idxR(vregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_idxR)(vregin, addr, x)
#else
#define st_VR_idxR(vregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_idxR)(vregin, addr, x)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR_postI(vregout, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_postI)(vregout, (const vr64 **)&(addr), vimm)
#else
#define ld_VR_postI(vregout, addr, vimm) { \
	vr64 __vregout; \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_postI)(__vregout, (const vr64 **)&(addr), vimm); \
	(vregout) = __vregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR_postI(vregin, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_postI)(vregin, (vr64 **)&(addr), vimm)
#else
#define st_VR_postI(vregin, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_postI)(vregin, (vr64 **)&(addr), vimm)
#endif

#ifdef _STRICT_ARG_TYPE
#define ld_VR_postR(vregout, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_postR)(vregout, (const vr64 **)&(addr), x)
#else
#define ld_VR_postR(vregout, addr, x) { \
	vr64 __vregout; \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_postR)(__vregout, (const vr64 **)&(addr), x); \
	(vregout) = __vregout; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define st_VR_postR(vregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_postR)(vregin, (vr64 **)&(addr), x)
#else
#define st_VR_postR(vregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_postR)(vregin, (vr64 **)&(addr), x)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_FR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_FR)(b)
#else
#define mv_FR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_FR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_ar_fr(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_ar_fr)(b)
#else
#define move_ar_fr(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_ar_fr)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_fr_ar(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_ar)(b)
#else
#define move_fr_ar(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_ar)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define mv_VR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_VR)(b)
#else
#define mv_VR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_VR)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_ar_bbr(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_ar_bbr)(b)
#else
#define move_ar_bbr(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_ar_bbr)(b)
#endif

#ifdef _STRICT_ARG_TYPE
#define move_bbr_ar(a) \
	CSTUB_(_TIE_hemilite_common_tie_move_bbr_ar)(a)
#else
#define move_bbr_ar(a) \
	CSTUB_(_TIE_hemilite_common_tie_move_bbr_ar)(a)
#endif

#ifdef _STRICT_ARG_TYPE
#define shift_from_bbr(a, x) \
	CSTUB_(_TIE_hemilite_common_tie_shift_from_bbr)(a, x)
#else
#define shift_from_bbr(a, x) { \
	unsigned int __a = a; \
	CSTUB_(_TIE_hemilite_common_tie_shift_from_bbr)(__a, x); \
	(a) = __a; \
}
#endif

#ifdef _STRICT_ARG_TYPE
#define shift_to_bbr(a, z) \
	CSTUB_(_TIE_hemilite_common_tie_shift_to_bbr)(a, z)
#else
#define shift_to_bbr(a, z) { \
	unsigned int __a = a; \
	atbool __z; \
	CSTUB_(_TIE_hemilite_common_tie_shift_to_bbr)(__a, __z); \
	(a) = __a; \
	(z) = __z; \
}
#endif

#define XT_RSR_PRID() \
	CSTUB_(_TIE_xt_core_RSR_PRID)()

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

typedef CSTUB_MSC_ALIGN(8) struct cr64_struct {
unsigned int _[2];
} CSTUB_GCC_ALIGN(8) cr64;

typedef CSTUB_MSC_ALIGN(4) struct mir18_struct {
unsigned int _[1];
} CSTUB_GCC_ALIGN(4) mir18;

typedef CSTUB_MSC_ALIGN(4) struct ulsr32_struct {
unsigned int _[1];
} CSTUB_GCC_ALIGN(4) ulsr32;

typedef CSTUB_MSC_ALIGN(1) struct atbool_struct {
unsigned char  _[1];
} CSTUB_GCC_ALIGN(1) atbool;

/* Proto declarations */
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
CSTUB_EXTERN void CSTUB_(_TIE_xt_density_NOP_N)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_NOP)(void);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANDBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ORBC)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_XORB)(const xtbool bs /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY4)(const xtbool4 bs4 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ALL8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN xtbool CSTUB_(_TIE_xt_booleans_ANY8)(const xtbool8 bs8 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVF)(unsigned int* arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_booleans_MOVT)(unsigned int* arr /*inout*/, const unsigned int ars /*in*/, const xtbool bt /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(immediate bitindex /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(const unsigned int art /*in*/, const unsigned int ars /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_atbool_storei)(const atbool a /*in*/, const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_atbool_loadi)(const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_atbool_move)(const atbool b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ulsr32_storei)(const ulsr32 a /*in*/, const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_ulsr32_loadi)(const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mir18_storei)(const mir18 a /*in*/, const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mir18_loadi)(const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_cr64_storei)(const cr64 a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_cr64_loadi)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_JammingBit)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_JammingBit)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_MvmAux)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_MvmAux)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_1)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_0)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_0)(const unsigned int v /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_1)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_1)(const unsigned int v /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mir18_move)(const mir18 b /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_ulsr32_move)(const ulsr32 b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_cr64_move)(const cr64 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fr32_move)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fr32_loadi)(const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storei)(const fr32 v /*in*/, const fr32 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fr32_loadx)(const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storex)(const fr32 v /*in*/, const fr32 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_loadip)(fr32* v /*out*/, const fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storeip)(const fr32 v /*in*/, fr32 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_loadxp)(fr32* v /*out*/, const fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fr32_storexp)(const fr32 v /*in*/, fr32 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_int32)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_uint32)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_int32_rtor_fr32)(const int a /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_fr32)(const unsigned int a /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_move)(const vr64 b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_loadi)(const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storei)(const vr64 v /*in*/, const vr64 * p /*in*/, immediate o /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_loadx)(const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storex)(const vr64 v /*in*/, const vr64 * p /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_loadip)(vr64* v /*out*/, const vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storeip)(const vr64 v /*in*/, vr64 ** p /*inout*/, immediate o /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_loadxp)(vr64* v /*out*/, const vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vr64_storexp)(const vr64 v /*in*/, vr64 ** p /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_get_VRH)(const vr64 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_get_VRL)(const vr64 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_set_VRH)(vr64* a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_set_VRL)(vr64* a /*inout*/, const fr32 b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vr64_pair)(const fr32 hi /*in*/, const fr32 lo /*in*/);
CSTUB_EXTERN int CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_int32)(const atbool b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_uint32)(const atbool b /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_int32_rtor_atbool)(const int a /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_atbool)(const unsigned int a /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_BBR)(const atbool a /*in*/, const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_ld_BBR)(const atbool * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_mv_BBR)(const atbool b /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_ULSR)(const ulsr32 a /*in*/, const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_ld_ULSR)(const ulsr32 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_MIR)(const mir18 a /*in*/, const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_ld_MIR)(const mir18 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_CR)(const cr64 a /*in*/, const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_ld_CR)(const cr64 * b /*in*/, immediate c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_ld)(const unsigned int * src /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_align_ld)(const unsigned int ** src /*inout*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_ldu)(const unsigned int ** src /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_flush_ld)(const unsigned int ** src /*inout*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_st)(const unsigned int * src /*in*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_align_st)(const unsigned int * src /*in*/, unsigned int ** dst /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_stu)(const unsigned int * src /*in*/, unsigned int ** dst /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_flush_st)(const unsigned int * src /*in*/, const unsigned int * dst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_dma_buf_save)(unsigned int ** dst /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_bdir)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_brev)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR_perm)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI_perm_vr)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR_perm)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI_perm_vr)(vr64* r /*out*/, const vr64 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI_perm)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR_perm)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI_perm_vr)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR_perm)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI_perm_vr)(vr64* r /*out*/, const vr64 z /*in*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate perm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI_perm)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate perm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postR)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postI)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_circI)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxR)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxI)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postR)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postI)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_circI)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxR)(const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxI)(const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postR)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postI)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_circI)(vr64* z /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxR)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxI)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postR)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postI)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_circI)(vr64* z /*inout*/, const unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_align_32x2_load)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a)(vr64* z /*out*/, ulsr32* buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_24x2_vr_a)(vr64* z /*out*/, ulsr32* buf /*inout*/, const unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_circ)(vr64* z /*out*/, ulsr32* buf /*inout*/, const unsigned int ** ptr /*inout*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxR)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxI)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postR)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_circI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxR)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxI)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postR)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_circI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxR)(const vr64 z /*in*/, const atbool gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxI)(const vr64 z /*in*/, const atbool gate /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postR)(const vr64 z /*in*/, const atbool gate /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postI)(const vr64 z /*in*/, const atbool gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_circI)(const vr64 z /*in*/, const atbool gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxR)(const vr64 z /*in*/, const atbool gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxI)(const vr64 z /*in*/, const atbool gate /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postR)(const vr64 z /*in*/, const atbool gate /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postI)(const vr64 z /*in*/, const atbool gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_circI)(const vr64 z /*in*/, const atbool gate /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_bdir)(const vr64 z /*in*/, const atbool gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_brev)(const vr64 z /*in*/, const atbool gate /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxR)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxI)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postR)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_circI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxR)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxI)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postR)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_circI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxR)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxI)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postR)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_circI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxR)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxI)(const vr64 z /*in*/, const unsigned int * ptr /*in*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postR)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, const unsigned int ofst /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_circI)(const vr64 z /*in*/, unsigned int ** ptr /*inout*/, immediate ofst1 /*in*/, const cr64 c /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_align_32x2_store)(const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a)(const vr64 z /*in*/, ulsr32* buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_24x2_vr_a)(const vr64 z /*in*/, ulsr32* buf /*inout*/, unsigned int ** ptr /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_circ)(const vr64 z /*in*/, ulsr32* buf /*inout*/, unsigned int ** ptr /*inout*/, const cr64 c /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_flush_32x2)(const ulsr32 buf /*in*/, const unsigned int * ptr /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_fr_postI)(fr32* fx /*out*/, const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_fr_postI)(const fr32 fx /*in*/, unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_brev_upd)(atbool* gate /*out*/, unsigned int* idx_out /*out*/, const unsigned int idx_in /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_brev_upd_ext)(atbool* gate /*inout*/, unsigned int* idx_out /*inout*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr)(const vr64 x /*in*/, immediate sel1 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move32_vr_ar)(vr64* z /*inout*/, immediate sel1 /*in*/, const unsigned int a /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr_idx)(const vr64 x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_move32_fr_vr_idx)(const vr64 x /*in*/, const unsigned int idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_eqz)(fr32* z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_gez)(fr32* z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_gtz)(fr32* z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_lez)(fr32* z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_ltz)(fr32* z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_nez)(fr32* z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_sat)(fr32* z /*inout*/, const fr32 x /*in*/, const fr32 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_move_fr_arnz)(fr32* z /*inout*/, const fr32 x /*in*/, const unsigned int ax /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_eqz)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gez)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gtz)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_lez)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_ltz)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_nez)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmove_vr_sat)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_replicate)(vr64* z /*inout*/, immediate sel_code /*in*/, const vr64 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_replicate_ar)(vr64* z /*inout*/, immediate sel_code /*in*/, const unsigned int ar /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vreplicate)(const vr64 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vreplicate_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x1)(vr64* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x2)(vr64* z /*inout*/, const unsigned int exp_fxp /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x1)(vr64* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x2)(vr64* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x1)(vr64* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x2)(vr64* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate round /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x1)(vr64* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x2)(vr64* z /*inout*/, immediate is_signed /*in*/, immediate exp_bits /*in*/, const unsigned int bias /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_32F_x1)(vr64* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_32I_x1)(vr64* z /*inout*/, const unsigned int exp_fxp /*in*/, immediate rnd /*in*/, immediate el /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_float_to_32F_x2)(vr64* z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_IEEE_float_x2)(vr64* z /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_64F)(const unsigned int x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32I)(const vr64 x /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_64F)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32F)(const vr64 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_double_to_64F)(vr64* z /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_IEEE_double)(vr64* z /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vadd_perm)(const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vsum_perm)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate sign_z /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmul_perm)(const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs2 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmac_perm)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs2 /*in*/, immediate sign_z /*in*/, immediate swap_z /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmac_boost)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs2 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vblend)(const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vblend_add)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate sign_z /*in*/, immediate swap_z /*in*/, immediate div_by_2_op /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vblend_boost)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate selin_h /*in*/, immediate selin_l /*in*/, immediate signs4 /*in*/, immediate boost /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fadds)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fmuls)(const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_fmacs)(const fr32 fz /*in*/, const fr32 fx /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_dadds)(const vr64 z /*in*/, const vr64 x /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_dmuls)(const vr64 x /*in*/, const vr64 y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_dmacs)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vadds)(const vr64 x /*in*/, const vr64 y /*in*/, immediate signs4 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmuls)(const vr64 x /*in*/, const vr64 y /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmacs)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate signs2 /*in*/, immediate sign_z /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_cmul)(const vr64 x /*in*/, const vr64 y /*in*/, immediate conj /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_cmac)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate conj /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_cmas)(const vr64 z /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate conj /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmulf)(const vr64 x /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmacf)(const vr64 z /*in*/, const vr64 x /*in*/, const fr32 fy /*in*/, immediate signs2 /*in*/, immediate sign_z /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vabs)(const vr64 x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vexp_adj)(const vr64 x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vexp_adji)(const vr64 x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vpermi)(const vr64 x /*in*/, const vr64 y /*in*/, immediate sel4 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_seta_vr)(vr64* z /*inout*/, immediate sel_code /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vseta_vr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_seta_ar)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_seta_fr)(immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_AccExtend_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idx16vr)(vr64* z /*inout*/, const unsigned int * ptr /*in*/, const vr64 vidx16 /*in*/, immediate ptr_sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB0_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB1_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB2_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB3_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB4_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB5_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB6_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_VB7_postI)(const unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_bounded)(vr64* z /*out*/, ulsr32* buf /*inout*/, const unsigned int ** ptr /*inout*/, mir18* count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_load_BBx_VB67_a_bounded)(ulsr32* buf /*inout*/, const unsigned int ** ptr /*inout*/, mir18* count /*inout*/, const unsigned int sel /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_flush_32x2_bounded)(const ulsr32 buf /*in*/, unsigned int ** ptr /*inout*/, mir18* count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_bounded)(const vr64 z /*in*/, ulsr32* buf /*inout*/, unsigned int ** ptr /*inout*/, mir18* count /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_AccExtend_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB0_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_BB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB1_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB2_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB3_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB4_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB5_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB6_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_store_VB7_postI)(unsigned int ** ptr /*inout*/, immediate ofst2 /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_afloat_exp_extract)(const vr64 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mov_AccExtend_vr)(const vr64 x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_mov_vr_AccExtend)(void);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_mov_BB_VB67_to_vrVB_VB45)(void);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mov_vrVB_VB45_to_BB_VB67)(const vr64 x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_precess_16bits)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_set_BB_vrVB67_zero)(void);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_exp_shift_amount)(const vr64 input1 /*in*/, const vr64 input2 /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rnd_sat_pack)(vr64* z /*inout*/, immediate el32 /*in*/, const vr64 x /*in*/, const vr64 y /*in*/, const atbool sgn /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rectify32_into8)(vr64* z /*inout*/, const vr64 x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/, immediate half /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_shift8_into32_arith)(const vr64 x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/, immediate el32 /*in*/, immediate half /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_shift32_arith)(const vr64 x /*in*/, const unsigned int shift /*in*/, immediate rnd /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mac8bx8b)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/, const atbool signed /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_sparse)(vr64* z /*inout*/, const vr64 x /*in*/, const vr64 y /*in*/, const atbool signed /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_conv)(vr64* z /*inout*/, const vr64 x /*in*/, const atbool signed /*in*/, immediate shift_in /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mir_init)(const unsigned int low /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_f_abs)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fclamp)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fclamp_bp)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fclamp_one)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fmax)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_fmin)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_max_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_min_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_log2)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_pow2)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sigmoid)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_inv)(const fr32 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ratio)(fr32* z /*out*/, const fr32 x /*in*/, const fr32 y /*in*/, atbool* bz /*out*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_atanratio)(const fr32 x /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_invsqrt)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sine)(const fr32 x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_cosine)(const fr32 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_log2mul)(fr32* z /*out*/, const fr32 x /*in*/, const fr32 y /*in*/, atbool* bz /*out*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_cspow2)(const fr32 x /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_comp)(const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_eq)(const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ge)(const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_gt)(const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_le)(const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_lt)(const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ne)(const vr64 x /*in*/, immediate el_x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_comp_const)(const vr64 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_eq_const)(const vr64 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ge_const)(const vr64 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_gt_const)(const vr64 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_le_const)(const vr64 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_lt_const)(const vr64 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ne_const)(const vr64 x /*in*/, immediate el_x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_comp_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_eq_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ge_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_gt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_le_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_lt_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_ne_fr)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_neg_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_abs_fr)(const fr32 fx /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_deqz)(const vr64 x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dgez)(const vr64 x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dgtz)(const vr64 x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dlez)(const vr64 x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dltz)(const vr64 x /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_dnez)(const vr64 x /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_veq)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vge)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vgt)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vle)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vlt)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vne)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_veq_const)(const vr64 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vge_const)(const vr64 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vgt_const)(const vr64 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vle_const)(const vr64 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vlt_const)(const vr64 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_vne_const)(const vr64 x /*in*/, immediate const_idx /*in*/, immediate exp_adj_const /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_1b2)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool bx /*in*/, immediate el_bx1 /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_eq)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_ge)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_gt)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_le)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_lt)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_ne)(const fr32 fx /*in*/, const fr32 fy /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_sel_ar)(const fr32 fx /*in*/, const fr32 fy /*in*/, const unsigned int sel /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vsel)(const vr64 x /*in*/, const vr64 y /*in*/, const atbool bx /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vsel_ar)(const vr64 x /*in*/, const vr64 y /*in*/, const unsigned int sel /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_andb2)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_andbc2)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_orb2)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_orbc2)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_xorb2)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount0_maskI)(const atbool bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount0_maskR)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount1_maskI)(const atbool bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bcount1_maskR)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskI)(const atbool bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskR)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskI)(const atbool bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskR)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast0_maskI)(const atbool bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast0_maskR)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast1_maskI)(const atbool bx /*in*/, immediate imask /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_blast1_maskR)(const atbool bx /*in*/, const atbool by /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bgetI)(const atbool bx /*in*/, immediate ipos /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_bgetR)(const atbool bx /*in*/, const unsigned int rpos /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_bsetI)(const atbool bx /*in*/, const unsigned int rpos /*in*/, immediate ibit /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_bsetR)(const atbool bx /*in*/, const unsigned int rpos /*in*/, const unsigned int by /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_exp_adj)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_exp_adji)(vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_exp_adj_fr)(const fr32 fx /*in*/, const unsigned int exp_adj_ar /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_exp_adji_fr)(const fr32 fx /*in*/, immediate exp_adj_imm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_neg)(const fr32 fx /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_copy)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_and)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_andc)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_or)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_orc)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_s_xor)(const fr32 fx /*in*/, const fr32 fy /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vneg)(const vr64 x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vcopy)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vand)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vandc)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vor)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vorc)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_s_vxor)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_floorp_frac)(unsigned int* floor /*out*/, vr64* z /*inout*/, immediate el_z /*in*/, const vr64 x /*in*/, immediate el_x /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_idx_frac)(unsigned int* floor /*out*/, vr64* z /*inout*/, immediate el_z /*in*/, const unsigned int input /*in*/, immediate nbits /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rmax_idx)(unsigned int* a /*out*/, fr32* fz /*out*/, const vr64 x /*in*/, const mir18 idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_rmin_idx)(unsigned int* a /*out*/, fr32* fz /*out*/, const vr64 x /*in*/, const mir18 idx /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmaxmin_init)(vr64* z /*out*/, const vr64 x /*in*/, mir18* idx /*out*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmax_idx)(vr64* z /*inout*/, const vr64 x /*in*/, mir18* idx /*inout*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_vmin_idx)(vr64* z /*inout*/, const vr64 x /*in*/, mir18* idx /*inout*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmax)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vmin)(const vr64 x /*in*/, const vr64 y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_vr)(unsigned int* a /*out*/, vr64* z /*out*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_des_vr)(unsigned int* a /*out*/, vr64* z /*out*/, const vr64 x /*in*/, const vr64 y /*in*/, immediate el_y /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_ar)(unsigned int* a /*inout*/, vr64* z /*out*/, const vr64 x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_sortupd_des_ar)(unsigned int* a /*inout*/, vr64* z /*out*/, const vr64 x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_vbool)(const vr64 x /*in*/, const vr64 y /*in*/, immediate op /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_align_up)(const unsigned int val /*in*/, const unsigned int option /*in*/);
CSTUB_EXTERN mir18 CSTUB_(_TIE_hemilite_common_tie_mv_MIR)(const mir18 b /*in*/);
CSTUB_EXTERN ulsr32 CSTUB_(_TIE_hemilite_common_tie_mv_ULSR)(const ulsr32 b /*in*/);
CSTUB_EXTERN cr64 CSTUB_(_TIE_hemilite_common_tie_mv_CR)(const cr64 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_ld_FR)(const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, immediate fimm /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_ld_FR_idxR)(const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR_idxR)(const fr32 fregin /*in*/, const fr32 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_FR_postI)(fr32* fregout /*out*/, const fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR_postI)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, immediate fimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_FR_postR)(fr32* fregout /*out*/, const fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_FR_postR)(const fr32 fregin /*in*/, fr32 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_ld_VR)(const vr64 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR)(const vr64 vregin /*in*/, const vr64 * addr /*in*/, immediate vimm /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_ld_VR_idxR)(const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR_idxR)(const vr64 vregin /*in*/, const vr64 * addr /*in*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_VR_postI)(vr64* vregout /*out*/, const vr64 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR_postI)(const vr64 vregin /*in*/, vr64 ** addr /*inout*/, immediate vimm /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_ld_VR_postR)(vr64* vregout /*out*/, const vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_st_VR_postR)(const vr64 vregin /*in*/, vr64 ** addr /*inout*/, const unsigned int x /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_mv_FR)(const fr32 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move_ar_fr)(const fr32 b /*in*/);
CSTUB_EXTERN fr32 CSTUB_(_TIE_hemilite_common_tie_move_fr_ar)(const unsigned int b /*in*/);
CSTUB_EXTERN vr64 CSTUB_(_TIE_hemilite_common_tie_mv_VR)(const vr64 b /*in*/);
CSTUB_EXTERN unsigned int CSTUB_(_TIE_hemilite_common_tie_move_ar_bbr)(const atbool b /*in*/);
CSTUB_EXTERN atbool CSTUB_(_TIE_hemilite_common_tie_move_bbr_ar)(const unsigned int a /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_shift_from_bbr)(unsigned int* a /*inout*/, const atbool x /*in*/);
CSTUB_EXTERN void CSTUB_(_TIE_hemilite_common_tie_shift_to_bbr)(unsigned int* a /*inout*/, atbool* z /*out*/);

CSTUB_EXTERN int CSTUB_(_TIE_xt_core_RSR_PRID)(void);
CSTUB_EXTERN unsigned CSTUB_(_TIE_xt_core_RSR_SAR)(void);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_WSR_SAR)(unsigned t);
CSTUB_EXTERN void CSTUB_(_TIE_xt_core_XSR_SAR)(unsigned* t /*inout*/);
/* Proto macros */
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
#define XT_NOP_N() \
	CSTUB_(_TIE_xt_density_NOP_N)()
#define XT_NOP() \
	CSTUB_(_TIE_xt_core_NOP)()
#define XT_ANDB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDB)(bs, bt)
#define XT_ANDBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ANDBC)(bs, bt)
#define XT_ORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORB)(bs, bt)
#define XT_ORBC(bs, bt) \
	CSTUB_(_TIE_xt_booleans_ORBC)(bs, bt)
#define XT_XORB(bs, bt) \
	CSTUB_(_TIE_xt_booleans_XORB)(bs, bt)
#define XT_ALL4(bs4) \
	CSTUB_(_TIE_xt_booleans_ALL4)(bs4)
#define XT_ANY4(bs4) \
	CSTUB_(_TIE_xt_booleans_ANY4)(bs4)
#define XT_ALL8(bs8) \
	CSTUB_(_TIE_xt_booleans_ALL8)(bs8)
#define XT_ANY8(bs8) \
	CSTUB_(_TIE_xt_booleans_ANY8)(bs8)
#define XT_MOVF(arr, ars, bt) \
	CSTUB_(_TIE_xt_booleans_MOVF)(&arr, ars, bt)
#define XT_MOVT(arr, ars, bt) \
	CSTUB_(_TIE_xt_booleans_MOVT)(&arr, ars, bt)
#define READ_IMPWIRE() \
	CSTUB_(_TIE_xt_ioports_READ_IMPWIRE)()
#define SETB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_SETB_EXPSTATE)(bitindex)
#define CLRB_EXPSTATE(bitindex) \
	CSTUB_(_TIE_xt_ioports_CLRB_EXPSTATE)(bitindex)
#define WRMSK_EXPSTATE(art, ars) \
	CSTUB_(_TIE_xt_ioports_WRMSK_EXPSTATE)(art, ars)
#define atbool_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_storei)(a, b, c)
#define atbool_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_loadi)(b, c)
#define atbool_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_move)(b)
#define ulsr32_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_storei)(a, b, c)
#define ulsr32_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_loadi)(b, c)
#define mir18_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_storei)(a, b, c)
#define mir18_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_loadi)(b, c)
#define cr64_storei(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_storei)(a, b, c)
#define cr64_loadi(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_loadi)(b, c)
#define RUR_JammingBit() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_JammingBit)()
#define WUR_JammingBit(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_JammingBit)(v)
#define RUR_AccExtend_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_0)()
#define WUR_AccExtend_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_0)(v)
#define RUR_AccExtend_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_AccExtend_1)()
#define WUR_AccExtend_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_AccExtend_1)(v)
#define RUR_BB0_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_0)()
#define WUR_BB0_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_0)(v)
#define RUR_BB0_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB0_1)()
#define WUR_BB0_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB0_1)(v)
#define RUR_BB1_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_0)()
#define WUR_BB1_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_0)(v)
#define RUR_BB1_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB1_1)()
#define WUR_BB1_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB1_1)(v)
#define RUR_BB2_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_0)()
#define WUR_BB2_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_0)(v)
#define RUR_BB2_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB2_1)()
#define WUR_BB2_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB2_1)(v)
#define RUR_BB3_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_0)()
#define WUR_BB3_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_0)(v)
#define RUR_BB3_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_BB3_1)()
#define WUR_BB3_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_BB3_1)(v)
#define RUR_MvmAux() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_MvmAux)()
#define WUR_MvmAux(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_MvmAux)(v)
#define RUR_VB1_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_0)()
#define WUR_VB1_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_0)(v)
#define RUR_VB1_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB1_1)()
#define WUR_VB1_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB1_1)(v)
#define RUR_VB2_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_0)()
#define WUR_VB2_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_0)(v)
#define RUR_VB2_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB2_1)()
#define WUR_VB2_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB2_1)(v)
#define RUR_VB3_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_0)()
#define WUR_VB3_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_0)(v)
#define RUR_VB3_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB3_1)()
#define WUR_VB3_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB3_1)(v)
#define RUR_VB4_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_0)()
#define WUR_VB4_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_0)(v)
#define RUR_VB4_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB4_1)()
#define WUR_VB4_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB4_1)(v)
#define RUR_VB5_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_0)()
#define WUR_VB5_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_0)(v)
#define RUR_VB5_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB5_1)()
#define WUR_VB5_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB5_1)(v)
#define RUR_VB6_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_0)()
#define WUR_VB6_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_0)(v)
#define RUR_VB6_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB6_1)()
#define WUR_VB6_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB6_1)(v)
#define RUR_VB7_0() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_0)()
#define WUR_VB7_0(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_0)(v)
#define RUR_VB7_1() \
	CSTUB_(_TIE_hemilite_common_tie_RUR_VB7_1)()
#define WUR_VB7_1(v) \
	CSTUB_(_TIE_hemilite_common_tie_WUR_VB7_1)(v)
#define mir18_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_mir18_move)(b)
#define ulsr32_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_ulsr32_move)(b)
#define cr64_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_cr64_move)(b)
#define fr32_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_move)(b)
#define fr32_loadi(p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadi)(p, o)
#define fr32_storei(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storei)(v, p, o)
#define fr32_loadx(p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadx)(p, x)
#define fr32_storex(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storex)(v, p, x)
#define fr32_loadip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadip)(&v, (const fr32 **)&(p), o)
#define fr32_storeip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storeip)(v, (fr32 **)&(p), o)
#define fr32_loadxp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_loadxp)(&v, (const fr32 **)&(p), x)
#define fr32_storexp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_storexp)(v, (fr32 **)&(p), x)
#define fr32_rtor_int32(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_int32)(b)
#define fr32_rtor_uint32(b) \
	CSTUB_(_TIE_hemilite_common_tie_fr32_rtor_uint32)(b)
#define int32_rtor_fr32(a) \
	CSTUB_(_TIE_hemilite_common_tie_int32_rtor_fr32)(a)
#define uint32_rtor_fr32(a) \
	CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_fr32)(a)
#define vr64_move(b) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_move)(b)
#define vr64_loadi(p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadi)(p, o)
#define vr64_storei(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storei)(v, p, o)
#define vr64_loadx(p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadx)(p, x)
#define vr64_storex(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storex)(v, p, x)
#define vr64_loadip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadip)(&v, (const vr64 **)&(p), o)
#define vr64_storeip(v, p, o) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storeip)(v, (vr64 **)&(p), o)
#define vr64_loadxp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_loadxp)(&v, (const vr64 **)&(p), x)
#define vr64_storexp(v, p, x) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_storexp)(v, (vr64 **)&(p), x)
#define get_VRH(b) \
	CSTUB_(_TIE_hemilite_common_tie_get_VRH)(b)
#define get_VRL(b) \
	CSTUB_(_TIE_hemilite_common_tie_get_VRL)(b)
#define set_VRH(a, b) \
	CSTUB_(_TIE_hemilite_common_tie_set_VRH)(&a, b)
#define set_VRL(a, b) \
	CSTUB_(_TIE_hemilite_common_tie_set_VRL)(&a, b)
#define vr64_pair(hi, lo) \
	CSTUB_(_TIE_hemilite_common_tie_vr64_pair)(hi, lo)
#define atbool_rtor_int32(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_int32)(b)
#define atbool_rtor_uint32(b) \
	CSTUB_(_TIE_hemilite_common_tie_atbool_rtor_uint32)(b)
#define int32_rtor_atbool(a) \
	CSTUB_(_TIE_hemilite_common_tie_int32_rtor_atbool)(a)
#define uint32_rtor_atbool(a) \
	CSTUB_(_TIE_hemilite_common_tie_uint32_rtor_atbool)(a)
#define st_BBR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_BBR)(a, b, c)
#define ld_BBR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_BBR)(b, c)
#define mv_BBR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_BBR)(b)
#define st_ULSR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_ULSR)(a, b, c)
#define ld_ULSR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_ULSR)(b, c)
#define st_MIR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_MIR)(a, b, c)
#define ld_MIR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_MIR)(b, c)
#define st_CR(a, b, c) \
	CSTUB_(_TIE_hemilite_common_tie_st_CR)(a, b, c)
#define ld_CR(b, c) \
	CSTUB_(_TIE_hemilite_common_tie_ld_CR)(b, c)
#define dma_ld(src) \
	CSTUB_(_TIE_hemilite_common_tie_dma_ld)(src)
#define dma_align_ld(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_align_ld)((const unsigned int **)&(src), dst)
#define dma_ldu(src) \
	CSTUB_(_TIE_hemilite_common_tie_dma_ldu)((const unsigned int **)&(src))
#define dma_flush_ld(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_flush_ld)((const unsigned int **)&(src), dst)
#define dma_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_st)(src, dst)
#define dma_align_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_align_st)(src, (unsigned int **)&(dst))
#define dma_stu(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_stu)(src, (unsigned int **)&(dst))
#define dma_flush_st(src, dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_flush_st)(src, dst)
#define dma_buf_save(dst) \
	CSTUB_(_TIE_hemilite_common_tie_dma_buf_save)((unsigned int **)&(dst))
#define load32x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR)(ptr, ofst)
#define load32x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI)(ptr, ofst2)
#define load32x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR)(&z, (const unsigned int **)&(ptr), ofst)
#define load32x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2)
#define load32x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c)
#define load32x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR)(&z, ptr, ofst, sel1)
#define load32x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI)(&z, ptr, ofst2, sel1)
#define load32x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel1)
#define load32x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel1)
#define load32x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#define load32x2_vr_bdir(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_bdir)(ptr, ofst)
#define load32x2_vr_brev(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_brev)(ptr, ofst)
#define load32x2_vr_idxR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxR_perm)(&z, ptr, ofst, perm)
#define load32x2_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_idxI_perm_vr)(z, ptr, ofst2, perm)
#define load32x2_vr_postR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postR_perm)(&z, (const unsigned int **)&(ptr), ofst, perm)
#define load32x2_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_postI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst2, perm)
#define load32x2_vr_circI_perm(z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x2_vr_circI_perm)(&z, (const unsigned int **)&(ptr), ofst1, c, perm)
#define load32x1_vr_idxR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxR_perm)(&z, ptr, ofst, perm)
#define load32x1_vr_idxI_perm_vr(z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idxI_perm_vr)(z, ptr, ofst2, perm)
#define load32x1_vr_postR_perm(z, ptr, ofst, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postR_perm)(&z, (const unsigned int **)&(ptr), ofst, perm)
#define load32x1_vr_postI_perm_vr(r, z, ptr, ofst2, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_postI_perm_vr)(&r, z, (const unsigned int **)&(ptr), ofst2, perm)
#define load32x1_vr_circI_perm(z, ptr, ofst1, c, perm) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_circI_perm)(&z, (const unsigned int **)&(ptr), ofst1, c, perm)
#define load16x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxR)(ptr, ofst)
#define load16x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_idxI)(ptr, ofst2)
#define load16x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postR)(&z, (const unsigned int **)&(ptr), ofst)
#define load16x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2)
#define load16x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_load16x2_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c)
#define load16x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxR)(&z, ptr, ofst, sel1)
#define load16x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_idxI)(&z, ptr, ofst2, sel1)
#define load16x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel1)
#define load16x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel1)
#define load16x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load16x1_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#define load8x2_vr_idxR(ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxR)(ptr, ofst)
#define load8x2_vr_idxI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_idxI)(ptr, ofst2)
#define load8x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postR)(&z, (const unsigned int **)&(ptr), ofst)
#define load8x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2)
#define load8x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_load8x2_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c)
#define load8x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxR)(&z, ptr, ofst, sel1)
#define load8x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_idxI)(&z, ptr, ofst2, sel1)
#define load8x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postR)(&z, (const unsigned int **)&(ptr), ofst, sel1)
#define load8x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_postI)(&z, (const unsigned int **)&(ptr), ofst2, sel1)
#define load8x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_load8x1_vr_circI)(&z, (const unsigned int **)&(ptr), ofst1, c, sel1)
#define align_32x2_load(ptr) \
	CSTUB_(_TIE_hemilite_common_tie_align_32x2_load)(ptr)
#define load_32x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a)(&z, &buf, (const unsigned int **)&(ptr))
#define load_24x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_load_24x2_vr_a)(&z, &buf, (const unsigned int **)&(ptr))
#define load_32x2_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_circ)(&z, &buf, (const unsigned int **)&(ptr), c)
#define store32x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxR)(z, ptr, ofst)
#define store32x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_idxI)(z, ptr, ofst2)
#define store32x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#define store32x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#define store32x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#define store32x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxR)(z, ptr, ofst, sel1)
#define store32x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_idxI)(z, ptr, ofst2, sel1)
#define store32x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#define store32x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#define store32x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#define store32x2_vr_br_idxR(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxR)(z, gate, ptr, ofst)
#define store32x2_vr_br_idxI(z, gate, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_idxI)(z, gate, ptr, ofst2)
#define store32x2_vr_br_postR(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postR)(z, gate, (unsigned int **)&(ptr), ofst)
#define store32x2_vr_br_postI(z, gate, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_postI)(z, gate, (unsigned int **)&(ptr), ofst2)
#define store32x2_vr_br_circI(z, gate, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_circI)(z, gate, (unsigned int **)&(ptr), ofst1, c)
#define store32x1_vr_br_idxR(z, gate, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxR)(z, gate, ptr, ofst, sel1)
#define store32x1_vr_br_idxI(z, gate, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_idxI)(z, gate, ptr, ofst2, sel1)
#define store32x1_vr_br_postR(z, gate, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postR)(z, gate, (unsigned int **)&(ptr), ofst, sel1)
#define store32x1_vr_br_postI(z, gate, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_postI)(z, gate, (unsigned int **)&(ptr), ofst2, sel1)
#define store32x1_vr_br_circI(z, gate, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store32x1_vr_br_circI)(z, gate, (unsigned int **)&(ptr), ofst1, c, sel1)
#define store32x2_vr_br_bdir(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_bdir)(z, gate, ptr, ofst)
#define store32x2_vr_br_brev(z, gate, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store32x2_vr_br_brev)(z, gate, ptr, ofst)
#define store16x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxR)(z, ptr, ofst)
#define store16x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_idxI)(z, ptr, ofst2)
#define store16x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#define store16x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#define store16x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store16x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#define store16x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxR)(z, ptr, ofst, sel1)
#define store16x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_idxI)(z, ptr, ofst2, sel1)
#define store16x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#define store16x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#define store16x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store16x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#define store8x2_vr_idxR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxR)(z, ptr, ofst)
#define store8x2_vr_idxI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_idxI)(z, ptr, ofst2)
#define store8x2_vr_postR(z, ptr, ofst) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postR)(z, (unsigned int **)&(ptr), ofst)
#define store8x2_vr_postI(z, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_postI)(z, (unsigned int **)&(ptr), ofst2)
#define store8x2_vr_circI(z, ptr, ofst1, c) \
	CSTUB_(_TIE_hemilite_common_tie_store8x2_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c)
#define store8x1_vr_idxR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxR)(z, ptr, ofst, sel1)
#define store8x1_vr_idxI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_idxI)(z, ptr, ofst2, sel1)
#define store8x1_vr_postR(z, ptr, ofst, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postR)(z, (unsigned int **)&(ptr), ofst, sel1)
#define store8x1_vr_postI(z, ptr, ofst2, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_postI)(z, (unsigned int **)&(ptr), ofst2, sel1)
#define store8x1_vr_circI(z, ptr, ofst1, c, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_store8x1_vr_circI)(z, (unsigned int **)&(ptr), ofst1, c, sel1)
#define align_32x2_store(ptr) \
	CSTUB_(_TIE_hemilite_common_tie_align_32x2_store)(ptr)
#define store_32x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a)(z, &buf, (unsigned int **)&(ptr))
#define store_24x2_vr_a(z, buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_store_24x2_vr_a)(z, &buf, (unsigned int **)&(ptr))
#define store_32x2_vr_a_circ(z, buf, ptr, c) \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_circ)(z, &buf, (unsigned int **)&(ptr), c)
#define flush_32x2(buf, ptr) \
	CSTUB_(_TIE_hemilite_common_tie_flush_32x2)(buf, ptr)
#define load_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_fr_postI)(&fx, (const unsigned int **)&(ptr), ofst2)
#define store_fr_postI(fx, ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_fr_postI)(fx, (unsigned int **)&(ptr), ofst2)
#define brev_upd(gate, idx_out, idx_in) \
	CSTUB_(_TIE_hemilite_common_tie_brev_upd)(&gate, &idx_out, idx_in)
#define brev_upd_ext(gate, idx_out) \
	CSTUB_(_TIE_hemilite_common_tie_brev_upd_ext)(&gate, &idx_out)
#define move32_ar_vr(x, sel1) \
	CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr)(x, sel1)
#define move32_vr_ar(z, sel1, a) \
	CSTUB_(_TIE_hemilite_common_tie_move32_vr_ar)(&z, sel1, a)
#define move32_ar_vr_idx(x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_move32_ar_vr_idx)(x, idx)
#define move32_fr_vr_idx(x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_move32_fr_vr_idx)(x, idx)
#define move_fr_eqz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_eqz)(&z, x, y)
#define move_fr_gez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_gez)(&z, x, y)
#define move_fr_gtz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_gtz)(&z, x, y)
#define move_fr_lez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_lez)(&z, x, y)
#define move_fr_ltz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_ltz)(&z, x, y)
#define move_fr_nez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_nez)(&z, x, y)
#define move_fr_sat(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_sat)(&z, x, y)
#define move_fr_arnz(z, x, ax) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_arnz)(&z, x, ax)
#define vmove_vr_eqz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_eqz)(&z, x, y)
#define vmove_vr_gez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gez)(&z, x, y)
#define vmove_vr_gtz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_gtz)(&z, x, y)
#define vmove_vr_lez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_lez)(&z, x, y)
#define vmove_vr_ltz(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_ltz)(&z, x, y)
#define vmove_vr_nez(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_nez)(&z, x, y)
#define vmove_vr_sat(z, x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmove_vr_sat)(&z, x, y)
#define replicate(z, sel_code, x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_replicate)(&z, sel_code, x, el_x)
#define replicate_ar(z, sel_code, ar) \
	CSTUB_(_TIE_hemilite_common_tie_replicate_ar)(&z, sel_code, ar)
#define vreplicate(x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_vreplicate)(x, el_x)
#define vreplicate_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_vreplicate_fr)(fx)
#define convert_16I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x1)(&z, exp_fxp, el)
#define convert_16I_to_32F_x2(z, exp_fxp) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16I_to_32F_x2)(&z, exp_fxp)
#define convert_32F_to_16I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x1)(&z, exp_fxp, rnd, el)
#define convert_32F_to_16I_x2(z, exp_fxp, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16I_x2)(&z, exp_fxp, rnd)
#define convert_32F_to_16F_x1(z, is_signed, exp_bits, bias, round, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x1)(&z, is_signed, exp_bits, bias, round, el)
#define convert_32F_to_16F_x2(z, is_signed, exp_bits, bias, round) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_16F_x2)(&z, is_signed, exp_bits, bias, round)
#define convert_16F_to_32F_x1(z, is_signed, exp_bits, bias, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x1)(&z, is_signed, exp_bits, bias, el)
#define convert_16F_to_32F_x2(z, is_signed, exp_bits, bias) \
	CSTUB_(_TIE_hemilite_common_tie_convert_16F_to_32F_x2)(&z, is_signed, exp_bits, bias)
#define convert_32I_to_32F_x1(z, exp_fxp, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_32F_x1)(&z, exp_fxp, el)
#define convert_32F_to_32I_x1(z, exp_fxp, rnd, el) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_32I_x1)(&z, exp_fxp, rnd, el)
#define convert_IEEE_float_to_32F_x2(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_float_to_32F_x2)(&z)
#define convert_32F_to_IEEE_float_x2(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_IEEE_float_x2)(&z)
#define convert_32I_to_64F(x) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32I_to_64F)(x)
#define convert_64F_to_32I(x, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32I)(x, rnd)
#define convert_32F_to_64F(fx) \
	CSTUB_(_TIE_hemilite_common_tie_convert_32F_to_64F)(fx)
#define convert_64F_to_32F(x) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_32F)(x)
#define convert_IEEE_double_to_64F(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_IEEE_double_to_64F)(&z)
#define convert_64F_to_IEEE_double(z) \
	CSTUB_(_TIE_hemilite_common_tie_convert_64F_to_IEEE_double)(&z)
#define vadd_perm(x, y, selin_h, selin_l, signs4, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vadd_perm)(x, y, selin_h, selin_l, signs4, div_by_2_op)
#define vsum_perm(z, x, y, selin_h, selin_l, signs4, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vsum_perm)(z, x, y, selin_h, selin_l, signs4, sign_z)
#define vmul_perm(x, y, selin_h, selin_l, signs2, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vmul_perm)(x, y, selin_h, selin_l, signs2, div_by_2_op)
#define vmac_perm(z, x, y, selin_h, selin_l, signs2, sign_z, swap_z, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vmac_perm)(z, x, y, selin_h, selin_l, signs2, sign_z, swap_z, div_by_2_op)
#define vmac_boost(z, x, y, selin_h, selin_l, signs2, boost) \
	CSTUB_(_TIE_hemilite_common_tie_vmac_boost)(z, x, y, selin_h, selin_l, signs2, boost)
#define vblend(x, y, selin_h, selin_l, signs4, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vblend)(x, y, selin_h, selin_l, signs4, div_by_2_op)
#define vblend_add(z, x, y, selin_h, selin_l, signs4, sign_z, swap_z, div_by_2_op) \
	CSTUB_(_TIE_hemilite_common_tie_vblend_add)(z, x, y, selin_h, selin_l, signs4, sign_z, swap_z, div_by_2_op)
#define vblend_boost(z, x, y, selin_h, selin_l, signs4, boost) \
	CSTUB_(_TIE_hemilite_common_tie_vblend_boost)(z, x, y, selin_h, selin_l, signs4, boost)
#define fadds(fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fadds)(fx, fy, signs2)
#define fmuls(fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fmuls)(fx, fy, signs2)
#define fmacs(fz, fx, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_fmacs)(fz, fx, fy, signs2)
#define dadds(z, x, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dadds)(z, x, signs2)
#define dmuls(x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dmuls)(x, y, signs2)
#define dmacs(z, x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_dmacs)(z, x, y, signs2)
#define vadds(x, y, signs4) \
	CSTUB_(_TIE_hemilite_common_tie_vadds)(x, y, signs4)
#define vmuls(x, y, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_vmuls)(x, y, signs2)
#define vmacs(z, x, y, signs2, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vmacs)(z, x, y, signs2, sign_z)
#define cmul(x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmul)(x, y, conj)
#define cmac(z, x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmac)(z, x, y, conj)
#define cmas(z, x, y, conj) \
	CSTUB_(_TIE_hemilite_common_tie_cmas)(z, x, y, conj)
#define vmulf(x, fy, signs2) \
	CSTUB_(_TIE_hemilite_common_tie_vmulf)(x, fy, signs2)
#define vmacf(z, x, fy, signs2, sign_z) \
	CSTUB_(_TIE_hemilite_common_tie_vmacf)(z, x, fy, signs2, sign_z)
#define vabs(x) \
	CSTUB_(_TIE_hemilite_common_tie_vabs)(x)
#define vexp_adj(x, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_vexp_adj)(x, exp_adj_ar)
#define vexp_adji(x, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_vexp_adji)(x, exp_adj_imm)
#define vpermi(x, y, sel4) \
	CSTUB_(_TIE_hemilite_common_tie_vpermi)(x, y, sel4)
#define seta_vr(z, sel_code, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_vr)(&z, sel_code, const_idx, exp_adj_const)
#define vseta_vr(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vseta_vr)(const_idx, exp_adj_const)
#define seta_ar(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_ar)(const_idx, exp_adj_const)
#define seta_fr(const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_seta_fr)(const_idx, exp_adj_const)
#define load_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_AccExtend_postI)((const unsigned int **)&(ptr), ofst2)
#define load32x1_vr_idx16vr(z, ptr, vidx16, ptr_sel) \
	CSTUB_(_TIE_hemilite_common_tie_load32x1_vr_idx16vr)(&z, ptr, vidx16, ptr_sel)
#define load_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB0_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB1_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB2_postI)((const unsigned int **)&(ptr), ofst2)
#define load_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_BB3_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB1_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB2_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB3_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB4_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB5_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB6_postI)((const unsigned int **)&(ptr), ofst2)
#define load_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_load_VB7_postI)((const unsigned int **)&(ptr), ofst2)
#define load_32x2_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_hemilite_common_tie_load_32x2_vr_a_bounded)(&z, &buf, (const unsigned int **)&(ptr), &count)
#define load_BBx_VB67_a_bounded(buf, ptr, count, sel) \
	CSTUB_(_TIE_hemilite_common_tie_load_BBx_VB67_a_bounded)(&buf, (const unsigned int **)&(ptr), &count, sel)
#define flush_32x2_bounded(buf, ptr, count) \
	CSTUB_(_TIE_hemilite_common_tie_flush_32x2_bounded)(buf, (unsigned int **)&(ptr), &count)
#define store_32x2_vr_a_bounded(z, buf, ptr, count) \
	CSTUB_(_TIE_hemilite_common_tie_store_32x2_vr_a_bounded)(z, &buf, (unsigned int **)&(ptr), &count)
#define store_AccExtend_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_AccExtend_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB0_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB0_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB1_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB2_postI)((unsigned int **)&(ptr), ofst2)
#define store_BB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_BB3_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB1_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB1_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB2_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB2_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB3_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB3_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB4_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB4_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB5_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB5_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB6_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB6_postI)((unsigned int **)&(ptr), ofst2)
#define store_VB7_postI(ptr, ofst2) \
	CSTUB_(_TIE_hemilite_common_tie_store_VB7_postI)((unsigned int **)&(ptr), ofst2)
#define afloat_exp_extract(x) \
	CSTUB_(_TIE_hemilite_common_tie_afloat_exp_extract)(x)
#define mov_AccExtend_vr(x) \
	CSTUB_(_TIE_hemilite_common_tie_mov_AccExtend_vr)(x)
#define mov_vr_AccExtend() \
	CSTUB_(_TIE_hemilite_common_tie_mov_vr_AccExtend)()
#define mov_BB_VB67_to_vrVB_VB45() \
	CSTUB_(_TIE_hemilite_common_tie_mov_BB_VB67_to_vrVB_VB45)()
#define mov_vrVB_VB45_to_BB_VB67(x) \
	CSTUB_(_TIE_hemilite_common_tie_mov_vrVB_VB45_to_BB_VB67)(x)
#define precess_16bits(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_precess_16bits)(x, y)
#define set_BB_vrVB67_zero() \
	CSTUB_(_TIE_hemilite_common_tie_set_BB_vrVB67_zero)()
#define exp_shift_amount(input1, input2) \
	CSTUB_(_TIE_hemilite_common_tie_exp_shift_amount)(input1, input2)
#define rnd_sat_pack(z, el32, x, y, sgn) \
	CSTUB_(_TIE_hemilite_common_tie_rnd_sat_pack)(&z, el32, x, y, sgn)
#define rectify32_into8(z, x, shift, rnd, el32, half) \
	CSTUB_(_TIE_hemilite_common_tie_rectify32_into8)(&z, x, shift, rnd, el32, half)
#define shift8_into32_arith(x, shift, rnd, el32, half) \
	CSTUB_(_TIE_hemilite_common_tie_shift8_into32_arith)(x, shift, rnd, el32, half)
#define shift32_arith(x, shift, rnd) \
	CSTUB_(_TIE_hemilite_common_tie_shift32_arith)(x, shift, rnd)
#define mac8bx8b(z, x, y, signed) \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b)(&z, x, y, signed)
#define mac8bx8b_sparse(z, x, y, signed) \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_sparse)(&z, x, y, signed)
#define mac8bx8b_conv(z, x, signed, shift_in) \
	CSTUB_(_TIE_hemilite_common_tie_mac8bx8b_conv)(&z, x, signed, shift_in)
#define mir_init(low) \
	CSTUB_(_TIE_hemilite_common_tie_mir_init)(low)
#define f_abs(z, el_z, x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_f_abs)(&z, el_z, x, el_x)
#define fclamp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fclamp)(&z, el_z, x, el_x, y, el_y)
#define fclamp_bp(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fclamp_bp)(&z, el_z, x, el_x, y, el_y)
#define fclamp_one(z, el_z, x, el_x) \
	CSTUB_(_TIE_hemilite_common_tie_fclamp_one)(&z, el_z, x, el_x)
#define fmax(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fmax)(&z, el_z, x, el_x, y, el_y)
#define fmin(z, el_z, x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_fmin)(&z, el_z, x, el_x, y, el_y)
#define max_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_max_fr)(fx, fy)
#define min_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_min_fr)(fx, fy)
#define log2(x) \
	CSTUB_(_TIE_hemilite_common_tie_log2)(x)
#define pow2(x) \
	CSTUB_(_TIE_hemilite_common_tie_pow2)(x)
#define sigmoid(x) \
	CSTUB_(_TIE_hemilite_common_tie_sigmoid)(x)
#define inv(x) \
	CSTUB_(_TIE_hemilite_common_tie_inv)(x)
#define ratio(z, x, y, bz) \
	CSTUB_(_TIE_hemilite_common_tie_ratio)(&z, x, y, &bz)
#define atanratio(x, bx) \
	CSTUB_(_TIE_hemilite_common_tie_atanratio)(x, bx)
#define invsqrt(x) \
	CSTUB_(_TIE_hemilite_common_tie_invsqrt)(x)
#define sine(x) \
	CSTUB_(_TIE_hemilite_common_tie_sine)(x)
#define cosine(x) \
	CSTUB_(_TIE_hemilite_common_tie_cosine)(x)
#define log2mul(z, x, y, bz) \
	CSTUB_(_TIE_hemilite_common_tie_log2mul)(&z, x, y, &bz)
#define cspow2(x, bx) \
	CSTUB_(_TIE_hemilite_common_tie_cspow2)(x, bx)
#define comp(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_comp)(x, el_x, y, el_y)
#define eq(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_eq)(x, el_x, y, el_y)
#define ge(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_ge)(x, el_x, y, el_y)
#define gt(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_gt)(x, el_x, y, el_y)
#define le(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_le)(x, el_x, y, el_y)
#define lt(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_lt)(x, el_x, y, el_y)
#define ne(x, el_x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_ne)(x, el_x, y, el_y)
#define comp_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_comp_const)(x, el_x, const_idx, exp_adj_const)
#define eq_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_eq_const)(x, el_x, const_idx, exp_adj_const)
#define ge_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_ge_const)(x, el_x, const_idx, exp_adj_const)
#define gt_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_gt_const)(x, el_x, const_idx, exp_adj_const)
#define le_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_le_const)(x, el_x, const_idx, exp_adj_const)
#define lt_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_lt_const)(x, el_x, const_idx, exp_adj_const)
#define ne_const(x, el_x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_ne_const)(x, el_x, const_idx, exp_adj_const)
#define comp_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_comp_fr)(fx, fy)
#define eq_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_eq_fr)(fx, fy)
#define ge_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_ge_fr)(fx, fy)
#define gt_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_gt_fr)(fx, fy)
#define le_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_le_fr)(fx, fy)
#define lt_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_lt_fr)(fx, fy)
#define ne_fr(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_ne_fr)(fx, fy)
#define neg_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_neg_fr)(fx)
#define abs_fr(fx) \
	CSTUB_(_TIE_hemilite_common_tie_abs_fr)(fx)
#define deqz(x) \
	CSTUB_(_TIE_hemilite_common_tie_deqz)(x)
#define dgez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dgez)(x)
#define dgtz(x) \
	CSTUB_(_TIE_hemilite_common_tie_dgtz)(x)
#define dlez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dlez)(x)
#define dltz(x) \
	CSTUB_(_TIE_hemilite_common_tie_dltz)(x)
#define dnez(x) \
	CSTUB_(_TIE_hemilite_common_tie_dnez)(x)
#define veq(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_veq)(x, y)
#define vge(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vge)(x, y)
#define vgt(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vgt)(x, y)
#define vle(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vle)(x, y)
#define vlt(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vlt)(x, y)
#define vne(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vne)(x, y)
#define veq_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_veq_const)(x, const_idx, exp_adj_const)
#define vge_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vge_const)(x, const_idx, exp_adj_const)
#define vgt_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vgt_const)(x, const_idx, exp_adj_const)
#define vle_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vle_const)(x, const_idx, exp_adj_const)
#define vlt_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vlt_const)(x, const_idx, exp_adj_const)
#define vne_const(x, const_idx, exp_adj_const) \
	CSTUB_(_TIE_hemilite_common_tie_vne_const)(x, const_idx, exp_adj_const)
#define sel_1b2(fx, fy, bx, el_bx1) \
	CSTUB_(_TIE_hemilite_common_tie_sel_1b2)(fx, fy, bx, el_bx1)
#define sel_eq(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_eq)(fx, fy, bx)
#define sel_ge(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ge)(fx, fy, bx)
#define sel_gt(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_gt)(fx, fy, bx)
#define sel_le(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_le)(fx, fy, bx)
#define sel_lt(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_lt)(fx, fy, bx)
#define sel_ne(fx, fy, bx) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ne)(fx, fy, bx)
#define sel_ar(fx, fy, sel) \
	CSTUB_(_TIE_hemilite_common_tie_sel_ar)(fx, fy, sel)
#define vsel(x, y, bx) \
	CSTUB_(_TIE_hemilite_common_tie_vsel)(x, y, bx)
#define vsel_ar(x, y, sel) \
	CSTUB_(_TIE_hemilite_common_tie_vsel_ar)(x, y, sel)
#define andb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_andb2)(bx, by)
#define andbc2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_andbc2)(bx, by)
#define orb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_orb2)(bx, by)
#define orbc2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_orbc2)(bx, by)
#define xorb2(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_xorb2)(bx, by)
#define bcount0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bcount0_maskI)(bx, imask)
#define bcount0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bcount0_maskR)(bx, by)
#define bcount1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bcount1_maskI)(bx, imask)
#define bcount1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bcount1_maskR)(bx, by)
#define bfirst0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskI)(bx, imask)
#define bfirst0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst0_maskR)(bx, by)
#define bfirst1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskI)(bx, imask)
#define bfirst1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_bfirst1_maskR)(bx, by)
#define blast0_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_blast0_maskI)(bx, imask)
#define blast0_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_blast0_maskR)(bx, by)
#define blast1_maskI(bx, imask) \
	CSTUB_(_TIE_hemilite_common_tie_blast1_maskI)(bx, imask)
#define blast1_maskR(bx, by) \
	CSTUB_(_TIE_hemilite_common_tie_blast1_maskR)(bx, by)
#define bgetI(bx, ipos) \
	CSTUB_(_TIE_hemilite_common_tie_bgetI)(bx, ipos)
#define bgetR(bx, rpos) \
	CSTUB_(_TIE_hemilite_common_tie_bgetR)(bx, rpos)
#define bsetI(bx, rpos, ibit) \
	CSTUB_(_TIE_hemilite_common_tie_bsetI)(bx, rpos, ibit)
#define bsetR(bx, rpos, by) \
	CSTUB_(_TIE_hemilite_common_tie_bsetR)(bx, rpos, by)
#define exp_adj(z, el_z, x, el_x, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adj)(&z, el_z, x, el_x, exp_adj_ar)
#define exp_adji(z, el_z, x, el_x, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adji)(&z, el_z, x, el_x, exp_adj_imm)
#define exp_adj_fr(fx, exp_adj_ar) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adj_fr)(fx, exp_adj_ar)
#define exp_adji_fr(fx, exp_adj_imm) \
	CSTUB_(_TIE_hemilite_common_tie_exp_adji_fr)(fx, exp_adj_imm)
#define s_neg(fx) \
	CSTUB_(_TIE_hemilite_common_tie_s_neg)(fx)
#define s_copy(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_copy)(fx, fy)
#define s_and(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_and)(fx, fy)
#define s_andc(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_andc)(fx, fy)
#define s_or(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_or)(fx, fy)
#define s_orc(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_orc)(fx, fy)
#define s_xor(fx, fy) \
	CSTUB_(_TIE_hemilite_common_tie_s_xor)(fx, fy)
#define s_vneg(x) \
	CSTUB_(_TIE_hemilite_common_tie_s_vneg)(x)
#define s_vcopy(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vcopy)(x, y)
#define s_vand(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vand)(x, y)
#define s_vandc(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vandc)(x, y)
#define s_vor(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vor)(x, y)
#define s_vorc(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vorc)(x, y)
#define s_vxor(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_s_vxor)(x, y)
#define floorp_frac(floor, z, el_z, x, el_x, nbits) \
	CSTUB_(_TIE_hemilite_common_tie_floorp_frac)(&floor, &z, el_z, x, el_x, nbits)
#define idx_frac(floor, z, el_z, input, nbits) \
	CSTUB_(_TIE_hemilite_common_tie_idx_frac)(&floor, &z, el_z, input, nbits)
#define rmax_idx(a, fz, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_rmax_idx)(&a, &fz, x, idx)
#define rmin_idx(a, fz, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_rmin_idx)(&a, &fz, x, idx)
#define vmaxmin_init(z, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_vmaxmin_init)(&z, x, &idx)
#define vmax_idx(z, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_vmax_idx)(&z, x, &idx)
#define vmin_idx(z, x, idx) \
	CSTUB_(_TIE_hemilite_common_tie_vmin_idx)(&z, x, &idx)
#define vmax(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmax)(x, y)
#define vmin(x, y) \
	CSTUB_(_TIE_hemilite_common_tie_vmin)(x, y)
#define sortupd_asc_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_vr)(&a, &z, x, y, el_y)
#define sortupd_des_vr(a, z, x, y, el_y) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_des_vr)(&a, &z, x, y, el_y)
#define sortupd_asc_ar(a, z, x) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_asc_ar)(&a, &z, x)
#define sortupd_des_ar(a, z, x) \
	CSTUB_(_TIE_hemilite_common_tie_sortupd_des_ar)(&a, &z, x)
#define vbool(x, y, op) \
	CSTUB_(_TIE_hemilite_common_tie_vbool)(x, y, op)
#define align_up(val, option) \
	CSTUB_(_TIE_hemilite_common_tie_align_up)(val, option)
#define mv_MIR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_MIR)(b)
#define mv_ULSR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_ULSR)(b)
#define mv_CR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_CR)(b)
#define ld_FR(addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR)(addr, fimm)
#define st_FR(fregin, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR)(fregin, addr, fimm)
#define ld_FR_idxR(addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_idxR)(addr, x)
#define st_FR_idxR(fregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_idxR)(fregin, addr, x)
#define ld_FR_postI(fregout, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_postI)(&fregout, (const fr32 **)&(addr), fimm)
#define st_FR_postI(fregin, addr, fimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_postI)(fregin, (fr32 **)&(addr), fimm)
#define ld_FR_postR(fregout, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_FR_postR)(&fregout, (const fr32 **)&(addr), x)
#define st_FR_postR(fregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_FR_postR)(fregin, (fr32 **)&(addr), x)
#define ld_VR(addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR)(addr, vimm)
#define st_VR(vregin, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR)(vregin, addr, vimm)
#define ld_VR_idxR(addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_idxR)(addr, x)
#define st_VR_idxR(vregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_idxR)(vregin, addr, x)
#define ld_VR_postI(vregout, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_postI)(&vregout, (const vr64 **)&(addr), vimm)
#define st_VR_postI(vregin, addr, vimm) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_postI)(vregin, (vr64 **)&(addr), vimm)
#define ld_VR_postR(vregout, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_ld_VR_postR)(&vregout, (const vr64 **)&(addr), x)
#define st_VR_postR(vregin, addr, x) \
	CSTUB_(_TIE_hemilite_common_tie_st_VR_postR)(vregin, (vr64 **)&(addr), x)
#define mv_FR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_FR)(b)
#define move_ar_fr(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_ar_fr)(b)
#define move_fr_ar(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_fr_ar)(b)
#define mv_VR(b) \
	CSTUB_(_TIE_hemilite_common_tie_mv_VR)(b)
#define move_ar_bbr(b) \
	CSTUB_(_TIE_hemilite_common_tie_move_ar_bbr)(b)
#define move_bbr_ar(a) \
	CSTUB_(_TIE_hemilite_common_tie_move_bbr_ar)(a)
#define shift_from_bbr(a, x) \
	CSTUB_(_TIE_hemilite_common_tie_shift_from_bbr)(&a, x)
#define shift_to_bbr(a, z) \
	CSTUB_(_TIE_hemilite_common_tie_shift_to_bbr)(&a, &z)
#define XT_RSR_PRID() \
	CSTUB_(_TIE_xt_core_RSR_PRID)()

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

#define RBB0_0 RUR_BB0_0
#define WBB0_0 WUR_BB0_0
#define RUR3 RUR_BB0_0
#define WUR3 WUR_BB0_0

#define RBB0_1 RUR_BB0_1
#define WBB0_1 WUR_BB0_1
#define RUR4 RUR_BB0_1
#define WUR4 WUR_BB0_1

#define RBB1_0 RUR_BB1_0
#define WBB1_0 WUR_BB1_0
#define RUR5 RUR_BB1_0
#define WUR5 WUR_BB1_0

#define RBB1_1 RUR_BB1_1
#define WBB1_1 WUR_BB1_1
#define RUR6 RUR_BB1_1
#define WUR6 WUR_BB1_1

#define RBB2_0 RUR_BB2_0
#define WBB2_0 WUR_BB2_0
#define RUR7 RUR_BB2_0
#define WUR7 WUR_BB2_0

#define RBB2_1 RUR_BB2_1
#define WBB2_1 WUR_BB2_1
#define RUR8 RUR_BB2_1
#define WUR8 WUR_BB2_1

#define RBB3_0 RUR_BB3_0
#define WBB3_0 WUR_BB3_0
#define RUR9 RUR_BB3_0
#define WUR9 WUR_BB3_0

#define RBB3_1 RUR_BB3_1
#define WBB3_1 WUR_BB3_1
#define RUR10 RUR_BB3_1
#define WUR10 WUR_BB3_1

#define RMvmAux RUR_MvmAux
#define WMvmAux WUR_MvmAux
#define RUR11 RUR_MvmAux
#define WUR11 WUR_MvmAux

#define RVB1_0 RUR_VB1_0
#define WVB1_0 WUR_VB1_0
#define RUR12 RUR_VB1_0
#define WUR12 WUR_VB1_0

#define RVB1_1 RUR_VB1_1
#define WVB1_1 WUR_VB1_1
#define RUR13 RUR_VB1_1
#define WUR13 WUR_VB1_1

#define RVB2_0 RUR_VB2_0
#define WVB2_0 WUR_VB2_0
#define RUR14 RUR_VB2_0
#define WUR14 WUR_VB2_0

#define RVB2_1 RUR_VB2_1
#define WVB2_1 WUR_VB2_1
#define RUR15 RUR_VB2_1
#define WUR15 WUR_VB2_1

#define RVB3_0 RUR_VB3_0
#define WVB3_0 WUR_VB3_0
#define RUR16 RUR_VB3_0
#define WUR16 WUR_VB3_0

#define RVB3_1 RUR_VB3_1
#define WVB3_1 WUR_VB3_1
#define RUR17 RUR_VB3_1
#define WUR17 WUR_VB3_1

#define RVB4_0 RUR_VB4_0
#define WVB4_0 WUR_VB4_0
#define RUR18 RUR_VB4_0
#define WUR18 WUR_VB4_0

#define RVB4_1 RUR_VB4_1
#define WVB4_1 WUR_VB4_1
#define RUR19 RUR_VB4_1
#define WUR19 WUR_VB4_1

#define RVB5_0 RUR_VB5_0
#define WVB5_0 WUR_VB5_0
#define RUR20 RUR_VB5_0
#define WUR20 WUR_VB5_0

#define RVB5_1 RUR_VB5_1
#define WVB5_1 WUR_VB5_1
#define RUR21 RUR_VB5_1
#define WUR21 WUR_VB5_1

#define RVB6_0 RUR_VB6_0
#define WVB6_0 WUR_VB6_0
#define RUR22 RUR_VB6_0
#define WUR22 WUR_VB6_0

#define RVB6_1 RUR_VB6_1
#define WVB6_1 WUR_VB6_1
#define RUR23 RUR_VB6_1
#define WUR23 WUR_VB6_1

#define RVB7_0 RUR_VB7_0
#define WVB7_0 WUR_VB7_0
#define RUR24 RUR_VB7_0
#define WUR24 WUR_VB7_0

#define RVB7_1 RUR_VB7_1
#define WVB7_1 WUR_VB7_1
#define RUR25 RUR_VB7_1
#define WUR25 WUR_VB7_1

#ifndef RUR
#define RUR(NUM) RUR##NUM()
#endif /* RUR */

#ifndef WUR
#define WUR(VAL, NUM) WUR##NUM(VAL)
#endif /* WUR */

/* Registration functions for external interfaces */
#define cstub_register_EXPSTATE(s, c) \
	CSTUB_(register_EXPSTATE)(s, c)
CSTUB_EXTERN void CSTUB_(register_EXPSTATE)(void *user_object, cstub_ExportState_func_t callback);

#define cstub_register_ERI_RD(l, c) \
	CSTUB_(register_ERI_RD)(l, c)
CSTUB_EXTERN void CSTUB_(register_ERI_RD)(void *user_object, cstub_Lookup_func_t callback);

#define cstub_register_ERI_WR(l, c) \
	CSTUB_(register_ERI_WR)(l, c)
CSTUB_EXTERN void CSTUB_(register_ERI_WR)(void *user_object, cstub_Lookup_func_t callback);

#define cstub_register_IPQ(q, e, d) \
	CSTUB_(register_IPQ)(q, e, d)
CSTUB_EXTERN void CSTUB_(register_IPQ)(void *user_object, cstub_InputQueue_Empty_func_t empty_callback, cstub_InputQueue_Data_func_t data_callback);

#define cstub_register_OPQ(q, e, d) \
	CSTUB_(register_OPQ)(q, e, d)
CSTUB_EXTERN void CSTUB_(register_OPQ)(void *user_object, cstub_OutputQueue_Full_func_t full_callback, cstub_OutputQueue_Data_func_t data_callback);

#define cstub_register_IMPWIRE(w, c) \
	CSTUB_(register_IMPWIRE)(w, c)
CSTUB_EXTERN void CSTUB_(register_IMPWIRE)(void *user_object, cstub_ImportWire_func_t callback);


#endif /* !CSTUB_Xm_hemilite_shapiro_RI04_HEADER */
