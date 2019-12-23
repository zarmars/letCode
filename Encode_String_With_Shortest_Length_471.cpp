给定一个 非空 字符串，将其编码为具有最短长度的字符串。

编码规则是：k[encoded_string]，其中在方括号 encoded_string 中的内容重复 k 次。

注：

k 为正整数且编码后的字符串不能为空或有额外的空格。
你可以假定输入的字符串只包含小写的英文字母。字符串长度不超过 160。
如果编码的过程不能使字符串缩短，则不要对其进行编码。如果有多种编码方式，返回任意一种即可。
 

示例 1：

输入： "aaa"
输出： "aaa"
解释： 无法将其编码为更短的字符串，因此不进行编码。
 

示例 2：

输入： "aaaaa"
输出： "5[a]"
解释： "5[a]" 比 "aaaaa" 短 1 个字符。
 

示例 3：

输入： "aaaaaaaaaa"
输出： "10[a]"
解释： "a9[a]" 或 "9[a]a" 都是合法的编码，和 "10[a]" 一样长度都为 5。
 

示例 4：

输入： "aabcaabcd"
输出： "2[aabc]d"
解释： "aabc" 出现两次，因此一种答案可以是 "2[aabc]d"。
 

示例 5：

输入： "abbbabbbcabbbabbbc"
输出： "2[2[abbb]c]"
解释： "abbbabbbc" 出现两次，但是 "abbbabbbc" 可以编码为 "2[abbb]c"，因此一种答案可以是 "2[2[abbb]c]"。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/encode-string-with-shortest-length
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 注意答案的不唯一性，比如"bbbb" 压缩后的结果"bbbb"和"4[b]"都是可以的。

class Solution {
public:
    // 动态规划问题
    // 最优子结构：若s[i,k)表示为了最短字符串，s[k,j)也表示为了最短字符串，则s[i,j)表示的
    // 最短字符串只会有两种可能：<1> 串接s[i,k)与s[k,j)表示的最短字符串; <2> 合并二者表示
    // 的最短字符串。结果为<1>,<2>中的小者。
    // 状态定义：f[i][j]表示s[i,j)压缩成的最短字符串
    // 状态转移：f[i][j] = (j-i)/(k-i)[f[i][k]] if s[i,j)==(j-i)/(k-i)*s[i,k) (*代表串接
    // 一定量的字符串) else f[i][j] = min(f[i][j],f[i][k]+f[k][j]) min求的是字符串的长度最小者
    // 最优解：f[0][n]
    // 时间复杂度O(n^3) 空间复杂度O(n^2)
    string encode(string s) {
        // s 非空
        const int n = s.length();

        // 要求长度最小者,需初始化为最大值
        vector<vector<string>> f(n+1,vector<string>(n+1,""));

        // base case
        for(int i = 0; i<n; i++) {
            f[i][i+1] += s[i];
        }

        for(int j = 2; j<=n; j++) {
            for(int i = j-2; i>=0; i--) {
                // 找到重复的子串位置
                f[i][j] = s.substr(i,j-i);            
                int repPos = findRepeatedString(f[i][j]);
                if(repPos<j-i && getLengthOfNumber((j-i) / repPos) + 2 + repPos < f[i][j].size()) {  // 找到了重复子串
                        f[i][j] = to_string((j-i) / repPos) + "[" + f[i][i+repPos] + "]";
                }

                for(int k = i+1; k<j; k++) {
                    // 下面的语句如果在函数中完成，由于频繁调用，会导致耗时剧增
                    if(f[i][k].size() + f[k][j].size() < f[i][j].size())
                        f[i][j] = f[i][k] + f[k][j];
                }                
            }
        }

        return f[0][n];
    }

    int getLengthOfNumber(int n) {
        return n<10 ? 1 : 1+getLengthOfNumber(n/10);
    }

    int findRepeatedString(string s) {
        return (s+s).find(s,1);
    }
    
/*  题解中另一种类似写法 状态表述是一致的，只是循环中的思路有所不同 这种等价于先求解长度短的子串的压缩问题，再求解长度较长的子串的压缩问题
    是一种比较清晰的自底而上的动态求解过程。上面的写法则要注意i从j开始递减，不能从0开始递增。因为有状态不确定。
        int find_rep_sub_size(string s) {
        return (s + s).find(s, 1);
    }
    int num_len(int n) {
        return (n < 10) ? 1 : 1 + num_len(n / 10);
    }
    string encode(string s) {
        int N = s.size();
        vector<vector<string> > dp(N, vector<string>(N));
        for (int i = 0; i < N; ++i) 
            dp[i][i] += s[i];
        for(int len = 2; len <= N; ++len) {
            for (int i = 0; i + len <= N; ++i) {
                int j = i + len - 1;
                dp[i][j] = s.substr(i, len);
                int sub_size = find_rep_sub_size(s.substr(i, len));
                if (sub_size < len && (num_len(len / sub_size) + 2 + dp[i][i + sub_size - 1].size()) < dp[i][j].size())
                    dp[i][j] = (to_string(len / sub_size)) + "[" + dp[i][i + sub_size - 1] + "]";
                for (int k = i; k < j; ++k) {
                    if (dp[i][k].size() + dp[k + 1][j].size() < dp[i][j].size())
                        dp[i][j] = dp[i][k] + dp[k + 1][j];
                }
            }
        }
        return dp[0][N - 1];
    }

*/
};

// 备注：对于二维动态规划问题，状态的取法有两种情形:
// 1. 当研究对象是一个具体的对象，比如一个字符串、数组，f[i][j]表示的是从下标i到j的一段连续子串或子数组相关信息(用于构造最优解), 也可将一个
//    下标固定，另一个作为长度，实际都是一样的，都是描述一个子问题的解。问题的关键是实现自底向上的求解，可结合题意、举例、加转移方程确定
//    base case.
// 2. 两个对象的比较，比如两个字符串，两个数组，将状态取为f[i][j]时，i,j代表两个对象的索引下标，用来描述二者之间的联系，也有可能变为
//    f[i][j][k], 第三维则代表长度。当然最终写出状态转移方程时，可能可以进行降维。状态的具体确定一定要能够完备的描述问题的所有可能的
//    情形.
// 3. 本题中按照第一种方法，base case不是很明朗，第二种方法则明确些，毕竟字符串是由短变长的。
// 4. 本题中的一个技巧，求解s[i,j)中包含了几个s[i,k), i<k<j. 利用的pos = (s+s).find(s,1), count = len(s)/pos. 可以通过画图清晰的证明这一点.
// 5. 对于最内层循环，要注意函数调用的消耗，不论是时间还是空间，频繁的函数调用会带来频繁的压栈出栈，可能带来性能的巨大下降。以本题为例，最内
//    层的循环如果采用函数调用比较字符串长度，运行时间与直接写if语句的结果对比为360ms/48ms, 80MB/18MB, 非常夸张的对比。
