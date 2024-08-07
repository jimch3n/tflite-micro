////////////////////////////////////////////////////////////////////////////////
//
// File: AQuaternion.h.h
//
// Copyright (c) 2018 Knowles Electronics, LLC. All rights reserved.
// THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
// SEE ALSO License.txt
//
////////////////////////////////////////////////////////////////////////////////

#if defined(AVL_GENERIC)

 #include "Generic/AQuaternion.h"

#elif defined(AVL_HEMI)

 #include "Hemi/AQuaternion.h"

#elif defined(AVL_DMX1A)

 #include "DMX1A/AQuaternion.h"

#elif defined(AVL_DELTAMAX)

 #include "DeltaMax/AQuaternion.h"

#endif
