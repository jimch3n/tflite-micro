/************************************************************************//**
 * File: TIE_defs.h
 *
 * Description: Defines to be used with TIE instructions
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
#ifndef __FILE_TIE_DEFS_H__
#define __FILE_TIE_DEFS_H__

// Load/Store Address Modes

#define IDX           0
#define POST          1

// Load/Store IDX offsets
#define MIDDLE_4_ELEM 1
#define SHIFT_RIGHT_1_MAC_CONV 9 // This is a 4 bit value 0x1101. 01 is to select X.1 and 11 is to select Y.0
typedef enum
{
    IDX0 = 0,
    IDX1,
    IDX2,
    IDX3,
    IDX_IMM_N
} IDX_IMM_t;

// Load/Store POST offsets

typedef enum
{
    DEC2 = 0,
    DEC1,
    INC1,
    INC2,
    POST_IMM_N
} POST_IMM_t;

typedef enum
{
    INC1_CIRC = 0,
    DEC1_CIRC,
    CIRC_IMM_N
} CIRC_IMM_t;

// vr64 half-register selects
typedef enum
{
    VRQ0 = 0,
    VRQ1,
    VR_LEN
} REG_ELEM_t;

typedef enum
{
    ELEM_HALF0 = 0,
    ELEM_HALF1,
    ELEM_HALF
} ELEM_HALF_t;

typedef enum
{
    CONJ_NONE = 0,
    CONJ_X,
    CONJ_Y,
    CONJ_X_Y
} CONJ_SPEC_t;

typedef enum
{
    TRUNCATING = 0,
    JAMMING
} JAMMING_t;

typedef enum
{
    VSEL_YL_XL = 0,
    VSEL_YL_XH,
    VSEL_YH_XL,
    VSEL_YH_XH,

    VSEL_XL_XL,
    VSEL_XH_XH,
    VSEL_YL_YL,
    VSEL_YH_YH,

    VSEL____XL,
    VSEL____XH,
    VSEL____YL,
    VSEL____YH,

    VSEL_XH_XL,
    VSEL_YH_YL,
    VSEL_RESERVED,
    VSEL_ZERO
} VSEL_t;

typedef enum
{
    VB_YHXH_YLXL = 0,
    VB_YHXH_YLXH,
    VB_YLXH_YLXL,
    VB_YHXL_YLXH,

    VB_YLYL_XLXL,
    VB_YLYL_XHXH,
    VB_YHYH_XLXL,
    VB_YHYH_XHXH,

    VB_YHYH_YLYL,
    VB_XHXH_XLXL,
    VB_YLXH_XHXH,
    VB_YHXL_XLXL,

    VB_YHXH_YHXL,
    VB_YHXL_YLXL,
    VB_YHYL_XYXL,
    VB_ZERO
} VB_SEL_t;

#define VMAC_H VSEL_YH_XH
#define VMAC_L VSEL_YL_XL
#define VMAC_SIGNS(S) (((S)&1) + ((S)&4)/2)
#define VMAC_SIGNZ(S) (((S)&2)/2 + ((S)&8)/4)

#define CMAC_H VB_YHXL_YLXH
#define CMAC_L VB_YHXH_YLXL
#define CMAC_SIGNS 0x2
#define CMAS_SIGNS (0xF & ~CMAC_SIGNS)
#define CMAC_CONJ(CONJ) (((CONJ) & CONJ_X ? 0x6 : 0) ^ ((CONJ) & CONJ_Y ? 0xa : 0))

#define FMAC_H(EZ,EX,EY)  ((EZ) ? 2*(EY) + (EX) : VSEL_ZERO)
#define FMAC_L(EZ,EX,EY)  ((EZ) ? VSEL_ZERO : 2*(EY) + (EX))
#define FADD_SIGNS(EZ,S)  ((S) << (2*(EZ)))
#define FMUL_SIGNS(EZ,S)  (((S)&1) << (EZ))
#define FMAC_SIGNZ(EZ,S)  (((S)>>1) << (EZ))

//#ifndef USE_SIM

// Convenience macros

//#define vadds(x,y,s)      vadd_perm(x,y,VMAC_H,VMAC_L,s,0)
#define vmidp(x,y,s)      vadd_perm(x,y,VMAC_H,VMAC_L,s,1)
//#define vmuls(x,y,s)      vmul_perm(x,y,VMAC_H,VMAC_L,VMAC_SIGNS(s),0)
//#define vmacs(z,x,y,s)    vmac_perm(z,x,y,VMAC_H,VMAC_L,VMAC_SIGNS(s),VMAC_SIGNZ(s),0,0)

//#define vmuls_perm(x,y,s,p)   vmul_perm(x,y,(p)>>2,(p)&3,VMAC_SIGNS(s),0)
//#define vmacs_perm(z,x,y,s,p) vmac_perm(z,x,y,(p)>>2,(p)&3,VMAC_SIGNS(s),VMAC_SIGNZ(s),0,0)
#define vmuls_perm(x,y,s,p)   vmul_perm(x,y,(p)>>2,(p)&3,s,0)
#define vmacs_perm(z,x,y,s,p) vmac_perm(z,x,y,(p)>>2,(p)&3,(s)&3,(s)>>2,0,0)

//#define cmul(x,y,m)       vblend(x,y,CMAC_H,CMAC_L,CMAC_SIGNS^CMAC_CONJ(m),0)
//#define cmac(z,x,y,m)     vblend_add(z,x,y,CMAC_H,CMAC_L,CMAC_SIGNS^CMAC_CONJ(m),0,0,0)
//#define cmas(z,x,y,m)     vblend_add(z,x,y,CMAC_H,CMAC_L,CMAS_SIGNS^CMAC_CONJ(m),0,0,0)

#define dsums(x,y,s,d)    vadd_perm(x,y,VSEL_YH_YL,VSEL_XH_XL,s,d)

//#define fadds(z,ez,x,ex,y,ey,s) z=vadd_perm(x,y,FMAC_H(ez,ex,ey),FMAC_L(ez,ex,ey),FADD_SIGNS(ez,s),0);
//#define fmuls(z,ez,x,ex,y,ey,s) z=vmul_perm(x,y,FMAC_H(ez,ex,ey),FMAC_L(ez,ex,ey),FMUL_SIGNS(ez,s),0);
//#define fmacs(z,ez,x,ex,y,ey,s) z=vmac_perm(z,x,y,FMAC_H(ez,ex,ey),FMAC_L(ez,ex,ey),FMUL_SIGNS(ez,s),FMAC_SIGNZ(ez,s),0,0);

#define align_24x2_load(p)    align_32x2_load(p)
#define align_24x2_store(p)   align_32x2_store(p)
#define flush_24x2(u,p)       flush_32x2(u,p)

// Delta instruction compatability macros

#define fadd(x,y)            fadds(x,y,0)
#define fsub(x,y)            fadds(x,y,2)
#define fmul(x,y)            fmuls(x,y,0)
#define fmac(z,x,y)          fmacs(z,x,y,0)
#define fmas(z,x,y)          fmacs(z,x,y,1)
#define set_vr(z,s,i)        seta_vr(z,s,i,0)
#define vadd(x,y)            vadds(x,y,0)
#define vsub(x,y)            vadds(x,y,0xA)
#define vmul(x,y)            vmuls(x,y,0)
#define vmac(z,x,y)          z=vmacs(z,x,y,0,0)
#define vmas(z,x,y)          z=vmacs(z,x,y,3,0)
#define vset_vr(i)           vseta_vr(i,0)

#define load32x2_vr_circ(z,a,c,s)	load32x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load32x1_vr_circ(z,a,c,s)	load32x1_vr_circI(z,a,INC1_CIRC,c,s)
#define load16x2_vr_circ(z,a,c,s)	load16x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load16x1_vr_circ(z,a,c,s)	load16x1_vr_circI(z,a,INC1_CIRC,c,s)
#define load8x2_vr_circ(z,a,c,s)	load8x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load8x1_vr_circ(z,a,c,s)	load8x1_vr_circI(z,a,INC1_CIRC,c,s)

#define store32x2_vr_circ(z,a,c,s)	store32x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store32x1_vr_circ(z,a,c,s)	store32x1_vr_circI(z,a,INC1_CIRC,c,s)
#define store16x2_vr_circ(z,a,c,s)	store16x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store16x1_vr_circ(z,a,c,s)	store16x1_vr_circI(z,a,INC1_CIRC,c,s)
#define store8x2_vr_circ(z,a,c,s)	store8x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store8x1_vr_circ(z,a,c,s)	store8x1_vr_circI(z,a,INC1_CIRC,c,s)

//#endif //!USE_SIM

#endif
