#include <iostream>
#include <vector>
#include <list>

template<typename K, typename V>
struct RandomHashTable {
private:
	constexpr static const size_t ONE = 1;
	constexpr static const unsigned int INIT_CAP = 4;
	constexpr static const float UPPER_LOAD_FACTOR = 0.75;
	constexpr static const float LOWER_LOAD_FACTOR = 0.125;

	// Key Value Node
	struct KVNode {
		K Key;
		V Value;
		int Index;

		KVNode(K key, V value, int index) : Key(key), Value(value), Index(index) {}
	};

public:
	RandomHashTable() : RandomHashTable(INIT_CAP) {}

	RandomHashTable(size_t capacity) : _size(0) {
		capacity = std::max(capacity, ONE);
		_table.resize(capacity);
	}

public:
	void insert(K key, V value) {
		size_t index = hash(key);
		auto& list = _table[index];
		for (auto& node : list) {
			if (node.Key == key) {
				std::cout << "===== Updating existing key: " << key << std::endl;
				node.Value = value;
				return;
			}
		}

		list.emplace_back(key, value, _keys.size());
		_keys.emplace_back(key);
		++_size;

		if (_size > _table.size() * UPPER_LOAD_FACTOR) {
			resize(_table.size() * 2);
		}
	}

	void remove(K key) {
		size_t index = hash(key);
		auto& list = _table[index];
		for (auto it = list.begin(); it != list.end(); ++it) {
			if (it->Key == key) {
				int index = it->Index;
				std::swap(_keys[index], _keys.back());
				_keys.pop_back();

				list.erase(it);
				--_size;

				if (_size < _table.size() * LOWER_LOAD_FACTOR) {
					resize(_table.size() / 2);
				}

				return;
			}
		}
	}

	const V get(K key) const {
		size_t index = hash(key);
		auto& list = _table[index];
		for (auto& node : list) {
			if (node->Key == key) {
				return node->Value;
			}
		}

		throw std::out_of_range("Key not found");
	}

	V& get(K key) {
		size_t index = hash(key);
		// std::cout << "\n\t\tGetting Key = " << key << ", Index = " << index << std::endl;
		auto& list = _table[index];
		// std::cout << "\t\tList Size = " << list.size() << std::endl;
		for (auto& node : list) {
			// std::cout << "\t\t\tChecking Node Key = " << node.Key << std::endl;
			if (node.Key == key) {
				return node.Value;
			}
		}

		throw std::out_of_range("Key not found");
	}

	std::vector<K> keys() const {
		std::vector<K> keys_list;
		for (const auto& key : _keys) {
			keys_list.push_back(key);
		}

		return keys_list;
	}

	K randomKey() const {
		if (_keys.empty()) {
			throw std::out_of_range("HashTable is empty");
		}
		int randIndex = std::rand() % _keys.size();
		return _keys[randIndex];
	}

	size_t size() const {
		return _size;
	}

private:
	unsigned int hash(K key) {
		// std::hash return size_t, make it non-negative
		// return (std::hash<K>()(key) & 0x7fffffff) % _table.size();
		return std::hash<K>()(key) % _table.size();
	}

	void resize(size_t newCapacity) {
		std::cout << "Resizing HashTable to new capacity: " << newCapacity << std::endl;
		newCapacity = std::max(newCapacity, ONE);

		// Traverse from Head to Tail and reinsert into the new HashTable
		// Keep the insertion order
		RandomHashTable<K, V> newTable(newCapacity);
		for (const auto& list : _table) {
			for (const auto& node : list) {
				newTable.insert(node.Key, node.Value);
			}
		}

		_table = std::move(newTable._table);
		_keys = std::move(newTable._keys);
	}

private:
	size_t _size;

	std::vector<std::list<KVNode>> _table;
	std::vector<K> _keys;
};
