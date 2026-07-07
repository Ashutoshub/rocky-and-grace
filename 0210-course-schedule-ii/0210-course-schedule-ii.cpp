class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        for(const auto& pre : prerequisites){
            int course = pre[0];
            int prereq = pre[1];
            adj[prereq].push_back(course);
            indegree[course]++;
        }
        queue<int> q;
        for(int i = 0; i < numCourses; ++i){
            if(indegree[i] == 0){
                q.push(i);
            }
        }
        vector<int> result;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            result.push_back(curr);
            for(int nei : adj[curr]){
                indegree[nei]--;
                if(indegree[nei] == 0){
                    q.push(nei);
                }
            }
        }
        if(result.size() == numCourses){
            return result;
        }
        else{
            return {};
        }
    }
};