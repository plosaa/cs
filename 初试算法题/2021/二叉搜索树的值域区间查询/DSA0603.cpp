// https://www.smqyoj.com/p/DSA0603
// https://www.smqyoj.com/record/68fb2f007fc8598513db3a6c

// compile locally by: `g++ DSA0603.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
5
1 10
1 20
2 10 20
1 30
2 10 31
*/

#include "count.h"

int count(BstNode* T, int lo, int hi) {
    // 转成 { < hi } - { < lo }
    // 本题保证二叉搜索树上的所有的关键码互异

    auto f = [&](auto& f, BstNode* T, int x) {
        if (T == nullptr) return 0;
        if (T->key < x) return 1 + (T->lc ? T->lc->size : 0) + f(f, T->rc, x);
        if (T->key >= x) return f(f, T->lc, x);
    };
    
    return f(f, T, hi) - f(f, T, lo);
}
