#ifndef _DOLCESDK_PSP2_GXM_TRANSFER_H_
#define _DOLCESDK_PSP2_GXM_TRANSFER_H_

#include <psp2/gxm/types.h>
#include <psp2/gxm/error.h>
#include <psp2/gxm/structs.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The formats available for transfers.

	@ingroup render
*/
typedef enum SceGxmTransferFormat {
	SCE_GXM_TRANSFER_FORMAT_U8_R				= 0x00000000U,	///< 8-bit format, 8-bit unsigned integer.
	SCE_GXM_TRANSFER_FORMAT_U4U4U4U4_ABGR		= 0x00010000U,	///< 16-bit format, 4x 4-bit unsigned integer, read in ABGR order from memory.
	SCE_GXM_TRANSFER_FORMAT_U1U5U5U5_ABGR		= 0x00020000U,	///< 16-bit format, 1-bit unsigned and 3x 5-bit unsigned integer, read in ABGR order from memory.
	SCE_GXM_TRANSFER_FORMAT_U5U6U5_BGR			= 0x00030000U,	///< 16-bit format, 5-bit unsigned, 6-bit unsigned and 5-bit unsigned integer, read in BGR order from memory.
	SCE_GXM_TRANSFER_FORMAT_U8U8_GR				= 0x00040000U,	///< 16-bit format, 2x 8-bit unsigned integer, read in GR order from memory.
	SCE_GXM_TRANSFER_FORMAT_U8U8U8_BGR			= 0x00050000U,	///< 24-bit packed format, 3x 8-bit unsigned integer, read in BGR order from memory.
	SCE_GXM_TRANSFER_FORMAT_U8U8U8U8_ABGR		= 0x00060000U,	///< 32-bit format, 4x 8-bit unsigned integer, read in ABGR order from memory.
	SCE_GXM_TRANSFER_FORMAT_VYUY422				= 0x00070000U,	///< Interleaved YUV, VYUY 2-pixel blocks.
	SCE_GXM_TRANSFER_FORMAT_YVYU422				= 0x00080000U,	///< Interleaved YUV, YVYU 2-pixel blocks.
	SCE_GXM_TRANSFER_FORMAT_UYVY422				= 0x00090000U,	///< Interleaved YUV, UYVY 2-pixel blocks.
	SCE_GXM_TRANSFER_FORMAT_YUYV422				= 0x000a0000U,	///< Interleaved YUV, YUYV 2-pixel blocks.
	SCE_GXM_TRANSFER_FORMAT_U2U10U10U10_ABGR	= 0x000d0000U,	///< 32-bit format, 2-bit unsigned and 3x 10-bit unsigned integer, read in ABGR order from memory.
	SCE_GXM_TRANSFER_FORMAT_RAW16				= 0x000f0000U,	///< 16-bit format, raw data.
	SCE_GXM_TRANSFER_FORMAT_RAW32				= 0x00110000U,	///< 32-bit format, raw data.
	SCE_GXM_TRANSFER_FORMAT_RAW64				= 0x00120000U,	///< 62-bit format, raw data.
	SCE_GXM_TRANSFER_FORMAT_RAW128				= 0x00130000U	///< 128-bit format, raw data.
} SceGxmTransferFormat;

/** The transfer memory layout types.

	@ingroup render
*/
typedef enum SceGxmTransferType {
	SCE_GXM_TRANSFER_LINEAR			= 0x00000000U,	///< The transfer area uses a linear memory layout.
	SCE_GXM_TRANSFER_TILED			= 0x00400000U,	///< The transfer area uses a tiled memory layout.
	SCE_GXM_TRANSFER_SWIZZLED		= 0x00800000U	///< The transfer area uses a swizzled memory layout.
} SceGxmTransferType;

/** Vertex and fragment synchronization flags for transfers.

	@ingroup render
*/
typedef enum SceGxmTransferFlags
{
	SCE_GXM_TRANSFER_FRAGMENT_SYNC	= 0x00000001U,	///< The transfer should wait for fragment processing to complete.
	SCE_GXM_TRANSFER_VERTEX_SYNC	= 0x00000002U	///< The transfer should wait for vertex processing to complete.
} SceGxmTransferFlags;

/** The color key modes.

	@ingroup render
*/
typedef enum SceGxmTransferColorKeyMode {
	SCE_GXM_TRANSFER_COLORKEY_NONE,			///< No color keying on source read.
	SCE_GXM_TRANSFER_COLORKEY_PASS,			///< Matching colors are passed.
	SCE_GXM_TRANSFER_COLORKEY_REJECT		///< Matching colors are rejected.
} SceGxmTransferColorKeyMode;

/** Performs a copy of data using transfer hardware, optionally converting between RGB formats,
	between YUV formats, or between memory layouts. For both RGB and YUV formats, color keying can
	also be applied to source data.

	@param[in]	width			The width of the transfer in pixels (1..1024).
	@param[in]	height			The height of the transfer in pixels (1..1024).
	@param[in]	colorKeyValue	The value used for color key comparison.
	@param[in]	colorKeyMask	The mask applied before color key processing. A value of 1 indicates that
								the bit should be used in the color key test.
	@param[in]	colorKeyMode	The mode used to specify whether color keying is enabled, or whether
								matching colors are passed or rejected.
	@param[in]	srcFormat		The source format.
	@param[in]	srcType			The source type.
	@param[in]	srcAddress		The source address.
	@param[in]	srcX			The X position associated with the top left of the source area (0..8191).
	@param[in]	srcY			The Y position associated with the top left of the source area (0..8191).
	@param[in]	srcStride		The source stride in bytes (-32768..32767).
	@param[in]	destFormat		The destination format.
	@param[in]	destType		The destination type.
	@param[in]	destAddress		The destination address.
	@param[in]	destX			The X position associated with the top left of the destination area (0..8191).
	@param[in]	destY			The Y position associated with the top left of the destination area (0..8191).
	@param[in]	destStride		The destination stride in bytes (-32768..32767).
	@param[in]	syncObject		An optional sync object to synchronize against transfer processing.
	@param[in]	syncFlags		The flags that define vertex and fragment synchronization behavior for the transfer.
	@param[in]	notification	A pointer to a notification object used to identify completion of
								transfer processing. Set this parameter to <c>NULL</c> if this is not required.

	@note The format of <c><i>colorKeyValue</i></c> and <c><i>colorKeyMask</i></c> parameters is either U8U8U8U8_ABGR (for RGB formats) or the
	destination YUV format (for YUV formats). However, if both the <c><i>srcFormat</i></c> and <c><i>destFormat</i></c> parameters are
	#SCE_GXM_TRANSFER_FORMAT_U2U10U10U10_ABGR then the format is U2U10U10U10_ABGR. If the <c><i>srcFormat</i></c> parameter refers to an
	RGB format that includes components that are less than 8 bits in size (#SCE_GXM_TRANSFER_FORMAT_U4U4U4U4_ABGR for example), the source
	data is expanded by shifting to the U8U8U8U8_ABGR format. After the shift the data occupies the most significant bits of the 8-bit output.
	The least significant bits are then formed by replicating the most significant bits of the source. As such the values of the
	<c><i>colorKeyValue</i></c> and	<c><i>colorKeyMask</i></c> parameters should take this into account. This is done by either defining
	<c><i>colorKeyValue</i></c> to include the replicated bits or by specifying a <c><i>colorKeyMask</i></c> value that masks off replicated bits.

	@note It is not permitted for both <c><i>srcType</i></c> and <c><i>destType</i></c> to be set to #SCE_GXM_TRANSFER_SWIZZLED. If this
	form of copy operation is required, it can be performed by setting both <c><i>srcType</i></c> and <c><i>destType</i></c> parameters
	to #SCE_GXM_TRANSFER_LINEAR.

	@note It is not permitted for <c><i>srcType</i></c> to be #SCE_GXM_TRANSFER_TILED if <c><i>destType</i></c> is #SCE_GXM_TRANSFER_SWIZZLED.

	@note It is not permitted for <c><i>srcType</i></c> to be #SCE_GXM_TRANSFER_SWIZZLED if <c><i>destType</i></c> is #SCE_GXM_TRANSFER_TILED.

	@note <c><i>width</i></c> and <c><i>height</i></c> must both be a power of two if <c><i>srcType</i></c> or <c><i>destType</i></c> are #SCE_GXM_TRANSFER_SWIZZLED.

	@note <c><i>width</i></c> and <c><i>height</i></c> must both be aligned to 32 if <c><i>srcType</i></c> or <c><i>destType</i></c> are #SCE_GXM_TRANSFER_TILED.

	@note <c><i>width</i></c> must be even if <c><i>srcFormat</i></c> or <c><i>dstFormat</i></c> are a YUV format.

	@note <c><i>srcStride</i></c> must be a multiple of the number of bytes per pixel associated with <c><i>srcFormat</i></c>.

	@note <c><i>srcStride</i></c> must match the width in bytes if <c><i>srcType</i></c> is #SCE_GXM_TRANSFER_TILED or #SCE_GXM_TRANSFER_SWIZZLED.

	@note <c><i>srcX</i></c> and <c><i>srcY</i></c> must both be 0 if <c><i>srcType</i></c> is #SCE_GXM_TRANSFER_TILED or #SCE_GXM_TRANSFER_SWIZZLED.

	@note <c><i>srcX</i></c> must be even if <c><i>srcFormat</i></c> is a YUV format.

	@note <c><i>srcX</i></c> + <c><i>width</i></c> must be less than 8192.

	@note <c><i>srcY</i></c> + <c><i>height</i></c> must be less than 8192.

	@note <c><i>destStride</i></c> must be a multiple of the number of bytes per pixel associated with <c><i>destFormat</i></c>.

	@note <c><i>destStride</i></c> must match the width in bytes if <c><i>destType</i></c> is #SCE_GXM_TRANSFER_TILED or #SCE_GXM_TRANSFER_SWIZZLED.

	@note <c><i>destX</i></c> and <c><i>destY</i></c> must both be 0 if <c><i>destType</i></c> is #SCE_GXM_TRANSFER_TILED or #SCE_GXM_TRANSFER_SWIZZLED.

	@note <c><i>destX</i></c> must be even if <c><i>destFormat</i></c> is a YUV format.

	@note <c><i>destX</i></c> + <c><i>width</i></c> must be less than 8192.

	@note <c><i>destY</i></c> + <c><i>height</i></c> must be less than 8192.

	@note <c><i>srcFormat</i></c> and <c><i>destFormat</i></c> must both be of the same fundamental type (RGB, YUV, or RAW).

	@note <c><i>colorKeyMode</i></c> must be #SCE_GXM_TRANSFER_COLORKEY_NONE for RAW formats.

	@note <c><i>colorKeyMode</i></c> must be #SCE_GXM_TRANSFER_COLORKEY_NONE if <c><i>srcType</i></c> or <c><i>destType</i></c> are not #SCE_GXM_TRANSFER_LINEAR.

	@note <c><i>colorKeyMode</i></c> must be #SCE_GXM_TRANSFER_COLORKEY_NONE if either <c><i>srcFormat</i></c> or <c><i>destFormat</i></c> are
	#SCE_GXM_TRANSFER_FORMAT_U2U10U10U10_ABGR and <c><i>srcFormat</i></c> is not equal to <c><i>destFormat</i></c>.

	@note If <c><i>srcFormat</i></c> is a format of type RAW, then <c><i>destFormat</i></c> must be the same format.

	@note If <c><i>srcFormat</i></c> is a format of type RAW, then <c><i>srcType</i></c> cannot be #SCE_GXM_TRANSFER_TILED.

	@note If <c><i>destFormat</i></c> is a format of type RAW, then <c><i>destType</i></c> cannot be #SCE_GXM_TRANSFER_TILED.

	@note If <c><i>srcFormat</i></c> is #SCE_GXM_TRANSFER_FORMAT_RAW64, then a maximum of 524288 pixels can be
	copied (1024x512).

	@note If <c><i>srcFormat</i></c> is #SCE_GXM_TRANSFER_FORMAT_RAW128, then a maximum of 262144 pixels can be
	copied (512x512).

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported format.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid alignment.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_THREAD The operation failed because the function was called from the display queue thread.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
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

/** Performs a fixed 50% downscale of source data using a box filter.

	@param[in]	srcFormat		The source format.
	@param[in]	srcAddress		The source address.
	@param[in]	srcX			The X position associated with the top left of the source area (0..8191).
	@param[in]	srcY			The Y position associated with the top left of the source area (0..8191).
	@param[in]	srcWidth		The width of the source area in pixels (2..1024).
	@param[in]	srcHeight		The height of the source area in pixels (2..1024).
	@param[in]	srcStride		The source stride in bytes (-32768..32767).
	@param[in]	destFormat		The destination format.
	@param[in]	destAddress		The destination address.
	@param[in]	destX			The X position associated with the top left of the destination area (0..8191).
	@param[in]	destY			The Y position associated with the top left of the destination area (0..8191)
	@param[in]	destStride		The destination stride in bytes (-32768..32767).
	@param[in]	syncObject		An optional sync object to synchronize against transfer processing.
	@param[in]	syncFlags		The flags defining vertex and fragment synchronization behavior for the transfer.
	@param[in]	notification	A pointer to a notification object used to identify completion of
								transfer processing. Set this parameter to <c>NULL</c> if this is not required.

	@note This function can only be used on linear data.

	@note <c><i>srcFormat</i></c> and <c><i>destFormat</i></c> must both be RGB formats.

	@note <c><i>srcStride</i></c> must be a multiple of the number of bytes per pixel associated with <c><i>srcFormat</i></c>.

	@note <c><i>srcWidth</i></c> and <c><i>srcHeight</i></c> must both be even.

	@note <c><i>srcWidth</i></c> must be less than 16, or aligned to 16.

	@note <c><i>srcX</i></c> + <c><i>srcWidth</i></c> must be less than 8192.

	@note <c><i>srcY</i></c> + <c><i>srcHeight</i></c> must be less than 8192.

	@note <c><i>destStride</i></c> must be a multiple of the number of bytes per pixel associated with <c><i>destFormat</i></c>.

	@note <c><i>destX</i></c> + (<c><i>srcWidth</i></c> / 2) must be less than 8192.

	@note <c><i>destY</i></c> + (<c><i>srcHeight</i></c> / 2) must be less than 8192.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported format.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid alignment.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_THREAD The operation failed because the function was called from the display queue thread.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/

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

/**	Performs a fill of RGB or YUV data with a specific value.

	@param[in]	fillColor		The fill color.
	@param[in]	destFormat		The destination format.
	@param[in]	destAddress		The destination address.
	@param[in]	destX			The X position associated with the top left of the destination area (0..8191).
	@param[in]	destY			The Y position associated with the top left of the destination area (0..8191).
	@param[in]	destWidth		The width of the destination in pixels (1..1024).
	@param[in]	destHeight		The height of the destination in pixels (1..1024).
	@param[in]	destStride		The destination stride in bytes (-32768..32767).
	@param[in]	syncObject		An optional sync object to synchronize against transfer processing.
	@param[in]	syncFlags		The flags that define vertex and fragment synchronization behavior for the transfer.
	@param[in]	notification	A pointer to a notification object used to identify completion of
								transfer processing. Set this parameter to <c>NULL</c> if this is not required.

	@note This function can only be used on linear data.

	@note The <c><i>fillColor</i></c> parameter format is either U8U8U8U8_ABGR (for RGB formats) or U8U8U8U8_AYUV
	(for YUV formats). However, if the <c><i>destFormat</i></c> parameter is #SCE_GXM_TRANSFER_FORMAT_U2U10U10U10_ABGR,
	the format should be U2U10U10U10_ABGR.

	@note <c><i>destFormat</i></c> must be an RGB or YUV format.

	@note <c><i>destWidth</i></c> must be even if <c><i>destFormat</i></c> is a YUV format.

	@note <c><i>destStride</i></c> must be a multiple of the number of bytes per pixel associated with <c><i>destFormat</i></c>.

	@note <c><i>destX</i></c> must be even if <c><i>destFormat</i></c> is a YUV format.

	@note <c><i>destX</i></c> + <c><i>destWidth</i></c> must be less than 8192.

	@note <c><i>destY</i></c> + <c><i>destHeight</i></c> must be less than 8192.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED The operation failed due to an unsupported format.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid alignment.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_THREAD The operation failed because the function was called from the display queue thread.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/

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

/** Blocks until all transfers have finished.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_THREAD The operation failed because the function was called from the display queue thread.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/

SceGxmErrorCode sceGxmTransferFinish(void);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_TRANSFER_H_ */
