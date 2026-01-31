/*
url: https://www.smqyoj.com/p/ecnu20171F
参考: https://www.luogu.com.cn/article/1gdjwagl
      https://www.smqyoj.com/record/6978e82472e16206fab4ba80
相关: 洛谷P1972. HH 的项链, 洛谷P4113. 采花
*/

/* 与 p435_impl3.cpp, p435_impl4.cpp 的写法对比，
扫描线扫 Q，然后通过 p 指针根据 q.r 加点，类似 洛谷/p4113.cpp 的写法
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

struct Query { int l, r, id; } Q[maxn];
bool cmp(const Query& a, const Query& b) {
    return a.r < b.r;
}

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
        Q[i] = {l, r, i};
    }
    sort(Q + 1, Q + 1 + m, cmp);
    int p = 1; // nums[1, p)的部分的贡献情况已经加入
    for (int i = 1; i <= m; i++) { // 扫描线从左到右扫的是 Q 的下标(或者说 queries 的 r，query 被挂到了 r 位置)，然后通过 p 指针根据 Q[i].r 加点
        // 加点
        auto [l, r, id] = Q[i];
        for (; p <= r; p++) {
            if (last[p]) modify(last[p], 1); // 每个从右往左数第二次出现的位置，+1
            if (last[last[p]]) modify(last[last[p]], -2); // 第三次出现
            if (last[last[last[p]]]) modify(last[last[last[p]]], 1); // 第四次出现
        }
        
        ans[id] = query(l, r);
    }
    for (int i = 1; i <= m; i++) {
        wr(ans[i]); putchar('\n');
    }

    return 0;
}