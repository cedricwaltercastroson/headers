/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_NGS_MODULES_SIGNAL_GENERATOR_H_
#define _DOLCESDK_NGS_MODULES_SIGNAL_GENERATOR_H_

#include <psp2/ngs.h>

#define SCE_NGS_GENERATOR_ID               (0x5CE8)

#define SCE_NGS_GENERATOR_PARAMS_STRUCT_ID (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_GENERATOR_ID,1,1))

#define SCE_NGS_GENERATOR_DISABLE          (0)
#define SCE_NGS_GENERATOR_ENABLE           (1)

#define SCE_NGS_GENERATOR_SINE             (0)
#define SCE_NGS_GENERATOR_TRIANGLE         (1)
#define SCE_NGS_GENERATOR_SAW              (2)
#define SCE_NGS_GENERATOR_NOISE            (3)
#define SCE_NGS_GENERATOR_NOISE_PSP        (4)
#define SCE_NGS_GENERATOR_PULSE            (5)

typedef struct SceNgsGeneratorSettings {
	SceUInt32  eGeneratorMode;
	SceInt32   nFrequency;
	SceFloat32 fAmplitude;
	SceFloat32 fPulseWidth;
	SceUInt32  uSampleOffset;
	SceUInt32  uPhaseAngle;
} SceNgsGeneratorSettings;

typedef struct SceNgsGeneratorParams {
	SceNgsParamsDescriptor  desc;
	SceNgsGeneratorSettings generator;
} SceNgsGeneratorParams;

typedef struct SceNgsGeneratorParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsGeneratorParams   params;
} SceNgsGeneratorParamsBlock;

#endif
