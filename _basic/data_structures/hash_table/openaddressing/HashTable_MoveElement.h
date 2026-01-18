#include <iostream>
#include <vector>
#include <list>

/*
	After deletion, move other elements to fill the empty slot.
*/

template<typename K, typename V>
struct HashTable {
private:
	constexpr static const size_t ONE = 1;
	constexpr static const unsigned int INIT_CAP = 4;
	constexpr static const float UPPER_LOAD_FACTOR = 0.75;
	constexpr static const float LOWER_LOAD_FACTOR = 0.125;

	// Key Value Node
	struct KVNode {
		K Key;
		V Value;

		KVNode(K key, V value) : Key(key), Value(value) {}
	};

public:
	HashTable() : HashTable(INIT_CAP) {}

	HashTable(size_t capacity) : _size(0) {
		capacity = std::max(capacity, ONE);
		_table.resize(capacity);
	}

public:
	void insert(K key, V value) {
		std::cout << "===== Inserting key: " << key << ", value: " << value << std::endl;
		int index = getKeyIndex(key);
		if (_table[index] != nullptr) {
			std::cout << "===== Updating existing key: " << key << " =====" << std::endl;
			_table[index]->Value = value;
			return;
		}

		// Is new key
		_table[index] = new KVNode(key, value);
		++_size;

		if (_size > _table.size() * UPPER_LOAD_FACTOR) {
			resize(_table.size() * 2);
		}
	}

	void remove(K key) {
		std::cout << "===== Removing key: " << key << std::endl;
		size_t index = getKeyIndex(key);
		if (_table[index] == nullptr) {
			std::cout << "===== Key not found: " << key << std::endl;
			return;
		}

		delete _table[index];
		_table[index] = nullptr;
		--_size;

		if (_size < _table.size() * LOWER_LOAD_FACTOR) {
			resize(_table.size() / 2);
		} else {
			// Rehash while preserving element continuity.
			index = (index + 1) % _table.size();
			while (_table[index] != nullptr) {
				KVNode* nodeToRehash = _table[index];
				_table[index] = nullptr;
				--_size;
				insert(nodeToRehash->Key, nodeToRehash->Value);
				delete nodeToRehash;
				index = (index + 1) % _table.size();
			}
		}
	}

	V& get(K key) {
		size_t index = getKeyIndex(key);
		if (_table[index] != nullptr) {
			return _table[index]->Value;
		}

		throw std::out_of_range("Key not found");
	}

	std::list<K> keys() const {
		std::list<K> keys;
		for (KVNode* node : _table) {
			if (node != nullptr) {
				keys.push_back(node->Key);
			}
		}

		return keys;
	}

	size_t size() const {
		return _size;
	}

private:
	size_t getKeyIndex(K key) {
		size_t index;
		for (index = hash(key); _table[index] != nullptr; index = (index + 1) % _table.size()) {
			if (_table[index]->Key == key) {
				return index;
			}
		}

		return index;
	}

	unsigned int hash(K key) {
	// std::hash return size_t, make it non-negative
	// return (std::hash<K>()(key) & 0x7fffffff) % _table.size();
		return std::hash<K>()(key) % _table.size();
	}

	void resize(size_t newCapacity) {
		std::cout << "===== Resizing table to capacity: " << newCapacity << " =====" << std::endl;
		newCapacity = std::max(newCapacity, ONE);

		// Cannot use a new std::vector<std::list<KVNode>> because it would affect the hash calculation.
		// A new HashTable must be used in order to compute the correct hash values.
		HashTable<K, V> newTable(newCapacity);
		for (KVNode* node : _table) {
			if (node != nullptr) {
				newTable.insert(node->Key, node->Value);
			}
		}

		_table = std::move(newTable._table);
	}

private:
	size_t _size;

	std::vector<KVNode*> _table;
};
