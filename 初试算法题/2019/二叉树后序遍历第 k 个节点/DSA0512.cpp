// https://www.smqyoj.com/p/DSA0512
// https://www.smqyoj.com/record/68fa41af7fc8598513db2ba9

// compile locally by: `g++ DSA0512.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
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
    if (T->size == 1) return T;
    int lsize = T->lc ? T->lc->size : 0;
    int rsize = T->rc ? T->rc->size : 0;
    if (k <= lsize) return rank(T->lc, k);
    else if (k <= lsize + rsize) return rank(T->rc, k - lsize);
    return T;
}
