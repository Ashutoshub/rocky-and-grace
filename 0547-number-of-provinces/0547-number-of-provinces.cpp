class Solution {
private:
    void dfs(int node, vector<vector<int>>& adj,vector<bool>& vis){
        vis[node] = true;
        for(int nei : adj[node]){
            if(!vis[nei]){
                dfs(nei, adj, vis);
            }
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<vector<int>> adj(n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(isConnected[i][j] == 1 && i != j){
                    adj[i].push_back(j);
                }
            }
        }
        int provinces = 0;
        vector<bool> vis(n, false);
        for(int i = 0;i < n; i++){
            if(!vis[i]){
                provinces++;
                dfs(i, adj, vis);
            }
        }
        return provinces;
    }
};