#ifndef _DOLCESDK_PSP2_GXM_DEFS_H_
#define _DOLCESDK_PSP2_GXM_DEFS_H_

/** The left-shift to apply to go from tile units to pixel units
	in the x dimension.

	@ingroup render
*/
#define SCE_GXM_TILE_SHIFTX							5U

/** The left-shift to apply to go from tile units to pixel units
	in the y dimension.

	@ingroup render
*/
#define SCE_GXM_TILE_SHIFTY							5U

/** The size of a tile in memory in the x dimension.

	@ingroup render
*/
#define SCE_GXM_TILE_SIZEX							(1U << SCE_GXM_TILE_SHIFTX)

/** The size of a tile in memory in the y dimension.

	@ingroup render
*/
#define SCE_GXM_TILE_SIZEY							(1U << SCE_GXM_TILE_SHIFTY)

/** The number of 32-bit words required to describe how a tile is emitted to memory.

	@ingroup render
*/
#define SCE_GXM_PBE_EMIT_WORD_COUNT					6U

/** Overfetch may occur due to the DMA fetch for an attribute being rounded up to the
	next multiple of 4 bytes. This value is the largest amount of overfetch that can occur when
	fetching the last attribute of the last vertex of a vertex stream. If the size of all
	attributes is aligned to 4 bytes, then overfetch cannot occur.

	@ingroup render
*/
#define	SCE_GXM_MAX_ATTRIBUTE_OVERFETCH				3U

/** The number of 32-bit words required to describe a texture.

	@ingroup render
*/
#define SCE_GXM_NUM_TEXTURE_CONTROL_WORDS			4U

/** The minimum alignment of texture data that satisfies the
	alignment requirements of all supported texture formats.

	When a specific texture format is being used, the required
	alignment may be less than this value. For details on
	each format’s alignment requirement, please see the
	<em>GPU User’s Guide</em>.

	@ingroup render
*/
#define SCE_GXM_TEXTURE_ALIGNMENT					16U

/** The minimum alignment of palette data.

	@ingroup render
*/
#define	SCE_GXM_PALETTE_ALIGNMENT					64U

/** The minimum alignment of color surface data.

	@ingroup render
*/
#define SCE_GXM_COLOR_SURFACE_ALIGNMENT				4U

/** The minimum alignment of depth or stencil data.

	@ingroup render
*/
#define SCE_GXM_DEPTHSTENCIL_SURFACE_ALIGNMENT		16U

/** The minimum alignment of the space between cube map faces when
	each face has a mip chain, and the length of the top level mip of
	each face is above the “no align” size.

	The “no align” size will be either
	#SCE_GXM_TEXTURE_CUBE_NO_ALIGN_SIZE_8BPP or
	#SCE_GXM_TEXTURE_CUBE_NO_ALIGN_SIZE_16_32BPP or
	#SCE_GXM_TEXTURE_CUBE_NO_ALIGN_SIZE_64BPP depending on the texture
	format of the cube map data.

	There is no padding between cube map faces for cubemaps less than
	or equal to the “no align” size.

	@ingroup render
*/
#define SCE_GXM_TEXTURE_FACE_ALIGNMENT				2048U

/** The largest cube face size where the space between each cube map face
	mip chain does <b>not</b> need to be aligned to
	#SCE_GXM_TEXTURE_FACE_ALIGNMENT bytes.

	This size applies to cube maps of 8 bits per pixel, or cube maps that
	use block compression.

	@ingroup render
*/
#define SCE_GXM_TEXTURE_CUBE_NO_ALIGN_SIZE_8BPP		16U

/** The largest cube face size where the space between each cube map face
	mip chain does <b>not</b> need to be aligned to
	#SCE_GXM_TEXTURE_FACE_ALIGNMENT bytes.

	This size applies to cube maps of 16 or 32 bits per pixel.

	@ingroup render
*/
#define SCE_GXM_TEXTURE_CUBE_NO_ALIGN_SIZE_16_32BPP	8U

/** The largest cube face size where the space between each cube map face
	mip chain does <b>not</b> need to be aligned to
	#SCE_GXM_TEXTURE_FACE_ALIGNMENT bytes.

	This size applies to cube maps of 64 bits per pixel.

	@ingroup render
*/
#define SCE_GXM_TEXTURE_CUBE_NO_ALIGN_SIZE_64BPP	4U

/** When using linear textures with implicit stride, the stride is formed
	by aligning the width to this value.

	@ingroup render
*/
#define SCE_GXM_TEXTURE_IMPLICIT_STRIDE_ALIGNMENT	8U

/** A mask used to extract the base texture format from a #SceGxmTextureFormat
	value.

	@ingroup render
*/
#define SCE_GXM_TEXTURE_BASE_FORMAT_MASK			0x9f000000U

/** A mask used to extract swizzle information from a #SceGxmTextureFormat
	value.

	@ingroup render
*/
#define	SCE_GXM_TEXTURE_SWIZZLE_MASK				0x00007000U

/** A mask used to extract the base color format from a #SceGxmColorFormat
	value.

	@ingroup render
*/
#define	SCE_GXM_COLOR_BASE_FORMAT_MASK				0xf1800000U

/** A mask used to extract swizzle information from a #SceGxmColorFormat
	value.

	@ingroup render
*/
#define	SCE_GXM_COLOR_SWIZZLE_MASK					0x00300000U

/** The alignment required for memory that is used for precomputed data.

	@ingroup render
*/
#define SCE_GXM_PRECOMPUTED_ALIGNMENT				16U

/** The number of GPU cores present on the system.

	@ingroup render
*/
#define SCE_GXM_GPU_CORE_COUNT						4U

/** The alignment required for USSE programs.

	@ingroup render
*/
#define SCE_GXM_USSE_ALIGNMENT						16U

/** The alignment required for visibility buffers.

	@ingroup render
*/
#define SCE_GXM_VISIBILITY_ALIGNMENT				16U

/** The maximum number of scenes per render target per frame.

	@ingroup render
*/
#define SCE_GXM_MAX_SCENES_PER_RENDERTARGET			8U

/** The maximum number of render targets that can be created.

	@ingroup render
*/
#define SCE_GXM_MAX_RENDER_TARGETS					48U

/** The number of 32-bit words used to describe a command list.

	@ingroup render
 */
#define SCE_GXM_COMMAND_LIST_WORD_COUNT				8U

#endif /* _DOLCESDK_PSP2_GXM_DEFS_H_ */
