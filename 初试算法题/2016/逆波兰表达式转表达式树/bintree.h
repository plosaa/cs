#include <string>
#include <vector>
struct BinNode
{
    std::string x; 
    BinNode *lc, *rc;
    BinNode(std::string s = "", BinNode *l = nullptr, BinNode *r = nullptr)
            :x(s), lc(l), rc(r) {}
};
BinNode *build_expr(const std::vector<std::string>& rpn);