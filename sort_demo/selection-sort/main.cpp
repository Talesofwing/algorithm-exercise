#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

/*
	Using Selection Sort to sort an array in ascending order
*/

void SelectionSort(vector<int> arr) {
	int min = 0, temp = 0;
	rep(i, arr.size() - 1) {
		min = i;
		rep2(j, i + 1, arr.size()) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}

		if (min != i) {
			temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;
		}
	}

	rep(i, arr.size()) {
		cout << arr[i] << " ";
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

	SelectionSort(arr);

	return 0;
}
