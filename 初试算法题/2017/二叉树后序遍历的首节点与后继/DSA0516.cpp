// https://www.smqyoj.com/p/DSA0516
// https://www.smqyoj.com/record/68fa225e7fc8598513db28f6

// compile locally by: `g++ DSA0516.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
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

#include "bintree.h"

std::pair<BinNode *, int> first(BinNode *T) {
    int cnt = 0;
    while (T) {
        if (T->lc) T = T->lc, cnt++;
        else if (T->rc) T = T->rc, cnt++;
        else return {T, cnt};
    }
    return {nullptr, 0}; // 不会执行到这里
}

std::pair<BinNode *, int> next(BinNode *u) {
    if (u->fa == nullptr) return {nullptr, 0}; // 根在后续遍历中没有后继
    if (u->fa->rc == u) return {u->fa, 1}; // u 为右孩子
    else { // u 为左孩子
        if (u->fa->rc == nullptr) {
            return {u->fa, 1};
        }
        else {
            auto [node, dis] = first(u->fa->rc);
            return {node, 2 + dis};
        }
    }
}
