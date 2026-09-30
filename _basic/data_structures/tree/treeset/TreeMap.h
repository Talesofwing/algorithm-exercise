#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <concepts>

template<typename T>
concept TreeMapKey = std::copyable<T> && requires(const T & a, const T & b) {
	{ a < b } -> std::convertible_to<bool>;
	{ a > b } -> std::convertible_to<bool>;
	{ a <= b } -> std::convertible_to<bool>;
};

// Base on BST
template<TreeMapKey K, typename V>
class TreeMap {
private:
	struct Node {
		K Key;
		V Value;
		Node* Left;
		Node* Right;
		int Size;

		Node(K key, V value) : Key(key), Value(value), Left(nullptr), Right(nullptr), Size(1) {}
	};

public:
	TreeMap() : _root(nullptr) {}
	TreeMap(const TreeMap&) = delete; // Disable copy constructor

	~TreeMap() {
		Destroy(_root);
	}

public:
	TreeMap& operator=(const TreeMap&) = delete; // Disable copy assignment

public:
	void Insert(K key, V value) {
		_root = Insert_Internal(_root, key, value);
	}

	V* Get(K key) {
		Node* node = Get_Internal(_root, key);
		if (node == nullptr) {
			return nullptr;
		}

		return &(node->Value);
	}

	void Remove(K key) {
		_root = Remove_Internal(_root, key);
	}

	void RemoveMin() {
		_root = RemoveMin_Internal(_root);
	}

	void RemoveMax() {
		_root = RemoveMax_Internal(_root);
	}

	const K* FloorKey(K key) {
		return FloorKey_Internal(_root, key) ? &(FloorKey_Internal(_root, key)->Key) : nullptr;
	}

	const K* CeilingKey(K key) {
		return CeilingKey_Internal(_root, key) ? &(CeilingKey_Internal(_root, key)->Key) : nullptr;
	}

	int Rank(K key) {
		return GetRank_Internal(_root, key);
	}

	K Select(int i) {
		if (i < 0 || i >= Size()) {
			throw std::out_of_range("Index out of range");
		}

		return Select_Internal(_root, i)->Key;
	}

	K MinKey() {
		Node* minNode = GetMin_Internal(_root);
		if (minNode == nullptr) {
			throw std::runtime_error("Tree is empty");
		}

		return minNode->Key;
	}

	K MaxKey() {
		Node* maxNode = GetMax_Internal(_root);
		if (maxNode == nullptr) {
			throw std::runtime_error("Tree is empty");
		}

		return maxNode->Key;
	}

	bool Contains(K key) {
		return Get_Internal(_root, key) != nullptr;
	}

	std::vector<K> Keys() {
		return Keys_Internal(_root);
	}

	std::vector<K> Keys(K low, K high) {
		return Keys_Internal(_root, low, high);
	}

	int Size() const {
		return GetSize_Internal(_root);
	}

	bool IsEmpty() const {
		return Size() == 0;
	}

private:
	Node* Insert_Internal(Node* node, K key, V value) {
		if (node == nullptr) {
			return new Node(key, value);
		}

		if (key < node->Key) {
			node->Left = Insert_Internal(node->Left, key, value);
		} else if (key > node->Key) {
			node->Right = Insert_Internal(node->Right, key, value);
		} else {
			node->Value = value; // Update existing key
		}

		node->Size = 1 + GetSize_Internal(node->Left) + GetSize_Internal(node->Right);

		return node;
	}

	Node* Get_Internal(Node* node, K key) {
		if (node == nullptr) {
			return nullptr;
		}

		if (key < node->Key) {
			return Get_Internal(node->Left, key);
		} else if (key > node->Key) {
			return Get_Internal(node->Right, key);
		}

		return node;
	}

	Node* GetMin_Internal(Node* node) {
		if (node == nullptr) {
			return nullptr;
		}

		while (node->Left != nullptr) {
			node = node->Left;
		}

		return node;
	}

	Node* GetMax_Internal(Node* node) {
		if (node == nullptr) {
			return nullptr;
		}

		while (node->Right != nullptr) {
			node = node->Right;
		}

		return node;
	}

	Node* Remove_Internal(Node* node, K key) {
		if (node == nullptr) {
			return nullptr;
		}

		if (key < node->Key) {
			node->Left = Remove_Internal(node->Left, key);
		} else if (key > node->Key) {
			node->Right = Remove_Internal(node->Right, key);
		} else {
			if (node->Left == nullptr) {
				Node* rightChild = node->Right;
				delete node;
				return rightChild;
			} else if (node->Right == nullptr) {
				Node* leftChild = node->Left;
				delete node;
				return leftChild;
			} else {
				Node* minNode = GetMin_Internal(node->Right);
				node->Key = minNode->Key;
				node->Value = minNode->Value;
				node->Right = RemoveMin_Internal(node->Right);
			}
		}

		node->Size = 1 + GetSize_Internal(node->Left) + GetSize_Internal(node->Right);

		return node;
	}

	Node* RemoveMin_Internal(Node* node) {
		if (node == nullptr) {
			return nullptr;
		}

		if (node->Left == nullptr) {
			Node* rightChild = node->Right;
			delete node;
			return rightChild;
		}

		node->Left = RemoveMin_Internal(node->Left);
		node->Size = 1 + GetSize_Internal(node->Left) + GetSize_Internal(node->Right);
		return node;
	}

	Node* RemoveMax_Internal(Node* node) {
		if (node == nullptr) {
			return nullptr;
		}

		if (node->Right == nullptr) {
			Node* leftChild = node->Left;
			delete node;
			return leftChild;
		}

		node->Right = RemoveMax_Internal(node->Right);
		node->Size = 1 + GetSize_Internal(node->Left) + GetSize_Internal(node->Right);
		return node;
	}

	std::vector<K> Keys_Internal(Node* node) {
		std::vector<K> keys;
		if (node == nullptr) {
			return keys;
		}

		std::vector<K> leftKeys = Keys_Internal(node->Left);
		keys.insert(keys.end(), leftKeys.begin(), leftKeys.end());

		keys.push_back(node->Key);

		std::vector<K> rightKeys = Keys_Internal(node->Right);
		keys.insert(keys.end(), rightKeys.begin(), rightKeys.end());

		return keys;
	}

	std::vector<K> Keys_Internal(Node* node, K low, K high) {
		std::vector<K> keys;
		if (node == nullptr) {
			return keys;
		}

		if (low < node->Key) {
			std::vector<K> leftKeys = Keys_Internal(node->Left, low, high);
			keys.insert(keys.end(), leftKeys.begin(), leftKeys.end());
		}

		if (low <= node->Key && node->Key <= high) {
			keys.push_back(node->Key);
		}

		if (high > node->Key) {
			std::vector<K> rightKeys = Keys_Internal(node->Right, low, high);
			keys.insert(keys.end(), rightKeys.begin(), rightKeys.end());
		}

		return keys;
	}

	Node* FloorKey_Internal(Node* node, K key) {
		if (node == nullptr) {
			return nullptr;
		}

		if (key < node->Key) {
			return FloorKey_Internal(node->Left, key);
		} else if (key > node->Key) {
			Node* rightFloor = FloorKey_Internal(node->Right, key);
			return rightFloor ? rightFloor : node;
		} else {
			return node;
		}
	}

	Node* CeilingKey_Internal(Node* node, K key) {
		if (node == nullptr) {
			return nullptr;
		}

		if (key > node->Key) {
			return CeilingKey_Internal(node->Right, key);
		} else if (key < node->Key) {
			Node* leftCeiling = CeilingKey_Internal(node->Left, key);
			return leftCeiling ? leftCeiling : node;
		} else {
			return node;
		}
	}

	int GetSize_Internal(Node* node) const {
		return node ? node->Size : 0;
	}

	int GetRank_Internal(Node* node, K key) {
		if (node == nullptr) {
			return 0;
		}

		if (key < node->Key) {
			return GetRank_Internal(node->Left, key);
		} else if (key > node->Key) {
			return 1 + GetSize_Internal(node->Left) + GetRank_Internal(node->Right, key);
		} else {
			return GetSize_Internal(node->Left);
		}
	}

	Node* Select_Internal(Node* node, int i) {
		if (node == nullptr) {
			return nullptr;
		}

		int leftSize = GetSize_Internal(node->Left);
		if (i < leftSize) {
			return Select_Internal(node->Left, i);
		} else if (i > leftSize) {
			return Select_Internal(node->Right, i - leftSize - 1);
		} else {
			return node;
		}
	}

	/// @brief Release all nodes in the tree
	void Destroy(Node* node) {
		if (node == nullptr) {
			return;
		}

		Destroy(node->Left);
		Destroy(node->Right);
		delete node;
	}

private:
	Node* _root;
};
