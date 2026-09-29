#include <iostream>
#include <stdexcept>
#include <vector>

#include "TreeMap.h"

using namespace std;

void Check(bool condition, const char* message) {
	if (!condition) {
		throw runtime_error(message);
	}
}

template<typename Exception, typename Callable>
void ExpectThrows(Callable&& callable, const char* message) {
	try {
		callable();
	} catch (const Exception&) {
		return;
	}

	throw runtime_error(message);
}

int main() {
	try {
		TreeMap<int, int> map;

		Check(map.IsEmpty(), "New tree should be empty");
		Check(map.size() == 0, "New tree size should be zero");
		Check(map.Keys().empty(), "Keys of an empty tree should be empty");
		Check(map.Get(1) == nullptr, "Get on an empty tree should return nullptr");
		Check(!map.Contains(1), "Empty tree should not contain keys");
		Check(map.FloorKey(1) == nullptr, "FloorKey on an empty tree should return nullptr");
		Check(map.CeilingKey(1) == nullptr, "CeilingKey on an empty tree should return nullptr");
		Check(map.Rank(1) == 0, "Rank on an empty tree should be zero");
		ExpectThrows<runtime_error>([&] { map.MinKey(); }, "MinKey should throw on an empty tree");
		ExpectThrows<runtime_error>([&] { map.MaxKey(); }, "MaxKey should throw on an empty tree");
		ExpectThrows<out_of_range>([&] { map.Select(0); }, "Select should reject an index on an empty tree");
		ExpectThrows<out_of_range>([&] { map.Select(-1); }, "Select should reject a negative index");
		map.RemoveMin();
		map.RemoveMax();

		map.Insert(5, 50);
		map.Insert(3, 30);
		map.Insert(7, 70);
		map.Insert(2, 20);
		map.Insert(4, 40);
		map.Insert(6, 60);
		map.Insert(8, 80);

		Check(map.size() == 7, "Insert should update the tree size");
		Check(!map.IsEmpty(), "Tree should not be empty after insertion");
		Check(map.Contains(4), "Contains should find an existing key");
		Check(!map.Contains(9), "Contains should reject a missing key");
		Check(map.Get(3) != nullptr && *map.Get(3) == 30, "Get should return the associated value");
		Check(map.Get(9) == nullptr, "Get should return nullptr for a missing key");

		map.Insert(4, 400);
		Check(map.size() == 7, "Inserting a duplicate key should not increase size");
		Check(map.Get(4) != nullptr && *map.Get(4) == 400, "Inserting a duplicate key should update its value");

		const vector<int> sortedKeys {2, 3, 4, 5, 6, 7, 8};
		Check(map.Keys() == sortedKeys, "Keys should return keys in sorted order");
		Check(map.Keys(3, 6) == vector<int>({3, 4, 5, 6}), "Range Keys should include both bounds");
		Check(map.Keys(6, 3).empty(), "Range Keys should be empty when low is greater than high");

		Check(map.MinKey() == 2, "MinKey should return the smallest key");
		Check(map.MaxKey() == 8, "MaxKey should return the largest key");
		Check(map.Select(0) == 2 && map.Select(6) == 8, "Select should return keys at boundary indices");
		Check(map.Select(3) == 5, "Select should return the key at an interior index");
		ExpectThrows<out_of_range>([&] { map.Select(7); }, "Select should reject an index past the end");
		Check(map.Rank(1) == 0, "Rank should be zero below the smallest key");
		Check(map.Rank(5) == 3, "Rank should count keys smaller than an existing key");
		Check(map.Rank(9) == 7, "Rank should equal size above the largest key");
		Check(map.Rank(5) == 3, "Rank should be stable across repeated calls");

		Check(map.FloorKey(1) == nullptr, "FloorKey should return nullptr below the smallest key");
		Check(map.CeilingKey(1) != nullptr && *map.CeilingKey(1) == 2, "CeilingKey should find the next key above the lower bound");
		Check(map.FloorKey(9) != nullptr && *map.FloorKey(9) == 8, "FloorKey should find the previous key below the upper bound");
		Check(map.CeilingKey(9) == nullptr, "CeilingKey should return nullptr above the largest key");

		map.Remove(5); // Remove a node with two children.
		Check(!map.Contains(5) && map.size() == 6, "Removing a two-child node should update membership and size");
		Check(map.Keys() == vector<int>({2, 3, 4, 6, 7, 8}), "Removing a two-child node should preserve ordering");
		Check(map.FloorKey(5) != nullptr && *map.FloorKey(5) == 4, "FloorKey should work after deletion");
		Check(map.CeilingKey(5) != nullptr && *map.CeilingKey(5) == 6, "CeilingKey should work after deletion");

		map.Remove(999);
		Check(map.size() == 6, "Removing a missing key should not change size");
		map.Remove(4); // Remove a leaf.
		Check(map.size() == 5 && !map.Contains(4), "Removing a leaf should update size");
		map.Remove(3); // This node now has one child.
		Check(map.size() == 4 && !map.Contains(3), "Removing a one-child node should update size");
		Check(map.Keys() == vector<int>({2, 6, 7, 8}), "Leaf and one-child removals should preserve ordering");

		map.RemoveMin();
		Check(map.MinKey() == 6 && map.size() == 3, "RemoveMin should remove the smallest key");
		map.RemoveMax();
		Check(map.MaxKey() == 7 && map.size() == 2, "RemoveMax should remove the largest key");
		map.Remove(6); // Remove the root when it has one child.
		Check(map.size() == 1 && map.MinKey() == 7 && map.MaxKey() == 7, "Removing a one-child root should keep its child");
		map.RemoveMax();
		Check(map.IsEmpty() && map.size() == 0, "Removing the final node should leave an empty tree");

		TreeMap<int, int> extrema;
		extrema.Insert(3, 30);
		extrema.Insert(1, 10);
		extrema.Insert(2, 20);
		extrema.Insert(5, 50);
		extrema.Insert(4, 40);
		extrema.RemoveMin(); // The minimum has a right child.
		Check(extrema.Keys() == vector<int>({2, 3, 4, 5}), "RemoveMin should reconnect the removed node's right child");
		extrema.RemoveMax(); // The maximum has a left child.
		Check(extrema.Keys() == vector<int>({2, 3, 4}), "RemoveMax should reconnect the removed node's left child");

		cout << "All tests passed\n";
		return 0;
	} catch (const exception& error) {
		cerr << "Test failed: " << error.what() << '\n';
		return 1;
	}
}
