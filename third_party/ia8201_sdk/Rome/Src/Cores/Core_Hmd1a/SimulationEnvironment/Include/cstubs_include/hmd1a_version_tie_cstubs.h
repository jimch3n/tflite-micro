// Machine generated file - DO NOT EDIT!

#ifndef __cstub_hmd1a_version_tie_h__
#define __cstub_hmd1a_version_tie_h__

#include "hmd1a_common_tie_cstubs.h"


/* BASE VERSIONS */
/* DMX: 0x01 */
/* HMD: 0x02 */
/* SSP: 0x03 */

/* COMPANION CORES */
/* HiFi3: 0x01 */

#define AIS_CORE_DEFINITION_ITEM_BASE_VER 0x02
#define AIS_CORE_DEFINITION_ITEM_MAJOR_VER 0x01
#define AIS_CORE_DEFINITION_ITEM_MINOR_VER 0x01
#define AIS_CORE_DEFINITION_ITEM_COMPANION 0x01

#define AIS_CORE_DEFINITION_ITEM_VERSION ( \
       (AIS_CORE_DEFINITION_ITEM_BASE_VER << 24) | \
       (AIS_CORE_DEFINITION_ITEM_MAJOR_VER << 16) | \
       (AIS_CORE_DEFINITION_ITEM_MINOR_VER << 8) | \
       AIS_CORE_DEFINITION_ITEM_COMPANION)

#define AIS_CORE_DEFINITION_ITEM_VER_STRING "HMD1A"

#endif
