#include <cassert>
#include <iostream>

#include "TrieSet.h"

void TestTrieSet() {
	TrieSet trieSet;

	// Initial state
	assert(trieSet.Size() == 0);
	assert(!trieSet.Contains("cat"));
	assert(!trieSet.ContainsPrefix("ca"));
	assert(!trieSet.ContainsPattern("c.t"));

	// Add
	trieSet.Add("cat");
	trieSet.Add("car");
	trieSet.Add("card");
	trieSet.Add("care");
	trieSet.Add("dog");
	trieSet.Add("door");

	assert(trieSet.Size() == 6);

	// Contains
	assert(trieSet.Contains("cat"));
	assert(trieSet.Contains("car"));
	assert(trieSet.Contains("card"));
	assert(trieSet.Contains("care"));
	assert(trieSet.Contains("dog"));
	assert(trieSet.Contains("door"));

	assert(!trieSet.Contains("ca"));
	assert(!trieSet.Contains("do"));
	assert(!trieSet.Contains("apple"));

	// Adding duplicate key should not increase size
	trieSet.Add("cat");
	assert(trieSet.Size() == 6);

	// Prefix
	assert(trieSet.ContainsPrefix("c"));
	assert(trieSet.ContainsPrefix("ca"));
	assert(trieSet.ContainsPrefix("car"));
	assert(trieSet.ContainsPrefix("do"));
	assert(!trieSet.ContainsPrefix("apple"));

	// Pattern
	assert(trieSet.ContainsPattern("c.t"));   // cat
	assert(trieSet.ContainsPattern("c.r"));   // car
	assert(trieSet.ContainsPattern("c.."));   // cat / car
	assert(trieSet.ContainsPattern("c..."));  // card / care
	assert(trieSet.ContainsPattern("d.g"));   // dog
	assert(trieSet.ContainsPattern("d..r"));  // door

	assert(!trieSet.ContainsPattern("z.."));
	assert(!trieSet.ContainsPattern("....."));

	// Shortest prefix
	assert(trieSet.ShortestPrefixOf("category") == "cat");
	assert(trieSet.ShortestPrefixOf("cardinal") == "car");
	assert(trieSet.ShortestPrefixOf("careful") == "car");
	assert(trieSet.ShortestPrefixOf("doggy") == "dog");
	assert(trieSet.ShortestPrefixOf("apple") == "");

	// Longest prefix
	assert(trieSet.LongestPrefixOf("category") == "cat");
	assert(trieSet.LongestPrefixOf("cardinal") == "card");
	assert(trieSet.LongestPrefixOf("careful") == "care");
	assert(trieSet.LongestPrefixOf("doorbell") == "door");
	assert(trieSet.LongestPrefixOf("apple") == "");

	// Remove leaf
	trieSet.Remove("card");

	assert(!trieSet.Contains("card"));
	assert(trieSet.Contains("car"));
	assert(trieSet.Contains("care"));
	assert(trieSet.Size() == 5);

	// Remove key which is also a prefix
	trieSet.Remove("car");

	assert(!trieSet.Contains("car"));
	assert(trieSet.Contains("care"));
	assert(trieSet.ContainsPrefix("car"));
	assert(trieSet.Size() == 4);

	// Remove nonexistent key
	trieSet.Remove("apple");
	assert(trieSet.Size() == 4);

	// Remove remaining branch
	trieSet.Remove("care");

	assert(!trieSet.Contains("care"));
	assert(!trieSet.ContainsPrefix("car"));
	assert(trieSet.Size() == 3);

	// Empty string
	trieSet.Add("");

	assert(trieSet.Contains(""));
	assert(trieSet.Size() == 4);

	trieSet.Remove("");

	assert(!trieSet.Contains(""));
	assert(trieSet.Size() == 3);

	std::cout << "TrieSet tests passed!\n";
}

int main() {
	TestTrieSet();

	std::cout << "All tests passed!\n";
	return 0;
}
