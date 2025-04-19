#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)
#define ll long long

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ll N, A, B, C;
	cin >> N >> A >> B >> C;

	ll ans = LLONG_MAX;
	for (int i = 0; i <= 9999; ++i) {
		for (int j = 0; j <= 9999 - i; ++j) {
			ll V = N - i * A - j * B;
			ll R = i + j + V / C;
			if (V % C != 0 || V < 0 || R > 9999) continue;
			ans = min(ans, R);
		}
	}

	cout << ans << endl;
}
