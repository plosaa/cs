// https://www.smqyoj.com/p/THU20171A

// 80分的值域线段树解法

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 10;

int tree[maxn];

int lowbit(int x) { return x & -x; }

void update(int i, int diff) {
    for (; i < maxn; i = i + lowbit(i)) {
        tree[i] += diff;
    }
}

int pre(int i) {
    int sum = 0;
    while (i > 0) {
        sum += tree[i];
        i -= lowbit(i);
    }
    return sum;
}

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k; cin >> n >> m >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[i] = x;
    }
    int ans = -1;
    for (int i = 0; i < n; i++) {
        int x = nums[i];
        update(x, 1);
        for (int l = max(1, x - k); l <= x; l++) {
            if (pre(l + k) - pre(l - 1) >= m) {
                ans = i + 1;
                goto OUT;
            }
        }
    }
    OUT:
    if (ans > 0) cout << ans << '\n';
    else cout << "impossible" << '\n';
    return 0;
}