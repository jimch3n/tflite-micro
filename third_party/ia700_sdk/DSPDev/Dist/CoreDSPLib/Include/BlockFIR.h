/************************************************************************//**
 * @file    BlockFIR.h
 *
 * @brief   Block FIR interface file.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #7 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef __FILE_BLOCK_FIR_H__
#define __FILE_BLOCK_FIR_H__

/**************************************************************************//**
 * @addtogroup hml_core_dsp
 * @{
 *****************************************************************************/

/****************************************************************************
 * Includes
 ****************************************************************************/
#ifdef __XTENSA__
#include "TIE_include.h"
#else
#include "cstubs.h"
#endif

#include <stdint.h>
#include "TIE_defs.h"

#ifdef __cplusplus
extern "C" {
#endif



/****************************************************************************
 * Types
 ****************************************************************************/

/************************************************************************//**
 * BlockFirState
 ****************************************************************************
 structure of the FIR filter.
 ****************************************************************************/
/*
           N
   H(z) = sum [b(i) * z^(-i)]
          i=0
*/

typedef struct {
    int N;              //!< The highest order of the filter                                
    AFLOAT_t *pCoeff;       //!< Coeff array, N+1 elements padded to a multiple of 2, and the    
                        //!< minimum size is 4 (0-padded as necessary).  The coefficients   
                        //!< are stored in reverse order by BlockFirInit().                          

    AFLOAT_t *pHist;        //!< History buffer, N+1 elements padded to a multiple of 2, and the 
                        //!< minimum size is 4.                                             

    AFLOAT_t *pCurrHist;    //!< Current read/write pointer into the history buffer.                       
    int numCoefsPadded; //!< Padded number of coefficients.                                     
} BlockFirState;



/****************************************************************************
 * Public Functions
 ****************************************************************************/
 
/************************************************************************//**
 * BlockFirGetMemorySize()
 ****************************************************************************
 * @brief       Call this function to get the number of bytes required in state memory to
 *              support the given FIR order.  Then once allocated, pass a pointer to the
 *              memory in BlockFirInit().
 *
 * @param[in]      firOrder        Order, N, of the desired FIR filter.
 *
 * @return      How many bytes of storage are required.
 *
 ****************************************************************************/
int BlockFirGetMemorySize(int firOrder);

/************************************************************************//**
 * BlockFirInit()
 ****************************************************************************
 * @brief       Initialize the given instance to prepare for processing.  Call
 *              BlockFirGetMemorySize() to determine how much memory is required in the
 *              pMemAlloc buffer.
 *
 * @param[in]      *pInst        Instance to initialize.
 * @param[in]      *pMemAlloc    Pointer to memory for the instance to use for internal state.
 *                               Call BlockFirGetMemorySize() to determine how big the memory
 *                               needs to be.  The caller need not worry about alignment.
 * @param[in]      *pCoeffs      Pointer to the order+1 coefficients.  These should be in
 *                               order from b0 to bN.  They will be copied in reverse order
 *                               to instance memory.
 * @param[in]      firOrder      Order, N, of the filter.
 *
 ****************************************************************************/
void BlockFirInit(BlockFirState *pInst, void *pMemAlloc, AFLOAT_t *pCoeffs, int firOrder);

/************************************************************************//**
 * BlockFirProcess()
 ****************************************************************************
 * @brief       The process function of the BlockFIR filter.
 *
 * @details
 *      Design:
 *            y(n)= b0w(n)+b1x(n-1)+b2x(n-2)+....+bNx(n-N)
 *                  where b(i) is coefficient,N is order of filter.
 *
 *                                  B0
 *       Xn---------------->------------>-------(+)-----------------> Yn
 *                             |                 |
 *                             V                 |
 *                          +-----+              |
 *                          |  -1 |              |
 *                          | Z   |              |
 *                          +-----+              |
 *                             |    B1           |
 *                             ----------->-----(+)
 *                             |                 |
 *                             V                 |
 *                          +-----+              |
 *                          |  -1 |              |
 *                          | Z   |              |
 *                          +-----+              |
 *                             |      B2         |
 *                             ---------->------(+)
 *                             .                 .
 *                             .                 .
 *                             .                 .
 *                             .                 .
 *                             |                 |
 *                             V                 |
 *                          +-----+              |
 *                          |  -1 |              |
 *                          | Z   |              |
 *                          +-----+              |
 *                             |        Bn       |
 *                             ---------->-- ---(+)
 *
 * Computation time:
 *
 * |frame size|   8   |  16   |   32   |   64   |  128   |  256   |  257   |  258   |  259   |  260  | 
 * |:--------:|:-----:|: ----:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:-----:| 
 * |FIR order |       |       |        |        |        |        |        |        |        |       |
 * |     31   |   226 |  398  |   742  |  1430  |  2806  |  5558  |  5660  |  5666  |  5664  |  5644 |
 * |     63   |   354 |  654  |  1254  |  2454  |  4854  |  9654  |  9820  |  9826  |  9824  |  9804 |
 * |    127   |   610 | 1166  |  2278  |  4502  |  8950  | 17846  | 18140  | 18146  | 18144  | 18124 |
 * |    255   |  1122 | 2190  |  4326  |  8598  | 17142  | 34230  | 34780  | 34786  | 34784  | 34764 |
 * |     58   |   338 |  622  |  1190  |  2326  |  4598  |  9142  |  9300  |  9306  |  9304  |  9284 |
 * |     59   |   338 |  622  |  1190  |  2326  |  4598  |  9142  |  9300  |  9306  |  9304  |  9284 |
 * |     60   |   346 |  638  |  1222  |  2390  |  4726  |  9398  |  9560  |  9566  |  9564  |  9544 |
 * |     61   |   346 |  638  |  1222  |  2390  |  4726  |  9398  |  9560  |  9566  |  9564  |  9544 |
 * |     62   |   354 |  654  |  1254  |  2454  |  4854  |  9654  |  9820  |  9826  |  9824  |  9804 |
 *
 * @param[in]      *pInst        Points to the BlockFirState structure instance.
 * @param[out]     *pOut         Output array "y".
 * @param[in]      *pIn          Input array "x".
 * @param[in]      size          Number of the samples to process.
 *
 ****************************************************************************/
void BlockFirProcess(BlockFirState *pInst, AFLOAT_t *pOut, const AFLOAT_t *pIn, int size);

#ifdef __cplusplus
};
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif
