#include <stdio.h>
#include <assert.h>
#include "peak.h"

const int N = 1000010, lim = 100;

int n, ans;
int a[N], getcnt;

int get(int idx)
{
    assert(idx >= 0 && idx < n);
    return ++getcnt, a[idx];
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    ans = findPeak(n);
    assert(getcnt <= lim);
    printf("%d\n", ans);
}