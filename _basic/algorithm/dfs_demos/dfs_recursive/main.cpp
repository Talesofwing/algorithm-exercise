#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

#define LL long long
#define max(v,u) (v > u ? v : u)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

char maze[500][500];
bool reached[500][500];
int w, h;

bool dfs(int x, int y) {
    if (x < 0 || x >= w || y < 0 || y >= h || maze[x][y] == '#')
        return false;

    if (reached[x][y])
        return false;

    if (maze[x][y] == 'g') {
        return true;
    }

    reached[x][y] = true;

    if (dfs(x + 1, y))
        return true;
          
    if (dfs(x - 1, y))
        return true;

    if (dfs(x, y + 1))
        return true;

    if (dfs(x, y - 1))
        return true;

    return false;
}

int main() {
    cin >> w >> h;

    int x_index, y_index;
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            char c;
            cin >> c;
            maze[x][y] = c;
            if (c == 's') {
                x_index = x;
                y_index = y;
            }
        }
    }

    if (dfs(x_index, y_index)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}