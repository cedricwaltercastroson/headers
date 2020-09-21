#ifndef _DOLCESDK_PSP2_XML_XML_DEBUG_H_
#define _DOLCESDK_PSP2_XML_XML_DEBUG_H_

#include <psp2/xml/xml_types.h>

#if defined(__cplusplus)

namespace sce
{
namespace Xml
{

namespace Dom
{
	class Document;

	/// Document デバッグインタフェースクラス
	class DocumentDebug
	{
		/** コンストラクタ
		@param[in] doc (in) 対象にするDocument
		*/
		DocumentDebug(Document* doc);

		/// デストラクタ
		~DocumentDebug();

		/**
		* Returns the size of structure in case of readOnly mode.
		*	@retval size in bytes.
		*/
		size_t getStructSize() const;

		/**
		* Returns the size of Character table.
		*	@retval size in bytes.
		*		if it is of type RW, it returns 0.
		*/
		size_t getCharTableSize() const;

		/**
		* Returns the size of attribute table.
		*	@retval size in bytes.
		*/
		size_t getAttrTableSize() const;

		/**
		* Returns the size of element table.
		*	@retval size in bytes.
		*/
		size_t getElementTableSize() const;

	private:
		/// uncopyable
		DocumentDebug(const DocumentDebug&);
		DocumentDebug& operator=(const DocumentDebug&);
	};

} // namespace Dom


} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#endif  // _DOLCESDK_PSP2_XML_XML_DEBUG_H_

