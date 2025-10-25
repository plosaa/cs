#include <stdio.h>
#include "lca.h"
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
const int N = 10010;
int n, q;
int pre[N], post[N];
int prepos[N], postpos[N];

int getTreeSize() { return n; }
int getPrePos(int v) { return prepos[v]; }
int getPostPos(int v) { return postpos[v]; }
int getPreNum(int p) { return pre[p]; }
int getPostNum(int p) { return post[p]; }

int lca(int x, int y);
int main()
{
    n = rd(), q = rd();
    for (int i = 0; i < n; ++i) pre[i] = rd(), prepos[pre[i]] = i;
    for (int i = 0; i < n; ++i) post[i] = rd(), postpos[post[i]] = i;

    while (q--)
    {
        int x = rd(), y = rd();
        wr(lca(x, y)), putchar('\n');
    }
}