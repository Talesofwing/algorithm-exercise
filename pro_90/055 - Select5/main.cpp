#include <iostream>
#include <unordered_set>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long;

#define endl "\n"
#define min(v,u) (v < u ? v : u)
#define max(v,u) (v > u ? v : u)
#define clamp(v,l,r) (min(max(v,l),r))
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ll N, P, Q;
	cin >> N >> P >> Q;
	vector<ll> A(N);
	rep(i, N) cin >> A[i];

	ll ans = 0;
	rep(i, N - 4) {
		rep2(j, i + 1, N - 3) {
			rep2(k, j + 1, N - 2) {
				rep2(l, k + 1, N - 1) {
					rep2(m, l + 1, N) {
						if (A[i] * A[j] % P * A[k] % P * A[l] % P * A[m] % P == Q) {
							ans++;
						}
					}
				}
			}
		}
	}
	cout << ans << endl;
}
