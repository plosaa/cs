// https://www.smqyoj.com/p/ecnu20171F
// https://www.smqyoj.com/record/697b2b4f72e16206fab50d2d

// 莫队解法，使用vector，总用时2000+ms

#include <bits/stdc++.h>

using namespace std;

/// ┌──────────────────────────── Mo algorithm template begin ────────────────────────────┐
/// 要求外部初始化 nums, querys，resize ans，写好 move 函数，并调用 mo_solve() 进行计算
/// 答案写在 ans 中
struct Query {
    int l, r, id;
};

int BLOCK_SIZE;

bool operator<(const Query& x, const Query& y) {
    int block_x = x.l / BLOCK_SIZE;
    int block_y = y.l / BLOCK_SIZE;
    if (block_x != block_y) return block_x < block_y;
    return (block_x & 1) ? x.r < y.r : x.r > y.r; // 奇偶化排序优化
}

vector<int> nums; /// 数组元素
vector<Query> querys; /// 查询

int l = 0, r = -1; // 当前的区间 [l, r]

/// 根据题目具体情况自定义 move 维护逻辑
vector<int> freq(1e5 + 1);
int nowAns; // 当前的答案，即区间内频率为 2 的元素个数
/// 移动区间的 l, r，pos 表示增加 / 删除的元素位置，sign 为 1 表示增加了 pos 位置元素，sign 为 -1 表示删除了 pos 位置元素
void move(int pos, int sign) {
    int x = nums[pos];
    if (freq[x] == 2) nowAns--;
    freq[x] += sign;
    if (freq[x] == 2) nowAns++;
}

vector<int> ans;
void mo_solve() {
    int n = nums.size(), m = querys.size();
    BLOCK_SIZE = int(ceil(pow(n, 0.5)));
    sort(querys.begin(), querys.end());
    for (int i = 0; i < m; i++) {
        const Query &q = querys[i];
        // 这4个循环的顺序对某些题目不能随便修改，否则移动指针可能出现加入次数是负数的情况，对某些题目可能有问题，具体见oiwiki
        while (l > q.l) move(--l, 1);
        while (r < q.r) move(++r, 1);
        while (l < q.l) move(l++, -1);
        while (r > q.r) move(r--, -1);
        ans[q.id] = nowAns;
    }
}
/// └──────────────────────────── Mo algorithm template end   ────────────────────────────┘

signed main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, q; cin >> n >> q;
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[i] = x;
    }
    // nums[i] 的范围是 1e9，导致莫队中必须用 map 不能用数组作为 map，但是 nums 的元素个数只有 5e5 ，因此将其离散化
    vector<int> temp(nums);
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    for (int i = 0; i < nums.size(); i++) {
        nums[i] = lower_bound(temp.begin(), temp.end(), nums[i]) - temp.begin();
    }

    querys.resize(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r; l--, r--; // 编号从 1 开始的
        querys[i] = {l, r, i}; // (l, r, 查询的编号)
    }
    ans.resize(q);
    mo_solve();
    for (auto a : ans) {
        cout << a << '\n';
    }
    return 0;
}

/*
样例输入:
5 2
0 0 1 1 2
3 3
1 5
*/