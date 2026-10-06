#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "SegmentTree.h"

using namespace std;

static int g_passed = 0;

void Check(bool condition, const string& message) {
	if (!condition) {
		throw runtime_error(message);
	}
	++g_passed;
}

template<typename Ex, typename F>
void CheckThrows(F&& f, const string& message) {
	try {
		f();
	} catch (const Ex&) {
		++g_passed;
		return;
	} catch (...) {
		throw runtime_error(message + " (threw a different exception type)");
	}
	throw runtime_error(message + " (did not throw)");
}

// ============================================================================
// 1. Basic behavior (your original cases; template argument added)
// ============================================================================
void TestBasic() {
	using ST = SegmentTree<int>;

	ST sumTree(1, 10, SegmentTreeMode::Sum);
	sumTree.AssignRange(1, 5, 3);
	Check(sumTree.QueryRange(1, 5) == 15, "Range assign should store the correct sum");
	Check(sumTree.QueryRange(1, 1) == 3, "Single-point query should return the assigned value");

	sumTree.Assign(10, 7);
	Check(sumTree.QueryRange(10, 10) == 7, "Point assign should update the last position correctly");

	sumTree.IncrementRange(3, 7, 2);
	Check(sumTree.QueryRange(3, 7) == 19, "Range increment should update all values in the range");
	Check(sumTree.QueryRange(1, 10) == 32, "Total sum after increment should be correct");

	ST maxTree(1, 8, SegmentTreeMode::Max);
	maxTree.AssignRange(1, 8, 4);
	maxTree.IncrementRange(3, 6, 3);
	Check(maxTree.QueryRange(1, 8) == 7, "Max mode should keep the largest value");
	Check(maxTree.QueryRange(3, 6) == 7, "Max mode should reflect the updated range values");
	Check(maxTree.QueryRange(1, 2) == 4, "Max mode untouched part should keep assigned value");

	ST minTree(1, 6, SegmentTreeMode::Min);
	minTree.AssignRange(1, 6, 8);
	minTree.IncrementRange(2, 5, -3);
	Check(minTree.QueryRange(1, 6) == 5, "Min mode should return the minimum value across the range");
	Check(minTree.QueryRange(2, 5) == 5, "Min mode should reflect the reduced values in the range");
	Check(minTree.QueryRange(6, 6) == 8, "Min mode untouched point should keep assigned value");
}

// ============================================================================
// 2. Initial state: every position starts at 0
// ============================================================================
void TestInitialState() {
	using ST = SegmentTree<int>;

	ST sumTree(0, 100, SegmentTreeMode::Sum);
	ST maxTree(0, 100, SegmentTreeMode::Max);
	ST minTree(0, 100, SegmentTreeMode::Min);

	Check(sumTree.QueryRange(0, 100) == 0, "Initial sum should be 0");
	Check(sumTree.QueryRange(37, 63) == 0, "Initial partial sum should be 0");
	Check(maxTree.QueryRange(0, 100) == 0, "Initial max should be 0");
	Check(minTree.QueryRange(13, 14) == 0, "Initial min should be 0");
}

// ============================================================================
// 3. Lazy tag interactions (the trickiest part)
// ============================================================================
void TestLazyInteractions() {
	using ST = SegmentTree<int>;

	// Repeated increments must accumulate (the original bug)
	{
		ST t(0, 7, SegmentTreeMode::Sum);
		t.IncrementRange(0, 7, 1);
		t.IncrementRange(0, 7, 1);
		Check(t.QueryRange(0, 7) == 16, "Two whole-range increments should accumulate");
		Check(t.QueryRange(3, 3) == 2, "Point value after two increments should be 2");
	}

	// Increment, then assign: assign wins
	{
		ST t(0, 7, SegmentTreeMode::Sum);
		t.IncrementRange(0, 7, 5);
		t.AssignRange(0, 7, 2);
		Check(t.QueryRange(0, 7) == 16, "Assign should override earlier increments");
		Check(t.QueryRange(4, 5) == 4, "Partial query after assign should be correct");
	}

	// Assign, then increment: increment merges into assign
	{
		ST t(0, 7, SegmentTreeMode::Sum);
		t.AssignRange(0, 7, 2);
		t.IncrementRange(0, 7, 3);
		Check(t.QueryRange(0, 7) == 40, "Increment after assign should add on top");
		Check(t.QueryRange(1, 2) == 10, "Partial query after assign+increment");
	}

	// Lazy tag on parent, then partial update must push down first
	{
		ST t(0, 7, SegmentTreeMode::Sum);
		t.AssignRange(0, 7, 1);      // tag on root
		t.IncrementRange(2, 5, 10);  // partial: needs pushdown
		// values: 1 1 11 11 11 11 1 1
		Check(t.QueryRange(0, 7) == 48, "Pushdown before partial increment");
		Check(t.QueryRange(0, 1) == 2, "Left side keeps assigned value");
		Check(t.QueryRange(5, 6) == 12, "Query across modified/unmodified boundary");
	}

	// Increment tag on parent, then partial assign
	{
		ST t(0, 7, SegmentTreeMode::Sum);
		t.IncrementRange(0, 7, 4);   // tag on root
		t.AssignRange(3, 4, -1);     // partial
		// values: 4 4 4 -1 -1 4 4 4
		Check(t.QueryRange(0, 7) == 22, "Pushdown increment before partial assign");
		Check(t.QueryRange(2, 5) == 6, "Mixed range after partial assign");
	}

	// Long chain alternating operations on overlapping ranges
	{
		ST t(1, 9, SegmentTreeMode::Max);
		t.AssignRange(1, 9, 0);
		t.IncrementRange(1, 5, 3);   // 3 3 3 3 3 0 0 0 0
		t.AssignRange(4, 7, 1);      // 3 3 3 1 1 1 1 0 0
		t.IncrementRange(3, 8, 2);   // 3 3 5 3 3 3 3 2 0
		t.AssignRange(9, 9, 10);     // ... 10
		Check(t.QueryRange(1, 9) == 10, "Max over chain of ops");
		Check(t.QueryRange(1, 8) == 5, "Max excluding last point");
		Check(t.QueryRange(4, 8) == 3, "Max in middle segment");
	}

	// Increments that cancel out (lazy increment becomes 0)
	{
		ST t(0, 15, SegmentTreeMode::Sum);
		t.AssignRange(0, 15, 1);
		t.IncrementRange(0, 7, 5);
		t.IncrementRange(0, 7, -5);
		Check(t.QueryRange(0, 15) == 16, "Cancelling increments should restore value");
		Check(t.QueryRange(6, 9) == 4, "Cancelling increments across boundary");
	}
}

// ============================================================================
// 4. Query on childless node (the no-node-creation branch)
// ============================================================================
void TestQueryWithoutChildren() {
	using ST = SegmentTree<long long>;

	ST sumTree(0, 999, SegmentTreeMode::Sum);
	sumTree.AssignRange(0, 999, 7);          // whole-range tag only, no children
	Check(sumTree.QueryRange(100, 199) == 700, "Partial sum on childless node");
	Check(sumTree.QueryRange(0, 0) == 7, "Single point on childless node");
	sumTree.IncrementRange(0, 999, 3);
	Check(sumTree.QueryRange(500, 549) == 500, "Partial sum after whole increment");

	ST maxTree(0, 999, SegmentTreeMode::Max);
	maxTree.IncrementRange(0, 999, -4);
	Check(maxTree.QueryRange(10, 20) == -4, "Partial max on childless node");

	ST minTree(0, 999, SegmentTreeMode::Min);
	minTree.AssignRange(0, 999, 9);
	Check(minTree.QueryRange(998, 999) == 9, "Partial min on childless node");
}

// ============================================================================
// 5. Boundaries: negative indices, single-element tree, edges
// ============================================================================
void TestBoundaries() {
	using ST = SegmentTree<int>;

	// Negative range
	{
		ST t(-10, 10, SegmentTreeMode::Sum);
		t.AssignRange(-10, -1, 2);
		t.AssignRange(0, 10, 3);
		Check(t.QueryRange(-10, 10) == 53, "Sum over negative and positive indices");
		Check(t.QueryRange(-1, 0) == 5, "Query across zero");
		t.Increment(-10, 100);
		Check(t.QueryRange(-10, -10) == 102, "Point increment at left edge");
	}

	// Single-element tree
	{
		ST t(5, 5, SegmentTreeMode::Sum);
		Check(t.QueryRange(5, 5) == 0, "Single-element initial");
		t.Assign(5, 42);
		Check(t.QueryRange(5, 5) == 42, "Single-element assign");
		t.Increment(5, -2);
		Check(t.QueryRange(5, 5) == 40, "Single-element increment");
	}

	// Odd length, query each single point after a mixed update
	{
		ST t(0, 6, SegmentTreeMode::Sum);
		t.IncrementRange(1, 5, 1);
		t.AssignRange(3, 3, 9);
		int expected[] = {0, 1, 1, 9, 1, 1, 0};
		for (int i = 0; i <= 6; ++i) {
			Check(t.QueryRange(i, i) == expected[i], "Point check on odd-length tree at " + to_string(i));
		}
	}
}

// ============================================================================
// 6. Large range and large values (long long)
// ============================================================================
void TestLargeValues() {
	using ST = SegmentTree<long long>;

	// Large index range (sparse / dynamic nodes)
	{
		ST t(-1000000000, 1000000000, SegmentTreeMode::Sum);
		t.AssignRange(-1000000000, 1000000000, 1);
		Check(t.QueryRange(-1000000000, 1000000000) == 2000000001LL, "Sum over 2e9+1 elements");
		t.IncrementRange(0, 999, 1000000000);
		Check(t.QueryRange(0, 999) == 1000LL * 1000000001LL, "Large increment on sub-range");
	}

	// Sum beyond int range
	{
		ST t(1, 100000, SegmentTreeMode::Sum);
		t.AssignRange(1, 100000, 1000000000);
		Check(t.QueryRange(1, 100000) == 100000LL * 1000000000LL, "Sum should not overflow with long long");
	}

	// Max with negative values
	{
		ST t(0, 10, SegmentTreeMode::Max);
		t.AssignRange(0, 10, -5000000000LL);
		t.Increment(7, 1);
		Check(t.QueryRange(0, 10) == -4999999999LL, "Max with large negative values");
	}
}

// ============================================================================
// 7. Floating-point type
// ============================================================================
void TestDouble() {
	using ST = SegmentTree<double>;

	ST t(0, 9, SegmentTreeMode::Sum);
	t.AssignRange(0, 9, 0.5);
	t.IncrementRange(5, 9, 0.25);
	double total = t.QueryRange(0, 9);
	Check(abs(total - 6.25) < 1e-9, "Double sum should be approximately correct");

	ST m(0, 9, SegmentTreeMode::Min);
	m.AssignRange(0, 9, 1.5);
	m.IncrementRange(2, 3, -2.0);
	Check(abs(m.QueryRange(0, 9) - (-0.5)) < 1e-9, "Double min should be correct");
}

// ============================================================================
// 8. Error handling
// ============================================================================
void TestErrors() {
	using ST = SegmentTree<int>;

	CheckThrows<invalid_argument>([] { ST t(5, 4, SegmentTreeMode::Sum); }, "Constructor with l > r");
	CheckThrows<invalid_argument>([] {
		ST t(numeric_limits<int>::min(), numeric_limits<int>::max(), SegmentTreeMode::Sum);
	}, "Constructor with too large range");

	ST t(0, 10, SegmentTreeMode::Sum);
	CheckThrows<invalid_argument>([&] { t.QueryRange(5, 4); }, "Query with l > r");
	CheckThrows<invalid_argument>([&] { t.AssignRange(5, 4, 1); }, "Assign with l > r");
	CheckThrows<invalid_argument>([&] { t.IncrementRange(5, 4, 1); }, "Increment with l > r");

	CheckThrows<out_of_range>([&] { t.QueryRange(-1, 5); }, "Query left out of bounds");
	CheckThrows<out_of_range>([&] { t.QueryRange(5, 11); }, "Query right out of bounds");
	CheckThrows<out_of_range>([&] { t.Assign(11, 1); }, "Point assign out of bounds");
	CheckThrows<out_of_range>([&] { t.Increment(-1, 1); }, "Point increment out of bounds");

	// A failed call must not corrupt the tree
	t.AssignRange(0, 10, 1);
	try { t.IncrementRange(5, 20, 100); } catch (...) {}
	Check(t.QueryRange(0, 10) == 11, "Failed call should leave tree unchanged");
}

// ============================================================================
// 9. Randomized test against a brute-force array
// ============================================================================
template<typename T>
void Fuzz(SegmentTreeMode mode, unsigned seed) {
	using ST = SegmentTree<T>;
	const int LO = -20, HI = 20;
	mt19937 rng(seed);
	auto rnd = [&](int a, int b) { return uniform_int_distribution<int>(a, b)(rng); };

	for (int round = 0; round < 200; ++round) {
		ST tree(LO, HI, mode);
		vector<T> ref(HI - LO + 1, T());

		for (int op = 0; op < 500; ++op) {
			int l = rnd(LO, HI), r = rnd(LO, HI);
			if (l > r) swap(l, r);
			T v = static_cast<T>(rnd(-100, 100));

			switch (rnd(0, 2)) {
				case 0:
					tree.AssignRange(l, r, v);
					for (int i = l; i <= r; ++i) ref[i - LO] = v;
					break;
				case 1:
					tree.IncrementRange(l, r, v);
					for (int i = l; i <= r; ++i) ref[i - LO] += v;
					break;
				default:
				{
					auto b = ref.begin() + (l - LO);
					auto e = ref.begin() + (r - LO) + 1;
					T expected = mode == SegmentTreeMode::Sum ? accumulate(b, e, T())
						: mode == SegmentTreeMode::Max ? *max_element(b, e)
						: *min_element(b, e);
					T actual = tree.QueryRange(l, r);
					if (actual != expected) {
						throw runtime_error("Fuzz mismatch: seed=" + to_string(seed) +
							" round=" + to_string(round) + " op=" + to_string(op) +
							" query[" + to_string(l) + "," + to_string(r) + "]" +
							" expected=" + to_string(expected) + " actual=" + to_string(actual));
					}
					++g_passed;
				}
			}
		}
	}
}

void TestFuzz() {
	for (unsigned seed = 1; seed <= 5; ++seed) {
		Fuzz<int>(SegmentTreeMode::Sum, seed);
		Fuzz<int>(SegmentTreeMode::Max, seed);
		Fuzz<int>(SegmentTreeMode::Min, seed);
		Fuzz<long long>(SegmentTreeMode::Sum, seed);
		Fuzz<long long>(SegmentTreeMode::Max, seed);
		Fuzz<long long>(SegmentTreeMode::Min, seed);
	}
}

// ============================================================================

int main() {
	struct { const char* name; void (*fn)(); } tests[] = {
		{"Basic", TestBasic},
		{"InitialState", TestInitialState},
		{"LazyInteractions", TestLazyInteractions},
		{"QueryWithoutChildren", TestQueryWithoutChildren},
		{"Boundaries", TestBoundaries},
		{"LargeValues", TestLargeValues},
		{"Double", TestDouble},
		{"Errors", TestErrors},
		{"Fuzz", TestFuzz},
	};

	int failed = 0;
	for (auto& t : tests) {
		try {
			t.fn();
			cout << "[PASS] " << t.name << '\n';
		} catch (const exception& e) {
			cout << "[FAIL] " << t.name << ": " << e.what() << '\n';
			++failed;
		}
	}

	cout << "\n" << g_passed << " checks passed, " << failed << " test group(s) failed\n";
	return failed == 0 ? 0 : 1;
}
