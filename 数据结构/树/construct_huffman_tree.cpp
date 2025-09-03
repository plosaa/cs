// https://www.smqyoj.com/record/684571ecdcecb6582e12e7a9

#include <bits/stdc++.h>

using namespace std;

struct Node {
    char c = '0';
    int fq = 0;
    Node *lc = nullptr;
    Node *rc = nullptr;
};

int main(int argc, char const *argv[]) {
    string s;
    cin >> s;
    // s = "aabc";
    // s = "aaa";

    vector<int> freq(26);
    for (char c : s) freq[c - 'a']++;

    int unique_cnt = 0;
    char unique_char = '0';
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            unique_cnt++;
            unique_char = 'a' + i;
        }
    }
    if (unique_cnt == 1) { // 只有一种字母
        cout << s.size() << '\n';
        cout << unique_char << " 0" << '\n';
        return 0;
    }

    auto comp = [&](Node* x, Node* y) {
        return (*x).fq > (*y).fq;
    };
    priority_queue<Node*, vector<Node*>, decltype(comp)> pq(comp); 

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            Node* node = new Node{'a' + i, freq[i], nullptr, nullptr};
            pq.push(node);
        }
    }
    Node *root = nullptr;
    while (pq.size() >= 2) {
        Node *node1 = pq.top(); pq.pop();
        Node *node2 = pq.top(); pq.pop();
        root = new Node{'0', node1->fq + node2->fq, node1, node2};
        pq.push(root);
    }
    root = pq.top(); pq.pop();

    // 计算每个字母的编码
    vector<string> code(26);

    auto dfs = [&](auto& dfs, Node *root, string s) {
        if (root->lc == nullptr) { // 叶子
            code[root->c - 'a'] = s;
            return;
        }
        dfs(dfs, root->lc, s + '0');
        dfs(dfs, root->rc, s + '1');
    };

    dfs(dfs, root, "");

    int code_len = 0;
    for (char c : s) {
        code_len += code[c - 'a'].size();
    }
    cout << code_len << '\n';

    for (int i = 0; i < 26; i++) {
        if (code[i] != "") {
            cout << (char)('a' + i) << ' ';
            cout << code[i] << '\n';
        }
    }

    return 0;
}