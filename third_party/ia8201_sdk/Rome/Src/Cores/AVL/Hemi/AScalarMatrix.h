/************************************************************************//**
 * @file    AVL/Hemi/AScalarMatrix.h
 *
 * @brief   ScalarMatrix wrapper for HemiLite
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ASCALARMATRIX_H
#define ASCALARMATRIX_H

#include "AScalarArray.h"

struct AScalarMatrix
{
    AScalar* a;
    uint16_t rows, cols;

    _AI AScalarMatrix() {}
    _AI AScalarMatrix(int r, int c, AScalar* ptr)    : a(ptr), rows(r), cols(c) {}

    _AI void init(int r, int c, AScalar* ptr)    {rows = r; cols = c; a = ptr;}
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
        int loops = cols >> 1;
        for (uint16_t i = 0; i < rows; i++) {
            UnalignedPairStorePointer SP_dst(a + i * cols);
            AScalar* P_src = x.a + i;
            vr64 V_dst;

            for (int j = 0; j < loops; j++) {
                load32x1_vr_postR(V_dst, P_src, rows, VRQ0);
                load32x1_vr_postR(V_dst, P_src, rows, VRQ1);
                SP_dst.store_post(V_dst);
            }
            SP_dst.flush();

            if (cols & 1) {
                #ifdef __XTENSA__
                #pragma frequency_hint NEVER
                #endif
                load32x1_vr_idxI(V_dst, P_src, IDX0, VRQ0);
                store32x1_vr_idxI(V_dst, SP_dst.ptr, IDX0, VRQ0);
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
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x=vseta_vr(0,0);
                    vr64 V_src_y=V_src_x;
                    load32x1_vr_postI(V_src_x, P_src_x, INC1, VRQ0);
                    load32x1_vr_postR(V_src_y, P_src_y, cols, VRQ0);
                    V_dst = vmac_perm(V_dst, V_src_x, V_src_y, VSEL_ZERO, VSEL_YL_XL, 0, 0, 0, 0);
                }

                store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
            }
        }
    }

    void mul_trans(const AScalarMatrix& x, const AScalarMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        int loops = x.cols >> 1;
        AScalar* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                UnalignedPairLoadPointer LP_src_x(x.a + i * x.cols);
                UnalignedPairLoadPointer LP_src_y(y.a + j * x.cols);
                APair V_dst = APair::Zero();

                for (int k = 0; k < loops; k++)
                    V_dst.mul_acc(LP_src_x.load_post(), LP_src_y.load_post());

                vr64 V_sum = vreplicate_fr(V_dst.sum());
                if (cols & 1) {
                    #ifdef __XTENSA__
                    #pragma frequency_hint NEVER
                    #endif
                    vr64 V_src_x=vseta_vr(0,0);
                    vr64 V_src_y=V_src_x;
                    load32x1_vr_idxI(V_src_x, LP_src_x.ptr, IDX0, VRQ0);
                    load32x1_vr_idxI(V_src_y, LP_src_y.ptr, IDX0, VRQ0);
                    V_sum = vmac_perm(V_sum, V_src_x, V_src_y, VSEL_ZERO, VSEL_YL_XL, 0, 0, 0, 0);
                }

                store32x1_vr_postI(V_sum, P_dst, INC1, VRQ0);
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
                vr64 V_dst = vseta_vr(0, 0);

                for (int k = 0; k < loops; k++) {
                    vr64 V_src_x=vseta_vr(0,0);
                    vr64 V_src_y=V_src_x;
                    load32x1_vr_postR(V_src_x, P_src_x, rows, VRQ0);
                    load32x1_vr_postR(V_src_y, P_src_y, cols, VRQ0);
                    V_dst = vmac_perm(V_dst, V_src_x, V_src_y, VSEL_ZERO, VSEL_YL_XL, 0, 0, 0, 0);
                }

                store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
            }
        }
    }
};

inline void AScalarArray::mul(const AScalarArray& x, const AScalarMatrix& y) {
    AVL_ASSERT(y.rows == x.N && y.cols == N);
    int loops = y.rows;
    AScalar* P_dst = a;
    for (int i = 0; i < N; i++) {
        AScalar* P_src_x = x.a;
        AScalar* P_src_y = y.a + i;
        vr64 V_dst = vseta_vr(0, 0);

        for (int j = 0; j < loops; j++) {
            vr64 V_src_x=vseta_vr(0,0);
            vr64 V_src_y=V_src_x;
            load32x1_vr_postI(V_src_x, P_src_x, INC1, VRQ0);
            load32x1_vr_postR(V_src_y, P_src_y, N,    VRQ0);
            V_dst = vmac_perm(V_dst, V_src_x, V_src_y, VSEL_ZERO, VSEL_YL_XL, 0, 0, 0, 0);
        }

        store32x1_vr_postI(V_dst, P_dst, INC1, VRQ0);
    }
}

inline void AScalarArray::mul(const AScalarMatrix& x, const AScalarArray& y) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i].dot(y);
}

_AI void AScalarArray::column(const AScalarMatrix& x, int col) {
    AVL_ASSERT(x.rows == N);
    AScalar* P_src = x.a + col;
    AScalar* P_dst = a;

    for (int i = 0; i < N; i++) {
        vr64 V_dst=vseta_vr(0,0);
        load32x1_vr_postR(V_dst,  P_src, x.cols, VRQ0);
        store32x1_vr_postI(V_dst, P_dst, INC1,   VRQ0);
    }
}

#endif
