#ifndef _DOLCESDK_PSP2_GXM_RENDER_TARGET_H_
#define _DOLCESDK_PSP2_GXM_RENDER_TARGET_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/constants.h>
#include <psp2/gxm/structs.h>
#include <psp2/gxm/error.h>
#include <psp2/kernel/sysmem.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Initialization flags for render target creation.

	See the documentation for #SceGxmRenderTargetParams for details of
	each flag.

	@ingroup render
*/
typedef enum SceGxmRenderTargetFlags
{
	SCE_GXM_RENDER_TARGET_CUSTOM_MULTISAMPLE_LOCATIONS	= 0x00000001U,	///< Set custom multisample locations.
	SCE_GXM_RENDER_TARGET_MACROTILE_SYNC				= 0x00000002U,	///< Synchronize between macrotiles.
	SCE_GXM_RENDER_TARGET_USE_DISPLAY_QUEUE_PARAMS		= 0x00000010U	///< Use the display queue parameters to tune CPU->GPU pipelining.
} SceGxmRenderTargetFlags;

/** The right-shift to apply to the macrotile count in the X direction
	when combining with other flags from the #SceGxmRenderTargetFlags
	enumeration.

	See the documentation for #SceGxmRenderTargetParams for details of
	each flag.

	@ingroup render
*/
#define SCE_GXM_RENDER_TARGET_MACROTILE_COUNT_X_SHIFT	8

/** The right-shift to apply to the macrotile count in the Y direction
	when combining with other flags from the #SceGxmRenderTargetFlags
	enumeration.

	See the documentation for #SceGxmRenderTargetParams for details of
	each flag.

	@ingroup render
*/
#define SCE_GXM_RENDER_TARGET_MACROTILE_COUNT_Y_SHIFT	12

/** The initialization parameters for a render target.

	If #SCE_GXM_RENDER_TARGET_CUSTOM_MULTISAMPLE_LOCATIONS is specified as
	part of the flags, the multisample locations may be overridden.
	These are specified as 4-bit x and y coordinates on a 16x16 grid
	over each pixel.  These coordinates should be written to the
	<c>multisampleLocations</c> field from the low nybble to the high nybble.

	For #SCE_GXM_MULTISAMPLE_NONE, only the low 8 bits are used.  If
	#SCE_GXM_RENDER_TARGET_CUSTOM_MULTISAMPLE_LOCATIONS is not set, the
	default value is 0x00000088 for the centre pixel at (8,8).

	For #SCE_GXM_MULTISAMPLE_2X, only the low 16 bits are used.  If
	#SCE_GXM_RENDER_TARGET_CUSTOM_MULTISAMPLE_LOCATIONS is not set, the
	default value is 0x0000cc44 for a diagonal 2-sample pattern of
	(4,4), (12,12).  A regular grid pattern would be 0x0000c848.

	For #SCE_GXM_MULTISAMPLE_4X, the full word is used.  If
	#SCE_GXM_RENDER_TARGET_CUSTOM_MULTISAMPLE_LOCATIONS is not set, the
	default value is 0xeaa26e26 for a 4-sample rotated grid pattern of
	(6,2), (14,6), (2,10), (10,14).  A regular grid pattern would be 0xccc44c44.

	If #SCE_GXM_RENDER_TARGET_MACROTILE_SYNC is specified as part of the flags,
	the GPU firmware will synchronize between each macrotile of the render
	target.  The idea of this feature is to allow color surface data from
	previous macrotiles to be safely read within the current scene.  This avoids
	expensive scene changes in the GPU firmware.  A macrotile is a rectangular
	group of tiles which must be a multiple of 4 tiles in width and height.
	A render target consists of a grid of up to 16 identical macrotiles.
	The macrotile synchronization feature is intended to be used to efficiently
	perform low-resolution,	multi-pass, post-processing operations within a single
	scene.  Instead of implementing post-processing using a separate render target
	for each stage, this feature allows each macrotile of a single render target to
	be used as a separate stage of the process, with all rendering performed in a
	single scene.  Although this approach has a much lower firmware
	overhead than using separate scenes there is a small cost to each synchronization
	point. This means that the #SCE_GXM_RENDER_TARGET_MACROTILE_SYNC flag should only
	be used if the synchronization points are actually required.

	When using the #SCE_GXM_RENDER_TARGET_MACROTILE_SYNC flag, the number of
	macrotiles in the X and Y direction must be provided as follows:

	@code
		flags	= SCE_GXM_RENDER_TARGET_MACROTILE_SYNC
				| (countX << SCE_GXM_RENDER_TARGET_MACROTILE_COUNT_X_SHIFT)
				| (countY << SCE_GXM_RENDER_TARGET_MACROTILE_COUNT_Y_SHIFT);
	@endcode

	The values of <c>countX</c> and <c>countY</c> must be between 1 and 4,
	but they cannot both be 1 simultaneously.  The size of each macrotile is
	inferred by dividing the width and height of the render target by these
	count values.  The width and height of each macrotile must be a multiple
	of 128 pixels and cannot be larger than 1024 pixels.  MSAA cannot be
	used when using macrotile synchronization, and the macrotile counts cannot
	be specified unless the macrotile synchronization flag is also specified.

	When macrotile synchronization is used, the color surface data from previous
	macrotiles may be safely read through the texture unit while shading the
	current macrotile.  Macrotiles are rendered in vertical scanline order
	through the render target.  For example, when <c>countX</c> and
	<c>countY</c> both have value 4, the order is as follows:

	@code
		1 	5	9	13
		2	6	10	14
		3	7	11	15
		4	8	12	16
	@endcode

	The macrotile order when <c>countX</c> is 3 and <c>countY</c> is 2 is as
	follows:

	@code
		1 	3	5
		2	4	6
	@endcode

	Synchronization is not provided within each macrotile; tiles within a single
	macrotile will complete in an arbitrary order after being shaded by any
	GPU core.  Because of hardware restrictions, internal render target memory is
	allocated for either the 2x2 mode or 4x4 mode. This means macrotile configurations
	that are larger than 2x2 all consume the memory of a 4x4 configuration.  However,
	macrotiles outside of <c>countX</c> and <c>countY</c> are skipped by the
	GPU firmware, and these values should be chosen in order to minimize the number of
	unused macrotiles.  To reduce the render target memory footprint, it is
	recommended that the macrotile mode be 2x2 when 4 or fewer macrotiles
	are required. For example, 2x2 should be used in preference to 1x4.

	In order to use color surface data safely from previous macrotiles,
	the following rules must be adhered to:

	<ul>
	<li>Color surface data for each macrotile must lie in separate 64-byte
	system level cache (SLC) lines.  A simple example that adheres to this rule
	is a linear color surface with a start address that is aligned to a 64-byte
	boundary.  Because all macrotiles are a multiple of 128 pixels in width and height,
	it is sufficient to use a linear color surface with a start address that is aligned
	to a 64 byte boundary.  Care must be taken to ensure that texture filtering does not
	load cache lines from other macrotiles.  It is sufficient to alias each macrotile as
	a separate #SceGxmTexture with a CLAMP address mode to ensure only that macrotile’s
	texels are loaded.</li>
	<li>All primitives that lie in macrotiles 1 to (N - 1) must be drawn before
	any primitives that lie in macrotile N are drawn. This ensures that split scenes,
	due either to ring buffer pressure or partial rendering, do not change the
	visual results.</li>
	</ul>

	Note that macrotile synchronization only makes the color surface data from
	previous macrotiles available to be read.  In particular, it does not perform
	synchronization of depth/stencil values.  Reading of the depth/stencil data
	from previous macrotiles should not be performed because there is a chance that
	tile data will be read before the depth/stencil writes have completed.

	A custom valid region cannot be used when rendering a scene using a render target
	that uses macrotile	synchronization.  This restriction	may be lifted in a future
	SDK.

	@ingroup render
*/
typedef struct SceGxmRenderTargetParams
{
	uint32_t flags;					///< Bitwise combined flags from #SceGxmRenderTargetFlags.
	uint16_t width;					///< The width of the render target in pixels.
	uint16_t height;				///< The height of the render target in pixels.
	uint16_t scenesPerFrame;		///< The expected number of scenes per frame, in the range [1,#SCE_GXM_MAX_SCENES_PER_RENDERTARGET].
	uint16_t multisampleMode;		///< A value from the #SceGxmMultisampleMode enum.
	uint32_t multisampleLocations;	///< If enabled in the flags, the multisample locations to use.
	SceUID driverMemBlock;			///< The uncached LPDDR memblock for the render target GPU data structures or SCE_UID_INVALID_UID to specify memory should be allocated in libgxm.
} SceGxmRenderTargetParams;

/** Computes the driver memory size needed for the given set of render
	target parameters.  The memory will be used for render target GPU data structures should
	be allocated as an uncached LPDDR memblock using <c>sceKernelAllocMemBlock()</c>.

	@param[in]	params			A pointer to render target parameters.
	@param[out]	driverMemSize	A pointer to storage for the driver memory size.

	@retval
	SCE_OK The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid parameter value.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer.

	@ingroup render
*/
SceGxmErrorCode sceGxmGetRenderTargetMemSize(
	const SceGxmRenderTargetParams *params,
	uint32_t* driverMemSize);

/** Creates a render target object.  A render target defines the layout for tiled
	rendering and is needed to start a scene and draw geometry.  Render targets
	should ideally be created at load time, since creating them requires resources
	from the OS.

	Once the render target is no longer needed, call #sceGxmDestroyRenderTarget()
	to destroy it.

	@param[in]	params			The creation parameters for the render target.
	@param[out]	renderTarget	A pointer to storage for the render target pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid parameter value.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer.
	@retval
	SCE_GXM_ERROR_OUT_OF_RENDER_TARGETS The operation failed because the maximum number
	of render targets have already been created.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmCreateRenderTarget(
	const SceGxmRenderTargetParams *params,
	SceGxmRenderTarget **renderTarget);

/** Retrieves the driver memblock UID that was used in the <c><i>driverMemBlock</i></c> member
	of the #SceGxmRenderTargetParams that created the given render target.

	@param[in]	renderTarget	A pointer to a render target.
	@param[out]	driverMemBlock	A pointer to storage for the memblock UID.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmRenderTargetGetDriverMemBlock(const SceGxmRenderTarget *renderTarget, SceUID *driverMemBlock);

/** Destroys a render target object.

	@param[in,out]	renderTarget	A pointer to the render target to destroy.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmDestroyRenderTarget(SceGxmRenderTarget *renderTarget);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_RENDER_TARGET_H_ */
