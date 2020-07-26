/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_READER_WRITER_LOCK_H_
#define _DOLCESDK_PSP2_ULT_READER_WRITER_LOCK_H_

#include <psp2/ult/error.h>
#include <psp2/ult/common.h>
#include <psp2/ult/resource_pool.h>

#define _SCE_ULT_READER_WRITER_LOCK_OPT_PARAM_SIZE     128
#define SCE_ULT_READER_WRITER_LOCK_OPT_PARAM_ALIGNMENT 8

#define _SCE_ULT_READER_WRITER_LOCK_SIZE               256
#define SCE_ULT_READER_WRITER_LOCK_ALIGNMENT           8

#define _SCE_ULT_READER_WRITER_LOCK_INFO_SIZE          128
#define SCE_ULT_READER_WRITER_LOCK_INFO_ALIGNMENT      8

typedef _SCE_ALIGN_BEG(SCE_ULT_READER_WRITER_LOCK_OPT_PARAM_ALIGNMENT) struct SceUltReaderWriterLockOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint64_t __reserved__[ (_SCE_ULT_READER_WRITER_LOCK_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_READER_WRITER_LOCK_OPT_PARAM_ALIGNMENT) SceUltReaderWriterLockOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_READER_WRITER_LOCK_ALIGNMENT) struct SceUltReaderWriterLock {
	uint64_t __reserved__[_SCE_ULT_READER_WRITER_LOCK_SIZE / sizeof(uint64_t)];
} _SCE_ALIGN_END(SCE_ULT_READER_WRITER_LOCK_ALIGNMENT) SceUltReaderWriterLock;

typedef _SCE_ALIGN_BEG(SCE_ULT_READER_WRITER_LOCK_INFO_ALIGNMENT) struct SceUltReaderWriterLockInfo {
	uint32_t size;
	uint32_t rwLockId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t waitingQueueResourcePoolId;
	uint32_t lockStatus;
	uint32_t numLockingReaders;
	uint32_t writeOwnerId;
	uint32_t numWaitThreads;
	int32_t writeOwnerThreadType;
	uint64_t reserved[ (_SCE_ULT_READER_WRITER_LOCK_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*5 - sizeof(int32_t))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_READER_WRITER_LOCK_INFO_ALIGNMENT) SceUltReaderWriterLockInfo;

#if defined(__cplusplus)
extern "C" {
#endif

int32_t _sceUltReaderWriterLockOptParamInitialize(
	SceUltReaderWriterLockOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int32_t sceUltReaderWriterLockOptParamInitialize(SceUltReaderWriterLockOptParam *optParam) {
	return _sceUltReaderWriterLockOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

int _sceUltReaderWriterLockCreate(
	SceUltReaderWriterLock *rwlock,
	const char* name,
	SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
	const SceUltReaderWriterLockOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int sceUltReaderWriterLockCreate(
		SceUltReaderWriterLock *rwlock,
		const char* name,
		SceUltWaitingQueueResourcePool *waitingQueueResourcePool,
		const SceUltReaderWriterLockOptParam *optParam) {
	return _sceUltReaderWriterLockCreate(rwlock, name, waitingQueueResourcePool, optParam, _SCE_ULT_VERSION);
}

int sceUltReaderWriterLockLockRead(SceUltReaderWriterLock *rwlock);
int sceUltReaderWriterLockTryLockRead(SceUltReaderWriterLock *rwlock);
int sceUltReaderWriterLockUnlockRead(SceUltReaderWriterLock *rwlock);

int sceUltReaderWriterLockLockWrite(SceUltReaderWriterLock *rwlock);
int sceUltReaderWriterLockTryLockWrite(SceUltReaderWriterLock *rwlock);
int sceUltReaderWriterLockUnlockWrite(SceUltReaderWriterLock *rwlock);

int sceUltReaderWriterLockDestroy(SceUltReaderWriterLock *rwlock);

int32_t sceUltGetReaderWriterLockInfo(
	const SceUltReaderWriterLock *rwlock,
	SceUltReaderWriterLockInfo *pInfo,
	SceUltWaitThreadInfo *waitThreadInfoList,
	const uint32_t maxNumThreadInfo);

#if defined(__cplusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_ULT_RWLOCK_H_ */
