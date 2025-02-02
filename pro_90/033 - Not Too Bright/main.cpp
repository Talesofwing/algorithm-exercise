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

	int H, W;
	cin >> H >> W;

	if (H == 1 || W == 1) cout << H * W << endl;
	else cout << ((H + 1) / 2) * ((W + 1) / 2) << endl;
}
