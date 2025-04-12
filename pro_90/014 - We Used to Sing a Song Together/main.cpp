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
	vector<ll> A(N), B(N);
	rep(i, N) cin >> A[i];
	rep(i, N) cin >> B[i];

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	ll ans = 0;
	rep(i, N) ans += abs(A[i] - B[i]);

	cout << ans << endl;
}
