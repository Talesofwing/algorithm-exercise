#include <iostream>
#include <deque>

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

	int Q;
	cin >> Q;
	deque<ll> d;
	rep(i, Q) {
		int t;
		cin >> t;
		if (t == 1) {
			ll x;
			cin >> x;
			d.push_front(x);
		} else if (t == 2) {
			ll x;
			cin >> x;
			d.push_back(x);
		} else if (t == 3) {
			int x;
			cin >> x;
			cout << d[x - 1] << endl;
		}
	}
}
