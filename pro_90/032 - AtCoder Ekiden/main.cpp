#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <numbers>

using namespace std;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N;
	cin >> N;
	vector<vector<int>> A(N, vector<int>(N));
	vector<int> digits(N);
	rep(i, N) {
		rep(j, N) {
			cin >> A[i][j];
			digits[i] = i;
		}
	}

	int M;
	cin >> M;
	vector<vector<bool>> B(N, vector<bool>(N, false));
	rep(i, M) {
		int f, s;
		cin >> f >> s;
		B[f - 1][s - 1] = true;
		B[s - 1][f - 1] = true;
	}

	long long ans = LLONG_MAX;
	do {
		bool b = false;
		rep(i, N - 1) {
			if (B[digits[i]][digits[i + 1]]) {
				b = true;
				break;
			}
		}

		if (b) continue;

		long long sum = 0;
		rep(i, N) {
			sum += A[digits[i]][i];
		}

		ans = min(ans, sum);
	} while (next_permutation(digits.begin(), digits.end()));

	cout << (ans == LLONG_MAX ? -1 : ans) << endl;
}
