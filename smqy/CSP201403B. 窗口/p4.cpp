#include <bits/stdc++.h>

using namespace std;

struct Window {
    int x1, y1, x2, y2;
    int z;
};

signed main(int argc, const char* argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<Window> win;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        win.push_back({x1, y1, x2, y2, i});
    }
    int t = n;
    for (int _ = 0; _ < m; _++) {
        int x, y; cin >> x >> y;
        int max_z = -1;
        int res = -1;
        for (int i = 0; i < n; i++) {
            auto [x1, y1, x2, y2, z] = win[i];
            if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
                if (z > max_z) {
                    res = i;
                    max_z = z;
                }
            }
        }
        if (res != -1) {
            win[res].z = t++;
            cout << res + 1 << '\n'; // 窗口编号从 1 开始
        }
        else cout << "IGNORED" << '\n';
    }
}