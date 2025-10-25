// https://www.smqyoj.com/p/DSA1205
// https://www.smqyoj.com/record/68fbc72c7fc8598513db4adf

// compile locally by: `g++ DSA1205.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
7
1 1 3 3 5 5
*/

#include <bits/stdc++.h>
#include "leftify.h"

using namespace std;

void leftify(BinNode* x) {
    auto dfs = [&](auto& dfs, BinNode* root) -> int {
        if (!root) return 0;
        int npl1 = 1 + dfs(dfs, root->lc);
        int npl2 = 1 + dfs(dfs, root->rc);
        if (npl1 < npl2) swap(root->lc, root->rc);
        return std::min(npl1, npl2);
    };
    dfs(dfs, x);
    return;
}
