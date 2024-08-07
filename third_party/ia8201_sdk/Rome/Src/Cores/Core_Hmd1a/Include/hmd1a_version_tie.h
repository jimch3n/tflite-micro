// Customer ID=11582; Build=0x766db; Copyright (c) 2017 Cadence Design Systems, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/* Do not modify. This is automatically generated.*/

#ifndef _XTENSA_hmd1a_version_tie_h_HEADER
#define _XTENSA_hmd1a_version_tie_h_HEADER


/* Header includes start */

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

/* Header includes end */

#endif /* !_XTENSA_hmd1a_version_tie_h_HEADER */
