#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N;
	cin >> N;
	vector<vector<long long>> a(N, vector<long long>(3));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < 3; ++j) {
			cin >> a[i][j];
		}
	}

	vector<vector<long long>> dp(N + 1, vector<long long>(3, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				if (j == k) continue;
				chmax(dp[i + 1][k], dp[i][j] + a[i][k]);
			}
		}
	}

	long long ans = 0;
	for (int j = 0; j < 3; ++j) chmax(ans, dp[N][j]);
	cout << ans << endl;

	return 0;
}
