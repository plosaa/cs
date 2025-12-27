#include <stdio.h>
#include <vector>
#include "fibavl.h"
std::vector<int> _preorder;
void print(int u) { _preorder.push_back(u); }

int main()
{
    int h = 0;
    scanf("%d", &h), preorder(h);
    for (size_t i = 0; i < _preorder.size(); ++i, putchar((i >= _preorder.size()) ? '\n' : ' '))
        printf("%d", _preorder[i]);
}