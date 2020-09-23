#ifndef _DOLCESDK_PSP2_GXM_TEXTURE_H_
#define _DOLCESDK_PSP2_GXM_TEXTURE_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/structs.h>
#include <psp2/gxm/constants.h>
#include <psp2/gxm/error.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Initializes the texture control words for swizzled texture data.

	The <c>data</c> parameter must have an alignment that is valid for the format
	of the texture.  Please see the <em>GPU User’s Guide</em> for each format’s
	alignment requirement.  The largest value the alignment can be is defined
	by #SCE_GXM_TEXTURE_ALIGNMENT.

	If the texture memory layout does not include mipmaps a value of zero can be
	specified for <c><i>mipCount</i></c>.

	@param[out]	texture			A pointer to the texture to be initialized.
	@param[in]	data			A pointer to the texture data.
	@param[in]	texFormat		The format of the texture data.
	@param[in]	width			The width of the texture (1..4096).
	@param[in]	height			The height of the texture (1..4096).
	@param[in]	mipCount		The number of mipmaps in the texture (0..13).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported texture format.

	@note
	Not supported for YUV texture formats.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureInitSwizzled(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

/** Initializes the texture control words for swizzled texture data with arbitrary dimensions.

	The <c>data</c> parameter must have an alignment that is valid for the format
	of the texture.  Please see the <em>GPU User’s Guide</em> for each format’s
	alignment requirement.  The largest value the alignment can be is defined
	by #SCE_GXM_TEXTURE_ALIGNMENT.

	If the texture memory layout does not include mipmaps, a value of zero can be
	specified for <c><i>mipCount</i></c>.

	@param[out]	texture			A pointer to the texture to be initialized.
	@param[in]	data			A pointer to the texture data.
	@param[in]	texFormat		The format of the texture data.
	@param[in]	width			The width of the texture (1..4096).
	@param[in]	height			The height of the texture (1..4096).
	@param[in]	mipCount		The number of mipmaps in the texture (0..13).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported texture format.

	@note
	Not supported for YUV texture formats.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureInitSwizzledArbitrary(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

/** Initializes the texture control words for linear texture data.

	The <c>data</c> parameter must have an alignment that is valid for the format
	of the texture.  Please see the <em>GPU User’s Guide</em> for each format’s
	alignment requirement.  The largest value the alignment can be is defined
	by #SCE_GXM_TEXTURE_ALIGNMENT.

	The stride of the <c><i>data</i></c> is formed by aligning the <c><i>width</i></c>
	to the nearest multiple of #SCE_GXM_TEXTURE_IMPLICIT_STRIDE_ALIGNMENT.

	If the texture memory layout does not include mipmaps, a value of zero can be
	specified for <c><i>mipCount</i></c>.

	@param[out]	texture			A pointer to texture to be initialized.
	@param[in]	data			A pointer to the texture data.
	@param[in]	texFormat		The format of the texture.
	@param[in]	width			The width of the texture (1..4096).
	@param[in]	height			The height of the texture (1..4096).
	@param[in]	mipCount		The number of mipmaps in the texture (0..13).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported texture format.

	@note
	Not supported for block compressed texture formats.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureInitLinear(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

/** Initializes the texture control words for linear strided texture data.

	The <c>data</c> parameter must have an alignment that is valid for the format
	of the texture.  Please see the <em>GPU User’s Guide</em> for each format’s
	alignment requirement.  The largest value the alignment can be is defined
	by #SCE_GXM_TEXTURE_ALIGNMENT.

	@param[out]	texture			A pointer to the texture to be initialized.
	@param[in]	data			A pointer to the texture data.
	@param[in]	texFormat		The format of the texture.
	@param[in]	width			The width of the texture (1..4096).
	@param[in]	height			The height of the texture (1..4096).
	@param[in]	byteStride		The stride of the texture in bytes.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported texture format.

	@note
	Not supported for 24-bit, block compressed or planar YUV texture formats.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureInitLinearStrided(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t byteStride);

/** Initializes the texture control words for tiled texture data.

	The <c>data</c> parameter must have an alignment that is valid for the format
	of the texture.  Please see the <em>GPU User’s Guide</em> for each format’s
	alignment requirement.  The largest value the alignment can be is defined
	by #SCE_GXM_TEXTURE_ALIGNMENT.

	If the texture memory layout does not include mipmaps a value of zero can be
	specified for <c><i>mipCount</i></c>.

	@param[out]	texture			A pointer to the texture to be initialized.
	@param[in]	data			A pointer to the texture data.
	@param[in]	texFormat		The format of the texture.
	@param[in]	width			The width of the texture (32..4096).
	@param[in]	height			The height of the texture (32..4096).
	@param[in]	mipCount		The number of mipmaps in the texture (0..13).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported texture format.

	@note
	Not supported for block compressed texture formats.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureInitTiled(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

/** Initializes the texture control words for cube texture data.

	The <c>data</c> parameter must have an alignment that is valid for the format
	of the texture.  Please see the <em>GPU User’s Guide</em> for each format’s
	alignment requirement.  The largest value the alignment can be is defined
	by #SCE_GXM_TEXTURE_ALIGNMENT.

	If the texture memory layout does not include mipmaps, a value of zero should be
	specified for <c><i>mipCount</i></c>;
	otherwise the memory layout assumes that all mip levels down to 1x1 are present.

	@param[out]	texture			A pointer to texture to be initialized.
	@param[in]	data			A pointer to the texture data.
	@param[in]	texFormat		The format of the texture.
	@param[in]	width			The width of the texture (1..4096).
	@param[in]	height			The height of the texture (1..4096).
	@param[in]	mipCount		The number of mipmaps in the texture (0..13).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported texture format.

	@note
	Not supported for YUV texture formats.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureInitCube(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

/** Initializes the texture control words for cube texture data with arbitrary dimensions.

	The <c>data</c> parameter must have an alignment that is valid for the format
	of the texture.  Please see the <em>GPU User’s Guide</em> for each format’s
	alignment requirement.  The largest value the alignment can be is defined
	by #SCE_GXM_TEXTURE_ALIGNMENT.

	If the texture memory layout does not include mipmaps, a value of zero should be
	specified for <c><i>mipCount</i></c>;
	otherwise the memory layout assumes that all mip levels down to 1x1 are present.

	@param[out]	texture			A pointer to texture to be initialized.
	@param[in]	data			A pointer to the texture data.
	@param[in]	texFormat		The format of the texture.
	@param[in]	width			The width of the texture (1..4096).
	@param[in]	height			The height of the texture (1..4096).
	@param[in]	mipCount		The number of mipmaps in the texture (0..13).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid buffer alignment.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported texture format.

	@note
	Not supported for YUV texture formats.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureInitCubeArbitrary(
	SceGxmTexture *texture,
	const void *data,
	SceGxmTextureFormat texFormat,
	uint32_t width,
	uint32_t height,
	uint32_t mipCount);

/** Gets the type of the given texture.

	@param[in]	texture 		A pointer to the texture.
	@return
	The type of the texture.

	@ingroup render
*/
SceGxmTextureType sceGxmTextureGetType(const SceGxmTexture *texture);

/** Sets the filter mode for when the texture is minified.

	@param[in,out]	texture 		A pointer to the texture.
	@param[in]		minFilter		The min filter mode.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED Operation not supported on #SCE_GXM_TEXTURE_LINEAR_STRIDED texture.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetMinFilter(SceGxmTexture *texture, SceGxmTextureFilter minFilter);

/** Gets the filter mode for when the texture is minified.

	@param[in]	texture 		A pointer to the texture.
	@return
	The min filter mode of the texture.

	@ingroup render
*/
SceGxmTextureFilter sceGxmTextureGetMinFilter(const SceGxmTexture *texture);

/** Sets the filter mode for when the texture is magnified.

	@param[in,out]	texture 		A pointer to the texture.
	@param[in]		magFilter		The mag filter mode.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetMagFilter(SceGxmTexture *texture, SceGxmTextureFilter magFilter);

/** Gets the filter mode for when the texture is magnified.

	@param[in]	texture		A pointer to the texture.
	@return
	The mag filter mode of the texture.

	@ingroup render
*/
SceGxmTextureFilter sceGxmTextureGetMagFilter(const SceGxmTexture *texture);

/** Sets the mip filter mode of the given texture.

	@param[in,out]	texture			A pointer to the texture.
	@param[in]		mipFilter		The mip filter mode.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation is not supported for #SCE_GXM_TEXTURE_LINEAR_STRIDED texture.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetMipFilter(SceGxmTexture *texture, SceGxmTextureMipFilter mipFilter);

/** Gets the mip filter mode of the given texture.

	@param[in]	texture	 	A pointer to the texture.
	@return
	The mip filter mode of the texture.

	@ingroup render
*/
SceGxmTextureMipFilter sceGxmTextureGetMipFilter(const SceGxmTexture *texture);

/** Sets the U addressing mode of the given texture.

	@param[in,out]	texture 		A pointer to the texture.
	@param[in]		addrMode		The U addressing mode.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation is not supported.

	@note
	Border addressing modes are only supported for texture types of #SCE_GXM_TEXTURE_SWIZZLED or
	#SCE_GXM_TEXTURE_SWIZZLED_ARBITRARY.

	@note
	Border addressing modes are not supported for palettized, block compressed, or YUV texture
	formats.

	@note
	An addressing mode of #SCE_GXM_TEXTURE_ADDR_MIRROR is only supported for textures of type #SCE_GXM_TEXTURE_SWIZZLED.

	@note
	Only addressing mode #SCE_GXM_TEXTURE_ADDR_CLAMP is supported for textures of type #SCE_GXM_TEXTURE_LINEAR_STRIDED.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetUAddrMode(SceGxmTexture *texture, SceGxmTextureAddrMode addrMode);

/** Gets the U addressing mode of the given texture.

	@param[in]	texture	 	A pointer to the texture.
	@return
	The U addressing mode of the texture.

	@ingroup render
*/
SceGxmTextureAddrMode sceGxmTextureGetUAddrMode(const SceGxmTexture *texture);

/** Sets the V addressing mode of the given texture.

	@param[in,out]	texture			A pointer to the texture.
	@param[in]		addrMode		The V addressing mode.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation is not supported.

	@note
	Border addressing modes are only supported for texture types of #SCE_GXM_TEXTURE_SWIZZLED or
	#SCE_GXM_TEXTURE_SWIZZLED_ARBITRARY.

	@note
	Border addressing modes are not supported for palettized, block compressed, or YUV texture
	formats.

	@note
	An addressing mode of #SCE_GXM_TEXTURE_ADDR_MIRROR is only supported for textures of type #SCE_GXM_TEXTURE_SWIZZLED.

	@note
	Only addressing mode #SCE_GXM_TEXTURE_ADDR_CLAMP is supported for textures of type #SCE_GXM_TEXTURE_LINEAR_STRIDED.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetVAddrMode(SceGxmTexture *texture, SceGxmTextureAddrMode addrMode);

/** Gets the V addressing mode of the given texture.

	@param[in]	texture 	A pointer to the texture.
	@return
	The V addressing mode of the texture.

	@ingroup render
*/
SceGxmTextureAddrMode sceGxmTextureGetVAddrMode(const SceGxmTexture *texture);

/** Sets the texture format.

	@param[in,out]	texture	 	A pointer to the texture.
	@param[in]		texFormat	The texture format.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT	The operation failed due to invalid alignment of texture data.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation was not supported.

	@note
	The number of bits per pixel for the format needs to match the number of bits per pixel
	for the format used during initialization.

	@note
	The specified texture format cannot refer to
	a YUV format for textures with a type of #SCE_GXM_TEXTURE_CUBE.

	@note
	The specified texture format must support gamma
	for textures with a gamma mode other than #SCE_GXM_TEXTURE_GAMMA_NONE.

	@note
	The specified texture format cannot refer to
	YUV, block compressed or palettized formats for textures using border addressing modes.

	@note
	The specified texture format cannot refer to block
	compressed formats for textures with a type of #SCE_GXM_TEXTURE_TILED, #SCE_GXM_TEXTURE_LINEAR or
	#SCE_GXM_TEXTURE_LINEAR_STRIDED.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetFormat(SceGxmTexture *texture, SceGxmTextureFormat texFormat);

/** Gets the texture format.

	@param[in]	texture 	A pointer to the texture.
	@return
	The format of the texture.

	@ingroup render
*/
SceGxmTextureFormat sceGxmTextureGetFormat(const SceGxmTexture *texture);

/** Sets the value that offsets the computed mip level when reducing the texture.

	The final value is computed as (bias-31)/8, which gives a value in the range [-3.875, +4]
	in 0.125 increments.

	@param[in,out]	texture	 	A pointer to the texture.
	@param[in]		bias		The integer representation of the lod bias (0..63).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation is not supported for #SCE_GXM_TEXTURE_LINEAR_STRIDED textures.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The bias was not in the range [0, 63].

	@note
	Not supported for texture type #SCE_GXM_TEXTURE_LINEAR_STRIDED.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetLodBias(SceGxmTexture *texture, uint32_t bias);

/** Gets the lod bias of the given texture. See #sceGxmTextureSetLodBias().

	@param[in]	texture	 	A pointer to the texture.
	@return
	The integer representation of the lod bias value (0..63).

	@ingroup render
*/
uint32_t sceGxmTextureGetLodBias(const SceGxmTexture *texture);

/** Sets the minimum lod for the given texture.

	@param[in,out]	texture	 	A pointer to the texture.
	@param[in]		lodMin		The minimum lod value to use.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation is not supported for #SCE_GXM_TEXTURE_LINEAR_STRIDED textures.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The minimum lod value was not in the
	range [0, #sceGxmTextureGetMipmapCount()].

	@note
	Not supported for texture type #SCE_GXM_TEXTURE_LINEAR_STRIDED.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetLodMin(SceGxmTexture *texture, uint32_t lodMin);

/** Gets the minimum lod of the given texture. See #sceGxmTextureSetLodMin().

	@param[in]	texture	 	A pointer to the texture.
	@return
	The minimum lod value.

	@ingroup render
*/
uint32_t sceGxmTextureGetLodMin(const SceGxmTexture *texture);

/** Sets the stride in bytes of the given texture.

	@param[in,out]	texture		A pointer to the texture.
	@param[in]		byteStride	The stride in bytes.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The texture was not of type #SCE_GXM_TEXTURE_LINEAR_STRIDED.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The stride was not correctly aligned.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The stride must be in the range [4, 131072].

	@note
	Only supported for texture type #SCE_GXM_TEXTURE_LINEAR_STRIDED

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetStride(SceGxmTexture *texture, uint32_t byteStride);

/** Gets the stride in bytes of the given texture.

	@param[in]	texture	 	A pointer to the texture.
	@return
	The stride of the texture in bytes.

	@note
	For types other than #SCE_GXM_TEXTURE_LINEAR_STRIDED, 0 is returned.

	@ingroup render
*/
uint32_t sceGxmTextureGetStride(const SceGxmTexture *texture);

/** Sets the width of the given texture.

	@param[in,out]	texture	 	A pointer to the texture.
	@param[in]		width		The texture width (1..4096).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The specified width was outside the range 1 to 4096.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The specified #SCE_GXM_TEXTURE_SWIZZLED or #SCE_GXM_TEXTURE_CUBE texture width was not a power of 2.

	@note
	For texture types #SCE_GXM_TEXTURE_SWIZZLED and #SCE_GXM_TEXTURE_CUBE the width must be a power of 2.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetWidth(SceGxmTexture *texture, uint32_t width);

/** Gets the width of the given texture.

	@param[in] texture	 	A pointer to the texture.
	@return
	The width of the texture.

	@ingroup render
*/
uint32_t sceGxmTextureGetWidth(const SceGxmTexture *texture);

/** Sets the height of the given texture.

	@param[in,out]	texture	 	A pointer to the texture.
	@param[in]		height		The texture height (1..4096).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The specified height was outside the range 1 to 4096.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The specified #SCE_GXM_TEXTURE_SWIZZLED or #SCE_GXM_TEXTURE_CUBE texture height was not a power of 2.

	@note
	For texture types #SCE_GXM_TEXTURE_SWIZZLED and #SCE_GXM_TEXTURE_CUBE the height must be a power of 2.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetHeight(SceGxmTexture *texture, uint32_t height);

/** Gets the height of the given texture.

	@param[in]	texture	 	A pointer to the texture.
	@return
	The height of the texture.

	@ingroup render
*/
uint32_t sceGxmTextureGetHeight(const SceGxmTexture *texture);

/** Sets the pointer to the data of the given texture.  The data pointer must
	have an alignment that is valid for the format of the texture. Please see the
	<em>GPU User’s Guide</em> for each format’s alignment requirement.
	The largest value the alignment can be is defined by #SCE_GXM_TEXTURE_ALIGNMENT.

	@param[in,out]	texture			A pointer to the texture.
	@param[in]		data			A pointer to the texture data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid data alignment.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetData(SceGxmTexture *texture, const void *data);

/** Gets a pointer to the data of the given texture.

	@param[in]	texture		A pointer to the texture.
	@return
	A pointer to the texture data.

	@ingroup render
*/
void *sceGxmTextureGetData(const SceGxmTexture *texture);

/** Sets the number of mipmaps in the given texture.

	The possible range of values are:

	0		No mipmaps
	1		Top level only
	..
	13		Levels, size is 4096x4096 down to 1x1

	The distinction between “No mipmaps” and “Top level only” is required for cube maps and planar
	YUV formats only. The former mode indicates that no mipmaps are present, and that the faces or planes
	are stored back to back without any additional alignment. For all other texture types the two
	modes are equivalent.

	@param[in,out]	texture			A pointer to the texture.
	@param[in]		mipCount		The number of mipmaps (0..13).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED Not supported for #SCE_GXM_TEXTURE_LINEAR_STRIDED textures.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The mip count must be in the range [0, 13].

	@note
	Not supported for texture type #SCE_GXM_TEXTURE_LINEAR_STRIDED.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetMipmapCount(SceGxmTexture *texture, uint32_t mipCount);

/** Gets the number of mipmaps in the given texture. See #sceGxmTextureSetMipmapCount().

	@param[in]	texture	 	A pointer to the texture.
	@return
	The mipmap count.

	@ingroup render
*/
uint32_t sceGxmTextureGetMipmapCount(const SceGxmTexture *texture);

/** Sets a pointer to the palette data for the given texture.  The palette data must
	be aligned to at least #SCE_GXM_PALETTE_ALIGNMENT bytes.

	@param[in,out]	texture			A pointer to the texture.
	@param[in]		paletteData		A pointer to palette data.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid palette alignment.

	@note
	For textures with a format of #SCE_GXM_TEXTURE_BASE_FORMAT_P4 or #SCE_GXM_TEXTURE_BASE_FORMAT_P8,
	the palette address must be non-<c>NULL</c>.  For textures with other formats, the palette address must
	be <c>NULL</c>.
	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetPalette(SceGxmTexture *texture, const void *paletteData);

/** Gets a pointer to the palette data for the given texture.

	@param[in]	texture	 	A pointer to the texture.
	@return
	A pointer to the palette data or <c>NULL</c>.

	@ingroup render
*/
void *sceGxmTextureGetPalette(const SceGxmTexture *texture);

/** Sets the texture gamma mode.

	@param[in,out]	texture		A pointer to the texture.
	@param[in]		gammaMode	The gamma mode to apply on the specified texture.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a gamma mode was specified
	that is not supported by the texture format.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetGammaMode(
	SceGxmTexture *texture,
	SceGxmTextureGammaMode gammaMode);

/** Gets the texture gamma mode.

	@param[in]	texture		A pointer to the texture.

	@return
	The gamma mode currently used for the texture.

	@ingroup render
*/
SceGxmTextureGammaMode sceGxmTextureGetGammaMode(
	const SceGxmTexture *texture);

/** Sets the texture normalize mode. When enabled, the results of integer-to-float conversion
	for block-compressed and YUV texture formats, and those texture formats that include 8,
	16, and 24-bit integer components will be normalized to produce results in the range
	[0.0, 1.0] for unsigned integer formats and [-1.0, 1.0] for signed integer formats.

	This setting has no effect when the texture format is floating point.

	@param[in,out]	texture			A pointer to the texture.
	@param[in]		normalizeMode	The normalization mode.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.

	@note When the texture has a gamma mode other than #SCE_GXM_TEXTURE_GAMMA_NONE, or the
	texture format is based on #SCE_GXM_TEXTURE_BASE_FORMAT_U2U10U10U10, results will
	always be normalized.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureSetNormalizeMode(
	SceGxmTexture *texture,
	SceGxmTextureNormalizeMode normalizeMode);

/** Gets the texture normalize mode.

	@param[in]	texture		A pointer to the texture.

	@return
	The normalize mode currently used for the texture.

	@ingroup render
*/
SceGxmTextureNormalizeMode sceGxmTextureGetNormalizeMode(
	const SceGxmTexture *texture);

/**	Checks texture control words are consistent and do not set unexpected bits.

	@param[in]	texture	 	A pointer to the texture.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed because the texture configuration is not supported.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a control word field has an invalid value.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_DATA_POINTER The operation failed because the texture has an invalid data pointer.
	@retval
	SCE_GXM_ERROR_INVALID_TEXTURE_PALETTE_POINTER The operation failed because the texture has an invalid palette pointer.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because the texture data has an invalid alignment.

	@note
	When using macros to create texture control words, care must be taken to only set fields which are valid for the type of texture.
	Due to the fact that some fields overlap, this function cannot check against the following (invalid) cases:
	- Setting TO_DADJUST on a LINEAR_STRIDED texture.
	- Setting T0_MIPMAPCLAMP on a LINEAR_STRIDED texture.
	- Setting T0_MINFILTER on a LINEAR_STRIDED texture.
	- Setting T0_MIPFILTER on a LINEAR_STRIDED texture.
	- Setting T0_STRIDELO/T0_STRIDEHI/T0_STRIDEEX on a texture that is not LINEAR_STRIDED.
	- Setting T1_USIZE/T1_VSIZE on a texture that is not SWIZZLED or CUBE.
	- Setting T1_WIDTH/T1_HEIGHT on a texture that is SWIZZLED or CUBE.

	@ingroup render
*/
SceGxmErrorCode sceGxmTextureValidate(
	const SceGxmTexture *texture);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_TEXTURE_H_ */
