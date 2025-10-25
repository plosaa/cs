// https://www.smqyoj.com/p/DSA1005
// https://www.smqyoj.com/record/68fa163e7fc8598513db26dd

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);

    int n, m; cin >> n >> m;
    vector<vector<int>> g(n + 1); // 节点编号从 1 开始
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = INT_MAX;
    
    auto bfs = [&](int r) {
        queue<int> q;
        vector<int> vis(n + 1);
        vector<int> depth(n + 1);
        vector<int> parent(n + 1);
        int level = 0;
        q.push(r);
        vis[r] = true;
        depth[r] = 0;
        while (!q.empty()) {
            int sz = q.size();
            level++;
            for (int _ = 0; _ < sz; _++) {
                int u = q.front(); q.pop();
                for (int v : g[u]) {
                    if (vis[v]) {
                        // 排除掉无向图“一条边顶两条边”而导致的后向边（不止是 u - v - u 这种情况）
                        /* 必须通过记录 parent 关系来排除无向图 u - v ，然后 v 又到 u 的环，
                        且这种后向边报告出来的环的点数还不一定只是 3 (u - v - u)，还可能例如 1 - 2 - 3，
                        然后访问 3 -> 2 这条边的时候没排除这类后向边，算 1 + depth[u] + depth[v] 会认为是个 4 节点的环 (1 - 2 - 3 - 2)

                        通过 depth 什么的也不行，可能后向边的两个点确实 depth 差 1，
                        必须通过记录 parent 关系来排除无向图“一条边顶两条边”而导致的的这类后向边
                        */
                        if (v != parent[u]) ans = min(ans, 1 + depth[u] + depth[v]);
                    }
                    else {
                        vis[v] = true;
                        parent[v] = u;
                        depth[v] = level;
                        q.push(v);
                    }
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }

    cout << (ans == INT_MAX ? "inf" : to_string(ans)) << endl;
    return 0;
}