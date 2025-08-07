// https://www.smqyoj.com/p/DSA0106

#include <bits/stdc++.h>

using namespace std;

/* 这个写法会 tle ， <https://www.smqyoj.com/record/689471a276ac5c10b798468c>
当 s1 和 s2 都大量是一个字符时， 会有大量 dfs 实例
把 dfs(i, j) 的公共子序列结果记忆化，然后去用
*/

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    string s1, s2;
    cin >> s1 >> s2;
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> f(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                f[i][j] = f[i - 1][j - 1] + 1;
            }
            else {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            }
        }
    }
    
    // 找到最长子序列的长度后，dfs找所有最长子序列
    /* 从 (m - 1, n - 1) 开始，(注意 s1[m - 1] 和 s2[n - 1] 不一定是匹配的)
    如果 s1[i] == s2[j] ，则这是一个最长子序列的尾字符，递归 (i - 1, j - 1)
    否则，递归 (i - 1, j) 和 (i, j - 1) 中较大者。这样找的全是最长匹配
    */
    string t;
    unordered_set<string> ans;
    auto dfs = [&](auto& dfs, int i, int j) {
        if (i == -1 || j == -1) {
            ans.insert(t);
            return;
        }
        if (s1[i] == s2[j]) {
            t.push_back(s1[i]); // 本来这里该是 push_front 和 pop_front ，用 back，然后最后反转效率更高
            dfs(dfs, i - 1, j - 1);
            t.pop_back();
        }
        else {
            if (f[i + 1][j - 1 + 1] >= f[i - 1+ 1][j + 1]) dfs(dfs, i, j - 1);
            if (f[i - 1 + 1][j + 1] >= f[i + 1][j - 1 + 1]) dfs(dfs, i - 1, j);
        }
    };

    dfs(dfs, m - 1, n - 1);

    vector<string> v;
    for (auto& s : ans) {
        auto ss = s;
        reverse(ss.begin(), ss.end());
        v.push_back(ss);
    }
    sort(v.begin(), v.end());
    for (auto& s: v) cout << s << endl;
}