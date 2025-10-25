// https://www.smqyoj.com/p/DSA0104
// https://www.smqyoj.com/record/68fa32d87fc8598513db2a30

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        nums[i] = t;
    }
    long long s = 0, ans = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        s += nums[i];
        ans = max(ans, s);
        if (s <= 0) s = 0;
    }
    cout << ans << endl;
    return 0;
}