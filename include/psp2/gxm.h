/**
 * \usergroup{SceGxm}
 * \usage{psp2/gxm.h,SceGxm_stub}
 */


#ifndef _DOLCESDK_PSP2_GXM_H_
#define _DOLCESDK_PSP2_GXM_H_

#include <psp2/gxm/internal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialization
 */

SceGxmErrorCode sceGxmInitialize(const SceGxmInitializeParams *params);

SceGxmErrorCode sceGxmGetParameterBufferThreshold(uint32_t *parameterBufferSize);

volatile uint32_t *sceGxmGetNotificationRegion(void);

SceGxmErrorCode sceGxmNotificationWait(const SceGxmNotification* notification);

SceGxmErrorCode sceGxmWaitEvent(void);

SceGxmErrorCode sceGxmTerminate(void);

SceGxmErrorCode sceGxmSetWarningEnabled(SceGxmWarning warning, bool enable);

bool sceGxmIsDebugVersion(void);

/**
 * GXM context
 */

SceGxmErrorCode sceGxmCreateContext(
	const SceGxmContextParams *params,
	SceGxmContext **immediateContext);

SceGxmErrorCode sceGxmDestroyContext(SceGxmContext *immediateContext);

SceGxmErrorCode sceGxmCreateDeferredContext(
	SceGxmDeferredContextParams *params,
	SceGxmContext **deferredContext);

SceGxmErrorCode sceGxmDestroyDeferredContext(
	SceGxmContext *deferredContext);

SceGxmErrorCode sceGxmGetContextType(
	const SceGxmContext *context,
	SceGxmContextType *type);

void sceGxmSetVertexProgram(
	SceGxmContext *context,
	const SceGxmVertexProgram *vertexProgram);

void sceGxmSetFragmentProgram(
	SceGxmContext *context,
	const SceGxmFragmentProgram *fragmentProgram);

SceGxmErrorCode sceGxmReserveVertexDefaultUniformBuffer(
	SceGxmContext *context,
	void **uniformBuffer);

SceGxmErrorCode sceGxmSetVertexDefaultUniformBuffer(
	SceGxmContext *context,
	const void *bufferData);

SceGxmErrorCode sceGxmReserveFragmentDefaultUniformBuffer(
	SceGxmContext *context,
	void **uniformBuffer);

SceGxmErrorCode sceGxmSetFragmentDefaultUniformBuffer(
	SceGxmContext *context,
	const void *bufferData);

SceGxmErrorCode sceGxmSetVertexStream(
	SceGxmContext *context,
	uint32_t streamIndex,
	const void *streamData);

SceGxmErrorCode sceGxmSetVertexTexture(
	SceGxmContext *context,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

SceGxmErrorCode sceGxmSetFragmentTexture(
	SceGxmContext *context,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

SceGxmErrorCode sceGxmSetVertexUniformBuffer(
	SceGxmContext *context,
	uint32_t bufferIndex,
	const void *bufferData);

SceGxmErrorCode sceGxmSetFragmentUniformBuffer(
	SceGxmContext *context,
	uint32_t bufferIndex,
	const void *bufferData);

void sceGxmSetPrecomputedFragmentState(
	SceGxmContext *context,
	const SceGxmPrecomputedFragmentState *precomputedState);

void sceGxmSetPrecomputedVertexState(
	SceGxmContext *context,
	const SceGxmPrecomputedVertexState *precomputedState);

SceGxmErrorCode sceGxmDrawPrecomputed(
	SceGxmContext *context,
	const SceGxmPrecomputedDraw *precomputedDraw);

SceGxmErrorCode sceGxmDraw(
	SceGxmContext *context,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount);

SceGxmErrorCode sceGxmDrawInstanced(
	SceGxmContext *context,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount,
	uint32_t indexWrap);

SceGxmErrorCode sceGxmSetVisibilityBuffer(
	SceGxmContext *immediateContext,
	void *bufferBase,
	uint32_t stridePerCore);

SceGxmErrorCode sceGxmSetYuvProfile(
	SceGxmContext *immediateContext,
	uint32_t cscIndex,
	SceGxmYuvProfile profile);

SceGxmErrorCode sceGxmBeginScene(
	SceGxmContext *immediateContext,
	uint32_t flags,
	const SceGxmRenderTarget *renderTarget,
	const SceGxmValidRegion *validRegion,
	SceGxmSyncObject *vertexSyncObject,
	SceGxmSyncObject *fragmentSyncObject,
	const SceGxmColorSurface *colorSurface,
	const SceGxmDepthStencilSurface *depthStencilSurface);

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

SceGxmErrorCode sceGxmMidSceneFlush(
	SceGxmContext *immediateContext,
	uint32_t flags,
	SceGxmSyncObject *vertexSyncObject,
	const SceGxmNotification *vertexNotification);

SceGxmErrorCode sceGxmEndScene(
	SceGxmContext *immediateContext,
	const SceGxmNotification *vertexNotification,
	const SceGxmNotification *fragmentNotification);

void sceGxmSetFrontDepthFunc(SceGxmContext *context, SceGxmDepthFunc depthFunc);

void sceGxmSetBackDepthFunc(SceGxmContext *context, SceGxmDepthFunc depthFunc);

void sceGxmSetFrontFragmentProgramEnable(SceGxmContext *context, SceGxmFragmentProgramMode enable);

void sceGxmSetBackFragmentProgramEnable(SceGxmContext *context, SceGxmFragmentProgramMode enable);

void sceGxmSetFrontDepthWriteEnable(SceGxmContext *context, SceGxmDepthWriteMode enable);

void sceGxmSetBackDepthWriteEnable(SceGxmContext *context, SceGxmDepthWriteMode enable);

void sceGxmSetFrontLineFillLastPixelEnable(SceGxmContext *context, SceGxmLineFillLastPixelMode enable);

void sceGxmSetBackLineFillLastPixelEnable(SceGxmContext *context, SceGxmLineFillLastPixelMode enable);

void sceGxmSetFrontStencilRef(SceGxmContext *context, uint8_t sref);

void sceGxmSetBackStencilRef(SceGxmContext *context, uint8_t sref);

void sceGxmSetFrontPointLineWidth(SceGxmContext *context, uint32_t width);

void sceGxmSetBackPointLineWidth(SceGxmContext *context, uint32_t width);

void sceGxmSetFrontPolygonMode(SceGxmContext *context, SceGxmPolygonMode mode);

void sceGxmSetBackPolygonMode(SceGxmContext *context, SceGxmPolygonMode mode);

void sceGxmSetFrontStencilFunc(SceGxmContext *context,
							   SceGxmStencilFunc func,
							   SceGxmStencilOp stencilFail,
							   SceGxmStencilOp depthFail,
							   SceGxmStencilOp depthPass,
							   uint8_t compareMask,
							   uint8_t writeMask);

void sceGxmSetBackStencilFunc(SceGxmContext *context,
							  SceGxmStencilFunc func,
							  SceGxmStencilOp stencilFail,
							  SceGxmStencilOp depthFail,
							  SceGxmStencilOp depthPass,
							  uint8_t compareMask,
							  uint8_t writeMask);

void sceGxmSetFrontDepthBias(SceGxmContext *context, int32_t factor, int32_t units);

void sceGxmSetBackDepthBias(SceGxmContext *context, int32_t factor, int32_t units);

void sceGxmSetTwoSidedEnable(SceGxmContext *context, SceGxmTwoSidedMode enable);

void sceGxmSetViewport(SceGxmContext *context, float xOffset, float xScale, float yOffset, float yScale, float zOffset, float zScale);

void sceGxmSetWClampValue(SceGxmContext *context, float clampValue);

void sceGxmSetWClampEnable(SceGxmContext *context, SceGxmWClampMode enable);

void sceGxmSetRegionClip(SceGxmContext *context, SceGxmRegionClipMode mode, uint32_t xMin, uint32_t yMin, uint32_t xMax, uint32_t yMax);

void sceGxmSetCullMode(SceGxmContext *context, SceGxmCullMode mode);

void sceGxmSetViewportEnable(SceGxmContext *context, SceGxmViewportMode enable);

void sceGxmSetWBufferEnable(SceGxmContext *context, SceGxmWBufferMode enable);

void sceGxmSetFrontVisibilityTestIndex(SceGxmContext *context, uint32_t index);

void sceGxmSetBackVisibilityTestIndex(SceGxmContext *context, uint32_t index);

void sceGxmSetFrontVisibilityTestOp(SceGxmContext *context, SceGxmVisibilityTestOp op);

void sceGxmSetBackVisibilityTestOp(SceGxmContext *context, SceGxmVisibilityTestOp op);

void sceGxmSetFrontVisibilityTestEnable(SceGxmContext *context, SceGxmVisibilityTestMode enable);

void sceGxmSetBackVisibilityTestEnable(SceGxmContext *context, SceGxmVisibilityTestMode enable);

SceGxmErrorCode sceGxmFinish(SceGxmContext *context);

SceGxmErrorCode sceGxmPushUserMarker(SceGxmContext *context, const char *tag);

SceGxmErrorCode sceGxmPopUserMarker(SceGxmContext *context);

SceGxmErrorCode sceGxmSetUserMarker(SceGxmContext *context, const char *tag);

SceGxmErrorCode sceGxmPadHeartbeat(
	const SceGxmColorSurface *displaySurface,
	SceGxmSyncObject *displaySyncObject);

SceGxmErrorCode sceGxmBeginCommandList(
	SceGxmContext *deferredContext);

SceGxmErrorCode sceGxmEndCommandList(
	SceGxmContext *deferredContext,
	SceGxmCommandList *commandList);

SceGxmErrorCode sceGxmExecuteCommandList(
	SceGxmContext *immediateContext,
	SceGxmCommandList *commandList);

void sceGxmSetDefaultRegionClipAndViewport(
	SceGxmContext *context,
	uint32_t xMax,
	uint32_t yMax);

SceGxmErrorCode sceGxmGetDeferredContextVdmBuffer(
	const SceGxmContext *deferredContext,
	void **mem);

SceGxmErrorCode sceGxmSetDeferredContextVdmBuffer(
	SceGxmContext *deferredContext,
	void *mem,
	uint32_t size);

SceGxmErrorCode sceGxmGetDeferredContextVertexBuffer(
	const SceGxmContext *deferredContext,
	void **mem);

SceGxmErrorCode sceGxmSetDeferredContextVertexBuffer(
	SceGxmContext *deferredContext,
	void *mem,
	uint32_t size);

SceGxmErrorCode sceGxmGetDeferredContextFragmentBuffer(
	const SceGxmContext *deferredContext,
	void **mem);

SceGxmErrorCode sceGxmSetDeferredContextFragmentBuffer(
	SceGxmContext *deferredContext,
	void *mem,
	uint32_t size);

/**
 * Memory
 */

SceGxmErrorCode sceGxmMapMemory(void *base, uint32_t size, uint32_t attribs);

SceGxmErrorCode sceGxmUnmapMemory(void *base);

SceGxmErrorCode sceGxmMapVertexUsseMemory(void *base, uint32_t size, uint32_t *offset);

SceGxmErrorCode sceGxmUnmapVertexUsseMemory(void *base);

SceGxmErrorCode sceGxmMapFragmentUsseMemory(void *base, uint32_t size, uint32_t *offset);

SceGxmErrorCode sceGxmUnmapFragmentUsseMemory(void *base);

SceGxmErrorCode sceGxmAddRazorGpuCaptureBuffer(void* base, uint32_t size);

SceGxmErrorCode sceGxmRemoveRazorGpuCaptureBuffer(void* base);

/**
 * Display queue
 */

SceGxmErrorCode sceGxmDisplayQueueAddEntry(
	SceGxmSyncObject *oldBuffer,
	SceGxmSyncObject *newBuffer,
	const void *callbackData);

SceGxmErrorCode sceGxmDisplayQueueFinish(void);

/**
 * Render target
 */

SceGxmErrorCode sceGxmGetRenderTargetMemSize(
	const SceGxmRenderTargetParams *params,
	uint32_t* driverMemSize);

SceGxmErrorCode sceGxmCreateRenderTarget(
	const SceGxmRenderTargetParams *params,
	SceGxmRenderTarget **renderTarget);

SceGxmErrorCode sceGxmRenderTargetGetDriverMemBlock(const SceGxmRenderTarget *renderTarget, SceUID *driverMemBlock);

SceGxmErrorCode sceGxmDestroyRenderTarget(SceGxmRenderTarget *renderTarget);

/**
 * Surface
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

SceGxmErrorCode sceGxmColorSurfaceInitDisabled(
	SceGxmColorSurface *surface);

bool sceGxmColorSurfaceIsEnabled(
	const SceGxmColorSurface *surface);

void sceGxmColorSurfaceGetClip(
	const SceGxmColorSurface *surface,
	uint32_t *xMin,
	uint32_t *yMin,
	uint32_t *xMax,
	uint32_t *yMax);

void sceGxmColorSurfaceSetClip(
	SceGxmColorSurface *surface,
	uint32_t xMin,
	uint32_t yMin,
	uint32_t xMax,
	uint32_t yMax);

SceGxmColorSurfaceScaleMode sceGxmColorSurfaceGetScaleMode(
	const SceGxmColorSurface *surface);

void sceGxmColorSurfaceSetScaleMode(
	SceGxmColorSurface *surface,
	SceGxmColorSurfaceScaleMode scaleMode);

void *sceGxmColorSurfaceGetData(
	const SceGxmColorSurface *surface);

SceGxmErrorCode sceGxmColorSurfaceSetData(
	SceGxmColorSurface *surface,
	void *data);

SceGxmColorFormat sceGxmColorSurfaceGetFormat(
	const SceGxmColorSurface *surface);

SceGxmErrorCode sceGxmColorSurfaceSetFormat(
	SceGxmColorSurface *surface,
	SceGxmColorFormat format);

SceGxmColorSurfaceType sceGxmColorSurfaceGetType(
	const SceGxmColorSurface *surface);

uint32_t sceGxmColorSurfaceGetStrideInPixels(
	const SceGxmColorSurface *surface);

SceGxmErrorCode sceGxmDepthStencilSurfaceInit(
	SceGxmDepthStencilSurface *surface,
	SceGxmDepthStencilFormat depthStencilFormat,
	SceGxmDepthStencilSurfaceType surfaceType,
	uint32_t strideInSamples,
	void *depthData,
	void *stencilData);

SceGxmErrorCode sceGxmDepthStencilSurfaceInitDisabled(
	SceGxmDepthStencilSurface *surface);

bool sceGxmDepthStencilSurfaceGetBackgroundMask(
	const SceGxmDepthStencilSurface *surface);

void sceGxmDepthStencilSurfaceSetBackgroundMask(
	SceGxmDepthStencilSurface *surface,
	bool backgroundMask);

float sceGxmDepthStencilSurfaceGetBackgroundDepth(
	const SceGxmDepthStencilSurface *surface);

void sceGxmDepthStencilSurfaceSetBackgroundDepth(
	SceGxmDepthStencilSurface *surface,
	float backgroundDepth);

uint8_t sceGxmDepthStencilSurfaceGetBackgroundStencil(
	const SceGxmDepthStencilSurface *surface);

void sceGxmDepthStencilSurfaceSetBackgroundStencil(
	SceGxmDepthStencilSurface *surface,
	uint8_t backgroundStencil);

bool sceGxmDepthStencilSurfaceIsEnabled(
	const SceGxmDepthStencilSurface *surface);

void sceGxmDepthStencilSurfaceSetForceLoadMode(
	SceGxmDepthStencilSurface *surface,
	SceGxmDepthStencilForceLoadMode forceLoad);

SceGxmDepthStencilForceLoadMode sceGxmDepthStencilSurfaceGetForceLoadMode(
	const SceGxmDepthStencilSurface *surface);

void sceGxmDepthStencilSurfaceSetForceStoreMode(
	SceGxmDepthStencilSurface *surface,
	SceGxmDepthStencilForceStoreMode forceStore);

SceGxmDepthStencilForceStoreMode sceGxmDepthStencilSurfaceGetForceStoreMode(
	const SceGxmDepthStencilSurface *surface);

SceGxmColorSurfaceGammaMode sceGxmColorSurfaceGetGammaMode(
	const SceGxmColorSurface *surface);

SceGxmErrorCode sceGxmColorSurfaceSetGammaMode(
	SceGxmColorSurface *surface,
	SceGxmColorSurfaceGammaMode gammaMode);

SceGxmColorSurfaceDitherMode sceGxmColorSurfaceGetDitherMode(
	const SceGxmColorSurface *surface);

SceGxmErrorCode sceGxmColorSurfaceSetDitherMode(
	SceGxmColorSurface *surface,
	SceGxmColorSurfaceDitherMode ditherMode);

SceGxmDepthStencilFormat sceGxmDepthStencilSurfaceGetFormat(
	const SceGxmDepthStencilSurface *surface);

uint32_t sceGxmDepthStencilSurfaceGetStrideInSamples(
	const SceGxmDepthStencilSurface *surface);

/**
 * Sync object
 */

SceGxmErrorCode sceGxmSyncObjectCreate(SceGxmSyncObject **syncObject);

SceGxmErrorCode sceGxmSyncObjectDestroy(SceGxmSyncObject *syncObject);

/**
 * Texture
 */

SceGxmErrorCode sceGxmTextureInitSwizzled(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

SceGxmErrorCode sceGxmTextureInitSwizzledArbitrary(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

SceGxmErrorCode sceGxmTextureInitLinear(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

SceGxmErrorCode sceGxmTextureInitLinearStrided(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t byteStride);

SceGxmErrorCode sceGxmTextureInitTiled(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

SceGxmErrorCode sceGxmTextureInitCube(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

SceGxmErrorCode sceGxmTextureInitCubeArbitrary(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

SceGxmTextureType sceGxmTextureGetType(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetMinFilter(SceGxmTexture *texture, SceGxmTextureFilter minFilter);

SceGxmTextureFilter sceGxmTextureGetMinFilter(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetMagFilter(SceGxmTexture *texture, SceGxmTextureFilter magFilter);

SceGxmTextureFilter sceGxmTextureGetMagFilter(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetMipFilter(SceGxmTexture *texture, SceGxmTextureMipFilter mipFilter);

SceGxmTextureMipFilter sceGxmTextureGetMipFilter(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetUAddrMode(SceGxmTexture *texture, SceGxmTextureAddrMode addrMode);

SceGxmTextureAddrMode sceGxmTextureGetUAddrMode(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetVAddrMode(SceGxmTexture *texture, SceGxmTextureAddrMode addrMode);

SceGxmTextureAddrMode sceGxmTextureGetVAddrMode(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetFormat(SceGxmTexture *texture, SceGxmTextureFormat texFormat);

SceGxmTextureFormat sceGxmTextureGetFormat(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetLodBias(SceGxmTexture *texture, uint32_t bias);

uint32_t sceGxmTextureGetLodBias(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetLodMin(SceGxmTexture *texture, uint32_t lodMin);

uint32_t sceGxmTextureGetLodMin(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetStride(SceGxmTexture *texture, uint32_t byteStride);

uint32_t sceGxmTextureGetStride(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetWidth(SceGxmTexture *texture, uint32_t width);

uint32_t sceGxmTextureGetWidth(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetHeight(SceGxmTexture *texture, uint32_t height);

uint32_t sceGxmTextureGetHeight(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetData(SceGxmTexture *texture, const void *data);

void *sceGxmTextureGetData(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetMipmapCount(SceGxmTexture *texture, uint32_t mipCount);

uint32_t sceGxmTextureGetMipmapCount(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetPalette(SceGxmTexture *texture, const void *paletteData);

void *sceGxmTextureGetPalette(const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetGammaMode(
	SceGxmTexture *texture,
	SceGxmTextureGammaMode gammaMode);

SceGxmTextureGammaMode sceGxmTextureGetGammaMode(
	const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureSetNormalizeMode(
	SceGxmTexture *texture,
	SceGxmTextureNormalizeMode normalizeMode);

SceGxmTextureNormalizeMode sceGxmTextureGetNormalizeMode(
	const SceGxmTexture *texture);

SceGxmErrorCode sceGxmTextureValidate(
	const SceGxmTexture *texture);

/**
 * Precomputation
 */

uint32_t sceGxmGetPrecomputedVertexStateSize(
	const SceGxmVertexProgram *vertexProgram);

SceGxmErrorCode sceGxmPrecomputedVertexStateInit(
	SceGxmPrecomputedVertexState *precomputedState,
	const SceGxmVertexProgram *vertexProgram,
	void *memBlock);

SceGxmErrorCode sceGxmPrecomputedVertexStateSetDefaultUniformBuffer(
	SceGxmPrecomputedVertexState *precomputedState,
	const void *defaultBuffer);

void *sceGxmPrecomputedVertexStateGetDefaultUniformBuffer(
	const SceGxmPrecomputedVertexState *precomputedState);

SceGxmErrorCode sceGxmPrecomputedVertexStateSetAllTextures(
	SceGxmPrecomputedVertexState *precomputedState,
	const SceGxmTexture *textureArray);

SceGxmErrorCode sceGxmPrecomputedVertexStateSetTexture(
	SceGxmPrecomputedVertexState *precomputedState,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

SceGxmErrorCode sceGxmPrecomputedVertexStateSetAllUniformBuffers(
	SceGxmPrecomputedVertexState *precomputedState,
	const void *const *bufferDataArray);

SceGxmErrorCode sceGxmPrecomputedVertexStateSetUniformBuffer(
	SceGxmPrecomputedVertexState *precomputedState,
	uint32_t bufferIndex,
	const void *bufferData);

uint32_t sceGxmGetPrecomputedFragmentStateSize(
	const SceGxmFragmentProgram *fragmentProgram);

SceGxmErrorCode sceGxmPrecomputedFragmentStateInit(
	SceGxmPrecomputedFragmentState *precomputedState,
	const SceGxmFragmentProgram *fragmentProgram,
	void *memBlock);

SceGxmErrorCode sceGxmPrecomputedFragmentStateSetDefaultUniformBuffer(
	SceGxmPrecomputedFragmentState *precomputedState,
	const void *defaultBuffer);

void *sceGxmPrecomputedFragmentStateGetDefaultUniformBuffer(
	const SceGxmPrecomputedFragmentState *precomputedState);

SceGxmErrorCode sceGxmPrecomputedFragmentStateSetAllTextures(
	SceGxmPrecomputedFragmentState *precomputedState,
	const SceGxmTexture *textureArray);

SceGxmErrorCode sceGxmPrecomputedFragmentStateSetTexture(
	SceGxmPrecomputedFragmentState *precomputedState,
	uint32_t textureIndex,
	const SceGxmTexture *texture);

SceGxmErrorCode sceGxmPrecomputedFragmentStateSetAllUniformBuffers(
	SceGxmPrecomputedFragmentState *precomputedState,
	const void *const *bufferDataArray);

SceGxmErrorCode sceGxmPrecomputedFragmentStateSetUniformBuffer(
	SceGxmPrecomputedFragmentState *precomputedState,
	uint32_t bufferIndex,
	const void *bufferData);

uint32_t sceGxmGetPrecomputedDrawSize(
	const SceGxmVertexProgram *vertexProgram);

SceGxmErrorCode sceGxmPrecomputedDrawInit(
	SceGxmPrecomputedDraw *precomputedDraw,
	const SceGxmVertexProgram *vertexProgram,
	void *memBlock);

SceGxmErrorCode sceGxmPrecomputedDrawSetAllVertexStreams(
	SceGxmPrecomputedDraw *precomputedDraw,
	const void *const *streamDataArray);

SceGxmErrorCode sceGxmPrecomputedDrawSetVertexStream(
	SceGxmPrecomputedDraw *precomputedDraw,
	uint32_t streamIndex,
	const void *streamData);

SceGxmErrorCode sceGxmPrecomputedDrawSetParams(
	SceGxmPrecomputedDraw *precomputedDraw,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount);

SceGxmErrorCode sceGxmPrecomputedDrawSetParamsInstanced(
	SceGxmPrecomputedDraw *precomputedDraw,
	SceGxmPrimitiveType primType,
	SceGxmIndexFormat indexType,
	const void *indexData,
	uint32_t indexCount,
	uint32_t indexWrap);

/**
 * Shader uniforms
 */

SceGxmErrorCode sceGxmSetUniformDataF(
	void *uniformBuffer,
	const SceGxmProgramParameter *parameter,
	uint32_t componentOffset,
	uint32_t componentCount,
	const float *sourceData);

/**
 * Vertex progams
 */

const SceGxmProgram *sceGxmVertexProgramGetProgram(
	const SceGxmVertexProgram *vertexProgram);

/**
 * Fragment progams
 */

const SceGxmProgram *sceGxmFragmentProgramGetProgram(
	const SceGxmFragmentProgram *fragmentProgram);

SceGxmPassType sceGxmFragmentProgramGetPassType(
	const SceGxmFragmentProgram *fragmentProgram);

bool sceGxmFragmentProgramIsEnabled(
	const SceGxmFragmentProgram *fragmentProgram);

/**
 * Shader programs
 */

SceGxmErrorCode sceGxmProgramCheck(
	const SceGxmProgram *program);

bool sceGxmProgramIsEquivalent(
	const SceGxmProgram *programA,
	const SceGxmProgram *programB);

uint32_t sceGxmProgramGetSize(
	const SceGxmProgram *program);

SceGxmProgramType sceGxmProgramGetType(
	const SceGxmProgram *program);

bool sceGxmProgramIsDiscardUsed(
	const SceGxmProgram *program);

bool sceGxmProgramIsDepthReplaceUsed(
	const SceGxmProgram *program);

bool sceGxmProgramIsSpriteCoordUsed(
	const SceGxmProgram *program);

bool sceGxmProgramIsNativeColorUsed(
	const SceGxmProgram *program);

bool sceGxmProgramIsFragColorUsed(
	const SceGxmProgram *program);

SceGxmErrorCode sceGxmProgramGetOutputRegisterFormat(
	const SceGxmProgram *program,
	SceGxmParameterType *type,
	uint32_t *componentCount);

uint32_t sceGxmProgramGetVertexProgramOutputs(
	const SceGxmProgram *program);

uint32_t sceGxmProgramGetFragmentProgramInputs(
	const SceGxmProgram *program);

uint32_t sceGxmProgramGetDefaultUniformBufferSize(
	const SceGxmProgram *program);

uint32_t sceGxmProgramGetParameterCount(
	const SceGxmProgram *program);

const SceGxmProgramParameter *sceGxmProgramGetParameter(
	const SceGxmProgram *program,
	uint32_t index);

const SceGxmProgramParameter *sceGxmProgramFindParameterByName(
	const SceGxmProgram *program,
	const char *name);

const SceGxmProgramParameter *sceGxmProgramFindParameterBySemantic(
	const SceGxmProgram *program,
	SceGxmParameterSemantic semantic,
	uint32_t index);

uint32_t sceGxmProgramParameterGetIndex(
	const SceGxmProgram *program,
	const SceGxmProgramParameter *parameter);

SceGxmParameterCategory sceGxmProgramParameterGetCategory(
	const SceGxmProgramParameter *parameter);

const char *sceGxmProgramParameterGetName(
	const SceGxmProgramParameter *parameter);

SceGxmParameterSemantic sceGxmProgramParameterGetSemantic(
	const SceGxmProgramParameter *parameter);

uint32_t sceGxmProgramParameterGetSemanticIndex(
	const SceGxmProgramParameter *parameter);

SceGxmParameterType sceGxmProgramParameterGetType(
	const SceGxmProgramParameter *parameter);

uint32_t sceGxmProgramParameterGetComponentCount(
	const SceGxmProgramParameter *parameter);

uint32_t sceGxmProgramParameterGetArraySize(
	const SceGxmProgramParameter *parameter);

uint32_t sceGxmProgramParameterGetResourceIndex(
	const SceGxmProgramParameter *parameter);

uint32_t sceGxmProgramParameterGetContainerIndex(
	const SceGxmProgramParameter *parameter);

bool sceGxmProgramParameterIsSamplerCube(
	const SceGxmProgramParameter *parameter);

bool sceGxmProgramParameterIsRegFormat(
	const SceGxmProgram *program,
	const SceGxmProgramParameter *parameter);

SceGxmErrorCode sceGxmShaderPatcherCreate(
	const SceGxmShaderPatcherParams *params,
	SceGxmShaderPatcher **shaderPatcher);


SceGxmErrorCode sceGxmShaderPatcherSetUserData(
	SceGxmShaderPatcher *shaderPatcher,
	void *userData);


void *sceGxmShaderPatcherGetUserData(
	const SceGxmShaderPatcher *shaderPatcher);


SceGxmErrorCode sceGxmShaderPatcherDestroy(
	SceGxmShaderPatcher *shaderPatcher);


SceGxmErrorCode sceGxmShaderPatcherRegisterProgram(
	SceGxmShaderPatcher *shaderPatcher,
	const SceGxmProgram *programHeader,
	SceGxmShaderPatcherId *programId);


SceGxmErrorCode sceGxmShaderPatcherUnregisterProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId);


SceGxmErrorCode sceGxmShaderPatcherForceUnregisterProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId);


const SceGxmProgram *sceGxmShaderPatcherGetProgramFromId(
	SceGxmShaderPatcherId programId);


SceGxmErrorCode sceGxmShaderPatcherCreateVertexProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId,
	const SceGxmVertexAttribute *attributes,
	uint32_t attributeCount,
	const SceGxmVertexStream *streams,
	uint32_t streamCount,
	SceGxmVertexProgram **vertexProgram);


SceGxmErrorCode sceGxmShaderPatcherCreateFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId,
	SceGxmOutputRegisterFormat outputFormat,
	SceGxmMultisampleMode multisampleMode,
	const SceGxmBlendInfo *blendInfo,
	const SceGxmProgram *vertexProgram,
	SceGxmFragmentProgram **fragmentProgram);


SceGxmErrorCode sceGxmShaderPatcherAddRefVertexProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmVertexProgram *vertexProgram);


SceGxmErrorCode sceGxmShaderPatcherAddRefFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmFragmentProgram *fragmentProgram);


SceGxmErrorCode sceGxmShaderPatcherReleaseVertexProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmVertexProgram *vertexProgram);


SceGxmErrorCode sceGxmShaderPatcherReleaseFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmFragmentProgram *fragmentProgram);


SceGxmErrorCode sceGxmShaderPatcherGetVertexProgramRefCount(
	const SceGxmShaderPatcher *shaderPatcher,
	const SceGxmVertexProgram *vertexProgram,
	uint32_t *refCount);


SceGxmErrorCode sceGxmShaderPatcherGetFragmentProgramRefCount(
	const SceGxmShaderPatcher *shaderPatcher,
	const SceGxmFragmentProgram *fragmentProgram,
	uint32_t *refCount);


uint32_t sceGxmShaderPatcherGetHostMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);


uint32_t sceGxmShaderPatcherGetBufferMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);


uint32_t sceGxmShaderPatcherGetVertexUsseMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);


uint32_t sceGxmShaderPatcherGetFragmentUsseMemAllocated(
	const SceGxmShaderPatcher *shaderPatcher);


SceGxmErrorCode sceGxmShaderPatcherCreateMaskUpdateFragmentProgram(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmFragmentProgram **fragmentProgram);

/**
 * Transfer
 */

SceGxmErrorCode	sceGxmTransferCopy(	uint32_t					width,
									uint32_t					height,
									uint32_t					colorKeyValue,
									uint32_t					colorKeyMask,
									SceGxmTransferColorKeyMode	colorKeyMode,
									SceGxmTransferFormat		srcFormat,
									SceGxmTransferType			srcType,
									const void					*srcAddress,
									uint32_t					srcX,
									uint32_t					srcY,
									int32_t						srcStride,
									SceGxmTransferFormat		destFormat,
									SceGxmTransferType			destType,
									void						*destAddress,
									uint32_t					destX,
									uint32_t					destY,
									int32_t						destStride,
									SceGxmSyncObject			*syncObject,
									uint32_t					syncFlags,
									const SceGxmNotification*	notification
									);

SceGxmErrorCode	sceGxmTransferDownscale(SceGxmTransferFormat		srcFormat,
										const void					*srcAddress,
										uint32_t					srcX,
										uint32_t					srcY,
										uint32_t					srcWidth,
										uint32_t					srcHeight,
										int32_t						srcStride,
										SceGxmTransferFormat		destFormat,
										void						*destAddress,
										uint32_t					destX,
										uint32_t					destY,
										int32_t						destStride,
										SceGxmSyncObject			*syncObject,
										uint32_t					syncFlags,
										const SceGxmNotification*	notification
										);

SceGxmErrorCode	sceGxmTransferFill(	uint32_t					fillColor,
									SceGxmTransferFormat		destFormat,
									void						*destAddress,
									uint32_t					destX,
									uint32_t					destY,
									uint32_t					destWidth,
									uint32_t					destHeight,
									int32_t						destStride,
									SceGxmSyncObject			*syncObject,
									uint32_t					syncFlags,
									const SceGxmNotification	*notification
									);

SceGxmErrorCode sceGxmTransferFinish(void);

/**
 * SceGxmForVsh
 */

SceGxmErrorCode sceGxmVshInitialize(const SceGxmInitializeParams *params);

#ifdef __cplusplus
}
#endif

#endif /* _DOLCESDK_PSP2_GXM_H_ */

