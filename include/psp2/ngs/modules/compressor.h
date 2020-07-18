/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_COMPRESSOR_H_
#define _DOLCESDK_PSP2_NGS_MODULES_COMPRESSOR_H_

#include <psp2/ngs.h>

#define SCE_NGS_COMPRESSOR_ID                  (0x5CE1)

#define SCE_NGS_COMPRESSOR_PARAMS_STRUCT_ID    (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_COMPRESSOR_ID,1,1))

#define SCE_NGS_COMPRESSOR_PARAMS_STRUCT_ID_V2 (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_COMPRESSOR_ID,1,2))

#define SCE_NGS_COMPRESSOR_RMS_MODE            (0)
#define SCE_NGS_COMPRESSOR_PEAK_MODE           (1)

#define SCE_NGS_COMPRESSOR_STEREO_LINK_OFF     (0)
#define SCE_NGS_COMPRESSOR_STEREO_LINK_ON      (1)

typedef struct SceNgsCompressorParams {
	SceNgsParamsDescriptor desc;
	SceFloat32 fRatio;
	SceFloat32 fThreshold;
	SceFloat32 fAttack;
	SceFloat32 fRelease;
	SceFloat32 fMakeupGain;
	SceInt32   nStereoLink;
	SceInt32   nPeakMode;
	SceFloat32 fSoftKnee;
} SceNgsCompressorParams;

typedef struct SceNgsCompressorParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsCompressorParams  params;
} SceNgsCompressorParamsBlock;

typedef struct SceNgsCompressorStates {
    SceFloat32 fInputLevel[SCE_NGS_MAX_SYSTEM_CHANNELS];
    SceFloat32 fOutputLevel[SCE_NGS_MAX_SYSTEM_CHANNELS];
} SceNgsCompressorStates;

#endif
