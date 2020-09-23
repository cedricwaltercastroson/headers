#ifndef _DOLCESDK_PSP2_GXM_UNIFORMS_H_
#define _DOLCESDK_PSP2_GXM_UNIFORMS_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/structs.h>
#include <psp2/gxm/program.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Writes data into a uniform buffer for a given uniform parameter from floating-point inputs.

	This function expects a contiguous array of floating point input values as
	the parameter <c><i>sourceData</i></c>.  These values are written to memory according
	to the type, component count and array size of the parameter.  The parameters
	<c><i>componentOffset</i></c> and <c><i>componentCount</i></c> control how many
	scalar components to write, and at what offset (in components) in the output
	to start writing.

	Use of this function is optional: the layout of uniform data in a uniform
	buffer is entirely defined by its declaration.  Uniform parameters generated
	by the shader compiler will always:

	<ul>
	<li>Have a component count between 1 and 4.
	<li>Have an array size of 1 or greater.
	</ul>

	Each component will be a scalar type from #SceGxmParameterType. The rules for
	uniform parameter layout in memory are as follows:

	<ul>
	<li>Floating-point vector array elements must start on a 64-bit boundary.
	<li>All other array element types must start on a 32-bit boundary.
	</ul>

	These rules are to ensure that vector instructions can always be used directly with vector data
	without intermediate copies having to be made, and to ensure that indexing is always efficient.

	For example: an array of <c>float3</c> elements (i.e. type #SCE_GXM_PARAMETER_TYPE_F32 with
	component count of 3) will have each array element aligned to 64 bits, effectively
	adding 4 bytes of padding between each array element.  However, an array of <c>float</c> elements
	(i.e. type #SCE_GXM_PARAMETER_TYPE_F32 with component count of 1) is scalar, so only
	32-bit alignment is required and the array does not contain any padding.  Similarly, an
	array of <c>char4</c> and array of <c>char</c> both consumed 4 bytes per element due
	to 32-bit alignment.

	This function is provided for convenience only, since it supports all possible
	uniform parameter types.  Data can be copied to uniform buffers by any means
	provided the alignment rules above are followed.

	@param[out]	uniformBuffer	The uniform buffer base address.
	@param[in]	parameter		A pointer to the program parameter that describes the layout.
	@param[in]	componentOffset	The destination component offset.
	@param[in]	componentCount	The number of components to write.
	@param[in]	sourceData		A pointer to the input data in float format.

	@retval
	SCE_OK		The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER 	The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE		The component offset or count were outside of the range of the parameter.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetUniformDataF(
	void *uniformBuffer,
	const SceGxmProgramParameter *parameter,
	uint32_t componentOffset,
	uint32_t componentCount,
	const float *sourceData);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_UNIFORMS_H_ */
