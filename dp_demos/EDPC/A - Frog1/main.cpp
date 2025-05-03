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

	vector<int> h(N);
	for (int i = 0; i < N; ++i) cin >> h[i];

	vector<int> dp(N);
	for (int i = 0; i < N; ++i) dp[i] = INT_MAX;

	dp[0] = 0;
	dp[1] = abs(h[1] - h[0]);

	for (int i = 2; i < N; ++i) {
		chmin(dp[i], dp[i - 1] + abs(h[i] - h[i - 1]));
		chmin(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
	}

	cout << dp[N - 1] << endl;

	return 0;
}
