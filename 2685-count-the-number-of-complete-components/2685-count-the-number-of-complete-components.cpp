class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for(const auto& edge : edges){
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(n, false);
        int compcnt = 0;
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                int vcnt = 0;
                int ecnt = 0;
                dfs(i, adj, visited, vcnt, ecnt);
                int actedges = ecnt / 2;
                if(actedges == (vcnt *(vcnt - 1))/ 2){
                    compcnt++;
                }
            }
        }
        return compcnt;
    }
private:
    void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited, int& vcnt, int& ecnt){
        visited[node] = true;
        vcnt++;
        ecnt += adj[node].size();
        for(int neigh : adj[node]){
            if(!visited[neigh]){
                dfs(neigh, adj, visited, vcnt, ecnt);
            }
        }
    }
};