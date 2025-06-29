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

ll m = 1000000007;

// a : base, n : exponent
ll power(ll a, ll n) {
	ll ans = 1;
	while (n != 0) {
		if (n % 2 == 1) {
			ans = ans * a % m;
		}
		a = a * a % m;
		n /= 2;
	}

	return ans;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ll n, k;
	cin >> n >> k;

	if (k == 1) {
		cout << (n == 1 ? 1 : 0) << endl;
	} else if (n == 1) {
		cout << k % m << endl;
	} else if (n == 2) {
		cout << (k * (k - 1)) % m << endl;
	} else {
		cout << k * (k - 1) % m * power(k - 2, n - 2) % m << endl;
	}

	return 0;
}
