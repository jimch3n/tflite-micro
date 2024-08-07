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


#include "dmx1a_common_tie.h"
#include "dmx1a_version_tie.h"
#include <xtensa/tie/xt_misc.h>
#include <xtensa/tie/xt_mul.h>


#undef st_PERM
#undef perm16_storei
#undef ld_PERM
#undef perm16_loadi
#undef st_ULSR
#undef ulsr128_storei
#undef ld_ULSR
#undef ulsr128_loadi
#undef st_MIR
#undef mir30_storei
#undef ld_MIR
#undef mir30_loadi
#undef st_CR
#undef cr64_storei
#undef ld_CR
#undef cr64_loadi
#undef st_WR
#undef wr64_storei
#undef ld_WR
#undef wr64_loadi
#undef RUR_JammingBit
#undef WUR_JammingBit
#undef RUR_AccExtend_0
#undef WUR_AccExtend_0
#undef RUR_AccExtend_1
#undef WUR_AccExtend_1
#undef RUR_AccExtend_2
#undef WUR_AccExtend_2
#undef RUR_AccExtend_3
#undef WUR_AccExtend_3
#undef RUR_BB0_0
#undef WUR_BB0_0
#undef RUR_BB0_1
#undef WUR_BB0_1
#undef RUR_BB0_2
#undef WUR_BB0_2
#undef RUR_BB0_3
#undef WUR_BB0_3
#undef RUR_BB1_0
#undef WUR_BB1_0
#undef RUR_BB1_1
#undef WUR_BB1_1
#undef RUR_BB1_2
#undef WUR_BB1_2
#undef RUR_BB1_3
#undef WUR_BB1_3
#undef RUR_BB2_0
#undef WUR_BB2_0
#undef RUR_BB2_1
#undef WUR_BB2_1
#undef RUR_BB2_2
#undef WUR_BB2_2
#undef RUR_BB2_3
#undef WUR_BB2_3
#undef RUR_BB3_0
#undef WUR_BB3_0
#undef RUR_BB3_1
#undef WUR_BB3_1
#undef RUR_BB3_2
#undef WUR_BB3_2
#undef RUR_BB3_3
#undef WUR_BB3_3
#undef RUR_BB4_0
#undef WUR_BB4_0
#undef RUR_BB4_1
#undef WUR_BB4_1
#undef RUR_BB4_2
#undef WUR_BB4_2
#undef RUR_BB4_3
#undef WUR_BB4_3
#undef RUR_BB5_0
#undef WUR_BB5_0
#undef RUR_BB5_1
#undef WUR_BB5_1
#undef RUR_BB5_2
#undef WUR_BB5_2
#undef RUR_BB5_3
#undef WUR_BB5_3
#undef RUR_BB6_0
#undef WUR_BB6_0
#undef RUR_BB6_1
#undef WUR_BB6_1
#undef RUR_BB6_2
#undef WUR_BB6_2
#undef RUR_BB6_3
#undef WUR_BB6_3
#undef RUR_BB7_0
#undef WUR_BB7_0
#undef RUR_BB7_1
#undef WUR_BB7_1
#undef RUR_BB7_2
#undef WUR_BB7_2
#undef RUR_BB7_3
#undef WUR_BB7_3
#undef RUR_MvmAux
#undef WUR_MvmAux
#undef RUR_VB1_0
#undef WUR_VB1_0
#undef RUR_VB1_1
#undef WUR_VB1_1
#undef RUR_VB1_2
#undef WUR_VB1_2
#undef RUR_VB1_3
#undef WUR_VB1_3
#undef RUR_VB2_0
#undef WUR_VB2_0
#undef RUR_VB2_1
#undef WUR_VB2_1
#undef RUR_VB2_2
#undef WUR_VB2_2
#undef RUR_VB2_3
#undef WUR_VB2_3
#undef RUR_VB3_0
#undef WUR_VB3_0
#undef RUR_VB3_1
#undef WUR_VB3_1
#undef RUR_VB3_2
#undef WUR_VB3_2
#undef RUR_VB3_3
#undef WUR_VB3_3
#undef RUR_VB4_0
#undef WUR_VB4_0
#undef RUR_VB4_1
#undef WUR_VB4_1
#undef RUR_VB4_2
#undef WUR_VB4_2
#undef RUR_VB4_3
#undef WUR_VB4_3
#undef RUR_VB5_0
#undef WUR_VB5_0
#undef RUR_VB5_1
#undef WUR_VB5_1
#undef RUR_VB5_2
#undef WUR_VB5_2
#undef RUR_VB5_3
#undef WUR_VB5_3
#undef RUR_VB6_0
#undef WUR_VB6_0
#undef RUR_VB6_1
#undef WUR_VB6_1
#undef RUR_VB6_2
#undef WUR_VB6_2
#undef RUR_VB6_3
#undef WUR_VB6_3
#undef RUR_VB7_0
#undef WUR_VB7_0
#undef RUR_VB7_1
#undef WUR_VB7_1
#undef RUR_VB7_2
#undef WUR_VB7_2
#undef RUR_VB7_3
#undef WUR_VB7_3
#undef RUR_look_state
#undef WUR_look_state
#undef load32x4_vr_idxR
#undef load32x4_vr_idxI
#undef load32x4_vr_postR
#undef load32x4_vr_postI
#undef load32x4_vr_circI
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
#undef load32x4_vr_idxR_perm_vr
#undef load32x4_vr_idxI_perm_vr
#undef load32x4_vr_postR_perm_vr
#undef load32x4_vr_postI_perm_vr
#undef load32x4_vr_circI_perm_vr
#undef load32x2_vr_idxR_perm_vr
#undef load32x2_vr_idxI_perm_vr
#undef load32x2_vr_postR_perm_vr
#undef load32x2_vr_postI_perm_vr
#undef load32x2_vr_circI_perm_vr
#undef load32x1_vr_idxR_perm_vr
#undef load32x1_vr_idxI_perm_vr
#undef load32x1_vr_postR_perm_vr
#undef load32x1_vr_postI_perm_vr
#undef load32x1_vr_circI_perm_vr
#undef set_perm16
#undef set_perm16_cond
#undef load16x4_vr_idxR
#undef load16x4_vr_idxI
#undef load16x4_vr_postR
#undef load16x4_vr_postI
#undef load16x4_vr_circI
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
#undef load8x4_vr_idxR
#undef load8x4_vr_idxI
#undef load8x4_vr_postR
#undef load8x4_vr_postI
#undef load8x4_vr_circI
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
#undef align_32x4_load
#undef align_24x4_load
#undef align_16x4_load
#undef align_8x4_load
#undef load_32x4_vr_a
#undef load_24x4_vr_a
#undef load_16x4_vr_a
#undef load_8x4_vr_a
#undef load_32x4_vr_a_circ
#undef load32x2_wr_idxR
#undef load32x2_wr_idxI
#undef load32x2_wr_postR
#undef load32x2_wr_postI
#undef store32x4_vr_idxR
#undef store32x4_vr_idxI
#undef store32x4_vr_postR
#undef store32x4_vr_postI
#undef store32x4_vr_circI
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
#undef store32x4_vr_br_idxR
#undef store32x4_vr_br_idxI
#undef store32x4_vr_br_postR
#undef store32x4_vr_br_postI
#undef store32x4_vr_br_circI
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
#undef store32x4_vr_vr_idxR_perm
#undef store32x4_vr_vr_idxI_perm
#undef store32x4_vr_vr_postR_perm
#undef store32x4_vr_vr_postI_perm
#undef store32x4_vr_vr_circI_perm
#undef store16x4_vr_idxR
#undef store16x4_vr_idxI
#undef store16x4_vr_postR
#undef store16x4_vr_postI
#undef store16x4_vr_circI
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
#undef store8x4_vr_idxR
#undef store8x4_vr_idxI
#undef store8x4_vr_postR
#undef store8x4_vr_postI
#undef store8x4_vr_circI
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
#undef align_32x4_store
#undef align_16x4_store
#undef align_8x4_store
#undef store_32x4_vr_a
#undef store_24x4_vr_a
#undef store_16x4_vr_a
#undef store_8x4_vr_a
#undef store_32x4_vr_a_circ
#undef flush_32x4
#undef flush_24x4
#undef flush_16x4
#undef flush_8x4
#undef br_get_idx_2_5
#undef br_get_idx_6_13
#undef br_get_idx_next_odd
#undef br_upd_idx_spec
#undef build_palindrome
#undef load_vr_bdir
#undef load_vr_brev
#undef store_vrl_wr_bdir
#undef store_vrh_wr_bdir
#undef store_vrl_wr_brev
#undef store_vrh_wr_brev
#undef store_vrl_vrl_postR
#undef store_vrh_vrh_postR
#undef store_vrl_wr_postR
#undef store_wr_vrl_postR
#undef store_vrh_wr_postR
#undef store_wr_vrh_postR
#undef load_fr_postI
#undef store_fr_postI
#undef move32_wr_vr
#undef move32_wr_fr
#undef move64_wr_vr
#undef move64_vr_wr
#undef move32_ar_vr
#undef move32_ar_vr_idx
#undef move32_fr_vr_idx
#undef int_to_xt_bool
#undef int_to_xt_bool2
#undef int_to_xt_bool4
#undef move_vr_eqz
#undef move_vr_gez
#undef move_vr_gtz
#undef move_vr_lez
#undef move_vr_ltz
#undef move_vr_nez
#undef move_vr_sat
#undef vmove_vr_eqz
#undef vmove_vr_gez
#undef vmove_vr_gtz
#undef vmove_vr_lez
#undef vmove_vr_ltz
#undef vmove_vr_nez
#undef vmove_vr_sat
#undef replicate
#undef replicate_ar
#undef creplicate_H
#undef creplicate_L
#undef vreplicate
#undef vreplicate_fr
#undef vreplicate_hr
#undef hreplicate_fr
#undef convert_16I_to_32F_x1
#undef convert_16I_to_32F_x2
#undef convert_16I_to_32F_x4
#undef convert_32F_to_16I_x1
#undef convert_32F_to_16I_x2
#undef convert_32F_to_16I_x4
#undef convert_32F_to_16F_x1
#undef convert_32F_to_16F_x2
#undef convert_32F_to_16F_x4
#undef convert_16F_to_32F_x1
#undef convert_16F_to_32F_x2
#undef convert_16F_to_32F_x4
#undef convert_32I_to_32F_x1
#undef convert_32F_to_32I_x1
#undef convert_IEEE_float_to_32F_x4
#undef convert_32F_to_IEEE_float_x4
#undef convert_IEEE_float_to_32F
#undef convert_32F_to_IEEE_float
#undef convert_32I_to_64F
#undef convert_64F_to_32I
#undef convert_32F_to_64F
#undef convert_64F_to_32F
#undef convert_IEEE_double_to_64F
#undef convert_64F_to_IEEE_double
#undef affine_adj_L
#undef affine_adj_H
#undef affine_perm_L
#undef affine_perm_H
#undef linear_adj_L
#undef linear_adj_H
#undef linear_perm_L
#undef linear_perm_H
#undef bfly_z_yl_xl_wr
#undef bfly_z_yl_xh_wr
#undef bfly_z_yh_xl_wr
#undef bfly_z_yh_xh_wr
#undef bfly_z_wr_xl_yl
#undef bfly_z_wr_xh_yl
#undef bfly_z_wr_xl_yh
#undef bfly_z_wr_xh_yh
#undef bfly_zl_zl_xl_yl
#undef bfly_zl_zl_xh_yl
#undef bfly_zh_zh_xl_yh
#undef bfly_zh_zh_xh_yh
#undef bfly_wr_zl_xl_yl
#undef bfly_wr_zl_xh_yl
#undef bfly_wr_zh_xl_yh
#undef bfly_wr_zh_xh_yh
#undef cmul
#undef cmul_conj
#undef cmac
#undef cmac_conj
#undef cmas
#undef cmas_conj
#undef cmul_L
#undef cmul_H
#undef cmac_L
#undef cmac_H
#undef cmas_L
#undef cmas_H
#undef cmac_Lx2
#undef cmac_Hx2
#undef cmul_x2
#undef cmac_adj_x2
#undef cmas_adj_x2
#undef xcorr
#undef xconv
#undef qmul_1
#undef qmul_2
#undef matmul_2x2
#undef vadds
#undef vmidp
#undef vmuls
#undef vmacs_adj
#undef vmuls_perm
#undef vmacs_perm
#undef vssub_L
#undef vssub_H
#undef vssub_x2
#undef vinterp_L
#undef vinterp_H
#undef vinterp_x2
#undef csums_L
#undef csums_H
#undef dsums_L
#undef dsums_H
#undef vadd_hr
#undef vsub_hr
#undef vmul_hr
#undef vmac_hr
#undef fpadd
#undef fpmul
#undef fpmac
#undef fpmul_sum3
#undef vscale
#undef vscale_adds
#undef fadds
#undef fmacs
#undef fmuls
#undef fmul_sum3
#undef dadds
#undef dmuls
#undef dmacs
#undef vabs
#undef vexp_adj
#undef vexp_adji
#undef vperm
#undef vperms
#undef vpermsi
#undef seta_vr
#undef vseta_vr
#undef seta_ar
#undef seta_fr
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
#undef log2_fr
#undef pow2_fr
#undef sigmoid_fr
#undef inv_fr
#undef invsqrt_fr
#undef sine_fr
#undef cosine_fr
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
#undef sel
#undef sel_1b4
#undef sel_eq
#undef sel_ge
#undef sel_gt
#undef sel_le
#undef sel_lt
#undef sel_ne
#undef vsel
#undef andb1
#undef andbc1
#undef orb1
#undef orbc1
#undef xorb1
#undef andb4
#undef andbc4
#undef orb4
#undef orbc4
#undef xorb4
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
#undef s_vnegs
#undef s_vcopy
#undef s_vand
#undef s_vandc
#undef s_vor
#undef s_vorc
#undef s_vxor
#undef s_vnegs_hr
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
#undef range_init
#undef range_check
#undef afloat_exp_extract
#undef exp_shift_amount
#undef flush_32x4_bounded
#undef load_AccExtend_postI
#undef load_BB0_flex
#undef load_BB1_flex
#undef load_BB2_flex
#undef load_BB3_flex
#undef load_BB4_flex
#undef load_BB5_flex
#undef load_BB6_flex
#undef load_BB7_flex
#undef load_BB0_postI
#undef load_BB1_postI
#undef load_BB2_postI
#undef load_BB3_postI
#undef load_BB4_postI
#undef load_BB5_postI
#undef load_BB6_postI
#undef load_BB7_postI
#undef load_BBx_a_bounded
#undef load_VB1_postI
#undef load_VB2_postI
#undef load_VB3_postI
#undef load_VB4_postI
#undef load_VB5_postI
#undef load_VB6_postI
#undef load_VB7_postI
#undef load_32x4_vr_a_bounded
#undef load_lookup_AccExtend_postI
#undef load_lookup_vr_postI
#undef load32x1_lookup_AccExtend_idx16vr
#undef load32x1_lookup_vr_idx16vr
#undef load32x1_vr_idx16vr
#undef mac8bx8b
#undef mac8bx8b_conv
#undef mac8bx8b_sparse
#undef mir_init
#undef mov_AccExtend_vr
#undef mov_BB_vrVB
#undef mov_vr_AccExtend
#undef mov_vrVB_BB
#undef next_lookup_load
#undef next_lookup_store
#undef precess_16bits
#undef rectify32_into8
#undef rnd_sat_pack
#undef set_BB_zero
#undef shift8_into32_arith
#undef shift32_arith
#undef store_32x4_vr_a_bounded
#undef store_AccExtend_postI
#undef store_BB0_postI
#undef store_BB1_postI
#undef store_BB2_postI
#undef store_BB3_postI
#undef store_BB4_postI
#undef store_BB5_postI
#undef store_BB6_postI
#undef store_BB7_postI
#undef store_VB1_postI
#undef store_VB2_postI
#undef store_VB3_postI
#undef store_VB4_postI
#undef store_VB5_postI
#undef store_VB6_postI
#undef store_VB7_postI
#undef store_lookup_AccExtend_postI
#undef store_lookup_vr_postI
#undef mv_WR
#undef wr64_move
#undef mv_PERM
#undef perm16_move
#undef mv_MIR
#undef mir30_move
#undef mv_ULSR
#undef ulsr128_move
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
#undef ld_HR
#undef st_HR
#undef ld_HR_idxR
#undef st_HR_idxR
#undef ld_HR_postI
#undef st_HR_postI
#undef ld_HR_postR
#undef st_HR_postR
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
#undef mv_HR
#undef vr64_move
#undef vr64_loadi
#undef vr64_storei
#undef vr64_loadx
#undef vr64_storex
#undef vr64_loadip
#undef vr64_storeip
#undef vr64_loadxp
#undef vr64_storexp
#undef vr64_rtor_int64
#undef vr64_rtor_uint64
#undef int64_rtor_vr64
#undef uint64_rtor_vr64
#undef vr64_pair
#undef get_HRL
#undef get_HRH
#undef set_HRL
#undef set_HRH
#undef mv_VR
#undef vr128_move
#undef vr128_loadi
#undef vr128_storei
#undef vr128_loadx
#undef vr128_storex
#undef vr128_loadip
#undef vr128_storeip
#undef vr128_loadxp
#undef vr128_storexp
#undef vr128_pair
#undef set_VRL
#undef set_VRH
#undef get_VRL
#undef get_VRH
#undef vr128_quad
#undef get_VRQ0
#undef get_VRQ1
#undef get_VRQ2
#undef get_VRQ3
#undef set_VRQ0
#undef set_VRQ1
#undef set_VRQ2
#undef set_VRQ3
#undef ld_ar_x2
#undef st_ar_x2
#define st_PERM(a,b,c)                                   \
    _TIE_dmx1a_common_tie_st_PERM(a,(perm16 *)(b),c)
#define perm16_storei(a,b,c)                             \
    _TIE_dmx1a_common_tie_perm16_storei(a,(perm16 *)(b),c)
#define ld_PERM(a,b)                                     \
    _TIE_dmx1a_common_tie_ld_PERM((const perm16 *)(a),b)
#define perm16_loadi(a,b)                                \
    _TIE_dmx1a_common_tie_perm16_loadi((const perm16 *)(a),b)
#define st_ULSR(a,b,c)                                   \
    _TIE_dmx1a_common_tie_st_ULSR(a,(ulsr128 *)(b),c)
#define ulsr128_storei(a,b,c)                            \
    _TIE_dmx1a_common_tie_ulsr128_storei(a,(ulsr128 *)(b),c)
#define ld_ULSR(a,b)                                     \
    _TIE_dmx1a_common_tie_ld_ULSR((const ulsr128 *)(a),b)
#define ulsr128_loadi(a,b)                               \
    _TIE_dmx1a_common_tie_ulsr128_loadi((const ulsr128 *)(a),b)
#define st_MIR(a,b,c)                                    \
    _TIE_dmx1a_common_tie_st_MIR(a,(mir30 *)(b),c)
#define mir30_storei(a,b,c)                              \
    _TIE_dmx1a_common_tie_mir30_storei(a,(mir30 *)(b),c)
#define ld_MIR(a,b)                                      \
    _TIE_dmx1a_common_tie_ld_MIR((const mir30 *)(a),b)
#define mir30_loadi(a,b)                                 \
    _TIE_dmx1a_common_tie_mir30_loadi((const mir30 *)(a),b)
#define st_CR(a,b,c)                                     \
    _TIE_dmx1a_common_tie_st_CR(a,(cr64 *)(b),c)
#define cr64_storei(a,b,c)                               \
    _TIE_dmx1a_common_tie_cr64_storei(a,(cr64 *)(b),c)
#define ld_CR(a,b)                                       \
    _TIE_dmx1a_common_tie_ld_CR((const cr64 *)(a),b)
#define cr64_loadi(a,b)                                  \
    _TIE_dmx1a_common_tie_cr64_loadi((const cr64 *)(a),b)
#define st_WR(a,b,c)                                     \
    _TIE_dmx1a_common_tie_st_WR(a,(wr64 *)(b),c)
#define wr64_storei(a,b,c)                               \
    _TIE_dmx1a_common_tie_wr64_storei(a,(wr64 *)(b),c)
#define ld_WR(a,b)                                       \
    _TIE_dmx1a_common_tie_ld_WR((const wr64 *)(a),b)
#define wr64_loadi(a,b)                                  \
    _TIE_dmx1a_common_tie_wr64_loadi((const wr64 *)(a),b)
#define RUR_JammingBit()                                 \
    _TIE_dmx1a_common_tie_RUR_JammingBit()
#define WUR_JammingBit(a)                                \
    _TIE_dmx1a_common_tie_WUR_JammingBit(a)
#define RUR_AccExtend_0()                                \
    _TIE_dmx1a_common_tie_RUR_AccExtend_0()
#define WUR_AccExtend_0(a)                               \
    _TIE_dmx1a_common_tie_WUR_AccExtend_0(a)
#define RUR_AccExtend_1()                                \
    _TIE_dmx1a_common_tie_RUR_AccExtend_1()
#define WUR_AccExtend_1(a)                               \
    _TIE_dmx1a_common_tie_WUR_AccExtend_1(a)
#define RUR_AccExtend_2()                                \
    _TIE_dmx1a_common_tie_RUR_AccExtend_2()
#define WUR_AccExtend_2(a)                               \
    _TIE_dmx1a_common_tie_WUR_AccExtend_2(a)
#define RUR_AccExtend_3()                                \
    _TIE_dmx1a_common_tie_RUR_AccExtend_3()
#define WUR_AccExtend_3(a)                               \
    _TIE_dmx1a_common_tie_WUR_AccExtend_3(a)
#define RUR_BB0_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB0_0()
#define WUR_BB0_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB0_0(a)
#define RUR_BB0_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB0_1()
#define WUR_BB0_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB0_1(a)
#define RUR_BB0_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB0_2()
#define WUR_BB0_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB0_2(a)
#define RUR_BB0_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB0_3()
#define WUR_BB0_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB0_3(a)
#define RUR_BB1_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB1_0()
#define WUR_BB1_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB1_0(a)
#define RUR_BB1_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB1_1()
#define WUR_BB1_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB1_1(a)
#define RUR_BB1_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB1_2()
#define WUR_BB1_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB1_2(a)
#define RUR_BB1_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB1_3()
#define WUR_BB1_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB1_3(a)
#define RUR_BB2_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB2_0()
#define WUR_BB2_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB2_0(a)
#define RUR_BB2_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB2_1()
#define WUR_BB2_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB2_1(a)
#define RUR_BB2_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB2_2()
#define WUR_BB2_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB2_2(a)
#define RUR_BB2_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB2_3()
#define WUR_BB2_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB2_3(a)
#define RUR_BB3_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB3_0()
#define WUR_BB3_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB3_0(a)
#define RUR_BB3_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB3_1()
#define WUR_BB3_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB3_1(a)
#define RUR_BB3_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB3_2()
#define WUR_BB3_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB3_2(a)
#define RUR_BB3_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB3_3()
#define WUR_BB3_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB3_3(a)
#define RUR_BB4_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB4_0()
#define WUR_BB4_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB4_0(a)
#define RUR_BB4_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB4_1()
#define WUR_BB4_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB4_1(a)
#define RUR_BB4_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB4_2()
#define WUR_BB4_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB4_2(a)
#define RUR_BB4_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB4_3()
#define WUR_BB4_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB4_3(a)
#define RUR_BB5_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB5_0()
#define WUR_BB5_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB5_0(a)
#define RUR_BB5_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB5_1()
#define WUR_BB5_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB5_1(a)
#define RUR_BB5_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB5_2()
#define WUR_BB5_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB5_2(a)
#define RUR_BB5_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB5_3()
#define WUR_BB5_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB5_3(a)
#define RUR_BB6_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB6_0()
#define WUR_BB6_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB6_0(a)
#define RUR_BB6_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB6_1()
#define WUR_BB6_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB6_1(a)
#define RUR_BB6_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB6_2()
#define WUR_BB6_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB6_2(a)
#define RUR_BB6_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB6_3()
#define WUR_BB6_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB6_3(a)
#define RUR_BB7_0()                                      \
    _TIE_dmx1a_common_tie_RUR_BB7_0()
#define WUR_BB7_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB7_0(a)
#define RUR_BB7_1()                                      \
    _TIE_dmx1a_common_tie_RUR_BB7_1()
#define WUR_BB7_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB7_1(a)
#define RUR_BB7_2()                                      \
    _TIE_dmx1a_common_tie_RUR_BB7_2()
#define WUR_BB7_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB7_2(a)
#define RUR_BB7_3()                                      \
    _TIE_dmx1a_common_tie_RUR_BB7_3()
#define WUR_BB7_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_BB7_3(a)
#define RUR_MvmAux()                                     \
    _TIE_dmx1a_common_tie_RUR_MvmAux()
#define WUR_MvmAux(a)                                    \
    _TIE_dmx1a_common_tie_WUR_MvmAux(a)
#define RUR_VB1_0()                                      \
    _TIE_dmx1a_common_tie_RUR_VB1_0()
#define WUR_VB1_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB1_0(a)
#define RUR_VB1_1()                                      \
    _TIE_dmx1a_common_tie_RUR_VB1_1()
#define WUR_VB1_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB1_1(a)
#define RUR_VB1_2()                                      \
    _TIE_dmx1a_common_tie_RUR_VB1_2()
#define WUR_VB1_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB1_2(a)
#define RUR_VB1_3()                                      \
    _TIE_dmx1a_common_tie_RUR_VB1_3()
#define WUR_VB1_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB1_3(a)
#define RUR_VB2_0()                                      \
    _TIE_dmx1a_common_tie_RUR_VB2_0()
#define WUR_VB2_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB2_0(a)
#define RUR_VB2_1()                                      \
    _TIE_dmx1a_common_tie_RUR_VB2_1()
#define WUR_VB2_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB2_1(a)
#define RUR_VB2_2()                                      \
    _TIE_dmx1a_common_tie_RUR_VB2_2()
#define WUR_VB2_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB2_2(a)
#define RUR_VB2_3()                                      \
    _TIE_dmx1a_common_tie_RUR_VB2_3()
#define WUR_VB2_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB2_3(a)
#define RUR_VB3_0()                                      \
    _TIE_dmx1a_common_tie_RUR_VB3_0()
#define WUR_VB3_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB3_0(a)
#define RUR_VB3_1()                                      \
    _TIE_dmx1a_common_tie_RUR_VB3_1()
#define WUR_VB3_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB3_1(a)
#define RUR_VB3_2()                                      \
    _TIE_dmx1a_common_tie_RUR_VB3_2()
#define WUR_VB3_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB3_2(a)
#define RUR_VB3_3()                                      \
    _TIE_dmx1a_common_tie_RUR_VB3_3()
#define WUR_VB3_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB3_3(a)
#define RUR_VB4_0()                                      \
    _TIE_dmx1a_common_tie_RUR_VB4_0()
#define WUR_VB4_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB4_0(a)
#define RUR_VB4_1()                                      \
    _TIE_dmx1a_common_tie_RUR_VB4_1()
#define WUR_VB4_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB4_1(a)
#define RUR_VB4_2()                                      \
    _TIE_dmx1a_common_tie_RUR_VB4_2()
#define WUR_VB4_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB4_2(a)
#define RUR_VB4_3()                                      \
    _TIE_dmx1a_common_tie_RUR_VB4_3()
#define WUR_VB4_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB4_3(a)
#define RUR_VB5_0()                                      \
    _TIE_dmx1a_common_tie_RUR_VB5_0()
#define WUR_VB5_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB5_0(a)
#define RUR_VB5_1()                                      \
    _TIE_dmx1a_common_tie_RUR_VB5_1()
#define WUR_VB5_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB5_1(a)
#define RUR_VB5_2()                                      \
    _TIE_dmx1a_common_tie_RUR_VB5_2()
#define WUR_VB5_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB5_2(a)
#define RUR_VB5_3()                                      \
    _TIE_dmx1a_common_tie_RUR_VB5_3()
#define WUR_VB5_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB5_3(a)
#define RUR_VB6_0()                                      \
    _TIE_dmx1a_common_tie_RUR_VB6_0()
#define WUR_VB6_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB6_0(a)
#define RUR_VB6_1()                                      \
    _TIE_dmx1a_common_tie_RUR_VB6_1()
#define WUR_VB6_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB6_1(a)
#define RUR_VB6_2()                                      \
    _TIE_dmx1a_common_tie_RUR_VB6_2()
#define WUR_VB6_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB6_2(a)
#define RUR_VB6_3()                                      \
    _TIE_dmx1a_common_tie_RUR_VB6_3()
#define WUR_VB6_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB6_3(a)
#define RUR_VB7_0()                                      \
    _TIE_dmx1a_common_tie_RUR_VB7_0()
#define WUR_VB7_0(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB7_0(a)
#define RUR_VB7_1()                                      \
    _TIE_dmx1a_common_tie_RUR_VB7_1()
#define WUR_VB7_1(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB7_1(a)
#define RUR_VB7_2()                                      \
    _TIE_dmx1a_common_tie_RUR_VB7_2()
#define WUR_VB7_2(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB7_2(a)
#define RUR_VB7_3()                                      \
    _TIE_dmx1a_common_tie_RUR_VB7_3()
#define WUR_VB7_3(a)                                     \
    _TIE_dmx1a_common_tie_WUR_VB7_3(a)
#define RUR_look_state()                                 \
    _TIE_dmx1a_common_tie_RUR_look_state()
#define WUR_look_state(a)                                \
    _TIE_dmx1a_common_tie_WUR_look_state(a)
#define load32x4_vr_idxR(a,b)                            \
    _TIE_dmx1a_common_tie_load32x4_vr_idxR((const unsigned *)(a),b)
#define load32x4_vr_idxI(a,b)                            \
    _TIE_dmx1a_common_tie_load32x4_vr_idxI((const unsigned *)(a),b)
#define load32x4_vr_postR(a,b,c)                         \
    _TIE_dmx1a_common_tie_load32x4_vr_postR(a,(const unsigned *)(b),c)
#define load32x4_vr_postI(a,b,c)                         \
    _TIE_dmx1a_common_tie_load32x4_vr_postI(a,(const unsigned *)(b),c)
#define load32x4_vr_circI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load32x4_vr_circI(a,(const unsigned *)(b),c,d)
#define load32x2_vr_idxR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load32x2_vr_idxR(a,(const unsigned *)(b),c,d)
#define load32x2_vr_idxI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load32x2_vr_idxI(a,(const unsigned *)(b),c,d)
#define load32x2_vr_postR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load32x2_vr_postR(a,(const unsigned *)(b),c,d)
#define load32x2_vr_postI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load32x2_vr_postI(a,(const unsigned *)(b),c,d)
#define load32x2_vr_circI(a,b,c,d,e)                     \
    _TIE_dmx1a_common_tie_load32x2_vr_circI(a,(const unsigned *)(b),c,d,e)
#define load32x1_vr_idxR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load32x1_vr_idxR(a,(const unsigned *)(b),c,d)
#define load32x1_vr_idxI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load32x1_vr_idxI(a,(const unsigned *)(b),c,d)
#define load32x1_vr_postR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load32x1_vr_postR(a,(const unsigned *)(b),c,d)
#define load32x1_vr_postI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load32x1_vr_postI(a,(const unsigned *)(b),c,d)
#define load32x1_vr_circI(a,b,c,d,e)                     \
    _TIE_dmx1a_common_tie_load32x1_vr_circI(a,(const unsigned *)(b),c,d,e)
#define load32x4_vr_idxR_perm_vr(a,b,c,d)                \
    _TIE_dmx1a_common_tie_load32x4_vr_idxR_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x4_vr_idxI_perm_vr(a,b,c,d)                \
    _TIE_dmx1a_common_tie_load32x4_vr_idxI_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x4_vr_postR_perm_vr(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_load32x4_vr_postR_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x4_vr_postI_perm_vr(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_load32x4_vr_postI_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x4_vr_circI_perm_vr(a,b,c,d,e,f)           \
    _TIE_dmx1a_common_tie_load32x4_vr_circI_perm_vr(a,b,(const unsigned *)(c),d,e,f)
#define load32x2_vr_idxR_perm_vr(a,b,c,d)                \
    _TIE_dmx1a_common_tie_load32x2_vr_idxR_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x2_vr_idxI_perm_vr(a,b,c,d)                \
    _TIE_dmx1a_common_tie_load32x2_vr_idxI_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x2_vr_postR_perm_vr(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_load32x2_vr_postR_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x2_vr_postI_perm_vr(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_load32x2_vr_postI_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x2_vr_circI_perm_vr(a,b,c,d,e,f)           \
    _TIE_dmx1a_common_tie_load32x2_vr_circI_perm_vr(a,b,(const unsigned *)(c),d,e,f)
#define load32x1_vr_idxR_perm_vr(a,b,c,d)                \
    _TIE_dmx1a_common_tie_load32x1_vr_idxR_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x1_vr_idxI_perm_vr(a,b,c,d)                \
    _TIE_dmx1a_common_tie_load32x1_vr_idxI_perm_vr(a,(const unsigned *)(b),c,d)
#define load32x1_vr_postR_perm_vr(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_load32x1_vr_postR_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x1_vr_postI_perm_vr(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_load32x1_vr_postI_perm_vr(a,b,(const unsigned *)(c),d,e)
#define load32x1_vr_circI_perm_vr(a,b,c,d,e,f)           \
    _TIE_dmx1a_common_tie_load32x1_vr_circI_perm_vr(a,b,(const unsigned *)(c),d,e,f)
#define set_perm16(a)                                    \
    _TIE_dmx1a_common_tie_set_perm16(a)
#define set_perm16_cond(a,b,c)                           \
    _TIE_dmx1a_common_tie_set_perm16_cond(a,b,c)
#define load16x4_vr_idxR(a,b)                            \
    _TIE_dmx1a_common_tie_load16x4_vr_idxR((const unsigned *)(a),b)
#define load16x4_vr_idxI(a,b)                            \
    _TIE_dmx1a_common_tie_load16x4_vr_idxI((const unsigned *)(a),b)
#define load16x4_vr_postR(a,b,c)                         \
    _TIE_dmx1a_common_tie_load16x4_vr_postR(a,(const unsigned *)(b),c)
#define load16x4_vr_postI(a,b,c)                         \
    _TIE_dmx1a_common_tie_load16x4_vr_postI(a,(const unsigned *)(b),c)
#define load16x4_vr_circI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load16x4_vr_circI(a,(const unsigned *)(b),c,d)
#define load16x2_vr_idxR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load16x2_vr_idxR(a,(const unsigned *)(b),c,d)
#define load16x2_vr_idxI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load16x2_vr_idxI(a,(const unsigned *)(b),c,d)
#define load16x2_vr_postR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load16x2_vr_postR(a,(const unsigned *)(b),c,d)
#define load16x2_vr_postI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load16x2_vr_postI(a,(const unsigned *)(b),c,d)
#define load16x2_vr_circI(a,b,c,d,e)                     \
    _TIE_dmx1a_common_tie_load16x2_vr_circI(a,(const unsigned *)(b),c,d,e)
#define load16x1_vr_idxR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load16x1_vr_idxR(a,(const unsigned *)(b),c,d)
#define load16x1_vr_idxI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load16x1_vr_idxI(a,(const unsigned *)(b),c,d)
#define load16x1_vr_postR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load16x1_vr_postR(a,(const unsigned *)(b),c,d)
#define load16x1_vr_postI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_load16x1_vr_postI(a,(const unsigned *)(b),c,d)
#define load16x1_vr_circI(a,b,c,d,e)                     \
    _TIE_dmx1a_common_tie_load16x1_vr_circI(a,(const unsigned *)(b),c,d,e)
#define load8x4_vr_idxR(a,b)                             \
    _TIE_dmx1a_common_tie_load8x4_vr_idxR((const unsigned *)(a),b)
#define load8x4_vr_idxI(a,b)                             \
    _TIE_dmx1a_common_tie_load8x4_vr_idxI((const unsigned *)(a),b)
#define load8x4_vr_postR(a,b,c)                          \
    _TIE_dmx1a_common_tie_load8x4_vr_postR(a,(const unsigned *)(b),c)
#define load8x4_vr_postI(a,b,c)                          \
    _TIE_dmx1a_common_tie_load8x4_vr_postI(a,(const unsigned *)(b),c)
#define load8x4_vr_circI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load8x4_vr_circI(a,(const unsigned *)(b),c,d)
#define load8x2_vr_idxR(a,b,c,d)                         \
    _TIE_dmx1a_common_tie_load8x2_vr_idxR(a,(const unsigned *)(b),c,d)
#define load8x2_vr_idxI(a,b,c,d)                         \
    _TIE_dmx1a_common_tie_load8x2_vr_idxI(a,(const unsigned *)(b),c,d)
#define load8x2_vr_postR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load8x2_vr_postR(a,(const unsigned *)(b),c,d)
#define load8x2_vr_postI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load8x2_vr_postI(a,(const unsigned *)(b),c,d)
#define load8x2_vr_circI(a,b,c,d,e)                      \
    _TIE_dmx1a_common_tie_load8x2_vr_circI(a,(const unsigned *)(b),c,d,e)
#define load8x1_vr_idxR(a,b,c,d)                         \
    _TIE_dmx1a_common_tie_load8x1_vr_idxR(a,(const unsigned *)(b),c,d)
#define load8x1_vr_idxI(a,b,c,d)                         \
    _TIE_dmx1a_common_tie_load8x1_vr_idxI(a,(const unsigned *)(b),c,d)
#define load8x1_vr_postR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load8x1_vr_postR(a,(const unsigned *)(b),c,d)
#define load8x1_vr_postI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_load8x1_vr_postI(a,(const unsigned *)(b),c,d)
#define load8x1_vr_circI(a,b,c,d,e)                      \
    _TIE_dmx1a_common_tie_load8x1_vr_circI(a,(const unsigned *)(b),c,d,e)
#define align_32x4_load(a)                               \
    _TIE_dmx1a_common_tie_align_32x4_load((const unsigned *)(a))
#define align_24x4_load(a)                               \
    _TIE_dmx1a_common_tie_align_24x4_load((const unsigned *)(a))
#define align_16x4_load(a)                               \
    _TIE_dmx1a_common_tie_align_16x4_load((const unsigned *)(a))
#define align_8x4_load(a)                                \
    _TIE_dmx1a_common_tie_align_8x4_load((const unsigned *)(a))
#define load_32x4_vr_a(a,b,c)                            \
    _TIE_dmx1a_common_tie_load_32x4_vr_a(a,b,(const unsigned *)(c))
#define load_24x4_vr_a(a,b,c)                            \
    _TIE_dmx1a_common_tie_load_24x4_vr_a(a,b,(const unsigned *)(c))
#define load_16x4_vr_a(a,b,c)                            \
    _TIE_dmx1a_common_tie_load_16x4_vr_a(a,b,(const unsigned *)(c))
#define load_8x4_vr_a(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_8x4_vr_a(a,b,(const unsigned *)(c))
#define load_32x4_vr_a_circ(a,b,c,d)                     \
    _TIE_dmx1a_common_tie_load_32x4_vr_a_circ(a,b,(const unsigned *)(c),d)
#define load32x2_wr_idxR(a,b)                            \
    _TIE_dmx1a_common_tie_load32x2_wr_idxR((const unsigned *)(a),b)
#define load32x2_wr_idxI(a,b)                            \
    _TIE_dmx1a_common_tie_load32x2_wr_idxI((const unsigned *)(a),b)
#define load32x2_wr_postR(a,b,c)                         \
    _TIE_dmx1a_common_tie_load32x2_wr_postR(a,(const unsigned *)(b),c)
#define load32x2_wr_postI(a,b,c)                         \
    _TIE_dmx1a_common_tie_load32x2_wr_postI(a,(const unsigned *)(b),c)
#define store32x4_vr_idxR(a,b,c)                         \
    _TIE_dmx1a_common_tie_store32x4_vr_idxR(a,(unsigned *)(b),c)
#define store32x4_vr_idxI(a,b,c)                         \
    _TIE_dmx1a_common_tie_store32x4_vr_idxI(a,(unsigned *)(b),c)
#define store32x4_vr_postR(a,b,c)                        \
    _TIE_dmx1a_common_tie_store32x4_vr_postR(a,(unsigned *)(b),c)
#define store32x4_vr_postI(a,b,c)                        \
    _TIE_dmx1a_common_tie_store32x4_vr_postI(a,(unsigned *)(b),c)
#define store32x4_vr_circI(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store32x4_vr_circI(a,(unsigned *)(b),c,d)
#define store32x2_vr_idxR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store32x2_vr_idxR(a,(unsigned *)(b),c,d)
#define store32x2_vr_idxI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store32x2_vr_idxI(a,(unsigned *)(b),c,d)
#define store32x2_vr_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store32x2_vr_postR(a,(unsigned *)(b),c,d)
#define store32x2_vr_postI(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store32x2_vr_postI(a,(unsigned *)(b),c,d)
#define store32x2_vr_circI(a,b,c,d,e)                    \
    _TIE_dmx1a_common_tie_store32x2_vr_circI(a,(unsigned *)(b),c,d,e)
#define store32x1_vr_idxR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store32x1_vr_idxR(a,(unsigned *)(b),c,d)
#define store32x1_vr_idxI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store32x1_vr_idxI(a,(unsigned *)(b),c,d)
#define store32x1_vr_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store32x1_vr_postR(a,(unsigned *)(b),c,d)
#define store32x1_vr_postI(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store32x1_vr_postI(a,(unsigned *)(b),c,d)
#define store32x1_vr_circI(a,b,c,d,e)                    \
    _TIE_dmx1a_common_tie_store32x1_vr_circI(a,(unsigned *)(b),c,d,e)
#define store32x4_vr_br_idxR(a,b,c,d)                    \
    _TIE_dmx1a_common_tie_store32x4_vr_br_idxR(a,b,(unsigned *)(c),d)
#define store32x4_vr_br_idxI(a,b,c,d)                    \
    _TIE_dmx1a_common_tie_store32x4_vr_br_idxI(a,b,(unsigned *)(c),d)
#define store32x4_vr_br_postR(a,b,c,d)                   \
    _TIE_dmx1a_common_tie_store32x4_vr_br_postR(a,b,(unsigned *)(c),d)
#define store32x4_vr_br_postI(a,b,c,d)                   \
    _TIE_dmx1a_common_tie_store32x4_vr_br_postI(a,b,(unsigned *)(c),d)
#define store32x4_vr_br_circI(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_store32x4_vr_br_circI(a,b,(unsigned *)(c),d,e)
#define store32x2_vr_br_idxR(a,b,c,d,e)                  \
    _TIE_dmx1a_common_tie_store32x2_vr_br_idxR(a,b,(unsigned *)(c),d,e)
#define store32x2_vr_br_idxI(a,b,c,d,e)                  \
    _TIE_dmx1a_common_tie_store32x2_vr_br_idxI(a,b,(unsigned *)(c),d,e)
#define store32x2_vr_br_postR(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_store32x2_vr_br_postR(a,b,(unsigned *)(c),d,e)
#define store32x2_vr_br_postI(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_store32x2_vr_br_postI(a,b,(unsigned *)(c),d,e)
#define store32x2_vr_br_circI(a,b,c,d,e,f)               \
    _TIE_dmx1a_common_tie_store32x2_vr_br_circI(a,b,(unsigned *)(c),d,e,f)
#define store32x1_vr_br_idxR(a,b,c,d,e)                  \
    _TIE_dmx1a_common_tie_store32x1_vr_br_idxR(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_idxI(a,b,c,d,e)                  \
    _TIE_dmx1a_common_tie_store32x1_vr_br_idxI(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_postR(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_store32x1_vr_br_postR(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_postI(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_store32x1_vr_br_postI(a,b,(unsigned *)(c),d,e)
#define store32x1_vr_br_circI(a,b,c,d,e,f)               \
    _TIE_dmx1a_common_tie_store32x1_vr_br_circI(a,b,(unsigned *)(c),d,e,f)
#define store32x4_vr_vr_idxR_perm(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_store32x4_vr_vr_idxR_perm(a,b,(unsigned *)(c),d,e)
#define store32x4_vr_vr_idxI_perm(a,b,c,d,e)             \
    _TIE_dmx1a_common_tie_store32x4_vr_vr_idxI_perm(a,b,(unsigned *)(c),d,e)
#define store32x4_vr_vr_postR_perm(a,b,c,d,e)            \
    _TIE_dmx1a_common_tie_store32x4_vr_vr_postR_perm(a,b,(unsigned *)(c),d,e)
#define store32x4_vr_vr_postI_perm(a,b,c,d,e)            \
    _TIE_dmx1a_common_tie_store32x4_vr_vr_postI_perm(a,b,(unsigned *)(c),d,e)
#define store32x4_vr_vr_circI_perm(a,b,c,d,e,f)          \
    _TIE_dmx1a_common_tie_store32x4_vr_vr_circI_perm(a,b,(unsigned *)(c),d,e,f)
#define store16x4_vr_idxR(a,b,c)                         \
    _TIE_dmx1a_common_tie_store16x4_vr_idxR(a,(unsigned *)(b),c)
#define store16x4_vr_idxI(a,b,c)                         \
    _TIE_dmx1a_common_tie_store16x4_vr_idxI(a,(unsigned *)(b),c)
#define store16x4_vr_postR(a,b,c)                        \
    _TIE_dmx1a_common_tie_store16x4_vr_postR(a,(unsigned *)(b),c)
#define store16x4_vr_postI(a,b,c)                        \
    _TIE_dmx1a_common_tie_store16x4_vr_postI(a,(unsigned *)(b),c)
#define store16x4_vr_circI(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store16x4_vr_circI(a,(unsigned *)(b),c,d)
#define store16x2_vr_idxR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store16x2_vr_idxR(a,(unsigned *)(b),c,d)
#define store16x2_vr_idxI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store16x2_vr_idxI(a,(unsigned *)(b),c,d)
#define store16x2_vr_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store16x2_vr_postR(a,(unsigned *)(b),c,d)
#define store16x2_vr_postI(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store16x2_vr_postI(a,(unsigned *)(b),c,d)
#define store16x2_vr_circI(a,b,c,d,e)                    \
    _TIE_dmx1a_common_tie_store16x2_vr_circI(a,(unsigned *)(b),c,d,e)
#define store16x1_vr_idxR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store16x1_vr_idxR(a,(unsigned *)(b),c,d)
#define store16x1_vr_idxI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store16x1_vr_idxI(a,(unsigned *)(b),c,d)
#define store16x1_vr_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store16x1_vr_postR(a,(unsigned *)(b),c,d)
#define store16x1_vr_postI(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store16x1_vr_postI(a,(unsigned *)(b),c,d)
#define store16x1_vr_circI(a,b,c,d,e)                    \
    _TIE_dmx1a_common_tie_store16x1_vr_circI(a,(unsigned *)(b),c,d,e)
#define store8x4_vr_idxR(a,b,c)                          \
    _TIE_dmx1a_common_tie_store8x4_vr_idxR(a,(unsigned *)(b),c)
#define store8x4_vr_idxI(a,b,c)                          \
    _TIE_dmx1a_common_tie_store8x4_vr_idxI(a,(unsigned *)(b),c)
#define store8x4_vr_postR(a,b,c)                         \
    _TIE_dmx1a_common_tie_store8x4_vr_postR(a,(unsigned *)(b),c)
#define store8x4_vr_postI(a,b,c)                         \
    _TIE_dmx1a_common_tie_store8x4_vr_postI(a,(unsigned *)(b),c)
#define store8x4_vr_circI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store8x4_vr_circI(a,(unsigned *)(b),c,d)
#define store8x2_vr_idxR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_store8x2_vr_idxR(a,(unsigned *)(b),c,d)
#define store8x2_vr_idxI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_store8x2_vr_idxI(a,(unsigned *)(b),c,d)
#define store8x2_vr_postR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store8x2_vr_postR(a,(unsigned *)(b),c,d)
#define store8x2_vr_postI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store8x2_vr_postI(a,(unsigned *)(b),c,d)
#define store8x2_vr_circI(a,b,c,d,e)                     \
    _TIE_dmx1a_common_tie_store8x2_vr_circI(a,(unsigned *)(b),c,d,e)
#define store8x1_vr_idxR(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_store8x1_vr_idxR(a,(unsigned *)(b),c,d)
#define store8x1_vr_idxI(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_store8x1_vr_idxI(a,(unsigned *)(b),c,d)
#define store8x1_vr_postR(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store8x1_vr_postR(a,(unsigned *)(b),c,d)
#define store8x1_vr_postI(a,b,c,d)                       \
    _TIE_dmx1a_common_tie_store8x1_vr_postI(a,(unsigned *)(b),c,d)
#define store8x1_vr_circI(a,b,c,d,e)                     \
    _TIE_dmx1a_common_tie_store8x1_vr_circI(a,(unsigned *)(b),c,d,e)
#define align_32x4_store(a)                              \
    _TIE_dmx1a_common_tie_align_32x4_store((const unsigned *)(a))
#define align_16x4_store(a)                              \
    _TIE_dmx1a_common_tie_align_16x4_store((const unsigned *)(a))
#define align_8x4_store(a)                               \
    _TIE_dmx1a_common_tie_align_8x4_store((const unsigned *)(a))
#define store_32x4_vr_a(a,b,c)                           \
    _TIE_dmx1a_common_tie_store_32x4_vr_a(a,b,(unsigned *)(c))
#define store_24x4_vr_a(a,b,c)                           \
    _TIE_dmx1a_common_tie_store_24x4_vr_a(a,b,(unsigned *)(c))
#define store_16x4_vr_a(a,b,c)                           \
    _TIE_dmx1a_common_tie_store_16x4_vr_a(a,b,(unsigned *)(c))
#define store_8x4_vr_a(a,b,c)                            \
    _TIE_dmx1a_common_tie_store_8x4_vr_a(a,b,(unsigned *)(c))
#define store_32x4_vr_a_circ(a,b,c,d)                    \
    _TIE_dmx1a_common_tie_store_32x4_vr_a_circ(a,b,(unsigned *)(c),d)
#define flush_32x4(a,b)                                  \
    _TIE_dmx1a_common_tie_flush_32x4(a,(unsigned *)(b))
#define flush_24x4(a,b)                                  \
    _TIE_dmx1a_common_tie_flush_24x4(a,(unsigned *)(b))
#define flush_16x4(a,b)                                  \
    _TIE_dmx1a_common_tie_flush_16x4(a,(unsigned *)(b))
#define flush_8x4(a,b)                                   \
    _TIE_dmx1a_common_tie_flush_8x4(a,(unsigned *)(b))
#define br_get_idx_2_5(a,b,c)                            \
    _TIE_dmx1a_common_tie_br_get_idx_2_5(a,b,c)
#define br_get_idx_6_13(a,b,c,d)                         \
    _TIE_dmx1a_common_tie_br_get_idx_6_13(a,b,c,d)
#define br_get_idx_next_odd(a,b)                         \
    _TIE_dmx1a_common_tie_br_get_idx_next_odd(a,b)
#define br_upd_idx_spec(a)                               \
    _TIE_dmx1a_common_tie_br_upd_idx_spec(a)
#define build_palindrome(a,b,c,d)                        \
    _TIE_dmx1a_common_tie_build_palindrome(a,b,c,d)
#define load_vr_bdir(a,b,c,d)                            \
    _TIE_dmx1a_common_tie_load_vr_bdir((const unsigned *)(a),b,c,d)
#define load_vr_brev(a,b,c,d)                            \
    _TIE_dmx1a_common_tie_load_vr_brev((const unsigned *)(a),b,c,d)
#define store_vrl_wr_bdir(a,b,c,d,e,f)                   \
    _TIE_dmx1a_common_tie_store_vrl_wr_bdir(a,b,(unsigned *)(c),d,e,f)
#define store_vrh_wr_bdir(a,b,c,d,e,f)                   \
    _TIE_dmx1a_common_tie_store_vrh_wr_bdir(a,b,(unsigned *)(c),d,e,f)
#define store_vrl_wr_brev(a,b,c,d,e,f)                   \
    _TIE_dmx1a_common_tie_store_vrl_wr_brev(a,b,(unsigned *)(c),d,e,f)
#define store_vrh_wr_brev(a,b,c,d,e,f)                   \
    _TIE_dmx1a_common_tie_store_vrh_wr_brev(a,b,(unsigned *)(c),d,e,f)
#define store_vrl_vrl_postR(a,b,c,d)                     \
    _TIE_dmx1a_common_tie_store_vrl_vrl_postR(a,b,(unsigned *)(c),d)
#define store_vrh_vrh_postR(a,b,c,d)                     \
    _TIE_dmx1a_common_tie_store_vrh_vrh_postR(a,b,(unsigned *)(c),d)
#define store_vrl_wr_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store_vrl_wr_postR(a,b,(unsigned *)(c),d)
#define store_wr_vrl_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store_wr_vrl_postR(a,b,(unsigned *)(c),d)
#define store_vrh_wr_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store_vrh_wr_postR(a,b,(unsigned *)(c),d)
#define store_wr_vrh_postR(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_store_wr_vrh_postR(a,b,(unsigned *)(c),d)
#define load_fr_postI(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_fr_postI(a,(const unsigned *)(b),c)
#define store_fr_postI(a,b,c)                            \
    _TIE_dmx1a_common_tie_store_fr_postI(a,(unsigned *)(b),c)
#define move32_wr_vr(a,b)                                \
    _TIE_dmx1a_common_tie_move32_wr_vr(a,b)
#define move32_wr_fr(a)                                  \
    _TIE_dmx1a_common_tie_move32_wr_fr(a)
#define move64_wr_vr(a,b)                                \
    _TIE_dmx1a_common_tie_move64_wr_vr(a,b)
#define move64_vr_wr(a,b,c)                              \
    _TIE_dmx1a_common_tie_move64_vr_wr(a,b,c)
#define move32_ar_vr(a,b)                                \
    _TIE_dmx1a_common_tie_move32_ar_vr(a,b)
#define move32_ar_vr_idx(a,b)                            \
    _TIE_dmx1a_common_tie_move32_ar_vr_idx(a,b)
#define move32_fr_vr_idx(a,b)                            \
    _TIE_dmx1a_common_tie_move32_fr_vr_idx(a,b)
#define int_to_xt_bool(a)                                \
    _TIE_dmx1a_common_tie_int_to_xt_bool(a)
#define int_to_xt_bool2(a)                               \
    _TIE_dmx1a_common_tie_int_to_xt_bool2(a)
#define int_to_xt_bool4(a)                               \
    _TIE_dmx1a_common_tie_int_to_xt_bool4(a)
#define move_vr_eqz(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_move_vr_eqz(a,b,c,d,e,f)
#define move_vr_gez(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_move_vr_gez(a,b,c,d,e,f)
#define move_vr_gtz(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_move_vr_gtz(a,b,c,d,e,f)
#define move_vr_lez(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_move_vr_lez(a,b,c,d,e,f)
#define move_vr_ltz(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_move_vr_ltz(a,b,c,d,e,f)
#define move_vr_nez(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_move_vr_nez(a,b,c,d,e,f)
#define move_vr_sat(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_move_vr_sat(a,b,c,d,e,f)
#define vmove_vr_eqz(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmove_vr_eqz(a,b,c)
#define vmove_vr_gez(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmove_vr_gez(a,b,c)
#define vmove_vr_gtz(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmove_vr_gtz(a,b,c)
#define vmove_vr_lez(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmove_vr_lez(a,b,c)
#define vmove_vr_ltz(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmove_vr_ltz(a,b,c)
#define vmove_vr_nez(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmove_vr_nez(a,b,c)
#define vmove_vr_sat(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmove_vr_sat(a,b,c)
#define replicate(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_replicate(a,b,c,d)
#define replicate_ar(a,b,c)                              \
    _TIE_dmx1a_common_tie_replicate_ar(a,b,c)
#define creplicate_H(a)                                  \
    _TIE_dmx1a_common_tie_creplicate_H(a)
#define creplicate_L(a)                                  \
    _TIE_dmx1a_common_tie_creplicate_L(a)
#define vreplicate(a,b)                                  \
    _TIE_dmx1a_common_tie_vreplicate(a,b)
#define vreplicate_fr(a)                                 \
    _TIE_dmx1a_common_tie_vreplicate_fr(a)
#define vreplicate_hr(a)                                 \
    _TIE_dmx1a_common_tie_vreplicate_hr(a)
#define hreplicate_fr(a)                                 \
    _TIE_dmx1a_common_tie_hreplicate_fr(a)
#define convert_16I_to_32F_x1(a,b,c)                     \
    _TIE_dmx1a_common_tie_convert_16I_to_32F_x1(a,b,c)
#define convert_16I_to_32F_x2(a,b,c)                     \
    _TIE_dmx1a_common_tie_convert_16I_to_32F_x2(a,b,c)
#define convert_16I_to_32F_x4(a,b)                       \
    _TIE_dmx1a_common_tie_convert_16I_to_32F_x4(a,b)
#define convert_32F_to_16I_x1(a,b,c,d)                   \
    _TIE_dmx1a_common_tie_convert_32F_to_16I_x1(a,b,c,d)
#define convert_32F_to_16I_x2(a,b,c,d)                   \
    _TIE_dmx1a_common_tie_convert_32F_to_16I_x2(a,b,c,d)
#define convert_32F_to_16I_x4(a,b,c)                     \
    _TIE_dmx1a_common_tie_convert_32F_to_16I_x4(a,b,c)
#define convert_32F_to_16F_x1(a,b,c,d,e,f)               \
    _TIE_dmx1a_common_tie_convert_32F_to_16F_x1(a,b,c,d,e,f)
#define convert_32F_to_16F_x2(a,b,c,d,e,f)               \
    _TIE_dmx1a_common_tie_convert_32F_to_16F_x2(a,b,c,d,e,f)
#define convert_32F_to_16F_x4(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_convert_32F_to_16F_x4(a,b,c,d,e)
#define convert_16F_to_32F_x1(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_convert_16F_to_32F_x1(a,b,c,d,e)
#define convert_16F_to_32F_x2(a,b,c,d,e)                 \
    _TIE_dmx1a_common_tie_convert_16F_to_32F_x2(a,b,c,d,e)
#define convert_16F_to_32F_x4(a,b,c,d)                   \
    _TIE_dmx1a_common_tie_convert_16F_to_32F_x4(a,b,c,d)
#define convert_32I_to_32F_x1(a,b,c)                     \
    _TIE_dmx1a_common_tie_convert_32I_to_32F_x1(a,b,c)
#define convert_32F_to_32I_x1(a,b,c,d)                   \
    _TIE_dmx1a_common_tie_convert_32F_to_32I_x1(a,b,c,d)
#define convert_IEEE_float_to_32F_x4(a)                  \
    _TIE_dmx1a_common_tie_convert_IEEE_float_to_32F_x4(a)
#define convert_32F_to_IEEE_float_x4(a)                  \
    _TIE_dmx1a_common_tie_convert_32F_to_IEEE_float_x4(a)
#define convert_IEEE_float_to_32F(a)                     \
    _TIE_dmx1a_common_tie_convert_IEEE_float_to_32F(a)
#define convert_32F_to_IEEE_float(a)                     \
    _TIE_dmx1a_common_tie_convert_32F_to_IEEE_float(a)
#define convert_32I_to_64F(a)                            \
    _TIE_dmx1a_common_tie_convert_32I_to_64F(a)
#define convert_64F_to_32I(a,b)                          \
    _TIE_dmx1a_common_tie_convert_64F_to_32I(a,b)
#define convert_32F_to_64F(a)                            \
    _TIE_dmx1a_common_tie_convert_32F_to_64F(a)
#define convert_64F_to_32F(a)                            \
    _TIE_dmx1a_common_tie_convert_64F_to_32F(a)
#define convert_IEEE_double_to_64F(a)                    \
    _TIE_dmx1a_common_tie_convert_IEEE_double_to_64F(a)
#define convert_64F_to_IEEE_double(a)                    \
    _TIE_dmx1a_common_tie_convert_64F_to_IEEE_double(a)
#define affine_adj_L(a,b,c,d,e)                          \
    _TIE_dmx1a_common_tie_affine_adj_L(a,b,c,d,e)
#define affine_adj_H(a,b,c,d,e)                          \
    _TIE_dmx1a_common_tie_affine_adj_H(a,b,c,d,e)
#define affine_perm_L(a,b,c,d,e)                         \
    _TIE_dmx1a_common_tie_affine_perm_L(a,b,c,d,e)
#define affine_perm_H(a,b,c,d,e)                         \
    _TIE_dmx1a_common_tie_affine_perm_H(a,b,c,d,e)
#define linear_adj_L(a,b,c,d,e)                          \
    _TIE_dmx1a_common_tie_linear_adj_L(a,b,c,d,e)
#define linear_adj_H(a,b,c,d,e)                          \
    _TIE_dmx1a_common_tie_linear_adj_H(a,b,c,d,e)
#define linear_perm_L(a,b,c,d,e)                         \
    _TIE_dmx1a_common_tie_linear_perm_L(a,b,c,d,e)
#define linear_perm_H(a,b,c,d,e)                         \
    _TIE_dmx1a_common_tie_linear_perm_H(a,b,c,d,e)
#define bfly_z_yl_xl_wr(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_yl_xl_wr(a,b,c,d,e)
#define bfly_z_yl_xh_wr(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_yl_xh_wr(a,b,c,d,e)
#define bfly_z_yh_xl_wr(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_yh_xl_wr(a,b,c,d,e)
#define bfly_z_yh_xh_wr(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_yh_xh_wr(a,b,c,d,e)
#define bfly_z_wr_xl_yl(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_wr_xl_yl(a,b,c,d,e)
#define bfly_z_wr_xh_yl(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_wr_xh_yl(a,b,c,d,e)
#define bfly_z_wr_xl_yh(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_wr_xl_yh(a,b,c,d,e)
#define bfly_z_wr_xh_yh(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_bfly_z_wr_xh_yh(a,b,c,d,e)
#define bfly_zl_zl_xl_yl(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_zl_zl_xl_yl(a,b,c,d,e,f)
#define bfly_zl_zl_xh_yl(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_zl_zl_xh_yl(a,b,c,d,e,f)
#define bfly_zh_zh_xl_yh(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_zh_zh_xl_yh(a,b,c,d,e,f)
#define bfly_zh_zh_xh_yh(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_zh_zh_xh_yh(a,b,c,d,e,f)
#define bfly_wr_zl_xl_yl(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_wr_zl_xl_yl(a,b,c,d,e,f)
#define bfly_wr_zl_xh_yl(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_wr_zl_xh_yl(a,b,c,d,e,f)
#define bfly_wr_zh_xl_yh(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_wr_zh_xl_yh(a,b,c,d,e,f)
#define bfly_wr_zh_xh_yh(a,b,c,d,e,f)                    \
    _TIE_dmx1a_common_tie_bfly_wr_zh_xh_yh(a,b,c,d,e,f)
#define cmul(a,b)                                        \
    _TIE_dmx1a_common_tie_cmul(a,b)
#define cmul_conj(a,b)                                   \
    _TIE_dmx1a_common_tie_cmul_conj(a,b)
#define cmac(a,b,c)                                      \
    _TIE_dmx1a_common_tie_cmac(a,b,c)
#define cmac_conj(a,b,c)                                 \
    _TIE_dmx1a_common_tie_cmac_conj(a,b,c)
#define cmas(a,b,c)                                      \
    _TIE_dmx1a_common_tie_cmas(a,b,c)
#define cmas_conj(a,b,c)                                 \
    _TIE_dmx1a_common_tie_cmas_conj(a,b,c)
#define cmul_L(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_cmul_L(a,b,c,d)
#define cmul_H(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_cmul_H(a,b,c,d)
#define cmac_L(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_cmac_L(a,b,c,d)
#define cmac_H(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_cmac_H(a,b,c,d)
#define cmas_L(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_cmas_L(a,b,c,d)
#define cmas_H(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_cmas_H(a,b,c,d)
#define cmac_Lx2(a,b,c,d)                                \
    _TIE_dmx1a_common_tie_cmac_Lx2(a,b,c,d)
#define cmac_Hx2(a,b,c,d)                                \
    _TIE_dmx1a_common_tie_cmac_Hx2(a,b,c,d)
#define cmul_x2(a,b,c)                                   \
    _TIE_dmx1a_common_tie_cmul_x2(a,b,c)
#define cmac_adj_x2(a,b,c,d,e)                           \
    _TIE_dmx1a_common_tie_cmac_adj_x2(a,b,c,d,e)
#define cmas_adj_x2(a,b,c,d,e)                           \
    _TIE_dmx1a_common_tie_cmas_adj_x2(a,b,c,d,e)
#define xcorr(a,b,c)                                     \
    _TIE_dmx1a_common_tie_xcorr(a,b,c)
#define xconv(a,b,c)                                     \
    _TIE_dmx1a_common_tie_xconv(a,b,c)
#define qmul_1(a,b,c)                                    \
    _TIE_dmx1a_common_tie_qmul_1(a,b,c)
#define qmul_2(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_qmul_2(a,b,c,d)
#define matmul_2x2(a,b,c)                                \
    _TIE_dmx1a_common_tie_matmul_2x2(a,b,c)
#define vadds(a,b,c)                                     \
    _TIE_dmx1a_common_tie_vadds(a,b,c)
#define vmidp(a,b,c)                                     \
    _TIE_dmx1a_common_tie_vmidp(a,b,c)
#define vmuls(a,b,c)                                     \
    _TIE_dmx1a_common_tie_vmuls(a,b,c)
#define vmacs_adj(a,b,c,d,e)                             \
    _TIE_dmx1a_common_tie_vmacs_adj(a,b,c,d,e)
#define vmuls_perm(a,b,c,d)                              \
    _TIE_dmx1a_common_tie_vmuls_perm(a,b,c,d)
#define vmacs_perm(a,b,c,d,e)                            \
    _TIE_dmx1a_common_tie_vmacs_perm(a,b,c,d,e)
#define vssub_L(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_vssub_L(a,b,c,d)
#define vssub_H(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_vssub_H(a,b,c,d)
#define vssub_x2(a,b,c)                                  \
    _TIE_dmx1a_common_tie_vssub_x2(a,b,c)
#define vinterp_L(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_vinterp_L(a,b,c,d)
#define vinterp_H(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_vinterp_H(a,b,c,d)
#define vinterp_x2(a,b,c)                                \
    _TIE_dmx1a_common_tie_vinterp_x2(a,b,c)
#define csums_L(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_csums_L(a,b,c,d)
#define csums_H(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_csums_H(a,b,c,d)
#define dsums_L(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_dsums_L(a,b,c,d)
#define dsums_H(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_dsums_H(a,b,c,d)
#define vadd_hr(a,b)                                     \
    _TIE_dmx1a_common_tie_vadd_hr(a,b)
#define vsub_hr(a,b)                                     \
    _TIE_dmx1a_common_tie_vsub_hr(a,b)
#define vmul_hr(a,b)                                     \
    _TIE_dmx1a_common_tie_vmul_hr(a,b)
#define vmac_hr(a,b,c)                                   \
    _TIE_dmx1a_common_tie_vmac_hr(a,b,c)
#define fpadd(a,b,c)                                     \
    _TIE_dmx1a_common_tie_fpadd(a,b,c)
#define fpmul(a,b,c)                                     \
    _TIE_dmx1a_common_tie_fpmul(a,b,c)
#define fpmac(a,b,c,d)                                   \
    _TIE_dmx1a_common_tie_fpmac(a,b,c,d)
#define fpmul_sum3(a,b,c,d)                              \
    _TIE_dmx1a_common_tie_fpmul_sum3(a,b,c,d)
#define vscale(a,b)                                      \
    _TIE_dmx1a_common_tie_vscale(a,b)
#define vscale_adds(a,b,c,d)                             \
    _TIE_dmx1a_common_tie_vscale_adds(a,b,c,d)
#define fadds(a,b,c,d,e,f,g)                             \
    _TIE_dmx1a_common_tie_fadds(a,b,c,d,e,f,g)
#define fmacs(a,b,c,d,e,f,g)                             \
    _TIE_dmx1a_common_tie_fmacs(a,b,c,d,e,f,g)
#define fmuls(a,b,c,d,e,f,g)                             \
    _TIE_dmx1a_common_tie_fmuls(a,b,c,d,e,f,g)
#define fmul_sum3(a,b,c,d,e,f)                           \
    _TIE_dmx1a_common_tie_fmul_sum3(a,b,c,d,e,f)
#define dadds(a,b,c)                                     \
    _TIE_dmx1a_common_tie_dadds(a,b,c)
#define dmuls(a,b,c)                                     \
    _TIE_dmx1a_common_tie_dmuls(a,b,c)
#define dmacs(a,b,c,d)                                   \
    _TIE_dmx1a_common_tie_dmacs(a,b,c,d)
#define vabs(a)                                          \
    _TIE_dmx1a_common_tie_vabs(a)
#define vexp_adj(a,b)                                    \
    _TIE_dmx1a_common_tie_vexp_adj(a,b)
#define vexp_adji(a,b)                                   \
    _TIE_dmx1a_common_tie_vexp_adji(a,b)
#define vperm(a,b,c)                                     \
    _TIE_dmx1a_common_tie_vperm(a,b,c)
#define vperms(a,b,c)                                    \
    _TIE_dmx1a_common_tie_vperms(a,b,c)
#define vpermsi(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_vpermsi(a,b,c,d)
#define seta_vr(a,b,c,d,e)                               \
    _TIE_dmx1a_common_tie_seta_vr(a,b,c,d,e)
#define vseta_vr(a,b,c)                                  \
    _TIE_dmx1a_common_tie_vseta_vr(a,b,c)
#define seta_ar(a,b,c)                                   \
    _TIE_dmx1a_common_tie_seta_ar(a,b,c)
#define seta_fr(a,b,c)                                   \
    _TIE_dmx1a_common_tie_seta_fr(a,b,c)
#define f_abs(a,b,c,d)                                   \
    _TIE_dmx1a_common_tie_f_abs(a,b,c,d)
#define fclamp(a,b,c,d,e,f)                              \
    _TIE_dmx1a_common_tie_fclamp(a,b,c,d,e,f)
#define fclamp_bp(a,b,c,d,e,f)                           \
    _TIE_dmx1a_common_tie_fclamp_bp(a,b,c,d,e,f)
#define fclamp_one(a,b,c,d)                              \
    _TIE_dmx1a_common_tie_fclamp_one(a,b,c,d)
#define fmax(a,b,c,d,e,f)                                \
    _TIE_dmx1a_common_tie_fmax(a,b,c,d,e,f)
#define fmin(a,b,c,d,e,f)                                \
    _TIE_dmx1a_common_tie_fmin(a,b,c,d,e,f)
#define max_fr(a,b)                                      \
    _TIE_dmx1a_common_tie_max_fr(a,b)
#define min_fr(a,b)                                      \
    _TIE_dmx1a_common_tie_min_fr(a,b)
#define log2(a,b,c,d)                                    \
    _TIE_dmx1a_common_tie_log2(a,b,c,d)
#define pow2(a,b,c,d)                                    \
    _TIE_dmx1a_common_tie_pow2(a,b,c,d)
#define sigmoid(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_sigmoid(a,b,c,d)
#define inv(a,b,c,d)                                     \
    _TIE_dmx1a_common_tie_inv(a,b,c,d)
#define ratio(a,b,c,d,e,f,g)                             \
    _TIE_dmx1a_common_tie_ratio(a,b,c,d,e,f,g)
#define atanratio(a,b,c,d,e)                             \
    _TIE_dmx1a_common_tie_atanratio(a,b,c,d,e)
#define invsqrt(a,b,c,d)                                 \
    _TIE_dmx1a_common_tie_invsqrt(a,b,c,d)
#define sine(a,b,c,d)                                    \
    _TIE_dmx1a_common_tie_sine(a,b,c,d)
#define cosine(a,b,c,d)                                  \
    _TIE_dmx1a_common_tie_cosine(a,b,c,d)
#define log2mul(a,b,c,d,e,f,g)                           \
    _TIE_dmx1a_common_tie_log2mul(a,b,c,d,e,f,g)
#define cspow2(a,b,c,d,e)                                \
    _TIE_dmx1a_common_tie_cspow2(a,b,c,d,e)
#define log2_fr(a)                                       \
    _TIE_dmx1a_common_tie_log2_fr(a)
#define pow2_fr(a)                                       \
    _TIE_dmx1a_common_tie_pow2_fr(a)
#define sigmoid_fr(a)                                    \
    _TIE_dmx1a_common_tie_sigmoid_fr(a)
#define inv_fr(a)                                        \
    _TIE_dmx1a_common_tie_inv_fr(a)
#define invsqrt_fr(a)                                    \
    _TIE_dmx1a_common_tie_invsqrt_fr(a)
#define sine_fr(a)                                       \
    _TIE_dmx1a_common_tie_sine_fr(a)
#define cosine_fr(a)                                     \
    _TIE_dmx1a_common_tie_cosine_fr(a)
#define comp(a,b,c,d)                                    \
    _TIE_dmx1a_common_tie_comp(a,b,c,d)
#define eq(a,b,c,d)                                      \
    _TIE_dmx1a_common_tie_eq(a,b,c,d)
#define ge(a,b,c,d)                                      \
    _TIE_dmx1a_common_tie_ge(a,b,c,d)
#define gt(a,b,c,d)                                      \
    _TIE_dmx1a_common_tie_gt(a,b,c,d)
#define le(a,b,c,d)                                      \
    _TIE_dmx1a_common_tie_le(a,b,c,d)
#define lt(a,b,c,d)                                      \
    _TIE_dmx1a_common_tie_lt(a,b,c,d)
#define ne(a,b,c,d)                                      \
    _TIE_dmx1a_common_tie_ne(a,b,c,d)
#define comp_const(a,b,c,d,e)                            \
    _TIE_dmx1a_common_tie_comp_const(a,b,c,d,e)
#define eq_const(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_eq_const(a,b,c,d,e)
#define ge_const(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_ge_const(a,b,c,d,e)
#define gt_const(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_gt_const(a,b,c,d,e)
#define le_const(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_le_const(a,b,c,d,e)
#define lt_const(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_lt_const(a,b,c,d,e)
#define ne_const(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_ne_const(a,b,c,d,e)
#define eq_fr(a,b)                                       \
    _TIE_dmx1a_common_tie_eq_fr(a,b)
#define ge_fr(a,b)                                       \
    _TIE_dmx1a_common_tie_ge_fr(a,b)
#define gt_fr(a,b)                                       \
    _TIE_dmx1a_common_tie_gt_fr(a,b)
#define le_fr(a,b)                                       \
    _TIE_dmx1a_common_tie_le_fr(a,b)
#define lt_fr(a,b)                                       \
    _TIE_dmx1a_common_tie_lt_fr(a,b)
#define ne_fr(a,b)                                       \
    _TIE_dmx1a_common_tie_ne_fr(a,b)
#define neg_fr(a)                                        \
    _TIE_dmx1a_common_tie_neg_fr(a)
#define abs_fr(a)                                        \
    _TIE_dmx1a_common_tie_abs_fr(a)
#define deqz(a)                                          \
    _TIE_dmx1a_common_tie_deqz(a)
#define dgez(a)                                          \
    _TIE_dmx1a_common_tie_dgez(a)
#define dgtz(a)                                          \
    _TIE_dmx1a_common_tie_dgtz(a)
#define dlez(a)                                          \
    _TIE_dmx1a_common_tie_dlez(a)
#define dltz(a)                                          \
    _TIE_dmx1a_common_tie_dltz(a)
#define dnez(a)                                          \
    _TIE_dmx1a_common_tie_dnez(a)
#define veq(a,b)                                         \
    _TIE_dmx1a_common_tie_veq(a,b)
#define vge(a,b)                                         \
    _TIE_dmx1a_common_tie_vge(a,b)
#define vgt(a,b)                                         \
    _TIE_dmx1a_common_tie_vgt(a,b)
#define vle(a,b)                                         \
    _TIE_dmx1a_common_tie_vle(a,b)
#define vlt(a,b)                                         \
    _TIE_dmx1a_common_tie_vlt(a,b)
#define vne(a,b)                                         \
    _TIE_dmx1a_common_tie_vne(a,b)
#define veq_const(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_veq_const(a,b,c,d)
#define vge_const(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_vge_const(a,b,c,d)
#define vgt_const(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_vgt_const(a,b,c,d)
#define vle_const(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_vle_const(a,b,c,d)
#define vlt_const(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_vlt_const(a,b,c,d)
#define vne_const(a,b,c,d)                               \
    _TIE_dmx1a_common_tie_vne_const(a,b,c,d)
#define sel(a,b,c,d,e,f,g)                               \
    _TIE_dmx1a_common_tie_sel(a,b,c,d,e,f,g)
#define sel_1b4(a,b,c,d,e,f,g,h)                         \
    _TIE_dmx1a_common_tie_sel_1b4(a,b,c,d,e,f,g,h)
#define sel_eq(a,b,c,d,e,f,g)                            \
    _TIE_dmx1a_common_tie_sel_eq(a,b,c,d,e,f,g)
#define sel_ge(a,b,c,d,e,f,g)                            \
    _TIE_dmx1a_common_tie_sel_ge(a,b,c,d,e,f,g)
#define sel_gt(a,b,c,d,e,f,g)                            \
    _TIE_dmx1a_common_tie_sel_gt(a,b,c,d,e,f,g)
#define sel_le(a,b,c,d,e,f,g)                            \
    _TIE_dmx1a_common_tie_sel_le(a,b,c,d,e,f,g)
#define sel_lt(a,b,c,d,e,f,g)                            \
    _TIE_dmx1a_common_tie_sel_lt(a,b,c,d,e,f,g)
#define sel_ne(a,b,c,d,e,f,g)                            \
    _TIE_dmx1a_common_tie_sel_ne(a,b,c,d,e,f,g)
#define vsel(a,b,c)                                      \
    _TIE_dmx1a_common_tie_vsel(a,b,c)
#define andb1(a,b)                                       \
    _TIE_dmx1a_common_tie_andb1(a,b)
#define andbc1(a,b)                                      \
    _TIE_dmx1a_common_tie_andbc1(a,b)
#define orb1(a,b)                                        \
    _TIE_dmx1a_common_tie_orb1(a,b)
#define orbc1(a,b)                                       \
    _TIE_dmx1a_common_tie_orbc1(a,b)
#define xorb1(a,b)                                       \
    _TIE_dmx1a_common_tie_xorb1(a,b)
#define andb4(a,b)                                       \
    _TIE_dmx1a_common_tie_andb4(a,b)
#define andbc4(a,b)                                      \
    _TIE_dmx1a_common_tie_andbc4(a,b)
#define orb4(a,b)                                        \
    _TIE_dmx1a_common_tie_orb4(a,b)
#define orbc4(a,b)                                       \
    _TIE_dmx1a_common_tie_orbc4(a,b)
#define xorb4(a,b)                                       \
    _TIE_dmx1a_common_tie_xorb4(a,b)
#define bcount0_maskI(a,b)                               \
    _TIE_dmx1a_common_tie_bcount0_maskI(a,b)
#define bcount0_maskR(a,b)                               \
    _TIE_dmx1a_common_tie_bcount0_maskR(a,b)
#define bcount1_maskI(a,b)                               \
    _TIE_dmx1a_common_tie_bcount1_maskI(a,b)
#define bcount1_maskR(a,b)                               \
    _TIE_dmx1a_common_tie_bcount1_maskR(a,b)
#define bfirst0_maskI(a,b)                               \
    _TIE_dmx1a_common_tie_bfirst0_maskI(a,b)
#define bfirst0_maskR(a,b)                               \
    _TIE_dmx1a_common_tie_bfirst0_maskR(a,b)
#define bfirst1_maskI(a,b)                               \
    _TIE_dmx1a_common_tie_bfirst1_maskI(a,b)
#define bfirst1_maskR(a,b)                               \
    _TIE_dmx1a_common_tie_bfirst1_maskR(a,b)
#define blast0_maskI(a,b)                                \
    _TIE_dmx1a_common_tie_blast0_maskI(a,b)
#define blast0_maskR(a,b)                                \
    _TIE_dmx1a_common_tie_blast0_maskR(a,b)
#define blast1_maskI(a,b)                                \
    _TIE_dmx1a_common_tie_blast1_maskI(a,b)
#define blast1_maskR(a,b)                                \
    _TIE_dmx1a_common_tie_blast1_maskR(a,b)
#define bgetI(a,b)                                       \
    _TIE_dmx1a_common_tie_bgetI(a,b)
#define bgetR(a,b)                                       \
    _TIE_dmx1a_common_tie_bgetR(a,b)
#define bsetI(a,b,c)                                     \
    _TIE_dmx1a_common_tie_bsetI(a,b,c)
#define bsetR(a,b,c)                                     \
    _TIE_dmx1a_common_tie_bsetR(a,b,c)
#define exp_adj(a,b,c,d,e)                               \
    _TIE_dmx1a_common_tie_exp_adj(a,b,c,d,e)
#define exp_adji(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_exp_adji(a,b,c,d,e)
#define exp_adj_fr(a,b)                                  \
    _TIE_dmx1a_common_tie_exp_adj_fr(a,b)
#define exp_adji_fr(a,b)                                 \
    _TIE_dmx1a_common_tie_exp_adji_fr(a,b)
#define s_neg(a,b,c,d)                                   \
    _TIE_dmx1a_common_tie_s_neg(a,b,c,d)
#define s_copy(a,b,c,d,e,f)                              \
    _TIE_dmx1a_common_tie_s_copy(a,b,c,d,e,f)
#define s_and(a,b,c,d,e,f)                               \
    _TIE_dmx1a_common_tie_s_and(a,b,c,d,e,f)
#define s_andc(a,b,c,d,e,f)                              \
    _TIE_dmx1a_common_tie_s_andc(a,b,c,d,e,f)
#define s_or(a,b,c,d,e,f)                                \
    _TIE_dmx1a_common_tie_s_or(a,b,c,d,e,f)
#define s_orc(a,b,c,d,e,f)                               \
    _TIE_dmx1a_common_tie_s_orc(a,b,c,d,e,f)
#define s_xor(a,b,c,d,e,f)                               \
    _TIE_dmx1a_common_tie_s_xor(a,b,c,d,e,f)
#define s_vnegs(a,b)                                     \
    _TIE_dmx1a_common_tie_s_vnegs(a,b)
#define s_vcopy(a,b)                                     \
    _TIE_dmx1a_common_tie_s_vcopy(a,b)
#define s_vand(a,b)                                      \
    _TIE_dmx1a_common_tie_s_vand(a,b)
#define s_vandc(a,b)                                     \
    _TIE_dmx1a_common_tie_s_vandc(a,b)
#define s_vor(a,b)                                       \
    _TIE_dmx1a_common_tie_s_vor(a,b)
#define s_vorc(a,b)                                      \
    _TIE_dmx1a_common_tie_s_vorc(a,b)
#define s_vxor(a,b)                                      \
    _TIE_dmx1a_common_tie_s_vxor(a,b)
#define s_vnegs_hr(a,b)                                  \
    _TIE_dmx1a_common_tie_s_vnegs_hr(a,b)
#define floorp_frac(a,b,c,d,e,f)                         \
    _TIE_dmx1a_common_tie_floorp_frac(a,b,c,d,e,f)
#define idx_frac(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_idx_frac(a,b,c,d,e)
#define truncate_fr(a)                                   \
    _TIE_dmx1a_common_tie_truncate_fr(a)
#define rmax_idx(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_rmax_idx(a,b,c,d,e)
#define rmin_idx(a,b,c,d,e)                              \
    _TIE_dmx1a_common_tie_rmin_idx(a,b,c,d,e)
#define vmaxmin_init(a,b,c)                              \
    _TIE_dmx1a_common_tie_vmaxmin_init(a,b,c)
#define vmax_idx(a,b,c)                                  \
    _TIE_dmx1a_common_tie_vmax_idx(a,b,c)
#define vmin_idx(a,b,c)                                  \
    _TIE_dmx1a_common_tie_vmin_idx(a,b,c)
#define vmax(a,b)                                        \
    _TIE_dmx1a_common_tie_vmax(a,b)
#define vmin(a,b)                                        \
    _TIE_dmx1a_common_tie_vmin(a,b)
#define sortupd_asc_vr(a,b,c,d,e)                        \
    _TIE_dmx1a_common_tie_sortupd_asc_vr(a,b,c,d,e)
#define sortupd_des_vr(a,b,c,d,e)                        \
    _TIE_dmx1a_common_tie_sortupd_des_vr(a,b,c,d,e)
#define sortupd_asc_ar(a,b,c)                            \
    _TIE_dmx1a_common_tie_sortupd_asc_ar(a,b,c)
#define sortupd_des_ar(a,b,c)                            \
    _TIE_dmx1a_common_tie_sortupd_des_ar(a,b,c)
#define vbool(a,b,c)                                     \
    _TIE_dmx1a_common_tie_vbool(a,b,c)
#define align_up(a,b)                                    \
    _TIE_dmx1a_common_tie_align_up(a,b)
#define range_init(a,b,c)                                \
    _TIE_dmx1a_common_tie_range_init(a,b,c)
#define range_check(a,b)                                 \
    _TIE_dmx1a_common_tie_range_check(a,b)
#define afloat_exp_extract(a)                            \
    _TIE_dmx1a_common_tie_afloat_exp_extract(a)
#define exp_shift_amount(a)                              \
    _TIE_dmx1a_common_tie_exp_shift_amount(a)
#define flush_32x4_bounded(a,b,c)                        \
    _TIE_dmx1a_common_tie_flush_32x4_bounded(a,(unsigned *)(b),c)
#define load_AccExtend_postI(a,b)                        \
    _TIE_dmx1a_common_tie_load_AccExtend_postI((const unsigned *)(a),b)
#define load_BB0_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB0_flex((const unsigned *)(a),b,c)
#define load_BB1_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB1_flex((const unsigned *)(a),b,c)
#define load_BB2_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB2_flex((const unsigned *)(a),b,c)
#define load_BB3_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB3_flex((const unsigned *)(a),b,c)
#define load_BB4_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB4_flex((const unsigned *)(a),b,c)
#define load_BB5_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB5_flex((const unsigned *)(a),b,c)
#define load_BB6_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB6_flex((const unsigned *)(a),b,c)
#define load_BB7_flex(a,b,c)                             \
    _TIE_dmx1a_common_tie_load_BB7_flex((const unsigned *)(a),b,c)
#define load_BB0_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB0_postI((const unsigned *)(a),b)
#define load_BB1_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB1_postI((const unsigned *)(a),b)
#define load_BB2_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB2_postI((const unsigned *)(a),b)
#define load_BB3_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB3_postI((const unsigned *)(a),b)
#define load_BB4_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB4_postI((const unsigned *)(a),b)
#define load_BB5_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB5_postI((const unsigned *)(a),b)
#define load_BB6_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB6_postI((const unsigned *)(a),b)
#define load_BB7_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_BB7_postI((const unsigned *)(a),b)
#define load_BBx_a_bounded(a,b,c,d)                      \
    _TIE_dmx1a_common_tie_load_BBx_a_bounded(a,(const unsigned *)(b),c,d)
#define load_VB1_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_VB1_postI((const unsigned *)(a),b)
#define load_VB2_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_VB2_postI((const unsigned *)(a),b)
#define load_VB3_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_VB3_postI((const unsigned *)(a),b)
#define load_VB4_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_VB4_postI((const unsigned *)(a),b)
#define load_VB5_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_VB5_postI((const unsigned *)(a),b)
#define load_VB6_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_VB6_postI((const unsigned *)(a),b)
#define load_VB7_postI(a,b)                              \
    _TIE_dmx1a_common_tie_load_VB7_postI((const unsigned *)(a),b)
#define load_32x4_vr_a_bounded(a,b,c,d)                  \
    _TIE_dmx1a_common_tie_load_32x4_vr_a_bounded(a,b,(const unsigned *)(c),d)
#define load_lookup_AccExtend_postI()                    \
    _TIE_dmx1a_common_tie_load_lookup_AccExtend_postI()
#define load_lookup_vr_postI()                           \
    _TIE_dmx1a_common_tie_load_lookup_vr_postI()
#define load32x1_lookup_AccExtend_idx16vr(a,b)           \
    _TIE_dmx1a_common_tie_load32x1_lookup_AccExtend_idx16vr(a,b)
#define load32x1_lookup_vr_idx16vr(a,b,c)                \
    _TIE_dmx1a_common_tie_load32x1_lookup_vr_idx16vr(a,b,c)
#define load32x1_vr_idx16vr(a,b,c,d)                     \
    _TIE_dmx1a_common_tie_load32x1_vr_idx16vr(a,(const unsigned *)(b),c,d)
#define mac8bx8b(a,b,c,d)                                \
    _TIE_dmx1a_common_tie_mac8bx8b(a,b,c,d)
#define mac8bx8b_conv(a,b,c,d)                           \
    _TIE_dmx1a_common_tie_mac8bx8b_conv(a,b,c,d)
#define mac8bx8b_sparse(a,b,c,d)                         \
    _TIE_dmx1a_common_tie_mac8bx8b_sparse(a,b,c,d)
#define mir_init(a)                                      \
    _TIE_dmx1a_common_tie_mir_init(a)
#define mov_AccExtend_vr(a)                              \
    _TIE_dmx1a_common_tie_mov_AccExtend_vr(a)
#define mov_BB_vrVB(a)                                   \
    _TIE_dmx1a_common_tie_mov_BB_vrVB(a)
#define mov_vr_AccExtend()                               \
    _TIE_dmx1a_common_tie_mov_vr_AccExtend()
#define mov_vrVB_BB()                                    \
    _TIE_dmx1a_common_tie_mov_vrVB_BB()
#define next_lookup_load()                               \
    _TIE_dmx1a_common_tie_next_lookup_load()
#define next_lookup_store()                              \
    _TIE_dmx1a_common_tie_next_lookup_store()
#define precess_16bits(a,b)                              \
    _TIE_dmx1a_common_tie_precess_16bits(a,b)
#define rectify32_into8(a,b,c,d,e)                       \
    _TIE_dmx1a_common_tie_rectify32_into8(a,b,c,d,e)
#define rnd_sat_pack(a,b,c,d)                            \
    _TIE_dmx1a_common_tie_rnd_sat_pack(a,b,c,d)
#define set_BB_zero()                                    \
    _TIE_dmx1a_common_tie_set_BB_zero()
#define shift8_into32_arith(a,b,c,d)                     \
    _TIE_dmx1a_common_tie_shift8_into32_arith(a,b,c,d)
#define shift32_arith(a,b,c)                             \
    _TIE_dmx1a_common_tie_shift32_arith(a,b,c)
#define store_32x4_vr_a_bounded(a,b,c,d)                 \
    _TIE_dmx1a_common_tie_store_32x4_vr_a_bounded(a,b,(unsigned *)(c),d)
#define store_AccExtend_postI(a,b)                       \
    _TIE_dmx1a_common_tie_store_AccExtend_postI((unsigned *)(a),b)
#define store_BB0_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB0_postI((unsigned *)(a),b)
#define store_BB1_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB1_postI((unsigned *)(a),b)
#define store_BB2_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB2_postI((unsigned *)(a),b)
#define store_BB3_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB3_postI((unsigned *)(a),b)
#define store_BB4_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB4_postI((unsigned *)(a),b)
#define store_BB5_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB5_postI((unsigned *)(a),b)
#define store_BB6_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB6_postI((unsigned *)(a),b)
#define store_BB7_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_BB7_postI((unsigned *)(a),b)
#define store_VB1_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_VB1_postI((unsigned *)(a),b)
#define store_VB2_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_VB2_postI((unsigned *)(a),b)
#define store_VB3_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_VB3_postI((unsigned *)(a),b)
#define store_VB4_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_VB4_postI((unsigned *)(a),b)
#define store_VB5_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_VB5_postI((unsigned *)(a),b)
#define store_VB6_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_VB6_postI((unsigned *)(a),b)
#define store_VB7_postI(a,b)                             \
    _TIE_dmx1a_common_tie_store_VB7_postI((unsigned *)(a),b)
#define store_lookup_AccExtend_postI()                   \
    _TIE_dmx1a_common_tie_store_lookup_AccExtend_postI()
#define store_lookup_vr_postI(a)                         \
    _TIE_dmx1a_common_tie_store_lookup_vr_postI(a)
#define mv_WR(a)                                         \
    _TIE_dmx1a_common_tie_mv_WR(a)
#define wr64_move(a)                                     \
    _TIE_dmx1a_common_tie_wr64_move(a)
#define mv_PERM(a)                                       \
    _TIE_dmx1a_common_tie_mv_PERM(a)
#define perm16_move(a)                                   \
    _TIE_dmx1a_common_tie_perm16_move(a)
#define mv_MIR(a)                                        \
    _TIE_dmx1a_common_tie_mv_MIR(a)
#define mir30_move(a)                                    \
    _TIE_dmx1a_common_tie_mir30_move(a)
#define mv_ULSR(a)                                       \
    _TIE_dmx1a_common_tie_mv_ULSR(a)
#define ulsr128_move(a)                                  \
    _TIE_dmx1a_common_tie_ulsr128_move(a)
#define mv_CR(a)                                         \
    _TIE_dmx1a_common_tie_mv_CR(a)
#define cr64_move(a)                                     \
    _TIE_dmx1a_common_tie_cr64_move(a)
#define ld_FR(a,b)                                       \
    _TIE_dmx1a_common_tie_ld_FR((const fr32 *)(a),b)
#define st_FR(a,b,c)                                     \
    _TIE_dmx1a_common_tie_st_FR(a,(fr32 *)(b),c)
#define ld_FR_idxR(a,b)                                  \
    _TIE_dmx1a_common_tie_ld_FR_idxR((const fr32 *)(a),b)
#define st_FR_idxR(a,b,c)                                \
    _TIE_dmx1a_common_tie_st_FR_idxR(a,(fr32 *)(b),c)
#define ld_FR_postI(a,b,c)                               \
    _TIE_dmx1a_common_tie_ld_FR_postI(a,(const fr32 *)(b),c)
#define st_FR_postI(a,b,c)                               \
    _TIE_dmx1a_common_tie_st_FR_postI(a,(fr32 *)(b),c)
#define ld_FR_postR(a,b,c)                               \
    _TIE_dmx1a_common_tie_ld_FR_postR(a,(const fr32 *)(b),c)
#define st_FR_postR(a,b,c)                               \
    _TIE_dmx1a_common_tie_st_FR_postR(a,(fr32 *)(b),c)
#define ld_HR(a,b)                                       \
    _TIE_dmx1a_common_tie_ld_HR((const vr64 *)(a),b)
#define st_HR(a,b,c)                                     \
    _TIE_dmx1a_common_tie_st_HR(a,(vr64 *)(b),c)
#define ld_HR_idxR(a,b)                                  \
    _TIE_dmx1a_common_tie_ld_HR_idxR((const vr64 *)(a),b)
#define st_HR_idxR(a,b,c)                                \
    _TIE_dmx1a_common_tie_st_HR_idxR(a,(vr64 *)(b),c)
#define ld_HR_postI(a,b,c)                               \
    _TIE_dmx1a_common_tie_ld_HR_postI(a,(const vr64 *)(b),c)
#define st_HR_postI(a,b,c)                               \
    _TIE_dmx1a_common_tie_st_HR_postI(a,(vr64 *)(b),c)
#define ld_HR_postR(a,b,c)                               \
    _TIE_dmx1a_common_tie_ld_HR_postR(a,(const vr64 *)(b),c)
#define st_HR_postR(a,b,c)                               \
    _TIE_dmx1a_common_tie_st_HR_postR(a,(vr64 *)(b),c)
#define ld_VR(a,b)                                       \
    _TIE_dmx1a_common_tie_ld_VR((const vr128 *)(a),b)
#define st_VR(a,b,c)                                     \
    _TIE_dmx1a_common_tie_st_VR(a,(vr128 *)(b),c)
#define ld_VR_idxR(a,b)                                  \
    _TIE_dmx1a_common_tie_ld_VR_idxR((const vr128 *)(a),b)
#define st_VR_idxR(a,b,c)                                \
    _TIE_dmx1a_common_tie_st_VR_idxR(a,(vr128 *)(b),c)
#define ld_VR_postI(a,b,c)                               \
    _TIE_dmx1a_common_tie_ld_VR_postI(a,(const vr128 *)(b),c)
#define st_VR_postI(a,b,c)                               \
    _TIE_dmx1a_common_tie_st_VR_postI(a,(vr128 *)(b),c)
#define ld_VR_postR(a,b,c)                               \
    _TIE_dmx1a_common_tie_ld_VR_postR(a,(const vr128 *)(b),c)
#define st_VR_postR(a,b,c)                               \
    _TIE_dmx1a_common_tie_st_VR_postR(a,(vr128 *)(b),c)
#define mv_FR(a)                                         \
    _TIE_dmx1a_common_tie_mv_FR(a)
#define move_ar_fr(a)                                    \
    _TIE_dmx1a_common_tie_move_ar_fr(a)
#define move_fr_ar(a)                                    \
    _TIE_dmx1a_common_tie_move_fr_ar(a)
#define fr32_move(a)                                     \
    _TIE_dmx1a_common_tie_fr32_move(a)
#define fr32_loadi(a,b)                                  \
    _TIE_dmx1a_common_tie_fr32_loadi((const fr32 *)(a),b)
#define fr32_storei(a,b,c)                               \
    _TIE_dmx1a_common_tie_fr32_storei(a,(fr32 *)(b),c)
#define fr32_loadx(a,b)                                  \
    _TIE_dmx1a_common_tie_fr32_loadx((const fr32 *)(a),b)
#define fr32_storex(a,b,c)                               \
    _TIE_dmx1a_common_tie_fr32_storex(a,(fr32 *)(b),c)
#define fr32_loadip(a,b,c)                               \
    _TIE_dmx1a_common_tie_fr32_loadip(a,(const fr32 *)(b),c)
#define fr32_storeip(a,b,c)                              \
    _TIE_dmx1a_common_tie_fr32_storeip(a,(fr32 *)(b),c)
#define fr32_loadxp(a,b,c)                               \
    _TIE_dmx1a_common_tie_fr32_loadxp(a,(const fr32 *)(b),c)
#define fr32_storexp(a,b,c)                              \
    _TIE_dmx1a_common_tie_fr32_storexp(a,(fr32 *)(b),c)
#define fr32_rtor_int32(a)                               \
    _TIE_dmx1a_common_tie_fr32_rtor_int32(a)
#define fr32_rtor_uint32(a)                              \
    _TIE_dmx1a_common_tie_fr32_rtor_uint32(a)
#define int32_rtor_fr32(a)                               \
    _TIE_dmx1a_common_tie_int32_rtor_fr32(a)
#define uint32_rtor_fr32(a)                              \
    _TIE_dmx1a_common_tie_uint32_rtor_fr32(a)
#define mv_HR(a)                                         \
    _TIE_dmx1a_common_tie_mv_HR(a)
#define vr64_move(a)                                     \
    _TIE_dmx1a_common_tie_vr64_move(a)
#define vr64_loadi(a,b)                                  \
    _TIE_dmx1a_common_tie_vr64_loadi((const vr64 *)(a),b)
#define vr64_storei(a,b,c)                               \
    _TIE_dmx1a_common_tie_vr64_storei(a,(vr64 *)(b),c)
#define vr64_loadx(a,b)                                  \
    _TIE_dmx1a_common_tie_vr64_loadx((const vr64 *)(a),b)
#define vr64_storex(a,b,c)                               \
    _TIE_dmx1a_common_tie_vr64_storex(a,(vr64 *)(b),c)
#define vr64_loadip(a,b,c)                               \
    _TIE_dmx1a_common_tie_vr64_loadip(a,(const vr64 *)(b),c)
#define vr64_storeip(a,b,c)                              \
    _TIE_dmx1a_common_tie_vr64_storeip(a,(vr64 *)(b),c)
#define vr64_loadxp(a,b,c)                               \
    _TIE_dmx1a_common_tie_vr64_loadxp(a,(const vr64 *)(b),c)
#define vr64_storexp(a,b,c)                              \
    _TIE_dmx1a_common_tie_vr64_storexp(a,(vr64 *)(b),c)
#define vr64_rtor_int64(a)                               \
    _TIE_dmx1a_common_tie_vr64_rtor_int64(a)
#define vr64_rtor_uint64(a)                              \
    _TIE_dmx1a_common_tie_vr64_rtor_uint64(a)
#define int64_rtor_vr64(a)                               \
    _TIE_dmx1a_common_tie_int64_rtor_vr64(a)
#define uint64_rtor_vr64(a)                              \
    _TIE_dmx1a_common_tie_uint64_rtor_vr64(a)
#define vr64_pair(a,b)                                   \
    _TIE_dmx1a_common_tie_vr64_pair(a,b)
#define get_HRL(a)                                       \
    _TIE_dmx1a_common_tie_get_HRL(a)
#define get_HRH(a)                                       \
    _TIE_dmx1a_common_tie_get_HRH(a)
#define set_HRL(a,b)                                     \
    _TIE_dmx1a_common_tie_set_HRL(a,b)
#define set_HRH(a,b)                                     \
    _TIE_dmx1a_common_tie_set_HRH(a,b)
#define mv_VR(a)                                         \
    _TIE_dmx1a_common_tie_mv_VR(a)
#define vr128_move(a)                                    \
    _TIE_dmx1a_common_tie_vr128_move(a)
#define vr128_loadi(a,b)                                 \
    _TIE_dmx1a_common_tie_vr128_loadi((const vr128 *)(a),b)
#define vr128_storei(a,b,c)                              \
    _TIE_dmx1a_common_tie_vr128_storei(a,(vr128 *)(b),c)
#define vr128_loadx(a,b)                                 \
    _TIE_dmx1a_common_tie_vr128_loadx((const vr128 *)(a),b)
#define vr128_storex(a,b,c)                              \
    _TIE_dmx1a_common_tie_vr128_storex(a,(vr128 *)(b),c)
#define vr128_loadip(a,b,c)                              \
    _TIE_dmx1a_common_tie_vr128_loadip(a,(const vr128 *)(b),c)
#define vr128_storeip(a,b,c)                             \
    _TIE_dmx1a_common_tie_vr128_storeip(a,(vr128 *)(b),c)
#define vr128_loadxp(a,b,c)                              \
    _TIE_dmx1a_common_tie_vr128_loadxp(a,(const vr128 *)(b),c)
#define vr128_storexp(a,b,c)                             \
    _TIE_dmx1a_common_tie_vr128_storexp(a,(vr128 *)(b),c)
#define vr128_pair(a,b)                                  \
    _TIE_dmx1a_common_tie_vr128_pair(a,b)
#define set_VRL(a,b)                                     \
    _TIE_dmx1a_common_tie_set_VRL(a,b)
#define set_VRH(a,b)                                     \
    _TIE_dmx1a_common_tie_set_VRH(a,b)
#define get_VRL(a)                                       \
    _TIE_dmx1a_common_tie_get_VRL(a)
#define get_VRH(a)                                       \
    _TIE_dmx1a_common_tie_get_VRH(a)
#define vr128_quad(a,b,c,d)                              \
    _TIE_dmx1a_common_tie_vr128_quad(a,b,c,d)
#define get_VRQ0(a)                                      \
    _TIE_dmx1a_common_tie_get_VRQ0(a)
#define get_VRQ1(a)                                      \
    _TIE_dmx1a_common_tie_get_VRQ1(a)
#define get_VRQ2(a)                                      \
    _TIE_dmx1a_common_tie_get_VRQ2(a)
#define get_VRQ3(a)                                      \
    _TIE_dmx1a_common_tie_get_VRQ3(a)
// Work around for compiler over-optimization:
#define set_VRQ0(a,b)                                    \
    asm("mv.FR %0, %1" : "+a" (a) : "a" (b))
#define set_VRQ1(a,b)                                    \
    _TIE_dmx1a_common_tie_set_VRQ1(a,b)
#define set_VRQ2(a,b)                                    \
    _TIE_dmx1a_common_tie_set_VRQ2(a,b)
#define set_VRQ3(a,b)                                    \
    _TIE_dmx1a_common_tie_set_VRQ3(a,b)
#define ld_ar_x2(a,b,c,d)                                \
    _TIE_dmx1a_common_tie_ld_ar_x2(a,b,(const void *)(c),d)
#define st_ar_x2(a,b,c,d)                                \
    _TIE_dmx1a_common_tie_st_ar_x2((void *)(a),b,c,d)

#endif //TIE_INCLUDE_H



/* End of File */

