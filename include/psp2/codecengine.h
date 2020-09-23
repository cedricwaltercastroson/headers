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

#define SCE_CODECENGINE_ERROR_INVALID_POINTER           ((int)0x80600000)
#define SCE_CODECENGINE_ERROR_INVALID_SIZE              ((int)0x80600001)
#define SCE_CODECENGINE_ERROR_INVALID_ALIGNMENT         ((int)0x80600002)
#define SCE_CODECENGINE_ERROR_NOT_PHYSICALLY_CONTIGUOUS ((int)0x80600003)
#define SCE_CODECENGINE_ERROR_INVALID_RANGE             ((int)0x80600004)
#define SCE_CODECENGINE_ERROR_INVALID_HEAP              ((int)0x80600005)
#define SCE_CODECENGINE_ERROR_HEAP_BROKEN               ((int)0x80600006)
#define SCE_CODECENGINE_ERROR_NO_MORE_ENTRY             ((int)0x80600007)
#define SCE_CODECENGINE_ERROR_INVALID_MEMTYPE           ((int)0x80600008)
#define SCE_CODECENGINE_ERROR_INVALID_VALUE             ((int)0x80600009)
#define SCE_CODECENGINE_ERROR_MEMORY_NOT_ALLOCATED      ((int)0x8060000A)
#define SCE_CODECENGINE_ERROR_MEMORY_IN_USE             ((int)0x8060000B)
#define SCE_CODECENGINE_ERROR_MEMORY_NOT_IN_USE         ((int)0x8060000C)

/* normal APIs */

SceUID sceCodecEngineOpenUnmapMemBlock(void *pMemBlock, SceUInt32 memBlockSize);
SceInt32 sceCodecEngineCloseUnmapMemBlock(SceUID uid);
SceUIntVAddr sceCodecEngineAllocMemoryFromUnmapMemBlock(SceUID uid, SceUInt32 size, SceUInt32 alignment);
SceInt32 sceCodecEngineFreeMemoryFromUnmapMemBlock(SceUID uid, SceUIntVAddr p);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_CODECENGINE_H_ */
