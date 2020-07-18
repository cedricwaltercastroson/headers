/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_MODULES_AT9_PLAYER_H_
#define _DOLCESDK_PSP2_NGS_MODULES_AT9_PLAYER_H_

#include <psp2/ngs.h>

#define SCE_NGS_AT9_ID                (0x5CAA)

#define SCE_NGS_AT9_PARAMS_STRUCT_ID  (SCE_NGS_MAKE_PARAMS_ID(SCE_NGS_AT9_ID,1,1))

#define SCE_NGS_AT9_MAX_BUFFERS       (4)

#define SCE_NGS_AT9_LOOP_CONTINUOUS   (-1)
#define SCE_NGS_AT9_NO_NEXT_BUFFER    (-1)
#define SCE_NGS_AT9_MAX_PCM_CHANNELS  (2)
#define SCE_NGS_AT9_MAX_OCTAVE_CHANGE (2)

#define SCE_NGS_AT9_LEFT_CHANNEL      (0)
#define SCE_NGS_AT9_RIGHT_CHANNEL     (1)
#define SCE_NGS_AT9_NULL_CHANNEL      (-1)

#define SCE_NGS_AT9_END_OF_DATA       (0)
#define SCE_NGS_AT9_SWAPPED_BUFFER    (1)
#define SCE_NGS_AT9_HEADER_ERROR      (2)
#define SCE_NGS_AT9_DECODE_ERROR      (3)
#define SCE_NGS_AT9_LOOPED_BUFFER     (4)

typedef struct SceNgsAT9BufferParams {
	const void* pBuffer;
	SceInt32 nNumBytes;
	SceInt16 nLoopCount;
	SceInt16 nNextBuff;
	SceInt16 nSamplesDiscardStart;
	SceInt16 nSamplesDiscardEnd;
} SceNgsAT9BufferParams;

typedef struct SceNgsAT9States {
	SceInt32 nCurrentBytePositionInBuffer;
	SceInt32 nCurrentBuffer;
	SceInt32 nSamplesGeneratedSinceKeyOn;
	SceInt32 nBytesConsumedSinceKeyOn;
	SceInt32 nSamplesGeneratedTotal;
	SceInt32 nBytesConsumedTotal;
} SceNgsAT9States;

typedef struct SceNgsAT9Params {
	SceNgsParamsDescriptor desc;
	SceNgsAT9BufferParams  buffs[SCE_NGS_AT9_MAX_BUFFERS];
	SceFloat32             fPlaybackFrequency;
	SceFloat32             fPlaybackScalar;
	SceInt32               nLeadInSamples;
	SceInt32               nLimitNumberOfSamplesPlayed;
	SceInt8                nChannels;
	SceInt8                nChannelMap[SCE_NGS_AT9_MAX_PCM_CHANNELS];
	SceInt8                reserved;
	SceInt32               configData;
} SceNgsAT9Params;

typedef struct SceNgsAT9ParamsBlock {
	SceNgsModuleParamHeader moduleInfo;
	SceNgsAT9Params         params;
} SceNgsAT9ParamsBlock;

#endif
