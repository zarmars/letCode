/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // 后序遍历实现翻转
    TreeNode* invertTree1(TreeNode* root) {
        if(root==nullptr) return nullptr;
        if(root->left==nullptr && root->right==nullptr) return root;

        TreeNode* pLeft = root->left;
        TreeNode* pRight = root->right;

        root->left = invertTree(pRight);
        root->right = invertTree(pLeft);

        return root;
    }

    // 先序遍历递归版
    TreeNode* invertTree(TreeNode* root)
    {
        if(root==nullptr) return root;

        stack<TreeNode*> st;
        TreeNode* p(root);

        while(p || !st.empty())
        {
            if(p)
            {
                TreeNode* tempNode = p->left;
                p->left = p->right;
                p->right = tempNode;

                st.push(p);
                p = p->left;
            }
            else
            {
                TreeNode* pNode = st.top();
                st.pop();
                p = pNode->right;
            }
        }

        return root;
    }
};
