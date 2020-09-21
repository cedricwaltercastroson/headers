#ifndef _DOLCESDK_PSP2_XML_XML_NODE_H_
#define _DOLCESDK_PSP2_XML_XML_NODE_H_

#include <psp2/xml/xml_types.h>

#if defined(__cplusplus)

namespace sce
{
namespace Xml
{
namespace Dom
{

	class Document;
	class NodeList;
	class NodeImpl;

	/** @brief Interface class of Node
	 *
	 * A Class represents Node with reference to a Document object. \n
	 * Note: Class Node is implemented as the wrapper to Document in this library. \n
	 * Please refer to Document class.
	 */
	class Node
	{
	public:
		/// Constructor
		Node(NodeId id);
		/// Copy constructor
		Node(const Node &src);
		/// Destructor
		~Node();

		/** @brief Assignment operator.
		* Returns the copy of the given Node.
		* @param[in] src (in) Node to be copied
		* @return Reference to the copied Node
		*/
		Node& operator=(const Node& src);

		/** @brief Get the node name.
		* Returns the name of this node.
		* @return String of the node name, or empty string if given node does not support node name.
		*/
		String getNodeName() const;

		/** @brief Get the node value.
		* Returns the value of this node.
		* @return String of the node value, or empty string if given node does not support node value.
		*/
		String getNodeValue() const;

		/** @brief Get the node type.
		* Returns the type of this node.
		* @return Type of the node.
		*/
		NodeType getNodeType() const;

		/** @brief Get the parent node.
		* Returns the parent node.
		* @return NodeId of the parent node.
		*/
		NodeId getParentNode() const;

		/** @brief Get the child nodes.
		* Returns list of the child nodes.
		* @return Pointer to the list of the child nodes.
		*/
		NodeList* getChildNodes() const;

		/** @brief Get the first child node.
		* Returns the first child node.
		* @return NodeId of the first child node.
		*/
		NodeId getFirstChild() const;

		/** @brief Get the last child node.
		* Returns the last child node.
		* @return NodeId of the last child node.
		*/
		NodeId getLastChild() const;

		/** @brief Get the sibling node.
		* Returns the sibling node.
		* @return NodeId of the sibling node.
		*/
		NodeId getNextSibling() const;

		/** @brief Get the attribute nodes.
		* Returns list of the attribute nodes.
		* @return Pointer to the list of the attribute nodes.
		*/
		NodeList* getAttributes() const;

		/** @brief Get the owner document.
		* Returns the owner document.
		* @return Pointer to the owner document.
		*/
		Document* getOwnerDocument() const;

		/** @brief Insert a node.
		* Inserts a new node.
		* @param[in] newChild (in) the node to be inserted
		* @param[in] refChild (in) the node of the position of the insertion
		* @return NodeId of the inserted node.
		*/
		NodeId insertBefore(NodeId newChild, NodeId refChild);

		/** @brief Remove the child node.
		* Removes the child node.
		* @param[in] oldChild (in) the node to be removed
		* @return NodeId of the removed node.
		* @note The NodeId is returned but it is unavailable any longer.
		*/
		NodeId removeChild(NodeId oldChild);

		/** @brief Insert a child node.
		* Inserts a new node to the current owner document.
		* @param[in] newChild (in) the node to be inserted
		* @return NodeId of the inserted node.
		*/
		NodeId appendChild(NodeId newChild);

		/** @brief Check if any child node(s) exist.
		* Returns if the node has child node(s)
		* @return true The node has a child at least
		* @return false The node has no child
		*/
		bool hasChildNodes() const;

		/** @brief Check if any attribute(s) exist.
		* Returns if the node has attribute(s)
		* @return true The node has a child at least
		* @return false The node has no child
		*/
		bool hasAttributes() const;

		/** @brief Check the availability.
		* Returns if this object is available.
		* @retval true Initialized and ready to use
		* @retval false Not initialized
		*/
		bool isAvailable() const;

	private:
		friend class NodeImpl;
		char impl[64];
	};


} // namespace Dom
} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#endif /* _DOLCESDK_PSP2_XML_XML_NODE_H_ */

