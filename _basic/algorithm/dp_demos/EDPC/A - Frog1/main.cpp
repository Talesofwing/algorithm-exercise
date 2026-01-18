#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

int N;
vector<int> h, dp;

// 貰う
void method_1() {
	dp[1] = abs(h[1] - h[0]);

	for (int i = 0; i < N - 1; ++i) {
		chmin(dp[i], dp[i - 1] + abs(h[i] - h[i - 1]));
		chmin(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
	}
}

// 配る
void method_2() {
	for (int i = 0; i < N - 1; ++i) {
		chmin(dp[i + 1], dp[i] + abs(h[i] - h[i + 1]));
		chmin(dp[i + 2], dp[i] + abs(h[i] - h[i + 2]));
	}
}

// Recursive
int method_3(int i) {
	if (dp[i] < INT_MAX) return dp[i];

	if (i == 0) return 0;

	int res = INT_MAX;
	chmin(res, method_3(i - 1) + abs(h[i] - h[i - 1]));
	if (i > 1) chmin(res, method_3(i - 2) + abs(h[i] - h[i - 2]));

	return dp[i] = res;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;

	h.resize(N);
	dp.resize(N);

	for (int i = 0; i < N; ++i) cin >> h[i];
	for (int i = 0; i < N; ++i) dp[i] = INT_MAX;

	dp[0] = 0;

	// method_1();
	// method_2();
	method_3(N - 1);

	cout << dp[N - 1] << endl;

	return 0;
}
