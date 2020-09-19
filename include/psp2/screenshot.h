/**
 * \usergroup{SceScreenShot}
 * \usage{psp2/screenshot.h,SceScreenShot_stub,SCE_SYSMODULE_SCREEN_SHOT}
 */


#ifndef _DOLCESDK_PSP2_SCREENSHOT_H_
#define _DOLCESDK_PSP2_SCREENSHOT_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SceScreenShot Error Codes
 */

typedef enum SceScreenshotError {
	SCE_SCREENSHOT_ERROR_INVALID_ARGUMENT       = (int)0x80102F01,
	SCE_SCREENSHOT_ERROR_NO_MEMORY              = (int)0x80102F02,
	SCE_SCREENSHOT_ERROR_FILE_NOT_FOUND         = (int)0x80102F03,
	SCE_SCREENSHOT_ERROR_NOT_SUPPORTED_FORMAT   = (int)0x80102F04,
	SCE_SCREENSHOT_ERROR_MEDIA_FULL             = (int)0x80102F05,
	SCE_SCREENSHOT_ERROR_INTERNAL               = (int)0x80102F06,
	SCE_SCREENSHOT_ERROR_SCREENSHOT_DISABLED    = (int)0x80102F07,
	SCE_SCREENSHOT_ERROR_CAPTURE_FAILED         = (int)0x80102F08,
	SCE_SCREENSHOT_ERROR_CAPTURE_BUSY           = (int)0x80102F09,
	SCE_SCREENSHOT_ERROR_CAPTURE_CANCELED       = (int)0x80102F0A,
	SCE_SCREENSHOT_ERROR_MEDIA_NOT_EXIST        = (int)0x80102F0B,
	SCE_SCREENSHOT_ERROR_CONTENT_FULL           = (int)0x80102F0C,
	SCE_SCREENSHOT_ERROR_INVALID_DATA           = (int)0x80102F0D,
	SCE_SCREENSHOT_ERROR_NOT_SUPPORTED_DATA     = (int)0x80102F0E,
} SceScreenshotError;

/*
 * SceScreenShot Constants
 */

//! Max size of path strings (includes device name and NULL terminator)
#define SCE_SCREENSHOT_MAX_FS_PATH              (1024)

//! Max length of photo title
#define SCE_SCREENSHOT_MAX_PHOTO_TITLE_LEN      (64)

//! Max size of photo title (includes NULL terminator)
#define SCE_SCREENSHOT_MAX_PHOTO_TITLE_SIZE     (SCE_SCREENSHOT_MAX_PHOTO_TITLE_LEN * 4)

//! Max length of game title
#define SCE_SCREENSHOT_MAX_GAME_TITLE_LEN       (64)

//! Max size of game title (includes NUL terminator)
#define SCE_SCREENSHOT_MAX_GAME_TITLE_SIZE      (SCE_SCREENSHOT_MAX_GAME_TITLE_LEN * 4)

//! Max length of comment (description)
#define SCE_SCREENSHOT_MAX_GAME_COMMENT_LEN     (128)

//! Max size of comment (description) (includes NUL terminator)
#define SCE_SCREENSHOT_MAX_GAME_COMMENT_SIZE    (SCE_SCREENSHOT_MAX_GAME_COMMENT_LEN * 4)

/*
 * SceScreenShot Types
 */

/* Mode for screenshot capture */
typedef enum SceScreenShotCaptureMode {
	SCE_SCREENSHOT_CAPTURE_MODE_NORMAL           = 0,
	SCE_SCREENSHOT_CAPTURE_MODE_FORCE_CAPTURE    = 1,
} SceScreenShotCaptureMode;

/* Screenshot parameter */
typedef struct SceScreenShotParam {
	const SceChar8 *photoTitle;     //!< Photo title
	const SceChar8 *gameTitle;      //!< Game title
	const SceChar8 *gameComment;    //!< Comment (description)
	void *reserved;                 //!< Reserved range (Must be NULL)
} SceScreenShotParam;

/* Screenshot game info */
typedef struct SceScreenShotGameInfo {
	SceChar8 photoTitle[SCE_SCREENSHOT_MAX_PHOTO_TITLE_SIZE];      /* photo title */
	SceChar8 gameTitle[SCE_SCREENSHOT_MAX_GAME_TITLE_SIZE];        /* game title  */
	SceChar8 gameComment[SCE_SCREENSHOT_MAX_GAME_COMMENT_SIZE];    /* comment (description) */
	SceDateTime createdDate;                                       /* image created date*/
} SceScreenShotGameInfo;

/* Screenshot capture file information */
typedef struct SceScreenShotCaptureFileInfo {
	SceChar8 path[SCE_SCREENSHOT_MAX_FS_PATH];    /* path of capture file */
} SceScreenShotCaptureFileInfo;

/* Callback function */
typedef SceBool (*SceScreenShotCaptureCancelFunc)(void*);

/*
 * SceScreenShot Functions
 */

/* Set screenshot parameters */
SceInt32 sceScreenShotSetParam(const SceScreenShotParam *param);

/* Set overlay image */
SceInt32 sceScreenShotSetOverlayImage(
	const SceChar8 *filePath,
	SceInt32 offsetX,
	SceInt32 offsetY);

/* Disable screenshot */
SceInt32 sceScreenShotDisable(void);

/* Enable screenshot */
SceInt32 sceScreenShotEnable(void);

/* Disable screenshot notification */
SceInt32 sceScreenShotDisableNotification(void);

/* Enable screenshot notification */
SceInt32 sceScreenShotEnableNotification(void);

/* Capture screenshot */
SceInt32 sceScreenShotCapture(
	SceScreenShotCaptureMode mode,
	SceScreenShotCaptureFileInfo *captureFileInfo,
	SceScreenShotCaptureCancelFunc cancelFunc,
	void *userdata);

/* Get screenshot parameters */
SceInt32 sceScreenShotGetParam(const SceChar8* filePath, SceScreenShotGameInfo* param);

#ifdef __cplusplus
}
#endif

#endif /* _DOLCESDK_PSP2_SCREENSHOT_H_ */
