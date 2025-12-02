#include <iostream>
#include <vector>
#include <list>

template<typename K, typename V>
struct LinkedHashTable {
private:
	constexpr static const size_t ONE = 1;
	constexpr static const unsigned int INIT_CAP = 4;
	constexpr static const float UPPER_LOAD_FACTOR = 0.75;
	constexpr static const float LOWER_LOAD_FACTOR = 0.125;

	// Key Value Node
	struct KVNode {
		K Key;
		V Value;
		KVNode* prev;
		KVNode* next;

		KVNode(K key, V value) : Key(key), Value(value), prev(nullptr), next(nullptr) {}
	};

public:
	LinkedHashTable() : LinkedHashTable(INIT_CAP) {}

	LinkedHashTable(size_t capacity) : _size(0) {
		capacity = std::max(capacity, ONE);
		_table.resize(capacity);

		_head = new KVNode(K(), V());
		_tail = new KVNode(K(), V());
		_head->next = _tail;
		_tail->prev = _head;
	}

	~LinkedHashTable() {
		// For convenience during testing, cleanup is not performed
		// In actual use, cleanup is necessary to avoid memory leaks

		// KVNode* current = _head->next;
		// while (current != _tail) {
		// 	KVNode* next = current->next;
		// 	delete current;
		// 	current = next;
		// }

		// delete _head;
		// delete _tail;
	}

public:
	void insert(K key, V value) {
		size_t index = hash(key);
		auto& list = _table[index];
		for (auto& node : list) {
			if (node->Key == key) {
				std::cout << "===== Updating existing key: " << key << std::endl;
				node->Value = value;
				return;
			}
		}

		KVNode* node = new KVNode(key, value);
		addLastNode(node);
		list.emplace_back(node);
		++_size;

		if (_size > _table.size() * UPPER_LOAD_FACTOR) {
			resize(_table.size() * 2);
		}
	}

	void remove(K key) {
		size_t index = hash(key);
		auto& list = _table[index];
		for (auto it = list.begin(); it != list.end(); ++it) {
			if ((*it)->Key == key) {
				list.erase(it);
				removeNode(*it);
				delete (*it);
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
		auto& list = _table[index];
		for (auto& node : list) {
			if (node->Key == key) {
				return node->Value;
			}
		}

		throw std::out_of_range("Key not found");
	}

	std::vector<K> keys() const {
		std::vector<K> keys_list;
		for (KVNode* current = _head->next; current != _tail; current = current->next) {
			keys_list.emplace_back(current->Key);
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

	void addLastNode(KVNode* node) {
		node->prev = _tail->prev;
		node->next = _tail;
		_tail->prev->next = node;
		_tail->prev = node;
	}

	void removeNode(KVNode* node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	void resize(size_t newCapacity) {
		newCapacity = std::max(newCapacity, ONE);

		// Traverse from Head to Tail and reinsert into the new HashTable
		// Keep the insertion order
		LinkedHashTable<K, V> newTable(newCapacity);
		KVNode* current = _head->next;
		while (current != _tail) {
			newTable.insert(current->Key, current->Value);
			current = current->next;
		}

		_table = std::move(newTable._table);
	}

private:
	size_t _size;

	KVNode* _head;
	KVNode* _tail;

	std::vector<std::list<KVNode*>> _table;
};
