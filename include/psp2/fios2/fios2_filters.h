/**
 * \usergroup{SceFios2}
 * \usage{psp2/fios2.h,SceFios2_stub}
 */

#ifndef _DOLCESDK_PSP2_FIOS2_FILTERS_H_
#define _DOLCESDK_PSP2_FIOS2_FILTERS_H_

#include <psp2/fios2/fios2_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceFiosIoFilterIndex {
	SCE_FIOS_IOFILTER_INDEX_FIRST = 0,
	SCE_FIOS_IOFILTER_INDEX_LAST  = 255
} SceFiosIoFilterIndex;

typedef void (*SceFiosIOFilterCallback)();

SCE_FIOS_LINKAGE int sceFiosIOFilterAdd(int index, SceFiosIOFilterCallback pFilterCallback, void *pFilterContext);
SCE_FIOS_LINKAGE int sceFiosIOFilterGetInfo(int index, SceFiosIOFilterCallback *pOutFilterCallback, void **pOutFilterContext);
SCE_FIOS_LINKAGE int sceFiosIOFilterRemove(int index);

#define SCE_FIOS_PSARC_DEARCHIVER_TEMP_BUFFERS	3

#define SCE_FIOS_PSARC_DEARCHIVER_WORK_BUFFER(blockSize)	\
	((blockSize) * SCE_FIOS_PSARC_DEARCHIVER_TEMP_BUFFERS)

#define SCE_FIOS_PSARC_DEARCHIVER_WORK_BUFFER_SIZE	SCE_FIOS_PSARC_DEARCHIVER_WORK_BUFFER(64*1024)

#define SCE_FIOS_PSARC_DEARCHIVER_WORK_BUFFER_ALIGNMENT  64

typedef enum SceFiosPsarcDearchiverFlags {
	SCE_FIOS_PSARC_DEARCHIVER_MOUNT_TRANSLUCENT = (1<<0)
} SceFiosPsarcDearchiverFlags;

typedef struct SceFiosPsarcDearchiverContext {
	size_t   sizeOfContext;
	size_t   workBufferSize;
	void*    pWorkBuffer;
	intptr_t flags;
	intptr_t reserved[3];
} SceFiosPsarcDearchiverContext;
#define SCE_FIOS_PSARC_DEARCHIVER_CONTEXT_INITIALIZER    { sizeof(SceFiosPsarcDearchiverContext), 0, 0, 0, {0,0,0} }

SCE_FIOS_LINKAGE void sceFiosIOFilterPsarcDearchiver();

#define SCE_FIOS_RAM_CACHE_BUFFER_SIZE       (128*1024)

#define SCE_FIOS_RAM_CACHE_BUFFER_SIZE_PER_BLOCK(blocks, blocksize, pathMax) \
	((blocks * (blocksize + 64)) + SCE_FIOS_ALIGN_UP((72 + pathMax + 1),8))

#define SCE_FIOS_RAM_CACHE_BUFFER_ALIGNMENT  8

typedef struct SceFiosRamCacheContext {
	size_t      sizeOfContext;
	size_t      workBufferSize;
	size_t      blockSize;
	void*       pWorkBuffer;
	const char* pPath;
	intptr_t    flags;
	intptr_t    reserved[3];
} SceFiosRamCacheContext;
#define SCE_FIOS_RAM_CACHE_CONTEXT_INITIALIZER    { sizeof(SceFiosRamCacheContext), 0, (64 * 1024), NULL, NULL, 0, {0,0,0} }

SCE_FIOS_LINKAGE void sceFiosIOFilterCache();

#ifdef __cplusplus
}
#endif

#endif
