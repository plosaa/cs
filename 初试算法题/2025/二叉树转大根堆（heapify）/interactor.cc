#include <stdio.h>
#include <assert.h>
#include "heapify.h"
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
set<int> pre, cur;
bool check_bintree()
{
    for (int i = 1; i <= n; ++i)
    {
        if (a[i].lc != backup[i].lc) return 0;
        if (a[i].rc != backup[i].rc) return 0;
        if (a[i].parent != backup[i].parent) return 0;
    }
    return 1;
}
bool check_data()
{
    for (int i = 1; i <= n; ++i) cur.insert(a[i].data);
    for (auto& c : pre) if (!cur.count(c)) return 0;
    return 1;
}
bool check_heap()
{
    for (int i = 1; i <= n; ++i)
    {
        int f = a[i].data;
        int lc = (a[i].lc) ? (a[i].lc)->data : 0, rc = (a[i].rc) ? (a[i].rc)->data : 0;
        if ((f < lc) || (f < rc)) return 0;
    }
    return 1;
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
    
    for (int i = 1; i <= n; ++i) a[i].data = rd(), pre.insert(a[i].data);

    heapify(a + 1);

    /*
    for (int i = 1; i <= n; ++i) fprintf(stderr, "%d ", a[i].data);
    fprintf(stderr, "\n");
    */

    if (!check_bintree()) return puts("Invalid structure!"), 0;
    if (!check_data()) return puts("Invalid data!"), 0;
    if (!check_heap()) return puts("Invalid heap!"), 0;
    return puts("OK!"), 0;
}