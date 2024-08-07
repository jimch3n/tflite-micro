# Audience Vector Library

The Audience Vector Library (AVL) is a cross-platform C++ library for floating-point arithmetic. The supported target platforms are Generic C++, DeltaMax, DMX1A, HemiDelta, HemiLite, and HMD1A. The supported compilers are `gcc`, `xt-xcc`, and MSVC. The native floating-point format is 32-bit IEEE single precision for the Generic target and 32-bit AFloat for the Audience targets.

| Target      | Native Format         | Invocation              |
|:------------|:---------------------:|:------------------------|
| Generic C++ | IEEE Single Precision | #`define AVL_GENERIC`   |
| DeltaMax    | 32-bit AFloat         | #`define AVL_DELTAMAX`  |
| DMX1A       | 32-bit AFloat         | #`define AVL_DMX1A`     |   
| HemiDelta   | 32-bit AFloat         | #`define AVL_HEMI`      |
| HemiLite    | 32-bit AFloat         | #`define AVL_HEMI`      |
| HMD1A       | 32-bit AFloat         | #`define AVL_HEMI`      |

Define the target before including the headers:
~~~{.cpp}

    #define AVL_GENERIC
    #include "AVL.h"

~~~

### The AScalar Class

The `AScalar` class contains an abstract floating-point number in the native format.
~~~{.cpp}

    AScalar x = 13;
    AScalar y = 5.2;
    AScalar z = 1 / 3.0;

~~~
Use the `CONST_ASCALAR` macro to avoid a runtime conversion from integer or IEEE floating-point constants or when the full 26-bits of AFloat precision is required.
~~~{.cpp}

    AScalar x = CONST_ASCALAR(13);
    AScalar y = CONST_ASCALAR(5.2);
    AScalar z = CONST_ASCALAR(1 / 3.0);

~~~
Use the built-in constants when available.
~~~{.cpp}

    AScalar pi  = AScalar::Pi();
    AScalar zip = AScalar::Zero();
    AScalar big = AScalar::MaxAFloat();

~~~

### Arrays of Floating-Point Constants

To avoid generating static initializers, arrays of `AScalar` constants should be declared as `"uint32_t"` but accessed via an `"AScalar*"`.

Here's an example of an array of floating-point constants representing the whole numbers from 1.0 through 8.0 in AFloat format, and a loop to compute the sum of the numbers in the array:
~~~{.cpp}

    static uint32_t afloat_array[8] = {
        0x40000000, 0x42000000, 0x43000000, 0x44000000,
        0x44800000, 0x45000000, 0x45800000, 0x46000000
    };
    AScalar* p_afloats = (AScalar*) afloat_array;

    AScalar sum = AScalar::Zero();
    for (int i = 0; i < 8; i++)
      sum += p_afloats[i];

~~~
Because these numbers are in AFloat format, a different sum will be computed on an IEEE format target.

`RAW_LITERAL()` can be used to generate floating-point constants in native format so the above can be rewritten to produce the same result on AFloat or IEEE targets.
~~~{.cpp}

    static uint32_t native_array[8] = {
        RAW_LITERAL(1.0), RAW_LITERAL(2.0), RAW_LITERAL(3.0), RAW_LITERAL(4.0),
        RAW_LITERAL(5.0), RAW_LITERAL(6.0), RAW_LITERAL(7.0), RAW_LITERAL(8.0)
    };
    AScalar* p_natives = (AScalar*) native_array;

    AScalar sum = AScalar::Zero();
    for (int i = 0; i < 8; i++)
        sum += p_natives[i];

~~~

### Example: Sum of an Array

This example computes the sum of an array of `AScalar`s by adding them one at a time:
~~~{.cpp}

    AScalar sum_v1(AScalar* pDataIn, int n)
    {
        // 400 cycles on HemiDelta (for n = 100)
        // 400 cycles on DeltaMax  (for n = 100)

        AScalar sum = AScalar::Zero();

        for(int i = 0; i < n; i++)
            sum += pDataIn[i];

        return sum;
    }

~~~
The cycle counts above (and below) are asymptotic counts of cycles spent in the loop and ignore overhead. HemiDelta cycle counts also apply to HemiLite and HMD1A.

### The AScalarArray Class

The `AScalarArray` class is an abstract array of `AScalar`s encapsulating a pointer and a size. `AScalarArray` provides a number of optimized operations on arrays including sum:
~~~{.cpp}

    AScalar sum_v2(AScalar* pDataIn, int n)
    {
        // 100 cycles on HemiDelta (for n = 100)
        //  50 cycles on DeltaMax  (for n = 100)

        AScalarArray array(n, pDataIn);

        return array.sum();
    }

~~~

### Example: Square Root

This example computes the square root of an array of 100 `AScalar`s:
~~~{.cpp}

    void sqrt_v1(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 600 cycles on HemiDelta
        // 600 cycles on DeltaMax

        for (int i = 0; i < 100; i++) {
           AScalar src = pDataIn[i];
            pDataOut[i] = src * src.f_invsqrt();
        }
    }

~~~


### The AQuad Class

The `AQuad` class is a vector of four `AScalar`s and can be used to vectorize a loop. This version of the square root loop requires the input and output to be 16-byte aligned on DeltaMax or DMX1A and 8-byte aligned on Hemi targets:
~~~{.cpp}

    void sqrt_v2(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 225 cycles on HemiDelta
        // 225 cycles on DeltaMax

        AQuad* pQuadIn  = (AQuad*) pDataIn;
        AQuad* pQuadOut = (AQuad*) pDataOut;

        for (int i = 0; i < 25; i++) {
            AQuad src = pQuadIn[i];
            AQuad dst;

            dst.set_q0(src.q0().f_invsqrt());
            dst.set_q1(src.q1().f_invsqrt());
            dst.set_q2(src.q2().f_invsqrt());
            dst.set_q3(src.q3().f_invsqrt());

            pQuadOut[i] = src * dst;
        }
    }

~~~

### Example: Squared Absolute Value

Consider a function `c_squabs()` that takes an input array of 50 complex numbers and outputs the squared absolute values of the inputs as an array of 50 scalars. Treating the complex inputs as consecutive `AScalar`s, the function could be written straightforwardly like so:
~~~{.cpp}

    void c_squabs_v1(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 350 cycles on HemiDelta
        // 350 cycles on DeltaMax

        for (int i = 0; i < 50; i++) {
            AScalar x = pDataIn[2 * i];
            AScalar y = pDataIn[2 * i + 1];
            pDataOut[i] = x * x + y * y;
        }
    }

~~~
It's a good idea to use fused multiply-add operations when possible:
~~~{.cpp}

    void c_squabs_v2(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 300 cycles on HemiDelta
        // 250 cycles on DeltaMax

        for (int i = 0; i < 50; i++) {
            AScalar x = pDataIn[2 * i];
            AScalar y = pDataIn[2 * i + 1];
            pDataOut[i] = (x * x).mul_add(y, y);
        }
    }

~~~

### The AComplex Class

The `AComplex` class contains a complex floating-point number in the native format. Assuming 8-byte alignment of the input, the `c_squabs()` function can be rewritten using `AComplex`:
~~~{.cpp}

    void c_squabs_v3(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 200 cycles on HemiDelta
        // 250 cycles on DeltaMax

        AComplex* pComplexIn = (AComplex*) pDataIn;

        for (int i = 0; i < 50; i++) {
            AComplex c = pComplexIn[i];
            pDataOut[i] = c.norm_sq();
        }
    }

~~~
The `AQuad` class can be used to process two complex numbers at a time. This version requires the input to be 16-byte aligned on DeltaMax or DMX1A and 8-byte aligned on Hemi targets:
~~~{.cpp}

    void c_squabs_v4(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 150 cycles on HemiDelta
        // 175 cycles on DeltaMax

        AQuad* pQuadIn = (AQuad*) pDataIn;

        for (int i = 0; i < 25; i++) {
            AQuad q = pQuadIn[i];
            pDataOut[2*i]     = q.h0().norm_sq();
            pDataOut[2*i + 1] = q.h1().norm_sq();
        }
    }

~~~

### Individual Function Optimization

The cycle counts above assume the functions are compiled with `"-O2 -Os"`. On Xtensa targets, functions can be optimized individually. For example, space optimization can be turned off for a time-critical function:
~~~{.cpp}

    #ifdef __XTENSA__
        __attribute__((optimize ("-O2")))
    #endif
    
    void c_squabs_v5(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 125 cycles on HemiDelta
        // 100 cycles on DeltaMax

        AQuad*  pQuadIn    = (AQuad*) pDataIn;

        for (int i = 0; i < 25; i++) {
            AQuad q = pQuadIn[i];
            pDataOut[2*i]     = q.h0().norm_sq();
            pDataOut[2*i + 1] = q.h1().norm_sq();
        }
    }

~~~

### The AComplexArray Class

The `c_squabs()` function can also be written using the `AComplexArray` class which works similarly to the `AScalarArray` class:
~~~{.cpp}

    void c_squabs_v6(AScalar* pDataIn, AScalar* pDataOut)
    {
        // 200 cycles on HemiDelta (125 cycles without -Os)
        // 100 cycles on DeltaMax

        AComplexArray c_array(50, (AComplex*) pDataIn);
        AScalarArray  s_array(50, pDataOut);

        s_array.norm_sq(c_array);
    }

~~~

### Example: Dot Products

Consider a function that takes two arrays `X` and `Y` of length `N` and computes `X•X`, `Y•Y`, and `X•Y`. A straightforward implementation using `AScalarArray` is:
~~~{.cpp}


    void dots_v1(AScalar* x_in, AScalar* y_in, int n,
                 AScalar& xx_out, AScalar& yy_out, AScalar& xy_out)
    {
        // 600 cycles on HemiDelta for n == 100
        // 300 cycles on DeltaMax  for n == 100

        AScalarArray ax(n, x_in);
        AScalarArray ay(n, y_in);

        xx_out = ax.dot(ax);
        yy_out = ay.dot(ay);
        xy_out = ax.dot(ay);
    }

~~~
Combining the calculations into a single loop and using `AQuad` gives better performance assuming N is a multiple of four:
~~~{.cpp}

    void dots_v2(AQuad* x_in, AQuad* y_in, int n,
                 AScalar& xx_out, AScalar& yy_out, AScalar& xy_out)
    {
        // 175 cycles on HemiDelta for n == 100
        // 100 cycles on DeltaMax  for n == 100

        AQuad xx = AQuad::Zero();
        AQuad yy = AQuad::Zero();
        AQuad xy = AQuad::Zero();

        for (int i = 0; i < (n >> 2); i++) {
            AQuad x = x_in[i];
            AQuad y = y_in[i];

            xx.mul_acc(x, x);
            yy.mul_acc(y, y);
            xy.mul_acc(x, y);
        }

        xx_out = xx.sum();
        yy_out = yy.sum();
        xy_out = xy.sum();
    }

~~~
With space optimization turned off on Hemi targets, the compiler achieves the asymptotic performance of hand-coded intrinsics for this function:
~~~{.cpp}

    #ifdef __XTENSA__
        __attribute__((optimize ("-O2")))
    #endif

    void dots_v3(AQuad* x_in, AQuad* y_in, int n,
                 AScalar& xx_out, AScalar& yy_out, AScalar& xy_out)
    {
        // 150 cycles on HemiDelta for n == 100
        // 100 cycles on DeltaMax  for n == 100

        AQuad xx = AQuad::Zero();
        AQuad yy = AQuad::Zero();
        AQuad xy = AQuad::Zero();

        for (int i = 0; i < (n >> 2); i++) {
            AQuad x = x_in[i];
            AQuad y = y_in[i];

            xx.mul_acc(x, x);
            yy.mul_acc(y, y);
            xy.mul_acc(x, y);
        }

        xx_out = xx.sum();
        yy_out = yy.sum();
        xy_out = xy.sum();
    }

~~~

### AScalarMatrix and AComplexMatrix

The `AScalarMatrix` and `AComplexMatrix` classes are two dimensional analogues to the array classes. This function computes the commutator of two 2x2 complex matrices:
~~~{.cpp}

    void commutator2x2(AComplexMatrix& result, const AComplexMatrix& a, const AComplexMatrix& b)
    {
        AComplex buffer[2][4];
        AComplexMatrix tmp1(2, 2, buffer[0]);
        AComplexMatrix tmp2(2, 2, buffer[1]);

        tmp1.mul(a, b);
        tmp2.mul(b, a);
        result.sub(tmp1, tmp2);   // result = [a, b] = ab - ba
    }

~~~
The following code verifies some of the commutation relations between the Pauli spin matrices:
~~~{.cpp}

    AComplex zero = AComplex::Zero();
    AComplex one  = AComplex::One();
    AComplex i    = AComplex::I();
    AScalar two   = AScalar::Two();

    AComplex buffer[5][4];
    AComplexMatrix Sx(2, 2, buffer[0]);
    AComplexMatrix Sy(2, 2, buffer[1]);
    AComplexMatrix Sz(2, 2, buffer[2]);

    Sx[0][0] = zero; Sx[0][1] = one;
    Sx[1][0] = one;  Sx[1][1] = zero;

    Sy[0][0] = zero; Sy[0][1] = -i;
    Sy[1][0] = i;    Sy[1][1] = zero;

    Sz[0][0] = one;  Sz[0][1] = zero;
    Sz[1][0] = zero; Sz[1][1] = -one;

    AComplexMatrix comm(2, 2, buffer[3]);
    AComplexMatrix tmp(2, 2, buffer[4]);

    commutator2x2(comm, Sx, Sx);   // comm = [Sx, Sx]
    tmp.fill(AComplex::Zero());    // tmp  = 0
    if (comm == tmp)
        printf("[Sx, Sx] =  0\n");

    commutator2x2(comm, Sy, Sy);   // comm = [Sy, Sy]
    if (comm == tmp)
        printf("[Sy, Sy] =  0\n");

    commutator2x2(comm, Sz, Sz);   // comm = [Sz, Sz]
    if (comm == tmp)
        printf("[Sz, Sz] =  0\n");

    commutator2x2(comm, Sx, Sy);   // comm = [Sx, Sy]
    tmp.mul(Sz, two * i);          // tmp  = 2i * Sz
    if (comm == tmp)
        printf("[Sx, Sy] =  2i * Sz\n");

    commutator2x2(comm, Sx, Sz);    // comm = [Sx, Sz]
    tmp.mul(Sy, -two * i);          // tmp  = -2i * Sy
    if (comm == tmp)
        printf("[Sx, Sz] = -2i * Sy\n");

    commutator2x2(comm, Sy, Sz);    // comm = [Sy, Sz]
    tmp.mul(Sx, two * i);           // tmp  = 2i * Sx
    if (comm == tmp)
        printf("[Sy, Sz] =  2i * Sx\n");

~~~

Copyright 2018 Knowles Electronics, LLC. All rights reserved.
