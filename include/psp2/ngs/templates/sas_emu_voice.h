/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_TEMPLATES_SAS_EMU_VOICE_H_
#define _DOLCESDK_PSP2_NGS_TEMPLATES_SAS_EMU_VOICE_H_

#define SCE_NGS_SAS_EMU_VOICE_PCM_PLAYER (0)
#define SCE_NGS_SAS_EMU_VOICE_ENVELOPE   (1)

#define SCE_NGS_SAS_EMU_NUM_MODULES      (2)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetSasEmuVoice(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
