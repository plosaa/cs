struct BinNode
{
    BinNode *fa;
    BinNode *lc, *rc;
    int size;

    BinNode(BinNode *f = nullptr, BinNode *l = nullptr, 
            BinNode *r = nullptr, int s = 1)
              : fa(f), lc(l), rc(r), size(s) {}
    void pushup()
    {
        size = 1;
        if (lc) size += lc->size;
        if (rc) size += rc->size;
    }
};
BinNode *get_fa(BinNode *);
BinNode *get_lc(BinNode *);
BinNode *get_rc(BinNode *);
int get_size(BinNode *);
int lSize(int);
BinNode* rank(BinNode*, int);
void splay_to(BinNode *, BinNode *);
BinNode *splay_to_comp(BinNode *);
