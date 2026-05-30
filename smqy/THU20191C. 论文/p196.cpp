// https://www.smqyoj.com/p/THU20191C

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 1e9 + 7;

int n, m;

vector<i64> calc_f(vector<vector<int>> &g, vector<int>& indeg, vector<int> &time) {
    queue<int> q;
    vector<i64> f(n + 1);
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) q.push(i), f[i] = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            f[v] = max(f[v], f[u] + time[u]);
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    return f;
}

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    vector<int> time(n + 1);
    for (int i = 1; i <= n; i++) cin >> time[i];
    vector<vector<int>> graph(n + 1);
    vector<vector<int>> rgraph(n + 1);
    vector<int> indeg(n + 1);
    vector<int> rindeg(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        rgraph[v].push_back(u);
        indeg[v]++;
        rindeg[u]++;
    }
    
    auto f = calc_f(graph, indeg, time);
    i64 tot = 0;
    for (int i = 1; i <= n; i++) {
        tot = max(tot, f[i] + time[i]);
    }
    cout << tot << '\n';
    auto g = calc_f(rgraph, rindeg, time);
    for (int i = 1; i <= n; i++) {
        g[i] = tot - g[i] - time[i];
    }
    i64 t = 1;
    for (int i = 1; i <= n; i++) {
        t = t * (g[i] - f[i] + 1) % MOD;
    }
    cout << t;
    return 0;
}