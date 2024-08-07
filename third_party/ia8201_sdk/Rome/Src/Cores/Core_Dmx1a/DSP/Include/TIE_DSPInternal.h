/************************************************************************//**
 * @file
 *
 * @brief   Delta instruction compatability macros
 *
 * $DateTime: 2021/03/09 09:01:05 $
 * $Revision: #1 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_TIE_DSPINTERNAL_H__
#define __FILE_TIE_DSPINTERNAL_H__

/****************************************************************************
 * Defines
 ****************************************************************************/
#define fadd(z,ez,x,ex,y,ey) fadds(z,ez,x,ex,y,ey,0)
#define fsub(z,ez,x,ex,y,ey) fadds(z,ez,x,ex,y,ey,0x10)
#define fmul(z,ez,x,ex,y,ey) fmuls(z,ez,x,ex,y,ey,0)
#define fmac(z,ez,x,ex,y,ey) fmacs(z,ez,x,ex,y,ey,0)
#define fmas(z,ez,x,ex,y,ey) fmacs(z,ez,x,ex,y,ey,1)

#define csum_L(z,x,d2)       csums_L(z,x,0,d2)
#define csum_H(z,x,d2)       csums_H(z,x,0,d2)
#define dsum_L(z,x,d2)       dsums_L(z,x,0,d2)
#define dsum_H(z,x,d2)       dsums_H(z,x,0,d2)
#define set_vr(z,s,i)        seta_vr(z,s,i,0,0)
#define vadd(x,y)            vadds(x,y,0)
#define vsub(x,y)            vadds(x,y,0xf0)
#define vmul(x,y)            vmuls(x,y,0)
#define vmac(z,x,y)          z=vmacs_adj(z,x,y,0,0)
#define vmas(z,x,y)          z=vmacs_adj(z,x,y,0xf,0)
#define vmacs(z,x,y,s)       vmacs_adj(z,x,y,s,0)
#define vmul_perm(x,y,p)     vmuls_perm(x,y,0,p)
#define vmac_perm(z,x,y,p)   z=vmacs_perm(z,x,y,0,p)
#define vmas_perm(z,x,y,p)   z=vmacs_perm(z,x,y,0xf,p)
#define vset_vr(i)           vseta_vr(i,0,0)
#define vpermi(x,y,p)        vpermsi(x,y,0,p)
#define s_vneg(x)            s_vnegs(x,0xf)

#define affine_L(z,x,y,s)    affine_adj_L(z,x,y,s,0)
#define affine_H(z,x,y,s)    affine_adj_H(z,x,y,s,0)
#define linear_L(z,x,y,s)    linear_adj_L(z,x,y,s,0)
#define linear_H(z,x,y,s)    linear_adj_H(z,x,y,s,0)
#define cmac_x2(z,x,y,m)     cmac_adj_x2(z,x,y,m,0)
#define cmas_x2(z,x,y,m)     cmas_adj_x2(z,x,y,m,0)

#define load32x4_vr_idxR_perm(z,a,o,p)  z=load32x4_vr_idxR_perm_vr(z,a,o,p)
#define load32x4_vr_idxI_perm(z,a,o,p)  z=load32x4_vr_idxI_perm_vr(z,a,o,p)
#define load32x4_vr_postR_perm(z,a,o,p) load32x4_vr_postR_perm_vr(z,z,a,o,p)
#define load32x4_vr_postI_perm(z,a,o,p) load32x4_vr_postI_perm_vr(z,z,a,o,p)
#define load32x4_vr_circ_perm(z,a,o,p)  load32x4_vr_circI_perm_vr(z,z,a,INC1_CIRC,o,p)
#define load32x2_vr_idxR_perm(z,a,o,p)  z=load32x2_vr_idxR_perm_vr(z,a,o,p)
#define load32x2_vr_idxI_perm(z,a,o,p)  z=load32x2_vr_idxI_perm_vr(z,a,o,p)
#define load32x2_vr_postR_perm(z,a,o,p) load32x2_vr_postR_perm_vr(z,z,a,o,p)
#define load32x2_vr_postI_perm(z,a,o,p) load32x2_vr_postI_perm_vr(z,z,a,o,p)
#define load32x2_vr_circ_perm(z,a,o,p)  load32x2_vr_circI_perm_vr(z,z,a,INC1_CIRC,o,p)
#define load32x1_vr_idxR_perm(z,a,o,p)  z=load32x1_vr_idxR_perm_vr(z,a,o,p)
#define load32x1_vr_idxI_perm(z,a,o,p)  z=load32x1_vr_idxI_perm_vr(z,a,o,p)
#define load32x1_vr_postR_perm(z,a,o,p) load32x1_vr_postR_perm_vr(z,z,a,o,p)
#define load32x1_vr_postI_perm(z,a,o,p) load32x1_vr_postI_perm_vr(z,z,a,o,p)
#define load32x1_vr_circ_perm(z,a,o,p)  load32x1_vr_circI_perm_vr(z,z,a,INC1_CIRC,o,p)

#define load32x4_vr_circ(z,a,c)     load32x4_vr_circI(z,a,INC1_CIRC,c)
#define load32x2_vr_circ(z,a,c,s)   load32x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load32x1_vr_circ(z,a,c,s)   load32x1_vr_circI(z,a,INC1_CIRC,c,s)
#define load16x4_vr_circ(z,a,c)     load16x4_vr_circI(z,a,INC1_CIRC,c)
#define load16x2_vr_circ(z,a,c,s)   load16x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load16x1_vr_circ(z,a,c,s)   load16x1_vr_circI(z,a,INC1_CIRC,c,s)
#define load8x4_vr_circ(z,a,c)      load8x4_vr_circI(z,a,INC1_CIRC,c)
#define load8x2_vr_circ(z,a,c,s)    load8x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load8x1_vr_circ(z,a,c,s)    load8x1_vr_circI(z,a,INC1_CIRC,c,s)

#define store32x4_vr_vr_circ_perm(z,y,a,c,s) store32x4_vr_vr_circI_perm(z,y,a,INC1_CIRC,c,s)
#define store32x4_vr_circ(z,a,c)    store32x4_vr_circI(z,a,INC1_CIRC,c)
#define store32x2_vr_circ(z,a,c,s)  store32x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store32x1_vr_circ(z,a,c,s)  store32x1_vr_circI(z,a,INC1_CIRC,c,s)
#define store16x4_vr_circ(z,a,c)    store16x4_vr_circI(z,a,INC1_CIRC,c)
#define store16x2_vr_circ(z,a,c,s)  store16x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store16x1_vr_circ(z,a,c,s)  store16x1_vr_circI(z,a,INC1_CIRC,c,s)
#define store8x4_vr_circ(z,a,c)     store8x4_vr_circI(z,a,INC1_CIRC,c)
#define store8x2_vr_circ(z,a,c,s)   store8x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store8x1_vr_circ(z,a,c,s)   store8x1_vr_circI(z,a,INC1_CIRC,c,s)

#define align_24x4_store(p)         align_32x4_store(p)

#define move32_vr_ar(z,ez,a)        replicate_ar(z,1<<(ez),a)

#endif /* __FILE_TIE_DSPINTERNAL_H__ */



/* End of File */

