///////////////////////////////////////////////////////////////////////////////
///
/// \file AFloatLiteral.h
///
/// \brief Compile-time AFloat constants
///
/// \author Marc Ferguson
///
/// \copyright Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
/// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
/// SEE ALSO License.txt
///
////////////////////////////////////////////////////////////////////////////////

#ifndef AFLOAT_LITERAL_H
#define AFLOAT_LITERAL_H

#include <stdint.h>

#define AFL_LOG_COARSE(D)                      \
    (8 * (((D) >= 1.0 / (1<<24))               \
        + ((D) >= 1.0 / (1<<16))               \
        + ((D) >= 1.0 / (1<<8))                \
        + ((D) >= 1)                           \
        + ((D) >= 1<<8)                        \
        + ((D) >= 1<<16)                       \
        + ((D) >= 1<<24)))

#define AFL_LOG_FINE(D)                        \
    (  ((D) >= 1<<19)                          \
     + ((D) >= 1<<20)                          \
     + ((D) >= 1<<21)                          \
     + ((D) >= 1<<22)                          \
     + ((D) >= 1<<23)                          \
     + ((D) >= 1<<24)                          \
     + ((D) >= 1<<25))

#define AFL_1(SIGN, EXP, MANT)                 \
    ((SIGN)                                    \
     | (((EXP) + ((MANT) >> 26)) << 25)        \
     | ((MANT) & 0x01ffffff))

#define AFL_2(SIGN, EXP, S)                                        \
    AFL_1(SIGN, (EXP) + AFL_LOG_FINE(S),                           \
          (uint32_t) (0.5 + (S) * (1 << 7 >> AFL_LOG_FINE(S))))

#define AFL_3(SIGN, D)                                             \
    (  (D) < 1.0 / (1LL<<32) + 1.0 / (1LL<<58) ? 0                 \
     : (D) >= 4294967232.0 ? AFL_1(SIGN, 63, 0x01ffffff)           \
     : AFL_2(SIGN, AFL_LOG_COARSE(D),                              \
             (D) / 64.0 * (1LL << 56 >> AFL_LOG_COARSE(D))))

#define AFL_4(D) \
     AFL_3(((D) < 0) << 31 , (D) < 0 ? -(D) : (D))


#ifdef __cplusplus

// Enforce compile-time evaluation

template <uint32_t V>
struct AFL_Constant {static const uint32_t value = V;};

#define AFLOAT_LITERAL(D) ((uint32_t) AFL_Constant<AFL_4(D)>::value)
#define CFLOAT_LITERAL(D) ((uint32_t) AFL_Constant<CFL_4(D)>::value)

#else

#define AFLOAT_LITERAL(D) AFL_4(D)
#define CFLOAT_LITERAL(D) CFL_4(D)

#endif

//
// "C" float version
//

#define CFL_LOG_COARSE(D) AFL_LOG_COARSE(D)
#define CFL_LOG_FINE(D)   AFL_LOG_FINE((D) * 4)

#define CFL_1(SIGN, EXP, MANT)                 \
    ((SIGN)                                    \
     | (((EXP) + 95 + ((MANT) >> 24)) << 23)   \
     | ((MANT) & 0x007fffff))

#define CFL_2(SIGN, EXP, S)                                        \
    CFL_1(SIGN, (EXP) + CFL_LOG_FINE(S),                           \
          (uint32_t) (0.5 + (S) * (1 << 7 >> CFL_LOG_FINE(S))))

#define CFL_3(SIGN, D)                                             \
    (  (D) < 1.0 / (1LL<<32) ? 0                                   \
     : (D) >= 4294967040.0 ? CFL_1(SIGN, 63, 0x007fffff)           \
     : CFL_2(SIGN, CFL_LOG_COARSE(D),                              \
             (D) / 256.0 * (1LL << 56 >> CFL_LOG_COARSE(D))))

#define CFL_4(D) \
    CFL_3(((D) < 0) << 31 , (D) < 0 ? -(D) : (D))

#endif
