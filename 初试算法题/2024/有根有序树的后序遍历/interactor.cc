#include <stdio.h>
#include "pre2post.h"
#include <assert.h>
int rd()
{
    int k = 0;
    char s = getchar();
    while (s < '0' || s > '9') s = getchar();
    while (s >= '0' && s <= '9') k = (k << 1) + (k << 3) + (s ^ '0'), s = getchar();
    return k;
}
void wr(int x)
{
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ '0');
}
std::stack<int> pre, deg, post;
int main()
{
    int n = rd();
    for (int i = 1; i <= n; ++i) pre.push(rd());
    for (int i = 1; i <= n; ++i) deg.push(rd());
    pre2post(pre, deg, post);
    assert(pre.empty()), assert(deg.empty()), assert(post.size() == n);
    for (int i = 1; i <= n; ++i, putchar((i > n) ? '\n' : ' ')) wr(post.top()), post.pop();
}