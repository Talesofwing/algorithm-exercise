#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <numbers>

using namespace std;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)
#define ll long long

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed << setprecision(12);

	long double T, L, X, Y;
	cin >> T >> L >> X >> Y;

	long double half_l = L / 2.0;

	int Q;
	cin >> Q;
	rep(i, Q) {
		ll E;
		cin >> E;

		long double e_t = E / T * numbers::pi * 2;

		long double x = 0;
		long double y = -half_l * sin(e_t);
		long double z = half_l - half_l * cos(e_t);
		long double diff_x = X - x;
		long double diff_y = Y - y;
		long double diff_z = 0 - z;
		long double length = sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
		long double ans = 90.0 - acos(z / length) * 180 / 3.1415926535897932;
		cout << ans << endl;
	}
}
