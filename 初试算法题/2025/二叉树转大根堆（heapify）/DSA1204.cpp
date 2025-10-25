// https://www.smqyoj.com/p/DSA1204
// https://www.smqyoj.com/record/68fbc5707fc8598513db4abf

// compile locally by: `g++ DSA1204.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
6
1 2 2 1 5
1 2 3 4 5 6
*/

#include <bits/stdc++.h>
#include "heapify.h"

using namespace std;

void heapify(BinNode* x) {
    vector<int> nums;
    
    auto dfs = [&](auto& dfs, BinNode* root) {
        if (root == nullptr) return;
        nums.push_back(root->data);
        dfs(dfs, root->lc);
        dfs(dfs, root->rc);
    };
    dfs(dfs, x);

    sort(nums.rbegin(), nums.rend());

    int index = 0;

    // 层序遍历填回去
    queue<BinNode*> q;
    q.push(x);
    while (!q.empty()) {
        BinNode* node = q.front(); q.pop();
        node->data = nums[index++];
        if (node->lc) q.push(node->lc);
        if (node->rc) q.push(node->rc);
    }

    return;
}
