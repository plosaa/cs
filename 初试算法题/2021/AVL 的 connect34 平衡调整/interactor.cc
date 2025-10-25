#include <stdio.h>
#include <algorithm>
#include "avl.h"
int rd()
{
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return f ? k : -k;
}
void wr(int x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}

void pushup_above(AVLNode *u) { while (u) u->pushup(), u = u->fa; }

int bal_fac(AVLNode *u) { return (u->lc ? u->lc->height : 0) - (u->rc ? u->rc->height : 0); }
bool balanced(AVLNode *u) { return std::abs(bal_fac(u)) <= 1; }

bool islc(AVLNode *u) { return u && u->fa && u->fa->lc == u; }
bool isrc(AVLNode *u) { return u && u->fa && u->fa->rc == u; }
AVLNode *succ(AVLNode *u)
{
    AVLNode *ret = u;
    if (u->rc)
    {
        ret = u->rc;
        while (ret->lc) ret = ret->lc; 
    }
    else
    {
        while (isrc(ret)) ret = ret->fa;
        ret = ret->fa;
    }
    return ret;
}
void link_lc(AVLNode *u, AVLNode *lc)
{
    u->lc = lc, u->pushup();
    if (lc) lc->fa = u;
}
void link_rc(AVLNode *u, AVLNode *rc)
{
    u->rc = rc, u->pushup();
    if (rc) rc->fa = u;
}
void unlink_lc(AVLNode *u)
{ 
    if (u->lc) u->lc->fa = nullptr;
    u->lc = nullptr, u->pushup();
}
void unlink_rc(AVLNode *u)
{
    if (u->rc) u->rc->fa = nullptr;
    u->rc = nullptr, u->pushup();
}
AVLNode *connect34(AVLNode *a, AVLNode *b, AVLNode *c,
                   AVLNode *T0, AVLNode *T1, AVLNode *T2, AVLNode *T3)
{
    link_lc(a, T0), link_rc(a, T1), link_lc(c, T2), link_rc(c, T3);
    return link_lc(b, a), link_rc(b, c), b;
}

// root and hit node
AVLNode *rt, *_hot;
// find node that equals v (nullptr if not exist), _hot will be it's father
AVLNode *find(int v)
{
    AVLNode *ret = rt;
    _hot = nullptr;
    while (ret && ret->val != v)
    {
        _hot = ret;
        (ret->val > v) ? (ret = ret->lc) : (ret = ret->rc);
    }
    return ret;
}

void rebalance(AVLNode *g)
{
    AVLNode *p = target_child(g), *v = target_child(p), *fag = g->fa;
    char flag = (fag == nullptr) ? 0 : islc(g) ? 1 : 2;

    AVLNode *new_rt = tuning(g, p, v);
    if (rt == g) rt = new_rt;
    (flag == 0) ? (void)(new_rt->fa = fag) : (flag == 1) ? (link_lc(fag, new_rt)) : (link_rc(fag, new_rt));
}

AVLNode *insert(int v)
{
    if (!rt) return rt = new AVLNode(v);
    AVLNode *u = find(v), *g = nullptr;
    if (u) return u->add_self(), pushup_above(u), u;
    u = new AVLNode(v, _hot);
    (v < _hot->val) ? link_lc(_hot, u) : link_rc(_hot, u);
    for (g = _hot; g; g = g->fa)
    {
        if (!balanced(g)) { rebalance(g); break; }
        else g->pushup();
    }
    // height no need to pushup above, but size does.
    pushup_above(g); 
    return u;
}
// return replace node (assume is succ)
AVLNode *remove_at(AVLNode *u)
{
    AVLNode *w = u, *nxt = nullptr;
    if (!u->lc)
    {
        if (u == rt) rt = u->rc;
        else (islc(u) ? u->fa->lc : u->fa->rc) = u->rc;
        nxt = u = u->rc;
    }
    else if (!u->rc) 
    {
        if (u == rt) rt = u->lc;
        else (islc(u) ? u->fa->lc : u->fa->rc) = u->lc;
        nxt = u = u->lc;
    }
    else
    {
        w = succ(w);
        std::swap(u->val, w->val), std::swap(u->cnt, w->cnt);
        AVLNode *faw = w->fa;
        ((faw == u) ? faw->rc : faw->lc) = nxt = w->rc;
        if (w->rc) w->rc->fa = faw;
    }
    _hot = w->fa;
    if (nxt) nxt->fa = _hot;
    delete w;
    return nxt;
}
bool remove(int v)
{
    if (!rt) return false;
    AVLNode *u = find(v);
    if (!u) return false;
    if (u->cnt > 1) return u->remove_self(), pushup_above(u), true;
    remove_at(u);
    for (AVLNode *g = _hot; g; g = g->fa)
    {
        if (!balanced(g)) rebalance(g);
        g->pushup();
    }
    return true;
}

int rank(int v)
{
    int ret = 1;
    if (!rt) return ret;
    AVLNode *u = rt;
    _hot = nullptr;
    while (u)
    {
        _hot = u;
        if (u->val >= v) u = u->lc;
        else ret += u->cnt + (u->lc ? u->lc->size : 0), u = u->rc;
    }
    return ret;
}
int kth(int rk) // assume rk <= rt->size
{
    AVLNode *u = rt;
    while (u)
    {
        if (u->lc == nullptr)
        {
            if (rk <= u->cnt) break;
            else rk -= u->cnt, u = u->rc;
        }
        else if (u->lc->size <= rk - 1 && u->lc->size >= rk - u->cnt) break;
        else if (u->lc->size >= rk) u = u->lc;
        else rk -= (u->lc->size + u->cnt), u = u->rc;
    }
    return u->val;
}
int pred(int v) { return kth(rank(v) - 1); }
int succ(int v) { return kth(rank(v + 1)); }
int main()
{
    int q = rd();
    while (q--)
    {
        int op = rd(), x = rd();
        switch (op)
        {
        case 1: insert(x); break;
        case 2: remove(x); break;
        case 3: wr(rank(x)), putchar('\n'); break;
        case 4: wr(kth(x)), putchar('\n'); break;
        case 5: wr(pred(x)), putchar('\n'); break;
        case 6: wr(succ(x)), putchar('\n'); break;
        default: break;
        }
    }
}