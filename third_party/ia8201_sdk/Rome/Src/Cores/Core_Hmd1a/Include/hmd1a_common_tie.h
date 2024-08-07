// Customer ID=14540; Build=0x7f35a; Copyright (c) 2017 Cadence Design Systems, Inc.
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

/* Definitions for the hmd1a_common_tie TIE package */

/* Do not modify. This is automatically generated.*/

#ifndef _XTENSA_hmd1a_common_tie_HEADER
#define _XTENSA_hmd1a_common_tie_HEADER

#ifdef __XTENSA__
#ifdef __XCC__

#ifndef _ASMLANGUAGE
#ifndef _NOCLANGUAGE
#ifndef __ASSEMBLER__

#include <xtensa/tie/xt_core.h>
typedef _TIE_hmd1a_common_tie_fr32 fr32;
typedef _TIE_hmd1a_common_tie_vr64 vr64;
typedef _TIE_hmd1a_common_tie_cr64 cr64;
typedef _TIE_hmd1a_common_tie_mir18 mir18;
typedef _TIE_hmd1a_common_tie_ulsr32 ulsr32;
typedef _TIE_hmd1a_common_tie_atbool atbool;

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

extern void _TIE_hmd1a_common_tie_st_BBR(atbool a, atbool * b, immediate c);
extern atbool _TIE_hmd1a_common_tie_ld_BBR(const atbool * b, immediate c);
extern atbool _TIE_hmd1a_common_tie_mv_BBR(atbool b);
extern void _TIE_hmd1a_common_tie_st_ULSR(ulsr32 a, ulsr32 * b, immediate c);
extern ulsr32 _TIE_hmd1a_common_tie_ld_ULSR(const ulsr32 * b, immediate c);
extern void _TIE_hmd1a_common_tie_st_MIR(mir18 a, mir18 * b, immediate c);
extern mir18 _TIE_hmd1a_common_tie_ld_MIR(const mir18 * b, immediate c);
extern void _TIE_hmd1a_common_tie_st_CR(cr64 a, cr64 * b, immediate c);
extern cr64 _TIE_hmd1a_common_tie_ld_CR(const cr64 * b, immediate c);
extern void _TIE_hmd1a_common_tie_dma_ld(const unsigned * src);
extern void _TIE_hmd1a_common_tie_dma_align_ld(const unsigned * src /*inout*/, const unsigned * dst);
extern void _TIE_hmd1a_common_tie_dma_ldu(const unsigned * src /*inout*/);
extern void _TIE_hmd1a_common_tie_dma_flush_ld(const unsigned * src /*inout*/, const unsigned * dst);
extern void _TIE_hmd1a_common_tie_dma_st(unsigned * src, unsigned * dst);
extern void _TIE_hmd1a_common_tie_dma_align_st(unsigned * src, unsigned * dst /*inout*/);
extern void _TIE_hmd1a_common_tie_dma_stu(unsigned * src, unsigned * dst /*inout*/);
extern void _TIE_hmd1a_common_tie_dma_flush_st(unsigned * src, unsigned * dst);
extern void _TIE_hmd1a_common_tie_dma_buf_save(unsigned * dst /*inout*/);
extern vr64 _TIE_hmd1a_common_tie_load32x2_vr_idxR(const unsigned * ptr, unsigned ofst);
extern vr64 _TIE_hmd1a_common_tie_load32x2_vr_idxI(const unsigned * ptr, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load32x2_vr_postR(vr64 z /*out*/, const unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_hmd1a_common_tie_load32x2_vr_postI(vr64 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load32x2_vr_circI(vr64 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_hmd1a_common_tie_load32x1_vr_idxR(vr64 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_load32x1_vr_idxI(vr64 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_load32x1_vr_postR(vr64 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_load32x1_vr_postI(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_load32x1_vr_circI(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern vr64 _TIE_hmd1a_common_tie_load32x2_vr_bdir(const unsigned * ptr, unsigned ofst);
extern vr64 _TIE_hmd1a_common_tie_load32x2_vr_brev(const unsigned * ptr, unsigned ofst);
extern void _TIE_hmd1a_common_tie_load32x2_vr_idxR_perm(vr64 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate perm);
extern vr64 _TIE_hmd1a_common_tie_load32x2_vr_idxI_perm_vr(vr64 z, const unsigned * ptr, immediate ofst2, immediate perm);
extern void _TIE_hmd1a_common_tie_load32x2_vr_postR_perm(vr64 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate perm);
extern void _TIE_hmd1a_common_tie_load32x2_vr_postI_perm_vr(vr64 r /*out*/, vr64 z, const unsigned * ptr /*inout*/, immediate ofst2, immediate perm);
extern void _TIE_hmd1a_common_tie_load32x2_vr_circI_perm(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate perm);
extern void _TIE_hmd1a_common_tie_load32x1_vr_idxR_perm(vr64 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate perm);
extern vr64 _TIE_hmd1a_common_tie_load32x1_vr_idxI_perm_vr(vr64 z, const unsigned * ptr, immediate ofst2, immediate perm);
extern void _TIE_hmd1a_common_tie_load32x1_vr_postR_perm(vr64 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate perm);
extern void _TIE_hmd1a_common_tie_load32x1_vr_postI_perm_vr(vr64 r /*out*/, vr64 z, const unsigned * ptr /*inout*/, immediate ofst2, immediate perm);
extern void _TIE_hmd1a_common_tie_load32x1_vr_circI_perm(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate perm);
extern vr64 _TIE_hmd1a_common_tie_load16x2_vr_idxR(const unsigned * ptr, unsigned ofst);
extern vr64 _TIE_hmd1a_common_tie_load16x2_vr_idxI(const unsigned * ptr, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load16x2_vr_postR(vr64 z /*out*/, const unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_hmd1a_common_tie_load16x2_vr_postI(vr64 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load16x2_vr_circI(vr64 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_hmd1a_common_tie_load16x1_vr_idxR(vr64 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_load16x1_vr_idxI(vr64 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_load16x1_vr_postR(vr64 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_load16x1_vr_postI(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_load16x1_vr_circI(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern vr64 _TIE_hmd1a_common_tie_load8x2_vr_idxR(const unsigned * ptr, unsigned ofst);
extern vr64 _TIE_hmd1a_common_tie_load8x2_vr_idxI(const unsigned * ptr, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load8x2_vr_postR(vr64 z /*out*/, const unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_hmd1a_common_tie_load8x2_vr_postI(vr64 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load8x2_vr_circI(vr64 z /*out*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_hmd1a_common_tie_load8x1_vr_idxR(vr64 z /*inout*/, const unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_load8x1_vr_idxI(vr64 z /*inout*/, const unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_load8x1_vr_postR(vr64 z /*inout*/, const unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_load8x1_vr_postI(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_load8x1_vr_circI(vr64 z /*inout*/, const unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern ulsr32 _TIE_hmd1a_common_tie_align_32x2_load(const unsigned * ptr);
extern void _TIE_hmd1a_common_tie_load_32x2_vr_a(vr64 z /*out*/, ulsr32 buf /*inout*/, const unsigned * ptr /*inout*/);
extern void _TIE_hmd1a_common_tie_load_24x2_vr_a(vr64 z /*out*/, ulsr32 buf /*inout*/, const unsigned * ptr /*inout*/);
extern void _TIE_hmd1a_common_tie_load_32x2_vr_a_circ(vr64 z /*out*/, ulsr32 buf /*inout*/, const unsigned * ptr /*inout*/, cr64 c);
extern void _TIE_hmd1a_common_tie_store32x2_vr_idxR(vr64 z, unsigned * ptr, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store32x2_vr_idxI(vr64 z, unsigned * ptr, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store32x2_vr_postR(vr64 z, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store32x2_vr_postI(vr64 z, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store32x2_vr_circI(vr64 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_hmd1a_common_tie_store32x1_vr_idxR(vr64 z, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_idxI(vr64 z, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_postR(vr64 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_postI(vr64 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_circI(vr64 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x2_vr_br_idxR(vr64 z, atbool gate, unsigned * ptr, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store32x2_vr_br_idxI(vr64 z, atbool gate, unsigned * ptr, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store32x2_vr_br_postR(vr64 z, atbool gate, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store32x2_vr_br_postI(vr64 z, atbool gate, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store32x2_vr_br_circI(vr64 z, atbool gate, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_hmd1a_common_tie_store32x1_vr_br_idxR(vr64 z, atbool gate, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_br_idxI(vr64 z, atbool gate, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_br_postR(vr64 z, atbool gate, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_br_postI(vr64 z, atbool gate, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x1_vr_br_circI(vr64 z, atbool gate, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_hmd1a_common_tie_store32x2_vr_br_bdir(vr64 z, atbool gate, unsigned * ptr, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store32x2_vr_br_brev(vr64 z, atbool gate, unsigned * ptr, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store16x2_vr_idxR(vr64 z, unsigned * ptr, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store16x2_vr_idxI(vr64 z, unsigned * ptr, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store16x2_vr_postR(vr64 z, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store16x2_vr_postI(vr64 z, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store16x2_vr_circI(vr64 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_hmd1a_common_tie_store16x1_vr_idxR(vr64 z, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store16x1_vr_idxI(vr64 z, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store16x1_vr_postR(vr64 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store16x1_vr_postI(vr64 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store16x1_vr_circI(vr64 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern void _TIE_hmd1a_common_tie_store8x2_vr_idxR(vr64 z, unsigned * ptr, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store8x2_vr_idxI(vr64 z, unsigned * ptr, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store8x2_vr_postR(vr64 z, unsigned * ptr /*inout*/, unsigned ofst);
extern void _TIE_hmd1a_common_tie_store8x2_vr_postI(vr64 z, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store8x2_vr_circI(vr64 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c);
extern void _TIE_hmd1a_common_tie_store8x1_vr_idxR(vr64 z, unsigned * ptr, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store8x1_vr_idxI(vr64 z, unsigned * ptr, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store8x1_vr_postR(vr64 z, unsigned * ptr /*inout*/, unsigned ofst, immediate sel1);
extern void _TIE_hmd1a_common_tie_store8x1_vr_postI(vr64 z, unsigned * ptr /*inout*/, immediate ofst2, immediate sel1);
extern void _TIE_hmd1a_common_tie_store8x1_vr_circI(vr64 z, unsigned * ptr /*inout*/, immediate ofst1, cr64 c, immediate sel1);
extern ulsr32 _TIE_hmd1a_common_tie_align_32x2_store(const unsigned * ptr);
extern void _TIE_hmd1a_common_tie_store_32x2_vr_a(vr64 z, ulsr32 buf /*inout*/, unsigned * ptr /*inout*/);
extern void _TIE_hmd1a_common_tie_store_24x2_vr_a(vr64 z, ulsr32 buf /*inout*/, unsigned * ptr /*inout*/);
extern void _TIE_hmd1a_common_tie_store_32x2_vr_a_circ(vr64 z, ulsr32 buf /*inout*/, unsigned * ptr /*inout*/, cr64 c);
extern void _TIE_hmd1a_common_tie_flush_32x2(ulsr32 buf, unsigned * ptr);
extern void _TIE_hmd1a_common_tie_load_fr_postI(fr32 fx /*out*/, const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_fr_postI(fr32 fx, unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_brev_upd(atbool gate /*out*/, unsigned idx_out /*out*/, unsigned idx_in);
extern void _TIE_hmd1a_common_tie_brev_upd_ext(atbool gate /*inout*/, unsigned idx_out /*inout*/);
extern unsigned _TIE_hmd1a_common_tie_move32_ar_vr(vr64 x, immediate sel1);
extern void _TIE_hmd1a_common_tie_move32_vr_ar(vr64 z /*inout*/, immediate sel1, unsigned a);
extern unsigned _TIE_hmd1a_common_tie_move32_ar_vr_idx(vr64 x, unsigned idx);
extern fr32 _TIE_hmd1a_common_tie_move32_fr_vr_idx(vr64 x, unsigned idx);
extern void _TIE_hmd1a_common_tie_move_fr_eqz(fr32 z /*inout*/, fr32 x, fr32 y);
extern void _TIE_hmd1a_common_tie_move_fr_gez(fr32 z /*inout*/, fr32 x, fr32 y);
extern void _TIE_hmd1a_common_tie_move_fr_gtz(fr32 z /*inout*/, fr32 x, fr32 y);
extern void _TIE_hmd1a_common_tie_move_fr_lez(fr32 z /*inout*/, fr32 x, fr32 y);
extern void _TIE_hmd1a_common_tie_move_fr_ltz(fr32 z /*inout*/, fr32 x, fr32 y);
extern void _TIE_hmd1a_common_tie_move_fr_nez(fr32 z /*inout*/, fr32 x, fr32 y);
extern void _TIE_hmd1a_common_tie_move_fr_sat(fr32 z /*inout*/, fr32 x, fr32 y);
extern void _TIE_hmd1a_common_tie_move_fr_arnz(fr32 z /*inout*/, fr32 x, unsigned ax);
extern void _TIE_hmd1a_common_tie_vmove_vr_eqz(vr64 z /*inout*/, vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_vmove_vr_gez(vr64 z /*inout*/, vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_vmove_vr_gtz(vr64 z /*inout*/, vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_vmove_vr_lez(vr64 z /*inout*/, vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_vmove_vr_ltz(vr64 z /*inout*/, vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_vmove_vr_nez(vr64 z /*inout*/, vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_vmove_vr_sat(vr64 z /*inout*/, vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_replicate(vr64 z /*inout*/, immediate sel_code, vr64 x, immediate el_x);
extern void _TIE_hmd1a_common_tie_replicate_ar(vr64 z /*inout*/, immediate sel_code, unsigned ar);
extern vr64 _TIE_hmd1a_common_tie_vreplicate(vr64 x, immediate el_x);
extern vr64 _TIE_hmd1a_common_tie_vreplicate_fr(fr32 fx);
extern void _TIE_hmd1a_common_tie_convert_16I_to_32F_x1(vr64 z /*inout*/, unsigned exp_fxp, immediate el);
extern void _TIE_hmd1a_common_tie_convert_16I_to_32F_x2(vr64 z /*inout*/, unsigned exp_fxp);
extern void _TIE_hmd1a_common_tie_convert_32F_to_16I_x1(vr64 z /*inout*/, unsigned exp_fxp, immediate rnd, immediate el);
extern void _TIE_hmd1a_common_tie_convert_32F_to_16I_x2(vr64 z /*inout*/, unsigned exp_fxp, immediate rnd);
extern void _TIE_hmd1a_common_tie_convert_32F_to_16F_x1(vr64 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate round, immediate el);
extern void _TIE_hmd1a_common_tie_convert_32F_to_16F_x2(vr64 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate round);
extern void _TIE_hmd1a_common_tie_convert_16F_to_32F_x1(vr64 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias, immediate el);
extern void _TIE_hmd1a_common_tie_convert_16F_to_32F_x2(vr64 z /*inout*/, immediate is_signed, immediate exp_bits, unsigned bias);
extern void _TIE_hmd1a_common_tie_convert_32I_to_32F_x1(vr64 z /*inout*/, unsigned exp_fxp, immediate el);
extern void _TIE_hmd1a_common_tie_convert_32F_to_32I_x1(vr64 z /*inout*/, unsigned exp_fxp, immediate rnd, immediate el);
extern void _TIE_hmd1a_common_tie_convert_IEEE_float_to_32F_x2(vr64 z /*inout*/);
extern void _TIE_hmd1a_common_tie_convert_32F_to_IEEE_float_x2(vr64 z /*inout*/);
extern vr64 _TIE_hmd1a_common_tie_convert_32I_to_64F(unsigned x);
extern unsigned _TIE_hmd1a_common_tie_convert_64F_to_32I(vr64 x, immediate rnd);
extern vr64 _TIE_hmd1a_common_tie_convert_32F_to_64F(fr32 fx);
extern fr32 _TIE_hmd1a_common_tie_convert_64F_to_32F(vr64 x);
extern void _TIE_hmd1a_common_tie_convert_IEEE_double_to_64F(vr64 z /*inout*/);
extern void _TIE_hmd1a_common_tie_convert_64F_to_IEEE_double(vr64 z /*inout*/);
extern vr64 _TIE_hmd1a_common_tie_vadd_perm(vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs4, immediate div_by_2_op);
extern vr64 _TIE_hmd1a_common_tie_vsum_perm(vr64 z, vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs4, immediate sign_z);
extern vr64 _TIE_hmd1a_common_tie_vmul_perm(vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs2, immediate div_by_2_op);
extern vr64 _TIE_hmd1a_common_tie_vmac_perm(vr64 z, vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs2, immediate sign_z, immediate swap_z, immediate div_by_2_op);
extern vr64 _TIE_hmd1a_common_tie_vmac_boost(vr64 z, vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs2, immediate boost);
extern vr64 _TIE_hmd1a_common_tie_vblend(vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs4, immediate div_by_2_op);
extern vr64 _TIE_hmd1a_common_tie_vblend_add(vr64 z, vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs4, immediate sign_z, immediate swap_z, immediate div_by_2_op);
extern vr64 _TIE_hmd1a_common_tie_vblend_boost(vr64 z, vr64 x, vr64 y, immediate selin_h, immediate selin_l, immediate signs4, immediate boost);
extern fr32 _TIE_hmd1a_common_tie_fadds(fr32 fx, fr32 fy, immediate signs2);
extern fr32 _TIE_hmd1a_common_tie_fmuls(fr32 fx, fr32 fy, immediate signs2);
extern fr32 _TIE_hmd1a_common_tie_fmacs(fr32 fz, fr32 fx, fr32 fy, immediate signs2);
extern vr64 _TIE_hmd1a_common_tie_dadds(vr64 z, vr64 x, immediate signs2);
extern vr64 _TIE_hmd1a_common_tie_dmuls(vr64 x, vr64 y, immediate signs2);
extern vr64 _TIE_hmd1a_common_tie_dmacs(vr64 z, vr64 x, vr64 y, immediate signs2);
extern vr64 _TIE_hmd1a_common_tie_vadds(vr64 x, vr64 y, immediate signs4);
extern vr64 _TIE_hmd1a_common_tie_vmuls(vr64 x, vr64 y, immediate signs2);
extern vr64 _TIE_hmd1a_common_tie_vmacs(vr64 z, vr64 x, vr64 y, immediate signs2, immediate sign_z);
extern vr64 _TIE_hmd1a_common_tie_cmul(vr64 x, vr64 y, immediate conj);
extern vr64 _TIE_hmd1a_common_tie_cmac(vr64 z, vr64 x, vr64 y, immediate conj);
extern vr64 _TIE_hmd1a_common_tie_cmas(vr64 z, vr64 x, vr64 y, immediate conj);
extern vr64 _TIE_hmd1a_common_tie_vmulf(vr64 x, fr32 fy, immediate signs2);
extern vr64 _TIE_hmd1a_common_tie_vmacf(vr64 z, vr64 x, fr32 fy, immediate signs2, immediate sign_z);
extern vr64 _TIE_hmd1a_common_tie_vabs(vr64 x);
extern vr64 _TIE_hmd1a_common_tie_vexp_adj(vr64 x, unsigned exp_adj_ar);
extern vr64 _TIE_hmd1a_common_tie_vexp_adji(vr64 x, immediate exp_adj_imm);
extern vr64 _TIE_hmd1a_common_tie_vpermi(vr64 x, vr64 y, immediate sel4);
extern void _TIE_hmd1a_common_tie_seta_vr(vr64 z /*inout*/, immediate sel_code, immediate const_idx, immediate exp_adj_const);
extern vr64 _TIE_hmd1a_common_tie_vseta_vr(immediate const_idx, immediate exp_adj_const);
extern unsigned _TIE_hmd1a_common_tie_seta_ar(immediate const_idx, immediate exp_adj_const);
extern fr32 _TIE_hmd1a_common_tie_seta_fr(immediate const_idx, immediate exp_adj_const);
extern void _TIE_hmd1a_common_tie_load_AccExtend_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load32x1_vr_idx16vr(vr64 z /*inout*/, const unsigned * ptr, vr64 vidx16, immediate ptr_sel);
extern void _TIE_hmd1a_common_tie_load_BB0_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_BB1_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_BB2_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_BB3_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_VB1_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_VB2_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_VB3_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_VB4_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_VB5_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_VB6_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_VB7_postI(const unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_load_32x2_vr_a_bounded(vr64 z /*out*/, ulsr32 buf /*inout*/, const unsigned * ptr /*inout*/, mir18 count /*inout*/);
extern void _TIE_hmd1a_common_tie_load_BBx_VB67_a_bounded(ulsr32 buf /*inout*/, const unsigned * ptr /*inout*/, mir18 count /*inout*/, unsigned sel);
extern void _TIE_hmd1a_common_tie_flush_32x2_bounded(ulsr32 buf, unsigned * ptr /*inout*/, mir18 count /*inout*/);
extern void _TIE_hmd1a_common_tie_store_32x2_vr_a_bounded(vr64 z, ulsr32 buf /*inout*/, unsigned * ptr /*inout*/, mir18 count /*inout*/);
extern void _TIE_hmd1a_common_tie_store_AccExtend_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_BB0_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_BB1_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_BB2_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_BB3_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_VB1_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_VB2_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_VB3_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_VB4_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_VB5_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_VB6_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern void _TIE_hmd1a_common_tie_store_VB7_postI(unsigned * ptr /*inout*/, immediate ofst2);
extern vr64 _TIE_hmd1a_common_tie_afloat_exp_extract(vr64 x);
extern void _TIE_hmd1a_common_tie_mov_AccExtend_vr(vr64 x);
extern vr64 _TIE_hmd1a_common_tie_mov_vr_AccExtend(void);
extern vr64 _TIE_hmd1a_common_tie_mov_BB_VB67_to_vrVB_VB45(void);
extern void _TIE_hmd1a_common_tie_mov_vrVB_VB45_to_BB_VB67(vr64 x);
extern vr64 _TIE_hmd1a_common_tie_precess_16bits(vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_set_BB_vrVB67_zero(void);
extern unsigned _TIE_hmd1a_common_tie_exp_shift_amount(vr64 input1, vr64 input2);
extern void _TIE_hmd1a_common_tie_rnd_sat_pack(vr64 z /*inout*/, immediate el32, vr64 x, vr64 y, atbool sgn);
extern void _TIE_hmd1a_common_tie_rectify32_into8(vr64 z /*inout*/, vr64 x, unsigned shift, immediate rnd, immediate el32, immediate half);
extern vr64 _TIE_hmd1a_common_tie_shift8_into32_arith(vr64 x, unsigned shift, immediate rnd, immediate el32, immediate half);
extern vr64 _TIE_hmd1a_common_tie_shift32_arith(vr64 x, unsigned shift, immediate rnd);
extern void _TIE_hmd1a_common_tie_mac8bx8b(vr64 z /*inout*/, vr64 x, vr64 y, atbool signed_xy);
extern void _TIE_hmd1a_common_tie_mac8bx8b_sparse(vr64 z /*inout*/, vr64 x, vr64 y, atbool signed_xy);
extern void _TIE_hmd1a_common_tie_mac8bx8b_conv(vr64 z /*inout*/, vr64 x, atbool signed_xy, immediate shift_in);
extern mir18 _TIE_hmd1a_common_tie_mir_init(unsigned low);
extern void _TIE_hmd1a_common_tie_f_abs(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x);
extern void _TIE_hmd1a_common_tie_fclamp(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x, vr64 y, immediate el_y);
extern void _TIE_hmd1a_common_tie_fclamp_bp(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x, vr64 y, immediate el_y);
extern void _TIE_hmd1a_common_tie_fclamp_one(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x);
extern void _TIE_hmd1a_common_tie_fmax(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x, vr64 y, immediate el_y);
extern void _TIE_hmd1a_common_tie_fmin(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x, vr64 y, immediate el_y);
extern fr32 _TIE_hmd1a_common_tie_max_fr(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_min_fr(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_log2(fr32 x);
extern fr32 _TIE_hmd1a_common_tie_pow2(fr32 x);
extern fr32 _TIE_hmd1a_common_tie_sigmoid(fr32 x);
extern fr32 _TIE_hmd1a_common_tie_inv(fr32 x);
extern void _TIE_hmd1a_common_tie_ratio(fr32 z /*out*/, fr32 x, fr32 y, atbool bz /*out*/);
extern fr32 _TIE_hmd1a_common_tie_atanratio(fr32 x, atbool bx);
extern fr32 _TIE_hmd1a_common_tie_invsqrt(fr32 x);
extern fr32 _TIE_hmd1a_common_tie_sine(fr32 x);
extern fr32 _TIE_hmd1a_common_tie_cosine(fr32 x);
extern void _TIE_hmd1a_common_tie_log2mul(fr32 z /*out*/, fr32 x, fr32 y, atbool bz /*out*/);
extern fr32 _TIE_hmd1a_common_tie_cspow2(fr32 x, atbool bx);
extern atbool _TIE_hmd1a_common_tie_comp(vr64 x, immediate el_x, vr64 y, immediate el_y);
extern unsigned _TIE_hmd1a_common_tie_eq(vr64 x, immediate el_x, vr64 y, immediate el_y);
extern unsigned _TIE_hmd1a_common_tie_ge(vr64 x, immediate el_x, vr64 y, immediate el_y);
extern unsigned _TIE_hmd1a_common_tie_gt(vr64 x, immediate el_x, vr64 y, immediate el_y);
extern unsigned _TIE_hmd1a_common_tie_le(vr64 x, immediate el_x, vr64 y, immediate el_y);
extern unsigned _TIE_hmd1a_common_tie_lt(vr64 x, immediate el_x, vr64 y, immediate el_y);
extern unsigned _TIE_hmd1a_common_tie_ne(vr64 x, immediate el_x, vr64 y, immediate el_y);
extern atbool _TIE_hmd1a_common_tie_comp_const(vr64 x, immediate el_x, immediate const_idx, immediate exp_adj_const);
extern unsigned _TIE_hmd1a_common_tie_eq_const(vr64 x, immediate el_x, immediate const_idx, immediate exp_adj_const);
extern unsigned _TIE_hmd1a_common_tie_ge_const(vr64 x, immediate el_x, immediate const_idx, immediate exp_adj_const);
extern unsigned _TIE_hmd1a_common_tie_gt_const(vr64 x, immediate el_x, immediate const_idx, immediate exp_adj_const);
extern unsigned _TIE_hmd1a_common_tie_le_const(vr64 x, immediate el_x, immediate const_idx, immediate exp_adj_const);
extern unsigned _TIE_hmd1a_common_tie_lt_const(vr64 x, immediate el_x, immediate const_idx, immediate exp_adj_const);
extern unsigned _TIE_hmd1a_common_tie_ne_const(vr64 x, immediate el_x, immediate const_idx, immediate exp_adj_const);
extern atbool _TIE_hmd1a_common_tie_comp_fr(fr32 fx, fr32 fy);
extern unsigned _TIE_hmd1a_common_tie_eq_fr(fr32 fx, fr32 fy);
extern unsigned _TIE_hmd1a_common_tie_ge_fr(fr32 fx, fr32 fy);
extern unsigned _TIE_hmd1a_common_tie_gt_fr(fr32 fx, fr32 fy);
extern unsigned _TIE_hmd1a_common_tie_le_fr(fr32 fx, fr32 fy);
extern unsigned _TIE_hmd1a_common_tie_lt_fr(fr32 fx, fr32 fy);
extern unsigned _TIE_hmd1a_common_tie_ne_fr(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_neg_fr(fr32 fx);
extern fr32 _TIE_hmd1a_common_tie_abs_fr(fr32 fx);
extern unsigned _TIE_hmd1a_common_tie_deqz(vr64 x);
extern unsigned _TIE_hmd1a_common_tie_dgez(vr64 x);
extern unsigned _TIE_hmd1a_common_tie_dgtz(vr64 x);
extern unsigned _TIE_hmd1a_common_tie_dlez(vr64 x);
extern unsigned _TIE_hmd1a_common_tie_dltz(vr64 x);
extern unsigned _TIE_hmd1a_common_tie_dnez(vr64 x);
extern atbool _TIE_hmd1a_common_tie_veq(vr64 x, vr64 y);
extern atbool _TIE_hmd1a_common_tie_vge(vr64 x, vr64 y);
extern atbool _TIE_hmd1a_common_tie_vgt(vr64 x, vr64 y);
extern atbool _TIE_hmd1a_common_tie_vle(vr64 x, vr64 y);
extern atbool _TIE_hmd1a_common_tie_vlt(vr64 x, vr64 y);
extern atbool _TIE_hmd1a_common_tie_vne(vr64 x, vr64 y);
extern atbool _TIE_hmd1a_common_tie_veq_const(vr64 x, immediate const_idx, immediate exp_adj_const);
extern atbool _TIE_hmd1a_common_tie_vge_const(vr64 x, immediate const_idx, immediate exp_adj_const);
extern atbool _TIE_hmd1a_common_tie_vgt_const(vr64 x, immediate const_idx, immediate exp_adj_const);
extern atbool _TIE_hmd1a_common_tie_vle_const(vr64 x, immediate const_idx, immediate exp_adj_const);
extern atbool _TIE_hmd1a_common_tie_vlt_const(vr64 x, immediate const_idx, immediate exp_adj_const);
extern atbool _TIE_hmd1a_common_tie_vne_const(vr64 x, immediate const_idx, immediate exp_adj_const);
extern fr32 _TIE_hmd1a_common_tie_sel_1b2(fr32 fx, fr32 fy, atbool bx, immediate el_bx1);
extern fr32 _TIE_hmd1a_common_tie_sel_eq(fr32 fx, fr32 fy, atbool bx);
extern fr32 _TIE_hmd1a_common_tie_sel_ge(fr32 fx, fr32 fy, atbool bx);
extern fr32 _TIE_hmd1a_common_tie_sel_gt(fr32 fx, fr32 fy, atbool bx);
extern fr32 _TIE_hmd1a_common_tie_sel_le(fr32 fx, fr32 fy, atbool bx);
extern fr32 _TIE_hmd1a_common_tie_sel_lt(fr32 fx, fr32 fy, atbool bx);
extern fr32 _TIE_hmd1a_common_tie_sel_ne(fr32 fx, fr32 fy, atbool bx);
extern fr32 _TIE_hmd1a_common_tie_sel_ar(fr32 fx, fr32 fy, unsigned sel);
extern vr64 _TIE_hmd1a_common_tie_vsel(vr64 x, vr64 y, atbool bx);
extern vr64 _TIE_hmd1a_common_tie_vsel_ar(vr64 x, vr64 y, unsigned sel);
extern atbool _TIE_hmd1a_common_tie_andb2(atbool bx, atbool by);
extern atbool _TIE_hmd1a_common_tie_andbc2(atbool bx, atbool by);
extern atbool _TIE_hmd1a_common_tie_orb2(atbool bx, atbool by);
extern atbool _TIE_hmd1a_common_tie_orbc2(atbool bx, atbool by);
extern atbool _TIE_hmd1a_common_tie_xorb2(atbool bx, atbool by);
extern unsigned _TIE_hmd1a_common_tie_bcount0_maskI(atbool bx, immediate imask);
extern unsigned _TIE_hmd1a_common_tie_bcount0_maskR(atbool bx, atbool by);
extern unsigned _TIE_hmd1a_common_tie_bcount1_maskI(atbool bx, immediate imask);
extern unsigned _TIE_hmd1a_common_tie_bcount1_maskR(atbool bx, atbool by);
extern unsigned _TIE_hmd1a_common_tie_bfirst0_maskI(atbool bx, immediate imask);
extern unsigned _TIE_hmd1a_common_tie_bfirst0_maskR(atbool bx, atbool by);
extern unsigned _TIE_hmd1a_common_tie_bfirst1_maskI(atbool bx, immediate imask);
extern unsigned _TIE_hmd1a_common_tie_bfirst1_maskR(atbool bx, atbool by);
extern unsigned _TIE_hmd1a_common_tie_blast0_maskI(atbool bx, immediate imask);
extern unsigned _TIE_hmd1a_common_tie_blast0_maskR(atbool bx, atbool by);
extern unsigned _TIE_hmd1a_common_tie_blast1_maskI(atbool bx, immediate imask);
extern unsigned _TIE_hmd1a_common_tie_blast1_maskR(atbool bx, atbool by);
extern unsigned _TIE_hmd1a_common_tie_bgetI(atbool bx, immediate ipos);
extern unsigned _TIE_hmd1a_common_tie_bgetR(atbool bx, unsigned rpos);
extern atbool _TIE_hmd1a_common_tie_bsetI(atbool bx, unsigned rpos, immediate ibit);
extern atbool _TIE_hmd1a_common_tie_bsetR(atbool bx, unsigned rpos, unsigned by);
extern void _TIE_hmd1a_common_tie_exp_adj(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x, unsigned exp_adj_ar);
extern void _TIE_hmd1a_common_tie_exp_adji(vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x, immediate exp_adj_imm);
extern fr32 _TIE_hmd1a_common_tie_exp_adj_fr(fr32 fx, unsigned exp_adj_ar);
extern fr32 _TIE_hmd1a_common_tie_exp_adji_fr(fr32 fx, immediate exp_adj_imm);
extern fr32 _TIE_hmd1a_common_tie_s_neg(fr32 fx);
extern fr32 _TIE_hmd1a_common_tie_s_copy(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_s_and(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_s_andc(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_s_or(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_s_orc(fr32 fx, fr32 fy);
extern fr32 _TIE_hmd1a_common_tie_s_xor(fr32 fx, fr32 fy);
extern vr64 _TIE_hmd1a_common_tie_s_vneg(vr64 x);
extern vr64 _TIE_hmd1a_common_tie_s_vcopy(vr64 x, vr64 y);
extern vr64 _TIE_hmd1a_common_tie_s_vand(vr64 x, vr64 y);
extern vr64 _TIE_hmd1a_common_tie_s_vandc(vr64 x, vr64 y);
extern vr64 _TIE_hmd1a_common_tie_s_vor(vr64 x, vr64 y);
extern vr64 _TIE_hmd1a_common_tie_s_vorc(vr64 x, vr64 y);
extern vr64 _TIE_hmd1a_common_tie_s_vxor(vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_floorp_frac(unsigned floor /*out*/, vr64 z /*inout*/, immediate el_z, vr64 x, immediate el_x, immediate nbits);
extern void _TIE_hmd1a_common_tie_idx_frac(unsigned floor /*out*/, vr64 z /*inout*/, immediate el_z, unsigned input, immediate nbits);
extern fr32 _TIE_hmd1a_common_tie_truncate_fr(fr32 x);
extern void _TIE_hmd1a_common_tie_rmax_idx(unsigned a /*out*/, fr32 fz /*out*/, vr64 x, mir18 idx);
extern void _TIE_hmd1a_common_tie_rmin_idx(unsigned a /*out*/, fr32 fz /*out*/, vr64 x, mir18 idx);
extern void _TIE_hmd1a_common_tie_vmaxmin_init(vr64 z /*out*/, vr64 x, mir18 idx /*out*/);
extern void _TIE_hmd1a_common_tie_vmax_idx(vr64 z /*inout*/, vr64 x, mir18 idx /*inout*/);
extern void _TIE_hmd1a_common_tie_vmin_idx(vr64 z /*inout*/, vr64 x, mir18 idx /*inout*/);
extern vr64 _TIE_hmd1a_common_tie_vmax(vr64 x, vr64 y);
extern vr64 _TIE_hmd1a_common_tie_vmin(vr64 x, vr64 y);
extern void _TIE_hmd1a_common_tie_sortupd_asc_vr(unsigned a /*out*/, vr64 z /*out*/, vr64 x, vr64 y, immediate el_y);
extern void _TIE_hmd1a_common_tie_sortupd_des_vr(unsigned a /*out*/, vr64 z /*out*/, vr64 x, vr64 y, immediate el_y);
extern void _TIE_hmd1a_common_tie_sortupd_asc_ar(unsigned a /*inout*/, vr64 z /*out*/, vr64 x);
extern void _TIE_hmd1a_common_tie_sortupd_des_ar(unsigned a /*inout*/, vr64 z /*out*/, vr64 x);
extern vr64 _TIE_hmd1a_common_tie_vbool(vr64 x, vr64 y, immediate op);
extern unsigned _TIE_hmd1a_common_tie_align_up(unsigned val, unsigned option);
extern mir18 _TIE_hmd1a_common_tie_mv_MIR(mir18 b);
extern ulsr32 _TIE_hmd1a_common_tie_mv_ULSR(ulsr32 b);
extern cr64 _TIE_hmd1a_common_tie_mv_CR(cr64 b);
extern fr32 _TIE_hmd1a_common_tie_ld_FR(const fr32 * addr, immediate fimm);
extern void _TIE_hmd1a_common_tie_st_FR(fr32 fregin, fr32 * addr, immediate fimm);
extern fr32 _TIE_hmd1a_common_tie_ld_FR_idxR(const fr32 * addr, unsigned x);
extern void _TIE_hmd1a_common_tie_st_FR_idxR(fr32 fregin, fr32 * addr, unsigned x);
extern void _TIE_hmd1a_common_tie_ld_FR_postI(fr32 fregout /*out*/, const fr32 * addr /*inout*/, immediate fimm);
extern void _TIE_hmd1a_common_tie_st_FR_postI(fr32 fregin, fr32 * addr /*inout*/, immediate fimm);
extern void _TIE_hmd1a_common_tie_ld_FR_postR(fr32 fregout /*out*/, const fr32 * addr /*inout*/, unsigned x);
extern void _TIE_hmd1a_common_tie_st_FR_postR(fr32 fregin, fr32 * addr /*inout*/, unsigned x);
extern vr64 _TIE_hmd1a_common_tie_ld_VR(const vr64 * addr, immediate vimm);
extern void _TIE_hmd1a_common_tie_st_VR(vr64 vregin, vr64 * addr, immediate vimm);
extern vr64 _TIE_hmd1a_common_tie_ld_VR_idxR(const vr64 * addr, unsigned x);
extern void _TIE_hmd1a_common_tie_st_VR_idxR(vr64 vregin, vr64 * addr, unsigned x);
extern void _TIE_hmd1a_common_tie_ld_VR_postI(vr64 vregout /*out*/, const vr64 * addr /*inout*/, immediate vimm);
extern void _TIE_hmd1a_common_tie_st_VR_postI(vr64 vregin, vr64 * addr /*inout*/, immediate vimm);
extern void _TIE_hmd1a_common_tie_ld_VR_postR(vr64 vregout /*out*/, const vr64 * addr /*inout*/, unsigned x);
extern void _TIE_hmd1a_common_tie_st_VR_postR(vr64 vregin, vr64 * addr /*inout*/, unsigned x);
extern fr32 _TIE_hmd1a_common_tie_mv_FR(fr32 b);
extern unsigned _TIE_hmd1a_common_tie_move_ar_fr(fr32 b);
extern fr32 _TIE_hmd1a_common_tie_move_fr_ar(unsigned b);
extern vr64 _TIE_hmd1a_common_tie_mv_VR(vr64 b);
extern unsigned _TIE_hmd1a_common_tie_move_ar_bbr(atbool b);
extern atbool _TIE_hmd1a_common_tie_move_bbr_ar(unsigned a);
extern void _TIE_hmd1a_common_tie_shift_from_bbr(unsigned a /*inout*/, atbool x);
extern void _TIE_hmd1a_common_tie_shift_to_bbr(unsigned a /*inout*/, atbool z /*out*/);
extern void _TIE_hmd1a_common_tie_ld_ar_x2(unsigned a1_out /*out*/, unsigned a0_out /*out*/, const void * ptr, immediate idx);
extern void _TIE_hmd1a_common_tie_st_ar_x2(void * ptr, immediate idx, unsigned a1_in, unsigned a0_in);
extern void _TIE_hmd1a_common_tie_atbool_storei(atbool a, atbool * b, immediate c);
extern atbool _TIE_hmd1a_common_tie_atbool_loadi(const atbool * b, immediate c);
extern atbool _TIE_hmd1a_common_tie_atbool_move(atbool b);
extern void _TIE_hmd1a_common_tie_ulsr32_storei(ulsr32 a, ulsr32 * b, immediate c);
extern ulsr32 _TIE_hmd1a_common_tie_ulsr32_loadi(const ulsr32 * b, immediate c);
extern void _TIE_hmd1a_common_tie_mir18_storei(mir18 a, mir18 * b, immediate c);
extern mir18 _TIE_hmd1a_common_tie_mir18_loadi(const mir18 * b, immediate c);
extern void _TIE_hmd1a_common_tie_cr64_storei(cr64 a, cr64 * b, immediate c);
extern cr64 _TIE_hmd1a_common_tie_cr64_loadi(const cr64 * b, immediate c);
extern unsigned _TIE_hmd1a_common_tie_RUR_JammingBit(void);
extern void _TIE_hmd1a_common_tie_WUR_JammingBit(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_AccExtend_0(void);
extern void _TIE_hmd1a_common_tie_WUR_AccExtend_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_AccExtend_1(void);
extern void _TIE_hmd1a_common_tie_WUR_AccExtend_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB0_0(void);
extern void _TIE_hmd1a_common_tie_WUR_BB0_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB0_1(void);
extern void _TIE_hmd1a_common_tie_WUR_BB0_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB1_0(void);
extern void _TIE_hmd1a_common_tie_WUR_BB1_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB1_1(void);
extern void _TIE_hmd1a_common_tie_WUR_BB1_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB2_0(void);
extern void _TIE_hmd1a_common_tie_WUR_BB2_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB2_1(void);
extern void _TIE_hmd1a_common_tie_WUR_BB2_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB3_0(void);
extern void _TIE_hmd1a_common_tie_WUR_BB3_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_BB3_1(void);
extern void _TIE_hmd1a_common_tie_WUR_BB3_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_MvmAux(void);
extern void _TIE_hmd1a_common_tie_WUR_MvmAux(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB1_0(void);
extern void _TIE_hmd1a_common_tie_WUR_VB1_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB1_1(void);
extern void _TIE_hmd1a_common_tie_WUR_VB1_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB2_0(void);
extern void _TIE_hmd1a_common_tie_WUR_VB2_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB2_1(void);
extern void _TIE_hmd1a_common_tie_WUR_VB2_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB3_0(void);
extern void _TIE_hmd1a_common_tie_WUR_VB3_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB3_1(void);
extern void _TIE_hmd1a_common_tie_WUR_VB3_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB4_0(void);
extern void _TIE_hmd1a_common_tie_WUR_VB4_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB4_1(void);
extern void _TIE_hmd1a_common_tie_WUR_VB4_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB5_0(void);
extern void _TIE_hmd1a_common_tie_WUR_VB5_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB5_1(void);
extern void _TIE_hmd1a_common_tie_WUR_VB5_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB6_0(void);
extern void _TIE_hmd1a_common_tie_WUR_VB6_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB6_1(void);
extern void _TIE_hmd1a_common_tie_WUR_VB6_1(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB7_0(void);
extern void _TIE_hmd1a_common_tie_WUR_VB7_0(unsigned v);
extern unsigned _TIE_hmd1a_common_tie_RUR_VB7_1(void);
extern void _TIE_hmd1a_common_tie_WUR_VB7_1(unsigned v);
extern mir18 _TIE_hmd1a_common_tie_mir18_move(mir18 b);
extern ulsr32 _TIE_hmd1a_common_tie_ulsr32_move(ulsr32 b);
extern cr64 _TIE_hmd1a_common_tie_cr64_move(cr64 b);
extern fr32 _TIE_hmd1a_common_tie_fr32_move(fr32 b);
extern fr32 _TIE_hmd1a_common_tie_fr32_loadi(const fr32 * p, immediate o);
extern void _TIE_hmd1a_common_tie_fr32_storei(fr32 v, fr32 * p, immediate o);
extern fr32 _TIE_hmd1a_common_tie_fr32_loadx(const fr32 * p, unsigned x);
extern void _TIE_hmd1a_common_tie_fr32_storex(fr32 v, fr32 * p, unsigned x);
extern void _TIE_hmd1a_common_tie_fr32_loadip(fr32 v /*out*/, const fr32 * p /*inout*/, immediate o);
extern void _TIE_hmd1a_common_tie_fr32_storeip(fr32 v, fr32 * p /*inout*/, immediate o);
extern void _TIE_hmd1a_common_tie_fr32_loadxp(fr32 v /*out*/, const fr32 * p /*inout*/, unsigned x);
extern void _TIE_hmd1a_common_tie_fr32_storexp(fr32 v, fr32 * p /*inout*/, unsigned x);
extern int _TIE_hmd1a_common_tie_fr32_rtor_int32(fr32 b);
extern unsigned _TIE_hmd1a_common_tie_fr32_rtor_uint32(fr32 b);
extern fr32 _TIE_hmd1a_common_tie_int32_rtor_fr32(int a);
extern fr32 _TIE_hmd1a_common_tie_uint32_rtor_fr32(unsigned a);
extern vr64 _TIE_hmd1a_common_tie_vr64_move(vr64 b);
extern vr64 _TIE_hmd1a_common_tie_vr64_loadi(const vr64 * p, immediate o);
extern void _TIE_hmd1a_common_tie_vr64_storei(vr64 v, vr64 * p, immediate o);
extern vr64 _TIE_hmd1a_common_tie_vr64_loadx(const vr64 * p, unsigned x);
extern void _TIE_hmd1a_common_tie_vr64_storex(vr64 v, vr64 * p, unsigned x);
extern void _TIE_hmd1a_common_tie_vr64_loadip(vr64 v /*out*/, const vr64 * p /*inout*/, immediate o);
extern void _TIE_hmd1a_common_tie_vr64_storeip(vr64 v, vr64 * p /*inout*/, immediate o);
extern void _TIE_hmd1a_common_tie_vr64_loadxp(vr64 v /*out*/, const vr64 * p /*inout*/, unsigned x);
extern void _TIE_hmd1a_common_tie_vr64_storexp(vr64 v, vr64 * p /*inout*/, unsigned x);
extern fr32 _TIE_hmd1a_common_tie_get_VRH(vr64 b);
extern fr32 _TIE_hmd1a_common_tie_get_VRL(vr64 b);
extern void _TIE_hmd1a_common_tie_set_VRH(vr64 a /*inout*/, fr32 b);
extern void _TIE_hmd1a_common_tie_set_VRL(vr64 a /*inout*/, fr32 b);
extern vr64 _TIE_hmd1a_common_tie_vr64_pair(fr32 hi, fr32 lo);
extern int _TIE_hmd1a_common_tie_atbool_rtor_int32(atbool b);
extern unsigned _TIE_hmd1a_common_tie_atbool_rtor_uint32(atbool b);
extern atbool _TIE_hmd1a_common_tie_int32_rtor_atbool(int a);
extern atbool _TIE_hmd1a_common_tie_uint32_rtor_atbool(unsigned a);

#endif /*__ASSEMBLER__*/
#endif /*_NOCLANGUAGE*/
#endif /*_ASMLANGUAGE*/

#define st_BBR _TIE_hmd1a_common_tie_st_BBR
#define ld_BBR _TIE_hmd1a_common_tie_ld_BBR
#define mv_BBR _TIE_hmd1a_common_tie_mv_BBR
#define st_ULSR _TIE_hmd1a_common_tie_st_ULSR
#define ld_ULSR _TIE_hmd1a_common_tie_ld_ULSR
#define st_MIR _TIE_hmd1a_common_tie_st_MIR
#define ld_MIR _TIE_hmd1a_common_tie_ld_MIR
#define st_CR _TIE_hmd1a_common_tie_st_CR
#define ld_CR _TIE_hmd1a_common_tie_ld_CR
#define dma_ld _TIE_hmd1a_common_tie_dma_ld
#define dma_align_ld _TIE_hmd1a_common_tie_dma_align_ld
#define dma_ldu _TIE_hmd1a_common_tie_dma_ldu
#define dma_flush_ld _TIE_hmd1a_common_tie_dma_flush_ld
#define dma_st _TIE_hmd1a_common_tie_dma_st
#define dma_align_st _TIE_hmd1a_common_tie_dma_align_st
#define dma_stu _TIE_hmd1a_common_tie_dma_stu
#define dma_flush_st _TIE_hmd1a_common_tie_dma_flush_st
#define dma_buf_save _TIE_hmd1a_common_tie_dma_buf_save
#define load32x2_vr_idxR _TIE_hmd1a_common_tie_load32x2_vr_idxR
#define load32x2_vr_idxI _TIE_hmd1a_common_tie_load32x2_vr_idxI
#define load32x2_vr_postR _TIE_hmd1a_common_tie_load32x2_vr_postR
#define load32x2_vr_postI _TIE_hmd1a_common_tie_load32x2_vr_postI
#define load32x2_vr_circI _TIE_hmd1a_common_tie_load32x2_vr_circI
#define load32x1_vr_idxR _TIE_hmd1a_common_tie_load32x1_vr_idxR
#define load32x1_vr_idxI _TIE_hmd1a_common_tie_load32x1_vr_idxI
#define load32x1_vr_postR _TIE_hmd1a_common_tie_load32x1_vr_postR
#define load32x1_vr_postI _TIE_hmd1a_common_tie_load32x1_vr_postI
#define load32x1_vr_circI _TIE_hmd1a_common_tie_load32x1_vr_circI
#define load32x2_vr_bdir _TIE_hmd1a_common_tie_load32x2_vr_bdir
#define load32x2_vr_brev _TIE_hmd1a_common_tie_load32x2_vr_brev
#define load32x2_vr_idxR_perm _TIE_hmd1a_common_tie_load32x2_vr_idxR_perm
#define load32x2_vr_idxI_perm_vr _TIE_hmd1a_common_tie_load32x2_vr_idxI_perm_vr
#define load32x2_vr_postR_perm _TIE_hmd1a_common_tie_load32x2_vr_postR_perm
#define load32x2_vr_postI_perm_vr _TIE_hmd1a_common_tie_load32x2_vr_postI_perm_vr
#define load32x2_vr_circI_perm _TIE_hmd1a_common_tie_load32x2_vr_circI_perm
#define load32x1_vr_idxR_perm _TIE_hmd1a_common_tie_load32x1_vr_idxR_perm
#define load32x1_vr_idxI_perm_vr _TIE_hmd1a_common_tie_load32x1_vr_idxI_perm_vr
#define load32x1_vr_postR_perm _TIE_hmd1a_common_tie_load32x1_vr_postR_perm
#define load32x1_vr_postI_perm_vr _TIE_hmd1a_common_tie_load32x1_vr_postI_perm_vr
#define load32x1_vr_circI_perm _TIE_hmd1a_common_tie_load32x1_vr_circI_perm
#define load16x2_vr_idxR _TIE_hmd1a_common_tie_load16x2_vr_idxR
#define load16x2_vr_idxI _TIE_hmd1a_common_tie_load16x2_vr_idxI
#define load16x2_vr_postR _TIE_hmd1a_common_tie_load16x2_vr_postR
#define load16x2_vr_postI _TIE_hmd1a_common_tie_load16x2_vr_postI
#define load16x2_vr_circI _TIE_hmd1a_common_tie_load16x2_vr_circI
#define load16x1_vr_idxR _TIE_hmd1a_common_tie_load16x1_vr_idxR
#define load16x1_vr_idxI _TIE_hmd1a_common_tie_load16x1_vr_idxI
#define load16x1_vr_postR _TIE_hmd1a_common_tie_load16x1_vr_postR
#define load16x1_vr_postI _TIE_hmd1a_common_tie_load16x1_vr_postI
#define load16x1_vr_circI _TIE_hmd1a_common_tie_load16x1_vr_circI
#define load8x2_vr_idxR _TIE_hmd1a_common_tie_load8x2_vr_idxR
#define load8x2_vr_idxI _TIE_hmd1a_common_tie_load8x2_vr_idxI
#define load8x2_vr_postR _TIE_hmd1a_common_tie_load8x2_vr_postR
#define load8x2_vr_postI _TIE_hmd1a_common_tie_load8x2_vr_postI
#define load8x2_vr_circI _TIE_hmd1a_common_tie_load8x2_vr_circI
#define load8x1_vr_idxR _TIE_hmd1a_common_tie_load8x1_vr_idxR
#define load8x1_vr_idxI _TIE_hmd1a_common_tie_load8x1_vr_idxI
#define load8x1_vr_postR _TIE_hmd1a_common_tie_load8x1_vr_postR
#define load8x1_vr_postI _TIE_hmd1a_common_tie_load8x1_vr_postI
#define load8x1_vr_circI _TIE_hmd1a_common_tie_load8x1_vr_circI
#define align_32x2_load _TIE_hmd1a_common_tie_align_32x2_load
#define load_32x2_vr_a _TIE_hmd1a_common_tie_load_32x2_vr_a
#define load_24x2_vr_a _TIE_hmd1a_common_tie_load_24x2_vr_a
#define load_32x2_vr_a_circ _TIE_hmd1a_common_tie_load_32x2_vr_a_circ
#define store32x2_vr_idxR _TIE_hmd1a_common_tie_store32x2_vr_idxR
#define store32x2_vr_idxI _TIE_hmd1a_common_tie_store32x2_vr_idxI
#define store32x2_vr_postR _TIE_hmd1a_common_tie_store32x2_vr_postR
#define store32x2_vr_postI _TIE_hmd1a_common_tie_store32x2_vr_postI
#define store32x2_vr_circI _TIE_hmd1a_common_tie_store32x2_vr_circI
#define store32x1_vr_idxR _TIE_hmd1a_common_tie_store32x1_vr_idxR
#define store32x1_vr_idxI _TIE_hmd1a_common_tie_store32x1_vr_idxI
#define store32x1_vr_postR _TIE_hmd1a_common_tie_store32x1_vr_postR
#define store32x1_vr_postI _TIE_hmd1a_common_tie_store32x1_vr_postI
#define store32x1_vr_circI _TIE_hmd1a_common_tie_store32x1_vr_circI
#define store32x2_vr_br_idxR _TIE_hmd1a_common_tie_store32x2_vr_br_idxR
#define store32x2_vr_br_idxI _TIE_hmd1a_common_tie_store32x2_vr_br_idxI
#define store32x2_vr_br_postR _TIE_hmd1a_common_tie_store32x2_vr_br_postR
#define store32x2_vr_br_postI _TIE_hmd1a_common_tie_store32x2_vr_br_postI
#define store32x2_vr_br_circI _TIE_hmd1a_common_tie_store32x2_vr_br_circI
#define store32x1_vr_br_idxR _TIE_hmd1a_common_tie_store32x1_vr_br_idxR
#define store32x1_vr_br_idxI _TIE_hmd1a_common_tie_store32x1_vr_br_idxI
#define store32x1_vr_br_postR _TIE_hmd1a_common_tie_store32x1_vr_br_postR
#define store32x1_vr_br_postI _TIE_hmd1a_common_tie_store32x1_vr_br_postI
#define store32x1_vr_br_circI _TIE_hmd1a_common_tie_store32x1_vr_br_circI
#define store32x2_vr_br_bdir _TIE_hmd1a_common_tie_store32x2_vr_br_bdir
#define store32x2_vr_br_brev _TIE_hmd1a_common_tie_store32x2_vr_br_brev
#define store16x2_vr_idxR _TIE_hmd1a_common_tie_store16x2_vr_idxR
#define store16x2_vr_idxI _TIE_hmd1a_common_tie_store16x2_vr_idxI
#define store16x2_vr_postR _TIE_hmd1a_common_tie_store16x2_vr_postR
#define store16x2_vr_postI _TIE_hmd1a_common_tie_store16x2_vr_postI
#define store16x2_vr_circI _TIE_hmd1a_common_tie_store16x2_vr_circI
#define store16x1_vr_idxR _TIE_hmd1a_common_tie_store16x1_vr_idxR
#define store16x1_vr_idxI _TIE_hmd1a_common_tie_store16x1_vr_idxI
#define store16x1_vr_postR _TIE_hmd1a_common_tie_store16x1_vr_postR
#define store16x1_vr_postI _TIE_hmd1a_common_tie_store16x1_vr_postI
#define store16x1_vr_circI _TIE_hmd1a_common_tie_store16x1_vr_circI
#define store8x2_vr_idxR _TIE_hmd1a_common_tie_store8x2_vr_idxR
#define store8x2_vr_idxI _TIE_hmd1a_common_tie_store8x2_vr_idxI
#define store8x2_vr_postR _TIE_hmd1a_common_tie_store8x2_vr_postR
#define store8x2_vr_postI _TIE_hmd1a_common_tie_store8x2_vr_postI
#define store8x2_vr_circI _TIE_hmd1a_common_tie_store8x2_vr_circI
#define store8x1_vr_idxR _TIE_hmd1a_common_tie_store8x1_vr_idxR
#define store8x1_vr_idxI _TIE_hmd1a_common_tie_store8x1_vr_idxI
#define store8x1_vr_postR _TIE_hmd1a_common_tie_store8x1_vr_postR
#define store8x1_vr_postI _TIE_hmd1a_common_tie_store8x1_vr_postI
#define store8x1_vr_circI _TIE_hmd1a_common_tie_store8x1_vr_circI
#define align_32x2_store _TIE_hmd1a_common_tie_align_32x2_store
#define store_32x2_vr_a _TIE_hmd1a_common_tie_store_32x2_vr_a
#define store_24x2_vr_a _TIE_hmd1a_common_tie_store_24x2_vr_a
#define store_32x2_vr_a_circ _TIE_hmd1a_common_tie_store_32x2_vr_a_circ
#define flush_32x2 _TIE_hmd1a_common_tie_flush_32x2
#define load_fr_postI _TIE_hmd1a_common_tie_load_fr_postI
#define store_fr_postI _TIE_hmd1a_common_tie_store_fr_postI
#define brev_upd _TIE_hmd1a_common_tie_brev_upd
#define brev_upd_ext _TIE_hmd1a_common_tie_brev_upd_ext
#define move32_ar_vr _TIE_hmd1a_common_tie_move32_ar_vr
#define move32_vr_ar _TIE_hmd1a_common_tie_move32_vr_ar
#define move32_ar_vr_idx _TIE_hmd1a_common_tie_move32_ar_vr_idx
#define move32_fr_vr_idx _TIE_hmd1a_common_tie_move32_fr_vr_idx
#define move_fr_eqz _TIE_hmd1a_common_tie_move_fr_eqz
#define move_fr_gez _TIE_hmd1a_common_tie_move_fr_gez
#define move_fr_gtz _TIE_hmd1a_common_tie_move_fr_gtz
#define move_fr_lez _TIE_hmd1a_common_tie_move_fr_lez
#define move_fr_ltz _TIE_hmd1a_common_tie_move_fr_ltz
#define move_fr_nez _TIE_hmd1a_common_tie_move_fr_nez
#define move_fr_sat _TIE_hmd1a_common_tie_move_fr_sat
#define move_fr_arnz _TIE_hmd1a_common_tie_move_fr_arnz
#define vmove_vr_eqz _TIE_hmd1a_common_tie_vmove_vr_eqz
#define vmove_vr_gez _TIE_hmd1a_common_tie_vmove_vr_gez
#define vmove_vr_gtz _TIE_hmd1a_common_tie_vmove_vr_gtz
#define vmove_vr_lez _TIE_hmd1a_common_tie_vmove_vr_lez
#define vmove_vr_ltz _TIE_hmd1a_common_tie_vmove_vr_ltz
#define vmove_vr_nez _TIE_hmd1a_common_tie_vmove_vr_nez
#define vmove_vr_sat _TIE_hmd1a_common_tie_vmove_vr_sat
#define replicate _TIE_hmd1a_common_tie_replicate
#define replicate_ar _TIE_hmd1a_common_tie_replicate_ar
#define vreplicate _TIE_hmd1a_common_tie_vreplicate
#define vreplicate_fr _TIE_hmd1a_common_tie_vreplicate_fr
#define convert_16I_to_32F_x1 _TIE_hmd1a_common_tie_convert_16I_to_32F_x1
#define convert_16I_to_32F_x2 _TIE_hmd1a_common_tie_convert_16I_to_32F_x2
#define convert_32F_to_16I_x1 _TIE_hmd1a_common_tie_convert_32F_to_16I_x1
#define convert_32F_to_16I_x2 _TIE_hmd1a_common_tie_convert_32F_to_16I_x2
#define convert_32F_to_16F_x1 _TIE_hmd1a_common_tie_convert_32F_to_16F_x1
#define convert_32F_to_16F_x2 _TIE_hmd1a_common_tie_convert_32F_to_16F_x2
#define convert_16F_to_32F_x1 _TIE_hmd1a_common_tie_convert_16F_to_32F_x1
#define convert_16F_to_32F_x2 _TIE_hmd1a_common_tie_convert_16F_to_32F_x2
#define convert_32I_to_32F_x1 _TIE_hmd1a_common_tie_convert_32I_to_32F_x1
#define convert_32F_to_32I_x1 _TIE_hmd1a_common_tie_convert_32F_to_32I_x1
#define convert_IEEE_float_to_32F_x2 _TIE_hmd1a_common_tie_convert_IEEE_float_to_32F_x2
#define convert_32F_to_IEEE_float_x2 _TIE_hmd1a_common_tie_convert_32F_to_IEEE_float_x2
#define convert_32I_to_64F _TIE_hmd1a_common_tie_convert_32I_to_64F
#define convert_64F_to_32I _TIE_hmd1a_common_tie_convert_64F_to_32I
#define convert_32F_to_64F _TIE_hmd1a_common_tie_convert_32F_to_64F
#define convert_64F_to_32F _TIE_hmd1a_common_tie_convert_64F_to_32F
#define convert_IEEE_double_to_64F _TIE_hmd1a_common_tie_convert_IEEE_double_to_64F
#define convert_64F_to_IEEE_double _TIE_hmd1a_common_tie_convert_64F_to_IEEE_double
#define vadd_perm _TIE_hmd1a_common_tie_vadd_perm
#define vsum_perm _TIE_hmd1a_common_tie_vsum_perm
#define vmul_perm _TIE_hmd1a_common_tie_vmul_perm
#define vmac_perm _TIE_hmd1a_common_tie_vmac_perm
#define vmac_boost _TIE_hmd1a_common_tie_vmac_boost
#define vblend _TIE_hmd1a_common_tie_vblend
#define vblend_add _TIE_hmd1a_common_tie_vblend_add
#define vblend_boost _TIE_hmd1a_common_tie_vblend_boost
#define fadds _TIE_hmd1a_common_tie_fadds
#define fmuls _TIE_hmd1a_common_tie_fmuls
#define fmacs _TIE_hmd1a_common_tie_fmacs
#define dadds _TIE_hmd1a_common_tie_dadds
#define dmuls _TIE_hmd1a_common_tie_dmuls
#define dmacs _TIE_hmd1a_common_tie_dmacs
#define vadds _TIE_hmd1a_common_tie_vadds
#define vmuls _TIE_hmd1a_common_tie_vmuls
#define vmacs _TIE_hmd1a_common_tie_vmacs
#define cmul _TIE_hmd1a_common_tie_cmul
#define cmac _TIE_hmd1a_common_tie_cmac
#define cmas _TIE_hmd1a_common_tie_cmas
#define vmulf _TIE_hmd1a_common_tie_vmulf
#define vmacf _TIE_hmd1a_common_tie_vmacf
#define vabs _TIE_hmd1a_common_tie_vabs
#define vexp_adj _TIE_hmd1a_common_tie_vexp_adj
#define vexp_adji _TIE_hmd1a_common_tie_vexp_adji
#define vpermi _TIE_hmd1a_common_tie_vpermi
#define seta_vr _TIE_hmd1a_common_tie_seta_vr
#define vseta_vr _TIE_hmd1a_common_tie_vseta_vr
#define seta_ar _TIE_hmd1a_common_tie_seta_ar
#define seta_fr _TIE_hmd1a_common_tie_seta_fr
#define load_AccExtend_postI _TIE_hmd1a_common_tie_load_AccExtend_postI
#define load32x1_vr_idx16vr _TIE_hmd1a_common_tie_load32x1_vr_idx16vr
#define load_BB0_postI _TIE_hmd1a_common_tie_load_BB0_postI
#define load_BB1_postI _TIE_hmd1a_common_tie_load_BB1_postI
#define load_BB2_postI _TIE_hmd1a_common_tie_load_BB2_postI
#define load_BB3_postI _TIE_hmd1a_common_tie_load_BB3_postI
#define load_VB1_postI _TIE_hmd1a_common_tie_load_VB1_postI
#define load_VB2_postI _TIE_hmd1a_common_tie_load_VB2_postI
#define load_VB3_postI _TIE_hmd1a_common_tie_load_VB3_postI
#define load_VB4_postI _TIE_hmd1a_common_tie_load_VB4_postI
#define load_VB5_postI _TIE_hmd1a_common_tie_load_VB5_postI
#define load_VB6_postI _TIE_hmd1a_common_tie_load_VB6_postI
#define load_VB7_postI _TIE_hmd1a_common_tie_load_VB7_postI
#define load_32x2_vr_a_bounded _TIE_hmd1a_common_tie_load_32x2_vr_a_bounded
#define load_BBx_VB67_a_bounded _TIE_hmd1a_common_tie_load_BBx_VB67_a_bounded
#define flush_32x2_bounded _TIE_hmd1a_common_tie_flush_32x2_bounded
#define store_32x2_vr_a_bounded _TIE_hmd1a_common_tie_store_32x2_vr_a_bounded
#define store_AccExtend_postI _TIE_hmd1a_common_tie_store_AccExtend_postI
#define store_BB0_postI _TIE_hmd1a_common_tie_store_BB0_postI
#define store_BB1_postI _TIE_hmd1a_common_tie_store_BB1_postI
#define store_BB2_postI _TIE_hmd1a_common_tie_store_BB2_postI
#define store_BB3_postI _TIE_hmd1a_common_tie_store_BB3_postI
#define store_VB1_postI _TIE_hmd1a_common_tie_store_VB1_postI
#define store_VB2_postI _TIE_hmd1a_common_tie_store_VB2_postI
#define store_VB3_postI _TIE_hmd1a_common_tie_store_VB3_postI
#define store_VB4_postI _TIE_hmd1a_common_tie_store_VB4_postI
#define store_VB5_postI _TIE_hmd1a_common_tie_store_VB5_postI
#define store_VB6_postI _TIE_hmd1a_common_tie_store_VB6_postI
#define store_VB7_postI _TIE_hmd1a_common_tie_store_VB7_postI
#define afloat_exp_extract _TIE_hmd1a_common_tie_afloat_exp_extract
#define mov_AccExtend_vr _TIE_hmd1a_common_tie_mov_AccExtend_vr
#define mov_vr_AccExtend _TIE_hmd1a_common_tie_mov_vr_AccExtend
#define mov_BB_VB67_to_vrVB_VB45 _TIE_hmd1a_common_tie_mov_BB_VB67_to_vrVB_VB45
#define mov_vrVB_VB45_to_BB_VB67 _TIE_hmd1a_common_tie_mov_vrVB_VB45_to_BB_VB67
#define precess_16bits _TIE_hmd1a_common_tie_precess_16bits
#define set_BB_vrVB67_zero _TIE_hmd1a_common_tie_set_BB_vrVB67_zero
#define exp_shift_amount _TIE_hmd1a_common_tie_exp_shift_amount
#define rnd_sat_pack _TIE_hmd1a_common_tie_rnd_sat_pack
#define rectify32_into8 _TIE_hmd1a_common_tie_rectify32_into8
#define shift8_into32_arith _TIE_hmd1a_common_tie_shift8_into32_arith
#define shift32_arith _TIE_hmd1a_common_tie_shift32_arith
#define mac8bx8b _TIE_hmd1a_common_tie_mac8bx8b
#define mac8bx8b_sparse _TIE_hmd1a_common_tie_mac8bx8b_sparse
#define mac8bx8b_conv _TIE_hmd1a_common_tie_mac8bx8b_conv
#define mir_init _TIE_hmd1a_common_tie_mir_init
#define f_abs _TIE_hmd1a_common_tie_f_abs
#define fclamp _TIE_hmd1a_common_tie_fclamp
#define fclamp_bp _TIE_hmd1a_common_tie_fclamp_bp
#define fclamp_one _TIE_hmd1a_common_tie_fclamp_one
#define fmax _TIE_hmd1a_common_tie_fmax
#define fmin _TIE_hmd1a_common_tie_fmin
#define max_fr _TIE_hmd1a_common_tie_max_fr
#define min_fr _TIE_hmd1a_common_tie_min_fr
#define log2 _TIE_hmd1a_common_tie_log2
#define pow2 _TIE_hmd1a_common_tie_pow2
#define sigmoid _TIE_hmd1a_common_tie_sigmoid
#define inv _TIE_hmd1a_common_tie_inv
#define ratio _TIE_hmd1a_common_tie_ratio
#define atanratio _TIE_hmd1a_common_tie_atanratio
#define invsqrt _TIE_hmd1a_common_tie_invsqrt
#define sine _TIE_hmd1a_common_tie_sine
#define cosine _TIE_hmd1a_common_tie_cosine
#define log2mul _TIE_hmd1a_common_tie_log2mul
#define cspow2 _TIE_hmd1a_common_tie_cspow2
#define comp _TIE_hmd1a_common_tie_comp
#define eq _TIE_hmd1a_common_tie_eq
#define ge _TIE_hmd1a_common_tie_ge
#define gt _TIE_hmd1a_common_tie_gt
#define le _TIE_hmd1a_common_tie_le
#define lt _TIE_hmd1a_common_tie_lt
#define ne _TIE_hmd1a_common_tie_ne
#define comp_const _TIE_hmd1a_common_tie_comp_const
#define eq_const _TIE_hmd1a_common_tie_eq_const
#define ge_const _TIE_hmd1a_common_tie_ge_const
#define gt_const _TIE_hmd1a_common_tie_gt_const
#define le_const _TIE_hmd1a_common_tie_le_const
#define lt_const _TIE_hmd1a_common_tie_lt_const
#define ne_const _TIE_hmd1a_common_tie_ne_const
#define comp_fr _TIE_hmd1a_common_tie_comp_fr
#define eq_fr _TIE_hmd1a_common_tie_eq_fr
#define ge_fr _TIE_hmd1a_common_tie_ge_fr
#define gt_fr _TIE_hmd1a_common_tie_gt_fr
#define le_fr _TIE_hmd1a_common_tie_le_fr
#define lt_fr _TIE_hmd1a_common_tie_lt_fr
#define ne_fr _TIE_hmd1a_common_tie_ne_fr
#define neg_fr _TIE_hmd1a_common_tie_neg_fr
#define abs_fr _TIE_hmd1a_common_tie_abs_fr
#define deqz _TIE_hmd1a_common_tie_deqz
#define dgez _TIE_hmd1a_common_tie_dgez
#define dgtz _TIE_hmd1a_common_tie_dgtz
#define dlez _TIE_hmd1a_common_tie_dlez
#define dltz _TIE_hmd1a_common_tie_dltz
#define dnez _TIE_hmd1a_common_tie_dnez
#define veq _TIE_hmd1a_common_tie_veq
#define vge _TIE_hmd1a_common_tie_vge
#define vgt _TIE_hmd1a_common_tie_vgt
#define vle _TIE_hmd1a_common_tie_vle
#define vlt _TIE_hmd1a_common_tie_vlt
#define vne _TIE_hmd1a_common_tie_vne
#define veq_const _TIE_hmd1a_common_tie_veq_const
#define vge_const _TIE_hmd1a_common_tie_vge_const
#define vgt_const _TIE_hmd1a_common_tie_vgt_const
#define vle_const _TIE_hmd1a_common_tie_vle_const
#define vlt_const _TIE_hmd1a_common_tie_vlt_const
#define vne_const _TIE_hmd1a_common_tie_vne_const
#define sel_1b2 _TIE_hmd1a_common_tie_sel_1b2
#define sel_eq _TIE_hmd1a_common_tie_sel_eq
#define sel_ge _TIE_hmd1a_common_tie_sel_ge
#define sel_gt _TIE_hmd1a_common_tie_sel_gt
#define sel_le _TIE_hmd1a_common_tie_sel_le
#define sel_lt _TIE_hmd1a_common_tie_sel_lt
#define sel_ne _TIE_hmd1a_common_tie_sel_ne
#define sel_ar _TIE_hmd1a_common_tie_sel_ar
#define vsel _TIE_hmd1a_common_tie_vsel
#define vsel_ar _TIE_hmd1a_common_tie_vsel_ar
#define andb2 _TIE_hmd1a_common_tie_andb2
#define andbc2 _TIE_hmd1a_common_tie_andbc2
#define orb2 _TIE_hmd1a_common_tie_orb2
#define orbc2 _TIE_hmd1a_common_tie_orbc2
#define xorb2 _TIE_hmd1a_common_tie_xorb2
#define bcount0_maskI _TIE_hmd1a_common_tie_bcount0_maskI
#define bcount0_maskR _TIE_hmd1a_common_tie_bcount0_maskR
#define bcount1_maskI _TIE_hmd1a_common_tie_bcount1_maskI
#define bcount1_maskR _TIE_hmd1a_common_tie_bcount1_maskR
#define bfirst0_maskI _TIE_hmd1a_common_tie_bfirst0_maskI
#define bfirst0_maskR _TIE_hmd1a_common_tie_bfirst0_maskR
#define bfirst1_maskI _TIE_hmd1a_common_tie_bfirst1_maskI
#define bfirst1_maskR _TIE_hmd1a_common_tie_bfirst1_maskR
#define blast0_maskI _TIE_hmd1a_common_tie_blast0_maskI
#define blast0_maskR _TIE_hmd1a_common_tie_blast0_maskR
#define blast1_maskI _TIE_hmd1a_common_tie_blast1_maskI
#define blast1_maskR _TIE_hmd1a_common_tie_blast1_maskR
#define bgetI _TIE_hmd1a_common_tie_bgetI
#define bgetR _TIE_hmd1a_common_tie_bgetR
#define bsetI _TIE_hmd1a_common_tie_bsetI
#define bsetR _TIE_hmd1a_common_tie_bsetR
#define exp_adj _TIE_hmd1a_common_tie_exp_adj
#define exp_adji _TIE_hmd1a_common_tie_exp_adji
#define exp_adj_fr _TIE_hmd1a_common_tie_exp_adj_fr
#define exp_adji_fr _TIE_hmd1a_common_tie_exp_adji_fr
#define s_neg _TIE_hmd1a_common_tie_s_neg
#define s_copy _TIE_hmd1a_common_tie_s_copy
#define s_and _TIE_hmd1a_common_tie_s_and
#define s_andc _TIE_hmd1a_common_tie_s_andc
#define s_or _TIE_hmd1a_common_tie_s_or
#define s_orc _TIE_hmd1a_common_tie_s_orc
#define s_xor _TIE_hmd1a_common_tie_s_xor
#define s_vneg _TIE_hmd1a_common_tie_s_vneg
#define s_vcopy _TIE_hmd1a_common_tie_s_vcopy
#define s_vand _TIE_hmd1a_common_tie_s_vand
#define s_vandc _TIE_hmd1a_common_tie_s_vandc
#define s_vor _TIE_hmd1a_common_tie_s_vor
#define s_vorc _TIE_hmd1a_common_tie_s_vorc
#define s_vxor _TIE_hmd1a_common_tie_s_vxor
#define floorp_frac _TIE_hmd1a_common_tie_floorp_frac
#define idx_frac _TIE_hmd1a_common_tie_idx_frac
#define truncate_fr _TIE_hmd1a_common_tie_truncate_fr
#define rmax_idx _TIE_hmd1a_common_tie_rmax_idx
#define rmin_idx _TIE_hmd1a_common_tie_rmin_idx
#define vmaxmin_init _TIE_hmd1a_common_tie_vmaxmin_init
#define vmax_idx _TIE_hmd1a_common_tie_vmax_idx
#define vmin_idx _TIE_hmd1a_common_tie_vmin_idx
#define vmax _TIE_hmd1a_common_tie_vmax
#define vmin _TIE_hmd1a_common_tie_vmin
#define sortupd_asc_vr _TIE_hmd1a_common_tie_sortupd_asc_vr
#define sortupd_des_vr _TIE_hmd1a_common_tie_sortupd_des_vr
#define sortupd_asc_ar _TIE_hmd1a_common_tie_sortupd_asc_ar
#define sortupd_des_ar _TIE_hmd1a_common_tie_sortupd_des_ar
#define vbool _TIE_hmd1a_common_tie_vbool
#define align_up _TIE_hmd1a_common_tie_align_up
#define mv_MIR _TIE_hmd1a_common_tie_mv_MIR
#define mv_ULSR _TIE_hmd1a_common_tie_mv_ULSR
#define mv_CR _TIE_hmd1a_common_tie_mv_CR
#define ld_FR _TIE_hmd1a_common_tie_ld_FR
#define st_FR _TIE_hmd1a_common_tie_st_FR
#define ld_FR_idxR _TIE_hmd1a_common_tie_ld_FR_idxR
#define st_FR_idxR _TIE_hmd1a_common_tie_st_FR_idxR
#define ld_FR_postI _TIE_hmd1a_common_tie_ld_FR_postI
#define st_FR_postI _TIE_hmd1a_common_tie_st_FR_postI
#define ld_FR_postR _TIE_hmd1a_common_tie_ld_FR_postR
#define st_FR_postR _TIE_hmd1a_common_tie_st_FR_postR
#define ld_VR _TIE_hmd1a_common_tie_ld_VR
#define st_VR _TIE_hmd1a_common_tie_st_VR
#define ld_VR_idxR _TIE_hmd1a_common_tie_ld_VR_idxR
#define st_VR_idxR _TIE_hmd1a_common_tie_st_VR_idxR
#define ld_VR_postI _TIE_hmd1a_common_tie_ld_VR_postI
#define st_VR_postI _TIE_hmd1a_common_tie_st_VR_postI
#define ld_VR_postR _TIE_hmd1a_common_tie_ld_VR_postR
#define st_VR_postR _TIE_hmd1a_common_tie_st_VR_postR
#define mv_FR _TIE_hmd1a_common_tie_mv_FR
#define move_ar_fr _TIE_hmd1a_common_tie_move_ar_fr
#define move_fr_ar _TIE_hmd1a_common_tie_move_fr_ar
#define mv_VR _TIE_hmd1a_common_tie_mv_VR
#define move_ar_bbr _TIE_hmd1a_common_tie_move_ar_bbr
#define move_bbr_ar _TIE_hmd1a_common_tie_move_bbr_ar
#define shift_from_bbr _TIE_hmd1a_common_tie_shift_from_bbr
#define shift_to_bbr _TIE_hmd1a_common_tie_shift_to_bbr
#define ld_ar_x2 _TIE_hmd1a_common_tie_ld_ar_x2
#define st_ar_x2 _TIE_hmd1a_common_tie_st_ar_x2
#define atbool_storei _TIE_hmd1a_common_tie_atbool_storei
#define atbool_loadi _TIE_hmd1a_common_tie_atbool_loadi
#define atbool_move _TIE_hmd1a_common_tie_atbool_move
#define ulsr32_storei _TIE_hmd1a_common_tie_ulsr32_storei
#define ulsr32_loadi _TIE_hmd1a_common_tie_ulsr32_loadi
#define mir18_storei _TIE_hmd1a_common_tie_mir18_storei
#define mir18_loadi _TIE_hmd1a_common_tie_mir18_loadi
#define cr64_storei _TIE_hmd1a_common_tie_cr64_storei
#define cr64_loadi _TIE_hmd1a_common_tie_cr64_loadi
#define RUR_JammingBit _TIE_hmd1a_common_tie_RUR_JammingBit
#define RJammingBit _TIE_hmd1a_common_tie_RUR_JammingBit
#define RUR0 _TIE_hmd1a_common_tie_RUR_JammingBit
#define WUR_JammingBit _TIE_hmd1a_common_tie_WUR_JammingBit
#define WJammingBit _TIE_hmd1a_common_tie_WUR_JammingBit
#define WUR0 _TIE_hmd1a_common_tie_WUR_JammingBit
#define RUR_AccExtend_0 _TIE_hmd1a_common_tie_RUR_AccExtend_0
#define RAccExtend_0 _TIE_hmd1a_common_tie_RUR_AccExtend_0
#define RUR1 _TIE_hmd1a_common_tie_RUR_AccExtend_0
#define WUR_AccExtend_0 _TIE_hmd1a_common_tie_WUR_AccExtend_0
#define WAccExtend_0 _TIE_hmd1a_common_tie_WUR_AccExtend_0
#define WUR1 _TIE_hmd1a_common_tie_WUR_AccExtend_0
#define RUR_AccExtend_1 _TIE_hmd1a_common_tie_RUR_AccExtend_1
#define RAccExtend_1 _TIE_hmd1a_common_tie_RUR_AccExtend_1
#define RUR2 _TIE_hmd1a_common_tie_RUR_AccExtend_1
#define WUR_AccExtend_1 _TIE_hmd1a_common_tie_WUR_AccExtend_1
#define WAccExtend_1 _TIE_hmd1a_common_tie_WUR_AccExtend_1
#define WUR2 _TIE_hmd1a_common_tie_WUR_AccExtend_1
#define RUR_BB0_0 _TIE_hmd1a_common_tie_RUR_BB0_0
#define RBB0_0 _TIE_hmd1a_common_tie_RUR_BB0_0
#define RUR3 _TIE_hmd1a_common_tie_RUR_BB0_0
#define WUR_BB0_0 _TIE_hmd1a_common_tie_WUR_BB0_0
#define WBB0_0 _TIE_hmd1a_common_tie_WUR_BB0_0
#define WUR3 _TIE_hmd1a_common_tie_WUR_BB0_0
#define RUR_BB0_1 _TIE_hmd1a_common_tie_RUR_BB0_1
#define RBB0_1 _TIE_hmd1a_common_tie_RUR_BB0_1
#define RUR4 _TIE_hmd1a_common_tie_RUR_BB0_1
#define WUR_BB0_1 _TIE_hmd1a_common_tie_WUR_BB0_1
#define WBB0_1 _TIE_hmd1a_common_tie_WUR_BB0_1
#define WUR4 _TIE_hmd1a_common_tie_WUR_BB0_1
#define RUR_BB1_0 _TIE_hmd1a_common_tie_RUR_BB1_0
#define RBB1_0 _TIE_hmd1a_common_tie_RUR_BB1_0
#define RUR5 _TIE_hmd1a_common_tie_RUR_BB1_0
#define WUR_BB1_0 _TIE_hmd1a_common_tie_WUR_BB1_0
#define WBB1_0 _TIE_hmd1a_common_tie_WUR_BB1_0
#define WUR5 _TIE_hmd1a_common_tie_WUR_BB1_0
#define RUR_BB1_1 _TIE_hmd1a_common_tie_RUR_BB1_1
#define RBB1_1 _TIE_hmd1a_common_tie_RUR_BB1_1
#define RUR6 _TIE_hmd1a_common_tie_RUR_BB1_1
#define WUR_BB1_1 _TIE_hmd1a_common_tie_WUR_BB1_1
#define WBB1_1 _TIE_hmd1a_common_tie_WUR_BB1_1
#define WUR6 _TIE_hmd1a_common_tie_WUR_BB1_1
#define RUR_BB2_0 _TIE_hmd1a_common_tie_RUR_BB2_0
#define RBB2_0 _TIE_hmd1a_common_tie_RUR_BB2_0
#define RUR7 _TIE_hmd1a_common_tie_RUR_BB2_0
#define WUR_BB2_0 _TIE_hmd1a_common_tie_WUR_BB2_0
#define WBB2_0 _TIE_hmd1a_common_tie_WUR_BB2_0
#define WUR7 _TIE_hmd1a_common_tie_WUR_BB2_0
#define RUR_BB2_1 _TIE_hmd1a_common_tie_RUR_BB2_1
#define RBB2_1 _TIE_hmd1a_common_tie_RUR_BB2_1
#define RUR8 _TIE_hmd1a_common_tie_RUR_BB2_1
#define WUR_BB2_1 _TIE_hmd1a_common_tie_WUR_BB2_1
#define WBB2_1 _TIE_hmd1a_common_tie_WUR_BB2_1
#define WUR8 _TIE_hmd1a_common_tie_WUR_BB2_1
#define RUR_BB3_0 _TIE_hmd1a_common_tie_RUR_BB3_0
#define RBB3_0 _TIE_hmd1a_common_tie_RUR_BB3_0
#define RUR9 _TIE_hmd1a_common_tie_RUR_BB3_0
#define WUR_BB3_0 _TIE_hmd1a_common_tie_WUR_BB3_0
#define WBB3_0 _TIE_hmd1a_common_tie_WUR_BB3_0
#define WUR9 _TIE_hmd1a_common_tie_WUR_BB3_0
#define RUR_BB3_1 _TIE_hmd1a_common_tie_RUR_BB3_1
#define RBB3_1 _TIE_hmd1a_common_tie_RUR_BB3_1
#define RUR10 _TIE_hmd1a_common_tie_RUR_BB3_1
#define WUR_BB3_1 _TIE_hmd1a_common_tie_WUR_BB3_1
#define WBB3_1 _TIE_hmd1a_common_tie_WUR_BB3_1
#define WUR10 _TIE_hmd1a_common_tie_WUR_BB3_1
#define RUR_MvmAux _TIE_hmd1a_common_tie_RUR_MvmAux
#define RMvmAux _TIE_hmd1a_common_tie_RUR_MvmAux
#define RUR11 _TIE_hmd1a_common_tie_RUR_MvmAux
#define WUR_MvmAux _TIE_hmd1a_common_tie_WUR_MvmAux
#define WMvmAux _TIE_hmd1a_common_tie_WUR_MvmAux
#define WUR11 _TIE_hmd1a_common_tie_WUR_MvmAux
#define RUR_VB1_0 _TIE_hmd1a_common_tie_RUR_VB1_0
#define RVB1_0 _TIE_hmd1a_common_tie_RUR_VB1_0
#define RUR12 _TIE_hmd1a_common_tie_RUR_VB1_0
#define WUR_VB1_0 _TIE_hmd1a_common_tie_WUR_VB1_0
#define WVB1_0 _TIE_hmd1a_common_tie_WUR_VB1_0
#define WUR12 _TIE_hmd1a_common_tie_WUR_VB1_0
#define RUR_VB1_1 _TIE_hmd1a_common_tie_RUR_VB1_1
#define RVB1_1 _TIE_hmd1a_common_tie_RUR_VB1_1
#define RUR13 _TIE_hmd1a_common_tie_RUR_VB1_1
#define WUR_VB1_1 _TIE_hmd1a_common_tie_WUR_VB1_1
#define WVB1_1 _TIE_hmd1a_common_tie_WUR_VB1_1
#define WUR13 _TIE_hmd1a_common_tie_WUR_VB1_1
#define RUR_VB2_0 _TIE_hmd1a_common_tie_RUR_VB2_0
#define RVB2_0 _TIE_hmd1a_common_tie_RUR_VB2_0
#define RUR14 _TIE_hmd1a_common_tie_RUR_VB2_0
#define WUR_VB2_0 _TIE_hmd1a_common_tie_WUR_VB2_0
#define WVB2_0 _TIE_hmd1a_common_tie_WUR_VB2_0
#define WUR14 _TIE_hmd1a_common_tie_WUR_VB2_0
#define RUR_VB2_1 _TIE_hmd1a_common_tie_RUR_VB2_1
#define RVB2_1 _TIE_hmd1a_common_tie_RUR_VB2_1
#define RUR15 _TIE_hmd1a_common_tie_RUR_VB2_1
#define WUR_VB2_1 _TIE_hmd1a_common_tie_WUR_VB2_1
#define WVB2_1 _TIE_hmd1a_common_tie_WUR_VB2_1
#define WUR15 _TIE_hmd1a_common_tie_WUR_VB2_1
#define RUR_VB3_0 _TIE_hmd1a_common_tie_RUR_VB3_0
#define RVB3_0 _TIE_hmd1a_common_tie_RUR_VB3_0
#define RUR16 _TIE_hmd1a_common_tie_RUR_VB3_0
#define WUR_VB3_0 _TIE_hmd1a_common_tie_WUR_VB3_0
#define WVB3_0 _TIE_hmd1a_common_tie_WUR_VB3_0
#define WUR16 _TIE_hmd1a_common_tie_WUR_VB3_0
#define RUR_VB3_1 _TIE_hmd1a_common_tie_RUR_VB3_1
#define RVB3_1 _TIE_hmd1a_common_tie_RUR_VB3_1
#define RUR17 _TIE_hmd1a_common_tie_RUR_VB3_1
#define WUR_VB3_1 _TIE_hmd1a_common_tie_WUR_VB3_1
#define WVB3_1 _TIE_hmd1a_common_tie_WUR_VB3_1
#define WUR17 _TIE_hmd1a_common_tie_WUR_VB3_1
#define RUR_VB4_0 _TIE_hmd1a_common_tie_RUR_VB4_0
#define RVB4_0 _TIE_hmd1a_common_tie_RUR_VB4_0
#define RUR18 _TIE_hmd1a_common_tie_RUR_VB4_0
#define WUR_VB4_0 _TIE_hmd1a_common_tie_WUR_VB4_0
#define WVB4_0 _TIE_hmd1a_common_tie_WUR_VB4_0
#define WUR18 _TIE_hmd1a_common_tie_WUR_VB4_0
#define RUR_VB4_1 _TIE_hmd1a_common_tie_RUR_VB4_1
#define RVB4_1 _TIE_hmd1a_common_tie_RUR_VB4_1
#define RUR19 _TIE_hmd1a_common_tie_RUR_VB4_1
#define WUR_VB4_1 _TIE_hmd1a_common_tie_WUR_VB4_1
#define WVB4_1 _TIE_hmd1a_common_tie_WUR_VB4_1
#define WUR19 _TIE_hmd1a_common_tie_WUR_VB4_1
#define RUR_VB5_0 _TIE_hmd1a_common_tie_RUR_VB5_0
#define RVB5_0 _TIE_hmd1a_common_tie_RUR_VB5_0
#define RUR20 _TIE_hmd1a_common_tie_RUR_VB5_0
#define WUR_VB5_0 _TIE_hmd1a_common_tie_WUR_VB5_0
#define WVB5_0 _TIE_hmd1a_common_tie_WUR_VB5_0
#define WUR20 _TIE_hmd1a_common_tie_WUR_VB5_0
#define RUR_VB5_1 _TIE_hmd1a_common_tie_RUR_VB5_1
#define RVB5_1 _TIE_hmd1a_common_tie_RUR_VB5_1
#define RUR21 _TIE_hmd1a_common_tie_RUR_VB5_1
#define WUR_VB5_1 _TIE_hmd1a_common_tie_WUR_VB5_1
#define WVB5_1 _TIE_hmd1a_common_tie_WUR_VB5_1
#define WUR21 _TIE_hmd1a_common_tie_WUR_VB5_1
#define RUR_VB6_0 _TIE_hmd1a_common_tie_RUR_VB6_0
#define RVB6_0 _TIE_hmd1a_common_tie_RUR_VB6_0
#define RUR22 _TIE_hmd1a_common_tie_RUR_VB6_0
#define WUR_VB6_0 _TIE_hmd1a_common_tie_WUR_VB6_0
#define WVB6_0 _TIE_hmd1a_common_tie_WUR_VB6_0
#define WUR22 _TIE_hmd1a_common_tie_WUR_VB6_0
#define RUR_VB6_1 _TIE_hmd1a_common_tie_RUR_VB6_1
#define RVB6_1 _TIE_hmd1a_common_tie_RUR_VB6_1
#define RUR23 _TIE_hmd1a_common_tie_RUR_VB6_1
#define WUR_VB6_1 _TIE_hmd1a_common_tie_WUR_VB6_1
#define WVB6_1 _TIE_hmd1a_common_tie_WUR_VB6_1
#define WUR23 _TIE_hmd1a_common_tie_WUR_VB6_1
#define RUR_VB7_0 _TIE_hmd1a_common_tie_RUR_VB7_0
#define RVB7_0 _TIE_hmd1a_common_tie_RUR_VB7_0
#define RUR24 _TIE_hmd1a_common_tie_RUR_VB7_0
#define WUR_VB7_0 _TIE_hmd1a_common_tie_WUR_VB7_0
#define WVB7_0 _TIE_hmd1a_common_tie_WUR_VB7_0
#define WUR24 _TIE_hmd1a_common_tie_WUR_VB7_0
#define RUR_VB7_1 _TIE_hmd1a_common_tie_RUR_VB7_1
#define RVB7_1 _TIE_hmd1a_common_tie_RUR_VB7_1
#define RUR25 _TIE_hmd1a_common_tie_RUR_VB7_1
#define WUR_VB7_1 _TIE_hmd1a_common_tie_WUR_VB7_1
#define WVB7_1 _TIE_hmd1a_common_tie_WUR_VB7_1
#define WUR25 _TIE_hmd1a_common_tie_WUR_VB7_1
#define mir18_move _TIE_hmd1a_common_tie_mir18_move
#define ulsr32_move _TIE_hmd1a_common_tie_ulsr32_move
#define cr64_move _TIE_hmd1a_common_tie_cr64_move
#define fr32_move _TIE_hmd1a_common_tie_fr32_move
#define fr32_loadi _TIE_hmd1a_common_tie_fr32_loadi
#define fr32_storei _TIE_hmd1a_common_tie_fr32_storei
#define fr32_loadx _TIE_hmd1a_common_tie_fr32_loadx
#define fr32_storex _TIE_hmd1a_common_tie_fr32_storex
#define fr32_loadip _TIE_hmd1a_common_tie_fr32_loadip
#define fr32_storeip _TIE_hmd1a_common_tie_fr32_storeip
#define fr32_loadxp _TIE_hmd1a_common_tie_fr32_loadxp
#define fr32_storexp _TIE_hmd1a_common_tie_fr32_storexp
#define fr32_rtor_int32 _TIE_hmd1a_common_tie_fr32_rtor_int32
#define fr32_rtor_uint32 _TIE_hmd1a_common_tie_fr32_rtor_uint32
#define int32_rtor_fr32 _TIE_hmd1a_common_tie_int32_rtor_fr32
#define uint32_rtor_fr32 _TIE_hmd1a_common_tie_uint32_rtor_fr32
#define vr64_move _TIE_hmd1a_common_tie_vr64_move
#define vr64_loadi _TIE_hmd1a_common_tie_vr64_loadi
#define vr64_storei _TIE_hmd1a_common_tie_vr64_storei
#define vr64_loadx _TIE_hmd1a_common_tie_vr64_loadx
#define vr64_storex _TIE_hmd1a_common_tie_vr64_storex
#define vr64_loadip _TIE_hmd1a_common_tie_vr64_loadip
#define vr64_storeip _TIE_hmd1a_common_tie_vr64_storeip
#define vr64_loadxp _TIE_hmd1a_common_tie_vr64_loadxp
#define vr64_storexp _TIE_hmd1a_common_tie_vr64_storexp
#define get_VRH _TIE_hmd1a_common_tie_get_VRH
#define get_VRL _TIE_hmd1a_common_tie_get_VRL
#define set_VRH _TIE_hmd1a_common_tie_set_VRH
#define set_VRL _TIE_hmd1a_common_tie_set_VRL
#define vr64_pair _TIE_hmd1a_common_tie_vr64_pair
#define atbool_rtor_int32 _TIE_hmd1a_common_tie_atbool_rtor_int32
#define atbool_rtor_uint32 _TIE_hmd1a_common_tie_atbool_rtor_uint32
#define int32_rtor_atbool _TIE_hmd1a_common_tie_int32_rtor_atbool
#define uint32_rtor_atbool _TIE_hmd1a_common_tie_uint32_rtor_atbool

#ifndef RUR
#define RUR(NUM) RUR##NUM()
#endif

#ifndef WUR
#define WUR(VAL, NUM) WUR##NUM(VAL)
#endif

#endif /* __XCC__ */

#endif /* __XTENSA__ */

#endif /* !_XTENSA_hmd1a_common_tie_HEADER */
