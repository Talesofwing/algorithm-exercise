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

	int N, Q;
	cin >> N >> Q;
	vector<ll> A(N + 1, 0), L(Q), R(Q), X(Q), B(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}

	rep(i, Q) {
		cin >> L[i] >> R[i] >> X[i];
	}

	ll ans = 0;
	for (int i = 1; i < N; ++i) {
		B[i] = A[i + 1] - A[i];
		ans += abs(B[i]);
	}

	rep(i, Q) {
		ll before = abs(B[L[i] - 1]) + abs(B[R[i]]);
		if (L[i] >= 2) B[L[i] - 1] += X[i];
		if (R[i] <= N - 1) B[R[i]] -= X[i];
		ll after = abs(B[L[i] - 1]) + abs(B[R[i]]);
		ans += after - before;
		cout << ans << endl;
	}

	return 0;
}
