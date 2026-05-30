// https://www.smqyoj.com/p/THU20151B

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 1e9 + 7;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, M; cin >> n >> M;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[i] = x;
    }
    sort(nums.begin(), nums.end());
    i64 ans = 0;
    for (int l = 0, r = n - 1; r >= 0; r--) {
        while (l < r && nums[l] + nums[r] <= M) l++;
        ans += min(r, l);
        ans %= MOD;
    }
    cout << ans << '\n';
    return 0;
}