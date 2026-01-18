#include <iostream>
#include <vector>

using namespace std;

int p[100000], h[100000];

int root(int x) {
	return p[x] == x ? x : p[x] = root(p[x]);
}

bool same(int x, int y) {
	return root(x) == root(y);
}

void unite(int x, int y) {
	int X = root(x);
	int Y = root(y);

	if (X == Y) {
		return;
	}

	if (h[X] < h[Y]) {
		p[X] = Y;
	} else {
		p[Y] = X;

		if (h[X] == h[Y]) {
			h[X]++;
		}
	}
}

int main() {
	int N, Q;
	cin >> N >> Q;

	for (int i = 0; i < N; ++i) {
		p[i] = i;
		h[i] = 0;
	}

	vector<string> ans;
	for (int i = 0; i < Q; ++i) {
		char q;
		int x, y;
		cin >> q >> x >> y;
		if (q == '0') {
			unite(x, y);
		} else if (q == '1') {
			if (same(x, y)) {
				ans.push_back("Yes");
			} else {
				ans.push_back("No");
			}
		}
	}

	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i] << endl;
	}
}
