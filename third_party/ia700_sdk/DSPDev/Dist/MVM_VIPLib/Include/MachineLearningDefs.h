/************************************************************************//**
 * @file    MVM_VIPLib/Include/MachineLearningDefs.h
 *
 * @brief   Machine learning specific definitions used by more than one machine learning module.
 *
 * $DateTime: 2021/05/19 07:24:16 $
 * $Revision: #6 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MACHINE_LEARNING_DEFS_H__
#define __FILE_MACHINE_LEARNING_DEFS_H__

/****************************************************************************
 * Types
 ****************************************************************************/
#include "DeltaPlatform.h"

typedef VAR_ALIGN_4  int8_t  int8v4_aligned4[4];
typedef VAR_ALIGN_8  int8_t  int8v8_aligned8[8];
typedef VAR_ALIGN_16 int8_t  int8v16_aligned16[16];
typedef VAR_ALIGN_4  int16_t int16v2_aligned4[2];
typedef VAR_ALIGN_8  int16_t int16v4_aligned8[4];
typedef VAR_ALIGN_16 int16_t int16v8_aligned16[8];
typedef VAR_ALIGN_8  int32_t int32v2_aligned8[2];
typedef VAR_ALIGN_16 int32_t int32v4_aligned16[4];



#endif  /* __FILE_MACHINE_LEARNING_DEFS_H__ */



/* End of File */

