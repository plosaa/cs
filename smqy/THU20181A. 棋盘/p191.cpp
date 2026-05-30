// https://www.smqyoj.com/p/THU20181A

/* 写复杂了，
不需要用两个棋盘滚动，用一个vector记录各个葱的位置和状态，然后每轮都放棋盘上去并计算就行
*/

#include <bits/stdc++.h>

using namespace std;

struct Info {
    int id;
    int d, f;

    bool operator==(const Info &other) {
        return this->id == other.id && this->d == other.d && this->f == other.f;
    }
};

const int maxn = 100;

using Board = vector<Info>[maxn + 10][maxn + 10]; // t 时刻和 t - 1 时刻的棋盘

Board g[2];

pair<int, int> ans[1000 + 10];

pair<int, int> directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    int N, M, K; cin >> N >> M >> K;
    for (int id = 1; id <= K; id++) {
        int x, y, d, f; cin >> x >> y >> d >> f;
        g[0][x][y].push_back({id, d, f});
    }
    
    int T; cin >> T;

    auto legal = [&](int x, int y) {
        return 1 <= x && x <= N && 1 <= y && y <= M;
    };

    for (int t = 1; t <= T; t++) {

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                g[t % 2][i][j].clear();
            }
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (g[(t - 1) % 2][i][j].empty()) continue;
                auto [id, d, f] = g[(t - 1) % 2][i][j][0]; // 上一个棋盘一个位置最多一个元素
                auto [di, dj] = directions[d];
                int ni = i + di, nj = j + dj;
                if (!legal(ni, nj)) d = d ^ 1, ni = i, nj = j;
                g[t % 2][ni][nj].push_back({id, d, f});
            }
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (g[t % 2][i][j].empty()) continue;
                int mx_f_idx = 0;
                for (int k = 1; k < g[t % 2][i][j].size(); k++) {
                    if (g[t % 2][i][j][k].f > g[t % 2][i][j][mx_f_idx].f) {
                        mx_f_idx = k;
                    }
                }
                for (int k = 0; k < g[t % 2][i][j].size(); k++) {
                    if (k == mx_f_idx) continue;
                    auto [id, d, f] = g[t % 2][i][j][k];
                    ans[id] = {i, j};
                }
                g[t % 2][i][j][0] = g[t % 2][i][j][mx_f_idx];
                g[t % 2][i][j].resize(1);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (g[T % 2][i][j].empty()) continue;
            auto [id, d, f] = g[T % 2][i][j][0];
            ans[id] = {i, j};
        }
    }
    for (int i = 1; i <= K; i++) {
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    }
    return 0;
}