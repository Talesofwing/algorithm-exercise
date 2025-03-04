#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#define endl "\n"
#define min(v,u) (v < u ? v : u)
#define max(v,u) (v > u ? v : u)
#define clamp(v,l,r) (min(max(v,l),r))
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

int main() {
	int N, M;
	cin >> N >> M;
	vector<int> counts(N, 0);
	rep(i, M) {
		int a, b;
		cin >> a >> b;
		if (a < b) {
			int temp = a;
			a = b;
			b = a;
		}
		counts[a - 1]++;
	}

	int total = 0;
	rep(i, N) {
		if (counts[i] == 1) {
			total++;
		}
	}

	cout << total << endl;
}
