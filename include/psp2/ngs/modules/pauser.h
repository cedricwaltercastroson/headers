/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_PAUSER_H_
#define _DOLCESDK_PSP2_NGS_MODULES_PAUSER_H_

#include <psp2/ngs.h>

#define SCE_NGS_PAUSER_ID               (0x5CE5)

#define SCE_NGS_PAUSER_PARAMS_STRUCT_ID (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_PAUSER_ID,1,1))

typedef struct SceNgsPauserParams {
    SceNgsParamsDescriptor desc;
    SceUInt32              uPauseLeadIn;
    SceUInt32              uPauseLeadOut;
} SceNgsPauserParams;


typedef struct SceNgsPauserParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsPauserParams      params;
} SceNgsPauserParamsBlock;

#endif
