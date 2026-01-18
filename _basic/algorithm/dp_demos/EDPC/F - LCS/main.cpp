# include <iostream>
# include <string>
using namespace std;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }
const long long INF = 1LL << 60;

// 入力
string s, t;

// DPテーブル
int dp[3100][3100] = {0}; // 初期値も初期条件も 0

int main() {
	cin >> s >> t;

	// DPループ
	for (int i = 0; i < s.size(); ++i) {
		for (int j = 0; j < t.size(); ++j) {
			if (s[i] == t[j]) chmax(dp[i + 1][j + 1], dp[i][j] + 1);
			chmax(dp[i + 1][j + 1], dp[i + 1][j]);
			chmax(dp[i + 1][j + 1], dp[i][j + 1]);
		}
	}

	for (int i = 0; i < s.size(); ++i) {
		for (int j = 0; j < t.size(); ++j) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}

	return 0;

	// 復元
	string res = "";
	int i = (int)s.size(), j = (int)t.size();
	while (i > 0 && j > 0) {
		// (i-1, j) -> (i, j) と更新されていた場合
		if (dp[i][j] == dp[i - 1][j]) {
			--i; // DP の遷移を遡る
		}

		// (i, j-1) -> (i, j) と更新されていた場合
		else if (dp[i][j] == dp[i][j - 1]) {
			--j; // DP の遷移を遡る
		}

		// (i-1, j-1) -> (i, j) と更新されていた場合
		else {
			res = s[i - 1] + res; // このとき s[i-1] == t[j-1] なので、t[j-1] + res でも OK
			--i, --j; // DP の遷移を遡る
		}
	}
	cout << res << endl;
}
