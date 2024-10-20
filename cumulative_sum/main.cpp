#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define endl "\n"
#define max(v,u) (v > u ? v : u)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

int main() {
  int N, Q;
  string S;
  cin >> N >> Q >> S;
  vector<int> counts(N, 0);
  rep2(i, 1, N) {
    counts[i] = counts[i - 1] + (S[i] == S[i - 1]);
  }

  rep(i, Q) {
    int L, R;
    cin >> L >> R;
    --L;
    --R;
    cout << counts[R] - counts[L] << endl;
  }
}