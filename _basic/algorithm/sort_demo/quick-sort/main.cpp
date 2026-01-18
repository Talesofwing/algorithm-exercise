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
	Using Quick Sort to sort an array in ascending order
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

int MedianOfThree(const vector<int>& arr, int low, int high) {
	int first = arr[low];
	int mid = arr[low + (high - low) / 2];
	int last = arr[high];
	return std::max(std::min(first, mid), std::min(std::max(first, mid), last));
}

int HoarePartition(vector<int>& arr, int pivot, int low, int high) {
	while (true) {
		while (arr[low] < pivot) {
			low++;
		}
		while (arr[high] > pivot) {
			high--;
		}

		if (low >= high) {
			return high;
		}

		swap(arr[low], arr[high]);
		low++;
		high--;
	}
}

void QuickSort(vector<int>& arr, int low, int high) {
	if (high - low <= 0) {
		return;
	} else if (high - low == 1) {
		if (arr[low] > arr[high]) {
			swap(arr[low], arr[high]);
		}
		return;
	} else if (high - low == 2) {
		if (arr[low] > arr[low + 1]) swap(arr[low], arr[low + 1]);
		if (arr[low] > arr[high]) swap(arr[low], arr[high]);
		if (arr[low + 1] > arr[high]) swap(arr[low + 1], arr[high]);
		return;
	}

	int pivot = MedianOfThree(arr, low, high);
	int index = HoarePartition(arr, pivot, low, high);

	QuickSort(arr, low, index);
	QuickSort(arr, index + 1, high);
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
		QuickSort(arr, 0, arr.size() - 1);
		assert(arr.empty());
		cout << "Test 1" << " (Empty array): Passed\n";
	}

	// Test 2: Single element array
	{
		vector<int> arr = {1};
		vector<int> original = arr;
		QuickSort(arr, 0, arr.size() - 1);
		assert(arr == original);
		cout << "Test 2" << " (Single element): Passed\n";
	}

	// Test 3: Sorted array
	{
		vector<int> arr = {1, 2, 3, 4, 5};
		vector<int> original = arr;
		QuickSort(arr, 0, arr.size() - 1);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 3" << " (Already sorted): Passed\n";
	}

	// Test 4: Reversed array
	{
		vector<int> arr = {5, 4, 3, 2, 1};
		vector<int> original = arr;
		QuickSort(arr, 0, arr.size() - 1);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 4" << " (Reverse sorted): Passed\n";
	}

	// Test 5: Duplicate elements
	{
		vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
		vector<int> original = arr;
		QuickSort(arr, 0, arr.size() - 1);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 5" << " (Duplicate elements): Passed\n";
	}

	// Test 6: Same elements
	{
		vector<int> arr(10, 5);
		vector<int> original = arr;
		QuickSort(arr, 0, arr.size() - 1);
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 6" << " (All same elements): Passed\n";
	}

	// Test 7: Random elements
	{
		vector<int> arr = GenerateRandomArray(1000000, -1000000, 1000000);
		vector<int> original = arr;
		auto start = chrono::high_resolution_clock::now();
		QuickSort(arr, 0, arr.size() - 1);
		auto end = chrono::high_resolution_clock::now();
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		chrono::duration<double> diff = end - start;
		cout << "Test 7" << " (Large random array): Passed (Time: " << diff.count() << " seconds)\n";
	}

	// Test 8: Boundary values
	{
		vector<int> arr = {INT_MIN, INT_MAX, 0, -1, 1};
		vector<int> original = arr;
		QuickSort(arr, 0, arr.size() - 1);
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
