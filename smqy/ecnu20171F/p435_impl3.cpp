/*
url: https://www.smqyoj.com/p/ecnu20171F
参考: https://www.luogu.com.cn/article/1gdjwagl
      https://www.smqyoj.com/record/6978e82472e16206fab4ba80
相关: 洛谷P1972. HH 的项链, 洛谷P4113. 采花
*/

/* 先看洛谷P4113。
将 queries 按 r 排序，然后把贡献记在次右的出现上可以统计出现次数 >= 2 的元素种数。
用 {>=2} - {>=3} 可以求出出现恰好两次的元素种数。

但是，看参考，有个技巧可以不用封装个函数然后两次调用相减。

具体来说，我们可以把一个元素的贡献维护成这样：

x    x    x    x    x    x
0    0    0   -1    1    0

这样如果 l 再往左出现 3 次以上，求区间和会使得 -1 自动把 1 抵消掉。

考虑第二次出现时 +1，会让数组变成：

x    x    x    x    x    x
1    1    1    1    1    0

考虑第三次出现时 -2，会变成：

x    x    x    x    x    x
-1  -1   -1   -1    1    0

考虑第四次出现时 +1，会变成：

x    x    x    x    x    x
0    0    0   -1    1    0

这样就变出来了

*/

#include <bits/stdc++.h>

using namespace std;

#include <stdio.h>
int rd() {
    int k = 0, f = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != EOF) f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return f ? k : -k;
}
void wr(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}

const int maxn = 5e5 + 2;

int n, m;

int nums[maxn];

int temp[maxn];

// Q[i] = (l, id)，表示 id 号 [l, r] 查询。这种写法把所有右边界为 r 的 query 挂在 Q[r] 中。
// 另外一种写法： struct Op {type, l, r, id} op[k * maxn]; 见洛谷/p1972_impl3.cpp

// vector要发生动态内存分配才显慢，例如发生push_back，或者vector<vector<pair<int, int>>> Q(maxn);的写法
// 和全局数组`pair<int, int> Q[maxn];`不一样，这maxn个全局vector初始化时调构造函数会被oj算进运行时间，但是：
// 由于这maxn个vector是空的，构造时不会涉及动态内存分配，且1e5的规模其实很小，
// 相当于只是初始化这maxn个连续的struct vector的内存为0，实际这个写法这里初始化的耗时基本没有。
vector<pair<int, int>> Q[maxn];

// maxn在vector的构造函数参数位置，动态分配了maxn个struct vector，内层vector没发生动态内存分配，
// 若用这写法在 smqyoj 上会直接报virtual memory exhausted: Cannot allocate memory
// 但是我本地测这个二层vector初始化也就2ms，不应该报错啊
// vector<vector<pair<int, int>>> Q(maxn);

int last[maxn]; // last[i] 表示 nums[i] 这个值在 nums 中的上一次出现位置，没出现就是 0
int pos[maxn]; // pos[x] 表示 x 的上一次出现位置

int ans[maxn];

int tree[maxn + 1];

int lowbit(int x) { return x & -x; }

void modify(int index, int diff) {
    // for (int i = index + 1; i < n + 1; i += lowbit(i)) {
    for (int i = index; i < n + 1; i += lowbit(i)) { // 外部已经是 1-based ，传入的 index 不用 +1
        tree[i] += diff;
    }
}

int pre_sum(int R) {
    // R++; // 外部已经是 1-based ，传入的 index 不用 +1
    int sum = 0;
    while (R > 0) {
        sum += tree[R];
        R -= lowbit(R);
    }
    return sum;
}

int query(int L, int R) {
    return pre_sum(R) - pre_sum(L - 1);
}

int main(int argc, char const *argv[]) {
    n = rd(), m = rd();
    // a[i] 是 1e9 范围，元素个数是 5e5 范围，且问题情景不关心具体值，离散化
    for (int i = 1; i <= n; i++) {
        int x = rd();
        nums[i] = temp[i] = x;
    }
    sort(temp + 1, temp + 1 + n);
    int total = unique(temp + 1, temp + 1 + n) - (temp + 1);
    for (int i = 1; i <= n; i++) {
        nums[i] = lower_bound(temp + 1, temp + 1 + total, nums[i]) - (temp + 1);
        last[i] = pos[nums[i]];
        pos[nums[i]] = i;
    }
    for (int i = 1; i <= m; i++) {
        int l = rd(), r = rd();
        Q[r].push_back({l, i});
    }
    for (int r = 1; r <= n; r++) { // 扫描线从左到右扫的是 nums 的下标，然后通过 Q[r] 找到 r 为右边界的所有查询，query 被挂到了 r 位置
        // 加点
        if (last[r]) modify(last[r], 1); // 每个从右往左数第二次出现的位置，+1
        if (last[last[r]]) modify(last[last[r]], -2); // 第三次出现
        if (last[last[last[r]]]) modify(last[last[last[r]]], 1); // 第四次出现
        for (auto [l, id] : Q[r]) {
            ans[id] = query(l, r);
        }
    }
    for (int i = 1; i <= m; i++) {
        wr(ans[i]); putchar('\n');
    }

    return 0;
}