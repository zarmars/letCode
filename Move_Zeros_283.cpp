给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/move-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

class Solution {
public:
    // 最优解 避免不必要的赋0操作，如[0,0,....,0,1]，采用下面的双指针法，数组所有位置都会被写一遍
    // 优化思路：数组中非零元素在调整后应该位于当前或者之前的位置，对于移动后剩余的零元素，不需要再写入
    void moveZeroes(vector<int>& nums) {
        if(nums.empty()) return;

        using InputItor = vector<int>::iterator;
        InputItor itorLast(nums.begin());
        InputItor itorAhead(nums.begin());

        while(itorAhead!=nums.end()) {
            if(*itorAhead==0) itorAhead++;
            else {                              // 交换两个指针指向的元素
                int tmp = *itorAhead;
                *itorAhead = *itorLast;   
                *itorLast = tmp;

                itorLast++;
                itorAhead++;
            }
        }

    }
    // 双指针法，时间复杂度O(n), 空间复杂度O(1)
    // 慢指针前的元素均非零，快指针遇到0则前进，遇到非零元素则覆盖到慢指针处，慢指针向前一步
    // 最终快指针到达数组末尾，将慢指针继续向后直到数组末尾，并在此过程中将数组剩余元素赋值0
    // 数组写入次数为n, 不是最优解 稍微做点修改即可
    /*
    void moveZeroes(vector<int>& nums) {
        if(nums.empty()) return;

        using InputItor = vector<int>::iterator;
        InputItor itorLast(nums.begin());
        InputItor itorAhead(nums.begin());

        while(itorAhead!=nums.end()) {
            if(*itorAhead==0) itorAhead++;
            else {
                *itorLast++ = *itorAhead++;
            }
        }

        while(itorLast!=nums.end()) *itorLast++ = 0;
    }
    */
};
