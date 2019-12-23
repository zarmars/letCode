给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次。

找到所有出现两次的元素。

你可以不用到任何额外空间并在O(n)时间复杂度内解决这个问题吗？

示例：

输入:
[4,3,2,7,8,2,3,1]

输出:
[2,3]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-all-duplicates-in-an-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



class Solution {
public:
    // 注意到数组元素的范围，利用数组下标来将元素放置在正确的位置
    // 以下方法的时间复杂度O(n), 但是容易压入重复元素。元素交换之前的判断不容易想到
    // 另外的方法是将下面的操作分解开，第一步循环遍历一遍所有元素，并将元素尽可能交换
    // 就位，除非相应位置已经被相同元素占据。第二步再次循环遍历所有元素，没有就位的元素
    // 一定就是重复元素。这样不用担心重复问题。时间复杂度仍是O(n), 但常数因子变大。
    // 另外一种方法是利用数组元素都大于0的特性，将遇到的元素对应在排序后的正确位置的元素取相反数
    // 具体来说，假设数组中元素2是重复的，那么2会被取两次相反数，最终仍为正数，那么它应该出现在结果中

    #define iabs(x) (x) >= 0 ? (x) : (-(x))

    vector<int> findDuplicates(vector<int>&nums) {
        vector<int> res;

        for(int i = 0; i<nums.size(); i++) {
            int absNum = iabs(nums[i]); // 注意用宏函数可能出现越界，所以先将其计算出来
            if(nums[absNum-1]>0) {   // 元素最多出现两次，只有第二次出现才会负负得正
                nums[absNum-1] *= -1;
            }
            else {                          // 元素第二次出现
                res.push_back(absNum);
            }
        }

        return res;
    }
    /*
    vector<int> findDuplicates(vector<int>& nums) {
        // 题目限定nums非空
        vector<int> res;
        bool isRepeated(false);

        for(int i = 0; i<nums.size(); ) {
            isRepeated = false;

            if(nums[i]!=i+1) {
                if(nums[nums[i]-1]==nums[i]) {
                    res.push_back(nums[i]);
                    ++i;
                } else {
                    // 如果交换的是索引i之前的元素x，那么该元素x一定是重复元素，所以在遍历过它之后
                    // 它的位置没有改变。由于已经在之前处理过它了，因此在交换后直接跳过它即可             
                    if (nums[i] < i + 1) isRepeated = true;                    
                    swap(nums[i],nums[nums[i]-1]);

                    if(isRepeated) ++i;                    
                }                
            } else ++i;      
        }

        return res;
    }

    void swap(int& a, int& b)
    {
        if(&a != &b) {
            a ^= b;
            b ^= a;
            a ^= b;
        }
    }

    */
};
