#include <bits/stdc++.h>

using namespace std;

int lcs(string s1, string s2) {
    int m = s1.size();
    int n = s2.size();
    // f[i][j] = max(f[i][j - 1], f[i - 1][j], if (s1[i] == s2[j]) f[i - 1][j - 1] + 1)
    vector<vector<int>> f(m + 1, vector<int>(n + 1));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (s1[i] == s2[j]) f[i + 1][j + 1] = f[i - 1 + 1][j - 1 + 1] + 1;
            else f[i + 1][j + 1] = max(f[i - 1 + 1][j + 1], f[i + 1][j - 1 + 1]);
        }
    }
    return f[m - 1 + 1][n - 1 + 1];
}

int main(int argc, char const *argv[]) {
    cout << lcs("advantage", "didactical") << endl;
}