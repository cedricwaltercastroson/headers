/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_TEMPLATES_SIMPLE_VOICE_AT9_H_
#define _DOLCESDK_PSP2_NGS_TEMPLATES_SIMPLE_VOICE_AT9_H_

#define SCE_NGS_SIMPLE_VOICE_AT9_PLAYER        (0)
#define SCE_NGS_SIMPLE_VOICE_AT9_EQ            (1)
#define SCE_NGS_SIMPLE_VOICE_AT9_ENVELOPE      (2)
#define SCE_NGS_SIMPLE_VOICE_AT9_PAUSER        (3)
#define SCE_NGS_SIMPLE_VOICE_AT9_SEND_1_FILTER (4)
#define SCE_NGS_SIMPLE_VOICE_AT9_SEND_2_FILTER (5)

#define SCE_NGS_SIMPLE_VOICE_AT9_NUM_MODULES   (6)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleAtrac9Voice(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
