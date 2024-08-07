/************************************************************************//**
 * @file    TIE_defs.h
 *
 * @brief   Defines to be used with DMX1A TIE instructions
 *
 * $DateTime: 2022/07/10 23:45:28 $
 * $Revision: #2 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_TIE_DEFS_H__
#define __FILE_TIE_DEFS_H__

// Alignment directives
#if !defined(VAR_ALIGN_4 ) && !defined(VAR_ALIGN_8 ) && !defined (VAR_ALIGN_16)
#if !defined(VAR_ALIGN_16)
 #if defined(_MSC_VER)
  #define VAR_ALIGN_4  __declspec(align(4)) 
  #define VAR_ALIGN_8  __declspec(align(8)) 
  #define VAR_ALIGN_16 __declspec(align(16)) 
 #else
  #define VAR_ALIGN_4  __attribute__ ((aligned(4)))
  #define VAR_ALIGN_8  __attribute__ ((aligned(8)))
  #define VAR_ALIGN_16 __attribute__ ((aligned(16)))
 #endif
#endif
#endif

/// Load/Store IDX offsets

typedef enum
{
    IDX0 = 0,
    IDX1,
    IDX2,
    IDX3,
} IDX_IMM_t;

/// Load/Store POST offsets

typedef enum
{
    DEC2 = 0,
    DEC1,
    INC1,
    INC2
} POST_IMM_t;

/// Circular Load/Store directions

typedef enum
{
    INC1_CIRC = 0,
    DEC1_CIRC
} CIRC_IMM_t;

/// vr128 half-register selection

typedef enum
{
    VRL = 0,
    VRH
} REG_HALF_t;

/// vr128 quarter-register selection

typedef enum
{
    VRQ0 = 0,
    VRQ1,
    VRQ2,
    WR_LEN = VRQ2,
    VRQ3,
    VR_LEN
} REG_ELEM_t;

/// Complex conjugation selection

typedef enum
{
    CONJ_NONE = 0,
    CONJ_X,
    CONJ_Y,
    CONJ_X_Y
} CONJ_SPEC_t;

/// Jamming/Truncation selection

typedef enum
{
    TRUNCATING = 0,
    JAMMING
} JAMMING_t;

// Bit reverse related definitions

typedef enum
{
    FIRST_IDX_SPEC_TYPE = 0,
    LESS_THAN_BR_6_BITS = FIRST_IDX_SPEC_TYPE,
    ALL_6_BITS,
    ALL_8_BITS,
    ALL_10_BITS
} idx_spec_types_t;


typedef enum
{
    BR_IDX_EVEN = 0,
    BR_IDX_ODD
} idx_mod2_t;

typedef enum
{
    PAL_NO_SHIFT = 0,
    PAL_SHIFT_OUT,
    PAL_SHIFT_IN_0,
    PAL_SHIFT_IN_1,
} pal_shift_t;

typedef enum
{
    MSB_OFF=0,
    MSB_ON
} msb_on_off_t;

// Butterfly related definitions

typedef enum
{
    NO_RE_IM_SWAP=0,
    RE_IM_SWAP
} re_im_swap_t;

/// vperms descriptor macro

#define VPERM_DESC( d3, d2, d1, d0 ) ((d3) << 12) | ((d2) << 8) | ((d1) << 4) | (d0))

// vpermsi descriptor macros
	
#define SHR_BY_1_ELEM 0
#define SHR_BY_2_ELEM 1
#define SHL_BY_1_ELEM 2
#define EVEN_ODD_ELEM 3
#define ODD_EVEN_ELEM 4
#define LOW_HIGH_ELEM 5
#define ALL_HIGH_ELEM 6
#define ALL_LOW__ELEM 7

/// seta and vseta constant selection

typedef enum
{
	kConstTable_Zero = 0,
	kConstTable_One,
	kConstTable_Two,
	kConstTable_Half,
	kConstTable_Epsilon,
	kConstTable_Pi,
	kConstTable_e,
	kConstTable_Log2_Of_10,
	kConstTable_Log10_Of_2,
	kConstTable_Log2_Of_e,
	kConstTable_Loge_Of_2,
	kConstTable_TwoPi,
	kConstTable_Epsilon_Mul,
	kConstTable_OneDiv1000,
	kConstTable_TwoDivPi,
	kConstTable_Sqrt2,
	kConstTable_Sqrt2Div2,
	kConstTable_NegOne,
	kConstTable_OneDiv120,
	kConstTable_OneDiv100,
	kConstTable_OneDiv96,
	kConstTable_Log2_Of_10_Div200,
	kConstTable_OneDiv10Log2_Of_10,
	kConstTable_OneDiv10,
	kConstTable_Log2_Of_10_Div10,
	kConstTable_OneDivGoldenRatio,

	kConstTable_GoldenRatio = 27,
	kConstTable_Three,
	kConstTable_TwentyDivLog2_Of_10,
	kConstTable_Ten,
	kConstTable_100,
} SETA_CONST_t;

/// seta and vseta exponent adjustment selection

typedef enum
{
	kConstTableExpAdj_Times1 = 0,
	kConstTableExpAdj_Times2,
	kConstTableExpAdj_Times4,
	kConstTableExpAdj_Times2exp63,
	kConstTableExpAdj_Div16,
	kConstTableExpAdj_Div8,
	kConstTableExpAdj_Div4,
	kConstTableExpAdj_Div2,
} SETA_EXP_t;

#if defined(USE_CSTUBS) && defined(_MSC_VER)
#define CAST_INT_FROM_XTBOOL2(xtb2) ((int) ((xtb2)##._[0]))
#define CAST_INT_FROM_XTBOOL4(xtb4) ((int) ((xtb4)##._[0]))
#else
#define CAST_INT_FROM_XTBOOL2(xtb2) ((int) (xtb2))
#define CAST_INT_FROM_XTBOOL4(xtb4) ((int) (xtb4))
#endif

#endif



/* End of File */

