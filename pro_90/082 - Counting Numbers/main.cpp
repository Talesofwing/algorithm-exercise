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

using namespace std;

using ll = long long;
using ull = unsigned long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

ull mod_mul(ull a, ull b, ull m) {
	long long res = 0;
	a %= m;
	b %= m;
	while (b) {
		if (b & 1) res = (res + a) % m;
		a = (a + a) % m;
		b >>= 1;
	}
	return res;
}

ull pow_self(ull x, ull n) {
	ull res = 1;
	while (n > 0) {
		if (n & 1) res *= x;
		x *= x;
		n >>= 1;
	}
	return res;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ull l, r;
	cin >> l >> r;

	constexpr ull m = 1000000007;

	ull ans = 0;
	for (ull i = 1; i <= 19; ++i) {
		ull L = pow_self(10, i - 1);
		ull R = pow_self(10, i) - 1;

		if (R < l) continue;
		if (L < l) L = l;
		bool flag = false;
		if (R > r) {
			R = r;
			flag = true;
		}

		ans = (ans + mod_mul(mod_mul(mod_mul((L + R) % m, (R - L + 1) % m, m), i % m, m), 500000004, m)) % m;

		if (flag) break;
	}

	cout << ans << endl;

	return 0;
}
