/************************************************************************//**
 * @file    blockcopy.h
 *
 * @brief   Block copy functions
 *
 * $DateTime: 2021/06/09 04:07:04 $
 * $Revision: #6 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_BLOCK_COPY_H__
#define __FILE_BLOCK_COPY_H__

/**************************************************************************//**
 * @addtogroup hml_core_dsp
 * @{
 *****************************************************************************/

/****************************************************************************
 * Includes
 ****************************************************************************/
#include <stdint.h>

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * BlockCopyWords()
 ****************************************************************************
 * @brief       Block copying of data as 32-bit words
 *
 * @details
 * Computation time:   For few number of counts are provided below for reference
 *
 * | count | Cycles |
 * |:-----:|:------:|
 * |    64 |     87 |
 * |   128 |    151 |
 * |   256 |    279 |
 * |   512 |    535 |
 * |  1024 |   1047 |
 *
 * @param[out]  *dst        Pointer to output vector
 * @param[in]   *src        Pointer to input vector
 * @param[in]   count       Number of words to be copied
 *
 * @return      none
 *
 ****************************************************************************/
void BlockCopyWords(int32_t *dst, const int32_t *src, int count);

/************************************************************************//**
 * BlockCopyBytes()
 ****************************************************************************
 * @brief       Block copying of data as byte
 *
 * @details
 * Computation time:   For few number of counts are provided below for reference
 *
 * | count | Cycles |
 * |:-----:|:------:|
 * |    64 |     55 |
 * |   128 |     71 |
 * |   256 |    103 |
 * |   512 |    167 |
 * |  1024 |    295 |
 *
 * @param[out]  *dst        Pointer to output vector
 * @param[in]   *src        Pointer to input vector
 * @param[in]   count       Number of bytes to be copied
 *
 * @return      none
 *
 ****************************************************************************/
void BlockCopyBytes(int8_t *dst, const int8_t *src, int count);

/************************************************************************//**
 * BlockFillWords()
 ****************************************************************************
 * @brief       fill word block
 *
 * @details
 * Computation time:   For few number of counts are provided below for reference
 *
 * | count | Cycles |
 * |:-----:|:------:|
 * |    64 |     57 |
 * |   128 |     89 |
 * |   256 |    153 |
 * |   512 |    281 |
 * |  1024 |    537 |
 *
 * @param[out]  *dst        Pointer to output vector
 * @param[in]   filler      Value to be filled
 * @param[in]   count       Number of words to be filled
 *
 * @return      none
 *
 ****************************************************************************/
void BlockFillWords(int32_t *dst, const int32_t filler, int count);

/************************************************************************//**
 * BlockFillBytes()
 ****************************************************************************
 * @brief       fill bytes
 *
 * @details
 * Computation time:   For few number of counts are provided below for reference
 *
 * | count | Cycles |
 * |:-----:|:------:|
 * |    64 |     51 |
 * |   128 |     59 |
 * |   256 |     75 |
 * |   512 |    107 |
 * |  1024 |    171 |
 *
 * @param[out]  *dst        Pointer to output vector
 * @param[in]   filler      Value to be filled
 * @param[in]   count       Number of bytes to be filled
 *
 * @return      none
 *
 ****************************************************************************/
void BlockFillBytes(int8_t *dst, const int8_t filler, int count);

/************************************************************************//**
 * ByteReverseWords()
 ****************************************************************************
 * @brief       copy words (32bits data) in reverse byte order of each word
 *
 * @details
 * Computation time:   For few number of counts are provided below for reference
 *
 * | count | Cycles |
 * |:-----:|:------:|
 * |    64 |    593 |
 * |   128 |   1169 |
 * |   256 |   2321 |
 * |   512 |   4625 |
 * |  1024 |   9233 |
 *
 * @param[out]  *pdst       Pointer to output vector
 * @param[in]   *psrc       Pointer to input vector
 * @param[in]   count       Number of words to be copied in reverse byte order
 *
 * @return      none
 *
 ****************************************************************************/
void ByteReverseWords(int32_t *pdst, const int32_t *psrc, int count);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif /* __FILE_BLOCK_COPY_H__ */



/* End of File */

