#include <stdlib.h>
struct BinNode
{
    BinNode *lc, *rc;
    int size;
    BinNode(BinNode* l = NULL, BinNode* r = NULL, int s = 1)
            : lc(l), rc(r), size(s) {}
};
BinNode* rank(BinNode* T, int k);