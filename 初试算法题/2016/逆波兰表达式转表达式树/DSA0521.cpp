// https://www.smqyoj.com/p/DSA0521
// https://www.smqyoj.com/record/68f9ed207fc8598513db1c1d

// compile locally by: `g++ DSA0521.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
// example input: "A B C D - * + E F + +"

#include <bits/stdc++.h>

using namespace std;

#include "bintree.h"

BinNode *build_expr(const std::vector<std::string>& rpn) {
    BinNode *rt = nullptr;
    stack<BinNode*> st;
    for (const string& s : rpn) {
        if ('A' <= s[0] && s[0] <= 'Z') { // 操作数
            st.push(new BinNode(s));
        }
        else {
            auto rc = st.top(); st.pop();
            auto lc = st.top(); st.pop();
            rt = new BinNode(s, lc, rc);
            st.push(rt);
        }
    }
    return rt;
}
