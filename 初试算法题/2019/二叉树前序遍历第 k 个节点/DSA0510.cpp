// https://www.smqyoj.com/p/DSA0510
// https://www.smqyoj.com/record/68fa3dd97fc8598513db2af2

// compile locally by: `g++ DSA0510.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
10
1 1 1
1 2 0
1 3 0
1 2 1
1 5 0
2 4
1 3 1
2 4
2 1
2 2
*/

#include "rank.h"

BinNode* rank(BinNode* T, int k) {
    if (k == 1) return T;
    int lsize = T->lc ? T->lc->size : 0;
    if (lsize >= k - 1) return rank(T->lc, k - 1);
    return rank(T->rc, k - (1 + lsize));
}
