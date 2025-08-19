#include <bits/stdc++.h>

using namespace std;

// 打印基础类型
template <typename T>
void print(const T& value) {
    std::cout << value;
}

template <typename T>
void print(const std::vector<T>& vec, const std::string& separator = ", ") {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        print(vec[i]);
        if (i + 1 != vec.size()) std::cout << separator;
    }
    std::cout << "]";
}

template <typename T>
void println(const std::vector<T>& vec, const std::string& separator = ", ") {
    print(vec, separator);
    std::cout << '\n';
}

// 找循环节，假定v无重复元素
vector<vector<int>> find_cycle(vector<int> v) {
    int n = v.size();
    vector<int> s = v;
    sort(s.begin(), s.end());
    unordered_map<int, int> pos; // 各个元素在s中的位置
    for (int i = 0; i < n; ++i) {
        pos[s[i]] = i;
    }
    vector<int> vis(n, false);
    vector<vector<int>> ans;

    // 以cur为起点找循环节
    auto dfs = [&](int cur) {
        vector<int> cycle;
        int start = cur;
        int next = -1;
        do {
            cycle.push_back(v[cur]);
            vis[cur] = true;
            next = pos[v[cur]];
            cur = next;
        } while (cur != start);

        return cycle;
    };

    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        // 开启dfs
        ans.push_back(dfs(i));
    }

    return ans;
}

int main(int argc, char const *argv[]) {
    println(find_cycle({3, 1, 2, 5, 4, 7, 6}));

    println(find_cycle({3, 1, 5, 2, 4, 7, 6})); // 交换两个元素，二者原属于不同循环节，循环节数 -1

    println(find_cycle({3, 2, 1, 5, 4, 7, 6})); // 交换两个元素，二者原属于同一循环节，循环节数 +1
    return 0;
}