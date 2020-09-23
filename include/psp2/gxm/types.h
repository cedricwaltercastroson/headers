#ifndef _DOLCESDK_PSP2_GXM_TYPES_H_
#define _DOLCESDK_PSP2_GXM_TYPES_H_

/** @file

	C99 basic types.  This file will be replaced with <scebase_common.h> in a future
	release.
*/

#ifdef _MSC_VER
	#ifdef SCE_GXM_EXPORTS
		#define SCE_GXM_INTERFACE			__declspec(dllexport)
	#else
		#define SCE_GXM_INTERFACE			__declspec(dllimport)
	#endif
	#if !defined(SCE_GXM_NO_STDINT_DEFS) && !defined(SCE_SCEBASE_NO_STDINT_DEFS) && !defined(_SCE_SCEBASE_STDINT_DEFINED)
		#define _SCE_SCEBASE_STDINT_DEFINED
		typedef signed char int8_t;
		typedef signed short int16_t;
		typedef signed int int32_t;
		typedef signed long long int64_t;
		typedef unsigned char uint8_t;
		typedef unsigned short uint16_t;
		typedef unsigned int uint32_t;
		typedef unsigned long long uint64_t;
	#endif
	#ifndef __cplusplus
		#if !defined(SCE_GXM_NO_STDBOOL_DEFS) && !defined(SCE_SCEBASE_NO_STDBOOL_DEFS) && !defined(_SCE_SCEBASE_STDBOOL_DEFINED)
			#define _SCE_SCEBASE_STDBOOL_DEFINED
			#define bool    int
			#define true    1
			#define false   0
		#endif
	#endif
#else
	#if !defined(DOXYGEN_IGNORE)
		#define SCE_GXM_INTERFACE
	#endif
	#include <stdint.h>
	#include <stdbool.h>
#endif

#endif /* _DOLCESDK_PSP2_GXM_TYPES_H_ */
