/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_DISTORTION_H_
#define _DOLCESDK_PSP2_NGS_MODULES_DISTORTION_H_

#include <psp2/ngs.h>

#define SCE_NGS_DISTORTION_ID               (0x5CE2)

#define SCE_NGS_DISTORTION_PARAMS_STRUCT_ID (SCE_NGS_MAKE_PARAMS_ID( SCE_NGS_DISTORTION_ID, 1, 1 ))

typedef struct SceNgsDistortionParams {
	SceNgsParamsDescriptor desc;
	SceFloat32             fA;
	SceFloat32             fB;
	SceFloat32             fClip;
	SceFloat32             fGate;
	SceFloat32             fWetGain;
	SceFloat32             fDryGain;
} SceNgsDistortionParams;

typedef struct SceNgsDistortionParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsDistortionParams  params;
} SceNgsDistortionParamsBlock;

#endif
