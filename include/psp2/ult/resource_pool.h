/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_RESOURCE_POOL_H_
#define _DOLCESDK_PSP2_ULT_RESOURCE_POOL_H_

#include <psp2/ult/error.h>
#include <psp2/ult/common.h>

#define _SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_OPT_PARAM_SIZE     128
#define SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_OPT_PARAM_ALIGNMENT 8

#define _SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_SIZE               256
#define SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_ALIGNMENT           8

#define _SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_INFO_SIZE          128
#define SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_INFO_ALIGNMENT      8

#define _SCE_ULT_QUEUE_DATA_RESOURCE_POOL_OPT_PARAM_SIZE        128
#define SCE_ULT_QUEUE_DATA_RESOURCE_POOL_OPT_PARAM_ALIGNMENT    8

#define _SCE_ULT_QUEUE_DATA_RESOURCE_POOL_SIZE                  256
#define SCE_ULT_QUEUE_DATA_RESOURCE_POOL_ALIGNMENT              8

#define _SCE_ULT_QUEUE_DATA_RESOURCE_POOL_INFO_SIZE             128
#define SCE_ULT_QUEUE_DATA_RESOURCE_POOL_INFO_ALIGNMENT         8

typedef _SCE_ALIGN_BEG(SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_OPT_PARAM_ALIGNMENT) struct SceUltWaitingQueueResourcePoolOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint64_t __reserved__[ (_SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_OPT_PARAM_ALIGNMENT) SceUltWaitingQueueResourcePoolOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_ALIGNMENT) struct SceUltWaitingQueueResourcePool {
	uint64_t __reserved__[_SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_SIZE / sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_ALIGNMENT) SceUltWaitingQueueResourcePool;

typedef _SCE_ALIGN_BEG(SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_INFO_ALIGNMENT) struct SceUltWaitingQueueResourcePoolInfo {
	uint32_t size;
	uint32_t waitingQueueResourcePoolId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t numThreads;
	uint32_t maxNumThreads;
	uint32_t numSyncObjects;
	uint32_t maxNumSyncObjects;
	uint64_t reserved[ (_SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*4)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_WAITING_QUEUE_RESOURCE_POOL_INFO_ALIGNMENT) SceUltWaitingQueueResourcePoolInfo;

typedef _SCE_ALIGN_BEG(SCE_ULT_QUEUE_DATA_RESOURCE_POOL_OPT_PARAM_ALIGNMENT) struct SceUltQueueDataResourcePoolOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint64_t __reserved__[ (_SCE_ULT_QUEUE_DATA_RESOURCE_POOL_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_QUEUE_DATA_RESOURCE_POOL_OPT_PARAM_ALIGNMENT) SceUltQueueDataResourcePoolOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_QUEUE_DATA_RESOURCE_POOL_ALIGNMENT) struct SceUltQueueDataResourcePool {
	uint64_t __reserved__[_SCE_ULT_QUEUE_DATA_RESOURCE_POOL_SIZE / sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_QUEUE_DATA_RESOURCE_POOL_ALIGNMENT) SceUltQueueDataResourcePool;

typedef _SCE_ALIGN_BEG(SCE_ULT_QUEUE_DATA_RESOURCE_POOL_INFO_ALIGNMENT) struct SceUltQueueDataResourcePoolInfo {
	uint32_t size;
	uint32_t queueDataResourcePoolId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t waitingQueueResourcePoolId;
	uint32_t dataSize;
	uint32_t numData;
	uint32_t maxNumData;
	uint32_t numQueueObjects;
	uint32_t maxNumQueueObjects;
	uint64_t reserved[ (_SCE_ULT_QUEUE_DATA_RESOURCE_POOL_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*6)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_QUEUE_DATA_RESOURCE_POOL_INFO_ALIGNMENT) SceUltQueueDataResourcePoolInfo;

#if defined(__cplusplus)
extern "C" {
#endif

int32_t _sceUltWaitingQueueResourcePoolOptParamInitialize(SceUltWaitingQueueResourcePoolOptParam *optParam, uint32_t buildVersion);

static __inline__ int32_t sceUltWaitingQueueResourcePoolOptParamInitialize(SceUltWaitingQueueResourcePoolOptParam *optParam) {
	return _sceUltWaitingQueueResourcePoolOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

uint32_t sceUltWaitingQueueResourcePoolGetWorkAreaSize(uint32_t numThreads, uint32_t numSyncObjects);

int _sceUltWaitingQueueResourcePoolCreate(
	SceUltWaitingQueueResourcePool *pool,
	const char* name,
	uint32_t numThreads,
	uint32_t numSyncObjects,
	void* workArea,
	const SceUltWaitingQueueResourcePoolOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int sceUltWaitingQueueResourcePoolCreate(
		SceUltWaitingQueueResourcePool *pool,
		const char* name,
		uint32_t numThreads,
		uint32_t numSyncObjects,
		void* workArea,
		const SceUltWaitingQueueResourcePoolOptParam *optParam) {
	return _sceUltWaitingQueueResourcePoolCreate(pool, name, numThreads, numSyncObjects, workArea, optParam, _SCE_ULT_VERSION);
}

int sceUltWaitingQueueResourcePoolDestroy(SceUltWaitingQueueResourcePool *pool);

int32_t sceUltGetWaitingQueueResourcePoolInfo(const SceUltWaitingQueueResourcePool *pool, SceUltWaitingQueueResourcePoolInfo *pInfo);

int32_t _sceUltQueueDataResourcePoolOptParamInitialize(SceUltQueueDataResourcePoolOptParam *optParam, uint32_t buildVersion);

static __inline__ int32_t sceUltQueueDataResourcePoolOptParamInitialize(SceUltQueueDataResourcePoolOptParam *optParam) {
	return _sceUltQueueDataResourcePoolOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

uint32_t sceUltQueueDataResourcePoolGetWorkAreaSize(uint32_t numData, uint32_t dataSize, uint32_t numQueueObject);

int _sceUltQueueDataResourcePoolCreate(
	SceUltQueueDataResourcePool *pool,
	const char* name,
	uint32_t numData,
	uint32_t dataSize,
	uint32_t numQueueObject,
	SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
	void* workArea,
	const SceUltQueueDataResourcePoolOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int sceUltQueueDataResourcePoolCreate(
		SceUltQueueDataResourcePool *pool,
		const char* name,
		uint32_t numData,
		uint32_t dataSize,
		uint32_t numQueueObject,
		SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
		void* workArea,
		const SceUltQueueDataResourcePoolOptParam *optParam) {
	return _sceUltQueueDataResourcePoolCreate(pool, name, numData, dataSize, numQueueObject, waitingQueueResourcePool, workArea, optParam, _SCE_ULT_VERSION);
}

int sceUltQueueDataResourcePoolDestroy(SceUltQueueDataResourcePool *pool);

int32_t sceUltGetQueueDataResourcePoolInfo(const SceUltQueueDataResourcePool *pool, SceUltQueueDataResourcePoolInfo *pInfo);

#if defined(__cplusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_ULT_RESOURCE_POOL_H_ */
