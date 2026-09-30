#include <iostream>
#include <stdexcept>
#include <vector>

#include "TreeSet.h"

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
		TreeSet<int> set;

		Check(set.IsEmpty(), "A new set should be empty");
		Check(set.Size() == 0, "A new set should have size zero");
		Check(set.Keys().empty(), "Keys of an empty set should be empty");
		Check(!set.Contains(1), "An empty set should not contain keys");
		Check(set.FloorKey(1) == nullptr, "FloorKey on an empty set should return nullptr");
		Check(set.CeilingKey(1) == nullptr, "CeilingKey on an empty set should return nullptr");
		Check(set.Rank(1) == 0, "Rank on an empty set should be zero");
		ExpectThrows<runtime_error>([&] { set.MinKey(); }, "MinKey should throw on an empty set");
		ExpectThrows<runtime_error>([&] { set.MaxKey(); }, "MaxKey should throw on an empty set");
		ExpectThrows<out_of_range>([&] { set.Select(0); }, "Select should reject an index on an empty set");
		ExpectThrows<out_of_range>([&] { set.Select(-1); }, "Select should reject a negative index");
		set.RemoveMin();
		set.RemoveMax();

		for (int key : {5, 3, 7, 2, 4, 6, 8}) {
			set.Insert(key);
		}

		Check(set.Size() == 7 && !set.IsEmpty(), "Insert should update set size");
		Check(set.Contains(4) && !set.Contains(9), "Contains should find only existing keys");
		set.Insert(4);
		Check(set.Size() == 7, "Inserting a duplicate should not increase set size");

		const vector<int> sortedKeys {2, 3, 4, 5, 6, 7, 8};
		Check(set.Keys() == sortedKeys, "Keys should return unique keys in sorted order");
		Check(set.Keys(3, 6) == vector<int>({3, 4, 5, 6}), "Range Keys should include both bounds");
		Check(set.Keys(6, 3).empty(), "Range Keys should be empty when low is greater than high");
		Check(set.MinKey() == 2 && set.MaxKey() == 8, "MinKey and MaxKey should return the set bounds");
		Check(set.Select(0) == 2 && set.Select(3) == 5 && set.Select(6) == 8, "Select should return keys by sorted index");
		ExpectThrows<out_of_range>([&] { set.Select(7); }, "Select should reject an index past the end");
		Check(set.Rank(1) == 0 && set.Rank(5) == 3 && set.Rank(9) == 7, "Rank should count keys smaller than its argument");
		Check(set.FloorKey(1) == nullptr, "FloorKey should return nullptr below the minimum");
		Check(set.CeilingKey(1) != nullptr && *set.CeilingKey(1) == 2, "CeilingKey should find the next key");
		Check(set.FloorKey(9) != nullptr && *set.FloorKey(9) == 8, "FloorKey should find the previous key");
		Check(set.CeilingKey(9) == nullptr, "CeilingKey should return nullptr above the maximum");
		Check(set.FloorKey(5) != nullptr && *set.FloorKey(5) == 5, "FloorKey should return an exact match");
		Check(set.CeilingKey(5) != nullptr && *set.CeilingKey(5) == 5, "CeilingKey should return an exact match");

		set.Remove(5);
		Check(!set.Contains(5) && set.Size() == 6, "Removing a key with two children should update membership and size");
		Check(set.Keys() == vector<int>({2, 3, 4, 6, 7, 8}), "Removal should preserve sorted order");
		Check(set.FloorKey(5) != nullptr && *set.FloorKey(5) == 4, "FloorKey should work after removal");
		Check(set.CeilingKey(5) != nullptr && *set.CeilingKey(5) == 6, "CeilingKey should work after removal");
		set.Remove(999);
		Check(set.Size() == 6, "Removing a missing key should not change size");
		set.Remove(4);
		set.Remove(3);
		Check(set.Size() == 4 && set.Keys() == vector<int>({2, 6, 7, 8}), "Leaf and one-child removals should preserve the set");
		set.RemoveMin();
		Check(set.MinKey() == 6 && set.Size() == 3, "RemoveMin should remove the smallest key");
		set.RemoveMax();
		Check(set.MaxKey() == 7 && set.Size() == 2, "RemoveMax should remove the largest key");
		set.Remove(6);
		Check(set.Size() == 1 && set.MinKey() == 7 && set.MaxKey() == 7, "Removing a one-child root should keep its child");
		set.RemoveMax();
		Check(set.IsEmpty() && set.Size() == 0, "Removing the final key should leave an empty set");

		TreeSet<int> extrema;
		for (int key : {3, 1, 2, 5, 4}) {
			extrema.Insert(key);
		}
		extrema.RemoveMin();
		Check(extrema.Keys() == vector<int>({2, 3, 4, 5}), "RemoveMin should reconnect the removed node's right child");
		extrema.RemoveMax();
		Check(extrema.Keys() == vector<int>({2, 3, 4}), "RemoveMax should reconnect the removed node's left child");

		cout << "All TreeSet tests passed\n";
		return 0;
	} catch (const exception& error) {
		cerr << "Test failed: " << error.what() << '\n';
		return 1;
	}
}
