/**
 * \usergroup{SceGxm}
 * \usage{psp2/gxm.h,SceGxm_stub}
 */

#include <psp2/types.h>

#ifndef _DOLCESDK_PSP2_GXM_STRUCTS_H_
#define _DOLCESDK_PSP2_GXM_STRUCTS_H_

#include <psp2/gxm/constants.h>
#include <psp2/gxm/functypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceGxmRenderTarget SceGxmRenderTarget;

typedef struct SceGxmSyncObject SceGxmSyncObject;

typedef struct SceGxmVertexAttribute {
	uint16_t streamIndex;		///< The index within the stream array.
	uint16_t offset;			///< The byte offset from the start of each vertex.
	uint8_t format;				///< The data type for each scalar from #SceGxmAttributeFormat.
	uint8_t componentCount;		///< The number of components of typed data or the number of 32-bit words of untyped data.
	uint16_t regIndex;			///< The PA register start index.
} SceGxmVertexAttribute;

typedef struct SceGxmVertexStream {
	uint16_t stride;		///< The byte stride between each vertex. A zero stride can be used to specify constant streams.
	uint16_t indexSource;	///< Defines how the stream is indexed from #SceGxmIndexSource.
} SceGxmVertexStream;

typedef struct SceGxmTexture {
	uint32_t controlWords[SCE_GXM_NUM_TEXTURE_CONTROL_WORDS];	///< Texture control words.
	/*
	// Control Word 0
	uint32_t unk0 : 1;                //!< Unknown field
	uint32_t stride_ext : 2;          //!< Stride extension for a LINEAR_STRIDED texture
	uint32_t vaddr_mode : 3;          //!< V Address Mode
	uint32_t uaddr_mode : 3;          //!< U Address Mode
	union {
		struct {
			uint32_t mip_filter : 1;  //!< Mip filter for a non LINEAR_STRIDED texture
			uint32_t min_filter : 2;  //!< Min filter for a non LINEAR_STRIDED texture)
		};
		uint32_t stride_low : 3;      //!< Internal stride lower bits for a LINEAR_STRIDED texture
	};
	uint32_t mag_filter : 2;          //!< Mag Filter (and Min filter if LINEAR_STRIDED texture)
	uint32_t unk1 : 3;                //!< Unknown field
	union {
		struct {
			uint32_t mip_count : 4;   //!< Mip count for a non LINEAR_STRIDED texture
			uint32_t lod_bias : 6;    //!< Level of Details value for a non LINEAR_STRIDED texture
		};
		uint32_t stride : 10;         //!< Stride for a LINEAR_STRIDED texture
	};
	uint32_t gamma_mode : 2;          //!< Gamma mode
	uint32_t unk2 : 2;                //!< Unknown field
	uint32_t format0 : 1;             //!< Texture format extension
	// Control Word 1
	union {
		struct {
			uint32_t height : 12;     //!< Texture height for non SWIZZLED and non CUBE textures
			uint32_t width : 12;      //!< Texture width for non SWIZZLED and non CUBE textures
		};
		struct {
			uint32_t height_pot : 4;  //!< Power of 2 height value for SWIZZLED and CUBE textures
			uint32_t reserved0 : 12;  //!< Reserved field
			uint32_t width_pot : 4;   //!< Power of 2 width value for SWIZZLED and CUBE textures
			uint32_t reserved1 : 4;   //!< Reserved field
		};
	};
	uint32_t base_format : 5;         //!< Texture base format
	uint32_t type : 3;                //!< Texture format type
	// Control Word 2
	uint32_t lod_min0 : 2;            //!< Level of Details higher bits
	uint32_t data_addr : 30;          //!< Texture data address
	// Control Word 3
	uint32_t palette_addr : 26;       //!< Texture palette address
	uint32_t lod_min1 : 2;            //!< Level of Details lower bits
	uint32_t swizzle_format : 3;      //!< Texture format swizzling
	uint32_t normalize_mode : 1;      //!< Normalize mode
	*/
} SceGxmTexture;

typedef struct SceGxmColorSurface {
	uint32_t pbeSidebandWord;								///< An opaque sideband word.
	uint32_t pbeEmitWords[SCE_GXM_PBE_EMIT_WORD_COUNT];		///< Opaque emit words.
	uint32_t outputRegisterSize;							///< Output register size.
	SceGxmTexture backgroundTex;							///< Precomputed background object texture control words.
} SceGxmColorSurface;

typedef struct SceGxmDepthStencilSurface {
	uint32_t zlsControl;			///< An opaque control word.
	void *depthData;				///< A pointer to the depth data or <c>NULL</c>.
	void *stencilData;				///< A pointer to the stencil data or <c>NULL</c>.
	float backgroundDepth;			///< The 32-bit floating point background object depth value.
	uint32_t backgroundControl;		///< An opaque background object control register.
} SceGxmDepthStencilSurface;

typedef struct SceGxmNotification {
	volatile uint32_t *address;		///< The address that will be written to by the GPU.
	uint32_t value;					///< The 32-bit value that will be written.
} SceGxmNotification;

typedef struct SceGxmValidRegion {
	uint32_t xMax;					///< The maximum x value in pixels.
	uint32_t yMax;					///< The maximum y value in pixels.
} SceGxmValidRegion;

typedef struct SceGxmCommandList {
	uint32_t data[SCE_GXM_COMMAND_LIST_WORD_COUNT];		///< Opaque contents.
} SceGxmCommandList;

/**
 * Initialization
 */

typedef struct SceGxmInitializeParams {
	uint32_t flags;
	uint32_t displayQueueMaxPendingCount;
	SceGxmDisplayQueueCallback displayQueueCallback;
	uint32_t displayQueueCallbackDataSize;
	uint32_t parameterBufferSize;
} SceGxmInitializeParams;

/**
 * GXM context
 */

typedef struct SceGxmContext SceGxmContext;

typedef struct SceGxmContextParams {
	void *hostMem;
	uint32_t hostMemSize;
	void *vdmRingBufferMem;
	uint32_t vdmRingBufferMemSize;
	void *vertexRingBufferMem;
	uint32_t vertexRingBufferMemSize;
	void *fragmentRingBufferMem;
	uint32_t fragmentRingBufferMemSize;
	void *fragmentUsseRingBufferMem;
	uint32_t fragmentUsseRingBufferMemSize;
	uint32_t fragmentUsseRingBufferOffset;
} SceGxmContextParams;

typedef struct SceGxmDeferredContextParams {
	void *hostMem;
	uint32_t hostMemSize;
	SceGxmDeferredContextCallback vdmCallback;
	SceGxmDeferredContextCallback vertexCallback;
	SceGxmDeferredContextCallback fragmentCallback;
	void *userData;
	void *vdmBufferMem;
	uint32_t vdmBufferMemSize;
	void *vertexBufferMem;
	uint32_t vertexBufferMemSize;
	void *fragmentBufferMem;
	uint32_t fragmentBufferMemSize;
} SceGxmDeferredContextParams;

/**
 * Render target
 */

typedef struct SceGxmRenderTargetParams {
	uint32_t flags;					///< Bitwise combined flags from #SceGxmRenderTargetFlags.
	uint16_t width;					///< The width of the render target in pixels.
	uint16_t height;				///< The height of the render target in pixels.
	uint16_t scenesPerFrame;		///< The expected number of scenes per frame, in the range [1,#SCE_GXM_MAX_SCENES_PER_RENDERTARGET].
	uint16_t multisampleMode;		///< A value from the #SceGxmMultisampleMode enum.
	uint32_t multisampleLocations;	///< If enabled in the flags, the multisample locations to use.
	SceUID driverMemBlock;			///< The uncached LPDDR memblock for the render target GPU data structures or SCE_UID_INVALID_UID to specify memory should be allocated in libgxm.
} SceGxmRenderTargetParams;

/**
 * Precomputation
 */

typedef struct SceGxmPrecomputedVertexState {
	uint32_t data[SCE_GXM_PRECOMPUTED_VERTEX_STATE_WORD_COUNT];		///< Opaque contents.
} SceGxmPrecomputedVertexState;

typedef struct SceGxmPrecomputedFragmentState {
	uint32_t data[SCE_GXM_PRECOMPUTED_FRAGMENT_STATE_WORD_COUNT];	///< Opaque contents.
} SceGxmPrecomputedFragmentState;

typedef struct SceGxmPrecomputedDraw {
	uint32_t data[SCE_GXM_PRECOMPUTED_DRAW_WORD_COUNT];				///< Opaque contents.
} SceGxmPrecomputedDraw;

/**
 * Vertex programs
 */

typedef struct SceGxmVertexProgram SceGxmVertexProgram;

/**
 * Fragment progams
 */

typedef struct SceGxmFragmentProgram SceGxmFragmentProgram;

/**
 * Shader programs
 */

typedef struct SceGxmProgram SceGxmProgram;
typedef struct SceGxmProgramParameter SceGxmProgramParameter;

typedef struct SceGxmShaderPatcher SceGxmShaderPatcher;
typedef struct SceGxmRegisteredProgram SceGxmRegisteredProgram;
typedef struct SceGxmRegisteredProgram *SceGxmShaderPatcherId;

typedef struct SceGxmShaderPatcherParams {
	void *userData;
	SceGxmShaderPatcherHostAllocCallback hostAllocCallback;
	SceGxmShaderPatcherHostFreeCallback hostFreeCallback;
	SceGxmShaderPatcherBufferAllocCallback bufferAllocCallback;
	SceGxmShaderPatcherBufferFreeCallback bufferFreeCallback;
	void *bufferMem;
	uint32_t bufferMemSize;
	SceGxmShaderPatcherUsseAllocCallback vertexUsseAllocCallback;
	SceGxmShaderPatcherUsseFreeCallback vertexUsseFreeCallback;
	void *vertexUsseMem;
	uint32_t vertexUsseMemSize;
	uint32_t vertexUsseOffset;
	SceGxmShaderPatcherUsseAllocCallback fragmentUsseAllocCallback;
	SceGxmShaderPatcherUsseFreeCallback fragmentUsseFreeCallback;
	void *fragmentUsseMem;
	uint32_t fragmentUsseMemSize;
	uint32_t fragmentUsseOffset;
} SceGxmShaderPatcherParams;

/**
 * Blending
 */

typedef struct	SceGxmBlendInfo {
	uint8_t	colorMask;			///< Mask bitfield using values from #SceGxmColorMask
	uint8_t	colorFunc	: 4;	///< Color blend function, from #SceGxmBlendFunc
	uint8_t	alphaFunc	: 4;	///< Alpha blend function, from #SceGxmBlendFunc
	uint8_t	colorSrc	: 4;	///< Source color blend factor, from #SceGxmBlendFactor
	uint8_t	colorDst	: 4;	///< Destination color blend factor, from #SceGxmBlendFactor
	uint8_t	alphaSrc	: 4;	///< Source alpha blend factor, from #SceGxmBlendFactor
	uint8_t	alphaDst	: 4;	///< Destination alpha blend factor, from #SceGxmBlendFactor
} SceGxmBlendInfo;

#ifdef __cplusplus
}
#endif

#endif
