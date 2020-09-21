#ifndef _DOLCESDK_PSP2_XML_XML_ATTRIBUTE_H_
#define _DOLCESDK_PSP2_XML_XML_ATTRIBUTE_H_

#include <psp2/xml/xml_result.h>
#include <psp2/xml/xml_types.h>

#if defined(__cplusplus)

namespace sce
{
namespace Xml
{

	class Initializer;
	class AttrImpl;

	/** @brief Attribute
	*
	* When an attribute list is supplied as part of a startElement event,
	* the list will return valid results only during the scope of the event;
	* once the event handler returns control to the parser, the attribute list is invalid.

	<pre>

	int startElement(void *userData, const String *name, const AttributeList *attrList)
	{
		for(size_t k=0; k < attrList->getLength(); k++){
			const Attr& att = attrList->getAttribute(k);

			const String& name = att.getName();
			const String& value = att.getValue();
		}
	}

	</pre>

	(Note that the result of attrList->getLength() will be zero if there are no attributes.)
	*/
	class Attr
	{
	public:
		/// Constructor
		Attr();
		/// Copy constructor
		Attr(const Attr &src);
		/// Destructor
		~Attr();

		/** @brief Assignment operator.
		* Returns the copy of the given Attr.
		* @param[in] src (in) Attr to be copied
		* @return Reference to the copied Attr
		*/
		Attr& operator=(const Attr &src);

		/** @brief Initialize.
		* This API must be called before another interface is used.
		* @param[in] init (in) Pointer to Initializer object
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int initialize(const Initializer* init);

		/** @brief Terminate.
		* Terminates and destroys the object and recovers the memory occupied.
		* @retval SCE_OK Success
		*/
		int terminate();

		/** @brief Get attribute name.
		Gets this attribute name.
		@return The attribute name associated to this Attr.
		*/
		String getName() const;

		/** @brief Get attribute value.
		Gets this attribute value.
		@return The attribute value associated to this Attr.
		*/
		String getValue() const;

		/** @brief Set attribute name.
		* Sets a name of this attribute.
		* @param[in] str (in) Pointer to the name to be set.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int setName(const String *str);

		/** @brief Set attribute value.
		* Sets a value of this attribute.
		* @param[in] str (in) Pointer to the value to be set.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int setValue(const String *str);

		/** @brief Check the availability.
		 * Returns if this object is available.
		 *
		 * @retval true Initialized and ready to use
		 * @retval false Not initialized
		 */
		bool isAvailable() const;

	private:
		friend class AttrImpl;
		AttrImpl *impl;
	};


} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#endif /* _DOLCESDK_PSP2_XML_XML_ATTRIBUTE_H_ */

