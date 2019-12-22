我们想要使用一棵四叉树来储存一个 N x N 的布尔值网络。网络中每一格的值只会是真或假。树的根结点代表整个网络。对于每个结点, 它将被分等成四个孩子结点直到这个区域内的值都是相同的.

每个结点还有另外两个布尔变量: isLeaf 和 val。isLeaf 当这个节点是一个叶子结点时为真。val 变量储存叶子结点所代表的区域的值。

你的任务是使用一个四叉树表示给定的网络。下面的例子将有助于你理解这个问题：

给定下面这个8 x 8 网络，我们将这样建立一个对应的四叉树：



由上文的定义，它能被这样分割：



 

对应的四叉树应该像下面这样，每个结点由一对 (isLeaf, val) 所代表.

对于非叶子结点，val 可以是任意的，所以使用 * 代替。



提示：

N 将小于 1000 且确保是 2 的整次幂。
如果你想了解更多关于四叉树的知识，你可以参考这个 wiki 页面。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-quad-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        if(grid.empty()) return nullptr;

        const int m(grid.size());

        Node* quadTreeRoot = construct(grid,0,0,m-1,m-1);
        return quadTreeRoot;
    }

    Node* construct(vector<vector<int>>&grid, int iStart, int jStart, int iEnd, int jEnd) {
        if(iStart==iEnd && jStart==jEnd) {
            return new Node(grid[iStart][jStart],true,nullptr,nullptr,nullptr,nullptr);
        }

        int iMid = (iStart + iEnd) >> 1;
        int jMid = (jStart + jEnd) >> 1;
        
        // 注意根结点val的取值，不能随意指定true还是false, 如果根结点被证实为叶子结点，则val的值是确定的
        Node* root = new Node(grid[iStart][jStart],false,nullptr,nullptr,nullptr,nullptr);
        if(checkGrid(grid,iStart,jStart,iEnd,jEnd)) {
            root->isLeaf = true;
            return root;
        }

        if(checkGrid(grid,iStart,jStart,iMid,jMid)) {
            root->topLeft = new Node(grid[iStart][jStart],true,nullptr,nullptr,nullptr,nullptr);
        } else {
            root->topLeft = construct(grid,iStart,jStart,iMid,jMid);
        }

        if(checkGrid(grid,iStart,jMid+1,iMid,jEnd)) {
            root->topRight = new Node(grid[iStart][jMid+1],true,nullptr,nullptr,nullptr,nullptr);
        } else {
            root->topRight = construct(grid,iStart,jMid+1,iMid,jEnd);
        }

        if(checkGrid(grid,iMid+1,jStart,iEnd,jMid)) {
            root->bottomLeft = new Node(grid[iMid+1][jStart],true,nullptr,nullptr,nullptr,nullptr);
        } else {
            root->bottomLeft = construct(grid,iMid+1,jStart,iEnd,jMid);
        }

        if(checkGrid(grid,iMid+1,jMid+1,iEnd,jEnd)) {
            root->bottomRight = new Node(grid[iMid+1][jMid+1],true,nullptr,nullptr,nullptr,nullptr);
        } else {
            root->bottomRight = construct(grid,iMid+1,jMid+1,iEnd,jEnd);
        }
        

        return root;
    }

    bool checkGrid(vector<vector<int>>&grid, int iStart, int jStart, int iEnd, int jEnd) {
        
        for(int i = iStart; i<=iEnd; i++) {
            for(int j = jStart; j<=jEnd; j++) {
                if(grid[i][j]!=grid[iStart][jStart]) return false;
            }
        }

        return true;

    }
};
