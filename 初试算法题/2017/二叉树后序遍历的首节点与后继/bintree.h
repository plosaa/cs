#include <algorithm>
struct BinNode
{
    BinNode *fa;
    BinNode *lc, *rc;

    BinNode(BinNode *f = nullptr, BinNode *l = nullptr, BinNode *r = nullptr)
            : fa(f), lc(l), rc(r) {}
};
std::pair<BinNode *, int> first(BinNode *);
std::pair<BinNode *, int> next(BinNode *);