/************************************************************************//**
 * @file    TIE_defs.h
 *
 * @brief   Defines to be used with HMD1A TIE instructions 
 *
 * $DateTime: 2021/03/09 09:01:05 $
 * $Revision: #1 $
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
    INC2,
} POST_IMM_t;

/// Circular Load/Store directions

typedef enum
{
    INC1_CIRC = 0,
    DEC1_CIRC,
} CIRC_IMM_t;

/// vr64 half-register selects
typedef enum
{
    VRQ0 = 0,
    VRQ1,
    VR_LEN
} REG_ELEM_t;

/// alternate names for vr64 half-register selects

typedef enum
{
    VRL = 0,
    VRH
} REG_HALF_t;

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

/// VSEL descriptors

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

    VSEL_ZERO = 15
} VSEL_t;

/// VBLEND descriptors

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

/// seta and vseta exponent selection

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

#endif



/* End of File */

