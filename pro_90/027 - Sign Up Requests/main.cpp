#include <iostream>
#include <unordered_set>
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
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	unordered_set<string> S;
	vector<int> records;
	rep(i, N) {
		string s;
		cin >> s;
		if (!S.contains(s)) {
			S.insert(s);
			records.push_back(i + 1);
		}
	}

	rep(i, records.size()) {
		cout << records[i] << endl;
	}

	return 0;
}
