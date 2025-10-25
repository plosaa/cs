// https://www.smqyoj.com/p/DSA0110
// https://www.smqyoj.com/record/68f9f4d77fc8598513db1cfa

// example input:
// 8 3
// 1 1 2 1 1 1 2 1


#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);

    int n, s;
    cin >> n >> s;

    int ans = 0;

    // 分组循环，但是这题 oj 要求空间复杂度 O(1)，得改造下分组循环
    int start = 0;
    int start_val;
    cin >> start_val;
    int i = 1;
    int i_val;
    while (i < n) {
        while (i++ < n && (cin >> i_val, i_val == start_val));
        // [start, i)
        int len = i - start;
        if (s % start_val == 0 && s / start_val <= len) {
            ans = std::max(ans, s / start_val);
        }
        start = i;
        if (i < n) start_val = i_val;
    }

    cout << ans << endl;

    return 0;
}