#ifndef _DOLCESDK_PSP2_XML_XML_ATTRIBUTE_LIST_H_
#define _DOLCESDK_PSP2_XML_XML_ATTRIBUTE_LIST_H_

#include <psp2/xml/xml_attribute.h>
#include <psp2/xml/xml_types.h>

#if defined(__cplusplus)

namespace sce
{
namespace Xml
{

	class Attr;
	class Initializer;
	class AttributeListImpl;

	/// Attribute List
	class AttributeList
	{
	public:
		/// Constructor
		AttributeList();
		/// Copy constructor
		AttributeList(const AttributeList &src);
		/// Destructor
		~AttributeList();

		/** @brief Assignment operator.
		* Returns the copy of the given AttributeList.
		* @param[in] src (in) AttributeList to be copied
		* @return Reference to the copied AttributeList
		*/
		AttributeList& operator=(const AttributeList &src);

		/** @brief Initialize.
		* This API must be called before another interface is used.
		* @param[in] init (in) Pointer to Initializer object
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int initialize(const Initializer* init);

		/** @brief Terminate.
		* Destroy any local objects
		*/
		int terminate();

		/** @brief Get Attribute by the name.
		* Get the Attr object pointer whose name is equal to "name".
		*
		* @param[in] attName (in) Attr name to be searched for in AttrList.
		*
		* @return The Attr object whose attName is matched, or invalid Attr if nothing found.
		*/
		Attr getAttribute(const String *attName) const;

		/** @brief Get Attribute by the index.
		* Return the Attr object pointer whose index is equal to "index".
		*
		* @param[in] index (in) Attr index to be returned by the AttrList.
		*
		* @return The Attr object whose index is matched, or invalid Attr if nothing found.
		*/
		Attr getAttribute(index_t index) const;

		/** @brief Get number of attributes.
		* Return the number of attributes in the attribute list.
		*
		* @return The number of attributes in the list.
		*/
		size_t getLength() const;

		/** @brief Add a new attribute.
		* Add a new attribute to the list with name and value.
		*
		* @param[in] name (in) Attr name.
		* @param[in] value (in) Attr value.
		*
		* @note No XML name rules are checked,
		*		 except for Attr name not NULL.
		*		 When using with R/W DOM APIs, the attribute
		*		 name and value can be any string,
		*		 it is user's responsibility to check for the
		*		 valid XML name if necessary. If invalid
		*		 name or value is given, resulting XML document
		*		 after serialize may not be well-formed document.
		*/
		int addAttribute(const String *name, const String *value);

		/** @brief Clear the list.
		* If the attribute list has to be used very frequently,
		* then using this funtion clears the attributes from the list logically.
		* But the logically deleted objects can be reused without creating
		* again. This will improve the performance.
		*/
		void clear();

		/** @brief Check the availability.
		 * Return if the list is available.
		 *
		 * @retval true Initialized and ready to use
		 * @retval false Not initialized
		 */
		bool isAvailable() const;

	protected:
		friend class AttributeListImpl;
		AttributeListImpl *impl;
	};


} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#endif	/* _DOLCESDK_PSP2_XML_XML_ATTRIBUTE_LIST_H_ */

