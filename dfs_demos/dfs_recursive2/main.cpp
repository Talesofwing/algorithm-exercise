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

string S;
string words[4]{ "dream", "dreamer", "erase", "eraser" };
string reversedWords[4]{ "maerd", "remaerd", "esare", "resare" };

bool dfs(string s) {
    if (s == S) {
        return true;
    }

    if (s.size() >= S.size()) {
        return false;
    }

    for (int i = 0; i < 4; ++i) {
        if (dfs(s + words[i])) {
            return true;
        }
    }

    return false;
}

int main() {
    cin >> S;
    reverse (S.begin(), S.end());

    while (S.size() > 0) {
        bool matched = false;
        for (int i = 0; i < 4; ++i) {
            string word = reversedWords[i];
            if (S.starts_with(word)) {
                S = S.substr(word.size(), S.size());
                // S.erase(0, word.size());     // slow method
                matched = true;
            }
        }

        if (!matched)
            break;
    }

    if (S.size() <= 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    // if (dfs("")) {
    //     cout << "YES" << endl;
    // } else {
    //     cout << "NO" << endl;
    // }
}