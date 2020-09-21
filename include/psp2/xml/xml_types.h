#ifndef _DOLCESDK_PSP2_XML_XML_TYPES_H_
#define _DOLCESDK_PSP2_XML_XML_TYPES_H_

#include <psp2/types.h>

#include <psp2/xml/xml_result.h>
#include <psp2/xml/xml_defs.h>

#if defined(__cplusplus)

namespace sce
{
namespace Xml
{
	/// インデックスを表す型
	typedef SceUInt32 index_t;

	/// 不正なインデックスを表す値
	#define SCE_XML_INVALID_INDEX  ((index_t)-1)
	/// 不正なインデックスを表す値
	const index_t invalidIndex = SCE_XML_INVALID_INDEX;

	#ifndef WIN32
	/// サイズを表す型
	typedef SceUInt32 size_t;
	#endif

	/// 不正なサイズを表す値
	#define SCE_XML_INVALID_SIZE  ((size_t)-1)
	/// 不正なサイズを表す値
	const size_t invalidSize = SCE_XML_INVALID_SIZE;

	/** データへのポインタと長さを保持するクラス
	*
	* メンバに直接アクセスして構いません。
	*/
	class SimpleData
	{
	public:
		/// メンバを 0 で初期化するデフォルトコンストラクタ
		SimpleData();

		/** データ列（'\\0'終端されていなくてもよい）と長さを受け取るコンストラクタ
			@param[in] data (in) セットするデータへのポインタ
			@param[in] size (in) セットするデータの長さ（単位：バイト）
		*/
		SimpleData(const char *data, size_t size);

		const char *buffer; ///< データへのポインタ
		size_t size; ///< データ長
	};

	typedef SimpleData BinaryData;


	/** @brief 文字列へのポインタと長さを保持するクラス
	*
	* コピーすると同じ領域を指すようになります。
	*/
	class String : public SimpleData
	{
	public:
		/** @brief Constructor
		* Initialize the member variables.
		* @return None
		*/
		String();

		/// Copy constructor
		String(const String& src);

		/** @brief Assignment operator.
		* Returns the copy of the given node.
		* @param[in] src (in) Node to be copied
		* @return Reference to the copied Node
		*/
		String& operator =(const String& src);

		/** 文字列（'\\0'終端されていなくてもよい）と長さを受け取るコンストラクタ
			@param[in] str (in) セットする文字列
			@param[in] size (in) セットする文字列の長さ（単位：バイト）
		*/
		String(const char *str, size_t size);

		/** 渡された文字列へのポインタを buffer へセットするコンストラクタ
			@param[in] str (in) セットする文字列
			文字列長を測定してsize へ格納します。
		*/
		String(const char * str);

		/** @brief 有効判定
		*
		* 保持しているものが有効かどうかを返します。
		* @retval true 有効
		* @retval false 無効（バッファへのポインタがNULLまたは文字列の長さが0）
		*/
		bool isAvailable() const
		{
			return (this && buffer && size);
		}
	};

	typedef String XmlText;


	/// トークンのタイプ
	typedef enum TokenType
	{
		tokenUnknown = -1,
		tokenInit = 0,
		tokenStartTag,
		tokenEndTag,
		tokenCharData,
		tokenDtd,
		tokenDtdEnd,
		tokenPi,
		tokenPiEnd,
		tokenCdata,
		tokenCdataEnd,
		tokenComment,
		tokenCommentEnd,
		tokenUnexpected,
		tokenEscapedText,
		tokenXmlEmpty,
		tokenXmlEntity,
		tokenXmlEntityEnd,
	} TokenType;


	/// エンティティのタイプ
	typedef enum EntityType
	{
		entityUnknown = 0, ///< エンティティタイプが不明
		entityCharReference, ///< 文字参照エンティティ
		entityBuiltInAmp, ///< 定義済みエンティティ：＆
		entityBuiltInQuot, ///< 定義済みエンティティ：”
		entityBuiltInLt, ///< 定義済みエンティティ：＜
		entityBuiltInGt, ///< 定義済みエンティティ：＞
		entityBuiltInApos, ///< 定義済みエンティティ：’
	} EntityType;


	/// メモリアロケータインタフェースクラス
	/** ライブラリを利用するユーザがこのクラスを継承して実装します。
	 ライブラリ内でメモリの確保・解放が必要な際に呼び出されます。
	*/
	class MemAllocator
	{
	public:
		/// コンストラクタ
		MemAllocator();
		/// デストラクタ
		virtual ~MemAllocator();

		/** メモリ割り当て関数
		@param[in] size (in) サイズ
		@param[in] userData (in) ユーザが渡す任意のデータ。\n
			InitParameter::userData に渡したものが返されます。
		@retval Non-NULL 確保したメモリ領域の先頭ポインタ
		@retval NULL メモリ確保に失敗したとき

		呼び出しがあった際にメモリ割り当てを行いポインタを返してください。
		割り当てに失敗したときはNULLを返してください。
		*/
		virtual void *allocate(size_t size, void *userData) =0;

		/** メモリ解放関数
			@param[in] ptr (in) 解放するポインタ
			@param[in] userData (in) ユーザが渡す任意のデータ。\n
				InitParameter::userData に渡したものが返されます。
		*/
		virtual void deallocate(void *ptr, void *userData) =0;
	};


	/** @brief 初期化パラメタクラス
	*/
	class InitParameter
	{
	public:
		/// メンバを 0 で初期化するデフォルトコンストラクタ
		InitParameter()
			: allocator(0), userData(0) {}

		InitParameter(MemAllocator *al, void *ud)
			: allocator(al), userData(ud) {}

		MemAllocator *allocator; ///< (in) メモリアロケータ
		void *userData; ///< (in) ユーザ任意のデータ \nメモリアロケータの実装関数の引数に渡されます
		int reserve[4]; ///< 未使用
	};


	class InitializerImpl;

	/** @brief オブジェクト初期化インタフェースクラス
	*
	* sce::Xml の他のオブジェクトを生成する前にこのクラスの
	* インスタンスを生成する必要があります。
	*/
	class Initializer
	{
	public:
		/// コンストラクタ
		Initializer();
		/// デストラクタ
		~Initializer();

		/** @brief 初期化
		* @param[in] initParam (in) Initialize parameter
		* @retval <0 Error code
		* @retval SCE_OK Success
		*/
		int initialize(const InitParameter* initParam);

		/** @brief 終了
		*
		* Terminates and destroys the object.
		* @retval SCE_OK Success
		*/
		int terminate();

	private:
		Initializer(const Initializer&);
		Initializer& operator=(Initializer&);
		friend class InitializerImpl;
		InitializerImpl *impl;
	};


#if 0
	/// XMLパースパラメタクラス
	class ParseParameter
	{
	public:
		/// メンバを デフォルト値で初期化するコンストラクタ
		ParseParameter();

		bool skipIgnorableWhiteSpace; ///< ホワイトスペースを無視するかどうか
		bool skipIgnorableText; ///< テキストノード以外のテキストを無視するかどうか
		bool resolveEntity; ///< エンティティを取り扱うかどうか
	};
#endif


	/// XML出力パラメタクラス
	class SerializeParameter
	{
	public:
		/// メンバを 0 で初期化するデフォルトコンストラクタ
		SerializeParameter();

		int serializeOption; ///< (in) 出力制御オプション
		int reserve[4]; ///< 未使用
	};


namespace Dom
{
	/// ノードID
	typedef SceUInt64 NodeId;
	typedef NodeId MetaNodeId;
	/// 不正なノードID値
	#define SCE_XML_INVALID_NODE_ID  (0ULL)
	const NodeId invalidNodeId = SCE_XML_INVALID_NODE_ID;

} // namespace Dom

} // namespace Xml
} // namespace sce

#endif // defined(__cplusplus)

#include <psp2/xml/xml_attribute_list.h>
#include <psp2/xml/xml_node_types.h>
#include <psp2/xml/xml_node.h>
#include <psp2/xml/xml_node_list.h>

#endif  // _DOLCESDK_PSP2_XML_XML_TYPES_H_

