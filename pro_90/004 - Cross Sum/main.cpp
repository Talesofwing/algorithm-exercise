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

    // h: 行
    // w: 列
    int h, w;
    cin >> h >> w;
    vector<vector<int>> a(h, vector<int>(w));
    rep(i, h)
        rep(j, w)
            cin >> a[i][j];

    // 前置處理
    vector<int> total_h(h, 0);
    vector<int> total_w(w, 0);
    rep(i, h) {
        rep(j, w) {
            total_h[i] += a[i][j];
            total_w[j] += a[i][j];
        }
    }

    rep(i, h) {
        rep(j, w) {
            cout << total_h[i] + total_w[j] - a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}