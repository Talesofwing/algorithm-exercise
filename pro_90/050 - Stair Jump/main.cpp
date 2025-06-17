#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <numbers>
#include <list>
#include <deque>

using namespace std;

using ll = long long;
using ull = unsigned long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, l;
	cin >> n >> l;

	vector<int> dp(n + 1, 0);
	dp[0] = 1;

	for (int i = 1; i <= n; ++i) {
		if (i < l) {
			dp[i] = dp[i - 1];
		} else {
			dp[i] = (dp[i - 1] + dp[i - l]) % 1000000007;
		}
	}

	cout << dp[n] << endl;

	return 0;
}
