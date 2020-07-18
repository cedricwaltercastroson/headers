/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgs_stub,SCE_SYSMODULE_NGS}
 */

#ifndef _DOLCESDK_PSP2_NGS_H_
#define _DOLCESDK_PSP2_NGS_H_

#include <psp2/ngs/ngs_top.h>

/* error codes */
#include <psp2/ngs/error.h>

/* modules */
#include <psp2/ngs/modules/at9_player.h>
#include <psp2/ngs/modules/compressor.h>
#include <psp2/ngs/modules/distortion.h>
#include <psp2/ngs/modules/envelope.h>
#include <psp2/ngs/modules/filter.h>
#include <psp2/ngs/modules/input_mixer.h>
#include <psp2/ngs/modules/mixer.h>
#include <psp2/ngs/modules/output.h>
#include <psp2/ngs/modules/para_eq.h>
#include <psp2/ngs/modules/pauser.h>
#include <psp2/ngs/modules/pcm_player.h>
#include <psp2/ngs/modules/reverb.h>
#include <psp2/ngs/modules/signal_generator.h>
#include <psp2/ngs/modules/delay.h>
#include <psp2/ngs/modules/pitch_shift.h>

/* voice templates */
#include <psp2/ngs/templates/compressor_buss_voice.h>
#include <psp2/ngs/templates/compressor_side_chain_buss_voice.h>
#include <psp2/ngs/templates/delay_buss_voice.h>
#include <psp2/ngs/templates/distortion_buss_voice.h>
#include <psp2/ngs/templates/env_buss_voice.h>
#include <psp2/ngs/templates/eq_buss_voice.h>
#include <psp2/ngs/templates/master_buss_voice.h>
#include <psp2/ngs/templates/mixer_buss_voice.h>
#include <psp2/ngs/templates/pauser_buss_voice.h>
#include <psp2/ngs/templates/reverb_buss_voice.h>
#include <psp2/ngs/templates/sas_emu_voice.h>
#include <psp2/ngs/templates/simple_voice.h>
#include <psp2/ngs/templates/voice_template_1.h>
#include <psp2/ngs/templates/voice_template_at9.h>
#include <psp2/ngs/templates/simple_voice_at9.h>
#include <psp2/ngs/templates/pitchshift_buss_voice.h>

#endif /* _DOLCESDK_PSP2_NGS_H_ */
