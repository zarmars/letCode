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
    // 回文链表的隐藏规律性：前半段链表反转后与后半段链表相同
    // 利用快慢指针法，在移动慢指针的同时反转链表前半部分，此后
    // 依次比较后半部分即可. 需要注意链表结点为奇数及偶数的情形
    // 时间复杂度O(n), 空间复杂度O(1)
    bool isPalindrome(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return true;

        ListNode* slow(head), *fast(head);
        ListNode* prev(nullptr);

        while(fast && fast->next) {
            fast = fast->next;
            fast = fast->next;

            // 反转前半部分链表
            ListNode *pNext = slow->next;
            slow->next = prev;
            prev = slow;
            slow = pNext;
        }

        // 退出循环的条件为fast为空(结点数为偶数) 或 fast->next为空(结点数为奇数)
        ListNode* pAhead;   // 指向反转后前半部分链表头结点
        ListNode *pLast;    // 指向未反转的后半部分链表头结点
        if(fast==nullptr) {
            pLast = slow;
            pAhead = prev;
        } else {
            pAhead = prev;
            pLast = slow->next;
        }

        // 检验回文性
        while(pAhead && pLast) {
            if(pAhead->val!=pLast->val) return false;

            pAhead = pAhead->next;
            pLast = pLast->next;
        }

        return true;
    }
};
