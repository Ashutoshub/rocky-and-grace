class Solution {
private:
    bool dfs(int node, vector<vector<int>>& graph, vector<int>& state){
        if(state[node] != 0){
            return state[node] == 2;
        }
        state[node] = 1;
        for(int nei : graph[node]){
            if(!dfs(nei, graph, state)){
                return false;
            }
        }
        state[node] = 2;
        return true;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> state(n, 0);
        vector<int> safenode;
        for(int i = 0; i < n; i++){
            if(dfs(i, graph, state)){
                safenode.push_back(i);
            }
        }
        return safenode;
    }
};