/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_PCM_PLAYER_H_
#define _DOLCESDK_PSP2_NGS_MODULES_PCM_PLAYER_H_

#include <psp2/ngs.h>

#define SCE_NGS_PLAYER_ID                (0x5CE6)

#define SCE_NGS_PLAYER_PARAMS_STRUCT_ID  (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_PLAYER_ID,1,1))

#define SCE_NGS_PLAYER_MAX_BUFFERS       (4)

#define SCE_NGS_PLAYER_LOOP_CONTINUOUS   (-1)
#define SCE_NGS_PLAYER_NO_NEXT_BUFFER    (-1)
#define SCE_NGS_PLAYER_MAX_PCM_CHANNELS  (2)
#define SCE_NGS_PLAYER_MAX_OCTAVE_CHANGE (2)

#define SCE_NGS_PLAYER_STREAMING         (0)
#define SCE_NGS_PLAYER_RESIDENT          (1)

#define SCE_NGS_PLAYER_LEFT_CHANNEL      (0)
#define SCE_NGS_PLAYER_RIGHT_CHANNEL     (1)
#define SCE_NGS_PLAYER_NULL_CHANNEL      (-1)

#define SCE_NGS_PLAYER_TYPE_PCM          (0)
#define SCE_NGS_PLAYER_TYPE_ADPCM        (1)

#define SCE_NGS_PLAYER_END_OF_DATA       (0)
#define SCE_NGS_PLAYER_SWAPPED_BUFFER    (1)
#define SCE_NGS_PLAYER_LOOPED_BUFFER     (2)

typedef struct SceNgsPlayerBufferParams {
	const void* pBuffer;
	SceInt32 nNumBytes;
	SceInt16 nLoopCount;
	SceInt16 nNextBuff;
} SceNgsPlayerBufferParams;

typedef struct SceNgsPlayerStates {
	SceInt32 nCurrentBytePositionInBuffer;
	SceInt32 nCurrentBuffer;
	SceInt32 nSamplesGeneratedSinceKeyOn;
	SceInt32 nBytesConsumedSinceKeyOn;
	SceInt32 nSamplesGeneratedTotal;
	SceInt32 nBytesConsumedTotal;
} SceNgsPlayerStates;

typedef struct SceNgsPlayerParams {
	SceNgsParamsDescriptor   desc;
	SceNgsPlayerBufferParams buffs[SCE_NGS_PLAYER_MAX_BUFFERS];
	SceFloat32               fPlaybackFrequency;
	SceFloat32               fPlaybackScalar;
	SceInt32                 nLeadInSamples;
	SceInt32                 nLimitNumberOfSamplesPlayed;
	SceInt32                 nStartByte;
	SceInt8                  nChannels;
	SceInt8                  nChannelMap[SCE_NGS_PLAYER_MAX_PCM_CHANNELS];
	SceInt8                  nType;
	SceInt8                  reserved;
	SceInt8                  nStartBuffer;
	SceInt8                  pad[2];
} SceNgsPlayerParams;


typedef struct SceNgsPlayerParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsPlayerParams      params;
} SceNgsPlayerParamsBlock;

#endif
