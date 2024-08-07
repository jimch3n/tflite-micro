// Customer ID=14540; Build=0x7f357; Copyright (c) 2017 Cadence Design Systems, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/* Definitions for the dmx1a_common_tie TIE package */

/* Do not modify. This is automatically generated.*/

#ifndef _XTENSA_dmx1a_common_tie_HEADER
#define _XTENSA_dmx1a_common_tie_HEADER

#ifdef __XTENSA__
#ifdef __XCC__

#ifndef _ASMLANGUAGE
#ifndef _NOCLANGUAGE
#ifndef __ASSEMBLER__

#include <xtensa/tie/xt_core.h>
#include <xtensa/tie/xt_booleans.h>
typedef _TIE_dmx1a_common_tie_fr32 fr32;
typedef _TIE_dmx1a_common_tie_vr64 vr64;
typedef _TIE_dmx1a_common_tie_vr128 vr128;
typedef _TIE_dmx1a_common_tie_wr64 wr64;
typedef _TIE_dmx1a_common_tie_cr64 cr64;
typedef _TIE_dmx1a_common_tie_mir30 mir30;
typedef _TIE_dmx1a_common_tie_ulsr128 ulsr128;
typedef _TIE_dmx1a_common_tie_perm16 perm16;

/*
 * The following prototypes describe intrinsic functions
 * corresponding to TIE instructions.  Some TIE instructions
 * may produce multiple results (designated as "out" operands
 * in the iclass section) or may have operands used as both
 * inputs and outputs (designated as "inout").  However, the C
 * and C++ languages do not provide syntax that can express
 * the in/out/inout constraints of TIE intrinsics.
 * Nevertheless, the compiler understands these constraints
 * and will check that the intrinsic functions are used
 * correctly.  To improve the readability of these prototypes,
 * the "out" and "inout" parameters are marked accordingly
 * with comments.
 */

extern void _TIE_dmx1a_common_tie_st_PERM(perm16 a, perm16 * b, immediate c);
extern perm16 _TIE_dmx1a_common_tie_ld_PERM(const perm16 * b, immediate c);
extern void _TIE_dmx1a_common_tie_st_ULSR(ulsr128 a, ulsr128 * b, immediate c);
extern ulsr128 _TIE_dmx1a_common_tie_ld_ULSR(const ulsr128 * b, immediate c);
extern void _TIE_dmx1a_common_tie_st_MIR(mir30 a, mir30 * b, immediate c);
extern mir30 _TIE_dmx1a_common_tie_ld_MIR(const mir30 * b, immediate c);
extern void _TIE_dmx1a_common_tie_st_CR(cr64 a, cr64 * b, immediate c);
extern cr64 _TIE_dmx1a_common_tie_ld_CR(const cr64 * b, immediate c);
extern void _TIE_dmx1a_common_tie_st_WR(wr64 a, wr64 * b, immediate c);
extern wr64 _TIE_dmx1a_common_tie_ld_WR(const wr64 * b, immediate c);
extern vr128 _TIE_dmx1a_common_tie_load32x4_vr_idxR(const unsigned * ptr, unsigned ofst);
extern vr128 _TIE_dmx1a_common_tie_load32x4_vr_idxI(const unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load32x4_vr_postR(vr128 z /*out*/, const unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_load32x4_vr_postI(vr128 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load32x4_vr_circI(vr128 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_dmx1a_common_tie_load32x2_vr_idxR(vr128 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_load32x2_vr_idxI(vr128 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_load32x2_vr_postR(vr128 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_load32x2_vr_postI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_load32x2_vr_circI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_dmx1a_common_tie_load32x1_vr_idxR(vr128 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_load32x1_vr_idxI(vr128 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_load32x1_vr_postR(vr128 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_load32x1_vr_postI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_load32x1_vr_circI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel2);
extern vr128 _TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr(vr128 z, const unsigned * ptr, unsigned ofst, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr(vr128 z, const unsigned * ptr, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, unsigned ofst, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr(vr128 z, const unsigned * ptr, unsigned ofst, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr(vr128 z, const unsigned * ptr, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, unsigned ofst, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr(vr128 z, const unsigned * ptr, unsigned ofst, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr(vr128 z, const unsigned * ptr, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, unsigned ofst, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr(vr128 r /*out*/, vr128 z, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, perm16 perm);
extern perm16 _TIE_dmx1a_common_tie_set_perm16(immediate perm);
extern void _TIE_dmx1a_common_tie_set_perm16_cond(perm16 z /*inout*/, immediate perm, xtbool bx);
extern vr128 _TIE_dmx1a_common_tie_load16x4_vr_idxR(const unsigned * ptr, unsigned ofst);
extern vr128 _TIE_dmx1a_common_tie_load16x4_vr_idxI(const unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load16x4_vr_postR(vr128 z /*out*/, const unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_load16x4_vr_postI(vr128 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load16x4_vr_circI(vr128 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_dmx1a_common_tie_load16x2_vr_idxR(vr128 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_load16x2_vr_idxI(vr128 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_load16x2_vr_postR(vr128 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_load16x2_vr_postI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_load16x2_vr_circI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_dmx1a_common_tie_load16x1_vr_idxR(vr128 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_load16x1_vr_idxI(vr128 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_load16x1_vr_postR(vr128 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_load16x1_vr_postI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_load16x1_vr_circI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel2);
extern vr128 _TIE_dmx1a_common_tie_load8x4_vr_idxR(const unsigned * ptr, unsigned ofst);
extern vr128 _TIE_dmx1a_common_tie_load8x4_vr_idxI(const unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load8x4_vr_postR(vr128 z /*out*/, const unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_load8x4_vr_postI(vr128 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load8x4_vr_circI(vr128 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_dmx1a_common_tie_load8x2_vr_idxR(vr128 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_load8x2_vr_idxI(vr128 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_load8x2_vr_postR(vr128 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_load8x2_vr_postI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_load8x2_vr_circI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_dmx1a_common_tie_load8x1_vr_idxR(vr128 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_load8x1_vr_idxI(vr128 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_load8x1_vr_postR(vr128 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_load8x1_vr_postI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_load8x1_vr_circI(vr128 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel2);
extern ulsr128 _TIE_dmx1a_common_tie_align_32x4_load(const unsigned * ptr);
extern ulsr128 _TIE_dmx1a_common_tie_align_24x4_load(const unsigned * ptr);
extern ulsr128 _TIE_dmx1a_common_tie_align_16x4_load(const unsigned * ptr);
extern ulsr128 _TIE_dmx1a_common_tie_align_8x4_load(const unsigned * ptr);
extern void _TIE_dmx1a_common_tie_load_32x4_vr_a(vr128 z /*out*/, ulsr128 buf /*inout*/, const unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_load_24x4_vr_a(vr128 z /*out*/, ulsr128 buf /*inout*/, const unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_load_16x4_vr_a(vr128 z /*out*/, ulsr128 buf /*inout*/, const unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_load_8x4_vr_a(vr128 z /*out*/, ulsr128 buf /*inout*/, const unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_load_32x4_vr_a_circ(vr128 z /*out*/, ulsr128 buf /*inout*/, const unsigned * ptr /*inout*/, cr64 c);
extern wr64 _TIE_dmx1a_common_tie_load32x2_wr_idxR(const unsigned * ptr, unsigned ofst);
extern wr64 _TIE_dmx1a_common_tie_load32x2_wr_idxI(const unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load32x2_wr_postR(wr64 w /*out*/, const unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_load32x2_wr_postI(wr64 w /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store32x4_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store32x4_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store32x4_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store32x4_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store32x4_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_dmx1a_common_tie_store32x2_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x1_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x4_vr_br_idxR(vr128 z, xtbool4 bx4, unsigned * ptr, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store32x4_vr_br_idxI(vr128 z, xtbool4 bx4, unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store32x4_vr_br_postR(vr128 z, xtbool4 bx4, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store32x4_vr_br_postI(vr128 z, xtbool4 bx4, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store32x4_vr_br_circI(vr128 z, xtbool4 bx4, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_dmx1a_common_tie_store32x2_vr_br_idxR(vr128 z, xtbool2 bx2, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_br_idxI(vr128 z, xtbool2 bx2, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_br_postR(vr128 z, xtbool2 bx2, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_br_postI(vr128 z, xtbool2 bx2, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x2_vr_br_circI(vr128 z, xtbool2 bx2, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_dmx1a_common_tie_store32x1_vr_br_idxR(vr128 z, xtbool bx, unsigned * ptr, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_br_idxI(vr128 z, xtbool bx, unsigned * ptr, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_br_postR(vr128 z, xtbool bx, unsigned * ptr /*inout*/, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_br_postI(vr128 z, xtbool bx, unsigned * ptr /*inout*/, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x1_vr_br_circI(vr128 z, xtbool bx, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel2);
extern void _TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm(vr128 z, vr128 y, unsigned * ptr, unsigned ofst, perm16 perm);
extern void _TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm(vr128 z, vr128 y, unsigned * ptr, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm(vr128 z, vr128 y, unsigned * ptr /*inout*/, unsigned ofst, perm16 perm);
extern void _TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm(vr128 z, vr128 y, unsigned * ptr /*inout*/, immediate ofst2, perm16 perm);
extern void _TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm(vr128 z, vr128 y, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, perm16 perm);
extern void _TIE_dmx1a_common_tie_store16x4_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store16x4_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store16x4_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store16x4_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store16x4_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_dmx1a_common_tie_store16x2_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store16x2_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store16x2_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store16x2_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store16x2_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_dmx1a_common_tie_store16x1_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store16x1_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store16x1_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store16x1_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store16x1_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel2);
extern void _TIE_dmx1a_common_tie_store8x4_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store8x4_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store8x4_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store8x4_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store8x4_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_dmx1a_common_tie_store8x2_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store8x2_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store8x2_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_dmx1a_common_tie_store8x2_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_dmx1a_common_tie_store8x2_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_dmx1a_common_tie_store8x1_vr_idxR(vr128 z, unsigned * ptr, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store8x1_vr_idxI(vr128 z, unsigned * ptr, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store8x1_vr_postR(vr128 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel2);
extern void _TIE_dmx1a_common_tie_store8x1_vr_postI(vr128 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel2);
extern void _TIE_dmx1a_common_tie_store8x1_vr_circI(vr128 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel2);
extern ulsr128 _TIE_dmx1a_common_tie_align_32x4_store(const unsigned * ptr);
extern ulsr128 _TIE_dmx1a_common_tie_align_16x4_store(const unsigned * ptr);
extern ulsr128 _TIE_dmx1a_common_tie_align_8x4_store(const unsigned * ptr);
extern void _TIE_dmx1a_common_tie_store_32x4_vr_a(vr128 z, ulsr128 buf /*inout*/, unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_store_24x4_vr_a(vr128 z, ulsr128 buf /*inout*/, unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_store_16x4_vr_a(vr128 z, ulsr128 buf /*inout*/, unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_store_8x4_vr_a(vr128 z, ulsr128 buf /*inout*/, unsigned * ptr /*inout*/);
extern void _TIE_dmx1a_common_tie_store_32x4_vr_a_circ(vr128 z, ulsr128 buf /*inout*/, unsigned * ptr /*inout*/, cr64 c);
extern void _TIE_dmx1a_common_tie_flush_32x4(ulsr128 buf, unsigned * ptr);
extern void _TIE_dmx1a_common_tie_flush_24x4(ulsr128 buf, unsigned * ptr);
extern void _TIE_dmx1a_common_tie_flush_16x4(ulsr128 buf, unsigned * ptr);
extern void _TIE_dmx1a_common_tie_flush_8x4(ulsr128 buf, unsigned * ptr);
extern unsigned _TIE_dmx1a_common_tie_br_get_idx_2_5(unsigned ar32x, xtbool four, immediate odd);
extern unsigned _TIE_dmx1a_common_tie_br_get_idx_6_13(unsigned ar32x, xtbool2 idx_spec, xtbool2 ext_size, immediate odd);
extern unsigned _TIE_dmx1a_common_tie_br_get_idx_next_odd(unsigned ar32x, xtbool4 nbits);
extern unsigned _TIE_dmx1a_common_tie_br_upd_idx_spec(unsigned ar32x);
extern unsigned _TIE_dmx1a_common_tie_build_palindrome(unsigned ar32x, xtbool4 nbits, immediate odd, immediate shift_type);
extern vr128 _TIE_dmx1a_common_tie_load_vr_bdir(const unsigned * ptr, unsigned ofst, xtbool4 br_len, immediate msb);
extern vr128 _TIE_dmx1a_common_tie_load_vr_brev(const unsigned * ptr, unsigned ofst, xtbool4 br_len, immediate msb);
extern void _TIE_dmx1a_common_tie_store_vrl_wr_bdir(vr128 z, wr64 w, unsigned * ptr, unsigned ofst, xtbool4 br_len, immediate msb);
extern void _TIE_dmx1a_common_tie_store_vrh_wr_bdir(vr128 z, wr64 w, unsigned * ptr, unsigned ofst, xtbool4 br_len, immediate msb);
extern void _TIE_dmx1a_common_tie_store_vrl_wr_brev(vr128 z, wr64 w, unsigned * ptr, unsigned ofst, xtbool4 br_len, immediate msb);
extern void _TIE_dmx1a_common_tie_store_vrh_wr_brev(vr128 z, wr64 w, unsigned * ptr, unsigned ofst, xtbool4 br_len, immediate msb);
extern void _TIE_dmx1a_common_tie_store_vrl_vrl_postR(vr128 z, vr128 y, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store_vrh_vrh_postR(vr128 z, vr128 y, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store_vrl_wr_postR(vr128 z, wr64 w, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store_wr_vrl_postR(wr64 w, vr128 y, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store_vrh_wr_postR(vr128 z, wr64 w, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_store_wr_vrh_postR(wr64 w, vr128 y, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_dmx1a_common_tie_load_fr_postI(fr32 fx /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_fr_postI(fr32 fx, unsigned * ptr /*inout*/, immediate ofst2);
extern wr64 _TIE_dmx1a_common_tie_move32_wr_vr(vr128 x, immediate sel2);
extern wr64 _TIE_dmx1a_common_tie_move32_wr_fr(fr32 fx);
extern wr64 _TIE_dmx1a_common_tie_move64_wr_vr(vr128 x, immediate sel1);
extern void _TIE_dmx1a_common_tie_move64_vr_wr(vr128 z /*inout*/, wr64 w, immediate sel1);
extern unsigned _TIE_dmx1a_common_tie_move32_ar_vr(vr128 x, immediate sel2);
extern unsigned _TIE_dmx1a_common_tie_move32_ar_vr_idx(vr128 x, unsigned idx);
extern fr32 _TIE_dmx1a_common_tie_move32_fr_vr_idx(vr128 x, unsigned idx);
extern xtbool _TIE_dmx1a_common_tie_int_to_xt_bool(unsigned ar32x);
extern xtbool2 _TIE_dmx1a_common_tie_int_to_xt_bool2(unsigned ar32x);
extern xtbool4 _TIE_dmx1a_common_tie_int_to_xt_bool4(unsigned ar32x);
extern void _TIE_dmx1a_common_tie_move_vr_eqz(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_move_vr_gez(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_move_vr_gtz(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_move_vr_lez(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_move_vr_ltz(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_move_vr_nez(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_move_vr_sat(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_vmove_vr_eqz(vr128 z /*inout*/, vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_vmove_vr_gez(vr128 z /*inout*/, vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_vmove_vr_gtz(vr128 z /*inout*/, vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_vmove_vr_lez(vr128 z /*inout*/, vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_vmove_vr_ltz(vr128 z /*inout*/, vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_vmove_vr_nez(vr128 z /*inout*/, vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_vmove_vr_sat(vr128 z /*inout*/, vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_replicate(vr128 z /*inout*/, immediate sel_code, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_replicate_ar(vr128 z /*inout*/, immediate sel_code, unsigned ar);
extern vr128 _TIE_dmx1a_common_tie_creplicate_H(vr128 x);
extern vr128 _TIE_dmx1a_common_tie_creplicate_L(vr128 x);
extern vr128 _TIE_dmx1a_common_tie_vreplicate(vr128 x, immediate el_x);
extern vr128 _TIE_dmx1a_common_tie_vreplicate_fr(fr32 fx);
extern vr128 _TIE_dmx1a_common_tie_vreplicate_hr(vr64 hx);
extern vr64 _TIE_dmx1a_common_tie_hreplicate_fr(fr32 fx);
extern void _TIE_dmx1a_common_tie_convert_16I_to_32F_x1(vr128 z /*inout*/, unsigned exp_fxp, immediate el);
extern void _TIE_dmx1a_common_tie_convert_16I_to_32F_x2(vr128 z /*inout*/, unsigned exp_fxp, immediate half);
extern void _TIE_dmx1a_common_tie_convert_16I_to_32F_x4(vr128 z /*inout*/, unsigned exp_fxp);
extern void _TIE_dmx1a_common_tie_convert_32F_to_16I_x1(vr128 z /*inout*/, unsigned exp_fxp, immediate rnd, immediate el);
extern void _TIE_dmx1a_common_tie_convert_32F_to_16I_x2(vr128 z /*inout*/, unsigned exp_fxp, immediate rnd, immediate half);
extern void _TIE_dmx1a_common_tie_convert_32F_to_16I_x4(vr128 z /*inout*/, unsigned exp_fxp, immediate rnd);
extern void _TIE_dmx1a_common_tie_convert_32F_to_16F_x1(vr128 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate round, immediate el);
extern void _TIE_dmx1a_common_tie_convert_32F_to_16F_x2(vr128 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate round, immediate half);
extern void _TIE_dmx1a_common_tie_convert_32F_to_16F_x4(vr128 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate round);
extern void _TIE_dmx1a_common_tie_convert_16F_to_32F_x1(vr128 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate el);
extern void _TIE_dmx1a_common_tie_convert_16F_to_32F_x2(vr128 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate half);
extern void _TIE_dmx1a_common_tie_convert_16F_to_32F_x4(vr128 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias);
extern void _TIE_dmx1a_common_tie_convert_32I_to_32F_x1(vr128 z /*inout*/, unsigned exp_fxp, immediate el);
extern void _TIE_dmx1a_common_tie_convert_32F_to_32I_x1(vr128 z /*inout*/, unsigned exp_fxp, immediate rnd, immediate el);
extern void _TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4(vr128 z /*inout*/);
extern void _TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4(vr128 z /*inout*/);
extern fr32 _TIE_dmx1a_common_tie_convert_IEEE_float_to_32F(unsigned ar);
extern unsigned _TIE_dmx1a_common_tie_convert_32F_to_IEEE_float(fr32 fx);
extern vr64 _TIE_dmx1a_common_tie_convert_32I_to_64F(unsigned x);
extern unsigned _TIE_dmx1a_common_tie_convert_64F_to_32I(vr64 x, immediate rnd);
extern vr64 _TIE_dmx1a_common_tie_convert_32F_to_64F(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_convert_64F_to_32F(vr64 x);
extern void _TIE_dmx1a_common_tie_convert_IEEE_double_to_64F(vr64 z /*inout*/);
extern void _TIE_dmx1a_common_tie_convert_64F_to_IEEE_double(vr64 z /*inout*/);
extern void _TIE_dmx1a_common_tie_affine_adj_L(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, immediate boost);
extern void _TIE_dmx1a_common_tie_affine_adj_H(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, immediate boost);
extern void _TIE_dmx1a_common_tie_affine_perm_L(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, perm16 perm);
extern void _TIE_dmx1a_common_tie_affine_perm_H(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, perm16 perm);
extern void _TIE_dmx1a_common_tie_linear_adj_L(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, immediate boost);
extern void _TIE_dmx1a_common_tie_linear_adj_H(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, immediate boost);
extern void _TIE_dmx1a_common_tie_linear_perm_L(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, perm16 perm);
extern void _TIE_dmx1a_common_tie_linear_perm_H(vr128 z /*inout*/, vr128 x, vr128 y, immediate signs6, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_yl_xl_wr(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_yl_xh_wr(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_yh_xl_wr(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_yh_xh_wr(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_wr_xl_yl(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_wr_xh_yl(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_wr_xl_yh(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr128 _TIE_dmx1a_common_tie_bfly_z_wr_xh_yh(wr64 w, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern void _TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh(vr128 z /*inout*/, wr64 w1 /*out*/, vr128 x, vr128 y, xtbool inv, immediate conjX_swap);
extern vr64 _TIE_dmx1a_common_tie_cmul(vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_cmul_conj(vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_cmac(vr64 hz, vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_cmac_conj(vr64 hz, vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_cmas(vr64 hz, vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_cmas_conj(vr64 hz, vr64 hx, vr64 hy);
extern void _TIE_dmx1a_common_tie_cmul_L(vr128 z /*inout*/, vr128 x, vr128 y, immediate mode);
extern void _TIE_dmx1a_common_tie_cmul_H(vr128 z /*inout*/, vr128 x, vr128 y, immediate mode);
extern void _TIE_dmx1a_common_tie_cmac_L(vr128 z /*inout*/, vr128 x, vr128 y, immediate mode);
extern void _TIE_dmx1a_common_tie_cmac_H(vr128 z /*inout*/, vr128 x, vr128 y, immediate mode);
extern void _TIE_dmx1a_common_tie_cmas_L(vr128 z /*inout*/, vr128 x, vr128 y, immediate mode);
extern void _TIE_dmx1a_common_tie_cmas_H(vr128 z /*inout*/, vr128 x, vr128 y, immediate mode);
extern vr128 _TIE_dmx1a_common_tie_cmac_Lx2(vr128 z, vr128 x, vr128 y, immediate mode);
extern vr128 _TIE_dmx1a_common_tie_cmac_Hx2(vr128 z, vr128 x, vr128 y, immediate mode);
extern vr128 _TIE_dmx1a_common_tie_cmul_x2(vr128 x, vr128 y, immediate mode);
extern vr128 _TIE_dmx1a_common_tie_cmac_adj_x2(vr128 z, vr128 x, vr128 y, immediate mode, immediate boost);
extern vr128 _TIE_dmx1a_common_tie_cmas_adj_x2(vr128 z, vr128 x, vr128 y, immediate mode, immediate boost);
extern vr128 _TIE_dmx1a_common_tie_xcorr(vr128 z, vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_xconv(vr128 z, vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_qmul_1(vr128 x, vr128 y, immediate mode);
extern void _TIE_dmx1a_common_tie_qmul_2(vr128 z /*inout*/, vr128 x, vr128 y, immediate mode);
extern vr128 _TIE_dmx1a_common_tie_matmul_2x2(vr128 z, vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_vadds(vr128 x, vr128 y, immediate signs8);
extern vr128 _TIE_dmx1a_common_tie_vmidp(vr128 x, vr128 y, immediate signs8);
extern vr128 _TIE_dmx1a_common_tie_vmuls(vr128 x, vr128 y, immediate signs8);
extern vr128 _TIE_dmx1a_common_tie_vmacs_adj(vr128 z, vr128 x, vr128 y, immediate signs8, immediate boost);
extern vr128 _TIE_dmx1a_common_tie_vmuls_perm(vr128 x, vr128 y, immediate signs8, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_vmacs_perm(vr128 z, vr128 x, vr128 y, immediate signs8, perm16 perm);
extern void _TIE_dmx1a_common_tie_vssub_L(vr128 z /*inout*/, vr128 x, vr128 y, wr64 w);
extern void _TIE_dmx1a_common_tie_vssub_H(vr128 z /*inout*/, vr128 x, vr128 y, wr64 w);
extern vr128 _TIE_dmx1a_common_tie_vssub_x2(vr128 x, vr128 y, wr64 w);
extern void _TIE_dmx1a_common_tie_vinterp_L(vr128 z /*inout*/, vr128 x, vr128 y, wr64 w);
extern void _TIE_dmx1a_common_tie_vinterp_H(vr128 z /*inout*/, vr128 x, vr128 y, wr64 w);
extern vr128 _TIE_dmx1a_common_tie_vinterp_x2(vr128 x, vr128 y, wr64 w);
extern void _TIE_dmx1a_common_tie_csums_L(vr128 z /*inout*/, vr128 x, immediate signs6, immediate div_by_2_op);
extern void _TIE_dmx1a_common_tie_csums_H(vr128 z /*inout*/, vr128 x, immediate signs6, immediate div_by_2_op);
extern void _TIE_dmx1a_common_tie_dsums_L(vr128 z /*inout*/, vr128 x, immediate signs6, immediate div_by_2_op);
extern void _TIE_dmx1a_common_tie_dsums_H(vr128 z /*inout*/, vr128 x, immediate signs6, immediate div_by_2_op);
extern vr64 _TIE_dmx1a_common_tie_vadd_hr(vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_vsub_hr(vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_vmul_hr(vr64 hx, vr64 hy);
extern vr64 _TIE_dmx1a_common_tie_vmac_hr(vr64 hz, vr64 hx, vr64 hy);
extern fr32 _TIE_dmx1a_common_tie_fpadd(fr32 fx, fr32 fy, immediate signs2);
extern fr32 _TIE_dmx1a_common_tie_fpmul(fr32 fx, fr32 fy, immediate signs2);
extern void _TIE_dmx1a_common_tie_fpmac(fr32 fz /*inout*/, fr32 fx, fr32 fy, immediate signs2);
extern fr32 _TIE_dmx1a_common_tie_fpmul_sum3(vr128 x, vr128 y, immediate signs3, perm16 perm);
extern vr128 _TIE_dmx1a_common_tie_vscale(fr32 fx, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_vscale_adds(vr128 z, fr32 fx, vr128 y, immediate signs2);
extern void _TIE_dmx1a_common_tie_fadds(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, immediate signs5);
extern void _TIE_dmx1a_common_tie_fmacs(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, immediate signs5);
extern void _TIE_dmx1a_common_tie_fmuls(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, immediate signs5);
extern void _TIE_dmx1a_common_tie_fmul_sum3(vr128 z /*inout*/, immediate el_z, vr128 x, vr128 y, immediate signs3, perm16 perm);
extern vr64 _TIE_dmx1a_common_tie_dadds(vr64 z, vr64 x, immediate signs2);
extern vr64 _TIE_dmx1a_common_tie_dmuls(vr64 x, vr64 y, immediate signs2);
extern vr64 _TIE_dmx1a_common_tie_dmacs(vr64 z, vr64 x, vr64 y, immediate signs2);
extern vr128 _TIE_dmx1a_common_tie_vabs(vr128 x);
extern vr128 _TIE_dmx1a_common_tie_vexp_adj(vr128 x, unsigned exp_adj_ar);
extern vr128 _TIE_dmx1a_common_tie_vexp_adji(vr128 x, immediate exp_adj_imm);
extern vr128 _TIE_dmx1a_common_tie_vperm(vr128 x, vr128 y, perm16 sel);
extern vr128 _TIE_dmx1a_common_tie_vperms(vr128 x, vr128 y, perm16 sel);
extern vr128 _TIE_dmx1a_common_tie_vpermsi(vr128 x, vr128 y, immediate signs, immediate sel3);
extern void _TIE_dmx1a_common_tie_seta_vr(vr128 z /*inout*/, immediate sel_code, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern vr128 _TIE_dmx1a_common_tie_vseta_vr(immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern unsigned _TIE_dmx1a_common_tie_seta_ar(immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern fr32 _TIE_dmx1a_common_tie_seta_fr(immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern void _TIE_dmx1a_common_tie_f_abs(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_fclamp(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_fclamp_bp(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_fclamp_one(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_fmax(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_fmin(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern fr32 _TIE_dmx1a_common_tie_max_fr(fr32 fx, fr32 fy);
extern fr32 _TIE_dmx1a_common_tie_min_fr(fr32 fx, fr32 fy);
extern void _TIE_dmx1a_common_tie_log2(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_pow2(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_sigmoid(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_inv(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_ratio(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool4 bz4 /*out*/);
extern void _TIE_dmx1a_common_tie_atanratio(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, xtbool4 bx4);
extern void _TIE_dmx1a_common_tie_invsqrt(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_sine(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_cosine(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_log2mul(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool bz /*out*/);
extern void _TIE_dmx1a_common_tie_cspow2(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, xtbool bx);
extern fr32 _TIE_dmx1a_common_tie_log2_fr(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_pow2_fr(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_sigmoid_fr(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_inv_fr(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_invsqrt_fr(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_sine_fr(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_cosine_fr(fr32 fx);
extern xtbool2 _TIE_dmx1a_common_tie_comp(vr128 x, immediate el_x, vr128 y, immediate el_y);
extern xtbool _TIE_dmx1a_common_tie_eq(vr128 x, immediate el_x, vr128 y, immediate el_y);
extern xtbool _TIE_dmx1a_common_tie_ge(vr128 x, immediate el_x, vr128 y, immediate el_y);
extern xtbool _TIE_dmx1a_common_tie_gt(vr128 x, immediate el_x, vr128 y, immediate el_y);
extern xtbool _TIE_dmx1a_common_tie_le(vr128 x, immediate el_x, vr128 y, immediate el_y);
extern xtbool _TIE_dmx1a_common_tie_lt(vr128 x, immediate el_x, vr128 y, immediate el_y);
extern xtbool _TIE_dmx1a_common_tie_ne(vr128 x, immediate el_x, vr128 y, immediate el_y);
extern xtbool2 _TIE_dmx1a_common_tie_comp_const(vr128 x, immediate el_x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool _TIE_dmx1a_common_tie_eq_const(vr128 x, immediate el_x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool _TIE_dmx1a_common_tie_ge_const(vr128 x, immediate el_x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool _TIE_dmx1a_common_tie_gt_const(vr128 x, immediate el_x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool _TIE_dmx1a_common_tie_le_const(vr128 x, immediate el_x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool _TIE_dmx1a_common_tie_lt_const(vr128 x, immediate el_x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool _TIE_dmx1a_common_tie_ne_const(vr128 x, immediate el_x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool _TIE_dmx1a_common_tie_eq_fr(fr32 fx, fr32 fy);
extern xtbool _TIE_dmx1a_common_tie_ge_fr(fr32 fx, fr32 fy);
extern xtbool _TIE_dmx1a_common_tie_gt_fr(fr32 fx, fr32 fy);
extern xtbool _TIE_dmx1a_common_tie_le_fr(fr32 fx, fr32 fy);
extern xtbool _TIE_dmx1a_common_tie_lt_fr(fr32 fx, fr32 fy);
extern xtbool _TIE_dmx1a_common_tie_ne_fr(fr32 fx, fr32 fy);
extern fr32 _TIE_dmx1a_common_tie_neg_fr(fr32 fx);
extern fr32 _TIE_dmx1a_common_tie_abs_fr(fr32 fx);
extern xtbool _TIE_dmx1a_common_tie_deqz(vr64 x);
extern xtbool _TIE_dmx1a_common_tie_dgez(vr64 x);
extern xtbool _TIE_dmx1a_common_tie_dgtz(vr64 x);
extern xtbool _TIE_dmx1a_common_tie_dlez(vr64 x);
extern xtbool _TIE_dmx1a_common_tie_dltz(vr64 x);
extern xtbool _TIE_dmx1a_common_tie_dnez(vr64 x);
extern xtbool4 _TIE_dmx1a_common_tie_veq(vr128 x, vr128 y);
extern xtbool4 _TIE_dmx1a_common_tie_vge(vr128 x, vr128 y);
extern xtbool4 _TIE_dmx1a_common_tie_vgt(vr128 x, vr128 y);
extern xtbool4 _TIE_dmx1a_common_tie_vle(vr128 x, vr128 y);
extern xtbool4 _TIE_dmx1a_common_tie_vlt(vr128 x, vr128 y);
extern xtbool4 _TIE_dmx1a_common_tie_vne(vr128 x, vr128 y);
extern xtbool4 _TIE_dmx1a_common_tie_veq_const(vr128 x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool4 _TIE_dmx1a_common_tie_vge_const(vr128 x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool4 _TIE_dmx1a_common_tie_vgt_const(vr128 x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool4 _TIE_dmx1a_common_tie_vle_const(vr128 x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool4 _TIE_dmx1a_common_tie_vlt_const(vr128 x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern xtbool4 _TIE_dmx1a_common_tie_vne_const(vr128 x, immediate const_idx, immediate exp_adj_const, immediate mul_rnd);
extern void _TIE_dmx1a_common_tie_sel(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool bx);
extern void _TIE_dmx1a_common_tie_sel_1b4(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool4 bx4, immediate el_bx4);
extern void _TIE_dmx1a_common_tie_sel_eq(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool2 bx2);
extern void _TIE_dmx1a_common_tie_sel_ge(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool2 bx2);
extern void _TIE_dmx1a_common_tie_sel_gt(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool2 bx2);
extern void _TIE_dmx1a_common_tie_sel_le(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool2 bx2);
extern void _TIE_dmx1a_common_tie_sel_lt(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool2 bx2);
extern void _TIE_dmx1a_common_tie_sel_ne(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y, xtbool2 bx2);
extern vr128 _TIE_dmx1a_common_tie_vsel(vr128 x, vr128 y, xtbool4 bx4);
extern xtbool _TIE_dmx1a_common_tie_andb1(xtbool bx, xtbool by);
extern xtbool _TIE_dmx1a_common_tie_andbc1(xtbool bx, xtbool by);
extern xtbool _TIE_dmx1a_common_tie_orb1(xtbool bx, xtbool by);
extern xtbool _TIE_dmx1a_common_tie_orbc1(xtbool bx, xtbool by);
extern xtbool _TIE_dmx1a_common_tie_xorb1(xtbool bx, xtbool by);
extern xtbool4 _TIE_dmx1a_common_tie_andb4(xtbool4 bx4, xtbool4 by4);
extern xtbool4 _TIE_dmx1a_common_tie_andbc4(xtbool4 bx4, xtbool4 by4);
extern xtbool4 _TIE_dmx1a_common_tie_orb4(xtbool4 bx4, xtbool4 by4);
extern xtbool4 _TIE_dmx1a_common_tie_orbc4(xtbool4 bx4, xtbool4 by4);
extern xtbool4 _TIE_dmx1a_common_tie_xorb4(xtbool4 bx4, xtbool4 by4);
extern unsigned _TIE_dmx1a_common_tie_bcount0_maskI(xtbool4 bx4, immediate imask);
extern unsigned _TIE_dmx1a_common_tie_bcount0_maskR(xtbool4 bx4, xtbool4 by4);
extern unsigned _TIE_dmx1a_common_tie_bcount1_maskI(xtbool4 bx4, immediate imask);
extern unsigned _TIE_dmx1a_common_tie_bcount1_maskR(xtbool4 bx4, xtbool4 by4);
extern unsigned _TIE_dmx1a_common_tie_bfirst0_maskI(xtbool4 bx4, immediate imask);
extern unsigned _TIE_dmx1a_common_tie_bfirst0_maskR(xtbool4 bx4, xtbool4 by4);
extern unsigned _TIE_dmx1a_common_tie_bfirst1_maskI(xtbool4 bx4, immediate imask);
extern unsigned _TIE_dmx1a_common_tie_bfirst1_maskR(xtbool4 bx4, xtbool4 by4);
extern unsigned _TIE_dmx1a_common_tie_blast0_maskI(xtbool4 bx4, immediate imask);
extern unsigned _TIE_dmx1a_common_tie_blast0_maskR(xtbool4 bx4, xtbool4 by4);
extern unsigned _TIE_dmx1a_common_tie_blast1_maskI(xtbool4 bx4, immediate imask);
extern unsigned _TIE_dmx1a_common_tie_blast1_maskR(xtbool4 bx4, xtbool4 by4);
extern xtbool _TIE_dmx1a_common_tie_bgetI(xtbool4 bx4, immediate ipos);
extern xtbool _TIE_dmx1a_common_tie_bgetR(xtbool4 bx4, unsigned rpos);
extern xtbool4 _TIE_dmx1a_common_tie_bsetI(xtbool4 bx4, unsigned rpos, immediate ibit);
extern xtbool4 _TIE_dmx1a_common_tie_bsetR(xtbool4 bx4, unsigned rpos, xtbool by);
extern void _TIE_dmx1a_common_tie_exp_adj(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, unsigned exp_adj_ar);
extern void _TIE_dmx1a_common_tie_exp_adji(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, immediate exp_adj_imm);
extern fr32 _TIE_dmx1a_common_tie_exp_adj_fr(fr32 fx, unsigned exp_adj_ar);
extern fr32 _TIE_dmx1a_common_tie_exp_adji_fr(fr32 fx, immediate exp_adj_imm);
extern void _TIE_dmx1a_common_tie_s_neg(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x);
extern void _TIE_dmx1a_common_tie_s_copy(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_s_and(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_s_andc(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_s_or(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_s_orc(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_s_xor(vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, vr128 y, immediate el_y);
extern vr128 _TIE_dmx1a_common_tie_s_vnegs(vr128 x, immediate signs);
extern vr128 _TIE_dmx1a_common_tie_s_vcopy(vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_s_vand(vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_s_vandc(vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_s_vor(vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_s_vorc(vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_s_vxor(vr128 x, vr128 y);
extern vr64 _TIE_dmx1a_common_tie_s_vnegs_hr(vr64 hx, immediate hr_signs);
extern void _TIE_dmx1a_common_tie_floorp_frac(unsigned floor /*out*/, vr128 z /*inout*/, immediate el_z, vr128 x, immediate el_x, immediate nbits);
extern void _TIE_dmx1a_common_tie_idx_frac(unsigned floor /*out*/, vr128 z /*inout*/, immediate el_z, unsigned input, immediate nbits);
extern fr32 _TIE_dmx1a_common_tie_truncate_fr(fr32 x);
extern void _TIE_dmx1a_common_tie_rmax_idx(unsigned a /*out*/, vr128 z /*inout*/, immediate el_z, vr128 x, mir30 idx);
extern void _TIE_dmx1a_common_tie_rmin_idx(unsigned a /*out*/, vr128 z /*inout*/, immediate el_z, vr128 x, mir30 idx);
extern void _TIE_dmx1a_common_tie_vmaxmin_init(vr128 z /*out*/, vr128 x, mir30 idx /*out*/);
extern void _TIE_dmx1a_common_tie_vmax_idx(vr128 z /*inout*/, vr128 x, mir30 idx /*inout*/);
extern void _TIE_dmx1a_common_tie_vmin_idx(vr128 z /*inout*/, vr128 x, mir30 idx /*inout*/);
extern vr128 _TIE_dmx1a_common_tie_vmax(vr128 x, vr128 y);
extern vr128 _TIE_dmx1a_common_tie_vmin(vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_sortupd_asc_vr(unsigned a /*out*/, vr128 z /*out*/, vr128 x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_sortupd_des_vr(unsigned a /*out*/, vr128 z /*out*/, vr128 x, vr128 y, immediate el_y);
extern void _TIE_dmx1a_common_tie_sortupd_asc_ar(unsigned a /*inout*/, vr128 z /*out*/, vr128 x);
extern void _TIE_dmx1a_common_tie_sortupd_des_ar(unsigned a /*inout*/, vr128 z /*out*/, vr128 x);
extern vr128 _TIE_dmx1a_common_tie_vbool(vr128 x, vr128 y, immediate op);
extern unsigned _TIE_dmx1a_common_tie_align_up(unsigned val, unsigned option);
extern mir30 _TIE_dmx1a_common_tie_range_init(unsigned low, unsigned high, immediate startOp);
extern void _TIE_dmx1a_common_tie_range_check(xtbool4 bz4 /*out*/, mir30 idx /*inout*/);
extern vr128 _TIE_dmx1a_common_tie_afloat_exp_extract(vr128 x);
extern unsigned _TIE_dmx1a_common_tie_exp_shift_amount(vr128 input);
extern void _TIE_dmx1a_common_tie_flush_32x4_bounded(ulsr128 buf, unsigned * ptr /*inout*/, mir30 count /*inout*/);
extern void _TIE_dmx1a_common_tie_load_AccExtend_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB0_flex(const unsigned * ptr, unsigned remBlock, mir30 parms);
extern void _TIE_dmx1a_common_tie_load_BB1_flex(const unsigned * ptr, unsigned remBlock, mir30 parms);
extern void _TIE_dmx1a_common_tie_load_BB2_flex(const unsigned * ptr, unsigned remBlock, mir30 parms);
extern void _TIE_dmx1a_common_tie_load_BB3_flex(const unsigned * ptr, unsigned remBlock, mir30 parms);
extern void _TIE_dmx1a_common_tie_load_BB4_flex(const unsigned * ptr, unsigned remBlock, mir30 parms);
extern void _TIE_dmx1a_common_tie_load_BB5_flex(const unsigned * ptr, unsigned remBlock, mir30 parms);
extern void _TIE_dmx1a_common_tie_load_BB6_flex(const unsigned * ptr, unsigned remBlock, mir30 parms);
extern void _TIE_dmx1a_common_tie_load_BB7_flex(const unsigned * ptr /*inout*/, unsigned remBlock, mir30 parms /*inout*/);
extern void _TIE_dmx1a_common_tie_load_BB0_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB1_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB2_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB3_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB4_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB5_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB6_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BB7_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_BBx_a_bounded(ulsr128 buf /*inout*/, const unsigned * ptr /*inout*/, mir30 count /*inout*/, unsigned sel);
extern void _TIE_dmx1a_common_tie_load_VB1_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_VB2_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_VB3_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_VB4_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_VB5_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_VB6_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_VB7_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_load_32x4_vr_a_bounded(vr128 z /*out*/, ulsr128 buf /*inout*/, const unsigned * ptr /*inout*/, mir30 count /*inout*/);
extern void _TIE_dmx1a_common_tie_load_lookup_AccExtend_postI(void);
extern vr128 _TIE_dmx1a_common_tie_load_lookup_vr_postI(void);
extern void _TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr(vr128 vidx16, immediate ptr_sel);
extern void _TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr(vr128 z /*inout*/, vr128 vidx16, immediate ptr_sel);
extern void _TIE_dmx1a_common_tie_load32x1_vr_idx16vr(vr128 z /*inout*/, const unsigned * ptr, vr128 vidx16, immediate ptr_sel);
extern void _TIE_dmx1a_common_tie_mac8bx8b(vr128 z /*inout*/, vr128 x, vr128 y, xtbool2 signed_xy);
extern void _TIE_dmx1a_common_tie_mac8bx8b_conv(vr128 z /*inout*/, vr128 x, xtbool2 signed_xy, immediate shift_in);
extern void _TIE_dmx1a_common_tie_mac8bx8b_sparse(vr128 z /*inout*/, vr128 x, vr128 y, xtbool2 signed_xy);
extern mir30 _TIE_dmx1a_common_tie_mir_init(unsigned low);
extern void _TIE_dmx1a_common_tie_mov_AccExtend_vr(vr128 x);
extern void _TIE_dmx1a_common_tie_mov_BB_vrVB(vr128 x);
extern vr128 _TIE_dmx1a_common_tie_mov_vr_AccExtend(void);
extern vr128 _TIE_dmx1a_common_tie_mov_vrVB_BB(void);
extern void _TIE_dmx1a_common_tie_next_lookup_load(void);
extern void _TIE_dmx1a_common_tie_next_lookup_store(void);
extern vr128 _TIE_dmx1a_common_tie_precess_16bits(vr128 x, vr128 y);
extern void _TIE_dmx1a_common_tie_rectify32_into8(vr128 z /*inout*/, vr128 x, unsigned shift, immediate rnd, immediate el32);
extern void _TIE_dmx1a_common_tie_rnd_sat_pack(vr128 z /*inout*/, immediate el32, vr128 x, xtbool sgn);
extern void _TIE_dmx1a_common_tie_set_BB_zero(void);
extern vr128 _TIE_dmx1a_common_tie_shift8_into32_arith(vr128 x, unsigned shift, immediate rnd, immediate el32);
extern vr128 _TIE_dmx1a_common_tie_shift32_arith(vr128 x, unsigned shift, immediate rnd);
extern void _TIE_dmx1a_common_tie_store_32x4_vr_a_bounded(vr128 z, ulsr128 buf /*inout*/, unsigned * ptr /*inout*/, mir30 count /*inout*/);
extern void _TIE_dmx1a_common_tie_store_AccExtend_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB0_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB1_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB2_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB3_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB4_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB5_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB6_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_BB7_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_VB1_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_VB2_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_VB3_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_VB4_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_VB5_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_VB6_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_VB7_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_dmx1a_common_tie_store_lookup_AccExtend_postI(void);
extern void _TIE_dmx1a_common_tie_store_lookup_vr_postI(vr128 z);
extern wr64 _TIE_dmx1a_common_tie_mv_WR(wr64 b);
extern perm16 _TIE_dmx1a_common_tie_mv_PERM(perm16 b);
extern mir30 _TIE_dmx1a_common_tie_mv_MIR(mir30 b);
extern ulsr128 _TIE_dmx1a_common_tie_mv_ULSR(ulsr128 b);
extern cr64 _TIE_dmx1a_common_tie_mv_CR(cr64 b);
extern fr32 _TIE_dmx1a_common_tie_ld_FR(const fr32 * addr, immediate fimm);
extern void _TIE_dmx1a_common_tie_st_FR(fr32 fregin, fr32 * addr, immediate fimm);
extern fr32 _TIE_dmx1a_common_tie_ld_FR_idxR(const fr32 * addr, unsigned x);
extern void _TIE_dmx1a_common_tie_st_FR_idxR(fr32 fregin, fr32 * addr, unsigned x);
extern void _TIE_dmx1a_common_tie_ld_FR_postI(fr32 fregout /*out*/, const fr32 * addr /*inout*/, immediate fimm);
extern void _TIE_dmx1a_common_tie_st_FR_postI(fr32 fregin, fr32 * addr /*inout*/, immediate fimm);
extern void _TIE_dmx1a_common_tie_ld_FR_postR(fr32 fregout /*out*/, const fr32 * addr /*inout*/, unsigned x);
extern void _TIE_dmx1a_common_tie_st_FR_postR(fr32 fregin, fr32 * addr /*inout*/, unsigned x);
extern vr64 _TIE_dmx1a_common_tie_ld_HR(const vr64 * addr, immediate himm);
extern void _TIE_dmx1a_common_tie_st_HR(vr64 hregin, vr64 * addr, immediate himm);
extern vr64 _TIE_dmx1a_common_tie_ld_HR_idxR(const vr64 * addr, unsigned x);
extern void _TIE_dmx1a_common_tie_st_HR_idxR(vr64 hregin, vr64 * addr, unsigned x);
extern void _TIE_dmx1a_common_tie_ld_HR_postI(vr64 hregout /*out*/, const vr64 * addr /*inout*/, immediate himm);
extern void _TIE_dmx1a_common_tie_st_HR_postI(vr64 hregin, vr64 * addr /*inout*/, immediate himm);
extern void _TIE_dmx1a_common_tie_ld_HR_postR(vr64 hregout /*out*/, const vr64 * addr /*inout*/, unsigned x);
extern void _TIE_dmx1a_common_tie_st_HR_postR(vr64 hregin, vr64 * addr /*inout*/, unsigned x);
extern vr128 _TIE_dmx1a_common_tie_ld_VR(const vr128 * addr, immediate vimm);
extern void _TIE_dmx1a_common_tie_st_VR(vr128 vregin, vr128 * addr, immediate vimm);
extern vr128 _TIE_dmx1a_common_tie_ld_VR_idxR(const vr128 * addr, unsigned x);
extern void _TIE_dmx1a_common_tie_st_VR_idxR(vr128 vregin, vr128 * addr, unsigned x);
extern void _TIE_dmx1a_common_tie_ld_VR_postI(vr128 vregout /*out*/, const vr128 * addr /*inout*/, immediate vimm);
extern void _TIE_dmx1a_common_tie_st_VR_postI(vr128 vregin, vr128 * addr /*inout*/, immediate vimm);
extern void _TIE_dmx1a_common_tie_ld_VR_postR(vr128 vregout /*out*/, const vr128 * addr /*inout*/, unsigned x);
extern void _TIE_dmx1a_common_tie_st_VR_postR(vr128 vregin, vr128 * addr /*inout*/, unsigned x);
extern fr32 _TIE_dmx1a_common_tie_mv_FR(fr32 b);
extern unsigned _TIE_dmx1a_common_tie_move_ar_fr(fr32 b);
extern fr32 _TIE_dmx1a_common_tie_move_fr_ar(unsigned b);
extern vr64 _TIE_dmx1a_common_tie_mv_HR(vr64 b);
extern vr128 _TIE_dmx1a_common_tie_mv_VR(vr128 b);
extern vr128 _TIE_dmx1a_common_tie_vr128_pair(vr64 hi, vr64 lo);
extern void _TIE_dmx1a_common_tie_set_VRL(vr128 v /*inout*/, vr64 lo);
extern void _TIE_dmx1a_common_tie_set_VRH(vr128 v /*inout*/, vr64 hi);
extern vr64 _TIE_dmx1a_common_tie_get_VRL(vr128 b);
extern vr64 _TIE_dmx1a_common_tie_get_VRH(vr128 b);
extern void _TIE_dmx1a_common_tie_ld_ar_x2(unsigned a1_out /*out*/, unsigned a0_out /*out*/, const void * ptr, immediate idx);
extern void _TIE_dmx1a_common_tie_st_ar_x2(void * ptr, immediate idx, unsigned a1_in, unsigned a0_in);
extern void _TIE_dmx1a_common_tie_perm16_storei(perm16 a, perm16 * b, immediate c);
extern perm16 _TIE_dmx1a_common_tie_perm16_loadi(const perm16 * b, immediate c);
extern void _TIE_dmx1a_common_tie_ulsr128_storei(ulsr128 a, ulsr128 * b, immediate c);
extern ulsr128 _TIE_dmx1a_common_tie_ulsr128_loadi(const ulsr128 * b, immediate c);
extern void _TIE_dmx1a_common_tie_mir30_storei(mir30 a, mir30 * b, immediate c);
extern mir30 _TIE_dmx1a_common_tie_mir30_loadi(const mir30 * b, immediate c);
extern void _TIE_dmx1a_common_tie_cr64_storei(cr64 a, cr64 * b, immediate c);
extern cr64 _TIE_dmx1a_common_tie_cr64_loadi(const cr64 * b, immediate c);
extern void _TIE_dmx1a_common_tie_wr64_storei(wr64 a, wr64 * b, immediate c);
extern wr64 _TIE_dmx1a_common_tie_wr64_loadi(const wr64 * b, immediate c);
extern unsigned _TIE_dmx1a_common_tie_RUR_JammingBit(void);
extern void _TIE_dmx1a_common_tie_WUR_JammingBit(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_AccExtend_0(void);
extern void _TIE_dmx1a_common_tie_WUR_AccExtend_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_AccExtend_1(void);
extern void _TIE_dmx1a_common_tie_WUR_AccExtend_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_AccExtend_2(void);
extern void _TIE_dmx1a_common_tie_WUR_AccExtend_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_AccExtend_3(void);
extern void _TIE_dmx1a_common_tie_WUR_AccExtend_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB0_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB0_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB0_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB0_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB0_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB0_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB0_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB0_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB1_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB1_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB1_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB1_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB1_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB1_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB1_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB1_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB2_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB2_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB2_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB2_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB2_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB2_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB2_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB2_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB3_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB3_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB3_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB3_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB3_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB3_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB3_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB3_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB4_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB4_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB4_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB4_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB4_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB4_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB4_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB4_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB5_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB5_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB5_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB5_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB5_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB5_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB5_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB5_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB6_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB6_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB6_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB6_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB6_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB6_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB6_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB6_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB7_0(void);
extern void _TIE_dmx1a_common_tie_WUR_BB7_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB7_1(void);
extern void _TIE_dmx1a_common_tie_WUR_BB7_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB7_2(void);
extern void _TIE_dmx1a_common_tie_WUR_BB7_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_BB7_3(void);
extern void _TIE_dmx1a_common_tie_WUR_BB7_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_MvmAux(void);
extern void _TIE_dmx1a_common_tie_WUR_MvmAux(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB1_0(void);
extern void _TIE_dmx1a_common_tie_WUR_VB1_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB1_1(void);
extern void _TIE_dmx1a_common_tie_WUR_VB1_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB1_2(void);
extern void _TIE_dmx1a_common_tie_WUR_VB1_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB1_3(void);
extern void _TIE_dmx1a_common_tie_WUR_VB1_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB2_0(void);
extern void _TIE_dmx1a_common_tie_WUR_VB2_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB2_1(void);
extern void _TIE_dmx1a_common_tie_WUR_VB2_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB2_2(void);
extern void _TIE_dmx1a_common_tie_WUR_VB2_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB2_3(void);
extern void _TIE_dmx1a_common_tie_WUR_VB2_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB3_0(void);
extern void _TIE_dmx1a_common_tie_WUR_VB3_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB3_1(void);
extern void _TIE_dmx1a_common_tie_WUR_VB3_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB3_2(void);
extern void _TIE_dmx1a_common_tie_WUR_VB3_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB3_3(void);
extern void _TIE_dmx1a_common_tie_WUR_VB3_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB4_0(void);
extern void _TIE_dmx1a_common_tie_WUR_VB4_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB4_1(void);
extern void _TIE_dmx1a_common_tie_WUR_VB4_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB4_2(void);
extern void _TIE_dmx1a_common_tie_WUR_VB4_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB4_3(void);
extern void _TIE_dmx1a_common_tie_WUR_VB4_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB5_0(void);
extern void _TIE_dmx1a_common_tie_WUR_VB5_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB5_1(void);
extern void _TIE_dmx1a_common_tie_WUR_VB5_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB5_2(void);
extern void _TIE_dmx1a_common_tie_WUR_VB5_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB5_3(void);
extern void _TIE_dmx1a_common_tie_WUR_VB5_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB6_0(void);
extern void _TIE_dmx1a_common_tie_WUR_VB6_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB6_1(void);
extern void _TIE_dmx1a_common_tie_WUR_VB6_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB6_2(void);
extern void _TIE_dmx1a_common_tie_WUR_VB6_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB6_3(void);
extern void _TIE_dmx1a_common_tie_WUR_VB6_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB7_0(void);
extern void _TIE_dmx1a_common_tie_WUR_VB7_0(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB7_1(void);
extern void _TIE_dmx1a_common_tie_WUR_VB7_1(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB7_2(void);
extern void _TIE_dmx1a_common_tie_WUR_VB7_2(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_VB7_3(void);
extern void _TIE_dmx1a_common_tie_WUR_VB7_3(unsigned v);
extern unsigned _TIE_dmx1a_common_tie_RUR_look_state(void);
extern void _TIE_dmx1a_common_tie_WUR_look_state(unsigned v);
extern wr64 _TIE_dmx1a_common_tie_wr64_move(wr64 b);
extern perm16 _TIE_dmx1a_common_tie_perm16_move(perm16 b);
extern mir30 _TIE_dmx1a_common_tie_mir30_move(mir30 b);
extern ulsr128 _TIE_dmx1a_common_tie_ulsr128_move(ulsr128 b);
extern cr64 _TIE_dmx1a_common_tie_cr64_move(cr64 b);
extern fr32 _TIE_dmx1a_common_tie_fr32_move(fr32 b);
extern fr32 _TIE_dmx1a_common_tie_fr32_loadi(const fr32 * p, immediate o);
extern void _TIE_dmx1a_common_tie_fr32_storei(fr32 v, fr32 * p, immediate o);
extern fr32 _TIE_dmx1a_common_tie_fr32_loadx(const fr32 * p, unsigned x);
extern void _TIE_dmx1a_common_tie_fr32_storex(fr32 v, fr32 * p, unsigned x);
extern void _TIE_dmx1a_common_tie_fr32_loadip(fr32 v /*out*/, const fr32 * p /*inout*/, immediate o);
extern void _TIE_dmx1a_common_tie_fr32_storeip(fr32 v, fr32 * p /*inout*/, immediate o);
extern void _TIE_dmx1a_common_tie_fr32_loadxp(fr32 v /*out*/, const fr32 * p /*inout*/, unsigned x);
extern void _TIE_dmx1a_common_tie_fr32_storexp(fr32 v, fr32 * p /*inout*/, unsigned x);
extern int _TIE_dmx1a_common_tie_fr32_rtor_int32(fr32 b);
extern unsigned _TIE_dmx1a_common_tie_fr32_rtor_uint32(fr32 b);
extern fr32 _TIE_dmx1a_common_tie_int32_rtor_fr32(int a);
extern fr32 _TIE_dmx1a_common_tie_uint32_rtor_fr32(unsigned a);
extern vr64 _TIE_dmx1a_common_tie_vr64_move(vr64 b);
extern vr64 _TIE_dmx1a_common_tie_vr64_loadi(const vr64 * p, immediate o);
extern void _TIE_dmx1a_common_tie_vr64_storei(vr64 v, vr64 * p, immediate o);
extern vr64 _TIE_dmx1a_common_tie_vr64_loadx(const vr64 * p, unsigned x);
extern void _TIE_dmx1a_common_tie_vr64_storex(vr64 v, vr64 * p, unsigned x);
extern void _TIE_dmx1a_common_tie_vr64_loadip(vr64 v /*out*/, const vr64 * p /*inout*/, immediate o);
extern void _TIE_dmx1a_common_tie_vr64_storeip(vr64 v, vr64 * p /*inout*/, immediate o);
extern void _TIE_dmx1a_common_tie_vr64_loadxp(vr64 v /*out*/, const vr64 * p /*inout*/, unsigned x);
extern void _TIE_dmx1a_common_tie_vr64_storexp(vr64 v, vr64 * p /*inout*/, unsigned x);
extern long long _TIE_dmx1a_common_tie_vr64_rtor_int64(vr64 b);
extern unsigned long long _TIE_dmx1a_common_tie_vr64_rtor_uint64(vr64 b);
extern vr64 _TIE_dmx1a_common_tie_int64_rtor_vr64(long long a);
extern vr64 _TIE_dmx1a_common_tie_uint64_rtor_vr64(unsigned long long a);
extern vr64 _TIE_dmx1a_common_tie_vr64_pair(fr32 hi, fr32 lo);
extern fr32 _TIE_dmx1a_common_tie_get_HRL(vr64 b);
extern fr32 _TIE_dmx1a_common_tie_get_HRH(vr64 b);
extern void _TIE_dmx1a_common_tie_set_HRL(vr64 a /*inout*/, fr32 b);
extern void _TIE_dmx1a_common_tie_set_HRH(vr64 a /*inout*/, fr32 b);
extern vr128 _TIE_dmx1a_common_tie_vr128_move(vr128 b);
extern vr128 _TIE_dmx1a_common_tie_vr128_loadi(const vr128 * b, immediate c);
extern void _TIE_dmx1a_common_tie_vr128_storei(vr128 a, vr128 * b, immediate c);
extern vr128 _TIE_dmx1a_common_tie_vr128_loadx(const vr128 * b, unsigned x);
extern void _TIE_dmx1a_common_tie_vr128_storex(vr128 a, vr128 * b, unsigned x);
extern void _TIE_dmx1a_common_tie_vr128_loadip(vr128 a /*out*/, const vr128 * b /*inout*/, immediate c);
extern void _TIE_dmx1a_common_tie_vr128_storeip(vr128 a, vr128 * b /*inout*/, immediate c);
extern void _TIE_dmx1a_common_tie_vr128_loadxp(vr128 a /*out*/, const vr128 * b /*inout*/, unsigned x);
extern void _TIE_dmx1a_common_tie_vr128_storexp(vr128 a, vr128 * b /*inout*/, unsigned x);
extern vr128 _TIE_dmx1a_common_tie_vr128_quad(fr32 q3, fr32 q2, fr32 q1, fr32 q0);
extern fr32 _TIE_dmx1a_common_tie_get_VRQ0(vr128 b);
extern fr32 _TIE_dmx1a_common_tie_get_VRQ1(vr128 b);
extern fr32 _TIE_dmx1a_common_tie_get_VRQ2(vr128 b);
extern fr32 _TIE_dmx1a_common_tie_get_VRQ3(vr128 b);
extern void _TIE_dmx1a_common_tie_set_VRQ0(vr128 a /*inout*/, fr32 b);
extern void _TIE_dmx1a_common_tie_set_VRQ1(vr128 a /*inout*/, fr32 b);
extern void _TIE_dmx1a_common_tie_set_VRQ2(vr128 a /*inout*/, fr32 b);
extern void _TIE_dmx1a_common_tie_set_VRQ3(vr128 a /*inout*/, fr32 b);

#endif /*__ASSEMBLER__*/
#endif /*_NOCLANGUAGE*/
#endif /*_ASMLANGUAGE*/

#define st_PERM _TIE_dmx1a_common_tie_st_PERM
#define ld_PERM _TIE_dmx1a_common_tie_ld_PERM
#define st_ULSR _TIE_dmx1a_common_tie_st_ULSR
#define ld_ULSR _TIE_dmx1a_common_tie_ld_ULSR
#define st_MIR _TIE_dmx1a_common_tie_st_MIR
#define ld_MIR _TIE_dmx1a_common_tie_ld_MIR
#define st_CR _TIE_dmx1a_common_tie_st_CR
#define ld_CR _TIE_dmx1a_common_tie_ld_CR
#define st_WR _TIE_dmx1a_common_tie_st_WR
#define ld_WR _TIE_dmx1a_common_tie_ld_WR
#define load32x4_vr_idxR _TIE_dmx1a_common_tie_load32x4_vr_idxR
#define load32x4_vr_idxI _TIE_dmx1a_common_tie_load32x4_vr_idxI
#define load32x4_vr_postR _TIE_dmx1a_common_tie_load32x4_vr_postR
#define load32x4_vr_postI _TIE_dmx1a_common_tie_load32x4_vr_postI
#define load32x4_vr_circI _TIE_dmx1a_common_tie_load32x4_vr_circI
#define load32x2_vr_idxR _TIE_dmx1a_common_tie_load32x2_vr_idxR
#define load32x2_vr_idxI _TIE_dmx1a_common_tie_load32x2_vr_idxI
#define load32x2_vr_postR _TIE_dmx1a_common_tie_load32x2_vr_postR
#define load32x2_vr_postI _TIE_dmx1a_common_tie_load32x2_vr_postI
#define load32x2_vr_circI _TIE_dmx1a_common_tie_load32x2_vr_circI
#define load32x1_vr_idxR _TIE_dmx1a_common_tie_load32x1_vr_idxR
#define load32x1_vr_idxI _TIE_dmx1a_common_tie_load32x1_vr_idxI
#define load32x1_vr_postR _TIE_dmx1a_common_tie_load32x1_vr_postR
#define load32x1_vr_postI _TIE_dmx1a_common_tie_load32x1_vr_postI
#define load32x1_vr_circI _TIE_dmx1a_common_tie_load32x1_vr_circI
#define load32x4_vr_idxR_perm_vr _TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr
#define load32x4_vr_idxI_perm_vr _TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr
#define load32x4_vr_postR_perm_vr _TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr
#define load32x4_vr_postI_perm_vr _TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr
#define load32x4_vr_circI_perm_vr _TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr
#define load32x2_vr_idxR_perm_vr _TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr
#define load32x2_vr_idxI_perm_vr _TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr
#define load32x2_vr_postR_perm_vr _TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr
#define load32x2_vr_postI_perm_vr _TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr
#define load32x2_vr_circI_perm_vr _TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr
#define load32x1_vr_idxR_perm_vr _TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr
#define load32x1_vr_idxI_perm_vr _TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr
#define load32x1_vr_postR_perm_vr _TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr
#define load32x1_vr_postI_perm_vr _TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr
#define load32x1_vr_circI_perm_vr _TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr
#define set_perm16 _TIE_dmx1a_common_tie_set_perm16
#define set_perm16_cond _TIE_dmx1a_common_tie_set_perm16_cond
#define load16x4_vr_idxR _TIE_dmx1a_common_tie_load16x4_vr_idxR
#define load16x4_vr_idxI _TIE_dmx1a_common_tie_load16x4_vr_idxI
#define load16x4_vr_postR _TIE_dmx1a_common_tie_load16x4_vr_postR
#define load16x4_vr_postI _TIE_dmx1a_common_tie_load16x4_vr_postI
#define load16x4_vr_circI _TIE_dmx1a_common_tie_load16x4_vr_circI
#define load16x2_vr_idxR _TIE_dmx1a_common_tie_load16x2_vr_idxR
#define load16x2_vr_idxI _TIE_dmx1a_common_tie_load16x2_vr_idxI
#define load16x2_vr_postR _TIE_dmx1a_common_tie_load16x2_vr_postR
#define load16x2_vr_postI _TIE_dmx1a_common_tie_load16x2_vr_postI
#define load16x2_vr_circI _TIE_dmx1a_common_tie_load16x2_vr_circI
#define load16x1_vr_idxR _TIE_dmx1a_common_tie_load16x1_vr_idxR
#define load16x1_vr_idxI _TIE_dmx1a_common_tie_load16x1_vr_idxI
#define load16x1_vr_postR _TIE_dmx1a_common_tie_load16x1_vr_postR
#define load16x1_vr_postI _TIE_dmx1a_common_tie_load16x1_vr_postI
#define load16x1_vr_circI _TIE_dmx1a_common_tie_load16x1_vr_circI
#define load8x4_vr_idxR _TIE_dmx1a_common_tie_load8x4_vr_idxR
#define load8x4_vr_idxI _TIE_dmx1a_common_tie_load8x4_vr_idxI
#define load8x4_vr_postR _TIE_dmx1a_common_tie_load8x4_vr_postR
#define load8x4_vr_postI _TIE_dmx1a_common_tie_load8x4_vr_postI
#define load8x4_vr_circI _TIE_dmx1a_common_tie_load8x4_vr_circI
#define load8x2_vr_idxR _TIE_dmx1a_common_tie_load8x2_vr_idxR
#define load8x2_vr_idxI _TIE_dmx1a_common_tie_load8x2_vr_idxI
#define load8x2_vr_postR _TIE_dmx1a_common_tie_load8x2_vr_postR
#define load8x2_vr_postI _TIE_dmx1a_common_tie_load8x2_vr_postI
#define load8x2_vr_circI _TIE_dmx1a_common_tie_load8x2_vr_circI
#define load8x1_vr_idxR _TIE_dmx1a_common_tie_load8x1_vr_idxR
#define load8x1_vr_idxI _TIE_dmx1a_common_tie_load8x1_vr_idxI
#define load8x1_vr_postR _TIE_dmx1a_common_tie_load8x1_vr_postR
#define load8x1_vr_postI _TIE_dmx1a_common_tie_load8x1_vr_postI
#define load8x1_vr_circI _TIE_dmx1a_common_tie_load8x1_vr_circI
#define align_32x4_load _TIE_dmx1a_common_tie_align_32x4_load
#define align_24x4_load _TIE_dmx1a_common_tie_align_24x4_load
#define align_16x4_load _TIE_dmx1a_common_tie_align_16x4_load
#define align_8x4_load _TIE_dmx1a_common_tie_align_8x4_load
#define load_32x4_vr_a _TIE_dmx1a_common_tie_load_32x4_vr_a
#define load_24x4_vr_a _TIE_dmx1a_common_tie_load_24x4_vr_a
#define load_16x4_vr_a _TIE_dmx1a_common_tie_load_16x4_vr_a
#define load_8x4_vr_a _TIE_dmx1a_common_tie_load_8x4_vr_a
#define load_32x4_vr_a_circ _TIE_dmx1a_common_tie_load_32x4_vr_a_circ
#define load32x2_wr_idxR _TIE_dmx1a_common_tie_load32x2_wr_idxR
#define load32x2_wr_idxI _TIE_dmx1a_common_tie_load32x2_wr_idxI
#define load32x2_wr_postR _TIE_dmx1a_common_tie_load32x2_wr_postR
#define load32x2_wr_postI _TIE_dmx1a_common_tie_load32x2_wr_postI
#define store32x4_vr_idxR _TIE_dmx1a_common_tie_store32x4_vr_idxR
#define store32x4_vr_idxI _TIE_dmx1a_common_tie_store32x4_vr_idxI
#define store32x4_vr_postR _TIE_dmx1a_common_tie_store32x4_vr_postR
#define store32x4_vr_postI _TIE_dmx1a_common_tie_store32x4_vr_postI
#define store32x4_vr_circI _TIE_dmx1a_common_tie_store32x4_vr_circI
#define store32x2_vr_idxR _TIE_dmx1a_common_tie_store32x2_vr_idxR
#define store32x2_vr_idxI _TIE_dmx1a_common_tie_store32x2_vr_idxI
#define store32x2_vr_postR _TIE_dmx1a_common_tie_store32x2_vr_postR
#define store32x2_vr_postI _TIE_dmx1a_common_tie_store32x2_vr_postI
#define store32x2_vr_circI _TIE_dmx1a_common_tie_store32x2_vr_circI
#define store32x1_vr_idxR _TIE_dmx1a_common_tie_store32x1_vr_idxR
#define store32x1_vr_idxI _TIE_dmx1a_common_tie_store32x1_vr_idxI
#define store32x1_vr_postR _TIE_dmx1a_common_tie_store32x1_vr_postR
#define store32x1_vr_postI _TIE_dmx1a_common_tie_store32x1_vr_postI
#define store32x1_vr_circI _TIE_dmx1a_common_tie_store32x1_vr_circI
#define store32x4_vr_br_idxR _TIE_dmx1a_common_tie_store32x4_vr_br_idxR
#define store32x4_vr_br_idxI _TIE_dmx1a_common_tie_store32x4_vr_br_idxI
#define store32x4_vr_br_postR _TIE_dmx1a_common_tie_store32x4_vr_br_postR
#define store32x4_vr_br_postI _TIE_dmx1a_common_tie_store32x4_vr_br_postI
#define store32x4_vr_br_circI _TIE_dmx1a_common_tie_store32x4_vr_br_circI
#define store32x2_vr_br_idxR _TIE_dmx1a_common_tie_store32x2_vr_br_idxR
#define store32x2_vr_br_idxI _TIE_dmx1a_common_tie_store32x2_vr_br_idxI
#define store32x2_vr_br_postR _TIE_dmx1a_common_tie_store32x2_vr_br_postR
#define store32x2_vr_br_postI _TIE_dmx1a_common_tie_store32x2_vr_br_postI
#define store32x2_vr_br_circI _TIE_dmx1a_common_tie_store32x2_vr_br_circI
#define store32x1_vr_br_idxR _TIE_dmx1a_common_tie_store32x1_vr_br_idxR
#define store32x1_vr_br_idxI _TIE_dmx1a_common_tie_store32x1_vr_br_idxI
#define store32x1_vr_br_postR _TIE_dmx1a_common_tie_store32x1_vr_br_postR
#define store32x1_vr_br_postI _TIE_dmx1a_common_tie_store32x1_vr_br_postI
#define store32x1_vr_br_circI _TIE_dmx1a_common_tie_store32x1_vr_br_circI
#define store32x4_vr_vr_idxR_perm _TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm
#define store32x4_vr_vr_idxI_perm _TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm
#define store32x4_vr_vr_postR_perm _TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm
#define store32x4_vr_vr_postI_perm _TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm
#define store32x4_vr_vr_circI_perm _TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm
#define store16x4_vr_idxR _TIE_dmx1a_common_tie_store16x4_vr_idxR
#define store16x4_vr_idxI _TIE_dmx1a_common_tie_store16x4_vr_idxI
#define store16x4_vr_postR _TIE_dmx1a_common_tie_store16x4_vr_postR
#define store16x4_vr_postI _TIE_dmx1a_common_tie_store16x4_vr_postI
#define store16x4_vr_circI _TIE_dmx1a_common_tie_store16x4_vr_circI
#define store16x2_vr_idxR _TIE_dmx1a_common_tie_store16x2_vr_idxR
#define store16x2_vr_idxI _TIE_dmx1a_common_tie_store16x2_vr_idxI
#define store16x2_vr_postR _TIE_dmx1a_common_tie_store16x2_vr_postR
#define store16x2_vr_postI _TIE_dmx1a_common_tie_store16x2_vr_postI
#define store16x2_vr_circI _TIE_dmx1a_common_tie_store16x2_vr_circI
#define store16x1_vr_idxR _TIE_dmx1a_common_tie_store16x1_vr_idxR
#define store16x1_vr_idxI _TIE_dmx1a_common_tie_store16x1_vr_idxI
#define store16x1_vr_postR _TIE_dmx1a_common_tie_store16x1_vr_postR
#define store16x1_vr_postI _TIE_dmx1a_common_tie_store16x1_vr_postI
#define store16x1_vr_circI _TIE_dmx1a_common_tie_store16x1_vr_circI
#define store8x4_vr_idxR _TIE_dmx1a_common_tie_store8x4_vr_idxR
#define store8x4_vr_idxI _TIE_dmx1a_common_tie_store8x4_vr_idxI
#define store8x4_vr_postR _TIE_dmx1a_common_tie_store8x4_vr_postR
#define store8x4_vr_postI _TIE_dmx1a_common_tie_store8x4_vr_postI
#define store8x4_vr_circI _TIE_dmx1a_common_tie_store8x4_vr_circI
#define store8x2_vr_idxR _TIE_dmx1a_common_tie_store8x2_vr_idxR
#define store8x2_vr_idxI _TIE_dmx1a_common_tie_store8x2_vr_idxI
#define store8x2_vr_postR _TIE_dmx1a_common_tie_store8x2_vr_postR
#define store8x2_vr_postI _TIE_dmx1a_common_tie_store8x2_vr_postI
#define store8x2_vr_circI _TIE_dmx1a_common_tie_store8x2_vr_circI
#define store8x1_vr_idxR _TIE_dmx1a_common_tie_store8x1_vr_idxR
#define store8x1_vr_idxI _TIE_dmx1a_common_tie_store8x1_vr_idxI
#define store8x1_vr_postR _TIE_dmx1a_common_tie_store8x1_vr_postR
#define store8x1_vr_postI _TIE_dmx1a_common_tie_store8x1_vr_postI
#define store8x1_vr_circI _TIE_dmx1a_common_tie_store8x1_vr_circI
#define align_32x4_store _TIE_dmx1a_common_tie_align_32x4_store
#define align_16x4_store _TIE_dmx1a_common_tie_align_16x4_store
#define align_8x4_store _TIE_dmx1a_common_tie_align_8x4_store
#define store_32x4_vr_a _TIE_dmx1a_common_tie_store_32x4_vr_a
#define store_24x4_vr_a _TIE_dmx1a_common_tie_store_24x4_vr_a
#define store_16x4_vr_a _TIE_dmx1a_common_tie_store_16x4_vr_a
#define store_8x4_vr_a _TIE_dmx1a_common_tie_store_8x4_vr_a
#define store_32x4_vr_a_circ _TIE_dmx1a_common_tie_store_32x4_vr_a_circ
#define flush_32x4 _TIE_dmx1a_common_tie_flush_32x4
#define flush_24x4 _TIE_dmx1a_common_tie_flush_24x4
#define flush_16x4 _TIE_dmx1a_common_tie_flush_16x4
#define flush_8x4 _TIE_dmx1a_common_tie_flush_8x4
#define br_get_idx_2_5 _TIE_dmx1a_common_tie_br_get_idx_2_5
#define br_get_idx_6_13 _TIE_dmx1a_common_tie_br_get_idx_6_13
#define br_get_idx_next_odd _TIE_dmx1a_common_tie_br_get_idx_next_odd
#define br_upd_idx_spec _TIE_dmx1a_common_tie_br_upd_idx_spec
#define build_palindrome _TIE_dmx1a_common_tie_build_palindrome
#define load_vr_bdir _TIE_dmx1a_common_tie_load_vr_bdir
#define load_vr_brev _TIE_dmx1a_common_tie_load_vr_brev
#define store_vrl_wr_bdir _TIE_dmx1a_common_tie_store_vrl_wr_bdir
#define store_vrh_wr_bdir _TIE_dmx1a_common_tie_store_vrh_wr_bdir
#define store_vrl_wr_brev _TIE_dmx1a_common_tie_store_vrl_wr_brev
#define store_vrh_wr_brev _TIE_dmx1a_common_tie_store_vrh_wr_brev
#define store_vrl_vrl_postR _TIE_dmx1a_common_tie_store_vrl_vrl_postR
#define store_vrh_vrh_postR _TIE_dmx1a_common_tie_store_vrh_vrh_postR
#define store_vrl_wr_postR _TIE_dmx1a_common_tie_store_vrl_wr_postR
#define store_wr_vrl_postR _TIE_dmx1a_common_tie_store_wr_vrl_postR
#define store_vrh_wr_postR _TIE_dmx1a_common_tie_store_vrh_wr_postR
#define store_wr_vrh_postR _TIE_dmx1a_common_tie_store_wr_vrh_postR
#define load_fr_postI _TIE_dmx1a_common_tie_load_fr_postI
#define store_fr_postI _TIE_dmx1a_common_tie_store_fr_postI
#define move32_wr_vr _TIE_dmx1a_common_tie_move32_wr_vr
#define move32_wr_fr _TIE_dmx1a_common_tie_move32_wr_fr
#define move64_wr_vr _TIE_dmx1a_common_tie_move64_wr_vr
#define move64_vr_wr _TIE_dmx1a_common_tie_move64_vr_wr
#define move32_ar_vr _TIE_dmx1a_common_tie_move32_ar_vr
#define move32_ar_vr_idx _TIE_dmx1a_common_tie_move32_ar_vr_idx
#define move32_fr_vr_idx _TIE_dmx1a_common_tie_move32_fr_vr_idx
#define int_to_xt_bool _TIE_dmx1a_common_tie_int_to_xt_bool
#define int_to_xt_bool2 _TIE_dmx1a_common_tie_int_to_xt_bool2
#define int_to_xt_bool4 _TIE_dmx1a_common_tie_int_to_xt_bool4
#define move_vr_eqz _TIE_dmx1a_common_tie_move_vr_eqz
#define move_vr_gez _TIE_dmx1a_common_tie_move_vr_gez
#define move_vr_gtz _TIE_dmx1a_common_tie_move_vr_gtz
#define move_vr_lez _TIE_dmx1a_common_tie_move_vr_lez
#define move_vr_ltz _TIE_dmx1a_common_tie_move_vr_ltz
#define move_vr_nez _TIE_dmx1a_common_tie_move_vr_nez
#define move_vr_sat _TIE_dmx1a_common_tie_move_vr_sat
#define vmove_vr_eqz _TIE_dmx1a_common_tie_vmove_vr_eqz
#define vmove_vr_gez _TIE_dmx1a_common_tie_vmove_vr_gez
#define vmove_vr_gtz _TIE_dmx1a_common_tie_vmove_vr_gtz
#define vmove_vr_lez _TIE_dmx1a_common_tie_vmove_vr_lez
#define vmove_vr_ltz _TIE_dmx1a_common_tie_vmove_vr_ltz
#define vmove_vr_nez _TIE_dmx1a_common_tie_vmove_vr_nez
#define vmove_vr_sat _TIE_dmx1a_common_tie_vmove_vr_sat
#define replicate _TIE_dmx1a_common_tie_replicate
#define replicate_ar _TIE_dmx1a_common_tie_replicate_ar
#define creplicate_H _TIE_dmx1a_common_tie_creplicate_H
#define creplicate_L _TIE_dmx1a_common_tie_creplicate_L
#define vreplicate _TIE_dmx1a_common_tie_vreplicate
#define vreplicate_fr _TIE_dmx1a_common_tie_vreplicate_fr
#define vreplicate_hr _TIE_dmx1a_common_tie_vreplicate_hr
#define hreplicate_fr _TIE_dmx1a_common_tie_hreplicate_fr
#define convert_16I_to_32F_x1 _TIE_dmx1a_common_tie_convert_16I_to_32F_x1
#define convert_16I_to_32F_x2 _TIE_dmx1a_common_tie_convert_16I_to_32F_x2
#define convert_16I_to_32F_x4 _TIE_dmx1a_common_tie_convert_16I_to_32F_x4
#define convert_32F_to_16I_x1 _TIE_dmx1a_common_tie_convert_32F_to_16I_x1
#define convert_32F_to_16I_x2 _TIE_dmx1a_common_tie_convert_32F_to_16I_x2
#define convert_32F_to_16I_x4 _TIE_dmx1a_common_tie_convert_32F_to_16I_x4
#define convert_32F_to_16F_x1 _TIE_dmx1a_common_tie_convert_32F_to_16F_x1
#define convert_32F_to_16F_x2 _TIE_dmx1a_common_tie_convert_32F_to_16F_x2
#define convert_32F_to_16F_x4 _TIE_dmx1a_common_tie_convert_32F_to_16F_x4
#define convert_16F_to_32F_x1 _TIE_dmx1a_common_tie_convert_16F_to_32F_x1
#define convert_16F_to_32F_x2 _TIE_dmx1a_common_tie_convert_16F_to_32F_x2
#define convert_16F_to_32F_x4 _TIE_dmx1a_common_tie_convert_16F_to_32F_x4
#define convert_32I_to_32F_x1 _TIE_dmx1a_common_tie_convert_32I_to_32F_x1
#define convert_32F_to_32I_x1 _TIE_dmx1a_common_tie_convert_32F_to_32I_x1
#define convert_IEEE_float_to_32F_x4 _TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4
#define convert_32F_to_IEEE_float_x4 _TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4
#define convert_IEEE_float_to_32F _TIE_dmx1a_common_tie_convert_IEEE_float_to_32F
#define convert_32F_to_IEEE_float _TIE_dmx1a_common_tie_convert_32F_to_IEEE_float
#define convert_32I_to_64F _TIE_dmx1a_common_tie_convert_32I_to_64F
#define convert_64F_to_32I _TIE_dmx1a_common_tie_convert_64F_to_32I
#define convert_32F_to_64F _TIE_dmx1a_common_tie_convert_32F_to_64F
#define convert_64F_to_32F _TIE_dmx1a_common_tie_convert_64F_to_32F
#define convert_IEEE_double_to_64F _TIE_dmx1a_common_tie_convert_IEEE_double_to_64F
#define convert_64F_to_IEEE_double _TIE_dmx1a_common_tie_convert_64F_to_IEEE_double
#define affine_adj_L _TIE_dmx1a_common_tie_affine_adj_L
#define affine_adj_H _TIE_dmx1a_common_tie_affine_adj_H
#define affine_perm_L _TIE_dmx1a_common_tie_affine_perm_L
#define affine_perm_H _TIE_dmx1a_common_tie_affine_perm_H
#define linear_adj_L _TIE_dmx1a_common_tie_linear_adj_L
#define linear_adj_H _TIE_dmx1a_common_tie_linear_adj_H
#define linear_perm_L _TIE_dmx1a_common_tie_linear_perm_L
#define linear_perm_H _TIE_dmx1a_common_tie_linear_perm_H
#define bfly_z_yl_xl_wr _TIE_dmx1a_common_tie_bfly_z_yl_xl_wr
#define bfly_z_yl_xh_wr _TIE_dmx1a_common_tie_bfly_z_yl_xh_wr
#define bfly_z_yh_xl_wr _TIE_dmx1a_common_tie_bfly_z_yh_xl_wr
#define bfly_z_yh_xh_wr _TIE_dmx1a_common_tie_bfly_z_yh_xh_wr
#define bfly_z_wr_xl_yl _TIE_dmx1a_common_tie_bfly_z_wr_xl_yl
#define bfly_z_wr_xh_yl _TIE_dmx1a_common_tie_bfly_z_wr_xh_yl
#define bfly_z_wr_xl_yh _TIE_dmx1a_common_tie_bfly_z_wr_xl_yh
#define bfly_z_wr_xh_yh _TIE_dmx1a_common_tie_bfly_z_wr_xh_yh
#define bfly_zl_zl_xl_yl _TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl
#define bfly_zl_zl_xh_yl _TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl
#define bfly_zh_zh_xl_yh _TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh
#define bfly_zh_zh_xh_yh _TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh
#define bfly_wr_zl_xl_yl _TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl
#define bfly_wr_zl_xh_yl _TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl
#define bfly_wr_zh_xl_yh _TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh
#define bfly_wr_zh_xh_yh _TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh
#define cmul _TIE_dmx1a_common_tie_cmul
#define cmul_conj _TIE_dmx1a_common_tie_cmul_conj
#define cmac _TIE_dmx1a_common_tie_cmac
#define cmac_conj _TIE_dmx1a_common_tie_cmac_conj
#define cmas _TIE_dmx1a_common_tie_cmas
#define cmas_conj _TIE_dmx1a_common_tie_cmas_conj
#define cmul_L _TIE_dmx1a_common_tie_cmul_L
#define cmul_H _TIE_dmx1a_common_tie_cmul_H
#define cmac_L _TIE_dmx1a_common_tie_cmac_L
#define cmac_H _TIE_dmx1a_common_tie_cmac_H
#define cmas_L _TIE_dmx1a_common_tie_cmas_L
#define cmas_H _TIE_dmx1a_common_tie_cmas_H
#define cmac_Lx2 _TIE_dmx1a_common_tie_cmac_Lx2
#define cmac_Hx2 _TIE_dmx1a_common_tie_cmac_Hx2
#define cmul_x2 _TIE_dmx1a_common_tie_cmul_x2
#define cmac_adj_x2 _TIE_dmx1a_common_tie_cmac_adj_x2
#define cmas_adj_x2 _TIE_dmx1a_common_tie_cmas_adj_x2
#define xcorr _TIE_dmx1a_common_tie_xcorr
#define xconv _TIE_dmx1a_common_tie_xconv
#define qmul_1 _TIE_dmx1a_common_tie_qmul_1
#define qmul_2 _TIE_dmx1a_common_tie_qmul_2
#define matmul_2x2 _TIE_dmx1a_common_tie_matmul_2x2
#define vadds _TIE_dmx1a_common_tie_vadds
#define vmidp _TIE_dmx1a_common_tie_vmidp
#define vmuls _TIE_dmx1a_common_tie_vmuls
#define vmacs_adj _TIE_dmx1a_common_tie_vmacs_adj
#define vmuls_perm _TIE_dmx1a_common_tie_vmuls_perm
#define vmacs_perm _TIE_dmx1a_common_tie_vmacs_perm
#define vssub_L _TIE_dmx1a_common_tie_vssub_L
#define vssub_H _TIE_dmx1a_common_tie_vssub_H
#define vssub_x2 _TIE_dmx1a_common_tie_vssub_x2
#define vinterp_L _TIE_dmx1a_common_tie_vinterp_L
#define vinterp_H _TIE_dmx1a_common_tie_vinterp_H
#define vinterp_x2 _TIE_dmx1a_common_tie_vinterp_x2
#define csums_L _TIE_dmx1a_common_tie_csums_L
#define csums_H _TIE_dmx1a_common_tie_csums_H
#define dsums_L _TIE_dmx1a_common_tie_dsums_L
#define dsums_H _TIE_dmx1a_common_tie_dsums_H
#define vadd_hr _TIE_dmx1a_common_tie_vadd_hr
#define vsub_hr _TIE_dmx1a_common_tie_vsub_hr
#define vmul_hr _TIE_dmx1a_common_tie_vmul_hr
#define vmac_hr _TIE_dmx1a_common_tie_vmac_hr
#define fpadd _TIE_dmx1a_common_tie_fpadd
#define fpmul _TIE_dmx1a_common_tie_fpmul
#define fpmac _TIE_dmx1a_common_tie_fpmac
#define fpmul_sum3 _TIE_dmx1a_common_tie_fpmul_sum3
#define vscale _TIE_dmx1a_common_tie_vscale
#define vscale_adds _TIE_dmx1a_common_tie_vscale_adds
#define fadds _TIE_dmx1a_common_tie_fadds
#define fmacs _TIE_dmx1a_common_tie_fmacs
#define fmuls _TIE_dmx1a_common_tie_fmuls
#define fmul_sum3 _TIE_dmx1a_common_tie_fmul_sum3
#define dadds _TIE_dmx1a_common_tie_dadds
#define dmuls _TIE_dmx1a_common_tie_dmuls
#define dmacs _TIE_dmx1a_common_tie_dmacs
#define vabs _TIE_dmx1a_common_tie_vabs
#define vexp_adj _TIE_dmx1a_common_tie_vexp_adj
#define vexp_adji _TIE_dmx1a_common_tie_vexp_adji
#define vperm _TIE_dmx1a_common_tie_vperm
#define vperms _TIE_dmx1a_common_tie_vperms
#define vpermsi _TIE_dmx1a_common_tie_vpermsi
#define seta_vr _TIE_dmx1a_common_tie_seta_vr
#define vseta_vr _TIE_dmx1a_common_tie_vseta_vr
#define seta_ar _TIE_dmx1a_common_tie_seta_ar
#define seta_fr _TIE_dmx1a_common_tie_seta_fr
#define f_abs _TIE_dmx1a_common_tie_f_abs
#define fclamp _TIE_dmx1a_common_tie_fclamp
#define fclamp_bp _TIE_dmx1a_common_tie_fclamp_bp
#define fclamp_one _TIE_dmx1a_common_tie_fclamp_one
#define fmax _TIE_dmx1a_common_tie_fmax
#define fmin _TIE_dmx1a_common_tie_fmin
#define max_fr _TIE_dmx1a_common_tie_max_fr
#define min_fr _TIE_dmx1a_common_tie_min_fr
#define log2 _TIE_dmx1a_common_tie_log2
#define pow2 _TIE_dmx1a_common_tie_pow2
#define sigmoid _TIE_dmx1a_common_tie_sigmoid
#define inv _TIE_dmx1a_common_tie_inv
#define ratio _TIE_dmx1a_common_tie_ratio
#define atanratio _TIE_dmx1a_common_tie_atanratio
#define invsqrt _TIE_dmx1a_common_tie_invsqrt
#define sine _TIE_dmx1a_common_tie_sine
#define cosine _TIE_dmx1a_common_tie_cosine
#define log2mul _TIE_dmx1a_common_tie_log2mul
#define cspow2 _TIE_dmx1a_common_tie_cspow2
#define log2_fr _TIE_dmx1a_common_tie_log2_fr
#define pow2_fr _TIE_dmx1a_common_tie_pow2_fr
#define sigmoid_fr _TIE_dmx1a_common_tie_sigmoid_fr
#define inv_fr _TIE_dmx1a_common_tie_inv_fr
#define invsqrt_fr _TIE_dmx1a_common_tie_invsqrt_fr
#define sine_fr _TIE_dmx1a_common_tie_sine_fr
#define cosine_fr _TIE_dmx1a_common_tie_cosine_fr
#define comp _TIE_dmx1a_common_tie_comp
#define eq _TIE_dmx1a_common_tie_eq
#define ge _TIE_dmx1a_common_tie_ge
#define gt _TIE_dmx1a_common_tie_gt
#define le _TIE_dmx1a_common_tie_le
#define lt _TIE_dmx1a_common_tie_lt
#define ne _TIE_dmx1a_common_tie_ne
#define comp_const _TIE_dmx1a_common_tie_comp_const
#define eq_const _TIE_dmx1a_common_tie_eq_const
#define ge_const _TIE_dmx1a_common_tie_ge_const
#define gt_const _TIE_dmx1a_common_tie_gt_const
#define le_const _TIE_dmx1a_common_tie_le_const
#define lt_const _TIE_dmx1a_common_tie_lt_const
#define ne_const _TIE_dmx1a_common_tie_ne_const
#define eq_fr _TIE_dmx1a_common_tie_eq_fr
#define ge_fr _TIE_dmx1a_common_tie_ge_fr
#define gt_fr _TIE_dmx1a_common_tie_gt_fr
#define le_fr _TIE_dmx1a_common_tie_le_fr
#define lt_fr _TIE_dmx1a_common_tie_lt_fr
#define ne_fr _TIE_dmx1a_common_tie_ne_fr
#define neg_fr _TIE_dmx1a_common_tie_neg_fr
#define abs_fr _TIE_dmx1a_common_tie_abs_fr
#define deqz _TIE_dmx1a_common_tie_deqz
#define dgez _TIE_dmx1a_common_tie_dgez
#define dgtz _TIE_dmx1a_common_tie_dgtz
#define dlez _TIE_dmx1a_common_tie_dlez
#define dltz _TIE_dmx1a_common_tie_dltz
#define dnez _TIE_dmx1a_common_tie_dnez
#define veq _TIE_dmx1a_common_tie_veq
#define vge _TIE_dmx1a_common_tie_vge
#define vgt _TIE_dmx1a_common_tie_vgt
#define vle _TIE_dmx1a_common_tie_vle
#define vlt _TIE_dmx1a_common_tie_vlt
#define vne _TIE_dmx1a_common_tie_vne
#define veq_const _TIE_dmx1a_common_tie_veq_const
#define vge_const _TIE_dmx1a_common_tie_vge_const
#define vgt_const _TIE_dmx1a_common_tie_vgt_const
#define vle_const _TIE_dmx1a_common_tie_vle_const
#define vlt_const _TIE_dmx1a_common_tie_vlt_const
#define vne_const _TIE_dmx1a_common_tie_vne_const
#define sel _TIE_dmx1a_common_tie_sel
#define sel_1b4 _TIE_dmx1a_common_tie_sel_1b4
#define sel_eq _TIE_dmx1a_common_tie_sel_eq
#define sel_ge _TIE_dmx1a_common_tie_sel_ge
#define sel_gt _TIE_dmx1a_common_tie_sel_gt
#define sel_le _TIE_dmx1a_common_tie_sel_le
#define sel_lt _TIE_dmx1a_common_tie_sel_lt
#define sel_ne _TIE_dmx1a_common_tie_sel_ne
#define vsel _TIE_dmx1a_common_tie_vsel
#define andb1 _TIE_dmx1a_common_tie_andb1
#define andbc1 _TIE_dmx1a_common_tie_andbc1
#define orb1 _TIE_dmx1a_common_tie_orb1
#define orbc1 _TIE_dmx1a_common_tie_orbc1
#define xorb1 _TIE_dmx1a_common_tie_xorb1
#define andb4 _TIE_dmx1a_common_tie_andb4
#define andbc4 _TIE_dmx1a_common_tie_andbc4
#define orb4 _TIE_dmx1a_common_tie_orb4
#define orbc4 _TIE_dmx1a_common_tie_orbc4
#define xorb4 _TIE_dmx1a_common_tie_xorb4
#define bcount0_maskI _TIE_dmx1a_common_tie_bcount0_maskI
#define bcount0_maskR _TIE_dmx1a_common_tie_bcount0_maskR
#define bcount1_maskI _TIE_dmx1a_common_tie_bcount1_maskI
#define bcount1_maskR _TIE_dmx1a_common_tie_bcount1_maskR
#define bfirst0_maskI _TIE_dmx1a_common_tie_bfirst0_maskI
#define bfirst0_maskR _TIE_dmx1a_common_tie_bfirst0_maskR
#define bfirst1_maskI _TIE_dmx1a_common_tie_bfirst1_maskI
#define bfirst1_maskR _TIE_dmx1a_common_tie_bfirst1_maskR
#define blast0_maskI _TIE_dmx1a_common_tie_blast0_maskI
#define blast0_maskR _TIE_dmx1a_common_tie_blast0_maskR
#define blast1_maskI _TIE_dmx1a_common_tie_blast1_maskI
#define blast1_maskR _TIE_dmx1a_common_tie_blast1_maskR
#define bgetI _TIE_dmx1a_common_tie_bgetI
#define bgetR _TIE_dmx1a_common_tie_bgetR
#define bsetI _TIE_dmx1a_common_tie_bsetI
#define bsetR _TIE_dmx1a_common_tie_bsetR
#define exp_adj _TIE_dmx1a_common_tie_exp_adj
#define exp_adji _TIE_dmx1a_common_tie_exp_adji
#define exp_adj_fr _TIE_dmx1a_common_tie_exp_adj_fr
#define exp_adji_fr _TIE_dmx1a_common_tie_exp_adji_fr
#define s_neg _TIE_dmx1a_common_tie_s_neg
#define s_copy _TIE_dmx1a_common_tie_s_copy
#define s_and _TIE_dmx1a_common_tie_s_and
#define s_andc _TIE_dmx1a_common_tie_s_andc
#define s_or _TIE_dmx1a_common_tie_s_or
#define s_orc _TIE_dmx1a_common_tie_s_orc
#define s_xor _TIE_dmx1a_common_tie_s_xor
#define s_vnegs _TIE_dmx1a_common_tie_s_vnegs
#define s_vcopy _TIE_dmx1a_common_tie_s_vcopy
#define s_vand _TIE_dmx1a_common_tie_s_vand
#define s_vandc _TIE_dmx1a_common_tie_s_vandc
#define s_vor _TIE_dmx1a_common_tie_s_vor
#define s_vorc _TIE_dmx1a_common_tie_s_vorc
#define s_vxor _TIE_dmx1a_common_tie_s_vxor
#define s_vnegs_hr _TIE_dmx1a_common_tie_s_vnegs_hr
#define floorp_frac _TIE_dmx1a_common_tie_floorp_frac
#define idx_frac _TIE_dmx1a_common_tie_idx_frac
#define truncate_fr _TIE_dmx1a_common_tie_truncate_fr
#define rmax_idx _TIE_dmx1a_common_tie_rmax_idx
#define rmin_idx _TIE_dmx1a_common_tie_rmin_idx
#define vmaxmin_init _TIE_dmx1a_common_tie_vmaxmin_init
#define vmax_idx _TIE_dmx1a_common_tie_vmax_idx
#define vmin_idx _TIE_dmx1a_common_tie_vmin_idx
#define vmax _TIE_dmx1a_common_tie_vmax
#define vmin _TIE_dmx1a_common_tie_vmin
#define sortupd_asc_vr _TIE_dmx1a_common_tie_sortupd_asc_vr
#define sortupd_des_vr _TIE_dmx1a_common_tie_sortupd_des_vr
#define sortupd_asc_ar _TIE_dmx1a_common_tie_sortupd_asc_ar
#define sortupd_des_ar _TIE_dmx1a_common_tie_sortupd_des_ar
#define vbool _TIE_dmx1a_common_tie_vbool
#define align_up _TIE_dmx1a_common_tie_align_up
#define range_init _TIE_dmx1a_common_tie_range_init
#define range_check _TIE_dmx1a_common_tie_range_check
#define afloat_exp_extract _TIE_dmx1a_common_tie_afloat_exp_extract
#define exp_shift_amount _TIE_dmx1a_common_tie_exp_shift_amount
#define flush_32x4_bounded _TIE_dmx1a_common_tie_flush_32x4_bounded
#define load_AccExtend_postI _TIE_dmx1a_common_tie_load_AccExtend_postI
#define load_BB0_flex _TIE_dmx1a_common_tie_load_BB0_flex
#define load_BB1_flex _TIE_dmx1a_common_tie_load_BB1_flex
#define load_BB2_flex _TIE_dmx1a_common_tie_load_BB2_flex
#define load_BB3_flex _TIE_dmx1a_common_tie_load_BB3_flex
#define load_BB4_flex _TIE_dmx1a_common_tie_load_BB4_flex
#define load_BB5_flex _TIE_dmx1a_common_tie_load_BB5_flex
#define load_BB6_flex _TIE_dmx1a_common_tie_load_BB6_flex
#define load_BB7_flex _TIE_dmx1a_common_tie_load_BB7_flex
#define load_BB0_postI _TIE_dmx1a_common_tie_load_BB0_postI
#define load_BB1_postI _TIE_dmx1a_common_tie_load_BB1_postI
#define load_BB2_postI _TIE_dmx1a_common_tie_load_BB2_postI
#define load_BB3_postI _TIE_dmx1a_common_tie_load_BB3_postI
#define load_BB4_postI _TIE_dmx1a_common_tie_load_BB4_postI
#define load_BB5_postI _TIE_dmx1a_common_tie_load_BB5_postI
#define load_BB6_postI _TIE_dmx1a_common_tie_load_BB6_postI
#define load_BB7_postI _TIE_dmx1a_common_tie_load_BB7_postI
#define load_BBx_a_bounded _TIE_dmx1a_common_tie_load_BBx_a_bounded
#define load_VB1_postI _TIE_dmx1a_common_tie_load_VB1_postI
#define load_VB2_postI _TIE_dmx1a_common_tie_load_VB2_postI
#define load_VB3_postI _TIE_dmx1a_common_tie_load_VB3_postI
#define load_VB4_postI _TIE_dmx1a_common_tie_load_VB4_postI
#define load_VB5_postI _TIE_dmx1a_common_tie_load_VB5_postI
#define load_VB6_postI _TIE_dmx1a_common_tie_load_VB6_postI
#define load_VB7_postI _TIE_dmx1a_common_tie_load_VB7_postI
#define load_32x4_vr_a_bounded _TIE_dmx1a_common_tie_load_32x4_vr_a_bounded
#define load_lookup_AccExtend_postI _TIE_dmx1a_common_tie_load_lookup_AccExtend_postI
#define load_lookup_vr_postI _TIE_dmx1a_common_tie_load_lookup_vr_postI
#define load32x1_lookup_AccExtend_idx16vr _TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr
#define load32x1_lookup_vr_idx16vr _TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr
#define load32x1_vr_idx16vr _TIE_dmx1a_common_tie_load32x1_vr_idx16vr
#define mac8bx8b _TIE_dmx1a_common_tie_mac8bx8b
#define mac8bx8b_conv _TIE_dmx1a_common_tie_mac8bx8b_conv
#define mac8bx8b_sparse _TIE_dmx1a_common_tie_mac8bx8b_sparse
#define mir_init _TIE_dmx1a_common_tie_mir_init
#define mov_AccExtend_vr _TIE_dmx1a_common_tie_mov_AccExtend_vr
#define mov_BB_vrVB _TIE_dmx1a_common_tie_mov_BB_vrVB
#define mov_vr_AccExtend _TIE_dmx1a_common_tie_mov_vr_AccExtend
#define mov_vrVB_BB _TIE_dmx1a_common_tie_mov_vrVB_BB
#define next_lookup_load _TIE_dmx1a_common_tie_next_lookup_load
#define next_lookup_store _TIE_dmx1a_common_tie_next_lookup_store
#define precess_16bits _TIE_dmx1a_common_tie_precess_16bits
#define rectify32_into8 _TIE_dmx1a_common_tie_rectify32_into8
#define rnd_sat_pack _TIE_dmx1a_common_tie_rnd_sat_pack
#define set_BB_zero _TIE_dmx1a_common_tie_set_BB_zero
#define shift8_into32_arith _TIE_dmx1a_common_tie_shift8_into32_arith
#define shift32_arith _TIE_dmx1a_common_tie_shift32_arith
#define store_32x4_vr_a_bounded _TIE_dmx1a_common_tie_store_32x4_vr_a_bounded
#define store_AccExtend_postI _TIE_dmx1a_common_tie_store_AccExtend_postI
#define store_BB0_postI _TIE_dmx1a_common_tie_store_BB0_postI
#define store_BB1_postI _TIE_dmx1a_common_tie_store_BB1_postI
#define store_BB2_postI _TIE_dmx1a_common_tie_store_BB2_postI
#define store_BB3_postI _TIE_dmx1a_common_tie_store_BB3_postI
#define store_BB4_postI _TIE_dmx1a_common_tie_store_BB4_postI
#define store_BB5_postI _TIE_dmx1a_common_tie_store_BB5_postI
#define store_BB6_postI _TIE_dmx1a_common_tie_store_BB6_postI
#define store_BB7_postI _TIE_dmx1a_common_tie_store_BB7_postI
#define store_VB1_postI _TIE_dmx1a_common_tie_store_VB1_postI
#define store_VB2_postI _TIE_dmx1a_common_tie_store_VB2_postI
#define store_VB3_postI _TIE_dmx1a_common_tie_store_VB3_postI
#define store_VB4_postI _TIE_dmx1a_common_tie_store_VB4_postI
#define store_VB5_postI _TIE_dmx1a_common_tie_store_VB5_postI
#define store_VB6_postI _TIE_dmx1a_common_tie_store_VB6_postI
#define store_VB7_postI _TIE_dmx1a_common_tie_store_VB7_postI
#define store_lookup_AccExtend_postI _TIE_dmx1a_common_tie_store_lookup_AccExtend_postI
#define store_lookup_vr_postI _TIE_dmx1a_common_tie_store_lookup_vr_postI
#define mv_WR _TIE_dmx1a_common_tie_mv_WR
#define mv_PERM _TIE_dmx1a_common_tie_mv_PERM
#define mv_MIR _TIE_dmx1a_common_tie_mv_MIR
#define mv_ULSR _TIE_dmx1a_common_tie_mv_ULSR
#define mv_CR _TIE_dmx1a_common_tie_mv_CR
#define ld_FR _TIE_dmx1a_common_tie_ld_FR
#define st_FR _TIE_dmx1a_common_tie_st_FR
#define ld_FR_idxR _TIE_dmx1a_common_tie_ld_FR_idxR
#define st_FR_idxR _TIE_dmx1a_common_tie_st_FR_idxR
#define ld_FR_postI _TIE_dmx1a_common_tie_ld_FR_postI
#define st_FR_postI _TIE_dmx1a_common_tie_st_FR_postI
#define ld_FR_postR _TIE_dmx1a_common_tie_ld_FR_postR
#define st_FR_postR _TIE_dmx1a_common_tie_st_FR_postR
#define ld_HR _TIE_dmx1a_common_tie_ld_HR
#define st_HR _TIE_dmx1a_common_tie_st_HR
#define ld_HR_idxR _TIE_dmx1a_common_tie_ld_HR_idxR
#define st_HR_idxR _TIE_dmx1a_common_tie_st_HR_idxR
#define ld_HR_postI _TIE_dmx1a_common_tie_ld_HR_postI
#define st_HR_postI _TIE_dmx1a_common_tie_st_HR_postI
#define ld_HR_postR _TIE_dmx1a_common_tie_ld_HR_postR
#define st_HR_postR _TIE_dmx1a_common_tie_st_HR_postR
#define ld_VR _TIE_dmx1a_common_tie_ld_VR
#define st_VR _TIE_dmx1a_common_tie_st_VR
#define ld_VR_idxR _TIE_dmx1a_common_tie_ld_VR_idxR
#define st_VR_idxR _TIE_dmx1a_common_tie_st_VR_idxR
#define ld_VR_postI _TIE_dmx1a_common_tie_ld_VR_postI
#define st_VR_postI _TIE_dmx1a_common_tie_st_VR_postI
#define ld_VR_postR _TIE_dmx1a_common_tie_ld_VR_postR
#define st_VR_postR _TIE_dmx1a_common_tie_st_VR_postR
#define mv_FR _TIE_dmx1a_common_tie_mv_FR
#define move_ar_fr _TIE_dmx1a_common_tie_move_ar_fr
#define move_fr_ar _TIE_dmx1a_common_tie_move_fr_ar
#define mv_HR _TIE_dmx1a_common_tie_mv_HR
#define mv_VR _TIE_dmx1a_common_tie_mv_VR
#define vr128_pair _TIE_dmx1a_common_tie_vr128_pair
#define set_VRL _TIE_dmx1a_common_tie_set_VRL
#define set_VRH _TIE_dmx1a_common_tie_set_VRH
#define get_VRL _TIE_dmx1a_common_tie_get_VRL
#define get_VRH _TIE_dmx1a_common_tie_get_VRH
#define ld_ar_x2 _TIE_dmx1a_common_tie_ld_ar_x2
#define st_ar_x2 _TIE_dmx1a_common_tie_st_ar_x2
#define perm16_storei _TIE_dmx1a_common_tie_perm16_storei
#define perm16_loadi _TIE_dmx1a_common_tie_perm16_loadi
#define ulsr128_storei _TIE_dmx1a_common_tie_ulsr128_storei
#define ulsr128_loadi _TIE_dmx1a_common_tie_ulsr128_loadi
#define mir30_storei _TIE_dmx1a_common_tie_mir30_storei
#define mir30_loadi _TIE_dmx1a_common_tie_mir30_loadi
#define cr64_storei _TIE_dmx1a_common_tie_cr64_storei
#define cr64_loadi _TIE_dmx1a_common_tie_cr64_loadi
#define wr64_storei _TIE_dmx1a_common_tie_wr64_storei
#define wr64_loadi _TIE_dmx1a_common_tie_wr64_loadi
#define RUR_JammingBit _TIE_dmx1a_common_tie_RUR_JammingBit
#define RJammingBit _TIE_dmx1a_common_tie_RUR_JammingBit
#define RUR0 _TIE_dmx1a_common_tie_RUR_JammingBit
#define WUR_JammingBit _TIE_dmx1a_common_tie_WUR_JammingBit
#define WJammingBit _TIE_dmx1a_common_tie_WUR_JammingBit
#define WUR0 _TIE_dmx1a_common_tie_WUR_JammingBit
#define RUR_AccExtend_0 _TIE_dmx1a_common_tie_RUR_AccExtend_0
#define RAccExtend_0 _TIE_dmx1a_common_tie_RUR_AccExtend_0
#define RUR1 _TIE_dmx1a_common_tie_RUR_AccExtend_0
#define WUR_AccExtend_0 _TIE_dmx1a_common_tie_WUR_AccExtend_0
#define WAccExtend_0 _TIE_dmx1a_common_tie_WUR_AccExtend_0
#define WUR1 _TIE_dmx1a_common_tie_WUR_AccExtend_0
#define RUR_AccExtend_1 _TIE_dmx1a_common_tie_RUR_AccExtend_1
#define RAccExtend_1 _TIE_dmx1a_common_tie_RUR_AccExtend_1
#define RUR2 _TIE_dmx1a_common_tie_RUR_AccExtend_1
#define WUR_AccExtend_1 _TIE_dmx1a_common_tie_WUR_AccExtend_1
#define WAccExtend_1 _TIE_dmx1a_common_tie_WUR_AccExtend_1
#define WUR2 _TIE_dmx1a_common_tie_WUR_AccExtend_1
#define RUR_AccExtend_2 _TIE_dmx1a_common_tie_RUR_AccExtend_2
#define RAccExtend_2 _TIE_dmx1a_common_tie_RUR_AccExtend_2
#define RUR3 _TIE_dmx1a_common_tie_RUR_AccExtend_2
#define WUR_AccExtend_2 _TIE_dmx1a_common_tie_WUR_AccExtend_2
#define WAccExtend_2 _TIE_dmx1a_common_tie_WUR_AccExtend_2
#define WUR3 _TIE_dmx1a_common_tie_WUR_AccExtend_2
#define RUR_AccExtend_3 _TIE_dmx1a_common_tie_RUR_AccExtend_3
#define RAccExtend_3 _TIE_dmx1a_common_tie_RUR_AccExtend_3
#define RUR4 _TIE_dmx1a_common_tie_RUR_AccExtend_3
#define WUR_AccExtend_3 _TIE_dmx1a_common_tie_WUR_AccExtend_3
#define WAccExtend_3 _TIE_dmx1a_common_tie_WUR_AccExtend_3
#define WUR4 _TIE_dmx1a_common_tie_WUR_AccExtend_3
#define RUR_BB0_0 _TIE_dmx1a_common_tie_RUR_BB0_0
#define RBB0_0 _TIE_dmx1a_common_tie_RUR_BB0_0
#define RUR5 _TIE_dmx1a_common_tie_RUR_BB0_0
#define WUR_BB0_0 _TIE_dmx1a_common_tie_WUR_BB0_0
#define WBB0_0 _TIE_dmx1a_common_tie_WUR_BB0_0
#define WUR5 _TIE_dmx1a_common_tie_WUR_BB0_0
#define RUR_BB0_1 _TIE_dmx1a_common_tie_RUR_BB0_1
#define RBB0_1 _TIE_dmx1a_common_tie_RUR_BB0_1
#define RUR6 _TIE_dmx1a_common_tie_RUR_BB0_1
#define WUR_BB0_1 _TIE_dmx1a_common_tie_WUR_BB0_1
#define WBB0_1 _TIE_dmx1a_common_tie_WUR_BB0_1
#define WUR6 _TIE_dmx1a_common_tie_WUR_BB0_1
#define RUR_BB0_2 _TIE_dmx1a_common_tie_RUR_BB0_2
#define RBB0_2 _TIE_dmx1a_common_tie_RUR_BB0_2
#define RUR7 _TIE_dmx1a_common_tie_RUR_BB0_2
#define WUR_BB0_2 _TIE_dmx1a_common_tie_WUR_BB0_2
#define WBB0_2 _TIE_dmx1a_common_tie_WUR_BB0_2
#define WUR7 _TIE_dmx1a_common_tie_WUR_BB0_2
#define RUR_BB0_3 _TIE_dmx1a_common_tie_RUR_BB0_3
#define RBB0_3 _TIE_dmx1a_common_tie_RUR_BB0_3
#define RUR8 _TIE_dmx1a_common_tie_RUR_BB0_3
#define WUR_BB0_3 _TIE_dmx1a_common_tie_WUR_BB0_3
#define WBB0_3 _TIE_dmx1a_common_tie_WUR_BB0_3
#define WUR8 _TIE_dmx1a_common_tie_WUR_BB0_3
#define RUR_BB1_0 _TIE_dmx1a_common_tie_RUR_BB1_0
#define RBB1_0 _TIE_dmx1a_common_tie_RUR_BB1_0
#define RUR9 _TIE_dmx1a_common_tie_RUR_BB1_0
#define WUR_BB1_0 _TIE_dmx1a_common_tie_WUR_BB1_0
#define WBB1_0 _TIE_dmx1a_common_tie_WUR_BB1_0
#define WUR9 _TIE_dmx1a_common_tie_WUR_BB1_0
#define RUR_BB1_1 _TIE_dmx1a_common_tie_RUR_BB1_1
#define RBB1_1 _TIE_dmx1a_common_tie_RUR_BB1_1
#define RUR10 _TIE_dmx1a_common_tie_RUR_BB1_1
#define WUR_BB1_1 _TIE_dmx1a_common_tie_WUR_BB1_1
#define WBB1_1 _TIE_dmx1a_common_tie_WUR_BB1_1
#define WUR10 _TIE_dmx1a_common_tie_WUR_BB1_1
#define RUR_BB1_2 _TIE_dmx1a_common_tie_RUR_BB1_2
#define RBB1_2 _TIE_dmx1a_common_tie_RUR_BB1_2
#define RUR11 _TIE_dmx1a_common_tie_RUR_BB1_2
#define WUR_BB1_2 _TIE_dmx1a_common_tie_WUR_BB1_2
#define WBB1_2 _TIE_dmx1a_common_tie_WUR_BB1_2
#define WUR11 _TIE_dmx1a_common_tie_WUR_BB1_2
#define RUR_BB1_3 _TIE_dmx1a_common_tie_RUR_BB1_3
#define RBB1_3 _TIE_dmx1a_common_tie_RUR_BB1_3
#define RUR12 _TIE_dmx1a_common_tie_RUR_BB1_3
#define WUR_BB1_3 _TIE_dmx1a_common_tie_WUR_BB1_3
#define WBB1_3 _TIE_dmx1a_common_tie_WUR_BB1_3
#define WUR12 _TIE_dmx1a_common_tie_WUR_BB1_3
#define RUR_BB2_0 _TIE_dmx1a_common_tie_RUR_BB2_0
#define RBB2_0 _TIE_dmx1a_common_tie_RUR_BB2_0
#define RUR13 _TIE_dmx1a_common_tie_RUR_BB2_0
#define WUR_BB2_0 _TIE_dmx1a_common_tie_WUR_BB2_0
#define WBB2_0 _TIE_dmx1a_common_tie_WUR_BB2_0
#define WUR13 _TIE_dmx1a_common_tie_WUR_BB2_0
#define RUR_BB2_1 _TIE_dmx1a_common_tie_RUR_BB2_1
#define RBB2_1 _TIE_dmx1a_common_tie_RUR_BB2_1
#define RUR14 _TIE_dmx1a_common_tie_RUR_BB2_1
#define WUR_BB2_1 _TIE_dmx1a_common_tie_WUR_BB2_1
#define WBB2_1 _TIE_dmx1a_common_tie_WUR_BB2_1
#define WUR14 _TIE_dmx1a_common_tie_WUR_BB2_1
#define RUR_BB2_2 _TIE_dmx1a_common_tie_RUR_BB2_2
#define RBB2_2 _TIE_dmx1a_common_tie_RUR_BB2_2
#define RUR15 _TIE_dmx1a_common_tie_RUR_BB2_2
#define WUR_BB2_2 _TIE_dmx1a_common_tie_WUR_BB2_2
#define WBB2_2 _TIE_dmx1a_common_tie_WUR_BB2_2
#define WUR15 _TIE_dmx1a_common_tie_WUR_BB2_2
#define RUR_BB2_3 _TIE_dmx1a_common_tie_RUR_BB2_3
#define RBB2_3 _TIE_dmx1a_common_tie_RUR_BB2_3
#define RUR16 _TIE_dmx1a_common_tie_RUR_BB2_3
#define WUR_BB2_3 _TIE_dmx1a_common_tie_WUR_BB2_3
#define WBB2_3 _TIE_dmx1a_common_tie_WUR_BB2_3
#define WUR16 _TIE_dmx1a_common_tie_WUR_BB2_3
#define RUR_BB3_0 _TIE_dmx1a_common_tie_RUR_BB3_0
#define RBB3_0 _TIE_dmx1a_common_tie_RUR_BB3_0
#define RUR17 _TIE_dmx1a_common_tie_RUR_BB3_0
#define WUR_BB3_0 _TIE_dmx1a_common_tie_WUR_BB3_0
#define WBB3_0 _TIE_dmx1a_common_tie_WUR_BB3_0
#define WUR17 _TIE_dmx1a_common_tie_WUR_BB3_0
#define RUR_BB3_1 _TIE_dmx1a_common_tie_RUR_BB3_1
#define RBB3_1 _TIE_dmx1a_common_tie_RUR_BB3_1
#define RUR18 _TIE_dmx1a_common_tie_RUR_BB3_1
#define WUR_BB3_1 _TIE_dmx1a_common_tie_WUR_BB3_1
#define WBB3_1 _TIE_dmx1a_common_tie_WUR_BB3_1
#define WUR18 _TIE_dmx1a_common_tie_WUR_BB3_1
#define RUR_BB3_2 _TIE_dmx1a_common_tie_RUR_BB3_2
#define RBB3_2 _TIE_dmx1a_common_tie_RUR_BB3_2
#define RUR19 _TIE_dmx1a_common_tie_RUR_BB3_2
#define WUR_BB3_2 _TIE_dmx1a_common_tie_WUR_BB3_2
#define WBB3_2 _TIE_dmx1a_common_tie_WUR_BB3_2
#define WUR19 _TIE_dmx1a_common_tie_WUR_BB3_2
#define RUR_BB3_3 _TIE_dmx1a_common_tie_RUR_BB3_3
#define RBB3_3 _TIE_dmx1a_common_tie_RUR_BB3_3
#define RUR20 _TIE_dmx1a_common_tie_RUR_BB3_3
#define WUR_BB3_3 _TIE_dmx1a_common_tie_WUR_BB3_3
#define WBB3_3 _TIE_dmx1a_common_tie_WUR_BB3_3
#define WUR20 _TIE_dmx1a_common_tie_WUR_BB3_3
#define RUR_BB4_0 _TIE_dmx1a_common_tie_RUR_BB4_0
#define RBB4_0 _TIE_dmx1a_common_tie_RUR_BB4_0
#define RUR21 _TIE_dmx1a_common_tie_RUR_BB4_0
#define WUR_BB4_0 _TIE_dmx1a_common_tie_WUR_BB4_0
#define WBB4_0 _TIE_dmx1a_common_tie_WUR_BB4_0
#define WUR21 _TIE_dmx1a_common_tie_WUR_BB4_0
#define RUR_BB4_1 _TIE_dmx1a_common_tie_RUR_BB4_1
#define RBB4_1 _TIE_dmx1a_common_tie_RUR_BB4_1
#define RUR22 _TIE_dmx1a_common_tie_RUR_BB4_1
#define WUR_BB4_1 _TIE_dmx1a_common_tie_WUR_BB4_1
#define WBB4_1 _TIE_dmx1a_common_tie_WUR_BB4_1
#define WUR22 _TIE_dmx1a_common_tie_WUR_BB4_1
#define RUR_BB4_2 _TIE_dmx1a_common_tie_RUR_BB4_2
#define RBB4_2 _TIE_dmx1a_common_tie_RUR_BB4_2
#define RUR23 _TIE_dmx1a_common_tie_RUR_BB4_2
#define WUR_BB4_2 _TIE_dmx1a_common_tie_WUR_BB4_2
#define WBB4_2 _TIE_dmx1a_common_tie_WUR_BB4_2
#define WUR23 _TIE_dmx1a_common_tie_WUR_BB4_2
#define RUR_BB4_3 _TIE_dmx1a_common_tie_RUR_BB4_3
#define RBB4_3 _TIE_dmx1a_common_tie_RUR_BB4_3
#define RUR24 _TIE_dmx1a_common_tie_RUR_BB4_3
#define WUR_BB4_3 _TIE_dmx1a_common_tie_WUR_BB4_3
#define WBB4_3 _TIE_dmx1a_common_tie_WUR_BB4_3
#define WUR24 _TIE_dmx1a_common_tie_WUR_BB4_3
#define RUR_BB5_0 _TIE_dmx1a_common_tie_RUR_BB5_0
#define RBB5_0 _TIE_dmx1a_common_tie_RUR_BB5_0
#define RUR25 _TIE_dmx1a_common_tie_RUR_BB5_0
#define WUR_BB5_0 _TIE_dmx1a_common_tie_WUR_BB5_0
#define WBB5_0 _TIE_dmx1a_common_tie_WUR_BB5_0
#define WUR25 _TIE_dmx1a_common_tie_WUR_BB5_0
#define RUR_BB5_1 _TIE_dmx1a_common_tie_RUR_BB5_1
#define RBB5_1 _TIE_dmx1a_common_tie_RUR_BB5_1
#define RUR26 _TIE_dmx1a_common_tie_RUR_BB5_1
#define WUR_BB5_1 _TIE_dmx1a_common_tie_WUR_BB5_1
#define WBB5_1 _TIE_dmx1a_common_tie_WUR_BB5_1
#define WUR26 _TIE_dmx1a_common_tie_WUR_BB5_1
#define RUR_BB5_2 _TIE_dmx1a_common_tie_RUR_BB5_2
#define RBB5_2 _TIE_dmx1a_common_tie_RUR_BB5_2
#define RUR27 _TIE_dmx1a_common_tie_RUR_BB5_2
#define WUR_BB5_2 _TIE_dmx1a_common_tie_WUR_BB5_2
#define WBB5_2 _TIE_dmx1a_common_tie_WUR_BB5_2
#define WUR27 _TIE_dmx1a_common_tie_WUR_BB5_2
#define RUR_BB5_3 _TIE_dmx1a_common_tie_RUR_BB5_3
#define RBB5_3 _TIE_dmx1a_common_tie_RUR_BB5_3
#define RUR28 _TIE_dmx1a_common_tie_RUR_BB5_3
#define WUR_BB5_3 _TIE_dmx1a_common_tie_WUR_BB5_3
#define WBB5_3 _TIE_dmx1a_common_tie_WUR_BB5_3
#define WUR28 _TIE_dmx1a_common_tie_WUR_BB5_3
#define RUR_BB6_0 _TIE_dmx1a_common_tie_RUR_BB6_0
#define RBB6_0 _TIE_dmx1a_common_tie_RUR_BB6_0
#define RUR29 _TIE_dmx1a_common_tie_RUR_BB6_0
#define WUR_BB6_0 _TIE_dmx1a_common_tie_WUR_BB6_0
#define WBB6_0 _TIE_dmx1a_common_tie_WUR_BB6_0
#define WUR29 _TIE_dmx1a_common_tie_WUR_BB6_0
#define RUR_BB6_1 _TIE_dmx1a_common_tie_RUR_BB6_1
#define RBB6_1 _TIE_dmx1a_common_tie_RUR_BB6_1
#define RUR30 _TIE_dmx1a_common_tie_RUR_BB6_1
#define WUR_BB6_1 _TIE_dmx1a_common_tie_WUR_BB6_1
#define WBB6_1 _TIE_dmx1a_common_tie_WUR_BB6_1
#define WUR30 _TIE_dmx1a_common_tie_WUR_BB6_1
#define RUR_BB6_2 _TIE_dmx1a_common_tie_RUR_BB6_2
#define RBB6_2 _TIE_dmx1a_common_tie_RUR_BB6_2
#define RUR31 _TIE_dmx1a_common_tie_RUR_BB6_2
#define WUR_BB6_2 _TIE_dmx1a_common_tie_WUR_BB6_2
#define WBB6_2 _TIE_dmx1a_common_tie_WUR_BB6_2
#define WUR31 _TIE_dmx1a_common_tie_WUR_BB6_2
#define RUR_BB6_3 _TIE_dmx1a_common_tie_RUR_BB6_3
#define RBB6_3 _TIE_dmx1a_common_tie_RUR_BB6_3
#define RUR32 _TIE_dmx1a_common_tie_RUR_BB6_3
#define WUR_BB6_3 _TIE_dmx1a_common_tie_WUR_BB6_3
#define WBB6_3 _TIE_dmx1a_common_tie_WUR_BB6_3
#define WUR32 _TIE_dmx1a_common_tie_WUR_BB6_3
#define RUR_BB7_0 _TIE_dmx1a_common_tie_RUR_BB7_0
#define RBB7_0 _TIE_dmx1a_common_tie_RUR_BB7_0
#define RUR33 _TIE_dmx1a_common_tie_RUR_BB7_0
#define WUR_BB7_0 _TIE_dmx1a_common_tie_WUR_BB7_0
#define WBB7_0 _TIE_dmx1a_common_tie_WUR_BB7_0
#define WUR33 _TIE_dmx1a_common_tie_WUR_BB7_0
#define RUR_BB7_1 _TIE_dmx1a_common_tie_RUR_BB7_1
#define RBB7_1 _TIE_dmx1a_common_tie_RUR_BB7_1
#define RUR34 _TIE_dmx1a_common_tie_RUR_BB7_1
#define WUR_BB7_1 _TIE_dmx1a_common_tie_WUR_BB7_1
#define WBB7_1 _TIE_dmx1a_common_tie_WUR_BB7_1
#define WUR34 _TIE_dmx1a_common_tie_WUR_BB7_1
#define RUR_BB7_2 _TIE_dmx1a_common_tie_RUR_BB7_2
#define RBB7_2 _TIE_dmx1a_common_tie_RUR_BB7_2
#define RUR35 _TIE_dmx1a_common_tie_RUR_BB7_2
#define WUR_BB7_2 _TIE_dmx1a_common_tie_WUR_BB7_2
#define WBB7_2 _TIE_dmx1a_common_tie_WUR_BB7_2
#define WUR35 _TIE_dmx1a_common_tie_WUR_BB7_2
#define RUR_BB7_3 _TIE_dmx1a_common_tie_RUR_BB7_3
#define RBB7_3 _TIE_dmx1a_common_tie_RUR_BB7_3
#define RUR36 _TIE_dmx1a_common_tie_RUR_BB7_3
#define WUR_BB7_3 _TIE_dmx1a_common_tie_WUR_BB7_3
#define WBB7_3 _TIE_dmx1a_common_tie_WUR_BB7_3
#define WUR36 _TIE_dmx1a_common_tie_WUR_BB7_3
#define RUR_MvmAux _TIE_dmx1a_common_tie_RUR_MvmAux
#define RMvmAux _TIE_dmx1a_common_tie_RUR_MvmAux
#define RUR37 _TIE_dmx1a_common_tie_RUR_MvmAux
#define WUR_MvmAux _TIE_dmx1a_common_tie_WUR_MvmAux
#define WMvmAux _TIE_dmx1a_common_tie_WUR_MvmAux
#define WUR37 _TIE_dmx1a_common_tie_WUR_MvmAux
#define RUR_VB1_0 _TIE_dmx1a_common_tie_RUR_VB1_0
#define RVB1_0 _TIE_dmx1a_common_tie_RUR_VB1_0
#define RUR38 _TIE_dmx1a_common_tie_RUR_VB1_0
#define WUR_VB1_0 _TIE_dmx1a_common_tie_WUR_VB1_0
#define WVB1_0 _TIE_dmx1a_common_tie_WUR_VB1_0
#define WUR38 _TIE_dmx1a_common_tie_WUR_VB1_0
#define RUR_VB1_1 _TIE_dmx1a_common_tie_RUR_VB1_1
#define RVB1_1 _TIE_dmx1a_common_tie_RUR_VB1_1
#define RUR39 _TIE_dmx1a_common_tie_RUR_VB1_1
#define WUR_VB1_1 _TIE_dmx1a_common_tie_WUR_VB1_1
#define WVB1_1 _TIE_dmx1a_common_tie_WUR_VB1_1
#define WUR39 _TIE_dmx1a_common_tie_WUR_VB1_1
#define RUR_VB1_2 _TIE_dmx1a_common_tie_RUR_VB1_2
#define RVB1_2 _TIE_dmx1a_common_tie_RUR_VB1_2
#define RUR40 _TIE_dmx1a_common_tie_RUR_VB1_2
#define WUR_VB1_2 _TIE_dmx1a_common_tie_WUR_VB1_2
#define WVB1_2 _TIE_dmx1a_common_tie_WUR_VB1_2
#define WUR40 _TIE_dmx1a_common_tie_WUR_VB1_2
#define RUR_VB1_3 _TIE_dmx1a_common_tie_RUR_VB1_3
#define RVB1_3 _TIE_dmx1a_common_tie_RUR_VB1_3
#define RUR41 _TIE_dmx1a_common_tie_RUR_VB1_3
#define WUR_VB1_3 _TIE_dmx1a_common_tie_WUR_VB1_3
#define WVB1_3 _TIE_dmx1a_common_tie_WUR_VB1_3
#define WUR41 _TIE_dmx1a_common_tie_WUR_VB1_3
#define RUR_VB2_0 _TIE_dmx1a_common_tie_RUR_VB2_0
#define RVB2_0 _TIE_dmx1a_common_tie_RUR_VB2_0
#define RUR42 _TIE_dmx1a_common_tie_RUR_VB2_0
#define WUR_VB2_0 _TIE_dmx1a_common_tie_WUR_VB2_0
#define WVB2_0 _TIE_dmx1a_common_tie_WUR_VB2_0
#define WUR42 _TIE_dmx1a_common_tie_WUR_VB2_0
#define RUR_VB2_1 _TIE_dmx1a_common_tie_RUR_VB2_1
#define RVB2_1 _TIE_dmx1a_common_tie_RUR_VB2_1
#define RUR43 _TIE_dmx1a_common_tie_RUR_VB2_1
#define WUR_VB2_1 _TIE_dmx1a_common_tie_WUR_VB2_1
#define WVB2_1 _TIE_dmx1a_common_tie_WUR_VB2_1
#define WUR43 _TIE_dmx1a_common_tie_WUR_VB2_1
#define RUR_VB2_2 _TIE_dmx1a_common_tie_RUR_VB2_2
#define RVB2_2 _TIE_dmx1a_common_tie_RUR_VB2_2
#define RUR44 _TIE_dmx1a_common_tie_RUR_VB2_2
#define WUR_VB2_2 _TIE_dmx1a_common_tie_WUR_VB2_2
#define WVB2_2 _TIE_dmx1a_common_tie_WUR_VB2_2
#define WUR44 _TIE_dmx1a_common_tie_WUR_VB2_2
#define RUR_VB2_3 _TIE_dmx1a_common_tie_RUR_VB2_3
#define RVB2_3 _TIE_dmx1a_common_tie_RUR_VB2_3
#define RUR45 _TIE_dmx1a_common_tie_RUR_VB2_3
#define WUR_VB2_3 _TIE_dmx1a_common_tie_WUR_VB2_3
#define WVB2_3 _TIE_dmx1a_common_tie_WUR_VB2_3
#define WUR45 _TIE_dmx1a_common_tie_WUR_VB2_3
#define RUR_VB3_0 _TIE_dmx1a_common_tie_RUR_VB3_0
#define RVB3_0 _TIE_dmx1a_common_tie_RUR_VB3_0
#define RUR46 _TIE_dmx1a_common_tie_RUR_VB3_0
#define WUR_VB3_0 _TIE_dmx1a_common_tie_WUR_VB3_0
#define WVB3_0 _TIE_dmx1a_common_tie_WUR_VB3_0
#define WUR46 _TIE_dmx1a_common_tie_WUR_VB3_0
#define RUR_VB3_1 _TIE_dmx1a_common_tie_RUR_VB3_1
#define RVB3_1 _TIE_dmx1a_common_tie_RUR_VB3_1
#define RUR47 _TIE_dmx1a_common_tie_RUR_VB3_1
#define WUR_VB3_1 _TIE_dmx1a_common_tie_WUR_VB3_1
#define WVB3_1 _TIE_dmx1a_common_tie_WUR_VB3_1
#define WUR47 _TIE_dmx1a_common_tie_WUR_VB3_1
#define RUR_VB3_2 _TIE_dmx1a_common_tie_RUR_VB3_2
#define RVB3_2 _TIE_dmx1a_common_tie_RUR_VB3_2
#define RUR48 _TIE_dmx1a_common_tie_RUR_VB3_2
#define WUR_VB3_2 _TIE_dmx1a_common_tie_WUR_VB3_2
#define WVB3_2 _TIE_dmx1a_common_tie_WUR_VB3_2
#define WUR48 _TIE_dmx1a_common_tie_WUR_VB3_2
#define RUR_VB3_3 _TIE_dmx1a_common_tie_RUR_VB3_3
#define RVB3_3 _TIE_dmx1a_common_tie_RUR_VB3_3
#define RUR49 _TIE_dmx1a_common_tie_RUR_VB3_3
#define WUR_VB3_3 _TIE_dmx1a_common_tie_WUR_VB3_3
#define WVB3_3 _TIE_dmx1a_common_tie_WUR_VB3_3
#define WUR49 _TIE_dmx1a_common_tie_WUR_VB3_3
#define RUR_VB4_0 _TIE_dmx1a_common_tie_RUR_VB4_0
#define RVB4_0 _TIE_dmx1a_common_tie_RUR_VB4_0
#define RUR50 _TIE_dmx1a_common_tie_RUR_VB4_0
#define WUR_VB4_0 _TIE_dmx1a_common_tie_WUR_VB4_0
#define WVB4_0 _TIE_dmx1a_common_tie_WUR_VB4_0
#define WUR50 _TIE_dmx1a_common_tie_WUR_VB4_0
#define RUR_VB4_1 _TIE_dmx1a_common_tie_RUR_VB4_1
#define RVB4_1 _TIE_dmx1a_common_tie_RUR_VB4_1
#define RUR51 _TIE_dmx1a_common_tie_RUR_VB4_1
#define WUR_VB4_1 _TIE_dmx1a_common_tie_WUR_VB4_1
#define WVB4_1 _TIE_dmx1a_common_tie_WUR_VB4_1
#define WUR51 _TIE_dmx1a_common_tie_WUR_VB4_1
#define RUR_VB4_2 _TIE_dmx1a_common_tie_RUR_VB4_2
#define RVB4_2 _TIE_dmx1a_common_tie_RUR_VB4_2
#define RUR52 _TIE_dmx1a_common_tie_RUR_VB4_2
#define WUR_VB4_2 _TIE_dmx1a_common_tie_WUR_VB4_2
#define WVB4_2 _TIE_dmx1a_common_tie_WUR_VB4_2
#define WUR52 _TIE_dmx1a_common_tie_WUR_VB4_2
#define RUR_VB4_3 _TIE_dmx1a_common_tie_RUR_VB4_3
#define RVB4_3 _TIE_dmx1a_common_tie_RUR_VB4_3
#define RUR53 _TIE_dmx1a_common_tie_RUR_VB4_3
#define WUR_VB4_3 _TIE_dmx1a_common_tie_WUR_VB4_3
#define WVB4_3 _TIE_dmx1a_common_tie_WUR_VB4_3
#define WUR53 _TIE_dmx1a_common_tie_WUR_VB4_3
#define RUR_VB5_0 _TIE_dmx1a_common_tie_RUR_VB5_0
#define RVB5_0 _TIE_dmx1a_common_tie_RUR_VB5_0
#define RUR54 _TIE_dmx1a_common_tie_RUR_VB5_0
#define WUR_VB5_0 _TIE_dmx1a_common_tie_WUR_VB5_0
#define WVB5_0 _TIE_dmx1a_common_tie_WUR_VB5_0
#define WUR54 _TIE_dmx1a_common_tie_WUR_VB5_0
#define RUR_VB5_1 _TIE_dmx1a_common_tie_RUR_VB5_1
#define RVB5_1 _TIE_dmx1a_common_tie_RUR_VB5_1
#define RUR55 _TIE_dmx1a_common_tie_RUR_VB5_1
#define WUR_VB5_1 _TIE_dmx1a_common_tie_WUR_VB5_1
#define WVB5_1 _TIE_dmx1a_common_tie_WUR_VB5_1
#define WUR55 _TIE_dmx1a_common_tie_WUR_VB5_1
#define RUR_VB5_2 _TIE_dmx1a_common_tie_RUR_VB5_2
#define RVB5_2 _TIE_dmx1a_common_tie_RUR_VB5_2
#define RUR56 _TIE_dmx1a_common_tie_RUR_VB5_2
#define WUR_VB5_2 _TIE_dmx1a_common_tie_WUR_VB5_2
#define WVB5_2 _TIE_dmx1a_common_tie_WUR_VB5_2
#define WUR56 _TIE_dmx1a_common_tie_WUR_VB5_2
#define RUR_VB5_3 _TIE_dmx1a_common_tie_RUR_VB5_3
#define RVB5_3 _TIE_dmx1a_common_tie_RUR_VB5_3
#define RUR57 _TIE_dmx1a_common_tie_RUR_VB5_3
#define WUR_VB5_3 _TIE_dmx1a_common_tie_WUR_VB5_3
#define WVB5_3 _TIE_dmx1a_common_tie_WUR_VB5_3
#define WUR57 _TIE_dmx1a_common_tie_WUR_VB5_3
#define RUR_VB6_0 _TIE_dmx1a_common_tie_RUR_VB6_0
#define RVB6_0 _TIE_dmx1a_common_tie_RUR_VB6_0
#define RUR58 _TIE_dmx1a_common_tie_RUR_VB6_0
#define WUR_VB6_0 _TIE_dmx1a_common_tie_WUR_VB6_0
#define WVB6_0 _TIE_dmx1a_common_tie_WUR_VB6_0
#define WUR58 _TIE_dmx1a_common_tie_WUR_VB6_0
#define RUR_VB6_1 _TIE_dmx1a_common_tie_RUR_VB6_1
#define RVB6_1 _TIE_dmx1a_common_tie_RUR_VB6_1
#define RUR59 _TIE_dmx1a_common_tie_RUR_VB6_1
#define WUR_VB6_1 _TIE_dmx1a_common_tie_WUR_VB6_1
#define WVB6_1 _TIE_dmx1a_common_tie_WUR_VB6_1
#define WUR59 _TIE_dmx1a_common_tie_WUR_VB6_1
#define RUR_VB6_2 _TIE_dmx1a_common_tie_RUR_VB6_2
#define RVB6_2 _TIE_dmx1a_common_tie_RUR_VB6_2
#define RUR60 _TIE_dmx1a_common_tie_RUR_VB6_2
#define WUR_VB6_2 _TIE_dmx1a_common_tie_WUR_VB6_2
#define WVB6_2 _TIE_dmx1a_common_tie_WUR_VB6_2
#define WUR60 _TIE_dmx1a_common_tie_WUR_VB6_2
#define RUR_VB6_3 _TIE_dmx1a_common_tie_RUR_VB6_3
#define RVB6_3 _TIE_dmx1a_common_tie_RUR_VB6_3
#define RUR61 _TIE_dmx1a_common_tie_RUR_VB6_3
#define WUR_VB6_3 _TIE_dmx1a_common_tie_WUR_VB6_3
#define WVB6_3 _TIE_dmx1a_common_tie_WUR_VB6_3
#define WUR61 _TIE_dmx1a_common_tie_WUR_VB6_3
#define RUR_VB7_0 _TIE_dmx1a_common_tie_RUR_VB7_0
#define RVB7_0 _TIE_dmx1a_common_tie_RUR_VB7_0
#define RUR62 _TIE_dmx1a_common_tie_RUR_VB7_0
#define WUR_VB7_0 _TIE_dmx1a_common_tie_WUR_VB7_0
#define WVB7_0 _TIE_dmx1a_common_tie_WUR_VB7_0
#define WUR62 _TIE_dmx1a_common_tie_WUR_VB7_0
#define RUR_VB7_1 _TIE_dmx1a_common_tie_RUR_VB7_1
#define RVB7_1 _TIE_dmx1a_common_tie_RUR_VB7_1
#define RUR63 _TIE_dmx1a_common_tie_RUR_VB7_1
#define WUR_VB7_1 _TIE_dmx1a_common_tie_WUR_VB7_1
#define WVB7_1 _TIE_dmx1a_common_tie_WUR_VB7_1
#define WUR63 _TIE_dmx1a_common_tie_WUR_VB7_1
#define RUR_VB7_2 _TIE_dmx1a_common_tie_RUR_VB7_2
#define RVB7_2 _TIE_dmx1a_common_tie_RUR_VB7_2
#define RUR64 _TIE_dmx1a_common_tie_RUR_VB7_2
#define WUR_VB7_2 _TIE_dmx1a_common_tie_WUR_VB7_2
#define WVB7_2 _TIE_dmx1a_common_tie_WUR_VB7_2
#define WUR64 _TIE_dmx1a_common_tie_WUR_VB7_2
#define RUR_VB7_3 _TIE_dmx1a_common_tie_RUR_VB7_3
#define RVB7_3 _TIE_dmx1a_common_tie_RUR_VB7_3
#define RUR65 _TIE_dmx1a_common_tie_RUR_VB7_3
#define WUR_VB7_3 _TIE_dmx1a_common_tie_WUR_VB7_3
#define WVB7_3 _TIE_dmx1a_common_tie_WUR_VB7_3
#define WUR65 _TIE_dmx1a_common_tie_WUR_VB7_3
#define RUR_look_state _TIE_dmx1a_common_tie_RUR_look_state
#define Rlook_state _TIE_dmx1a_common_tie_RUR_look_state
#define RUR66 _TIE_dmx1a_common_tie_RUR_look_state
#define WUR_look_state _TIE_dmx1a_common_tie_WUR_look_state
#define Wlook_state _TIE_dmx1a_common_tie_WUR_look_state
#define WUR66 _TIE_dmx1a_common_tie_WUR_look_state
#define wr64_move _TIE_dmx1a_common_tie_wr64_move
#define perm16_move _TIE_dmx1a_common_tie_perm16_move
#define mir30_move _TIE_dmx1a_common_tie_mir30_move
#define ulsr128_move _TIE_dmx1a_common_tie_ulsr128_move
#define cr64_move _TIE_dmx1a_common_tie_cr64_move
#define fr32_move _TIE_dmx1a_common_tie_fr32_move
#define fr32_loadi _TIE_dmx1a_common_tie_fr32_loadi
#define fr32_storei _TIE_dmx1a_common_tie_fr32_storei
#define fr32_loadx _TIE_dmx1a_common_tie_fr32_loadx
#define fr32_storex _TIE_dmx1a_common_tie_fr32_storex
#define fr32_loadip _TIE_dmx1a_common_tie_fr32_loadip
#define fr32_storeip _TIE_dmx1a_common_tie_fr32_storeip
#define fr32_loadxp _TIE_dmx1a_common_tie_fr32_loadxp
#define fr32_storexp _TIE_dmx1a_common_tie_fr32_storexp
#define fr32_rtor_int32 _TIE_dmx1a_common_tie_fr32_rtor_int32
#define fr32_rtor_uint32 _TIE_dmx1a_common_tie_fr32_rtor_uint32
#define int32_rtor_fr32 _TIE_dmx1a_common_tie_int32_rtor_fr32
#define uint32_rtor_fr32 _TIE_dmx1a_common_tie_uint32_rtor_fr32
#define vr64_move _TIE_dmx1a_common_tie_vr64_move
#define vr64_loadi _TIE_dmx1a_common_tie_vr64_loadi
#define vr64_storei _TIE_dmx1a_common_tie_vr64_storei
#define vr64_loadx _TIE_dmx1a_common_tie_vr64_loadx
#define vr64_storex _TIE_dmx1a_common_tie_vr64_storex
#define vr64_loadip _TIE_dmx1a_common_tie_vr64_loadip
#define vr64_storeip _TIE_dmx1a_common_tie_vr64_storeip
#define vr64_loadxp _TIE_dmx1a_common_tie_vr64_loadxp
#define vr64_storexp _TIE_dmx1a_common_tie_vr64_storexp
#define vr64_rtor_int64 _TIE_dmx1a_common_tie_vr64_rtor_int64
#define vr64_rtor_uint64 _TIE_dmx1a_common_tie_vr64_rtor_uint64
#define int64_rtor_vr64 _TIE_dmx1a_common_tie_int64_rtor_vr64
#define uint64_rtor_vr64 _TIE_dmx1a_common_tie_uint64_rtor_vr64
#define vr64_pair _TIE_dmx1a_common_tie_vr64_pair
#define get_HRL _TIE_dmx1a_common_tie_get_HRL
#define get_HRH _TIE_dmx1a_common_tie_get_HRH
#define set_HRL _TIE_dmx1a_common_tie_set_HRL
#define set_HRH _TIE_dmx1a_common_tie_set_HRH
#define vr128_move _TIE_dmx1a_common_tie_vr128_move
#define vr128_loadi _TIE_dmx1a_common_tie_vr128_loadi
#define vr128_storei _TIE_dmx1a_common_tie_vr128_storei
#define vr128_loadx _TIE_dmx1a_common_tie_vr128_loadx
#define vr128_storex _TIE_dmx1a_common_tie_vr128_storex
#define vr128_loadip _TIE_dmx1a_common_tie_vr128_loadip
#define vr128_storeip _TIE_dmx1a_common_tie_vr128_storeip
#define vr128_loadxp _TIE_dmx1a_common_tie_vr128_loadxp
#define vr128_storexp _TIE_dmx1a_common_tie_vr128_storexp
#define vr128_quad _TIE_dmx1a_common_tie_vr128_quad
#define get_VRQ0 _TIE_dmx1a_common_tie_get_VRQ0
#define get_VRQ1 _TIE_dmx1a_common_tie_get_VRQ1
#define get_VRQ2 _TIE_dmx1a_common_tie_get_VRQ2
#define get_VRQ3 _TIE_dmx1a_common_tie_get_VRQ3
#define set_VRQ0 _TIE_dmx1a_common_tie_set_VRQ0
#define set_VRQ1 _TIE_dmx1a_common_tie_set_VRQ1
#define set_VRQ2 _TIE_dmx1a_common_tie_set_VRQ2
#define set_VRQ3 _TIE_dmx1a_common_tie_set_VRQ3

#ifndef RUR
#define RUR(NUM) RUR##NUM()
#endif

#ifndef WUR
#define WUR(VAL, NUM) WUR##NUM(VAL)
#endif

#endif /* __XCC__ */

#endif /* __XTENSA__ */

#endif /* !_XTENSA_dmx1a_common_tie_HEADER */
