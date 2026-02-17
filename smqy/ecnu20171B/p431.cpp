#include <iostream>
#include <bitset>

using namespace std;

using i64 = long long;

using u64 = unsigned long long;

u64 solve(u64 a, u64 b) {
    // cout << std::bitset<64>(a) << endl;
    for (int i = 64; i >= 0; i--) { // 枚举 1 的个数
        int remain = i;
        u64 cur = 0;
        // 试填
        for (int j = 63; j >= 0; j--) {
            if (remain >= j + 1) cur |= (1ULL << j), remain--;
            else {
                if (cur > a) continue; // cur 够大，填 0
                else if ((a >> j) & 1) cur |= (1ULL << j), remain--;
            }
            // cout << std::bitset<64>(cur) << endl;
        }
        if (cur <= b) return cur;
    }
    return -1;
}

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        u64 a, b; cin >> a >> b;
        cout << "Case " << i + 1 << ": ";
        cout << solve(a, b) << '\n';
    }
    return 0;
}