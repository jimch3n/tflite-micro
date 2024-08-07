////////////////////////////////////////////////////////////////////////////////
//
// File: AVector.h
//
// Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
// SEE ALSO License.txt
//
////////////////////////////////////////////////////////////////////////////////

#if defined(AVL_GENERIC)

 #include "Generic/AVector.h"

#elif defined(AVL_HEMI)

 #include "Hemi/AVector.h"

#elif defined(AVL_DMX1A)

 #include "DMX1A/AVector.h"

#elif defined(AVL_DELTAMAX)

 #include "DeltaMax/AVector.h"

#endif
