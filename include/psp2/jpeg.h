/**
 * \usergroup{SceJpeg}
 * \usage{psp2/jpeg.h,SceJpeg_stub}
 */

#ifndef _DOLCESDK_PSP2_JPEG_H_
#define _DOLCESDK_PSP2_JPEG_H_

#include <psp2/types.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

/* Option flag for sceJpegInitMJpegWithParam() */
#define SCE_JPEG_MJPEG_INIT_OPTION_NONE          0
#define SCE_JPEG_MJPEG_INIT_OPTION_LPDDR2_MEMORY 1

/* Upper bound of screen size (upper bound determined by baseline JPEG) */
#define SCE_JPEG_MAX_HEIGHT                      65535
#define SCE_JPEG_MAX_WIDTH                       65535

/* Value assigned to fifth argument of sceJpegDecodeMJpeg() and sceJpegDecodeMJpegYCbCr() */
#define SCE_JPEG_MJPEG_WITH_DHT                  0
#define SCE_JPEG_MJPEG_WITHOUT_DHT               1
#define SCE_JPEG_MJPEG_ANY_SAMPLING_WITHOUT_DHT  2
#define SCE_JPEG_MJPEG_ANY_SAMPLING              3

#define SCE_JPEG_MJPEG_DOWNSCALE_1_2             (1<<4)
#define SCE_JPEG_MJPEG_DOWNSCALE_1_4             (1<<5)
#define SCE_JPEG_MJPEG_DOWNSCALE_1_8             (1<<6)

/* Value of color space/format assigned to sceJpegMJpegCsc() */
#define SCE_JPEG_PIXEL_RGBA8888                  0      /* R:G:B:A=8:8:8:8 32bit U8U8U8U8_ABGR */
#define SCE_JPEG_PIXEL_BGRA8888                  4      /* B:G:R:A=8:8:8:8 32bit U8U8U8U8_ARGB */

#define SCE_JPEG_COLORSPACE_JFIF                 0x00
#define SCE_JPEG_COLORSPACE_BT601                0x10

#define SCE_JPEG_NO_CSC_OUTPUT                   (-1)

/* Error codes */
#define SCE_JPEG_OK                              0

#define SCE_JPEG_ERROR_IMAGE_EMPTY               ((int)0x80650003)
#define SCE_JPEG_ERROR_BAD_MARKER_LENGTH         ((int)0x80650004)
#define SCE_JPEG_ERROR_BAD_DHT_COUNTS            ((int)0x80650005)
#define SCE_JPEG_ERROR_BAD_DHT_INDEX             ((int)0x80650006)
#define SCE_JPEG_ERROR_BAD_DQT_INDEX             ((int)0x80650007)
#define SCE_JPEG_ERROR_DECODE_ERROR              ((int)0x80650009)
#define SCE_JPEG_ERROR_INVALID_POINTER           ((int)0x80650010)
#define SCE_JPEG_ERROR_BAD_COMPONENT_ID          ((int)0x80650011)
#define SCE_JPEG_ERROR_UNSUPPORT_COLORSPACE      ((int)0x80650013)
#define SCE_JPEG_ERROR_BAD_MCU_SIZE              ((int)0x80650014)
#define SCE_JPEG_ERROR_BAD_PRECISION             ((int)0x80650015)
#define SCE_JPEG_ERROR_UNSUPPORT_SAMPLING        ((int)0x80650016)
#define SCE_JPEG_ERROR_COMPONENT_COUNT           ((int)0x80650017)
#define SCE_JPEG_ERROR_CONVERSION_NOTIMPL        ((int)0x80650018)
#define SCE_JPEG_ERROR_EOI_EXPECTED              ((int)0x80650019)
#define SCE_JPEG_ERROR_UNSUPPORT_IMAGE_SIZE      ((int)0x80650020)
#define SCE_JPEG_ERROR_NO_HUFF_TABLE             ((int)0x80650021)
#define SCE_JPEG_ERROR_NO_QUANT_TABLE            ((int)0x80650022)
#define SCE_JPEG_ERROR_NO_SOI                    ((int)0x80650023)
#define SCE_JPEG_ERROR_BAD_DQT_MARKER            ((int)0x80650024)
#define SCE_JPEG_ERROR_BAD_DHT_MARKER            ((int)0x80650025)
#define SCE_JPEG_ERROR_BAD_DRI_MARKER            ((int)0x80650026)
#define SCE_JPEG_ERROR_BAD_SOF_MARKER            ((int)0x80650027)
#define SCE_JPEG_ERROR_BAD_SOS_MARKER            ((int)0x80650028)
#define SCE_JPEG_ERROR_SOF_DUPLICATE             ((int)0x80650029)
#define SCE_JPEG_ERROR_NO_LOSSLESS_SUPPORT       ((int)0x80650031)
#define SCE_JPEG_ERROR_NO_ARITH_SUPPORT          ((int)0x80650032)
#define SCE_JPEG_ERROR_UNKNOWN_MARKER            ((int)0x80650035)
#define SCE_JPEG_ERROR_BAD_RESTART_MARKER        ((int)0x80650036)
#define SCE_JPEG_ERROR_UNEXPECTED_MARKER         ((int)0x80650037)
#define SCE_JPEG_ERROR_INVALID_REGION            ((int)0x80650038)
#define SCE_JPEG_ERROR_INVALID_STATE             ((int)0x80650039)
#define SCE_JPEG_ERROR_CANNOT_CONTINUE           ((int)0x80650040)
#define SCE_JPEG_ERROR_MEMORY_SIZE               ((int)0x80650041)
#define SCE_JPEG_ERROR_CANNOT_INIT               ((int)0x80650042)
#define SCE_JPEG_ERROR_CANNOT_FINISH             ((int)0x80650043)
#define SCE_JPEG_ERROR_INVALID_COLOR_FORMAT      ((int)0x80650050)
#define SCE_JPEG_ERROR_NOT_PHY_CONTINUOUS_MEMORY ((int)0x80650053)
#define SCE_JPEG_ERROR_INVALID_DECODE_MODE       ((int)0x80650060)
#define SCE_JPEG_ERROR_BAD_PROGRESSIVE_PARAM     ((int)0x80650061)
#define SCE_JPEG_ERROR_EXCEED_MAX_SPLIT_DECODER  ((int)0x80650062)
#define SCE_JPEG_ERROR_INIT_DONE                 ((int)0x80650063)
#define SCE_JPEG_ERROR_INPUT_SUSPENDED           ((int)0x80650064)
#define SCE_JPEG_ERROR_INPUT_DATA_TOO_BIG        ((int)0x80650065)
#define SCE_JPEG_ERROR_INVALID_DATA_SIZE         ((int)0x80650066)
#define SCE_JPEG_ERROR_INVALID_INIT_PARAM        ((int)0x80650067)

/* for backward compatibility */
#define SCE_JPEG_ERROR_UNSUPPORT_DOWNSCALE       (SCE_JPEG_ERROR_INVALID_DECODE_MODE)
#define SCE_JPEG_ERROR_OUT_OF_MEMORY             (SCE_JPEG_ERROR_MEMORY_SIZE)

/* Initialization/termination of motion JPEG */
int sceJpegInitMJpeg(int maxSplitDecoder);
int sceJpegFinishMJpeg(void);

typedef struct {
	SceSize		size;
	int			maxSplitDecoder;
	int			option;
} SceJpegMJpegInitParam;

int sceJpegInitMJpegWithParam(const SceJpegMJpegInitParam *pInitParam);

/* Decode JPEG data to RGBA format */
int sceJpegDecodeMJpeg(
		const unsigned char *pJpeg,
		SceSize isize,
		void *pRGBA,
		SceSize osize,
		int decodeMode,
		void *pTempBuffer,
		SceSize tempBufferSize,
		void *pCoefBuffer,
		SceSize coefBufferSize);

/* Decode JPEG data (no color conversion) */
int sceJpegDecodeMJpegYCbCr(
		const unsigned char *pJpeg,
		SceSize isize,
		unsigned char *pYCbCr,
		SceSize osize,
		int decodeMode,
		void *pCoefBuffer,
		SceSize coefBufferSize);

/* Color convert YCbCr data to RGBA */
int sceJpegMJpegCsc(
		void *pRGBA,
		const unsigned char *pYCbCr,
		int xysize,
		int iFrameWidth,
		int colorOption,
		int sampling);

/* Color convert YCbCr data to RGBA (support YCbCr 4:4:4 only) */
int sceJpegCsc(
		void *pRGBA,
		const unsigned char *pYCbCr,
		int xysize,
		int iFrameWidth,
		int colorOption,
		int sampling);

typedef struct {
	int colorSpace;
	unsigned short imageWidth;
	unsigned short imageHeight;
	SceSize outputBufferSize;
	SceSize tempBufferSize;
	SceSize coefBufferSize;
	struct {
		unsigned int x;
		unsigned int y;
	} pitch[4];
} SceJpegOutputInfo;

/* Return color space and each buffer sizes required when decoding a JPEG image */
int sceJpegGetOutputInfo(
		const unsigned char *pJpeg,
		SceSize isize,
		int outputFormat,
		int decodeMode,
		SceJpegOutputInfo *pOutputInfo);

/* Color space values returned by above functions.
 * The logical OR-ed value of color space and color space sampling.
 */
#define SCE_JPEG_CS_UNKNOWN   (0<<16) /* unknown */
#define SCE_JPEG_CS_GRAYSCALE (1<<16) /* Y only */
#define SCE_JPEG_CS_YCBCR     (2<<16) /* Y/Cb/Cr */

#define SCE_JPEG_CS_H1V1      (0x101) /* 1:1 */
#define SCE_JPEG_CS_H2V1      (0x201) /* 2:1 */
#define SCE_JPEG_CS_H4V1      (0x401) /* 4:1 */
#define SCE_JPEG_CS_H1V2      (0x102) /* 1:2 */
#define SCE_JPEG_CS_H2V2      (0x202) /* 2:2 */
#define SCE_JPEG_CS_H1V4      (0x104) /* 1:4 */

/* Control information for split decoding */
typedef struct {
	unsigned char  *pStreamBuffer;
	SceSize			streamBufferSize;
	unsigned char  *pWriteBuffer;
	SceSize			writeBufferSize;
	int				isEndOfStream;
	int				decodeMode;

	SceJpegOutputInfo outputInfo;

	void		   *pOutputBuffer;
	void		   *pCoefBuffer;

	unsigned int	internalData[3];
} SceJpegSplitDecodeCtrl;

/* Creation/deletion of split decoder */
int sceJpegCreateSplitDecoder(SceJpegSplitDecodeCtrl *pCtrl);
int sceJpegDeleteSplitDecoder(SceJpegSplitDecodeCtrl *pCtrl);

/* Process split decoding of JPEG data (no color conversion) */
int sceJpegSplitDecodeMJpeg(SceJpegSplitDecodeCtrl *pCtrl);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_JPEG_H_ */

