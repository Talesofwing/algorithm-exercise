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

int binary_serach(const vector<ll>& nums, ll target, ll left, ll right) {

	while (left <= right) {
		ll mid = left + (right - left) / 2;
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] < target) {
			left = mid + 1;
		} else if (nums[mid] > target) {
			right = mid - 1;
		}
	}

	return -1;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ll n;
	cin >> n;

	vector<ll> nums(n);
	rep(i, n) cin >> nums[i];

	vector<ll> b(2 * n + 1, 0);
	for (int i = 1; i <= n; ++i) b[i] = b[i - 1] + nums[i - 1];
	for (int i = 1; i <= n; ++i) b[i + n] = b[i + n - 1] + nums[i - 1];

	if (b[n] % 10ll != 0ll) {
		cout << "No" << endl;
		return 0;
	}

	for (int i = 0; i < n; ++i) {
		ll target = b[i] + b[n] / 10ll;
		ll index = binary_serach(b, target, i, b.size() - 1);
		if (index != -1) {
			cout << "Yes" << endl;
			return 0;
		}
	}

	cout << "No" << endl;

	return 0;
}
