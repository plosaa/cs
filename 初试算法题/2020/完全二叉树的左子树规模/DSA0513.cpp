// https://www.smqyoj.com/p/DSA0513
// https://www.smqyoj.com/record/68fa53ba7fc8598513db2d1e

#include "lsize.h"

#include <bits/stdc++.h>

using namespace std;

int lSize(int n) {
    // 高为 h 的满二叉树，节点数为 (1 << (h + 1)) - 1

    if (n == 1) return 0;
    int h = std::__lg(n); // 完全二叉树高度
    // 排开最后一层一定是满二叉（当然可能最后一层也是满的），然后再算最后一层在根的左子树上有几个节点，就能知道节点规模为 n 的完全二叉树的高度
    int ans = ((1 << h) - 1) / 2;
    return ans + min((1 << (h - 1)), n - ((1 << h) - 1));
}
