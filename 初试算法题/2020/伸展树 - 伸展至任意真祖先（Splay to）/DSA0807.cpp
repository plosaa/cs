// https://www.smqyoj.com/p/DSA0807
// https://www.smqyoj.com/record/68fb080d7fc8598513db368c

// compile locally by: `g++ DSA0807.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
8 2
2 3
6 4
5 7
0 8
0 0
0 0
0 0
0 0
0 2
2 7
*/

#include "splay.h"

void splay_to(BinNode *a, BinNode *x) {
    // x 伸展到 a 的儿子，a 可能为 nullptr，此时相当于伸展到根(根的父亲为 nullptr)
    while (x->fa != a) {
        BinNode* p = x->fa;
        BinNode* g = p ? p->fa : nullptr;
        if (g == a) islc(x) ? zig(p) : zag(p);
        else {
            if (islc(p) && islc(x)) { // 左左
                zig(g);
                zig(p);
            }
            else if (isrc(p) && isrc(x)) { // 右右
                zag(g);
                zag(p);
            }
            else { // 左右 / 右左，从 p 开始旋的，不是从 g 开始！，一个错误提交<https://www.smqyoj.com/record/68fb01d57fc8598513db3654>
                islc(x) ? zig(p) : zag(p);
                islc(p) ? zig(g) : zag(g);
            }
        }
    }
    return;
}
