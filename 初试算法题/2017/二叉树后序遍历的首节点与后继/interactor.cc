#include <stdio.h>
#include "bintree.h"
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
const int N = 1000010;

BinNode a[N];
BinNode *rt;

int dis[N];
int main()
{
    int n = rd();
    for (int i = 1; i <= n; ++i)
    {
        int l = rd(), r = rd();
        if (l) (a + i)->lc = (a + l), (a + l)->fa = (a + i);
        if (r) (a + i)->rc = (a + r), (a + r)->fa = (a + i);
    }
    rt = a + 1;
    std::pair<BinNode *, int> info = first(rt);
    BinNode *cur = info.first;
    wr(cur - a), putchar(' '), dis[1] = info.second;
    for (int i = 2; i <= n; ++i)
    {
        std::pair<BinNode *, int> info = next(cur);
        wr(info.first - a), putchar((i == n) ? '\n' : ' '), dis[i] = info.second;
        cur = info.first;
    }
    int sum_dis = 0;
    for (int i = 1; i <= n; ++i, putchar((i > n) ? '\n' : ' ')) wr(dis[i]), sum_dis += dis[i];
    wr(sum_dis), putchar('\n');
}