#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <concepts>

#include "TreeMap.h"

// Base on TreeMap
template<typename K>
class TreeSet {
private:
public:
	TreeSet() {}
	TreeSet(const TreeSet&) = delete; // Disable copy constructor

	~TreeSet() {}

public:
	TreeSet& operator=(const TreeSet&) = delete; // Disable copy assignment

public:
	void Insert(K key) {
		_map.Insert(key, true);
	}

	void Remove(K key) {
		_map.Remove(key);
	}

	void RemoveMin() {
		_map.RemoveMin();
	}

	void RemoveMax() {
		_map.RemoveMax();
	}

	bool Contains(K key) {
		return _map.Contains(key);
	}

	int Size() const {
		return _map.Size();
	}

	bool IsEmpty() const {
		return _map.IsEmpty();
	}

	std::vector<K> Keys() {
		return _map.Keys();
	}

	std::vector<K> Keys(K low, K high) {
		return _map.Keys(low, high);
	}

	K MinKey() {
		return _map.MinKey();
	}

	K MaxKey() {
		return _map.MaxKey();
	}

	const K* FloorKey(K key) {
		return _map.FloorKey(key);
	}

	const K* CeilingKey(K key) {
		return _map.CeilingKey(key);
	}

	K Select(int i) {
		return _map.Select(i);
	}

	int Rank(K key) {
		return _map.Rank(key);
	}

private:
	TreeMap<K, bool> _map;
};
