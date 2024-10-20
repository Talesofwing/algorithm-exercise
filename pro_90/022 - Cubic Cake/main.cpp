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

struct Cube {
public:
    ll x, y, z;
    Cube(ll x, ll y, ll z) : x(x), y(y), z(z) {}
    bool isCube() { return x == y && y == z; }
};

void split_cube() {
    ll A, B, C;
    cin >> A >> B >> C;
    Cube cube(A, B, C);

    queue<Cube> q;
    q.push(cube);
    ll count = 0;
    while (!q.empty()) {
        Cube c  = q.front();
        q.pop();
        if (c.isCube()) {
            continue;
        } else {
            count++;
            if (c.x < c.y) {
                ll diff = c.y - c.x;
                q.push(Cube(c.x, c.y - diff, c.z));
                q.push(Cube(c.x, diff, c.z));
            } else if (c.x > c.y) {
                ll diff = c.x - c.y;
                q.push(Cube(c.x - diff, c.y, c.z));
                q.push(Cube(diff, c.y, c.z));
            } else if (c.x < c.z) {
                ll diff = c.z - c.x;
                q.push(Cube(c.x, c.y, c.z - diff));
                q.push(Cube(c.x, c.y, diff));
            } else if (c.x > c.z) {
                ll diff = c.x - c.z;
                q.push(Cube(c.x - diff, c.y, c.z));
                q.push(Cube(diff, c.y, c.z));
            }
        }
    }
    cout << count << endl;
}

ll gcd(ll a, ll b) {
    if (b == 0) return a;

    if (a >= b) {
        return gcd(b, a % b);
    } else {
        return gcd(a, b % a);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll A, B, C;
    cin >> A >> B >> C;

    ll g = gcd(A, gcd(B, C));
    ll count = A / g + B / g + C / g - 3;
    cout << count << endl;

    return 0;
}