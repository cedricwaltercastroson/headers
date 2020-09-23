#ifndef _DOLCESDK_PSP2_GXM_ERROR_H_
#define _DOLCESDK_PSP2_GXM_ERROR_H_

/** @file
*/

#include <psp2/error.h>
#include <psp2/types.h>

/** A typedef to clarify when a return value is an error code.

	@ingroup render
*/
typedef int32_t SceGxmErrorCode;

/** The call failed because the library is uninitialized

	@ingroup render
*/
#define	SCE_GXM_ERROR_UNINITIALIZED							-2141519872		/* 0x805B0000 */

/** The call failed because the library is already initialized.

	@ingroup render
*/
#define	SCE_GXM_ERROR_ALREADY_INITIALIZED					-2141519871		/* 0x805B0001 */

/** The call failed because a memory allocation failed.

	@ingroup render
*/
#define	SCE_GXM_ERROR_OUT_OF_MEMORY							-2141519870		/* 0x805B0002 */

/** The call failed because a parameter has an invalid value.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_VALUE							-2141519869		/* 0x805B0003 */

/** The call failed because a pointer has an invalid value.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_POINTER						-2141519868		/* 0x805B0004 */

/** The call failed because a parameter is incorrectly aligned.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_ALIGNMENT						-2141519867		/* 0x805B0005 */

/** The call failed because the rendering context is currently not within a scene.

	@ingroup render
*/
#define	SCE_GXM_ERROR_NOT_WITHIN_SCENE						-2141519866		/* 0x805B0006 */

/** The call failed because the rendering context is currently within a scene.

	@ingroup render
*/
#define	SCE_GXM_ERROR_WITHIN_SCENE							-2141519865		/* 0x805B0007 */

/** The call failed because the rendering context currently has a <c>NULL</c> program set.

	@ingroup render
*/
#define	SCE_GXM_ERROR_NULL_PROGRAM							-2141519864		/* 0x805B0008 */

/** The call failed because the operation is not supported on this hardware.

	@ingroup render
*/
#define	SCE_GXM_ERROR_UNSUPPORTED							-2141519863		/* 0x805B0009 */

/** The call failed because the internal patching process failed.

	@ingroup render
*/
#define SCE_GXM_ERROR_PATCHER_INTERNAL						-2141519862		/* 0x805B000A */

/** The call failed because a buffer failed to reserve space for data.

	@ingroup render
*/
#define	SCE_GXM_ERROR_RESERVE_FAILED						-2141519861		/* 0x805B000B */

/** The call failed because a program from the shader patcher is still in use.

	@ingroup render
*/
#define	SCE_GXM_ERROR_PROGRAM_IN_USE						-2141519860		/* 0x805B000C */

/** The call failed because an invalid index count was supplied.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_INDEX_COUNT					-2141519859		/* 0x805B000D */

/** The call failed because an invalid polygon mode was supplied for the selected primitive type.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_POLYGON_MODE					-2141519858		/* 0x805B000E */

/** The call failed because the precision of the texture query format is not
	supported by the texture format being used.  For example, the texture
	query could be expecting half precision but the texture format only
	supports float precision. The list of supported query formats for each
	texture format is available in the <em>GPU User’s Guide</em> documentation.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_PRECISION	-2141519857		/* 0x805B000F */

/** The call failed because the component count of the texture query format
	does not match the swizzle of the texture format being used.  For example,
	the texture query could be expecting 4 components, but the texture format
	could be using a swizzle that returns only 1 component.  The list of
	supported query formats and swizzles for each texture format is available
	in the <em>GPU User’s Guide</em> documentation.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_SAMPLER_RESULT_TYPE_COMPONENT_COUNT	-2141519856		/* 0x805B0010 */

/** The call failed because the uniform buffer has not been reserved.

	@ingroup render
*/
#define	SCE_GXM_ERROR_UNIFORM_BUFFER_NOT_RESERVED			-2141519855		/* 0x805B0011 */

/** The call failed because the precomputed draw call was created for a different
	vertex program than the current vertex program.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_PRECOMPUTED_DRAW				-2141519852	/* 0x805B0014 */

/** The call failed because the precomputed vertex state was created for a different
	vertex program than the current vertex program.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_PRECOMPUTED_VERTEX_STATE		-2141519851	/* 0x805B0015 */

/** The call failed because the precomputed fragment state was created for a different
	fragment program than the current fragment program.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_PRECOMPUTED_FRAGMENT_STATE	-2141519850	/* 0x805B0016 */

/** The call failed because of a driver error.

	@ingroup render
*/
#define	SCE_GXM_ERROR_DRIVER								-2141519849	/* 0x805B0017 */

/** The call failed because it was called from the display queue thread.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_THREAD						-2141519848	/* 0x805B0018 */

/** The call failed because an invalid texture data pointer was supplied.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_TEXTURE_DATA_POINTER			-2141519847	/* 0x805B0019 */

/** The call failed because an invalid texture palette pointer was supplied.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_TEXTURE_PALETTE_POINTER		-2141519846	/* 0x805B001A */

/** The call failed because of a mismatch between fragment program and color
	surface output register sizes.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_OUTPUT_REGISTER_SIZE			-2141519845	/* 0x805B001B */

/** The call failed because of a mismatch between fragment program and render
	target MSAA usage.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_FRAGMENT_MSAA_MODE			-2141519844	/* 0x805B001C */

/** The call failed because an invalid visibility buffer pointer was supplied.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_VISIBILITY_BUFFER_POINTER		-2141519843	/* 0x805B001D */

/** The call failed because an invalid visibility index was supplied.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_VISIBILITY_INDEX				-2141519842	/* 0x805B001E */

/** The call failed because of an invalid depth/stencil configuration.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_DEPTH_STENCIL_CONFIGURATION	-2141519841	/* 0x805B001F */

/** The call failed because an invalid texture was supplied.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_TEXTURE						-2141519840	/* 0x805B0020 */

/** The call failed because a shader patcher host memory allocation failed.

	@ingroup render
*/
#define	SCE_GXM_ERROR_OUT_OF_HOST_MEMORY					-2141519839	/* 0x805B0021 */

/** The call failed because a shader patcher buffer memory allocation failed.

	@ingroup render
*/
#define	SCE_GXM_ERROR_OUT_OF_BUFFER_MEMORY					-2141519838	/* 0x805B0022 */

/** The call failed because a shader patcher vertex USSE memory allocation failed.

	@ingroup render
*/
#define	SCE_GXM_ERROR_OUT_OF_VERTEX_USSE_MEMORY				-2141519837	/* 0x805B0023 */

/** The call failed because a shader patcher fragment USSE memory allocation failed.

	@ingroup render
*/
#define	SCE_GXM_ERROR_OUT_OF_FRAGMENT_USSE_MEMORY			-2141519836	/* 0x805B0024 */

/** The call failed because an invalid primitive type was supplied.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_PRIMITIVE_TYPE				-2141519835	/* 0x805B0025 */

/** The call failed because memory was not mapped or was mapped with incorrect
	attributes.

	@ingroup render
*/
#define SCE_GXM_ERROR_INVALID_MAPPING						-2141519834 /* 0x805B0026 */

/** The call failed because the maximum number of render targets have already been created.

	@ingroup render
*/
#define SCE_GXM_ERROR_OUT_OF_RENDER_TARGETS					-2141519833 /* 0x805B0027 */

/** The call failed because an invalid visibility operation was used.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_VISIBILITY_OP					-2141519832	/* 0x805B0028 */

/** The call failed because of a Razor error.

	@ingroup render
*/
#define	SCE_GXM_ERROR_RAZOR									-2141519831	/* 0x805B0029 */

/** The call failed because the filtering mode required for the texture query is not
	compatible with the filtering mode set on the texture being used. For example, this
	error code will be returned if a shadow map query is requested when the	texture
	filtering mode is not bilinear.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_INVALID_SAMPLER_FILTER_MODE			-2141519830	/* 0x805B002A */

/** The call failed because the draw calls within a command list use a region clip
	configuration that exceeds the scene valid region in the Y direction.  This
	configuration is not correctly handled by the GPU, so it must be avoided when
	building a command list.

	When using the region clip on the immediate context, this clamping operation is
	applied automatically to the Y coordinates to avoid this issue. On a deferred context,
	it is not possible to do the clamping operation automatically because the valid region
	that the resulting command list will be used with is unknown.

	@ingroup render
 */
#define SCE_GXM_ERROR_INVALID_REGION_CLIP_IN_COMMAND_LIST	-2141519829 /* 0x805B002B */

/** The call failed because the deferred context is currently within a command list.

	@ingroup render
*/
#define	SCE_GXM_ERROR_WITHIN_COMMAND_LIST					-2141519828 /* 0x805B002C */

/** The call failed because the deferred context is not currently within a command list.

	@ingroup render
*/
#define	SCE_GXM_ERROR_NOT_WITHIN_COMMAND_LIST				-2141519827 /* 0x805B002D */

/** The call failed because the memory directly after the default uniform buffer reservation was
	modified between the reserve call and the draw call.  This indicates a memory overrun
	when writing the default uniform buffer contents.

	@note This error code is only returned when running the debug version of libgxm.

	@ingroup render
*/
#define	SCE_GXM_ERROR_BUFFER_OVERRUN						-2141519826 /* 0x805B002E */

#endif /* _DOLCESDK_PSP2_GXM_ERROR_H_ */

