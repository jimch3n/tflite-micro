/************************************************************************//**
 * File:  DeltaTypes.h
 * 
 * Description: HemiLite platform data types
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
#ifndef _FILE_DELTA_TYPES_H_
#define _FILE_DELTA_TYPES_H_

typedef short              SHORT_t;
typedef unsigned short     USHORT_t;
typedef int                INT_t;
typedef unsigned int       UINT_t;
typedef long long          INT64_t;
typedef unsigned long long UINT64_t;
typedef signed char        CHAR_t;
typedef unsigned char      UCHAR_t;

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

typedef short   SP_t;
#define SP_SIZE 16

typedef UINT_t  AFLOATcarrier_t;
typedef unsigned short mFLOAT_t;

typedef struct
{
	UCHAR_t data[3];
} SFLOAT_t;					// AFLOAT truncated to 24 bits to save memory

#ifndef __XTENSA__
#ifdef __cplusplus
#define USE_AFLOAT_CLASS
#endif
#endif

#if defined(USE_AFLOAT_CLASS) && defined(__cplusplus)
class AFLOAT_t
{
    AFLOATcarrier_t aa;
public:
    // Constructors 
    AFLOAT_t() : aa() {}
    AFLOAT_t(const AFLOAT_t& x) : aa(x.aa) {}
    AFLOAT_t(const AFLOATcarrier_t& x) : aa(x) {}
    AFLOAT_t(const int x) : aa((UINT_t)x) {}
    explicit AFLOAT_t(const INT64_t x) : aa((UINT_t)x) {}
    explicit AFLOAT_t(const double x) ;

    // Conversion operators 
    operator unsigned int() const {return aa;}
    double toDouble();
};
#else
typedef fr32 AFLOAT_t;
#endif 

// Enums used with the set, vset instructions
enum
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
	kConstTable_OneDivLog2_Of_e,
	kConstTable_GoldenRatio,
	kConstTable_Three,
	kConstTable_TwentyDivLog2_Of_10,
	kConstTable_Ten,
	kConstTable_100,
	kNumConstTableValues
};

enum
{
	kConstTableExpAdj_Times1 = 0,
	kConstTableExpAdj_Times2,
	kConstTableExpAdj_Times4,
	kConstTableExpAdj_Times2exp63,
	kConstTableExpAdj_Div16,
	kConstTableExpAdj_Div8,
	kConstTableExpAdj_Div4,
	kConstTableExpAdj_Div2,
	kNumConstTableExpAdjValues
};

#endif //  _FILE_DELTA_TYPES_H_
