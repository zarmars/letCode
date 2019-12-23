给定两个非空链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储单个数字。将这两数相加会返回一个新的链表。

 

你可以假设除了数字 0 之外，这两个数字都不会以零开头。

进阶:

如果输入链表不能修改该如何处理？换句话说，你不能对列表中的节点进行翻转。

示例:

输入: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
输出: 7 -> 8 -> 0 -> 7

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



// 该题也可使用两个栈来模拟递归过程，先将结点压栈，在弹出时计算和
// 若对于短的链表进行前补0，可以提高运行速度，递归函数写起来也能简单些
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    // 如果链表的头结点代表数字最低位，那很好处理，无论是采用递归法还是迭代法
    // 而本题中头结点代表数字最高位，而数的相加需要从低位加起，所以如果用递归
    // 法的话，我们不再是在深入过程中加和，而应该在回溯过程中加和。且两链表的
    // 长度可能不等，因此我们需要在递归过程中进行对齐。也就是说，在递归过程中
    // 我们关注的是链表的头结点及链表长度
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 题目已明确两链表非空
        // 获取链表长度
        int iLen1 = getLength(l1);
        int iLen2 = getLength(l2);
        bool haveCarry(false);

        ListNode* pHeadNext = addTwoNumbers(l1,iLen1,l2,iLen2,haveCarry);
        ListNode* pHead(nullptr);
        if(haveCarry) { // 产生进位
            pHead = new ListNode(1);
            pHead->next = pHeadNext;
        } else {
            pHead = pHeadNext;
        }

        return pHead;
    }

    ListNode* addTwoNumbers(ListNode* l1, int len1, ListNode*l2, int len2, bool& haveCarry) {
        // 必须是&&才行，若为||, 则[1,8] + [0] = [1]
        if(l1->next==nullptr && l2->next==nullptr) {
            ListNode* head = new ListNode((l1->val + l2->val) % 10);
            haveCarry = static_cast<bool>((l1->val + l2->val) / 10);
            return head;
        }
        ListNode* head(nullptr);

        // 当链表相加产生进位时，头结点为0
        if(len1>len2) {
            int sum(l1->val);
            ListNode* pHeadNext = addTwoNumbers(l1->next,len1-1,l2,len2,haveCarry);
            if(haveCarry) { // 产生了进位
                sum += 1;
            } 
            head = new ListNode(sum % 10);
            haveCarry = static_cast<bool>(sum / 10);
            head->next = pHeadNext;
        } else if(len1<len2) {
            return addTwoNumbers(l2,len2,l1,len1,haveCarry);
        } else {    // len1==len2
            int sum = l1->val + l2->val;
            ListNode* pHeadNext = addTwoNumbers(l1->next,len1-1,l2->next,len2-1,haveCarry);
            if(haveCarry) { // 有进位
                sum += 1;
            }
            head = new ListNode(sum % 10);
            haveCarry = static_cast<bool>(sum / 10);
            head->next = pHeadNext;
        }

        return head;
    }

    int getLength(ListNode* head) {
        if(head==nullptr) return 0;

        return getLength(head->next) + 1;
    }
};
