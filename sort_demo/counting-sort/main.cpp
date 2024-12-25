#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

using ll = long long;

// #define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

/*
	Using Counting Sort to sort an array in ascending order
*/

ostream& operator<<(ostream& os, vector<int>& arr) {
	os << "[";
	rep(i, arr.size()) {
		os << arr[i];
		if (i != arr.size() - 1) {
			os << ", ";
		}
	}
	os << "]";
	return os;
}

int GetMax(const std::vector<int>& arr) {
	int m = abs(arr[0]);
	for (int i = 1; i < arr.size(); ++i) {
		m = max(m, abs(arr[i]));
	}
	return m;
}

pair<vector<int>, vector<int>> SeperateNumbers(const vector<int>& arr) {
	vector<int> negatives, positives;
	for (int num : arr) {
		if (num < 0) {
			negatives.push_back(num);
		} else {
			positives.push_back(num);
		}
	}
	return {negatives, positives};
}

void Sorting(vector<int>& arr) {
	int m = GetMax(arr);
	vector<int> counts(m + 1, 0);
	vector<int> output(arr.size());

	for (int num : arr) {
		counts[abs(num)]++;
	}

	for (int i = 1; i <= m; ++i) {
		counts[i] += counts[i - 1];
	}

	for (int i = arr.size() - 1; i >= 0; --i) {
		output[counts[abs(arr[i])] - 1] = arr[i];
		counts[abs(arr[i])]--;
	}

	arr = output;
}

void CountingSort(vector<int>& arr) {
	auto [negatives, positives] = SeperateNumbers(arr);

	if (!negatives.empty()) {
		Sorting(negatives);
	}

	if (!positives.empty()) {
		Sorting(positives);
	}

	arr.clear();

	for (int i = negatives.size() - 1; i >= 0; --i) {
		arr.push_back(negatives[i]);
	}

	for (int i = 0; i < positives.size(); ++i) {
		arr.push_back(positives[i]);
	}
}

#pragma region Test

bool IsSorted(const vector<int>& arr) {
	for (size_t i = 1; i < arr.size(); i++) {
		if (arr[i] < arr[i - 1]) {
			return false;
		}
	}
	return true;
}

bool AreEqual(const vector<int>& a, const vector<int>& b) {
	if (a.size() != b.size()) return false;
	vector<int> sorted_b = b;
	sort(sorted_b.begin(), sorted_b.end());
	return a == sorted_b;
}

vector<int> GenerateRandomArray(int size, int min_val, int max_val) {
	vector<int> arr(size);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(min_val, max_val);
	for (int& num : arr) {
		num = dis(gen);
	}
	return arr;
}

void RunTest() {
	// Test 1: Empty array
	{
		vector<int> arr;
		CountingSort(arr);
		assert(arr.empty());
		cout << "Test 1" << " (Empty array): Passed\n";
	}

	// Test 2: Single element
	{
		vector<int> arr = {1};
		vector<int> original = arr;
		CountingSort(arr);
		assert(arr == original);
		cout << "Test 2" << " (Single element): Passed\n";
	}

	// Test 3: Sorted array
	{
		vector<int> arr = {1, 2, 3, 4, 5};
		vector<int> original = arr;
		CountingSort(arr);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 3" << " (Already sorted): Passed\n";
	}

	// Test 4: Reverse array
	{
		vector<int> arr = {5, 4, 3, 2, 1};
		vector<int> original = arr;
		CountingSort(arr);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 4" << " (Reverse sorted): Passed\n";
	}

	// Test 5: Duplicate elements
	{
		vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
		vector<int> original = arr;
		CountingSort(arr);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 5" << " (Duplicate elements): Passed\n";
	}

	// Test 6: Same elements
	{
		vector<int> arr(10, 5);
		vector<int> original = arr;
		CountingSort(arr);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 6" << " (All same elements): Passed\n";
	}

	// Test 7: Random elements
	{
		vector<int> arr = GenerateRandomArray(1000000, -1000000, 1000000);
		vector<int> original = arr;
		auto start = chrono::high_resolution_clock::now();
		CountingSort(arr);
		auto end = chrono::high_resolution_clock::now();
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		chrono::duration<double> diff = end - start;
		cout << "Test 7" << " (Large random array): Passed (Time: " << diff.count() << " seconds)\n";
	}

	// // Test 8: Boundary values
	{
		vector<int> arr = {-2000000, 2000000, 0, -1, 1};
		vector<int> original = arr;
		CountingSort(arr);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 8" << " (Boundary values): Passed\n";
	}
}

#pragma endregion

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	RunTest();

	return 0;
}
