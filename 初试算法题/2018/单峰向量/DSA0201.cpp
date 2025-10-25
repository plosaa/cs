// https://www.smqyoj.com/p/DSA0201
// https://www.smqyoj.com/record/68fa34da7fc8598513db2a75

// compile locally by: `g++ DSA0201.cpp interactor.cc -Wall -std=c++20 -o foo -lm -O2`

#include "peak.h"

int findPeak(int n) {
    // 找 nums[i - 1] < nums[i] 的最后一个位置 i
    int left = 1, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        (get(mid - 1) < get(mid)) ? (left = mid + 1) : (right = mid - 1); 
    }
    return right;
}
