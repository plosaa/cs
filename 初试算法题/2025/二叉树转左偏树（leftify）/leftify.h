#include <bits/stdc++.h>
using namespace std;
struct BinNode
{
    BinNode *lc, *rc; // ����Ӻ��Ҷ���
    BinNode *parent; // ���ף����ڸ��ڵ�Ϊ NULL��
};
void leftify(BinNode* x);