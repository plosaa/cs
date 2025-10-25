#include <bits/stdc++.h>
using namespace std;
struct BinNode
{
    BinNode *lc, *rc; // 左儿子和右儿子
    BinNode *parent; // 父亲（对于根节点为 NULL）
};
void leftify(BinNode* x);