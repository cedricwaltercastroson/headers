/**
 * \usergroup{SceCes}
 * \usage{psp2/ces.h}
 */

#ifndef _DOLCESDK_PSP2_CES_ERROR_H_
#define _DOLCESDK_PSP2_CES_ERROR_H_

#include <psp2/error.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_CES_OK                       SCE_OK
#define SCE_CES_ERROR_INVALID_PARAMETER  ((int)0x805C0001)
#define SCE_CES_ERROR_INVALID_PROFILE    ((int)0x805C0004)
#define SCE_CES_ERROR_INVALID_SRC_BUFFER ((int)0x805C0010)
#define SCE_CES_ERROR_SRC_BUFFER_END     ((int)0x805C0011)
#define SCE_CES_ERROR_INVALID_ENCODE     ((int)0x805C0014)
#define SCE_CES_ERROR_ILLEGAL_CODE       ((int)0x805C0015)
#define SCE_CES_ERROR_UNASSIGNED_CODE    ((int)0x805C0020)
#define SCE_CES_ERROR_OUT_OF_CODE_RANGE  ((int)0x805C0024)
#define SCE_CES_ERROR_INVALID_DST_BUFFER ((int)0x805C0030)
#define SCE_CES_ERROR_DST_BUFFER_END     ((int)0x805C0031)

#ifdef __cplusplus
}
#endif

#endif // _DOLCESDK_PSP2_CES_ERROR_H_
