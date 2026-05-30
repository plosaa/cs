// https://www.smqyoj.com/p/THU20171A

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5;

int pre[maxn + 10];

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
    #endif
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k; cin >> n >> m >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[i] = x;
    }

    auto check = [&](int r) {
        vector<int> t(nums.begin(), nums.begin() + r + 1);
        // sort(t.begin(), t.end());
        fill(pre, pre + maxn + 1, 0);
        for (int x : t) pre[x] += 1;
        for (int i = 0; i <= maxn; i++) {
            pre[i + 1] += pre[i];
        }
        for (int i = 1; i <= maxn; i++) {
            if (pre[i] - pre[max(0, i - k - 1)] >= m) return true;
        }
        return false;
    };
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (!check(mid)) left = mid + 1;
        else right = mid - 1;
    }
    if (left < n) cout << left + 1 << '\n';
    else cout << "impossible" << '\n';
    return 0;
}