#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;
using ll = long long;
using ull = unsigned long long;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N, W;
	cin >> N >> W;
	vector<pair<int, ll>> goods(N);
	for (int i = 0; i < N; ++i) {
		cin >> goods[i].first >> goods[i].second;
	}

	vector<vector<ll>> dp(N + 1, vector<ll>(W + 1, 0));
	for (int i = 0; i < N; ++i) {
		for (int w = 0; w <= W; ++w) {
			if (w - goods[i].first >= 0) {
				chmax(dp[i + 1][w], dp[i][w - goods[i].first] + goods[i].second);
			}

			chmax(dp[i + 1][w], dp[i][w]);
		}
	}

	cout << dp[N][W] << endl;

	return 0;
}
