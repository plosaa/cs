/*
参考: https://oi-wiki.org/math/number-theory/continued-fraction/
      https://blog.csdn.net/zzq61974/article/details/74484670
*/

// 这个连分数，Mario的[提交](https://www.smqyoj.com/record/697e03a772e16206fab57723)里有板子，可以看一下

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

pair<i64, i64> calc(vector<i64>& frac) {
    i64 a = frac.back(); // 当前分数为 a / b
    i64 b = 1;
    for (int i = frac.size() - 2; i >= 0; i--) {
        i64 f = frac[i]; // f + 1 / (a / b) = (af + b) / a
        i64 t = a;
        a = a * f + b;
        b = t;
    }
    return {a, b};
}

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    string score; cin >> score; // score 一定是 0.后面17位小数，例如 0.333333333333333
    long double t = stold(score);
    vector<i64> frac;
    while (true) {
        frac.push_back((i64)t);

        // if (abs(t - floor(t)) < 1e-16) break;
        t = 1 / (t - floor(t));

        auto [a, b] = calc(frac);
        ostringstream oss;
        oss << fixed << setprecision(15) << a / (long double)b; // fixed 是四舍五入
        if (oss.str() == score) break; // 必须要用 string 来比小数点后 15 位是否相同
    }
    
    auto [a, b] = calc(frac);
    cout << (long long)(a / __gcd(a, b)) << " " << (long long)(b / __gcd(a, b));
    return 0;
}