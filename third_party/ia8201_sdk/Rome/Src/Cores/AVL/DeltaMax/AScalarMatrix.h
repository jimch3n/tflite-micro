/************************************************************************//**
 * @file    AVL\DeltaMax\AScalarMatrix.h
 *
 * @brief   ScalarMatrix wrapper for DeltaMax
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ASCALARMATRIX_H
#define ASCALARMATRIX_H

/**************************************************************************//**
 * @addtogroup dmx_avl
 * @{
 *****************************************************************************/

#include "AScalarArray.h"

struct AScalarMatrix
{
    AScalar* a;
    uint16_t rows, cols;

    _AI AScalarMatrix() {}
    _AI AScalarMatrix(int r, int c, AScalar* ptr) : a(ptr), rows(r), cols(c) {}

    _AI void init(int r, int c, AScalar* ptr) {rows = r; cols = c; a = ptr;}
    _AI int n_rows() const {return rows;}
    _AI int n_cols() const {return cols;}

    _AI AScalar& at(int r, int c) {return a[(uint16_t) r * cols + c];}
    _AI const AScalar& at(int r, int c) const {return a[(uint16_t) r * cols + c];}

    _AI operator AScalar* () {return a;}
    _AI operator const AScalar* () const {return a;}
    _AI AScalarArray operator[] (int r) const {
        return AScalarArray(cols, a + (uint16_t) r * cols);
    }

    _AI AScalarArray flat() const {
        return AScalarArray(rows * cols, a);
    }

    _AI bool operator== (const AScalarMatrix& x) const {
        return flat() == x.flat();
    }
    _AI bool operator!= (const AScalarMatrix& x) const {
        return flat() != x.flat();
    }

    _AI void fill(const AScalar& x) {
        flat().fill(x);
    }
    _AI void identity(const AScalar& scale = AScalar::One()) {
        AVL_ASSERT(rows == cols);
        int loops = rows;
        fr32* P_dst = (fr32*) a;

        fill(AScalar::Zero());
        for (int i = 0; i < loops; i++)
            fr32_storexp(scale.fr, P_dst, 4 * (cols + 1));
    }
    _AI void copy(const AScalarMatrix& x) {
        flat().copy(x.flat());
    }
    void transpose(const AScalarMatrix& x) {
        AVL_ASSERT(rows == x.cols && cols == x.rows);
        int loops = cols >> 2;
        for (uint16_t i = 0; i < rows; i++) {
            UnalignedQuadStorePointer SP_dst(a + i * cols);
            AScalar* P_src = x.a + i;

            for (int j = 0; j < loops; j++) {
                vr128 V_dst;
                load32x1_vr_postR(V_dst, P_src, rows, VRQ0);
                load32x1_vr_postR(V_dst, P_src, rows, VRQ1);
                load32x1_vr_postR(V_dst, P_src, rows, VRQ2);
                load32x1_vr_postR(V_dst, P_src, rows, VRQ3);
                SP_dst.store_post(V_dst);
            }
            SP_dst.flush();

            AScalar* P_dst = SP_dst;
            for (int j = 0; j < (cols & 3); j++) {
                vr128 V_dst;
                load32x1_vr_postR(V_dst,  P_src, rows, VRQ0);
                store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
            }
        }
    }

    _AI void add(const AScalarMatrix& x, const AScalarMatrix& y) {
        flat().add(x.flat(), y.flat());
    }
    _AI void sub(const AScalarMatrix& x, const AScalarMatrix& y) {
        flat().sub(x.flat(), y.flat());
    }
    _AI void mul(const AScalarMatrix& x, const AScalar& y) {
        flat().mul(x.flat(), y);
    }

    void mul(const AScalarMatrix& x, const AScalarMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AScalar* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AScalar* P_src_x = x.a + i * x.cols;
                AScalar* P_src_y = y.a + j;
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x, V_src_y;
                    load32x1_vr_postI(V_src_x, P_src_x, INC1, VRQ0);
                    load32x1_vr_postR(V_src_y, P_src_y, cols, VRQ0);
                    fmacs(V_dst, VRQ0, V_src_x, VRQ0, V_src_y, VRQ0, 0);
                }

                store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
            }
        }
    }

    void mul_trans(const AScalarMatrix& x, const AScalarMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        int loops = x.cols >> 2;
        AScalar* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                UnalignedQuadLoadPointer LP_src_x(x.a + i * x.cols);
                UnalignedQuadLoadPointer LP_src_y(y.a + j * x.cols);
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x = LP_src_x.load_post().vr;
                    vr128 V_src_y = LP_src_y.load_post().vr;
                    V_dst = vmacs_adj(V_dst, V_src_x, V_src_y, 0, 0);
                }
                dsums_L(V_dst, V_dst, 0, 0);
                dsums_L(V_dst, V_dst, 0, 0);

                const AScalar* P_src_x = LP_src_x;
                const AScalar* P_src_y = LP_src_y;
                for (int k = 0; k < (x.cols & 3); k++) {
                    vr128 V_src_x, V_src_y;

                    load32x1_vr_postI(V_src_x, P_src_x, INC1, VRQ0);
                    load32x1_vr_postI(V_src_y, P_src_y, INC1, VRQ0);
                    fmacs(V_dst, VRQ0, V_src_x, VRQ0, V_src_y, VRQ0, 0);
                }

                store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
            }
        }
    }

    void trans_mul(const AScalarMatrix& x, const AScalarMatrix& y) {
        AVL_ASSERT(rows == x.cols && cols == y.cols && x.rows == y.rows);
        int loops = x.rows;
        AScalar* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AScalar* P_src_x = x.a + i;
                AScalar* P_src_y = y.a + j;
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x, V_src_y;
                    load32x1_vr_postR(V_src_x, P_src_x, rows, VRQ0);
                    load32x1_vr_postR(V_src_y, P_src_y, cols, VRQ0);
                    fmacs(V_dst, VRQ0, V_src_x, VRQ0, V_src_y, VRQ0, 0);
                }

                store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
            }
        }
    }
};

inline void AScalarArray::mul(const AScalarArray& x, const struct AScalarMatrix& y) {
    AVL_ASSERT(y.rows == x.N && y.cols == N);
    int loops = y.rows;
    AScalar* P_dst = a;
    for (int i = 0; i < N; i++) {
        AScalar* P_src_x = x.a;
        AScalar* P_src_y = y.a + i;
        vr128 V_dst = vseta_vr(0, 0, 0);

        for (int j = 0; j < loops; j++) {
            vr128 V_src_x, V_src_y;
            load32x1_vr_postI(V_src_x, P_src_x, INC1, VRQ0);
            load32x1_vr_postR(V_src_y, P_src_y, N,    VRQ0);
            fmacs(V_dst, VRQ0, V_src_x, VRQ0, V_src_y, VRQ0, 0);
        }

        store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
    }
}

inline void AScalarArray::mul(const struct AScalarMatrix& x, const AScalarArray& y) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i].dot(y);
}

_AI void AScalarArray::column(const struct AScalarMatrix& x, int col) {
    AVL_ASSERT(x.rows == N);
    AScalar* P_src = x.a + col;
    AScalar* P_dst = a;

    for (int i = 0; i < N; i++) {
        vr128 V_dst;
        load32x1_vr_postR(V_dst,  P_src, x.cols, VRQ0);
        store32x1_vr_postI(V_dst, P_dst, INC1,   VRQ0);
    }
}

/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif

/** \class AScalarMatrix
    \brief Wraps an abstract pointer to an AScalar and height and width

    \fn AScalarMatrix::AScalarMatrix(int r, int c, AScalar* ptr)
    \brief Constructor taking a length and height and width

    \fn void AScalarMatrix::init(int r, int c, AScalar* ptr)
    \brief Reinitialize with height and width and a pointer

    \fn int AScalarMatrix::n_rows()
    \brief Returns the number of rows

    \fn int AScalarMatrix::n_cols()
    \brief Returns the number of columns

    \fn AScalar& AScalarMatrix::at(int r, int c)
    \brief Returns the value at row r, column c

    \fn AScalarArray AScalarMatrix::flat()
    \brief Returns a flat AScalarArray view of the matrix

    \fn void AScalarMatrix::fill(const AScalar& x)
    \brief Fills matrix with copies of x

    \fn void AScalarMatrix::identity(const AScalar& scale = AScalar::One())
    \brief Fills matrix with zero off the diagonal and scale on the diagonal

    \fn void AScalarMatrix::copy(const AScalarMatrix& x)
    \brief Copies matrix from the elements of x

    \fn void AScalarMatrix::transpose(const AScalarMatrix& x)
    \brief *this = transpose(x)

    \fn void AScalarMatrix::add(const AScalarMatrix& x, const AScalarMatrix& y)
    \brief *this = x + y elementwise

    \fn void AScalarMatrix::sub(const AScalarMatrix& x, const AScalarMatrix& y)
    \brief *this = x - y elementwise

    \fn void AScalarMatrix::mul(const AScalarMatrix& x, const AScalar& y)
    \brief *this = x * y elementwise

    \fn void AScalarMatrix::mul(const AScalarMatrix& x, const AScalarMatrix& y)
    \brief *this = x * y

    \fn void AScalarMatrix::mul_trans(const AScalarMatrix& x, const AScalarMatrix& y)
    \brief *this = x * transpose(y)

    \fn void AScalarMatrix::trans_mul(const AScalarMatrix& x, const AScalarMatrix& y)
    \brief *this = transpose(x) * y
*/
