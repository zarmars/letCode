给一个嵌套整数序列，请你返回每个数字在序列中的加权和，它们的权重由它们的深度决定。

序列中的每一个元素要么是一个整数，要么是一个序列（这个序列中的每个元素也同样是整数或序列）。

与 前一个问题 不同的是，前一题的权重按照从根到叶逐一增加，而本题的权重从叶到根逐一增加。

也就是说，在本题中，叶子的权重为1，而根拥有最大的权重。

示例 1:

输入: [[1,1],2,[1,1]]
输出: 8 
解释: 四个 1 在深度为 1 的位置， 一个 2 在深度为 2 的位置。
示例 2:

输入: [1,[4,[6]]]
输出: 17 
解释: 一个 1 在深度为 3 的位置， 一个 4 在深度为 2 的位置，一个 6 在深度为 1 的位置。 1*3 + 4*2 + 6*1 = 17。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/nested-list-weight-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
 
 

// 一种不太好的解法--思路不够清晰 没有将复杂问题分解为简单问题的叠加
class Solution {
public:
    // 遍历序列数组中的所有元素，其元素可能是整数，也可能是序列，所以需要利用dfs深度搜索
    // 假设根的权重为x，则逐步进入内层，权重将变为x-1,x-2,...,x-n, n为最深的层数, 用变量
    // level表示，而实际元素的权重，最内层应为1, 因此，x=n+1. 最终的加权和
    // weightSum = v0*x+v1*(x-1)+...+vn*(x-n) = sum(v0...vn)*x - sum(vi*level_i)
    // 只要在深搜过程中记录好level和元素之和，则可得到最终结果
    // 时间复杂度O(n)，空间复杂度O(logn) n为所有整数元素数目, logn为树的深度
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        if(nestedList.empty()) return 0;
        int level(0);
        int intSum(0);
        int weightSum(0);   // 辅助加权和，sum(vi*level)
        int maxDepth(0);
        int depthSum(0);
        
        dfs(nestedList,level,intSum,weightSum,maxDepth);
        depthSum = intSum*(maxDepth+1)-weightSum;

        return depthSum;
    }

    void dfs(vector<NestedInteger>& nestedList, int level, int &intSum, 
            int &weightSum, int& maxDepth)
    {   
        maxDepth = max(level,maxDepth); 
        for(int i = 0; i<nestedList.size(); i++) {
            if((nestedList[i]).isInteger()) {
                intSum += (nestedList[i]).getInteger();
                weightSum += level*(nestedList[i]).getInteger();
            } else {
                dfs(nestedList[i].getList(),level+1,intSum,weightSum,maxDepth);
            }
        }
    }
};
