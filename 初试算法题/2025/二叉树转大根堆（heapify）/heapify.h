#include <bits/stdc++.h>
using namespace std;
struct BinNode
{
    int data; // �ؼ���
    BinNode *lc, *rc; // ����Ӻ��Ҷ���
    BinNode *parent; // ���ף����ڸ��ڵ�Ϊ NULL��
};
void heapify(BinNode* x);