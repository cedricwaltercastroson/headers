#ifndef _DOLCESDK_PSP2_GXM_DISPLAY_QUEUE_H_
#define _DOLCESDK_PSP2_GXM_DISPLAY_QUEUE_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/error.h>
#include <psp2/gxm/sync_object.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** A callback function to handle displaying a buffer.

	This function is called when the GPU has completed rendering.  It is
	responsible for flipping the display buffer and blocking until the
	flip operation is completed.  This means there is the potential for the old
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

	@param[in]	callbackData	A pointer to data that was copied to internal
								storage during #sceGxmDisplayQueueAddEntry().

	@ingroup render
*/
typedef void (* SceGxmDisplayQueueCallback)(const void *callbackData);

/** Adds an entry to the display queue.  The parameters pointed to by
	<c><i>callbackData</i></c> are copied to internal storage during this call.  Because this
	copy is passed to the callback there is no need for the parameters to persist
	once this call has completed.

	The display callback will be called from a thread once all queued
	operations to both the old and new buffers have completed.

	@param[in]	oldBuffer		A pointer to a sync object that is associated with the
								currently displayed buffer at the time this entry
								is processed.
	@param[in]	newBuffer		A pointer to a sync object associated with the
								buffer that will be displayed by the callback.
	@param[in]	callbackData	A pointer to the data to be passed to the display
								callback.  This data is copied to internal
								storage during this call.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED No display queue callback was provided to #sceGxmInitialize()
	as part of the #SceGxmInitializeParams structure.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER A pointer parameter was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmDisplayQueueAddEntry(
	SceGxmSyncObject *oldBuffer,
	SceGxmSyncObject *newBuffer,
	const void *callbackData);

/** Blocks until all pending display queue entries have completed.  This
	function can be called to ensure that there will be no further calls
	to the display callback.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED No display queue callback was provided to #sceGxmInitialize()
								as part of the #SceGxmInitializeParams structure.

	@ingroup render
*/
SceGxmErrorCode sceGxmDisplayQueueFinish(void);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_DISPLAY_QUEUE_H_ */
