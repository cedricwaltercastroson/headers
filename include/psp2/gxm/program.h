#ifndef _DOLCESDK_PSP2_GXM_PROGRAM_H_
#define _DOLCESDK_PSP2_GXM_PROGRAM_H_

/** @file
*/

#include <psp2/gxm/types.h>
#include <psp2/gxm/structs.h>
#include <psp2/gxm/error.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The maximum number of (vector) vertex attributes supported by Cg and the libgxm API.

	@ingroup shader
*/
#define SCE_GXM_MAX_VERTEX_ATTRIBUTES				16U

/** The maximum number of independent vertex stream addresses supported by Cg and the libgxm API.

	@ingroup shader
*/
#define SCE_GXM_MAX_VERTEX_STREAMS					16U

/** The maximum number of texture units supported by Cg and the libgxm API.

	@ingroup shader
*/
#define SCE_GXM_MAX_TEXTURE_UNITS					16U

/** The maximum number of uniform buffers supported by Cg and the libgxm API.

	@ingroup shader
*/
#define SCE_GXM_MAX_UNIFORM_BUFFERS					14U

/** The opaque data type for the Cg compiler output.

	@ingroup shader
*/
typedef struct SceGxmProgram SceGxmProgram;

/** The opaque data type for the parameter of a program.

	@ingroup shader
*/
typedef struct SceGxmProgramParameter SceGxmProgramParameter;

/** The type of program.

	@ingroup shader
*/
typedef enum SceGxmProgramType {
	SCE_GXM_VERTEX_PROGRAM,		///< The shader is a vertex program.
	SCE_GXM_FRAGMENT_PROGRAM	///< The shader is a fragment program.
} SceGxmProgramType;

/** The category of shader program parameter.

	@ingroup shader
*/
typedef enum SceGxmParameterCategory {
	SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE		= 0,	///< The parameter is a vertex attribute.
	SCE_GXM_PARAMETER_CATEGORY_UNIFORM			= 1,	///< The parameter is a uniform.
	SCE_GXM_PARAMETER_CATEGORY_SAMPLER 			= 2,	///< The parameter is a sampler.
	SCE_GXM_PARAMETER_CATEGORY_UNIFORM_BUFFER	= 4		///< The parameter is a uniform buffer.
} SceGxmParameterCategory;

/** The data type of program parameters.

	For uniform parameters, this is the data type that uniform data should
	be stored as in the buffer. For sampler parameters, this is the result type
	of the texture data that is expected by the shader code.

	@ingroup shader
*/
typedef enum SceGxmParameterType {
	SCE_GXM_PARAMETER_TYPE_F32,			///< 32-bit floating point, equivalent to the Cg type “float”.
	SCE_GXM_PARAMETER_TYPE_F16,			///< 16-bit floating point, equivalent to the Cg type “half”.
	SCE_GXM_PARAMETER_TYPE_C10,			///< 10-bit fixed point, equivalent to the Cg type “fixed”.
	SCE_GXM_PARAMETER_TYPE_U32,			///< 32-bit unsigned integer.
	SCE_GXM_PARAMETER_TYPE_S32,			///< 32-bit signed integer.
	SCE_GXM_PARAMETER_TYPE_U16,			///< 16-bit unsigned integer.
	SCE_GXM_PARAMETER_TYPE_S16,			///< 16-bit signed integer.
	SCE_GXM_PARAMETER_TYPE_U8,			///< 8-bit unsigned integer.
	SCE_GXM_PARAMETER_TYPE_S8,			///< 8-bit signed integer.
	SCE_GXM_PARAMETER_TYPE_AGGREGATE	///< Aggregate type (used for uniform buffers).
} SceGxmParameterType;

/**	The semantic associated with a program parameter.

	For vertex attribute parameters, this is the semantic that was associated with
	the declaration. Semantics serve as an alternative to name based lookups and allow
	for parameters being described in terms of their function rather than their
	name.  Each semantic is indexed with an index value between and 0 and 15.

	Semantics are not used for parameters that are not vertex attributes; non-
	attribute parameters will always report #SCE_GXM_PARAMETER_SEMANTIC_NONE.

	@ingroup shader
*/
typedef enum SceGxmParameterSemantic {
	SCE_GXM_PARAMETER_SEMANTIC_NONE,			///< The parameter has no semantic.
	SCE_GXM_PARAMETER_SEMANTIC_ATTR,			///< The parameter has an ATTR semantic.
	SCE_GXM_PARAMETER_SEMANTIC_BCOL,			///< The parameter has a BCOL semantic.
	SCE_GXM_PARAMETER_SEMANTIC_BINORMAL,		///< The parameter has a BINORMAL semantic.
	SCE_GXM_PARAMETER_SEMANTIC_BLENDINDICES,	///< The parameter has a BLENDINDICES semantic.
	SCE_GXM_PARAMETER_SEMANTIC_BLENDWEIGHT,		///< The parameter has a BLENDWEIGHT semantic.
	SCE_GXM_PARAMETER_SEMANTIC_COLOR,			///< The parameter has a COLOR semantic.
	SCE_GXM_PARAMETER_SEMANTIC_DIFFUSE,			///< The parameter has a DIFFUSE semantic.
	SCE_GXM_PARAMETER_SEMANTIC_FOGCOORD,		///< The parameter has a FOGCOORD semantic.
	SCE_GXM_PARAMETER_SEMANTIC_NORMAL,			///< The parameter has a NORMAL semantic.
	SCE_GXM_PARAMETER_SEMANTIC_POINTSIZE,		///< The parameter has a POINTSIZE semantic.
	SCE_GXM_PARAMETER_SEMANTIC_POSITION,		///< The parameter has a POSITION semantic.
	SCE_GXM_PARAMETER_SEMANTIC_SPECULAR,		///< The parameter has a SPECULAR semantic.
	SCE_GXM_PARAMETER_SEMANTIC_TANGENT,			///< The parameter has a TANGENT semantic.
	SCE_GXM_PARAMETER_SEMANTIC_TEXCOORD			///< The parameter has a TEXCOORD semantic.
} SceGxmParameterSemantic;

/** All possible vertex program outputs.

	The outputs written by a vertex program can be found by testing the result
	of #sceGxmProgramGetVertexProgramOutputs against the values of this enumeration.
	If the bit is set, then the vertex program writes the output.

	@ingroup shader
*/
typedef enum SceGxmVertexProgramOutput {
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_POSITION		= (1U << 0),	///< Position.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_FOG			= (1U << 1),	///< Fog coordinate.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_COLOR0		= (1U << 2),	///< Color 0.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_COLOR1		= (1U << 3),	///< Color 1.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD0		= (1U << 4),	///< Texture coordinate 0.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD1		= (1U << 5),	///< Texture coordinate 1.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD2		= (1U << 6),	///< Texture coordinate 2.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD3		= (1U << 7),	///< Texture coordinate 3.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD4		= (1U << 8),	///< Texture coordinate 4.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD5		= (1U << 9),	///< Texture coordinate 5.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD6		= (1U << 10),	///< Texture coordinate 6.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD7		= (1U << 11),	///< Texture coordinate 7.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD8		= (1U << 12),	///< Texture coordinate 8.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_TEXCOORD9		= (1U << 13),	///< Texture coordinate 9.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_PSIZE			= (1U << 14),	///< Point size.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP0			= (1U << 15),	///< Clip plane 0.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP1			= (1U << 16),	///< Clip plane 1.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP2			= (1U << 17),	///< Clip plane 2.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP3			= (1U << 18),	///< Clip plane 3.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP4			= (1U << 19),	///< Clip plane 4.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP5			= (1U << 20),	///< Clip plane 5.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP6			= (1U << 21),	///< Clip plane 6.
	SCE_GXM_VERTEX_PROGRAM_OUTPUT_CLIP7			= (1U << 22)	///< Clip plane 7.
} SceGxmVertexProgramOutput;

/** All possible fragment program inputs.

	The inputs read by a fragment program can be found by testing the result
	of #sceGxmProgramGetFragmentProgramInputs against the values of this enumeration.
	If the bit is set, then the fragment program reads the input.

	@ingroup shader
*/
typedef enum SceGxmFragmentProgramInput {
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_WPOS			= (1U << 0),	///< Position.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_FOG			= (1U << 1),	///< Fog coordinate.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_COLOR0		= (1U << 2),	///< Color 0.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_COLOR1		= (1U << 3),	///< Color 1.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD0	= (1U << 4),	///< Texture coordinate 0.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD1	= (1U << 5),	///< Texture coordinate 1.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD2	= (1U << 6),	///< Texture coordinate 2.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD3	= (1U << 7),	///< Texture coordinate 3.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD4	= (1U << 8),	///< Texture coordinate 4.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD5	= (1U << 9),	///< Texture coordinate 5.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD6	= (1U << 10),	///< Texture coordinate 6.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD7	= (1U << 11),	///< Texture coordinate 7.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD8	= (1U << 12),	///< Texture coordinate 8.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_TEXCOORD9	= (1U << 13),	///< Texture coordinate 9.
	SCE_GXM_FRAGMENT_PROGRAM_INPUT_SPRITECOORD	= (1U << 14)	///< Sprite coordinate.
} SceGxmFragmentProgramInput;

/** Returns SCE_OK if the given pointer looks like the compiler output.

	@param[in]	program			A pointer to the program.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the header magic number was invalid
	or the version numbers are not compatible.

	@ingroup shader
*/
SCE_GXM_INTERFACE
SceGxmErrorCode sceGxmProgramCheck(
	const SceGxmProgram *program);

/** Checks if the compiler output for two shaders is equivalent.

	This function ignores shader association data used by Razor to disambiguate between
	shaders that produces identical shader compiler output.

	@param[in]	programA		A pointer to the first program. This must not be <c>NULL</c>.
	@param[in]	programB		A pointer to the second program. This must not be <c>NULL</c>.

	@return
	Returns <c>true</c> if <c>programA</c> and <c>programB</c> are equivalent; otherwise <c>false</c> is returned.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramIsEquivalent(
	const SceGxmProgram *programA,
	const SceGxmProgram *programB);

/** Gets the total size of the compiler output.

	@param[in]	program			A pointer to the program. This must not be <c>NULL</c>.
	@return
	The size of the program in bytes.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramGetSize(
	const SceGxmProgram *program);

/** Gets the pipeline that the program is expected to run on.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	The type of program.

	@ingroup shader
*/
SCE_GXM_INTERFACE
SceGxmProgramType sceGxmProgramGetType(
	const SceGxmProgram *program);

/** Checks whether the fragment program uses discard.  This function
	always returns false for vertex programs.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	True only if the fragment program uses discard, false otherwise.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramIsDiscardUsed(
	const SceGxmProgram *program);

/** Checks whether the fragment program replaces the depth value.  This function
	always returns false for vertex programs.

	A fragment program uses depth replace if it writes to an output variable
	with the DEPTH semantic.  This output depth value replaces the interpolated
	depth value over the primitive.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	True only if the fragment program uses depth replace, false otherwise.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramIsDepthReplaceUsed(
	const SceGxmProgram *program);

/** Checks whether the fragment program uses the SPRITECOORD semantic.  This
	function always returns false for vertex programs.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	True only if the fragment program uses SPRITECOORD, false otherwise.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramIsSpriteCoordUsed(
	const SceGxmProgram *program);

/** Checks whether the fragment program uses __nativecolor.  This
	function always returns false for vertex programs.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	If the fragment program uses __nativecolor, true is returned; otherwise the function returns false.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramIsNativeColorUsed(
	const SceGxmProgram *program);

/** Checks whether the fragment program uses the FRAGCOLOR semantic.  This
	function always returns false for vertex programs.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	If the fragment program uses FRAGCOLOR, true is returned; otherwise the function returns false.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramIsFragColorUsed(
	const SceGxmProgram *program);

/** Returns the type and component count for a fragment program’s output.

	@param[in]	program			A pointer to the program.
	@param[out]	type			Storage for the output type.
	@param[out]	componentCount	Storage for the output component count.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to an invalid input pointer.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the supplied program was
	not a fragment program.

	@ingroup shader
*/
SCE_GXM_INTERFACE
SceGxmErrorCode sceGxmProgramGetOutputRegisterFormat(
	const SceGxmProgram *program,
	SceGxmParameterType *type,
	uint32_t *componentCount);

/** Gets the set of vertex program outputs in use by the given program.

	The return value is formed by combining values of the
	#SceGxmVertexProgramOutput enumeration using bitwise OR.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	The set of vertex program outputs. 0 is returned if the program is not
	a vertex program.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramGetVertexProgramOutputs(
	const SceGxmProgram *program);

/** Gets the set of fragment program inputs in use by the given program.

	The return value is formed by combining values of the
	#SceGxmFragmentProgramInput enumeration using bitwise OR.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	The set of fragment program inputs. 0 is returned if the program is not
	a fragment program.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramGetFragmentProgramInputs(
	const SceGxmProgram *program);

/** Gets the size of the default uniform buffer for the given program.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	The size of the default uniform buffer in bytes.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramGetDefaultUniformBufferSize(
	const SceGxmProgram *program);

/** Gets the number of parameters exposed by the given program.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@return
	The number of parameters exposed.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramGetParameterCount(
	const SceGxmProgram *program);

/** Gets a parameter exposed by the given program by index.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@param[in]	index		The index in the parameter array.
	@return
	A pointer to the parameter or <c>NULL</c> if the index is out of bounds.

	@ingroup shader
*/
SCE_GXM_INTERFACE
const SceGxmProgramParameter *sceGxmProgramGetParameter(
	const SceGxmProgram *program,
	uint32_t index);

/** Finds a parameter by matching the given name.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@param[in]	name		The name of the parameter to search for.
	@return
	A pointer to the parameter or <c>NULL</c> if it was not found.

	@ingroup shader
*/
SCE_GXM_INTERFACE
const SceGxmProgramParameter *sceGxmProgramFindParameterByName(
	const SceGxmProgram *program,
	const char *name);

/** Finds a vertex attribute parameter by matching the semantic and
	index.  This function will only ever match vertex attributes
	because other categories of parameter do not have semantics.

	@note
	Passing the #SCE_GXM_PARAMETER_SEMANTIC_NONE semantic will not
	match any parameters.

	@param[in]	program		A pointer to the program. This must not be <c>NULL</c>.
	@param[in]	semantic	The semantic to search for.
	@param[in]	index		The index within this semantic to match.
	@return
	A pointer to the parameter or <c>NULL</c> if it was not found.

	@ingroup shader
*/
SCE_GXM_INTERFACE
const SceGxmProgramParameter *sceGxmProgramFindParameterBySemantic(
	const SceGxmProgram *program,
	SceGxmParameterSemantic semantic,
	uint32_t index);

/** Gets the index of the given parameter within the program.  This
	index will always be greater than or equal to 0 and less than the
	value returned by #sceGxmProgramGetParameterCount().

	@param[in]	program		A pointer to the parent program. This must not be <c>NULL</c>.
	@param[in]	parameter	A pointer to the program parameter. This must not be <c>NULL</c>.
	@return
	The index of the parameter within the program.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramParameterGetIndex(
	const SceGxmProgram *program,
	const SceGxmProgramParameter *parameter);

/** Gets the type of category of a given parameter.

	@param[in]	parameter	A pointer to the program parameter. This must not be <c>NULL</c>.
	@return
	The type of category of the parameter.

	@ingroup shader
*/
SCE_GXM_INTERFACE
SceGxmParameterCategory sceGxmProgramParameterGetCategory(
	const SceGxmProgramParameter *parameter);

/** Gets the name of the given parameter.

	@param[in]	parameter	A pointer to the program parameter. This must not be <c>NULL</c>.
	@return
	The name of the parameter.

	@ingroup shader
*/
SCE_GXM_INTERFACE
const char *sceGxmProgramParameterGetName(
	const SceGxmProgramParameter *parameter);

/** Gets the semantic of the given parameter.

	@param[in]	parameter	A pointer to the program parameter. This must not be <c>NULL</c>.
	@return
	The name of the parameter.

	@ingroup shader
*/
SCE_GXM_INTERFACE
SceGxmParameterSemantic sceGxmProgramParameterGetSemantic(
	const SceGxmProgramParameter *parameter);

/** Gets the semantic index of the given parameter.

	@param[in]	parameter	A pointer to the program parameter. This must not be <c>NULL</c>.
	@return
	The semantic index of the parameter.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramParameterGetSemanticIndex(
	const SceGxmProgramParameter *parameter);

/** Gets the scalar data type of the given parameter.

	@param[in]	parameter	The pointer to a program parameter. This must not be <c>NULL</c>.
	@return
	The type of the parameter.

	@ingroup shader
*/
SCE_GXM_INTERFACE
SceGxmParameterType sceGxmProgramParameterGetType(
	const SceGxmProgramParameter *parameter);

/** Gets the number of scalar components per array element.  This will always
	be a value between 1 and 4.

	@param[in]	parameter	A pointer to a program parameter. This must not be <c>NULL</c>.
	@return
	The component count of the parameter.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramParameterGetComponentCount(
	const SceGxmProgramParameter *parameter);

/** Gets the number of elements in the array.

	@param[in]	parameter	A pointer to a program parameter. This must not be <c>NULL</c>.
	@return
	The size of the element array.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramParameterGetArraySize(
	const SceGxmProgramParameter *parameter);

/** Gets the resource index of the given parameter.

	Resources index values are used as follows:

	<ul>
	<li>Attributes: register index
	<li>Uniforms: word (32-bit) offset from start of buffer
	<li>Samplers: texture unit index
	<li>Uniform buffers: uniform buffer index
	</ul>

	@param[in]	parameter	A pointer to a program parameter. This must not be <c>NULL</c>.
	@return
	The resource index of the given parameter.

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramParameterGetResourceIndex(
	const SceGxmProgramParameter *parameter);

/** Gets the container index of the given parameter.

	Container index values are used as follows:

	<ul>
	<li>Attributes: unused
	<li>Uniforms: uniform buffer index
	<li>Samplers: unused
	<li>Uniform buffers: unused
	</ul>

	When the parameter is a member of the default uniform buffer,
	the container index will have a value of #SCE_GXM_MAX_UNIFORM_BUFFERS.

	@param[in]	parameter	A pointer to a program parameter. This must not be <c>NULL</c>.
	@return
	The container index of the given parameter

	@ingroup shader
*/
SCE_GXM_INTERFACE
uint32_t sceGxmProgramParameterGetContainerIndex(
	const SceGxmProgramParameter *parameter);

/** For parameters of category #SCE_GXM_PARAMETER_CATEGORY_SAMPLER, this
	function returns true if the given parameter is a cube map sampler.
	For parameters that are not of category #SCE_GXM_PARAMETER_CATEGORY_SAMPLER,
	this function always returns false.

	@param[in]	parameter	A pointer to a program parameter. This must not be <c>NULL</c>.
	@return
	True only if the parameter is a cube map sampler, false otherwise.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramParameterIsSamplerCube(
	const SceGxmProgramParameter *parameter);

/** For parameters of category #SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE, this
	function returns true if the given parameter has a <c>__regformat</c> qualifier.
	For parameters that are not of category #SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE,
	this function always returns false.

	@param[in]	program		A pointer to the parent program. This must not be <c>NULL</c>.
	@param[in]	parameter	A pointer to a program parameter. This must not be <c>NULL</c>.
	@return
	True only if the parameter is an attribute with a <c>__regformat</c> qualifier, false otherwise.

	@ingroup shader
*/
SCE_GXM_INTERFACE
bool sceGxmProgramParameterIsRegFormat(
	const SceGxmProgram *program,
	const SceGxmProgramParameter *parameter);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_PROGRAM_H_ */
