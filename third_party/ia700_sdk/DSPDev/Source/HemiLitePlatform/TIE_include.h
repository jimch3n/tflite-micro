/************************************************************************//**
 * File: TIE_include.h
 *
 * Description: Definitions needed for TIE Intrinsics
 *
 * Copyright 2018 Knowles Corporation. All rights reserved.
 *
 * All information, including software, contained herein is and remains
 * the property of Knowles Corporation. The intellectual and technical 
 * concepts contained herein are proprietary to Knowles Corporation
 * and may be covered by U.S. and foreign patents, patents in process,
 * and/or are protected by trade secret and/or copyright law. 
 * This information may only be used in accordance with the applicable
 * Knowles SDK License. Dissemination of this information or distribution
 * of this material is strictly forbidden unless in accordance with the 
 * applicable Knowles SDK License.   
 * 
 *
 * KNOWLES SOURCE CODE IS STRICTLY PROVIDED "AS IS" WITHOUT ANY WARRANTY
 * WHATSOEVER, AND KNOWLES EXPRESSLY DISCLAIMS ALL WARRANTIES,
 * EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE OR NON-INFRINGEMENT OF THIRD PARTY RIGHTS. KNOWLES
 * SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF
 * USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 * IN CERTAIN STATES, THE LAW MAY NOT ALLOW KNOWLES TO DISCLAIM OR EXCLUDE
 * WARRANTIES OR DISCLAIM DAMAGES, SO THE ABOVE DISCLAIMERS MAY NOT APPLY.
 * IN SUCH EVENT, KNOWLES' AGGREGATE LIABILITY SHALL NOT EXCEED 
 * FIFTY DOLLARS ($50.00).
 *
 ****************************************************************************/
#ifndef TIE_INCLUDE_H
#define TIE_INCLUDE_H


#include "hemilite_common_tie.h"

#ifdef LOG_TIE
#include <stdio.h>
#include "typedefs.h"
#define LOG_TIE0(fmt) fprintf(gTieLogFile,fmt)
#define LOG_TIE1(fmt,a) fprintf(gTieLogFile,fmt,a)
#define LOG_TIE2(fmt,a,b) fprintf(gTieLogFile,fmt,a,b)
#define LOG_TIE3(fmt,a,b,c) fprintf(gTieLogFile,fmt,a,b,c)
#define LOG_TIE4(fmt,a,b,c,d) fprintf(gTieLogFile,fmt,a,b,c,d)
#define LOG_TIE5(fmt,a,b,c,d,e) fprintf(gTieLogFile,fmt,a,b,c,d,e)
#define LOG_TIE6(fmt,a,b,c,d,e,f) fprintf(gTieLogFile,fmt,a,b,c,d,e,f)
#define LOG_TIE7(fmt,a,b,c,d,e,f,g) fprintf(gTieLogFile,fmt,a,b,c,d,e,f,g)
#define LOG_TIE8(fmt,a,b,c,d,e,f,g,h) fprintf(gTieLogFile,fmt,a,b,c,d,e,f,g,h)
#define LOG_TIE9(fmt,a,b,c,d,e,f,g,h,i) fprintf(gTieLogFile,fmt,a,b,c,d,e,f,g,h,i)
#define LT_MEM(t,v,i) LT##t##i=v
extern FILE* gTieLogFile;
extern cr64 LTcr64_a;
extern mir18 LTmir18_a;
extern ulsr32 LTulsr32_a;
extern fr32 LTfr32_a, LTfr32_b, LTfr32_c;
extern vr64 LTvr64_a, LTvr64_b, LTvr64_c;
extern atbool LTatbool_a;
#else //!LOG_TIE
#define LT_MEM(t,v,i) (void)0
#define LOG_TIE0(fmt) (void)0
#define LOG_TIE1(fmt,a) (void)0
#define LOG_TIE2(fmt,a,b) (void)0
#define LOG_TIE3(fmt,a,b,c) (void)0
#define LOG_TIE4(fmt,a,b,c,d) (void)0
#define LOG_TIE5(fmt,a,b,c,d,e) (void)0
#define LOG_TIE6(fmt,a,b,c,d,e,f) (void)0
#define LOG_TIE7(fmt,a,b,c,d,e,f,g) (void)0
#define LOG_TIE8(fmt,a,b,c,d,e,f,g,h) (void)0
#define LOG_TIE9(fmt,a,b,c,d,e,f,g,h,i) (void)0
#endif //LOG_TIE

#ifdef __cplusplus
#define CPP_ULONG_CAST(a) reinterpret_cast<unsigned long&>(a)
#else
#define CPP_ULONG_CAST(a) a
#endif

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
#undef dma_ld
#undef dma_align_ld
#undef dma_ldu
#undef dma_flush_ld
#undef dma_st
#undef dma_align_st
#undef dma_stu
#undef dma_flush_st
#undef dma_buf_save
#define st_BBR(a,b,c)                               (LT_MEM(atbool,a,_a),LOG_TIE3("st_BBR(0x%x,0x%08x,%d)\n",(uint8_t)LTatbool_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_BBR(a,(atbool *)(b),c))
#define atbool_storei(a,b,c)                        (LT_MEM(atbool,a,_a),LOG_TIE3("atbool_storei(0x%x,0x%08x,%d)\n",(uint8_t)LTatbool_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_atbool_storei(a,(atbool *)(b),c))
#define ld_BBR(a,b)                                 (LOG_TIE2("ld_BBR(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_ld_BBR((const atbool *)(a),b))
#define atbool_loadi(a,b)                           (LOG_TIE2("atbool_loadi(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_atbool_loadi((const atbool *)(a),b))
#define mv_BBR(a)                                   (LT_MEM(atbool,a,_a),LOG_TIE1("mv_BBR(0x%x)\n",(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_mv_BBR(a))
#define atbool_move(a)                              (LT_MEM(atbool,a,_a),LOG_TIE1("atbool_move(0x%x)\n",(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_atbool_move(a))
#define st_ULSR(a,b,c)                              (LT_MEM(ulsr32,a,_a),LOG_TIE3("st_ULSR(0x%08x,0x%08x,%d)\n",(unsigned)LTulsr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_ULSR(a,(ulsr32 *)(b),c))
#define ulsr32_storei(a,b,c)                        (LT_MEM(ulsr32,a,_a),LOG_TIE3("ulsr32_storei(0x%08x,0x%08x,%d)\n",(unsigned)LTulsr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_ulsr32_storei(a,(ulsr32 *)(b),c))
#define ld_ULSR(a,b)                                (LOG_TIE2("ld_ULSR(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_ld_ULSR((const ulsr32 *)(a),b))
#define ulsr32_loadi(a,b)                           (LOG_TIE2("ulsr32_loadi(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_ulsr32_loadi((const ulsr32 *)(a),b))
#define st_MIR(a,b,c)                               (LT_MEM(mir18,a,_a),LOG_TIE3("st_MIR(0x%08x,0x%08x,%d)\n",*(unsigned*)&LTmir18_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_MIR(a,(mir18 *)(b),c))
#define mir18_storei(a,b,c)                         (LT_MEM(mir18,a,_a),LOG_TIE3("mir18_storei(0x%08x,0x%08x,%d)\n",*(unsigned*)&LTmir18_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_mir18_storei(a,(mir18 *)(b),c))
#define ld_MIR(a,b)                                 (LOG_TIE2("ld_MIR(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_ld_MIR((const mir18 *)(a),b))
#define mir18_loadi(a,b)                            (LOG_TIE2("mir18_loadi(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_mir18_loadi((const mir18 *)(a),b))
#define st_CR(a,b,c)                                (LT_MEM(cr64,a,_a),LOG_TIE3("st_CR(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTcr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_CR(a,(cr64 *)(b),c))
#define cr64_storei(a,b,c)                          (LT_MEM(cr64,a,_a),LOG_TIE3("cr64_storei(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTcr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_cr64_storei(a,(cr64 *)(b),c))
#define ld_CR(a,b)                                  (LOG_TIE2("ld_CR(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_ld_CR((const cr64 *)(a),b))
#define cr64_loadi(a,b)                             (LOG_TIE2("cr64_loadi(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_cr64_loadi((const cr64 *)(a),b))
#define RUR_JammingBit()                            (LOG_TIE0("RUR_JammingBit()\n"),\
    _TIE_hemilite_common_tie_RUR_JammingBit())
#define WUR_JammingBit(a)                           (LOG_TIE1("WUR_JammingBit(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_JammingBit(a))
#define RUR_AccExtend_0()                           (LOG_TIE0("RUR_AccExtend_0()\n"),\
    _TIE_hemilite_common_tie_RUR_AccExtend_0())
#define WUR_AccExtend_0(a)                          (LOG_TIE1("WUR_AccExtend_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_AccExtend_0(a))
#define RUR_AccExtend_1()                           (LOG_TIE0("RUR_AccExtend_1()\n"),\
    _TIE_hemilite_common_tie_RUR_AccExtend_1())
#define WUR_AccExtend_1(a)                          (LOG_TIE1("WUR_AccExtend_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_AccExtend_1(a))
#define RUR_BB0_0()                                 (LOG_TIE0("RUR_BB0_0()\n"),\
    _TIE_hemilite_common_tie_RUR_BB0_0())
#define WUR_BB0_0(a)                                (LOG_TIE1("WUR_BB0_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB0_0(a))
#define RUR_BB0_1()                                 (LOG_TIE0("RUR_BB0_1()\n"),\
    _TIE_hemilite_common_tie_RUR_BB0_1())
#define WUR_BB0_1(a)                                (LOG_TIE1("WUR_BB0_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB0_1(a))
#define RUR_BB1_0()                                 (LOG_TIE0("RUR_BB1_0()\n"),\
    _TIE_hemilite_common_tie_RUR_BB1_0())
#define WUR_BB1_0(a)                                (LOG_TIE1("WUR_BB1_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB1_0(a))
#define RUR_BB1_1()                                 (LOG_TIE0("RUR_BB1_1()\n"),\
    _TIE_hemilite_common_tie_RUR_BB1_1())
#define WUR_BB1_1(a)                                (LOG_TIE1("WUR_BB1_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB1_1(a))
#define RUR_BB2_0()                                 (LOG_TIE0("RUR_BB2_0()\n"),\
    _TIE_hemilite_common_tie_RUR_BB2_0())
#define WUR_BB2_0(a)                                (LOG_TIE1("WUR_BB2_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB2_0(a))
#define RUR_BB2_1()                                 (LOG_TIE0("RUR_BB2_1()\n"),\
    _TIE_hemilite_common_tie_RUR_BB2_1())
#define WUR_BB2_1(a)                                (LOG_TIE1("WUR_BB2_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB2_1(a))
#define RUR_BB3_0()                                 (LOG_TIE0("RUR_BB3_0()\n"),\
    _TIE_hemilite_common_tie_RUR_BB3_0())
#define WUR_BB3_0(a)                                (LOG_TIE1("WUR_BB3_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB3_0(a))
#define RUR_BB3_1()                                 (LOG_TIE0("RUR_BB3_1()\n"),\
    _TIE_hemilite_common_tie_RUR_BB3_1())
#define WUR_BB3_1(a)                                (LOG_TIE1("WUR_BB3_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_BB3_1(a))
#define RUR_MvmAux()                                (LOG_TIE0("RUR_MvmAux()\n"),\
    _TIE_hemilite_common_tie_RUR_MvmAux())
#define WUR_MvmAux(a)                               (LOG_TIE1("WUR_MvmAux(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_MvmAux(a))
#define RUR_VB1_0()                                 (LOG_TIE0("RUR_VB1_0()\n"),\
    _TIE_hemilite_common_tie_RUR_VB1_0())
#define WUR_VB1_0(a)                                (LOG_TIE1("WUR_VB1_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB1_0(a))
#define RUR_VB1_1()                                 (LOG_TIE0("RUR_VB1_1()\n"),\
    _TIE_hemilite_common_tie_RUR_VB1_1())
#define WUR_VB1_1(a)                                (LOG_TIE1("WUR_VB1_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB1_1(a))
#define RUR_VB2_0()                                 (LOG_TIE0("RUR_VB2_0()\n"),\
    _TIE_hemilite_common_tie_RUR_VB2_0())
#define WUR_VB2_0(a)                                (LOG_TIE1("WUR_VB2_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB2_0(a))
#define RUR_VB2_1()                                 (LOG_TIE0("RUR_VB2_1()\n"),\
    _TIE_hemilite_common_tie_RUR_VB2_1())
#define WUR_VB2_1(a)                                (LOG_TIE1("WUR_VB2_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB2_1(a))
#define RUR_VB3_0()                                 (LOG_TIE0("RUR_VB3_0()\n"),\
    _TIE_hemilite_common_tie_RUR_VB3_0())
#define WUR_VB3_0(a)                                (LOG_TIE1("WUR_VB3_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB3_0(a))
#define RUR_VB3_1()                                 (LOG_TIE0("RUR_VB3_1()\n"),\
    _TIE_hemilite_common_tie_RUR_VB3_1())
#define WUR_VB3_1(a)                                (LOG_TIE1("WUR_VB3_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB3_1(a))
#define RUR_VB4_0()                                 (LOG_TIE0("RUR_VB4_0()\n"),\
    _TIE_hemilite_common_tie_RUR_VB4_0())
#define WUR_VB4_0(a)                                (LOG_TIE1("WUR_VB4_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB4_0(a))
#define RUR_VB4_1()                                 (LOG_TIE0("RUR_VB4_1()\n"),\
    _TIE_hemilite_common_tie_RUR_VB4_1())
#define WUR_VB4_1(a)                                (LOG_TIE1("WUR_VB4_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB4_1(a))
#define RUR_VB5_0()                                 (LOG_TIE0("RUR_VB5_0()\n"),\
    _TIE_hemilite_common_tie_RUR_VB5_0())
#define WUR_VB5_0(a)                                (LOG_TIE1("WUR_VB5_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB5_0(a))
#define RUR_VB5_1()                                 (LOG_TIE0("RUR_VB5_1()\n"),\
    _TIE_hemilite_common_tie_RUR_VB5_1())
#define WUR_VB5_1(a)                                (LOG_TIE1("WUR_VB5_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB5_1(a))
#define RUR_VB6_0()                                 (LOG_TIE0("RUR_VB6_0()\n"),\
    _TIE_hemilite_common_tie_RUR_VB6_0())
#define WUR_VB6_0(a)                                (LOG_TIE1("WUR_VB6_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB6_0(a))
#define RUR_VB6_1()                                 (LOG_TIE0("RUR_VB6_1()\n"),\
    _TIE_hemilite_common_tie_RUR_VB6_1())
#define WUR_VB6_1(a)                                (LOG_TIE1("WUR_VB6_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB6_1(a))
#define RUR_VB7_0()                                 (LOG_TIE0("RUR_VB7_0()\n"),\
    _TIE_hemilite_common_tie_RUR_VB7_0())
#define WUR_VB7_0(a)                                (LOG_TIE1("WUR_VB7_0(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB7_0(a))
#define RUR_VB7_1()                                 (LOG_TIE0("RUR_VB7_1()\n"),\
    _TIE_hemilite_common_tie_RUR_VB7_1())
#define WUR_VB7_1(a)                                (LOG_TIE1("WUR_VB7_1(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_WUR_VB7_1(a))
#define load32x2_vr_idxR(a,b)                       (LOG_TIE2("load32x2_vr_idxR(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_load32x2_vr_idxR((const unsigned *)(a),b))
#define load32x2_vr_idxI(a,b)                       (LOG_TIE2("load32x2_vr_idxI(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_load32x2_vr_idxI((const unsigned *)(a),b))
#define load32x2_vr_postR(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("load32x2_vr_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_load32x2_vr_postR(a,(const unsigned *)(b),c))
#define load32x2_vr_postI(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("load32x2_vr_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_load32x2_vr_postI(a,(const unsigned *)(b),c))
#define load32x2_vr_circI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE4("load32x2_vr_circI(0x%016llx,0x%08x,%d,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_load32x2_vr_circI(a,(const unsigned *)(b),c,d))
#define load32x1_vr_idxR(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("load32x1_vr_idxR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load32x1_vr_idxR(a,(const unsigned *)(b),c,d))
#define load32x1_vr_idxI(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("load32x1_vr_idxI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load32x1_vr_idxI(a,(const unsigned *)(b),c,d))
#define load32x1_vr_postR(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("load32x1_vr_postR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load32x1_vr_postR(a,(const unsigned *)(b),c,d))
#define load32x1_vr_postI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("load32x1_vr_postI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load32x1_vr_postI(a,(const unsigned *)(b),c,d))
#define load32x1_vr_circI(a,b,c,d,e)                (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("load32x1_vr_circI(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_load32x1_vr_circI(a,(const unsigned *)(b),c,d,e))
#define load32x2_vr_bdir(a,b)                       (LOG_TIE2("load32x2_vr_bdir(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_load32x2_vr_bdir((const unsigned *)(a),b))
#define load32x2_vr_brev(a,b)                       (LOG_TIE2("load32x2_vr_brev(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_load32x2_vr_brev((const unsigned *)(a),b))
#define load32x2_vr_idxR_perm(a,b,c,d)              (LT_MEM(vr64,a,_a),LOG_TIE4("load32x2_vr_idxR_perm(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load32x2_vr_idxR_perm(a,(const unsigned *)(b),c,d))
#define load32x2_vr_idxI_perm_vr(a,b,c,d)           (LT_MEM(vr64,a,_a),LOG_TIE4("load32x2_vr_idxI_perm_vr(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load32x2_vr_idxI_perm_vr(a,(const unsigned *)(b),c,d))
#define load32x2_vr_postR_perm(a,b,c,d)             (LT_MEM(vr64,a,_a),LOG_TIE4("load32x2_vr_postR_perm(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load32x2_vr_postR_perm(a,(const unsigned *)(b),c,d))
#define load32x2_vr_postI_perm_vr(a,b,c,d,e)        (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE5("load32x2_vr_postI_perm_vr(0x%016llx,0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,(unsigned)c,d,e),\
    _TIE_hemilite_common_tie_load32x2_vr_postI_perm_vr(a,b,(const unsigned *)(c),d,e))
#define load32x2_vr_circI_perm(a,b,c,d,e)           (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("load32x2_vr_circI_perm(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_load32x2_vr_circI_perm(a,(const unsigned *)(b),c,d,e))
#define load32x1_vr_idxR_perm(a,b,c,d)              (LT_MEM(vr64,a,_a),LOG_TIE4("load32x1_vr_idxR_perm(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load32x1_vr_idxR_perm(a,(const unsigned *)(b),c,d))
#define load32x1_vr_idxI_perm_vr(a,b,c,d)           (LT_MEM(vr64,a,_a),LOG_TIE4("load32x1_vr_idxI_perm_vr(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load32x1_vr_idxI_perm_vr(a,(const unsigned *)(b),c,d))
#define load32x1_vr_postR_perm(a,b,c,d)             (LT_MEM(vr64,a,_a),LOG_TIE4("load32x1_vr_postR_perm(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load32x1_vr_postR_perm(a,(const unsigned *)(b),c,d))
#define load32x1_vr_postI_perm_vr(a,b,c,d,e)        (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE5("load32x1_vr_postI_perm_vr(0x%016llx,0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,(unsigned)c,d,e),\
    _TIE_hemilite_common_tie_load32x1_vr_postI_perm_vr(a,b,(const unsigned *)(c),d,e))
#define load32x1_vr_circI_perm(a,b,c,d,e)           (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("load32x1_vr_circI_perm(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_load32x1_vr_circI_perm(a,(const unsigned *)(b),c,d,e))
#define load16x2_vr_idxR(a,b)                       (LOG_TIE2("load16x2_vr_idxR(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_load16x2_vr_idxR((const unsigned *)(a),b))
#define load16x2_vr_idxI(a,b)                       (LOG_TIE2("load16x2_vr_idxI(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_load16x2_vr_idxI((const unsigned *)(a),b))
#define load16x2_vr_postR(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("load16x2_vr_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_load16x2_vr_postR(a,(const unsigned *)(b),c))
#define load16x2_vr_postI(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("load16x2_vr_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_load16x2_vr_postI(a,(const unsigned *)(b),c))
#define load16x2_vr_circI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE4("load16x2_vr_circI(0x%016llx,0x%08x,%d,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_load16x2_vr_circI(a,(const unsigned *)(b),c,d))
#define load16x1_vr_idxR(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("load16x1_vr_idxR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load16x1_vr_idxR(a,(const unsigned *)(b),c,d))
#define load16x1_vr_idxI(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("load16x1_vr_idxI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load16x1_vr_idxI(a,(const unsigned *)(b),c,d))
#define load16x1_vr_postR(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("load16x1_vr_postR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load16x1_vr_postR(a,(const unsigned *)(b),c,d))
#define load16x1_vr_postI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("load16x1_vr_postI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load16x1_vr_postI(a,(const unsigned *)(b),c,d))
#define load16x1_vr_circI(a,b,c,d,e)                (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("load16x1_vr_circI(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_load16x1_vr_circI(a,(const unsigned *)(b),c,d,e))
#define load8x2_vr_idxR(a,b)                        (LOG_TIE2("load8x2_vr_idxR(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_load8x2_vr_idxR((const unsigned *)(a),b))
#define load8x2_vr_idxI(a,b)                        (LOG_TIE2("load8x2_vr_idxI(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_load8x2_vr_idxI((const unsigned *)(a),b))
#define load8x2_vr_postR(a,b,c)                     (LT_MEM(vr64,a,_a),LOG_TIE3("load8x2_vr_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_load8x2_vr_postR(a,(const unsigned *)(b),c))
#define load8x2_vr_postI(a,b,c)                     (LT_MEM(vr64,a,_a),LOG_TIE3("load8x2_vr_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_load8x2_vr_postI(a,(const unsigned *)(b),c))
#define load8x2_vr_circI(a,b,c,d)                   (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE4("load8x2_vr_circI(0x%016llx,0x%08x,%d,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_load8x2_vr_circI(a,(const unsigned *)(b),c,d))
#define load8x1_vr_idxR(a,b,c,d)                    (LT_MEM(vr64,a,_a),LOG_TIE4("load8x1_vr_idxR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load8x1_vr_idxR(a,(const unsigned *)(b),c,d))
#define load8x1_vr_idxI(a,b,c,d)                    (LT_MEM(vr64,a,_a),LOG_TIE4("load8x1_vr_idxI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load8x1_vr_idxI(a,(const unsigned *)(b),c,d))
#define load8x1_vr_postR(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("load8x1_vr_postR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_load8x1_vr_postR(a,(const unsigned *)(b),c,d))
#define load8x1_vr_postI(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("load8x1_vr_postI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_load8x1_vr_postI(a,(const unsigned *)(b),c,d))
#define load8x1_vr_circI(a,b,c,d,e)                 (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("load8x1_vr_circI(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_load8x1_vr_circI(a,(const unsigned *)(b),c,d,e))
#define align_32x2_load(a)                          (LOG_TIE1("align_32x2_load(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_align_32x2_load((const unsigned *)(a)))
#define load_32x2_vr_a(a,b,c)                       (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LOG_TIE3("load_32x2_vr_a(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c),\
    _TIE_hemilite_common_tie_load_32x2_vr_a(a,b,(const unsigned *)(c)))
#define load_24x2_vr_a(a,b,c)                       (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LOG_TIE3("load_24x2_vr_a(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c),\
    _TIE_hemilite_common_tie_load_24x2_vr_a(a,b,(const unsigned *)(c)))
#define load_32x2_vr_a_circ(a,b,c,d)                (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LT_MEM(cr64,d,_a),LOG_TIE4("load_32x2_vr_a_circ(0x%016llx,0x%08x,0x%08x,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_load_32x2_vr_a_circ(a,b,(const unsigned *)(c),d))
#define store32x2_vr_idxR(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("store32x2_vr_idxR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_store32x2_vr_idxR(a,(unsigned *)(b),c))
#define store32x2_vr_idxI(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("store32x2_vr_idxI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_store32x2_vr_idxI(a,(unsigned *)(b),c))
#define store32x2_vr_postR(a,b,c)                   (LT_MEM(vr64,a,_a),LOG_TIE3("store32x2_vr_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_store32x2_vr_postR(a,(unsigned *)(b),c))
#define store32x2_vr_postI(a,b,c)                   (LT_MEM(vr64,a,_a),LOG_TIE3("store32x2_vr_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_store32x2_vr_postI(a,(unsigned *)(b),c))
#define store32x2_vr_circI(a,b,c,d)                 (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE4("store32x2_vr_circI(0x%016llx,0x%08x,%d,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_store32x2_vr_circI(a,(unsigned *)(b),c,d))
#define store32x1_vr_idxR(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("store32x1_vr_idxR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store32x1_vr_idxR(a,(unsigned *)(b),c,d))
#define store32x1_vr_idxI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("store32x1_vr_idxI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_store32x1_vr_idxI(a,(unsigned *)(b),c,d))
#define store32x1_vr_postR(a,b,c,d)                 (LT_MEM(vr64,a,_a),LOG_TIE4("store32x1_vr_postR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store32x1_vr_postR(a,(unsigned *)(b),c,d))
#define store32x1_vr_postI(a,b,c,d)                 (LT_MEM(vr64,a,_a),LOG_TIE4("store32x1_vr_postI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_store32x1_vr_postI(a,(unsigned *)(b),c,d))
#define store32x1_vr_circI(a,b,c,d,e)               (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("store32x1_vr_circI(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_store32x1_vr_circI(a,(unsigned *)(b),c,d,e))
#define store32x2_vr_br_idxR(a,b,c,d)               (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE4("store32x2_vr_br_idxR(0x%016llx,0x%x,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,(unsigned)d),\
    _TIE_hemilite_common_tie_store32x2_vr_br_idxR(a,b,(unsigned *)(c),d))
#define store32x2_vr_br_idxI(a,b,c,d)               (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE4("store32x2_vr_br_idxI(0x%016llx,0x%x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store32x2_vr_br_idxI(a,b,(unsigned *)(c),d))
#define store32x2_vr_br_postR(a,b,c,d)              (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE4("store32x2_vr_br_postR(0x%016llx,0x%x,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,(unsigned)d),\
    _TIE_hemilite_common_tie_store32x2_vr_br_postR(a,b,(unsigned *)(c),d))
#define store32x2_vr_br_postI(a,b,c,d)              (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE4("store32x2_vr_br_postI(0x%016llx,0x%x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store32x2_vr_br_postI(a,b,(unsigned *)(c),d))
#define store32x2_vr_br_circI(a,b,c,d,e)            (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LT_MEM(cr64,e,_a),LOG_TIE5("store32x2_vr_br_circI(0x%016llx,0x%x,0x%08x,%d,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,d,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_store32x2_vr_br_circI(a,b,(unsigned *)(c),d,e))
#define store32x1_vr_br_idxR(a,b,c,d,e)             (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE5("store32x1_vr_br_idxR(0x%016llx,0x%x,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,(unsigned)d,e),\
    _TIE_hemilite_common_tie_store32x1_vr_br_idxR(a,b,(unsigned *)(c),d,e))
#define store32x1_vr_br_idxI(a,b,c,d,e)             (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE5("store32x1_vr_br_idxI(0x%016llx,0x%x,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,d,e),\
    _TIE_hemilite_common_tie_store32x1_vr_br_idxI(a,b,(unsigned *)(c),d,e))
#define store32x1_vr_br_postR(a,b,c,d,e)            (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE5("store32x1_vr_br_postR(0x%016llx,0x%x,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,(unsigned)d,e),\
    _TIE_hemilite_common_tie_store32x1_vr_br_postR(a,b,(unsigned *)(c),d,e))
#define store32x1_vr_br_postI(a,b,c,d,e)            (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE5("store32x1_vr_br_postI(0x%016llx,0x%x,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,d,e),\
    _TIE_hemilite_common_tie_store32x1_vr_br_postI(a,b,(unsigned *)(c),d,e))
#define store32x1_vr_br_circI(a,b,c,d,e,f)          (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LT_MEM(cr64,e,_a),LOG_TIE6("store32x1_vr_br_circI(0x%016llx,0x%x,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,d,*(uint64_t*)&LTcr64_a,f),\
    _TIE_hemilite_common_tie_store32x1_vr_br_circI(a,b,(unsigned *)(c),d,e,f))
#define store32x2_vr_br_bdir(a,b,c,d)               (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE4("store32x2_vr_br_bdir(0x%016llx,0x%x,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,(unsigned)d),\
    _TIE_hemilite_common_tie_store32x2_vr_br_bdir(a,b,(unsigned *)(c),d))
#define store32x2_vr_br_brev(a,b,c,d)               (LT_MEM(vr64,a,_a),LT_MEM(atbool,b,_a),LOG_TIE4("store32x2_vr_br_brev(0x%016llx,0x%x,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(uint8_t)LTatbool_a,(unsigned)c,(unsigned)d),\
    _TIE_hemilite_common_tie_store32x2_vr_br_brev(a,b,(unsigned *)(c),d))
#define store16x2_vr_idxR(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("store16x2_vr_idxR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_store16x2_vr_idxR(a,(unsigned *)(b),c))
#define store16x2_vr_idxI(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("store16x2_vr_idxI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_store16x2_vr_idxI(a,(unsigned *)(b),c))
#define store16x2_vr_postR(a,b,c)                   (LT_MEM(vr64,a,_a),LOG_TIE3("store16x2_vr_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_store16x2_vr_postR(a,(unsigned *)(b),c))
#define store16x2_vr_postI(a,b,c)                   (LT_MEM(vr64,a,_a),LOG_TIE3("store16x2_vr_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_store16x2_vr_postI(a,(unsigned *)(b),c))
#define store16x2_vr_circI(a,b,c,d)                 (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE4("store16x2_vr_circI(0x%016llx,0x%08x,%d,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_store16x2_vr_circI(a,(unsigned *)(b),c,d))
#define store16x1_vr_idxR(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("store16x1_vr_idxR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store16x1_vr_idxR(a,(unsigned *)(b),c,d))
#define store16x1_vr_idxI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("store16x1_vr_idxI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_store16x1_vr_idxI(a,(unsigned *)(b),c,d))
#define store16x1_vr_postR(a,b,c,d)                 (LT_MEM(vr64,a,_a),LOG_TIE4("store16x1_vr_postR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store16x1_vr_postR(a,(unsigned *)(b),c,d))
#define store16x1_vr_postI(a,b,c,d)                 (LT_MEM(vr64,a,_a),LOG_TIE4("store16x1_vr_postI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_store16x1_vr_postI(a,(unsigned *)(b),c,d))
#define store16x1_vr_circI(a,b,c,d,e)               (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("store16x1_vr_circI(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_store16x1_vr_circI(a,(unsigned *)(b),c,d,e))
#define store8x2_vr_idxR(a,b,c)                     (LT_MEM(vr64,a,_a),LOG_TIE3("store8x2_vr_idxR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_store8x2_vr_idxR(a,(unsigned *)(b),c))
#define store8x2_vr_idxI(a,b,c)                     (LT_MEM(vr64,a,_a),LOG_TIE3("store8x2_vr_idxI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_store8x2_vr_idxI(a,(unsigned *)(b),c))
#define store8x2_vr_postR(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("store8x2_vr_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_store8x2_vr_postR(a,(unsigned *)(b),c))
#define store8x2_vr_postI(a,b,c)                    (LT_MEM(vr64,a,_a),LOG_TIE3("store8x2_vr_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_store8x2_vr_postI(a,(unsigned *)(b),c))
#define store8x2_vr_circI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE4("store8x2_vr_circI(0x%016llx,0x%08x,%d,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_store8x2_vr_circI(a,(unsigned *)(b),c,d))
#define store8x1_vr_idxR(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("store8x1_vr_idxR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store8x1_vr_idxR(a,(unsigned *)(b),c,d))
#define store8x1_vr_idxI(a,b,c,d)                   (LT_MEM(vr64,a,_a),LOG_TIE4("store8x1_vr_idxI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_store8x1_vr_idxI(a,(unsigned *)(b),c,d))
#define store8x1_vr_postR(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("store8x1_vr_postR(0x%016llx,0x%08x,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c,d),\
    _TIE_hemilite_common_tie_store8x1_vr_postR(a,(unsigned *)(b),c,d))
#define store8x1_vr_postI(a,b,c,d)                  (LT_MEM(vr64,a,_a),LOG_TIE4("store8x1_vr_postI(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_store8x1_vr_postI(a,(unsigned *)(b),c,d))
#define store8x1_vr_circI(a,b,c,d,e)                (LT_MEM(vr64,a,_a),LT_MEM(cr64,d,_a),LOG_TIE5("store8x1_vr_circI(0x%016llx,0x%08x,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,*(uint64_t*)&LTcr64_a,e),\
    _TIE_hemilite_common_tie_store8x1_vr_circI(a,(unsigned *)(b),c,d,e))
#define align_32x2_store(a)                         (LOG_TIE1("align_32x2_store(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_align_32x2_store((const unsigned *)(a)))
#define store_32x2_vr_a(a,b,c)                      (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LOG_TIE3("store_32x2_vr_a(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c),\
    _TIE_hemilite_common_tie_store_32x2_vr_a(a,b,(unsigned *)(c)))
#define store_24x2_vr_a(a,b,c)                      (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LOG_TIE3("store_24x2_vr_a(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c),\
    _TIE_hemilite_common_tie_store_24x2_vr_a(a,b,(unsigned *)(c)))
#define store_32x2_vr_a_circ(a,b,c,d)               (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LT_MEM(cr64,d,_a),LOG_TIE4("store_32x2_vr_a_circ(0x%016llx,0x%08x,0x%08x,0x%016llx)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c,*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_store_32x2_vr_a_circ(a,b,(unsigned *)(c),d))
#define flush_32x2(a,b)                             (LT_MEM(ulsr32,a,_a),LOG_TIE2("flush_32x2(0x%08x,0x%08x)\n",(unsigned)LTulsr32_a,(unsigned)b),\
    _TIE_hemilite_common_tie_flush_32x2(a,(unsigned *)(b)))
#define load_fr_postI(a,b,c)                        (LT_MEM(fr32,a,_a),LOG_TIE3("load_fr_postI(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_load_fr_postI(a,(const unsigned *)(b),c))
#define store_fr_postI(a,b,c)                       (LT_MEM(fr32,a,_a),LOG_TIE3("store_fr_postI(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_store_fr_postI(a,(unsigned *)(b),c))
#define brev_upd(a,b,c)                             (LT_MEM(atbool,a,_a),LOG_TIE3("brev_upd(0x%x,0x%08x,0x%08x)\n",(uint8_t)LTatbool_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_brev_upd(a,b,c))
#define brev_upd_ext(a,b)                           (LT_MEM(atbool,a,_a),LOG_TIE2("brev_upd_ext(0x%x,0x%08x)\n",(uint8_t)LTatbool_a,(unsigned)b),\
    _TIE_hemilite_common_tie_brev_upd_ext(a,b))
#define move32_ar_vr(a,b)                           (LT_MEM(vr64,a,_a),LOG_TIE2("move32_ar_vr(0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b),\
    _TIE_hemilite_common_tie_move32_ar_vr(a,b))
#define move32_vr_ar(a,b,c)                         (LT_MEM(vr64,a,_a),LOG_TIE3("move32_vr_ar(0x%016llx,%d,0x%08x)\n",*(uint64_t*)&LTvr64_a,b,(unsigned)c),\
    _TIE_hemilite_common_tie_move32_vr_ar(a,b,c))
#define move32_ar_vr_idx(a,b)                       (LT_MEM(vr64,a,_a),LOG_TIE2("move32_ar_vr_idx(0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b),\
    _TIE_hemilite_common_tie_move32_ar_vr_idx(a,b))
#define move32_fr_vr_idx(a,b)                       (LT_MEM(vr64,a,_a),LOG_TIE2("move32_fr_vr_idx(0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b),\
    _TIE_hemilite_common_tie_move32_fr_vr_idx(a,b))
#define move_fr_eqz(a,b,c)                          (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE3("move_fr_eqz(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c),\
    _TIE_hemilite_common_tie_move_fr_eqz(a,b,c))
#define move_fr_gez(a,b,c)                          (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE3("move_fr_gez(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c),\
    _TIE_hemilite_common_tie_move_fr_gez(a,b,c))
#define move_fr_gtz(a,b,c)                          (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE3("move_fr_gtz(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c),\
    _TIE_hemilite_common_tie_move_fr_gtz(a,b,c))
#define move_fr_lez(a,b,c)                          (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE3("move_fr_lez(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c),\
    _TIE_hemilite_common_tie_move_fr_lez(a,b,c))
#define move_fr_ltz(a,b,c)                          (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE3("move_fr_ltz(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c),\
    _TIE_hemilite_common_tie_move_fr_ltz(a,b,c))
#define move_fr_nez(a,b,c)                          (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE3("move_fr_nez(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c),\
    _TIE_hemilite_common_tie_move_fr_nez(a,b,c))
#define move_fr_sat(a,b,c)                          (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE3("move_fr_sat(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c),\
    _TIE_hemilite_common_tie_move_fr_sat(a,b,c))
#define move_fr_arnz(a,b,c)                         (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE3("move_fr_arnz(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)c),\
    _TIE_hemilite_common_tie_move_fr_arnz(a,b,c))
#define vmove_vr_eqz(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE3("vmove_vr_eqz(0x%016llx,0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c),\
    _TIE_hemilite_common_tie_vmove_vr_eqz(a,b,c))
#define vmove_vr_gez(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE3("vmove_vr_gez(0x%016llx,0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c),\
    _TIE_hemilite_common_tie_vmove_vr_gez(a,b,c))
#define vmove_vr_gtz(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE3("vmove_vr_gtz(0x%016llx,0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c),\
    _TIE_hemilite_common_tie_vmove_vr_gtz(a,b,c))
#define vmove_vr_lez(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE3("vmove_vr_lez(0x%016llx,0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c),\
    _TIE_hemilite_common_tie_vmove_vr_lez(a,b,c))
#define vmove_vr_ltz(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE3("vmove_vr_ltz(0x%016llx,0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c),\
    _TIE_hemilite_common_tie_vmove_vr_ltz(a,b,c))
#define vmove_vr_nez(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE3("vmove_vr_nez(0x%016llx,0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c),\
    _TIE_hemilite_common_tie_vmove_vr_nez(a,b,c))
#define vmove_vr_sat(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE3("vmove_vr_sat(0x%016llx,0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c),\
    _TIE_hemilite_common_tie_vmove_vr_sat(a,b,c))
#define replicate(a,b,c,d)                          (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("replicate(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_replicate(a,b,c,d))
#define replicate_ar(a,b,c)                         (LT_MEM(vr64,a,_a),LOG_TIE3("replicate_ar(0x%016llx,%d,0x%08x)\n",*(uint64_t*)&LTvr64_a,b,(unsigned)c),\
    _TIE_hemilite_common_tie_replicate_ar(a,b,c))
#define vreplicate(a,b)                             (LT_MEM(vr64,a,_a),LOG_TIE2("vreplicate(0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b),\
    _TIE_hemilite_common_tie_vreplicate(a,b))
#define vreplicate_fr(a)                            (LT_MEM(fr32,a,_a),LOG_TIE1("vreplicate_fr(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_vreplicate_fr(a))
#define convert_16I_to_32F_x1(a,b,c)                (LT_MEM(vr64,a,_a),LOG_TIE3("convert_16I_to_32F_x1(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_convert_16I_to_32F_x1(a,b,c))
#define convert_16I_to_32F_x2(a,b)                  (LT_MEM(vr64,a,_a),LOG_TIE2("convert_16I_to_32F_x2(0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b),\
    _TIE_hemilite_common_tie_convert_16I_to_32F_x2(a,b))
#define convert_32F_to_16I_x1(a,b,c,d)              (LT_MEM(vr64,a,_a),LOG_TIE4("convert_32F_to_16I_x1(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_convert_32F_to_16I_x1(a,b,c,d))
#define convert_32F_to_16I_x2(a,b,c)                (LT_MEM(vr64,a,_a),LOG_TIE3("convert_32F_to_16I_x2(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_convert_32F_to_16I_x2(a,b,c))
#define convert_32F_to_16F_x1(a,b,c,d,e,f)          (LT_MEM(vr64,a,_a),LOG_TIE6("convert_32F_to_16F_x1(0x%016llx,%d,%d,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,(unsigned)d,e,f),\
    _TIE_hemilite_common_tie_convert_32F_to_16F_x1(a,b,c,d,e,f))
#define convert_32F_to_16F_x2(a,b,c,d,e)            (LT_MEM(vr64,a,_a),LOG_TIE5("convert_32F_to_16F_x2(0x%016llx,%d,%d,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,b,c,(unsigned)d,e),\
    _TIE_hemilite_common_tie_convert_32F_to_16F_x2(a,b,c,d,e))
#define convert_16F_to_32F_x1(a,b,c,d,e)            (LT_MEM(vr64,a,_a),LOG_TIE5("convert_16F_to_32F_x1(0x%016llx,%d,%d,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,b,c,(unsigned)d,e),\
    _TIE_hemilite_common_tie_convert_16F_to_32F_x1(a,b,c,d,e))
#define convert_16F_to_32F_x2(a,b,c,d)              (LT_MEM(vr64,a,_a),LOG_TIE4("convert_16F_to_32F_x2(0x%016llx,%d,%d,0x%08x)\n",*(uint64_t*)&LTvr64_a,b,c,(unsigned)d),\
    _TIE_hemilite_common_tie_convert_16F_to_32F_x2(a,b,c,d))
#define convert_32I_to_32F_x1(a,b,c)                (LT_MEM(vr64,a,_a),LOG_TIE3("convert_32I_to_32F_x1(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_convert_32I_to_32F_x1(a,b,c))
#define convert_32F_to_32I_x1(a,b,c,d)              (LT_MEM(vr64,a,_a),LOG_TIE4("convert_32F_to_32I_x1(0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d),\
    _TIE_hemilite_common_tie_convert_32F_to_32I_x1(a,b,c,d))
#define convert_IEEE_float_to_32F_x2(a)             (LT_MEM(vr64,a,_a),LOG_TIE1("convert_IEEE_float_to_32F_x2(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_convert_IEEE_float_to_32F_x2(a))
#define convert_32F_to_IEEE_float_x2(a)             (LT_MEM(vr64,a,_a),LOG_TIE1("convert_32F_to_IEEE_float_x2(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_convert_32F_to_IEEE_float_x2(a))
#define convert_32I_to_64F(a)                       (LOG_TIE1("convert_32I_to_64F(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_convert_32I_to_64F(a))
#define convert_64F_to_32I(a,b)                     (LT_MEM(vr64,a,_a),LOG_TIE2("convert_64F_to_32I(0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b),\
    _TIE_hemilite_common_tie_convert_64F_to_32I(a,b))
#define convert_32F_to_64F(a)                       (LT_MEM(fr32,a,_a),LOG_TIE1("convert_32F_to_64F(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_convert_32F_to_64F(a))
#define convert_64F_to_32F(a)                       (LT_MEM(vr64,a,_a),LOG_TIE1("convert_64F_to_32F(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_convert_64F_to_32F(a))
#define convert_IEEE_double_to_64F(a)               (LT_MEM(vr64,a,_a),LOG_TIE1("convert_IEEE_double_to_64F(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_convert_IEEE_double_to_64F(a))
#define convert_64F_to_IEEE_double(a)               (LT_MEM(vr64,a,_a),LOG_TIE1("convert_64F_to_IEEE_double(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_convert_64F_to_IEEE_double(a))
#define vadd_perm(a,b,c,d,e,f)                      (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE6("vadd_perm(0x%016llx,0x%016llx,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c,d,e,f),\
    _TIE_hemilite_common_tie_vadd_perm(a,b,c,d,e,f))
#define vsum_perm(a,b,c,d,e,f,g)                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE7("vsum_perm(0x%016llx,0x%016llx,0x%016llx,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d,e,f,g),\
    _TIE_hemilite_common_tie_vsum_perm(a,b,c,d,e,f,g))
#define vmul_perm(a,b,c,d,e,f)                      (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE6("vmul_perm(0x%016llx,0x%016llx,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c,d,e,f),\
    _TIE_hemilite_common_tie_vmul_perm(a,b,c,d,e,f))
#define vmac_perm(a,b,c,d,e,f,g,h,i)                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE9("vmac_perm(0x%016llx,0x%016llx,0x%016llx,%d,%d,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d,e,f,g,h,i),\
    _TIE_hemilite_common_tie_vmac_perm(a,b,c,d,e,f,g,h,i))
#define vmac_boost(a,b,c,d,e,f,g)                   (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE7("vmac_boost(0x%016llx,0x%016llx,0x%016llx,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d,e,f,g),\
    _TIE_hemilite_common_tie_vmac_boost(a,b,c,d,e,f,g))
#define vblend(a,b,c,d,e,f)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE6("vblend(0x%016llx,0x%016llx,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c,d,e,f),\
    _TIE_hemilite_common_tie_vblend(a,b,c,d,e,f))
#define vblend_add(a,b,c,d,e,f,g,h,i)               (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE9("vblend_add(0x%016llx,0x%016llx,0x%016llx,%d,%d,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d,e,f,g,h,i),\
    _TIE_hemilite_common_tie_vblend_add(a,b,c,d,e,f,g,h,i))
#define vblend_boost(a,b,c,d,e,f,g)                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE7("vblend_boost(0x%016llx,0x%016llx,0x%016llx,%d,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d,e,f,g),\
    _TIE_hemilite_common_tie_vblend_boost(a,b,c,d,e,f,g))
#define fadds(a,b,c)                                (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE3("fadds(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,c),\
    _TIE_hemilite_common_tie_fadds(a,b,c))
#define fmuls(a,b,c)                                (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE3("fmuls(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,c),\
    _TIE_hemilite_common_tie_fmuls(a,b,c))
#define fmacs(a,b,c,d)                              (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LOG_TIE4("fmacs(0x%08x,0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c,d),\
    _TIE_hemilite_common_tie_fmacs(a,b,c,d))
#define dadds(a,b,c)                                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("dadds(0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c),\
    _TIE_hemilite_common_tie_dadds(a,b,c))
#define dmuls(a,b,c)                                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("dmuls(0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c),\
    _TIE_hemilite_common_tie_dmuls(a,b,c))
#define dmacs(a,b,c,d)                              (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE4("dmacs(0x%016llx,0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d),\
    _TIE_hemilite_common_tie_dmacs(a,b,c,d))
#define vadds(a,b,c)                                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("vadds(0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c),\
    _TIE_hemilite_common_tie_vadds(a,b,c))
#define vmuls(a,b,c)                                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("vmuls(0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c),\
    _TIE_hemilite_common_tie_vmuls(a,b,c))
#define vmacs(a,b,c,d,e)                            (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE5("vmacs(0x%016llx,0x%016llx,0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d,e),\
    _TIE_hemilite_common_tie_vmacs(a,b,c,d,e))
#define cmul(a,b,c)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("cmul(0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c),\
    _TIE_hemilite_common_tie_cmul(a,b,c))
#define cmac(a,b,c,d)                               (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE4("cmac(0x%016llx,0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d),\
    _TIE_hemilite_common_tie_cmac(a,b,c,d))
#define cmas(a,b,c,d)                               (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LOG_TIE4("cmas(0x%016llx,0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,d),\
    _TIE_hemilite_common_tie_cmas(a,b,c,d))
#define vmulf(a,b,c)                                (LT_MEM(vr64,a,_a),LT_MEM(fr32,b,_a),LOG_TIE3("vmulf(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTfr32_a,c),\
    _TIE_hemilite_common_tie_vmulf(a,b,c))
#define vmacf(a,b,c,d,e)                            (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(fr32,c,_a),LOG_TIE5("vmacf(0x%016llx,0x%016llx,0x%08x,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,(unsigned)LTfr32_a,d,e),\
    _TIE_hemilite_common_tie_vmacf(a,b,c,d,e))
#define vabs(a)                                     (LT_MEM(vr64,a,_a),LOG_TIE1("vabs(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_vabs(a))
#define vexp_adj(a,b)                               (LT_MEM(vr64,a,_a),LOG_TIE2("vexp_adj(0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b),\
    _TIE_hemilite_common_tie_vexp_adj(a,b))
#define vexp_adji(a,b)                              (LT_MEM(vr64,a,_a),LOG_TIE2("vexp_adji(0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b),\
    _TIE_hemilite_common_tie_vexp_adji(a,b))
#define vpermi(a,b,c)                               (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("vpermi(0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c),\
    _TIE_hemilite_common_tie_vpermi(a,b,c))
#define seta_vr(a,b,c,d)                            (LT_MEM(vr64,a,_a),LOG_TIE4("seta_vr(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_seta_vr(a,b,c,d))
#define vseta_vr(a,b)                               (LOG_TIE2("vseta_vr(%d,%d)\n",a,b),\
    _TIE_hemilite_common_tie_vseta_vr(a,b))
#define seta_ar(a,b)                                (LOG_TIE2("seta_ar(%d,%d)\n",a,b),\
    _TIE_hemilite_common_tie_seta_ar(a,b))
#define seta_fr(a,b)                                (LOG_TIE2("seta_fr(%d,%d)\n",a,b),\
    _TIE_hemilite_common_tie_seta_fr(a,b))
#define load_AccExtend_postI(a,b)                   (LOG_TIE2("load_AccExtend_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_AccExtend_postI((const unsigned *)(a),b))
#define load32x1_vr_idx16vr(a,b,c,d)                (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("load32x1_vr_idx16vr(0x%016llx,0x%08x,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_load32x1_vr_idx16vr(a,(const unsigned *)(b),c,d))
#define load_BB0_postI(a,b)                         (LOG_TIE2("load_BB0_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_BB0_postI((const unsigned *)(a),b))
#define load_BB1_postI(a,b)                         (LOG_TIE2("load_BB1_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_BB1_postI((const unsigned *)(a),b))
#define load_BB2_postI(a,b)                         (LOG_TIE2("load_BB2_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_BB2_postI((const unsigned *)(a),b))
#define load_BB3_postI(a,b)                         (LOG_TIE2("load_BB3_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_BB3_postI((const unsigned *)(a),b))
#define load_VB1_postI(a,b)                         (LOG_TIE2("load_VB1_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_VB1_postI((const unsigned *)(a),b))
#define load_VB2_postI(a,b)                         (LOG_TIE2("load_VB2_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_VB2_postI((const unsigned *)(a),b))
#define load_VB3_postI(a,b)                         (LOG_TIE2("load_VB3_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_VB3_postI((const unsigned *)(a),b))
#define load_VB4_postI(a,b)                         (LOG_TIE2("load_VB4_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_VB4_postI((const unsigned *)(a),b))
#define load_VB5_postI(a,b)                         (LOG_TIE2("load_VB5_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_VB5_postI((const unsigned *)(a),b))
#define load_VB6_postI(a,b)                         (LOG_TIE2("load_VB6_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_VB6_postI((const unsigned *)(a),b))
#define load_VB7_postI(a,b)                         (LOG_TIE2("load_VB7_postI(0x%08x,%d)\n",(const unsigned *)a,b),\
    _TIE_hemilite_common_tie_load_VB7_postI((const unsigned *)(a),b))
#define load_32x2_vr_a_bounded(a,b,c,d)             (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LT_MEM(mir18,d,_a),LOG_TIE4("load_32x2_vr_a_bounded(0x%016llx,0x%08x,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_load_32x2_vr_a_bounded(a,b,(const unsigned *)(c),d))
#define load_BBx_VB67_a_bounded(a,b,c,d)            (LT_MEM(ulsr32,a,_a),LT_MEM(mir18,c,_a),LOG_TIE4("load_BBx_VB67_a_bounded(0x%08x,0x%08x,0x%08x,0x%08x)\n",(unsigned)LTulsr32_a,(unsigned)b,*(unsigned*)&LTmir18_a,(unsigned)d),\
    _TIE_hemilite_common_tie_load_BBx_VB67_a_bounded(a,(const unsigned *)(b),c,d))
#define flush_32x2_bounded(a,b,c)                   (LT_MEM(ulsr32,a,_a),LT_MEM(mir18,c,_a),LOG_TIE3("flush_32x2_bounded(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTulsr32_a,(unsigned)b,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_flush_32x2_bounded(a,(unsigned *)(b),c))
#define store_32x2_vr_a_bounded(a,b,c,d)            (LT_MEM(vr64,a,_a),LT_MEM(ulsr32,b,_a),LT_MEM(mir18,d,_a),LOG_TIE4("store_32x2_vr_a_bounded(0x%016llx,0x%08x,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTulsr32_a,(unsigned)c,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_store_32x2_vr_a_bounded(a,b,(unsigned *)(c),d))
#define store_AccExtend_postI(a,b)                  (LOG_TIE2("store_AccExtend_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_AccExtend_postI((unsigned *)(a),b))
#define store_BB0_postI(a,b)                        (LOG_TIE2("store_BB0_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_BB0_postI((unsigned *)(a),b))
#define store_BB1_postI(a,b)                        (LOG_TIE2("store_BB1_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_BB1_postI((unsigned *)(a),b))
#define store_BB2_postI(a,b)                        (LOG_TIE2("store_BB2_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_BB2_postI((unsigned *)(a),b))
#define store_BB3_postI(a,b)                        (LOG_TIE2("store_BB3_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_BB3_postI((unsigned *)(a),b))
#define store_VB1_postI(a,b)                        (LOG_TIE2("store_VB1_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_VB1_postI((unsigned *)(a),b))
#define store_VB2_postI(a,b)                        (LOG_TIE2("store_VB2_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_VB2_postI((unsigned *)(a),b))
#define store_VB3_postI(a,b)                        (LOG_TIE2("store_VB3_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_VB3_postI((unsigned *)(a),b))
#define store_VB4_postI(a,b)                        (LOG_TIE2("store_VB4_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_VB4_postI((unsigned *)(a),b))
#define store_VB5_postI(a,b)                        (LOG_TIE2("store_VB5_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_VB5_postI((unsigned *)(a),b))
#define store_VB6_postI(a,b)                        (LOG_TIE2("store_VB6_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_VB6_postI((unsigned *)(a),b))
#define store_VB7_postI(a,b)                        (LOG_TIE2("store_VB7_postI(0x%08x,%d)\n",(unsigned *)a,b),\
    _TIE_hemilite_common_tie_store_VB7_postI((unsigned *)(a),b))
#define afloat_exp_extract(a)                       (LT_MEM(vr64,a,_a),LOG_TIE1("afloat_exp_extract(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_afloat_exp_extract(a))
#define mov_AccExtend_vr(a)                         (LT_MEM(vr64,a,_a),LOG_TIE1("mov_AccExtend_vr(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_mov_AccExtend_vr(a))
#define mov_vr_AccExtend()                          (LOG_TIE0("mov_vr_AccExtend()\n"),\
    _TIE_hemilite_common_tie_mov_vr_AccExtend())
#define mov_BB_VB67_to_vrVB_VB45()                  (LOG_TIE0("mov_BB_VB67_to_vrVB_VB45()\n"),\
    _TIE_hemilite_common_tie_mov_BB_VB67_to_vrVB_VB45())
#define mov_vrVB_VB45_to_BB_VB67(a)                 (LT_MEM(vr64,a,_a),LOG_TIE1("mov_vrVB_VB45_to_BB_VB67(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_mov_vrVB_VB45_to_BB_VB67(a))
#define precess_16bits(a,b)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("precess_16bits(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_precess_16bits(a,b))
#define set_BB_vrVB67_zero()                        (LOG_TIE0("set_BB_vrVB67_zero()\n"),\
    _TIE_hemilite_common_tie_set_BB_vrVB67_zero())
#define exp_shift_amount(a,b)                       (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("exp_shift_amount(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_exp_shift_amount(a,b))
#define rnd_sat_pack(a,b,c,d,e)                     (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LT_MEM(vr64,d,_c),LT_MEM(atbool,e,_a),LOG_TIE5("rnd_sat_pack(0x%016llx,%d,0x%016llx,0x%016llx,0x%x)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_rnd_sat_pack(a,b,c,d,e))
#define rectify32_into8(a,b,c,d,e,f)                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE6("rectify32_into8(0x%016llx,0x%016llx,0x%08x,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,(unsigned)c,d,e,f),\
    _TIE_hemilite_common_tie_rectify32_into8(a,b,c,d,e,f))
#define shift8_into32_arith(a,b,c,d,e)              (LT_MEM(vr64,a,_a),LOG_TIE5("shift8_into32_arith(0x%016llx,0x%08x,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c,d,e),\
    _TIE_hemilite_common_tie_shift8_into32_arith(a,b,c,d,e))
#define shift32_arith(a,b,c)                        (LT_MEM(vr64,a,_a),LOG_TIE3("shift32_arith(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_shift32_arith(a,b,c))
#define mac8bx8b(a,b,c,d)                           (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LT_MEM(atbool,d,_a),LOG_TIE4("mac8bx8b(0x%016llx,0x%016llx,0x%016llx,0x%x)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_mac8bx8b(a,b,c,d))
#define mac8bx8b_sparse(a,b,c,d)                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(vr64,c,_c),LT_MEM(atbool,d,_a),LOG_TIE4("mac8bx8b_sparse(0x%016llx,0x%016llx,0x%016llx,0x%x)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_mac8bx8b_sparse(a,b,c,d))
#define mac8bx8b_conv(a,b,c,d)                      (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(atbool,c,_a),LOG_TIE4("mac8bx8b_conv(0x%016llx,0x%016llx,0x%x,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,(uint8_t)LTatbool_a,d),\
    _TIE_hemilite_common_tie_mac8bx8b_conv(a,b,c,d))
#define mir_init(a)                                 (LOG_TIE1("mir_init(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_mir_init(a))
#define f_abs(a,b,c,d)                              (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("f_abs(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_f_abs(a,b,c,d))
#define fclamp(a,b,c,d,e,f)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LT_MEM(vr64,e,_c),LOG_TIE6("fclamp(0x%016llx,%d,0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d,*(uint64_t*)&LTvr64_c,f),\
    _TIE_hemilite_common_tie_fclamp(a,b,c,d,e,f))
#define fclamp_bp(a,b,c,d,e,f)                      (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LT_MEM(vr64,e,_c),LOG_TIE6("fclamp_bp(0x%016llx,%d,0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d,*(uint64_t*)&LTvr64_c,f),\
    _TIE_hemilite_common_tie_fclamp_bp(a,b,c,d,e,f))
#define fclamp_one(a,b,c,d)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("fclamp_one(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_fclamp_one(a,b,c,d))
#define fmax(a,b,c,d,e,f)                           (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LT_MEM(vr64,e,_c),LOG_TIE6("fmax(0x%016llx,%d,0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d,*(uint64_t*)&LTvr64_c,f),\
    _TIE_hemilite_common_tie_fmax(a,b,c,d,e,f))
#define fmin(a,b,c,d,e,f)                           (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LT_MEM(vr64,e,_c),LOG_TIE6("fmin(0x%016llx,%d,0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d,*(uint64_t*)&LTvr64_c,f),\
    _TIE_hemilite_common_tie_fmin(a,b,c,d,e,f))
#define max_fr(a,b)                                 (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("max_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_max_fr(a,b))
#define min_fr(a,b)                                 (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("min_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_min_fr(a,b))
#define log2(a)                                     (LT_MEM(fr32,a,_a),LOG_TIE1("log2(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_log2(a))
#define pow2(a)                                     (LT_MEM(fr32,a,_a),LOG_TIE1("pow2(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_pow2(a))
#define sigmoid(a)                                  (LT_MEM(fr32,a,_a),LOG_TIE1("sigmoid(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_sigmoid(a))
#define inv(a)                                      (LT_MEM(fr32,a,_a),LOG_TIE1("inv(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_inv(a))
#define ratio(a,b,c,d)                              (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LT_MEM(atbool,d,_a),LOG_TIE4("ratio(0x%08x,0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_ratio(a,b,c,d))
#define atanratio(a,b)                              (LT_MEM(fr32,a,_a),LT_MEM(atbool,b,_a),LOG_TIE2("atanratio(0x%08x,0x%x)\n",(unsigned)LTfr32_a,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_atanratio(a,b))
#define invsqrt(a)                                  (LT_MEM(fr32,a,_a),LOG_TIE1("invsqrt(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_invsqrt(a))
#define sine(a)                                     (LT_MEM(fr32,a,_a),LOG_TIE1("sine(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_sine(a))
#define cosine(a)                                   (LT_MEM(fr32,a,_a),LOG_TIE1("cosine(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_cosine(a))
#define log2mul(a,b,c,d)                            (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(fr32,c,_c),LT_MEM(atbool,d,_a),LOG_TIE4("log2mul(0x%08x,0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)LTfr32_c,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_log2mul(a,b,c,d))
#define cspow2(a,b)                                 (LT_MEM(fr32,a,_a),LT_MEM(atbool,b,_a),LOG_TIE2("cspow2(0x%08x,0x%x)\n",(unsigned)LTfr32_a,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_cspow2(a,b))
#define comp(a,b,c,d)                               (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("comp(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_comp(a,b,c,d))
#define eq(a,b,c,d)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("eq(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_eq(a,b,c,d))
#define ge(a,b,c,d)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("ge(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_ge(a,b,c,d))
#define gt(a,b,c,d)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("gt(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_gt(a,b,c,d))
#define le(a,b,c,d)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("le(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_le(a,b,c,d))
#define lt(a,b,c,d)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("lt(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_lt(a,b,c,d))
#define ne(a,b,c,d)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE4("ne(0x%016llx,%d,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d),\
    _TIE_hemilite_common_tie_ne(a,b,c,d))
#define comp_const(a,b,c,d)                         (LT_MEM(vr64,a,_a),LOG_TIE4("comp_const(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_comp_const(a,b,c,d))
#define eq_const(a,b,c,d)                           (LT_MEM(vr64,a,_a),LOG_TIE4("eq_const(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_eq_const(a,b,c,d))
#define ge_const(a,b,c,d)                           (LT_MEM(vr64,a,_a),LOG_TIE4("ge_const(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_ge_const(a,b,c,d))
#define gt_const(a,b,c,d)                           (LT_MEM(vr64,a,_a),LOG_TIE4("gt_const(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_gt_const(a,b,c,d))
#define le_const(a,b,c,d)                           (LT_MEM(vr64,a,_a),LOG_TIE4("le_const(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_le_const(a,b,c,d))
#define lt_const(a,b,c,d)                           (LT_MEM(vr64,a,_a),LOG_TIE4("lt_const(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_lt_const(a,b,c,d))
#define ne_const(a,b,c,d)                           (LT_MEM(vr64,a,_a),LOG_TIE4("ne_const(0x%016llx,%d,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c,d),\
    _TIE_hemilite_common_tie_ne_const(a,b,c,d))
#define comp_fr(a,b)                                (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("comp_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_comp_fr(a,b))
#define eq_fr(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("eq_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_eq_fr(a,b))
#define ge_fr(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("ge_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_ge_fr(a,b))
#define gt_fr(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("gt_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_gt_fr(a,b))
#define le_fr(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("le_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_le_fr(a,b))
#define lt_fr(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("lt_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_lt_fr(a,b))
#define ne_fr(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("ne_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_ne_fr(a,b))
#define neg_fr(a)                                   (LT_MEM(fr32,a,_a),LOG_TIE1("neg_fr(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_neg_fr(a))
#define abs_fr(a)                                   (LT_MEM(fr32,a,_a),LOG_TIE1("abs_fr(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_abs_fr(a))
#define deqz(a)                                     (LT_MEM(vr64,a,_a),LOG_TIE1("deqz(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_deqz(a))
#define dgez(a)                                     (LT_MEM(vr64,a,_a),LOG_TIE1("dgez(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_dgez(a))
#define dgtz(a)                                     (LT_MEM(vr64,a,_a),LOG_TIE1("dgtz(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_dgtz(a))
#define dlez(a)                                     (LT_MEM(vr64,a,_a),LOG_TIE1("dlez(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_dlez(a))
#define dltz(a)                                     (LT_MEM(vr64,a,_a),LOG_TIE1("dltz(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_dltz(a))
#define dnez(a)                                     (LT_MEM(vr64,a,_a),LOG_TIE1("dnez(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_dnez(a))
#define veq(a,b)                                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("veq(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_veq(a,b))
#define vge(a,b)                                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("vge(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_vge(a,b))
#define vgt(a,b)                                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("vgt(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_vgt(a,b))
#define vle(a,b)                                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("vle(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_vle(a,b))
#define vlt(a,b)                                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("vlt(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_vlt(a,b))
#define vne(a,b)                                    (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("vne(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_vne(a,b))
#define veq_const(a,b,c)                            (LT_MEM(vr64,a,_a),LOG_TIE3("veq_const(0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c),\
    _TIE_hemilite_common_tie_veq_const(a,b,c))
#define vge_const(a,b,c)                            (LT_MEM(vr64,a,_a),LOG_TIE3("vge_const(0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c),\
    _TIE_hemilite_common_tie_vge_const(a,b,c))
#define vgt_const(a,b,c)                            (LT_MEM(vr64,a,_a),LOG_TIE3("vgt_const(0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c),\
    _TIE_hemilite_common_tie_vgt_const(a,b,c))
#define vle_const(a,b,c)                            (LT_MEM(vr64,a,_a),LOG_TIE3("vle_const(0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c),\
    _TIE_hemilite_common_tie_vle_const(a,b,c))
#define vlt_const(a,b,c)                            (LT_MEM(vr64,a,_a),LOG_TIE3("vlt_const(0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c),\
    _TIE_hemilite_common_tie_vlt_const(a,b,c))
#define vne_const(a,b,c)                            (LT_MEM(vr64,a,_a),LOG_TIE3("vne_const(0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,c),\
    _TIE_hemilite_common_tie_vne_const(a,b,c))
#define sel_1b2(a,b,c,d)                            (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(atbool,c,_a),LOG_TIE4("sel_1b2(0x%08x,0x%08x,0x%x,%d)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(uint8_t)LTatbool_a,d),\
    _TIE_hemilite_common_tie_sel_1b2(a,b,c,d))
#define sel_eq(a,b,c)                               (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(atbool,c,_a),LOG_TIE3("sel_eq(0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_sel_eq(a,b,c))
#define sel_ge(a,b,c)                               (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(atbool,c,_a),LOG_TIE3("sel_ge(0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_sel_ge(a,b,c))
#define sel_gt(a,b,c)                               (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(atbool,c,_a),LOG_TIE3("sel_gt(0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_sel_gt(a,b,c))
#define sel_le(a,b,c)                               (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(atbool,c,_a),LOG_TIE3("sel_le(0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_sel_le(a,b,c))
#define sel_lt(a,b,c)                               (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(atbool,c,_a),LOG_TIE3("sel_lt(0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_sel_lt(a,b,c))
#define sel_ne(a,b,c)                               (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LT_MEM(atbool,c,_a),LOG_TIE3("sel_ne(0x%08x,0x%08x,0x%x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_sel_ne(a,b,c))
#define sel_ar(a,b,c)                               (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE3("sel_ar(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b,(unsigned)c),\
    _TIE_hemilite_common_tie_sel_ar(a,b,c))
#define vsel(a,b,c)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(atbool,c,_a),LOG_TIE3("vsel(0x%016llx,0x%016llx,0x%x)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_vsel(a,b,c))
#define vsel_ar(a,b,c)                              (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("vsel_ar(0x%016llx,0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,(unsigned)c),\
    _TIE_hemilite_common_tie_vsel_ar(a,b,c))
#define andb2(a,b)                                  (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("andb2(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_andb2(a,b))
#define andbc2(a,b)                                 (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("andbc2(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_andbc2(a,b))
#define orb2(a,b)                                   (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("orb2(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_orb2(a,b))
#define orbc2(a,b)                                  (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("orbc2(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_orbc2(a,b))
#define xorb2(a,b)                                  (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("xorb2(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_xorb2(a,b))
#define bcount0_maskI(a,b)                          (LT_MEM(atbool,a,_a),LOG_TIE2("bcount0_maskI(0x%x,%d)\n",(uint8_t)LTatbool_a,b),\
    _TIE_hemilite_common_tie_bcount0_maskI(a,b))
#define bcount0_maskR(a,b)                          (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("bcount0_maskR(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_bcount0_maskR(a,b))
#define bcount1_maskI(a,b)                          (LT_MEM(atbool,a,_a),LOG_TIE2("bcount1_maskI(0x%x,%d)\n",(uint8_t)LTatbool_a,b),\
    _TIE_hemilite_common_tie_bcount1_maskI(a,b))
#define bcount1_maskR(a,b)                          (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("bcount1_maskR(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_bcount1_maskR(a,b))
#define bfirst0_maskI(a,b)                          (LT_MEM(atbool,a,_a),LOG_TIE2("bfirst0_maskI(0x%x,%d)\n",(uint8_t)LTatbool_a,b),\
    _TIE_hemilite_common_tie_bfirst0_maskI(a,b))
#define bfirst0_maskR(a,b)                          (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("bfirst0_maskR(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_bfirst0_maskR(a,b))
#define bfirst1_maskI(a,b)                          (LT_MEM(atbool,a,_a),LOG_TIE2("bfirst1_maskI(0x%x,%d)\n",(uint8_t)LTatbool_a,b),\
    _TIE_hemilite_common_tie_bfirst1_maskI(a,b))
#define bfirst1_maskR(a,b)                          (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("bfirst1_maskR(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_bfirst1_maskR(a,b))
#define blast0_maskI(a,b)                           (LT_MEM(atbool,a,_a),LOG_TIE2("blast0_maskI(0x%x,%d)\n",(uint8_t)LTatbool_a,b),\
    _TIE_hemilite_common_tie_blast0_maskI(a,b))
#define blast0_maskR(a,b)                           (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("blast0_maskR(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_blast0_maskR(a,b))
#define blast1_maskI(a,b)                           (LT_MEM(atbool,a,_a),LOG_TIE2("blast1_maskI(0x%x,%d)\n",(uint8_t)LTatbool_a,b),\
    _TIE_hemilite_common_tie_blast1_maskI(a,b))
#define blast1_maskR(a,b)                           (LT_MEM(atbool,a,_a),LT_MEM(atbool,b,_b),LOG_TIE2("blast1_maskR(0x%x,0x%x)\n",(uint8_t)LTatbool_a,(uint8_t)LTatbool_b),\
    _TIE_hemilite_common_tie_blast1_maskR(a,b))
#define bgetI(a,b)                                  (LT_MEM(atbool,a,_a),LOG_TIE2("bgetI(0x%x,%d)\n",(uint8_t)LTatbool_a,b),\
    _TIE_hemilite_common_tie_bgetI(a,b))
#define bgetR(a,b)                                  (LT_MEM(atbool,a,_a),LOG_TIE2("bgetR(0x%x,0x%08x)\n",(uint8_t)LTatbool_a,(unsigned)b),\
    _TIE_hemilite_common_tie_bgetR(a,b)
#define bsetI(a,b,c)                                (LT_MEM(atbool,a,_a),LOG_TIE3("bsetI(0x%x,0x%08x,%d)\n",(uint8_t)LTatbool_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_bsetI(a,b,c))
#define bsetR(a,b,c)                                (LT_MEM(atbool,a,_a),LOG_TIE3("bsetR(0x%x,0x%08x,0x%08x)\n",(uint8_t)LTatbool_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_bsetR(a,b,c))
#define exp_adj(a,b,c,d,e)                          (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE5("exp_adj(0x%016llx,%d,0x%016llx,%d,0x%08x)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d,(unsigned)e),\
    _TIE_hemilite_common_tie_exp_adj(a,b,c,d,e))
#define exp_adji(a,b,c,d,e)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,c,_b),LOG_TIE5("exp_adji(0x%016llx,%d,0x%016llx,%d,%d)\n",*(uint64_t*)&LTvr64_a,b,*(uint64_t*)&LTvr64_b,d,e),\
    _TIE_hemilite_common_tie_exp_adji(a,b,c,d,e))
#define exp_adj_fr(a,b)                             (LT_MEM(fr32,a,_a),LOG_TIE2("exp_adj_fr(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)b),\
    _TIE_hemilite_common_tie_exp_adj_fr(a,b))
#define exp_adji_fr(a,b)                            (LT_MEM(fr32,a,_a),LOG_TIE2("exp_adji_fr(0x%08x,%d)\n",(unsigned)LTfr32_a,b),\
    _TIE_hemilite_common_tie_exp_adji_fr(a,b))
#define s_neg(a)                                    (LT_MEM(fr32,a,_a),LOG_TIE1("s_neg(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_s_neg(a))
#define s_copy(a,b)                                 (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("s_copy(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_s_copy(a,b))
#define s_and(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("s_and(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_s_and(a,b))
#define s_andc(a,b)                                 (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("s_andc(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_s_andc(a,b))
#define s_or(a,b)                                   (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("s_or(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_s_or(a,b))
#define s_orc(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("s_orc(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_s_orc(a,b))
#define s_xor(a,b)                                  (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("s_xor(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_s_xor(a,b))
#define s_vneg(a)                                   (LT_MEM(vr64,a,_a),LOG_TIE1("s_vneg(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_s_vneg(a))
#define s_vcopy(a,b)                                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("s_vcopy(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_s_vcopy(a,b))
#define s_vand(a,b)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("s_vand(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_s_vand(a,b))
#define s_vandc(a,b)                                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("s_vandc(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_s_vandc(a,b))
#define s_vor(a,b)                                  (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("s_vor(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_s_vor(a,b))
#define s_vorc(a,b)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("s_vorc(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_s_vorc(a,b))
#define s_vxor(a,b)                                 (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("s_vxor(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_s_vxor(a,b))
#define floorp_frac(a,b,c,d,e,f)                    (LT_MEM(vr64,b,_a),LT_MEM(vr64,d,_b),LOG_TIE6("floorp_frac(0x%08x,0x%016llx,%d,0x%016llx,%d,%d)\n",(unsigned)a,*(uint64_t*)&LTvr64_a,c,*(uint64_t*)&LTvr64_b,e,f),\
    _TIE_hemilite_common_tie_floorp_frac(a,b,c,d,e,f))
#define idx_frac(a,b,c,d,e)                         (LT_MEM(vr64,b,_a),LOG_TIE5("idx_frac(0x%08x,0x%016llx,%d,0x%08x,%d)\n",(unsigned)a,*(uint64_t*)&LTvr64_a,c,(unsigned)d,e),\
    _TIE_hemilite_common_tie_idx_frac(a,b,c,d,e))
#define rmax_idx(a,b,c,d)                           (LT_MEM(fr32,b,_a),LT_MEM(vr64,c,_a),LT_MEM(mir18,d,_a),LOG_TIE4("rmax_idx(0x%08x,0x%08x,0x%016llx,0x%08x)\n",(unsigned)a,(unsigned)LTfr32_a,*(uint64_t*)&LTvr64_a,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_rmax_idx(a,b,c,d))
#define rmin_idx(a,b,c,d)                           (LT_MEM(fr32,b,_a),LT_MEM(vr64,c,_a),LT_MEM(mir18,d,_a),LOG_TIE4("rmin_idx(0x%08x,0x%08x,0x%016llx,0x%08x)\n",(unsigned)a,(unsigned)LTfr32_a,*(uint64_t*)&LTvr64_a,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_rmin_idx(a,b,c,d))
#define vmaxmin_init(a,b,c)                         (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(mir18,c,_a),LOG_TIE3("vmaxmin_init(0x%016llx,0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_vmaxmin_init(a,b,c))
#define vmax_idx(a,b,c)                             (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(mir18,c,_a),LOG_TIE3("vmax_idx(0x%016llx,0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_vmax_idx(a,b,c))
#define vmin_idx(a,b,c)                             (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LT_MEM(mir18,c,_a),LOG_TIE3("vmin_idx(0x%016llx,0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_vmin_idx(a,b,c))
#define vmax(a,b)                                   (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("vmax(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_vmax(a,b))
#define vmin(a,b)                                   (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE2("vmin(0x%016llx,0x%016llx)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_vmin(a,b))
#define sortupd_asc_vr(a,b,c,d,e)                   (LT_MEM(vr64,b,_a),LT_MEM(vr64,c,_b),LT_MEM(vr64,d,_c),LOG_TIE5("sortupd_asc_vr(0x%08x,0x%016llx,0x%016llx,0x%016llx,%d)\n",(unsigned)a,*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,e),\
    _TIE_hemilite_common_tie_sortupd_asc_vr(a,b,c,d,e))
#define sortupd_des_vr(a,b,c,d,e)                   (LT_MEM(vr64,b,_a),LT_MEM(vr64,c,_b),LT_MEM(vr64,d,_c),LOG_TIE5("sortupd_des_vr(0x%08x,0x%016llx,0x%016llx,0x%016llx,%d)\n",(unsigned)a,*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,*(uint64_t*)&LTvr64_c,e),\
    _TIE_hemilite_common_tie_sortupd_des_vr(a,b,c,d,e))
#define sortupd_asc_ar(a,b,c)                       (LT_MEM(vr64,b,_a),LT_MEM(vr64,c,_b),LOG_TIE3("sortupd_asc_ar(0x%08x,0x%016llx,0x%016llx)\n",(unsigned)a,*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_sortupd_asc_ar(a,b,c))
#define sortupd_des_ar(a,b,c)                       (LT_MEM(vr64,b,_a),LT_MEM(vr64,c,_b),LOG_TIE3("sortupd_des_ar(0x%08x,0x%016llx,0x%016llx)\n",(unsigned)a,*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b),\
    _TIE_hemilite_common_tie_sortupd_des_ar(a,b,c))
#define vbool(a,b,c)                                (LT_MEM(vr64,a,_a),LT_MEM(vr64,b,_b),LOG_TIE3("vbool(0x%016llx,0x%016llx,%d)\n",*(uint64_t*)&LTvr64_a,*(uint64_t*)&LTvr64_b,c),\
    _TIE_hemilite_common_tie_vbool(a,b,c))
#define align_up(a,b)                               (LOG_TIE2("align_up(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_align_up(a,b))
#define mv_MIR(a)                                   (LT_MEM(mir18,a,_a),LOG_TIE1("mv_MIR(0x%08x)\n",*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_mv_MIR(a))
#define mir18_move(a)                               (LT_MEM(mir18,a,_a),LOG_TIE1("mir18_move(0x%08x)\n",*(unsigned*)&LTmir18_a),\
    _TIE_hemilite_common_tie_mir18_move(a))
#define mv_ULSR(a)                                  (LT_MEM(ulsr32,a,_a),LOG_TIE1("mv_ULSR(0x%08x)\n",(unsigned)LTulsr32_a),\
    _TIE_hemilite_common_tie_mv_ULSR(a))
#define ulsr32_move(a)                              (LT_MEM(ulsr32,a,_a),LOG_TIE1("ulsr32_move(0x%08x)\n",(unsigned)LTulsr32_a),\
    _TIE_hemilite_common_tie_ulsr32_move(a))
#define mv_CR(a)                                    (LT_MEM(cr64,a,_a),LOG_TIE1("mv_CR(0x%016llx)\n",*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_mv_CR(a))
#define cr64_move(a)                                (LT_MEM(cr64,a,_a),LOG_TIE1("cr64_move(0x%016llx)\n",*(uint64_t*)&LTcr64_a),\
    _TIE_hemilite_common_tie_cr64_move(a))
#define ld_FR(a,b)                                  (LOG_TIE2("ld_FR(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_ld_FR((const fr32 *)(a),b))
#define st_FR(a,b,c)                                (LT_MEM(fr32,a,_a),LOG_TIE3("st_FR(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_FR(a,(fr32 *)(b),c))
#define ld_FR_idxR(a,b)                             (LOG_TIE2("ld_FR_idxR(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_ld_FR_idxR((const fr32 *)(a),b))
#define st_FR_idxR(a,b,c)                           (LT_MEM(fr32,a,_a),LOG_TIE3("st_FR_idxR(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_st_FR_idxR(a,(fr32 *)(b),c))
#define ld_FR_postI(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("ld_FR_postI(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_ld_FR_postI(a,(const fr32 *)(b),c))
#define st_FR_postI(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("st_FR_postI(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_FR_postI(a,(fr32 *)(b),c))
#define ld_FR_postR(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("ld_FR_postR(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_ld_FR_postR(a,(const fr32 *)(b),c))
#define st_FR_postR(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("st_FR_postR(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_st_FR_postR(a,(fr32 *)(b),c))
#define ld_VR(a,b)                                  (LOG_TIE2("ld_VR(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_ld_VR((const vr64 *)(a),b))
#define st_VR(a,b,c)                                (LT_MEM(vr64,a,_a),LOG_TIE3("st_VR(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_VR(a,(vr64 *)(b),c))
#define ld_VR_idxR(a,b)                             (LOG_TIE2("ld_VR_idxR(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_ld_VR_idxR((const vr64 *)(a),b))
#define st_VR_idxR(a,b,c)                           (LT_MEM(vr64,a,_a),LOG_TIE3("st_VR_idxR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_st_VR_idxR(a,(vr64 *)(b),c))
#define ld_VR_postI(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("ld_VR_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_ld_VR_postI(a,(const vr64 *)(b),c))
#define st_VR_postI(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("st_VR_postI(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_st_VR_postI(a,(vr64 *)(b),c))
#define ld_VR_postR(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("ld_VR_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_ld_VR_postR(a,(const vr64 *)(b),c))
#define st_VR_postR(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("st_VR_postR(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_st_VR_postR(a,(vr64 *)(b),c))
#define mv_FR(a)                                    (LT_MEM(fr32,a,_a),LOG_TIE1("mv_FR(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_mv_FR(a))
#define move_ar_fr(a)                               (LT_MEM(fr32,a,_a),LOG_TIE1("move_ar_fr(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_move_ar_fr(a))
#define move_fr_ar(a)                               (LOG_TIE1("move_fr_ar(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_move_fr_ar(a))
#define fr32_move(a)                                (LT_MEM(fr32,a,_a),LOG_TIE1("fr32_move(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_fr32_move(a))
#define fr32_loadi(a,b)                             (LOG_TIE2("fr32_loadi(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_fr32_loadi((const fr32 *)(a),b))
#define fr32_storei(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("fr32_storei(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_fr32_storei(a,(fr32 *)(b),c))
#define fr32_loadx(a,b)                             (LOG_TIE2("fr32_loadx(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_fr32_loadx((const fr32 *)(a),b))
#define fr32_storex(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("fr32_storex(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_fr32_storex(a,(fr32 *)(b),c))
#define fr32_loadip(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("fr32_loadip(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_fr32_loadip(a,(const fr32 *)(b),c))
#define fr32_storeip(a,b,c)                         (LT_MEM(fr32,a,_a),LOG_TIE3("fr32_storeip(0x%08x,0x%08x,%d)\n",(unsigned)LTfr32_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_fr32_storeip(a,(fr32 *)(b),c))
#define fr32_loadxp(a,b,c)                          (LT_MEM(fr32,a,_a),LOG_TIE3("fr32_loadxp(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_fr32_loadxp(a,(const fr32 *)(b),c))
#define fr32_storexp(a,b,c)                         (LT_MEM(fr32,a,_a),LOG_TIE3("fr32_storexp(0x%08x,0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_fr32_storexp(a,(fr32 *)(b),c))
#define fr32_rtor_int32(a)                          (LT_MEM(fr32,a,_a),LOG_TIE1("fr32_rtor_int32(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_fr32_rtor_int32(a))
#define fr32_rtor_uint32(a)                         (LT_MEM(fr32,a,_a),LOG_TIE1("fr32_rtor_uint32(0x%08x)\n",(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_fr32_rtor_uint32(a))
#define int32_rtor_fr32(a)                          (LOG_TIE1("int32_rtor_fr32(%d)\n",a),\
    _TIE_hemilite_common_tie_int32_rtor_fr32(a))
#define uint32_rtor_fr32(a)                         (LOG_TIE1("uint32_rtor_fr32(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_uint32_rtor_fr32(a))
#define mv_VR(a)                                    (LT_MEM(vr64,a,_a),LOG_TIE1("mv_VR(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_mv_VR(a))
#define vr64_move(a)                                (LT_MEM(vr64,a,_a),LOG_TIE1("vr64_move(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_vr64_move(a))
#define vr64_loadi(a,b)                             (LOG_TIE2("vr64_loadi(0x%08x,%d)\n",(unsigned)a,b),\
    _TIE_hemilite_common_tie_vr64_loadi((const vr64 *)(a),b))
#define vr64_storei(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("vr64_storei(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_vr64_storei(a,(vr64 *)(b),c))
#define vr64_loadx(a,b)                             (LOG_TIE2("vr64_loadx(0x%08x,0x%08x)\n",(unsigned)a,(unsigned)b),\
    _TIE_hemilite_common_tie_vr64_loadx((const vr64 *)(a),b))
#define vr64_storex(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("vr64_storex(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_vr64_storex(a,(vr64 *)(b),c))
#define vr64_loadip(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("vr64_loadip(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_vr64_loadip(a,(const vr64 *)(b),c))
#define vr64_storeip(a,b,c)                         (LT_MEM(vr64,a,_a),LOG_TIE3("vr64_storeip(0x%016llx,0x%08x,%d)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,c),\
    _TIE_hemilite_common_tie_vr64_storeip(a,(vr64 *)(b),c))
#define vr64_loadxp(a,b,c)                          (LT_MEM(vr64,a,_a),LOG_TIE3("vr64_loadxp(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_vr64_loadxp(a,(const vr64 *)(b),c))
#define vr64_storexp(a,b,c)                         (LT_MEM(vr64,a,_a),LOG_TIE3("vr64_storexp(0x%016llx,0x%08x,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)b,(unsigned)c),\
    _TIE_hemilite_common_tie_vr64_storexp(a,(vr64 *)(b),c))
#define get_VRH(a)                                  (LT_MEM(vr64,a,_a),LOG_TIE1("get_VRH(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_get_VRH(a))
#define get_VRL(a)                                  (LT_MEM(vr64,a,_a),LOG_TIE1("get_VRL(0x%016llx)\n",*(uint64_t*)&LTvr64_a),\
    _TIE_hemilite_common_tie_get_VRL(a))
#define set_VRH(a,b)                                (LT_MEM(vr64,a,_a),LT_MEM(fr32,b,_a),LOG_TIE2("set_VRH(0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_set_VRH(a,b))
#define set_VRL(a,b)                                (LT_MEM(vr64,a,_a),LT_MEM(fr32,b,_a),LOG_TIE2("set_VRL(0x%016llx,0x%08x)\n",*(uint64_t*)&LTvr64_a,(unsigned)LTfr32_a),\
    _TIE_hemilite_common_tie_set_VRL(a,b))
#define vr64_pair(a,b)                              (LT_MEM(fr32,a,_a),LT_MEM(fr32,b,_b),LOG_TIE2("vr64_pair(0x%08x,0x%08x)\n",(unsigned)LTfr32_a,(unsigned)LTfr32_b),\
    _TIE_hemilite_common_tie_vr64_pair(a,b))
#define move_ar_bbr(a)                              (LT_MEM(atbool,a,_a),LOG_TIE1("move_ar_bbr(0x%x)\n",(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_move_ar_bbr(a))
#define move_bbr_ar(a)                              (LOG_TIE1("move_bbr_ar(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_move_bbr_ar(a))
#define shift_from_bbr(a,b)                         (LT_MEM(atbool,b,_a),LOG_TIE2("shift_from_bbr(0x%08x,0x%x)\n",(unsigned)a,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_shift_from_bbr(a,b))
#define shift_to_bbr(a,b)                           (LT_MEM(atbool,b,_a),LOG_TIE2("shift_to_bbr(0x%08x,0x%x)\n",(unsigned)a,(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_shift_to_bbr(a,b))
#define atbool_rtor_int32(a)                        (LT_MEM(atbool,a,_a),LOG_TIE1("atbool_rtor_int32(0x%x)\n",(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_atbool_rtor_int32(a))
#define atbool_rtor_uint32(a)                       (LT_MEM(atbool,a,_a),LOG_TIE1("atbool_rtor_uint32(0x%x)\n",(uint8_t)LTatbool_a),\
    _TIE_hemilite_common_tie_atbool_rtor_uint32(a))
#define int32_rtor_atbool(a)                        (LOG_TIE1("int32_rtor_atbool(%d)\n",a),\
    _TIE_hemilite_common_tie_int32_rtor_atbool(a))
#define uint32_rtor_atbool(a)                       (LOG_TIE1("uint32_rtor_atbool(0x%08x)\n",(unsigned)a),\
    _TIE_hemilite_common_tie_uint32_rtor_atbool(a))
#define dma_ld(a)                                   (LOG_TIE1("dma_ld(0x%08x)\n",(const unsigned *)a),\
    _TIE_hemilite_common_tie_dma_ld((const unsigned *)(a)))
#define dma_align_ld(a,b)                           (LOG_TIE2("dma_align_ld(0x%08x,0x%08x)\n",(const unsigned *)a,(const unsigned *)b),\
    _TIE_hemilite_common_tie_dma_align_ld((const unsigned *)(a),(const unsigned *)(b)))
#define dma_ldu(a)                                  (LOG_TIE1("dma_ldu(0x%08x)\n",(const unsigned *)a),\
    _TIE_hemilite_common_tie_dma_ldu((const unsigned *)(a)))
#define dma_flush_ld(a,b)                           (LOG_TIE2("dma_flush_ld(0x%08x,0x%08x)\n",(const unsigned *)a,(const unsigned *)b),\
    _TIE_hemilite_common_tie_dma_flush_ld((const unsigned *)(a),(const unsigned *)(b)))
#define dma_st(a,b)                                 (LOG_TIE2("dma_st(0x%08x,0x%08x)\n",(unsigned *)a,(unsigned *)b),\
    _TIE_hemilite_common_tie_dma_st((unsigned *)(a),(unsigned *)(b)))
#define dma_align_st(a,b)                           (LOG_TIE2("dma_align_st(0x%08x,0x%08x)\n",(unsigned *)a,(unsigned *)b),\
    _TIE_hemilite_common_tie_dma_align_st((unsigned *)(a),(unsigned *)(b)))
#define dma_stu(a,b)                                (LOG_TIE2("dma_stu(0x%08x,0x%08x)\n",(unsigned *)a,(unsigned *)b),\
    _TIE_hemilite_common_tie_dma_stu((unsigned *)(a),(unsigned *)(b)))
#define dma_flush_st(a,b)                           (LOG_TIE2("dma_flush_st(0x%08x,0x%08x)\n",(unsigned *)a,(unsigned *)b),\
    _TIE_hemilite_common_tie_dma_flush_st((unsigned *)(a),(unsigned *)(b)))
#define dma_buf_save(a)                             (LOG_TIE1("dma_buf_save(0x%08x)\n",(unsigned *)a),\
    _TIE_hemilite_common_tie_dma_buf_save((unsigned *)(a)))

#endif //TIE_INCLUDE_H
