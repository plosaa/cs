// https://www.smqyoj.com/p/THU20253A

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n; cin >> n;
    vector<pair<i64, i64>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    i64 ans[4]{};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto [x, y] = a[i];
            auto [xx, yy] = a[j];
            if (xx == x) continue;
            i64 dy = yy - y, dx = xx - x;
            if (dy == dx) ans[1]++;
            if (dy == 2 * dx) ans[2]++;
            if (dy == 3 * dx) ans[3]++;
        }
    }
    cout << ans[1] << '\n';
    cout << ans[2] << '\n';
    cout << ans[3] << '\n';
    return 0;
}