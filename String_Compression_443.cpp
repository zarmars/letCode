给定一组字符，使用原地算法将其压缩。

压缩后的长度必须始终小于或等于原数组长度。

数组的每个元素应该是长度为1 的字符（不是 int 整数类型）。

在完成原地修改输入数组后，返回数组的新长度。

 

进阶：
你能否仅使用O(1) 空间解决问题？

 

示例 1：

输入：
["a","a","b","b","c","c","c"]

输出：
返回6，输入数组的前6个字符应该是：["a","2","b","2","c","3"]

说明：
"aa"被"a2"替代。"bb"被"b2"替代。"ccc"被"c3"替代。
示例 2：

输入：
["a"]

输出：
返回1，输入数组的前1个字符应该是：["a"]

说明：
没有任何字符串被替代。
示例 3：

输入：
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

输出：
返回4，输入数组的前4个字符应该是：["a","b","1","2"]。

说明：
由于字符"a"不重复，所以不会被压缩。"bbbbbbbbbbbb"被“b12”替代。
注意每个数字在数组中都有它自己的位置。
注意：

所有字符都有一个ASCII值在[35, 126]区间内。
1 <= len(chars) <= 1000。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/string-compression
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


// 本题虽然简单，但是极容易出错，因为要操纵三个指针。
class Solution {
public:
    // 题中隐含的条件是相同字符在数组中是连续排列的，所以不需要再进行排序
    // 类似数组覆盖法去重，不同之处在于需要统计每个字符出现的次数，如果次数
    // 大于1，需要把次数添加到元素的后面
    int compress(vector<char>& chars) {
        if(chars.empty()) return 0;

        int readIndex(0);
        int writeIndex(0);
        int newCharIndex(0);
        const int n = chars.size();
        
        while(readIndex<n) {
            while(readIndex<n && chars[readIndex]==chars[newCharIndex]) ++readIndex;

            int count = readIndex - newCharIndex;
            chars[writeIndex++] = chars[newCharIndex];

            if(count == 1) {
                newCharIndex = readIndex;
            } else {
                string strCount = to_string(count);
                for(int i = 0; i<strCount.size(); i++) {
                    chars[writeIndex++] = strCount[i];
                }
                newCharIndex = readIndex;
            }
        }
        /* 注意这种写法的问题，累计计数会出错，且因为if...else结构，最后一个字符不能被正确处理
        int count = 1;
        while(readIndex<chars.size()) {
            if(chars[readIndex]==chars[writeIndex]) {
                readIndex++;
            } else {
                if(count==1) writeIndex++;
                else {    // 要将count写入到数组中，由于是字符数组，而count可能>=10, 因此需循环写入
                    string strCount = to_string(count);
                    for(int i = 0; i<strCount.size(); i++) {
                        chars[++writeIndex] = strCount[i];
                    }
                    ++writeIndex;
                    count = 1;
                }
            }
        }
        */
        return writeIndex;
    }
};
