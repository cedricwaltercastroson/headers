/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_ENVELOPE_H_
#define _DOLCESDK_PSP2_NGS_MODULES_ENVELOPE_H_

#include <psp2/ngs.h>

#define SCE_NGS_ENVELOPE_ID                (0x5CE3)

#define SCE_NGS_ENVELOPE_PARAMS_STRUCT_ID  ( SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_ENVELOPE_ID, 1, 1 ) )

#define SCE_NGS_ENVELOPE_MAX_POINTS        (4)
#define SCE_NGS_ENVELOPE_NO_LOOP           (-1)
#define SCE_NGS_ENVELOPE_NO_LOOP_TERMINATE (-2)
#define SCE_NGS_ENVELOPE_NO_LOOP_RELEASE   (-3)

#define SCE_NGS_ENVELOPE_LINEAR            (0)
#define SCE_NGS_ENVELOPE_CURVED            (1)

typedef struct SceNgsEnvelopePoint {
	SceUInt32  uMsecsToNextPoint;
	SceFloat32 fAmplitude;
	SceUInt32  eCurveType;
} SceNgsEnvelopePoint;

typedef struct SceNgsEnvelopeParams {
	SceNgsParamsDescriptor desc;
	SceNgsEnvelopePoint    envelopePoints[SCE_NGS_ENVELOPE_MAX_POINTS];
	SceUInt32              uReleaseMsecs;
	SceUInt32              uNumPoints;
	SceUInt32              uLoopStart;
	SceInt32               nLoopEnd;
} SceNgsEnvelopeParams;

typedef struct SceNgsEnvelopeStates {
	SceFloat32 fCurrentHeight;
	SceFloat32 fPosition;
	SceFloat32 fReleaseScale;
	SceInt32   nCurrentPoint;
	SceInt32   nReleasing;
} SceNgsEnvelopeStates;


typedef struct SceNgsEnvelopeParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsEnvelopeParams    params;
} SceNgsEnvelopeParamsBlock;

#endif
