#include <stdio.h>
#include <assert.h>
#include "leftify.h"
int rd()
{
    int k = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return k;
}
const int N = 1000010;
int n;
BinNode a[N];

BinNode backup[N];
int fcnt[N];

bool check_bintree()
{
    for (int i = 1; i <= n; ++i) if (a[i].parent != backup[i].parent) return 0;
    for (int i = 2; i <= n; ++i)
    {
        BinNode* f = a[i].parent;
        if ((f->lc != (a + i)) && (f->rc != (a + i))) return 0;
    }
    return 1;
}

bool is_leftlist;
int get_npl(BinNode* x)
{
    if (x == nullptr) return 0;
    int lnpl = get_npl(x->lc), rnpl = get_npl(x->rc);
    int ret_npl = 1 + std::min(lnpl, rnpl);
    if (ret_npl != 1 + rnpl) is_leftlist = 0;
    return ret_npl;
}
bool check_leftlist()
{
    is_leftlist = 1;
    int x = get_npl(a + 1);
    return is_leftlist;
}

int main()
{
    n = rd();
    for (int i = 2; i <= n; ++i) 
    {
        int f = rd();
        a[i].parent = a + f, assert(fcnt[f] < 2);
        (fcnt[f] == 0) ? (a[f].lc = a + i) : (a[f].rc = a + i);
        ++fcnt[f];
    }
    for (int i = 1; i <= n; ++i) backup[i].lc = a[i].lc, backup[i].rc = a[i].rc, backup[i].parent = a[i].parent;

    leftify(a + 1);

    /*
    for (int i = 1; i <= n; ++i) fprintf(stderr, "%d ", a[i].data);
    fprintf(stderr, "\n");
    */

    if (!check_bintree()) return puts("Invalid structure!"), 0;
    if (!check_leftlist()) return puts("Invalid leftlist!"), 0;
    return puts("OK!"), 0;
}