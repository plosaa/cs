#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    // 填成 n 的上一个状态可能在比 n 大的位置，但是不会超过 2n，因为这题减少只能 -1，如果变到 > 2n 的上一步是靠翻倍，那减回去的开销只会更大，如果是靠 +1 ，也是无意义操作
    int n, x, y; cin >> n >> x >> y;
    i64 ans;
    // f[i] 需要依赖父问题，建图用 Dijkstra 搜
    priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<pair<i64, i64>>> pq; // (cost, 位置)
    vector<i64> dis(2 * n + 1, INT64_MAX);
    pq.push({x, 1});
    dis[1] = x;
    while (!pq.empty()) {
        auto [cost, pos] = pq.top(); pq.pop();
        if (pos == n) {
            ans = cost;
            break;
        }
        if (dis[pos] < cost) continue;
        if (pos - 1 > 0 && cost + x < dis[pos - 1]) {
            pq.push({cost + x, pos - 1});
            dis[pos - 1] = cost + x;
        }
        if (pos + 1 <= 2 * n && cost + x < dis[pos + 1]) {
            pq.push({cost + x, pos + 1});
            dis[pos + 1] = cost + x;
        }
        if (pos * 2 <= 2 * n && cost + y < dis[2 * pos]) {
            pq.push({cost + y, 2 * pos});
            dis[2 * pos] = cost + y;
        }
    }
    cout << ans;
    return 0;
}