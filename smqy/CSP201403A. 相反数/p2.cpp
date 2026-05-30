#include <bits/stdc++.h>

using namespace std;

signed main(int argc, const char *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n; cin >> n;
    unordered_set<int> st; // 输入数字各不相同
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        st.insert(x);
    }
    int ans = 0;
    for (auto x : st) {
        if (st.count(-x)) ans++;
    }
    cout << ans / 2 << '\n';
}