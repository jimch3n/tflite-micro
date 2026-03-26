#ifndef KSP_TYPES_H
#define KSP_TYPES_H
#include <stdint.h>
//#include <inttypes.h>


// return status
typedef enum {
    KSP_SUCCESS        = 0,
    KSP_FAILURE        = 1,  // generic failure
    KSP_MEMORY_FAILURE = 2,
    KSP_UNRELIABLE     = 3
    // etc...
} ksp_status_t;

typedef enum {
    KSP_OFF = 0,
    KSP_ON = 1
} ksp_enable_t;

// Resolve AVL selection.
#ifdef AVL_DELTAPLUS
#undef AVL_DELTAPLUS
#ifndef AVL_DELTAMAX
#define AVL_DELTAMAX
#endif
#endif
#ifdef AVL_HEMILITE
#undef AVL_HEMILITE
#ifndef AVL_HEMI
#define AVL_HEMI
#endif
#endif
#ifdef AVL_DELTAMAX
#include "DeltaPlatform.h"
#endif
#ifdef AVL_HEMI
// FIX: does this work for Hemi?
#include "DeltaPlatform.h"
#endif
#ifdef AVL_DMX1A
#include "DeltaPlatform.h"
#endif
#if defined(AVL_GENERIC) || defined(AVL_DELTAMAX) || defined(AVL_HEMI) || defined(AVL_DMX1A)
#include "AVL.h"
#define KSP_FLOAT_CONST(x) CONST_ASCALAR(x)
#define KSP_FLOAT_FROM_UINT(x) (AScalar(x, 0))
#define EVAL RAW_LITERAL
#ifdef INLINE
#undef INLINE
#endif
#define INLINE AVL_ALWAYS_INLINE
typedef AScalar  ksp_float_t;
typedef AScalar  ksp_float_reg_t;
typedef unsigned ksp_float_literal_t;
typedef AComplex ksp_complex_t;
typedef AComplex ksp_complex_reg_t;
typedef struct { unsigned re; unsigned im; } ksp_complex_literal_t;
#else
#error Must define: AVL_GENERIC, AVL_DELTAMAX, or AVL_HEMI
#endif

// FIX: We should replace all of these, in our code,
// with equivalents from stdint, then drop these definitions.
typedef signed char     ksp_int8_t;
typedef unsigned char   ksp_uint8_t;
typedef short           ksp_int16_t;
typedef unsigned short  ksp_uint16_t;
typedef int             ksp_int32_t;
typedef unsigned int    ksp_uint32_t;

// ksp_matrix_float_t defines the matrix structure needed
// to implement the filter for a non-scalar state
typedef struct {
    ksp_float_t *Mat;
    int16_t rows;
    int16_t cols;
} ksp_matrix_float_t;

typedef struct {
    ksp_float_t** pBuf;
    ksp_int32_t  scf;
} ksp_float_vector_scaled_t;

typedef struct {
    ksp_complex_t* pBuf;
    ksp_int32_t  scf;
} ksp_complex_vector_scaled_t;

typedef struct {
    ksp_float_t** pRows;  // points to rows
    ksp_int32_t  scf;
} ksp_float_array_scaled_t;

typedef struct {
    ksp_complex_t** pRows;  // points to rows
    ksp_int32_t  scf;
} ksp_complex_array_scaled_t;

// parameter array types, used for paramGen content
typedef struct {
    ksp_uint32_t              size;
    const ksp_float_t         *val;
} ksp_param_arr_float_t;

typedef struct {
    ksp_uint32_t              size;
    const ksp_float_literal_t *val;
} ksp_param_arr_float_l_t;

typedef struct {
    ksp_uint32_t              size;
    const ksp_complex_t       *val;
} ksp_param_arr_complex_t;

typedef struct {
    ksp_uint32_t                size;
    const ksp_complex_literal_t *val;
} ksp_param_arr_complex_l_t;

typedef struct {
    ksp_uint32_t              size;
    const ksp_int32_t         *val;
} ksp_param_arr_int32_t;

// parameter 2D array (matrix) types, used for paramGen content
typedef struct {
    ksp_uint32_t              size[2];
    ksp_float_t               **val;
} ksp_param_mat_float_t;

typedef struct {
    ksp_uint32_t              size[2];
    ksp_float_literal_t       **val;
} ksp_param_mat_float_l_t;

#endif  /* _KSP_TYPES_H */
