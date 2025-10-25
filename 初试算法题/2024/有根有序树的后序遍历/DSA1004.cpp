// https://www.smqyoj.com/p/DSA1004
// https://www.smqyoj.com/record/68fbc3ce7fc8598513db4a8d

// compile locally by: `g++ DSA1004.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
10
0 6 7 8 5 1 4 3 2 9
0 0 0 0 3 1 0 0 2 3
*/

#include "pre2post.h"
#include <bits/stdc++.h>

using namespace std;

void pre2post(std::stack<int>& pre, std::stack<int>& deg, std::stack<int>& post) {
    // (节点编号，度数)
    stack<pair<int, int>> st;
    st.push({pre.top(), deg.top()}); // 根入栈
    pre.pop(); deg.pop();
    while (!st.empty()) {
        auto& [node, degree] = st.top(); // 注意这里是引用
        if (degree == 0) { // node的各子树已经访问完
            post.push(node);
            st.pop();
        }
        else { // node还有子树未访问完
            degree--; // node的待访问子树减1
            st.push({pre.top(), deg.top()});
            pre.pop(); deg.pop();
        }
    }
}
