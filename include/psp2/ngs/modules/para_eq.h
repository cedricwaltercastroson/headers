/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_PARA_EQ_H_
#define _DOLCESDK_PSP2_NGS_MODULES_PARA_EQ_H_

#include <psp2/ngs.h>

#define SCE_NGS_PARAM_EQ_ID              (0x5CEC)

#define SCE_NGS_PARAM_EQ_STRUCT_ID       (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_PARAM_EQ_ID,1,1))
#define SCE_NGS_PARAM_EQ_COEFF_STRUCT_ID (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_PARAM_EQ_ID,2,1))

#define SCE_NGS_MAX_EQ_FILTERS           (4)

typedef struct SceNgsParamEqFilter {
	SceUInt32  eFilterMode;
	SceFloat32 fFrequency;
	SceFloat32 fResonance;
	SceFloat32 fGain;
} SceNgsParamEqFilter;

typedef struct SceNgsParamEqCoEff {
	SceFloat32 fB0;
	SceFloat32 fB1;
	SceFloat32 fB2;
	SceFloat32 fA1;
	SceFloat32 fA2;
} SceNgsParamEqCoEff;

typedef struct SceNgsParamEqParams {
	SceNgsParamsDescriptor desc;
	SceNgsParamEqFilter    filter[SCE_NGS_MAX_EQ_FILTERS];
} SceNgsParamEqParams;

typedef struct SceNgsParamEqParamsCoEff {
	SceNgsParamsDescriptor desc;
	SceNgsParamEqCoEff     filterCoEff[SCE_NGS_MAX_EQ_FILTERS];
} SceNgsParamEqParamsCoEff;

typedef struct SceNgsParamEqParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsParamEqParams     params;
} SceNgsParamEqParamsBlock;

typedef struct SceNgsParamEqCoEffParamsBlock {
	SceNgsModuleParamHeader  moduleInfo;
	SceNgsParamEqParamsCoEff params;
} SceNgsParamEqCoEffParamsBlock;

#endif
