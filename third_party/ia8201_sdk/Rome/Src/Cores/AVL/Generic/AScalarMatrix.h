////////////////////////////////////////////////////////////////////////////////
///
/// \file AScalarMatrix.h
///
/// ScalarMatrix wrapper for generic C++
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ASCALARMATRIX_H
#define ASCALARMATRIX_H

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

    _AI operator AScalar* () {return (AScalar*) a;}
    _AI operator const AScalar* () const {return (const AScalar*) a;}
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
        fill(AScalar::Zero());
        for (int i = 0; i < rows; i++)
            at(i, i) = scale;
    }
    _AI void copy(const AScalarMatrix& x) {
        flat().copy(x.flat());
    }
    _AI void transpose(const AScalarMatrix& x) {
        AVL_ASSERT(rows == x.cols && cols == x.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                at(i, j) = x.at(j, i);
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
    _AI void mul(const AScalarMatrix& x, const AScalarMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AScalar sum = AScalar::Zero();
                for (int k = 0; k < x.cols; k++)
                    sum += x.at(i, k) * y.at(k, j);
                at(i, j) = sum;
            }
    }
    _AI void mul_trans(const AScalarMatrix& x, const AScalarMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AScalar sum = AScalar::Zero();
                for (int k = 0; k < x.cols; k++)
                    sum += x.at(i, k) * y.at(j, k);
                at(i, j) = sum;
            }
    }
    _AI void trans_mul(const AScalarMatrix& x, const AScalarMatrix& y) {
        AVL_ASSERT(rows == x.cols && cols == y.cols && x.rows == y.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AScalar sum = AScalar::Zero();
                for (int k = 0; k < x.rows; k++)
                    sum += x.at(k, i) * y.at(k, j);
                at(i, j) = sum;
            }
    }
};

_AI void AScalarArray::mul(const AScalarArray& x, const struct AScalarMatrix& y) {
    AVL_ASSERT(y.rows == x.N && y.cols == N);
    for (int i = 0; i < N; i++) {
        AScalar sum = AScalar::Zero();
        for (int j = 0; j < x.N; j++)
            sum += x[j] * y[j][i];
        a[i] = sum;
    }
}

_AI void AScalarArray::mul(const struct AScalarMatrix& x, const AScalarArray& y) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i].dot(y);
}

_AI void AScalarArray::column(const struct AScalarMatrix& x, int col) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i][col];
}

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
