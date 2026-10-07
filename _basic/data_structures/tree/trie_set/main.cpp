#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "TrieMap.h"

void AssertStringVectorEqual(
	std::vector<std::string> actual,
	std::vector<std::string> expected) {
	// TrieMap uses unordered_map, so traversal order is not guaranteed.
	std::sort(actual.begin(), actual.end());
	std::sort(expected.begin(), expected.end());

	assert(actual == expected);
}

int main() {
	TrieMap<int> trie;

	// ============================================================
	// Initial state
	// ============================================================

	assert(trie.Size() == 0);

	assert(!trie.Contains("cat"));
	assert(!trie.ContainsPrefix("cat"));
	assert(!trie.ContainsPrefix(""));
	assert(!trie.ContainsPattern("cat"));

	assert(trie.Get("cat") == nullptr);

	assert(trie.Keys().empty());
	assert(trie.KeysWithPrefix("ca").empty());
	assert(trie.KeysWithPattern("c..").empty());

	// ============================================================
	// Put
	// ============================================================

	trie.Put("cat", 10);
	trie.Put("car", 20);
	trie.Put("card", 30);
	trie.Put("care", 40);
	trie.Put("dog", 50);
	trie.Put("door", 60);

	assert(trie.Size() == 6);

	// ============================================================
	// Contains
	// ============================================================

	assert(trie.Contains("cat"));
	assert(trie.Contains("car"));
	assert(trie.Contains("card"));
	assert(trie.Contains("care"));
	assert(trie.Contains("dog"));
	assert(trie.Contains("door"));

	assert(!trie.Contains("ca"));
	assert(!trie.Contains("do"));
	assert(!trie.Contains("category"));
	assert(!trie.Contains("apple"));

	// ============================================================
	// Get
	// ============================================================

	assert(trie.Get("cat") != nullptr);
	assert(*trie.Get("cat") == 10);

	assert(trie.Get("car") != nullptr);
	assert(*trie.Get("car") == 20);

	assert(trie.Get("door") != nullptr);
	assert(*trie.Get("door") == 60);

	assert(trie.Get("ca") == nullptr);
	assert(trie.Get("do") == nullptr);
	assert(trie.Get("apple") == nullptr);

	// ============================================================
	// Update existing value
	// ============================================================

	trie.Put("cat", 100);

	assert(trie.Size() == 6);
	assert(*trie.Get("cat") == 100);

	// ============================================================
	// Modify value through Get()
	// ============================================================

	{
		int* value = trie.Get("cat");

		assert(value != nullptr);

		*value = 123;

		assert(*trie.Get("cat") == 123);
	}

	// ============================================================
	// ContainsPrefix
	// ============================================================

	assert(trie.ContainsPrefix("c"));
	assert(trie.ContainsPrefix("ca"));
	assert(trie.ContainsPrefix("cat"));
	assert(trie.ContainsPrefix("car"));
	assert(trie.ContainsPrefix("card"));

	assert(trie.ContainsPrefix("d"));
	assert(trie.ContainsPrefix("do"));
	assert(trie.ContainsPrefix("dog"));
	assert(trie.ContainsPrefix("doo"));

	assert(!trie.ContainsPrefix("cow"));
	assert(!trie.ContainsPrefix("apple"));

	// Empty string is a prefix of every string.
	// Since trie is not empty, this should be true.
	assert(trie.ContainsPrefix(""));

	// ============================================================
	// ShortestPrefixOf
	// ============================================================

	// "cat" exists.
	assert(trie.ShortestPrefixOf("category") == "cat");

	// "car" and "card" both exist.
	// Shortest is "car".
	assert(trie.ShortestPrefixOf("cardinal") == "car");

	// "car" and "care" both exist.
	// Shortest is "car".
	assert(trie.ShortestPrefixOf("careful") == "car");

	assert(trie.ShortestPrefixOf("doggy") == "dog");

	assert(trie.ShortestPrefixOf("doorbell") == "door");

	assert(trie.ShortestPrefixOf("apple") == "");

	// Query itself is a key.
	assert(trie.ShortestPrefixOf("cat") == "cat");

	// ============================================================
	// LongestPrefixOf
	// ============================================================

	assert(trie.LongestPrefixOf("category") == "cat");

	// "car" and "card" both match.
	assert(trie.LongestPrefixOf("cardinal") == "card");

	// "car" and "care" both match.
	assert(trie.LongestPrefixOf("careful") == "care");

	assert(trie.LongestPrefixOf("doggy") == "dog");

	assert(trie.LongestPrefixOf("doorbell") == "door");

	assert(trie.LongestPrefixOf("apple") == "");

	// Query itself is a key.
	assert(trie.LongestPrefixOf("card") == "card");

	// ============================================================
	// Keys
	// ============================================================

	AssertStringVectorEqual(
		trie.Keys(),
		{
			"cat",
			"car",
			"card",
			"care",
			"dog",
			"door"
		});

	// ============================================================
	// KeysWithPrefix
	// ============================================================

	AssertStringVectorEqual(
		trie.KeysWithPrefix("ca"),
		{
			"cat",
			"car",
			"card",
			"care"
		});

	AssertStringVectorEqual(
		trie.KeysWithPrefix("car"),
		{
			"car",
			"card",
			"care"
		});

	AssertStringVectorEqual(
		trie.KeysWithPrefix("card"),
		{
			"card"
		});

	AssertStringVectorEqual(
		trie.KeysWithPrefix("do"),
		{
			"dog",
			"door"
		});

	AssertStringVectorEqual(
		trie.KeysWithPrefix("door"),
		{
			"door"
		});

	AssertStringVectorEqual(
		trie.KeysWithPrefix("apple"),
		{});

	// Empty prefix means all keys.
	AssertStringVectorEqual(
		trie.KeysWithPrefix(""),
		{
			"cat",
			"car",
			"card",
			"care",
			"dog",
			"door"
		});

	// ============================================================
	// ContainsPattern
	//
	// '.' matches exactly ONE character.
	// ============================================================

	assert(trie.ContainsPattern("cat"));
	assert(trie.ContainsPattern("car"));

	assert(trie.ContainsPattern("c.t"));   // cat
	assert(trie.ContainsPattern("c.r"));   // car

	assert(trie.ContainsPattern("c.."));   // cat / car
	assert(trie.ContainsPattern("c..."));  // card / care

	assert(trie.ContainsPattern("d.g"));   // dog
	assert(trie.ContainsPattern("d..r"));  // door

	assert(trie.ContainsPattern(".at"));   // cat
	assert(trie.ContainsPattern(".ar"));   // car
	assert(trie.ContainsPattern("..."));   // cat / car / dog

	assert(!trie.ContainsPattern(".."));
	assert(!trie.ContainsPattern("....."));
	assert(!trie.ContainsPattern("z.."));
	assert(!trie.ContainsPattern("c.x"));
	assert(!trie.ContainsPattern("apple"));

	// ============================================================
	// KeysWithPattern
	// ============================================================

	AssertStringVectorEqual(
		trie.KeysWithPattern("c.t"),
		{
			"cat"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("c.r"),
		{
			"car"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("c.."),
		{
			"cat",
			"car"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("c..."),
		{
			"card",
			"care"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("d.g"),
		{
			"dog"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("d..r"),
		{
			"door"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("..."),
		{
			"cat",
			"car",
			"dog"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("...."),
		{
			"card",
			"care",
			"door"
		});

	AssertStringVectorEqual(
		trie.KeysWithPattern("z.."),
		{});

	// ============================================================
	// const Get
	// ============================================================

	{
		const TrieMap<int>& constTrie = trie;

		const int* value = constTrie.Get("dog");

		assert(value != nullptr);
		assert(*value == 50);

		assert(constTrie.Get("apple") == nullptr);
	}

	// ============================================================
	// Remove nonexistent key
	// ============================================================

	{
		int oldSize = trie.Size();

		trie.Remove("apple");

		assert(trie.Size() == oldSize);
	}

	// ============================================================
	// Remove path that exists but is not a key
	// ============================================================

	{
		int oldSize = trie.Size();

		trie.Remove("ca");

		assert(trie.Size() == oldSize);
		assert(trie.Contains("cat"));
		assert(trie.Contains("car"));
	}

	// ============================================================
	// Remove leaf key
	// ============================================================

	trie.Remove("card");

	assert(!trie.Contains("card"));

	assert(trie.Contains("car"));
	assert(trie.Contains("care"));

	assert(trie.Size() == 5);

	// ============================================================
	// Remove key that is also prefix of another key
	// ============================================================

	trie.Remove("car");

	assert(!trie.Contains("car"));

	// "care" still exists.
	assert(trie.Contains("care"));

	// Path "car" still exists because "care" uses it.
	assert(trie.ContainsPrefix("car"));

	assert(trie.Size() == 4);

	// ============================================================
	// Remove remaining branch
	// ============================================================

	trie.Remove("care");

	assert(!trie.Contains("care"));

	// No more keys beginning with "car".
	assert(!trie.ContainsPrefix("car"));

	assert(trie.Size() == 3);

	// Remaining:
	// cat
	// dog
	// door

	AssertStringVectorEqual(
		trie.Keys(),
		{
			"cat",
			"dog",
			"door"
		});

	// ============================================================
	// Remove "dog"
	// ============================================================

	trie.Remove("dog");

	assert(!trie.Contains("dog"));

	// "do" still exists because "door" remains.
	assert(trie.ContainsPrefix("do"));

	assert(trie.Contains("door"));

	assert(trie.Size() == 2);

	// ============================================================
	// Remove "door"
	// ============================================================

	trie.Remove("door");

	assert(!trie.Contains("door"));

	// Entire "d" branch should be pruned.
	assert(!trie.ContainsPrefix("d"));
	assert(!trie.ContainsPrefix("do"));

	assert(trie.Size() == 1);

	// ============================================================
	// Remove final key
	// ============================================================

	trie.Remove("cat");

	assert(trie.Size() == 0);

	assert(!trie.Contains("cat"));
	assert(!trie.ContainsPrefix("c"));
	assert(!trie.ContainsPrefix(""));
	assert(trie.Keys().empty());

	// ============================================================
	// Empty string key
	// ============================================================

	trie.Put("", 999);

	assert(trie.Size() == 1);

	assert(trie.Contains(""));
	assert(trie.Get("") != nullptr);
	assert(*trie.Get("") == 999);

	assert(trie.ContainsPrefix(""));

	AssertStringVectorEqual(
		trie.Keys(),
		{
			""
		});

	assert(trie.ContainsPattern(""));

	AssertStringVectorEqual(
		trie.KeysWithPattern(""),
		{
			""
		});

	// Empty string key is the shortest possible prefix.
	assert(trie.ShortestPrefixOf("anything") == "");

	trie.Remove("");

	assert(trie.Size() == 0);
	assert(!trie.Contains(""));
	assert(trie.Get("") == nullptr);

	// ============================================================
	// Finished
	// ============================================================

	std::cout << "All TrieMap tests passed!" << std::endl;

	return 0;
}
