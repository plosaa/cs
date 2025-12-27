// https://www.smqyoj.com/p/DSA0610
// https://www.smqyoj.com/record/694fce109ba766269a4ff47d

// compile locally by: `g++ DSA0610.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 1;

long long f[3][maxn];

// 返回 n 个节点的 fib-avl，深度为 h 的层有多少个节点
int calc(int h, int k) {
    for (int i = 0; i < 3; i++) for (int j = 0; j < maxn; j++) f[i][j] = 0;
    f[0][0] = 1;
    f[1][0] = f[1][1] = 1;
    for (int i = 2; i <= h; i++) {
        f[i % 3][0] = 1;
        for (int j = 1; j <= i; j++) {
            f[i % 3][j] = ((long long)f[(i - 2 + 3) % 3][j - 1] + f[(i - 1 + 3) % 3][j - 1]);
        }
    }
    return f[h % 3][k];
}

#include "fibavl.h"
void preorder(int h) {
    // 1 <= h <= 40
    int cnt[41]{};
    long long pre[42]{}; // pre[i] 表示深度 < i 的总共有多少个节点
    for (int i = 1; i <= 41; i++) {
        pre[i] = pre[i - 1] + calc(h, i - 1);
    }

    auto dfs = [&](auto&& dfs, int h, int depth, long long id) { // id 为子问题的根的编号
        if (h < 0) return;
        print(id);
        cnt[depth]++;

        // 现在开始 dfs 子树
        // 递归子问题的难点在于，如何知道当前节点的 id ？上层的节点数可以通过计算 s[h][k] 的前缀和获取，但是本层的节点号怎么办？
        // 由于先序遍历一定会先访问完左边（同层节点一定是从左到右被访问的），所以可以直接用一个 cnt[h] 数组知道当前访问到的是本层的几号节点！
        dfs(dfs, h - 2, depth + 1, pre[depth + 1] + cnt[depth + 1]); // 左子树

        dfs(dfs, h - 1, depth + 1, pre[depth + 1] + cnt[depth + 1]); // 右子树
    };

    dfs(dfs, h, 0, 0);
}
