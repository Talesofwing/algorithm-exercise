#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <numbers>

using namespace std;

using ll = long long;
using ull = unsigned long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ll A, B, THRESHOLD = 1000000000000000000LL;
	cin >> A >> B;

	ll c = A / gcd(A, B);
	if (B <= THRESHOLD / c) cout << B * c << endl;
	else cout << "Large" << endl;
}
