/**
 * \usergroup{SceGxm}
 * \usage{psp2/gxm.h,SceGxm_stub}
 */

#include <psp2/types.h>

#ifndef _DOLCESDK_PSP2_GXM_FUNCTYPES_H_
#define _DOLCESDK_PSP2_GXM_FUNCTYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * GXM context
 */

typedef void* (*SceGxmDeferredContextCallback)(void* userData, uint32_t minSize, uint32_t *size);

/**
 * Display queue
 */

typedef void (* SceGxmDisplayQueueCallback)(const void *callbackData);

/**
 * Shader programs
 */

typedef void *(* SceGxmShaderPatcherHostAllocCallback)(void *userData, uint32_t size);

typedef void (* SceGxmShaderPatcherHostFreeCallback)(void *userData, void *mem);

typedef void *(* SceGxmShaderPatcherBufferAllocCallback)(void *userData, uint32_t size);

typedef void (* SceGxmShaderPatcherBufferFreeCallback)(void *userData, void *mem);

typedef void *(* SceGxmShaderPatcherUsseAllocCallback)(void *userData, uint32_t size, uint32_t *usseOffset);

typedef void (* SceGxmShaderPatcherUsseFreeCallback)(void *userData, void *mem);

#ifdef __cplusplus
}
#endif

#endif
