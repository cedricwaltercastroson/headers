#ifndef _DOLCESDK_PSP2_GXM_SYNC_OBJECT_H_
#define _DOLCESDK_PSP2_GXM_SYNC_OBJECT_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/error.h>
#include <psp2/gxm/structs.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Creates a sync object.  Currently sync objects are used purely to
	synchronize rendering with display operations in the display queue.

	@param[out]	syncObject		A pointer to storage for a sync object pointer.

	@retval
	SCE_OK		The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed as the sync object pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmSyncObjectCreate(SceGxmSyncObject **syncObject);

/** Destroys a sync object.

	@param[in,out]	syncObject		A sync object pointer.

	@retval
	SCE_OK		The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed as the sync object pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmSyncObjectDestroy(SceGxmSyncObject *syncObject);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_SYNC_OBJECT_H_ */
