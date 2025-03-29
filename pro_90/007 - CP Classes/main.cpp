#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)
#define ll long long

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N;
	cin >> N;
	vector<ll> A(N);
	rep(i, N) cin >> A[i];

	int Q;
	cin >> Q;

	sort(A.begin(), A.end());

	rep(i, Q) {
		ll B;
		cin >> B;

		int j = lower_bound(A.begin(), A.end(), B) - A.begin();
		ll res = LLONG_MAX;
		if (j < N) res = min(res, abs(B - A[j]));
		if (j > 0) res = min(res, abs(B - A[j - 1]));
		cout << res << endl;
	}
}
