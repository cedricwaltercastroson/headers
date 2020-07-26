/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_SEMAPHORE_H_
#define _DOLCESDK_PSP2_ULT_SEMAPHORE_H_

#include <psp2/ult/error.h>
#include <psp2/ult/common.h>
#include <psp2/ult/resource_pool.h>

#define _SCE_ULT_SEMAPHORE_OPT_PARAM_SIZE     128
#define SCE_ULT_SEMAPHORE_OPT_PARAM_ALIGNMENT 8

#define _SCE_ULT_SEMAPHORE_SIZE               256
#define SCE_ULT_SEMAPHORE_ALIGNMENT           8

#define _SCE_ULT_SEMAPHORE_INFO_SIZE          128
#define SCE_ULT_SEMAPHORE_INFO_ALIGNMENT      8

typedef _SCE_ALIGN_BEG(SCE_ULT_SEMAPHORE_OPT_PARAM_ALIGNMENT) struct SceUltSemaphoreOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint64_t  __reserved__[ (_SCE_ULT_SEMAPHORE_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_SEMAPHORE_OPT_PARAM_ALIGNMENT) SceUltSemaphoreOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_SEMAPHORE_ALIGNMENT) struct SceUltSemaphore {
	uint64_t __reserved__[_SCE_ULT_SEMAPHORE_SIZE / sizeof(uint64_t)];
} _SCE_ALIGN_END(SCE_ULT_SEMAPHORE_ALIGNMENT) SceUltSemaphore;

typedef struct _SCE_ALIGN_BEG(SCE_ULT_SEMAPHORE_INFO_ALIGNMENT) SceUltSemaphoreInfo {
	uint32_t size;
	uint32_t semaphoreId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t waitingQueueResourcePoolId;
	uint32_t numCurrentResource;
	uint32_t numWaitThreads;
	uint32_t reserved0;
	uint64_t reserved[ (_SCE_ULT_SEMAPHORE_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*4)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_SEMAPHORE_INFO_ALIGNMENT) SceUltSemaphoreInfo;

#if defined(__cplusplus)
extern "C" {
#endif

int _sceUltSemaphoreOptParamInitialize(SceUltSemaphoreOptParam *optParam, uint32_t buildVersion);

static __inline__ int sceUltSemaphoreOptParamInitialize(SceUltSemaphoreOptParam *optParam) {
	return _sceUltSemaphoreOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

int _sceUltSemaphoreCreate(
	SceUltSemaphore *semaphore,
	const char* name,
	int32_t  numInitialResource,
	SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
	const SceUltSemaphoreOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int sceUltSemaphoreCreate(
		SceUltSemaphore *semaphore,
		const char* name,
		int32_t  numInitialResource,
		SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
		const SceUltSemaphoreOptParam *optParam) {
	return _sceUltSemaphoreCreate(semaphore, name, numInitialResource, waitingQueueResourcePool, optParam, _SCE_ULT_VERSION);
}

int sceUltSemaphoreAcquire(SceUltSemaphore *semaphore, int32_t numResource);

int sceUltSemaphoreTryAcquire(SceUltSemaphore *semaphore, int32_t numResource);

int sceUltSemaphoreRelease(SceUltSemaphore *semaphore, int32_t numResource);

int sceUltSemaphoreDestroy(SceUltSemaphore *semaphore);

int32_t sceUltGetSemaphoreInfo(
	const SceUltSemaphore *semaphore,
	SceUltSemaphoreInfo *pInfo,
	SceUltWaitThreadInfo *waitThreadInfoList,
	const uint32_t maxNumThreadInfo);

#if defined(__cplusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_ULT_SEMAPHORE_H_ */
