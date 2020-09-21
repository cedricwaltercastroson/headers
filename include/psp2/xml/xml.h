#ifndef _DOLCESDK_PSP2_XML_XML_H_
#define _DOLCESDK_PSP2_XML_XML_H_

#include <psp2/xml/xml_types.h>

#if defined(__cplusplus)

namespace sce
{
/// XMLプロセッサの名前空間
namespace Xml
{

/// SAX APIの名前空間
namespace Sax
{
	class DocumentHandler;
	class ParserImpl;

	/// SAX インタフェースクラス
	class Parser
	{
	public:
		/// コンストラクタ
		Parser();
		/// デストラクタ
		~Parser();

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

		/**
		* Attach the SAX handler object to parser to be used for delegating the SAX events.
		*
		* @param[in] processor (in) The XML Processor object to which the SAX events will be
		* delegated while parsing the XML document from XML stream.
		*
		*/
		void setDocumentHandler(DocumentHandler *processor);

		/**
		* Attach the SAX handler object to parser to be used for delegating the SAX events.
		*
		* @param[in] data (in) User data set by the application to the parser which is given to all the further SAX events.
		*
		*/
		void setUserData(void *data);

		/**
		* Parse the XML document from the buffer and delegate SAX events. If the isFinal is true, then the parser will be reset before returning from the function call. Returns error, if the handler is NULL.
		*
		* @param[in] text (in) The chunk of XML data to be parsed.
		* @param[in] isFinal (in) Is the chunk is the final chunk to be parsed in the current XML stream. Default value is true.
		*
		* @retval <0 Error code
		* @retval SCE_OK Success in case isFinal is true.
		* @retval resultXmlParseInProgress In case of chunk parsing, the
		*	current parse with the given chunk is successful.
		*/
		int parse(const XmlText *text, bool isFinal = true);

		/** @brief Reset the XML parser.
		* Reinitialize all the stacks and local variables.
		*
		* @retval <0 Error code
		* @retval SCE_OK Success in case isFinal is true.
		*/
		int reset();

		/**
		* Skip the ignorable white spaces, if the skip flag is set to true.
		*
		* @param[in] isSkipped (in) True in case the ignorable white spaces have to be kipped.
		*/
		void setSkipIgnorableWhiteSpace(bool isSkipped);

		/**
		* Resolve the built in entities and character references. In case of
		user defined entities, it will be treated like entity without being
		resolved.
		*
		* @param[in] isResolved (in) True in case the entities have to be resolved while
		parsing the XML document.
		*/
		void setResolveEntity(bool isResolved);

	protected:
		ParserImpl *impl;

	private:
		Parser(const Parser&);
		Parser& operator=(const Parser&);
	};

} // namespace Sax


/// DOM APIの名前空間
namespace Dom
{
	class Document;
	class DocumentBuilderImpl;

	/// DOM 生成 インタフェースクラス
	class DocumentBuilder
	{
	public:
		/// コンストラクタ
		DocumentBuilder();
		/// デストラクタ
		~DocumentBuilder();

		/** @brief Initialize.
		* This API must be called before another interface is used.
		* @param[in] init (in) Pointer to Initializer object
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int initialize(const Initializer* init);

		/** @brief Terminate.
		* Terminates and destroys any local objects including generated the Document.
		* @retval SCE_OK Success
		*/
		int terminate();

		/** @brief Parse and create the Document tree structure
		*
		* Parse the XML document from the buffer and create Document. \n
		* If the isFinal is true, then the parser will be
		* reset before returning from the function call.
		*
		* @param[in] text (in) The chunk of XML data to be parsed.
		* @param[in] isFinal (in) Whether the input chunk is the final
		* chunk to be parsed in the current XML stream. Default value
		* is true.
		* @retval <0 Error code
		* @retval SCE_OK Success in case isFinal is true.
		* @retval resultXmlParseInProgress In case of chunk parsing, the
		*	current parse with the given chunk is successful.
		*/
		int parse(const XmlText *text, bool isFinal = true);

		/** @brief Get the created Document
		*
		* Get the Document created by the last parse() call.
		* This returned object has a reference to the Document held in this DocumentBuilder instance.
		* The Document in the DocumentBuilder is kept until the next parse() call
		* or the DocumentBuilder deleted.
		* The DocumentBuilder is required to be remained while using the Document.
		*
		* @return The Document, created by parsing the XML document in the last parse() call.
		*/
		Document getDocument();

		/** @brief Set white space skip behavior
		*
		* Skip the ignorable white spaces, if the skip flag is set to true. \n
		* Default is true.
		*
		* @param[in] isSkipped (in) Set true in case the ignorable white spaces have to be skipped.
		*/
		void setSkipIgnorableWhiteSpace(bool isSkipped);

		/** @brief Set text skip behavior
		*
		* Ignore the skip text (CDATA, Programming Instruction(PI),
		* XML Declaration, Comment and Document Type
		* Definition(DTD))to be included in the bX structure.  When
		* the parse is in progress in case of chunked parsing, it can
		* not be changed. \n
		* Default is true.
		*
		* @param[in] isSkipped (in) True if it has to be skipped. False
		* otherwise. Default value is false
		*
		*/
		void setSkipIgnorableText(bool isSkipped);

		/** @brief Set entity resolving behavior
		*
		* Configure if the parser resolves the built in entities and character references. \n
		* In case of user defined entities, it will be treated like entity without being resolved. \n
		* Default is false.
		* @param[in] isResolved (in) True in case the entities have to be resolved while
		parsing the XML document.
		*/
		void setResolveEntity(bool isResolved);

	protected:
		DocumentBuilderImpl *impl;

	private:
		DocumentBuilder(const DocumentBuilder&);
		DocumentBuilder& operator=(const DocumentBuilder&);
	};


	class DocumentImpl;

	/// DOM インタフェースクラス
	class Document
	{
	public:
		/// Constructor
		Document();
		/// Copy constructor
		Document(const Document &src);
		/// Destructor
		~Document();

		const Document& operator=(const Document&);

		/** @brief Initialize.
		* This API must be called before another interface is used.
		* @param[in] init (in) Pointer to Initializer object
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int initialize(const Initializer* init);

		/** @brief Terminate.
		* Terminates and destroys the Document and recovers the memory occupied.
		* @retval SCE_OK Success
		*/
		int terminate();

		/**  @brief Get the document root node.
		* Returns the document root node(first node) of the document.
		*  The returned node may have XML Meta information stored before
		*  the first document element node.
		* @return NodeId to the document root, or Dom::invalidNodeId
		*  if document root node does not exist or the document not initialized.
		*/
		NodeId getDocRoot() const;

		/**  @brief Get the root node.
		* Returns the root node(first element node) of the document.
		* @return Valid NodeId of the root node, or Dom::invalidNodeId
		*  if root node does not exist or the document not initialized.
		*/
		NodeId getRoot() const;

		/** @brief Get the first child node.
		* Returns the first child for the given node within the current document.
		* @param[in] node (in) Node for which child node is returned.
		* @return Valid NodeId of the first child node, or Dom::invalidNodeId
		*  if no child node or the node is leaf node.
		*/
		NodeId getFirstChild(NodeId node) const;

		/** @brief Get the sibling node.
		* Returns the sibling for the given node within the current document.
		* @param[in] node (in) Node for which sibling node is returned.
		* @return Valid NodeId of the sibling node exists, or Dom::invalidNodeId
		*  if no sibling node.
		*/
		NodeId getSibling(NodeId node) const;

		/** @brief Get the node name.
		* Returns the name of the given element node.
		* @param[in] node (in) Node for which name is returned.
		* @return String of the node name, or empty string if given node does not support node name.
		*/
		String getNodeName(NodeId node) const;

		/** @brief Get the text node value.
		* Returns the value of the given text node.
		* @param[in] node (in) Node for which name is returned.
		* @return String of the text, or empty string if given node does not support text.
		*/
		String getText(NodeId node) const;

		/** @brief Get the first attribute.
		* Returns the first attribute for a given element node.
		* @param[in] node (in) Node for which first attribute
		*					is returned.
		* @return Valid NodeId of the document root, or Dom::invalidNodeId
		*  if given node does not have any attribute.
		*/
		NodeId getFirstAttr(NodeId node) const;

		/** @brief Get the next attribute.
		* Returns the next attribute for a given element node.
		* @param[in] node (in) Node for which next attribute
		*					is returned.
		* @return Valid NodeId of the document root, or Dom::invalidNodeId
		*  if given node does not have any more attribute.
		*/
		NodeId getNextAttr(NodeId node) const;

		/** @brief Get the attribute name.
		* Returns the name of the given attribute node.
		* @param[in] node (in) Node for which attribute name is returned.
		* @return String of the attribute name, or empty string if given node is not of attribute type.
		*/
		String getAttrName(NodeId node) const;

		/** @brief Get the attribute value.
		* Returns the attribute value for the given attribute node.
		* @param[in] node (in) Node for which attribute value is returned.
		* @return String of the attribute value, or empty string if given node is not of attribute type.
		*/
		String getAttrValue(NodeId node) const;

		/** @brief Get the parent node.
		* Returns the parent node a given node.
		* @param[in] node (in) Node for which parent
		*					is returned.
		* @return Valid NodeId of the parent node, or Dom::invalidNodeId
		*  if given node does not belong to the current Document.
		*
		*  @note Performance note: getParent searches the document from root
		*			for parent, may reduce performance if used many time.
		*			Instead it is recomonded to keep parent NodeId.
		*/
		NodeId getParent(NodeId node) const;

		/** @brief Get the skipped text.
		* Returns the value of the given skipped text node.
		* @param[in] node (in) Node for which value is returned.
		* @return String of the skipped text, or empty string if given node does not support skipped text.
		*/
		String getSkippedText(NodeId node) const;

		/** @brief Get the entity type.
		* Returns the entity type of the given entity node.
		* @param[in] node (in) Node for which entity is returned.
		* @return Entity type of the node.
		*/
		EntityType getEntityType(NodeId node) const;

		/** @brief Get the entity text.
		* Returns the value of the given entity node, for
		*  user defined entity or character entity reference.
		* @param[in] node (in) Node for which entity value is returned.
		* @return String of the entity text, or empty string if given node is not of user defined entity or character entity reference.
		*/
		String getEntity(NodeId node) const;

		/** @brief Get the MetaNodeId.
		* Returns the meta node for the document root.
		* @return Valid MetaNodeId of the document root node.
		*/
		MetaNodeId getXmlMeta() const;

		/** @brief Get the node type.
		*  A type representing the type of the underlying object,
		*  as defined in Dom::NodeType.
		* @return type of the node.
		*/
		NodeType getNodeType(NodeId node) const;

		/** @brief Get a NodeList by the name.
		* Returns a NodeList of all the descendant elements with a given node name
		*  in the order in which they are encountered in a preorder traversal
		*  of this element tree. \n
		* nodelist is not required NodeList::initialize() before this API call. It requires to be deleted after an application finishes using it.
		* @param[in] node (in) root of the search tree.
		* @param[in] name (in) name of the elements to match on.
		* @param[out] nodelist (out) NodeList object to get the result.
		* The special value "*" matches all names. \n
		* Application doesn't need to call initialize() for passing nodelist.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int getElementsByTagName(NodeId node, const String *name, NodeList *nodelist) const;

		/** @brief Get the status.
		* Returns status of previous operation.
		*
		* @return The last error code
		*/
		int getStatus() const;

		/** @brief Reset the status.
		*  Reset the Document status to resultSuccess.
		* If the previously invoked API results in error
		* such as:
		* - resultDomMaxNumOfAttrError,
		* - resultDomMaxUniqueElementError,
		* it is safe to reset, so that the Document can be reused.
		* In case of memory error, or other critical errors, in such case
		* resetting may cause unknown behavior. In such case it is better to
		* re-create the document, by removing the error.
		*/
		void resetStatus();

		/** Returns if the Document is read only.
		*/
		bool isReadOnly() const;

		/** @brief Set the DOM tree read-write
		* @retval <0 Error code
		* @return NodeId for DocumentRoot cf. getDocRoot()
		* @return Dom::invalidNodeId if failed.
		*/
		NodeId setWritable();

		/** @brief Create and add an element.
		* The element with attribute list and text is
		* added to the end of the list of children of the specified node.
		*
		* @param[in] parent (in) parent node to which the given element is appended.
		* @param[in] name (in) The name of the element node to be instantiated.
		* @note The  name is not checked for XML canonical naming convention.
		*
		* @param[in] list (in) attribute list to be added to the element.
		* @param[in] text (in) text to be added to the element as child node.
		*
		* @return The node added.
		*/
		NodeId addElementChild(NodeId parent, const String *name, const AttributeList *list = 0, const String *text = 0);

		/** @brief Creates an element.
		*
		* @note Memory Note: If the created Node is inserted to R/W DOM tree
		*				  using insertNode() then, the  node will be recovered
		*				  automatically when document is destroyed.
		*				  If the node is not inserted as part of the tree,
		*				  it has to be destroyed explicitly by using recurseDelete()
		*				  API, failed to do so will result in memory leak.
		*
		* @param[in] name (in) The name of the element node to be instantiated.
		* @note The  name is not checked for XML cannonical naming convension.
		* @param[in] list (in) list of attributes which has to be added to the element.
		* @param[in] text (in) text child to be added
		*
		ex., to create a node such as
		<pre>

		&lt;test&gt;example&lt;/test&gt;

		</pre>
		following call will create such element node:

		createElement(&String("test"), NULL, &String("example"));

		* @return A new element node
		*/
		NodeId createElement(const String *name, const AttributeList *list =0,
			const String *text = 0);

		/** @brief Insert the node.
		* Inserts the node child after the existing child
		* node ref. If ref is invalid, insert child as
		* the first node of the element.
		* If the child is already in the tree, it is
		* first removed.
		*
		* @param[in] parent (in) parent of the reference node or
		*						to which given child node is inserted.
		* @param[in] ref (in) The reference node, i.e., the node after
		*							which the new node must be inserted.
		* @param[in] child (in) The node to insert.
		* @return The node being inserted.
		*/
		NodeId insertNode(NodeId parent, NodeId ref, NodeId child);

		/** @brief Creates a Text node.
		*  Creates a Text node given the specified string and length.
		*  @note Memory Note: If the created Node is inserted to R/W DOM tree
		*				  using insertNode then, the  node will be recovered
		*				  automatically when document is destroyed.
		*				  If the node is not inserted as part of the tree,
		*				  it has to be destroyed explicitly by using recurseDelete()
		*				  API, failed to do so will result in memory leak.
		*
		* @param[in] text (in) The text for the node.
		* @return The new Text object.
		*/
		NodeId createTextNode(const String *text);

		/** @brief Remove nodes recursively.
		* Deletes the given node from memory.
		* If the given node is a tree, it deletes recursively.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int recurseDelete(NodeId node);

		/** @brief Remove the child node.
		* Removes the child node indicated by child from the
		* list of children, and returns it.
		*
		* @param[in] child (in) The node being removed.
		* @param[in] parent (in) The parent node of node being removed.
		*
		* @return The node removed.
		*/
		NodeId removeChild(NodeId child, NodeId parent);

		/** @brief Import another document.
		* Imports the given document with the given node as parent.
		* The complete document becomes the child of given node.
		* Note: The child tree's parent node will be last node of the
		*		  given parent tree.
		<pre>

		ex., if the parent tree is:

		&lt;test&gt;&lt;firstNode&gt;&lt;impNode/&gt;&lt;/firstNode&gt;&lt;/test&gt;

		child tree:
		&lt;bigChild&gt;Big Big Tree&lt;/bigChild&gt;

		</pre>
		If the parent tree is imported as parent of child tree,
		the impNode of parent tree becomes the parent node of the tree.
		* The imported parent node must not have attributes.
		* @param[in] parentDoc (in) parent document
		* @param[in] parent (in) parent node which will become parent.
		*
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int importParent(const Document *parentDoc, NodeId parent);

		/** @brief Import another document.
		* Imports the given node with the given document to the.
		* given node of this document. The import operation copies
		* all the data and the nodes to this document.
		*
		* @param[in] nparent (in) starting node which has to be imported.
		* @param[in] ref (in) The reference node, i.e., the node after
		*							which the new node must be inserted.
		* @param[in] doc (in) document from which nparent node to be imported.
		* @param[in] node (in) node which to which imported nodes are attached.
		*/
		NodeId importNode(NodeId nparent, NodeId ref, const Document *doc, NodeId node);

		/** @brief Set the text.
		* Sets text value for text node
		* @param[in] node (in) Text node whose value has to be changed.
		* @param[in] text (in) value which has to be set.
		* @note It will replace the old value.
		*
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int setText(NodeId node, const String *text);

		/** @brief Set the attribute value.
		* Sets value for the given attribute name, of the given
		*  element node. If the given attribute does not exists, a new
		*  attribute is added to the given element node.
		* @param[in] node (in) Element node, attribute of this node is changed.
		* @param[in] name (in) Name of the attribute whose value to be changed.
		* @param[in] value (in) Vvalue which has to be set for the given attribute.
		* @note It will replace the old value.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int setAttrValue(NodeId node, const String *name, const String *value);

		/** @brief Set the attribute.
		*  Adds the given attribute name, of the given
		*  element node. If the given attribute does not exists, a new
		*	attribute is added to the given element node, otherwise, the value is
		*  updated.
		*  @param[in] node (in) Element node, attribute of this node is changed.
		*  @param[in] name (in) Name of the attribute whose value to be changed.
		*  @param[in] value (in) Value which has to be set for the given attribute.
		* @note It will replace the old value.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int setAttribute(NodeId node, const String *name, const String *value);

		/** @brief Set the attributes.
		*  Add attribute list to the node.
		*  This API removes all the attribute from the given node if exists.
		*  @param[in] node (in) the element node to which attribute list to be added.
		*  @param[in] list (in) attribute list to be added to the element.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int setAttributeList(NodeId node, const AttributeList* list);

		/** @brief Remove attributes.
		*  Remove the attributes from the given element node.
		*	This API removes the attribute from element of a R/W DOM tree, whose
		*  name is given.
		*  @param[in] node (in) Element node, attribute of this node is removed.
		*  @param[in] name (in) attribute name which has to be removed.
		*  If the tree is read only, error flag is set to result_DOM_ReadOnlyError.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int removeAttribute(NodeId node, const String *name);

		/** @brief Remove attributes recursively.
		* Remove all the attributes from the given element node.
		* This API removes all the attribute from the element.
		* If the tree is read only, error flag is set to result_DOM_ReadOnlyError.
		* @param[in] node (in) Element node
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int removeAttributes(NodeId node);

		/** @brief Get child nodes.
		* Returns the list including all the childs if exists. \n
		* nodelist is not required NodeList::initialize() before this API call. It requires to be deleted after an application finishes using it.
		* @param[in] node (in) specifying Node for which child node list is returned.
		* @param[out] nodelist (out) NodeList object to get the result containing all the matches.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int getChildNodes(NodeId node, NodeList *nodelist) const;

		/** @brief Get the last child.
		* Gets the last child node of the given node
		*/
		NodeId getLastChild(NodeId node) const;

		/** @brief Check if any child node(s) exist.
		* Returns true if the given node has child node(s)
		*/
		bool hasChildNodes(NodeId node) const;

		/** @brief Check if any attribute(s) exist.
		* Returns true if the given node has attribute(s)
		*/
		bool hasAttributes(NodeId node) const;

		/** @brief Get the attribute value.
		* Returns the attribute value for the given attribute
		*/
		String getAttribute(const NodeId node, const String *name) const;

		/** @brief Get attributes.
		* Returns the attribute list for the given element node.
		* Input Node must be valid node of type element,
		* this check is not done internally, and it must be ensured before sending the node. \n
		* nodelist is not required NodeList::initialize() before this API call. It requires to be deleted after an application finishes using it.
		* @param[in] node (in) specifying Node for which child node list is returned.
		* @param[out] nodelist (out) NodeList object to get the result containing all the matches.
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int getAttributes(NodeId node, NodeList *nodelist) const;

		/** @brief Serialize the Document to XML text.
		*	@param[in] param (in) parameter to control serialization
		*	@param[out] outputString (out) output string
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int serialize(const SerializeParameter *param, XmlText* outputString);

		/** @brief Check the availability.
		 * Returns if this object is available.
		 *
		 * @retval true Initialized and ready to use
		 * @retval false Not initialized
		 */
		bool isAvailable() const;

	protected:
		DocumentImpl *impl;
	};

} // namespace Dom


/// ユーティリティの名前空間
namespace Util
{
	/** Convert result error number to string
		@param[in] result (in) result number
		@return string expression of the given result
	*/
	const char* strResult(int result);

} // namespace Util

} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#endif  // _DOLCESDK_PSP2_XML_XML_H_

