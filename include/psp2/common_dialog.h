/**
 * \usergroup{SceCommonDialog}
 * \usage{psp2/common_dialog.h,SceCommonDialog_stub}
 */


#ifndef _PSP2_COMMON_API_H_
#define _PSP2_COMMON_API_H_

#include <string.h>
#include <psp2/system_param.h>
#include <psp2/gxm.h>
#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Errors */
typedef enum SceCommonDialogErrorCode {
	SCE_COMMON_DIALOG_ERROR_BUSY                            = (int)0x80020401,
	SCE_COMMON_DIALOG_ERROR_NULL                            = (int)0x80020402,
	SCE_COMMON_DIALOG_ERROR_INVALID_ARGUMENT                = (int)0x80020403,
	SCE_COMMON_DIALOG_ERROR_NOT_RUNNING                     = (int)0x80020404,
	SCE_COMMON_DIALOG_ERROR_NOT_SUPPORTED                   = (int)0x80020405,
	SCE_COMMON_DIALOG_ERROR_ILLEGAL_CALLER_THREAD           = (int)0x80020406,
	SCE_COMMON_DIALOG_ERROR_NOT_CONFIGURED                  = (int)0x80020407,
	SCE_COMMON_DIALOG_ERROR_NOT_AVAILABLE                   = (int)0x80020408,
	SCE_COMMON_DIALOG_ERROR_NOT_FINISHED                    = (int)0x80020410,
	SCE_COMMON_DIALOG_ERROR_NOT_IN_USE                      = (int)0x80020411,
	SCE_COMMON_DIALOG_ERROR_INVALID_COLOR_FORMAT            = (int)0x80020420,
	SCE_COMMON_DIALOG_ERROR_INVALID_SURFACE_RESOLUTION      = (int)0x80020421,
	SCE_COMMON_DIALOG_ERROR_INVALID_SURFACE_STRIDE          = (int)0x80020422,
	SCE_COMMON_DIALOG_ERROR_INVALID_SURFACE_TYPE            = (int)0x80020423,
	SCE_COMMON_DIALOG_ERROR_WITHIN_SCENE                    = (int)0x80020424,
	SCE_COMMON_DIALOG_ERROR_IME_IN_USE                      = (int)0x80020430,
	SCE_COMMON_DIALOG_ERROR_INVALID_LANGUAGE                = (int)0x80020431,
	SCE_COMMON_DIALOG_ERROR_INVALID_ENTER_BUTTON_ASSIGN     = (int)0x80020432,
	SCE_COMMON_DIALOG_ERROR_INVALID_INFOBAR_PARAM           = (int)0x80020433,
	SCE_COMMON_DIALOG_ERROR_INVALID_BG_COLOR                = (int)0x80020434,
	SCE_COMMON_DIALOG_ERROR_INVALID_DIMMER_COLOR            = (int)0x80020435,
	SCE_COMMON_DIALOG_ERROR_GXM_IS_UNINITIALIZED            = (int)0x80020436,
	SCE_COMMON_DIALOG_ERROR_UNEXPECTED_FATAL                = (int)0x8002047F
} SceCommonDialogErrorCode;

typedef struct SceCommonDialogConfigParam {
	SceUInt32 sdkVersion;
	SceSystemParamLang language;
	SceSystemParamEnterButtonAssign enterButtonAssign;
	SceUInt8 reserved[32];
} SceCommonDialogConfigParam;

typedef enum SceCommonDialogStatus {
	SCE_COMMON_DIALOG_STATUS_NONE       = 0,
	SCE_COMMON_DIALOG_STATUS_RUNNING    = 1,
	SCE_COMMON_DIALOG_STATUS_FINISHED   = 2
} SceCommonDialogStatus;

typedef enum SceCommonDialogResult {
	SCE_COMMON_DIALOG_RESULT_OK,
	SCE_COMMON_DIALOG_RESULT_USER_CANCELED,
	SCE_COMMON_DIALOG_RESULT_ABORTED
} SceCommonDialogResult;

typedef struct SceCommonDialogRenderTargetInfo {
	ScePVoid depthSurfaceData;
	ScePVoid colorSurfaceData;
	SceGxmColorSurfaceType surfaceType;
	SceGxmColorFormat colorFormat;
	SceUInt32 width;
	SceUInt32 height;
	SceUInt32 strideInPixels;
	SceUInt8 reserved[32];
} SceCommonDialogRenderTargetInfo;

typedef struct SceCommonDialogUpdateParam {
	SceCommonDialogRenderTargetInfo renderTarget;
	SceGxmSyncObject *displaySyncObject;
	SceUInt8 reserved[32];
} SceCommonDialogUpdateParam;

typedef struct SceCommonDialogInfobarParam {
	SceInt32 visibility;
	SceInt32 color;
	SceInt32 transparency;
	SceUInt8 reserved[32];
} SceCommonDialogInfobarParam;

typedef struct SceCommonDialogColor {
	SceUInt8 r;
	SceUInt8 g;
	SceUInt8 b;
	SceUInt8 a;
} SceCommonDialogColor;

typedef SceCommonDialogColor SceCommonDialogBgColor;

typedef struct SceCommonDialogParam {
	SceCommonDialogInfobarParam* infobarParam;
	SceCommonDialogColor* bgColor;
	SceCommonDialogColor* dimmerColor;
	SceUInt8 reserved[60];
	SceUInt32 magic;
} SceCommonDialogParam;

#define SCE_COMMON_DIALOG_MAGIC_NUMBER 0xC0D1A109

static inline
void _sceCommonDialogSetMagicNumber(SceCommonDialogParam *param)
{
	param->magic = SCE_COMMON_DIALOG_MAGIC_NUMBER + *(SceUInt32*)&param;
}

static inline
void sceCommonDialogConfigParamInit(SceCommonDialogConfigParam *param)
{
	memset(param, 0x0, sizeof(SceCommonDialogConfigParam));
	param->language = SCE_SYSTEM_PARAM_LANG_MAX_VALUE;
	param->enterButtonAssign = SCE_SYSTEM_PARAM_ENTER_BUTTON_MAX_VALUE;
	param->sdkVersion = 0x03570011;
};

int sceCommonDialogSetConfigParam(const SceCommonDialogConfigParam *configParam);
int sceCommonDialogUpdate(const SceCommonDialogUpdateParam *updateParam);

#ifdef __cplusplus
}
#endif

#endif

