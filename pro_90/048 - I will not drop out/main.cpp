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

	int n, k;
	cin >> n >> k;
	vector<ll> v(2 * n);
	rep(i, n) {
		ll a, b;
		cin >> a >> b;
		v[2 * i] = b;
		v[2 * i + 1] = a - b;
	}

	ll ans = 0;
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	rep(i, k) ans += v[i];
	cout << ans << endl;
}
