class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for(const auto& road : roads){
            graph[road[0]].push_back({road[1], road[2]});
            graph[road[1]].push_back({road[0], road[2]});
        }
        int minscore = INT_MAX;
        vector<bool> vis(n + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            for(auto& edge : graph[curr]){
                int nextnode = edge.first;
                int weight = edge.second;
                minscore = min(minscore, weight);
                if(!vis[nextnode]){
                    vis[nextnode] = true;
                    q.push(nextnode);
                }
            }
        }
        return minscore;
    }
};