// https://www.smqyoj.com/p/DSA0508
// https://www.smqyoj.com/record/68fb91997fc8598513db46fc

/*
example input:
6
2 0
0 3
4 6
0 5
0 0
0 0
*/

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    vector<int> fa(n + 1); // 节点编号从 1 开始
    for (int i = 1; i <= n; i++) { // n - 1 条边
        int u, v;
        cin >> u >> v; // i 号节点的长子是 u ，兄弟是 v
        fa[u] = i;
        fa[v] = fa[i]; // 这里有个有意思的点，题目是按长子-兄弟树的先序遍历顺序给每个节点顺序编号的，给出每个节点的 长子 兄弟 也是按顺序给出的。此时 fa[i] 一定有值
    }

    for (int i = 2; i <= n; i++) {
        cout << fa[i] << ' ';
    }
    return 0;
}