给定一个非负整数数组和一个整数 m，你需要将这个数组分成 m 个非空的连续子数组。设计一个算法使得这 m 个子数组各自和的最大值最小。

注意:
数组长度 n 满足以下条件:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
示例:

输入:
nums = [7,2,5,10,8]
m = 2

输出:
18

解释:
一共有四种方法将nums分割为2个子数组。
其中最好的方式是将其分为[7,2,5] 和 [10,8]，
因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/split-array-largest-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



class Solution {
public:
    // 动态规划
    // 最优子结构：将数组切分为m个非空连续子数组，设各子数组和最大值为x, 则去掉最后一个子数组，
    // 其余子数组和的最大值也不会超过x. 
    // 状态定义：两个状态，一个是数组中元素的位置，另一个是之前划分的子数组数目。
    // f[i][j]表示从下标0开始长度为i的数组划分为j个子数组的各自和的最大值的最小值
    // 状态转移：f[i][j] = min(f[i][j], max(f[k][j-1], sum(nums[k],nums[k+1],...,nums[i-1])))), 1<=k<i
    // 最优解：f[n][m] 即将长度为n的数组划分为m个连续子数组的各自和的最大值的最小值
    // 因为状态转移方程中需要计算数组元素之和，因此可以单独设置一个和数组sum[i]，标识长度为i的
    // 数组的和。
    // 时间复杂度：遍历所有状态需要O(mn), 在状态转移最终需要遍历当前位置之前的元素，时间为O(n),
    // 数组求和时间为O(n)，故最终时间复杂度为O(mn*n)+O(n)=O(mn^2).
    // 空间复杂度: O(mn)
    int splitArray(vector<int>& nums, int m) {
        // 题中已表明数组长度与m的范围，因此无需再行检验
        const int n = nums.size();
        using Lint = long long;
        vector<Lint> sum(n+1,0);
        for(int i = 0; i<n; i++) {
            sum[i+1] = sum[i] + nums[i];    // 若声明为int可能会溢出，如[1,2147483647] m = 2
        }

        // 结合状态转移方程，要想求得f[i][j], 需要求最小值，因此将状态初始化为最大值
        // 主要解决f[0][j], f[i][0] 边界情形问题, 这两种情形均是不应该影响最终结果的
        // 最好举一个小的例子快速构建正确的状态方程写法，比如[1,4,4] m = 2 最终结果应为5
        vector<vector<int>> f(n+1,vector<int>(m+1,INT_MAX));

        f[0][0] = 0;    // 注意题目明确数组元素为非负整数，否则f[0][0]应该定为INT_MIN
        
        for(int i = 0; i<n; i++) {
            for(int j = 0; j<m; j++) {
                for(int k = 0; k<=i; k++) {
                    f[i+1][j+1] = min(f[i+1][j+1], max(f[k][j],static_cast<int>(sum[i+1]-sum[k])));
                }
            }
        }

        return f[n][m];

    }
};

// 注：该题还有一种二分查找解法，参见
链接：https://leetcode-cn.com/problems/split-array-largest-sum/solution/er-fen-cha-zhao-by-coder233-2/
