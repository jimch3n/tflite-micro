/************************************************************************//**
 * @file    Interleave.h
 *
 * @brief   Interleave and Deinterleave functions
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_INTERLEAVE_H__
#define __FILE_INTERLEAVE_H__

/**************************************************************************//**
 * @addtogroup hml_core_dsp
 * @{
 *****************************************************************************/

/****************************************************************************
 * Includes
 ****************************************************************************/
#if defined(__XTENSA__)
 #include "TIE_include.h"
#else
 #include "cstubs.h"
#endif
#include "TIE_defs.h"

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * Interleave2x4()
 ****************************************************************************
 * @brief       Interleave 4-bytes items from each of 2 channels
 *
 * @param[out]      *out    pointer to output buffer
 * @param[in]       n       number of items to interleave
 * @param[in]       *ch_1   pointer to input channel buffer
 * @param[in]       *ch_2   pointer to input channel buffer
 *
 * @details
 * Computation time:   For few number of items are provided below for reference
 * 
 * |   n   | Cycles |
 * |:-----:|:------:|
 * |     8 |     42 |
 * |     9 |     45 |
 * |    10 |     48 |
 * |    11 |     51 |
 *
 * @note
 *          Size of each input buffer ch_1, ch_2 should be atleast n*4 Bytes;\n
 *          Size of output buffer out should be atleast (2*n)*4 Bytes;
 *
 * @return      None
 *
 ****************************************************************************/
void Interleave2x4(AFLOAT_t* out, int n,
                   const AFLOAT_t* ch_1, const AFLOAT_t* ch_2);

/************************************************************************//**
 * Interleave4x4()
 ****************************************************************************
 * @brief       Interleave 4-bytes items from each of 4 channels
 *
 * @details
 * Computation time:   For few number of items are provided below for reference
 *
 * |   n   | Cycles |
 * |:-----:|:------:|
 * |     8 |     68 |
 * |     9 |     74 |
 * |    10 |     80 |
 * |    11 |     86 |
 *
 * @param[out]      *out    pointer to output buffer
 * @param[in]       n       number of items to interleave
 * @param[in]       *ch_1   pointer to input channel buffer
 * @param[in]       *ch_2   pointer to input channel buffer
 * @param[in]       *ch_3   pointer to input channel buffer
 * @param[in]       *ch_4   pointer to input channel buffer
 *
 * @note
 *          Size of each input buffer ch_1 to ch_4 should be atleast n*4 Bytes;\n
 *          Size of output buffer out should be atleast (4*n)*4 Bytes;
 *
 * @return      None
 *
 ****************************************************************************/
void Interleave4x4(AFLOAT_t* out, int n,
                   const AFLOAT_t* ch_1, const AFLOAT_t* ch_2,
                   const AFLOAT_t* ch_3, const AFLOAT_t* ch_4);

/************************************************************************//**
 * Interleave8x4()
 ****************************************************************************
 * @brief       Interleave 4-bytes items from each of 8 channels
 *
 * @details
 * Computation time:   For few number of items are provided below for reference
 *
 * |   n   | Cycles |
 * |:-----:|:------:|
 * |     8 |    127 |
 * |     9 |    139 |
 * |    10 |    151 |
 * |    11 |    163 |
 *
 * @param[out]      *out    pointer to output buffer
 * @param[in]       n       number of items to interleave
 * @param[in]       *ch_1   pointer to input channel buffer
 * @param[in]       *ch_2   pointer to input channel buffer
 * @param[in]       *ch_3   pointer to input channel buffer
 * @param[in]       *ch_4   pointer to input channel buffer
 * @param[in]       *ch_5   pointer to input channel buffer
 * @param[in]       *ch_6   pointer to input channel buffer
 * @param[in]       *ch_7   pointer to input channel buffer
 * @param[in]       *ch_8   pointer to input channel buffer
 *
 * @note
 *          Size of each input buffer ch_1 to ch_8 should be atleast n*4 Bytes;\n
 *          Size of output buffer out should be atleast (8*n)*4 Bytes;
 *
 * @return      None
 *
 ****************************************************************************/
void Interleave8x4(AFLOAT_t* out, int n,
                   const AFLOAT_t* ch_1, const AFLOAT_t* ch_2,
                   const AFLOAT_t* ch_3, const AFLOAT_t* ch_4,
                   const AFLOAT_t* ch_5, const AFLOAT_t* ch_6,
                   const AFLOAT_t* ch_7, const AFLOAT_t* ch_8);

/************************************************************************//**
 * Deinterleave2x4()
 ****************************************************************************
 * @brief       Deinterleave 4-bytes items into each of 2 channels
 *
 * @details
 * Computation time:   For few number of items are provided below for reference
 *
 * |   n   | Cycles |
 * |:-----:|:------:|
 * |     8 |     41 |
 * |     9 |     44 |
 * |    10 |     47 |
 * |    11 |     50 |
 *
 * @param[in]       *in     pointer to input buffer
 * @param[in]       n       number of items to deinterleave
 * @param[out]      *ch_1   pointer to output channel buffer
 * @param[out]      *ch_2   pointer to output channel buffer
 *
 * @note
 *          Size of input buffer out should be atleast (2*n)*4 Bytes;
 *          Size of each output buffer ch_1, ch_2 should be atleast n*4 Bytes;\n
 *
 * @return      None
 *
 ****************************************************************************/
void Deinterleave2x4(const AFLOAT_t* in, int n,
                     AFLOAT_t* ch_1, AFLOAT_t* ch_2);

/************************************************************************//**
 * Deinterleave4x4()
 ****************************************************************************
 * @brief       Deinterleave 4-bytes items into each of 4 channels
 *
 * @details
 * Computation time:   For few number of items are provided below for reference
 *
 * |   n   | Cycles |
 * |:-----:|:------:|
 * |     8 |     69 |
 * |     9 |     75 |
 * |    10 |     81 |
 * |    11 |     87 |
 *
 * @param[in]       *in     pointer to input buffer
 * @param[in]       n       number of items to deinterleave
 * @param[out]      *ch_1   pointer to output channel buffer
 * @param[out]      *ch_2   pointer to output channel buffer
 * @param[out]      *ch_3   pointer to output channel buffer
 * @param[out]      *ch_4   pointer to output channel buffer
 *
 * @note
 *          Size of input buffer out should be atleast (4*n)*4 Bytes;
 *          Size of each output buffer ch_1 to ch_4 should be atleast n*4 Bytes;\n
 *
 * @return      None
 *
 ****************************************************************************/
void Deinterleave4x4(const AFLOAT_t* in, int n,
                     AFLOAT_t* ch_1, AFLOAT_t* ch_2,
                     AFLOAT_t* ch_3, AFLOAT_t* ch_4);

/************************************************************************//**
 * Deinterleave8x4()
 ****************************************************************************
 * @brief       Deinterleave 4-bytes items into each of 8 channels
 *
 * @details
 * Computation time:   For few number of items are provided below for reference
 *
 * |   n   | Cycles |
 * |:-----:|:------:|
 * |     8 |    126 |
 * |     9 |    138 |
 * |    10 |    150 |
 * |    11 |    162 |
 *
 * @param[in]       *in     pointer to input buffer
 * @param[in]       n       number of items to deinterleave
 * @param[out]      *ch_1   pointer to output channel buffer
 * @param[out]      *ch_2   pointer to output channel buffer
 * @param[out]      *ch_3   pointer to output channel buffer
 * @param[out]      *ch_4   pointer to output channel buffer
 * @param[out]      *ch_5   pointer to output channel buffer
 * @param[out]      *ch_6   pointer to output channel buffer
 * @param[out]      *ch_7   pointer to output channel buffer
 * @param[out]      *ch_8   pointer to output channel buffer
 *
 * @note
 *          Size of input buffer out should be atleast (8*n)*4 Bytes;
 *          Size of each output buffer ch_1 to ch_8 should be atleast n*4 Bytes;\n
 *
 * @return      None
 *
 ****************************************************************************/
void Deinterleave8x4(const AFLOAT_t* in, int n,
                     AFLOAT_t* ch_1, AFLOAT_t* ch_2,
                     AFLOAT_t* ch_3, AFLOAT_t* ch_4,
                     AFLOAT_t* ch_5, AFLOAT_t* ch_6,
                     AFLOAT_t* ch_7, AFLOAT_t* ch_8);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/
 
#endif /* __FILE_INTERLEAVE_H__ */

/* End of File */

