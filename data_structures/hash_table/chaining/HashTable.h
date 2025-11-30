#include <iostream>
#include <vector>
#include <list>

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
		size_t index = hash(key);
		auto& list = _table[index];
		for (auto& node : list) {
			if (node.Key == key) {
				std::cout << "===== Updating existing key: " << key << std::endl;
				node.Value = value;
				return;
			}
		}

		list.emplace_back(key, value);
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
			if (node.Key == key) {
				return node.Value;
			}
		}

		throw std::out_of_range("Key not found");
	}

	V& get(K key) {
		size_t index = hash(key);
		auto& list = _table[index];
		for (auto& node : list) {
			if (node.Key == key) {
				return node.Value;
			}
		}

		throw std::out_of_range("Key not found");
	}

	std::list<K> keys() const {
		std::list<K> keys_list;
		for (const auto& bucket : _table) {
			for (const auto& node : bucket) {
				keys_list.push_back(node.Key);
			}
		}
		return keys_list;
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
		newCapacity = std::max(newCapacity, ONE);

		// Cannot use a new std::vector<std::list<KVNode>> because it would affect the hash calculation.
		// A new HashTable must be used in order to compute the correct hash values.
		HashTable<K, V> newTable(newCapacity);
		for (const auto& list : _table) {
			for (const auto& node : list) {
				newTable.insert(node.Key, node.Value);
			}
		}

		_table = std::move(newTable._table);
	}

private:
	size_t _size;

	std::vector<std::list<KVNode>> _table;
};
