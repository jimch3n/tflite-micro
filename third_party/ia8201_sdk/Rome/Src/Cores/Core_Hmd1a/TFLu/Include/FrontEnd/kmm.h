/************************************************************************//**
* @file  kmm.h
*
* @brief Provides the public interface for the kmm module
*
* Contains definitions of public types and functions for using the kmm 
* (Knowles Memory Management) module.  The kmm module is tightly coupled with
* ksp library modules in the sense that all memory allocation in ksp modules
* MUST be done via kmm.
*
* KMM is a memory management library that allows simple allocation functions
* for typical users.  For system developers, it allows two modes of operation:
*
*   1. buffered -- memory management using a user supplied buffer
*   2. counting -- counts memory usage without allocating
*
* The counting mode exists to enable calculation of the buffer sizes needed
* for buffered mode, and works with the expectation that module creation logic
* will make all the allocation calls in count mode that it would make in
* buffered mode, but skip associated initialization of the pointers returned
* since they would not be backed by actual storage.  In practice, the creation
* code for a given module accumulates returned pointers on the stack then
* checks via a single status result whether it is safe to collectively
* initialize the memory allocated for that module.
*
* KMM support two allocation pools, one for persistent 'state' allocations,
* and one for 'scratch' allocations, the latter a stack-style sharing of
* memory windows tied to function calling chains.
*
* @seealso
* Put references to (names of) other relevant files here
*
* @info
* $Author: jimchen $
* $DateTime: 2022/07/13 02:57:03 $
* $Revision: #1 $
* $Id: //AudEngr/AlgoSW/Product/sdk-support-TFuL-dev/Rome/Src/Cores/Core_Hmd1a/TFLu/Include/FrontEnd/kmm.h#1 $
*
* @copyright
* Copyright (c) 2016 by Knowles Corporation. All rights reserved.
*
* This software is the confidential and proprietary information of Knowles
* Corporation. ("Confidential Information"). You shall not disclose such
* Confidential Information and shall use it only in accordance with the Terms
* of Sale of Knowles Corporation products and the terms of any license
* agreement you entered into with Knowles Corporation for such products.
*
* KNOWLES CORPORATION SOURCE CODE STRICTLY "AS IS" WITHOUT ANY WARRANTY
* WHATSOEVER, AND KNOWLES CORPORATION EXPRESSLY DISCLAIMS ALL WARRANTIES,
* EXPRESS, IMPLIED OR STATUTORY WITH REGARD THERETO, INCLUDING THE IMPLIED
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR
* NON-INFRINGEMENT OF THIRD PARTY RIGHTS. KNOWLES CORPORATION SHALL NOT BE
* LIABLE FOR ANY DAMAGES SUFFERED BY YOU AS A RESULT OF USING, MODIFYING OR
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
****************************************************************************/

#ifndef KMM_H
#define KMM_H

//#define KMM_PROFILE   // Enable this macro to capture and dump memory profile information

//#ifdef __XTENSA__   // Force disable memory profiling for Xtensa mode, as a precaution.
//#ifdef KMM_PROFILE
//#undef KMM_PROFILE
//#endif
//#endif

#ifdef KMM_PROFILE
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _MSC_VER
#define EXPORTED_FUNCTION __declspec(dllexport)
#else
#define EXPORTED_FUNCTION 
#endif

/******************  External/default library includes  *********************/
#include <stdint.h>
#include <stdlib.h>  // Needed for size_t, not functions.

/******************  Knowles support includes  ******************************/

#ifdef  __cplusplus
extern "C" {
#endif  //  __cplusplus
/******************  Local typedefs *****************************************/
typedef enum {
    KMM_SUCCESS      = 0,
    KMM_FAILURE      = 1,
    KMM_FAILURE_USER = 2,
} kmm_status_t;

/* KMM alignment spec for allocations. */
typedef enum {
    KMM_ALIGN_1  = 1,
    KMM_ALIGN_2  = 2,
    KMM_ALIGN_4  = 4,
    KMM_ALIGN_8  = 8,
    KMM_ALIGN_16 = 16,
    KMM_ALIGN_32 = 32,
} kmm_align_t;
#define KMM_ALIGN_PTR (sizeof(void*))  /* alignof(void*) */

/* Advances a pointer (or size) to meet alignment requirements. */
#define KMM_ALIGNUP(x, a) ((((uintptr_t)(x))+((a)-1)) & ~(((uintptr_t)(a))-1))

#ifdef KMM_PROFILE

#define kmm_allocate(HKMM, SIZE, ALIGN) \
  kmm_allocate_internal(HKMM, SIZE, ALIGN, __FUNCTION__, __FILE__, __LINE__)

#define kmm_scratch_allocate(HKMM, SIZE, ALIGN) \
  kmm_scratch_allocate_internal(HKMM, SIZE, ALIGN, __FUNCTION__, __FILE__, __LINE__)

#define INIT_VAR(X,Y) init_##X_##Y
#define kmm_dump_data_scratch_once(SUFFIX, DSIZE, MODULE) do {\
	static int INIT_VAR(SUFFIX,MODULE) = 0;\
	if(! INIT_VAR(SUFFIX,MODULE) ){ kmm_dump_data_scratch(#SUFFIX, DSIZE, #MODULE);\
			 INIT_VAR(SUFFIX,MODULE) = 1;\
	}\
	}while(0)

// linked-list
enum {
    KMM_PERSIST_T,
    KMM_SCRATCH_T
};
struct kmm_prof_t
{
    int memType; //scratch or persist
    char typeName[0x100];
    char funcName[0x100];
    char bufferName[0x100];
    char fileName[0x100];
    uint32_t size;
    uint32_t align;
    uint32_t pointer;
    long line;
    struct kmm_prof_t *pNext;
};

EXPORTED_FUNCTION void kmm_set_profile(struct kmm_prof_t *pSrc);
#endif  //KMM_PROFILE

/*****************************************************************************
* kmm_State_t exists to enable easy allocation of the storage backing
* a KMM instance, but should not be construed as an invitation to
* read/write KMM internals.  Use the public interface.
*****************************************************************************/
typedef struct kmm_ab {
    size_t   a;
    size_t   b;
    uint8_t *c;
    size_t   d;
} kmm_ab_t;
typedef struct kmm_State {
    kmm_ab_t a;
    kmm_ab_t b;
    uint32_t c;
    uint32_t d;
    void    *e;
#ifdef KMM_PROFILE
    struct kmm_prof_t *f;
#endif
} kmm_State_t;

typedef struct kmm_State *kmm_Handle_t;

/******************  Public Functions ***************************************/

/*****************************************************************************
* kmm_allocate
*************************************************************************//**
* Allocates persist memory to the specified alignment.
*
* Convention is to retain returned pointer for use but not check its
* value as a measure of success.  See kmm_get_allocation_status().
*
* @param[in]  size       Bytes to allocate.
* @param[in]  alignment  Desired alignment, which must be a power of 2.
*
* @returns    pMem       Pointer to allocated memory on success,
*                        or 0 on failure (the norm for count mode).
*****************************************************************************/
#ifndef KMM_PROFILE
EXPORTED_FUNCTION void* kmm_allocate(
    kmm_Handle_t hKmm,
    size_t size,
    size_t alignment
);
#else
EXPORTED_FUNCTION void* kmm_allocate_internal(
    kmm_Handle_t hKmm,
    size_t size,
    size_t alignment,
    const char *func,
	const char *file,
    long line
);

EXPORTED_FUNCTION void kmm_prof_dump(struct kmm_prof_t *pf, const char *suffixName);
EXPORTED_FUNCTION void kmm_prof_free(struct kmm_prof_t *pf);
#endif

/*****************************************************************************
* kmm_scratch_allocate
*************************************************************************//**
* Allocates scratch memory to the specified alignment.
*
* Convention is to retain returned pointer for use but not check its
* value as a measure of success.  See kmm_get_allocation_status().
*
* @param[in]  size       Bytes to allocate.
* @param[in]  alignment  Desired alignment, which must be a power of 2.
*
* @returns    pMem       Pointer to allocated memory on success,
*                        or 0 on failure (the norm for count mode).
*****************************************************************************/
#ifndef KMM_PROFILE
EXPORTED_FUNCTION void* kmm_scratch_allocate(
    kmm_Handle_t hKmm,
    size_t size,
    size_t alignment
);
#else
EXPORTED_FUNCTION void* kmm_scratch_allocate_internal(
    kmm_Handle_t hKmm,
    size_t size,
    size_t alignment,
    const char *func,
	const char *file,
    long line);
EXPORTED_FUNCTION void kmm_dump_data_scratch(const char *suffixName, int dSize, const char *module);
EXPORTED_FUNCTION void kmm_dump_data_persist(struct kmm_prof_t *pf, const char *suffixName, int dSize);
#endif

/*****************************************************************************
* kmm_scratch_push
*************************************************************************//**
* Adds a frame to the scratch memory window stack, returning its byte offset.
* The typical flow for scratch allocation is:
*   kmm_scratch_push()
*   kmm_scratch_allocate() -- potentially multiple calls
*   kmm_scratch_pop()
*
* If a submodule needs scratch that does not step on that of the module,
* its creation function should be called before kmm_scratch_pop(), but
* after the last kmm_scratch_allocate() associated with memory that needs
* to be preserved across calls to the given submodule.
*
* @param[in]  hKmm               Handle for KMM instance.
*
* @returns    byteCountFromPush  Provide this to matched kmm_scratch_pop().
*****************************************************************************/
size_t kmm_scratch_push(const kmm_Handle_t hKmm);

/*****************************************************************************
* kmm_scratch_pop
*************************************************************************//**
* Discards the scratch memory window stack frame created by a corresponding
* kmm_scratch_push(), reverting the allocation pointer used for new scratch
* allocations to where it was when the frame was created.  Does not revert
* accumulated requirements.  See kmm_get_buffer_requirements().
*
* @param[in]  hKmm               Handle to initialized KMM instance.
* @param[in]  byteCountFromPush  Return value from kmm_scratch_push().
*
* @returns    void
*****************************************************************************/
void kmm_scratch_pop(
    kmm_Handle_t hKmm,
    size_t byteCountFromPush
);

/*****************************************************************************
* kmm_get_allocation_status
*************************************************************************//**
* Returns cumulative allocation status.  If KMM_SUCCESS is returned, then
* all allocation attempts made so far, from either user provided buffer,
* have returned valid addresses.
*
* Convention is to front load a module creation function with allocations,
* then mass initialize the memory returned by those allocation at the
* end of said function if a single kmm_get_allocation_status() returns
* KMM_SUCCESS at that point, storing pointers on the stack until then.
* The convention is not required, but it aligns with efficiency and
* the needs of count mode.  See kmm_init_count_mode().
*
* @param[in]  hKmm    Handle to KMM instance.
*
* @returns    status  kmm_status_t accumulated by allocation attempts.
*****************************************************************************/
kmm_status_t kmm_get_allocation_status(const kmm_Handle_t hKmm);

/*****************************************************************************
* kmm_set_allocation_status_to_failure
*************************************************************************//**
* Sets cumulative allocation status to KMM_FAILURE_USER.
*
* Intended usage is to register a violated creation assertion,
* independent of memory availability.
*
* @param[in]  hKmm  Handle to KMM instance.
*
* @returns    void
*****************************************************************************/
void kmm_set_allocation_status_to_failure(kmm_Handle_t hKmm);

/*****************************************************************************
* kmm_get_context
*************************************************************************//**
* Returns user context set by kmm_set_context(), otherwise 0.
*
* @param[in]  hKmm  Handle to KMM instance.
*
* @returns    pCtx  User context pointer.
*****************************************************************************/
void *kmm_get_context(const kmm_Handle_t hKmm);

/*****************************************************************************
* kmm_set_context
*************************************************************************//**
* Sets user context.
*
* Intended usage is to propagate an optional user (system) context to
* a hierarchy of modules at the time of their creation, with the logic
* responsible for that creation being able to access this context through
* the instance of KMM already needed for allocation purposes.
*
* @param[in]  hKmm  Handle to KMM instance.
* @param[in]  pCtx  User context pointer.
*
* @returns    void
*****************************************************************************/
void kmm_set_context(
    kmm_Handle_t hKmm,
    const void *pCtx);

/*****************************************************************************
* kmm_get_buffer_requirements
*************************************************************************//**
* Return cumulative buffer requirements.
*
* @param[in]   hKmm               Handle to count mode KMM instance against
*                                 which allocations have been attempted.
* @param[out]  pPersistByteCount  Number of bytes of persist memory required.
* @param[out]  pPersistMinAlign   Minimum alignment required for persist.
* @param[out]  pScratchByteCount  Number of bytes of scratch memory required.
* @param[out]  pScratchMinAlign   Minimum alignment required for scratch.
*
* @returns     void
*****************************************************************************/
void kmm_get_buffer_requirements(
    const kmm_Handle_t hKmm,
    size_t *pPersistByteCount,
    size_t *pPersistMinAlign,
    size_t *pScratchByteCount,
    size_t *pScratchMinAlign);

/*****************************************************************************
* kmm_get_instance_requirements
*************************************************************************//**
* Provides requirements for storage appropriate to pass to
* kmm_init_buffer_mode(), kmm_init_count_mode(), or kmm_clone()
* for the purpose of backing the initialization of a KMM instance.
*
* While kmm_State_t exists to support easy creation of a KMM instance
* on the client stack, kmm_get_instance_requirements() exists to
* support the client heap equivalent.  In both cases, the storage
* is for the KMM instance itself, not any persist or scratch buffers
* bound to that instance.
*
* @param[out]  pByteCount  Size of a KMM instance in bytes.
* @param[out]  pMinAlign   Minimum alignment required for a KMM instance.
*
* @returns    void
*****************************************************************************/
void kmm_get_instance_requirements(
    size_t *pByteCount,
    size_t *pMinAlign);

/*****************************************************************************
* kmm_init_buffer_mode
*************************************************************************//**
* Initializes a KMM instance for buffer mode.  User context is set to 0.
*
* When in buffer mode, allocations will return valid pointer addresses
* if, at the end of an allocation, the cumulative allocation status is
* still KMM_SUCCESS.
*
* A KMM instance initialized into buffer mode will start with its
* allocation status set to KMM_SUCCESS.  If the cumulative attempted
* consumption of either user provided buffer exceeds its respective size,
* and kmm_set_allocation_status_to_failure() has not already been used
* to set allocation status to KMM_FAILURE_USER, that status will be set
* KMM_FAILURE.
*
* @param[in]  hKmm            Handle to storage to initialize
*                             as a KMM instance.
* @param[in]  pPersistBuf     pointer to persist memory buffer.
* @param[in]  sizePersistBuf  size of persist memory buffer.
* @param[in]  pScratchBuf     pointer to scratch memory buffer.
* @param[in]  sizeScratchBuf  size of scratch memory buffer.
*
* @returns    void
*****************************************************************************/
void kmm_init_buffer_mode(
    kmm_Handle_t hKmm,
    const void *pPersistBuf,
    size_t sizePersistBuf,
    const void *pScratchBuf,
    size_t sizeScratchBuf);

/*****************************************************************************
* kmm_init_count_mode
*************************************************************************//**
* Initializes a KMM instance for count mode.  User context is set to 0.
*
* When in count mode, allocations will not return valid pointer addresses,
* but the act of allocation will advance counters and alignment tracking
* such that when done "allocating", kmm_get_buffer_requirements() can be
* called to retrieve requirements for buffers that will enable proper
* allocation if passed to kmm_init_buffer_mode().
*
* A KMM instance initialized into count mode will start with its allocation
* status set to KMM_FAILURE.  Requirements should not be considered correct
* if final allocation status, accessible by kmm_get_allocation_status(),
* is KMM_FAILURE_USER rather than KMM_FAILURE.
*
* @param[in]  hKmm  Handle to storage to initialize as a KMM instance.
*
* @returns    void
*****************************************************************************/
void kmm_init_count_mode(kmm_Handle_t hKmm);

/*****************************************************************************
* kmm_reset
*************************************************************************//**
* Except for user context, re-initializes the KMM instance to original values
* for its existing mode.  Essentially, the instance is left to start over.
*
* @param[in]  hKmm  Handle to KMM instance to reset.
*
* @returns    void
*****************************************************************************/
void kmm_reset(kmm_Handle_t hKmm);

/*****************************************************************************
* kmm_clone
*************************************************************************//**
* Copies a KMM instance, generally for save and restore purposes.
*
* @param[in]  hDst  Handle to storage to copy KMM instance into.
* @param[in]  hSrc  Handle to existing KMM instance.
*
* @returns    void
*****************************************************************************/
void kmm_clone(
    kmm_Handle_t hDst,
    const kmm_Handle_t hSrc);

#ifdef  __cplusplus
}
#endif  //  __cplusplus

#endif // KMM_H
