/**
 * \usergroup{SceFios2}
 * \usage{psp2/fios2.h,SceFios2_stub}
 */

#ifndef _DOLCESDK_PSP2_FIOS2_TYPES_H_
#define _DOLCESDK_PSP2_FIOS2_TYPES_H_

#include <psp2/fios2/fios2_common.h>
#include <psp2/fios2/fios2_platform.h>
#include <stddef.h>
#include <stdarg.h>
#include <time.h>

typedef int64_t SceFiosOffset;
typedef int64_t SceFiosSize;
typedef uint8_t SceFiosOpEvent;

typedef int32_t SceFiosHandle;
#define SCE_FIOS_HANDLE_INVALID            0

typedef SceFiosHandle SceFiosOp;
#define SCE_FIOS_OP_INVALID                0

typedef SceFiosHandle SceFiosFH;
#define SCE_FIOS_FH_INVALID                0

typedef SceFiosHandle SceFiosDH;
#define SCE_FIOS_DH_INVALID                0

typedef int64_t SceFiosTime;

typedef int8_t SceFiosPriority;

typedef SceFiosTime SceFiosTimeInterval;

typedef uint64_t SceFiosDate;

typedef int32_t SceFiosOverlayID;

typedef int (*SceFiosOpCallback)(void *pContext, SceFiosOp op, SceFiosOpEvent event, int err);

typedef int (*SceFiosVprintfCallback)(const char *fmt, va_list ap);

typedef void * (*SceFiosMemcpyCallback)(void *dst, const void *src, size_t len);

#define SCE_FIOS_ALIGN_UP(val,align)      (((val) + ((align)-1)) & ~((align)-1))
#define SCE_FIOS_ALIGN_DOWN(val,align)    ((val) & ~((align)-1))
#define SCE_FIOS_DIVIDE_ROUNDING_UP(val,divisor)   (((val) + (divisor) - 1) / (divisor))
#define SCE_FIOS_IS_ALIGNED(ptr,align)    ((((intptr_t)ptr) & ((align)-1)) == 0)

#define SCE_FIOS_PATH_MAX        1024
#define SCE_FIOS_PATH_DEFAULT    1024
#define SCE_FIOS_OFFSET_MAX      ((int64_t)0x7FFFFFFFFFFFFFFFLL)

#define SCE_FIOS_NANOSECONDS_PER_SECOND       1000000000LL
#define SCE_FIOS_NANOSECONDS_PER_MILLISECOND  1000000LL
#define SCE_FIOS_MICROSECONDS_PER_SECOND      1000000LL
#define SCE_FIOS_NANOSECONDS_PER_MICROSECOND  1000LL
#define SCE_FIOS_MICROSECONDS_PER_MILLISECOND 1000LL
#define SCE_FIOS_MILLISECONDS_PER_SECOND      1000LL
#define SCE_FIOS_SECONDS_PER_MINUTE           60LL
#define SCE_FIOS_SECONDS_PER_HOUR             3600LL
#define SCE_FIOS_SECONDS_PER_DAY              86400LL
#define SCE_FIOS_SECONDS_PER_YEAR             31557600LL

#define SCE_FIOS_TIME_NULL         ((SceFiosTime)0)
#define SCE_FIOS_TIME_EARLIEST     ((SceFiosTime)1)
#define SCE_FIOS_TIME_LATEST       ((SceFiosTime)0x7FFFFFFFFFFFFFFFLL)

#define SCE_FIOS_PRIO_MIN          ((int8_t)-128)
#define SCE_FIOS_PRIO_DEFAULT      ((int8_t)0)
#define SCE_FIOS_PRIO_MAX          ((int8_t)127)

typedef enum SceFiosOpFlags {
	SCE_FIOS_OPFLAG_IMMED = (1<<0),
	SCE_FIOS_OPFLAG_DONTUSECACHE = (1<<1),
	SCE_FIOS_OPFLAG_DONTFILLRAMCACHE = (1<<2),
	SCE_FIOS_OPFLAG_DONTFILLDISKCACHE = (1<<3),
	SCE_FIOS_OPFLAG_CACHEPERSIST = (1<<4),
	SCE_FIOS_OPFLAG_UNCACHEDBUFFER = (1<<5),
	SCE_FIOS_OPFLAG_NONDMABUFFER = (1<<6),
	SCE_FIOS_OPFLAG_PERSISTENTPATH = (1<<7),
	SCE_FIOS_OPFLAG_DONTFILLCACHE = (SCE_FIOS_OPFLAG_DONTFILLRAMCACHE | SCE_FIOS_OPFLAG_DONTFILLDISKCACHE),
	SCE_FIOS_OPFLAG_NOCACHE = (SCE_FIOS_OPFLAG_DONTFILLCACHE | SCE_FIOS_OPFLAG_DONTUSECACHE)
} SceFiosOpFlags;

typedef enum SceFiosOpEvents {
	SCE_FIOS_OPEVENT_COMPLETE = 1,
	SCE_FIOS_OPEVENT_DELETE = 2
} SceFiosOpEvents;

typedef enum SceFiosWhence {
	SCE_FIOS_SEEK_SET = 0,
	SCE_FIOS_SEEK_CUR = 1,
	SCE_FIOS_SEEK_END = 2
} SceFiosWhence;

typedef enum SceFiosStatusFlags {
	SCE_FIOS_STATUS_DIRECTORY = (1<<0),
	SCE_FIOS_STATUS_READABLE = (1<<1),
	SCE_FIOS_STATUS_WRITABLE = (1<<2)
} SceFiosStatusFlags;

typedef enum SceFiosOpenFlags {
	SCE_FIOS_O_READ = (1U<<0),
	SCE_FIOS_O_RDONLY = SCE_FIOS_O_READ,
	SCE_FIOS_O_WRITE = (1U<<1),
	SCE_FIOS_O_WRONLY = SCE_FIOS_O_WRITE,
	SCE_FIOS_O_RDWR = (SCE_FIOS_O_READ | SCE_FIOS_O_WRITE),
	SCE_FIOS_O_APPEND = (1U<<2),
	SCE_FIOS_O_CREAT = (1U<<3),
	SCE_FIOS_O_TRUNC = (1U<<4),
	SCE_FIOS_O_DIRECT = (1U<<12)
} SceFiosOpenFlags;

typedef enum SceFiosProfilingMask {
	SCE_FIOS_PROFILE_API        = (1U<<0),
	SCE_FIOS_PROFILE_SCHEDULER  = (1U<<1),
	SCE_FIOS_PROFILE_OP         = (1U<<2),
	SCE_FIOS_PROFILE_CHUNK      = (1U<<3),
	SCE_FIOS_PROFILE_IO         = (1U<<4),
	SCE_FIOS_PROFILE_CACHE      = (1U<<5),
	SCE_FIOS_PROFILE_DEARCHIVER = (1U<<6),
	SCE_FIOS_PROFILE_OVERLAY    = (1U<<7),
	SCE_FIOS_PROFILE_ALL        = 0xFFFFFFFFU
} SceFiosProfilingMask;

typedef enum SceFiosOverlayLimits {
	SCE_FIOS_OVERLAY_MAX_OVERLAYS = 64,
	SCE_FIOS_OVERLAY_POINT_MAX    = 292
} SceFiosOverlayLimits;

typedef enum SceFiosOverlayType {
	SCE_FIOS_OVERLAY_TYPE_OPAQUE      = 0,
	SCE_FIOS_OVERLAY_TYPE_TRANSLUCENT = 1,
	SCE_FIOS_OVERLAY_TYPE_NEWER       = 2,
	SCE_FIOS_OVERLAY_TYPE_WRITABLE    = 3
} SceFiosOverlayType;

typedef enum SceFiosOverlayOrder {
	SCE_FIOS_OVERLAY_ORDER_USER_FIRST = 0,
	SCE_FIOS_OVERLAY_ORDER_USER_LAST  = 127
} SceFiosOverlayOrder;

typedef enum SceFiosOverlayResolveMode {
	SCE_FIOS_OVERLAY_RESOLVE_FOR_READ = 0,
	SCE_FIOS_OVERLAY_RESOLVE_FOR_WRITE = 1
} SceFiosOverlayResolveMode;

#define SCE_FIOS_INVALID_LBA 0x7FFFFFFFFFFFFFFFLL

typedef enum SceFiosProfilingEventType {
	SCE_FIOS_PROFILE_EVENT_OPEN = 0,
	SCE_FIOS_PROFILE_EVENT_READ = 1,
	SCE_FIOS_PROFILE_EVENT_WRITE = 2,
	SCE_FIOS_PROFILE_EVENT_CLOSE = 3,
	SCE_FIOS_PROFILE_EVENT_STAT = 4,
	SCE_FIOS_PROFILE_EVENT_SYNC = 5,
	SCE_FIOS_PROFILE_EVENT_OPENDIR = 6,
	SCE_FIOS_PROFILE_EVENT_READDIR = 7,
	SCE_FIOS_PROFILE_EVENT_CLOSEDIR = 8,
	SCE_FIOS_PROFILE_EVENT_SCHEDULETREE = 9,
	SCE_FIOS_PROFILE_EVENT_UNSCHEDULETREE = 10,
	SCE_FIOS_PROFILE_EVENT_ADDTOSCHEDULE = 11,
	SCE_FIOS_PROFILE_EVENT_REMOVEFROMSCHEDULE = 12,
	SCE_FIOS_PROFILE_EVENT_EXECUTE = 13
} SceFiosProfilingEventType;

typedef struct SceFiosIoProfileData {
	SceFiosOffset offset;
	SceFiosOffset LBA;
	SceFiosSize length;
	SceFiosTime deadline;
	const char * path;
	uint16_t chunkID;
	int8_t priority;
	int8_t reserved[1];
} SceFiosIoProfileData;

typedef struct SceFiosSchedulerProfileData {
	intptr_t threadId;
	uint16_t chunkID;
	uint8_t chunkType;
	int8_t reserved[1];
} SceFiosSchedulerProfileData;

typedef struct SceFiosProfilingEvent {
	SceFiosTime startTime;
	SceFiosTime endTime;
	const void* data;
	int8_t eventType;
	int8_t reserved[3];
} SceFiosProfilingEvent;

typedef void (*SceFiosProfileCallback)(const SceFiosProfilingEvent *event);

typedef struct SceFiosBuffer {
	void *pPtr;
	size_t length;
	#ifdef __cplusplus
	inline void set(void *pBuf, size_t bufLen) { pPtr = pBuf; length = bufLen; }
	inline uint8_t * start() { return (uint8_t*)pPtr; }
	inline uint8_t * end() { return (uint8_t*)pPtr + length; }
	inline bool isAligned(size_t s) { return SCE_FIOS_ALIGN_DOWN((intptr_t)pPtr,(intptr_t)s) == (intptr_t)pPtr; }
	#endif
} SceFiosBuffer;
#define SCE_FIOS_BUFFER_INITIALIZER  { 0, 0 }

typedef struct SceFiosOpAttr {
	SceFiosTime       deadline;
	SceFiosOpCallback pCallback;
	void *            pCallbackContext;
	int32_t           priority : 8;
	uint32_t          opflags : 24;
	uint32_t          userTag;
	void *            userPtr;
	void *            pReserved;
} SceFiosOpAttr;
#define SCE_FIOS_OPATTR_INITIALIZER { 0, 0, 0, 0, 0, 0, 0, 0 }

typedef struct SceFiosDirEntry {
	SceFiosOffset     fileSize;
	uint32_t          statFlags;
	uint16_t          nameLength;
	uint16_t          fullPathLength;
	uint16_t          offsetToName;
	uint16_t          reserved[3];
	char              fullPath[SCE_FIOS_PATH_MAX];
} SceFiosDirEntry;
#define SCE_FIOS_DIRENTRY_INITIALIZER { 0, 0, 0, 0, 0, {0,0,0}, "" }

typedef struct SceFiosStat {
	SceFiosOffset     fileSize;
	SceFiosDate       accessDate;
	SceFiosDate       modificationDate;
	SceFiosDate       creationDate;
	uint32_t          statFlags;
	uint32_t          reserved;
	int64_t           uid;
	int64_t           gid;
	int64_t           dev;
	int64_t           ino;
	int64_t           mode;
} SceFiosStat;
#define SCE_FIOS_STAT_INITIALIZER { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

typedef struct SceFiosOpenParams {
	uint32_t        openFlags:16;
	uint32_t        opFlags:16;
	uint32_t        reserved;
	SceFiosBuffer   buffer;
} SceFiosOpenParams;
#define SCE_FIOS_OPENPARAMS_INITIALIZER { 0, 0, 0, SCE_FIOS_BUFFER_INITIALIZER }

typedef struct SceFiosTuple {
	SceFiosOffset offset;
	SceFiosSize   size;
	char          path[SCE_FIOS_PATH_MAX];
} SceFiosTuple;
#define SCE_FIOS_TUPLE_INITIALIZER   { 0, 0, "" }

typedef enum SceFiosIOThreadCount {
	SCE_FIOS_IO_THREAD_COUNT_MIN = 1,
	SCE_FIOS_IO_THREAD_COUNT_MAX = 2
} SceFiosIOThreadCount;

typedef enum SceFiosSchedulerThreadCount {
	SCE_FIOS_SCHEDULER_THREAD_COUNT_MIN = 1,
	SCE_FIOS_SCHEDULER_THREAD_COUNT_MAX = 2,
	SCE_FIOS_SCHEDULER_THREAD_COUNT_DEFAULT = 1
} SceFiosSchedulerThreadCount;

#define SCE_FIOS_DECOMPRESSOR_THREAD_COUNT_MAX      3

#define SCE_FIOS_DECOMPRESSOR_THREAD_COUNT_DEFAULT  2

#define SCE_FIOS_CHUNK_DEFAULT         (256*1024)

typedef struct SceFiosParams {
	uint32_t initialized : 1;
	uint32_t paramsSize : 15;
	uint32_t pathMax : 16;
	uint32_t profiling;
	uint32_t ioThreadCount;
	uint32_t threadsPerScheduler;
	uint32_t extraFlag1 : 1;
	uint32_t extraFlags : 31;
	uint32_t maxChunk;
	uint8_t  maxDecompressorThreadCount;
	uint8_t  reserved1;
	uint8_t  reserved2;
	uint8_t  reserved3;
	intptr_t reserved4;
	intptr_t reserved5;
	SceFiosBuffer opStorage;
	SceFiosBuffer fhStorage;
	SceFiosBuffer dhStorage;
	SceFiosBuffer chunkStorage;
	SceFiosVprintfCallback pVprintf;
	SceFiosMemcpyCallback  pMemcpy;
	SceFiosProfileCallback pProfileCallback;
	int    threadPriority[SCE_FIOS_THREAD_TYPES];
	int    threadAffinity[SCE_FIOS_THREAD_TYPES];
	int    threadStackSize[SCE_FIOS_THREAD_TYPES];
} SceFiosParams;

#define SCE_FIOS_PARAMS_INITIALIZER   { 0, sizeof(SceFiosParams), 0, 0, \
		SCE_FIOS_IO_THREAD_COUNT_MAX, SCE_FIOS_SCHEDULER_THREAD_COUNT_DEFAULT, \
		0, 0, \
		SCE_FIOS_CHUNK_DEFAULT, \
		SCE_FIOS_DECOMPRESSOR_THREAD_COUNT_DEFAULT, 0, 0, 0, 0, 0, \
		SCE_FIOS_BUFFER_INITIALIZER, SCE_FIOS_BUFFER_INITIALIZER, SCE_FIOS_BUFFER_INITIALIZER, SCE_FIOS_BUFFER_INITIALIZER, \
		NULL, NULL, NULL, \
		{ SCE_FIOS_IO_THREAD_DEFAULT_PRIORITY, SCE_FIOS_DECOMPRESSOR_THREAD_DEFAULT_PRIORITY, SCE_FIOS_CALLBACK_THREAD_DEFAULT_PRIORITY }, \
		{ SCE_FIOS_IO_THREAD_DEFAULT_AFFINITY, SCE_FIOS_DECOMPRESSOR_THREAD_DEFAULT_AFFINITY, SCE_FIOS_CALLBACK_THREAD_DEFAULT_AFFINITY}, \
		{ SCE_FIOS_IO_THREAD_DEFAULT_STACKSIZE, SCE_FIOS_DECOMPRESSOR_THREAD_DEFAULT_STACKSIZE, SCE_FIOS_CALLBACK_THREAD_DEFAULT_STACKSIZE}}

#define SCE_FIOS_DH_STORAGE_ALIGNMENT                  8
#define SCE_FIOS_FH_STORAGE_ALIGNMENT                  8
#define SCE_FIOS_OP_STORAGE_ALIGNMENT                  8

#define SCE_FIOS_CHUNK_STORAGE_ALIGNMENT               8

#define SCE_FIOS_FH_SIZE	80
#define SCE_FIOS_DH_SIZE	80
#define SCE_FIOS_OP_SIZE	168
#define SCE_FIOS_CHUNK_SIZE	64

#define SCE_FIOS_STORAGE_SIZE(num, size) \
	(((num) * (size)) + SCE_FIOS_ALIGN_UP(SCE_FIOS_ALIGN_UP((num), 8) / 8, 8))

#define SCE_FIOS_DH_STORAGE_SIZE(numDHs, pathMax) \
	SCE_FIOS_STORAGE_SIZE(numDHs, SCE_FIOS_DH_SIZE + pathMax)

#define SCE_FIOS_FH_STORAGE_SIZE(numFHs,pathMax) \
	SCE_FIOS_STORAGE_SIZE(numFHs, SCE_FIOS_FH_SIZE + pathMax)

#define SCE_FIOS_OP_STORAGE_SIZE(numOps,pathMax) \
	SCE_FIOS_STORAGE_SIZE(numOps, SCE_FIOS_OP_SIZE + pathMax)

#define SCE_FIOS_CHUNK_STORAGE_SIZE(numChunks) \
	SCE_FIOS_STORAGE_SIZE(numChunks, SCE_FIOS_CHUNK_SIZE)

#define SCE_FIOS_MAX_ALLOCATION_SIZE 65536

#define SCE_FIOS_MAX_HANDLE_ELEMENTS 16384

#define SCE_FIOS_CHUNK_ALLOCATION_UNIT    8

#define SCE_FIOS_CHUNK_STORAGE_SIZE_MAX \
	SCE_FIOS_STORAGE_SIZE(SCE_FIOS_MAX_ALLOCATION_SIZE, SCE_FIOS_CHUNK_ALLOCATION_UNIT)

typedef struct SceFiosOverlay {
	uint8_t type;
	uint8_t order;
	uint8_t reserved[10];
	SceFiosOverlayID id;
	char    dst[SCE_FIOS_OVERLAY_POINT_MAX];
	char    src[SCE_FIOS_OVERLAY_POINT_MAX];
} SceFiosOverlay;
#define SCE_FIOS_OVERLAY_INITIALIZER   {0,0,{0,0,0,0,0,0,0,0,0,0},0,"",""}

#endif
