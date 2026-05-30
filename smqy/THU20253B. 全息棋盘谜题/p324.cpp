// https://www.smqyoj.com/p/THU20253B
// 讲评地址: https://www.bilibili.com/video/BV1NRwuzsEj4/
// 参考: https://www.smqyoj.com/record/69b65ea75b27d07ec1092a51
#include <bits/stdc++.h>

using namespace std;

/*
多观察样例，要把原本的 左白右黑 移动成 左黑右白，黑色要越过白色，这个跨越的次数总共是 n * m 次，
还有一种是只移动一格不产生跨越，由于二者代价一致，但 +/-2 的能产生更高的移动，所以应该尽量操作出跨越。

而 n m -> m n 的结构，总共的移动距离是 n(m + 1) + m(n + 1)，而 x(移动) 和 y(跨越) 的贡献分别是 1 和 2。
那么约束为 x + 2y = 2nm + n + m ，这个情景下求 x + y 的最小值，只要不做无用功（指又回到之前达到过的状态），
y 应当刚好是 nm，所以总代价为 n + m + nm 。

接下来看具体怎么操作，不妨从白棋开始操作，看样例
bb hh
b bhh 为什么这步要先移动而非选择跨越，因为这样可以接着选择让 h 跨越从而让其移动两步，如果是 bbhh，接下来就不能跨越
bhb h
bhbh 
bh hb
...

整个过程，同色棋子的相对顺序不会变，一直在往一个方向走，只是每步走 1 走 2 的区别。
*/

int n, m;

vector<int> ans;

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
        freopen("case.txt", "r", stdin);
        cout << unitbuf;
    #endif
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    cout << n * m + n + m << '\n';
    vector<int> a(n + m + 1 + 1); // [1, n + m + 1]
    for (int i = 1; i <= n; i++) a[i] = 0; // 白
    for (int i = n + 2; i < a.size(); i++) a[i] = 1; // 黑
    int p = n + 1; // 空格位置
    int flag = 0; // 0 代表要移动白的，1 代表要移动黑的
    int cnt = n * m + n + m;
    while (cnt) {
        if (flag == 0) { // 在移白棋
            if (p - 2 >= 1) {
                if (a[p - 1] == flag) {
                    cout << p - 1 << ' ';
                    a[p] = flag;
                    cnt--;
                    if (a[p - 2] == flag) flag ^= 1; // bb*hh -> b*bhh 后，空格两边同色时，该主动换个方向，让 h 来跳两步
                    p = p - 1;
                }
                else {
                    if (a[p - 2] == flag) { // 此时 a[p - 2] 该为白，不然转方向。（无法操作，则转方向）
                        cout << p - 2 << ' ';
                        a[p] = flag;
                        cnt--;
                        p = p - 2;
                    }
                    else flag ^= 1;
                }
            }
            else if (p - 1 >= 1) {
                // 此时在移白的状态，p - 2 又没东西，a[p - 1] 一定该是白，否则该转方向
                if (a[p - 1] == flag) {
                    cout << p - 1 << ' ';
                    a[p] = flag;
                    cnt--;
                    p = p - 1;
                }
                else flag ^= 1;
            }
            else flag ^= 1;
        }
        else { // 对称情况
            if (p + 2 <= n + m + 1) {
                if (a[p + 1] == flag) {
                    cout << p + 1 << ' ';
                    a[p] = flag;
                    cnt--;
                    if (a[p + 2] == flag) flag ^= 1;
                    p = p + 1;
                }
                else {
                    if (a[p + 2] == flag) {
                        cout << p + 2 << ' ';
                        a[p] = flag;
                        cnt--;
                        p = p + 2;
                    }
                    else flag ^= 1;
                }
            }
            else if (p + 1 <= n + m + 1) {
                if (a[p + 1] == flag) {
                    cout << p + 1 << ' ';
                    a[p] = flag;
                    cnt--;
                    p = p + 1;
                }
                else flag ^= 1;
            }
            else flag ^= 1;
        }
    }
    return 0;
}