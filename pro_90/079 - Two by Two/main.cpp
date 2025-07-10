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

	int h, w;
	cin >> h >> w;

	vector<vector<int>> a(h, vector<int>(w)), b(h, vector<int>(w));
	rep(y, h) {
		rep(x, w) {
			cin >> a[y][x];
		}
	}

	rep(y, h) {
		rep(x, w) {
			cin >> b[y][x];
		}
	}

	ll ans = 0;
	rep(y, h - 1) {
		rep(x, w - 1) {
			ll diff = b[y][x] - a[y][x];
			a[y][x] += diff;
			a[y][x + 1] += diff;
			a[y + 1][x] += diff;
			a[y + 1][x + 1] += diff;
			ans += abs(diff);
		}
	}

	if (a == b) {
		cout << "Yes" << endl;
		cout << ans << endl;
	} else {
		cout << "No" << endl;
	}

	return 0;
}
