struct BinNode
{
    BinNode *fa;
    BinNode *lc, *rc;
    int size;
    long long sum_dep;

    BinNode(BinNode *f = nullptr, BinNode *l = nullptr, 
            BinNode *r = nullptr, int s = 1, long long d = 0)
              : fa(f), lc(l), rc(r), size(s), sum_dep(d) {}
    void pushup()
    {
        size = 1, sum_dep = 0;
        if (lc) size += lc->size, sum_dep += lc->sum_dep;
        if (rc) size += rc->size, sum_dep += rc->sum_dep;
        sum_dep += (size - 1);
    }
};
bool islc(BinNode *);
bool isrc(BinNode *);
void zig(BinNode *);
void zag(BinNode *);
void splay_to(BinNode *, BinNode *);