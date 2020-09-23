#ifndef _DOLCESDK_PSP2_GXM_BLENDING_H_
#define _DOLCESDK_PSP2_GXM_BLENDING_H_

/** @file
*/

#include <psp2/gxm/types.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The blend functions for the runtime patching of shader code by the shader patcher.

	@note Use of #SCE_GXM_BLEND_FUNC_MIN or #SCE_GXM_BLEND_FUNC_MAX requires that the
	blend factor is set to #SCE_GXM_BLEND_FACTOR_ONE.

	@ingroup shaderpatcher
*/
typedef enum SceGxmBlendFunc {
	SCE_GXM_BLEND_FUNC_NONE,				///< D = S
	SCE_GXM_BLEND_FUNC_ADD,					///< D = S * factorS + D * factorD
	SCE_GXM_BLEND_FUNC_SUBTRACT,			///< D = S * factorS - D * factorD
	SCE_GXM_BLEND_FUNC_REVERSE_SUBTRACT,	///< D = D * factorD - S * factorS
	SCE_GXM_BLEND_FUNC_MIN,					///< D = min(S, D)
	SCE_GXM_BLEND_FUNC_MAX					///< D = max(S, D)
} SceGxmBlendFunc;

/** The blend factors for the runtime patching of shader code by the shader patcher.

	The individual descriptions are in RGBA order.

	@ingroup shaderpatcher
*/
typedef enum SceGxmBlendFactor {
	SCE_GXM_BLEND_FACTOR_ZERO,					///< (0, 0, 0, 0)
	SCE_GXM_BLEND_FACTOR_ONE,					///< (1, 1, 1, 1)
	SCE_GXM_BLEND_FACTOR_SRC_COLOR,				///< (R_s, G_s, B_s, A_s)
	SCE_GXM_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,	///< (1 - R_s, 1 - G_s, 1 - B_s, 1 - A_s)
	SCE_GXM_BLEND_FACTOR_SRC_ALPHA,				///< (A_s, A_s, A_s, A_s)
	SCE_GXM_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,	///< (1 - A_s, 1 - A_s, 1 - A_s, 1 - A_s)
	SCE_GXM_BLEND_FACTOR_DST_COLOR,				///< (R_d, G_d, B_d, A_d)
	SCE_GXM_BLEND_FACTOR_ONE_MINUS_DST_COLOR,	///< (1 - R_d, 1 - G_d, 1 - B_d, 1 - A_d)
	SCE_GXM_BLEND_FACTOR_DST_ALPHA,				///< (A_d, A_d, A_d, A_d)
	SCE_GXM_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,	///< (1 - A_d, 1 - A_d, 1 - A_d, 1 - A_d)
	SCE_GXM_BLEND_FACTOR_SRC_ALPHA_SATURATE,	///< (i, i, i, i) where i = min(A_s, 1 - A_d)
	SCE_GXM_BLEND_FACTOR_DST_ALPHA_SATURATE		///< (i, i, i, i) where i = min(A_d, 1 - A_s)
} SceGxmBlendFactor;

/** The color masks for the runtime patching of shader code by the shader patcher.

	@ingroup shaderpatcher
*/
typedef enum SceGxmColorMask {
	SCE_GXM_COLOR_MASK_NONE	= 0,			///< No channels written
	SCE_GXM_COLOR_MASK_A	= (1 << 0),		///< Alpha channel written
	SCE_GXM_COLOR_MASK_R	= (1 << 1),		///< Red channel written
	SCE_GXM_COLOR_MASK_G	= (1 << 2),		///< Green channel written
	SCE_GXM_COLOR_MASK_B	= (1 << 3),		///< Blue channel written
	SCE_GXM_COLOR_MASK_ALL	= (SCE_GXM_COLOR_MASK_A | SCE_GXM_COLOR_MASK_B | SCE_GXM_COLOR_MASK_G | SCE_GXM_COLOR_MASK_R)	///< All channels written
} SceGxmColorMask;

/** Describes the blending and masking of the shader result into the color surface.
	Used for runtime patching of the shader code by the shader patcher.

	@ingroup shaderpatcher
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

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_BLENDING_H_ */
