#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

#define ll long long
#define endl "\n"
#define max(v,u) (v > u ? v : u)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

int p[100000], h[100000];

int root(int x) {
  return p[x] == x ? x : p[x] = root(p[x]);
}

bool same(int x, int y) {
  return root(x) == root(y);
}

void unite(int x, int y) {
  int X = root(x);
  int Y = root(y);

  // 相同的父節點
  if (X == Y) return;

  if (h[X] < h[Y]) {
    p[X] = Y;
  } else {
    p[Y] = X;

    // 維護高度
    if (h[X] == h[Y]) 
      h[X]++;
  }
}

int main() {
  int N, Q;
  cin >> N >> Q;

  // 初始化Union_Find樹
  for (int i = 0; i < N; ++i) {
    p[i] = i;
    h[i] = 0;
  }

  vector<string> ans;
  // 讀取命令
  for (int i = 0; i < Q; ++i) {
    char q;
    int x, y;
    cin >> q >> x >> y;
    if (q == '0') {
      unite(x, y);
    } else if (q == '1') {
      if (same(x, y)) {
        ans.push_back("Yes");
      } else {
        ans.push_back("No");
      }
    }
  }

  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i] << endl;
  }
}