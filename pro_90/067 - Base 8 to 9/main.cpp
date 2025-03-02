#include <iostream>
#include <deque>

using namespace std;

using ll = long long;

#define endl "\n"
#define min(v,u) (v < u ? v : u)
#define max(v,u) (v > u ? v : u)
#define clamp(v,l,r) (min(max(v,l),r))
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

ll base8_to_long(string N) {
	long long res = 0;
	for (int i = 0; i < N.size(); ++i) {
		res = res * 8 + int(N[i] - '0');
	}
	return res;
}

string long_to_base9(ll N) {
	if (N == 0) {
		return "0";
	}
	string res;
	while (N > 0) {
		res = char(N % 9 + '0') + res;
		N /= 9;
	}
	return res;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	string N; int K;
	cin >> N >> K;

	rep(i, K) {
		N = long_to_base9(base8_to_long(N));
		rep(j, N.size()) {
			if (N[j] == '8') {
				N[j] = '5';
			}
		}
	}

	cout << N << endl;
}
