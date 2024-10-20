#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

using ll = long long;

#define endl "\n"
#define min(v,u) (v < u ? v : u)
#define max(v,u) (v > u ? v : u)
#define clamp(v,l,r) (min(max(v,l),r))
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

int result = 0;

void dfs(int curr_idx, int prev_idx, int curr_count, int max_count, vector<int> &a) {
    if (a.size() - curr_idx - 2 < max_count - curr_count) {
        // not enough
        return;
    }

    if (curr_count != 0) {
        int value1 = max(result, a[curr_idx] - a[prev_idx]);
        if (curr_count == max_count) {
            value1 = min(value1, a[a.size() - 1] - a[curr_idx]);
        }
        cout << "value: " << value1 << endl;
    }

    rep2(i, curr_idx + 1, a.size() - 1) {
        dfs(i, curr_idx, curr_count + 1, max_count, a);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, l, k;
    cin >> n >> l >> k;
    vector<int> a(n + 2, 0);
    rep2(i, 1, n + 1) {
        cin >> a[i];
    }
    a[n + 1] = l;

    dfs(1, 0, 0, k, a);

    cout << result << endl;

    return 0;
}