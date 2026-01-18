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

	int N, MAX_V = 0;
	ll W;
	cin >> N >> W;
	vector<pair<ll, int>> goods(N);
	for (int i = 0; i < N; ++i) {
		cin >> goods[i].first >> goods[i].second;
		MAX_V += goods[i].second;
	}

	vector<vector<ll>> dp(N + 1, vector<ll>(MAX_V + 1, 1ll << 60));
	dp[0][0] = 0;

	for (int i = 0; i < N; ++i) {
		for (int sum_v = 0; sum_v <= MAX_V; ++sum_v) {
			if (sum_v - goods[i].second >= 0) {
				chmin(dp[i + 1][sum_v], dp[i][sum_v - goods[i].second] + goods[i].first);
			}

			chmin(dp[i + 1][sum_v], dp[i][sum_v]);
		}
	}

	int res = 0;
	for (int sum_v = 0; sum_v <= MAX_V; ++sum_v) {
		if (dp[N][sum_v] <= W) res = sum_v;
	}
	cout << res << endl;

	return 0;
}
