// https://www.smqyoj.com/p/CSP201403C

#include <bits/stdc++.h>

using namespace std;

bool valid[256];
int type[256]; // type[char] 表示 char 是否带参数

signed main(int argc, const char* argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    string line; cin >> line;
    int n; cin >> n;
    for (int i = 0; i < line.size(); i++) {
        char cur = line[i];
        if (cur == ':') {
            char a = line[i - 1];
            type[a] = true;
        }
        else {
            valid[cur] = true;
        }
    }
    string last_arg;
    cin.ignore();
    for (int i = 1; i <= n; i++) {
        map<string, string> res;
        int wait_content = false; // 是否在等待参数内容
        string s; getline(cin, s);
        stringstream ss(s);
        string t;
        ss >> t;
        while (ss >> t) {
            if (!wait_content) { // 应当见到选项
                if (t.size() != 2) break;
                if (t[0] != '-') {
                    break;
                }
                else {
                    char arg = t[1];
                    if (!valid[arg]) break;
                    if (type[arg]) wait_content = true, last_arg = t;
                    else res[t] = "";
                }
            }
            else { // 选项内容
                res[last_arg] = t;
                last_arg = "";
                wait_content = false;
            }
        }
        if (last_arg != "") res[last_arg] = "";
        cout << "Case " << i << ":";
        for (auto& [arg, cont] : res) {
            cout << ' ' << arg;
            if (cont != "") cout << ' ' << cont;
        }
        cout << '\n';
    }
    return 0;
}