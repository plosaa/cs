#include <bits/stdc++.h>
using namespace std;
struct BinNode
{
    int data; // 关键码
    BinNode *lc, *rc; // 左儿子和右儿子
    BinNode *parent; // 父亲（对于根节点为 NULL）
};
void heapify(BinNode* x);