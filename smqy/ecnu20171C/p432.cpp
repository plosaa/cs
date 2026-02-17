#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, x, y; cin >> n >> x >> y;
    // f[i] 需要依赖父问题吗？1 2 4 8 7 ，是的
    // 但是到达 i 的前前一步一定在 i 的左边，用 i 的前前一步做转移，证明:
    // 若到达 i 的最后需要 >= 2 步 -1 ，例如是 ? ... i + 2, i + 1, i，
    // 若 ? 是 +1，则可以抵消一对 +1, -1 ，得到更优
    // 若 ? 是 *2，例如 5 10 9 8，不如修改成 5 4 8 得到更优
    vector<i64> f(n + 1, INT64_MAX);
    f[1] = x;
    for (int i = 2; i <= n; i++) {
        // 到达 i 的前一步是 -1，则前前一步一定是 加倍
        if ((i + 1) % 2 == 0) {
            f[i] = min(f[i], f[(i + 1) / 2] + y + x);
        }

        // 到达 i 的前一步是 +1
        f[i] = min(f[i], f[i - 1] + x);

        // 到达 i 的前一步是 加倍
        if (i % 2 == 0) f[i] = min(f[i], f[i / 2] + y);
    }
    cout << f[n];
    return 0;
}