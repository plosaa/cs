// https://www.smqyoj.com/p/THU20151A

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, k; cin >> n >> k;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (abs(x) > k) ans++;
    }
    cout << ans << '\n';
    return 0;
}