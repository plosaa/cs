// https://www.smqyoj.com/p/DSA0506
// https://www.smqyoj.com/record/68fc46ab7fc8598513db5324

// compile locally by: `g++ DSA0506.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`
/*
example input:
11 3
3 0 8 5 2 6 7 10 4 1 9
5 8 2 0 10 4 7 9 1 6 3
2 5
8 4
6 9
*/

#include "lca.h"
#include <bits/stdc++.h>

int lca(int x, int y) {
    if (x == y) return x; // 题目输入给出的 x 和 y 可能相等
    
    // 若 x, y 有祖先关系，以 x 是祖先为例，则先序中一定是 x ... y ，后序中一定是 y ... x 。判定前后关系相反，即可知道在先序中前的那个为 lca
    
    // 若 x, y 无祖先关系，以 x 在左边为例，则先序中是 lca ... x ... y ，后序中是 x ... y ... lca ，前后关系一致
    // 但是怎么找 lca ？
    // 仔细观察 subtree(lca) 的访问，先序中是 lca {... x ...} {... y ...} ，后序中是 {... x ...} {... y ... } lca
    // 从 x 往前看，第一次出现其在先序遍历中在 x 左边，但在后序遍历中在 y 右边(不能用“在 x 右边”，先序中 x 前面的...可能在后序中在 x 的后面)的节点就是 lca
    int p1 = getPrePos(x); int p2 = getPrePos(y);
    int q1 = getPostPos(x); int q2 = getPostPos(y);
    if ((p1 - p2) * (q1 - q2) < 0) return p1 < p2 ? x : y;
    else {
        if (p1 > p2) std::swap(p1, p2), std::swap(q1, q2);
        while (--p1 >= 0) {
            if (getPostPos(getPreNum(p1)) > q2) return getPreNum(p1);
        }
    }
    return -1; // 不会执行到
}

// AnonTokyo 的[代码](https://www.smqyoj.com/record/68c5ed1909f2ddcb4bbde983)，和我的代码等效，但是特别简洁，甚至没有分情况讨论
/*
这个写法的思考方式，Mario佬在群里教了下我：
"祖先在前序遍历的位置一定在他俩前面，后序遍历的位置一定在他俩后面
然后就从二者前序遍历靠前的那个点开始向前比，看哪个点的后序遍历位置在他俩后面，就是答案"
*/
int lca_implementation2(int x, int y) {
    int p = std::min(getPrePos(x), getPrePos(y));
    int q = std::max(getPostPos(x), getPostPos(y));
    while (getPostPos(x = getPreNum(p--)) < q);
    return x;
}

/*
见威哥的[帖子](https://xinweikaoyan.blog.csdn.net/article/details/144108072) ，递归子问题时是有办法找到 x 的父亲的，从而可以缩减问题规模

如何找 x 的父节点 z？

1. 若 x 是 z 的左孩子，则先序遍历一定是 zx... ，后序遍历一定是 x...z
2. 若 x 是 z 的右孩子，则先序遍历一定是 z...x ，后序遍历一定是 ...xz

也就是说，z 要么是先序里 x 的直接前驱，要么是后序里 x 的直接后继，并且，若实际情况是例如case2而我们拿着 x 的直接前驱 c 以为是 z ，这时会发现
c 在后序遍历里在 x 的前面，从而可以区分

z 只有一个孩子的情况可以合并，不用单独考虑

不过这个方法每步只往上跳一步到父节点然后递归，效率不算高。
*/
int lca_implementation3(int x, int y) {
    if (x == y) return x; // 题目输入给出的 x 和 y 可能相等
    int px = getPrePos(x); int py = getPrePos(y);
    int qx = getPostPos(x); int qy = getPostPos(y);
    if ((px - py) * (qx - qy) < 0) return px < py ? x : y;
    else {
        // 求 x 的父节点 z
        int z = (getPostPos(getPreNum(px - 1)) > qx) ? getPreNum(px - 1) : getPostNum(qx + 1);
        // int z = getPrePos(getPostNum(qx + 1)) < px ? getPostNum(qx + 1) : getPreNum(px - 1);
        return lca(z, y);
    }
}