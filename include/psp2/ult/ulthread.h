/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_ULTHREAD_H_
#define _DOLCESDK_PSP2_ULT_ULTHREAD_H_

#include <psp2/fiber.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/ult/error.h>
#include <psp2/ult/common.h>

#define _SCE_ULT_ULTHREAD_RUNTIME_OPT_PARAM_SIZE     128
#define SCE_ULT_ULTHREAD_RUNTIME_OPT_PARAM_ALIGNMENT 8

#define _SCE_ULT_ULTHREAD_RUNTIME_SIZE               1024
#define SCE_ULT_ULTHREAD_RUNTIME_ALIGNMENT           8

#define _SCE_ULT_ULTHREAD_OPT_PARAM_SIZE             128
#define SCE_ULT_ULTHREAD_OPT_PARAM_ALIGNMENT         8

#define SCE_ULT_ULTHREAD_ATTRIBUTE_FORCE_WAIT        1

#define _SCE_ULT_ULTHREAD_SIZE                       256
#define SCE_ULT_ULTHREAD_ALIGNMENT                   8

#define _SCE_ULT_ULTHREAD_RUNTIME_INFO_SIZE          128
#define SCE_ULT_ULTHREAD_RUNTIME_INFO_ALIGNMENT      8

#define _SCE_ULT_ULTHREAD_INFO_SIZE                  256
#define SCE_ULT_ULTHREAD_INFO_ALIGNMENT              8

typedef _SCE_ALIGN_BEG(SCE_ULT_ULTHREAD_RUNTIME_OPT_PARAM_ALIGNMENT) struct SceUltUlthreadRuntimeOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint32_t  oneShotThreadStackSize;
	int32_t   workerThreadPriority;
	uint32_t  workerThreadCpuAffinityMask;
	uint32_t  workerThreadAttr;
	const SceKernelThreadOptParam* workerThreadOptParam;
	uint64_t __reserved__[ (_SCE_ULT_ULTHREAD_RUNTIME_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader) - sizeof(uint32_t) - sizeof(int32_t) - sizeof(uint32_t)*2 - sizeof(const SceKernelThreadOptParam*))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_ULTHREAD_RUNTIME_OPT_PARAM_ALIGNMENT) SceUltUlthreadRuntimeOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_ULTHREAD_RUNTIME_ALIGNMENT) struct SceUltUlthreadRuntime {
	uint64_t __reserved__[_SCE_ULT_ULTHREAD_RUNTIME_SIZE / sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_ULTHREAD_RUNTIME_ALIGNMENT) SceUltUlthreadRuntime;

typedef _SCE_ALIGN_BEG(SCE_ULT_ULTHREAD_OPT_PARAM_ALIGNMENT) struct SceUltUlthreadOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint32_t attribute;
	uint32_t __reserved__0;
	uint64_t __reserved__[ (_SCE_ULT_ULTHREAD_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader) - sizeof(uint32_t)*2)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_ULTHREAD_OPT_PARAM_ALIGNMENT) SceUltUlthreadOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_ULTHREAD_ALIGNMENT) struct SceUltUlthread {
	uint64_t __reserved__[_SCE_ULT_ULTHREAD_SIZE / sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_ULTHREAD_ALIGNMENT) SceUltUlthread;

typedef _SCE_ALIGN_BEG(SCE_ULT_ULTHREAD_RUNTIME_INFO_ALIGNMENT) struct SceUltUlthreadRuntimeInfo {
	uint32_t size;
	uint32_t ulthreadRuntimeId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t numUlthread;
	uint32_t maxNumUlthread;
	uint32_t numWorkerThread;
	uint32_t oneShotThreadStackSize;
	uint64_t reserved[ (_SCE_ULT_ULTHREAD_RUNTIME_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*4)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_ULTHREAD_RUNTIME_INFO_ALIGNMENT) SceUltUlthreadRuntimeInfo;

typedef _SCE_ALIGN_BEG(SCE_ULT_ULTHREAD_INFO_ALIGNMENT) struct SceUltUlthreadInfo {
	uint32_t size;
	uint32_t ulthreadId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t attribute;
	uint32_t ulthreadRuntimeId;
	SceFiberInfo fiberInfo;
	uint64_t reserved[ (_SCE_ULT_ULTHREAD_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*2 - sizeof(SceFiberInfo))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_ULTHREAD_INFO_ALIGNMENT) SceUltUlthreadInfo;

#if defined(__cplusplus)
extern "C" {
#endif

int32_t _sceUltUlthreadRuntimeOptParamInitialize(SceUltUlthreadRuntimeOptParam *optParam, uint32_t buildVersion);

static __inline__ int32_t sceUltUlthreadRuntimeOptParamInitialize(SceUltUlthreadRuntimeOptParam *optParam) {
	return _sceUltUlthreadRuntimeOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

uint32_t sceUltUlthreadRuntimeGetWorkAreaSize(uint32_t maxNumUlthread, uint32_t numWorkerThread);

int32_t _sceUltUlthreadRuntimeCreate(
	SceUltUlthreadRuntime* runtime,
	const char* name,
	uint32_t maxNumUlthread,
	uint32_t numWorkerThread,
	void* workArea,
	const SceUltUlthreadRuntimeOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int32_t sceUltUlthreadRuntimeCreate(
		SceUltUlthreadRuntime* runtime,
		const char* name,
		uint32_t maxNumUlthread,
		uint32_t numWorkerThread,
		void* workArea,
		const SceUltUlthreadRuntimeOptParam *optParam) {
	return _sceUltUlthreadRuntimeCreate(runtime, name, maxNumUlthread, numWorkerThread, workArea, optParam, _SCE_ULT_VERSION);
}

int32_t sceUltUlthreadRuntimeDestroy(SceUltUlthreadRuntime* runtime);

int32_t _sceUltUlthreadOptParamInitialize(SceUltUlthreadOptParam *optParam, uint32_t buildVersion);

static __inline__ int32_t sceUltUlthreadOptParamInitialize(SceUltUlthreadOptParam *optParam) {
	return _sceUltUlthreadOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

typedef int32_t (*SceUltUlthreadEntry)(uint32_t arg);

int32_t _sceUltUlthreadCreate(
	SceUltUlthread *ulthread,
	const char* name,
	SceUltUlthreadEntry entry,
	uint32_t arg,
	void* context,
	uint32_t sizeContext,
	SceUltUlthreadRuntime *runtime,
	const SceUltUlthreadOptParam *optParam, uint32_t buildVersion);

static __inline__ int32_t sceUltUlthreadCreate(
		SceUltUlthread *ulthread,
		const char* name,
		SceUltUlthreadEntry entry,
		uint32_t arg,
		void* context,
		uint32_t sizeContext,
		SceUltUlthreadRuntime *runtime,
		const SceUltUlthreadOptParam *optParam) {
	return _sceUltUlthreadCreate(ulthread, name, entry, arg, context, sizeContext, runtime, optParam, _SCE_ULT_VERSION);
}

int32_t sceUltUlthreadYield(void);
int32_t sceUltUlthreadExit(int32_t status);
int32_t sceUltUlthreadJoin(SceUltUlthread *ulthread, int32_t *status);
int32_t sceUltUlthreadTryJoin(SceUltUlthread *ulthread, int32_t *status);
int32_t sceUltUlthreadGetSelf(SceUltUlthread **ulthread);

int32_t sceUltGetUlthreadRuntimeInfo(
	const SceUltUlthreadRuntime *runtime,
	SceUltUlthreadRuntimeInfo *pInfo,
	SceUltUlthread **ulthreadList,
	const uint32_t maxNumUlthread,
	uint32_t *workerThreadIdList,
	const uint32_t maxNumWorkerThreadId);

int32_t sceUltGetUlthreadInfo(const SceUltUlthread *ulthread, SceUltUlthreadInfo *pInfo);

#if defined(__cplusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_ULT_ULTHREAD_H_ */
