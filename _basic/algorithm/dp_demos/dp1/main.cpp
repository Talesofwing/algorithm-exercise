#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long dp(int idx, bool less, bool hasForbidden, const string& num, vector<vector<vector<long long>>>& memo) {
	if (idx == num.size()) {
		return hasForbidden;
	}

	if (memo[idx][less][hasForbidden] != -1) {
		cout << "\tres: " << memo[idx][less][hasForbidden] << endl;
		return memo[idx][less][hasForbidden];
	}

	long long res = 0;
	int maxDigit = less ? 9 : (num[idx] - '0');
	for (int d = 0; d <= maxDigit; ++d) {
		res += dp(idx + 1, less || d < maxDigit, hasForbidden || d == 4 || d == 9, num, memo);
	}

	memo[idx][less][hasForbidden] = res;
	return res;
}


long long forbiddenCount(long long n) {
	if (n < 0) {
		return 0;
	}

	string num = to_string(n);

	// First dimension: digits
	// Second dimension: less than previous digit
	// Third dimension: has forbidden digit
	vector<vector<vector<long long>>> memo(num.size(), vector<vector<long long>>(2, vector<long long>(2, -1)));
	return dp(0, false, false, num, memo);
}

int main() {
	long long A, B;
	cin >> A >> B;
	cout << forbiddenCount(B) - forbiddenCount(A - 1) << endl;
	return 0;
}
