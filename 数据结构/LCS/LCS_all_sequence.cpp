// https://www.smqyoj.com/p/DSA0106

// https://www.smqyoj.com/record/6894846776ac5c10b7984a4d

#include <bits/stdc++.h>

using namespace std;

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
    vector<vector<int>> calculated(m + 1, vector<int>(n + 1)); // memo[i][j]是否计算过
    vector<vector<unordered_set<string>>> memo(m + 1, vector<unordered_set<string>>(n + 1, {""})); // memo[i + 1][j + 1] 存 [0, i] × [0, j] 的lcs
    auto dfs = [&](auto& dfs, int i, int j) {
        if (i == -1 || j == -1) return;
        if (calculated[i + 1][j + 1]) return;

        unordered_set<string> st;

        if (s1[i] == s2[j]) {
            if (!calculated[i - 1 + 1][j - 1 + 1]) dfs(dfs, i - 1, j - 1);
            for (auto& s : memo[i - 1 + 1][j - 1 + 1]) { // memo的初始状态得是空串，不然这里怎么都进不去
                st.insert(s + s1[i]);
            }
        }
        else {
            if (f[i + 1][j - 1 + 1] >= f[i - 1 + 1][j + 1]) {
                dfs(dfs, i, j - 1);
                st.insert(memo[i + 1][j - 1 + 1].begin(), memo[i + 1][j - 1 + 1].end());
            }
            if (f[i - 1 + 1][j + 1] >= f[i + 1][j - 1 + 1]) {
                dfs(dfs, i - 1, j);
                st.insert(memo[i - 1 + 1][j + 1].begin(), memo[i - 1 + 1][j + 1].end());
            }
        }

        calculated[i + 1][j + 1] = true;
        memo[i + 1][j + 1] = st;
    };

    dfs(dfs, m - 1, n - 1);

    vector<string> v;
    for (auto& s : memo[m - 1 + 1][n - 1 + 1]) {
        v.push_back(s);
    }
    sort(v.begin(), v.end());
    for (auto& s: v) cout << s << endl;
}