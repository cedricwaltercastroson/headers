/**
 * \usergroup{SceCodecEngine}
 * \usage{psp2/codecengine.h,SceCodecEngine_stub}
 */

#ifndef _DOLCESDK_PSP2_CODECENGINE_H_
#define _DOLCESDK_PSP2_CODECENGINE_H_

#include <psp2/types.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

/* Error definition */

#define SCE_CODECENGINE_ERROR_INVALID_POINTER           0x80600000
#define SCE_CODECENGINE_ERROR_INVALID_SIZE              0x80600001
#define SCE_CODECENGINE_ERROR_INVALID_ALIGNMENT         0x80600002
#define SCE_CODECENGINE_ERROR_NOT_PHYSICALLY_CONTIGUOUS 0x80600003
#define SCE_CODECENGINE_ERROR_INVALID_RANGE             0x80600004
#define SCE_CODECENGINE_ERROR_INVALID_HEAP              0x80600005
#define SCE_CODECENGINE_ERROR_HEAP_BROKEN               0x80600006
#define SCE_CODECENGINE_ERROR_NO_MORE_ENTRY             0x80600007
#define SCE_CODECENGINE_ERROR_INVALID_MEMTYPE           0x80600008
#define SCE_CODECENGINE_ERROR_INVALID_VALUE             0x80600009
#define SCE_CODECENGINE_ERROR_MEMORY_NOT_ALLOCATED      0x8060000A
#define SCE_CODECENGINE_ERROR_MEMORY_IN_USE             0x8060000B
#define SCE_CODECENGINE_ERROR_MEMORY_NOT_IN_USE         0x8060000C

/* normal APIs */

SceUID sceCodecEngineOpenUnmapMemBlock(void *pMemBlock, SceUInt32 memBlockSize);
SceInt32 sceCodecEngineCloseUnmapMemBlock(SceUID uid);
SceUIntVAddr sceCodecEngineAllocMemoryFromUnmapMemBlock(SceUID uid, SceUInt32 size, SceUInt32 alignment);
SceInt32 sceCodecEngineFreeMemoryFromUnmapMemBlock(SceUID uid, SceUIntVAddr p);

/* debug APIs */

typedef struct SceCodecEnginePmonProcessorLoad {
	SceUInt32 size;
	SceUInt32 average;
} SceCodecEnginePmonProcessorLoad;

SceInt32 sceCodecEnginePmonStart(void);
SceInt32 sceCodecEnginePmonStop(void);
SceInt32 sceCodecEnginePmonGetProcessorLoad(SceCodecEnginePmonProcessorLoad *pProcessorLoad);
SceInt32 sceCodecEnginePmonReset(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_CODECENGINE_H_ */
