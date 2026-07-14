class Solution {
public:
    int timer = 0;
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for(auto& conn : connections){
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        vector<int> disc(n, -1);
        vector<int> low(n, -1);
        vector<vector<int>> bridges;
        dfs(0, -1, adj, disc, low, bridges);
        return bridges;
    }
private:
    void dfs(int u,int parent, vector<vector<int>>& adj, vector<int>& disc, vector<int>& low, vector<vector<int>>& bridges){
        disc[u] = low[u] = timer++;
        for(int v: adj[u]){
            if(v == parent){
                continue;
            }
            if(disc[v] == -1){
                dfs(v, u, adj, disc, low, bridges);
                low[u] = min(low[u], low[v]);
                if(low[v] > disc[u]){
                    bridges.push_back({u, v});
                }
            }
            else{
                low[u] = min(low[u], disc[v]);
            }
        }
    }
};