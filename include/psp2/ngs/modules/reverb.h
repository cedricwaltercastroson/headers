/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_REVERB_H_
#define _DOLCESDK_PSP2_NGS_MODULES_REVERB_H_

#include <psp2/ngs.h>

#define SCE_NGS_REVERB_ID                  (0x5CE7)

#define SCE_NGS_REVERB_PARAMS_STRUCT_ID    (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_REVERB_ID,1,1))

#define SCE_NGS_REVERB_PARAMS_STRUCT_ID_V2 (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_REVERB_ID,1,2))

#define SCE_NGS_REVERB_ROOM1_LEFT          0
#define SCE_NGS_REVERB_ROOM1_RIGHT         1
#define SCE_NGS_REVERB_ROOM2_LEFT          2
#define SCE_NGS_REVERB_ROOM2_RIGHT         3
#define SCE_NGS_REVERB_ROOM3_LEFT          4
#define SCE_NGS_REVERB_ROOM3_RIGHT         5

typedef struct SceNgsReverbParams {
	SceNgsParamsDescriptor desc;
	SceFloat32             fRoom;
	SceFloat32             fRoomHF;
	SceFloat32             fDecayTime;
	SceFloat32             fDecayHFRatio;
	SceFloat32             fReflections;
	SceFloat32             fReflectionsDelay;
	SceFloat32             fReverb;
	SceFloat32             fReverbDelay;
	SceFloat32             fDiffusion;
	SceFloat32             fDensity;
	SceFloat32             fHFReference;
	SceInt32               eEarlyReflectionPattern[SCE_NGS_MAX_SYSTEM_CHANNELS];
	SceFloat32             fEarlyReflectionScalar;
	SceFloat32             fLFReference;
	SceFloat32             fRoomLF;
	SceFloat32             fDryMB;
} SceNgsReverbParams;

typedef struct SceNgsReverbParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsReverbParams      params;
} SceNgsReverbParamsBlock;

#define SCE_NGS_REVERB_PRESET_DEFAULT          (0)
#define SCE_NGS_REVERB_PRESET_GENERIC          (1)
#define SCE_NGS_REVERB_PRESET_PADDED_CELL      (2)
#define SCE_NGS_REVERB_PRESET_ROOM             (3)
#define SCE_NGS_REVERB_PRESET_BATHROOM         (4)
#define SCE_NGS_REVERB_PRESET_LIVING_ROOM      (5)
#define SCE_NGS_REVERB_PRESET_STONE_ROOM       (6)
#define SCE_NGS_REVERB_PRESET_AUDITORIUM       (7)
#define SCE_NGS_REVERB_PRESET_CONCERT_HALL     (8)
#define SCE_NGS_REVERB_PRESET_CAVE             (9)
#define SCE_NGS_REVERB_PRESET_ARENA            (10)
#define SCE_NGS_REVERB_PRESET_HANGAR           (11)
#define SCE_NGS_REVERB_PRESET_CARPETED_HALLWAY (12)
#define SCE_NGS_REVERB_PRESET_HALLWAY          (13)
#define SCE_NGS_REVERB_PRESET_STONE_CORRIDOR   (14)
#define SCE_NGS_REVERB_PRESET_ALLEY            (15)
#define SCE_NGS_REVERB_PRESET_FOREST           (16)
#define SCE_NGS_REVERB_PRESET_CITY             (17)
#define SCE_NGS_REVERB_PRESET_MOUNTAINS        (18)
#define SCE_NGS_REVERB_PRESET_QUARRY           (19)
#define SCE_NGS_REVERB_PRESET_PLAIN            (20)
#define SCE_NGS_REVERB_PRESET_PARKING_LOT      (21)
#define SCE_NGS_REVERB_PRESET_SEWER_PIPE       (22)
#define SCE_NGS_REVERB_PRESET_UNDERWATER       (23)

#define SCE_NGS_REVERB_PRESET_SMALL_ROOM       (24)
#define SCE_NGS_REVERB_PRESET_MEDIUM_ROOM      (25)
#define SCE_NGS_REVERB_PRESET_LARGE_ROOM       (26)
#define SCE_NGS_REVERB_PRESET_MEDIUM_HALL      (27)
#define SCE_NGS_REVERB_PRESET_LARGE_HALL       (28)
#define SCE_NGS_REVERB_PRESET_PLATE            (29)

#endif
