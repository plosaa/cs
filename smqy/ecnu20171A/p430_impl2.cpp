#include <bits/stdc++.h>

using namespace std;

// 参考 Mario 解法，差分的思想。枚举最终的区间包含的一个数的值，再遍历一遍所有式子判断（式子个数只有 200 个，所以二重循环没问题）
int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n; cin >> n;
    set<int> cand;
    vector<pair<string, int>> ops;
    for (int i = 0; i < n; i++) {
        char X; string op; int C;
        cin >> X >> op >> C;
        if (op == "<") op = "<=", C--;
        if (op == ">") op = ">=", C++;
        ops.push_back({op, C});
        cand.insert(C);
    }
    int ans = 0;
    for (int x : cand) {
        int res = 0;
        for (auto &[o, C] : ops) {
            if (o == "=") res += (C == x);
            else if (o == "<=") res += (C >= x);
            else if (o == ">=") res += (C <= x);
        }
        ans = max(ans, res);
    }
    cout << ans;
    return 0;
}