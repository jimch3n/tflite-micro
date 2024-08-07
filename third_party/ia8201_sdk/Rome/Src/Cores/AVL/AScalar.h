////////////////////////////////////////////////////////////////////////////////
//
// File: AScalar.h
//
// Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
// SEE ALSO License.txt
//
////////////////////////////////////////////////////////////////////////////////

// for float16 bit 
#define FLT16_SIGN 1
#define FLT16_EXP  5
#define FLT16_BIAS 14
#if !defined(__cplusplus)

 #error AScalar.h requires C++

#elif defined(AVL_GENERIC)

 #include "Generic/AScalar.h"

#elif defined(AVL_HEMI)

 #include "Hemi/AScalar.h"

#elif defined(AVL_DMX1A)

 #include "DMX1A/AScalar.h"

#elif defined(AVL_DELTAMAX)

 #include "DeltaMax/AScalar.h"

#else

 #error AVL target undefined

#endif
