#ifndef _DOLCESDK_PSP2_GXM_PRECOMPUTATION_H_
#define _DOLCESDK_PSP2_GXM_PRECOMPUTATION_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/structs.h>
#include <psp2/gxm/vertex_program.h>
#include <psp2/gxm/fragment_program.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The number of opaque 32-bit words in precomputed vertex state.

	@ingroup render
*/
#define SCE_GXM_PRECOMPUTED_VERTEX_STATE_WORD_COUNT		7

/** The number of opaque 32-bit words in precomputed fragment state.

	@ingroup render
*/
#define SCE_GXM_PRECOMPUTED_FRAGMENT_STATE_WORD_COUNT	9

/** The number of opaque 32-bit words in a precomputed draw command.

	@ingroup render
*/
#define SCE_GXM_PRECOMPUTED_DRAW_WORD_COUNT				11

/** The precomputed vertex state.  Allows for vertex secondary updates to be
	precomputed, which reduces CPU overheads.

	@ingroup render
*/
typedef struct SceGxmPrecomputedVertexState {
	uint32_t data[SCE_GXM_PRECOMPUTED_VERTEX_STATE_WORD_COUNT];		///< Opaque contents.
} SceGxmPrecomputedVertexState;

/** The precomputed fragment state.  Allows for fragment secondary and primary updates
	to be precomputed, which reduces CPU overheads.

	@ingroup render
*/
typedef struct SceGxmPrecomputedFragmentState {
	uint32_t data[SCE_GXM_PRECOMPUTED_FRAGMENT_STATE_WORD_COUNT];	///< Opaque contents.
} SceGxmPrecomputedFragmentState;

/** The precomputed draw command.  Allows for a draw call to be done using precomputed
	data, which reduces CPU overheads.

	@ingroup render
*/
typedef struct SceGxmPrecomputedDraw {
	uint32_t data[SCE_GXM_PRECOMPUTED_DRAW_WORD_COUNT];				///< Opaque contents.
} SceGxmPrecomputedDraw;

/** Computes the amount of memory needed for precomputed vertex state for the
	given vertex program.

	@param[in]	vertexProgram	A pointer to the vertex program.
	@return
	The size in bytes of the vertex program state.

	@ingroup render
*/
uint32_t sceGxmGetPrecomputedVertexStateSize(
	const SceGxmVertexProgram *vertexProgram);

/** Initializes precomputed vertex state using the given memory.

	The memory supplied to this function via <c><i>memBlock</i></c> should be aligned
	to #SCE_GXM_PRECOMPUTED_ALIGNMENT.  The size of the memory should be at least that returned by
	#sceGxmGetPrecomputedVertexStateSize().  The memory must be mapped for the
	GPU with at least read access.

	This memory is used to store precomputed data structures to upload vertex
	program uniforms and texture state for future draw calls.  The memory does
	not contain the default uniform buffer.  If the vertex program requires a
	default uniform buffer, then one should be allocated separately and
	assigned using #sceGxmPrecomputedVertexStateSetDefaultUniformBuffer().

	@param[out]	precomputedState	A pointer to the precomputed state.
	@param[in]	vertexProgram		A pointer to the vertex program. This must persist for the
									lifetime of the #SceGxmPrecomputedVertexState structure.
	@param[out]	memBlock			A pointer to a block of memory to use for precomputed data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because one or more of the pointers were not aligned.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedVertexStateInit(
	SceGxmPrecomputedVertexState *precomputedState,
	const SceGxmVertexProgram *vertexProgram,
	void *memBlock);

/** Sets the default uniform buffer for the precomputed vertex state.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		defaultBuffer		A pointer to the default uniform buffer data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedVertexStateSetDefaultUniformBuffer(
	SceGxmPrecomputedVertexState *precomputedState,
	const void *defaultBuffer);

/** Gets the default uniform buffer for the precomputed vertex state.

	@param[in]	precomputedState		A pointer to the precomputed state.
	@return
	A pointer to the default uniform buffer.

	@ingroup render
*/
void *sceGxmPrecomputedVertexStateGetDefaultUniformBuffer(
	const SceGxmPrecomputedVertexState *precomputedState);

/** Sets all the textures for the precomputed vertex state.  The textures will be accessed
	within this array using their sampler resource index (i.e. the TEXUNITn binding
	in the shader source code).  This implementation is more efficient than setting every
	texture individually using #sceGxmPrecomputedVertexStateSetTexture().

	Note that it is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		textureArray		A pointer to the texture array. The structures are copied
										during this function and therefore do not need to persist after the
										call.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The format of one of the textures is not supported as a vertex texture.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_PRECISION The operation failed
	because one of the textures does not support the precision of a query format
	used in shader code. This error is only returned when running the debug version of libgxm.
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
	a texture has a <c>NULL</c> data pointer. This error is only returned when running
	the debug version of libgxm.

	@note Textures whose formats are based on #SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2,
	#SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3, #SCE_GXM_TEXTURE_BASE_FORMAT_YUV422,
	#SCE_GXM_TEXTURE_BASE_FORMAT_P4 and #SCE_GXM_TEXTURE_BASE_FORMAT_P8 are not supported
	for use as vertex textures.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedVertexStateSetAllTextures(
	SceGxmPrecomputedVertexState *precomputedState,
	const SceGxmTexture *textureArray);

/** Sets a single texture for the precomputed vertex state.  This function is convenient when
	changing a single texture.  However, calling this function multiple times to set multiple textures
	is not as efficient as calling #sceGxmPrecomputedVertexStateSetAllTextures() once.

	Note that it is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		textureIndex		The <c>TEXUNIT</c> index to set the texture as.
	@param[in]		texture				A pointer to the texture. The structure is copied
										during this function and therefore do not need to persist after the
										call.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The texture index was not valid.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The format of one of the textures is not supported as a vertex texture.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_PRECISION The operation failed
	because the texture does not support the precision of a query format used
	in shader code. This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_COMPONENT_COUNT The operation
	failed because the texture is using a swizzle that produces an incorrect
	number of components for the query formats used in the shader code. This error is
	only returned when running the debug version of libgxm.
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
	the texture has a <c>NULL</c> data pointer. This error is only returned when running
	the debug version of libgxm.

	@note Textures whose formats are based on #SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2,
	#SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3, #SCE_GXM_TEXTURE_BASE_FORMAT_YUV422,
	#SCE_GXM_TEXTURE_BASE_FORMAT_P4 and #SCE_GXM_TEXTURE_BASE_FORMAT_P8 are not supported
	for use as vertex textures.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedVertexStateSetTexture(
	SceGxmPrecomputedVertexState *precomputedState,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

/** Sets all the uniform buffers for the precomputed vertex state.  The buffer addresses will
	be accessed within this array using their buffer index (i.e. the <c>BUFFER<i>n</i></c> binding
	in the shader source code).  This implementation is more efficient than setting every
	uniform buffer individually.

	Note that it is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		bufferDataArray		An array of pointers to uniform buffer data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.


	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedVertexStateSetAllUniformBuffers(
	SceGxmPrecomputedVertexState *precomputedState,
	const void *const *bufferDataArray);

/** Sets a single uniform buffer for the precomputed vertex state.  This function is convenient when
	changing a single uniform buffer.  However, calling this function multiple times to set multiple uniform buffers
	is not as efficient as calling #sceGxmPrecomputedVertexStateSetAllUniformBuffers() once.

	Note that it is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		bufferIndex			The buffer index to set the base address for.
	@param[in]		bufferData			A pointer to the uniform buffer data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The buffer index was not valid.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedVertexStateSetUniformBuffer(
	SceGxmPrecomputedVertexState *precomputedState,
	uint32_t bufferIndex,
	const void *bufferData);

/** Computes the amount of memory needed for precomputed fragment state for
	the given fragment program.

	@param[in]	fragmentProgram		A pointer to the fragment program.
	@return
	The size of the state in bytes.

	@ingroup render
*/
uint32_t sceGxmGetPrecomputedFragmentStateSize(
	const SceGxmFragmentProgram *fragmentProgram);

/** Initializes precomputed fragment state using the given memory.

	The memory supplied to this function via <c><i>memBlock</i></c> should be aligned
	to #SCE_GXM_PRECOMPUTED_ALIGNMENT.  The size of the memory should be at least that returned by
	#sceGxmGetPrecomputedFragmentStateSize().  The memory must be mapped for the
	GPU with at least read access.

	This memory is used to store precomputed data structures to upload fragment
	program uniforms and texture state for future draw calls.  The memory does
	not contain the default uniform buffer.  If the fragment program requires a
	default uniform buffer, then one should be allocated separately and
	assigned using #sceGxmPrecomputedFragmentStateSetDefaultUniformBuffer().

	@param[out]	precomputedState		A pointer to the precomputed state.
	@param[in]	fragmentProgram			A pointer to the fragment program. This must persist for the
										lifetime of the #SceGxmPrecomputedFragmentState structure.
	@param[out]	memBlock				A pointer to a block of memory to use for precomputed data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because one or more of
	the pointers were not aligned.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed because the fragment program
	was a mask update fragment program, which is not supported.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedFragmentStateInit(
	SceGxmPrecomputedFragmentState *precomputedState,
	const SceGxmFragmentProgram *fragmentProgram,
	void *memBlock);

/** Sets the default uniform buffer for the precomputed fragment state.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		defaultBuffer		A pointer to the default uniform buffer data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedFragmentStateSetDefaultUniformBuffer(
	SceGxmPrecomputedFragmentState *precomputedState,
	const void *defaultBuffer);

/** Gets the default uniform buffer for the precomputed fragment state.

	@param[in]	precomputedState	The pointer to the precomputed state.
	@return
	A pointer to the default uniform buffer.

	@ingroup render
*/
void *sceGxmPrecomputedFragmentStateGetDefaultUniformBuffer(
	const SceGxmPrecomputedFragmentState *precomputedState);

/** Sets all the textures for the precomputed fragment state. The textures will be accessed
	within this array using their sampler resource index (i.e. the <c>TEXUNIT<i>n</i></c> binding
	in the shader source code). This implementation is more efficient than setting every
	texture individually.

	It is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to precomputed fragment state.
	@param[in]		textureArray		A pointer to the texture array. The structures are copied
										during this function and therefore do not need to persist after the
										call.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
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

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedFragmentStateSetAllTextures(
	SceGxmPrecomputedFragmentState *precomputedState,
	const SceGxmTexture *textureArray);

/** Sets a single texture for the precomputed fragment state.  This function is convenient when
	changing a single texture.  However, calling this function multiple times to set multiple textures
	is not as efficient as calling #sceGxmPrecomputedFragmentStateSetAllTextures() once.

	Note that it is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		textureIndex		The <c>TEXUNIT</c> index to set the texture as.
	@param[in]		texture				A pointer to the texture. The structure is copied
										during this function and therefore does not need to persist after the
										call.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The texture index was not valid.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_PRECISION The operation failed
	because the texture does not support the precision of a query format used
	in shader code.	This error is only returned when running the debug version
	of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_COMPONENT_COUNT The operation
	failed because the texture is using a swizzle that produces an incorrect
	number of components for the query formats used in the shader code. This
	error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_SAMPLER_FILTER_MODE The operation failed because one of
	the textures has a filtering mode that is incompatible with the query used
	in the shader code. This error is only returned when running the debug version
	of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_DATA_POINTER The operation failed because
	the texture has a <c>NULL</c> data pointer. This error is only returned
	when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE The operation failed because a texture was invalid.
	This can occur if the format or dimensionality of the texture is not compatible with
	its usage in the shader code, or the texture control words themselves are malformed.
	This error is only returned when running the debug version of libgxm.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_PALETTE_POINTER The operation failed because
	the palettized texture has a <c>NULL</c> palette pointer. This error is
	only returned when running the debug version of libgxm.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedFragmentStateSetTexture(
	SceGxmPrecomputedFragmentState *precomputedState,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

/** Sets all the uniform buffers for the precomputed fragment state.  The buffer addresses will
	be accessed within this array using their buffer index (i.e. the <c>BUFFER<i>n</i></c> binding
	in the shader source code).  This implementation is more efficient than setting every
	uniform buffer individually.

	Note that it is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		bufferDataArray		An array of pointers to uniform buffer data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedFragmentStateSetAllUniformBuffers(
	SceGxmPrecomputedFragmentState *precomputedState,
	const void *const *bufferDataArray);

/** Sets a single uniform buffer for the precomputed fragment state.  This function is convenient when
	changing a uniform buffer.  However, calling this function multiple times to set multiple uniform buffers
	is not as efficient as calling #sceGxmPrecomputedFragmentStateSetAllUniformBuffers() once.

	Note that it is the caller’s responsibility to ensure this precomputed state is not currently
	being used by the GPU while it is being patched.

	@param[in,out]	precomputedState	A pointer to the precomputed state.
	@param[in]		bufferIndex			The buffer index to set the base address for.
	@param[in]		bufferData			A pointer to the uniform buffer data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The buffer index was not valid.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedFragmentStateSetUniformBuffer(
	SceGxmPrecomputedFragmentState *precomputedState,
	uint32_t bufferIndex,
	const void *bufferData);

/** Computes the amount of memory needed for a precomputed draw for the
	given vertex program.

	@param[in]	vertexProgram		A pointer to the vertex program.
	@return
	The memory needed for the precomputed draw in bytes.

	@ingroup render
*/
uint32_t sceGxmGetPrecomputedDrawSize(
	const SceGxmVertexProgram *vertexProgram);

/** Initializes a precomputed draw command.

	The memory supplied to this function via <c><i>memBlock</i></c> should be aligned
	to #SCE_GXM_PRECOMPUTED_ALIGNMENT. The size of the memory should be at least that returned by
	#sceGxmGetPrecomputedDrawSize().  The memory must be mapped for the
	GPU with at least read access.

	This memory is used to store precomputed data structures to draw some
	geometry using particular vertex streams.

	Before this precomputed draw can be used, the function
	#sceGxmPrecomputedDrawSetAllVertexStreams() must be called to set the vertex
	streams.  Either the #sceGxmPrecomputedDrawSetParams() or the
	#sceGxmPrecomputedDrawSetParamsInstanced() function must also be called to set the
	parameters of the draw call.  The object can then be drawn by calling
	#sceGxmDrawPrecomputed() with a #SceGxmContext.

	@param[out]	precomputedDraw		A pointer to the precomputed state.
	@param[in]	vertexProgram		A pointer to the vertex program. This must persist for the
									lifetime of the #SceGxmPrecomputedDraw structure.
	@param[out]	memBlock			A pointer to a block of memory to use for precomputed data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because one or more of
	the pointers were not aligned.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedDrawInit(
	SceGxmPrecomputedDraw *precomputedDraw,
	const SceGxmVertexProgram *vertexProgram,
	void *memBlock);

/** Sets all vertex stream base addresses for the precomputed draw command.

	It is the caller’s responsibility to ensure the precomputed draw command is not
	currently being used by the GPU during patching.

	@param[in,out]	precomputedDraw		A pointer to precomputed draw command.
	@param[in]		streamDataArray		An array of stream base addresses.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedDrawSetAllVertexStreams(
	SceGxmPrecomputedDraw *precomputedDraw,
	const void *const *streamDataArray);

/** Sets a vertex stream base addresses for the precomputed draw command.

	It is the caller’s responsibility to ensure the precomputed draw command is not
	currently being used by the GPU during patching.

	@param[in,out]	precomputedDraw		A pointer to precomputed draw command.
	@param[in]		streamIndex			The index of the vertex stream.
	@param[in]		streamData			A pointer to the vertex stream data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE	The stream index was not valid.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedDrawSetVertexStream(
	SceGxmPrecomputedDraw *precomputedDraw,
	uint32_t streamIndex,
	const void *streamData);

/** Sets the parameters for the precomputed draw command.  It is the caller’s
	responsibility to ensure this object is not currently being used by the GPU.

	@param[in,out]	precomputedDraw		A pointer to the precomputed draw command.
	@param[in]		primType			The type of the primitive.
	@param[in]		indexType			The type of the index data in memory.
	@param[in]		indexData			A pointer to the index data.
	@param[in]		indexCount			The number of indices.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedDrawSetParams(
	SceGxmPrecomputedDraw *precomputedDraw,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount);

/** Sets the parameters for the precomputed instanced draw command.  It is the caller’s
	responsibility to ensure this object is not currently being used by the GPU.

	@param[in,out]	precomputedDraw		A pointer to the precomputed draw command.
	@param[in]		primType			The type of the primitive.
	@param[in]		indexType			The type of the index data in memory.
	@param[in]		indexData			A pointer to the index data.
	@param[in]		indexCount			The number of indices.
	@param[in]		indexWrap			The number of indices to draw for each instance.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of
	the pointers supplied was <c>NULL</c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmPrecomputedDrawSetParamsInstanced(
	SceGxmPrecomputedDraw *precomputedDraw,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount,
	uint32_t indexWrap);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_PRECOMPUTATION_H_ */
