#include <iostream>
#include <bitset>

using namespace std;

using i64 = long long;

using u64 = unsigned long long;

// 参考 Mario 代码，不需要枚举 1 的个数。以 a 为基础，贪心地把 a 的 0 变成 1
// ans 里 a 的 1 是一定不会动的，否则，ans 里抹掉了 a 里的某个位置的 1，那么由于 ans >= a，则 ans 左边一定多出来 1，
// 把多出来的的 1 填到 a 被抹掉的 1 的位置，能得到更小的 ans
// 此外，必须从低位开始填，否则结果会偏大

/* 如果题目是要求最多个 1 并取最大的值，该怎么做？
[1, 1100] 的答案是 1011，似乎可以枚举 1 的个数，然后从高位开始填，某一位能不能填 1 还得看 b 右边和剩余的 1 的个数。
chatgpt 给的做法大概是这样：先考虑 b 的低位全为 1 的这个数，但是这个数可能 < a ，继续按这个方式思考，答案就该是枚举 b 的每个 1，
然后把其变成 0，然后让 b 这个 1 的右边全是 1 。
*/
u64 solve(u64 a, u64 b) {
    // for (int p = 63; p >= 0; p--) { // 不能从高位开始填，必须从低位开始
    for (int p = 0; p <= 63; p++) {
        if (((a >> p) & 1) == 0 && (a | (1LL << p)) <= b) {
            a |= (1LL << p);
        }
    }
    return a;
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