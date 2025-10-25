#include <stdio.h>
#include "count.h"
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
void pushup(BstNode*& u)
{
    u->size = 1;
    if (u->lc) u->size += u->lc->size;
    if (u->rc) u->size += u->rc->size;
}
int cur_dep;
BstNode *rt, *_hot;
// find node that v will insert
// return <_hot, NULL>
BstNode* find(int v)
{
    BstNode *ret = rt;
    _hot = NULL;
    cur_dep = 0;
    while (ret)
    {
        _hot = ret, ++cur_dep;
        (ret->key > v) ? (ret = ret->lc) : (ret = ret->rc);
    }
    return ret;
}
BstNode* insert(int v)
{
    BstNode* u = find(v);
    if (_hot == NULL) // BstNode(v) become root now.
    {
        rt = new BstNode(v, NULL, NULL, NULL, 1);
        return rt;
    }
    u = new BstNode(v, _hot, NULL, NULL, 1);
    (_hot->key <= v) ? (_hot->rc = u) : (_hot->lc = u);
    _hot = u;
    // update size above
    while (_hot) pushup(_hot), _hot = _hot->fa;
    return u;
}
int main()
{
    int q = rd(), op = 0, lo = 0, hi = 0, x = 0;
    while (q--)
    {
        int op = rd();
        if (op & 1) x = rd(), insert(x);
        else lo = rd(), hi = rd(), wr(count(rt, lo, hi)), putchar('\n');
    }
}