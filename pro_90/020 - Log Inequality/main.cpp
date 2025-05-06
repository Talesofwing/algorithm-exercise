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
#define ull unsigned long long

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	ull a, b, c;
	cin >> a >> b >> c;

	ull v2 = 1;
	for (int i = 0; i < b; ++i) {
		v2 *= c;
	}

	cout << (a < v2 ? "Yes" : "No") << endl;
}
