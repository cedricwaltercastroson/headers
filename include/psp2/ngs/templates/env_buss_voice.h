/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_TEMPLATES_ENV_BUSS_VOICE_H_
#define _DOLCESDK_PSP2_NGS_TEMPLATES_ENV_BUSS_VOICE_H_

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

#define SCE_NGS_ENV_BUSS_ENVELOPE_MODULE (1)

struct SceNgsVoiceDefinition;

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetEnvelopeBuss(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
