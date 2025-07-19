#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <numbers>
#include <list>
#include <deque>
#include <string>
#include <queue>

using namespace std;

using ll = long long;
using ull = unsigned long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

void Naive() {
	int n;
	string s;
	cin >> n >> s;

	queue<int> xPos, oPos;
	rep(i, n) {
		if (s[i] == 'x') xPos.push(i);
		else oPos.push(i);
	}

	ll ans = 0;
	ll index = -1;
	bool xFlag = true, oFlag = true;
	rep(i, n) {
		if (s[i] == 'x') {
			if (!oFlag) continue;

			if (i >= index) {
				oFlag = false;
				for (int j = i + 1; j < n; ++j) {
					if (s[j] == 'o') {
						index = j;
						oFlag = true;
						break;
					}
				}

				if (!oFlag) continue;
			}

			ans += n - index;
		} else {
			if (!xFlag) continue;

			if (i >= index) {
				xFlag = false;
				for (int j = i + 1; j < n; ++j) {
					if (s[j] == 'x') {
						index = j;
						xFlag = true;
						break;
					}
				}

				if (!xFlag) continue;
			}

			ans += n - index;
		}
	}

	cout << ans << endl;
}

void Short() {
	int n;
	string s;
	cin >> n >> s;

	vector<pair<char, int>> vec;
	int cnt = 0;
	rep(i, n) {
		cnt++;
		if (i == s.size() - 1 || s[i] != s[i + 1]) {
			vec.push_back({s[i], cnt});
			cnt = 0;
		}
	}

	ll accum = 0;
	ll ans = 0;
	rep(i, vec.size() - 1) {
		ll l = vec[i].second;
		ll r = n - l - accum;
		ans += l * r;
		accum += l;
	}

	cout << ans << endl;
}

void Contradiction() {
	int n;
	string s;
	cin >> n >> s;

	vector<ll> vec;
	int cnt = 0;
	rep(i, n) {
		cnt++;
		if (i == s.size() - 1 || s[i] != s[i + 1]) {
			vec.push_back(cnt);
			cnt = 0;
		}
	}

	ll amount = 0;
	rep(i, vec.size()) {
		amount += ((1 + vec[i]) * vec[i]) / 2ll;
	}

	cout << (((n + 1ll) * n) / 2ll) - amount << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	// Naive();
	Short();
	// Contradiction();

	return 0;
}
