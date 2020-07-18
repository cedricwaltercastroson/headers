/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_TEMPLATES_VOICE_TEMPLATE_AT9_H_
#define _DOLCESDK_PSP2_NGS_TEMPLATES_VOICE_TEMPLATE_AT9_H_

#define SCE_NGS_VOICE_AT9_PLAYER           (0)
#define SCE_NGS_VOICE_AT9_SIGNAL_GENERATOR (1)
#define SCE_NGS_VOICE_AT9_MIXER            (2)
#define SCE_NGS_VOICE_AT9_EQ               (3)
#define SCE_NGS_VOICE_AT9_ENVELOPE         (4)
#define SCE_NGS_VOICE_AT9_DISTORTION       (5)
#define SCE_NGS_VOICE_AT9_SEND_1_EQ        (6)
#define SCE_NGS_VOICE_AT9_SEND_2_EQ        (7)
#define SCE_NGS_VOICE_AT9_SEND_3_EQ        (8)
#define SCE_NGS_VOICE_AT9_SEND_4_EQ        (9)

#define SCE_NGS_VOICE_AT9_NUM_MODULES      (10)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetAtrac9Voice(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
