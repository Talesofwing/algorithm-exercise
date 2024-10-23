#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N, K;
	cin >> N >> K;

	vector<int> A(N, 0), B(N, 0);
	rep(i, N) {
		cin >> A[i];
	}
	rep(i, N) {
		cin >> B[i];
	}

	int diff = 0;
	rep(i, N) {
		diff += abs(A[i] - B[i]);
	}

	if (diff % 2 == K % 2) {
		if (diff <= K) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	} else {
		cout << "No" << endl;
	}

	return 0;
}
