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

vector<ll> split(ll n) {
	ll tmp = n;
	vector<ll> res;
	for (ll i = 2; i * i <= n; ++i) {
		while (tmp % i == 0) {
			res.push_back(i);
			tmp /= i;
		}
	}

	if (tmp != 1ll) res.push_back(tmp);

	return res;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ll n;
	cin >> n;

	vector<ll> v = split(n);
	int floor = 0;
	while (true) {
		int i = 1 << floor;
		if (i >= v.size()) {
			break;
		}
		floor++;
	}

	cout << floor << endl;

	return 0;
}
