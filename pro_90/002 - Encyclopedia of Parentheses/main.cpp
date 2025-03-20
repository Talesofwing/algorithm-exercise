#include <iostream>

using namespace std;

#define endl "\n"
#define rep(i, n) for (int i = 0; i < n; ++i)

bool isValid(const string& s) {
	int score = 0;
	for (auto c : s) {
		if (c == '(') ++score;
		else if (c == ')') --score;
		if (score < 0) return false;
	}

	return score == 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N;
	cin >> N;
	if (N % 2 == 1) return 0;

	for (int bit = 0; bit < (1 << N); ++bit) {
		string s = "";

		for (int i = N - 1; i >= 0; --i) {
			if (!(bit & (1 << i))) s += '(';
			else s += ')';
		}

		if (isValid(s)) cout << s << endl;
	}

	return 0;
}
