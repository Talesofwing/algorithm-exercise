#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	// h: row
	// w: column
	int h, w;
	cin >> h >> w;
	vector<vector<int>> a(h, vector<int>(w));
	rep(i, h) {
		rep(j, w) {
			cin >> a[i][j];
		}
	}

	// Pre-processing
	vector<int> total_h(h, 0);
	vector<int> total_w(w, 0);
	rep(i, h) {
		rep(j, w) {
			total_h[i] += a[i][j];
			total_w[j] += a[i][j];
		}
	}

	rep(i, h) {
		rep(j, w) {
			cout << total_h[i] + total_w[j] - a[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
