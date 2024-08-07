/************************************************************************//**
 * @file    AVL/DMX1A/AComplexMatrix.h
 *
 * @brief   ComplexMatrix wrapper for DMX1A
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/

#ifndef ACOMPLEXMATRIX_H
#define ACOMPLEXMATRIX_H

/**************************************************************************//**
 * @addtogroup dmx1a_avl
 * @{
 *****************************************************************************/

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
    //alias
    _AI int num_rows() const { return rows; }
    _AI int num_columns() const { return cols; }

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
    _AI const AComplexMatrix & elements() const {
        return *this;//(rows * cols, a);
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
        AComplex* P_dst = a;

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
                vr128 V_dst=vseta_vr(0,0,0);
                load32x2_vr_postR(V_dst, P_src, rows, VRL);
                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }
    void exp_adj_matrix(const int shift) {
        //AVL_ASSERT(rows == x.cols && cols == x.rows);
        int loops = cols;
        AComplex* P_dst = a;
        AComplex* P_src = a;
        for (uint16_t i = 0; i < rows; i++) {

            for (int j = 0; j < loops; j++) {
                vr128 V_dst = vseta_vr(0, 0, 0);
                load32x2_vr_postI(V_dst, P_src, INC1, VRL);
           
                store32x2_vr_postI(vexp_adj(V_dst, shift), P_dst, INC1, VRL);
            }
        }
    }

    void scale(const AScalar &scaling) {
        //AVL_ASSERT(rows == x.cols && cols == x.rows);
        //int loops = cols;
        AComplex* P_dst = a;
        AComplex* P_src = a;
        vr128 VR_scale;
        replicate_ar(VR_scale, 0xf, scaling.fr);
        for (uint16_t i = 0; i < rows; i++) {

            for (int j = 0; j < cols; j++) {
                vr128 V_dst = vseta_vr(0, 0, 0);
                load32x2_vr_postI(V_dst, P_src, INC1, VRL);

                store32x2_vr_postI(vmuls(V_dst, VR_scale, 0), P_dst, INC1, VRL);
            }
        }
    }
    void blend(const AScalar& factor_old, AComplexMatrix &old_matrix, 
        const AScalar factor_new, AComplexMatrix &new_matrix) {
        //AVL_ASSERT(rows == x.cols && cols == x.rows);
        //int loops = cols;
        AComplex* P_dst = a;
        AComplex* P_src1 = old_matrix.a;
        AComplex* P_src2 = new_matrix.a;
        vr128 VR_blend;
        AVL_ASSERT(old_matrix.rows == new_matrix.rows);
        AVL_ASSERT(old_matrix.cols == new_matrix.cols);
        replicate_ar(VR_blend, 0x3, factor_old.fr); // VRQ0, VRQ1
        replicate_ar(VR_blend, 0xc, factor_new.fr); // VRQ2, VRQ3

        perm16 permYL = set_perm16(0x7610); //X:0, 1
        perm16 permYH = set_perm16(0xfe98);
        for (uint16_t i = 0; i < rows; i++) {

            for (int j = 0; j < cols; j++) {
                vr128 V_old, V_new; // = vseta_vr(0, 0, 0);
                load32x2_vr_postI(V_old, P_src1, INC1, VRL); 
                
                vr128 VR_out = vmuls_perm(V_old, VR_blend,  0, permYL);
                load32x2_vr_postI(V_new, P_src2, INC1, VRL);
                VR_out = vmacs_perm(VR_out, V_new, VR_blend, 0, permYH);
                store32x2_vr_postI(VR_out, P_dst, INC1, VRL);
            }
        }
    }
    
    void conj_trans(const AComplexMatrix& x) {
        AVL_ASSERT(rows == x.cols && cols == x.rows);
        int loops = cols;
        AComplex* P_dst = a;
        for (int i = 0; i < rows; i++) {
            AComplex* P_src = x.a + i;

            for (int j = 0; j < loops; j++) {
                vr128 V_dst=vseta_vr(0,0,0);
                load32x2_vr_postR(V_dst, P_src, rows, VRL);
                s_neg(V_dst, VRQ1, V_dst, VRQ1);
                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
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
    // AScalarArray

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
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x=vseta_vr(0,0,0);
                    vr128 V_src_y=V_src_x;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);

                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
                    
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }

    void mas(const AComplexMatrix &acc, const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        AComplex* P_acc = acc.a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                vr128 V_dst = vseta_vr(0, 0, 0);
                vr128 V_acc;
                load32x2_vr_postI(V_acc, P_acc, INC1, VRL);
                
                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x = vseta_vr(0, 0, 0);
                    vr128 V_src_y = V_src_x;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
                }
                V_dst = vadds(V_acc, V_dst, 0x50); //negate image output 
                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
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
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x=vseta_vr(0,0,0);
                    vr128 V_src_y=V_src_x;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_Y);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }

    void mul_trans(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        int loops = x.cols >> 1;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                UnalignedQuadLoadPointer LP_src_x((AScalar*) (x.a + i * x.cols));
                UnalignedQuadLoadPointer LP_src_y((AScalar*) (y.a + j * x.cols));
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++)
                    V_dst = cmac_adj_x2(V_dst, LP_src_x.load_post().vr,
                                               LP_src_y.load_post().vr,
                                               CONJ_NONE, 0);
                csums_L(V_dst, V_dst, 0, 0);

                if (x.cols & 1) {
                    vr128 V_src_x=vseta_vr(0,0,0);
                    vr128 V_src_y=V_src_x;
                    load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
                    load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }

    void mul_conj_trans(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.rows && x.cols == y.cols);
        int loops = x.cols >> 1;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                UnalignedQuadLoadPointer LP_src_x((AScalar*) (x.a + i * x.cols));
                UnalignedQuadLoadPointer LP_src_y((AScalar*) (y.a + j * x.cols));
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++)
                    V_dst = cmac_adj_x2(V_dst, LP_src_x.load_post().vr,
                                               LP_src_y.load_post().vr,
                                               CONJ_Y, 0);
                csums_L(V_dst, V_dst, 0, 0);

                if (x.cols & 1) {
                    vr128 V_src_x=vseta_vr(0,0,0);
                    vr128 V_src_y=V_src_x;
                    load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
                    load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_Y);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }
    // accumulate self
    void conj_mac(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        AComplex* P_dst0 = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                //vr128 V_dst = vseta_vr(0, 0, 0);
                vr128 V_dst;
                load32x2_vr_postI(V_dst, P_dst0, INC1, VRL);
                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x = vseta_vr(0, 0, 0);
                    vr128 V_src_y = V_src_x;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_X);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }

    // accumulate self
    void mac_conj(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        AComplex* P_dst0 = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                //vr128 V_dst = vseta_vr(0, 0, 0);
                vr128 V_dst;
                load32x2_vr_postI(V_dst, P_dst0, INC1, VRL);
                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x = vseta_vr(0, 0, 0);
                    vr128 V_src_y = V_src_x;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_Y);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
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
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x=vseta_vr(0,0,0);
                    vr128 V_src_y=V_src_x;
                    load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_X);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }

    void conj_mul_interleaved(const AComplexMatrix& x, const AComplexMatrix& y, int mx=1,
        int my=1, int mz=1) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        for (uint16_t i = 0; i < rows; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                vr128 V_dst = vseta_vr(0, 0, 0);
                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x = vseta_vr(0, 0, 0);
                    vr128 V_src_y = V_src_x;
                    load32x2_vr_postR(V_src_x, P_src_x, mx, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, my*cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_X);
                }
                store32x2_vr_postR(V_dst, P_dst, mz, VRL);
            }
        }
    }

    // experiment x2
    void conj_mul_x2(const AComplexMatrix& x, const AComplexMatrix& y) {
        AVL_ASSERT(rows == x.rows && cols == y.cols && x.cols == y.rows);
        int loops = x.cols;
        AComplex* P_dst = a;
        AVL_ASSERT((rows & 1) == 0);

        for (uint16_t i = 0; i < rows/2; i++) {
            for (uint16_t j = 0; j < cols; j++) {
                AComplex* P_src_x = x.a + i * x.cols;
                AComplex* P_src_y = y.a + j;
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x = vseta_vr(0, 0, 0);
                    vr128 V_src_y = V_src_x;
                    load32x4_vr_postI(V_src_x, P_src_x, INC1);
                    load32x2_vr_postI(V_src_y, P_src_y, INC1, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols*2-1, VRH);
                    V_dst = cmac_adj_x2(V_dst, V_src_x, V_src_y, CONJ_X, 0);
                  
                }

                store32x4_vr_postI(V_dst, P_dst, INC1);
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
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x=vseta_vr(0,0,0);
                    vr128 V_src_y=V_src_x;
                    load32x2_vr_postR(V_src_x, P_src_x, rows, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
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
                vr128 V_dst = vseta_vr(0, 0, 0);

                for (int k = 0; k < loops; k++) {
                    vr128 V_src_x=vseta_vr(0,0,0);
                    vr128 V_src_y=V_src_x;
                    load32x2_vr_postR(V_src_x, P_src_x, rows, VRL);
                    load32x2_vr_postR(V_src_y, P_src_y, cols, VRL);
                    cmac_L(V_dst, V_src_x, V_src_y, CONJ_X);
                }

                store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
            }
        }
    }
};

inline void AComplexArray::mul(const AComplexArray& x, const struct AComplexMatrix& y) {
    AVL_ASSERT(y.rows == x.N && y.cols == N);
    AComplex* P_dst = a;
    for (int i = 0; i < N; i++) {
        AComplex* P_src_x = x.a;
        AComplex* P_src_y = y.a + i;
        vr128 V_dst = vseta_vr(0, 0, 0);

        for (int j = 0; j < x.N; j++) {
            vr128 V_src_x=vseta_vr(0,0,0);
            vr128 V_src_y=V_src_x;
            load32x2_vr_postI(V_src_x, P_src_x, INC1, VRL);
            load32x2_vr_postR(V_src_y, P_src_y, N,    VRL);
            cmac_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
        }

        store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
    }
}

inline void AComplexArray::mul(const struct AComplexMatrix& x, const AComplexArray& y) {
    AVL_ASSERT(x.rows == N && x.cols == y.N);
    int loops = y.N >> 1;
    AComplex* P_dst = a;
    for (uint16_t i = 0; i < N; i++) {
        UnalignedQuadLoadPointer LP_src_x((AScalar*) (x.a + i * x.cols));
        UnalignedQuadLoadPointer LP_src_y((AScalar*) y.a);
        vr128 V_dst = vseta_vr(0, 0, 0);

        for (int j = 0; j < loops; j++)
            V_dst = cmac_adj_x2(V_dst, LP_src_x.load_post().vr,
                                       LP_src_y.load_post().vr,
                                       CONJ_NONE, 0);
        csums_L(V_dst, V_dst, 0, 0);

        if (y.N & 1) {
            vr128 V_src_x=vseta_vr(0,0,0);
            vr128 V_src_y=V_src_x;
            load32x2_vr_idxI(V_src_x, (const AScalar*) LP_src_x, IDX0, VRL);
            load32x2_vr_idxI(V_src_y, (const AScalar*) LP_src_y, IDX0, VRL);
            cmac_L(V_dst, V_src_x, V_src_y, CONJ_NONE);
        }

        store32x2_vr_postI(V_dst, P_dst, INC1, VRL);
    }
}

inline void AComplexArray::mul_conj(const struct AComplexMatrix& x, const AComplexArray& y) {
    AVL_ASSERT(x.rows == N);
    for (int i = 0; i < N; i++)
        a[i] = x[i].dot(y);
}

_AI void AComplexArray::column(const struct AComplexMatrix& x, int col) {
    AVL_ASSERT(x.rows == N);
    AComplex* P_src = x.a + col;
    AComplex* P_dst = a;

    for (int i = 0; i < N; i++) {
        vr128 V_dst=vseta_vr(0,0,0);
        load32x2_vr_postR(V_dst,  P_src, x.cols, VRL);
        store32x2_vr_postI(V_dst, P_dst, INC1,   VRL);
    }
}

/**************************************************************************//**
 * @}
 *****************************************************************************/

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
