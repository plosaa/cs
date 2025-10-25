// https://www.smqyoj.com/p/DSA0509
// https://www.smqyoj.com/record/68fb961d7fc8598513db4759

// compile locally by: `g++ DSA0509.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
6
2 0
0 3
4 6
0 5
0 0
0 0
*/

#include "traverse.h"

#include <queue>

using namespace std;

void traverse(BinNode* x) {
    queue<BinNode*> q;
    q.push(x);
    while (!q.empty()) {
        BinNode* node = q.front(); q.pop();
        while (node) {
            print(node->data);
            if (node->lc) q.push(node->lc);
            node = node->rc;
        }
    }
}
