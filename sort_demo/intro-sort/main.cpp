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
#define INSERTION_SORT_THRESHOLD 16

/*
	Using Intro Sort to sort an array in ascending order
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

void MaxHeapify(vector<int>& arr, int index, int low, int high) {
	int parent = index;
	int son = parent * 2 + 1;
	while (son <= high) {
		if (son + 1 <= high && arr[son + low] < arr[son + low + 1]) {
			son++;
		}

		if (arr[parent + low] > arr[son + low]) {
			return;
		} else {
			swap(arr[parent + low], arr[son + low]);
			parent = son;
			son = parent * 2 + 1;
		}
	}
}

void HeapSort(vector<int>& arr, int low, int high) {
	int size = high - low + 1;
	for (int i = size / 2 - 1; i >= 0; --i) {
		MaxHeapify(arr, i, low, size - 1);
	}

	for (int i = size - 1; i > 0; --i) {
		swap(arr[low], arr[i + low]);
		MaxHeapify(arr, 0, low, i - 1);
	}
}

void InsertionSort_BinarySearch(vector<int>& arr, int low, int high) {
	int left, right, temp;
	rep2(i, low + 1, high + 1) {
		temp = arr[i];
		left = low, right = i - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (arr[mid] > temp) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}

		for (int j = i - 1; j >= left; --j) {
			arr[j + 1] = arr[j];
		}
		arr[left] = temp;
	}
}

void Introsort(vector<int>& arr, int low, int high, int depthLimit) {
	if (low < high) {
		if (depthLimit == 0) {
			// Heap Sort

			HeapSort(arr, low, high);
		} else if (high - low < INSERTION_SORT_THRESHOLD) {
			// Insertion Sort

			InsertionSort_BinarySearch(arr, low, high);
		} else {
			// Quick Sort

			int pivot = MedianOfThree(arr, low, high);
			int index = HoarePartition(arr, pivot, low, high);
			Introsort(arr, low, index, depthLimit - 1);
			Introsort(arr, index + 1, high, depthLimit - 1);
		}
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
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
		assert(arr.empty());
		cout << "Test 1" << " (Empty array): Passed\n";
	}

	// Test 2: Single element
	{
		vector<int> arr = {1};
		vector<int> original = arr;
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
		assert(arr == original);
		cout << "Test 2" << " (Single element): Passed\n";
	}

	// Test 3: Sorted array
	{
		vector<int> arr = {1, 2, 3, 4, 5};
		vector<int> original = arr;
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 3" << " (Already sorted): Passed\n";
	}

	// Test 4: Reverse array
	{
		vector<int> arr = {5, 4, 3, 2, 1};
		vector<int> original = arr;
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 4" << " (Reverse sorted): Passed\n";
	}

	// Test 5: Duplicate elements
	{
		vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
		vector<int> original = arr;
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 5" << " (Duplicate elements): Passed\n";
	}

	// Test 6: Same elements
	{
		vector<int> arr(10, 5);
		vector<int> original = arr;
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 6" << " (All same elements): Passed\n";
	}

	// Test 7: Random elements
	{
		vector<int> arr = GenerateRandomArray(1000000, -1000000, 1000000);
		vector<int> original = arr;
		auto start = chrono::high_resolution_clock::now();
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
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
		Introsort(arr, 0, arr.size() - 1, 2 * log2(arr.size()));
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
