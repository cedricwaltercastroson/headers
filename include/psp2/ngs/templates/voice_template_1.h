/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_TEMPLATES_VOICE_TEMPLATE_1_H_
#define _DOLCESDK_PSP2_NGS_TEMPLATES_VOICE_TEMPLATE_1_H_

#define SCE_NGS_VOICE_T1_PCM_PLAYER       (0)
#define SCE_NGS_VOICE_T1_SIGNAL_GENERATOR (1)
#define SCE_NGS_VOICE_T1_MIXER            (2)
#define SCE_NGS_VOICE_T1_EQ               (3)
#define SCE_NGS_VOICE_T1_ENVELOPE         (4)
#define SCE_NGS_VOICE_T1_DISTORTION       (5)
#define SCE_NGS_VOICE_T1_SEND_1_EQ        (6)
#define SCE_NGS_VOICE_T1_SEND_2_EQ        (7)
#define SCE_NGS_VOICE_T1_SEND_3_EQ        (8)
#define SCE_NGS_VOICE_T1_SEND_4_EQ        (9)

#define SCE_NGS_VOICE_T1_NUM_MODULES      (10)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetTemplate1(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
