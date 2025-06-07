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

	int n;
	cin >> n;
	vector<int> a(46), b(46), c(46);
	rep(i, n) {
		ll A;
		cin >> A;
		a[(A % 46)]++;
	}
	rep(i, n) {
		ll B;
		cin >> B;
		b[(B % 46)]++;
	}
	rep(i, n) {
		ll C;
		cin >> C;
		c[(C % 46)]++;
	}

	ll ans = 0;
	for (int i = 0; i < 46; ++i) {
		for (int j = 0; j < 46; ++j) {
			for (int k = 0; k < 46; ++k) {
				if ((i + j + k) % 46 == 0) {
					ans += 1ll * a[i] * b[j] * c[k];
				}
			}
		}
	}
	cout << ans << endl;
}
