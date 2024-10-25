#include <iostream>
#include <queue>

using namespace std;

char maze[51][51];
bool reached[51][51];
int R, C;

int main() {
    // from 1 to 50

    // R : row(行)
    // C : column(列)
    cin >> R >> C;
    int sy, sx, gy, gx;     // y: row(行), x: column(列)
    cin >> sy >> sx >> gy >> gx;

    for(int i = 1; i <= R; i++)
        for(int j = 1; j <= C; j++)
            cin >> maze[i][j];

    int count = 0;
    queue<pair<int, int>> cache;
    queue<pair<int, int>> q;
    q.push({sy, sx});
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int y = p.first, x = p.second;

        if (!reached[y][x]) {
            if (y == gy && x == gx) {
                cout << count << endl;
                break;
            }
            reached[y][x] = true;

            // up
            if (y - 1 >= 1 && maze[y - 1][x] != '#') {
                cache.push({y - 1, x});
            }
            // down
            if (y + 1 <= R && maze[y + 1][x] != '#') {
                cache.push({y + 1, x});
            }
            // left
            if (x - 1 >= 1 && maze[y][x - 1] != '#') {
                cache.push({y, x - 1});
            }
            // right
            if (x + 1 <= C && maze[y][x + 1] != '#') {
                cache.push({y, x + 1});
            }
        }

        if (q.empty()) {
            swap(q, cache);
            count++;
        }
    }

    return 0;
}
