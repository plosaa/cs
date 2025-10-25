// https://www.smqyoj.com/p/DSA0808
// https://www.smqyoj.com/record/68fb23b07fc8598513db3916

// compile locally by: `g++ DSA0808.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
8
2 3
6 4
5 7
0 8
0 0
0 0
0 0
0 0
*/

#include "splay.h"

BinNode *splay_to_comp(BinNode *rt) {
    if (get_size(rt) <= 1) return rt;
    int size = get_size(rt);
    int expect_lsize = lSize(size);
    BinNode* root = rank(rt, expect_lsize + 1); // 找到完全二叉树该有的根
    if (rt != root) splay_to(get_fa(rt), root); // 把 root 转到根
    splay_to_comp(get_lc(root));
    splay_to_comp(get_rc(root));
    return root;
}
