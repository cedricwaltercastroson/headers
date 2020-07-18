/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_FILTER_H_
#define _DOLCESDK_PSP2_NGS_MODULES_FILTER_H_

#include <psp2/ngs.h>

#define SCE_NGS_FILTER_ID                          (0x5CE4)

#define SCE_NGS_FILTER_PARAMS_STRUCT_ID            (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_FILTER_ID,1,1))
#define SCE_NGS_FILTER_PARAMS_COEFF_STRUCT_ID      (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_FILTER_ID,2,1))

#define SCE_NGS_FILTER_MODE_OFF                    (0)
#define SCE_NGS_FILTER_LOWPASS_RESONANT            (1)
#define SCE_NGS_FILTER_HIGHPASS_RESONANT           (2)
#define SCE_NGS_FILTER_BANDPASS_PEAK               (3)
#define SCE_NGS_FILTER_BANDPASS_ZERO               (4)
#define SCE_NGS_FILTER_NOTCH                       (5)
#define SCE_NGS_FILTER_PEAK                        (6)
#define SCE_NGS_FILTER_HIGHSHELF                   (7)
#define SCE_NGS_FILTER_LOWSHELF                    (8)
#define SCE_NGS_FILTER_LOWPASS_ONEPOLE             (9)
#define SCE_NGS_FILTER_HIGHPASS_ONEPOLE            (10)
#define SCE_NGS_FILTER_ALLPASS                     (11)
#define SCE_NGS_FILTER_LOWPASS_RESONANT_NORMALIZED (12)

typedef struct SceNgsFilterParams {
	SceNgsParamsDescriptor desc;
	SceUInt32              eFilterMode;
	SceFloat32             fFrequency;
	SceFloat32             fResonance;
	SceFloat32             fGain;
} SceNgsFilterParams;

typedef struct SceNgsFilterParamsCoEff {
	SceNgsParamsDescriptor desc;
	SceFloat32             fB0;
	SceFloat32             fB1;
	SceFloat32             fB2;
	SceFloat32             fA1;
	SceFloat32             fA2;
} SceNgsFilterParamsCoEff;

typedef struct SceNgsFilterParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsFilterParams      params;
} SceNgsFilterParamsBlock;

typedef struct SceNgsFilterCoEffParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsFilterParamsCoEff params;
} SceNgsFilterCoEffParamsBlock;

#endif
