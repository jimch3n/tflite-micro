/************************************************************************//**
 * @file    AVL/Hemi/AComplexMatrix.h
 *
 * @brief   ComplexMatrix wrapper for HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEXMATRIX_H
#define ACOMPLEXMATRIX_H

#include "AComplexArray.h"

struct AComplexMatrix
{
    AComplex* a;
    uint16_t rows, cols;

    _AI AComplexMatrix() {}
    _AI AComplexMatrix(int r, int c, AComplex* ptr)    : a(ptr), rows(r), cols(c) {}

    _AI void init(int r, int c, AComplex* ptr)    {rows = r; cols = c; a = ptr;}

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
    void identity(const AComplex& scale = AComplex::One()) {
        AVL_ASSERT(rows == cols);
        int loops = rows;
        vr64* P_dst = (vr64*) a;

        fill(AComplex::Zero());
        for (int i = 0; i < loops; i++)
            vr64_storexp(scale.vr, P_dst, 8 * (cols + 1));
    }
    _AI void copy(const AComplexMatrix& x) {
        flat().copy(x.flat());
    }
    _AI void conj(const AComplexMatrix& x) {
        flat().conj(x.flat());
    }
    void transpose(const AComplexMatrix& x) {
        AVL_ASSERT(rows == x.cols && cols == x.rows);
        int loops = cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            AComplex* P_src = x.a + i;

            for (int j = 0; j < loops; j++) {
                vr64 V_dst;
                load32x2_vr_postR(V_dst, P_src, rows);
                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }
    void conj_trans(const AComplexMatrix& x) {
        AVL_ASSERT(rows == x.cols && cols == x.rows);
        int loops = cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            AComplex* P_src = x.a + i;

            for (int j = 0; j < loops; j++) {
                vr64 V_dst;
                load32x2_vr_postR(V_dst, P_src, rows);
                set_VRH(V_dst, neg_fr(get_VRH(V_dst)));
                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
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

    void mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x, V_src_y;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1);
                    load32x2_vr_postR(V_src_y, P_src_y, cols);
                    V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_NONE);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }

    void mul_conj(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x, V_src_y;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1);
                    load32x2_vr_postR(V_src_y, P_src_y, cols);
                    V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_Y);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }

    void mul_trans(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        int loops = x.cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                vr64* P_src_x = (vr64*) x.a + i * x.cols;
                vr64* P_src_y = (vr64*) y.a + j * x.cols;
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x, V_src_y;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1);
                    load32x2_vr_postI(V_src_y, P_src_y, INC1);
                    V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_NONE);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }

    void mul_conj_trans(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        int loops = x.cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                vr64* P_src_x = (vr64*) x.a + i * x.cols;
                vr64* P_src_y = (vr64*) y.a + j * x.cols;
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x, V_src_y;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1);
                    load32x2_vr_postI(V_src_y, P_src_y, INC1);
                    V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_Y);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }

    void conj_mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x, V_src_y;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1);
                    load32x2_vr_postR(V_src_y, P_src_y, cols);
                    V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_X);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }

    void trans_mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.cols && cols == y.cols && x.rows == y.rows);
        int loops = x.rows;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i;
                AComplex* P_src_y = y.a + j;
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x, V_src_y;
                    load32x2_vr_postR(V_src_x, P_src_x, rows);
                    load32x2_vr_postR(V_src_y, P_src_y, cols);
                    V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_NONE);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }

    void conj_trans_mul(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.cols && cols == y.cols && x.rows == y.rows);
        int loops = x.rows;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i;
                AComplex* P_src_y = y.a + j;
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x, V_src_y;
                    load32x2_vr_postR(V_src_x, P_src_x, rows);
                    load32x2_vr_postR(V_src_y, P_src_y, cols);
                    V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_X);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1);
            }
        }
    }
};

inline void AComplexArray::mul(const AComplexArray& x, const AComplexMatrix& y) {
    AVL_ASSERT(y.rows == x.N && y.cols == N);
    AComplex* P_dst = a;
    for (int i = 0; i < N; i++) {
        AComplex* P_src_x = x.a;
        AComplex* P_src_y = y.a + i;
        vr64 V_dst = vseta_vr(0, 0);

        for (int j = 0; j < x.N; j++) {
            vr64 V_src_x, V_src_y;
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            load32x2_vr_postR(V_src_y, P_src_y, N);
            V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_NONE);
        }

        store32x2_vr_postI(V_dst, P_dst, INC1);
    }
}

inline void AComplexArray::mul(const AComplexMatrix& x, const AComplexArray& y) {
    AVL_ASSERT(x.rows == N && x.cols == y.N);
    int loops = y.N;
    AComplex* P_dst = a;
    for (uint16_t i = 0; i < N; i++) {
        vr64* P_src_x = (vr64*) x.a + i * x.cols;
        vr64* P_src_y = (vr64*) y.a;
        vr64 V_dst = vseta_vr(0, 0);

        for (int j = 0; j < loops; j++) {
            vr64 V_src_x, V_src_y;
            load32x2_vr_postI(V_src_x, P_src_x, INC1);
            load32x2_vr_postI(V_src_y, P_src_y, INC1);
            V_dst = cmac(V_dst, V_src_x, V_src_y, CONJ_NONE);
        }

        store32x2_vr_postI(V_dst, P_dst, INC1);
    }
}

inline void AComplexArray::mul_conj(const AComplexMatrix& x, const AComplexArray& y) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i].dot(y);
}

_AI void AComplexArray::column(const AComplexMatrix& x, int col) {
    AVL_ASSERT(x.rows == N);
    AComplex* P_src = x.a + col;
    AComplex* P_dst = a;

    for (int i = 0; i < N; i++) {
        vr64 V_dst;
        load32x2_vr_postR(V_dst,  P_src, x.cols);
        store32x2_vr_postI(V_dst, P_dst, INC1);
    }
}

#endif
