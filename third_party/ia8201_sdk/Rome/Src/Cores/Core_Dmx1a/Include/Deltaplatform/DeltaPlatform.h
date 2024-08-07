#ifndef __DELTA_PLATFORM_H__
#define __DELTA_PLATFORM_H__

#include <stdint.h>
#include <stdbool.h>
#ifdef __XTENSA__
#include "TIE_include.h"
#else
#include "cstubs.h"
#endif
#include "TIE_defs.h"

// NOTE: Taken from //AudEngr/AlgoSW/Common/Infrastructure/Xtensa/DeltaTypes.h #2
typedef short              SHORT_t;
typedef unsigned short     USHORT_t;
typedef int                INT_t;
typedef unsigned int       UINT_t;
typedef long long          INT64_t;
typedef unsigned long long UINT64_t;
typedef signed char        CHAR_t;
typedef unsigned char      UCHAR_t;

// NOTE: Taken from //AudEngr/AlgoSW/Common/Infrastructure/Xtensa/Dmx1a/TIE_defs.h #1
#define SHR_BY_1_ELEM 0
#define SHR_BY_2_ELEM 1
#define SHL_BY_1_ELEM 2
#define EVEN_ODD_ELEM 3
#define ODD_EVEN_ELEM 4
#define MIDDLE_4_ELEM 1
#define LOW_HIGH_ELEM 5
#define ALL_HIGH_ELEM 6
#define ALL_LOW__ELEM 7

// NOTE: Taken from //AudEngr/AlgoSW/Common/Infrastructure/Xtensa/Dmx1a/TIE_defs.h #1
// Delta instruction compatability macros
//#ifndef USE_SIM

#ifdef EMULATE_OLD_SCALAR_OPS
#define SCALAR_SIGNS(S) (((S)&1) + ((S)&16)/8)
#define fadds(Z,EZ,X,EX,Y,EY,S) set_##EZ(Z, fpadd(get_##EX(X), get_##EY(Y), SCALAR_SIGNS(S)))
#define fmuls(Z,EZ,X,EX,Y,EY,S) set_##EZ(Z, fpmul(get_##EX(X), get_##EY(Y), SCALAR_SIGNS(S)))
#define fmacs(Z,EZ,X,EX,Y,EY,S) {vr32 _frr = get_##EZ(Z); \
                                 fpmac(_frr, get_##EX(X), get_##EY(Y), SCALAR_SIGNS(S)); \
                                 set_##EZ(Z, _frr);}
#define fmul_sum3(Z,EZ,X,Y,S,P) set_##EZ(Z, fpmul_sum3(X, Y, S, P))
#endif

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

#define load32x4_vr_circ(z,a,c)		load32x4_vr_circI(z,a,INC1_CIRC,c)
#define load32x2_vr_circ(z,a,c,s)	load32x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load32x1_vr_circ(z,a,c,s)	load32x1_vr_circI(z,a,INC1_CIRC,c,s)
#define load16x4_vr_circ(z,a,c)		load16x4_vr_circI(z,a,INC1_CIRC,c)
#define load16x2_vr_circ(z,a,c,s)	load16x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load16x1_vr_circ(z,a,c,s)	load16x1_vr_circI(z,a,INC1_CIRC,c,s)
#define load8x4_vr_circ(z,a,c)		load8x4_vr_circI(z,a,INC1_CIRC,c)
#define load8x2_vr_circ(z,a,c,s)	load8x2_vr_circI(z,a,INC1_CIRC,c,s)
#define load8x1_vr_circ(z,a,c,s)	load8x1_vr_circI(z,a,INC1_CIRC,c,s)

#define store32x4_vr_vr_circ_perm(z,y,a,c,s) store32x4_vr_vr_circI_perm(z,y,a,INC1_CIRC,c,s)
#define store32x4_vr_circ(z,a,c)	store32x4_vr_circI(z,a,INC1_CIRC,c)
#define store32x2_vr_circ(z,a,c,s)	store32x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store32x1_vr_circ(z,a,c,s)	store32x1_vr_circI(z,a,INC1_CIRC,c,s)
#define store16x4_vr_circ(z,a,c)	store16x4_vr_circI(z,a,INC1_CIRC,c)
#define store16x2_vr_circ(z,a,c,s)	store16x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store16x1_vr_circ(z,a,c,s)	store16x1_vr_circI(z,a,INC1_CIRC,c,s)
#define store8x4_vr_circ(z,a,c)		store8x4_vr_circI(z,a,INC1_CIRC,c)
#define store8x2_vr_circ(z,a,c,s)	store8x2_vr_circI(z,a,INC1_CIRC,c,s)
#define store8x1_vr_circ(z,a,c,s)	store8x1_vr_circI(z,a,INC1_CIRC,c,s)

#define align_24x4_store(p) 		align_32x4_store(p)

#define move32_vr_ar(z,ez,a)        replicate_ar(z,1<<(ez),a)

// ToDo: Need to Fix This, this is a part of //AudEngr/AlgoSW/Common/Infrastructure/Xtensa/Dmx1a/TIE_defs.h #1 enum
#define N_IDX_SPEC_TYPES            (4)

#endif // __DELTA_PLATFORM_H__



