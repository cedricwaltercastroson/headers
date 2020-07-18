/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_PITCH_SHIFT_H_
#define _DOLCESDK_PSP2_NGS_MODULES_PITCH_SHIFT_H_

#include <psp2/ngs.h>

#define SCE_NGS_PITCHSHIFT_ID               (0x5CEA)

#define SCE_NGS_PITCHSHIFT_PARAMS_STRUCT_ID (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_PITCHSHIFT_ID,1,1))

typedef struct SceNgsPitchShiftParams {
	SceNgsParamsDescriptor desc;
	SceFloat32             fPitchOffsetInCents;
} SceNgsPitchShiftParams;

typedef struct SceNgsPitchShiftParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsPitchShiftParams  params;
} SceNgsPitchShiftParamsBlock;

#endif
