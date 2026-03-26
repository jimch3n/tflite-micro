/************************************************************************//**
 * @file    LatticeIIR.h
 *
 * @brief   Lattice IIR filter interface file
 *
 * $DateTime: 2018/10/29 23:15:29 $
 * $Revision: #3 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_LATTICEIIR_H__
#define __FILE_LATTICEIIR_H__

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

/* C++ protection */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define LATC_OPT

/****************************************************************************
 * Types
 ****************************************************************************/

/************************************************************************//**
 * IIRLatticeState_t
 ****************************************************************************
 structure of the Lattice IIR filter.
 ****************************************************************************/
typedef void (funcPtr_rM)(fr32 *pKcoef, fr32 *pVcoef, fr32 *pState, fr32 *pInput, fr32 *pOutput, int blkSize, int stageM);

typedef struct
{
    int M;
    AFLOAT_t *pKcoeffs;
    AFLOAT_t *pVcoeffs;
    AFLOAT_t *pState;
    funcPtr_rM *latticeProc;
} IIRLatticeState_t;



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * IIR_lattice_filter_Init()
 ****************************************************************************
 * @brief       Initialize the state & coefficients of Lattice IIR filters
 *
 * @param[out]      *pInst          pointer for maintaining delay and coefficients.
 * @param[in]       *pKCoeffs       pointer to the 8-Byte aligned buffer of (N + 1) AFLOAT_t format reflection coefficients in time-reversed order.
 * @param[in]       *pVCoeffs       pointer to the 8-Byte aligned buffer of (N + 1) AFLOAT_t format ladder coefficients in time-reversed order.
 * @param[in]       *pState         pointer to the 8-Byte aligned state buffer of (stageM + blksize) AFLOAT_t format delays.
 * @param[in]       stageM          Number of Lattice stages.
 * @param[in]       blkSize         Number of the samples to process.
 *
 * @note            pKCoeffs and pVCoeffs should be stored in time-reversed order.
 *
 * @return          Nothing
 *
 ****************************************************************************/
void IIR_lattice_filter_Init(IIRLatticeState_t *pInst, AFLOAT_t *pKCoeffs, AFLOAT_t *pVCoeffs, AFLOAT_t *pState, int stageM, int blkSize);

/************************************************************************//**
 * IIR_lattice_filter()
 ****************************************************************************
 * @brief       Calculates a higher order IIR filter on real data and real coefficients by lattice form.
 *
 * @details
 *              Lattice filters are used in a variety of adaptive filter applications.
 *              The filter structure has feedforward and feedback components.
 *
 *              Example:  
 *                  For a 2 stages Lattice-Ladder IIR filter, the equations can be written as 
 *                      f2(n) = x(n)
 *                      f<m-1>(n) = fm(n) - km * g<m-1>(n-1)   ,  for m = 2, 1.
 *                      g<m>(n) = km * f<m-1>(n) + g<m-1>(n-1) ,  for m = 2, 1.
 *                      y(n) = v2 * g2(n) + v1 * g1(n) + v0 * g0(n) .
 *
 *                  Below is a 2 stages Lattice-Ladder IIR filter illustration for quickly image.
 *
 *                          f2(n)                 f1(n)                       f0(n)   
 *                  X(n) ----------> (-) ------------------------> (-) ----------------->
 *                                    |    /                        |    /               |
 *                                    ^   /(*k2)                    ^   /(*k1)           |
 *                                     \ /                           \ /                 |
 *                                      \                             \                  |
 *                                     / \                           / \                 |
 *                                    /   \(*k2)                    /   \(*k1)           |
 *                                   v     \    +-----+    g1(n)   v     \    +-----+    |
 *                       g2(n) <--- (+) <---\---|  -1 | <---------(+) <---\---|  -1 | <--- g0(n)
 *                        |                     | Z   |       |               | Z   |    |
 *                        |                     +-----+       |               +-----+    | 
 *                        |                                   |                          |
 *                        |(*v2)                              |(*v1)                     |(*v0)
 *                        |                                   v                          v
 *                        ---------------------------------> (+) ---------------------> (+) ---> y(n)
 *
 *
 *                  Thus for a M stages Lattice-Ladder IIR filter, the equations can be shown as
 *                      fM(n) = x(n)
 *                      f<M-1>(n) = fM(n) - kM * g<M-1>(n-1)   ,  for m = M, M-1, ..., 2, 1.
 *                      g<M>(n) = kM * f<M-1>(n) + g<M-1>(n-1) ,  for m = M, M-1, ..., 2, 1.
 *                      y(n) = vM * gM(n) + v<M-1> * g<M-1>(n) + ... + v1 * g1(n) + v0 * g0(n) .
 *
 *
 * Computation time:
 *
 * |         | frame size |   8   |   16  |   32   |   64   |   128  |   256   |   512   |   1024  |   2048   |
 * |:-------:|:----------:|:-----:|:-----:|:------:|:------:|:------:|:-------:|:-------:|:-------:|:--------:|
 * |IIR order| Lat stages |       |       |        |        |        |         |         |         |          |
 * |      1  |         1  |  142  |  214  |   358  |   646  |  1222  |   2374  |   4678  |   9286  |   18502  |
 * |      2  |         2  |  138  |  210  |   354  |   642  |  1218  |   2370  |   4674  |   9282  |   18498  |
 * |      3  |         3  |  165  |  253  |   429  |   781  |  1485  |   2893  |   5709  |  11341  |   22605  |
 * |      4  |         4  |  187  |  299  |   523  |   971  |  1867  |   3659  |   7243  |  14411  |   28747  |
 * |      5  |         5  |  203  |  323  |   563  |  1043  |  2003  |   3923  |   7763  |  15443  |   30803  |
 * |      6  |         6  |  233  |  385  |   689  |  1297  |  2513  |   4945  |   9809  |  19537  |   38993  |
 * |      7  |         7  |  242  |  394  |   698  |  1306  |  2522  |   4954  |   9818  |  19546  |   39002  |
 * |      8  |         8  |  278  |  470  |   854  |  1622  |  3158  |   6230  |  12374  |  24662  |   49238  |
 * |      9  |         9  |  435  |  787  |  1491  |  2899  |  5715  |  11347  |  22611  |  45139  |   90195  |
 * |     10  |        10  |  463  |  847  |  1615  |  3151  |  6223  |  12367  |  24655  |  49231  |   98383  |
 * |     11  |        11  |  477  |  869  |  1653  |  3221  |  6357  |  12629  |  25173  |  50261  |  100437  |
 * |     12  |        12  |  505  |  929  |  1777  |  3473  |  6865  |  13649  |  27217  |  54353  |  108625  |
 *
 * @param[in,out]   *pInst          pointer for maintaining delay and coefficients.
 * @param[in]       *src            pointer to the buffer of input.
 * @param[out]      *dst            pointer to the buffer of output.
 * @param[in]       blkSize         Number of the samples to process.
 *
 * @note            none
 *
 * @return          Nothing
 *
 ****************************************************************************/
void IIR_lattice_filter(IIRLatticeState_t *pInst, AFLOAT_t* src, AFLOAT_t *dst, int blkSize);



#ifdef __cplusplus
}
#endif /* __cplusplus */

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif /* __FILE_LATTICEIIR_H__ */



/* End of File */

