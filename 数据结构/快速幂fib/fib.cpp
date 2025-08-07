// https://www.smqyoj.com/p/DSA0102?tid=6817779e33a97843a8b96dac

// https://www.smqyoj.com/record/68185ec133a97843a8b9803a

#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9 + 7;

vector<vector<long long>> multi(vector<vector<long long>> x, vector<vector<long long>> y) {
    vector<vector<long long>> res = {{0, 0}, {0, 0}};
    res[0][0] = ((x[0][0] * y[0][0]) % mod + (x[0][1] * y[1][0]) % mod) % mod;
    res[0][1] = ((x[0][0] * y[0][1]) % mod + (x[0][1] * y[1][1]) % mod) % mod;
    res[1][0] = ((x[1][0] * y[0][0]) % mod + (x[1][1] * y[1][0]) % mod) % mod;
    res[1][1] = ((x[1][0] * y[0][1]) % mod + (x[1][1] * y[1][1]) % mod) % mod;
    return res;
}

vector<vector<long long>> qpow(vector<vector<long long>> v, long long b) { // 求v的b次方
    vector<vector<long long>> res = {{1, 0}, {0, 1}};
    while (b > 0) {
        if ((b & 1) != 0) {
            res = multi(res, v);
        }
        v = multi(v, v);
        b >>= 1;
    }
    return res;
}

long long fib(long long n) {
    // 习题解析1-20，[f(n), f(n + 1)] = [[0, 1], [1, 1]]^n * [0, 1]
    vector<vector<long long>> a = {{0, 1}, {1, 1}};
    auto p = qpow(a, n);
    return p[0][1];
}

int main(int argc, char const *argv[]) {
    int q;
    cin >> q;
    // q较少，求fib(i)的i较大，1e18，不线性算，对单个i用快速幂
    for (int i = 0; i < q; i++) {
        long long n;
        cin >> n;
        cout << fib(n) << "\n";
    }
    return 0;
}