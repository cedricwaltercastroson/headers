/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_TEMPLATES_REVERB_BUSS_VOICE_H_
#define _DOLCESDK_PSP2_NGS_TEMPLATES_REVERB_BUSS_VOICE_H_

#include <psp2/ngs.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

#define SCE_NGS_REVERB_VOICE_REVERB_MODULE (1)

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetReverbBuss(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
