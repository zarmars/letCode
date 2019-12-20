class Solution {
public:
    // 题目基本要求：不能使用除法，O(n)时间复杂度
    // 题目进阶要求：O(1)空间复杂度限制
    // 乘积 = 左边乘积 * 右边乘积 O(n)时间复杂度， O(1)空间复杂度
    vector<int> productExceptSelf(vector<int>& nums) {
        if(nums.empty()) return nums;

        const int n = nums.size();
        vector<int> product(n,1);

        int leftProduct(1); // 保存左边乘积
        int rightProduct(1); // 保存右边乘积

        // 拆解成两个循环更容易理解，一个计算相应位置元素左边的元素乘积，另一个计算相应位置元素右边元素的乘积
        for(int i = 0; i<n; i++) {
            product[i] *= leftProduct;
            leftProduct *= nums[i];

            product[n-1-i] *= rightProduct;
            rightProduct *= nums[n-1-i];
        }

        return product;
    }
};
