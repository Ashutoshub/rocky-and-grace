class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int MOD = 1e9 + 7;
        vector<vector<pair<int, long long>>> adj(n);
        for(const auto& road : roads){
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }
        vector<long long> dist(n, 1e18);
        vector<long long> ways(n, 0);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        dist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});
        while(!pq.empty()){
            auto [currtime, u] = pq.top();
            pq.pop();
            if(currtime > dist[u]) continue;
            for(const auto& edge : adj[u]){
                int v = edge.first;
                long long time = edge.second;
                if(dist[u] + time < dist[v]){
                    dist[v] = dist[u] + time;
                    ways[v] = ways[u];
                    pq.push({dist[v], v});
                }
                else if(dist[u] + time == dist[v]){
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }
        return ways[n - 1];
    }
};