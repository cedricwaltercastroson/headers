#ifndef _DOLCESDK_PSP2_GXM_SHADER_PATCHER_H_
#define _DOLCESDK_PSP2_GXM_SHADER_PATCHER_H_

/** @file
*/

#include <psp2/gxm/context.h>
#include <psp2/gxm/blending.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The opaque structure for shader patcher internals.

	@ingroup shaderpatcher
*/
typedef struct SceGxmShaderPatcher SceGxmShaderPatcher;

/** The opaque structure for a registered program.

	@ingroup shaderpatcher
*/
typedef struct SceGxmRegisteredProgram SceGxmRegisteredProgram;

/** The opaque structure for a registered program, exposed as an ID.

	@ingroup shaderpatcher
*/
typedef struct SceGxmRegisteredProgram *SceGxmShaderPatcherId;

/** The shader patcher host memory allocation callback.  This should return standard
	cached CPU memory for shader patcher data structures, such as that returned from
	libc malloc.

	@param[in,out]	userData	A pointer to user data for optional use by the callback.
	@param[in]		size		The size in bytes of the memory to allocate.

	@return
	A pointer to the allocated memory, or <c>NULL</c> if none can be allocated.  The
	pointer must be aligned to at least 4 bytes.

	@ingroup shaderpatcher
*/
typedef void *(* SceGxmShaderPatcherHostAllocCallback)(void *userData, uint32_t size);

/** The shader patcher host memory free callback.

	@param[in,out]	userData	A pointer to user data for optional use by the callback.
	@param[in,out]	mem			A pointer to the memory to be freed.

	@ingroup shaderpatcher
*/
typedef void (* SceGxmShaderPatcherHostFreeCallback)(void *userData, void *mem);

/** The shader patcher buffer memory allocation callback.

	This callback is called to allocate memory for buffers required by vertex
	or fragment programs, and is called when the program is registered using
	#sceGxmShaderPatcherRegisterProgram().  These buffers can be used for:

	<ul>
	<li>Constant literals loaded from memory by the USSE.  Usually the shader compiler
	will be able to remap literals to secondary attribute registers, but if pressure
	is high enough then literals must sometimes be loaded from memory directly.
	<li>Spilled values or indexable temps.  If the shader compiler needs to spill temp
	registers to memory then this buffer needs to be allocated.
	</ul>

	Any buffers allocated using this callback will be shared by all vertex or fragment
	programs created from the registered program.  The memory allocated by this callback
	must have been mapped with both #SCE_GXM_MEMORY_ATTRIB_READ and #SCE_GXM_MEMORY_ATTRIB_WRITE
	access using #sceGxmMapMemory().

	@param[in,out]	userData	A pointer to user data for optional use by the callback.
	@param[in]		size		The size in bytes of memory to allocate.

	@return
	A pointer to the allocated memory, or <c>NULL</c> if none can be allocated.  The
	pointer must be aligned to at least 4 bytes.

	@ingroup shaderpatcher
*/
typedef void *(* SceGxmShaderPatcherBufferAllocCallback)(void *userData, uint32_t size);

/** The shader patcher buffer memory deallocation callback.

	This callback is called to deallocate memory for buffers required by vertex or
	fragment programs.  It is called when the program is unregistered using
	#sceGxmShaderPatcherUnregisterProgram().

	@param[in,out]	userData	A pointer to user data for optional use by the callback.
	@param[in,out]	mem			A pointer to the memory to be freed.

	@ingroup shaderpatcher
*/
typedef void (* SceGxmShaderPatcherBufferFreeCallback)(void *userData, void *mem);

/** The shader patcher vertex or fragment USSE allocation callback.

	This callback is called to allocate memory for USSE code required by the vertex
	or fragment programs.  It is called when a new program needs to be created
	during #sceGxmShaderPatcherCreateVertexProgram() or #sceGxmShaderPatcherCreateFragmentProgram().

	Any buffers allocated using this callback will be shared by all vertex or fragment
	programs created from the registered program.  The memory allocated by this callback
	must have been mapped as vertex or fragment USSE code, depending on whether the
	callback is the vertex USSE callback or fragment USSE callback respectively.

	Note that it is possible to map memory as both vertex and fragment USSE code,
	and the shader patcher can be configured to use a shared heap for vertex and
	fragment USSE code.  See the documentation for #SceGxmShaderPatcherParams for
	more details.

	@param[in,out]	userData	A pointer to user data for optional use by the callback.
	@param[in]		size		The size in bytes of the memory to allocate.
	@param[out]		usseOffset	The storage for the USSE offset of the allocation.

	@return
	A pointer to the allocated memory, or <c>NULL</c> if none can be allocated. The
	pointer must be aligned to at least #SCE_GXM_USSE_ALIGNMENT bytes.

	@ingroup shaderpatcher
*/
typedef void *(* SceGxmShaderPatcherUsseAllocCallback)(void *userData, uint32_t size, uint32_t *usseOffset);

/** The shader patcher vertex or fragment USSE deallocation callback.

	This callback is called to deallocate memory for USSE code required by the
	vertex or fragment programs, and is called when a program hits a reference
	count of zero and is destroyed during #sceGxmShaderPatcherReleaseVertexProgram()
	or #sceGxmShaderPatcherReleaseFragmentProgram().

	@param[in,out]	userData	A pointer to user data for optional use by the callback.
	@param[in,out]	mem			A pointer to the memory to be freed.

	@ingroup shaderpatcher
*/
typedef void (* SceGxmShaderPatcherUsseFreeCallback)(void *userData, void *mem);

/** The initialization parameters for the shader patcher.

	Host memory must always be provided using the callbacks <c>hostAllocCallback</c>
	and <c>hostFreeCallback</c>.

	For the remaining categories of callback, either an alloc/free callback pair
	must be provided, or a static allocation.  When a static allocation is provided,
	the shader patcher will internally create a heap on that allocation, implementing
	the callbacks itself.

	If the base addresses and sizes of the vertex USSE memory and fragment USSE
	memory match, then the allocation is treated as a shared heap.  For this case,
	the memory must be mapped as both vertex and fragment USSE code using
	#sceGxmMapVertexUsseMemory() and #sceGxmMapFragmentUsseMemory(), which allows
	for vertex and fragment code to share a memory budget.  If the base addresses
	or sizes are different, then the heaps will be independent.

	@ingroup shaderpatcher
*/
typedef struct SceGxmShaderPatcherParams {
	/// The user data parameter to pass to memory callbacks.
	void *userData;

	/// The callback for host memory allocations. This cannot be <c>NULL</c>.
	SceGxmShaderPatcherHostAllocCallback hostAllocCallback;

	/// The callback for host memory deallocations. This cannot be <c>NULL</c>.
	SceGxmShaderPatcherHostFreeCallback hostFreeCallback;

	/** The callback for GPU buffer memory allocations.  This callback can be <c>NULL</c>
		if a pre-allocated region for buffers is provided, in which case the
		shader patcher will manage a heap internally using this region.
	*/
	SceGxmShaderPatcherBufferAllocCallback bufferAllocCallback;

	/** The callback for GPU buffer memory deallocations.  This callback can be <c>NULL</c>
		if a pre-allocated region for buffers is provided, in which case the
		shader patcher will manage a heap internally using this region.
	*/
	SceGxmShaderPatcherBufferFreeCallback bufferFreeCallback;

	/** The pre-allocated memory region for GPU buffers.  This region must be <c>NULL</c>
		if buffer allocation callbacks are provided.
	*/
	void *bufferMem;

	/** The size of the pre-allocated memory region for GPU buffers.  This size
		must be zero if buffer allocation callbacks are provided.
	*/
	uint32_t bufferMemSize;

	/** The callback for vertex USSE code memory allocations.  This callback can be <c>NULL</c>
		if a pre-allocated region for vertex USSE code is provided, in which case the
		shader patcher will manage a heap internally using this region.
	*/
	SceGxmShaderPatcherUsseAllocCallback vertexUsseAllocCallback;

	/** The callback for vertex USSE code memory deallocations.  This callback can be <c>NULL</c>
		if a pre-allocated region for vertex USSE code is provided, in which case the
		shader patcher will manage a heap internally using this region.
	*/
	SceGxmShaderPatcherUsseFreeCallback vertexUsseFreeCallback;

	/** The pre-allocated memory region for vertex USSE code.  This region must be <c>NULL</c>
		if vertex USSE allocation callbacks are provided.
	*/
	void *vertexUsseMem;

	/** The size of the pre-allocated memory region for vertex USSE code.  This size
		must be zero if vertex USSE allocation callbacks are provided.
	*/
	uint32_t vertexUsseMemSize;

	/** The USSE offset of the pre-allocated memory region for vertex USSE code.  This
		field is ignored if vertex USSE allocation callbacks are provided.
	*/
	uint32_t vertexUsseOffset;

	/** The callback for fragment USSE code memory allocations.  This callback can be <c>NULL</c>
		if a pre-allocated region for fragment USSE code is provided, in which case the
		shader patcher will manage a heap internally using this region.
	*/
	SceGxmShaderPatcherUsseAllocCallback fragmentUsseAllocCallback;

	/** The callback for fragment USSE code memory deallocations.  This callback can be <c>NULL</c>
		if a pre-allocated region for fragment USSE code is provided, in which case the
		shader patcher will manage a heap internally using this region.
	*/
	SceGxmShaderPatcherUsseFreeCallback fragmentUsseFreeCallback;

	/** The pre-allocated memory region for fragment USSE code.  This region must be <c>NULL</c>
		if fragment USSE allocation callbacks are provided.
	*/
	void *fragmentUsseMem;

	/** The size of the pre-allocated memory region for fragment USSE code.  This size
		must be zero if fragment USSE allocation callbacks are provided.
	*/
	uint32_t fragmentUsseMemSize;

	/** The USSE offset of the pre-allocated memory region for fragment USSE code.  This
		field is ignored if fragment USSE allocation callbacks are provided.
	*/
	uint32_t fragmentUsseOffset;
} SceGxmShaderPatcherParams;

/** Creates a new shader patcher.

	@param[in]	params			The shader patcher parameters, including host alloc/free callbacks.
								This structure does	not need to persist after this function returns.
	@param[out]	shaderPatcher	A pointer to storage for a shader patcher pointer.  The host
								allocation callback is used to allocate memory for the shader patcher
								internal structures.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the input parameter was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because some allocated memory did not have the required alignment.
	@retval
	SCE_GXM_ERROR_OUT_OF_HOST_MEMORY The operation failed because a host memory allocation failed.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherCreate(
	const SceGxmShaderPatcherParams *params,
	SceGxmShaderPatcher **shaderPatcher);

/** Sets a new user data pointer for this shader patcher.  The user data
	pointer is passed to all memory allocation and deallocation callbacks.

	@param[in,out]	shaderPatcher	The shader patcher to update.
	@param[in]		userData		The new user data pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the input parameter was <c>NULL</c>.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherSetUserData(
	SceGxmShaderPatcher *shaderPatcher,
	void *userData);

/** Gets the user data pointer associated with this shader patcher.

	@param[in]	shaderPatcher	The shader patcher to query.

	@return
	The user data pointer for this shader patcher.

	@ingroup shaderpatcher
*/
void *sceGxmShaderPatcherGetUserData(
	const SceGxmShaderPatcher *shaderPatcher);

/** Destroys the shader patcher.

	All registered programs will be unregistered.  It is an error to destroy the shader
	patcher before all vertex and fragment programs have been released.

	@param[in,out]	shaderPatcher	The shader patcher to be destroyed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_PROGRAM_IN_USE The operation failed because a program is still in use.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherDestroy(
	SceGxmShaderPatcher *shaderPatcher);

/** Registers a compiled program to the shader patcher returning an ID.  The caller
	should take care to only create one ID per compiled program to avoid duplication.

	Final vertex and fragment programs may be created from the ID by calling
	#sceGxmShaderPatcherCreateVertexProgram() or #sceGxmShaderPatcherCreateFragmentProgram().

	The compiled program must persist in memory until all vertex or fragment
	programs have been released and the ID has been unregistered using
	#sceGxmShaderPatcherUnregisterProgram().

	@param[in,out]	shaderPatcher	The shader patcher to register with.
	@param[in]		programHeader	The compiled program header to register.
	@param[out]		programId		Storage for the program ID.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the input parameter was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because some allocated memory did not have the required alignment.
	@retval
	SCE_GXM_ERROR_OUT_OF_HOST_MEMORY The operation failed because a host memory allocation failed.
	@retval
	SCE_GXM_ERROR_OUT_OF_BUFFER_MEMORY  The operation failed because a buffer memory allocation failed.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherRegisterProgram(
	SceGxmShaderPatcher *shaderPatcher,
	const SceGxmProgram *programHeader,
	SceGxmShaderPatcherId *programId);

/** Unregisters a compiled program with the patcher.

	This function may only be called after all vertex or fragment programs that were
	created from the ID have been released.

	@param[in,out]	shaderPatcher	The shader patcher the ID was registered with.
	@param[in]		programId		The ID to unregister.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the input parameter was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_PROGRAM_IN_USE The operation failed because the program is still in use.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherUnregisterProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId);

/** Unregisters a compiled program with the patcher and forces all vertex or
	fragment programs for the ID to be released.

	This function will force all vertex or fragment programs that were created
	from the ID to be destroyed even if their reference counts are still non-zero.
	Callers should ensure that no vertex or fragment programs for this ID are
	currently in use by the GPU.  Once this function has completed successfully,
	vertex or fragment programs for this ID are invalid and should no longer be
	used.

	@param[in,out]	shaderPatcher	The shader patcher the ID was registered with.
	@param[in]		programId		The ID of the program this operation must force to unregister.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the input parameter was <c>NULL</c>.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherForceUnregisterProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId);

/** Gets the program for the given program ID.

	@param[in]	programId		The ID to get the program for.
	@return
	The compiled program for the given ID or <c>NULL</c> if the <c>programId</c> parameter
	was <c>NULL</c>.

	@ingroup shaderpatcher
*/
const SceGxmProgram *sceGxmShaderPatcherGetProgramFromId(
	SceGxmShaderPatcherId programId);

/** Finds or creates a final vertex program.

	The vertex program is constructed by pairing the offline program
	with the vertex attribute types and stream configuration.

	When this program is no longer needed it should be released by calling
	#sceGxmShaderPatcherReleaseVertexProgram(). The caller is responsible for ensuring that
	the GPU is no longer using this program before it is released.

	@param[in,out]	shaderPatcher			A pointer to the shader patcher.
	@param[in]		programId				The ID for a program registered with this shader patcher.
	@param[in]		attributes				A pointer to the vertex attributes. These structures are
											copied by the function and therefore do not need to persist after
											the call.
	@param[in]		attributeCount			The number of attributes.
	@param[in]		streams					A pointer to the vertex streams. These structures are
											copied by the function and therefore do not need to persist after
											the call.
	@param[in]		streamCount				The number of vertex streams.
	@param[out]		vertexProgram			A pointer to storage for a vertex program pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because some allocated memory did not have the required alignment.
	@retval
	SCE_GXM_ERROR_OUT_OF_HOST_MEMORY The operation failed because a host memory allocation failed.
	@retval
	SCE_GXM_ERROR_OUT_OF_VERTEX_USSE_MEMORY The operation failed because a vertex USSE memory allocation failed.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherCreateVertexProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId,
	const SceGxmVertexAttribute *attributes,
	uint32_t attributeCount,
	const SceGxmVertexStream *streams,
	uint32_t streamCount,
	SceGxmVertexProgram **vertexProgram);

/** Finds or creates a final fragment program.

	The fragment program is constructed by appending the shader compiler output
	with output register conversion and blending code.

	When this program is no longer needed, it should be released by calling
	#sceGxmShaderPatcherReleaseFragmentProgram().  The caller is responsible for ensuring that
	the GPU is no longer using this program before it is released.

	Blending/masking is only supported for the output register formats
	#SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4 or #SCE_GXM_OUTPUT_REGISTER_FORMAT_HALF4.
	If the <c><i>blendInfo</i></c> structure has an active blend or non-trivial mask when using
	unsupported output register format, the error code #SCE_GXM_ERROR_UNSUPPORTED
	will be returned.

	The parameter <c><i>vertexProgram</i></c> is only required to remap texture coordinates.  If all
	vertex programs that will be used with this fragment program write a contiguous range of
	texture coordinates starting at <c>TEXCOORD0</c> (or do not write texture coordinates), then the
	<c><i>vertexProgram</i></c> parameter may be <c>NULL</c>.  Any vertex program that uses texture coordinates
	that either start at a non-zero binding (such as <c>TEXCOORD1</c>) or form a non-contiguous range
	must be explicitly linked by passing the program as the <c><i>vertexProgram</i></c> parameter.

	@param[in,out]	shaderPatcher			A pointer to the shader patcher.
	@param[in]		programId				The ID for a program registered with this shader patcher.
	@param[in]		outputFormat			The format for the fragment program <c>COLOR0</c> output.
	@param[in]		multisampleMode			The multisample mode.
	@param[in]		blendInfo				A pointer to the blend info structure or <c>NULL</c>. This
											structure is copied by the function and therefore does not need to
											persist after the call.
	@param[in]		vertexProgram			A pointer to the vertex program or <c>NULL</c>. This
											structure does not need to persist after the call.
	@param[out]		fragmentProgram			A pointer to storage for a fragment program pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED Blending or masking is enabled for an unsupported
	output register format.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because some allocated memory did not have the required alignment.
	@retval
	SCE_GXM_ERROR_OUT_OF_HOST_MEMORY The operation failed because a host memory allocation failed.
	@retval
	SCE_GXM_ERROR_OUT_OF_FRAGMENT_USSE_MEMORY The operation failed because a fragment USSE memory allocation failed.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherCreateFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId,
	SceGxmOutputRegisterFormat outputFormat,
	SceGxmMultisampleMode multisampleMode,
	const SceGxmBlendInfo *blendInfo,
	const SceGxmProgram *vertexProgram,
	SceGxmFragmentProgram **fragmentProgram);

/** Increases the reference count of the vertex program.  The vertex program must have
	been created by the shader patcher.

	@param[in,out]	shaderPatcher		A pointer to the shader patcher.
	@param[in,out]	vertexProgram		A pointer to the vertex program whose reference count should be increased.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the program was not in the cache.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherAddRefVertexProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmVertexProgram *vertexProgram);

/** Increases the reference count of the fragment program.  The fragment program must have
	been created by the shader patcher.

	@param[in,out]	shaderPatcher		A pointer to the shader patcher.
	@param[in,out]	fragmentProgram		A pointer to the fragment program whose reference count should be increased.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the program was not in the cache.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherAddRefFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmFragmentProgram *fragmentProgram);

/** Decreases the reference count of the vertex program. The vertex program must have
	been created by the shader patcher. If the reference count of the program hits zero
	the program is destroyed. Therefore callers should ensure that the GPU has finished
	using this program before calling this function.

	@param[in,out]	shaderPatcher		A pointer to the shader patcher.
	@param[in,out]	vertexProgram		A pointer to the vertex program whose reference count is to be decremented.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the program was not in the cache.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherReleaseVertexProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmVertexProgram *vertexProgram);

/** Decreases the reference count of the fragment program.  The fragment program must have
	been created by the shader patcher. If the reference count of the program hits zero
	the program is destroyed. Therefore callers should ensure that the GPU has finished
	using this program before calling this function.

	@param[in,out]	shaderPatcher		A pointer to the shader patcher.
	@param[in,out]	fragmentProgram		A pointer to the fragment program whose reference count is to be decremented.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the program was not in the cache.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherReleaseFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmFragmentProgram *fragmentProgram);

/** Retrieves the reference count of the vertex program.  The vertex program must have
	been created by the shader patcher.

	@param[in]	shaderPatcher		A pointer to the shader patcher.
	@param[in]	vertexProgram		A pointer to the vertex program whose reference count should be retrieved.
	@param[out]	refCount			The storage for the reference count.
	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the program was not in the cache.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherGetVertexProgramRefCount(
	const SceGxmShaderPatcher *shaderPatcher,
	const SceGxmVertexProgram *vertexProgram,
	uint32_t *refCount);

/** Retrieves the reference count of the fragment program.  The fragment program must have
	been created by the shader patcher.

	@param[in]	shaderPatcher		A pointer to the shader patcher.
	@param[in]	fragmentProgram		A pointer to the fragment program whose reference count should be retrieved.
	@param[out]	refCount			The storage for the reference count.
	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the program was not in the cache.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherGetFragmentProgramRefCount(
	const SceGxmShaderPatcher *shaderPatcher,
	const SceGxmFragmentProgram *fragmentProgram,
	uint32_t *refCount);

/** Gets the total amount of host memory currently allocated by the shader patcher.

	@param[in]	shaderPatcher		A pointer to the shader patcher.
	@return
	The amount of host memory in bytes that is currently allocated.

	@ingroup shaderpatcher
*/
uint32_t sceGxmShaderPatcherGetHostMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);

/** Gets the total amount of GPU buffer memory currently allocated by the shader patcher.

	@param[in]	shaderPatcher		A pointer to the shader patcher.
	@return
	The amount of buffer memory in bytes that is currently allocated.

	@ingroup shaderpatcher
*/
uint32_t sceGxmShaderPatcherGetBufferMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);

/** Gets the total amount of vertex USSE memory currently allocated by the shader patcher.

	@param[in]	shaderPatcher		A pointer to the shader patcher.
	@return
	The amount of vertex USSE memory in bytes that is currently allocated.

	@ingroup shaderpatcher
*/
uint32_t sceGxmShaderPatcherGetVertexUsseMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);

/** Gets the total amount of fragment USSE memory currently allocated by the shader patcher.

	@param[in]	shaderPatcher		A pointer to the shader patcher.
	@return
	The amount of fragment USSE memory in bytes that is currently allocated.

	@ingroup shaderpatcher
*/
uint32_t sceGxmShaderPatcherGetFragmentUsseMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);

/** Creates a mask update fragment program.

	If the shader patcher has already created a mask update fragment program, then
	the existing program is used after its reference count has been incremented.

	When this program is no longer needed, it should be released by calling
	#sceGxmShaderPatcherReleaseFragmentProgram().  The caller is responsible for
	ensuring that the GPU is no longer using this program before it is released.

	The purpose of a mask update fragment is to clear or set the mask bit that is
	part of a depth/stencil surface of format #SCE_GXM_DEPTH_STENCIL_FORMAT_DF32M
	or #SCE_GXM_DEPTH_STENCIL_FORMAT_DF32M_S8.  A mask update fragment program has
	a pass type of #SCE_GXM_PASS_TYPE_MASK_UPDATE, does not require any shader
	resources such as uniform buffers or textures, and will automatically disable
	the fragment program while it is set on the libgxm context.

	When a mask update fragment program is used with a draw call, the hardware
	behaviour changes as follows:

	<ul>
		<li>The depth test is bypassed. All pixels or samples covered by the
		geometry are considered to pass the depth test.
		<li>Depth writes do not occur.
		<li>The stencil test is bypassed. All pixels or samples covered by
		the geometry are considered to pass the stencil test.
		<li>Stencil operations do not occur.
		<li>The meaning of the current stencil function is changed.  If the
		current stencil function has 0 in bit 25, such as
		#SCE_GXM_STENCIL_FUNC_NEVER, the mask bit is cleared for all pixels or
		samples covered by the geometry.  If the current stencil function has 1
		in bit 25, such as #SCE_GXM_STENCIL_FUNC_ALWAYS, the mask bit is set
		for all pixels or samples covered by the geometry.
	</ul>

	The mask bit can be used to implement a 2D viewport or scissoring.
	This is achieved by drawing	2D geometry to clear and set the mask bit
	to the desired shape.

	@param[in,out]	shaderPatcher			A pointer to the shader patcher.
	@param[out]		fragmentProgram			A pointer to the storage for a fragment program pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because an allocation did not have the required alignment.
	@retval
	SCE_GXM_ERROR_OUT_OF_HOST_MEMORY The operation failed because a host allocation failed.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherCreateMaskUpdateFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmFragmentProgram **fragmentProgram);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_SHADER_PATCHER_H_ */
