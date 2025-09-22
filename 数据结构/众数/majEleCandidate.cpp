#include <bits/stdc++.h>

using namespace std;

// 返回众数的候选者，是否真为众数由外部再检查
int majEleCandidate(vector<int> nums) {
    int n = nums.size();
    int maj = nums[0];
    int diff = 0;
    for (int i = 0; i < n; i++) {
        if (diff == 0) {
            maj = nums[i];
            diff++;
        }
        else {
            maj == nums[i] ? diff++ : diff--;
        }
    }
    return maj;
}

int main(int argc, char const *argv[]) {
    cout << majEleCandidate({5,3,9,3,1,2,3,3}) << endl;
    return 0;
}