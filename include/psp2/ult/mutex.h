/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_MUTEX_H_
#define _DOLCESDK_PSP2_ULT_MUTEX_H_

#include <psp2/ult/error.h>
#include <psp2/ult/common.h>
#include <psp2/ult/resource_pool.h>

#define _SCE_ULT_MUTEX_OPT_PARAM_SIZE     128
#define SCE_ULT_MUTEX_OPT_PARAM_ALIGNMENT 8

#define SCE_ULT_MUTEX_ATTRIBUTE_RECURSIVE 0x1

#define _SCE_ULT_MUTEX_SIZE               256
#define SCE_ULT_MUTEX_ALIGNMENT           8

#define _SCE_ULT_MUTEX_INFO_SIZE          128
#define SCE_ULT_MUTEX_INFO_ALIGNMENT      8

typedef _SCE_ALIGN_BEG(SCE_ULT_MUTEX_OPT_PARAM_ALIGNMENT) struct SceUltMutexOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint32_t attribute;
	uint32_t __reserved__0;
	uint64_t __reserved__[ (_SCE_ULT_MUTEX_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader) - sizeof(uint32_t)*2)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_MUTEX_OPT_PARAM_ALIGNMENT) SceUltMutexOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_MUTEX_ALIGNMENT) struct SceUltMutex {
	uint64_t __reserved__[_SCE_ULT_MUTEX_SIZE / sizeof(uint64_t)];
} _SCE_ALIGN_END(SCE_ULT_MUTEX_ALIGNMENT) SceUltMutex;

typedef _SCE_ALIGN_BEG(SCE_ULT_MUTEX_INFO_ALIGNMENT) struct SceUltMutexInfo {
	uint32_t size;
	uint32_t mutexId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t attribute;
	uint32_t waitingQueueResourcePoolId;
	uint32_t currentOwnerId;
	uint32_t recursiveLockCount;
	uint32_t numWaitThreads;
	int32_t currentOwnerThreadType;
	uint64_t reserved[ (_SCE_ULT_MUTEX_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*5 - sizeof(int32_t))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_MUTEX_INFO_ALIGNMENT) SceUltMutexInfo;

#if defined(__cplusplus)
extern "C" {
#endif

int32_t _sceUltMutexOptParamInitialize(SceUltMutexOptParam *optParam, uint32_t buildVersion);

static __inline__ int32_t sceUltMutexOptParamInitialize(SceUltMutexOptParam *optParam) {
	return _sceUltMutexOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

int32_t _sceUltMutexCreate(
	SceUltMutex *mutex,
	const char* name,
	SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
	const SceUltMutexOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int32_t sceUltMutexCreate(
		SceUltMutex *mutex,
		const char* name,
		SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
		const SceUltMutexOptParam *optParam) {
	return _sceUltMutexCreate(mutex, name, waitingQueueResourcePool, optParam, _SCE_ULT_VERSION);
}

int32_t sceUltMutexLock(SceUltMutex *mutex);

int32_t sceUltMutexTryLock(SceUltMutex *mutex);

int32_t sceUltMutexUnlock(SceUltMutex *mutex);

int32_t sceUltMutexDestroy(SceUltMutex *mutex);

int32_t sceUltGetMutexInfo(
	const SceUltMutex *mutex,
	SceUltMutexInfo *pInfo,
	SceUltWaitThreadInfo *waitThreadInfoList,
	const uint32_t maxNumThreadInfo);

#if defined(__cplusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_ULT_MUTEX_H_ */
