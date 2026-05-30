// https://www.smqyoj.com/p/THU20151D

#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int mx_size = 1; // 最大分量

    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        if (size[rx] < size[ry]) {
            parent[rx] = ry;
            size[ry] += size[rx];
            mx_size = max(mx_size, size[ry]);
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
            mx_size = max(mx_size, size[rx]);
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int getSize(int x) {
        return size[find(x)];
    }

    int is_connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k; cin >> n >> m >> k;
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; // 节点编号从 1 开始的
        edges.push_back({u - 1, v - 1, w});
    }
    sort(edges.begin(), edges.end(), [&](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) > get<2>(b);
    });
    UnionFind uf(n);
    int ans = 0;
    for (auto [u, v, w] : edges) {
        uf.unite(u, v);
        if (uf.mx_size >= k) { // 也可以不用记录 mx_size，unite 后 get_size(u) 检查就行了
            ans = w;
            break;
        }
    }
    cout << ans << '\n';
    return 0;
}