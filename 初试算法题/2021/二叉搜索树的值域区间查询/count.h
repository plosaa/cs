#include <stdlib.h>
struct BstNode
{
    int key;
    BstNode *fa;
    BstNode *lc, *rc;
    int size;
    BstNode(int v = 0, BstNode* f = NULL,
            BstNode* l = NULL, BstNode* r = NULL, int s = 1)
            : key(v), fa(f), lc(l), rc(r), size(s) {}
};
int count(BstNode* T, int lo, int hi);