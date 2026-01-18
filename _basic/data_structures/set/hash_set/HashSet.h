#include <iostream>
#include <map>

template<typename K>
struct HashSet {
public:
	void add(const K& key) {
		_map[key] = true;
	}

	void remove(const K& key) {
		_map.erase(key);
	}

	void contains(const K& key) const {
		return _map.find(key) != _map.end();
	}

	void clear() {
		_map.clear();
	}

	size_t size() const {
		return _map.size();
	}

private:
	std::map<K, bool> _map;
};
