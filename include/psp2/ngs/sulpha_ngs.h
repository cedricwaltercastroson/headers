/**
 * \usergroup{SceSulpha}
 * \usage{psp2/ngs/sulpha_ngs.h,SceSulpha_stub}
 */

#ifndef _DOLCESDK_PSP2_NGS_SULPHA_NGS_H_
#define _DOLCESDK_PSP2_NGS_SULPHA_NGS_H_

#include <psp2/ngs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceSulphaNgsConfig {
	SceUInt32 maxNamedObjects;
	SceUInt32 maxTraceBufferBytes;
} SceSulphaNgsConfig;

int sceSulphaNgsGetDefaultConfig(SceSulphaNgsConfig *config);
int sceSulphaNgsGetNeededMemory(const SceSulphaNgsConfig *config, SceUInt32 *sizeInBytes);
int sceSulphaNgsInit(const SceSulphaNgsConfig *config, void *buffer, SceUInt32 sizeInBytes);
int sceSulphaNgsShutdown(void);

int sceSulphaNgsSetSynthName(SceNgsHSynSystem synthHandle, const char *name);
int sceSulphaNgsSetRackName(SceNgsHRack rackHandle, const char *name);
int sceSulphaNgsSetVoiceName(SceNgsHVoice voiceHandle, const char *name);
int sceSulphaNgsSetSampleName(const void *location, SceUInt32 length, const char *name);

int sceSulphaNgsTrace(const char *message);

#ifdef __cplusplus
}
#endif

#endif /* _DOLCESDK_PSP2_NGS_SULPHA_NGS_H_ */
