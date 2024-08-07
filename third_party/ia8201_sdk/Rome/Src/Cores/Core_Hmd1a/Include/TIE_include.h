/************************************************************************//**
 * @file    TIE_include.h
 *
 * @brief   Include all TIE instructions
 *          This is the file to include for Xtensa builds
 *
 * $DateTime: 2021/03/09 09:01:05 $
 * $Revision: #1 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef TIE_INCLUDE_H
#define TIE_INCLUDE_H


#include "hmd1a_common_tie.h"
#include "hmd1a_version_tie.h"
#include <xtensa/tie/xt_misc.h>
#include <xtensa/tie/xt_mul.h>


#undef st_BBR
#undef atbool_storei
#undef ld_BBR
#undef atbool_loadi
#undef mv_BBR
#undef atbool_move
#undef st_ULSR
#undef ulsr32_storei
#undef ld_ULSR
#undef ulsr32_loadi
#undef st_MIR
#undef mir18_storei
#undef ld_MIR
#undef mir18_loadi
#undef st_CR
#undef cr64_storei
#undef ld_CR
#undef cr64_loadi
#undef dma_ld
#undef dma_align_ld
#undef dma_ldu
#undef dma_flush_ld
#undef dma_st
#undef dma_align_st
#undef dma_stu
#undef dma_flush_st
#undef dma_buf_save
#undef RUR_JammingBit
#undef WUR_JammingBit
#undef RUR_AccExtend_0
#undef WUR_AccExtend_0
#undef RUR_AccExtend_1
#undef WUR_AccExtend_1
#undef RUR_BB0_0
#undef WUR_BB0_0
#undef RUR_BB0_1
#undef WUR_BB0_1
#undef RUR_BB1_0
#undef WUR_BB1_0
#undef RUR_BB1_1
#undef WUR_BB1_1
#undef RUR_BB2_0
#undef WUR_BB2_0
#undef RUR_BB2_1
#undef WUR_BB2_1
#undef RUR_BB3_0
#undef WUR_BB3_0
#undef RUR_BB3_1
#undef WUR_BB3_1
#undef RUR_MvmAux
#undef WUR_MvmAux
#undef RUR_VB1_0
#undef WUR_VB1_0
#undef RUR_VB1_1
#undef WUR_VB1_1
#undef RUR_VB2_0
#undef WUR_VB2_0
#undef RUR_VB2_1
#undef WUR_VB2_1
#undef RUR_VB3_0
#undef WUR_VB3_0
#undef RUR_VB3_1
#undef WUR_VB3_1
#undef RUR_VB4_0
#undef WUR_VB4_0
#undef RUR_VB4_1
#undef WUR_VB4_1
#undef RUR_VB5_0
#undef WUR_VB5_0
#undef RUR_VB5_1
#undef WUR_VB5_1
#undef RUR_VB6_0
#undef WUR_VB6_0
#undef RUR_VB6_1
#undef WUR_VB6_1
#undef RUR_VB7_0
#undef WUR_VB7_0
#undef RUR_VB7_1
#undef WUR_VB7_1
#undef load32x2_vr_idxR
#undef load32x2_vr_idxI
#undef load32x2_vr_postR
#undef load32x2_vr_postI
#undef load32x2_vr_circI
#undef load32x1_vr_idxR
#undef load32x1_vr_idxI
#undef load32x1_vr_postR
#undef load32x1_vr_postI
#undef load32x1_vr_circI
#undef load32x2_vr_bdir
#undef load32x2_vr_brev
#undef load32x2_vr_idxR_perm
#undef load32x2_vr_idxI_perm_vr
#undef load32x2_vr_postR_perm
#undef load32x2_vr_postI_perm_vr
#undef load32x2_vr_circI_perm
#undef load32x1_vr_idxR_perm
#undef load32x1_vr_idxI_perm_vr
#undef load32x1_vr_postR_perm
#undef load32x1_vr_postI_perm_vr
#undef load32x1_vr_circI_perm
#undef load16x2_vr_idxR
#undef load16x2_vr_idxI
#undef load16x2_vr_postR
#undef load16x2_vr_postI
#undef load16x2_vr_circI
#undef load16x1_vr_idxR
#undef load16x1_vr_idxI
#undef load16x1_vr_postR
#undef load16x1_vr_postI
#undef load16x1_vr_circI
#undef load8x2_vr_idxR
#undef load8x2_vr_idxI
#undef load8x2_vr_postR
#undef load8x2_vr_postI
#undef load8x2_vr_circI
#undef load8x1_vr_idxR
#undef load8x1_vr_idxI
#undef load8x1_vr_postR
#undef load8x1_vr_postI
#undef load8x1_vr_circI
#undef align_32x2_load
#undef load_32x2_vr_a
#undef load_24x2_vr_a
#undef load_32x2_vr_a_circ
#undef store32x2_vr_idxR
#undef store32x2_vr_idxI
#undef store32x2_vr_postR
#undef store32x2_vr_postI
#undef store32x2_vr_circI
#undef store32x1_vr_idxR
#undef store32x1_vr_idxI
#undef store32x1_vr_postR
#undef store32x1_vr_postI
#undef store32x1_vr_circI
#undef store32x2_vr_br_idxR
#undef store32x2_vr_br_idxI
#undef store32x2_vr_br_postR
#undef store32x2_vr_br_postI
#undef store32x2_vr_br_circI
#undef store32x1_vr_br_idxR
#undef store32x1_vr_br_idxI
#undef store32x1_vr_br_postR
#undef store32x1_vr_br_postI
#undef store32x1_vr_br_circI
#undef store32x2_vr_br_bdir
#undef store32x2_vr_br_brev
#undef store16x2_vr_idxR
#undef store16x2_vr_idxI
#undef store16x2_vr_postR
#undef store16x2_vr_postI
#undef store16x2_vr_circI
#undef store16x1_vr_idxR
#undef store16x1_vr_idxI
#undef store16x1_vr_postR
#undef store16x1_vr_postI
#undef store16x1_vr_circI
#undef store8x2_vr_idxR
#undef store8x2_vr_idxI
#undef store8x2_vr_postR
#undef store8x2_vr_postI
#undef store8x2_vr_circI
#undef store8x1_vr_idxR
#undef store8x1_vr_idxI
#undef store8x1_vr_postR
#undef store8x1_vr_postI
#undef store8x1_vr_circI
#undef align_32x2_store
#undef store_32x2_vr_a
#undef store_24x2_vr_a
#undef store_32x2_vr_a_circ
#undef flush_32x2
#undef load_fr_postI
#undef store_fr_postI
#undef brev_upd
#undef brev_upd_ext
#undef move32_ar_vr
#undef move32_vr_ar
#undef move32_ar_vr_idx
#undef move32_fr_vr_idx
#undef move_fr_eqz
#undef move_fr_gez
#undef move_fr_gtz
#undef move_fr_lez
#undef move_fr_ltz
#undef move_fr_nez
#undef move_fr_sat
#undef move_fr_arnz
#undef vmove_vr_eqz
#undef vmove_vr_gez
#undef vmove_vr_gtz
#undef vmove_vr_lez
#undef vmove_vr_ltz
#undef vmove_vr_nez
#undef vmove_vr_sat
#undef replicate
#undef replicate_ar
#undef vreplicate
#undef vreplicate_fr
#undef convert_16I_to_32F_x1
#undef convert_16I_to_32F_x2
#undef convert_32F_to_16I_x1
#undef convert_32F_to_16I_x2
#undef convert_32F_to_16F_x1
#undef convert_32F_to_16F_x2
#undef convert_16F_to_32F_x1
#undef convert_16F_to_32F_x2
#undef convert_32I_to_32F_x1
#undef convert_32F_to_32I_x1
#undef convert_IEEE_float_to_32F_x2
#undef convert_32F_to_IEEE_float_x2
#undef convert_32I_to_64F
#undef convert_64F_to_32I
#undef convert_32F_to_64F
#undef convert_64F_to_32F
#undef convert_IEEE_double_to_64F
#undef convert_64F_to_IEEE_double
#undef vadd_perm
#undef vsum_perm
#undef vmul_perm
#undef vmac_perm
#undef vmac_boost
#undef vblend
#undef vblend_add
#undef vblend_boost
#undef fadds
#undef fmuls
#undef fmacs
#undef dadds
#undef dmuls
#undef dmacs
#undef vadds
#undef vmuls
#undef vmacs
#undef cmul
#undef cmac
#undef cmas
#undef vmulf
#undef vmacf
#undef vabs
#undef vexp_adj
#undef vexp_adji
#undef vpermi
#undef seta_vr
#undef vseta_vr
#undef seta_ar
#undef seta_fr
#undef load_AccExtend_postI
#undef load32x1_vr_idx16vr
#undef load_BB0_postI
#undef load_BB1_postI
#undef load_BB2_postI
#undef load_BB3_postI
#undef load_VB1_postI
#undef load_VB2_postI
#undef load_VB3_postI
#undef load_VB4_postI
#undef load_VB5_postI
#undef load_VB6_postI
#undef load_VB7_postI
#undef load_32x2_vr_a_bounded
#undef load_BBx_VB67_a_bounded
#undef flush_32x2_bounded
#undef store_32x2_vr_a_bounded
#undef store_AccExtend_postI
#undef store_BB0_postI
#undef store_BB1_postI
#undef store_BB2_postI
#undef store_BB3_postI
#undef store_VB1_postI
#undef store_VB2_postI
#undef store_VB3_postI
#undef store_VB4_postI
#undef store_VB5_postI
#undef store_VB6_postI
#undef store_VB7_postI
#undef afloat_exp_extract
#undef mov_AccExtend_vr
#undef mov_vr_AccExtend
#undef mov_BB_VB67_to_vrVB_VB45
#undef mov_vrVB_VB45_to_BB_VB67
#undef precess_16bits
#undef set_BB_vrVB67_zero
#undef exp_shift_amount
#undef rnd_sat_pack
#undef rectify32_into8
#undef shift8_into32_arith
#undef shift32_arith
#undef mac8bx8b
#undef mac8bx8b_sparse
#undef mac8bx8b_conv
#undef mir_init
#undef f_abs
#undef fclamp
#undef fclamp_bp
#undef fclamp_one
#undef fmax
#undef fmin
#undef max_fr
#undef min_fr
#undef log2
#undef pow2
#undef sigmoid
#undef inv
#undef ratio
#undef atanratio
#undef invsqrt
#undef sine
#undef cosine
#undef log2mul
#undef cspow2
#undef comp
#undef eq
#undef ge
#undef gt
#undef le
#undef lt
#undef ne
#undef comp_const
#undef eq_const
#undef ge_const
#undef gt_const
#undef le_const
#undef lt_const
#undef ne_const
#undef comp_fr
#undef eq_fr
#undef ge_fr
#undef gt_fr
#undef le_fr
#undef lt_fr
#undef ne_fr
#undef neg_fr
#undef abs_fr
#undef deqz
#undef dgez
#undef dgtz
#undef dlez
#undef dltz
#undef dnez
#undef veq
#undef vge
#undef vgt
#undef vle
#undef vlt
#undef vne
#undef veq_const
#undef vge_const
#undef vgt_const
#undef vle_const
#undef vlt_const
#undef vne_const
#undef sel_1b2
#undef sel_eq
#undef sel_ge
#undef sel_gt
#undef sel_le
#undef sel_lt
#undef sel_ne
#undef sel_ar
#undef vsel
#undef vsel_ar
#undef andb2
#undef andbc2
#undef orb2
#undef orbc2
#undef xorb2
#undef bcount0_maskI
#undef bcount0_maskR
#undef bcount1_maskI
#undef bcount1_maskR
#undef bfirst0_maskI
#undef bfirst0_maskR
#undef bfirst1_maskI
#undef bfirst1_maskR
#undef blast0_maskI
#undef blast0_maskR
#undef blast1_maskI
#undef blast1_maskR
#undef bgetI
#undef bgetR
#undef bsetI
#undef bsetR
#undef exp_adj
#undef exp_adji
#undef exp_adj_fr
#undef exp_adji_fr
#undef s_neg
#undef s_copy
#undef s_and
#undef s_andc
#undef s_or
#undef s_orc
#undef s_xor
#undef s_vneg
#undef s_vcopy
#undef s_vand
#undef s_vandc
#undef s_vor
#undef s_vorc
#undef s_vxor
#undef floorp_frac
#undef idx_frac
#undef truncate_fr
#undef rmax_idx
#undef rmin_idx
#undef vmaxmin_init
#undef vmax_idx
#undef vmin_idx
#undef vmax
#undef vmin
#undef sortupd_asc_vr
#undef sortupd_des_vr
#undef sortupd_asc_ar
#undef sortupd_des_ar
#undef vbool
#undef align_up
#undef mv_MIR
#undef mir18_move
#undef mv_ULSR
#undef ulsr32_move
#undef mv_CR
#undef cr64_move
#undef ld_FR
#undef st_FR
#undef ld_FR_idxR
#undef st_FR_idxR
#undef ld_FR_postI
#undef st_FR_postI
#undef ld_FR_postR
#undef st_FR_postR
#undef ld_VR
#undef st_VR
#undef ld_VR_idxR
#undef st_VR_idxR
#undef ld_VR_postI
#undef st_VR_postI
#undef ld_VR_postR
#undef st_VR_postR
#undef mv_FR
#undef move_ar_fr
#undef move_fr_ar
#undef fr32_move
#undef fr32_loadi
#undef fr32_storei
#undef fr32_loadx
#undef fr32_storex
#undef fr32_loadip
#undef fr32_storeip
#undef fr32_loadxp
#undef fr32_storexp
#undef fr32_rtor_int32
#undef fr32_rtor_uint32
#undef int32_rtor_fr32
#undef uint32_rtor_fr32
#undef mv_VR
#undef vr64_move
#undef vr64_loadi
#undef vr64_storei
#undef vr64_loadx
#undef vr64_storex
#undef vr64_loadip
#undef vr64_storeip
#undef vr64_loadxp
#undef vr64_storexp
#undef get_VRH
#undef get_VRL
#undef set_VRH
#undef set_VRL
#undef vr64_pair
#undef move_ar_bbr
#undef move_bbr_ar
#undef shift_from_bbr
#undef shift_to_bbr
#undef atbool_rtor_int32
#undef atbool_rtor_uint32
#undef int32_rtor_atbool
#undef uint32_rtor_atbool
#undef ld_ar_x2
#undef st_ar_x2
#define st_BBR(a,b,c)                               \
    _TIE_hmd1a_common_tie_st_BBR(a,(atbool *)(b),c)
#define atbool_storei(a,b,c)                        \
    _TIE_hmd1a_common_tie_atbool_storei(a,(atbool *)(b),c)
#define ld_BBR(a,b)                                 \
    _TIE_hmd1a_common_tie_ld_BBR((const atbool *)(a),b)
#define atbool_loadi(a,b)                           \
    _TIE_hmd1a_common_tie_atbool_loadi((const atbool *)(a),b)
#define mv_BBR(a)                                   \
    _TIE_hmd1a_common_tie_mv_BBR(a)
#define atbool_move(a)                              \
    _TIE_hmd1a_common_tie_atbool_move(a)
#define st_ULSR(a,b,c)                              \
    _TIE_hmd1a_common_tie_st_ULSR(a,(ulsr32 *)(b),c)
#define ulsr32_storei(a,b,c)                        \
    _TIE_hmd1a_common_tie_ulsr32_storei(a,(ulsr32 *)(b),c)
#define ld_ULSR(a,b)                                \
    _TIE_hmd1a_common_tie_ld_ULSR((const ulsr32 *)(a),b)
#define ulsr32_loadi(a,b)                           \
    _TIE_hmd1a_common_tie_ulsr32_loadi((const ulsr32 *)(a),b)
#define st_MIR(a,b,c)                               \
    _TIE_hmd1a_common_tie_st_MIR(a,(mir18 *)(b),c)
#define mir18_storei(a,b,c)                         \
    _TIE_hmd1a_common_tie_mir18_storei(a,(mir18 *)(b),c)
#define ld_MIR(a,b)                                 \
    _TIE_hmd1a_common_tie_ld_MIR((const mir18 *)(a),b)
#define mir18_loadi(a,b)                            \
    _TIE_hmd1a_common_tie_mir18_loadi((const mir18 *)(a),b)
#define st_CR(a,b,c)                                \
    _TIE_hmd1a_common_tie_st_CR(a,(cr64 *)(b),c)
#define cr64_storei(a,b,c)                          \
    _TIE_hmd1a_common_tie_cr64_storei(a,(cr64 *)(b),c)
#define ld_CR(a,b)                                  \
    _TIE_hmd1a_common_tie_ld_CR((const cr64 *)(a),b)
#define cr64_loadi(a,b)                             \
    _TIE_hmd1a_common_tie_cr64_loadi((const cr64 *)(a),b)
#define dma_ld(a)                                   \
    _TIE_hmd1a_common_tie_dma_ld((const unsigned *)(a))
#define dma_align_ld(a,b)                           \
    _TIE_hmd1a_common_tie_dma_align_ld((const unsigned *)(a),(const unsigned *)(b))
#define dma_ldu(a)                                  \
    _TIE_hmd1a_common_tie_dma_ldu((const unsigned *)(a))
#define dma_flush_ld(a,b)                           \
    _TIE_hmd1a_common_tie_dma_flush_ld((const unsigned *)(a),(const unsigned *)(b))
#define dma_st(a,b)                                 \
    _TIE_hmd1a_common_tie_dma_st((unsigned *)(a),(unsigned *)(b))
#define dma_align_st(a,b)                           \
    _TIE_hmd1a_common_tie_dma_align_st((unsigned *)(a),(unsigned *)(b))
#define dma_stu(a,b)                                \
    _TIE_hmd1a_common_tie_dma_stu((unsigned *)(a),(unsigned *)(b))
#define dma_flush_st(a,b)                           \
    _TIE_hmd1a_common_tie_dma_flush_st((unsigned *)(a),(unsigned *)(b))
#define dma_buf_save(a)                             \
    _TIE_hmd1a_common_tie_dma_buf_save((unsigned *)(a))
#define RUR_JammingBit()                            \
    _TIE_hmd1a_common_tie_RUR_JammingBit()
#define WUR_JammingBit(a)                           \
    _TIE_hmd1a_common_tie_WUR_JammingBit(a)
#define RUR_AccExtend_0()                           \
    _TIE_hmd1a_common_tie_RUR_AccExtend_0()
#define WUR_AccExtend_0(a)                          \
    _TIE_hmd1a_common_tie_WUR_AccExtend_0(a)
#define RUR_AccExtend_1()                           \
    _TIE_hmd1a_common_tie_RUR_AccExtend_1()
#define WUR_AccExtend_1(a)                          \
    _TIE_hmd1a_common_tie_WUR_AccExtend_1(a)
#define RUR_BB0_0()                                 \
    _TIE_hmd1a_common_tie_RUR_BB0_0()
#define WUR_BB0_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB0_0(a)
#define RUR_BB0_1()                                 \
    _TIE_hmd1a_common_tie_RUR_BB0_1()
#define WUR_BB0_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB0_1(a)
#define RUR_BB1_0()                                 \
    _TIE_hmd1a_common_tie_RUR_BB1_0()
#define WUR_BB1_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB1_0(a)
#define RUR_BB1_1()                                 \
    _TIE_hmd1a_common_tie_RUR_BB1_1()
#define WUR_BB1_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB1_1(a)
#define RUR_BB2_0()                                 \
    _TIE_hmd1a_common_tie_RUR_BB2_0()
#define WUR_BB2_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB2_0(a)
#define RUR_BB2_1()                                 \
    _TIE_hmd1a_common_tie_RUR_BB2_1()
#define WUR_BB2_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB2_1(a)
#define RUR_BB3_0()                                 \
    _TIE_hmd1a_common_tie_RUR_BB3_0()
#define WUR_BB3_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB3_0(a)
#define RUR_BB3_1()                                 \
    _TIE_hmd1a_common_tie_RUR_BB3_1()
#define WUR_BB3_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_BB3_1(a)
#define RUR_MvmAux()                                \
    _TIE_hmd1a_common_tie_RUR_MvmAux()
#define WUR_MvmAux(a)                               \
    _TIE_hmd1a_common_tie_WUR_MvmAux(a)
#define RUR_VB1_0()                                 \
    _TIE_hmd1a_common_tie_RUR_VB1_0()
#define WUR_VB1_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB1_0(a)
#define RUR_VB1_1()                                 \
    _TIE_hmd1a_common_tie_RUR_VB1_1()
#define WUR_VB1_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB1_1(a)
#define RUR_VB2_0()                                 \
    _TIE_hmd1a_common_tie_RUR_VB2_0()
#define WUR_VB2_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB2_0(a)
#define RUR_VB2_1()                                 \
    _TIE_hmd1a_common_tie_RUR_VB2_1()
#define WUR_VB2_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB2_1(a)
#define RUR_VB3_0()                                 \
    _TIE_hmd1a_common_tie_RUR_VB3_0()
#define WUR_VB3_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB3_0(a)
#define RUR_VB3_1()                                 \
    _TIE_hmd1a_common_tie_RUR_VB3_1()
#define WUR_VB3_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB3_1(a)
#define RUR_VB4_0()                                 \
    _TIE_hmd1a_common_tie_RUR_VB4_0()
#define WUR_VB4_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB4_0(a)
#define RUR_VB4_1()                                 \
    _TIE_hmd1a_common_tie_RUR_VB4_1()
#define WUR_VB4_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB4_1(a)
#define RUR_VB5_0()                                 \
    _TIE_hmd1a_common_tie_RUR_VB5_0()
#define WUR_VB5_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB5_0(a)
#define RUR_VB5_1()                                 \
    _TIE_hmd1a_common_tie_RUR_VB5_1()
#define WUR_VB5_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB5_1(a)
#define RUR_VB6_0()                                 \
    _TIE_hmd1a_common_tie_RUR_VB6_0()
#define WUR_VB6_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB6_0(a)
#define RUR_VB6_1()                                 \
    _TIE_hmd1a_common_tie_RUR_VB6_1()
#define WUR_VB6_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB6_1(a)
#define RUR_VB7_0()                                 \
    _TIE_hmd1a_common_tie_RUR_VB7_0()
#define WUR_VB7_0(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB7_0(a)
#define RUR_VB7_1()                                 \
    _TIE_hmd1a_common_tie_RUR_VB7_1()
#define WUR_VB7_1(a)                                \
    _TIE_hmd1a_common_tie_WUR_VB7_1(a)
#define load32x2_vr_idxR(a,b)                       \
    _TIE_hmd1a_common_tie_load32x2_vr_idxR((const unsigned *)(a),b)
#define load32x2_vr_idxI(a,b)                       \
    _TIE_hmd1a_common_tie_load32x2_vr_idxI((const unsigned *)(a),b)
#define load32x2_vr_postR(a,b,c)                    \
    _TIE_hmd1a_common_tie_load32x2_vr_postR(a,(const unsigned *)(b),c)
#define load32x2_vr_postI(a,b,c)                    \
    _TIE_hmd1a_common_tie_load32x2_vr_postI(a,(const unsigned *)(b),c)
#define load32x2_vr_circI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_load32x2_vr_circI(a,(const unsigned *)(b),c,d)
#define load32x1_vr_idxR(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_load32x1_vr_idxR(a,(const unsigned *)(b),c,d)
#define load32x1_vr_idxI(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_load32x1_vr_idxI(a,(const unsigned *)(b),c,d)
#define load32x1_vr_postR(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_load32x1_vr_postR(a,(const unsigned *)(b),c,d)
#define load32x1_vr_postI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_load32x1_vr_postI(a,(const unsigned *)(b),c,d)
#define load32x1_vr_circI(a,b,c,d,e)                \
    _TIE_hmd1a_common_tie_load32x1_vr_circI(a,(const unsigned *)(b),c,d,e)
#define load32x2_vr_bdir(a,b)                       \
    _TIE_hmd1a_common_tie_load32x2_vr_bdir((const unsigned *)(a),b)
#define load32x2_vr_brev(a,b)                       \
    _TIE_hmd1a_common_tie_load32x2_vr_brev((const unsigned *)(a),b)
#define load32x2_vr_idxR_perm(a,b,c,d)              \
    _TIE_hmd1a_common_tie_load32x2_vr_idxR_perm(a,(const unsigned *)(b),c,d)
#define load32x2_vr_idxI_perm_vr(a,b,c,d)           \
    _TIE_hmd1a_common_tie_load32x2_vr_idxI_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x2_vr_postR_perm(a,b,c,d)             \
    _TIE_hmd1a_common_tie_load32x2_vr_postR_perm(a,(const unsigned *)(b),c,d)
#define load32x2_vr_postI_perm_vr(a,b,c,d,e)        \
    _TIE_hmd1a_common_tie_load32x2_vr_postI_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x2_vr_circI_perm(a,b,c,d,e)           \
    _TIE_hmd1a_common_tie_load32x2_vr_circI_perm(a,(const unsigned *)(b),c,d,e)
#define load32x1_vr_idxR_perm(a,b,c,d)              \
    _TIE_hmd1a_common_tie_load32x1_vr_idxR_perm(a,(const unsigned *)(b),c,d)
#define load32x1_vr_idxI_perm_vr(a,b,c,d)           \
    _TIE_hmd1a_common_tie_load32x1_vr_idxI_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x1_vr_postR_perm(a,b,c,d)             \
    _TIE_hmd1a_common_tie_load32x1_vr_postR_perm(a,(const unsigned *)(b),c,d)
#define load32x1_vr_postI_perm_vr(a,b,c,d,e)        \
    _TIE_hmd1a_common_tie_load32x1_vr_postI_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x1_vr_circI_perm(a,b,c,d,e)           \
    _TIE_hmd1a_common_tie_load32x1_vr_circI_perm(a,(const unsigned *)(b),c,d,e)
#define load16x2_vr_idxR(a,b)                       \
    _TIE_hmd1a_common_tie_load16x2_vr_idxR((const unsigned *)(a),b)
#define load16x2_vr_idxI(a,b)                       \
    _TIE_hmd1a_common_tie_load16x2_vr_idxI((const unsigned *)(a),b)
#define load16x2_vr_postR(a,b,c)                    \
    _TIE_hmd1a_common_tie_load16x2_vr_postR(a,(const unsigned *)(b),c)
#define load16x2_vr_postI(a,b,c)                    \
    _TIE_hmd1a_common_tie_load16x2_vr_postI(a,(const unsigned *)(b),c)
#define load16x2_vr_circI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_load16x2_vr_circI(a,(const unsigned *)(b),c,d)
#define load16x1_vr_idxR(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_load16x1_vr_idxR(a,(const unsigned *)(b),c,d)
#define load16x1_vr_idxI(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_load16x1_vr_idxI(a,(const unsigned *)(b),c,d)
#define load16x1_vr_postR(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_load16x1_vr_postR(a,(const unsigned *)(b),c,d)
#define load16x1_vr_postI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_load16x1_vr_postI(a,(const unsigned *)(b),c,d)
#define load16x1_vr_circI(a,b,c,d,e)                \
    _TIE_hmd1a_common_tie_load16x1_vr_circI(a,(const unsigned *)(b),c,d,e)
#define load8x2_vr_idxR(a,b)                        \
    _TIE_hmd1a_common_tie_load8x2_vr_idxR((const unsigned *)(a),b)
#define load8x2_vr_idxI(a,b)                        \
    _TIE_hmd1a_common_tie_load8x2_vr_idxI((const unsigned *)(a),b)
#define load8x2_vr_postR(a,b,c)                     \
    _TIE_hmd1a_common_tie_load8x2_vr_postR(a,(const unsigned *)(b),c)
#define load8x2_vr_postI(a,b,c)                     \
    _TIE_hmd1a_common_tie_load8x2_vr_postI(a,(const unsigned *)(b),c)
#define load8x2_vr_circI(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_load8x2_vr_circI(a,(const unsigned *)(b),c,d)
#define load8x1_vr_idxR(a,b,c,d)                    \
    _TIE_hmd1a_common_tie_load8x1_vr_idxR(a,(const unsigned *)(b),c,d)
#define load8x1_vr_idxI(a,b,c,d)                    \
    _TIE_hmd1a_common_tie_load8x1_vr_idxI(a,(const unsigned *)(b),c,d)
#define load8x1_vr_postR(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_load8x1_vr_postR(a,(const unsigned *)(b),c,d)
#define load8x1_vr_postI(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_load8x1_vr_postI(a,(const unsigned *)(b),c,d)
#define load8x1_vr_circI(a,b,c,d,e)                 \
    _TIE_hmd1a_common_tie_load8x1_vr_circI(a,(const unsigned *)(b),c,d,e)
#define align_32x2_load(a)                          \
    _TIE_hmd1a_common_tie_align_32x2_load((const unsigned *)(a))
#define load_32x2_vr_a(a,b,c)                       \
    _TIE_hmd1a_common_tie_load_32x2_vr_a(a,b,(const unsigned *)(c))
#define load_24x2_vr_a(a,b,c)                       \
    _TIE_hmd1a_common_tie_load_24x2_vr_a(a,b,(const unsigned *)(c))
#define load_32x2_vr_a_circ(a,b,c,d)                \
    _TIE_hmd1a_common_tie_load_32x2_vr_a_circ(a,b,(const unsigned *)(c),d)
#define store32x2_vr_idxR(a,b,c)                    \
    _TIE_hmd1a_common_tie_store32x2_vr_idxR(a,(unsigned *)(b),c)
#define store32x2_vr_idxI(a,b,c)                    \
    _TIE_hmd1a_common_tie_store32x2_vr_idxI(a,(unsigned *)(b),c)
#define store32x2_vr_postR(a,b,c)                   \
    _TIE_hmd1a_common_tie_store32x2_vr_postR(a,(unsigned *)(b),c)
#define store32x2_vr_postI(a,b,c)                   \
    _TIE_hmd1a_common_tie_store32x2_vr_postI(a,(unsigned *)(b),c)
#define store32x2_vr_circI(a,b,c,d)                 \
    _TIE_hmd1a_common_tie_store32x2_vr_circI(a,(unsigned *)(b),c,d)
#define store32x1_vr_idxR(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_store32x1_vr_idxR(a,(unsigned *)(b),c,d)
#define store32x1_vr_idxI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_store32x1_vr_idxI(a,(unsigned *)(b),c,d)
#define store32x1_vr_postR(a,b,c,d)                 \
    _TIE_hmd1a_common_tie_store32x1_vr_postR(a,(unsigned *)(b),c,d)
#define store32x1_vr_postI(a,b,c,d)                 \
    _TIE_hmd1a_common_tie_store32x1_vr_postI(a,(unsigned *)(b),c,d)
#define store32x1_vr_circI(a,b,c,d,e)               \
    _TIE_hmd1a_common_tie_store32x1_vr_circI(a,(unsigned *)(b),c,d,e)
#define store32x2_vr_br_idxR(a,b,c,d)               \
    _TIE_hmd1a_common_tie_store32x2_vr_br_idxR(a,b,(unsigned *)(c),d)
#define store32x2_vr_br_idxI(a,b,c,d)               \
    _TIE_hmd1a_common_tie_store32x2_vr_br_idxI(a,b,(unsigned *)(c),d)
#define store32x2_vr_br_postR(a,b,c,d)              \
    _TIE_hmd1a_common_tie_store32x2_vr_br_postR(a,b,(unsigned *)(c),d)
#define store32x2_vr_br_postI(a,b,c,d)              \
    _TIE_hmd1a_common_tie_store32x2_vr_br_postI(a,b,(unsigned *)(c),d)
#define store32x2_vr_br_circI(a,b,c,d,e)            \
    _TIE_hmd1a_common_tie_store32x2_vr_br_circI(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_idxR(a,b,c,d,e)             \
    _TIE_hmd1a_common_tie_store32x1_vr_br_idxR(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_idxI(a,b,c,d,e)             \
    _TIE_hmd1a_common_tie_store32x1_vr_br_idxI(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_postR(a,b,c,d,e)            \
    _TIE_hmd1a_common_tie_store32x1_vr_br_postR(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_postI(a,b,c,d,e)            \
    _TIE_hmd1a_common_tie_store32x1_vr_br_postI(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_circI(a,b,c,d,e,f)          \
    _TIE_hmd1a_common_tie_store32x1_vr_br_circI(a,b,(unsigned *)(c),d,e,f)
#define store32x2_vr_br_bdir(a,b,c,d)               \
    _TIE_hmd1a_common_tie_store32x2_vr_br_bdir(a,b,(unsigned *)(c),d)
#define store32x2_vr_br_brev(a,b,c,d)               \
    _TIE_hmd1a_common_tie_store32x2_vr_br_brev(a,b,(unsigned *)(c),d)
#define store16x2_vr_idxR(a,b,c)                    \
    _TIE_hmd1a_common_tie_store16x2_vr_idxR(a,(unsigned *)(b),c)
#define store16x2_vr_idxI(a,b,c)                    \
    _TIE_hmd1a_common_tie_store16x2_vr_idxI(a,(unsigned *)(b),c)
#define store16x2_vr_postR(a,b,c)                   \
    _TIE_hmd1a_common_tie_store16x2_vr_postR(a,(unsigned *)(b),c)
#define store16x2_vr_postI(a,b,c)                   \
    _TIE_hmd1a_common_tie_store16x2_vr_postI(a,(unsigned *)(b),c)
#define store16x2_vr_circI(a,b,c,d)                 \
    _TIE_hmd1a_common_tie_store16x2_vr_circI(a,(unsigned *)(b),c,d)
#define store16x1_vr_idxR(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_store16x1_vr_idxR(a,(unsigned *)(b),c,d)
#define store16x1_vr_idxI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_store16x1_vr_idxI(a,(unsigned *)(b),c,d)
#define store16x1_vr_postR(a,b,c,d)                 \
    _TIE_hmd1a_common_tie_store16x1_vr_postR(a,(unsigned *)(b),c,d)
#define store16x1_vr_postI(a,b,c,d)                 \
    _TIE_hmd1a_common_tie_store16x1_vr_postI(a,(unsigned *)(b),c,d)
#define store16x1_vr_circI(a,b,c,d,e)               \
    _TIE_hmd1a_common_tie_store16x1_vr_circI(a,(unsigned *)(b),c,d,e)
#define store8x2_vr_idxR(a,b,c)                     \
    _TIE_hmd1a_common_tie_store8x2_vr_idxR(a,(unsigned *)(b),c)
#define store8x2_vr_idxI(a,b,c)                     \
    _TIE_hmd1a_common_tie_store8x2_vr_idxI(a,(unsigned *)(b),c)
#define store8x2_vr_postR(a,b,c)                    \
    _TIE_hmd1a_common_tie_store8x2_vr_postR(a,(unsigned *)(b),c)
#define store8x2_vr_postI(a,b,c)                    \
    _TIE_hmd1a_common_tie_store8x2_vr_postI(a,(unsigned *)(b),c)
#define store8x2_vr_circI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_store8x2_vr_circI(a,(unsigned *)(b),c,d)
#define store8x1_vr_idxR(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_store8x1_vr_idxR(a,(unsigned *)(b),c,d)
#define store8x1_vr_idxI(a,b,c,d)                   \
    _TIE_hmd1a_common_tie_store8x1_vr_idxI(a,(unsigned *)(b),c,d)
#define store8x1_vr_postR(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_store8x1_vr_postR(a,(unsigned *)(b),c,d)
#define store8x1_vr_postI(a,b,c,d)                  \
    _TIE_hmd1a_common_tie_store8x1_vr_postI(a,(unsigned *)(b),c,d)
#define store8x1_vr_circI(a,b,c,d,e)                \
    _TIE_hmd1a_common_tie_store8x1_vr_circI(a,(unsigned *)(b),c,d,e)
#define align_32x2_store(a)                         \
    _TIE_hmd1a_common_tie_align_32x2_store((const unsigned *)(a))
#define store_32x2_vr_a(a,b,c)                      \
    _TIE_hmd1a_common_tie_store_32x2_vr_a(a,b,(unsigned *)(c))
#define store_24x2_vr_a(a,b,c)                      \
    _TIE_hmd1a_common_tie_store_24x2_vr_a(a,b,(unsigned *)(c))
#define store_32x2_vr_a_circ(a,b,c,d)               \
    _TIE_hmd1a_common_tie_store_32x2_vr_a_circ(a,b,(unsigned *)(c),d)
#define flush_32x2(a,b)                             \
    _TIE_hmd1a_common_tie_flush_32x2(a,(unsigned *)(b))
#define load_fr_postI(a,b,c)                        \
    _TIE_hmd1a_common_tie_load_fr_postI(a,(const unsigned *)(b),c)
#define store_fr_postI(a,b,c)                       \
    _TIE_hmd1a_common_tie_store_fr_postI(a,(unsigned *)(b),c)
#define brev_upd(a,b,c)                             \
    _TIE_hmd1a_common_tie_brev_upd(a,b,c)
#define brev_upd_ext(a,b)                           \
    _TIE_hmd1a_common_tie_brev_upd_ext(a,b)
#define move32_ar_vr(a,b)                           \
    _TIE_hmd1a_common_tie_move32_ar_vr(a,b)
#define move32_vr_ar(a,b,c)                         \
    _TIE_hmd1a_common_tie_move32_vr_ar(a,b,c)
#define move32_ar_vr_idx(a,b)                       \
    _TIE_hmd1a_common_tie_move32_ar_vr_idx(a,b)
#define move32_fr_vr_idx(a,b)                       \
    _TIE_hmd1a_common_tie_move32_fr_vr_idx(a,b)
#define move_fr_eqz(a,b,c)                          \
    _TIE_hmd1a_common_tie_move_fr_eqz(a,b,c)
#define move_fr_gez(a,b,c)                          \
    _TIE_hmd1a_common_tie_move_fr_gez(a,b,c)
#define move_fr_gtz(a,b,c)                          \
    _TIE_hmd1a_common_tie_move_fr_gtz(a,b,c)
#define move_fr_lez(a,b,c)                          \
    _TIE_hmd1a_common_tie_move_fr_lez(a,b,c)
#define move_fr_ltz(a,b,c)                          \
    _TIE_hmd1a_common_tie_move_fr_ltz(a,b,c)
#define move_fr_nez(a,b,c)                          \
    _TIE_hmd1a_common_tie_move_fr_nez(a,b,c)
#define move_fr_sat(a,b,c)                          \
    _TIE_hmd1a_common_tie_move_fr_sat(a,b,c)
#define move_fr_arnz(a,b,c)                         \
    _TIE_hmd1a_common_tie_move_fr_arnz(a,b,c)
#define vmove_vr_eqz(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmove_vr_eqz(a,b,c)
#define vmove_vr_gez(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmove_vr_gez(a,b,c)
#define vmove_vr_gtz(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmove_vr_gtz(a,b,c)
#define vmove_vr_lez(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmove_vr_lez(a,b,c)
#define vmove_vr_ltz(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmove_vr_ltz(a,b,c)
#define vmove_vr_nez(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmove_vr_nez(a,b,c)
#define vmove_vr_sat(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmove_vr_sat(a,b,c)
#define replicate(a,b,c,d)                          \
    _TIE_hmd1a_common_tie_replicate(a,b,c,d)
#define replicate_ar(a,b,c)                         \
    _TIE_hmd1a_common_tie_replicate_ar(a,b,c)
#define vreplicate(a,b)                             \
    _TIE_hmd1a_common_tie_vreplicate(a,b)
#define vreplicate_fr(a)                            \
    _TIE_hmd1a_common_tie_vreplicate_fr(a)
#define convert_16I_to_32F_x1(a,b,c)                \
    _TIE_hmd1a_common_tie_convert_16I_to_32F_x1(a,b,c)
#define convert_16I_to_32F_x2(a,b)                  \
    _TIE_hmd1a_common_tie_convert_16I_to_32F_x2(a,b)
#define convert_32F_to_16I_x1(a,b,c,d)              \
    _TIE_hmd1a_common_tie_convert_32F_to_16I_x1(a,b,c,d)
#define convert_32F_to_16I_x2(a,b,c)                \
    _TIE_hmd1a_common_tie_convert_32F_to_16I_x2(a,b,c)
#define convert_32F_to_16F_x1(a,b,c,d,e,f)          \
    _TIE_hmd1a_common_tie_convert_32F_to_16F_x1(a,b,c,d,e,f)
#define convert_32F_to_16F_x2(a,b,c,d,e)            \
    _TIE_hmd1a_common_tie_convert_32F_to_16F_x2(a,b,c,d,e)
#define convert_16F_to_32F_x1(a,b,c,d,e)            \
    _TIE_hmd1a_common_tie_convert_16F_to_32F_x1(a,b,c,d,e)
#define convert_16F_to_32F_x2(a,b,c,d)              \
    _TIE_hmd1a_common_tie_convert_16F_to_32F_x2(a,b,c,d)
#define convert_32I_to_32F_x1(a,b,c)                \
    _TIE_hmd1a_common_tie_convert_32I_to_32F_x1(a,b,c)
#define convert_32F_to_32I_x1(a,b,c,d)              \
    _TIE_hmd1a_common_tie_convert_32F_to_32I_x1(a,b,c,d)
#define convert_IEEE_float_to_32F_x2(a)             \
    _TIE_hmd1a_common_tie_convert_IEEE_float_to_32F_x2(a)
#define convert_32F_to_IEEE_float_x2(a)             \
    _TIE_hmd1a_common_tie_convert_32F_to_IEEE_float_x2(a)
#define convert_32I_to_64F(a)                       \
    _TIE_hmd1a_common_tie_convert_32I_to_64F(a)
#define convert_64F_to_32I(a,b)                     \
    _TIE_hmd1a_common_tie_convert_64F_to_32I(a,b)
#define convert_32F_to_64F(a)                       \
    _TIE_hmd1a_common_tie_convert_32F_to_64F(a)
#define convert_64F_to_32F(a)                       \
    _TIE_hmd1a_common_tie_convert_64F_to_32F(a)
#define convert_IEEE_double_to_64F(a)               \
    _TIE_hmd1a_common_tie_convert_IEEE_double_to_64F(a)
#define convert_64F_to_IEEE_double(a)               \
    _TIE_hmd1a_common_tie_convert_64F_to_IEEE_double(a)
#define vadd_perm(a,b,c,d,e,f)                      \
    _TIE_hmd1a_common_tie_vadd_perm(a,b,c,d,e,f)
#define vsum_perm(a,b,c,d,e,f,g)                    \
    _TIE_hmd1a_common_tie_vsum_perm(a,b,c,d,e,f,g)
#define vmul_perm(a,b,c,d,e,f)                      \
    _TIE_hmd1a_common_tie_vmul_perm(a,b,c,d,e,f)
#define vmac_perm(a,b,c,d,e,f,g,h,i)                \
    _TIE_hmd1a_common_tie_vmac_perm(a,b,c,d,e,f,g,h,i)
#define vmac_boost(a,b,c,d,e,f,g)                   \
    _TIE_hmd1a_common_tie_vmac_boost(a,b,c,d,e,f,g)
#define vblend(a,b,c,d,e,f)                         \
    _TIE_hmd1a_common_tie_vblend(a,b,c,d,e,f)
#define vblend_add(a,b,c,d,e,f,g,h,i)               \
    _TIE_hmd1a_common_tie_vblend_add(a,b,c,d,e,f,g,h,i)
#define vblend_boost(a,b,c,d,e,f,g)                 \
    _TIE_hmd1a_common_tie_vblend_boost(a,b,c,d,e,f,g)
#define fadds(a,b,c)                                \
    _TIE_hmd1a_common_tie_fadds(a,b,c)
#define fmuls(a,b,c)                                \
    _TIE_hmd1a_common_tie_fmuls(a,b,c)
#define fmacs(a,b,c,d)                              \
    _TIE_hmd1a_common_tie_fmacs(a,b,c,d)
#define dadds(a,b,c)                                \
    _TIE_hmd1a_common_tie_dadds(a,b,c)
#define dmuls(a,b,c)                                \
    _TIE_hmd1a_common_tie_dmuls(a,b,c)
#define dmacs(a,b,c,d)                              \
    _TIE_hmd1a_common_tie_dmacs(a,b,c,d)
#define vadds(a,b,c)                                \
    _TIE_hmd1a_common_tie_vadds(a,b,c)
#define vmuls(a,b,c)                                \
    _TIE_hmd1a_common_tie_vmuls(a,b,c)
#define vmacs(a,b,c,d,e)                            \
    _TIE_hmd1a_common_tie_vmacs(a,b,c,d,e)
#define cmul(a,b,c)                                 \
    _TIE_hmd1a_common_tie_cmul(a,b,c)
#define cmac(a,b,c,d)                               \
    _TIE_hmd1a_common_tie_cmac(a,b,c,d)
#define cmas(a,b,c,d)                               \
    _TIE_hmd1a_common_tie_cmas(a,b,c,d)
#define vmulf(a,b,c)                                \
    _TIE_hmd1a_common_tie_vmulf(a,b,c)
#define vmacf(a,b,c,d,e)                            \
    _TIE_hmd1a_common_tie_vmacf(a,b,c,d,e)
#define vabs(a)                                     \
    _TIE_hmd1a_common_tie_vabs(a)
#define vexp_adj(a,b)                               \
    _TIE_hmd1a_common_tie_vexp_adj(a,b)
#define vexp_adji(a,b)                              \
    _TIE_hmd1a_common_tie_vexp_adji(a,b)
#define vpermi(a,b,c)                               \
    _TIE_hmd1a_common_tie_vpermi(a,b,c)
#define seta_vr(a,b,c,d)                            \
    _TIE_hmd1a_common_tie_seta_vr(a,b,c,d)
#define vseta_vr(a,b)                               \
    _TIE_hmd1a_common_tie_vseta_vr(a,b)
#define seta_ar(a,b)                                \
    _TIE_hmd1a_common_tie_seta_ar(a,b)
#define seta_fr(a,b)                                \
    _TIE_hmd1a_common_tie_seta_fr(a,b)
#define load_AccExtend_postI(a,b)                   \
    _TIE_hmd1a_common_tie_load_AccExtend_postI((const unsigned *)(a),b)
#define load32x1_vr_idx16vr(a,b,c,d)                \
    _TIE_hmd1a_common_tie_load32x1_vr_idx16vr(a,(const unsigned *)(b),c,d)
#define load_BB0_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_BB0_postI((const unsigned *)(a),b)
#define load_BB1_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_BB1_postI((const unsigned *)(a),b)
#define load_BB2_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_BB2_postI((const unsigned *)(a),b)
#define load_BB3_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_BB3_postI((const unsigned *)(a),b)
#define load_VB1_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_VB1_postI((const unsigned *)(a),b)
#define load_VB2_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_VB2_postI((const unsigned *)(a),b)
#define load_VB3_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_VB3_postI((const unsigned *)(a),b)
#define load_VB4_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_VB4_postI((const unsigned *)(a),b)
#define load_VB5_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_VB5_postI((const unsigned *)(a),b)
#define load_VB6_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_VB6_postI((const unsigned *)(a),b)
#define load_VB7_postI(a,b)                         \
    _TIE_hmd1a_common_tie_load_VB7_postI((const unsigned *)(a),b)
#define load_32x2_vr_a_bounded(a,b,c,d)             \
    _TIE_hmd1a_common_tie_load_32x2_vr_a_bounded(a,b,(const unsigned *)(c),d)
#define load_BBx_VB67_a_bounded(a,b,c,d)            \
    _TIE_hmd1a_common_tie_load_BBx_VB67_a_bounded(a,(const unsigned *)(b),c,d)
#define flush_32x2_bounded(a,b,c)                   \
    _TIE_hmd1a_common_tie_flush_32x2_bounded(a,(unsigned *)(b),c)
#define store_32x2_vr_a_bounded(a,b,c,d)            \
    _TIE_hmd1a_common_tie_store_32x2_vr_a_bounded(a,b,(unsigned *)(c),d)
#define store_AccExtend_postI(a,b)                  \
    _TIE_hmd1a_common_tie_store_AccExtend_postI((unsigned *)(a),b)
#define store_BB0_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_BB0_postI((unsigned *)(a),b)
#define store_BB1_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_BB1_postI((unsigned *)(a),b)
#define store_BB2_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_BB2_postI((unsigned *)(a),b)
#define store_BB3_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_BB3_postI((unsigned *)(a),b)
#define store_VB1_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_VB1_postI((unsigned *)(a),b)
#define store_VB2_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_VB2_postI((unsigned *)(a),b)
#define store_VB3_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_VB3_postI((unsigned *)(a),b)
#define store_VB4_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_VB4_postI((unsigned *)(a),b)
#define store_VB5_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_VB5_postI((unsigned *)(a),b)
#define store_VB6_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_VB6_postI((unsigned *)(a),b)
#define store_VB7_postI(a,b)                        \
    _TIE_hmd1a_common_tie_store_VB7_postI((unsigned *)(a),b)
#define afloat_exp_extract(a)                       \
    _TIE_hmd1a_common_tie_afloat_exp_extract(a)
#define mov_AccExtend_vr(a)                         \
    _TIE_hmd1a_common_tie_mov_AccExtend_vr(a)
#define mov_vr_AccExtend()                          \
    _TIE_hmd1a_common_tie_mov_vr_AccExtend()
#define mov_BB_VB67_to_vrVB_VB45()                  \
    _TIE_hmd1a_common_tie_mov_BB_VB67_to_vrVB_VB45()
#define mov_vrVB_VB45_to_BB_VB67(a)                 \
    _TIE_hmd1a_common_tie_mov_vrVB_VB45_to_BB_VB67(a)
#define precess_16bits(a,b)                         \
    _TIE_hmd1a_common_tie_precess_16bits(a,b)
#define set_BB_vrVB67_zero()                        \
    _TIE_hmd1a_common_tie_set_BB_vrVB67_zero()
#define exp_shift_amount(a,b)                       \
    _TIE_hmd1a_common_tie_exp_shift_amount(a,b)
#define rnd_sat_pack(a,b,c,d,e)                     \
    _TIE_hmd1a_common_tie_rnd_sat_pack(a,b,c,d,e)
#define rectify32_into8(a,b,c,d,e,f)                \
    _TIE_hmd1a_common_tie_rectify32_into8(a,b,c,d,e,f)
#define shift8_into32_arith(a,b,c,d,e)              \
    _TIE_hmd1a_common_tie_shift8_into32_arith(a,b,c,d,e)
#define shift32_arith(a,b,c)                        \
    _TIE_hmd1a_common_tie_shift32_arith(a,b,c)
#define mac8bx8b(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_mac8bx8b(a,b,c,d)
#define mac8bx8b_sparse(a,b,c,d)                    \
    _TIE_hmd1a_common_tie_mac8bx8b_sparse(a,b,c,d)
#define mac8bx8b_conv(a,b,c,d)                      \
    _TIE_hmd1a_common_tie_mac8bx8b_conv(a,b,c,d)
#define mir_init(a)                                 \
    _TIE_hmd1a_common_tie_mir_init(a)
#define f_abs(a,b,c,d)                              \
    _TIE_hmd1a_common_tie_f_abs(a,b,c,d)
#define fclamp(a,b,c,d,e,f)                         \
    _TIE_hmd1a_common_tie_fclamp(a,b,c,d,e,f)
#define fclamp_bp(a,b,c,d,e,f)                      \
    _TIE_hmd1a_common_tie_fclamp_bp(a,b,c,d,e,f)
#define fclamp_one(a,b,c,d)                         \
    _TIE_hmd1a_common_tie_fclamp_one(a,b,c,d)
#define fmax(a,b,c,d,e,f)                           \
    _TIE_hmd1a_common_tie_fmax(a,b,c,d,e,f)
#define fmin(a,b,c,d,e,f)                           \
    _TIE_hmd1a_common_tie_fmin(a,b,c,d,e,f)
#define max_fr(a,b)                                 \
    _TIE_hmd1a_common_tie_max_fr(a,b)
#define min_fr(a,b)                                 \
    _TIE_hmd1a_common_tie_min_fr(a,b)
#define log2(a)                                     \
    _TIE_hmd1a_common_tie_log2(a)
#define pow2(a)                                     \
    _TIE_hmd1a_common_tie_pow2(a)
#define sigmoid(a)                                  \
    _TIE_hmd1a_common_tie_sigmoid(a)
#define inv(a)                                      \
    _TIE_hmd1a_common_tie_inv(a)
#define ratio(a,b,c,d)                              \
    _TIE_hmd1a_common_tie_ratio(a,b,c,d)
#define atanratio(a,b)                              \
    _TIE_hmd1a_common_tie_atanratio(a,b)
#define invsqrt(a)                                  \
    _TIE_hmd1a_common_tie_invsqrt(a)
#define sine(a)                                     \
    _TIE_hmd1a_common_tie_sine(a)
#define cosine(a)                                   \
    _TIE_hmd1a_common_tie_cosine(a)
#define log2mul(a,b,c,d)                            \
    _TIE_hmd1a_common_tie_log2mul(a,b,c,d)
#define cspow2(a,b)                                 \
    _TIE_hmd1a_common_tie_cspow2(a,b)
#define comp(a,b,c,d)                               \
    _TIE_hmd1a_common_tie_comp(a,b,c,d)
#define eq(a,b,c,d)                                 \
    _TIE_hmd1a_common_tie_eq(a,b,c,d)
#define ge(a,b,c,d)                                 \
    _TIE_hmd1a_common_tie_ge(a,b,c,d)
#define gt(a,b,c,d)                                 \
    _TIE_hmd1a_common_tie_gt(a,b,c,d)
#define le(a,b,c,d)                                 \
    _TIE_hmd1a_common_tie_le(a,b,c,d)
#define lt(a,b,c,d)                                 \
    _TIE_hmd1a_common_tie_lt(a,b,c,d)
#define ne(a,b,c,d)                                 \
    _TIE_hmd1a_common_tie_ne(a,b,c,d)
#define comp_const(a,b,c,d)                         \
    _TIE_hmd1a_common_tie_comp_const(a,b,c,d)
#define eq_const(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_eq_const(a,b,c,d)
#define ge_const(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_ge_const(a,b,c,d)
#define gt_const(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_gt_const(a,b,c,d)
#define le_const(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_le_const(a,b,c,d)
#define lt_const(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_lt_const(a,b,c,d)
#define ne_const(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_ne_const(a,b,c,d)
#define comp_fr(a,b)                                \
    _TIE_hmd1a_common_tie_comp_fr(a,b)
#define eq_fr(a,b)                                  \
    _TIE_hmd1a_common_tie_eq_fr(a,b)
#define ge_fr(a,b)                                  \
    _TIE_hmd1a_common_tie_ge_fr(a,b)
#define gt_fr(a,b)                                  \
    _TIE_hmd1a_common_tie_gt_fr(a,b)
#define le_fr(a,b)                                  \
    _TIE_hmd1a_common_tie_le_fr(a,b)
#define lt_fr(a,b)                                  \
    _TIE_hmd1a_common_tie_lt_fr(a,b)
#define ne_fr(a,b)                                  \
    _TIE_hmd1a_common_tie_ne_fr(a,b)
#define neg_fr(a)                                   \
    _TIE_hmd1a_common_tie_neg_fr(a)
#define abs_fr(a)                                   \
    _TIE_hmd1a_common_tie_abs_fr(a)
#define deqz(a)                                     \
    _TIE_hmd1a_common_tie_deqz(a)
#define dgez(a)                                     \
    _TIE_hmd1a_common_tie_dgez(a)
#define dgtz(a)                                     \
    _TIE_hmd1a_common_tie_dgtz(a)
#define dlez(a)                                     \
    _TIE_hmd1a_common_tie_dlez(a)
#define dltz(a)                                     \
    _TIE_hmd1a_common_tie_dltz(a)
#define dnez(a)                                     \
    _TIE_hmd1a_common_tie_dnez(a)
#define veq(a,b)                                    \
    _TIE_hmd1a_common_tie_veq(a,b)
#define vge(a,b)                                    \
    _TIE_hmd1a_common_tie_vge(a,b)
#define vgt(a,b)                                    \
    _TIE_hmd1a_common_tie_vgt(a,b)
#define vle(a,b)                                    \
    _TIE_hmd1a_common_tie_vle(a,b)
#define vlt(a,b)                                    \
    _TIE_hmd1a_common_tie_vlt(a,b)
#define vne(a,b)                                    \
    _TIE_hmd1a_common_tie_vne(a,b)
#define veq_const(a,b,c)                            \
    _TIE_hmd1a_common_tie_veq_const(a,b,c)
#define vge_const(a,b,c)                            \
    _TIE_hmd1a_common_tie_vge_const(a,b,c)
#define vgt_const(a,b,c)                            \
    _TIE_hmd1a_common_tie_vgt_const(a,b,c)
#define vle_const(a,b,c)                            \
    _TIE_hmd1a_common_tie_vle_const(a,b,c)
#define vlt_const(a,b,c)                            \
    _TIE_hmd1a_common_tie_vlt_const(a,b,c)
#define vne_const(a,b,c)                            \
    _TIE_hmd1a_common_tie_vne_const(a,b,c)
#define sel_1b2(a,b,c,d)                            \
    _TIE_hmd1a_common_tie_sel_1b2(a,b,c,d)
#define sel_eq(a,b,c)                               \
    _TIE_hmd1a_common_tie_sel_eq(a,b,c)
#define sel_ge(a,b,c)                               \
    _TIE_hmd1a_common_tie_sel_ge(a,b,c)
#define sel_gt(a,b,c)                               \
    _TIE_hmd1a_common_tie_sel_gt(a,b,c)
#define sel_le(a,b,c)                               \
    _TIE_hmd1a_common_tie_sel_le(a,b,c)
#define sel_lt(a,b,c)                               \
    _TIE_hmd1a_common_tie_sel_lt(a,b,c)
#define sel_ne(a,b,c)                               \
    _TIE_hmd1a_common_tie_sel_ne(a,b,c)
#define sel_ar(a,b,c)                               \
    _TIE_hmd1a_common_tie_sel_ar(a,b,c)
#define vsel(a,b,c)                                 \
    _TIE_hmd1a_common_tie_vsel(a,b,c)
#define vsel_ar(a,b,c)                              \
    _TIE_hmd1a_common_tie_vsel_ar(a,b,c)
#define andb2(a,b)                                  \
    _TIE_hmd1a_common_tie_andb2(a,b)
#define andbc2(a,b)                                 \
    _TIE_hmd1a_common_tie_andbc2(a,b)
#define orb2(a,b)                                   \
    _TIE_hmd1a_common_tie_orb2(a,b)
#define orbc2(a,b)                                  \
    _TIE_hmd1a_common_tie_orbc2(a,b)
#define xorb2(a,b)                                  \
    _TIE_hmd1a_common_tie_xorb2(a,b)
#define bcount0_maskI(a,b)                          \
    _TIE_hmd1a_common_tie_bcount0_maskI(a,b)
#define bcount0_maskR(a,b)                          \
    _TIE_hmd1a_common_tie_bcount0_maskR(a,b)
#define bcount1_maskI(a,b)                          \
    _TIE_hmd1a_common_tie_bcount1_maskI(a,b)
#define bcount1_maskR(a,b)                          \
    _TIE_hmd1a_common_tie_bcount1_maskR(a,b)
#define bfirst0_maskI(a,b)                          \
    _TIE_hmd1a_common_tie_bfirst0_maskI(a,b)
#define bfirst0_maskR(a,b)                          \
    _TIE_hmd1a_common_tie_bfirst0_maskR(a,b)
#define bfirst1_maskI(a,b)                          \
    _TIE_hmd1a_common_tie_bfirst1_maskI(a,b)
#define bfirst1_maskR(a,b)                          \
    _TIE_hmd1a_common_tie_bfirst1_maskR(a,b)
#define blast0_maskI(a,b)                           \
    _TIE_hmd1a_common_tie_blast0_maskI(a,b)
#define blast0_maskR(a,b)                           \
    _TIE_hmd1a_common_tie_blast0_maskR(a,b)
#define blast1_maskI(a,b)                           \
    _TIE_hmd1a_common_tie_blast1_maskI(a,b)
#define blast1_maskR(a,b)                           \
    _TIE_hmd1a_common_tie_blast1_maskR(a,b)
#define bgetI(a,b)                                  \
    _TIE_hmd1a_common_tie_bgetI(a,b)
#define bgetR(a,b)                                  \
    _TIE_hmd1a_common_tie_bgetR(a,b)
#define bsetI(a,b,c)                                \
    _TIE_hmd1a_common_tie_bsetI(a,b,c)
#define bsetR(a,b,c)                                \
    _TIE_hmd1a_common_tie_bsetR(a,b,c)
#define exp_adj(a,b,c,d,e)                          \
    _TIE_hmd1a_common_tie_exp_adj(a,b,c,d,e)
#define exp_adji(a,b,c,d,e)                         \
    _TIE_hmd1a_common_tie_exp_adji(a,b,c,d,e)
#define exp_adj_fr(a,b)                             \
    _TIE_hmd1a_common_tie_exp_adj_fr(a,b)
#define exp_adji_fr(a,b)                            \
    _TIE_hmd1a_common_tie_exp_adji_fr(a,b)
#define s_neg(a)                                    \
    _TIE_hmd1a_common_tie_s_neg(a)
#define s_copy(a,b)                                 \
    _TIE_hmd1a_common_tie_s_copy(a,b)
#define s_and(a,b)                                  \
    _TIE_hmd1a_common_tie_s_and(a,b)
#define s_andc(a,b)                                 \
    _TIE_hmd1a_common_tie_s_andc(a,b)
#define s_or(a,b)                                   \
    _TIE_hmd1a_common_tie_s_or(a,b)
#define s_orc(a,b)                                  \
    _TIE_hmd1a_common_tie_s_orc(a,b)
#define s_xor(a,b)                                  \
    _TIE_hmd1a_common_tie_s_xor(a,b)
#define s_vneg(a)                                   \
    _TIE_hmd1a_common_tie_s_vneg(a)
#define s_vcopy(a,b)                                \
    _TIE_hmd1a_common_tie_s_vcopy(a,b)
#define s_vand(a,b)                                 \
    _TIE_hmd1a_common_tie_s_vand(a,b)
#define s_vandc(a,b)                                \
    _TIE_hmd1a_common_tie_s_vandc(a,b)
#define s_vor(a,b)                                  \
    _TIE_hmd1a_common_tie_s_vor(a,b)
#define s_vorc(a,b)                                 \
    _TIE_hmd1a_common_tie_s_vorc(a,b)
#define s_vxor(a,b)                                 \
    _TIE_hmd1a_common_tie_s_vxor(a,b)
#define floorp_frac(a,b,c,d,e,f)                    \
    _TIE_hmd1a_common_tie_floorp_frac(a,b,c,d,e,f)
#define idx_frac(a,b,c,d,e)                         \
    _TIE_hmd1a_common_tie_idx_frac(a,b,c,d,e)
#define truncate_fr(a)                              \
    _TIE_hmd1a_common_tie_truncate_fr(a)
#define rmax_idx(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_rmax_idx(a,b,c,d)
#define rmin_idx(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_rmin_idx(a,b,c,d)
#define vmaxmin_init(a,b,c)                         \
    _TIE_hmd1a_common_tie_vmaxmin_init(a,b,c)
#define vmax_idx(a,b,c)                             \
    _TIE_hmd1a_common_tie_vmax_idx(a,b,c)
#define vmin_idx(a,b,c)                             \
    _TIE_hmd1a_common_tie_vmin_idx(a,b,c)
#define vmax(a,b)                                   \
    _TIE_hmd1a_common_tie_vmax(a,b)
#define vmin(a,b)                                   \
    _TIE_hmd1a_common_tie_vmin(a,b)
#define sortupd_asc_vr(a,b,c,d,e)                   \
    _TIE_hmd1a_common_tie_sortupd_asc_vr(a,b,c,d,e)
#define sortupd_des_vr(a,b,c,d,e)                   \
    _TIE_hmd1a_common_tie_sortupd_des_vr(a,b,c,d,e)
#define sortupd_asc_ar(a,b,c)                       \
    _TIE_hmd1a_common_tie_sortupd_asc_ar(a,b,c)
#define sortupd_des_ar(a,b,c)                       \
    _TIE_hmd1a_common_tie_sortupd_des_ar(a,b,c)
#define vbool(a,b,c)                                \
    _TIE_hmd1a_common_tie_vbool(a,b,c)
#define align_up(a,b)                               \
    _TIE_hmd1a_common_tie_align_up(a,b)
#define mv_MIR(a)                                   \
    _TIE_hmd1a_common_tie_mv_MIR(a)
#define mir18_move(a)                               \
    _TIE_hmd1a_common_tie_mir18_move(a)
#define mv_ULSR(a)                                  \
    _TIE_hmd1a_common_tie_mv_ULSR(a)
#define ulsr32_move(a)                              \
    _TIE_hmd1a_common_tie_ulsr32_move(a)
#define mv_CR(a)                                    \
    _TIE_hmd1a_common_tie_mv_CR(a)
#define cr64_move(a)                                \
    _TIE_hmd1a_common_tie_cr64_move(a)
#define ld_FR(a,b)                                  \
    _TIE_hmd1a_common_tie_ld_FR((const fr32 *)(a),b)
#define st_FR(a,b,c)                                \
    _TIE_hmd1a_common_tie_st_FR(a,(fr32 *)(b),c)
#define ld_FR_idxR(a,b)                             \
    _TIE_hmd1a_common_tie_ld_FR_idxR((const fr32 *)(a),b)
#define st_FR_idxR(a,b,c)                           \
    _TIE_hmd1a_common_tie_st_FR_idxR(a,(fr32 *)(b),c)
#define ld_FR_postI(a,b,c)                          \
    _TIE_hmd1a_common_tie_ld_FR_postI(a,(const fr32 *)(b),c)
#define st_FR_postI(a,b,c)                          \
    _TIE_hmd1a_common_tie_st_FR_postI(a,(fr32 *)(b),c)
#define ld_FR_postR(a,b,c)                          \
    _TIE_hmd1a_common_tie_ld_FR_postR(a,(const fr32 *)(b),c)
#define st_FR_postR(a,b,c)                          \
    _TIE_hmd1a_common_tie_st_FR_postR(a,(fr32 *)(b),c)
#define ld_VR(a,b)                                  \
    _TIE_hmd1a_common_tie_ld_VR((const vr64 *)(a),b)
#define st_VR(a,b,c)                                \
    _TIE_hmd1a_common_tie_st_VR(a,(vr64 *)(b),c)
#define ld_VR_idxR(a,b)                             \
    _TIE_hmd1a_common_tie_ld_VR_idxR((const vr64 *)(a),b)
#define st_VR_idxR(a,b,c)                           \
    _TIE_hmd1a_common_tie_st_VR_idxR(a,(vr64 *)(b),c)
#define ld_VR_postI(a,b,c)                          \
    _TIE_hmd1a_common_tie_ld_VR_postI(a,(const vr64 *)(b),c)
#define st_VR_postI(a,b,c)                          \
    _TIE_hmd1a_common_tie_st_VR_postI(a,(vr64 *)(b),c)
#define ld_VR_postR(a,b,c)                          \
    _TIE_hmd1a_common_tie_ld_VR_postR(a,(const vr64 *)(b),c)
#define st_VR_postR(a,b,c)                          \
    _TIE_hmd1a_common_tie_st_VR_postR(a,(vr64 *)(b),c)
#define mv_FR(a)                                    \
    _TIE_hmd1a_common_tie_mv_FR(a)
#define move_ar_fr(a)                               \
    _TIE_hmd1a_common_tie_move_ar_fr(a)
#define move_fr_ar(a)                               \
    _TIE_hmd1a_common_tie_move_fr_ar(a)
#define fr32_move(a)                                \
    _TIE_hmd1a_common_tie_fr32_move(a)
#define fr32_loadi(a,b)                             \
    _TIE_hmd1a_common_tie_fr32_loadi((const fr32 *)(a),b)
#define fr32_storei(a,b,c)                          \
    _TIE_hmd1a_common_tie_fr32_storei(a,(fr32 *)(b),c)
#define fr32_loadx(a,b)                             \
    _TIE_hmd1a_common_tie_fr32_loadx((const fr32 *)(a),b)
#define fr32_storex(a,b,c)                          \
    _TIE_hmd1a_common_tie_fr32_storex(a,(fr32 *)(b),c)
#define fr32_loadip(a,b,c)                          \
    _TIE_hmd1a_common_tie_fr32_loadip(a,(const fr32 *)(b),c)
#define fr32_storeip(a,b,c)                         \
    _TIE_hmd1a_common_tie_fr32_storeip(a,(fr32 *)(b),c)
#define fr32_loadxp(a,b,c)                          \
    _TIE_hmd1a_common_tie_fr32_loadxp(a,(const fr32 *)(b),c)
#define fr32_storexp(a,b,c)                         \
    _TIE_hmd1a_common_tie_fr32_storexp(a,(fr32 *)(b),c)
#define fr32_rtor_int32(a)                          \
    _TIE_hmd1a_common_tie_fr32_rtor_int32(a)
#define fr32_rtor_uint32(a)                         \
    _TIE_hmd1a_common_tie_fr32_rtor_uint32(a)
#define int32_rtor_fr32(a)                          \
    _TIE_hmd1a_common_tie_int32_rtor_fr32(a)
#define uint32_rtor_fr32(a)                         \
    _TIE_hmd1a_common_tie_uint32_rtor_fr32(a)
#define mv_VR(a)                                    \
    _TIE_hmd1a_common_tie_mv_VR(a)
#define vr64_move(a)                                \
    _TIE_hmd1a_common_tie_vr64_move(a)
#define vr64_loadi(a,b)                             \
    _TIE_hmd1a_common_tie_vr64_loadi((const vr64 *)(a),b)
#define vr64_storei(a,b,c)                          \
    _TIE_hmd1a_common_tie_vr64_storei(a,(vr64 *)(b),c)
#define vr64_loadx(a,b)                             \
    _TIE_hmd1a_common_tie_vr64_loadx((const vr64 *)(a),b)
#define vr64_storex(a,b,c)                          \
    _TIE_hmd1a_common_tie_vr64_storex(a,(vr64 *)(b),c)
#define vr64_loadip(a,b,c)                          \
    _TIE_hmd1a_common_tie_vr64_loadip(a,(const vr64 *)(b),c)
#define vr64_storeip(a,b,c)                         \
    _TIE_hmd1a_common_tie_vr64_storeip(a,(vr64 *)(b),c)
#define vr64_loadxp(a,b,c)                          \
    _TIE_hmd1a_common_tie_vr64_loadxp(a,(const vr64 *)(b),c)
#define vr64_storexp(a,b,c)                         \
    _TIE_hmd1a_common_tie_vr64_storexp(a,(vr64 *)(b),c)
#define get_VRH(a)                                  \
    _TIE_hmd1a_common_tie_get_VRH(a)
#define get_VRL(a)                                  \
    _TIE_hmd1a_common_tie_get_VRL(a)
#define set_VRH(a,b)                                \
    _TIE_hmd1a_common_tie_set_VRH(a,b)
#define set_VRL(a,b)                                \
    _TIE_hmd1a_common_tie_set_VRL(a,b)
#define vr64_pair(a,b)                              \
    _TIE_hmd1a_common_tie_vr64_pair(a,b)
#define move_ar_bbr(a)                              \
    _TIE_hmd1a_common_tie_move_ar_bbr(a)
#define move_bbr_ar(a)                              \
    _TIE_hmd1a_common_tie_move_bbr_ar(a)
#define shift_from_bbr(a,b)                         \
    _TIE_hmd1a_common_tie_shift_from_bbr(a,b)
#define shift_to_bbr(a,b)                           \
    _TIE_hmd1a_common_tie_shift_to_bbr(a,b)
#define atbool_rtor_int32(a)                        \
    _TIE_hmd1a_common_tie_atbool_rtor_int32(a)
#define atbool_rtor_uint32(a)                       \
    _TIE_hmd1a_common_tie_atbool_rtor_uint32(a)
#define int32_rtor_atbool(a)                        \
    _TIE_hmd1a_common_tie_int32_rtor_atbool(a)
#define uint32_rtor_atbool(a)                       \
    _TIE_hmd1a_common_tie_uint32_rtor_atbool(a)
#define ld_ar_x2(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_ld_ar_x2(a,b,(const void *)(c),d)
#define st_ar_x2(a,b,c,d)                           \
    _TIE_hmd1a_common_tie_st_ar_x2((void *)(a),b,c,d)

#endif //TIE_INCLUDE_H



/* End of File */

