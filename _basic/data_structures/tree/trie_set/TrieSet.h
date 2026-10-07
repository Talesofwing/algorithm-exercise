#include "TrieMap.h"

class TrieSet {
public:
	TrieSet() = default;
	TrieSet(const TrieSet&) = delete; // Disable copy constructor
	~TrieSet() = default;

public:
	TrieSet& operator=(const TrieSet&) = delete; // Disable copy assignment

public:
	void Add(const std::string& key) {
		_trieMap.Put(key, true);
	}

	void Remove(const std::string& key) {
		_trieMap.Remove(key);
	}

	bool Contains(const std::string& key) const {
		return _trieMap.Contains(key);
	}

	bool ContainsPrefix(const std::string& prefix) const {
		return _trieMap.ContainsPrefix(prefix);
	}

	bool ContainsPattern(const std::string& pattern) const {
		return _trieMap.ContainsPattern(pattern);
	}

	std::string ShortestPrefixOf(const std::string& prefix) const {
		return _trieMap.ShortestPrefixOf(prefix);
	}

	std::string LongestPrefixOf(const std::string& prefix) const {
		return _trieMap.LongestPrefixOf(prefix);
	}

	int Size() const {
		return _trieMap.Size();
	}

private:
	TrieMap<bool> _trieMap;
};
