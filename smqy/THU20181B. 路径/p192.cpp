// https://www.smqyoj.com/p/THU20181B

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 991127;

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    int n; cin >> n;
    vector<i64> A(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    // O(n^2) 过不了，按位来考虑
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }
    i64 pre[32]{}; // 前缀按位来考虑的sum。相当于对 i ，在每一位上可用的接口数
    for (int b = 0; b <= 31; b++) {
        if ((A[1] >> b) & 1) pre[b] = 1;
    }

    i64 ans = 0;
    for (int i = 2; i <= n; i++) {
        i64 sum = 0; // 能通过 i 新增的接口数
        for (int b = 0; b <= 31; b++) {
            if ((A[i] >> b) & 1) {
                sum = (sum + pre[b]) % MOD;
            }
        }
        if (i == n) ans = sum; // 要在中间记录答案
        for (int b = 0; b <= 31; b++) {
            if ((A[i] >> b) & 1) {
                pre[b] = (pre[b] + sum) % MOD;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}