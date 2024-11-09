#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

/*
	Using Insertion Sort to sort an array in ascending order
*/

void InsertionSort(vector<int>& arr) {
	int j, temp;
	rep2(i, 1, arr.size()) {
		temp = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > temp) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}


void InsertionSort_BinarySearch(vector<int>& arr) {
	int left, right, temp;
	rep2(i, 1, arr.size()) {
		temp = arr[i];
		left = 0, right = i - 1;
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

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> arr(n);
	rep(i, n) {
		cin >> arr[i];
	}

	// InsertionSort(arr);
	InsertionSort_BinarySearch(arr);

	rep(i, arr.size()) {
		cout << arr[i] << " ";
	}

	return 0;
}
