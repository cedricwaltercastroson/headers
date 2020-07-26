/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_QUEUE_H_
#define _DOLCESDK_PSP2_ULT_QUEUE_H_

#include <psp2/ult/error.h>
#include <psp2/ult/common.h>
#include <psp2/ult/resource_pool.h>

#define _SCE_ULT_QUEUE_OPT_PARAM_SIZE     128
#define SCE_ULT_QUEUE_OPT_PARAM_ALIGNMENT 8

#define _SCE_ULT_QUEUE_SIZE               256
#define SCE_ULT_QUEUE_ALIGNMENT           8

#define _SCE_ULT_QUEUE_INFO_SIZE          128
#define SCE_ULT_QUEUE_INFO_ALIGNMENT      8

typedef _SCE_ALIGN_BEG(SCE_ULT_QUEUE_OPT_PARAM_ALIGNMENT) struct SceUltQueueOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint64_t __reserved__[ (_SCE_ULT_QUEUE_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_QUEUE_OPT_PARAM_ALIGNMENT) SceUltQueueOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_QUEUE_ALIGNMENT) struct SceUltQueue {
	uint64_t __reserved__[_SCE_ULT_QUEUE_SIZE / sizeof(uint64_t)];
} _SCE_ALIGN_END(SCE_ULT_QUEUE_ALIGNMENT) SceUltQueue;

typedef _SCE_ALIGN_BEG(SCE_ULT_QUEUE_INFO_ALIGNMENT) struct SceUltQueueInfo {
	uint32_t size;
	uint32_t queueId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t waitingQueueResourcePoolId;
	uint32_t queueDataResourcePoolId;
	uint32_t dataSize;
	uint32_t numData;
	uint32_t numPushWaitThreads;
	uint32_t numPopWaitThreads;
	uint64_t reserved[ (_SCE_ULT_QUEUE_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*6)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_QUEUE_INFO_ALIGNMENT) SceUltQueueInfo;

#if defined(__cplusplus)
extern "C" {
#endif

int _sceUltQueueOptParamInitialize(SceUltQueueOptParam *optParam, uint32_t buildVersion);

static __inline__ int sceUltQueueOptParamInitialize(SceUltQueueOptParam *optParam) {
	return _sceUltQueueOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

int _sceUltQueueCreate(
	SceUltQueue *queue,
	const char* _name,
	uint32_t  dataSize,
	SceUltWaitingQueueResourcePool *resourcePool,
	SceUltQueueDataResourcePool* queueResourcePool,
	const SceUltQueueOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int sceUltQueueCreate(
		SceUltQueue *queue,
		const char* name,
		uint32_t  dataSize,
		SceUltQueueDataResourcePool* queueResourcePool,
		SceUltWaitingQueueResourcePool *resourcePool,
		const SceUltQueueOptParam *optParam) {
	return _sceUltQueueCreate(queue, name, dataSize, resourcePool, queueResourcePool, optParam, _SCE_ULT_VERSION);
}

int sceUltQueuePush    (SceUltQueue *queue,	 const void* data);
int sceUltQueueTryPush (SceUltQueue *queue,	 const void* data);
int sceUltQueuePop     (SceUltQueue *queue,	 void* data);
int sceUltQueueTryPop  (SceUltQueue *queue,	 void* data);
int sceUltQueueDestroy (SceUltQueue *queue);

int32_t sceUltGetQueueInfo(
	const SceUltQueue *queue,
	SceUltQueueInfo *pInfo,
	SceUltWaitThreadInfo *waitThreadInfoList,
	const uint32_t maxNumThreadInfo);

#if defined(__cplusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_ULT_QUEUE_H_ */
