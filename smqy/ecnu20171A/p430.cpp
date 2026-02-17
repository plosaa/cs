#include <bits/stdc++.h>

using namespace std;

#include <string>
template <typename T, typename = std::enable_if_t<std::is_same_v<T, int> || std::is_same_v<T, long long>>>
void rd(T& x) { /// 读入 int / long long
    T k = 0, f = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != EOF) f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    x = f ? k : -k;
}
void rd(std::string& s) { /// 读入单词
    s.clear(); int c = getchar();
    while (c == ' ' || c == '\n') c = getchar();
    while (c != ' ' && c != '\n' && c != EOF) { s.push_back(c); c = getchar(); }
}
void rdline(std::string& s) { /// 读入一行，注意：与通常的读行函数不同，rdline 的实现跳过了前导空白字符
    s.clear(); int c = getchar();
    while (c == ' ' || c == '\n') c = getchar();
    while (c != '\n' && c != EOF) { s.push_back(c); c = getchar(); }
}
template <typename T, typename = std::enable_if_t<std::is_same_v<T, int> || std::is_same_v<T, long long>>>
void wr(T x) { /// 输出 int / long long
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}
void wr(char c) { putchar(c); } /// 输出 char
void wr(const std::string& s) { for (const char *p = s.c_str(); *p; ++p) putchar(*p); }

const int maxn = 210;
int le[maxn];
int eq[maxn];
int ge[maxn];
int le_pre[maxn + 1];
int le_suf[maxn + 1];
int ge_pre[maxn + 1];
int ge_suf[maxn + 1];

int main(int argc, char const *argv[]) {
    int n; rd(n);
    vector<pair<string, int>> ops;
    for (int i = 0; i < n; i++) {
        char X; string op; int C;
        X = getchar(), rd(op), rd(C);
        if (op == "<") op = "<=", C--;
        if (op == ">") op = ">=", C++;
        ops.push_back({op, C});
    }
    auto tmp(ops);
    sort(tmp.begin(), tmp.end(), [&](auto& a, auto& b) {
        return a.second < b.second;
    });
    for (auto &[op, C] : ops) {
        C = lower_bound(tmp.begin(), tmp.end(), C, [&](auto& a, int val) {
            return a.second <= val;
        }) - tmp.begin(); // 离散化编号从 1 开始
    }

    for (auto& [op, C] : ops) {
        if (op == "<=") le[C]++;
        else if (op == "=") eq[C]++;
        else ge[C]++;
    }
    // 算 le / ge 的前缀和 & 后缀和
    for (int i = 0; i < maxn; i++) le_pre[i + 1] = le_pre[i] + le[i];
    for (int i = maxn - 1; i >= 0; i--) le_suf[i] = le_suf[i + 1] + le[i];
    for (int i = 0; i < maxn; i++) ge_pre[i + 1] = ge_pre[i] + ge[i];
    for (int i = maxn - 1; i >= 0; i--) ge_suf[i] = ge_suf[i + 1] + ge[i];

    int ans = 0;
    // 选一个 eq
    for (int i = 0; i < maxn; i++) {
        if (eq[i] != 0) {
            // printf("ans: %d\n", ans);
            ans = max(ans, eq[i] + le_suf[i] + ge_pre[i + 1]);
        }
    }
    // 不选 eq
    // 不选 le
    ans = max(ans, ge_suf[0]);
    // 枚举选 le
    for (int i = 0; i < maxn; i++) {
        ans = max(ans, le_suf[i] + ge_pre[i + 1]);
    }
    wr(ans);
    return 0;
}