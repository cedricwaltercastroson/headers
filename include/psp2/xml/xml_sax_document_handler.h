#ifndef _DOLCESDK_PSP2_XML_XML_SAX_DOCUMENT_HANDLER_H_
#define _DOLCESDK_PSP2_XML_XML_SAX_DOCUMENT_HANDLER_H_

#include <psp2/xml/xml_types.h>

#pragma warning( push )
#pragma warning( disable:4100 ) // Suppress unused var warnings

#if defined(__SNC__)
#pragma diag_push
#pragma diag_suppress=828 // // Suppress unused var warnings
#endif

#if defined(__cplusplus)

namespace sce
{
namespace Xml
{
namespace Sax
{
	/** SAXのイベントハンドラインタフェースクラス
	*
	* SAXイベントを受け取るためにこのクラスを継承したクラスで各関数を実装してください。
	*/
	class DocumentHandler
	{

	public:
		/// コンストラクタ
		DocumentHandler() {}
		/// デストラクタ
		virtual ~DocumentHandler() {}

		/**
		* Receive notification of the beginning of a document.
		* The SAX parser will invoke this method only once, before any other methods in this interface are invoked.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		*
		* @retval Non-zero value to abort the parsing.
		*/
		virtual int startDocument(void *userData)
		{
			return 0;
		}

		/**
		*
		* Receive notification of the beginning of an element.
		* The Parser will invoke this method at the beginning of every element in the XML document;
		* there will be a corresponding endElement() event for every startElement() event (even when the element is empty).
		* All of the element's content will be reported, in order, before the corresponding endElement() event.
		* If the element name has a namespace prefix, the prefix will still be attached.
		* Note that the attribute list provided will contain only attributes with explicit values specified.
		* Element name, attribute names and values will be null terminated.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		* @param[out] name (out) Name of the start element.
		* @param[out] attrList (out) Attribute list of the start element.
		*
		* @retval Non-zero value to abort the parsing.
		*/
		virtual int startElement(void *userData, const String *name, const AttributeList *attrList)
		{
			return 0;
		}

		/**
		* Receive notification of character data.
		* The Parser will call this method to report each chunk of character data.
		* SAX parser may return all contiguous character data in a single chunk, or they may split it into several chunks;
		* The application must not attempt to read from the array outside of the specified range.
		* Character data will not be null terminated.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		* @param[out] ch (out) Character data.
		*
		* @retval Non-zero value to abort the parsing.
		*/
		virtual int characters(void *userData, const String *ch)
		{
			return 0;
		}

		/**
		* Receive notification of the end of an element.
		* The SAX parser will invoke this method at the end of every element in the XML document;
		* there will be a corresponding startElement() event for every endElement() event (even when the element is empty).
		* If the element name has a namespace prefix, the prefix will still be attached to the name.
		* End element name will be null terminated.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		* @param[out] name (out) Name of the end element.
		*
		* @retval Non-zero value to abort the parsing.
		*/
		virtual int endElement(void *userData, const String *name)
		{
			return 0;
		}

		/**
		* Receive notification of the end of a document.
		* The SAX parser will invoke this method only once, and it will be the last method invoked during the parse.
		* The parser shall not invoke this method until it has either abandoned parsing (because of an unrecoverable error) or
		* reached the end of input.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		*
		* @retval Non-zero value to abort the parsing.
		*/
		virtual int endDocument(void *userData)
		{
			return 0;
		}

		/**
		* Receive notification of the escaped text.
		* The escaped text is part of XML specifications but not supported by the parser.
		* This unsupported data will be sent to escapeText event, so that the application can extend this functionality for support.
		* @note Escaped text will not be null terminated.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		* @param[out] tokenType (out) The kind of token that represents the text. The possible tokens are as follows:
		- tokenPi
		- tokenDtd
		- tokenComment
		- tokenCdata
		- tokenPiEnd
		- tokenDtdEnd
		- tokenCommentEnd
		- tokenCdataEnd
		*
		* The tokens ends with _END are the ends of escaped text.
		* Otherwise there is still some data following the text in the following events.
		*
		* @param[out] text (out) Escaped text by the parser.
		*
		* @retval Non-zero value to abort the parsing.
		*/
		virtual int skippedText(void *userData, TokenType tokenType, const String *text)
		{
			return 0;
		}

		/**
		* Receive notification of entity information.
		*
		* This should be handled by the application to resolve appropriately.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		* @param[out] entityType (out) EntityType.
		*      In case of unknown entity the name will be sent as it is.
		* This event will be delegated only in case the resolving entity is true. This can be enabled/disabled by using SetResolveEntity() API of Parser.
		* @param[out] name (out) User defined entity name or built in entity name or resolved entity data.
		*
		* @retval Non-zero value to abort the parsing.
		*/
		virtual int entityData(void *userData, EntityType entityType, const String *name)
		{
			return 0;
		}

		/**
		* Receive notification of a non-recoverable error.
		* This corresponds to the definition of "fatal error" in section 1.2 of the W3C XML 1.0 Recommendation.
		* For example, a parser would use this callback to report the violation of a well-formedness constraint.
		* The application must assume that the document is unusable after the parser has invoked this method and
		* the parsing will be stopped after this callback.
		*
		* @param[out] userData (out) User defined data assigned by the application to the parser.
		* @param[out] errCode (out) Error while scanning the XML document.
		*/

		virtual void fatalError(void *userData, int errCode)
		{
		}
	}; // class DocumentHandler


} // namespace Sax
} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#if defined(__SNC__)
#pragma diag_pop
#endif

#pragma warning( pop )

#endif  // _DOLCESDK_PSP2_XML_XML_SAX_DOCUMENT_HANDLER_H_

