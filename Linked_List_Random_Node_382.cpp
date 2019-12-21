给定一个单链表，随机选择链表的一个节点，并返回相应的节点值。保证每个节点被选的概率一样。

进阶:
如果链表十分大且长度未知，如何解决这个问题？你能否使用常数级空间复杂度实现？

示例:

// 初始化一个单链表 [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom()方法应随机返回1,2,3中的一个，保证每个元素被返回的概率相等。
solution.getRandom();

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/linked-list-random-node
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

 // 蓄水池采样算法：用于解决在O(n)时间内对n个数据进行等概率随机选取的问题，适用于n确定及n很大且
 // 仍在增长的情形。其思想就是构造一个蓄水池，在水池中放入遍历到当前位置时按照一定概率随机选择的
 // 元素，并在之后的遍历中按照一定的概率替换之前放置在蓄水池的元素。当最终遍历完成后，蓄水池中剩
 // 余的元素就是我们要等概率随机选取的元素。
 // 拿抓号球来举例子就是，生产线不断生产不同号码的小球，我们从当前生产好的m个小球中等概率抽取一个放入
 // 篮子中, 显然每个小球被选中放入篮子中的概率为1/m，当第m+1个小球出现时，我们以1/m+1的概率去选取它
 // 是否放入篮子中替换其中的小球。就好像我们从来没有放入小球到篮子中一样，等价于从m+1个小球中等概率选取
 // 一个放入篮子。现在需要证明这样的操作能否保证前m个小球中任一个被放入篮子的概率是否是1/m+1。首先，在
 // 第m+1个小球出现前，它们任一个放入篮子的概率都是1/m，那么第m+1个小球出现后，它们能够保留在篮子中不被
 // 替换的概率是多少呢？当然是1/m*(1-1/m+1)=1/m+1.也就是要保证第m+1个小球没有被选取。从而我们保证了所有
 // 的小球都以1/m+1的概率出现在篮子中。这种情形会一直持续下去。
 // 推而广之，篮子的容量不再是1，而是m, 我们要从n个小球中随机选取m个小球放入篮子。实际上，当n<=m时，前面的
 // 小球都会被先放入篮子中，当n=m+1时，第m+1个小球被选取放入篮子的概率为m/m+1, 符合我们预期，那前面的m个小
 // 球呢？它们在此前被选中的概率是1，现在被替换的概率是1/m*(m/m+1)=1/m+1, 不被替换也就是被选择的概率就是
 // 1-1/m+1=m/m+1.从而我们保证了等概率选取。这种情形也会一直持续下去。
class Solution {
private:
    ListNode* pHead;
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        pHead = head;
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        int n(0);   // 统计遍历到的结点个数
        ListNode* head = pHead;
        ListNode* pSel(nullptr);    // 存储被选择的结点。蓄水池中的小球
        while(head) {
            ++n;
            if(rand()%n==0) {   // 概率1/n
                pSel = head;
            }

            head = head->next;
        }

        return pSel->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
