#include <iostream>
#include <stdexcept>

#include "SegmentTree.h"

using namespace std;

void Check(bool condition, const char* message) {
	if (!condition) {
		throw runtime_error(message);
	}
}

int main() {
	try {
		SegmentTree sumTree(1, 10, SegmentTree::Mode::Sum);
		sumTree.AssignRange(1, 5, 3);
		Check(sumTree.QueryRange(1, 5) == 15, "Range assign should store the correct sum");
		Check(sumTree.QueryRange(1, 1) == 3, "Single-point query should return the assigned value");

		sumTree.Assign(10, 7);
		Check(sumTree.QueryRange(10, 10) == 7, "Point assign should update the last position correctly");

		sumTree.IncrementRange(3, 7, 2);
		Check(sumTree.QueryRange(3, 7) == 19, "Range increment should update all values in the range");
		Check(sumTree.QueryRange(1, 10) == 32, "Total sum after increment should be correct");

		SegmentTree maxTree(1, 8, SegmentTree::Mode::Max);
		maxTree.AssignRange(1, 8, 4);
		maxTree.IncrementRange(3, 6, 3);
		Check(maxTree.QueryRange(1, 8) == 7, "Max mode should keep the largest value");
		Check(maxTree.QueryRange(3, 6) == 7, "Max mode should reflect the updated range values");

		SegmentTree minTree(1, 6, SegmentTree::Mode::Min);
		minTree.AssignRange(1, 6, 8);
		minTree.IncrementRange(2, 5, -3);
		Check(minTree.QueryRange(1, 6) == 5, "Min mode should return the minimum value across the range");
		Check(minTree.QueryRange(2, 5) == 5, "Min mode should reflect the reduced values in the range");

		cout << "All segment tree tests passed\n";
		return 0;
	} catch (const exception& error) {
		cerr << "Test failed: " << error.what() << '\n';
		return 1;
	}
}
