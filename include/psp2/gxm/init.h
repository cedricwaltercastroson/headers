#ifndef _DOLCESDK_PSP2_GXM_INIT_H_
#define _DOLCESDK_PSP2_GXM_INIT_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/constants.h>
#include <psp2/gxm/error.h>
#include <psp2/gxm/structs.h>
#include <psp2/gxm/display_queue.h>
#include <psp2/kernel/sysmem.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The number of notifications created during #sceGxmInitialize().  Each notification is
	a 32-bit word, that can be used as the address in a #SceGxmNotification structure.

	@ingroup render
*/
#define SCE_GXM_NOTIFICATION_COUNT						512

/** A default size for the libgxm parameter buffer.

	@ingroup render
*/
#define SCE_GXM_DEFAULT_PARAMETER_BUFFER_SIZE			(16*1024*1024)

/** Flags for libgxm initialization.

	@ingroup render
*/

typedef enum SceGxmInitializeFlags
{
	SCE_GXM_INITIALIZE_FLAG_DISPLAY_QUEUE_THREAD_AFFINITY_CPU_0		=	0x00000000U,	///< Display queue thread and callback will run on user CPU 0
	SCE_GXM_INITIALIZE_FLAG_DISPLAY_QUEUE_THREAD_AFFINITY_CPU_1		=	0x00010000U,	///< Display queue thread and callback will run on user CPU 1
	SCE_GXM_INITIALIZE_FLAG_DISPLAY_QUEUE_THREAD_AFFINITY_CPU_2		=	0x00020000U		///< Display queue thread and callback will run on user CPU 2
} SceGxmInitializeFlags;

/** The initialization parameters for the library.

	@ingroup render
*/
typedef struct SceGxmInitializeParams {
	/** Flags from #SceGxmInitializeFlags
	*/
	uint32_t flags;

	/**	The maximum number of pending display swaps to allow before blocking.
		This is usually a low number, such as 2 or 3.
	*/
	uint32_t displayQueueMaxPendingCount;

	/** The callback function to use to display a buffer.

		This function is called when the GPU has completed rendering.  It is
		responsible for flipping the display buffer and blocking until the
		flip operation is completed.  After the function returns, the GPU will
		be allowed to continue. This means there is the potential for the old
		display buffer to be overwritten immediately.

		Since the libgxm context is single threaded, no libgxm context functions
		or synchronization functions should be called from this callback function;
		otherwise undefined behavior could occur.  In particular, neither the
		#sceGxmNotificationWait() synchronization function or any function that takes a
		libgxm context (such as #sceGxmBeginScene(), #sceGxmDraw() or #sceGxmFinish())
		should be called.

		The expected behavior is to call <c>sceDisplaySetFrameBuf()</c> to enqueue a new
		display buffer address. A call to <c>sceDisplayWaitSetFrameBuf()</c> should follow this
		if the flip operation was called with <c>SCE_DISPLAY_UPDATETIMING_NEXTVSYNC</c>.
		This ensures that future GPU operations on the old front buffer do not start
		until the new front buffer is being displayed.
	*/
	SceGxmDisplayQueueCallback displayQueueCallback;

	/** The size of the data that needs to be passed to the callback function. Storage will be allocated
		to ensure this data can be copied to the display queue.

		The total size of the storage of displayQueueMaxPendingCount*displayQueueCallbackDataSize must
		not exceed 512 bytes.
	*/
	uint32_t displayQueueCallbackDataSize;

	/** The size of parameter buffer to allocate.
	*/
	uint32_t parameterBufferSize;

} SceGxmInitializeParams;

/** Initializes the libgxm library.

	Internally this function will prepare this process for rendering, creating
	the parameter buffer with the given size.

	This function must be called before any other libgxm object is created, such
	as a context, or sync object.

	@param[in]	params					A pointer to a populated SceGxmInitializeParams structure.

	@retval
	SCE_OK	The operation completed successfully.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER		The SceGxmInitializeParams pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE			One or more parameters were invalid.
	@retval
	SCE_GXM_ERROR_ALREADY_INITIALIZED	The operation failed because libgxm is already initialized.
	@retval
	SCE_GXM_ERROR_OUT_OF_MEMORY			There was no memory to perform the operation.
	@retval
	SCE_GXM_ERROR_DRIVER				The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmInitialize(const SceGxmInitializeParams *params);

/** Returns the parameter buffer size used for geometry data.

	Specifically, this is the size of the
	parameter buffer memory area reserved during the call to #sceGxmInitialize(), whose size is specified
	by <c>SceGxmInitializeParams.parameterBufferSize</c> minus the memory area reserved internally
	to store page management data and for use during partial renders.

	@param[out]	parameterBufferSize					A pointer to storage for the parameter buffer geometry data memory size.

	@retval
	SCE_OK	The operation completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED	The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER	The <c><i>parameterBufferSize</i></c> pointer was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmGetParameterBufferThreshold(uint32_t *parameterBufferSize);


/** Gets the start of the notification region created during #sceGxmInitialize().
	Within this region, #SCE_GXM_NOTIFICATION_COUNT 32-bit notification values can be
	used.

	All values within the notification region are initialized to zero when libgxm is
	initialized.

	@return
	A pointer to a region of memory which can hold 32-bit values for #SceGxmNotification objects.

	@ingroup render
*/
volatile uint32_t *sceGxmGetNotificationRegion(void);

/** Waits until a given notification has completed.

	A notification is considered to be completed when the following is true:

	@code
		*notification->address == notification->value
	@endcode

	Note that this function blocks execution (suspending the calling thread)
	until the notification has completed.

	This function is equivalent to polling the notification with a call to
	#sceGxmWaitEvent() between polling attempts.

	@param[in]	notification	A pointer to the notification struct.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to the notification pointer being out of range.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to the notification pointer being <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_THREAD The operation failed because the function was called from the display queue thread.

	@ingroup render
*/
SceGxmErrorCode sceGxmNotificationWait(const SceGxmNotification* notification);

/** Waits for a GPU event to occur.

	This function blocks execution of the calling thread until one of the following
	occurs:
	<ul>
	<li>The GPU has finished a job for <em>any</em> process since the last time
	#sceGxmWaitEvent() was called from this thread.
	<li>The GPU has finished an internal firmware job since the last call to
	#sceGxmWaitEvent() from this thread.
	<li>An internal GPU driver timeout occurred while waiting.
	</ul>

	Any of these conditions will result in the thread waking up and a return
	value of <c>SCE_OK</c>.

	This function may be called from any thread.

	@retval
	SCE_OK	The operation was successful.
	@retval
	SCE_GXM_ERROR_DRIVER
	An internal driver error occurred.

	@ingroup render
*/
SceGxmErrorCode sceGxmWaitEvent(void);

/** Terminates the libgxm library.

	This function should be called before the process exits, after all other libgxm
	objects have been destroyed.

	@retval
	SCE_OK	The operation completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because libgxm is not initialized.

	@ingroup render
*/
SceGxmErrorCode sceGxmTerminate(void);

/** Warnings that can be selectively configured using #sceGxmSetWarningEnabled().

	@ingroup render
*/
typedef enum SceGxmWarning {
	SCE_GXM_WARNING_SCENE_SPLIT,  										///< Ring buffer high-water marks have been passed, resulting in the scene being split into multiple jobs.
	SCE_GXM_WARNING_VERTEX_DEFAULT_UNIFORM_BUFFER_RECYCLED,				///< The previous vertex default uniform buffer has not been used, resulting in it being recycled.
	SCE_GXM_WARNING_FRAGMENT_DEFAULT_UNIFORM_BUFFER_RECYCLED,			///< The previous fragment default uniform buffer has not been used, resulting in it being recycled.
	SCE_GXM_WARNING_STREAMS_PROVIDED_WITH_ZERO_COUNT,					///< Streams provided to #sceGxmShaderPatcherCreateVertexProgram(), but the provided stream count is 0.
	SCE_GXM_WARNING_ATTRIBUTES_PROVIDED_WITH_ZERO_COUNT,				///< Attributes provided to #sceGxmShaderPatcherCreateVertexProgram(), but the provided attribute count is 0.
	SCE_GXM_WARNING_PROGRAM_REGISTERED_WITH_SHADER_PATCHER,				///< Program is being registered multiple times with the shader patcher.
	SCE_GXM_WARNING_BLEND_INFO_IGNORED_FOR_NATIVECOLOR,					///< Ignoring #SceGxmBlendInfo structure provided to #sceGxmShaderPatcherCreateFragmentProgram() as program uses __nativecolor.
	SCE_GXM_WARNING_USING_INTERPOLANT_NOT_WRITTEN_BY_VERTEX_PROGRAM,	///< An interpolant is being used by the fragment program, without being written by the associated vertex program.
	SCE_GXM_WARNING_DEPTH_STENCIL_SURFACE_SETTING_IGNORED,				///< The depth stencil surface has a setting which is ignored.
	SCE_GXM_WARNING_DEFERRED_CONTEXT_MISSING_VIEWPORT,					///< A deferred context has encountered a draw call, but it has not had a valid viewport set.
	SCE_GXM_WARNING_DEFERRED_CONTEXT_MISSING_REGION_CLIP,				///< A deferred context has encountered a draw call, but it has not had a valid region clip set.
	SCE_GXM_WARNING_USING_INAPPROPRIATE_MEMORY_CACHE_CONFIGURATION,		///< Supplied memory is using an inappropriate cache configuration.
	SCE_GXM_WARNING_PRECOMPUTING_DISABLED_FRAGMENT_STATE				///< Precomputed fragment state is being created for a fragment program with shading disabled.
} SceGxmWarning;

/** Configures warnings that are output when running the debug version of libgxm.

	When running the debug version of libgxm, warnings may be output to TTY indicating the
	occurrence of events that an application developer would wish to informed of. By default
	all of the warning types present in the #SceGxmWarning enumeration are enabled. This
	function can be called to enable/disable warnings.

	@param[in]	warning					The warning to configure.
	@param[in]	enable					true if the warning is to be enabled, else false.

	@retval
	SCE_OK								The operation completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED 		The operation failed because libgxm is not initialized.

	@note When not running the debug version of libgxm, this function has no effect.

	@ingroup render
*/

SceGxmErrorCode sceGxmSetWarningEnabled(SceGxmWarning warning, bool enable);

/** Determines whether the debug version of libgxm is currently being used.

    @retval
	true					The debug version of libgxm is being used.
    @retval
	false					The debug version of libgxm is not being used.

	@ingroup render
*/

bool sceGxmIsDebugVersion(void);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_INIT_H_ */
