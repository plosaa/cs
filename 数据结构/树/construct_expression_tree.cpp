#include <bits/stdc++.h>

using namespace std;

struct Node {
    enum class Type {OPERATOR, OPERAND};
    Type type;
    string val;

    Node *left = nullptr;
    Node *right = nullptr;
};

bool is_digit(string &s) {
    return '0' <= s[0] && s[0] <= '9'; // 简便起见这里就这样
}

Node * construct_expression_tree(string expression) {
    stringstream ss(expression);
    string s;
    stack<Node *> st;
    Node *node = nullptr;
    while (ss >> s) {
        if (is_digit(s)) {
            node = new Node {Node::Type::OPERAND, s};
        }
        else {
            node = new Node {Node::Type::OPERATOR, s};
            Node * rc = st.top(); st.pop();
            Node * lc = st.top(); st.pop();
            node->left = lc;
            node->right = rc;
        }
        st.push(node);
    }
    return node;
}

// 打印中序遍历
void print_inorder(Node* root) {
    if (root == nullptr) return;
    print_inorder(root->left);
    cout << root->val << ' ';
    print_inorder(root->right);
}

// 打印层序遍历
void print_levelorder(Node* root) {
    if (root == nullptr) return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* cur = q.front();
            q.pop();
            cout << cur->val << ' ';
            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[]) {
    // 为了简便起见，assert: 输入为一个RPN，且只含双值操作符(不含阶乘)
    // 这个例子来自新威补充ppt P136，做了点小改动，去掉了阶乘
    auto root = construct_expression_tree("1 1 + 2 6 * 4 + 5 - ^ 6 7 * + 8 9 * -");

    // 打印中序和层序遍历结果看这棵树：
    cout << "中序：" << endl;
    print_inorder(root);
    cout << endl << endl;

    cout << "层序：" << endl;
    print_levelorder(root);
    cout << endl;
    return 0;
}