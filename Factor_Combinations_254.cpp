整数可以被看作是其因子的乘积。

例如：

8 = 2 x 2 x 2;
  = 2 x 4.
请实现一个函数，该函数接收一个整数 n 并返回该整数所有的因子组合。

注意：

你可以假定 n 为永远为正数。
因子必须大于 1 并且小于 n。
示例 1：

输入: 1
输出: []
示例 2：

输入: 37
输出: []
示例 3：

输入: 12
输出:
[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]
示例 4:

输入: 32
输出:
[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/factor-combinations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


class Solution {
public:
    // dfs 需要注意重复的问题
    // 以12为例 12 = 2*6 = 2*(2*3) = 3*4 = [3*(2*2)]
    // 注意，第一个因子由小到大增大，我们只需要分解第二个因子即可
    // 此外，第二个因子分解时也要保证不会分解出小于第一个因子的因子，
    // 比如上面最后一项，会与第二项重复(n = x*y, x<y, 将y继续分解为y1*y2,
    // 若y1<x, 则在x从小到大的遍历过程中,已经处理过x=y1时的情形，这样就形成了重复)
    // 这就表明在dfs过程中，不只需要关注待分解的数，还要关注起始因子大小
    vector<vector<int>> getFactors(int n) {
        if(n==1) return vector<vector<int>>();

        vector<vector<int>> res;
        vector<int> factor;

        dfs(n,2,factor,res);
        
        return res;
    }

    void dfs(int n, int start, vector<int>&factor, vector<vector<int>>&res) {

        for(int i = start; i*i<=n; i++) {
            if(n % i != 0) continue;
            
            factor.push_back(i);
            factor.push_back(n / i);
            res.push_back(factor);
            
            factor.pop_back();
            dfs(n / i, i, factor, res);
            factor.pop_back();
        }
    }


};
