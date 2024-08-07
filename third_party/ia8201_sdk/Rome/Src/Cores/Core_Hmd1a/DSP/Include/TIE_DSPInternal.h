/************************************************************************//**
 * @file
 *
 * @brief   Delta instruction compatability macros
 *
 * $DateTime: 2021/03/09 09:01:05 $
 * $Revision: #1 $
 *
 * @copyright Copyright ? 2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_TIE_DSPINTERNAL_H__
#define __FILE_TIE_DSPINTERNAL_H__

/****************************************************************************
 * Defines
 ****************************************************************************/
// Convenience macros

//#define vadds(x,y,s)      vadd_perm(x,y,VMAC_H,VMAC_L,s,0)
//#define vmidp(x, y, s) vadd_perm(x, y, VMAC_H, VMAC_L, s, 1)
//#define vmuls(x,y,s)      vmul_perm(x,y,VMAC_H,VMAC_L,VMAC_SIGNS(s),0)
//#define vmacs(z,x,y,s)    vmac_perm(z,x,y,VMAC_H,VMAC_L,VMAC_SIGNS(s),VMAC_SIGNZ(s),0,0)

//#define vmuls_perm(x,y,s,p)   vmul_perm(x,y,(p)>>2,(p)&3,VMAC_SIGNS(s),0)
//#define vmacs_perm(z,x,y,s,p) vmac_perm(z,x,y,(p)>>2,(p)&3,VMAC_SIGNS(s),VMAC_SIGNZ(s),0,0)
#define vmuls_perm(x, y, s, p) vmul_perm(x, y, (p) >> 2, (p)&3, s, 0)
#define vmacs_perm(z, x, y, s, p) vmac_perm(z, x, y, (p) >> 2, (p)&3, (s)&3, (s) >> 2, 0, 0)

//#define cmul(x,y,m)       vblend(x,y,CMAC_H,CMAC_L,CMAC_SIGNS^CMAC_CONJ(m),0)
//#define cmac(z,x,y,m)     vblend_add(z,x,y,CMAC_H,CMAC_L,CMAC_SIGNS^CMAC_CONJ(m),0,0,0)
//#define cmas(z,x,y,m)     vblend_add(z,x,y,CMAC_H,CMAC_L,CMAS_SIGNS^CMAC_CONJ(m),0,0,0)

#define dsums(x, y, s, d) vadd_perm(x, y, VSEL_YH_YL, VSEL_XH_XL, s, d)

//#define fadds(z,ez,x,ex,y,ey,s) z=vadd_perm(x,y,FMAC_H(ez,ex,ey),FMAC_L(ez,ex,ey),FADD_SIGNS(ez,s),0);
//#define fmuls(z,ez,x,ex,y,ey,s) z=vmul_perm(x,y,FMAC_H(ez,ex,ey),FMAC_L(ez,ex,ey),FMUL_SIGNS(ez,s),0);
//#define fmacs(z,ez,x,ex,y,ey,s) z=vmac_perm(z,x,y,FMAC_H(ez,ex,ey),FMAC_L(ez,ex,ey),FMUL_SIGNS(ez,s),FMAC_SIGNZ(ez,s),0,0);

#define align_24x2_load(p) align_32x2_load(p)
#define align_24x2_store(p) align_32x2_store(p)
#define flush_24x2(u, p) flush_32x2(u, p)

// Delta instruction compatability macros

#define fadd(x, y) fadds(x, y, 0)
#define fsub(x, y) fadds(x, y, 2)
#define fmul(x, y) fmuls(x, y, 0)
#define fmac(z, x, y) fmacs(z, x, y, 0)
#define fmas(z, x, y) fmacs(z, x, y, 1)
#define set_vr(z, s, i) seta_vr(z, s, i, 0)
#define vadd(x, y) vadds(x, y, 0)
#define vsub(x, y) vadds(x, y, 0xA)
#define vmul(x, y) vmuls(x, y, 0)
#define vmac(z, x, y) z = vmacs(z, x, y, 0, 0)
#define vmas(z, x, y) z = vmacs(z, x, y, 3, 0)
#define vset_vr(i) vseta_vr(i, 0)

#define load32x2_vr_circ(z, a, c, s) load32x2_vr_circI(z, a, INC1_CIRC, c, s)
#define load32x1_vr_circ(z, a, c, s) load32x1_vr_circI(z, a, INC1_CIRC, c, s)
#define load16x2_vr_circ(z, a, c, s) load16x2_vr_circI(z, a, INC1_CIRC, c, s)
#define load16x1_vr_circ(z, a, c, s) load16x1_vr_circI(z, a, INC1_CIRC, c, s)
#define load8x2_vr_circ(z, a, c, s) load8x2_vr_circI(z, a, INC1_CIRC, c, s)
#define load8x1_vr_circ(z, a, c, s) load8x1_vr_circI(z, a, INC1_CIRC, c, s)

#define store32x2_vr_circ(z, a, c, s) store32x2_vr_circI(z, a, INC1_CIRC, c, s)
#define store32x1_vr_circ(z, a, c, s) store32x1_vr_circI(z, a, INC1_CIRC, c, s)
#define store16x2_vr_circ(z, a, c, s) store16x2_vr_circI(z, a, INC1_CIRC, c, s)
#define store16x1_vr_circ(z, a, c, s) store16x1_vr_circI(z, a, INC1_CIRC, c, s)
#define store8x2_vr_circ(z, a, c, s) store8x2_vr_circI(z, a, INC1_CIRC, c, s)
#define store8x1_vr_circ(z, a, c, s) store8x1_vr_circI(z, a, INC1_CIRC, c, s)



#endif /* __FILE_TIE_DSPINTERNAL_H__ */



/* End of File */

