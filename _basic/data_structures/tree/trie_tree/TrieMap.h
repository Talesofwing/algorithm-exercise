#include <vector>
#include <unordered_map>
#include <optional>
#include <utility>
#include <string>
#include <memory>

template<typename T>
class TrieMap {
private:
	struct Node {
	public:
		std::optional<T> Value;
		std::unordered_map<char, std::unique_ptr<Node>> Children;
	};

public:
	TrieMap() = default;
	TrieMap(const TrieMap&) = delete; // Disable copy constructor
	~TrieMap() = default;

public:
	TrieMap& operator=(const TrieMap&) = delete; // Disable copy assignment

public:
	void Put(const std::string& key, T value) {
		Node& node = GetOrCreateNode(key);

		if (!node.Value) {
			++_size;
		}

		node.Value = std::move(value);
	}

	void Remove(const std::string& key) {
		std::vector<std::pair<Node*, char>> path;
		path.reserve(key.length());
		Node* node = &_root;

		for (char c : key) {
			auto it = node->Children.find(c);
			if (it == node->Children.end()) {
				return;
			}
			path.emplace_back(node, c);
			node = it->second.get();
		}

		if (!node->Value) {
			return;
		}

		node->Value.reset(); // Remove the value associated with the key
		--_size;

		for (auto it = path.rbegin(); it != path.rend(); ++it) {
			Node* parent = it->first;
			char c = it->second;

			if (node->Children.empty() && !node->Value) {
				parent->Children.erase(c);
				node = parent;
			} else {
				break;
			}
		}
	}

	T* Get(const std::string& key) {
		Node* node = GetNode(key);
		return node && node->Value ? &*node->Value : nullptr;
	}

	const T* Get(const std::string& key) const {
		const Node* node = GetNode(key);
		return node && node->Value ? &*node->Value : nullptr;
	}

	// Check if the trie contains the given key.
	bool Contains(const std::string& key) const {
		const Node* node = GetNode(key);
		return node && node->Value;
	}

	// Check if there is any key in the trie that starts with the given prefix.
	bool ContainsPrefix(const std::string& prefix) const {
		if (prefix.empty()) {
			return _size > 0;
		}

		return GetNode(prefix) != nullptr;
	}

	// Check if there is any key in the trie that matches the given pattern, where '.' can match any character.
	bool ContainsPattern(const std::string& pattern) const {
		return ContainsPattern_Internal(&_root, pattern, 0);
	}

	// Returns the shortest prefix of the given prefix that exists in the trie. If no such prefix exists, returns an empty string.
	std::string ShortestPrefixOf(const std::string& prefix) const {
		const Node* node = &_root;

		if (node->Value) {
			return "";
		}

		for (int i = 0; i < prefix.size(); ++i) {
			char c = prefix[i];
			auto it = node->Children.find(c);
			if (it == node->Children.end()) {
				return "";
			}

			node = it->second.get();

			if (node->Value) {
				return prefix.substr(0, i + 1);
			}
		}

		return "";
	}

	// Returns the longest prefix of the given prefix that exists in the trie. If no such prefix exists, returns an empty string.
	std::string LongestPrefixOf(const std::string& prefix) const {
		const Node* node = &_root;

		int max_length = 0;

		for (int i = 0; i < prefix.size(); ++i) {
			char c = prefix[i];
			auto it = node->Children.find(c);
			if (it == node->Children.end()) {
				break;
			}
			node = it->second.get();

			if (node->Value) {
				max_length = i + 1;
			}
		}

		return prefix.substr(0, max_length);
	}

	std::vector<std::string> Keys() const {
		std::vector<std::string> result;
		std::string path;

		GetKeys(_root, path, result);

		return result;
	}

	std::vector<std::string> KeysWithPrefix(const std::string& prefix) const {
		return GetKeysWithPrefix(prefix);
	}

	// Returns all keys in the trie that match the given pattern, where '.' can match any character.
	std::vector<std::string> KeysWithPattern(const std::string& pattern) const {
		std::vector<std::string> result;
		std::string path;

		GetKeysWithPattern(_root, pattern, 0, path, result);

		return result;
	}

	int Size() const {
		return _size;
	}

private:
	Node& GetOrCreateNode(const std::string& key) {
		Node* node = &_root;

		for (char c : key) {
			auto& child = node->Children[c];

			if (!child) {
				child = std::make_unique<Node>();
			}

			node = child.get();
		}

		return *node;
	}

	Node* GetNode(const std::string& key) {
		return const_cast<Node*>(
			std::as_const(*this).GetNode(key)
		);
	}

	const Node* GetNode(const std::string& key) const {
		const Node* node = &_root;

		for (char c : key) {
			auto it = node->Children.find(c);
			if (it == node->Children.end()) {
				return nullptr;
			}
			node = it->second.get();
		}

		return node;
	}

	bool ContainsPattern_Internal(const Node* node, const std::string& pattern, size_t index) const {
		if (!node) {
			return false;
		}

		if (index == pattern.size()) {
			return node->Value.has_value();
		}

		char c = pattern[index];
		if (c != '.') {
			auto it = node->Children.find(c);
			if (it == node->Children.end()) {
				return false;
			}

			return ContainsPattern_Internal(it->second.get(), pattern, index + 1);
		}

		// '.' -> Match any character
		for (const auto& [key, child] : node->Children) {
			if (ContainsPattern_Internal(child.get(), pattern, index + 1)) {
				// Found a match in one of the children
				return true;
			}
		}

		return false;
	}

	void GetKeys(const Node& node, std::string& path, std::vector<std::string>& result) const {
		if (node.Value) {
			result.push_back(path);
		}

		for (const auto& [key, child] : node.Children) {
			path.push_back(key);
			GetKeys(*child, path, result);
			path.pop_back();
		}
	}

	std::vector<std::string> GetKeysWithPrefix(const std::string& prefix) const {
		std::vector<std::string> result;
		const Node* node = GetNode(prefix);
		if (!node) {
			return result;
		}

		std::string path = prefix;
		GetKeys(*node, path, result);

		return result;
	}

	void GetKeysWithPattern(const Node& node, const std::string& pattern, size_t index, std::string& path, std::vector<std::string>& result) const {
		if (index == pattern.size()) {
			if (node.Value) {
				result.push_back(path);
			}
			return;
		}

		char c = pattern[index];
		if (c != '.') {
			auto it = node.Children.find(c);
			if (it != node.Children.end()) {
				path.push_back(c);
				GetKeysWithPattern(*it->second, pattern, index + 1, path, result);
				path.pop_back();
			}
		} else {
			for (const auto& [key, child] : node.Children) {
				path.push_back(key);
				GetKeysWithPattern(*child, pattern, index + 1, path, result);
				path.pop_back();
			}
		}
	}

private:
	Node _root;
	int _size = 0;
};
