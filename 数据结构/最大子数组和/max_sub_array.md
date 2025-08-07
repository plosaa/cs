01.Introduction.pdf P74

[LeetCode53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/solutions/228009/zui-da-zi-xu-he-by-leetcode-solution/)

```cpp
int max_sub_array(vector<int> nums) {
    int n = nums.size();
    int ans = 0;
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += nums[i];
        if (s > ans) ans = s;
        if (s <= 0) s = 0;
    }
    return ans;
}
```

还有个用线段树(或者说分治)的解法，见[LeetCode53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/solutions/228009/zui-da-zi-xu-he-by-leetcode-solution/)，时间复杂度也是 $O(n)$，但是建树之后，可以以 $O(logn)$ 时间求任意区间的最大子数组和，也可以修改元素后重新求答案。