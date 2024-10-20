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

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<int> group1(N + 1, 0), group2(N + 1, 0);
    rep2(i, 1, N + 1) {
        int group, score;
        cin >> group >> score;
        if (group == 1) {
            group1[i] = score + group1[i - 1];
            group2[i] = group2[i - 1];
        } else if (group == 2) {
            group2[i] = score + group2[i - 1];
            group1[i] = group1[i - 1];
        }
    }

    int Q;
    cin >> Q;
    vector<pair<int, int>> queries(Q);
    rep(i, Q) {
        cin >> queries[i].first >> queries[i].second;
    }

    rep(i, Q) {
        auto[min, max] = queries[i];
        int group1_sum = group1[max] - group1[min - 1], group2_sum = group2[max] - group2[min - 1];
        cout << group1_sum << " " << group2_sum << endl;
    }

    return 0;
}