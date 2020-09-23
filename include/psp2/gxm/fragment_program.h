#ifndef _DOLCESDK_PSP2_GXM_FRAGMENT_PROGRAM_H_
#define _DOLCESDK_PSP2_GXM_FRAGMENT_PROGRAM_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/program.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The data structure for fragment programs.

	This structure is currently opaque, filled out internally by the
	shader patcher.

	@ingroup render
*/
typedef struct SceGxmFragmentProgram SceGxmFragmentProgram;

/** Gets the underlying program for the given fragment program.

	@param[in]	fragmentProgram		A pointer to the fragment program. This must not be <c>NULL</c>.
	@return
	A pointer to the program.

	@ingroup render
*/
const SceGxmProgram *sceGxmFragmentProgramGetProgram(
	const SceGxmFragmentProgram *fragmentProgram);

/** Gets the pass type for the given fragment program.

	@param[in]	fragmentProgram		A pointer to the fragment program. This must not be <c>NULL</c>.
	@return
	The pass type of the program.

	@ingroup render
*/
SceGxmPassType sceGxmFragmentProgramGetPassType(
	const SceGxmFragmentProgram *fragmentProgram);

/** Tests whether this fragment program performs fragment shading.

	If a fragment program has no side-effects, the shader patcher will configure
	the fragment program to disable fragment shading entirely.  During rendering,
	this setting is combined with #sceGxmSetFrontFragmentProgramEnable() and
	#sceGxmSetBackFragmentProgramEnable(). This has the effect that either setting
	can disable fragment shading.

	Fragment shading is disabled by the shader patcher if the fragment program
	satisfies the following requirements:

	<ul>
	<li>The output register is not modified. This is to say the blend or mask operation has
	no effect on the output pixel either through programmable blending or blending code
	added by the shader patcher.
	<li>A discard or depth replace is not used. Fragment shading is required in order for
	the	GPU to perform a discard or depth replace.
	<li>Writeable uniform buffers are not written to.
	</ul>

	@param[in]	fragmentProgram		A pointer to the fragment program. This must not be <c>NULL</c>.
	@return
	If the fragment program performs fragment shading, true is returned; otherwise false is returned,
	which indicates fragment shading is disabled for this fragment program.

	@ingroup render
*/
bool sceGxmFragmentProgramIsEnabled(
	const SceGxmFragmentProgram *fragmentProgram);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_FRAGMENT_PROGRAM_H_ */
