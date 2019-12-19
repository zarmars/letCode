class Solution {
public:
    // 入度为0的节点代表没有前置课程或者前置课程已经修完。依次将入度为0的结点添加到结果中即可。
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        if(numCourses<=0) return vector<int>();
        vector<int> topoOrder;
        // 课程之间没有依赖关系
        if(prerequisites.empty()) {
            for(int i = 0; i<numCourses; i++) topoOrder.push_back(i);
            return topoOrder;
        }

        // 邻接表
        unordered_map<int,vector<int>> adjGraph;
        // 入度信息存储
        vector<int> inDegree(numCourses,0);

        const int row = prerequisites.size();

        // 创建邻接表
        for(int i = 0; i<row; i++) {
            int src = prerequisites[i][1];
            int dest = prerequisites[i][0];

            if(adjGraph.find(src)!=adjGraph.end()) {
                adjGraph[src].push_back(dest);
            } else {
                vector<int> v{dest};
                adjGraph.insert({src,v});
            }

            inDegree[dest]++;
        }

        queue<int> q;   // 存储入度为0的结点
        for(int i = 0; i<numCourses; i++) {
            if(inDegree[i]==0) {
                q.push(i);
                topoOrder.push_back(i);
            }
        }

        while(!q.empty()) {
            int courseID = q.front();
            q.pop();

            if(adjGraph.find(courseID)!=adjGraph.end()) {
                for(int id : adjGraph[courseID]) {
                    inDegree[id]--;
                    if(inDegree[id]==0) {
                        q.push(id);
                        topoOrder.push_back(id);
                    }
                }
            }
        }

        if(topoOrder.size()==numCourses) return topoOrder;
        else return vector<int>();
    }

};
