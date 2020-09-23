#ifndef _DOLCESDK_PSP2_GXM_MEMORY_H_
#define _DOLCESDK_PSP2_GXM_MEMORY_H_

/** @file

  	Memory mapping API for the GPU.
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/error.h>
#include <psp2/kernel/sysmem.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Flags that can be used when mapping memory using #sceGxmMapMemory().

	@ingroup render
*/
typedef enum SceGxmMemoryAttribFlags
{
	SCE_GXM_MEMORY_ATTRIB_READ			= 0x00000001,	///< The GPU is permitted to read.
	SCE_GXM_MEMORY_ATTRIB_WRITE			= 0x00000002	///< The GPU is permitted to write.
} SceGxmMemoryAttribFlags;

/** Maps memory for GPU usage.  Once mapped, pointers within the region of
	memory described by <c><i>base</i></c> and <c><i>size</i></c> may be used with libgxm
	functions directly.	It is not valid to call this function with a memory range where all
	or part of that range has already been mapped.

	@param[in]	base		A 4K-aligned base address of the region to map.
	@param[in]	size		A 4K-aligned size in bytes of the region to map.
	@param[in]	attribs		Bitwise combined attributes from #SceGxmMemoryAttribFlags.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmMapMemory(void *base, uint32_t size, uint32_t attribs);

/** Unmaps memory, removing it from GPU usage.  It is the responsibility of
	the caller to ensure that the GPU no longer needs this memory for rendering.
	This could be accomplished by calling #sceGxmFinish() before unmapping.

	@param[in]	base	The base address of the region to unmap.  This must match
						the base address that was used when mapping the memory
						using #sceGxmMapMemory().

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmUnmapMemory(void *base);

/** Maps memory for vertex USSE code usage.  If successful, this mapping
	operation returns a USSE offset to address the memory as vertex USSE code.

	@param[in]	base	A 4K-aligned base address of the region to map.
	@param[in]	size	A 4K-aligned size in bytes of the region to map. This
						cannot be greater than 8MB.
	@param[in]	offset	A pointer to a 32-bit value to hold the USSE offset.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a parameter was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmMapVertexUsseMemory(void *base, uint32_t size, uint32_t *offset);

/** Unmaps memory that was previously mapped as vertex USSE code.  It is the
	responsibility of the caller to ensure that the GPU no longer needs this
	memory for rendering.  This could be accomplished by calling #sceGxmFinish()
	before unmapping.

	@param[in]	base	The base address of the region to unmap.  This must match
						the base address that was used when mapping the memory
						using #sceGxmMapVertexUsseMemory().

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmUnmapVertexUsseMemory(void *base);

/** Maps memory for fragment USSE code usage.  If successful, this mapping
	operation returns a USSE offset to address the memory as fragment USSE code.

	@param[in]	base	A 4K-aligned base address of the region to map.
	@param[in]	size	A 4K-aligned size in bytes of the region to map. This
						cannot be greater than 8MB.
	@param[in]	offset	A pointer to a 32-bit value to hold the USSE offset.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a parameter was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmMapFragmentUsseMemory(void *base, uint32_t size, uint32_t *offset);

/** Unmaps memory that was previously mapped as fragment USSE code.  It is the
	responsibility of the caller to ensure that the GPU no longer needs this
	memory for rendering.  This could be accomplished by calling #sceGxmFinish()
	before unmapping.

	@param[in]	base	The base address of the region to unmap.  This must match
						the base address that was used when mapping the memory
						using #sceGxmMapFragmentUsseMemory().

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmUnmapFragmentUsseMemory(void *base);

/** Register a capture buffer with Razor.

	This API is required only when performing a Razor GPU Capture.

	Registering a buffer with Razor is only necessary if the size of a user
	declared uniform buffer declared in a vertex or fragment program can be
	exceeded through dynamic indexing at runtime. One example is an array of
	matrices dynamically indexed by a vertex program performing skinning.

	When a uniform buffer start address is set, by calling
	#sceGxmSetVertexUniformBuffer() or #sceGxmSetFragmentUniformBuffer(), for a
	vertex or fragment program which dynamically indexes the buffer, Razor
	will try to capture the whole registered capture buffer whose range
	includes this start address. Therefore, one call to this function can
	register one single capture buffer,sub-ranges of which can be used as
	user-declared uniform buffers for individual draw calls.

	Currently up to 1024 buffers can be registered through this API at any
	one time.

	@param[in]	base	The base address of the GPU capture buffer.
	@param[in]	size	The size of the capture buffer in bytes.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>size</i></c> parameter was 0.
	@retval
	SCE_GXM_ERROR_RAZOR The operation failed because of an error in the Razor layer.

	@ingroup render
 */
SceGxmErrorCode sceGxmAddRazorGpuCaptureBuffer(void* base, uint32_t size);

/** Unregister a capture buffer from Razor.

	Please see #sceGxmAddRazorGpuCaptureBuffer() for details on the matching
	API to use for adding GPU capture buffers.

	@param[in]	base	The base address of the GPU capture buffer.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_RAZOR The operation failed because of an error in the Razor layer.

	@ingroup render
 */
SceGxmErrorCode sceGxmRemoveRazorGpuCaptureBuffer(void* base);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_MEMORY_H_ */
