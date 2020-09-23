#ifndef _DOLCESDK_PSP2_GXM_STRUCTS_H_
#define _DOLCESDK_PSP2_GXM_STRUCTS_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/constants.h>
#include <psp2/gxm/defs.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The opaque structure for render targets.

	@ingroup render
*/
typedef struct SceGxmRenderTarget SceGxmRenderTarget;

/** The opaque structure for sync objects.

	@ingroup render
*/
typedef struct SceGxmSyncObject SceGxmSyncObject;

/**	A vertex attribute descriptor.

	A vertex attribute is either typed or untyped.  Typed attributes are unpacked
	to float4 format for the shader code, and must specify between 1 and 4 scalar
	components in the <c><i>componentCount</i></c> field.  Untyped attributes may only
	be used with attributes that are unpacked in shader code explicitly (using
	the <c>__regformat</c> keyword), and may specify between 1 and 255 32-bit
	words of untyped data in the <c><i>componentCount</i></c> field.

	Vertex attributes are fetched in units of 32-bit words even if the address
	of the vertex attribute data is not aligned to 4 bytes.  Because of this, additional
	data may be fetched after the attribute data in order to align the fetched size up to
	a whole number of 32-bit words.  To ensure that this overfetch does not result
	in unexpected GPU page faults, vertex data should not be placed in the last
	#SCE_GXM_MAX_ATTRIBUTE_OVERFETCH bytes of GPU mapped memory.

	@ingroup render
*/
typedef struct SceGxmVertexAttribute {
	uint16_t streamIndex;		///< The index within the stream array.
	uint16_t offset;			///< The byte offset from the start of each vertex.
	uint8_t format;				///< The data type for each scalar from #SceGxmAttributeFormat.
	uint8_t componentCount;		///< The number of components of typed data or the number of 32-bit words of untyped data.
	uint16_t regIndex;			///< The PA register start index.
} SceGxmVertexAttribute;

/** A vertex stream descriptor.

	@ingroup render
*/
typedef struct SceGxmVertexStream {
	uint16_t stride;		///< The byte stride between each vertex. A zero stride can be used to specify constant streams.
	uint16_t indexSource;	///< Defines how the stream is indexed from #SceGxmIndexSource.
} SceGxmVertexStream;

/** Direct representation of texture control words.

	Textures are fully described by the four 32-bit words of data associated with a
	PDS DOUTT instruction. They can be defined by using the libgxm texture API or by using
	the defines in <c>gxm\texture_defs.h</c>.  Please see the <em>GPU User’s Guide</em> for
	more details.

	Texture control words can be validated in libgxm using #sceGxmTextureValidate().

	@ingroup render
*/
typedef struct SceGxmTexture {
	uint32_t controlWords[SCE_GXM_NUM_TEXTURE_CONTROL_WORDS];	///< Texture control words.
} SceGxmTexture;

/** Represents the destination for tile values.

	@note Must only be modified using provided API calls.

	@ingroup render
*/
typedef struct SceGxmColorSurface {
	uint32_t pbeSidebandWord;								///< An opaque sideband word.
	uint32_t pbeEmitWords[SCE_GXM_PBE_EMIT_WORD_COUNT];		///< Opaque emit words.
	uint32_t outputRegisterSize;							///< Output register size.
	SceGxmTexture backgroundTex;							///< Precomputed background object texture control words.
} SceGxmColorSurface;

#if !defined(_LP64) && !defined(_M_X64)

/** Controls how depth and stencil values are loaded from memory at the
	start of each tile, and how they are saved to memory at the end of each tile.

	@note Must only be modified using provided API calls.

	@ingroup render
*/
typedef struct SceGxmDepthStencilSurface {
	uint32_t zlsControl;			///< An opaque control word.
	void *depthData;				///< A pointer to the depth data or <c>NULL</c>.
	void *stencilData;				///< A pointer to the stencil data or <c>NULL</c>.
	float backgroundDepth;			///< The 32-bit floating point background object depth value.
	uint32_t backgroundControl;		///< An opaque background object control register.
} SceGxmDepthStencilSurface;

/** This struct describes a GPU notification, which occurs when a scene completes on
	either the vertex or fragment pipeline.

	These notifications must use addresses within the notification region allocated
	at initialization time. Once libgxm has been initialized, the base address of the
	region can be queried using #sceGxmGetNotificationRegion().

	@ingroup render
*/
typedef struct SceGxmNotification {
	volatile uint32_t *address;		///< The address that will be written to by the GPU.
	uint32_t value;					///< The 32-bit value that will be written.
} SceGxmNotification;

#endif // !defined(_LP64) && !defined(_M_X64)

/** Represents a rectangular region from 0,0 to xMax,yMax (inclusive). This structure is for
	use as the optional <c><i>validRegion</i></c> parameter to #sceGxmBeginScene().

	Although the region is provided in pixels, this will be internally aligned to
	tile granularity for the hardware.

	@ingroup render
*/
typedef struct SceGxmValidRegion {
	uint32_t xMax;					///< The maximum x value in pixels.
	uint32_t yMax;					///< The maximum y value in pixels.
} SceGxmValidRegion;

/** Represents a group of draw calls built up using a deferred
	context.

	@ingroup render
 */
typedef struct SceGxmCommandList {
	uint32_t data[SCE_GXM_COMMAND_LIST_WORD_COUNT];		///< Opaque contents.
} SceGxmCommandList;

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_STRUCTS_H_ */
