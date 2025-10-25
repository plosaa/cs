// https://www.smqyoj.com/p/DSA0507
// https://www.smqyoj.com/record/68fb599f7fc8598513db3f76

/*
example input:
6
1 1 3 3 1
*/

#include <bits/stdc++.h>

using namespace std;

// smoj 的 interactor.cc 里的快读快写板子
int rd() {
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar(); // c ^ 48 把字符 '0'~'9' 转成对应数字 0~9
    return f ? k : -k;
}

void wr(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48); // digit ^ 48 把数字 0~9 转成对应字符 '0'~'9'
}

void wr(char c) {
    putchar(c);
}

int main(int argc, char const *argv[]) {
    // cin.tie(0)->sync_with_stdio(false); // 用 stdio，不用 C++ 的 iostream

    int n = rd();
    // 节点编号从 1 开始
    vector<vector<int>> g(n + 1); // 节点的儿子列表
    vector<int> next_bro(n + 1); // 下一个兄弟
    for (int i = 2; i <= n; i++) {
        int fa = rd(); // i 的父节点是 fa
        if (!g[fa].empty()) next_bro[g[fa].back()] = i;
        g[fa].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        wr(g[i].empty() ? 0 : g[i].front()); wr(' '); wr(next_bro[i]); wr('\n');
    }
    return 0;
}