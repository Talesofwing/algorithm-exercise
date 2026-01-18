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

	int N, K;
	cin >> N >> K;
	vector<int> h(N);
	for (int i = 0; i < N; ++i)	cin >> h[i];

	vector<int> dp(N, INT_MAX);
	dp[0] = 0;

	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= K; ++j) {
			if (i - j < 0)	break;
			chmin(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
		}
	}
	cout << dp[N - 1] << endl;

	return 0;
}
