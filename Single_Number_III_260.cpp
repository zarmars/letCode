给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

示例 :

输入: [1,2,1,3,2,5]
输出: [3,5]
注意：

结果输出的顺序并不重要，对于上面的例子， [5, 3] 也是正确答案。
你的算法应该具有线性时间复杂度。你能否仅使用常数空间复杂度来实现？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/single-number-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        if(nums.empty()) return vector<int>();

        int xorSum(0);
        // 相同的元素异或为0，最终得到的xorSum即为两个只出现一次元素的异或结果
        for(auto num : nums) {
            xorSum ^= num;
        }

        //xorSum = a^b 不会为零，找到其中任意以为不为0的位，即可用来分辨出a,b
        int mask(1);
        //while((mask&xorSum)==0) mask = mask << 1;
         mask = xorSum & (-xorSum);

        int firstNum(0);    // 存储其中一个只出现一次的元素
        int secondNum(0);   // 存储另一个只出现一次的元素

        for(auto num : nums) {
            if(mask&num) {
                firstNum ^= num;
            } else {
                secondNum ^= num;
            }
        }

        vector<int> ret{firstNum,secondNum};

        return ret;
    }
};

// 位运算几个小技巧：
// 1. x & (-x) 可以提取x最低位的1
// 2. x & (x-1) 可以将x最低位的1置0，循环操作直到结果为0，循环次数即为x的二进制编码中1的个数
// 3. x & 0x1 可以用来判断x的奇偶性, 结果为0表明x为偶数，反之为奇数.
