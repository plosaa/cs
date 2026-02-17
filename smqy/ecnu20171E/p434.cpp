// 参考 Mario 代码

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int P, N1, N5, N10, N25; // 价格，1，5，10，25 的硬币数
    cin >> P >> N1 >> N5 >> N10 >> N25;
    // f[i] = f[i - v] + 1; 但 1e8 的范围，不能背包

    int ans = -1;

    /*
    贪心优先选小币值最多不一定是对的，小范围枚举一下
    观察这件事：
    ans 里，"面值为 1 的选择个数"可不可能 <= min(P, N1) - 25 ？
    不可能，
    1. 若 ans 有更大的面值，把其中至少一张大面值变成 多个 1 更优
    2. 若 ans 没有更大的面值，min(P, N1) 就是答案
    所以只需枚举 [ubound - 24, ubound] 即可
    同样的道理，后面的 5 10 25 满足 5 * n5 + 10 * n10 + 25 * n25 = P_left，
    如果要 ans 选 10 和 25，那么说明 5 不够，那么 5 的张数相对 ubound 减少量不会 >= max(10, 25) / 5，
    因为如果 5 的剩余张数 > 5 且答案果真要用 10 和 25，那么剩余的这几张 5 一定可以用来替换并获得更大张数。
    或者这样来看，要用 10 和 25 说明 5 不够，那么剩余的 5 张 5，一定可以用来替换至少存在一张的 10 / 25，得到更优
    
    对于枚举 10 和 25 的情况，情况有些不同，10 不是 25 的因子，没包含关系。这时候要求的是 10x + 25y = P_left 的约束下，x + y 的最大值，
    10x + 25y = P_left 在 x轴 的截距大，在 y轴 的截距小，所以最优解在 x 最大(10 选最多)的位置，但是还要考虑整数问题，
    10x + 25y = k，y = (k - 10x) / 25，如果 y 能成为整数，枚举 x 多少次一定会出现？
    首先 k 需要是 5 的倍数，设 k = 5k'，则等价于 10x ≡ 5k'(mod 25)，即 2x ≡ k'(mod 5)，于是 2x - k' ≡ 0 (mod 5)，而
    k' 是 5 的倍数，所以充要条件是 x 是 5 的倍数。于是，只需要倒着枚举 10 的 5 种选择个数就行了
    */
    for (int i = 0; i < 25; i++) { // 从高到低枚举 25 次
        int n1 = min(P, N1) - i; // 1 的最大选择个数是 min(P, N1)，是上限
        if (n1 < 0) break;
        int Q = P - n1;
        for (int j = 0; j < 5; j++) { // 从高到低枚举 5 次
            int n5 = min(Q / 5, N5) - j;
            if (n5 < 0) break;
            int R = Q - n5 * 5;
            for (int k = 0; k < 5; k++) { // 从高到低枚举 5 次
                int n10 = min(R / 10, N10) - k;
                if (n10 < 0) break;
                int S = R - n10 * 10;
                if (S % 25 == 0 && S / 25 <= N25) {
                    ans = max(ans, n1 + n5 + n10 + S / 25);
                }
            }
        }
    }

    if (ans != -1) cout << ans << '\n';
    else cout << "Impossible" << '\n';
    return 0;
}