#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

using ll = long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

/*
	Using Merge Sort to sort an array in ascending order
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

void Merge(vector<int>& arr, int left, int mid, int right) {
	int l_index = left, r_index = mid + 1, k = 0;
	vector<int> temp(right - left + 1);

	while (l_index <= mid && r_index <= right) {
		if (arr[l_index] < arr[r_index]) {
			temp[k++] = arr[l_index++];
		} else {
			temp[k++] = arr[r_index++];
		}
	}

	rep2(l, l_index, mid + 1) {
		temp[k++] = arr[l];
	}

	rep2(r, r_index, right + 1) {
		temp[k++] = arr[r];
	}

	rep(i, k) {
		arr[left + i] = temp[i];
	}
}

void RecursiveMerge(vector<int>& arr, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		RecursiveMerge(arr, left, mid);
		RecursiveMerge(arr, mid + 1, right);
		Merge(arr, left, mid, right);
	}
}

void IterativeMerge(vector<int>& arr) {
	int n = arr.size();
	for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
		for (int l = 0; l < n - 1; l += 2 * curr_size) {
			int mid = min(l + curr_size - 1, n - 1);
			int r = min(l + 2 * curr_size - 1, n - 1);
			Merge(arr, l, mid, r);
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

void RunTest(bool useIterative) {
	// Test 1: Empty array
	{
		vector<int> arr;
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
		assert(arr.empty());
		cout << "Test 1" << " (Empty array): Passed\n";
	}

	// Test 2: Single element
	{
		vector<int> arr = {1};
		vector<int> original = arr;
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
		assert(arr == original);
		cout << "Test 2" << " (Single element): Passed\n";
	}

	// Test 3: Sorted array
	{
		vector<int> arr = {1, 2, 3, 4, 5};
		vector<int> original = arr;
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 3" << " (Already sorted): Passed\n";
	}

	// Test 4: Reverse array
	{
		vector<int> arr = {5, 4, 3, 2, 1};
		vector<int> original = arr;
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 4" << " (Reverse sorted): Passed\n";
	}

	// Test 5: Duplicate elements
	{
		vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
		vector<int> original = arr;
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 5" << " (Duplicate elements): Passed\n";
	}

	// Test 6: Same elements
	{
		vector<int> arr(10, 5);
		vector<int> original = arr;
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 6" << " (All same elements): Passed\n";
	}

	// Test 7: Random elements
	{
		vector<int> arr = GenerateRandomArray(1000000, -1000000, 1000000);
		vector<int> original = arr;
		auto start = chrono::high_resolution_clock::now();
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
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
		if (useIterative) {
			IterativeMerge(arr);
		} else {
			RecursiveMerge(arr, 0, arr.size() - 1);
		}
		assert(IsSorted(arr));
		assert(AreEqual(arr, original));
		cout << "Test 8" << " (Boundary values): Passed\n";
	}
}

#pragma endregion

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << "===== RecursiveMerge =====" << endl;
	RunTest(false);
	cout << "===== IterativeMerge =====" << endl;
	RunTest(true);

	return 0;
}
