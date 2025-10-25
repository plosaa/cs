#include <stdio.h>
#include "splay.h"
int rd()
{
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return f ? k : -k;
}
void wr(long long x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}
const int N = 100010;
BinNode tr[N];
BinNode *rt;
void pushup_above(BinNode *u) { while (u) u->pushup(), u = u->fa; }

bool islc(BinNode *u) { return u && u->fa && u->fa->lc == u; }
bool isrc(BinNode *u) { return u && u->fa && u->fa->rc == u; }

void link_lc(BinNode *u, BinNode *lc)
{
    u->lc = lc, u->pushup();
    if (lc) lc->fa = u;
}
void link_rc(BinNode *u, BinNode *rc)
{
    u->rc = rc, u->pushup();
    if (rc) rc->fa = u;
}

void zig(BinNode *u)
{
    if (u && u->lc)
    {
        BinNode *l = u->lc, *f = u->fa;
        char flag = (f == nullptr) ? 0 : islc(u) ? 1 : 2;
        link_lc(u, l->rc), link_rc(l, u);
        (flag == 0) ? (void)(l->fa = f) : (flag == 1) ? (link_lc(f, l)) : (link_rc(f, l));
    }
}
void zag(BinNode *u)
{
    if (u && u->rc)
    {
        BinNode *r = u->rc, *f = u->fa;
        char flag = (f == nullptr) ? 0 : islc(u) ? 1 : 2;
        link_rc(u, r->lc), link_lc(r, u); 
        (flag == 0) ? (void)(r->fa = f) : (flag == 1) ? (link_lc(f, r)) : (link_rc(f, r));
    }
}

void dfs_pushup(BinNode *u)
{
    if (u->lc) dfs_pushup(u->lc);
    if (u->rc) dfs_pushup(u->rc);
    u->pushup();
}

int main()
{
    int n = rd(), q = rd();
    for (int i = 1; i <= n; ++i)
    {
        int l = rd(), r = rd();
        if (l) link_lc(tr + i, tr + l);
        if (r) link_rc(tr + i, tr + r);
    }
    rt = tr + 1;
    dfs_pushup(tr + 1);
    wr(rt->sum_dep), putchar('\n');

    while (q--)
    {
        int a = rd(), x = rd();
        splay_to(a ? (tr + a) : nullptr, tr + x);
        if (!a) rt = tr + x;
        if (a) pushup_above(tr + a);
        wr(rt->sum_dep), putchar('\n');
    }
}