/**
 * \usergroup{SceFios2}
 * \usage{psp2/fios2.h,SceFios2_stub}
 */

#ifndef _DOLCESDK_PSP2_FIOS2_API_H_
#define _DOLCESDK_PSP2_FIOS2_API_H_

#include <psp2/scebase.h>
#include <psp2/fios2/fios2_types.h>
#include <psp2/fios2/fios2_filters.h>
#include <psp2/fios2/fios2_errors.h>
#include <stdarg.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

SCE_FIOS_LINKAGE int       sceFiosInitialize(const SceFiosParams *pParameters);
SCE_FIOS_LINKAGE void      sceFiosTerminate();
SCE_FIOS_LINKAGE bool      sceFiosIsInitialized(SceFiosParams *pOutParameters);
SCE_FIOS_LINKAGE void      sceFiosUpdateParameters(const SceFiosParams *pParameters);
SCE_FIOS_LINKAGE void      sceFiosSetGlobalDefaultOpAttr(const SceFiosOpAttr *pAttr);
SCE_FIOS_LINKAGE bool      sceFiosGetGlobalDefaultOpAttr(SceFiosOpAttr *pOutAttr);

#if SCE_FIOS_THREAD_LOCAL_SUPPORTED
SCE_FIOS_LINKAGE void      sceFiosSetThreadDefaultOpAttr(const SceFiosOpAttr *pAttr);
SCE_FIOS_LINKAGE bool      sceFiosGetThreadDefaultOpAttr(SceFiosOpAttr *pOutAttr);
#endif

SCE_FIOS_LINKAGE void      sceFiosGetDefaultOpAttr(SceFiosOpAttr *pOutAttr);
SCE_FIOS_LINKAGE void      sceFiosSuspend();
SCE_FIOS_LINKAGE uint32_t  sceFiosGetSuspendCount();
SCE_FIOS_LINKAGE bool      sceFiosIsSuspended();
SCE_FIOS_LINKAGE void      sceFiosResume();
SCE_FIOS_LINKAGE void      sceFiosShutdownAndCancelOps();
SCE_FIOS_LINKAGE void      sceFiosCancelAllOps();
SCE_FIOS_LINKAGE void      sceFiosCloseAllFiles();
SCE_FIOS_LINKAGE bool      sceFiosIsIdle();
SCE_FIOS_LINKAGE void sceFiosStatisticsReset();
SCE_FIOS_LINKAGE void sceFiosStatisticsPrint();
SCE_FIOS_LINKAGE size_t    sceFiosGetAllFHs(SceFiosFH *pOutArray, size_t arraySize);
SCE_FIOS_LINKAGE size_t    sceFiosGetAllDHs(SceFiosDH *pOutArray, size_t arraySize);
SCE_FIOS_LINKAGE size_t    sceFiosGetAllOps(SceFiosOp *pOutArray, size_t arraySize);
SCE_FIOS_LINKAGE bool      sceFiosIsValidHandle(SceFiosHandle h);
SCE_FIOS_LINKAGE int       sceFiosPathcmp(const char *pA, const char *pB);
SCE_FIOS_LINKAGE int       sceFiosPathncmp(const char *pA, const char *pB, size_t n);
SCE_FIOS_LINKAGE int       sceFiosPrintf(const char *pFormat, ...)
	SCE_FIOS_ATTRIBUTE((__format__(__printf__,1,2)))
	SCE_FIOS_ATTRIBUTE_NONNULL((__nonnull__(1)));
SCE_FIOS_LINKAGE int       sceFiosVprintf(const char *pFormat, va_list ap)
	SCE_FIOS_ATTRIBUTE((__format__(__printf__,1,0)))
	SCE_FIOS_ATTRIBUTE_NONNULL((__nonnull__(1)));

SCE_FIOS_LINKAGE SceFiosOp sceFiosFileExists(const SceFiosOpAttr *pAttr, const char *pPath, bool *pOutExists);
SCE_FIOS_LINKAGE bool      sceFiosFileExistsSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFileGetSize(const SceFiosOpAttr *pAttr, const char *pPath, SceFiosSize *pOutSize);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFileGetSizeSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFileDelete(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE int       sceFiosFileDeleteSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE int      sceFiosCacheContainsFileSync(const char *pPath, SceFiosSize *pOutSize);
SCE_FIOS_LINKAGE int      sceFiosCacheContainsFileRangeSync(const char *pPath, SceFiosOffset offset, SceFiosSize length);
SCE_FIOS_LINKAGE void      sceFiosCacheFlushFileSync(const char *pPath);
SCE_FIOS_LINKAGE void      sceFiosCacheFlushFileRangeSync(const char *pPath, SceFiosOffset offset, SceFiosSize length);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDirectoryExists(const SceFiosOpAttr *pAttr, const char *pPath, bool *pOutExists);
SCE_FIOS_LINKAGE bool      sceFiosDirectoryExistsSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDirectoryCreate(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE int       sceFiosDirectoryCreateSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDirectoryCreateWithMode(const SceFiosOpAttr *pAttr, const char *pPath, int32_t nativeMode);
SCE_FIOS_LINKAGE int       sceFiosDirectoryCreateWithModeSync(const SceFiosOpAttr *pAttr, const char *pPath, int32_t nativeMode);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDirectoryDelete(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE int       sceFiosDirectoryDeleteSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE SceFiosOp sceFiosExists(const SceFiosOpAttr *pAttr, const char *pPath, bool *pOutExists);
SCE_FIOS_LINKAGE bool      sceFiosExistsSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE SceFiosOp sceFiosStat(const SceFiosOpAttr *pAttr, const char *pPath, SceFiosStat *pOutStatus);
SCE_FIOS_LINKAGE int       sceFiosStatSync(const SceFiosOpAttr *pAttr, const char *pPath, SceFiosStat *pOutStatus);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDelete(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE int       sceFiosDeleteSync(const SceFiosOpAttr *pAttr, const char *pPath);
SCE_FIOS_LINKAGE SceFiosOp sceFiosResolve(const SceFiosOpAttr *pAttr, const SceFiosTuple *pInTuple, SceFiosTuple *pOutTuple);
SCE_FIOS_LINKAGE int       sceFiosResolveSync(const SceFiosOpAttr *pAttr, const SceFiosTuple *pInTuple, SceFiosTuple *pOutTuple);
SCE_FIOS_LINKAGE SceFiosOp sceFiosRename(const SceFiosOpAttr *pAttr, const char *pOldPath, const char *pNewPath);
SCE_FIOS_LINKAGE int       sceFiosRenameSync(const SceFiosOpAttr *pAttr, const char *pOldPath, const char *pNewPath);

SCE_FIOS_LINKAGE SceFiosOp sceFiosChangeStat(const SceFiosOpAttr *pAttr, const char *pPath, SceFiosStat *pStatus, int cbit);
SCE_FIOS_LINKAGE int sceFiosChangeStatSync(const SceFiosOpAttr *pAttr, const char *pPath, SceFiosStat *pStatus, int cbit);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDevctl(
	const SceFiosOpAttr *pAttr, const char *pPath, int cmd, void *pArg, size_t arglen, void *pBuffer, size_t buflen);
SCE_FIOS_LINKAGE int sceFiosDevctlSync(
	const SceFiosOpAttr *pAttr, const char *pPath, int cmd, void *pArg, size_t arglen, void *pBuffer, size_t buflen);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHIoctl(
	const SceFiosOpAttr *pAttr, const SceFiosFH fh, int cmd, void *pArg, size_t arglen, void *pBuffer, size_t buflen);
SCE_FIOS_LINKAGE int sceFiosFHIoctlSync(
	const SceFiosOpAttr *pAttr, const SceFiosFH fh, int cmd, void *pArg, size_t arglen, void *pBuffer, size_t buflen);
SCE_FIOS_LINKAGE SceFiosOp sceFiosSync(const SceFiosOpAttr *pAttr, const char *pPath, int flag);
SCE_FIOS_LINKAGE  int sceFiosSyncSync(const SceFiosOpAttr *pAttr, const char *pPath, int flag);

SCE_FIOS_LINKAGE SceFiosOp sceFiosFileRead(const SceFiosOpAttr *pAttr, const char *pPath, void *pBuf,
                                           SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFileReadSync(const SceFiosOpAttr *pAttr, const char *pPath, void *pBuf,
                                               SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFileWrite(const SceFiosOpAttr *pAttr, const char *pPath, const void *pBuf,
                                            SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFileWriteSync(const SceFiosOpAttr *pAttr, const char *pPath, const void *pBuf,
                                                SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFileTruncate(const SceFiosOpAttr *pAttr, const char *pPath, SceFiosSize length);
SCE_FIOS_LINKAGE int       sceFiosFileTruncateSync(const SceFiosOpAttr *pAttr, const char *pPath, SceFiosSize length);

SCE_FIOS_LINKAGE SceFiosOp sceFiosFHOpen(const SceFiosOpAttr *pAttr, SceFiosFH *pOutFH, const char *pPath, const SceFiosOpenParams *pOpenParams);
SCE_FIOS_LINKAGE int       sceFiosFHOpenSync(const SceFiosOpAttr *pAttr, SceFiosFH *pOutFH, const char *pPath, const SceFiosOpenParams *pOpenParams);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHOpenWithMode(const SceFiosOpAttr *pAttr, SceFiosFH *pOutFH, const char *pPath, const SceFiosOpenParams *pOpenParams, int32_t nativeMode);
SCE_FIOS_LINKAGE int       sceFiosFHOpenWithModeSync(const SceFiosOpAttr *pAttr, SceFiosFH *pOutFH, const char *pPath, const SceFiosOpenParams *pOpenParams, int32_t nativeMode);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHStat(const SceFiosOpAttr *pAttr, SceFiosFH fh, SceFiosStat *pOutStatus);
SCE_FIOS_LINKAGE int       sceFiosFHStatSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, SceFiosStat *pOutStatus);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHTruncate(const SceFiosOpAttr *pAttr, SceFiosFH fh, SceFiosSize length);
SCE_FIOS_LINKAGE int       sceFiosFHTruncateSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, SceFiosSize length);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHSync(const SceFiosOpAttr *pAttr, SceFiosFH fh);
SCE_FIOS_LINKAGE int       sceFiosFHSyncSync(const SceFiosOpAttr *pAttr, SceFiosFH fh);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHRead(const SceFiosOpAttr *pAttr, SceFiosFH fh, void *pBuf, SceFiosSize length);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHReadSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, void *pBuf, SceFiosSize length);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHWrite(const SceFiosOpAttr *pAttr, SceFiosFH fh, const void *pBuf, SceFiosSize length);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHWriteSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, const void *pBuf, SceFiosSize length);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHReadv(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHReadvSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHWritev(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHWritevSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHPread(const SceFiosOpAttr *pAttr, SceFiosFH fh, void *pBuf, SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHPreadSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, void *pBuf, SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHPwrite(const SceFiosOpAttr *pAttr, SceFiosFH fh, const void *pBuf, SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHPwriteSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, const void *pBuf, SceFiosSize length, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosOp sceFiosFHPreadv(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHPreadvSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosOp   sceFiosFHPwritev(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt, SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosSize sceFiosFHPwritevSync(const SceFiosOpAttr *pAttr, SceFiosFH fh, const SceFiosBuffer iov[], int iovcnt,
												SceFiosOffset offset);
SCE_FIOS_LINKAGE SceFiosOp   sceFiosFHClose(const SceFiosOpAttr *pAttr, SceFiosFH fh);
SCE_FIOS_LINKAGE int       sceFiosFHCloseSync(const SceFiosOpAttr *pAttr, SceFiosFH fh);
SCE_FIOS_LINKAGE SceFiosOffset sceFiosFHSeek(SceFiosFH fh, SceFiosOffset offset, SceFiosWhence whence);
SCE_FIOS_LINKAGE SceFiosOffset sceFiosFHTell(SceFiosFH fh);
SCE_FIOS_LINKAGE const char *  sceFiosFHGetPath(SceFiosFH fh);
SCE_FIOS_LINKAGE SceFiosSize   sceFiosFHGetSize(SceFiosFH fh);
SCE_FIOS_LINKAGE SceFiosOpenParams * sceFiosFHGetOpenParams(SceFiosFH fh);

SCE_FIOS_LINKAGE SceFiosOp sceFiosDHOpen(const SceFiosOpAttr *pAttr, SceFiosDH *pOutDH, const char *pPath, SceFiosBuffer buf);
SCE_FIOS_LINKAGE int       sceFiosDHOpenSync(const SceFiosOpAttr *pAttr, SceFiosDH *pOutDH, const char *pPath, SceFiosBuffer buf);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDHRead(const SceFiosOpAttr *pAttr, SceFiosDH dh, SceFiosDirEntry *pOutEntry);
SCE_FIOS_LINKAGE int       sceFiosDHReadSync(const SceFiosOpAttr *pAttr, SceFiosDH dh, SceFiosDirEntry *pOutEntry);
SCE_FIOS_LINKAGE SceFiosOp sceFiosDHClose(const SceFiosOpAttr *pAttr, SceFiosDH dh);
SCE_FIOS_LINKAGE int       sceFiosDHCloseSync(const SceFiosOpAttr *pAttr, SceFiosDH dh);
SCE_FIOS_LINKAGE const char * sceFiosDHGetPath(SceFiosDH dh);

SCE_FIOS_LINKAGE bool      sceFiosOpIsDone(SceFiosOp op);
SCE_FIOS_LINKAGE int       sceFiosOpWait(SceFiosOp op);
SCE_FIOS_LINKAGE int       sceFiosOpWaitUntil(SceFiosOp op, SceFiosTime deadline);
SCE_FIOS_LINKAGE void      sceFiosOpDelete(SceFiosOp op);
SCE_FIOS_LINKAGE int       sceFiosOpSyncWait(SceFiosOp op);
SCE_FIOS_LINKAGE SceFiosSize sceFiosOpSyncWaitForIO(SceFiosOp op);
SCE_FIOS_LINKAGE int       sceFiosOpGetError(SceFiosOp op);
SCE_FIOS_LINKAGE void      sceFiosOpCancel(SceFiosOp op);
SCE_FIOS_LINKAGE bool      sceFiosOpIsCancelled(SceFiosOp op);
SCE_FIOS_LINKAGE const SceFiosOpAttr * sceFiosOpGetAttr(SceFiosOp op);
SCE_FIOS_LINKAGE const char * sceFiosOpGetPath(SceFiosOp op);
SCE_FIOS_LINKAGE void *    sceFiosOpGetBuffer(SceFiosOp op);
SCE_FIOS_LINKAGE SceFiosOffset sceFiosOpGetOffset(SceFiosOp op);
SCE_FIOS_LINKAGE SceFiosSize sceFiosOpGetRequestCount(SceFiosOp op);
SCE_FIOS_LINKAGE SceFiosSize sceFiosOpGetActualCount(SceFiosOp op);
SCE_FIOS_LINKAGE void      sceFiosOpReschedule(SceFiosOp op, SceFiosTime newDeadline);
SCE_FIOS_LINKAGE void      sceFiosOpRescheduleWithPriority(SceFiosOp op, SceFiosTime newDeadline, SceFiosPriority newPriority);

SCE_FIOS_LINKAGE SceFiosTime sceFiosTimeGetCurrent();
SCE_FIOS_LINKAGE int64_t sceFiosTimeIntervalToNanoseconds(SceFiosTimeInterval interval);
SCE_FIOS_LINKAGE SceFiosTimeInterval sceFiosTimeIntervalFromNanoseconds(int64_t ns);

#include <psp2/kernel/processmgr.h>
#define sceFiosTimeGetCurrent()           ((int64_t)sceKernelGetProcessTimeWide())

#define sceFiosTimeIntervalFromMicroseconds(us)         \
	sceFiosTimeIntervalFromNanoseconds((us) * SCE_FIOS_NANOSECONDS_PER_MICROSECOND)

#define sceFiosTimeIntervalFromMilliseconds(ms)         \
	sceFiosTimeIntervalFromNanoseconds((ms) * SCE_FIOS_NANOSECONDS_PER_MILLISECOND)

#define sceFiosTimeIntervalFromSeconds(s)               \
	sceFiosTimeIntervalFromNanoseconds((s) * SCE_FIOS_NANOSECONDS_PER_SECOND)

#define sceFiosTimeIntervalToMicroseconds(interval)   \
	SCE_FIOS_DIVIDE_ROUNDING_UP(sceFiosTimeIntervalToNanoseconds(interval), SCE_FIOS_NANOSECONDS_PER_MICROSECOND)

#define sceFiosTimeIntervalToMilliseconds(interval)   \
	SCE_FIOS_DIVIDE_ROUNDING_UP(sceFiosTimeIntervalToNanoseconds(interval), SCE_FIOS_NANOSECONDS_PER_MILLISECOND)

#define sceFiosTimeIntervalToSeconds(interval)        \
	SCE_FIOS_DIVIDE_ROUNDING_UP(sceFiosTimeIntervalToNanoseconds(interval), SCE_FIOS_NANOSECONDS_PER_SECOND)

#define sceFiosTimeRelativeNanoseconds(ns)            \
	(sceFiosTimeGetCurrent() + sceFiosTimeIntervalFromNanoseconds(ns))

#define sceFiosTimeRelativeMicroseconds(us)           \
	(sceFiosTimeGetCurrent() + sceFiosTimeIntervalFromMicroseconds(us))

#define sceFiosTimeRelativeMilliseconds(ms)           \
	(sceFiosTimeGetCurrent() + sceFiosTimeIntervalFromMilliseconds(ms))

#define sceFiosTimeRelativeSeconds(s)                 \
	(sceFiosTimeGetCurrent() + sceFiosTimeIntervalFromSeconds(s))

#ifdef __cplusplus
inline SCE_FIOS_LINKAGE bool sceFiosTimeoutElapsed(SceFiosTime start, SceFiosTimeInterval timeout) {
	SceFiosTimeInterval elapsed = sceFiosTimeGetCurrent() - start;
	return (elapsed > timeout);
}
#else
#define sceFiosTimeoutElapsed(start,timeout)  ((sceFiosTimeGetCurrent() - start) > timeout)
#endif

SCE_FIOS_LINKAGE SceFiosDate sceFiosDateGetCurrent();
SCE_FIOS_LINKAGE SceFiosDate sceFiosDateFromComponents(const struct tm *pComponents);
SCE_FIOS_LINKAGE struct tm * sceFiosDateToComponents(SceFiosDate date, struct tm *pOutComponents);
SCE_FIOS_LINKAGE SceFiosDate sceFiosDateFromSceDateTime(const SceDateTime *pSceDateTime);
SCE_FIOS_LINKAGE SceDateTime * sceFiosDateToSceDateTime(SceFiosDate date, SceDateTime *pSceDateTime);

SCE_FIOS_LINKAGE int sceFiosOverlayAdd(const SceFiosOverlay *pOverlay, SceFiosOverlayID *pOutID);
SCE_FIOS_LINKAGE int sceFiosOverlayRemove(SceFiosOverlayID id);
SCE_FIOS_LINKAGE int sceFiosOverlayGetInfo(SceFiosOverlayID id, SceFiosOverlay *pOutOverlay);
SCE_FIOS_LINKAGE int sceFiosOverlayModify(SceFiosOverlayID id, const SceFiosOverlay *pNewValue);
SCE_FIOS_LINKAGE int sceFiosOverlayGetList(SceFiosOverlayID *pOutIDs, size_t maxIDs, size_t *pActualIDs);
SCE_FIOS_LINKAGE int sceFiosOverlayResolveSync(int resolveFlag, const char *pInPath, char *pOutPath, size_t maxPath);

SCE_FIOS_LINKAGE SceFiosOp sceFiosArchiveGetMountBufferSize(
	const SceFiosOpAttr *pAttr, const char *pArchivePath, const SceFiosOpenParams *pOpenParams);
SCE_FIOS_LINKAGE SceFiosSize sceFiosArchiveGetMountBufferSizeSync(
	const SceFiosOpAttr *pAttr, const char *pArchivePath, const SceFiosOpenParams *pOpenParams);
SCE_FIOS_LINKAGE SceFiosOp sceFiosArchiveMount(
	const SceFiosOpAttr *pAttr, SceFiosFH *pOutFH, const char *pArchivePath, const char *pMountPoint,
	SceFiosBuffer mountBuffer, const SceFiosOpenParams *pOpenParams);
SCE_FIOS_LINKAGE int sceFiosArchiveMountSync(
	const SceFiosOpAttr *pAttr, SceFiosFH *pOutFH, const char *pArchivePath, const char *pMountPoint,
	SceFiosBuffer mountBuffer, const SceFiosOpenParams *pOpenParams);
SCE_FIOS_LINKAGE SceFiosOp sceFiosArchiveUnmount(const SceFiosOpAttr *pAttr, SceFiosFH fh);
SCE_FIOS_LINKAGE int sceFiosArchiveUnmountSync(const SceFiosOpAttr *pAttr, SceFiosFH fh);
SCE_FIOS_LINKAGE uint8_t sceFiosArchiveSetDecompressorThreadCount(uint8_t threadCount);
SCE_FIOS_LINKAGE uint8_t sceFiosArchiveGetDecompressorThreadCount();

#ifdef __cplusplus
}
#endif

#endif
