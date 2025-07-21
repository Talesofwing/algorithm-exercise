#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <numbers>
#include <list>
#include <deque>
#include <string>
#include <queue>

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

	int n;
	ll l;
	cin >> n >> l;

	int k;
	cin >> k;
	vector<ll> a(n + 1);
	rep(i, n) cin >> a[i];
	a[n] = l;

	ll left = -1, right = l + 1;
	while (right - left > 1) {
		ll mid = left + (right - left) / 2;

		int cnt = 0;
		ll prev = 0;
		for (int i = 0; i < a.size(); i++) {
			if (a[i] - prev >= mid) {
				cnt++;
				prev = a[i];
			}
		}

		if (cnt >= k + 1) left = mid;
		else right = mid;
	}

	cout << left << endl;

	return 0;
}
