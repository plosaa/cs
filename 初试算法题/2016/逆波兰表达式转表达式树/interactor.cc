#include <iostream>
#include <sstream>
#include "bintree.h"

std::string input, s;
std::vector<std::string> rpn;
bool isleaf(BinNode *u) { return (u->lc == nullptr) && (u->rc == nullptr); }
void print(BinNode *u)
{
    if (u->lc) (!isleaf(u->lc)) ? (void)(std::cout << '(', print(u->lc), std::cout << ')') : (void)(print(u->lc));
    std::cout << u->x;
    if (u->lc) (!isleaf(u->rc)) ? (void)(std::cout << '(', print(u->rc), std::cout << ')') : (void)(print(u->rc));
}
int main()
{
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    std::getline(std::cin, input);
    std::stringstream ss(input);
    while (ss >> s) rpn.push_back(s);
    BinNode *rt = build_expr(rpn);
    print(rt), std::cout << '\n';
}