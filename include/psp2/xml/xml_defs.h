#ifndef _DOLCESDK_PSP2_XML_XML_DEFS_H_
#define _DOLCESDK_PSP2_XML_XML_DEFS_H_


//J XML出力オプション
//E XML serialization options
#define SCE_XML_SERIALIZE_OPT_USE_XML_DECLARATION  (1) ///< XML宣言を出力する


/** @brief Maximum size of an element name in DOM
 * If user provides element name bigger than this, it will
 * be truncated to fit this size.
 */
#define SCE_XML_ELEMENT_NAME_SIZE_MAX  (1024)

/** @brief Maximum size of an attribute name in DOM
 * If user provides attribute name bigger than this, it will
 * be truncated to fit this size.
 */
#define SCE_XML_ATTR_NAME_SIZE_MAX  (128)




#endif /* _DOLCESDK_PSP2_XML_XML_DEFS_H_ */

