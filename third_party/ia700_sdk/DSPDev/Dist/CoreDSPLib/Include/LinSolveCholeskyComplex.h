/************************************************************************//**
 * @file    LinSolveCholeskyComplex.h
 *
 * @brief   Complex Cholesky solver interface file.
 *
 * $DateTime: 2019/04/17 07:20:18 $
 * $Revision: #5 $
 *
 * @copyright Copyright ©  2018 Knowles Electronics, LLC.  All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef _FILE_LIN_SOLVE_CHOLESKY_COMPLEX_H_
#define _FILE_LIN_SOLVE_CHOLESKY_COMPLEX_H_

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

/*
*   NOTE: In all instances vr64* means there is an expectation that
*   the pointer points to a 8-byte aligned array.
*/

#ifdef __cplusplus
extern "C" {
#endif 



/***************************************************************************
 * Public Functions
 ****************************************************************************/

/************************************************************************//**
 * LinSolveCholeskyComplex()
 ****************************************************************************
 * @brief        Complex linear system solver using Cholesky factorization.
 *
 * @details
 *       Input matrix is expected to be Hermitian positive definite of size nxn.
 *       Real and imaginary parts are interleaved throughout.
 *
 * Computation time:   For few number of 'n' sizes are provided below for reference
 *
 *  | size (n) | Cycles  |
 *  |:--------:|:-------:|
 *  |     3    |     266 |
 *  |     7    |     968 |
 *  |    16    |    4556 |
 *  |    28    |   15766 |
 *  |    32    |   21668 |
 *  |    64    |  126292 |
 *  |   128    |  846516 |
 *  |   256    | 6165877 |
 *
 * @param[out]   *x    Pointer to solution vector (of length n).
 * @param[in]    *A    Pointer to Hermitian positive definite nxn matrix
 *                     (row major format). Real and imaginary parts are interleaved.
 *                     For the factorization A = L\* L, the lower triangular part
 *                     of A is overwritten with L.
 * @param[in]    *b     Right hand side of linear system (of length n).
 *                     Gets overwritten with scratch data.
 * @param[in]    n     Size of linear system.
 *
 * @return       1 for success
 *               0 for failure (A apparently not Hermitian positive definite)
 *
 ****************************************************************************/
int LinSolveCholeskyComplex(AFLOAT_t *x, AFLOAT_t *A, AFLOAT_t *b, int n);

#ifdef __cplusplus
}
#endif

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  // _FILE_LIN_SOLVE_CHOLESKY_COMPLEX_H_
