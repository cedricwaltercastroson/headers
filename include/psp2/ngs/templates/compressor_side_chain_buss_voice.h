/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_TEMPLATES_COMPRESSOR_SIDE_CHAIN_BUSS_VOICE_H_
#define _DOLCESDK_PSP2_NGS_TEMPLATES_COMPRESSOR_SIDE_CHAIN_BUSS_VOICE_H_

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

#define SCE_NGS_COMPRESSOR_SIDE_CHAIN_VOICE_INPUT_0_MODULE    (0)
#define SCE_NGS_COMPRESSOR_SIDE_CHAIN_VOICE_INPUT_1_MODULE    (1)
#define SCE_NGS_COMPRESSOR_SIDE_CHAIN_VOICE_COMPRESSOR_MODULE (2)

const struct SceNgsVoiceDefinition* sceNgsVoiceDefGetCompressorSideChainBuss(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
