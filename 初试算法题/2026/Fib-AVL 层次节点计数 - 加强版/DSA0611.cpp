// https://www.smqyoj.com/p/DSA0611
// https://www.smqyoj.com/record/695013aa9ba766269a4ffe81

// 此加强版要求把计算 s(h, k) 的时间复杂度优化到 O(h)，而非考试时的 O(h^2)
#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 1; // 1 <= h <= 1e6
const int MOD = (int)(1e9 + 7);

long long fac[MX];
long long inv_fac[MX];

long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

auto init = []() {
    fac[0] = 1;
    for (int i = 1; i < MX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv_fac[MX - 1] = fastPow(fac[MX - 1], MOD - 2);
    for (int i = MX - 2; i >= 0; i--) {
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    if (m > n) return 0;
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

/*
s(h, k) = s(h - 2, k - 1) + s(h - 1, k - 1)

s(h, k) 的表为：
1                        s(0, 0)
1  1                     s(1, 0)  s(1, 1)
1  2  1
1  2  3  1
1  2  4  4  1
1  2  4  7  5  1

观察 s(h, k) 的计算过程，例如 s(5, 3)：
(5, 3)
        (4, 2)
        (3, 2)
                (3, 1)
                (2, 1)
                (1, 1)
                        (2, 0)
                        (1, 0)
                        (0, 0)
                        (-1, 0)

递归基为 (2, 0) (1, 0) (0, 0) (-1, 0) ，对 s(i, 0) ，当 i >= 0 时 s(i, 0) 为 1，否则为 0

再考虑这些子问题的贡献次数（系数），实际上是：
1 * (5, 3)
            1 * (4, 2)
            1 * (3, 2)
                        1 * (3, 1)
                        2 * (2, 1)
                        1 * (1, 1)
                                    1 * (2, 0)
                                    3 * (1, 0)
                                    3 * (0, 0)
                                    1 * (-1, 0)
最后一列的系数实际上是杨辉三角的 C_{k}^{i}，i = 0, 1, ... , k
1        C_{0}^{0}
1 1      C_{1}^{0}  C_{1}^{1}
1 2 1
1 3 3 1

最后一列的递归基为 s(h - k, 0), s(h - k - 1, 0), ... , s(h - 2k)
h - 2k 可能 < 0，比如 s(5, 4) 最后是 s(-3, 0), s(-2, 0), s(-1, 0), s(0, 0), s(1, 0)
所以只需把 s(h - k, 0) 到 s(0, 0) 这 h - k + 1 个 1 乘上 C_{k}^{i}, i = 0, ... , h - k ，然后加起来就行
*/

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int h, k; cin >> h >> k;
    long long ans = 0;
    for (int i = h - k; i >= 0; i--) {
        ans = (ans + comb(k, (h - k) - i)) % MOD;
    }
    // 预处理组合数时间 O(h)，单层循环时间 O(h)，总时间复杂度 O(h)
    cout << ans;
    return 0;
}