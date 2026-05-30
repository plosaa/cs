// https://www.smqyoj.com/p/CSP201403D

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

struct Node {
    int id;
    int x, y;
    int type; // 1 表示是候选节点
};

int vis[301][301];

signed main(int argc, const char* argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k, r; cin >> n >> m >> k >> r;
    vector<Node> nodes;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        nodes.emplace_back(nodes.size(), x, y, 0);
    }
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        nodes.emplace_back(nodes.size(), x, y, 1);
    }
    vector<pair<int, int>> edges;
    for (int i = 0; i < n + m; i++) {
        for (int j = i + 1; j < n + m; j++) {
            i64 x1 = nodes[i].x, y1 = nodes[i].y;
            i64 x2 = nodes[j].x, y2 = nodes[j].y;
            if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= r * 1LL * r) {
                edges.push_back({nodes[i].id, nodes[j].id});
            }
        }
    }
    vector<vector<int>> g(n + m);
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // bfs 搜，有最多只能用 k 个候选的约束
    queue<pair<int, int>> q; // (节点，剩余候选点次数)
    q.push({0, k}); // 从 0 走到 1
    vis[0][k] = true;
    int level = 1;
    while (!q.empty()) {
        for (int _ = q.size(); _ > 0; _--) {
            auto [node, cnt] = q.front(); q.pop();
            if (node == 1) { cout << level - 2 << '\n'; return 0; };
            for (int nbr : g[node]) {
                if (nodes[nbr].type == 0) {
                    if (!vis[nbr][cnt]) q.push({nbr, cnt}), vis[nbr][cnt] = true;
                }
                else if (cnt > 0) {
                    if (!vis[nbr][cnt - 1]) q.push({nbr, cnt - 1}), vis[nbr][cnt - 1] = true;
                }
            }
        }
        level++;
    }
    return 0;
}