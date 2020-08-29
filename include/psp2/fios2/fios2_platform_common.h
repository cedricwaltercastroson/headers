/**
 * \usergroup{SceFios2}
 * \usage{psp2/fios2.h,SceFios2_stub}
 */

#ifndef _DOLCESDK_PSP2_FIOS2_PLATFORM_COMMON_H_
#define _DOLCESDK_PSP2_FIOS2_PLATFORM_COMMON_H_

typedef enum SceFiosThreadType {
	SCE_FIOS_IO_THREAD           = 0,
	SCE_FIOS_DECOMPRESSOR_THREAD = 1,
	SCE_FIOS_CALLBACK_THREAD     = 2,
	SCE_FIOS_THREAD_TYPES        = 3
} SceFiosThreadType;

#define SCE_FIOS_THREAD_INVALID_PRIORITY	-1

#endif
