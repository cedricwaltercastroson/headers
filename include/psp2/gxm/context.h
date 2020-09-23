#ifndef _DOLCESDK_PSP2_GXM_CONTEXT_H_
#define _DOLCESDK_PSP2_GXM_CONTEXT_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/constants.h>
#include <psp2/gxm/uniforms.h>
#include <psp2/gxm/precomputation.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The opaque data structure for a rendering context.

	The rendering context may be an immediate context or a deferred context.
	Many libgxm functions, such as those involved with setting state and drawing,
	are supported on both immediate and deferred contexts, but some functions,
	such as those involved with scenes or command lists, require a context of
	a specific type.  These functions will be clearly marked in their reference
	documentation.

	Call #sceGxmGetContextType() to determine whether a context is a deferred
	or an immediate context.

	@ingroup render
*/
typedef struct SceGxmContext SceGxmContext;

/** The type of a rendering context.

	@ingroup render
*/
typedef enum SceGxmContextType {
	SCE_GXM_CONTEXT_TYPE_IMMEDIATE,	///< The immediate context, which will have been created with sceGxmCreateContext().
	SCE_GXM_CONTEXT_TYPE_DEFERRED	///< A deferred context, which will have been created with sceGxmCreateDeferredContext().
} SceGxmContextType;

/** The minimum required size in bytes of the host memory in #SceGxmContextParams.

	@ingroup render
*/
#define SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE			2048

/** A default size for the VDM ring buffer in #SceGxmContextParams.

	@ingroup render
*/
#define SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE			(128*1024)

/** A default size for the vertex ring buffer in #SceGxmContextParams.

	@ingroup render
*/
#define SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE			(2*1024*1024)

/** A default size for the fragment ring buffer in #SceGxmContextParams.

	@ingroup render
*/
#define SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE		(512*1024)

/** A default size for the fragment USSE ring buffer in #SceGxmContextParams.

	@ingroup render
*/
#define SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE	(16*1024)

/** The minimum size of a deferred context buffer.

	@ingroup render
*/
#define SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE	1024

/** The parameters for creating the immediate context.

	@ingroup render
*/
typedef struct SceGxmContextParams {
	/** Host memory for the #SceGxmContext structure.  This should be standard cached
		CPU	memory, such as that returned by libc malloc. This should be aligned to 4 bytes.
	*/
	void *hostMem;

	/** The size of the host memory pointed to by <c><i>hostMem</i></c>.  The minimum size
		this memory can be is defined by #SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE. This should be
		aligned to 4 bytes.
	*/
	uint32_t hostMemSize;

	/** Memory for the VDM ring buffer.  This should be mapped to the GPU with read
		access.  A sensible default size is #SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE. This should be
		aligned to 4 bytes.
	*/
	void *vdmRingBufferMem;

	/** The size in bytes of the VDM ring buffer memory pointed to by <c><i>vdmRingBufferMem</i></c>.
		This should be aligned to 4 bytes.
	*/
	uint32_t vdmRingBufferMemSize;

	/** The memory for the vertex ring buffer.  This should be mapped to the GPU with read
		access.  A sensible default size is #SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE. This should be
		aligned to 4 bytes.
	*/
	void *vertexRingBufferMem;

	/** The size in bytes of the vertex ring buffer memory pointed to by <c><i>vertexRingBufferMem</i></c>.
		This should be aligned to 4 bytes.
	*/
	uint32_t vertexRingBufferMemSize;

	/** The memory for the fragment ring buffer.  This should be mapped to the GPU with read
		access.  A sensible default size is #SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE. This should be
		aligned to 4 bytes.
	*/
	void *fragmentRingBufferMem;

	/** The size in bytes of the fragment ring buffer memory pointed to by <c><i>fragmentRingBufferMem</i></c>.
		This should be aligned to 4 bytes.
	*/
	uint32_t fragmentRingBufferMemSize;

	/** The memory for the fragment USSE ring buffer.  This should be mapped as fragment USSE code.
		A sensible default size is #SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE. This should be
		aligned to 4 bytes.
	*/
	void *fragmentUsseRingBufferMem;

	/** The size in bytes of the fragment USSE ring buffer memory pointed to by <c><i>fragmentUsseRingBufferMem</i></c>.
		This should be aligned to 4 bytes.
	*/
	uint32_t fragmentUsseRingBufferMemSize;

	/** The USSE offset of the start of the fragment USSE ring buffer memory pointed to by
		<c><i>fragmentUsseRingBufferMem</i></c>.
	*/
	uint32_t fragmentUsseRingBufferOffset;
} SceGxmContextParams;

/** A callback function for handling deferred context memory buffers.

	The <c><i>userData</i></c> parameter provides the user data pointer from the
	initialization parameters used to create the deferred context.

	An implementation of this callback must return GPU-mapped memory of at least
	<c><i>minSize</i></c> bytes, and it must write the memory’s actual size to the
	storage pointed	to by the <c><i>size</i></c> parameter.  The value of
	<c><i>minSize</i></c> will always be at least
	#SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE bytes in size. If larger blocks
	of memory are provided by the application, then overheads due to repeated invocation
	of the callback can be reduced. This is especially relevant when using the debug
	version of libgxm as this performs exhaustive validation of the memory address
	returned from this callback, which can degrade runtime performance.

	If no memory is available, then the callback may return <c>NULL</c>.  If this occurs
	during #sceGxmBeginCommandList() then creation of the command list will fail.
	If this occurs within a command list, then that reservation or draw call will
	fail, but the command list will remain in a well-defined state.  The
	implementation of #sceGxmEndCommandList() will always succeed if a command
	list is in progress on that deferred context.  In this way, command lists that
	are successfully begun can always be ended and later executed on an
	immediate context, but may contain fewer than expected draw calls if a
	callback function failed to provide additional memory while the command list
	was being constructed.

	It is not valid to call any function on the deferred context in the
	implementation of a callback function triggered from that deferred context,
	as these functions are not designed to be re-entrant.

	@param[in]	userData		The user data pointer from the initialization parameters
								that were used to create the deferred context.
	@param[in]	minSize			The minimum size the memory created by this callback can be.
	@param[out]	size			This should receive the actual size of the memory created by the callback.

	@return						The GPU-mapped memory created by the callback. This should be set
								to <c>NULL</c> if no memory was created.

	@ingroup render
 */
typedef void* (*SceGxmDeferredContextCallback)(void* userData, uint32_t minSize, uint32_t *size);

/** The parameters for creating a deferred context.

	@ingroup render
*/
typedef struct SceGxmDeferredContextParams {
	/** Host memory for the #SceGxmContext structure.  This should be standard cached
		CPU	memory, such as that returned by libc malloc. This should be aligned to 4 bytes.
	*/
	void *hostMem;

	/** The size of the host memory pointed to by <c><i>hostMem</i></c>.  This size must be
		at least #SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE. This should be aligned to 4 bytes.
	*/
	uint32_t hostMemSize;

	/** The callback function called by a deferred context when memory is required for VDM
        stream entries.
 	*/
	SceGxmDeferredContextCallback vdmCallback;

 	/** The callback function called by a deferred context when memory is required for supporting
		vertex data structures.
 	*/
	SceGxmDeferredContextCallback vertexCallback;

	/** The callback function called by a deferred context when memory is required for supporting
		fragment data structures.
 	*/
	SceGxmDeferredContextCallback fragmentCallback;

	/** Optional user data pointer which is passed to vdmCallback, vertexCallback and fragmentCallback functions.
 	 */
	void *userData;

	/** Optional memory for the initial VDM buffer. This should be mapped to the GPU with read
		access. If <c>NULL</c> is specified then memory must be provided through the callback
		pointed to by <c><i>vdmCallback</i></c>. This should be aligned to 4 bytes.
	*/
	void *vdmBufferMem;

	/** The size in bytes of the VDM buffer memory pointed to by <c><i>vdmBufferMem</i></c>
		or 0 if <c><i>vdmBufferMem</i></c> is <c>NULL</c>.  If non-zero, the size must be at least
		#SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE. This should be aligned to 4 bytes.
	*/
	uint32_t vdmBufferMemSize;

	/** Optional memory for the initial vertex buffer. This should be mapped to the GPU with read
		access. If <c>NULL</c> is specified then memory must be provided through the callback
		pointed to by <c><i>vertexCallback</i></c>. This should be aligned to 4 bytes.
	*/
	void *vertexBufferMem;

	/** The size in bytes of the vertex buffer memory pointed to by <c><i>vertexBufferMem</i></c>
		or 0 if <c><i>vertexBufferMem</i></c> is <c>NULL</c>.  If non-zero, the size must be at least
		#SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE. This should be aligned to 4 bytes.
	 */
	uint32_t vertexBufferMemSize;

	/** Optional memory for the initial fragment buffer. This should be mapped to the GPU with read
		access. If <c>NULL</c> is specified then memory must be provided through the callback pointed
		to by <c><i>fragmentCallback</i></c>. This should be aligned to 4 bytes.
	*/
	void *fragmentBufferMem;

	/** The size in bytes of the fragment buffer memory pointed to by <c><i>fragmentBufferMem</i></c>
		or 0 if <c><i>fragmentBufferMem</i></c> is <c>NULL</c>.  If non-zero, the size must be at least
		#SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE. This should be aligned to 4 bytes.
	*/
	uint32_t fragmentBufferMemSize;

} SceGxmDeferredContextParams;

/** Creates the immediate context.

	The rendering context uses the memory pointed to by the <c><i>hostMem</i></c> member of
	#SceGxmContextParams for state tracking between draw calls and between GPU jobs.
	The remaining memory regions described by #SceGxmContextParams are used for
	dynamically generated GPU data structures.

	After the rendering context has been created, the following states will be set to
	<c>NULL</c>:

	<ul>
		<li>Vertex program
		<li>Fragment program
		<li>Vertex streams
		<li>Vertex and fragment uniform buffers
		<li>Vertex and fragment textures
		<li>Precomputed vertex and fragment state
		<li>Visibility buffer
	</ul>

	The following default states are set during creation:

	@code
	sceGxmSetYuvProfile(context, 0, SCE_GXM_YUV_PROFILE_BT601_STANDARD);
	sceGxmSetYuvProfile(context, 1, SCE_GXM_YUV_PROFILE_BT709_STANDARD);
	sceGxmSetFrontDepthFunc(context, SCE_GXM_DEPTH_FUNC_LESS_EQUAL);
	sceGxmSetBackDepthFunc(context, SCE_GXM_DEPTH_FUNC_LESS_EQUAL);
	sceGxmSetFrontFragmentProgramEnable(context, SCE_GXM_FRAGMENT_PROGRAM_ENABLED);
	sceGxmSetBackFragmentProgramEnable(context, SCE_GXM_FRAGMENT_PROGRAM_ENABLED);
	sceGxmSetFrontDepthWriteEnable(context, SCE_GXM_DEPTH_WRITE_ENABLED);
	sceGxmSetBackDepthWriteEnable(context, SCE_GXM_DEPTH_WRITE_ENABLED);
	sceGxmSetFrontLineFillLastPixelEnable(context, SCE_GXM_LINE_FILL_LAST_PIXEL_DISABLED);
	sceGxmSetBackLineFillLastPixelEnable(context, SCE_GXM_LINE_FILL_LAST_PIXEL_DISABLED);
	sceGxmSetFrontStencilRef(context, 0);
	sceGxmSetBackStencilRef(context, 0);
	sceGxmSetFrontPointLineWidth(context, 1);
	sceGxmSetBackPointLineWidth(context, 1);
	sceGxmSetFrontPolygonMode(context, SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);
	sceGxmSetBackPolygonMode(context, SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);
	sceGxmSetFrontStencilFunc(
		context,
		SCE_GXM_STENCIL_FUNC_ALWAYS,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		0,
		0);
	sceGxmSetBackStencilFunc(
		context,
		SCE_GXM_STENCIL_FUNC_ALWAYS,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		0,
		0);
	sceGxmSetFrontDepthBias(context, 0, 0);
	sceGxmSetBackDepthBias(context, 0, 0);
	sceGxmSetTwoSidedEnable(context, SCE_GXM_TWO_SIDED_DISABLED);
	sceGxmSetViewport(context, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	sceGxmSetWClampValue(context, 0.00001f);
	sceGxmSetWClampEnable(context, SCE_GXM_WCLAMP_MODE_ENABLED);
	sceGxmSetRegionClip(context, SCE_GXM_REGION_CLIP_NONE, 0, 0, 0, 0);
	sceGxmSetCullMode(context, SCE_GXM_CULL_NONE);
	sceGxmSetViewportEnable(context, SCE_GXM_VIEWPORT_ENABLED);
	sceGxmSetWBufferEnable(context, SCE_GXM_WBUFFER_DISABLED);
	sceGxmSetFrontVisibilityTestIndex(context, 0);
	sceGxmSetBackVisibilityTestIndex(context, 0);
	sceGxmSetFrontVisibilityTestOp(context, SCE_GXM_VISIBILITY_TEST_OP_INCREMENT);
	sceGxmSetBackVisibilityTestOp(context, SCE_GXM_VISIBILITY_TEST_OP_INCREMENT);
	sceGxmSetFrontVisibilityTestEnable(context, SCE_GXM_VISIBILITY_TEST_DISABLED);
	sceGxmSetBackVisibilityTestEnable(context, SCE_GXM_VISIBILITY_TEST_DISABLED);
	@endcode

	Note that the region clip and viewport are reset during #sceGxmBeginScene().

	When the rendering context is no longer needed, it should be destroyed,
	by calling #sceGxmDestroyContext(), after the GPU has finished executing all jobs
	issued from the context.

	@param[in]	params			A pointer to the initialization parameters.  This structure does
								not need to persist after the call.
	@param[out]	immediateContext	A pointer to storage for an #SceGxmContext pointer.

	@retval
	SCE_OK The operation was successful and the rendering context is now populated.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.

	@ingroup render
*/
SceGxmErrorCode sceGxmCreateContext(
	const SceGxmContextParams *params,
	SceGxmContext **immediateContext);

/** Destroys the given immediate context.

	This function may only be called for contexts created with #sceGxmCreateContext().
	Contexts created with #sceGxmCreateDeferredContext() should be destroyed by calling
	#sceGxmDestroyDeferredContext().

	@param[in,out]	immediateContext	A pointer to an immediate context.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the context was not an immediate context.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The pointer to the context was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmDestroyContext(SceGxmContext *immediateContext);

/** Creates a deferred context.

	This context will use the memory pointed to by the <c><i>hostMem</i></c> member of
	#SceGxmDeferredContextParams for state tracking between draw calls.
	As the context is used to create a command list, the callbacks and optional initial
	remaining memory regions described by #SceGxmDeferredContextParams are used for dynamically
	generated GPU data structures.

	Note that unlike an immediate context, a deferred context only tracks state
	for draw calls and not GPU jobs.  State used at the job level, such as YUV profiles or
	the visibility buffer base address, may only be set on an immediate context.

	After the context has been created, the following states will be set to
	<c>NULL</c>:

	<ul>
		<li>Vertex program
		<li>Fragment program
		<li>Vertex streams
		<li>Vertex and fragment uniform buffers
		<li>Vertex and fragment textures
		<li>Precomputed vertex and fragment state
	</ul>

	The following default states are set during creation:

	@code
	sceGxmSetFrontDepthFunc(context, SCE_GXM_DEPTH_FUNC_LESS_EQUAL);
	sceGxmSetBackDepthFunc(context, SCE_GXM_DEPTH_FUNC_LESS_EQUAL);
	sceGxmSetFrontFragmentProgramEnable(context, SCE_GXM_FRAGMENT_PROGRAM_ENABLED);
	sceGxmSetBackFragmentProgramEnable(context, SCE_GXM_FRAGMENT_PROGRAM_ENABLED);
	sceGxmSetFrontDepthWriteEnable(context, SCE_GXM_DEPTH_WRITE_ENABLED);
	sceGxmSetBackDepthWriteEnable(context, SCE_GXM_DEPTH_WRITE_ENABLED);
	sceGxmSetFrontLineFillLastPixelEnable(context, SCE_GXM_LINE_FILL_LAST_PIXEL_DISABLED);
	sceGxmSetBackLineFillLastPixelEnable(context, SCE_GXM_LINE_FILL_LAST_PIXEL_DISABLED);
	sceGxmSetFrontStencilRef(context, 0);
	sceGxmSetBackStencilRef(context, 0);
	sceGxmSetFrontPointLineWidth(context, 1);
	sceGxmSetBackPointLineWidth(context, 1);
	sceGxmSetFrontPolygonMode(context, SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);
	sceGxmSetBackPolygonMode(context, SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);
	sceGxmSetFrontStencilFunc(
		context,
		SCE_GXM_STENCIL_FUNC_ALWAYS,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		0,
		0);
	sceGxmSetBackStencilFunc(
		context,
		SCE_GXM_STENCIL_FUNC_ALWAYS,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		SCE_GXM_STENCIL_OP_KEEP,
		0,
		0);
	sceGxmSetFrontDepthBias(context, 0, 0);
	sceGxmSetBackDepthBias(context, 0, 0);
	sceGxmSetTwoSidedEnable(context, SCE_GXM_TWO_SIDED_DISABLED);
	sceGxmSetViewport(context, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	sceGxmSetWClampValue(context, 0.00001f);
	sceGxmSetWClampEnable(context, SCE_GXM_WCLAMP_MODE_ENABLED);
	sceGxmSetRegionClip(context, SCE_GXM_REGION_CLIP_NONE, 0, 0, 0, 0);
	sceGxmSetCullMode(context, SCE_GXM_CULL_NONE);
	sceGxmSetViewportEnable(context, SCE_GXM_VIEWPORT_ENABLED);
	sceGxmSetWBufferEnable(context, SCE_GXM_WBUFFER_DISABLED);
	sceGxmSetFrontVisibilityTestIndex(context, 0);
	sceGxmSetBackVisibilityTestIndex(context, 0);
	sceGxmSetFrontVisibilityTestOp(context, SCE_GXM_VISIBILITY_TEST_OP_INCREMENT);
	sceGxmSetBackVisibilityTestOp(context, SCE_GXM_VISIBILITY_TEST_OP_INCREMENT);
	sceGxmSetFrontVisibilityTestEnable(context, SCE_GXM_VISIBILITY_TEST_DISABLED);
	sceGxmSetBackVisibilityTestEnable(context, SCE_GXM_VISIBILITY_TEST_DISABLED);
	@endcode

	The state set on a deferred context is self-contained and independent from
	all other contexts.  Because of this, before adding draw calls to a command list,
	it is necessary to manually set at least the region clip and viewport by calling,
	for example, #sceGxmSetDefaultRegionClipAndViewport().  The debug version of libgxm will
	warn when draw calls are performed on a deferred context that has not yet had region
	clip or viewport set up.

	When the context is no longer needed, it should be destroyed by calling
	#sceGxmDestroyDeferredContext().  A deferred context does not need to persist in
	order to use command lists created by that particular deferred context, so it may be safely
	destroyed once all the command lists have been created.

	@param[in]	params			A pointer to the initialization parameters.  This structure does
								not need to persist after the call.
	@param[out]	deferredContext	A pointer to storage for an #SceGxmContext pointer.

	@retval
	SCE_OK The operation was successful and <c><i>deferredContext</i></c> is now populated.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.

	@ingroup render
 */
SceGxmErrorCode sceGxmCreateDeferredContext(
	SceGxmDeferredContextParams *params,
	SceGxmContext **deferredContext);

/** Destroys a deferred context.

	This function may only be called for contexts created with #sceGxmCreateDeferredContext().
	Immediate contexts created with #sceGxmCreateContext() should be destroyed by calling
	#sceGxmDestroyContext().

	@param[in,out]	deferredContext		A pointer to a #SceGxmContext structure.

	@retval
	SCE_OK The operation was successful and <c><i>deferredContext</i></c> is now destroyed.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the context was not a deferred context.

	@ingroup render
 */
SceGxmErrorCode sceGxmDestroyDeferredContext(
	SceGxmContext *deferredContext);

/** Gets the type of a context.

	@param[in]	context		A pointer to a context.
	@param[out]	type		A pointer to storage for a #SceGxmContextType value.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.

	@ingroup render
*/
SceGxmErrorCode sceGxmGetContextType(
	const SceGxmContext *context,
	SceGxmContextType *type);

/** Sets a vertex program for future draw calls.

	This function may be called at any time. The vertex program set will persist indefinitely.

	Vertex program uniforms do not have any default values when the program has been set.  Unless
	the caller will be using a precomputed vertex state with this program, the default buffer should
	be reserved using #sceGxmReserveVertexDefaultUniformBuffer() and filled with data before drawing.
	Once reserved, the default buffer remains valid until a new vertex program is set or the scene
	is ended.

	The vertex program pointed to by <c><i>vertexProgram</i></c> must persist in memory after this call
	until a different program is set by a future call.  The context allows a <c>NULL</c> program to be set
	for the purpose of allowing all vertex programs to be destroyed. Note that the context will return an
	error if the user attempts a draw call with a <c>NULL</c> vertex program.

	It is still necessary to set the vertex program when using a precomputed vertex state or
	precomputed draw calls (even if you are using both). This is because the vertex program also defines
	state, which must be flushed to the GPU.

	@param[in,out]	context				A pointer to a context.
	@param[in]		vertexProgram		A pointer to the vertex program to set or <c>NULL</c>. The
										program must not be released until another program or <c>NULL</c>
										is set on the #SceGxmContext, and until vertex processing for the
										current scene has completed.

	@ingroup render
*/
void sceGxmSetVertexProgram(
	SceGxmContext *context,
	const SceGxmVertexProgram *vertexProgram);

/** Sets a fragment program for future draw calls.

	This function may be called at any time. The fragment program set will persist indefinitely.

	Fragment program uniforms do not have any default values when the program has been set. Unless
	the caller will be using a precomputed fragment state with this program the default buffer should
	be reserved using #sceGxmReserveFragmentDefaultUniformBuffer() and filled with data before drawing.
	Once reserved, the default buffer remains valid until a new fragment program is set or the scene
	has ended.

	The fragment program pointed to by <c><i>fragmentProgram</i></c> must persist in memory after this call
	until a different program is set by a future call.  The context allows a <c>NULL</c> program to be set
	for the purpose of allowing all fragment programs to be destroyed. Note that the context will return an
	error if the user attempts a draw call with a <c>NULL</c> fragment program.

	It is still necessary to set the fragment program when using a precomputed fragment state. This is because
	the fragment program also defines state, which must be flushed to the GPU.

	@param[in,out]	context				A pointer to the rendering context.
	@param[in]		fragmentProgram		A pointer to the fragment program to set or <c>NULL</c>. The
										program must not be released until another program or <c>NULL</c>
										is set on the #SceGxmContext, and until fragment processing for the
										current scene has completed.

	@ingroup render
*/
void sceGxmSetFragmentProgram(
	SceGxmContext *context,
	const SceGxmFragmentProgram *fragmentProgram);

/** Allocates a new default uniform buffer for the current vertex program from the vertex
	data ring buffer. The previous vertex default uniform buffer will be recycled for future
	reservations as the GPU consumes the ring buffers during normal rendering.  Reserving a
	vertex default uniform buffer replaces any previous vertex default uniform buffer set using
	#sceGxmSetVertexDefaultUniformBuffer().

	This function may only be called inside a scene or command list.
	When using the immediate context, calling this function outside of a scene will
	result in the #SCE_GXM_ERROR_NOT_WITHIN_SCENE error code being returned.  When using a
	deferred context, calling this function outside of a command list will result in the
	#SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST error code being returned.

	This function can only be called if the current vertex program is non-<c>NULL</c>. Calling
	this function when the current vertex program is <c>NULL</c> will return the
	#SCE_GXM_ERROR_NULL_PROGRAM error code and no uniform buffer will be reserved.

	If the current vertex program has a non-zero size default uniform buffer,
	this will be reserved from the vertex data ring buffer and the base address
	will be written to the <c><i>uniformBuffer</i></c> parameter.  The contents of
	this buffer can then either be written directly or written by using utility
	functions such as #sceGxmSetUniformDataF().  If the current vertex program
	has a zero size default uniform buffer, then nothing will be reserved and
	<c>NULL</c> will be written to the <c><i>uniformBuffer</i></c> parameter.  In both cases,
	this function will return <c>SCE_OK</c>.

	It is not necessary to call this function when using precomputed vertex state. In this case the
	default uniform buffer is set on the #SceGxmPrecomputedVertexState object by calling
	#sceGxmPrecomputedVertexStateSetDefaultUniformBuffer().

	@param[in,out]	context				A pointer to the rendering context.
	@param[out]		uniformBuffer		A pointer to storage for a uniform buffer pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NULL_PROGRAM The operation failed because no vertex program was set.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to a buffer callback function
	failing to provide sufficient memory for the reservation.  This error will only
	be returned from a deferred context. Immediate context reservations always succeed,
	but they potentially have high latency if scenes are split to recycle memory.

	@ingroup render
*/
SceGxmErrorCode sceGxmReserveVertexDefaultUniformBuffer(
	SceGxmContext *context,
	void **uniformBuffer);

/** Sets a new vertex default uniform buffer for future draw calls.

	This function may be called at any time and replaces any previous reservation made using
	#sceGxmReserveVertexDefaultUniformBuffer().  The vertex default uniform buffer persists until
	either a new buffer is set, or a new buffer is reserved using #sceGxmReserveVertexDefaultUniformBuffer().

	It is not necessary to call this function when using precomputed vertex state. In this case the
	default uniform buffer is set on the #SceGxmPrecomputedVertexState object by calling
	#sceGxmPrecomputedVertexStateSetDefaultUniformBuffer().

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		bufferData		A pointer to the uniform buffer data. The GPU data pointed to
									must persist until vertex processing for the current scene has
									completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetVertexDefaultUniformBuffer(
	SceGxmContext *context,
	const void *bufferData);

/** Allocates a new default uniform buffer for the current fragment program from the fragment
	data ring buffer. The previous fragment default uniform buffer will be recycled for future
	reservations as the GPU consumes the ring buffers during normal rendering.  Reserving a
	fragment default uniform buffer replaces any previous fragment default uniform buffer set using
	#sceGxmSetFragmentDefaultUniformBuffer().

	This function may only be called inside a scene or command list.
	When using the immediate context, calling this function outside of a scene will
	result in the #SCE_GXM_ERROR_NOT_WITHIN_SCENE error code being returned.  When using a deferred
	context, calling this function outside of a command list will result in the
	#SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST error code being returned.

	This function can only be called if the current fragment program is non-<c>NULL</c>. Calling
	this function when the current fragment program is <c>NULL</c> will return the
	#SCE_GXM_ERROR_NULL_PROGRAM error code and no uniform buffer will be reserved.

	If the current fragment program has a non-zero size default uniform buffer,
	this will be reserved from the fragment data ring buffer and the base
	address will be written to the <c><i>uniformBuffer</i></c> parameter.  The contents
	of this buffer can then either be written directly or written by using
	utility functions such as #sceGxmSetUniformDataF().  If the current fragment
	program has a zero size default uniform buffer, then nothing will be
	reserved and <c>NULL</c> will be written to the <c><i>uniformBuffer</i></c> parameter. In
	both cases, this function will return <c>SCE_OK</c>.

	It is not necessary to call this function when using precomputed fragment state. In this case the
	default buffer is set on the #SceGxmPrecomputedFragmentState object by calling
	#sceGxmPrecomputedFragmentStateSetDefaultUniformBuffer().

	@param[in,out]	context				A pointer to the rendering context.
	@param[out]		uniformBuffer		A pointer to storage for a uniform buffer pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NULL_PROGRAM The operation failed because no fragment program was set.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to a buffer callback function
	failing to provide sufficient memory for the reservation.  This error will only
	be returned from a deferred context. Immediate context reservations always succeed,
	but they potentially have high latency if scenes are split to recycle memory.

	@ingroup render
*/
SceGxmErrorCode sceGxmReserveFragmentDefaultUniformBuffer(
	SceGxmContext *context,
	void **uniformBuffer);

/** Sets a new default uniform buffer for future draw calls.

	This function may be called at any time and replaces any previous reservation made using
	#sceGxmReserveFragmentDefaultUniformBuffer().  The fragment default uniform buffer persists until
	either a new buffer is set, or a new buffer is reserved using #sceGxmReserveFragmentDefaultUniformBuffer().

	It is not necessary to call this function when using precomputed fragment state. In this case the
	default uniform buffer is set on the #SceGxmPrecomputedFragmentState object by calling
	#sceGxmPrecomputedFragmentStateSetDefaultUniformBuffer().

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		bufferData		A pointer to the uniform buffer data. The GPU data pointed to
									must persist until fragment processing for the current scene has
									completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetFragmentDefaultUniformBuffer(
	SceGxmContext *context,
	const void *bufferData);

/** Sets a vertex stream address for future draw calls.

	This function may be called at any time. The stream address persists indefinitely.

	It is not necessary to call this function when using precomputed draw calls. In this case stream
	addresses can be patched directly on the #SceGxmPrecomputedDraw object by
	calling #sceGxmPrecomputedDrawSetAllVertexStreams().

	The <c><i>streamIndex</i></c> parameter must be between 0 and (#SCE_GXM_MAX_VERTEX_STREAMS - 1).

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		streamIndex		The index of the vertex stream.
	@param[in]		streamData		A pointer to the vertex stream data. The GPU data pointed to
									must persist until vertex processing for the current scene has
									completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The stream index was not valid.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetVertexStream(
	SceGxmContext *context,
	uint32_t streamIndex,
	const void *streamData);

/**	Sets a vertex program texture for future draw calls.

	This function may be called at any time. The vertex texture persists indefinitely.

	It is not necessary to call this function when using a precomputed vertex state. In this case
	textures can be patched directly on the #SceGxmPrecomputedVertexState object
	by calling #sceGxmPrecomputedVertexStateSetAllTextures().

	The <c><i>textureIndex</i></c> parameter must be between 0 and (#SCE_GXM_MAX_TEXTURE_UNITS - 1).

	The texture control words pointed to by <c><i>texture</i></c> are copied by value during this call
	and do not need to persist in memory afterwards. Note that the texture data must remain
	valid in memory until the GPU has finished vertex processing for the current scene.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		textureIndex	The <c>TEXUNIT</c> index to set the texture as.
	@param[in]		texture			A pointer to the texture. The structure is copied during this
									function and therefore does not need to persist after the call. The GPU
									data pointed to by the structure must persist until vertex
									processing for the current scene has completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The texture index was not valid.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The format of the texture is not supported as a vertex texture.

	@note Textures whose formats are based on #SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2,
	#SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3, #SCE_GXM_TEXTURE_BASE_FORMAT_YUV422,
	#SCE_GXM_TEXTURE_BASE_FORMAT_P4 and #SCE_GXM_TEXTURE_BASE_FORMAT_P8 are not supported
	for use as vertex textures.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetVertexTexture(
	SceGxmContext *context,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

/** Sets a fragment program texture for future draw calls.

	This function may be called at any time. The fragment texture persists indefinitely.

	It is not necessary to call this function when using a precomputed fragment state. In this case the
	textures can be patched directly on the #SceGxmPrecomputedFragmentState object
	by calling #sceGxmPrecomputedFragmentStateSetAllTextures().

	The <c><i>textureIndex</i></c> parameter must be between 0 and (#SCE_GXM_MAX_TEXTURE_UNITS - 1).

	The texture control words pointed to by <c><i>texture</i></c> are copied by value during this call
	and do not need to persist in memory afterwards. Note that the texture data must remain
	valid in memory until the GPU has finished fragment processing for the current scene.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		textureIndex	The <c>TEXUNIT</c> index to set the texture as.
	@param[in]		texture			A pointer to the texture. The structure is copied during this
									function, so does not need to persist after the call. The GPU
									data pointed to by the structure must persist until fragment
									processing for the current scene has completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The texture index was not valid.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetFragmentTexture(
	SceGxmContext *context,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

/**	Sets a vertex uniform buffer base address for future draw calls.

	This function may be called at any time. The vertex uniform buffer persists indefinitely.

	It is not necessary to call this function when using a precomputed vertex state. In this case
	uniform buffers can be patched directly on the #SceGxmPrecomputedVertexState object
	by calling #sceGxmPrecomputedVertexStateSetAllUniformBuffers().

	The <c><i>bufferIndex</i></c> parameter must be between 0 and (#SCE_GXM_MAX_UNIFORM_BUFFERS - 1).

	The <c><i>bufferData</i></c> parameter should be aligned to 64-bytes if the buffer is being used
	as a writable uniform buffer due to the behaviour of system level cache flush operations.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		bufferIndex		The buffer index to set the base address for.
	@param[in]		bufferData		A pointer to the uniform buffer data. The GPU data pointed to
									must persist until vertex processing for the current scene has
									completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The buffer index was not valid.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetVertexUniformBuffer(
	SceGxmContext *context,
	uint32_t bufferIndex,
	const void *bufferData);

/**	Sets a fragment uniform buffer base address for future draw calls.

	This function may be called at any time. The fragment uniform buffer persists indefinitely.

	It is not necessary to call this function when using a precomputed fragment state. In this case
	uniform buffers can be patched directly on the #SceGxmPrecomputedFragmentState object
	by calling #sceGxmPrecomputedFragmentStateSetAllUniformBuffers().

	The <c><i>bufferIndex</i></c> parameter must be between 0 and (#SCE_GXM_MAX_UNIFORM_BUFFERS - 1).

	The <c><i>bufferData</i></c> parameter should be aligned to 64-bytes if the buffer is being used
	as a writable uniform buffer due to the behaviour of system level cache flush operations.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		bufferIndex		The buffer index to set the base address for.
	@param[in]		bufferData		A pointer to the uniform buffer data. The GPU data pointed to
									must persist until fragment processing for the current scene has
									completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The buffer index was not valid.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetFragmentUniformBuffer(
	SceGxmContext *context,
	uint32_t bufferIndex,
	const void *bufferData);

/** Sets or unsets a precomputed fragment state for future draw calls.

	This function may be called at any time. The precomputed state persists indefinitely.

	If <c><i>precomputedState</i></c> is non-<c>NULL</c>, this #SceGxmPrecomputedFragmentState object
	overrides the fragment default uniform buffer reservation, all fragment uniform buffers and all
	fragment textures set on the context. In this case those patched into the fragment
	state are used instead.  The precomputed state pointed to by
	<c><i>precomputedState</i></c> must persist in memory after this call until a
	different precomputed state or <c>NULL</c> is set by a future call.

	If <c><i>precomputedState</i></c> is <c>NULL</c> the context reverts back to using the
	fragment uniform buffers and fragment textures currently set on the context.

	@param[in,out]	context				A pointer to the rendering context.
	@param[in]		precomputedState	A pointer to the precomputed state or <c>NULL</c>. The
										precomputed state must not be released until another program
										or <c>NULL</c> is set on the #SceGxmContext, and until fragment
										processing for the current scene has completed.

	@ingroup render
*/
void sceGxmSetPrecomputedFragmentState(
	SceGxmContext *context,
	const SceGxmPrecomputedFragmentState *precomputedState);

/** Sets or unsets a precomputed vertex state for future draw calls.

	This function may be called at any time. The precomputed state persists indefinitely.

	If <c><i>precomputedState</i></c> is non-<c>NULL</c>, this #SceGxmPrecomputedVertexState object
	overrides the vertex default uniform buffer reservation, all vertex uniform buffers and all
	vertex textures set on the context. In this case those patched into the vertex state are used instead.
	The precomputed state pointed to by <c><i>precomputedState</i></c> must persist in
	memory after this call until a different precomputed state or <c>NULL</c> is set by
	a future call.

	If <c><i>precomputedState</i></c> is <c>NULL</c> the context reverts back to using the
	vertex uniform buffers and vertex textures currently set on the context.

	@param[in,out]	context				A pointer to the rendering context.
	@param[in]		precomputedState	A pointer to the precomputed state or <c>NULL</c>. The
										precomputed state must not be released until another program
										or <c>NULL</c> is set on the #SceGxmContext, and until vertex
										processing for the current scene has completed.

	@ingroup render
*/
void sceGxmSetPrecomputedVertexState(
	SceGxmContext *context,
	const SceGxmPrecomputedVertexState *precomputedState);

/** Draws indexed geometry using a precomputed draw object.

	Drawing geometry using a precomputed draw object overrides all vertex streams
	currently set on the context. Instead vertex streams are used that have been
	set on the precomputed draw object.

	This function may only be called inside a scene or command list.
	When using the immediate context, calling this function outside of a scene will
	result in the #SCE_GXM_ERROR_NOT_WITHIN_SCENE error code being returned.  When using a deferred
	context, calling this function outside of a command list will result in the
	#SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST error code being returned.

	Drawing geometry is only valid when both the current vertex program and
	current fragment program are non-<c>NULL</c>.  If either are <c>NULL</c>, this function
	will return the error code #SCE_GXM_ERROR_NULL_PROGRAM and nothing will be
	drawn.

	Drawing geometry flushes any pending state changes to the GPU, if any state
	has changed since the last draw call.  To reduce most of the CPU overhead
	involved in flushing state, precomputed vertex or fragment state can be
	used via the #SceGxmPrecomputedVertexState and
	#SceGxmPrecomputedFragmentState objects.  While using these objects has CPU
	cost benefits, using precomputed state can mean that you have a larger
	memory footprint than flushing state dynamically.

	If the current vertex or fragment program has a non-empty default uniform
	buffer, and if the precomputed state is not being used for that pipeline,
	the default uniform buffer needs to have been reserved or set. This is done
	by calling #sceGxmReserveVertexDefaultUniformBuffer() or
	#sceGxmSetVertexDefaultUniformBuffer() for the vertex pipeline, and by calling
	#sceGxmReserveFragmentDefaultUniformBuffer() or
	#sceGxmSetFragmentDefaultUniformBuffer() for the fragment pipeline.
	Failing to reserve or set a (non-empty) default uniform buffer before a draw call
	will result in the #SCE_GXM_ERROR_UNIFORM_BUFFER_NOT_RESERVED error code being returned,
	and	nothing will be drawn.  Once a default uniform buffer is reserved successfully,
	it persists until either the scene is ended or a different program is set on that
	pipeline.  When using the same program for consecutive draw calls, it is not
	necessary to reserve it again before the next draw call unless different uniform
	values need to be written.

	When drawing using the immediate context, the data for all GPU resources (textures,
	vertex streams and uniform buffers) needs to have been fully written to memory before
	the draw function is called.  This is because the immediate context may need to
	split a scene into multiple jobs internally to free up ring buffer space, which
	potentially causes the GPU to begin processing the draw call immediately after the
	function returns.

	When drawing using a deferred context, the writing of data for GPU resources
	(textures, vertex streams and uniform buffers) may be deferred until the
	command list containing the draw call is used on the immediate context.
	This is done by calling #sceGxmExecuteCommandList().

	If, when drawing using a deferred context, additional buffer space is required
	to generate GPU data structures, one or more of the #SceGxmDeferredContextCallback
	functions will be called to acquire more space.  Should the callback function fail
	to provide enough memory, the draw call will return an #SCE_GXM_ERROR_RESERVE_FAILED
	error code, and it will not be present in the current command list.
	Future draw calls on the deferred context will continue to request memory through
	the buffer callbacks and fail in the same way if the callback continues to fail.
	It is always possible to end the command list using #sceGxmEndCommandList(),
	and the resulting command list will still be valid to execute on the immediate
	context using #sceGxmExecuteCommandList(). However, only draw calls that succeeded
	without error will be present in the command list.

	@param[in,out]	context				A pointer to the rendering context.
	@param[in]		precomputedDraw		A pointer to the precomputed draw commands. The
										precomputed draw commands must not be released until another
										program or <c>NULL</c> is set on the #SceGxmContext, and until
										fragment processing for the current scene has completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_NULL_PROGRAM The operation failed because a vertex and/or fragment
	program was not set.
	@retval
	SCE_GXM_ERROR_UNIFORM_BUFFER_NOT_RESERVED The operation failed because a required
	default uniform buffer has not been reserved.
	@retval
	SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION The operation failed
	because of an invalid depth/stencil configuration.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to a buffer callback function
	failing to provide sufficient memory for the GPU data structures required by this draw call.
	This error will only be returned from a deferred context. Immediate context reservations
	always succeed,	but they potentially have high latency if scenes are split to recycle memory.
	@retval
	SCE_GXM_ERROR_INVALID_PRECOMPUTED_FRAGMENT_STATE The operation failed because
	the precomputed fragment state program does not match the current fragment program.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_PRECOMPUTED_VERTEX_STATE The operation failed because
	the precomputed vertex state program does not match the current vertex program.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_PRECOMPUTED_DRAW The operation failed because the
	precomputed draw call vertex program does not match the current vertex program.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_INDEX_COUNT The operation failed because an invalid index
	count or index wrap was supplied. This error is only returned when running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_POLYGON_MODE The operation failed due to an invalid polygon
	mode. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_PRIMITIVE_TYPE The operation failed because a primitive type
	of #SCE_GXM_PRIMITIVE_POINTS was supplied but the current vertex program does not
	output PSIZE. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_PRECISION The operation failed
	because one of the textures does not support the precision of a query format
	used in shader code. This error is only returned when running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_COMPONENT_COUNT The operation
	failed because one of the textures is using a swizzle that produces an
	incorrect number of components for the query formats used in the shader
	code. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_FILTER_MODE The operation failed because one of
	the textures has a filtering mode that is incompatible with the query used
	in the shader code. This error is only returned when running the debug version
	of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE The operation failed because a texture was invalid.
	This can occur if the format or dimensionality of the texture is not compatible with
	its usage in the shader code.  It can also occur if the texture control words themselves
	are malformed.  This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_DATA_POINTER The operation failed because
	a texture has a <c>NULL</c> data pointer. This error is only returned when
    running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_PALETTE_POINTER The operation failed because
	a palettized texture has a <c>NULL</c> palette pointer. This error is only
	returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_OUTPUT_REGISTER_SIZE The operation failed because
	there is a mismatch in output register size between the fragment program
	and the color surface.  This error is only returned when using the immediate context
	while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_FRAGMENT_MSAA_MODE The operation failed because there is
	a mismatch in MSAA usage between the fragment program and the render target.
	This error can only occur for fragment programs that read the output register
	to perform blending operations, and it is only returned when using the
	immediate context while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_BUFFER_POINTER The operation failed because
	visibility testing is enabled but the visibility buffer pointer is <c>NULL</c>.
	This error is only returned when using the immediate context while running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_INDEX The operation failed because visibility
	testing is enabled but the visibility index is invalid.  This error is only returned
	when using the immediate context while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_BUFFER_OVERRUN The operation failed because the memory directly after
	the default uniform buffer reservation was	modified between the reserve call and
	the draw call.  This indicates a memory overrun	when writing the default uniform buffer
	contents. This error is only returned when running the debug version of
	libgxm.

	@ingroup render
*/
SceGxmErrorCode sceGxmDrawPrecomputed(
	SceGxmContext *context,
	const SceGxmPrecomputedDraw *precomputedDraw);

/** Draws indexed geometry.

	This function may only be called inside a scene or command list.
	When using the immediate context, calling this function outside of a scene will
	result in the #SCE_GXM_ERROR_NOT_WITHIN_SCENE error code being returned.  When using
	a deferred context, calling this function outside of a command list will result in the
	#SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST error code being returned.

	Drawing geometry is only valid when both the current vertex program and
	current fragment program are non-<c>NULL</c>.  If either are <c>NULL</c>, this function
	will return the error code #SCE_GXM_ERROR_NULL_PROGRAM and nothing will be
	drawn.

	Drawing geometry flushes any pending state changes to the GPU, if any state
	has changed since the last draw call.  To reduce most of the CPU overhead
	involved in flushing state, precomputed vertex or fragment state can be
	used via the #SceGxmPrecomputedVertexState and
	#SceGxmPrecomputedFragmentState objects.  While using these objects has CPU
	cost benefits, using precomputed state can mean that you have a larger
	memory footprint than flushing state dynamically.  To further reduce
	overheads, the draw call itself can be precomputed by using a
	#SceGxmPrecomputedDraw object with #sceGxmDrawPrecomputed().

	If the current vertex or fragment program has a non-empty default uniform
	buffer, and if you are not using precomputed state for that pipeline,
	the default uniform buffer needs to have been reserved or set. This is done
	by calling #sceGxmReserveVertexDefaultUniformBuffer() or
	#sceGxmSetVertexDefaultUniformBuffer() for the vertex pipeline, and by calling
	#sceGxmReserveFragmentDefaultUniformBuffer() or
	#sceGxmSetFragmentDefaultUniformBuffer() for the fragment pipeline.
	Failing to reserve or set a (non-empty) default uniform buffer before a draw call
	will result in the #SCE_GXM_ERROR_UNIFORM_BUFFER_NOT_RESERVED error code being returned,
	and nothing will be drawn.  Once a default uniform buffer is reserved successfully,
	it persists until either the scene is ended or a different program is set on that
	pipeline.  When using the same program for consecutive draw calls, it is not
	necessary to reserve it again before the next draw call unless different uniform
	values need to be written.

	When drawing using the immediate context, the data for all GPU resources (textures,
	vertex streams and uniform buffers) must have been fully written to memory before
	the draw function is called.  This is because the immediate context may need to
	split a scene into multiple jobs internally to free up ring buffer space, which
	potentially causes the GPU to begin processing the draw call immediately after the
	function returns.

	When drawing using a deferred context, the writing of data for	GPU resources
	(textures, vertex streams and uniform buffers) may be deferred until the
	command list containing the draw call is used on the immediate context.
	This is done by calling #sceGxmExecuteCommandList().

	If, when drawing using a deferred context, additional buffer space is required
	to generate GPU data structures, one or more of the #SceGxmDeferredContextCallback
	functions will be called to acquire more space.  Should the callback function fail
	to provide enough memory, the draw call will return an #SCE_GXM_ERROR_RESERVE_FAILED
	error, and it will not be present in the current command list.
	Future draw calls on the deferred context will continue to request memory through
	the buffer callbacks and fail in the same way if the callback continues to fail.
	It is always possible to end the command list using #sceGxmEndCommandList(),
	and the resulting command list will still be valid to execute on the immediate
	context using #sceGxmExecuteCommandList(). However, only draw calls that succeeded
	without error will be present in the command list.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		primType		The type of primitive.
	@param[in]		indexType		The type of the indices.
	@param[in]		indexData		A pointer to the index data. The GPU data pointed to must persist
									until vertex processing for the current scene has completed.
	@param[in]		indexCount		The number of indices.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_NULL_PROGRAM The operation failed because a vertex and/or fragment
	program was not set.
	@retval
	SCE_GXM_ERROR_UNIFORM_BUFFER_NOT_RESERVED The operation failed because a required
	default uniform buffer has not been reserved.
	@retval
	SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION The operation failed
	because of an invalid depth/stencil configuration.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to a buffer callback function
	failing to provide sufficient memory for the GPU data structures required by this draw call.
	This error will only be returned from a deferred context. Immediate context reservations
	always succeed,	but they potentially have high latency if scenes are split to recycle memory.
	@retval
	SCE_GXM_ERROR_INVALID_INDEX_COUNT The operation failed because an invalid index
	count was supplied. This error is only returned when running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_POLYGON_MODE The operation failed because an invalid polygon
	mode was supplied for the selected primitive type. This error is only returned when
    running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_PRIMITIVE_TYPE The operation failed because a primitive type
	of #SCE_GXM_PRIMITIVE_POINTS was supplied but the current vertex program does not
	output PSIZE. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_PRECISION The operation failed
	because one of the textures does not support the precision of a query format
	used in shader code. This error is only returned when running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_COMPONENT_COUNT The operation
	failed because one of the textures is using a swizzle that produces an
	incorrect number of components for the query formats used in the shader
	code. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_FILTER_MODE The operation failed because one of
	the textures has a filtering mode that is incompatible with the query used
	in the shader code. This error is only returned when running the debug version
	of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE The operation failed because a texture was invalid.
	This can occur if the format or dimensionality of the texture is not compatible with
	its usage in the shader code, or the texture control words themselves are malformed.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_DATA_POINTER The operation failed because
	a texture has a <c>NULL</c> data pointer. This error is only returned when
    running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_PALETTE_POINTER The operation failed because
	a palettized texture has a <c>NULL</c> palette pointer. This error is only
	returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_OUTPUT_REGISTER_SIZE The operation failed because
	there is a mismatch in output register size between the fragment program
	and the color surface.  This error is only returned when using the immediate context
	while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_FRAGMENT_MSAA_MODE The operation failed because there is
	a mismatch in MSAA usage between the fragment program and the render target.
	This error can only occur for fragment programs that read the output register
	to perform blending operations, and it is only returned when using the
	immediate context while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_BUFFER_POINTER The operation failed because
	visibility testing is enabled but the visibility buffer pointer is <c>NULL</c>.
	This error is only returned when using the immediate context while running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_INDEX The operation failed because visibility
	testing is enabled but the visibility index is invalid.  This error is only returned
	when using the immediate context while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_BUFFER_OVERRUN The operation failed because the memory directly after
	the default uniform buffer reservation was	modified between the reserve call and
	the draw call.  This indicates a memory overrun	when writing the default uniform buffer
	contents. This error is only returned when running the debug version of
	libgxm.

	@ingroup render
*/
SceGxmErrorCode sceGxmDraw(
	SceGxmContext *context,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount);

/** Draws multiple instances of indexed geometry.

	The position within the index buffer is reset each time <c><i>indexWrap</i></c> indices
	are processed until a total of <c><i>indexCount</i></c> indices have been processed.
	Each instance must be a whole number of primitives. Triangle strips and triangle
	fans are reset for the start of each instance.

	This function may only be called inside a scene or command list.
	When using the immediate context, calling this function outside of a scene will
	result in the #SCE_GXM_ERROR_NOT_WITHIN_SCENE error code being returned.  When using
	a deferred context, calling this function outside of a command list will result in the
	#SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST error code being returned.

	Drawing geometry is only valid when both the current vertex program and
	current fragment program are non-<c>NULL</c>.  If either are <c>NULL</c>, this function
	will return the error code #SCE_GXM_ERROR_NULL_PROGRAM and nothing will be
	drawn.

	Drawing geometry flushes any pending state changes to the GPU, if any state
	has changed since the last draw call.  To reduce most of the CPU overhead
	involved in flushing state, precomputed vertex or fragment state can be
	used via the #SceGxmPrecomputedVertexState and
	#SceGxmPrecomputedFragmentState objects.  While using these objects has CPU
	cost benefits, using precomputed state can mean that you have a larger
	memory footprint than flushing state dynamically.  To further reduce
	overheads, the draw call itself can be precomputed by using a
	#SceGxmPrecomputedDraw object with #sceGxmDrawPrecomputed().

	If the current vertex or fragment program has a non-empty default uniform
	buffer, and if you are not using precomputed state for that pipeline,
	the default uniform buffer needs to have been reserved or set. This is done
	by calling #sceGxmReserveVertexDefaultUniformBuffer() or
	#sceGxmSetVertexDefaultUniformBuffer() for the vertex pipeline, and by calling
	#sceGxmReserveFragmentDefaultUniformBuffer() or
	#sceGxmSetFragmentDefaultUniformBuffer() for the fragment pipeline.
	Failing to reserve or set a (non-empty) default uniform buffer before a draw call
	will result in the #SCE_GXM_ERROR_UNIFORM_BUFFER_NOT_RESERVED error code being returned,
	and nothing will be drawn.  Once a default uniform buffer is reserved successfully,
	it persists until either the scene is ended or a different program is set on that
	pipeline.  When using the same program for consecutive draw calls, it is not
	necessary to reserve it again before the next draw call unless different uniform
	values need to be written.

	When drawing using the immediate context, the data for all GPU resources (textures,
	vertex streams and uniform buffers) must have been fully written to memory before
	the draw function is called.  This is because the immediate context may need to
	split a scene into multiple jobs internally to free up ring buffer space, which
	potentially causes the GPU to begin processing the draw call immediately after the
	function returns.

	When drawing using a deferred context, the writing of data for	GPU resources
	(textures, vertex streams and uniform buffers) may be deferred until the
	command list containing the draw call is used on the immediate context.
	This is done by calling #sceGxmExecuteCommandList().

	If, when drawing using a deferred context, additional buffer space is required
	to generate GPU data structures, one or more of the #SceGxmDeferredContextCallback
	functions will be called to acquire more space.  Should the callback function fail
	to provide enough memory, the draw call will return an #SCE_GXM_ERROR_RESERVE_FAILED
	error, and it will not be present in the current command list.
	Future draw calls on the deferred context will continue to request memory through
	the buffer callbacks and fail in the same way if the callback continues to fail.
	It is always possible to end the command list using #sceGxmEndCommandList(),
	and the resulting command list will still be valid to execute on the immediate
	context using #sceGxmExecuteCommandList(). However, only draw calls that succeeded
	without error will be present in the command list.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		primType		The type of primitive.
	@param[in]		indexType		The type of the indices.
	@param[in]		indexData		A pointer to the index data. The GPU data pointed to must persist
									until vertex processing for the current scene has completed.
	@param[in]		indexCount		The total number of indices to draw.
	@param[in]		indexWrap		The number of indices to draw for each instance.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_NULL_PROGRAM The operation failed because a vertex and/or fragment
	program was not set.
	@retval
	SCE_GXM_ERROR_UNIFORM_BUFFER_NOT_RESERVED The operation failed because a required
	default uniform buffer has not been reserved.
	@retval
	SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION The operation failed
	because of an invalid depth/stencil configuration.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to a buffer callback function
	failing to provide sufficient memory for the GPU data structures required by this draw call.
	This error will only be returned from a deferred context. Immediate context reservations
	always succeed,	but they potentially have high latency if scenes are split to recycle memory.
	@retval
	SCE_GXM_ERROR_INVALID_INDEX_COUNT The operation failed because an invalid index
	count or index wrap was supplied. This error is only returned when running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_POLYGON_MODE The operation failed because an invalid polygon
	mode was supplied for the selected primitive type. This error is only returned when
	running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_PRIMITIVE_TYPE The operation failed because a primitive type
	of #SCE_GXM_PRIMITIVE_POINTS was supplied but the current vertex program does not
	output PSIZE. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_PRECISION The operation failed
	because one of the textures does not support the precision of a query format
	used in shader code. This error is only returned when running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_COMPONENT_COUNT The operation
	failed because one of the textures is using a swizzle that produces an
	incorrect number of components for the query formats used in the shader
	code. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_FILTER_MODE The operation failed because one of
	the textures has a filtering mode that is incompatible with the query used
	in the shader code. This error is only returned when running the debug version
	of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE The operation failed because a texture was invalid.
	This can occur if the format or dimensionality of the texture is not compatible with
	its usage in the shader code, or the texture control words themselves are malformed.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_DATA_POINTER The operation failed because
	a texture has a <c>NULL</c> data pointer. This error is only returned when
    running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_PALETTE_POINTER The operation failed because
	a palettized texture has a <c>NULL</c> palette pointer. This error is only
	returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_OUTPUT_REGISTER_SIZE The operation failed because
	there is a mismatch in output register size between the fragment program
	and the color surface.  This error is only returned when using the immediate context
	while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_FRAGMENT_MSAA_MODE The operation failed because there is
	a mismatch in MSAA usage between the fragment program and the render target.
	This error can only occur for fragment programs that read the output register
	to perform blending operations, and it is only returned when using the
	immediate context while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_BUFFER_POINTER The operation failed because
	visibility testing is enabled but the visibility buffer pointer is <c>NULL</c>.
	This error is only returned when using the immediate context while running the debug
	version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_INDEX The operation failed because visibility
	testing is enabled but the visibility index is invalid.  This error is only returned
	when using the immediate context while running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_BUFFER_OVERRUN The operation failed because the memory directly after
	the default uniform buffer reservation was	modified between the reserve call and
	the draw call.  This indicates a memory overrun	when writing the default uniform buffer
	contents. This error is only returned when running the debug version of
	libgxm.

	@ingroup render
*/
SceGxmErrorCode sceGxmDrawInstanced(
	SceGxmContext *context,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount,
	uint32_t indexWrap);

/** Updates the visibility buffers for the next scene.  This function cannot be called from within
	a #sceGxmBeginScene()/#sceGxmEndScene() pair.  The visibility buffers will be used for all scenes
	started after this function returns.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	The visibility buffer must be mapped with read/write access for the GPU, or page faults will
	occur.  The mapped region must extend from <c><i>bufferBase</i></c> for #SCE_GXM_GPU_CORE_COUNT times
	<c><i>stridePerCore</i></c> bytes.  In addition, the visibility slot index must be no more than
	<c><i>stridePerCore</i></c>/4 to ensure that the per-core buffers do not overlap.  Both the base
	address and stride must be aligned to #SCE_GXM_VISIBILITY_ALIGNMENT bytes.

	@param[in,out]	immediateContext	A pointer to the immediate context.
	@param[in]		bufferBase		The base address of the visibility buffer. The address must
									persist until fragment processing for the current scene has completed.
	@param[in]		stridePerCore	The stride between cores through the visibility buffer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the context is not an immediate context.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to either the base address or
	stride per core not being aligned to #SCE_GXM_VISIBILITY_ALIGNMENT bytes.
	@retval
    SCE_GXM_ERROR_WITHIN_SCENE The operation failed since the call is between calls to
	#sceGxmBeginScene() and #sceGxmEndScene().	This function may not be called within a scene.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetVisibilityBuffer(
	SceGxmContext *immediateContext,
	void *bufferBase,
	uint32_t stridePerCore);


/** Updates a YUV color profile for the next scene.  This function cannot be called from within
	a #sceGxmBeginScene()/#sceGxmEndScene() pair.  The YUV color profile will be used for all scenes
	started after this function returns.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	The <c><i>cscIndex</i></c> parameter defines whether the profile being set will be active for
	textures that use YUV swizzles referencing CSC0 or CSC1.

	The default profile for CSC0 is #SCE_GXM_YUV_PROFILE_BT601_STANDARD, and the default profile for
	CSC1 is #SCE_GXM_YUV_PROFILE_BT709_STANDARD.

	@param[in,out]	immediateContext	A pointer to the immediate context.
	@param[in]		cscIndex		The CSC index (0 or 1).
	@param[in]		profile			The YUV color profile.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter, or because
	the context is not an immediate context.
	@retval
    SCE_GXM_ERROR_WITHIN_SCENE The operation failed since the call is between calls to
	#sceGxmBeginScene() and #sceGxmEndScene().	This function may not be called within a scene.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetYuvProfile(
	SceGxmContext *immediateContext,
	uint32_t cscIndex,
	SceGxmYuvProfile profile);

/** Starts a scene with the given render target and optional color and depth/stencil surfaces.

	For a complete description of this function, please refer to the documentation for #sceGxmBeginSceneEx().
	#sceGxmBeginScene() behaves identically to #sceGxmBeginSceneEx() when using the same depth stencil surface
	for both load and store.

	@param[in,out]	immediateContext		A pointer to the immediate context.
	@param[in]		flags					Bitwise combined flags from #SceGxmSceneFlags.
	@param[in]		renderTarget			The render target dimensions and firmware job info. The
											render target must not be destroyed until the scene has
											been ended using #sceGxmEndScene().
	@param[in]		validRegion				An optional valid region of the render target. This
											structure does not need to persist after the call.
	@param[in]		vertexSyncObject		Reserved for future use. This must be <c>NULL</c>.
	@param[in]		fragmentSyncObject		An optional sync object to synchronize against fragment processing.
	@param[in]		colorSurface			An optional pointer to the color surface.  The
											structure is copied during this function and therefore does not need
											to persist after the call. The GPU data pointed to by the
											structure must persist until fragment processing for the
											current scene has been completed.
	@param[in]		depthStencilSurface		An optional pointer to the depth/stencil surface. Passing <c>NULL</c>
											results in behaviour that is the same as providing a depth/stencil
											surface that has been initialized with #SceGxmDepthStencilSurfaceInitDisabled().
											The structure is copied during this function and therefore does
											not need to persist after the call. The GPU data pointed to by the
											structure must persist until fragment processing for the current
											scene has been completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because both color and depth surfaces were
	disabled or <c>NULL</c>, or because the context is not an immediate context.
	@retval
	SCE_GXM_ERROR_WITHIN_SCENE The operation failed because the function was called within a scene.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported combination of MSAA mode and color surface downscale.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmBeginScene(
	SceGxmContext *immediateContext,
	uint32_t flags,
	const SceGxmRenderTarget *renderTarget,
	const SceGxmValidRegion *validRegion,
	SceGxmSyncObject *vertexSyncObject,
	SceGxmSyncObject *fragmentSyncObject,
	const SceGxmColorSurface *colorSurface,
	const SceGxmDepthStencilSurface *depthStencilSurface);

/** Starts a scene with the given render target and optional color and load/store depth/stencil surfaces.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	The <c><i>flags</i></c> argument contains information about scene dependencies and synchronization. See the documentation
	for #SceGxmSceneFlags for more details.

	The render target defines the how the surfaces are tiled for fragment processing, and provides resources
	for the firmware layer to schedule the job(s) for this scene. Within the render target, the set of valid
	tiles can be restricted to a subset of the render target using the <c><i>validRegion</i></c> parameter.
	If this parameter is not supplied, then the whole render target is considered to be valid. Only valid tiles
	are executed by the fragment pipeline. Geometry can be discarded at tile granularity by calling
	#sceGxmSetRegionClip() before drawing. Although the valid region must be static for the whole scene, region
	clip can change	between draw calls. Geometry, in tiles that pass region clip, is serialized into the parameter
	buffer for fragment processing.

	If the <c><i>colorSurface</i></c> is not <c>NULL</c> and is not disabled, the region in which color
	values are written to memory can be clipped at pixel granularity by calling #sceGxmColorSurfaceSetClip()
	on the surface before #sceGxmBeginSceneEx(). The <c><i>colorSurface</i></c> parameter does not need to
	persist in memory after the call to #sceGxmBeginSceneEx() returns.

	If depth tests other than NEVER or ALWAYS are required within the scene, a store depth/stencil surface
	must be provided that contains depth data as part of its format; this ensures correct behavior during a
	partial render. Similarly, if stencil tests	other than NEVER or ALWAYS are required within the scene,
	a store depth/stencil buffer must be provided that contains stencil data as part of its format. Attempting
	to use a depth test other than NEVER or ALWAYS with either a disabled store depth/stencil surface or a
	store depth/stencil surface with no depth data in its format will cause the draw call to return
	#SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION. Attempting to use a stencil test other than NEVER
	or ALWAYS with either a disabled store depth/stencil surface or a store depth/stencil surface with no
	stencil data in its format will also cause the draw call to return #SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION.
	If the depth and stencil tests will be NEVER or ALWAYS for all draw calls in a scene, the store depth/stencil
	surface may be <c>NULL</c> or disabled.  If a mask update fragment program is required within the
	scene, a store depth/stencil surface must be provided that contains mask data as part of its format; this
	ensures correct behavior during a partial render.  Attempting to issue a draw call that uses the mask
	update fragment program when the store depth/stencil surface does not contain mask data as part of its
	format will cause the draw call to return #SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION.

	In order to have correct behavior during a partial render, the
	depth/stencil/mask components supported by the load surface must be a subset of the depth/stencil/mask
	components supported by the store surface. After a partial render, all depth/stencil/mask data is loaded
	and stored through the store surface only.

	The implementation of #sceGxmBeginSceneEx() also sets the region clip to clip all geometry outside
	of the render target, and sets the viewport to cover the valid region.  This is equivalent to calling:

	@code
	uint32_t xMax = validRegion ? validRegion->xMax : (renderTargetWidthInPixels - 1);
	uint32_t yMax = validRegion ? validRegion->yMax : (renderTargetHeightInPixels - 1);
	sceGxmSetDefaultRegionClipAndViewport(context, xMax, yMax);
	@endcode

	@param[in,out]	immediateContext			A pointer to the immediate context.
	@param[in]		flags						Bitwise combined flags from #SceGxmSceneFlags.
	@param[in]		renderTarget				The render target dimensions and firmware job info. The
												render target must not be destroyed until the scene has
												been ended using #sceGxmEndScene().
	@param[in]		validRegion					An optional valid region of the render target. This
												structure does not need to persist after the call.
	@param[in]		vertexSyncObject			Reserved for future use.  Must be <c>NULL</c>.
	@param[in]		fragmentSyncObject			An optional sync object to synchronize against fragment processing.
	@param[in]		colorSurface				An optional pointer to the color surface.  The
												structure is copied during this function and therefore does not need
												to persist after the call. The GPU data pointed to by the
												structure must persist until fragment processing for the
												current scene has been completed.
	@param[in]		loadDepthStencilSurface		An optional pointer to the depth/stencil surface used for load. The
												structure is copied during this function and therefore does not need
												to persist after the call. The GPU data pointed to by the
												structure must persist until fragment processing for the
												current scene has been completed.
	@param[in]		storeDepthStencilSurface	An optional pointer to the depth/stencil surface used for load. The
												structure is copied during this function and therefore does not need
												to persist after the call. The GPU data pointed to by the
												structure must persist until fragment processing for the
												current scene has been completed.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_WITHIN_SCENE The operation failed because the function was called within a scene.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported combination of MSAA mode and color surface downscale.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmBeginSceneEx(
	SceGxmContext *immediateContext,
	uint32_t flags,
	const SceGxmRenderTarget *renderTarget,
	const SceGxmValidRegion *validRegion,
	SceGxmSyncObject *vertexSyncObject,
	SceGxmSyncObject *fragmentSyncObject,
	const SceGxmColorSurface *colorSurface,
	const SceGxmDepthStencilSurface *loadDepthStencilSurface,
	const SceGxmDepthStencilSurface *storeDepthStencilSurface);

/** Flushes vertex processing, creating and submitting a vertex-processing-only job to the
	firmware layer.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	The default behavior of this flush operation is to lose the reservation for
	the vertex default uniform buffer.  To preserve this buffer, pass
	#SCE_GXM_MIDSCENE_PRESERVE_DEFAULT_UNIFORM_BUFFERS as the <c><i>flags</i></c>
	parameter.  This has some overhead due to the underlying copy operation, but
	allows the caller to continue calling draw functions without having to
	manually reserve and write the vertex default uniform buffer contents again.
	This flag has no effect if the current vertex program is <c>NULL</c> or the vertex
	default uniform buffer has not yet been reserved.

	The optional notification object can be used to signal that the GPU has finished
	processing this job on the vertex pipeline.  This can be used to synchronize
	resources used by the vertex pipeline with the GPU, such as dynamic vertex data.

	@param[in,out]	immediateContext		A pointer to the immediate context.
	@param[in]		flags					Bitwise combined flags from #SceGxmMidSceneFlags.
	@param[in]		vertexSyncObject		Reserved for future use.  Must be <c>NULL</c>.
	@param[in]		vertexNotification		A Pointer to a notification object used to identify completion of
											vertex processing. Set to <c>NULL</c> if this is not required.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the context is not an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed because there is no matching call to #sceGxmBeginScene().

	@ingroup render
*/
SceGxmErrorCode sceGxmMidSceneFlush(
	SceGxmContext *immediateContext,
	uint32_t flags,
	SceGxmSyncObject *vertexSyncObject,
	const SceGxmNotification *vertexNotification);

/** Ends the scene, which immediately creates and submits a job to the firmware layer.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	The optional notification objects can be used to signal that the GPU has finished
	processing the scene on the vertex or fragment pipeline.

	@param[in,out]	immediateContext		A pointer to the immediate context.
	@param[in]		vertexNotification		A pointer to a notification object used to identify completion of
											vertex processing. Set to <c>NULL</c> if this is not required.
	@param[in]		fragmentNotification	A pointer to a notification object used to identify completion of
											fragment processing. Set to <c>NULL</c> if this is not required.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the context is not an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed because there is no matching call to #sceGxmBeginScene().

	@ingroup render
*/
SceGxmErrorCode sceGxmEndScene(
	SceGxmContext *immediateContext,
	const SceGxmNotification *vertexNotification,
	const SceGxmNotification *fragmentNotification);

/** Sets the comparison mode to be applied to depth values for front-facing primitives. If
	two-sided rendering has not been enabled then this setting applies to both front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		depthFunc		The depth comparison function.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontDepthFunc(SceGxmContext *context, SceGxmDepthFunc depthFunc);

/**	Sets the comparison mode to be applied to depth values for back-facing primitives when
	two-sided rendering has been enabled. It is only necessary to call this function when two-sided
	rendering is enabled.	When not using two-sided rendering, then the setting of
	#sceGxmSetFrontDepthFunc() is used for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		depthFunc		The depth comparison function.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetBackDepthFunc(SceGxmContext *context, SceGxmDepthFunc depthFunc);

/** Enables fragment program processing for front-facing primitives. If two-sided rendering has
	not been enabled then this setting applies to both front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			A flag specifying whether to enable or disable fragment program processing.

	@see #sceGxmSetTwoSidedEnable
	@see #sceGxmFragmentProgramIsEnabled

	@ingroup render
*/
void sceGxmSetFrontFragmentProgramEnable(SceGxmContext *context, SceGxmFragmentProgramMode enable);

/** Enables fragment program processing for back-facing primitives when two-sided rendering has
	been enabled. It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontFragmentProgramEnable() is used
	for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			A flag specifying whether to enable or disable fragment program processing.

	@see #sceGxmSetTwoSidedEnable
	@see #sceGxmFragmentProgramIsEnabled

	@ingroup render
*/
void sceGxmSetBackFragmentProgramEnable(SceGxmContext *context, SceGxmFragmentProgramMode enable);

/** Enables depth writes for front-facing primitives. If not enabled, the depth buffer is not
	updated regardless of whether any depth test has passed. If two-sided rendering has not been
	enabled then this setting applies to both front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			A flag specifying whether to enable or disable depth writes.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontDepthWriteEnable(SceGxmContext *context, SceGxmDepthWriteMode enable);

/** Enables depth writes for back-facing primitives when two-sided rendering has been enabled.
	If not enabled, the depth buffer is not updated regardless of whether any depth test has passed.
	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontDepthWriteEnable() is used
	for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			A flag specifying whether to enable or disable depth writes.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetBackDepthWriteEnable(SceGxmContext *context, SceGxmDepthWriteMode enable);

/** Enables filling of the last pixel of a line for front-facing primitives. If not enabled,
	the last pixel of a line is not filled. If two-sided rendering has not been enabled then this
	setting applies to both front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			A flag specifying whether to enable or disable filling of the last pixel.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontLineFillLastPixelEnable(SceGxmContext *context, SceGxmLineFillLastPixelMode enable);

/** Enables filling of the last pixel of a line for back-facing primitives when two-sided rendering
	has been enabled. If not enabled, the last pixel of a line is not filled. It is only necessary
	to call this function when two-sided rendering is enabled. When not using two-sided rendering
	the setting of #sceGxmSetFrontLineFillLastPixelEnable() is used for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			A flag specifying whether to enable or disable filling of the last pixel.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetBackLineFillLastPixelEnable(SceGxmContext *context, SceGxmLineFillLastPixelMode enable);

/** Sets the stencil reference value for front-facing primitives. If two-sided rendering has not
	been enabled then this setting applies to both front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		sref			The reference value used for stencil testing.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontStencilRef(SceGxmContext *context, uint8_t sref);

/** Sets the stencil reference value for back-facing primitives when two-sided rendering has been enabled.
	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontStencilRef() is used
	for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		sref			The reference value used for stencil testing.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetBackStencilRef(SceGxmContext *context, uint8_t sref);

/** Sets the width of front-facing points and lines in pixels. If two-sided rendering has not
	been enabled then this setting applies to both front and back-facing primitives.

	This setting only applies to primitives rendered using polygon mode #SCE_GXM_POLYGON_MODE_LINE,
	#SCE_GXM_POLYGON_MODE_TRIANGLE_LINE or #SCE_GXM_POLYGON_MODE_TRIANGLE_POINT.  Point primitives
	that use one of the #SCE_GXM_POLYGON_MODE_POINT polygon modes must always use the PSIZE
	output from the vertex program.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		width			The width of the points and lines (1-16).

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontPointLineWidth(SceGxmContext *context, uint32_t width);

/** Sets the width of back-facing points and lines when two-sided rendering has been enabled.
	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontPointLineWidth() is used
	for both sides.

	This setting only applies to primitives rendered using polygon mode #SCE_GXM_POLYGON_MODE_LINE,
	#SCE_GXM_POLYGON_MODE_TRIANGLE_LINE or #SCE_GXM_POLYGON_MODE_TRIANGLE_POINT.  Point primitives
	that use one of the #SCE_GXM_POLYGON_MODE_POINT polygon modes must always use the PSIZE
	output from the vertex program.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		width			The width of the points and lines (1-16).

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetBackPointLineWidth(SceGxmContext *context, uint32_t width);

/** Sets the polygon mode for front-facing primitives. If two-sided rendering has not been enabled
	then this setting applies to both front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		mode			The polygon mode.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontPolygonMode(SceGxmContext *context, SceGxmPolygonMode mode);

/** Sets the polygon mode for back-facing primitives when two-sided rendering has been enabled.
	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontPolygonMode() is used
	for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		mode			The polygon mode.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetBackPolygonMode(SceGxmContext *context, SceGxmPolygonMode mode);

/** Sets the stencil function and operations for front-facing primitives. If two-sided rendering
	has not been enabled then this setting applies to both front and back-facing primitives.

	If stencil testing is not required, the stencil comparison function
	should be set to #SCE_GXM_STENCIL_FUNC_ALWAYS, and all stencil operations
	should be set to #SCE_GXM_STENCIL_OP_KEEP because this specific setting
	reduces the amount of parameter buffer used for each primitive block.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		func			The stencil comparison function.
	@param[in]		stencilFail		The stencil operation performed if the stencil test fails.
	@param[in]		depthFail		The stencil operation performed if the depth test fails.
	@param[in]		depthPass		The stencil operation performed if the depth test passes.
	@param[in]		compareMask		A mask of bits used when performing stencil buffer comparison.
									The current stencil value is anded with this value prior to the test
									being carried out.
	@param[in]		writeMask		A bitwise mask applied to the stencil value after stencil operations.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontStencilFunc(SceGxmContext *context,
							   SceGxmStencilFunc func,
							   SceGxmStencilOp stencilFail,
							   SceGxmStencilOp depthFail,
							   SceGxmStencilOp depthPass,
							   uint8_t compareMask,
							   uint8_t writeMask);

/** Sets the stencil function and operations for back-facing primitives when two-sided rendering
	has been enabled. It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontStencilFunc() is used
	for both sides.

	If two-sided rendering is enabled but stencil testing is not required,
	the stencil comparison function
	should be set to #SCE_GXM_STENCIL_FUNC_ALWAYS, and all stencil operations
	should be set to #SCE_GXM_STENCIL_OP_KEEP because this specific setting
	reduces the amount of parameter buffer used for each primitive block.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		func			The stencil comparison function.
	@param[in]		stencilFail		The stencil operation performed if the stencil test fails.
	@param[in]		depthFail		The stencil operation performed if the depth test fails.
	@param[in]		depthPass		The stencil operation performed if the depth test passes.
	@param[in]		compareMask		A mask of bits used when performing stencil buffer comparison.
									The current stencil value is anded with this value prior to the test
									being carried out.
	@param[in]		writeMask		A per-bit mask applied to the stencil value after stencil operations.

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/

void sceGxmSetBackStencilFunc(SceGxmContext *context,
							  SceGxmStencilFunc func,
							  SceGxmStencilOp stencilFail,
							  SceGxmStencilOp depthFail,
							  SceGxmStencilOp depthPass,
							  uint8_t compareMask,
							  uint8_t writeMask);

/** Sets values that offset the computed depth value for front-facing primitives. The <c><i>factor</i></c>
	parameter scales the maximum Z slope, with respect to the X or Y of the primitive, while the <c><i>units</i></c>
	parameter scales the minimum resolvable depth buffer value. The results are summed to produce a single
	value that offsets the depth value for a fragment. If two-sided rendering has not been enabled
	then this setting applies to both front and back-facing primitives.

	Depth bias is always enabled and applied to the on-chip depth value at F32 precision.
	The equation used for depth bias is as follows:

	@code
		final_z = raw_z + factor*z_slope + units*z_epsilon;
	@endcode

	The terms in this equation are defined as follows:

	<ul>
	<li><c>raw_z</c> is the z value of this sample on the triangle</li>
	<li><c>z_slope</c> is the maximum Z slope at this sample, defined by
		<c>z_slope = fabsf(dz/dx) + fabsf(dz/dy)</c></li>
	<li><c>z_epsilon</c> is the smallest value that would affect this sample, defined by
		<c>{ int n; frexp(raw_z, &n); z_epsilon = ldexp(1.0f, n - 23); }</c></li>
	<li><c>factor</c> and <c>units</c> are the arguments to this function</li>
	<li><c>final_z</c> is the final z value of this sample used for the depth test and write</li>
	</ul>

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		factor			A signed slope value in the range [-16, 15].
	@param[in]		units			A signed bias value in the range [-16, 15].

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetFrontDepthBias(SceGxmContext *context, int32_t factor, int32_t units);

/** Sets values that offset the computed depth value for back-facing primitives when two-sided rendering
	has been enabled. The <c><i>factor</i></c> parameter scales the maximum Z slope, with respect to the X
	or Y of the primitive, while the <c><i>units</i></c> parameter scales the minimum resolvable depth buffer
	value. The results are summed to produce a single value that offsets the depth value for a fragment.
	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontDepthBias() is used
	for both sides.

	The documentation for #sceGxmSetFrontDepthBias() describes how the parameters
	affect the depth value of each sample on the triangle.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		factor			A signed slope value in the range [-16, 15].
	@param[in]		units			A signed bias value in the range [-16, 15].

	@see #sceGxmSetTwoSidedEnable

	@ingroup render
*/
void sceGxmSetBackDepthBias(SceGxmContext *context, int32_t factor, int32_t units);

/** Enables two-sided rendering of primitives.

	Primitives are determined to be front facing or back facing based on the winding order of
	their screen-space coordinates. Primitives with a clockwise winding order are
	treated as front-facing, while primitives with a counterclockwise winding order are treated as
	back-facing. When two-sided rendering is enabled, state must be set independently for front and
	back-facing primitives. When two-sided rendering is not enabled, all primitives use the
	front-facing state.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			Enable/disable two sided rendering.

	@ingroup render
*/
void sceGxmSetTwoSidedEnable(SceGxmContext *context, SceGxmTwoSidedMode enable);

/** Sets values that define a viewport transformation, used to transform clipping space coordinates
	generated by the USSE (<c>cx</c>,<c>cy</c>,<c>cz</c>,<c>cw</c>) into screen space coordinates
	(<c>sx</c>,<c>sy</c>,<c>sz</c>,<c>sw</c>).

	The viewport values can be changed at any time, but please note that
	#sceGxmBeginScene() resets the viewport values to the size of the render target
	or valid region.  When using a deferred context, the viewport values must be
	set manually, using this function or #sceGxmSetDefaultRegionClipAndViewport(),
	before the first draw call of the deferred context.

	The value is computed as shown in the supplied pseudo-code. The W clamping and buffering states
	used are those set using #sceGxmSetWClampValue(), #sceGxmSetWClampEnable(), and #sceGxmSetWBufferEnable().

	If the viewport transform is disabled by calling #sceGxmSetViewportEnable, then this step is
	bypassed, with the USSE outputs assumed to already be in screen space coordinates.

	@code
		if (WClamp enabled)
			if (cw < WClamp value)
				cw = WClamp value

		sx = xOffset + xScale * (cx/cw)
		sy = yOffset + yScale * (cy/cw)
		if (WBuffer enabled)
			sz = zOffset + zScale/cw
		else
			sz = zOffset + zScale * (cz/cw)
		sw = 1.0/cw
	@endcode

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		xOffset			The offset applied to X.
	@param[in]		xScale			The scale applied to X.
	@param[in]		yOffset			The offset applied to Y.
	@param[in]		yScale			The scale applied to Y.
	@param[in]		zOffset			The offset applied to Z.
	@param[in]		zScale			The scale applied to Z.

	@ingroup render
*/
void sceGxmSetViewport(SceGxmContext *context, float xOffset, float xScale, float yOffset, float yScale, float zOffset, float zScale);

/** Sets a value used to clamp the W passed to viewport transformation when #sceGxmSetWClampEnable()
	has been called with the <c><i>enable</i></c> parameter set to true.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		clampValue		The value with which to clamp W prior to viewport transformation.
									See #sceGxmSetViewport() for a description of how this interacts with the
									viewport transformation.

	@ingroup render
*/
void sceGxmSetWClampValue(SceGxmContext *context, float clampValue);

/** Enables clamping of the W value passed to viewport transformation to the value set by
	#sceGxmSetWClampValue().

	See #sceGxmSetViewport() for a description of how this interacts with the viewport transform.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			Specifies whether to enable or disable W clamping.

	@ingroup render
*/
void sceGxmSetWClampEnable(SceGxmContext *context, SceGxmWClampMode enable);

/** Defines a rectangular area and region clip mode that controls which tiles
	are active during vertex processing.  Only active tiles write their data to
	the parameter buffer for fragment shading.  Geometry that intersects
	inactive tiles will not be shaded within those tiles.

	Region clip can be changed at any time, but please note that
	#sceGxmBeginScene() resets the region clip to the size of the render target
	or valid region.  When using a deferred context, region clip must be
	set manually, using this function or #sceGxmSetDefaultRegionClipAndViewport(),
	before the first draw call of the deferred context.

	@note
	The coordinates given here are specified in pixels and are
	inclusive, so a region starting at the origin should use a region clip of
	(0, 0, width - 1, height - 1) to clip accurately.  Although the clip coordinates
	are supplied in pixels, they will be internally aligned to #SCE_GXM_TILE_SIZEX
	and #SCE_GXM_TILE_SIZEY within this function.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		mode			The region clip mode.
	@param[in]		xMin			The left edge (inclusive) of the clip region in pixels.
	@param[in]		yMin			The top edge (inclusive) of the clip region in pixels.
	@param[in]		xMax			The right edge (inclusive) of the clip region in pixels.
	@param[in]		yMax			The bottom edge (inclusive) of the clip region in pixels.

	@ingroup render
*/
void sceGxmSetRegionClip(SceGxmContext *context, SceGxmRegionClipMode mode, uint32_t xMin, uint32_t yMin, uint32_t xMax, uint32_t yMax);

/** Sets the culling mode for primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		mode			The cull mode.

	@ingroup render
*/
void sceGxmSetCullMode(SceGxmContext *context, SceGxmCullMode mode);

/** Enables or disables the viewport transform, allowing for data coming out of the USSE
	to be used without clipping or viewport transformation taking place when disabled. When
	the viewport transfer is disabled, coordinates passed through for rasterization need to
	fall within the guard band defined by the GPU. This is a range of -1024 to 7167 for
	each axis. Use of coordinates outside of this range may result in incorrect rasterization.

	See #sceGxmSetViewport() for details of the viewport transform.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			Specifies whether to enable or disable the viewport transform.

	@ingroup render
*/
void sceGxmSetViewportEnable(SceGxmContext *context, SceGxmViewportMode enable);

/** Enables W buffering mode during viewport transformation defined by #sceGxmSetViewport().

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			Specifies whether to enable or disable W buffering.

	@ingroup render
*/
void sceGxmSetWBufferEnable(SceGxmContext *context, SceGxmWBufferMode enable);

/** Sets the visibility test index for front-facing primitives.  The visibility test
	index is used as an offset within an array of 32-bit visibility test results
	that are written by each GPU core.

	If two-sided rendering has not been enabled then this setting applies to both
	front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		index			The index in the range [0, 16383].

	@ingroup render
*/
void sceGxmSetFrontVisibilityTestIndex(SceGxmContext *context, uint32_t index);

/** Sets the visibility test operation for back-facing primitives.  The visibility test
	index is used as an offset within an array of 32-bit visibility test results
	that are written by each GPU core.

	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering the setting of #sceGxmSetFrontVisibilityTestIndex()
	is used for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		index			The index in the range [0, 16383].

	@ingroup render
*/
void sceGxmSetBackVisibilityTestIndex(SceGxmContext *context, uint32_t index);

/** Sets the visibility test operation for front-facing primitives.  When visibility testing
	is enabled, this operation is performed for each visible pixel.

	If two-sided rendering has not been enabled then this setting applies to both
	front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		op				The operation to perform for visible pixels.

	@ingroup render
*/
void sceGxmSetFrontVisibilityTestOp(SceGxmContext *context, SceGxmVisibilityTestOp op);

/** Sets the visibility test operation for back-facing primitives.  When visibility testing
	is enabled, this operation is performed for each visible pixel.

	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering, then the setting of #sceGxmSetFrontVisibilityTestOp()
	is used for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		op				The operation to perform for visible pixels.

	@ingroup render
*/
void sceGxmSetBackVisibilityTestOp(SceGxmContext *context, SceGxmVisibilityTestOp op);

/** Enables or disables the visibility test for front-facing primitives.

	If two-sided rendering has not been enabled then this setting applies to both
	front and back-facing primitives.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			Specifies whether to enable or disable the visibility test.

	@ingroup render
*/
void sceGxmSetFrontVisibilityTestEnable(SceGxmContext *context, SceGxmVisibilityTestMode enable);

/** Enables or disables the visibility test for back-facing primitives.

	It is only necessary to call this function when two-sided rendering is enabled.
	When not using two-sided rendering the setting of #sceGxmSetFrontVisibilityTestEnable()
	is used for both sides.

	@param[in,out]	context			A pointer to the rendering context.
	@param[in]		enable			Specifies whether to enable or disable the visibility test.

	@ingroup render
*/
void sceGxmSetBackVisibilityTestEnable(SceGxmContext *context, SceGxmVisibilityTestMode enable);

/** Blocks until all rendering has finished on the GPU.

	Blocks until all rendering up to and including the last call to
	#sceGxmEndScene() has completed.

	@param[in,out]	context			A pointer to the rendering context.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_THREAD The operation failed because the function was called from the display queue thread.

	@ingroup render
*/
SceGxmErrorCode sceGxmFinish(SceGxmContext *context);

/** Inserts a user push marker into the captured render data.

	@param[in,out]	context			A pointer to the rendering context.
    @param[in]		tag				A pointer to the marker string. The string does
									not need to persist after the call.

	@retval
	SCE_OK The operation was successful.
	@retval
    SCE_GXM_ERROR_INVALID_POINTER The operation failed due to
    the <c><i>context</i></c> or <c><i>tag</i></c> pointer being <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to the VDM buffer callback
	function failing to provide sufficient memory for the user marker.
	This error will only be returned from a deferred context.

	@note
	User marker operations only take place when the Razor GPU Capture module
	is loaded.  When the operation takes place, there are significant
	memory and performance differences for this function
	depending on the type of context used.

	@note
	If this function is used with an immediate context, it will have no effect
	unless a Razor GPU Capture is being written. If a capture is being written,
	the tag string will be copied into memory managed by the Razor GPU Capture module.

	@note
	If this function is used with a deferred context, the tag string will be
	copied into the VDM Stream memory associated with that context. It will be
	copied even if a Razor GPU Capture is not being written.

	@ingroup render
*/
SceGxmErrorCode sceGxmPushUserMarker(SceGxmContext *context, const char *tag);

/** Inserts a user pop marker into the captured render data.

	@param[in,out]	context			A pointer to the rendering context.

	@retval
	SCE_OK The operation was successful.
	@retval
    SCE_GXM_ERROR_INVALID_POINTER The operation failed due to
    the <c><i>context</i></c> pointer being <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to the VDM buffer callback
	function failing to provide sufficient memory for the user marker.
	This error will only be returned from a deferred context.

	@note
	User marker operations only take place when the Razor GPU Capture module
	is currently loaded.  When using an immediate context, operations are
	also skipped if a Razor GPU Capture is not being written.

	@ingroup render
*/
SceGxmErrorCode sceGxmPopUserMarker(SceGxmContext *context);

/** Inserts a user set marker into the captured render data.

	@param[in,out]	context			A pointer to the rendering context.
    @param[in]		tag				A pointer to the marker string. The string does
									not need to persist after the call.

	@retval
	SCE_OK The operation was successful.
	@retval
    SCE_GXM_ERROR_INVALID_POINTER The operation failed due to
    the <c><i>context</i></c> or <c><i>tag</i></c> pointer being <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed since the call is
	not between calls to #sceGxmBeginScene() and #sceGxmEndScene().  This error will
	only be returned from an immediate context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the call
	is not between calls to #sceGxmBeginCommandList() and #sceGxmEndCommandList().  This
	error will only be returned from a deferred context.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to the VDM buffer callback
	function failing to provide sufficient memory for the user marker.
	This error will only be returned from a deferred context.

	@note
	User marker operations only take place when the Razor GPU Capture module
	is currently loaded.  When the operation takes place, there are significant
	memory and performance differences for this function
	depending on the type of context used.

	@note
	If this function is used with an immediate context, it will have no effect
	unless a Razor GPU Capture is being written. If a capture is being written,
	the tag string will be copied into memory managed by the Razor GPU Capture module.

	@note
	If this function is used with a deferred context, the tag string will be
	copied into the VDM Stream memory associated with that context. It will be
	copied even if a Razor GPU Capture is not being written.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetUserMarker(SceGxmContext *context, const char *tag);

/** Heartbeat function for PA.

	This function should be called after the last scene of your frame,
	before adding a display queue entry to swap the buffers.

	@param[in]	displaySurface		A surface to display, usually the back buffer.
	@param[in]	displaySyncObject	The display sync object to use with this surface.

	@retval
	SCE_OK The operation was successful.

	@note The <c><i>displaySurface</i></c> and <c><i>displaySyncObject</i></c> arguments can be <c>NULL</c>
	when Razor HUD display is not required. In this case, Razor HUD display cannot be enabled. However,
	other features such as GPU Traces and GPU Live Metrics can be enabled.

	@ingroup render
*/
SceGxmErrorCode sceGxmPadHeartbeat(
	const SceGxmColorSurface *displaySurface,
	SceGxmSyncObject *displaySyncObject);

/** Begins rendering to a command list.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	A command list represents a group of draw calls with a full GPU state reset before and
	after the group.  Draw calls within the command list use the current state
	set on the deferred context. This is independent from the state of any other deferred
	context and also the immediate context, which will ultimately execute the command list.

	Region clip and viewport are not set automatically on the deferred context when
	starting a command list, so this state, if necessary, should be set before the first
	draw call. At a minimum, it should be set once after the deferred context has been created.

	Once all draw calls have been submitted, the command list can be ended using
	#sceGxmEndCommandList(), and the resulting #SceGxmCommandList may
	be executed on the immediate context.

	@param[in,out]  deferredContext		A pointer to a deferred context.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the pointer to the deferred context was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the context is not a deferred context.
	@retval
	SCE_GXM_ERROR_WITHIN_COMMAND_LIST The operation failed because the deferred context
	is already within a command list.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed because the VDM buffer callback
	function failed to provide the minimum amount of memory required for a command list.

	@ingroup render
 */
SceGxmErrorCode sceGxmBeginCommandList(
	SceGxmContext *deferredContext);

/** Ends rendering to a command list.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	The implementation of this function will not trigger a memory callback function, so
	it will always succeed even if draw calls within the command list failed due to lack
	of memory.

	Once the function has completed successfully, the resulting #SceGxmCommandList may
	be executed on the immediate context using #sceGxmExecuteCommandList().

	Ending a command list will cause the current default uniform buffer reservations to
	be lost.  These must be reserved again using #sceGxmBeginCommandList() if a new
	command list is started on this	deferred context.  All other state on the deferred
	context will persist for future command lists, but no internal GPU data structures
	persist to the next command list.  This ensures that the deferred context buffers
	can be reset between command lists, and that new command lists only reference
	GPU data structures that are generated using the new buffers.

	Various state is stored with the command list such as the maximum region clip
	dimensions, and whether the draw calls within the region clip require depth, stencil or
	mask data to be part of the depth/stencil format.  This state will be validated
	during #sceGxmExecuteCommandList(), and it must be compatible with the scene the
	command list will be made part of. #sceGxmExecuteCommandList() will return
	an error if the state is not compatible.  Please see the documentation of
	#sceGxmExecuteCommandList() for more details.

	@param[in,out]	deferredContext		A pointer to a deferred context.
	@param[out]		commandList			A pointer to a #SceGxmCommandList.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed as a pointer to the deferred context or command list was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed as the context is not a deferred context.
	@retval
	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST The operation failed since the deferred context
	is not currently within a command list.

	@ingroup render
 */
SceGxmErrorCode sceGxmEndCommandList(
	SceGxmContext *deferredContext,
	SceGxmCommandList *commandList);

/** Links a command list into the current scene to be executed by the GPU.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	Executing a command list is implemented by placing jump commands in the
	VDM stream executed by the GPU during vertex processing.  A jump from the
	immediate context will jump to the start of the command list, and the command list
	VDM stream is patched to jump back to the immediate context.  Because of this, the
	command list must not be executed in another scene until vertex processing for
	this scene or, if using #sceGxmMidSceneFlush(), job is completed.

	To ensure the GPU is not given an illegal combination of region clip and valid region,
	the tile-aligned maximum Y value of region clip over all draw calls in the command list
	must be at most the tile-aligned maximum Y value of the valid region of the current scene.
	If this condition is not met, the command list execution will fail, and the
	#SCE_GXM_ERROR_INVALID_REGION_CLIP_IN_COMMAND_LIST error code will be returned.  This clamping
	operation is performed automatically for region clip state on the immediate context; for command
	lists, this restriction must only be handled manually since the valid region is
	not known at the time the command list is built on a deferred context.

	To ensure correct behavior during a partial render, if the command list
	contains draw calls that use depth tests other than NEVER or ALWAYS, the store
	depth/stencil surface for this scene must contain depth data as part of its format.
	Similarly, if the command list contains draw calls that use a stencil test other than
	NEVER or ALWAYS, the store depth/stencil surface for this scene must contain stencil
	data as part of its format.  If the command contains draw calls that use a mask update
	fragment program, the store depth/stencil surface for this scene must contain mask data
	as part of its format.  If any of these conditions are not met, executing the command list
	will fail, and a #SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION error code will be returned.

	@param[in,out]	immediateContext	A pointer to an immediate context.
	@param[in,out]	commandList			A pointer to a #SceGxmCommandList.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer to the immediate context or command list was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>immediateContext</i></c> parameter does not
	point to the immediate context, or the command list is not valid.
	@retval
    SCE_GXM_ERROR_NOT_WITHIN_SCENE The operation failed because the call is not between calls to
	#sceGxmBeginScene() and #sceGxmEndScene().	This function must be called within a scene.
	@retval
	SCE_GXM_ERROR_INVALID_REGION_CLIP_IN_COMMAND_LIST The operation failed because a draw call
	within the command list uses a region clip outside the bounds of the scene valid region.
	@retval
	SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION The operation failed because a draw call
	within the command list using a depth test, stencil test or mask update is not supported
	by the store depth/stencil buffer.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_BUFFER_POINTER The operation failed because
	visibility testing is used by draw calls within the command list, but the
	visibility buffer pointer is <c>NULL</c>.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_VISIBILITY_INDEX The operation failed because visibility
	testing, which uses a visibility index that is greater than the maximum value supported
	by the visibility buffer stride, is used by draw calls within the command list.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_OUTPUT_REGISTER_SIZE The operation failed because
	there is a output register size mismatch between a fragment program
	used by draw calls within the command list and the color surface.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_FRAGMENT_MSAA_MODE The operation failed because there is
	a MSAA usage mismatch between a fragment program used by draw calls within
	the command list and the render target.  This error can only occur for
	fragment programs that read the output register to perform blending operations,
	and it is only returned when running the debug version of libgxm.

	@ingroup render
 */
SceGxmErrorCode sceGxmExecuteCommandList(
	SceGxmContext *immediateContext,
	SceGxmCommandList *commandList);

/** A helper function that internally calls #sceGxmSetRegionClip() and
	#sceGxmSetViewport() to cover a rectangular region from (0,0) to
	(xMax,yMax).

	This function is provided for convenience, and it allows deferred contexts to set
	the region clip and viewport to the same values that would be set up
	by #sceGxmBeginScene() on the immediate context. It is equivalent to calling:

	@code
	uint32_t xMin = 0, yMin = 0;
	sceGxmSetRegionClip(context, SCE_GXM_REGION_CLIP_OUTSIDE, xMin, yMin, xMax, yMax);
	sceGxmSetViewport(
		context,
		0.5f*(float)(1 + xMax + xMin),
		0.5f*(float)(1 + xMax - xMin),
		0.5f*(float)(1 + yMax + yMin),
		-0.5f*(float)(1 + yMax - yMin),
		0.5f,
		0.5f);
	@endcode

	This function is called automatically for immediate contexts as part
	of the implementation of #sceGxmBeginScene().

	@param[in,out]	context		A pointer to a rendering context.
	@param[in]		xMax		The inclusive maximum x value of the rectangle in pixels.
	@param[in]		yMax		The inclusive maximum y value of the rectangle in pixels.

	@ingroup render
*/
void sceGxmSetDefaultRegionClipAndViewport(
	SceGxmContext *context,
	uint32_t xMax,
	uint32_t yMax);

/** Gets the current write address within the VDM buffer of a deferred context.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	This function is only supported when the deferred context is not currently
	building a command list.  Calling this function within a command list will
	the result in the #SCE_GXM_ERROR_WITHIN_COMMAND_LIST error code being returned.

	@param[in]		deferredContext		A pointer to a deferred context.
	@param[out]		mem					Receives the current VDM buffer write address.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>deferredContext</i></c>
	parameter does not point to a deferred context.
	@retval
	SCE_GXM_ERROR_WITHIN_COMMAND_LIST The operation failed because the deferred context
	is already within a command list.

	@ingroup render
*/

SceGxmErrorCode sceGxmGetDeferredContextVdmBuffer(
	const SceGxmContext *deferredContext,
	void **mem);

/** Sets a new VDM buffer for a deferred context.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	This function is only supported when the deferred context is not currently
	building a command list.  Calling this function within a command list will result in
	the #SCE_GXM_ERROR_WITHIN_COMMAND_LIST error code being returned.

	Setting a <c>NULL</c> base address with a buffer size of zero is supported.  If these settings are
	used, this will, while the next command list is being constructed, result in the callback function
	being called the first time memory is required for this buffer.	 If the <c><i>size</i></c> parameter
	is non-zero, it must be a minimum of #SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE bytes.

	@param[in,out]	deferredContext		A pointer to a deferred context.
	@param[in]		mem					The base address of the buffer. This should be aligned to 4 bytes.
										Set to <c>NULL</c> if memory is to be allocated as required via a callback.
	@param[in]		size				The size of the buffer. This should be aligned to 4 bytes.
										Set to 0 if memory is to be allocated as required via a callback.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the pointer to the deferred context was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>deferredContext</i></c> parameter
	does not point to a deferred context, or there is inconsistency in the values supplied to either <c><i>mem</i></c>
	or <c><i>size</i></c>.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because an invalid address was supplied, or there was
	a size alignment issue.
	@retval
	SCE_GXM_ERROR_WITHIN_COMMAND_LIST The operation failed because the deferred context
	is already within a command list.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetDeferredContextVdmBuffer(
	SceGxmContext *deferredContext,
	void *mem,
	uint32_t size);

/** Gets the current write address within the vertex buffer of a deferred context.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	This function is only supported when the deferred context is not currently
	building a command list.  Calling this function within a command list will result in
	the #SCE_GXM_ERROR_WITHIN_COMMAND_LIST error code being returned.

	@param[in]		deferredContext		A pointer to a deferred context.
	@param[out]		mem					Receives the current vertex buffer write address.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was set to <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>deferredContext</i></c>
	parameter does not point to a deferred context.
	@retval
	SCE_GXM_ERROR_WITHIN_COMMAND_LIST The operation failed because the deferred context
	is already within a command list.

	@ingroup render
*/

SceGxmErrorCode sceGxmGetDeferredContextVertexBuffer(
	const SceGxmContext *deferredContext,
	void **mem);

/** Sets a new vertex buffer for a deferred context.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	This function is only supported when the deferred context is not currently
	building a command list.  Calling this function within a command list will result in
	the #SCE_GXM_ERROR_WITHIN_COMMAND_LIST error code being returned.

	Setting a <c>NULL</c> base address with a buffer size of zero is supported.  If these settings are
	used, this will, while the next command list is being constructed, result in the callback function
	being called the first time memory is required for this buffer.	 If the <c><i>size</i></c> parameter
	is non-zero, it must be a minimum of #SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE bytes.

	@param[in,out]	deferredContext		A pointer to a deferred context.
	@param[in]		mem					The base address of the buffer. This should be aligned to 4 bytes.
										Set to <c>NULL</c> if memory is to be allocated as required via a callback.
	@param[in]		size				The size of the memory. This should be aligned to 4 bytes.
										Set to 0 if memory is to be allocated as required via a callback.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the pointer to the deferred context was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>deferredContext</i></c> parameter
	does not point to a deferred context, or there is inconsistency in the values supplied to either <c><i>mem</i></c>
	or <c><i>size</i></c>.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because an invalid address was supplied, or there was
	a size alignment issue.
	@retval
	SCE_GXM_ERROR_WITHIN_COMMAND_LIST The operation failed because the deferred context
	is already within a command list.


	@ingroup render
*/
SceGxmErrorCode sceGxmSetDeferredContextVertexBuffer(
	SceGxmContext *deferredContext,
	void *mem,
	uint32_t size);

/** Gets the current write address within the fragment buffer of a deferred context.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	This function is only supported when the deferred context is not currently
	building a command list.  Calling this function within a command list will result
	in the #SCE_GXM_ERROR_WITHIN_COMMAND_LIST error code being returned.

	@param[in]		deferredContext		A pointer to a deferred context.
	@param[out]		mem					Receives the current fragment buffer write address.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>deferredContext</i></c>
	parameter does not point to a deferred context.
	@retval
	SCE_GXM_ERROR_WITHIN_COMMAND_LIST The operation failed because the deferred context
	is already within a command list.

	@ingroup render
*/
SceGxmErrorCode sceGxmGetDeferredContextFragmentBuffer(
	const SceGxmContext *deferredContext,
	void **mem);

/** Sets a new fragment buffer for a deferred context.

	This function is only supported on a deferred context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using the immediate context.

	This function is only supported when the deferred context is not currently
	building a command list.  Calling this function within a command list will result
	in the #SCE_GXM_ERROR_WITHIN_COMMAND_LIST error code being returned.

	Setting a <c>NULL</c> base address with a buffer size of zero is supported. If these settings are
	used, this will, while the next command list is being constructed, result in the callback function
	being called the first time memory is required for this buffer.	If the <c><i>size</i></c> parameter
	is non-zero, it must be a minimum of #SCE_GXM_MINIMUM_DEFERRED_CONTEXT_BUFFER_SIZE bytes.

	@param[in,out]	deferredContext		A pointer to a deferred context.
	@param[in]		mem					The base address of the buffer. This should be aligned to 4 bytes.
										Set to <c>NULL</c> if memory is to be allocated as required via a callback.
	@param[in]		size				The size of the memory. This should be aligned to 4 bytes.
										Set to 0 if memory is to be allocated as required via a callback.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because the pointer to the deferred context was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the <c><i>deferredContext</i></c> parameter
	does not point to a deferred context, or there is inconsistency in the values supplied to either <c><i>mem</i></c>
	or <c><i>size</i></c>.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because an invalid address was supplied, or there was
	a size alignment issue.
	@retval
	SCE_GXM_ERROR_WITHIN_COMMAND_LIST The operation failed because the deferred context
	is already within a command list.


	@ingroup render
*/
SceGxmErrorCode sceGxmSetDeferredContextFragmentBuffer(
	SceGxmContext *deferredContext,
	void *mem,
	uint32_t size);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_CONTEXT_H_ */
