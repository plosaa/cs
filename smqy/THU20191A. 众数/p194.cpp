// https://www.smqyoj.com/p/THU20191A

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    for (int i = 0; i < m; i++) {
        int freq[10]{};
        for (int& x : nums) {
            freq[x % 10]++;
            x /= 10;
        }
        cout << max_element(freq, freq + 10) - freq << '\n';
    }
    return 0;
}