#ifndef _DOLCESDK_PSP2_GXM_SURFACE_H_
#define _DOLCESDK_PSP2_GXM_SURFACE_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/constants.h>
#include <psp2/gxm/structs.h>
#include <psp2/gxm/error.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Creates a surface with the given buffer parameters.

	The surface is set up by default to emit to all pixels in the buffer.  To clip the
	output to a subset of the buffer, call #sceGxmColorSurfaceSetClip().

	The <c>data</c> parameter must be aligned to #SCE_GXM_COLOR_SURFACE_ALIGNMENT bytes.
	The <c>strideInPixels</c> parameter must be aligned to 2 pixels.

	@param[out]	surface				A pointer to surface to be initialized.
	@param[in]	colorFormat			The color format for the surface.
	@param[in]	surfaceType			The memory layout type.
	@param[in]	scaleMode			The scaling mode to use before storing pixels.
	@param[in]	outputRegisterSize	The output register size.
	@param[in]	width				The width of the surface.
	@param[in]	height				The height of the surface.
	@param[in]	strideInPixels		The stride of the surface in pixels.
	@param[in]	data				A pointer to the surface data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER	The operation failed because a pointer was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE		The operation failed because a parameter was invalid.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED	The operation failed because an unsupported output register size was specified.

	@ingroup render
*/
SceGxmErrorCode sceGxmColorSurfaceInit(
	SceGxmColorSurface *surface,
	SceGxmColorFormat colorFormat,
	SceGxmColorSurfaceType surfaceType,
	SceGxmColorSurfaceScaleMode scaleMode,
	SceGxmOutputRegisterSize outputRegisterSize,
	uint32_t width,
	uint32_t height,
	uint32_t strideInPixels,
	void *data);

/** Creates a color surface for depth-only rendering.

	@param[out]	surface		A pointer to the surface.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because #SceGxmColorSurface cannot be a <c>NULL</c> pointer.

	@ingroup render
*/
SceGxmErrorCode sceGxmColorSurfaceInitDisabled(
	SceGxmColorSurface *surface);

/** Returns true if the given color surface emits pixels.

	@param[in]	surface		A pointer to the depth/stencil surface.

	@retval
	true	The color surface is enabled (emits pixels).
	@retval
	false	The color surface is disabled (depth only rendering).

	@ingroup render
*/
bool sceGxmColorSurfaceIsEnabled(
	const SceGxmColorSurface *surface);

/** Gets the color surface clip parameters.

	The min and max values are inclusive.

	@param[in]	surface      A pointer to the surface.
	@param[out]	xMin         A pointer to storage for the minimum x value in pixels.
	@param[out]	yMin         A pointer to storage for the minimum y value in pixels.
	@param[out]	xMax         A pointer to storage for the maximum x value in pixels.
	@param[out]	yMax         A pointer to storage for the maximum y value in pixels.

	@ingroup render
*/
void sceGxmColorSurfaceGetClip(
	const SceGxmColorSurface *surface,
	uint32_t *xMin,
	uint32_t *yMin,
	uint32_t *xMax,
	uint32_t *yMax);

/** Sets the surface clip parameters to only emit to a subset of the pixels in the buffer.

	The min and max values are inclusive.

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		xMin		The minimum x value in pixels.
	@param[in]		yMin		The minimum y value in pixels.
	@param[in]		xMax		The maximum x value in pixels.
	@param[in]		yMax		The maximum y value in pixels.

	@ingroup render
*/
void sceGxmColorSurfaceSetClip(
	SceGxmColorSurface *surface,
	uint32_t xMin,
	uint32_t yMin,
	uint32_t xMax,
	uint32_t yMax);

/** Gets the color surface scale mode.

	@param[in]	surface		A pointer to the surface.

	@return
	The scale mode currently used for the surface.

	@ingroup render
*/
SceGxmColorSurfaceScaleMode sceGxmColorSurfaceGetScaleMode(
	const SceGxmColorSurface *surface);

/** Sets the color surface scale mode.

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		scaleMode	The scaling mode to use before storing pixels.

	@ingroup render
*/
void sceGxmColorSurfaceSetScaleMode(
	SceGxmColorSurface *surface,
	SceGxmColorSurfaceScaleMode scaleMode);

/** Gets a pointer to the surface data for the given color surface.

	@param[in]	surface		A pointer to the surface.

	@return
	A pointer to the surface data.

	@ingroup render
*/
void *sceGxmColorSurfaceGetData(
	const SceGxmColorSurface *surface);

/** Sets the data pointer for the given color surface.

	The <c>data</c> parameter must be aligned to #SCE_GXM_COLOR_SURFACE_ALIGNMENT bytes.

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		data		A pointer to the surface data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the surface was not aligned correctly.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed because it is not supported.

	@note Not supported when the surface was initialized using
	#sceGxmColorSurfaceInitDisabled().

	@ingroup render
*/
SceGxmErrorCode sceGxmColorSurfaceSetData(
	SceGxmColorSurface *surface,
	void *data);

/** Gets the color format for the given color surface.

	@param[in]	surface		A pointer to the surface.

	@return
	The color format of the surface.

	@ingroup render
*/
SceGxmColorFormat sceGxmColorSurfaceGetFormat(
	const SceGxmColorSurface *surface);

/** Sets the color format for the given color surface.

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		format		The color format to set.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed because it is not supported.

	@note Not supported when the surface was initialized using
	#sceGxmColorSurfaceInitDisabled().

	@note The number of bits per pixel for the format needs to match the
	number of bits per pixel for the format used during initialization.

	@note The supplied format must be able to support the use of the
	scale mode currently set on the color surface.

	@ingroup render
*/
SceGxmErrorCode sceGxmColorSurfaceSetFormat(
	SceGxmColorSurface *surface,
	SceGxmColorFormat format);

/** Gets the memory layout type for the given color surface.

	@param[in]	surface		A pointer to the surface.

	@return
	The memory layout of the surface.

	@ingroup render
*/
SceGxmColorSurfaceType sceGxmColorSurfaceGetType(
	const SceGxmColorSurface *surface);

/** Gets the stride in pixels for the given color surface.

	@param[in]	surface		A pointer to the surface.

	@return
	The stride in pixels of the surface data.

	@ingroup render
*/
uint32_t sceGxmColorSurfaceGetStrideInPixels(
	const SceGxmColorSurface *surface);

/** Sets up a surface to store depth/stencil data to memory.

	Note that depth/stencil surfaces store values at sample resolution when
	using MSAA and may be of linear or tiled layout only.  The <c>depthData</c> and
	<c>stencilData</c> parameters must be aligned to #SCE_GXM_DEPTHSTENCIL_SURFACE_ALIGNMENT
	bytes.  The <c>strideInSamples</c> parameter must be a multiple of #SCE_GXM_TILE_SIZEX.

	The depth/stencil surface is set up by default not to load or save its values
	at the beginning or end of a scene respectively.  Call #sceGxmDepthStencilSurfaceSetForceLoadMode()
	or #sceGxmDepthStencilSurfaceSetForceStoreMode() to change this behavior.

	@param[out]	surface				A pointer to the depth/stencil surface.
	@param[in]	depthStencilFormat	The depth/stencil format.
	@param[in]	surfaceType			The memory layout type.
	@param[in]	strideInSamples		The stride of the surface in samples.
	@param[in]	depthData			A pointer to the depth data or <c>NULL</c>.
	@param[in]	stencilData			A pointer to the stencil data or <c>NULL</c>.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer parameter.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to an invalid alignment of an input parameter.

	@ingroup render
*/
SceGxmErrorCode sceGxmDepthStencilSurfaceInit(
	SceGxmDepthStencilSurface *surface,
	SceGxmDepthStencilFormat depthStencilFormat,
	SceGxmDepthStencilSurfaceType surfaceType,
	uint32_t strideInSamples,
	void *depthData,
	void *stencilData);

/** Creates a depth/stencil surface that does not store to memory.

	@param[out]	surface			A pointer to the depth/stencil surface.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer parameter.

	@ingroup render
*/
SceGxmErrorCode sceGxmDepthStencilSurfaceInitDisabled(
	SceGxmDepthStencilSurface *surface);

/** Gets the current background mask value to use if a tile does not
	read mask values from memory.

	@param[in]	surface			A pointer to the depth/stencil surface.
	@return						A boolean representing the background mask value.

	@ingroup render
*/
bool sceGxmDepthStencilSurfaceGetBackgroundMask(
	const SceGxmDepthStencilSurface *surface);

/** Sets the current background mask value to use if a tile does not
	read mask values from memory.  The default value for the background
	mask is <c>true</c>.

	@param[in,out]	surface			A pointer to the depth/stencil surface.
	@param[in]		backgroundMask	The boolean representing the background mask value.

	@ingroup render
*/
void sceGxmDepthStencilSurfaceSetBackgroundMask(
	SceGxmDepthStencilSurface *surface,
	bool backgroundMask);

/** Gets the current background depth value to use if a tile does not
	read depth values from memory.

	@param[in]	surface			A pointer to the depth/stencil surface.
	@return						The floating-point background depth value.

	@ingroup render
*/
float sceGxmDepthStencilSurfaceGetBackgroundDepth(
	const SceGxmDepthStencilSurface *surface);

/** Sets the current background depth value to use if a tile does not
	read depth values from memory.  The default value for the background
	depth is 1.0f.

	@param[in,out]	surface			A pointer to the depth/stencil surface.
	@param[in]		backgroundDepth	The floating-point background depth value.

	@ingroup render
*/
void sceGxmDepthStencilSurfaceSetBackgroundDepth(
	SceGxmDepthStencilSurface *surface,
	float backgroundDepth);

/** Gets the current background stencil value to use if a tile does not
	read stencil values from memory.

	@param[in]	surface		A pointer to the depth/stencil surface.
	@return					The background stencil value.

	@ingroup render
*/
uint8_t sceGxmDepthStencilSurfaceGetBackgroundStencil(
	const SceGxmDepthStencilSurface *surface);

/** Sets the current background stencil value to use if a tile does not
	read stencil values from memory.  The default value for the background
	stencil is 0x00.

	@param[in,out]	surface				A pointer to the depth/stencil surface.
	@param[in]		backgroundStencil	The background stencil value.

	@ingroup render
*/
void sceGxmDepthStencilSurfaceSetBackgroundStencil(
	SceGxmDepthStencilSurface *surface,
	uint8_t backgroundStencil);

/** Returns true if the given depth/stencil surface is enabled.

	@param[in]	surface			A pointer to the depth/stencil surface.

	@retval
	true	The depth/stencil surface is enabled. The data will be stored at least during partial renders.
	@retval
	false	The depth/stencil surface is disabled and no data will ever be stored.

	@ingroup render
*/
bool sceGxmDepthStencilSurfaceIsEnabled(
	const SceGxmDepthStencilSurface *surface);

/** Controls forced loading of depth/stencil values at the start of a scene.

	You will need to force a load if you wish to load depth or stencil values from
	a previous scene. This previous scene must have forced a store of its depth/stencil values.

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		forceLoad	A flag that specifies whether to enable or disable forced loading.

	@ingroup render
*/
void sceGxmDepthStencilSurfaceSetForceLoadMode(
	SceGxmDepthStencilSurface *surface,
	SceGxmDepthStencilForceLoadMode forceLoad);

/** Tests if forced loading of depth/stencil values is enabled for a surface.

	@param[in]	surface		A pointer to the surface.

	@return
	A flag that indicates whether forced loading is enabled or disabled.

	@ingroup render
*/
SceGxmDepthStencilForceLoadMode sceGxmDepthStencilSurfaceGetForceLoadMode(
	const SceGxmDepthStencilSurface *surface);

/** Controls forced storing of depth/stencil values at the end of a scene.

	You will need to force a store if you wish to use the depth or stencil values from this
	scene in a future scene (for example, as a shadow map).

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		forceStore	A flag that specifies whether to enable or disable forced storing.

	@ingroup render
*/
void sceGxmDepthStencilSurfaceSetForceStoreMode(
	SceGxmDepthStencilSurface *surface,
	SceGxmDepthStencilForceStoreMode forceStore);

/** Tests if forced storing of depth/stencil values is enabled for a surface.

	@param[in]	surface		A pointer to the surface.

	@return
	A flag that indicates whether forced storing is enabled or disabled.

	@ingroup render
*/
SceGxmDepthStencilForceStoreMode sceGxmDepthStencilSurfaceGetForceStoreMode(
	const SceGxmDepthStencilSurface *surface);

/** Gets the color surface gamma mode.

	@param[in]	surface		A pointer to the surface.

	@return
	The gamma mode currently used for the surface.

	@ingroup render
*/
SceGxmColorSurfaceGammaMode sceGxmColorSurfaceGetGammaMode(
	const SceGxmColorSurface *surface);

/** Sets the color surface gamma mode.

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		gammaMode	The gamma mode to apply on pixel write.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a parameter was invalid.

	@ingroup render
*/
SceGxmErrorCode sceGxmColorSurfaceSetGammaMode(
	SceGxmColorSurface *surface,
	SceGxmColorSurfaceGammaMode gammaMode);

/** Gets the color surface dither mode.

	@param[in]	surface		A pointer to the surface.

	@return
	The dither mode currently used for the surface.

	@ingroup render
*/
SceGxmColorSurfaceDitherMode sceGxmColorSurfaceGetDitherMode(
	const SceGxmColorSurface *surface);

/** Sets the color surface dither mode.

	@param[in,out]	surface		A pointer to the surface.
	@param[in]		ditherMode	The dither mode to apply on pixel write.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a parameter was invalid.

	@ingroup render
*/
SceGxmErrorCode sceGxmColorSurfaceSetDitherMode(
	SceGxmColorSurface *surface,
	SceGxmColorSurfaceDitherMode ditherMode);

/** Gets the depth/stencil format of the given surface.

	@param[in]	surface		A pointer to the surface.

	@return
	The depth/stencil format of the surface.

	@ingroup render
*/
SceGxmDepthStencilFormat sceGxmDepthStencilSurfaceGetFormat(
	const SceGxmDepthStencilSurface *surface);

/** Gets the stride of the given surface in samples.  Each sample is of
	the format returned by #sceGxmDepthStencilSurfaceGetFormat().

	@param[in]	surface		A pointer to the surface.

	@return
	The stride of the surface in samples.

	@ingroup render
*/
uint32_t sceGxmDepthStencilSurfaceGetStrideInSamples(
	const SceGxmDepthStencilSurface *surface);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_SURFACE_H_ */
