// https://www.smqyoj.com/p/THU20171B

#include <bits/stdc++.h>

using namespace std;

int n, m;
char grid[1001][1001];
bool discovered[1001][1001];
bool flagged[1001][1001];

string over_status;

int total_step;

int blank_cnt;
int discovered_blank_cnt;

struct Info {
    bool boom = false;
    int cnt = 0;
    set<pair<int, int>> nodes; // 一次 sweep 打开的点
};

vector<pair<int, int>> directions = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};

bool legal(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

// 现场算周围炸弹数
int count_bomb(int x, int y) {
    int cnt = 0;
    for (auto [dx, dy] : directions) {
        int xx = x + dx, yy = y + dy;
        if (legal(xx, yy) && grid[xx][yy] == '*') {
            cnt++;
        }
    }
    return cnt;
}

// 现场算周围旗帜数
int count_flag(int x, int y) {
    int cnt = 0;
    for (auto [dx, dy] : directions) {
        int xx = x + dx, yy = y + dy;
        if (legal(xx, yy) && flagged[xx][yy]) {
            cnt++;
        }
    }
    return cnt;
}

// (x, y) 未被打开时调用，去 dfs。first 判断函数调用是否是点击的那次
// 第一次调用点到炸弹是炸，后面是不开
void sweep_dfs(Info& info, int x, int y, bool first = true) {
    if (first) {
        if (grid[x][y] == '*') {
            info.boom = true;
            return;
        }
        else {
            discovered[x][y] = true;
            flagged[x][y] = false;
            info.nodes.insert({x, y});
            if (count_bomb(x, y) != 0) return;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (!legal(xx, yy) || discovered[xx][yy]) continue;
                if (grid[xx][yy] == '.') {
                    info.nodes.insert({xx, yy});
                    discovered[xx][yy] = true;
                    flagged[xx][yy] = false;
                    if (count_bomb(xx, yy) == 0) sweep_dfs(info, xx, yy, false);
                }
            }
        }
    }
    else {
        if (grid[x][y] == '.') {
            discovered[x][y] = true;
            flagged[x][y] = false;
            info.nodes.insert({x, y});
            if (count_bomb(x, y) != 0) return;
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (!legal(xx, yy) || discovered[xx][yy]) continue;
                if (grid[xx][yy] == '.') {
                    info.nodes.insert({xx, yy});
                    discovered[xx][yy] = true;
                    flagged[xx][yy] = false;
                    if (count_bomb(xx, yy) == 0) sweep_dfs(info, xx, yy, false);
                }
            }
        }
    }
}

bool check_succ() {
    return blank_cnt == discovered_blank_cnt;
}

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case3.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = 1; j <= m; j++) {
            if (s[j - 1] == '.') blank_cnt++;
            grid[i][j] = s[j - 1];
        }
    }
    cin.ignore();
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string s;
        ss >> s;
        if (s == "Quit") {
            cout << "give up" << '\n';
            cout << "total step " << total_step << '\n';
            return 0;
        }

        int x, y; ss >> x >> y;
        total_step++;
        if (s == "Flag") {
            if (discovered[x][y]) {
                cout << "swept" << '\n';
            }
            else {
                if (!flagged[x][y]) flagged[x][y] = true, cout << "success" << '\n';
                else flagged[x][y] = false, cout << "cancelled" << '\n';
            }
        }
        else if (s == "Sweep") {
            if (discovered[x][y]) cout << "swept" << '\n';
            else {
                if (flagged[x][y]) cout << "flagged" << '\n';
                else { // 方块未打开
                    Info info;
                    sweep_dfs(info, x, y, true);
                    if (info.boom) {
                        cout << "boom" << '\n';
                        over_status = "game over";
                        goto OVER;
                    }
                    else {
                        if (info.nodes.empty()) {
                            cout << "no cell detected" << '\n';
                        }
                        else {
                            discovered_blank_cnt += info.nodes.size();
                            cout << info.nodes.size() << " cell(s) detected" << '\n';
                            for (auto [x, y] : info.nodes) {
                                cout << x << ' ' << y << ' ' << count_bomb(x, y) << '\n';
                            }
                        }
                    }
                }
            }
            if (check_succ()) {
                over_status = "finish";
                goto OVER;
            }
        }
        else if (s == "DSweep") {
            if (!discovered[x][y]) {
                cout << "not swept" << '\n';
            }
            else {
                if (count_bomb(x, y) == 0 || count_bomb(x, y) != count_flag(x, y)) {
                    cout << "failed" << '\n';
                }
                else {
                    Info info;
                    for (auto [dx, dy] : directions) {
                        int xx = x + dx, yy = y + dy;
                        if (legal(xx, yy) && !flagged[xx][yy] && !discovered[xx][yy]) sweep_dfs(info, xx, yy, true);
                    }
                    if (info.boom) {
                        cout << "boom" << '\n';
                        over_status = "game over";
                        goto OVER;
                    }
                    else {
                        if (info.nodes.empty()) {
                            cout << "no cell detected" << '\n';
                        }
                        else {
                            discovered_blank_cnt += info.nodes.size();
                            cout << info.nodes.size() << " cell(s) detected" << '\n';
                            for (auto [x, y] : info.nodes) {
                                cout << x << ' ' << y << ' ' << count_bomb(x, y) << '\n';
                            }
                        }
                    }
                }
            }
            if (check_succ()) {
                over_status = "finish";
                goto OVER;
            }
        }
    }
    OVER:
    cout << over_status << '\n';
    cout << "total step " << total_step << '\n';
    return 0;
}