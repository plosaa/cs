// https://www.smqyoj.com/p/DSA0511
// https://www.smqyoj.com/record/68fa55a27fc8598513db2d60

#include "rank.h"

BinNode* rank(BinNode* T, int k) {
    if (T->size == 1) return T;
    int lsize = T->lc ? T->lc->size : 0;
    if (lsize >= k) return rank(T->lc, k);
    else if (lsize + 1 == k) return T;
    return rank(T->rc, k - (lsize + 1));
}
