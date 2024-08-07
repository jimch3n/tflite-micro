////////////////////////////////////////////////////////////////////////////////
///
/// \file AComplexMatrix.h
///
/// ComplexMatrix wrapper for generic C++
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef ACOMPLEXMATRIX_H
#define ACOMPLEXMATRIX_H

#include "AComplexArray.h"

struct AComplexMatrix
{
    AComplex* a;
    uint16_t rows, cols;

    _AI AComplexMatrix() {}
    _AI AComplexMatrix(int r, int c, AComplex* ptr) : a(ptr), rows(r), cols(c) {}

    _AI void init(int r, int c, AComplex* ptr) {rows = r; cols = c; a = ptr;}

    _AI int n_rows() const {return rows;}
    _AI int n_cols() const {return cols;}

    _AI AComplex& at(int r, int c) {return a[(uint16_t) r * cols + c];}
    _AI const AComplex& at(int r, int c) const {return a[(uint16_t) r * cols + c];}

    _AI operator AComplex* () {return a;}
    _AI operator const AComplex* () const {return a;}
    _AI AComplexArray operator[] (int r) const {
        return AComplexArray(cols, a + (uint16_t) r * cols);
    }

    _AI AComplexArray flat() const {
        return AComplexArray(rows * cols, a);
    }

    _AI bool operator== (const AComplexMatrix& x) const {
        return flat() == x.flat();
    }
    _AI bool operator!= (const AComplexMatrix& x) const {
        return flat() != x.flat();
    }

    _AI void fill(const AComplex& x) {
        flat().fill(x);
    }
    _AI void identity(const AComplex& scale = AComplex::One()) {
        fill(AComplex::Zero());
        for (int i = 0; i < rows; i++)
            at(i, i) = scale;
    }
    _AI void copy(const AComplexMatrix& x) {
        flat().copy(x.flat());
    }
    _AI void conj(const AComplexMatrix& x) {
        flat().conj(x.flat());
    }
    _AI void transpose(const AComplexMatrix& x) {
        AVL_ASSERT(rows == x.cols && cols == x.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                at(i, j) = x.at(j, i);
    }
    _AI void conj_trans(const AComplexMatrix& x) {
        AVL_ASSERT(rows == x.cols && cols == x.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                at(i, j) = x.at(j, i).conj();
    }

    _AI void add(const AComplexMatrix& x, const AComplexMatrix& y) {
        flat().add(x.flat(), y.flat());
    }
    _AI void sub(const AComplexMatrix& x, const AComplexMatrix& y) {
        flat().sub(x.flat(), y.flat());
    }
    _AI void mul(const AComplexMatrix& x, const AScalar& y) {
        flat().mul(x.flat(), y);
    }
    _AI void mul(const AComplexMatrix& x, const AComplex& y) {
        flat().mul(x.flat(), y);
    }
    _AI void mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AComplex sum = AComplex::Zero();
                for (int k = 0; k < x.cols; k++)
                    sum += x.at(i, k) * y.at(k, j);
                at(i, j) = sum;
            }
    }
    _AI void mul_conj(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AComplex sum = AComplex::Zero();
                for (int k = 0; k < x.cols; k++)
                    sum += x.at(i, k) * y.at(k, j).conj();
                at(i, j) = sum;
            }
    }
    _AI void mul_trans(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AComplex sum = AComplex::Zero();
                for (int k = 0; k < x.cols; k++)
                    sum += x.at(i, k) * y.at(j, k);
                at(i, j) = sum;
            }
    }
    _AI void mul_conj_trans(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AComplex sum = AComplex::Zero();
                for (int k = 0; k < x.cols; k++)
                    sum += x.at(i, k) * y.at(j, k).conj();
                at(i, j) = sum;
            }
    }
    _AI void conj_mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AComplex sum = AComplex::Zero();
                for (int k = 0; k < x.cols; k++)
                    sum += x.at(i, k).conj() * y.at(k, j);
                at(i, j) = sum;
            }
    }
    _AI void trans_mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.cols && cols == y.cols && x.rows == y.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AComplex sum = AComplex::Zero();
                for (int k = 0; k < x.rows; k++)
                    sum += x.at(k, i) * y.at(k, j);
                at(i, j) = sum;
            }
    }
    _AI void conj_trans_mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.cols && cols == y.cols && x.rows == y.rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                AComplex sum = AComplex::Zero();
                for (int k = 0; k < x.rows; k++)
                    sum += x.at(k, i).conj() * y.at(k, j);
                at(i, j) = sum;
            }
    }
};

_AI void AComplexArray::mul(const AComplexArray& x, const struct AComplexMatrix& y) {
    AVL_ASSERT(y.rows == x.N && y.cols == N);
    for (int i = 0; i < N; i++) {
        AComplex sum = AComplex::Zero();
        for (int j = 0; j < x.N; j++)
            sum += x[j] * y[j][i];
        a[i] = sum;
    }
}

_AI void AComplexArray::mul(const struct AComplexMatrix& x, const AComplexArray& y) {
    AVL_ASSERT(x.rows == N && x.cols == y.N);
    for (int i = 0; i < N; i++) {
        AComplex sum = AComplex::Zero();
        for (int j = 0; j < y.N; j++)
            sum += x[i][j] * y[j];
        a[i] = sum;
    }
}

_AI void AComplexArray::mul_conj(const struct AComplexMatrix& x, const AComplexArray& y) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i].dot(y);
}

_AI void AComplexArray::column(const struct AComplexMatrix& x, int col) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i][col];
}

#endif

/** \class AComplexMatrix
    \brief Wraps an abstract pointer to an AComplex and height and width

    \fn AComplexMatrix::AComplexMatrix(int r, int c, AComplex* ptr)
    \brief Constructor taking a length and height and width

    \fn void AComplexMatrix::init(int r, int c, AComplex* ptr)
    \brief Reinitialize with height and width and a pointer

    \fn int AComplexMatrix::n_rows()
    \brief Returns the number of rows

    \fn int AComplexMatrix::n_cols()
    \brief Returns the number of columns

    \fn AComplex& AComplexMatrix::at(int r, int c)
    \brief Returns the value at row r, column c

    \fn AComplexArray AComplexMatrix::flat()
    \brief Returns a flat AComplexArray view of the matrix

    \fn void AComplexMatrix::fill(const AComplex& x)
    \brief Fills matrix with copies of x

    \fn void AComplexMatrix::identity(const AComplex& scale = AComplex::One())
    \brief Fills matrix with zero off the diagonal and scale on the diagonal

    \fn void AComplexMatrix::copy(const AComplexMatrix& x)
    \brief Copies matrix from the elements of x

    \fn void AComplexMatrix::transpose(const AComplexMatrix& x)
    \brief *this = transpose(x)

    \fn void AComplexMatrix::add(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = x + y elementwise

    \fn void AComplexMatrix::sub(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = x - y elementwise

    \fn void AComplexMatrix::mul(const AComplexMatrix& x, const AScalar& y)
    \brief *this = x * y elementwise

    \fn void AComplexMatrix::mul(const AComplexMatrix& x, const AComplex& y)
    \brief *this = x * y elementwise

    \fn void AComplexMatrix::mul(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = x * y

    \fn void AComplexMatrix::mul_conj(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = x * conj(y)

    \fn void AComplexMatrix::mul_trans(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = x * transpose(y)

    \fn void AComplexMatrix::mul_conj_trans(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = x * transpose(conj(y))

    \fn void AComplexMatrix::conj_mul(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = conj(x) * y

    \fn void AComplexMatrix::trans_mul(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = transpose(x) * y

    \fn void AComplexMatrix::conj_trans_mul(const AComplexMatrix& x, const AComplexMatrix& y)
    \brief *this = transpose(conj(x)) * y
*/
