/*
描述: 清本数据结构-2016年期末，最后的那道算法题，只写了 x < y 的搜索情况
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node* parent = nullptr;
    Node* lc = nullptr;
    Node* rc = nullptr;
    int val = -1;

    Node(int val) { this->val = val; }
};

int total_step = 0;

// root 为树根，从 start 节点 找到值为 target 的节点
// 两种方案交替走一步。path1()一开始往上，走到lca后往下；path2()往下
Node* solve(Node* root, Node* start, int y) {
    assert(start->val < y); // 这里只写从 x 找 y，且 x < y 的情景，对称情况类似，不写了

    Node* cur1 = start;
    Node* cur2 = start;
    
    auto path1 = [&]() {
        if (cur1 == nullptr) return;
        Node* parent = cur1->parent;
        if (parent != nullptr) {
            if (parent->rc == cur1) cur1 = parent; // 左父亲，path1继续往上，parent的左子树不可能有y，右子树已有path1过程在搜索
            else { // 右父亲
                if (parent->val <= y) { // path2别搜了，那里不可能有y，来这里搜
                    cur2 = parent;
                    cur1 = parent; // path1继续往上为path2物色搜索起点
                }
                else cur1 = nullptr; // parent->val > y，parent以及parent再往上都不需要让path2来搜了
            }
        }
    };

    auto path2 = [&]() {
        if (cur2 == nullptr) return;
        cur2 = (cur2->lc != nullptr && cur2->lc->val >= y) ? cur2->lc : cur2->rc;
    };

    while (1) {
        path1();
        total_step++;
        cout << "path1 at node: " << (cur1 != nullptr ? cur1->val : -1) << endl;
        if (cur1 != nullptr && cur1->val == y) return cur1;
        
        path2();
        total_step++;
        cout << "path2 at node: " << (cur2 != nullptr ? cur2->val : -1) << endl;
        if (cur2 != nullptr && cur2->val == y) return cur2;
    }

    return nullptr; // 不会走到这里
}

int main(int argc, char const *argv[]) {
    vector<int> nodes(21);
    iota(nodes.begin(), nodes.end(), 1);
    vector<pair<int, int>> edges = {
        {2,1},{2,4},
        {4,3},{4,6},
        {6,5},{6,8},
        {8,7},
        {9,2},{9,11},
        {11,10},{11,12},
        {13,9},{13,14},
        {15,13},{15,18},
        {17,16},
        {18,17},{18,19},
        {20,15},{20,21}
    };
    unordered_map<int, Node*> map;
    for (int val : nodes) {
        Node* node = new Node(val);
        map[val] = node;
    }
    for (auto [u, v] : edges) {
        auto from = map[u];
        auto to = map[v];
        to->parent = from;
        (to->val < from->val) ? (from->lc = to) : (from->rc = to);
    }
    // 树已建好

    Node* root = map[20];
    int x = 6;
    int y = 17;
    /* int x = 5;
    int y = 8; */
    
    // 这里只写从 x 找 y，且 x < y 的情景，对称情况类似，不写了
    auto ans = solve(root, map[x], y);

    assert(ans->val == y); // 检查答案对不对

    cout << "total_step: " << total_step << endl;

    return 0;
}
