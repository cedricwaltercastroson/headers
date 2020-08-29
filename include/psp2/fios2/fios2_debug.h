/**
 * \usergroup{SceFios2}
 * \usage{psp2/fios2.h,SceFios2_stub}
 */

#ifndef _DOLCESDK_PSP2_FIOS2_DEBUG_H_
#define _DOLCESDK_PSP2_FIOS2_DEBUG_H_

#include <psp2/fios2/fios2_types.h>
#include <psp2/fios2/fios2_common.h>

#ifdef __cplusplus
extern "C" {
#endif

SCE_FIOS_LINKAGE char * sceFiosDebugDumpError(int err, char *pBuffer, size_t bufferSize);
SCE_FIOS_LINKAGE char * sceFiosDebugDumpOp(SceFiosOp op, char *pBuffer, size_t bufferSize);
SCE_FIOS_LINKAGE char * sceFiosDebugDumpFH(SceFiosFH fh, char *pBuffer, size_t bufferSize);
SCE_FIOS_LINKAGE char * sceFiosDebugDumpDH(SceFiosDH dh, char *pBuffer, size_t bufferSize);
SCE_FIOS_LINKAGE char * sceFiosDebugDumpDate(SceFiosDate date, char *pBuffer, size_t bufferSize);

#ifdef __cplusplus
}
#endif

#endif
