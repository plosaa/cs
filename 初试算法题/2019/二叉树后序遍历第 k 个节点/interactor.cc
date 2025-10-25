#include <stdio.h>
#include "rank.h"
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
void pushup(BinNode*& u)
{
    u->size = 1;
    if (u->lc) u->size += u->lc->size;
    if (u->rc) u->size += u->rc->size;
}
const int N = 200010;
BinNode a[N];
BinNode* f[N];
int main()
{
    int q = rd(), sz = 1;
    a[sz].size = 1;
    while (q--)
    {
        int op = rd();
        if (op & 1)
        {
            ++sz;
            int fa = rd(), x = rd();
            (x & 1) ? (a[fa].rc = a + sz) : (a[fa].lc = a + sz);
            f[sz] = a + fa;
            BinNode* tmp = a + sz;
            while (tmp) pushup(tmp), tmp = f[tmp - a];
        }
        else
        {
            int k = rd();
            BinNode* ret = rank(a + 1, k);
            wr(ret - a), putchar('\n');
        }
    }
}