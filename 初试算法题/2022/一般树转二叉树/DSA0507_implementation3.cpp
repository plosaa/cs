// https://www.smqyoj.com/p/DSA0507
// https://www.smqyoj.com/record/68fb59f47fc8598513db3fa0

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

constexpr int N = 1e6;

// 长子，节点编号从 1 开始
int first_son[N + 1];

// i 最近读到的 son，用来更新 next_bro，例如 i 是 1 的 lastest_son，则如果发现 j 是 1 的 son，则 i 的 next_bro 是 j
int latest_son[N + 1];

// 下一个兄弟
int next_bro[N + 1];

int main(int argc, char const *argv[]) {
    int n = rd();

    for (int i = 2; i <= n; i++) {
        int fa = rd(); // i 的父节点是 fa
        if (first_son[fa] == 0) first_son[fa] = i;
        if (latest_son[fa] != 0) {
            next_bro[latest_son[fa]] = i;
        }
        latest_son[fa] = i;
    }

    for (int i = 1; i <= n; i++) {
        wr(first_son[i]); wr(' '); wr(next_bro[i]); wr('\n');
    }

    return 0;
}