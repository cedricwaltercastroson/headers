/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_MIXER_H_
#define _DOLCESDK_PSP2_NGS_MODULES_MIXER_H_

#include <psp2/ngs.h>

#define SCE_NGS_MIXER_ID               (0x5CE9)

#define SCE_NGS_MIXER_PARAMS_STRUCT_ID (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_MIXER_ID,1,1))

#define SCE_NGS_MIXER_MAX_PORTS        (2)

typedef struct SceNgsMixerParams {
	SceNgsParamsDescriptor desc;
	SceFloat32             fGainIn[SCE_NGS_MIXER_MAX_PORTS];
	SceUInt32              uPauseLeadIn;
	SceUInt32              uPauseLeadOut;
} SceNgsMixerParams;

typedef struct SceNgsMixerParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsMixerParams       params;
} SceNgsMixerParamsBlock;

#endif
