#include <stdio.h>
#include <assert.h>
#include <queue>
#include "splay.h"
int rd()
{
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return f ? k : -k;
}
void wr(int x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}

const int N = 600010;

BinNode *get_fa(BinNode *u) { return u ? u->fa : nullptr; }
BinNode *get_lc(BinNode *u) { return u ? u->lc : nullptr; }
BinNode *get_rc(BinNode *u) { return u ? u->rc : nullptr; }
int get_size(BinNode *u) { return u ? u->size : 0; }

BinNode tr[N];
BinNode *root;

bool islc(BinNode *u) { return u && u->fa && u->fa->lc == u; }
bool isrc(BinNode *u) { return u && u->fa && u->fa->rc == u; }

void link_lc(BinNode *u, BinNode *lc)
{
    u->lc = lc, u->pushup();
    if (lc) lc->fa = u;
}
void link_rc(BinNode *u, BinNode *rc)
{
    u->rc = rc, u->pushup();
    if (rc) rc->fa = u;
}

void zig(BinNode *u)
{
    if (u && u->lc)
    {
        BinNode *l = u->lc, *f = u->fa;
        char flag = (f == nullptr) ? 0 : islc(u) ? 1 : 2;
        link_lc(u, l->rc), link_rc(l, u);
        (flag == 0) ? (void)(l->fa = f) : (flag == 1) ? (link_lc(f, l)) : (link_rc(f, l));
    }
}
void zag(BinNode *u)
{
    if (u && u->rc)
    {
        BinNode *r = u->rc, *f = u->fa;
        char flag = (f == nullptr) ? 0 : islc(u) ? 1 : 2;
        link_rc(u, r->lc), link_lc(r, u); 
        (flag == 0) ? (void)(r->fa = f) : (flag == 1) ? (link_lc(f, r)) : (link_rc(f, r));
    }
}
void dfs_pushup(BinNode *u)
{
    if (u->lc) dfs_pushup(u->lc);
    if (u->rc) dfs_pushup(u->rc);
    u->pushup();
}

int lSize(int n) {
    // 高为 h 的满二叉树，节点数为 (1 << (h + 1)) - 1

    if (n == 1) return 0;
    int h = std::__lg(n); // 完全二叉树高度
    // 排开最后一层一定是满二叉（当然可能最后一层也是满的），然后再算最后一层在根的左子树上有几个节点，就能知道节点规模为 n 的完全二叉树的高度
    int ans = ((1 << h) - 1) / 2;
    return ans + std::min((1 << (h - 1)), n - ((1 << h) - 1));
}

BinNode* rank(BinNode* T, int k) {
    if (T->size == 1) return T;
    int lsize = T->lc ? T->lc->size : 0;
    if (lsize >= k) return rank(T->lc, k);
    else if (lsize + 1 == k) return T;
    return rank(T->rc, k - (lsize + 1));
}

void splay_to(BinNode *a, BinNode *x) {
    // x 伸展到 a 的儿子，a 可能为 nullptr，此时相当于伸展到根(根的父亲为 nullptr)
    while (x->fa != a) {
        BinNode* p = x->fa;
        BinNode* g = p ? p->fa : nullptr;
        if (g == a) islc(x) ? zig(p) : zag(p);
        else {
            if (islc(p) && islc(x)) { // 左左
                zig(g);
                zig(p);
            }
            else if (isrc(p) && isrc(x)) { // 右右
                zag(g);
                zag(p);
            }
            else { // 左右 / 右左，从 p 开始旋的，不是从 g 开始！，一个错误提交<https://www.smqyoj.com/record/68fb01d57fc8598513db3654>
                islc(x) ? zig(p) : zag(p);
                islc(p) ? zig(g) : zag(g);
            }
        }
    }
    return;
}

bool judge_complete(BinNode *rt)
{
    std::queue<BinNode *> q;
    q.push(rt);
    bool flag = 0, ret = 1;
    while (q.size())
    {
        BinNode *u = q.front();
        q.pop();
        if (!u) flag = 1;
        else if (flag) ret = 0;
        if (u) q.push(u->lc), q.push(u->rc);
    }
    return ret;
}

int main()
{
    int n = rd();
    for (int i = 1; i <= n; ++i)
    {
        int l = rd(), r = rd();
        if (l) link_lc(tr + i, tr + l);
        if (r) link_rc(tr + i, tr + r);
    }
    root = tr + 1;
    dfs_pushup(root);
    root = splay_to_comp(root);

    puts(judge_complete(root) ? "OK!" : "Not a complete tree!");
}