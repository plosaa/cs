// https://www.smqyoj.com/p/THU20253C
// 讲评地址: https://www.bilibili.com/video/BV1NRwuzsEj4/
/* 还有个用容斥的解法，<https://www.smqyoj.com/record/69b67a895b27d07ec10965fa>
记 A0 = 不含数字0的区间集合，A1 = 不含数字1的区间集合，A2 = 不含数字2的区间集合，
合法区间数 = 总区间数 - |A0 ∪ A1 ∪ A2|，
然后 |A0 ∪ A1 ∪ A2| = 不含0 + 不含1 + 不含2 - (只含0 + 只含1 + 只含2) + 0，
等式右边通过线段树维护计数
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5;

int a[maxn + 10];

int n, q;

using i64 = long long;

int state_change[8][3]; // 每种区间状态，加上 0 / 1 / 2 (超过 3 的对 3 取模)，会转换到哪种状态

auto init = []() {
    for (int state = 1; state <= 7; state++) {
        for (int j = 0; j <= 2; j++) {
            string s;
            s.push_back(((state >> 2) & 1) + '0');
            s.push_back(((state >> 1) & 1) + '0');
            s.push_back(((state >> 0) & 1) + '0');
            rotate(s.begin(), s.begin() + j, s.end());
            state_change[state][j] = stoi(s, 0, 2);
        }
    }
    return 0;
}();

struct Node {
    i64 cnt; // 合法区间数
    array<i64, 8> left;
    array<i64, 8> right;
    int tot_or;
    int lazy = 0;
};

// 区间更新，只查询根的cnt，无需记录lazy，把树上节点的每个值都当成懒惰标记就行，
// 且单点查询时不需要 pushdown，记录祖先 lazy 的和即可
class SegTree {
public:
    vector<Node> tree;
private:
    int n;

    void build(vector<int>& nums, int s, int t, int p) {
        if (s == t) {
            array<i64, 8> left{};
            left[1 << nums[s]] = 1;
            array<i64, 8> right{};
            right[1 << nums[s]] = 1;
            tree[p] = {0, left, right, 1 << nums[s], 0};
            return;
        }
        int m = s + ((t - s) >> 1);
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(s, t, p);
    }

    void update_node(int val, int p) {
        auto& node = tree[p];
        // 合法区间数不会变
        array<i64, 8> new_left{};
        for (int state = 1; state <= 7; state++) {
            new_left[state_change[state][val % 3]] += node.left[state]; // 状态转移是个双射，不用 +=
        }
        array<i64, 8> new_right{};
        for (int state = 1; state <= 7; state++) {
            new_right[state_change[state][val % 3]] += node.right[state];
        }
        node.left = new_left; node.right = new_right;
        node.tot_or = state_change[node.tot_or][val % 3];
        node.lazy += val;
    }

    void range_add(int L, int R, int val, int s, int t, int p) {
        if (L <= s && t <= R) {
            update_node(val, p);
            return;
        }
        pushdown(p);
        int m = s + ((t - s) >> 1);
        if (L <= m) range_add(L, R, val, s, m, p * 2);
        if (R > m) range_add(L, R, val, m + 1, t, p * 2 + 1);
        pushup(s, t, p);
    }

    void pushdown(int p) {
        if (tree[p].lazy != 0) {
            int val = tree[p].lazy;
            update_node(val, 2 * p);
            update_node(val, 2 * p + 1);
            tree[p].lazy = 0;
        }
    }

    void pushup(int s, int t, int p) {
        const Node& info1 = tree[2 * p];
        const Node& info2 = tree[2 * p + 1];
        array<i64, 8> left{};
        array<i64, 8> right{};
        // 计算 [l, r] 的 left
        for (int mask = 1; mask <= 7; mask++) {
            left[mask] += info1.left[mask];
            for (int mask_r = 1; mask_r <= 7; mask_r++) {
                if ((info1.tot_or | mask_r) == mask) {
                    left[mask] += info2.left[mask_r];
                }
            }
        }
        // 计算 [l, r] 的 right
        for (int mask = 1; mask <= 7; mask++) {
            right[mask] += info2.right[mask];
            for (int mask_l = 1; mask_l <= 7; mask_l++) {
                if ((mask_l | info2.tot_or) == mask) {
                    right[mask] += info1.right[mask_l];
                }
            }
        }
        
        i64 cnt = info1.cnt + info2.cnt; // 左右各自的合法区间
        // 跨中点的合法区间
        for (int mask1 = 1; mask1 <= 7; mask1++) {
            for (int mask2 = 1; mask2 <= 7; mask2++) {
                if ((mask1 | mask2) == 7) {
                    cnt += info1.right[mask1] * info2.left[mask2];
                }
            }
        }
        tree[p].cnt = cnt;
        tree[p].left = left;
        tree[p].right = right;
        tree[p].tot_or = info1.tot_or | info2.tot_or;
    }

public:
    SegTree(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1);
    }

    void range_add(int L, int R, int val) { return range_add(L, R, val, 0, n - 1, 1); }
};

/*
分治去求合法区间数，
左边的合法区间数 + 右边的合法区间数 + 跨中间的
为了求跨中间的合法区间，每个子问题需要记录：
left[mask]: 从左端点往右，让区间成分包含成 mask 的最小右端点
right[mask]: 从右端点往左，让区间成分包含成 mask 的最大左端点

不行，记录左端点，最后再通过 mask1 | mask2 = 7 来计数的话，会重复计数，
比如 0 1 2 | 0 ，左边的 mask 构成 110 时，会把 0 1 2 | 0 计数一次，左边的 mask 构成 111 时，又会把 0 1 2 | 0 计数一次。
所以，要记录构成 mask 的区间数
*/
i64 calc(SegTree& tree) {
    return tree.tree[1].cnt;
}

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> nums(n);
    for (int i = 0; i < n; i++) nums[i] = a[i + 1];
    SegTree tree(nums);
    cout << calc(tree) << '\n';
    for (int _ = 1; _ <= q; _++) {
        int l, r; cin >> l >> r; // 输入下标从 1 开始
        l--, r--;
        tree.range_add(l, r, 1);
        cout << calc(tree) << '\n';
    }
    return 0;
}