#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <stack>

using namespace std;

#define ll long long
#define max(v,u) (v > u ? v : u)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, s, n) for (int i = s; i < n; ++i)

char maze[500][500];
bool reached[500][500];
int w, h;

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

    stack<pair<int, int>> s;
    s.push({x_index, y_index});
    while(!s.empty()) {
        pair<int, int> p = s.top();
        s.pop();
        int x = p.first, y = p.second;
        reached[x][y] = true;
        if (maze[x][y] == 'g') {
            // Found the destination
            cout << "Yes" << endl;
            return 0;
        } else {
            int nx, ny;

            nx = x + 1; ny = y;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && !reached[nx][ny] && maze[nx][ny] != '#') {
                s.push({nx, ny});
            }

            nx = x - 1; ny = y;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && !reached[nx][ny] && maze[nx][ny] != '#') {
                s.push({nx, ny});
            }

            nx = x; ny = y + 1;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && !reached[nx][ny] && maze[nx][ny] != '#') {
                s.push({nx, ny});
            }

            nx = x; ny = y - 1;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && !reached[nx][ny] && maze[nx][ny] != '#') {
                s.push({nx, ny});
            }
        }
    }

    cout << "No" << endl;
    return 0;
}