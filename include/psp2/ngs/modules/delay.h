/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_DELAY_H_
#define _DOLCESDK_PSP2_NGS_MODULES_DELAY_H_

#include <psp2/ngs.h>

#define SCE_NGS_DELAY_ID                           (0x5CEB)

#define SCE_NGS_DELAY_PARAMS_STRUCT_ID             (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_DELAY_ID,1,1))

#define SCE_NGS_DELAY_MAX_TAPS                     (4)

#define SCE_NGS_DELAY_FILTER_MODE_OFF              (0)
#define SCE_NGS_DELAY_FILTER_MODE_LOWPASS_ONEPOLE  (1)
#define SCE_NGS_DELAY_FILTER_MODE_HIGHPASS_ONEPOLE (2)
#define SCE_NGS_DELAY_FILTER_MODE_ALLPASS          (3)

typedef struct SceNgsDelayTap {
    SceFloat32 fDelayMillisecs;
    SceFloat32 fVolume;
    SceFloat32 fFeedback;
    SceUInt32  eFilterMode;
    SceFloat32 fCutoff;
    SceFloat32 fPhaseOffsetDeg;
    SceFloat32 fModWidthMillisecs;
} SceNgsDelayTap;

typedef struct SceNgsDelayParams {
    SceNgsParamsDescriptor desc;
    SceFloat32             fDryVol;
    SceFloat32             fModRate;
    SceNgsDelayTap         taps[SCE_NGS_DELAY_MAX_TAPS];
} SceNgsDelayParams;


typedef struct SceNgsDelayParamsBlock {
    SceNgsModuleParamHeader moduleInfo;
    SceNgsDelayParams       params;
} SceNgsDelayParamsBlock;

#define SCE_NGS_DELAY_PRESET_DEFAULT              (0)
#define SCE_NGS_DELAY_PRESET_MONO_CHORUS          (1)
#define SCE_NGS_DELAY_PRESET_STEREO_CHORUS_LEFT   (2)
#define SCE_NGS_DELAY_PRESET_STEREO_CHORUS_RIGHT  (3)
#define SCE_NGS_DELAY_PRESET_MONO_FLANGER         (4)
#define SCE_NGS_DELAY_PRESET_STEREO_FLANGER_LEFT  (4)
#define SCE_NGS_DELAY_PRESET_STEREO_FLANGER_RIGHT (5)

#endif
