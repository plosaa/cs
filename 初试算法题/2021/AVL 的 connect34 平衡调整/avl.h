#include <algorithm>
struct AVLNode
{
    int val;
    AVLNode *fa;
    AVLNode *lc, *rc;
    int cnt, size; // cnt : count of v in this node, size : count of subtree
    int height; // height of subtree

    AVLNode(int v = 0, AVLNode *f = nullptr,
            AVLNode *l = nullptr, AVLNode *r = nullptr, int c = 1, int s = 1, int h = 1)
        : val(v), fa(f), lc(l), rc(r), cnt(c), size(s), height(h) {}
    // add / remove same v in node (assume cnt >= 1 after operation)
    void add_self() { ++cnt, ++size; }
    void remove_self() { --cnt, --size; }
    void pushup()
    {
        size = cnt, height = 1;
        if (lc) size += lc->size, height = std::max(height, 1 + lc->height);
        if (rc) size += rc->size, height = std::max(height, 1 + rc->height);
    }
};

bool islc(AVLNode *);
bool isrc(AVLNode *);
AVLNode *connect34(AVLNode *a, AVLNode *b, AVLNode *c,
                   AVLNode *T0, AVLNode *T1, AVLNode *T2, AVLNode *T3);


AVLNode *target_child(AVLNode *);
AVLNode *tuning(AVLNode *, AVLNode *, AVLNode *);
