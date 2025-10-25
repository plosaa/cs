// https://www.smqyoj.com/p/DSA0507
// https://www.smqyoj.com/record/68fb59d17fc8598513db3f8b

#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e6;

// 长子，节点编号从 1 开始
int first_son[N + 1];

// i 最近读到的 son，用来更新 next_bro，例如 i 是 1 的 lastest_son，则如果发现 j 是 1 的 son，则 i 的 next_bro 是 j
int latest_son[N + 1];

// 下一个兄弟
int next_bro[N + 1];

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa; // i 的父节点是 fa
        if (first_son[fa] == 0) first_son[fa] = i;
        if (latest_son[fa] != 0) {
            next_bro[latest_son[fa]] = i;
        }
        latest_son[fa] = i;
    }

    for (int i = 1; i <= n; i++) {
        cout << first_son[i] << ' ' << next_bro[i] << '\n'; // 不要用 endl，<https://www.smqyoj.com/record/68fb394a7fc8598513db3b67> 直接超时了，改用 '\n' 就通过 <https://www.smqyoj.com/record/68fb47ba7fc8598513db3d72>
    }

    return 0;
}