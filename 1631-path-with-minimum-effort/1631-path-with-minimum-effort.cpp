class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        pq.push({0, {0, 0}});
        dist[0][0] = 0;
        while(!pq.empty()){
            auto [effort, pos] = pq.top();
            int r = pos.first;
            int c = pos.second;
            pq.pop();
            if(r == m - 1 && c == n - 1) return effort;
            if(effort > dist[r][c]) continue;
            for(auto& d : dirs){
                int nr = r + d.first;
                int nc = c + d.second;
                if(nr >= 0 && nr < m && nc >= 0 && nc < n){
                    int edgewt = abs(heights[r][c] - heights[nr][nc]);
                    int nextef = max(effort, edgewt);
                    if(nextef < dist[nr][nc]){
                        dist[nr][nc] = nextef;
                        pq.push({nextef ,{nr, nc}});
                    }
                }
            }
        }
        return 0;
    }
};