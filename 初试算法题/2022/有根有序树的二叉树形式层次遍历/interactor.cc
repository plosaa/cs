#include <stdio.h>
#include "traverse.h"

int rd()
{
    int k = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return k;
}
void wr(int x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}
const int N = 1000010;
int n;
BinNode a[N], b[N];

int res[N], rcnt;
void print(int x) { res[++rcnt] = x; }
bool judge()
{
    for (int i = 1; i <= n; ++i)
    {
        if (a[i].data != b[i].data) return 0;
        if (a[i].lc != b[i].lc) return 0;
        if (a[i].rc != b[i].rc) return 0;
    }
    return 1;
}
int main()
{
    n = rd();
    for (int i = 1; i <= n; ++i)
    {
        a[i].data = i;
        int l = rd(), r = rd();
        if (l) a[i].lc = a + l;
        if (r) a[i].rc = a + r;
    }
    for (int i = 1; i <= n; ++i) b[i].data = a[i].data, b[i].lc = a[i].lc, b[i].rc = a[i].rc;
    traverse(a + 1);
    if (!judge()) return 0;
    for (int i = 1; i <= rcnt; ++i, putchar((i > n) ? '\n' : ' ')) wr(res[i]);
}