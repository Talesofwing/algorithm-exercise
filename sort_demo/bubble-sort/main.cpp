#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

/*
	Using Bubble Sort to sort an array in ascending order
*/

void BubbleSort(vector<int> arr) {
	bool swapped = false;
	rep(i, arr.size() - 1) {
		swapped = false;
		rep(j, arr.size() - 1) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}

		// Early termination
		if (!swapped) {
			break;
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

	BubbleSort(arr);

	return 0;
}
