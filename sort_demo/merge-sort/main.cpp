#include <iostream>
#include <vector>

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

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> arr(n);
	rep(i, n) {
		cin >> arr[i];
	}

	// RecursiveMerge(arr, 0, n - 1);
	IterativeMerge(arr);

	cout << arr << endl;

	return 0;
}
