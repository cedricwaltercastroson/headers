#ifndef _DOLCESDK_PSP2_XML_XML_NODE_LIST_H_
#define _DOLCESDK_PSP2_XML_XML_NODE_LIST_H_

#include <psp2/xml/xml_result.h>
#include <psp2/xml/xml_node.h>
#include <psp2/xml/xml_types.h>

#if defined(__cplusplus)

namespace sce
{
namespace Xml
{
namespace Dom
{
	class Document;
	class Node;
	class NodeListImpl;

	/** @brief Interface class of the linked list of Node
	 *
	 *  A Class represents a linked list of Node with reference to a
	 *  Document object. The list is with respect to the Document, provided
	 *  during the initialization. Mixing of nodes from different Document
	 *  objects are not supported, which may cause unknown behaviour.
	 */
	class NodeList
	{
	public:
		/// Constructor
		NodeList();
		/// Copy constructor
		NodeList(const NodeList &src);
		/// Destructor
		~NodeList();

		/** @brief Assignment operator.
		* Returns the copy of the given NodeList.
		* @param[in] src (in) NodeList to be copied
		* @return Reference to the copied NodeList
		*/
		NodeList& operator=(const NodeList &src);

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
		 * @brief Clears the list
		 *
		 * Clears the list by removing all the nodes.
		 */
		void clear();

		/** @brief Get the number of nodes.
		 * Returns the number of nodes in the list.
		 * The range of valid
		 * child node indices is 0 to (length-1) inclusive.
		 *
		 * @retval >0 Length of the list
		 * @retval 0 The list is empty, unavailable or invalid.
		 */
		size_t getLength() const;

		/** @brief Insert a new Node at the beginning of the list.
		 *
		 * @param[in] newNode (in) The node to be inserted.
		 * @return the inserted node
		 * @return Dom::invalidNodeId : In case the NodeList is unavailable or invalid.
		 */
		NodeId insertFirst(NodeId newNode);

		/**
		 * Insert a new Node at the end of the list.
		 *
		 * @param[in] newNode (in) The node to be inserted.
		 * @return the inserted node
		 * @return Dom::invalidNodeId : In case the NodeList is unavailable or invalid.
		 */
		NodeId insertLast(NodeId newNode);

		/**
		 * Removes the arg node from the list.
		 *
		 * @param[in] node (in) The node to be deleted.
		 * @return the removed node
		 * @return Dom::invalidNodeId : In case the NodeList is unavailable or invalid.
		 */
		NodeId removeItem(NodeId node);

		/**
		 * Returns the indexth item in the list.
		 *
		 * If index is greater than or equal to the number of nodes in the
		 * list, this returns Dom::invalidNodeId.
		 *
		 * @param[in] index (in) Index into the collection.
		 *
		 * @return The node at the indexth position in the NodeList.
		 * @return Dom::invalidNodeId : In case the NodeList is unavailable or invalid.
		 */
		NodeId item(index_t index) const;
		/** @brief Get a node by the index.
		 * Returns the indexth item in the list.
		 *
		 * Same as item().
		 */
		NodeId operator[](index_t index) const;

		/**
		 * Finds the node with the given name.
		 *
		 * If there are more than
		 *  one first matched node is returned.
		 *
		 * @param[in] name (in) the node name to be searched.
		 * @return the found node
		 * @return Dom::invalidNodeId if not found.
		 */
		NodeId findItem(const String *name) const;

		/**
		 * Search the list to find if the given arg node is already present,
		 * in the list.
		 *
		 * @param[in] node (in) the node to be searched.
		 * @return found node
		 * @return Dom::invalidNodeId if not found.
		 */
		NodeId findItem(NodeId node) const;

		/** @brief Check the availability.
		 * Returns if the list is available
		 *
		 * @retval true Initialized and ready to use
		 * @retval false Not initialized
		 */
		bool isAvailable() const;

	protected:
		NodeListImpl *impl;
	};

} // namespace Dom
} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#endif /* _DOLCESDK_PSP2_XML_XML_NODE_LIST_H_ */

