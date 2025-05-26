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

	deque<ll> A;
	rep(i, N) {
		ll a;
		cin >> a;
		A.emplace_back(a);
	}

	rep(i, Q) {
		short T;
		cin >> T;
		int x, y;
		cin >> x >> y;
		if (T == 1) {
			swap(A[x - 1], A[y - 1]);
		} else if (T == 2) {
			ll a = A.back();
			A.pop_back();
			A.emplace_front(a);
		} else if (T == 3) {
			cout << A[x - 1] << endl;
		}
	}
}
