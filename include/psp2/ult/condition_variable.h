/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_CONDITION_VARIABLE_H_
#define _DOLCESDK_PSP2_ULT_CONDITION_VARIABLE_H_

#include <psp2/ult/error.h>
#include <psp2/ult/mutex.h>
#include <psp2/ult/resource_pool.h>

#define _SCE_ULT_CONDITION_VARIABLE_OPT_PARAM_SIZE     128
#define SCE_ULT_CONDITION_VARIABLE_OPT_PARAM_ALIGNMENT 8

#define _SCE_ULT_CONDITION_VARIABLE_SIZE               256
#define SCE_ULT_CONDITION_VARIABLE_ALIGNMENT           8

#define _SCE_ULT_CONDITION_VARIABLE_INFO_SIZE          128
#define SCE_ULT_CONDITION_VARIABLE_INFO_ALIGNMENT      8

typedef _SCE_ALIGN_BEG(SCE_ULT_CONDITION_VARIABLE_OPT_PARAM_ALIGNMENT) struct SceUltConditionVariableOptParam {
	_SceUltOptParamHeader __reserved__header;
	uint64_t __reserved__[ (_SCE_ULT_CONDITION_VARIABLE_OPT_PARAM_SIZE - sizeof(_SceUltOptParamHeader))/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_CONDITION_VARIABLE_OPT_PARAM_ALIGNMENT) SceUltConditionVariableOptParam;

typedef _SCE_ALIGN_BEG(SCE_ULT_CONDITION_VARIABLE_ALIGNMENT) struct SceUltConditionVariable {
	uint64_t __reserved__[_SCE_ULT_CONDITION_VARIABLE_SIZE / sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_CONDITION_VARIABLE_ALIGNMENT) SceUltConditionVariable;

typedef _SCE_ALIGN_BEG(SCE_ULT_CONDITION_VARIABLE_INFO_ALIGNMENT) struct SceUltConditionVariableInfo {
	uint32_t size;
	uint32_t cvId;
	char name[SCE_ULT_MAX_NAME_LENGTH+1];
	uint32_t mutexId;
	uint32_t numWaitThreads;
	uint64_t reserved[ (_SCE_ULT_CONDITION_VARIABLE_INFO_SIZE - sizeof(uint32_t)*2 - (SCE_ULT_MAX_NAME_LENGTH+1) - sizeof(uint32_t)*2)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_CONDITION_VARIABLE_INFO_ALIGNMENT) SceUltConditionVariableInfo;

#if defined(__cplusplus)
extern "C" {
#endif

int32_t _sceUltConditionVariableOptParamInitialize(SceUltConditionVariableOptParam *optParam, uint32_t buildVersion);

static __inline__ int32_t sceUltConditionVariableOptParamInitialize(SceUltConditionVariableOptParam *optParam) {
	return _sceUltConditionVariableOptParamInitialize(optParam, _SCE_ULT_VERSION);
}

int32_t _sceUltConditionVariableCreate(
	SceUltConditionVariable *conditionVariable,
	const char* name,
	SceUltMutex *mutex,
	const SceUltConditionVariableOptParam *optParam,
	uint32_t buildVersion);

static __inline__ int32_t sceUltConditionVariableCreate(
		SceUltConditionVariable *conditionVariable,
		const char* name,
		SceUltMutex *mutex,
		const SceUltConditionVariableOptParam *optParam) {
	return _sceUltConditionVariableCreate(conditionVariable, name, mutex, optParam, _SCE_ULT_VERSION);
}

int32_t sceUltConditionVariableSignal(SceUltConditionVariable *conditionVariable);

int32_t sceUltConditionVariableSignalAll(SceUltConditionVariable *conditionVariable);

int32_t sceUltConditionVariableWait(SceUltConditionVariable *conditionVariable);

int32_t sceUltConditionVariableDestroy(SceUltConditionVariable *conditionVariable);

int32_t sceUltGetConditionVariableInfo(
	const SceUltConditionVariable *cv,
	SceUltConditionVariableInfo *pInfo,
	SceUltWaitThreadInfo *waitThreadInfoList,
	const uint32_t maxNumThreadInfo);

#if defined(__cplusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_ULT_CONDITION_VARIABLE_H_ */
