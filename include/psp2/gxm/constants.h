#ifndef _DOLCESDK_PSP2_GXM_CONSTANTS_H_
#define _DOLCESDK_PSP2_GXM_CONSTANTS_H_

/** @file
*/

#include <psp2/gxm/texture_defs.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/**	The vertex attribute formats.

	@ingroup render
*/
typedef enum SceGxmAttributeFormat {
	SCE_GXM_ATTRIBUTE_FORMAT_U8,		///< 8-bit unsigned integer
	SCE_GXM_ATTRIBUTE_FORMAT_S8,		///< 8-bit signed integer
	SCE_GXM_ATTRIBUTE_FORMAT_U16,		///< 16-bit unsigned integer
	SCE_GXM_ATTRIBUTE_FORMAT_S16,		///< 16-bit signed integer
	SCE_GXM_ATTRIBUTE_FORMAT_U8N,		///< 8-bit unsigned integer normalized to [0,1] range
	SCE_GXM_ATTRIBUTE_FORMAT_S8N,		///< 8-bit signed integer normalized to [-1,1] range
	SCE_GXM_ATTRIBUTE_FORMAT_U16N,		///< 16-bit unsigned integer normalized to [0,1] range
	SCE_GXM_ATTRIBUTE_FORMAT_S16N,		///< 16-bit signed integer normalized to [-1,1] range
	SCE_GXM_ATTRIBUTE_FORMAT_F16,		///< 16-bit half precision floating point
	SCE_GXM_ATTRIBUTE_FORMAT_F32,		///< 32-bit single precision floating point
	SCE_GXM_ATTRIBUTE_FORMAT_UNTYPED	///< 32-bit untyped data for use with offline vertex unpack
} SceGxmAttributeFormat;

/** The depth/stencil surface formats.

	@ingroup render
*/
typedef enum SceGxmDepthStencilFormat {
	SCE_GXM_DEPTH_STENCIL_FORMAT_DF32		= 0x00044000U,	///< 32-bit floating point Z only
	SCE_GXM_DEPTH_STENCIL_FORMAT_S8			= 0x00022000U,	///< 8-bit stencil only
	SCE_GXM_DEPTH_STENCIL_FORMAT_DF32_S8	= 0x00066000U,	///< Separate 32-bit floating point Z and 8-bit stencil
	SCE_GXM_DEPTH_STENCIL_FORMAT_DF32M		= 0x000CC000U,	///< 32-bit floating point Z with mask in sign bit
	SCE_GXM_DEPTH_STENCIL_FORMAT_DF32M_S8	= 0x000EE000U,	///< Separate 32-bit floating point Z with mask in sign bit and 8-bit stencil
	SCE_GXM_DEPTH_STENCIL_FORMAT_S8D24		= 0x01266000U,	///< Packed 24-bit Z and 8-bit stencil
	SCE_GXM_DEPTH_STENCIL_FORMAT_D16		= 0x02444000U	///< 16-bit Z only
} SceGxmDepthStencilFormat;

/** The primitive types.

	@ingroup render
*/
typedef enum SceGxmPrimitiveType {
	SCE_GXM_PRIMITIVE_TRIANGLES				= 0x00000000U,	///< Indexed triangle list
	SCE_GXM_PRIMITIVE_LINES					= 0x04000000U,	///< Indexed line list
	SCE_GXM_PRIMITIVE_POINTS				= 0x08000000U,	///< Indexed point list
	SCE_GXM_PRIMITIVE_TRIANGLE_STRIP		= 0x0c000000U,	///< Indexed triangle strip
	SCE_GXM_PRIMITIVE_TRIANGLE_FAN			= 0x10000000U,	///< Indexed triangle fan
	SCE_GXM_PRIMITIVE_TRIANGLE_EDGES		= 0x14000000U	///< Indexed triangle edge list
} SceGxmPrimitiveType;

/** The edge enable bits for primitives of type #SCE_GXM_PRIMITIVE_TRIANGLE_EDGES.

	Additional detail can be found in the <em>GPU User’s Guide</em>.

	@ingroup render
*/
typedef enum SceGxmEdgeEnableFlags {
	SCE_GXM_EDGE_ENABLE_01					= 0x00000100U,	///< Enable edge 0-1
	SCE_GXM_EDGE_ENABLE_12					= 0x00000200U,	///< Enable edge 1-2
	SCE_GXM_EDGE_ENABLE_20					= 0x00000400U	///< Enable edge 2-0
} SceGxmEdgeEnableFlags;

/** The tile level clipping modes.

	@ingroup render
*/
typedef enum SceGxmRegionClipMode {
	SCE_GXM_REGION_CLIP_NONE				= 0x00000000U,	///< No tiles are clipped
	SCE_GXM_REGION_CLIP_OUTSIDE				= 0x80000000U	///< Tiles outside the region are clipped
} SceGxmRegionClipMode;

/** The depth compare functions.

	To ensure that depth data can be preserved during partial render,
	when the current scene is using a depth/stencil surface that does not
	contain depth data as part of the format, only the depth functions
	#SCE_GXM_DEPTH_FUNC_NEVER and #SCE_GXM_DEPTH_FUNC_ALWAYS may be used.

	@ingroup render
*/
typedef enum SceGxmDepthFunc {
	SCE_GXM_DEPTH_FUNC_NEVER				= 0x00000000U,	///< Never pass
	SCE_GXM_DEPTH_FUNC_LESS					= 0x00400000U,	///< Pass when input depth is less than stored depth
	SCE_GXM_DEPTH_FUNC_EQUAL				= 0x00800000U,	///< Pass when input depth is equal to stored depth
	SCE_GXM_DEPTH_FUNC_LESS_EQUAL			= 0x00c00000U,	///< Pass when input depth is less than or equal to stored depth
	SCE_GXM_DEPTH_FUNC_GREATER				= 0x01000000U,	///< Pass when input depth is greater than stored depth
	SCE_GXM_DEPTH_FUNC_NOT_EQUAL			= 0x01400000U,	///< Pass when input depth is not equal to stored depth
	SCE_GXM_DEPTH_FUNC_GREATER_EQUAL		= 0x01800000U,	///< Pass when input depth is greater than or equal to stored depth
	SCE_GXM_DEPTH_FUNC_ALWAYS				= 0x01c00000U	///< Always pass
} SceGxmDepthFunc;

/** The stencil compare functions.

	When a mask update fragment program is used, stencil testing is bypassed
	and bit 25 of these values specifies the mask update behaviour.  The mask
	bit is cleared when bit 25 is 0 and set when bit 25 is 1.

	To ensure that stencil data can be preserved during partial render,
	when the current scene is using a depth/stencil surface that does not
	contain stencil data as part of the format, only the stencil functions
	#SCE_GXM_STENCIL_FUNC_NEVER and #SCE_GXM_STENCIL_FUNC_ALWAYS may be used.
	These stencil modes should be used to clear or set the mask bit when
	drawing geometry using a mask update fragment program, since they
	are both allowed when stencil data is not present.

	See #sceGxmShaderPatcherCreateMaskUpdateFragmentProgram() for more
	information about the mask bit.

	@ingroup render
*/
typedef enum SceGxmStencilFunc {
	SCE_GXM_STENCIL_FUNC_NEVER				= 0x00000000U,	///< Never pass
	SCE_GXM_STENCIL_FUNC_LESS				= 0x02000000U,	///< Pass when (reference & mask) is less than (stencil & mask)
	SCE_GXM_STENCIL_FUNC_EQUAL				= 0x04000000U,	///< Pass when (reference & mask) is equal to (stencil & mask)
	SCE_GXM_STENCIL_FUNC_LESS_EQUAL			= 0x06000000U,	///< Pass when (reference & mask) is less than or equal to (stencil & mask)
	SCE_GXM_STENCIL_FUNC_GREATER			= 0x08000000U,	///< Pass when (reference & mask) is greater than (stencil & mask)
	SCE_GXM_STENCIL_FUNC_NOT_EQUAL			= 0x0a000000U,	///< Pass when (reference & mask) is not equal to (stencil & mask)
	SCE_GXM_STENCIL_FUNC_GREATER_EQUAL		= 0x0c000000U,	///< Pass when (reference & mask) is greater than or equal to (stencil & mask)
	SCE_GXM_STENCIL_FUNC_ALWAYS				= 0x0e000000U	///< Always pass
} SceGxmStencilFunc;

/** The stencil operations.

	@ingroup render
*/
typedef enum SceGxmStencilOp {
	SCE_GXM_STENCIL_OP_KEEP					= 0x00000000U,	///< Keep the current stencil buffer value
	SCE_GXM_STENCIL_OP_ZERO					= 0x00000001U,	///< Set the stencil buffer value to 0
	SCE_GXM_STENCIL_OP_REPLACE				= 0x00000002U,	///< Replace the stencil buffer value with the stencil ref value
	SCE_GXM_STENCIL_OP_INCR					= 0x00000003U,	///< Increment the stencil buffer value, clamp to 255
	SCE_GXM_STENCIL_OP_DECR					= 0x00000004U,	///< Decrement the stencil buffer value, clamp to 0
	SCE_GXM_STENCIL_OP_INVERT				= 0x00000005U,	///< Bitwise invert the stencil buffer value
	SCE_GXM_STENCIL_OP_INCR_WRAP			= 0x00000006U,	///< Increment the stencil buffer value, wrap from 255 to 0
	SCE_GXM_STENCIL_OP_DECR_WRAP			= 0x00000007U	///< Decrement the stencil buffer value, wrap from 0 to 255
} SceGxmStencilOp;

/** The backface culling modes.

	@ingroup render
*/
typedef enum SceGxmCullMode {
	SCE_GXM_CULL_NONE						= 0x00000000U,	///< No culling
	SCE_GXM_CULL_CW							= 0x00000001U,	///< Cull triangles with clockwise window coordinates
	SCE_GXM_CULL_CCW						= 0x00000002U	///< Cull triangles with counter-clockwise window coordinates
} SceGxmCullMode;

/** The pass type of a fragment program.

	@ingroup render
*/
typedef enum SceGxmPassType {
	SCE_GXM_PASS_TYPE_OPAQUE				= 0x00000000U,	///< Opaque with no discard or depth replace
	SCE_GXM_PASS_TYPE_TRANSLUCENT			= 0x02000000U,	///< Translucent with no discard or depth replace
	SCE_GXM_PASS_TYPE_DISCARD				= 0x04000000U,	///< Translucent with discard but no depth replace
	SCE_GXM_PASS_TYPE_MASK_UPDATE			= 0x06000000U,	///< Fragment program updates mask bit only
	SCE_GXM_PASS_TYPE_DEPTH_REPLACE			= 0x0A000000U	///< Depth replace used, can also be translucent or use discard
} SceGxmPassType;

/** The polygon filling modes.

	@ingroup render
*/
typedef enum SceGxmPolygonMode {
	SCE_GXM_POLYGON_MODE_TRIANGLE_FILL		= 0x00000000U,	///< Triangle polygons with shaded interior
	SCE_GXM_POLYGON_MODE_LINE				= 0x00008000U,	///< Lines shaded as lines
	SCE_GXM_POLYGON_MODE_POINT_10UV			= 0x00010000U,	///< Point sprites using UV coordinate range (0,1) to (1,0)
	SCE_GXM_POLYGON_MODE_POINT				= 0x00018000U,	///< Point sprites using supplied UV values
	SCE_GXM_POLYGON_MODE_POINT_01UV			= 0x00020000U,	///< Point sprites using UV coordinate range (0,0) to (1,1)
	SCE_GXM_POLYGON_MODE_TRIANGLE_LINE		= 0x00028000U,	///< Triangle polygons with edges shaded only
	SCE_GXM_POLYGON_MODE_TRIANGLE_POINT		= 0x00030000U	///< Triangle polygons with vertices shaded only
} SceGxmPolygonMode;

/** Defines the 4-component color format swizzles.

	@ingroup render
*/
typedef enum SceGxmColorSwizzle4Mode {
	SCE_GXM_COLOR_SWIZZLE4_ABGR				= 0x00000000U,	///< Color format written in ABGR order
	SCE_GXM_COLOR_SWIZZLE4_ARGB				= 0x00100000U,	///< Color format written in ARGB order
	SCE_GXM_COLOR_SWIZZLE4_RGBA				= 0x00200000U,	///< Color format written in RGBA order
	SCE_GXM_COLOR_SWIZZLE4_BGRA				= 0x00300000U	///< Color format written in BGRA order
} SceGxmColorSwizzle4Mode;

/** Defines the 3-component color format swizzles.

	@ingroup render
*/
typedef enum SceGxmColorSwizzle3Mode {
	SCE_GXM_COLOR_SWIZZLE3_BGR				= 0x00000000U,	///< Color format written in BGR order (A is ignored)
	SCE_GXM_COLOR_SWIZZLE3_RGB				= 0x00100000U	///< Color format written in RGB order (A is ignored)
} SceGxmColorSwizzle3Mode;

/** Defines the 2-component color format swizzles.

	@ingroup render
*/
typedef enum SceGxmColorSwizzle2Mode {
	SCE_GXM_COLOR_SWIZZLE2_GR				= 0x00000000U,	///< Color format written in GR order (A and B are ignored)
	SCE_GXM_COLOR_SWIZZLE2_RG				= 0x00100000U,	///< Color format written in RG order (A and B are ignored)
	SCE_GXM_COLOR_SWIZZLE2_RA				= 0x00200000U,	///< Color format written in RA order (B and G are ignored)
	SCE_GXM_COLOR_SWIZZLE2_AR				= 0x00300000U	///< Color format written in AR order (B and G are ignored)
} SceGxmColorSwizzle2Mode;

/** Defines the 1-component color format swizzles.

	Note that #SCE_GXM_COLOR_SWIZZLE1_G and #SCE_GXM_COLOR_SWIZZLE1_A intentionally
	have the same value.  This is due to some color formats only supporting R or G,
	whereas others support on R or A.

	@ingroup render
*/
typedef enum SceGxmColorSwizzle1Mode {
	SCE_GXM_COLOR_SWIZZLE1_R				= 0x00000000U,	///< Color format uses the R component only (A, B and G are ignored)
	SCE_GXM_COLOR_SWIZZLE1_G				= 0x00100000U,	///< Color format uses the G component only (A, B and R are ignored)
	SCE_GXM_COLOR_SWIZZLE1_A				= 0x00100000U	///< Color format uses the A component only (B, G and R are ignored)
} SceGxmColorSwizzle1Mode;

/** The base formats for color surfaces.  A color format is made from (bitwise) combining
	a base format with a compatible swizzle.

	@ingroup render
*/
typedef enum SceGxmColorBaseFormat {
	SCE_GXM_COLOR_BASE_FORMAT_U8U8U8U8			= 0x00000000U,	///< 32-bit format, 4x 8-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U8U8U8			= 0x10000000U,	///< 24-bit packed format, 3x 8-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U5U6U5			= 0x30000000U,	///< 16-bit format, 5-bit unsigned, 6-bit unsigned and 5-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U1U5U5U5			= 0x40000000U,	///< 16-bit format, 1-bit unsigned and 3x 5-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U4U4U4U4			= 0x50000000U,	///< 16-bit format, 4x 4-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U8U3U3U2			= 0x60000000U,	///< 16-bit format, 8-bit unsigned, 3-bit unsigned, 3-bit unsigned and 2-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_F16				= 0xf0000000U,	///< 16-bit format, 16-bit s1e5m10 floating point
	SCE_GXM_COLOR_BASE_FORMAT_F16F16			= 0x00800000U,	///< 32-bit format, 2x 16-bit s1e5m10 floating point
	SCE_GXM_COLOR_BASE_FORMAT_F32				= 0x10800000U,	///< 32-bit format, 32-bit floating point
	SCE_GXM_COLOR_BASE_FORMAT_S16				= 0x20800000U,	///< 16-bit format, 16-bit signed integer
	SCE_GXM_COLOR_BASE_FORMAT_S16S16			= 0x30800000U,	///< 32-bit format, 2x 16-bit signed integer
	SCE_GXM_COLOR_BASE_FORMAT_U16				= 0x40800000U,	///< 16-bit format, 16-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U16U16			= 0x50800000U,	///< 32-bit format, 2x 16-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U2U10U10U10		= 0x60800000U,	///< 32-bit format, 2-bit unsigned and 3x 10-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U8				= 0x80800000U,	///< 8-bit format, 8-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_S8				= 0x90800000U,	///< 8-bit format, 8-bit signed integer
	SCE_GXM_COLOR_BASE_FORMAT_S5S5U6			= 0xa0800000U,	///< 16-bit format, 5-bit signed, 5-bit signed and 6-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_U8U8				= 0xb0800000U,	///< 16-bit format, 2x 8-bit unsigned integer
	SCE_GXM_COLOR_BASE_FORMAT_S8S8				= 0xc0800000U,	///< 16-bit format, 2x 8-bit signed integer
	SCE_GXM_COLOR_BASE_FORMAT_S8S8S8S8			= 0xe0800000U,	///< 32-bit format, 4x 8-bit signed integer
	SCE_GXM_COLOR_BASE_FORMAT_F16F16F16F16		= 0x01000000U,	///< 64-bit format, 4x 16-bit s1e5m10 floating point
	SCE_GXM_COLOR_BASE_FORMAT_F32F32			= 0x11000000U,	///< 64-bit format, 2x 32-bit floating point
	SCE_GXM_COLOR_BASE_FORMAT_F11F11F10			= 0x21000000U,	///< 32-bit format, 2x 11-bit s0e5m6 floating point and 10-bit s0e5m5 floating point
	SCE_GXM_COLOR_BASE_FORMAT_SE5M9M9M9			= 0x31000000U,	///< 32-bit format, 5-bit shared exponent and 3x 9-bit floating point mantissa
	SCE_GXM_COLOR_BASE_FORMAT_U2F10F10F10		= 0x41000000U	///< 32-bit format, 2-bit unsigned integer and 3x 10-bit s0e5m5 floating point
} SceGxmColorBaseFormat;

/** The color formats.

	These are split into two sections: the full list of all color formats
	supported by the hardware, followed by some legacy defines for convenience.
	The full list uses a standard syntax of <c>FORMAT_SWIZZLE</c>.

	The format part of the name is written for high-to-low bit ordering assuming
	the value is in a register.  Note that registers are stored in memory in a
	little-endian format.

	For 4 and 3-component formats in memory, the swizzle part of the name is the
	component ordering in the value stored to memory.  For example, a pixel of
	format #SCE_GXM_COLOR_FORMAT_U4U4U4U4_ABGR would have A in the high 4 bits
	and R in the low 4 bits if the 16-bit value was loaded into a register.

	For 2 and 1-component formats in memory, the format in memory is always GR or
	R and the swizzle represents the selection from the ABGR value of the current
	pixel.  For example, the format #SCE_GXM_COLOR_FORMAT_U8_A would write the A
	component of each pixel to memory when the tile is finished.

	For a full table of all color base formats, swizzles and supported output
	register formats please refer to the <em>GPU User’s Guide</em>, Appendix A.

	@ingroup render
*/
typedef enum SceGxmColorFormat {
	// Full list of supported texture formats

	SCE_GXM_COLOR_FORMAT_U8U8U8U8_ABGR		= SCE_GXM_COLOR_BASE_FORMAT_U8U8U8U8 | SCE_GXM_COLOR_SWIZZLE4_ABGR,		///< Pixels are written to memory in U8U8U8U8 format in ABGR order.
	SCE_GXM_COLOR_FORMAT_U8U8U8U8_ARGB		= SCE_GXM_COLOR_BASE_FORMAT_U8U8U8U8 | SCE_GXM_COLOR_SWIZZLE4_ARGB,		///< Pixels are written to memory in U8U8U8U8 format in ARGB order.
	SCE_GXM_COLOR_FORMAT_U8U8U8U8_RGBA		= SCE_GXM_COLOR_BASE_FORMAT_U8U8U8U8 | SCE_GXM_COLOR_SWIZZLE4_RGBA,		///< Pixels are written to memory in U8U8U8U8 format in RGBA order.
	SCE_GXM_COLOR_FORMAT_U8U8U8U8_BGRA		= SCE_GXM_COLOR_BASE_FORMAT_U8U8U8U8 | SCE_GXM_COLOR_SWIZZLE4_BGRA,		///< Pixels are written to memory in U8U8U8U8 format in BGRA order.

	SCE_GXM_COLOR_FORMAT_U8U8U8_BGR			= SCE_GXM_COLOR_BASE_FORMAT_U8U8U8 | SCE_GXM_COLOR_SWIZZLE3_BGR,		///< Pixels are written to memory in packed 24-bit U8U8U8 format in BGR order, A is discarded.
	SCE_GXM_COLOR_FORMAT_U8U8U8_RGB			= SCE_GXM_COLOR_BASE_FORMAT_U8U8U8 | SCE_GXM_COLOR_SWIZZLE3_RGB,		///< Pixels are written to memory in packed 24-bit U8U8U8 format in RGB order, A is discarded.

	SCE_GXM_COLOR_FORMAT_U5U6U5_BGR			= SCE_GXM_COLOR_BASE_FORMAT_U5U6U5 | SCE_GXM_COLOR_SWIZZLE3_BGR,		///< Pixels are written to memory in U5U6U5 format in BGR order, A is discarded.
	SCE_GXM_COLOR_FORMAT_U5U6U5_RGB			= SCE_GXM_COLOR_BASE_FORMAT_U5U6U5 | SCE_GXM_COLOR_SWIZZLE3_RGB,		///< Pixels are written to memory in U5U6U5 format in RGB order, A is discarded.

	SCE_GXM_COLOR_FORMAT_U1U5U5U5_ABGR		= SCE_GXM_COLOR_BASE_FORMAT_U1U5U5U5 | SCE_GXM_COLOR_SWIZZLE4_ABGR,		///< Pixels are written to memory in U1U5U5U5 format in ABGR order.
	SCE_GXM_COLOR_FORMAT_U1U5U5U5_ARGB		= SCE_GXM_COLOR_BASE_FORMAT_U1U5U5U5 | SCE_GXM_COLOR_SWIZZLE4_ARGB,		///< Pixels are written to memory in U1U5U5U5 format in ARGB order.
	SCE_GXM_COLOR_FORMAT_U5U5U5U1_RGBA		= SCE_GXM_COLOR_BASE_FORMAT_U1U5U5U5 | SCE_GXM_COLOR_SWIZZLE4_RGBA,		///< Pixels are written to memory in U5U5U5U1 format in RGBA order.
	SCE_GXM_COLOR_FORMAT_U5U5U5U1_BGRA		= SCE_GXM_COLOR_BASE_FORMAT_U1U5U5U5 | SCE_GXM_COLOR_SWIZZLE4_BGRA,		///< Pixels are written to memory in U5U5U5U1 format in BGRA order.

	SCE_GXM_COLOR_FORMAT_U4U4U4U4_ABGR		= SCE_GXM_COLOR_BASE_FORMAT_U4U4U4U4 | SCE_GXM_COLOR_SWIZZLE4_ABGR,		///< Pixels are written to memory in U4U4U4U4 format in ABGR order.
	SCE_GXM_COLOR_FORMAT_U4U4U4U4_ARGB		= SCE_GXM_COLOR_BASE_FORMAT_U4U4U4U4 | SCE_GXM_COLOR_SWIZZLE4_ARGB,		///< Pixels are written to memory in U4U4U4U4 format in ARGB order.
	SCE_GXM_COLOR_FORMAT_U4U4U4U4_RGBA		= SCE_GXM_COLOR_BASE_FORMAT_U4U4U4U4 | SCE_GXM_COLOR_SWIZZLE4_RGBA,		///< Pixels are written to memory in U4U4U4U4 format in RGBA order.
	SCE_GXM_COLOR_FORMAT_U4U4U4U4_BGRA		= SCE_GXM_COLOR_BASE_FORMAT_U4U4U4U4 | SCE_GXM_COLOR_SWIZZLE4_BGRA,		///< Pixels are written to memory in U4U4U4U4 format in BGRA order.

	SCE_GXM_COLOR_FORMAT_U8U3U3U2_ARGB		= SCE_GXM_COLOR_BASE_FORMAT_U8U3U3U2,									///< Pixels are written to memory in U8U3U3U2 format in ARGB order.

	SCE_GXM_COLOR_FORMAT_F16_R				= SCE_GXM_COLOR_BASE_FORMAT_F16 | SCE_GXM_COLOR_SWIZZLE1_R,				///< Pixels are written to memory in F16 format using the R component only, G is discarded.
	SCE_GXM_COLOR_FORMAT_F16_G				= SCE_GXM_COLOR_BASE_FORMAT_F16 | SCE_GXM_COLOR_SWIZZLE1_G,				///< Pixels are written to memory in F16 format using the G component only, R is discarded.

	SCE_GXM_COLOR_FORMAT_F16F16_GR			= SCE_GXM_COLOR_BASE_FORMAT_F16F16 | SCE_GXM_COLOR_SWIZZLE2_GR,			///< Pixels are written to memory in F16F16 format in GR order.
	SCE_GXM_COLOR_FORMAT_F16F16_RG			= SCE_GXM_COLOR_BASE_FORMAT_F16F16 | SCE_GXM_COLOR_SWIZZLE2_RG,			///< Pixels are written to memory in F16F16 format in RG order.

	SCE_GXM_COLOR_FORMAT_F32_R				= SCE_GXM_COLOR_BASE_FORMAT_F32 | SCE_GXM_COLOR_SWIZZLE1_R,				///< Pixels are written to memory in F32 format using the R component only.

	SCE_GXM_COLOR_FORMAT_S16_R				= SCE_GXM_COLOR_BASE_FORMAT_S16 | SCE_GXM_COLOR_SWIZZLE1_R,				///< Pixels are written to memory in S16 format using the R component only, G is discarded.
	SCE_GXM_COLOR_FORMAT_S16_G				= SCE_GXM_COLOR_BASE_FORMAT_S16 | SCE_GXM_COLOR_SWIZZLE1_G,				///< Pixels are written to memory in S16 format using the G component only, R is discarded.

	SCE_GXM_COLOR_FORMAT_S16S16_GR			= SCE_GXM_COLOR_BASE_FORMAT_S16S16 | SCE_GXM_COLOR_SWIZZLE2_GR,			///< Pixels are written to memory in S16S16 format in GR order.
	SCE_GXM_COLOR_FORMAT_S16S16_RG			= SCE_GXM_COLOR_BASE_FORMAT_S16S16 | SCE_GXM_COLOR_SWIZZLE2_RG,			///< Pixels are written to memory in S16S16 format in RG order.

	SCE_GXM_COLOR_FORMAT_U16_R				= SCE_GXM_COLOR_BASE_FORMAT_U16 | SCE_GXM_COLOR_SWIZZLE1_R,				///< Pixels are written to memory in U16 format using the R component only, G is discarded.
	SCE_GXM_COLOR_FORMAT_U16_G				= SCE_GXM_COLOR_BASE_FORMAT_U16 | SCE_GXM_COLOR_SWIZZLE1_G,				///< Pixels are written to memory in U16 format using the G component only, R is discarded

	SCE_GXM_COLOR_FORMAT_U16U16_GR			= SCE_GXM_COLOR_BASE_FORMAT_U16U16 | SCE_GXM_COLOR_SWIZZLE2_GR,			///< Pixels are written to memory in U16U16 format in GR order.
	SCE_GXM_COLOR_FORMAT_U16U16_RG			= SCE_GXM_COLOR_BASE_FORMAT_U16U16 | SCE_GXM_COLOR_SWIZZLE2_RG,			///< Pixels are written to memory in U16U16 format in RG order.

	SCE_GXM_COLOR_FORMAT_U2U10U10U10_ABGR	= SCE_GXM_COLOR_BASE_FORMAT_U2U10U10U10	| SCE_GXM_COLOR_SWIZZLE4_ABGR,	///< Pixels are written to memory in U2U10U10U10 format in ABGR order.
	SCE_GXM_COLOR_FORMAT_U2U10U10U10_ARGB	= SCE_GXM_COLOR_BASE_FORMAT_U2U10U10U10	| SCE_GXM_COLOR_SWIZZLE4_ARGB,	///< Pixels are written to memory in U2U10U10U10 format in ARGB order.
	SCE_GXM_COLOR_FORMAT_U10U10U10U2_RGBA	= SCE_GXM_COLOR_BASE_FORMAT_U2U10U10U10	| SCE_GXM_COLOR_SWIZZLE4_RGBA,	///< Pixels are written to memory in U10U10U10U2 format in RGBA order.
	SCE_GXM_COLOR_FORMAT_U10U10U10U2_BGRA	= SCE_GXM_COLOR_BASE_FORMAT_U2U10U10U10	| SCE_GXM_COLOR_SWIZZLE4_BGRA,	///< Pixels are written to memory in U10U10U10U2 format in BGRA order.

	SCE_GXM_COLOR_FORMAT_U8_R				= SCE_GXM_COLOR_BASE_FORMAT_U8 | SCE_GXM_COLOR_SWIZZLE1_R,				///< Pixels are written to memory in U8 format using the R component only, A B and G are discarded.
	SCE_GXM_COLOR_FORMAT_U8_A				= SCE_GXM_COLOR_BASE_FORMAT_U8 | SCE_GXM_COLOR_SWIZZLE1_A,				///< Pixels are written to memory in U8 format using the A component only, B G and R are discarded.

	SCE_GXM_COLOR_FORMAT_S8_R				= SCE_GXM_COLOR_BASE_FORMAT_S8 | SCE_GXM_COLOR_SWIZZLE1_R,				///< Pixels are written to memory in S8 format using the R component only, A B and G are discarded.
	SCE_GXM_COLOR_FORMAT_S8_A				= SCE_GXM_COLOR_BASE_FORMAT_S8 | SCE_GXM_COLOR_SWIZZLE1_A,				///< Pixels are written to memory in S8 format using the A component only, B G and R are discarded.

	SCE_GXM_COLOR_FORMAT_U6S5S5_BGR			= SCE_GXM_COLOR_BASE_FORMAT_S5S5U6 | SCE_GXM_COLOR_SWIZZLE3_BGR,		///< Pixels are written to memory in U6S5S5 format in BGR order, A is discarded.
	SCE_GXM_COLOR_FORMAT_S5S5U6_RGB			= SCE_GXM_COLOR_BASE_FORMAT_S5S5U6 | SCE_GXM_COLOR_SWIZZLE3_RGB,		///< Pixels are written to memory in S5S5U6 format in RGB order, A is discarded.

	SCE_GXM_COLOR_FORMAT_U8U8_GR			= SCE_GXM_COLOR_BASE_FORMAT_U8U8 | SCE_GXM_COLOR_SWIZZLE2_GR,			///< Pixels are written to memory in U8U8 format in GR order, A and B are discarded.
	SCE_GXM_COLOR_FORMAT_U8U8_RG			= SCE_GXM_COLOR_BASE_FORMAT_U8U8 | SCE_GXM_COLOR_SWIZZLE2_RG,			///< Pixels are written to memory in U8U8 format in RG order, A and B are discarded.
	SCE_GXM_COLOR_FORMAT_U8U8_RA			= SCE_GXM_COLOR_BASE_FORMAT_U8U8 | SCE_GXM_COLOR_SWIZZLE2_RA,			///< Pixels are written to memory in U8U8 format in RA order, B and G are discarded.
	SCE_GXM_COLOR_FORMAT_U8U8_AR			= SCE_GXM_COLOR_BASE_FORMAT_U8U8 | SCE_GXM_COLOR_SWIZZLE2_AR,			///< Pixels are written to memory in U8U8 format in AR order, B and G are discarded.

	SCE_GXM_COLOR_FORMAT_S8S8_GR			= SCE_GXM_COLOR_BASE_FORMAT_S8S8 | SCE_GXM_COLOR_SWIZZLE2_GR,			///< Pixels are written to memory in S8S8 format in GR order, A and B are discarded.
	SCE_GXM_COLOR_FORMAT_S8S8_RG			= SCE_GXM_COLOR_BASE_FORMAT_S8S8 | SCE_GXM_COLOR_SWIZZLE2_RG,			///< Pixels are written to memory in S8S8 format in RG order, A and B are discarded.
	SCE_GXM_COLOR_FORMAT_S8S8_RA			= SCE_GXM_COLOR_BASE_FORMAT_S8S8 | SCE_GXM_COLOR_SWIZZLE2_RA,			///< Pixels are written to memory in S8S8 format in RA order, B and G are discarded.
	SCE_GXM_COLOR_FORMAT_S8S8_AR			= SCE_GXM_COLOR_BASE_FORMAT_S8S8 | SCE_GXM_COLOR_SWIZZLE2_AR,			///< Pixels are written to memory in S8S8 format in AR order, B and G are discarded.

	SCE_GXM_COLOR_FORMAT_S8S8S8S8_ABGR		= SCE_GXM_COLOR_BASE_FORMAT_S8S8S8S8 | SCE_GXM_COLOR_SWIZZLE4_ABGR,		///< Pixels are written to memory in S8S8S8S8 format in ABGR order.
	SCE_GXM_COLOR_FORMAT_S8S8S8S8_ARGB		= SCE_GXM_COLOR_BASE_FORMAT_S8S8S8S8 | SCE_GXM_COLOR_SWIZZLE4_ARGB,		///< Pixels are written to memory in S8S8S8S8 format in ARGB order.
	SCE_GXM_COLOR_FORMAT_S8S8S8S8_RGBA		= SCE_GXM_COLOR_BASE_FORMAT_S8S8S8S8 | SCE_GXM_COLOR_SWIZZLE4_RGBA,		///< Pixels are written to memory in S8S8S8S8 format in RGBA order.
	SCE_GXM_COLOR_FORMAT_S8S8S8S8_BGRA		= SCE_GXM_COLOR_BASE_FORMAT_S8S8S8S8 | SCE_GXM_COLOR_SWIZZLE4_BGRA,		///< Pixels are written to memory in S8S8S8S8 format in BGRA order.

	SCE_GXM_COLOR_FORMAT_F16F16F16F16_ABGR	= SCE_GXM_COLOR_BASE_FORMAT_F16F16F16F16 | SCE_GXM_COLOR_SWIZZLE4_ABGR,	///< Pixels are written to memory in F16F16F16F16 format in ABGR order.
	SCE_GXM_COLOR_FORMAT_F16F16F16F16_ARGB	= SCE_GXM_COLOR_BASE_FORMAT_F16F16F16F16 | SCE_GXM_COLOR_SWIZZLE4_ARGB,	///< Pixels are written to memory in F16F16F16F16 format in ARGB order.
	SCE_GXM_COLOR_FORMAT_F16F16F16F16_RGBA	= SCE_GXM_COLOR_BASE_FORMAT_F16F16F16F16 | SCE_GXM_COLOR_SWIZZLE4_RGBA,	///< Pixels are written to memory in F16F16F16F16 format in RGBA order.
	SCE_GXM_COLOR_FORMAT_F16F16F16F16_BGRA	= SCE_GXM_COLOR_BASE_FORMAT_F16F16F16F16 | SCE_GXM_COLOR_SWIZZLE4_BGRA,	///< Pixels are written to memory in F16F16F16F16 format in BGRA order.

	SCE_GXM_COLOR_FORMAT_F32F32_GR			= SCE_GXM_COLOR_BASE_FORMAT_F32F32 | SCE_GXM_COLOR_SWIZZLE2_GR,			///< Pixels are written to memory in F32F32 format in GR order.
	SCE_GXM_COLOR_FORMAT_F32F32_RG			= SCE_GXM_COLOR_BASE_FORMAT_F32F32 | SCE_GXM_COLOR_SWIZZLE2_RG,			///< Pixels are written to memory in F32F32 format in RG order.

	SCE_GXM_COLOR_FORMAT_F10F11F11_BGR		= SCE_GXM_COLOR_BASE_FORMAT_F11F11F10 | SCE_GXM_COLOR_SWIZZLE3_BGR,		///< Pixels are written to memory in F10F11F11 format in BGR order, A is discarded.
	SCE_GXM_COLOR_FORMAT_F11F11F10_RGB		= SCE_GXM_COLOR_BASE_FORMAT_F11F11F10 | SCE_GXM_COLOR_SWIZZLE3_RGB,		///< Pixels are written to memory in F11F11F10 format in RGB order, A is discarded.

	SCE_GXM_COLOR_FORMAT_SE5M9M9M9_BGR		= SCE_GXM_COLOR_BASE_FORMAT_SE5M9M9M9 | SCE_GXM_COLOR_SWIZZLE3_BGR,		///< Pixels are written to memory in SE5M9M9M9 format in BGR order, A is discarded.
	SCE_GXM_COLOR_FORMAT_SE5M9M9M9_RGB		= SCE_GXM_COLOR_BASE_FORMAT_SE5M9M9M9 | SCE_GXM_COLOR_SWIZZLE3_RGB,		///< Pixels are written to memory in SE5M9M9M9 format in RGB order, A is discarded.

	SCE_GXM_COLOR_FORMAT_U2F10F10F10_ABGR	= SCE_GXM_COLOR_BASE_FORMAT_U2F10F10F10	| SCE_GXM_COLOR_SWIZZLE4_ABGR,	///< Pixels are written to memory in U2F10F10F10 format in ABGR order.
	SCE_GXM_COLOR_FORMAT_U2F10F10F10_ARGB	= SCE_GXM_COLOR_BASE_FORMAT_U2F10F10F10	| SCE_GXM_COLOR_SWIZZLE4_ARGB,	///< Pixels are written to memory in U2F10F10F10 format in ARGB order.
	SCE_GXM_COLOR_FORMAT_F10F10F10U2_RGBA	= SCE_GXM_COLOR_BASE_FORMAT_U2F10F10F10	| SCE_GXM_COLOR_SWIZZLE4_RGBA,	///< Pixels are written to memory in F10F10F10U2 format in RGBA order.
	SCE_GXM_COLOR_FORMAT_F10F10F10U2_BGRA	= SCE_GXM_COLOR_BASE_FORMAT_U2F10F10F10	| SCE_GXM_COLOR_SWIZZLE4_BGRA,	///< Pixels are written to memory in F10F10F10U2 format in BGRA order.

	// Legacy formats (defined in terms of full list above)

	SCE_GXM_COLOR_FORMAT_A8B8G8R8			= SCE_GXM_COLOR_FORMAT_U8U8U8U8_ABGR,	///< Legacy name for #SCE_GXM_COLOR_FORMAT_U8U8U8U8_ABGR.
	SCE_GXM_COLOR_FORMAT_A8R8G8B8			= SCE_GXM_COLOR_FORMAT_U8U8U8U8_ARGB,	///< Legacy name for #SCE_GXM_COLOR_FORMAT_U8U8U8U8_ARGB.
	SCE_GXM_COLOR_FORMAT_R5G6B5				= SCE_GXM_COLOR_FORMAT_U5U6U5_RGB,		///< Legacy name for #SCE_GXM_COLOR_FORMAT_U5U6U5_RGB.
	SCE_GXM_COLOR_FORMAT_A1R5G5B5			= SCE_GXM_COLOR_FORMAT_U1U5U5U5_ARGB,	///< Legacy name for #SCE_GXM_COLOR_FORMAT_U1U5U5U5_ARGB.
	SCE_GXM_COLOR_FORMAT_A4R4G4B4			= SCE_GXM_COLOR_FORMAT_U4U4U4U4_ARGB,	///< Legacy name for #SCE_GXM_COLOR_FORMAT_U4U4U4U4_ARGB.
	SCE_GXM_COLOR_FORMAT_A8					= SCE_GXM_COLOR_FORMAT_U8_A				///< Legacy name for #SCE_GXM_COLOR_FORMAT_U8_A.
} SceGxmColorFormat;

/** The color surface memory layout types.

	@ingroup render
*/
typedef enum SceGxmColorSurfaceType {
	SCE_GXM_COLOR_SURFACE_LINEAR			= 0x00000000U,	///< The color surface uses a linear memory layout
	SCE_GXM_COLOR_SURFACE_TILED				= 0x04000000U,	///< The color surface uses a tiled memory layout
	SCE_GXM_COLOR_SURFACE_SWIZZLED			= 0x08000000U	///< The color surface uses a swizzled memory layout
} SceGxmColorSurfaceType;

/** The color surface gamma mode

	@note SCE_GXM_COLOR_SURFACE_GAMMA_R and SCE_GXM_COLOR_SURFACE_GAMMA_BGR enumerations
	intentionally share the same value. The implied meaning of the value changes depending
	on the color surface format being used. Please see the <em>GPU User’s Guide</em> for details.

	@ingroup render
*/
typedef enum SceGxmColorSurfaceGammaMode {
	SCE_GXM_COLOR_SURFACE_GAMMA_NONE		= 0x00000000U,	///< No gamma correction on pixel write.
	SCE_GXM_COLOR_SURFACE_GAMMA_R			= 0x00001000U,	///< Gamma correction is performed for the R component on pixel write.
	SCE_GXM_COLOR_SURFACE_GAMMA_GR			= 0x00003000U,	///< Gamma correction is performed for the G and R components on pixel write.
	SCE_GXM_COLOR_SURFACE_GAMMA_BGR			= 0x00001000U	///< Gamma correction is performed for the B, G, and R components on pixel write.
} SceGxmColorSurfaceGammaMode;

/** The color surface dither mode

	@ingroup render
*/
typedef enum SceGxmColorSurfaceDitherMode {
	SCE_GXM_COLOR_SURFACE_DITHER_DISABLED	= 0x00000000U,	///< Dithering is disabled.
	SCE_GXM_COLOR_SURFACE_DITHER_ENABLED	= 0x00000008U	///< Dithering is enabled.
} SceGxmColorSurfaceDitherMode;

/** The depth/stencil surface memory layout types.

	@ingroup render
*/
typedef enum SceGxmDepthStencilSurfaceType {
	SCE_GXM_DEPTH_STENCIL_SURFACE_LINEAR	= 0x00000000U,	///< Depth/stencil surface uses a linear memory layout
	SCE_GXM_DEPTH_STENCIL_SURFACE_TILED		= 0x00011000U	///< Depth/stencil surface uses a tiled memory layout
} SceGxmDepthStencilSurfaceType;

/** When using a fragment program that does not declare its output format in
	the shader code, one of these formats may be selected as the format to use
	for the <c>COLOR0</c> output.

	This format must match the output register size of the color surface.
	For details of which color surface formats support which output register
	formats, please see the <em>GPU User’s Guide</em>.

	@ingroup render
*/
typedef enum SceGxmOutputRegisterFormat {
	SCE_GXM_OUTPUT_REGISTER_FORMAT_DECLARED,	///< Use the output format declared in the shader code.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,		///< Perform a normalized pack to unsigned char4.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_CHAR4,		///< Perform a normalized pack to char4.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_USHORT2,		///< Perform a normalized pack to unsigned short2.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_SHORT2,		///< Perform a normalized pack to short2.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_HALF4,		///< Perform a pack to half4.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_HALF2,		///< Perform a pack to half2.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_FLOAT2,		///< Perform a pack to float2.
	SCE_GXM_OUTPUT_REGISTER_FORMAT_FLOAT		///< Perform a pack to float.
} SceGxmOutputRegisterFormat;

/** The multisample modes.

	@ingroup render
*/
typedef enum SceGxmMultisampleMode {
	SCE_GXM_MULTISAMPLE_NONE,		///< Single central sample.
	SCE_GXM_MULTISAMPLE_2X,			///< 2x diagonal samples.
	SCE_GXM_MULTISAMPLE_4X			///< 4x rotated grid.
} SceGxmMultisampleMode;

/** Defines the layout of 4-component texture formats which can be swizzled.

	@ingroup render
*/
typedef enum SceGxmTextureSwizzle4Mode {
	SCE_GXM_TEXTURE_SWIZZLE4_ABGR			= 0x00000000U,	///< Texture format read in ABGR order
	SCE_GXM_TEXTURE_SWIZZLE4_ARGB			= 0x00001000U,	///< Texture format read in ARGB order
	SCE_GXM_TEXTURE_SWIZZLE4_RGBA			= 0x00002000U,	///< Texture format read in RGBA order
	SCE_GXM_TEXTURE_SWIZZLE4_BGRA			= 0x00003000U,	///< Texture format read in BGRA order
	SCE_GXM_TEXTURE_SWIZZLE4_1BGR			= 0x00004000U,	///< Texture format read in ABGR order, and A is forced to 1.0
	SCE_GXM_TEXTURE_SWIZZLE4_1RGB			= 0x00005000U,	///< Texture format read in ARGB order, and A is forced to 1.0
	SCE_GXM_TEXTURE_SWIZZLE4_RGB1			= 0x00006000U,	///< Texture format read in RGBA order, and A is forced to 1.0
	SCE_GXM_TEXTURE_SWIZZLE4_BGR1			= 0x00007000U	///< Texture format read in BGRA order, and A is forced to 1.0
} SceGxmTextureSwizzle4Mode;

/** Defines the layout of 3-component texture formats which can be swizzled.

	@ingroup render
*/
typedef enum SceGxmTextureSwizzle3Mode {
	SCE_GXM_TEXTURE_SWIZZLE3_BGR			= 0x00000000U,	///< Texture format read in BGR order
	SCE_GXM_TEXTURE_SWIZZLE3_RGB			= 0x00001000U	///< Texture format read in RGB order
} SceGxmTextureSwizzle3Mode;

/** Defines the result layout of 2-component texture formats which can be swizzled.

	@ingroup render
*/
typedef enum SceGxmTextureSwizzle2Mode {
	SCE_GXM_TEXTURE_SWIZZLE2_GR				= 0x00000000U,	///< The texture format is swizzled to ABGR form as XXGR (where X is undefined)
	SCE_GXM_TEXTURE_SWIZZLE2_00GR			= 0x00001000U,	///< The texture format is swizzled to ABGR form as 00GR
	SCE_GXM_TEXTURE_SWIZZLE2_GRRR			= 0x00002000U,	///< The texture format is swizzled to ABGR form as GRRR
	SCE_GXM_TEXTURE_SWIZZLE2_RGGG			= 0x00003000U,	///< The texture format is swizzled to ABGR form as RGGG
	SCE_GXM_TEXTURE_SWIZZLE2_GRGR			= 0x00004000U,	///< The texture format is swizzled to ABGR form as GRGR
	SCE_GXM_TEXTURE_SWIZZLE2_00RG			= 0x00005000U	///< The texture format is swizzled to ABGR form as 00RG
} SceGxmTextureSwizzle2Mode;

/** Defines the result layout of 2-component texture formats which can be swizzled.

	@ingroup render
*/
typedef enum SceGxmTextureSwizzle2ModeAlt {
	SCE_GXM_TEXTURE_SWIZZLE2_SD				= 0x00000000U,	///< The depth/stencil texture format read in SD order
	SCE_GXM_TEXTURE_SWIZZLE2_DS				= 0x00001000U	///< The depth/stencil texture format read in DS order
} SceGxmTextureSwizzle2ModeAlt;

/** Defines the result layout of 1-component texture formats which can be swizzled.

	@ingroup render
*/
typedef enum SceGxmTextureSwizzle1Mode {
	SCE_GXM_TEXTURE_SWIZZLE1_R				= 0x00000000U,	///< Texture format is swizzled to ABGR form as XXXR (where X is undefined)
	SCE_GXM_TEXTURE_SWIZZLE1_000R			= 0x00001000U,	///< Texture format is swizzled to ABGR form as 000R
	SCE_GXM_TEXTURE_SWIZZLE1_111R			= 0x00002000U,	///< Texture format is swizzled to ABGR form as 111R
	SCE_GXM_TEXTURE_SWIZZLE1_RRRR			= 0x00003000U,	///< Texture format is swizzled to ABGR form as RRRR
	SCE_GXM_TEXTURE_SWIZZLE1_0RRR			= 0x00004000U,	///< Texture format is swizzled to ABGR form as 0RRR
	SCE_GXM_TEXTURE_SWIZZLE1_1RRR			= 0x00005000U,	///< Texture format is swizzled to ABGR form as 1RRR
	SCE_GXM_TEXTURE_SWIZZLE1_R000			= 0x00006000U,	///< Texture format is swizzled to ABGR form as R000
	SCE_GXM_TEXTURE_SWIZZLE1_R111			= 0x00007000U	///< Texture format is swizzled to ABGR form as R111
} SceGxmTextureSwizzle1Mode;

/** Defines the memory layout of YUV422 texture formats.

	@ingroup render
*/
typedef enum SceGxmTextureSwizzleYUV422Mode {
	SCE_GXM_TEXTURE_SWIZZLE_YUYV_CSC0		= 0x00000000U,	///< Texture format read in Y1UY0V order, using CSC matrix 0
	SCE_GXM_TEXTURE_SWIZZLE_YVYU_CSC0		= 0x00001000U,	///< Texture format read in Y1VY0U order, using CSC matrix 0
	SCE_GXM_TEXTURE_SWIZZLE_UYVY_CSC0		= 0x00002000U,	///< Texture format read in UY1VY0 order, using CSC matrix 0
	SCE_GXM_TEXTURE_SWIZZLE_VYUY_CSC0		= 0x00003000U,	///< Texture format read in VY1UY0 order, using CSC matrix 0
	SCE_GXM_TEXTURE_SWIZZLE_YUYV_CSC1		= 0x00004000U,	///< Texture format read in Y1UY0V order, using CSC matrix 1
	SCE_GXM_TEXTURE_SWIZZLE_YVYU_CSC1		= 0x00005000U,	///< Texture format read in Y1VY0U order, using CSC matrix 1
	SCE_GXM_TEXTURE_SWIZZLE_UYVY_CSC1		= 0x00006000U,	///< Texture format read in UY1VY0 order, using CSC matrix 1
	SCE_GXM_TEXTURE_SWIZZLE_VYUY_CSC1		= 0x00007000U	///< Texture format read in VY1UY0 order, using CSC matrix 1
} SceGxmTextureSwizzleYUV422Mode;

/** Defines the memory layout of YUV420 texture formats.

	@ingroup render
*/
typedef enum SceGxmTextureSwizzleYUV420Mode {
	SCE_GXM_TEXTURE_SWIZZLE_YUV_CSC0		= 0x00000000U,	///< Texture planes read in YUV order, using CSC matrix 0
	SCE_GXM_TEXTURE_SWIZZLE_YVU_CSC0		= 0x00001000U,	///< Texture planes read in YVU order, using CSC matrix 0
	SCE_GXM_TEXTURE_SWIZZLE_YUV_CSC1		= 0x00002000U,	///< Texture planes read in YUV order, using CSC matrix 1
	SCE_GXM_TEXTURE_SWIZZLE_YVU_CSC1		= 0x00003000U	///< Texture planes read in YVU order, using CSC matrix 1
} SceGxmTextureSwizzleYUV420Mode;

/** The base formats for textures.  A texture format is made from (bitwise) combining
	a base format with a compatible swizzle.

	@ingroup render
*/
typedef enum SceGxmTextureBaseFormat {
	SCE_GXM_TEXTURE_BASE_FORMAT_U8					= 0x00000000U,	///< 8-bit format, 8-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S8					= 0x01000000U,	///< 8-bit format, 8-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4			= 0x02000000U,	///< 16-bit format, 4x 4-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U8U3U3U2			= 0x03000000U,	///< 16-bit format, 8-bit unsigned, 3-bit unsigned, 3-bit unsigned and 2-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5			= 0x04000000U,	///< 16-bit format, 1-bit unsigned and 3x 5-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U5U6U5				= 0x05000000U,	///< 16-bit format, 5-bit unsigned, 6-bit unsigned and 5-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S5S5U6				= 0x06000000U,	///< 16-bit format, 5-bit signed, 5-bit signed and 6-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U8U8				= 0x07000000U,	///< 16-bit format, 2x 8-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S8S8				= 0x08000000U,	///< 16-bit format, 2x 8-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U16					= 0x09000000U,	///< 16-bit format, 16-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S16					= 0x0a000000U,	///< 16-bit format, 16-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_F16					= 0x0b000000U,	///< 16-bit format, 16-bit s1e5m10 floating point
	SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8			= 0x0c000000U,	///< 32-bit format, 4x 8-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8			= 0x0d000000U,	///< 32-bit format, 4x 8-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10			= 0x0e000000U,	///< 32-bit format, 2-bit unsigned and 3x 10-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U16U16				= 0x0f000000U,	///< 32-bit format, 2x 16-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S16S16				= 0x10000000U,	///< 32-bit format, 2x 16-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_F16F16				= 0x11000000U,	///< 32-bit format, 2x 16-bit s1e5m10 floating point
	SCE_GXM_TEXTURE_BASE_FORMAT_F32					= 0x12000000U,	///< 32-bit format, 32-bit floating point
	SCE_GXM_TEXTURE_BASE_FORMAT_F32M				= 0x13000000U,	///< 32-bit format, 32-bit floating point with sign bit masked off
	SCE_GXM_TEXTURE_BASE_FORMAT_X8S8S8U8			= 0x14000000U,	///< 32-bit format, 8-bit unused, 8-bit signed, 8-bit signed and 8-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_X8U24				= 0x15000000U,	///< 32-bit format, 8-bit unused, 24-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U32					= 0x17000000U,	///< 32-bit format, 32-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S32					= 0x18000000U,	///< 32-bit format, 32-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_SE5M9M9M9			= 0x19000000U,	///< 32-bit format, 5-bit shared exponent and 3x 9-bit floating point mantissa
	SCE_GXM_TEXTURE_BASE_FORMAT_F11F11F10			= 0x1a000000U,	///< 32-bit format, 2x 11-bit s0e5m6 floating point and 10-bit s0e5m5 floating point
	SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16		= 0x1b000000U,	///< 64-bit format, 4x 16-bit s1e5m10 floating point
	SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16		= 0x1c000000U,	///< 64-bit format, 4x 16-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16		= 0x1d000000U,	///< 64-bit format, 4x 16-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_F32F32				= 0x1e000000U,	///< 64-bit format, 2x 32-bit floating point
	SCE_GXM_TEXTURE_BASE_FORMAT_U32U32				= 0x1f000000U,	///< 64-bit format, 2x 32-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_PVRT2BPP			= 0x80000000U,	///< Block compressed PVRT1, 2 bits per pixel mode
	SCE_GXM_TEXTURE_BASE_FORMAT_PVRT4BPP			= 0x81000000U,	///< Block compressed PVRT1, 4 bits per pixel mode
	SCE_GXM_TEXTURE_BASE_FORMAT_PVRTII2BPP			= 0x82000000U,	///< Block compressed PVRT2, 2 bits per pixel mode
	SCE_GXM_TEXTURE_BASE_FORMAT_PVRTII4BPP			= 0x83000000U,	///< Block compressed PVRT2, 4 bits per pixel mode
	SCE_GXM_TEXTURE_BASE_FORMAT_UBC1				= 0x85000000U,	///< Block compressed UBC1 (aka DXT1), 4 bits per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_UBC2				= 0x86000000U,	///< Block compressed UBC2 (aka DXT3), 8 bits per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_UBC3				= 0x87000000U,	///< Block compressed UBC3 (aka DXT5), 8 bits per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_UBC4				= 0x88000000U,	///< Block compressed UBC4, 4 bits per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_SBC4				= 0x89000000U,	///< Block compressed SBC4, 4 bits per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_UBC5				= 0x8A000000U,	///< Block compressed UBC5, 8 bits per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_SBC5				= 0x8B000000U,	///< Block compressed SBC5, 8 bits per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2			= 0x90000000U,	///< Y plane, interleaved UV plane
	SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3			= 0x91000000U,	///< Y plane, U plane, V plane
	SCE_GXM_TEXTURE_BASE_FORMAT_YUV422				= 0x92000000U,	///< Interleaved YUV
	SCE_GXM_TEXTURE_BASE_FORMAT_P4					= 0x94000000U,	///< Palettized format, 4-bit palette index per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_P8					= 0x95000000U,	///< Palettized format, 8-bit palette index per pixel
	SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8				= 0x98000000U,	///< 24-bit packed format, 3x 8-bit unsigned integer
	SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8				= 0x99000000U,	///< 24-bit packed format, 3x 8-bit signed integer
	SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10			= 0x9a000000U	///< 32-bit format, 2-bit unsigned integer and 3x 10-bit s0e5m5 floating point
} SceGxmTextureBaseFormat;

/** The texture formats.

	These are split into two sections: the full list of all texture formats
	supported by the hardware, followed by some legacy defines for convenience.
	The full list uses a standard syntax of <c>FORMAT_SWIZZLE</c>.

	The format part of the name is written for high-to-low bit ordering assuming
	the value is in a register.  Note that registers are stored in memory in a
	little-endian format.

	For 4 and 3-component formats in memory, the swizzle part of the name is the
	component ordering in the value loaded from memory.  For example, a texel of
	format #SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_ABGR would have A in the high 4 bits
	and R in the low 4 bits if the 16-bit value was loaded into a register.

	For 2 and 1-component formats in memory, the format in memory is always GR or
	R and the swizzle represents the mapping to an ABGR (or WZYX) result in the
	shader code.  For example, the format #SCE_GXM_TEXTURE_FORMAT_U8_000R would
	return zero in the ABG components and the U8 value in the R component.

	The depth/stencil format X8U24 is an exception and behaves like the 4 and
	3-component formats: the swizzle part of the name is the component ordering
	in memory, and the result is always returned with D in the x component.  Because of this,
	the format can only be used with single-component query formats.

	For a full table of all texture base formats, swizzles and supported query
	formats please refer to the <em>GPU User’s Guide</em>, Appendix A.

	@ingroup render
*/
typedef enum SceGxmTextureFormat {
	// Full list of supported texture formats

	SCE_GXM_TEXTURE_FORMAT_U8_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The U8 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The U8 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The U8 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The U8 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The U8 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The U8 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The U8 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8_R					= SCE_GXM_TEXTURE_BASE_FORMAT_U8 | SCE_GXM_TEXTURE_SWIZZLE1_R,				///< The U8 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_S8_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The S8 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The S8 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The S8 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The S8 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The S8 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The S8 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The S8 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8_R					= SCE_GXM_TEXTURE_BASE_FORMAT_S8 | SCE_GXM_TEXTURE_SWIZZLE1_R,	 			///< The S8 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,		///< The U4U4U4U4 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_ARGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,		///< The U4U4U4U4 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_RGBA		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,		///< The U4U4U4U4 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_BGRA		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,		///< The U4U4U4U4 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X4U4U4U4_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,		///< The U4U4U4U4 data is read in ABGR order from memory, A is replaced with 0xf.
	SCE_GXM_TEXTURE_FORMAT_X4U4U4U4_1RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,		///< The U4U4U4U4 data is read in ARGB order from memory, A is replaced with 0xf.
	SCE_GXM_TEXTURE_FORMAT_U4U4U4X4_RGB1		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,		///< The U4U4U4U4 data is read in RGBA order from memory, A is replaced with 0xf.
	SCE_GXM_TEXTURE_FORMAT_U4U4U4X4_BGR1		= SCE_GXM_TEXTURE_BASE_FORMAT_U4U4U4U4 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,		///< The U4U4U4U4 data is read in BGRA order from memory, A is replaced with 0xf.

	SCE_GXM_TEXTURE_FORMAT_U8U3U3U2_ARGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U3U3U2,										///< The U8U3U3U2 data is read in ARGB order from memory.

	SCE_GXM_TEXTURE_FORMAT_U1U5U5U5_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,		///< The U1U5U5U5 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_U1U5U5U5_ARGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,		///< The U1U5U5U5 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_U5U5U5U1_RGBA		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,		///< The U5U5U5U1 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_U5U5U5U1_BGRA		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,		///< The U5U5U5U1 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X1U5U5U5_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,		///< The U1U5U5U5 data is read in ABGR order from memory, A is replaced with 1.
	SCE_GXM_TEXTURE_FORMAT_X1U5U5U5_1RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,		///< The U1U5U5U5 data is read in ARGB order from memory, A is replaced with 1.
	SCE_GXM_TEXTURE_FORMAT_U5U5U5X1_RGB1		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,		///< The U5U5U5U1 data is read in RGBA order from memory, A is replaced with 1.
	SCE_GXM_TEXTURE_FORMAT_U5U5U5X1_BGR1		= SCE_GXM_TEXTURE_BASE_FORMAT_U1U5U5U5 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,		///< The U5U5U5U1 data is read in BGRA order from memory, A is replaced with 1.

	SCE_GXM_TEXTURE_FORMAT_U5U6U5_BGR			= SCE_GXM_TEXTURE_BASE_FORMAT_U5U6U5 | SCE_GXM_TEXTURE_SWIZZLE3_BGR,		///< The U5U6U5 data is read in BGR order from memory, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_U5U6U5_RGB			= SCE_GXM_TEXTURE_BASE_FORMAT_U5U6U5 | SCE_GXM_TEXTURE_SWIZZLE3_RGB,		///< The U5U6U5 data is read in RGB order from memory, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_U6S5S5_BGR			= SCE_GXM_TEXTURE_BASE_FORMAT_S5S5U6 | SCE_GXM_TEXTURE_SWIZZLE3_BGR,		///< The U6S5S5 data is read in BGR order from memory, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_S5S5U6_RGB			= SCE_GXM_TEXTURE_BASE_FORMAT_S5S5U6 | SCE_GXM_TEXTURE_SWIZZLE3_RGB,		///< The S5S5U6 data is read in RGB order from memory, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_U8U8_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,			///< The U8U8 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8U8_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,			///< The U8U8 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8U8_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,			///< The U8U8 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8U8_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,			///< The U8U8 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8U8_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,			///< The U8U8 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U8U8_GR				= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8 | SCE_GXM_TEXTURE_SWIZZLE2_GR,			///< The U8U8 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_S8S8_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,			///< The S8S8 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8S8_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,			///< The S8S8 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8S8_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,			///< The S8S8 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8S8_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,			///< The S8S8 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8S8_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,			///< The S8S8 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S8S8_GR				= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8 | SCE_GXM_TEXTURE_SWIZZLE2_GR,   		///< The S8S8 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_U16_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The U16 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The U16 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The U16 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The U16 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The U16 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The U16 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The U16 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16_R				= SCE_GXM_TEXTURE_BASE_FORMAT_U16 | SCE_GXM_TEXTURE_SWIZZLE1_R,	  			///< The U16 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_S16_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The S16 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The S16 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The S16 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The S16 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The S16 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The S16 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The S16 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16_R				= SCE_GXM_TEXTURE_BASE_FORMAT_S16 | SCE_GXM_TEXTURE_SWIZZLE1_R,	  			///< The S16 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_F16_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The F16 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The F16 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The F16 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The F16 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The F16 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The F16 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The F16 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16_R				= SCE_GXM_TEXTURE_BASE_FORMAT_F16 | SCE_GXM_TEXTURE_SWIZZLE1_R,	  			///< The F16 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,		///< The U8U8U8U8 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,		///< The U8U8U8U8 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_RGBA		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,		///< The U8U8U8U8 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_BGRA		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,		///< The U8U8U8U8 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X8U8U8U8_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,		///< The U8U8U8U8 data is read in ABGR order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_X8U8U8U8_1RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,		///< The U8U8U8U8 data is read in ARGB order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_U8U8U8X8_RGB1		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,		///< The U8U8U8U8 data is read in RGBA order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_U8U8U8X8_BGR1		= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,		///< The U8U8U8U8 data is read in BGRA order from memory, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_S8S8S8S8_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,		///< The S8S8S8S8 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_S8S8S8S8_ARGB		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,		///< The S8S8S8S8 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_S8S8S8S8_RGBA		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,		///< The S8S8S8S8 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_S8S8S8S8_BGRA		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,		///< The S8S8S8S8 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X8S8S8S8_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,		///< The S8S8S8S8 data is read in ABGR order from memory, A is replaced with 0x7f.
	SCE_GXM_TEXTURE_FORMAT_X8S8S8S8_1RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,		///< The S8S8S8S8 data is read in ARGB order from memory, A is replaced with 0x7f.
	SCE_GXM_TEXTURE_FORMAT_S8S8S8X8_RGB1		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,		///< The S8S8S8S8 data is read in RGBA order from memory, A is replaced with 0x7f.
	SCE_GXM_TEXTURE_FORMAT_S8S8S8X8_BGR1		= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,		///< The S8S8S8S8 data is read in BGRA order from memory, A is replaced with 0x7f.

	SCE_GXM_TEXTURE_FORMAT_U2U10U10U10_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,	///< The U2U10U10U10 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_U2U10U10U10_ARGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,	///< The U2U10U10U10 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_U10U10U10U2_RGBA		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,	///< The U10U10U10U2 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_U10U10U10U2_BGRA		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,	///< The U10U10U10U2 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X2U10U10U10_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,	///< The U2U10U10U10 data is read in ABGR order from memory, A is replaced with 0x3.
	SCE_GXM_TEXTURE_FORMAT_X2U10U10U10_1RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,	///< The U2U10U10U10 data is read in ARGB order from memory, A is replaced with 0x3.
	SCE_GXM_TEXTURE_FORMAT_U10U10U10X2_RGB1		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,	///< The U10U10U10U2 data is read in RGBA order from memory, A is replaced with 0x3.
	SCE_GXM_TEXTURE_FORMAT_U10U10U10X2_BGR1		= SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,	///< The U10U10U10U2 data is read in BGRA order from memory, A is replaced with 0x3.

	SCE_GXM_TEXTURE_FORMAT_U16U16_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,		///< The U16U16 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16U16_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,		///< The U16U16 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16U16_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,		///< The U16U16 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16U16_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,		///< The U16U16 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16U16_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,		///< The U16U16 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U16U16_GR			= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16 | SCE_GXM_TEXTURE_SWIZZLE2_GR,	  		///< The U16U16 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_S16S16_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,		///< The S16S16 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16S16_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,		///< The S16S16 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16S16_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,		///< The S16S16 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16S16_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,		///< The S16S16 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16S16_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,		///< The S16S16 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S16S16_GR			= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16 | SCE_GXM_TEXTURE_SWIZZLE2_GR,	  		///< The S16S16 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_F16F16_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,		///< The F16F16 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16F16_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,		///< The F16F16 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16F16_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,		///< The F16F16 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16F16_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,		///< The F16F16 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16F16_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,		///< The F16F16 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F16F16_GR			= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16 | SCE_GXM_TEXTURE_SWIZZLE2_GR,	  		///< The F16F16 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_F32_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The F32 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The F32 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The F32 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The F32 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The F32 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The F32 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The F32 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32_R				= SCE_GXM_TEXTURE_BASE_FORMAT_F32 | SCE_GXM_TEXTURE_SWIZZLE1_R,	  			///< The F32 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_F32M_000R			= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The F32M value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32M_111R			= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The F32M value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32M_RRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The F32M value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32M_0RRR			= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The F32M value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32M_1RRR			= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The F32M value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32M_R000			= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The F32M value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32M_R111			= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The F32M value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32M_R				= SCE_GXM_TEXTURE_BASE_FORMAT_F32M | SCE_GXM_TEXTURE_SWIZZLE1_R,   			///< The F32M value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_X8S8S8U8_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_X8S8S8U8 | SCE_GXM_TEXTURE_SWIZZLE3_BGR,		///< The U8S8S8U8 data is read in ABGR order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_X8U8S8S8_1RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_X8S8S8U8 | SCE_GXM_TEXTURE_SWIZZLE3_RGB,		///< The U8U8S8S8 data is read in ARGB order from memory, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_X8U24_SD				= SCE_GXM_TEXTURE_BASE_FORMAT_X8U24 | SCE_GXM_TEXTURE_SWIZZLE2_SD,			///< The U8U24 data is read in SD order, D is returned as a single component result.
	SCE_GXM_TEXTURE_FORMAT_U24X8_DS				= SCE_GXM_TEXTURE_BASE_FORMAT_X8U24 | SCE_GXM_TEXTURE_SWIZZLE2_DS,			///< The U24U8 data is read in DS order, D is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_U32_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The U32 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The U32 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The U32 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The U32 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The U32 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The U32 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The U32 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32_R				= SCE_GXM_TEXTURE_BASE_FORMAT_U32 | SCE_GXM_TEXTURE_SWIZZLE1_R,	  			///< The U32 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_S32_000R				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The S32 value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S32_111R				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The S32 value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S32_RRRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The S32 value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S32_0RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The S32 value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S32_1RRR				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The S32 value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S32_R000				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The S32 value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S32_R111				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The S32 value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_S32_R				= SCE_GXM_TEXTURE_BASE_FORMAT_S32 | SCE_GXM_TEXTURE_SWIZZLE1_R,	  			///< The S32 value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_SE5M9M9M9_BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_SE5M9M9M9 | SCE_GXM_TEXTURE_SWIZZLE3_BGR,		///< The SE5M9M9M9 data is read in EBGR order from memory, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_SE5M9M9M9_RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_SE5M9M9M9 | SCE_GXM_TEXTURE_SWIZZLE3_RGB,		///< The SE5M9M9M9 data is read in ERGB order from memory, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_F10F11F11_BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_F11F11F10 | SCE_GXM_TEXTURE_SWIZZLE3_BGR,		///< The F10F11F11 data is read in BGR order from memory, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_F11F11F10_RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_F11F11F10 | SCE_GXM_TEXTURE_SWIZZLE3_RGB,		///< The F11F11F10 data is read in RGB order from memory, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_F16F16F16F16_ABGR	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,	///< The F16F16F16F16 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_F16F16F16F16_ARGB	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,	///< The F16F16F16F16 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_F16F16F16F16_RGBA	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,	///< The F16F16F16F16 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_F16F16F16F16_BGRA	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,	///< The F16F16F16F16 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X16F16F16F16_1BGR	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,	///< The F16F16F16F16 data is read in ABGR order from memory, A is replaced with 0x3c00.
	SCE_GXM_TEXTURE_FORMAT_X16F16F16F16_1RGB	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,	///< The F16F16F16F16 data is read in ARGB order from memory, A is replaced with 0x3c00.
	SCE_GXM_TEXTURE_FORMAT_F16F16F16X16_RGB1	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,	///< The F16F16F16F16 data is read in RGBA order from memory, A is replaced with 0x3c00.
	SCE_GXM_TEXTURE_FORMAT_F16F16F16X16_BGR1	= SCE_GXM_TEXTURE_BASE_FORMAT_F16F16F16F16 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,	///< The F16F16F16F16 data is read in BGRA order from memory, A is replaced with 0x3c00.

	SCE_GXM_TEXTURE_FORMAT_U16U16U16U16_ABGR	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,	///< The U16U16U16U16 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_U16U16U16U16_ARGB	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,	///< The U16U16U16U16 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_U16U16U16U16_RGBA	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,	///< The U16U16U16U16 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_U16U16U16U16_BGRA	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,	///< The U16U16U16U16 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X16U16U16U16_1BGR	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,	///< The U16U16U16U16 data is read in ABGR order from memory, A is replaced with 0xffff.
	SCE_GXM_TEXTURE_FORMAT_X16U16U16U16_1RGB	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,	///< The U16U16U16U16 data is read in ARGB order from memory, A is replaced with 0xffff.
	SCE_GXM_TEXTURE_FORMAT_U16U16U16X16_RGB1	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,	///< The U16U16U16U16 data is read in RGBA order from memory, A is replaced with 0xffff.
	SCE_GXM_TEXTURE_FORMAT_U16U16U16X16_BGR1	= SCE_GXM_TEXTURE_BASE_FORMAT_U16U16U16U16 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,	///< The U16U16U16U16 data is read in BGRA order from memory, A is replaced with 0xffff.

	SCE_GXM_TEXTURE_FORMAT_S16S16S16S16_ABGR	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,	///< The S16S16S16S16 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_S16S16S16S16_ARGB	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,	///< The S16S16S16S16 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_S16S16S16S16_RGBA	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,	///< The S16S16S16S16 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_S16S16S16S16_BGRA	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,	///< The S16S16S16S16 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X16S16S16S16_1BGR	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,	///< The S16S16S16S16 data is read in ABGR order from memory, A is replaced with 0x7fff.
	SCE_GXM_TEXTURE_FORMAT_X16S16S16S16_1RGB	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,	///< The S16S16S16S16 data is read in ARGB order from memory, A is replaced with 0x7fff.
	SCE_GXM_TEXTURE_FORMAT_S16S16S16X16_RGB1	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,	///< The S16S16S16S16 data is read in RGBA order from memory, A is replaced with 0x7fff.
	SCE_GXM_TEXTURE_FORMAT_S16S16S16X16_BGR1	= SCE_GXM_TEXTURE_BASE_FORMAT_S16S16S16S16 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,	///< The S16S16S16S16 data is read in BGRA order from memory, A is replaced with 0x7fff.

	SCE_GXM_TEXTURE_FORMAT_F32F32_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_F32F32 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,		///< The F32F32 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32F32_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_F32F32 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,		///< The F32F32 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32F32_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_F32F32 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,		///< The F32F32 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32F32_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_F32F32 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,		///< The F32F32 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32F32_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_F32F32 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,		///< The F32F32 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_F32F32_GR			= SCE_GXM_TEXTURE_BASE_FORMAT_F32F32 | SCE_GXM_TEXTURE_SWIZZLE2_GR,			///< The F32F32 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_U32U32_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_U32U32 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,		///< The U32U32 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32U32_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_U32U32 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,		///< The U32U32 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32U32_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_U32U32 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,		///< The U32U32 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32U32_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_U32U32 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,		///< The U32U32 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32U32_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_U32U32 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,		///< The U32U32 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_U32U32_GR			= SCE_GXM_TEXTURE_BASE_FORMAT_U32U32 | SCE_GXM_TEXTURE_SWIZZLE2_GR,			///< The U32U32 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_PVRT2BPP_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRT2BPP | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,		///< The PVRT2BPP data is decoded into ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRT2BPP_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRT2BPP | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,		///< The PVRT2BPP data is decoded into ABGR, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_PVRT4BPP_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRT4BPP | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,		///< The PVRT4BPP data is decoded into ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRT4BPP_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRT4BPP | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,		///< The PVRT4BPP data is decoded into ABGR, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_PVRTII2BPP_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRTII2BPP | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,	///< The PVRTII2BPP data is decoded into ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRTII2BPP_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRTII2BPP | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,	///< The PVRTII2BPP data is decoded into ABGR, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_PVRTII4BPP_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRTII4BPP | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,	///< The PVRTII4BPP data is decoded into ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRTII4BPP_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_PVRTII4BPP | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,	///< The PVRTII4BPP data is decoded into ABGR, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_UBC1_ABGR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC1 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,			///< The UBC1 data is decoded into ABGR.
	SCE_GXM_TEXTURE_FORMAT_UBC1_1BGR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC1 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,			///< The UBC1 data is decoded into ABGR, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_UBC2_ABGR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC2 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,			///< The UBC2 data is decoded into ABGR.
	SCE_GXM_TEXTURE_FORMAT_UBC2_1BGR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC2 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,			///< The UBC2 data is decoded into ABGR, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_UBC3_ABGR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC3 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,			///< The UBC3 data is decoded into ABGR.
	SCE_GXM_TEXTURE_FORMAT_UBC3_1BGR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC3 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,			///< The UBC3 data is decoded into ABGR, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_UBC4_000R			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The decoded UBC4 (R) value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC4_111R			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The decoded UBC4 (R) value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC4_RRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The decoded UBC4 (R) value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC4_0RRR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The decoded UBC4 (R) value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC4_1RRR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The decoded UBC4 (R) value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC4_R000			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The decoded UBC4 (R) value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC4_R111			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The decoded UBC4 (R) value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC4_R				= SCE_GXM_TEXTURE_BASE_FORMAT_UBC4 | SCE_GXM_TEXTURE_SWIZZLE1_R,			///< The decoded UBC4 (R) value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_SBC4_000R			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_000R,			///< The decoded SBC4 (R) value is swizzled to 000R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC4_111R			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_111R,			///< The decoded SBC4 (R) value is swizzled to 111R (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC4_RRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_RRRR,			///< The decoded SBC4 (R) value is swizzled to RRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC4_0RRR			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_0RRR,			///< The decoded SBC4 (R) value is swizzled to 0RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC4_1RRR			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_1RRR,			///< The decoded SBC4 (R) value is swizzled to 1RRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC4_R000			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_R000,			///< The decoded SBC4 (R) value is swizzled to R000 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC4_R111			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_R111,			///< The decoded SBC4 (R) value is swizzled to R111 (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC4_R				= SCE_GXM_TEXTURE_BASE_FORMAT_SBC4 | SCE_GXM_TEXTURE_SWIZZLE1_R,			///< The decoded SBC4 (R) value is returned as a single component result.

	SCE_GXM_TEXTURE_FORMAT_UBC5_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC5 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,			///< The decoded UBC5 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC5_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC5 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,			///< The decoded UBC5 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC5_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC5 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,			///< The decoded UBC5 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC5_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC5 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,			///< The decoded UBC5 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC5_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_UBC5 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,			///< The decoded UBC5 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_UBC5_GR				= SCE_GXM_TEXTURE_BASE_FORMAT_UBC5 | SCE_GXM_TEXTURE_SWIZZLE2_GR,			///< The decoded UBC5 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_SBC5_00GR			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC5 | SCE_GXM_TEXTURE_SWIZZLE2_00GR,			///< The decoded SBC5 (GR) value is swizzled to 00GR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC5_GRRR			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC5 | SCE_GXM_TEXTURE_SWIZZLE2_GRRR,			///< The decoded SBC5 (GR) value is swizzled to GRRR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC5_RGGG			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC5 | SCE_GXM_TEXTURE_SWIZZLE2_RGGG,			///< The decoded SBC5 (GR) value is swizzled to RGGG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC5_GRGR			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC5 | SCE_GXM_TEXTURE_SWIZZLE2_GRGR,			///< The decoded SBC5 (GR) value is swizzled to GRGR (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC5_00RG			= SCE_GXM_TEXTURE_BASE_FORMAT_SBC5 | SCE_GXM_TEXTURE_SWIZZLE2_00RG,			///< The decoded SBC5 (GR) value is swizzled to 00RG (in ABGR notation).
	SCE_GXM_TEXTURE_FORMAT_SBC5_GR				= SCE_GXM_TEXTURE_BASE_FORMAT_SBC5 | SCE_GXM_TEXTURE_SWIZZLE2_GR,			///< The decoded SBC5 (GR) value is returned as a 2-component result.

	SCE_GXM_TEXTURE_FORMAT_YUV420P2_CSC0		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2 | SCE_GXM_TEXTURE_SWIZZLE_YUV_CSC0,	///< The Y plane and UV plane is converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YVU420P2_CSC0		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2 | SCE_GXM_TEXTURE_SWIZZLE_YVU_CSC0,	///< The Y plane and VU plane is converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YUV420P2_CSC1		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2 | SCE_GXM_TEXTURE_SWIZZLE_YUV_CSC1,	///< The Y plane and UV plane is converted to ABGR using CSC matrix 1, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YVU420P2_CSC1		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P2 | SCE_GXM_TEXTURE_SWIZZLE_YVU_CSC1,	///< The Y plane and VU plane is converted to ABGR using CSC matrix 1, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_YUV420P3_CSC0		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3 | SCE_GXM_TEXTURE_SWIZZLE_YUV_CSC0,	///< The Y plane, U plane and V plane is converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YVU420P3_CSC0		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3 | SCE_GXM_TEXTURE_SWIZZLE_YVU_CSC0,	///< The Y plane, V plane and U plane is converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YUV420P3_CSC1		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3 | SCE_GXM_TEXTURE_SWIZZLE_YUV_CSC1,	///< The Y plane, U plane and V plane is converted to ABGR using CSC matrix 1, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YVU420P3_CSC1		= SCE_GXM_TEXTURE_BASE_FORMAT_YUV420P3 | SCE_GXM_TEXTURE_SWIZZLE_YVU_CSC1,	///< The Y plane, V plane and U plane is converted to ABGR using CSC matrix 1, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_YUYV422_CSC0			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_YUYV_CSC0,	///< Packed YUYV 2-pixel blocks are converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YVYU422_CSC0			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_YVYU_CSC0,	///< Packed YVYU 2-pixel blocks are converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_UYVY422_CSC0			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_UYVY_CSC0,	///< Packed UYVY 2-pixel blocks are converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_VYUY422_CSC0			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_VYUY_CSC0,	///< Packed VYUY 2-pixel blocks are converted to ABGR using CSC matrix 0, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YUYV422_CSC1			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_YUYV_CSC1,	///< Packed YUYV 2-pixel blocks are converted to ABGR using CSC matrix 1, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_YVYU422_CSC1			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_YVYU_CSC1,	///< Packed YVYU 2-pixel blocks are converted to ABGR using CSC matrix 1, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_UYVY422_CSC1			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_UYVY_CSC1,	///< Packed UYVY 2-pixel blocks are converted to ABGR using CSC matrix 1, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_VYUY422_CSC1			= SCE_GXM_TEXTURE_BASE_FORMAT_YUV422 | SCE_GXM_TEXTURE_SWIZZLE_VYUY_CSC1,	///< Packed VYUY 2-pixel blocks are converted to ABGR using CSC matrix 1, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_P4_ABGR				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,			///< The U4 index looks up into a palette of U8U8U8U8 data read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_P4_ARGB				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,			///< The U4 index looks up into a palette of U8U8U8U8 data read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_P4_RGBA				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,			///< The U4 index looks up into a palette of U8U8U8U8 data read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_P4_BGRA				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,			///< The U4 index looks up into a palette of U8U8U8U8 data read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_P4_1BGR				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,			///< The U4 index looks up into a palette of U8U8U8U8 data read in ABGR order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_P4_1RGB				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,			///< The U4 index looks up into a palette of U8U8U8U8 data read in ARGB order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_P4_RGB1				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,			///< The U4 index looks up into a palette of U8U8U8U8 data read in RGBA order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_P4_BGR1				= SCE_GXM_TEXTURE_BASE_FORMAT_P4 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,			///< The U4 index looks up into a palette of U8U8U8U8 data read in BGRA order from memory, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_P8_ABGR				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,			///< The U8 index looks up into a palette of U8U8U8U8 data read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_P8_ARGB				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,			///< The U8 index looks up into a palette of U8U8U8U8 data read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_P8_RGBA				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,			///< The U8 index looks up into a palette of U8U8U8U8 data read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_P8_BGRA				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,			///< The U8 index looks up into a palette of U8U8U8U8 data read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_P8_1BGR				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,			///< The U8 index looks up into a palette of U8U8U8U8 data read in ABGR order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_P8_1RGB				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,			///< The U8 index looks up into a palette of U8U8U8U8 data read in ARGB order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_P8_RGB1				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,			///< The U8 index looks up into a palette of U8U8U8U8 data read in RGBA order from memory, A is replaced with 0xff.
	SCE_GXM_TEXTURE_FORMAT_P8_BGR1				= SCE_GXM_TEXTURE_BASE_FORMAT_P8 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,			///< The U8 index looks up into a palette of U8U8U8U8 data read in BGRA order from memory, A is replaced with 0xff.

	SCE_GXM_TEXTURE_FORMAT_U8U8U8_BGR			= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE3_BGR,		///< The packed 24-bit U8U8U8 data is read in BGR order from memory, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_U8U8U8_RGB			= SCE_GXM_TEXTURE_BASE_FORMAT_U8U8U8 | SCE_GXM_TEXTURE_SWIZZLE3_RGB,		///< The packed 24-bit U8U8U8 data is read in RGB order from memory, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_S8S8S8_BGR			= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE3_BGR,		///< The packed 24-bit S8S8S8 data is read in BGR order from memory, A is implicit and assigned 1.
	SCE_GXM_TEXTURE_FORMAT_S8S8S8_RGB			= SCE_GXM_TEXTURE_BASE_FORMAT_S8S8S8 | SCE_GXM_TEXTURE_SWIZZLE3_RGB,		///< The packed 24-bit S8S8S8 data is read in RGB order from memory, A is implicit and assigned 1.

	SCE_GXM_TEXTURE_FORMAT_U2F10F10F10_ABGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_ABGR,	///< The U2F10F10F10 data is read in ABGR order from memory.
	SCE_GXM_TEXTURE_FORMAT_U2F10F10F10_ARGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_ARGB,	///< The U2F10F10F10 data is read in ARGB order from memory.
	SCE_GXM_TEXTURE_FORMAT_F10F10F10U2_RGBA		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_RGBA,	///< The F10F10F10U2 data is read in RGBA order from memory.
	SCE_GXM_TEXTURE_FORMAT_F10F10F10U2_BGRA		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_BGRA,	///< The F10F10F10U2 data is read in BGRA order from memory.
	SCE_GXM_TEXTURE_FORMAT_X2F10F10F10_1BGR		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_1BGR,	///< The U2F10F10F10 data is read in ABGR order from memory, A is replaced with 0x3.
	SCE_GXM_TEXTURE_FORMAT_X2F10F10F10_1RGB		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_1RGB,	///< The U2F10F10F10 data is read in ARGB order from memory, A is replaced with 0x3.
	SCE_GXM_TEXTURE_FORMAT_F10F10F10X2_RGB1		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_RGB1,	///< The F10F10F10U2 data is read in RGBA order from memory, A is replaced with 0x3.
	SCE_GXM_TEXTURE_FORMAT_F10F10F10X2_BGR1		= SCE_GXM_TEXTURE_BASE_FORMAT_U2F10F10F10 | SCE_GXM_TEXTURE_SWIZZLE4_BGR1,	///< The F10F10F10U2 data is read in BGRA order from memory, A is replaced with 0x3.

	// Legacy formats (defined in terms of full list above)

	SCE_GXM_TEXTURE_FORMAT_L8					= SCE_GXM_TEXTURE_FORMAT_U8_1RRR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8_1RRR.
	SCE_GXM_TEXTURE_FORMAT_A8					= SCE_GXM_TEXTURE_FORMAT_U8_R000,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8_R000.
	SCE_GXM_TEXTURE_FORMAT_R8					= SCE_GXM_TEXTURE_FORMAT_U8_000R,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8_000R.
	SCE_GXM_TEXTURE_FORMAT_A4R4G4B4				= SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_ARGB,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U4U4U4U4_ARGB.
	SCE_GXM_TEXTURE_FORMAT_A1R5G5B5				= SCE_GXM_TEXTURE_FORMAT_U1U5U5U5_ARGB,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U1U5U5U5_ARGB.
	SCE_GXM_TEXTURE_FORMAT_R5G6B5				= SCE_GXM_TEXTURE_FORMAT_U5U6U5_RGB,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U5U6U5_RGB.
	SCE_GXM_TEXTURE_FORMAT_A8L8					= SCE_GXM_TEXTURE_FORMAT_U8U8_GRRR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8U8_GRRR.
	SCE_GXM_TEXTURE_FORMAT_L8A8					= SCE_GXM_TEXTURE_FORMAT_U8U8_RGGG,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8U8_RGGG.
	SCE_GXM_TEXTURE_FORMAT_G8R8					= SCE_GXM_TEXTURE_FORMAT_U8U8_00GR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8U8_00GR.
	SCE_GXM_TEXTURE_FORMAT_L16					= SCE_GXM_TEXTURE_FORMAT_U16_1RRR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U16_1RRR.
	SCE_GXM_TEXTURE_FORMAT_A16					= SCE_GXM_TEXTURE_FORMAT_U16_R000,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U16_R000.
	SCE_GXM_TEXTURE_FORMAT_R16					= SCE_GXM_TEXTURE_FORMAT_U16_000R,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U16_000R.
	SCE_GXM_TEXTURE_FORMAT_D16					= SCE_GXM_TEXTURE_FORMAT_U16_R,				///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U16_R.
	SCE_GXM_TEXTURE_FORMAT_LF16					= SCE_GXM_TEXTURE_FORMAT_F16_1RRR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F16_1RRR.
	SCE_GXM_TEXTURE_FORMAT_AF16					= SCE_GXM_TEXTURE_FORMAT_F16_R000,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F16_R000.
	SCE_GXM_TEXTURE_FORMAT_RF16					= SCE_GXM_TEXTURE_FORMAT_F16_000R,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F16_000R.
	SCE_GXM_TEXTURE_FORMAT_A8R8G8B8				= SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB.
	SCE_GXM_TEXTURE_FORMAT_A8B8G8R8				= SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ABGR.
	SCE_GXM_TEXTURE_FORMAT_AF16LF16				= SCE_GXM_TEXTURE_FORMAT_F16F16_GRRR,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F16F16_GRRR.
	SCE_GXM_TEXTURE_FORMAT_LF16AF16				= SCE_GXM_TEXTURE_FORMAT_F16F16_RGGG,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F16F16_RGGG.
	SCE_GXM_TEXTURE_FORMAT_GF16RF16				= SCE_GXM_TEXTURE_FORMAT_F16F16_00GR,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F16F16_00GR.
	SCE_GXM_TEXTURE_FORMAT_LF32M				= SCE_GXM_TEXTURE_FORMAT_F32M_1RRR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F32M_1RRR.
	SCE_GXM_TEXTURE_FORMAT_AF32M				= SCE_GXM_TEXTURE_FORMAT_F32M_R000,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F32M_R000.
	SCE_GXM_TEXTURE_FORMAT_RF32M				= SCE_GXM_TEXTURE_FORMAT_F32M_000R,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F32M_000R.
	SCE_GXM_TEXTURE_FORMAT_DF32M				= SCE_GXM_TEXTURE_FORMAT_F32M_R,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_F32M_R.
	SCE_GXM_TEXTURE_FORMAT_VYUY					= SCE_GXM_TEXTURE_FORMAT_VYUY422_CSC0,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_VYUY422_CSC0.
	SCE_GXM_TEXTURE_FORMAT_YVYU					= SCE_GXM_TEXTURE_FORMAT_YVYU422_CSC0,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_YVYU422_CSC0.
	SCE_GXM_TEXTURE_FORMAT_UBC1					= SCE_GXM_TEXTURE_FORMAT_UBC1_ABGR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_UBC1_ABGR.
	SCE_GXM_TEXTURE_FORMAT_UBC2					= SCE_GXM_TEXTURE_FORMAT_UBC2_ABGR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_UBC2_ABGR.
	SCE_GXM_TEXTURE_FORMAT_UBC3					= SCE_GXM_TEXTURE_FORMAT_UBC3_ABGR,			///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_UBC3_ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRT2BPP				= SCE_GXM_TEXTURE_FORMAT_PVRT2BPP_ABGR,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_PVRT2BPP_ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRT4BPP				= SCE_GXM_TEXTURE_FORMAT_PVRT4BPP_ABGR,		///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_PVRT4BPP_ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRTII2BPP			= SCE_GXM_TEXTURE_FORMAT_PVRTII2BPP_ABGR,	///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_PVRTII2BPP_ABGR.
	SCE_GXM_TEXTURE_FORMAT_PVRTII4BPP			= SCE_GXM_TEXTURE_FORMAT_PVRTII4BPP_ABGR	///< Legacy name for #SCE_GXM_TEXTURE_FORMAT_PVRTII4BPP_ABGR.
} SceGxmTextureFormat;

/** The texture type.

	@ingroup render
*/
typedef enum SceGxmTextureType {
	SCE_GXM_TEXTURE_SWIZZLED				= 0x00000000U,	///< The texture uses a swizzled memory layout.
	SCE_GXM_TEXTURE_CUBE					= 0x40000000U,	///< The texture uses a (implicitly swizzled) cube memory layout.
	SCE_GXM_TEXTURE_LINEAR					= 0x60000000U,	///< The texture uses a linear memory layout with implicit stride.
	SCE_GXM_TEXTURE_TILED					= 0x80000000U,	///< The texture uses a tiled memory layout.
	SCE_GXM_TEXTURE_SWIZZLED_ARBITRARY		= 0xa0000000U,	///< The texture uses a swizzled memory layout with arbitrary width and height.
	SCE_GXM_TEXTURE_LINEAR_STRIDED			= 0xc0000000U,	///< The texture uses a linear memory layout with an explicit stride value.
	SCE_GXM_TEXTURE_CUBE_ARBITRARY			= 0xe0000000U	///< The texture uses a cube memory layout (implicitly swizzled) with arbitrary width and height.
} SceGxmTextureType;

/** The texture filter mode.

	@ingroup render
*/
typedef enum SceGxmTextureFilter {
	SCE_GXM_TEXTURE_FILTER_POINT			= 0x00000000U,	///< Point sampling
	SCE_GXM_TEXTURE_FILTER_LINEAR			= 0x00000001U	///< Linear filtering
} SceGxmTextureFilter;

/** The mipmap filter mode.

	@ingroup render
*/
typedef enum SceGxmTextureMipFilter {
	SCE_GXM_TEXTURE_MIP_FILTER_DISABLED		= 0x00000000U,	///< Do not filter between mipmaps
	SCE_GXM_TEXTURE_MIP_FILTER_ENABLED		= 0x00000200U	///< Filter between mipmaps
} SceGxmTextureMipFilter;

/** The texture addressing mode.

	The first four modes (#SCE_GXM_TEXTURE_ADDR_REPEAT,
	#SCE_GXM_TEXTURE_ADDR_MIRROR, #SCE_GXM_TEXTURE_ADDR_CLAMP, and
	#SCE_GXM_TEXTURE_ADDR_MIRROR_CLAMP) are only for textures that do not
	provide border data.  They cannot be used if border data is part of the
	texture data.

	The second four modes (#SCE_GXM_TEXTURE_ADDR_REPEAT_IGNORE_BORDER,
	#SCE_GXM_TEXTURE_ADDR_CLAMP_IGNORE_BORDER,
	#SCE_GXM_TEXTURE_ADDR_CLAMP_FULL_BORDER and
	#SCE_GXM_TEXTURE_ADDR_CLAMP_HALF_BORDER) are only for textures of type
	#SCE_GXM_TEXTURE_SWIZZLED or #SCE_GXM_TEXTURE_SWIZZLED_ARBITRARY that provide
	border data.  They cannot be used if border data is not part of the texture
	data or if the texture is not of type #SCE_GXM_TEXTURE_SWIZZLED or
	#SCE_GXM_TEXTURE_SWIZZLED_ARBITRARY.

	The results of address modes #SCE_GXM_TEXTURE_ADDR_REPEAT and
	#SCE_GXM_TEXTURE_ADDR_REPEAT_IGNORE_BORDER are identical.  The first mode is
	for textures where border data <b>is not</b> present, and the second is for
	textures where border data <b>is</b> present. Similarly, the results of
	address modes #SCE_GXM_TEXTURE_ADDR_CLAMP and
	#SCE_GXM_TEXTURE_ADDR_CLAMP_IGNORE_BORDER are identical, but the second mode
	is for textures with border data (even though the data is ignored).

	More detail on texture addressing modes can be found in the <em>GPU
	User’s Guide</em>.

	@ingroup render
*/
typedef enum SceGxmTextureAddrMode {
	/** Addresses the texture using the fractional part of the uv.  This results
		in the texture being repeated along this axis.
	*/
	SCE_GXM_TEXTURE_ADDR_REPEAT					= 0x00000000U,

	/** Alternates between using f and (1 - f), where f is the fractional part
		of the uv.  This results in the texture alternating between flipped
		and non-flipped as it repeats in this axis.
	*/
	SCE_GXM_TEXTURE_ADDR_MIRROR					= 0x00000001U,

	/** Clamps the uv to [0, 1] and does not filter across texture edges when
		filtering is enabled.  This produces a clamped-to-edge result.
	*/
	SCE_GXM_TEXTURE_ADDR_CLAMP					= 0x00000002U,

	/** Clamps the absolute value of the uv to [0, 1] and does not filter across
		texture edges when filtering is enabled.  This results in a texture that
		is mirrored once around 0.
	*/
	SCE_GXM_TEXTURE_ADDR_MIRROR_CLAMP			= 0x00000003U,

	/** Addresses the texture using the fractional part of the uv.  This results
		in the texture being repeated along this axis. Border texels are
		ignored but must be present in the texture data.
	*/
	SCE_GXM_TEXTURE_ADDR_REPEAT_IGNORE_BORDER	= 0x00000004U,

	/** Uses border texels for data outside of [0, 1].  Since the address is not
		clamped, if uv is outside of [0, 1], the filtered result can be 100%
		border texels.
	*/
	SCE_GXM_TEXTURE_ADDR_CLAMP_FULL_BORDER		= 0x00000005U,

	/** Clamps the uv to [0, 1] and does not filter across texture edges when
		filtering is enabled.  This produces a clamped-to-edge result.  Border
		texels are ignored but must be present in the texture data.
	*/
	SCE_GXM_TEXTURE_ADDR_CLAMP_IGNORE_BORDER	= 0x00000006U,

	/** Clamps the uv to [0, 1] and uses border texels for data outside of
		[0, 1] when filtering is enabled.  Since the address is clamped, the
		filtered result can be at most 50% border texels (in this axis).
	*/
	SCE_GXM_TEXTURE_ADDR_CLAMP_HALF_BORDER		= 0x00000007U
} SceGxmTextureAddrMode;

/** The texture gamma mode.

	@note #SCE_GXM_TEXTURE_GAMMA_R and #SCE_GXM_TEXTURE_GAMMA_BGR enumerations
	intentionally share the same value. The implied meaning of the value changes depending
	on the texture format being used. Please see the <em>GPU User’s Guide</em> for details.

	@ingroup render
*/
typedef enum SceGxmTextureGammaMode {
	SCE_GXM_TEXTURE_GAMMA_NONE				= 0x00000000U,	///< No gamma correction on texture read.
	SCE_GXM_TEXTURE_GAMMA_R					= 0x08000000U,	///< Gamma correction is performed for the R component on texture read.
	SCE_GXM_TEXTURE_GAMMA_GR				= 0x18000000U,	///< Gamma correction is performed for the G and R components on texture read.
	SCE_GXM_TEXTURE_GAMMA_BGR				= 0x08000000U	///< Gamma correction is performed for the B, G, and R components on texture read.
} SceGxmTextureGammaMode;

/** The texture normalize mode

	@ingroup render
*/
typedef enum SceGxmTextureNormalizeMode {
	SCE_GXM_TEXTURE_NORMALIZE_DISABLED		= 0x00000000U,	///< No normalization of values during integer-to-float conversion on texture read.
	SCE_GXM_TEXTURE_NORMALIZE_ENABLED		= 0x80000000U	///< Normalize values during integer-to-float conversion on texture read, producing results in the range [0.0, 1.0] for unsigned data and [-1.0, 1.0] for signed data.
} SceGxmTextureNormalizeMode;

/** The index format used in draw calls.

	@ingroup render
*/
typedef enum SceGxmIndexFormat {
	SCE_GXM_INDEX_FORMAT_U16				= 0x00000000U,	///< Uses 16-bit indices
	SCE_GXM_INDEX_FORMAT_U32				= 0x01000000U	///< Uses 32-bit indices (only the low 24 bits are used)
} SceGxmIndexFormat;

/** The index source type for indexing into vertex streams.

	The 16-bit index sources generate more efficient PDS code since they only need to
	implement a 16-bit multiply. However, this imposes restrictions on either the maximum index
	values or maximum instance counts.  Note that it is valid to use
	#SCE_GXM_INDEX_FORMAT_U32 indices with #SCE_GXM_INDEX_SOURCE_INDEX_16BIT as long as
	the actual values are not larger than 16 bit.

	@ingroup render
*/
typedef enum SceGxmIndexSource
{
	SCE_GXM_INDEX_SOURCE_INDEX_16BIT		= 0x00000000U,	///< The stream is indexed using the index values and all values must be less than 64K. However, they can use either U16 or U32 format in memory.
	SCE_GXM_INDEX_SOURCE_INDEX_32BIT		= 0x00000001U,	///< The stream is indexed using the index values.
	SCE_GXM_INDEX_SOURCE_INSTANCE_16BIT		= 0x00000002U,	///< The stream is indexed using the instance number and can only be used with draw calls of up to 64K instances.
	SCE_GXM_INDEX_SOURCE_INSTANCE_32BIT		= 0x00000003U	///< The stream is indexed using the instance number.
} SceGxmIndexSource;

/** Fragment program enable mode.

	When the fragment program is disabled, only the depth/stencil test is performed.  No
	pixels are shaded.  Fragment program can be enabled or disabled independently when using
	two-sided rendering.

	@ingroup render
*/
typedef enum SceGxmFragmentProgramMode
{
	SCE_GXM_FRAGMENT_PROGRAM_DISABLED		= 0x00200000U,	///< Fragment program disabled, no pixels shaded.
	SCE_GXM_FRAGMENT_PROGRAM_ENABLED		= 0x00000000U	///< Fragment program enabled, pixels shaded.
} SceGxmFragmentProgramMode;

/** Depth write enable mode.

	Note that this setting only affects depth writes to the local cache used
	for each tile as it is processed.  To then ensure that tiles are stored to
	memory, the appropriate #SceGxmDepthStencilForceStoreMode should be set on
	the depth/stencil surface.

	@ingroup render
*/
typedef enum SceGxmDepthWriteMode
{
	SCE_GXM_DEPTH_WRITE_DISABLED			= 0x00100000U,	///< Depth writes disabled.
	SCE_GXM_DEPTH_WRITE_ENABLED				= 0x00000000U	///< Depth writes enabled.
} SceGxmDepthWriteMode;

/** Line last pixel fill mode.

	When enabled, the last pixel of a line is filled.

	@ingroup render
*/
typedef enum SceGxmLineFillLastPixelMode
{
	SCE_GXM_LINE_FILL_LAST_PIXEL_DISABLED	= 0x00000000U,	///< The last pixel of a line is not rendered.
	SCE_GXM_LINE_FILL_LAST_PIXEL_ENABLED	= 0x00080000U	///< The last pixel of a line is rendered.
} SceGxmLineFillLastPixelMode;

/** Two-sided mode.

	When two sided mode is enabled, most state can be set independently for front
	and back polygons.  When two sided mode is disabled, the front setting is used for
	both front and back, and setting the back state is unnecessary (and should be avoided).

	@ingroup render
*/
typedef enum SceGxmTwoSidedMode
{
	SCE_GXM_TWO_SIDED_DISABLED				= 0x00000000U,	///< Front setting used for both front and back.
	SCE_GXM_TWO_SIDED_ENABLED				= 0x00000800U	///< Independent front and back setting.
} SceGxmTwoSidedMode;

/** W clamp mode.

	See #sceGxmSetViewport() for a description of how this interacts with the viewport transform.

	@ingroup render
*/
typedef enum SceGxmWClampMode
{
	SCE_GXM_WCLAMP_MODE_DISABLED			= 0x00000000U,	///< No W clamping in the viewport transform.
	SCE_GXM_WCLAMP_MODE_ENABLED				= 0x00008000U	///< W clamping in the viewport transform.
} SceGxmWClampMode;

/** Viewport transform mode.

	When the viewport transform is disabled, vertices are assumed to be output directly
	in screen space coordinates within a range of -1024 to 7167 for each axis. Use of
	coordinates outside of this range may result in incorrect rasterization.
	For a description of the usual transform see #sceGxmSetViewport().

	@ingroup render
*/
typedef enum SceGxmViewportMode
{
	SCE_GXM_VIEWPORT_DISABLED				= 0x00010000U,	///< No viewport transform.
	SCE_GXM_VIEWPORT_ENABLED				= 0x00000000U	///< Use the viewport transform.
} SceGxmViewportMode;

/** W buffering mode.

	Enabled or disable using the W value when building the screen space coordinates during
	the viewport transform.  See #sceGxmSetViewport() for more details.

	@ingroup render
*/
typedef enum SceGxmWBufferMode
{
	SCE_GXM_WBUFFER_DISABLED				= 0x00000000U,	///< Do not use W buffer, use Z buffering.
	SCE_GXM_WBUFFER_ENABLED					= 0x00004000U	///< Use W buffering.
} SceGxmWBufferMode;

/** Depth/stencil surface force load mode.

	@ingroup render
*/
typedef enum SceGxmDepthStencilForceLoadMode
{
	SCE_GXM_DEPTH_STENCIL_FORCE_LOAD_DISABLED	= 0x00000000U,	///< No forced load, depth values are uninitialized at the start of each tile.
	SCE_GXM_DEPTH_STENCIL_FORCE_LOAD_ENABLED	= 0x00000002U	///< Forced load, depth values are loaded from memory at the start of each tile.
} SceGxmDepthStencilForceLoadMode;

/** Depth/stencil surface force store mode.

	@ingroup render
*/
typedef enum SceGxmDepthStencilForceStoreMode
{
	SCE_GXM_DEPTH_STENCIL_FORCE_STORE_DISABLED	= 0x00000000U,	///< No forced store, depth values are not stored to memory at the end of each tile.
	SCE_GXM_DEPTH_STENCIL_FORCE_STORE_ENABLED	= 0x00000004U	///< Forced store, depth values are stored to memory at the end of each tile.
} SceGxmDepthStencilForceStoreMode;

/** Scene flags passed to #sceGxmBeginScene().

	Note that it is valid to set both #SCE_GXM_SCENE_FRAGMENT_SET_DEPENDENCY
	and #SCE_GXM_SCENE_VERTEX_WAIT_FOR_DEPENDENCY. The scene does not end up depending on itself
	because the vertex wait flag is processed first.

	@ingroup render
*/
typedef enum SceGxmSceneFlags
{
	SCE_GXM_SCENE_FRAGMENT_SET_DEPENDENCY		= 0x00000001U,	///< The fragment processing of this scene is used as a dependency for the vertex processing of the next scene to set #SCE_GXM_SCENE_VERTEX_WAIT_FOR_DEPENDENCY.
	SCE_GXM_SCENE_VERTEX_WAIT_FOR_DEPENDENCY	= 0x00000002U,	///< Do not start the vertex processing for this scene until the fragment processing for the last scene to set #SCE_GXM_SCENE_FRAGMENT_SET_DEPENDENCY is complete.
	SCE_GXM_SCENE_FRAGMENT_TRANSFER_SYNC		= 0x00000004U,	///< The fragment processing is strongly ordered with transfers that have #SCE_GXM_TRANSFER_FRAGMENT_SYNC set.
	SCE_GXM_SCENE_VERTEX_TRANSFER_SYNC			= 0x00000008U	///< The vertex processing is strongly ordered with transfers that have #SCE_GXM_TRANSFER_VERTEX_SYNC set.
} SceGxmSceneFlags;

/** Mid-scene flush flags for #sceGxmMidSceneFlush().

	@ingroup render
*/
typedef enum SceGxmMidSceneFlags
{
	SCE_GXM_MIDSCENE_PRESERVE_DEFAULT_UNIFORM_BUFFERS	= 0x00000001U	///< Preserve the vertex default uniform buffer contents during the mid-scene flush.
} SceGxmMidSceneFlags;

/** Color surface scaling mode.

	Specifies the scaling to perform before a whole tile of shaded pixels is stored
	back to memory.

	When using #SCE_GXM_MULTISAMPLE_4X, scaling is optional.  When enabled, the 2x2
	block of samples for each pixel are merged into a single pixel before being stored
	to memory.  When disabled, raw samples are stored to memory.

	When using #SCE_GXM_MULTISAMPLE_2X, scaling must be enabled.  The 2x1 block of
	samples for each pixel are merged to a single pixel before being stored to memory.

	When using #SCE_GXM_MULTISAMPLE_NONE, scaling is optional.  When enabled, a 2x2
	downscale operation is applied to the pixels before they are stored to memory.  When
	disabled, pixels are stored to memory directly.

	@ingroup render
*/
typedef enum SceGxmColorSurfaceScaleMode
{
	SCE_GXM_COLOR_SURFACE_SCALE_NONE			= 0x00000000U,	///< Do not apply scaling. This enumerator may not be used when rendering with a 2xMSAA render target.
	SCE_GXM_COLOR_SURFACE_SCALE_MSAA_DOWNSCALE	= 0x00000001U	///< Downscale samples to pixel level, or perform a 2x2 downscale when rendering without MSAA.
} SceGxmColorSurfaceScaleMode;

/** Output register size used by the color surface.  This field instructs the
	GPU to ensure that there is either exactly 32 bits or 64 bits of on-chip
	storage (called the “output register”) per pixel.

	@ingroup render
*/
typedef enum SceGxmOutputRegisterSize
{
	SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT			= 0x00000000U,	///< Output register size is 32-bit.
	SCE_GXM_OUTPUT_REGISTER_SIZE_64BIT			= 0x00000001U	///< Output register size is 64-bit.
} SceGxmOutputRegisterSize;

/** Visibility test mode.

	@ingroup render
*/
typedef enum SceGxmVisibilityTestMode {
	SCE_GXM_VISIBILITY_TEST_DISABLED			= 0x00000000U,	///< Visibility test disabled.
	SCE_GXM_VISIBILITY_TEST_ENABLED				= 0x00004000U	///< Visibility test enabled.
} SceGxmVisibilityTestMode;

/** Operation to perform during visibility test.

	@ingroup render
*/
typedef enum SceGxmVisibilityTestOp {
	SCE_GXM_VISIBILITY_TEST_OP_INCREMENT		= 0x00000000U,	///< Increment the count for each visible pixel.
	SCE_GXM_VISIBILITY_TEST_OP_SET				= 0x00040000U	///< Set the count to a non-zero value if any pixel is visible.
} SceGxmVisibilityTestOp;


/** YUV profile.

	@ingroup render
*/
typedef enum SceGxmYuvProfile {
	SCE_GXM_YUV_PROFILE_BT601_STANDARD,		///< BT.601 with brightness range from 16-235 and color difference values from 16-240.
	SCE_GXM_YUV_PROFILE_BT709_STANDARD,		///< BT.709 with brightness range from 16-235 and color difference values from 16-240.
	SCE_GXM_YUV_PROFILE_BT601_FULL_RANGE,	///< BT.601 with brightness range from 0-255 and color difference values from 0-255.
	SCE_GXM_YUV_PROFILE_BT709_FULL_RANGE	///< BT.709 with brightness range from 0-255 and color difference values from 0-255.
} SceGxmYuvProfile;

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_CONSTANTS_H_ */
