class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(mat[i][j] == 0){
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        vector<pair<int, int>> dirs = {{-1, 0},{1, 0},{0, -1},{0, 1}};
        while(!q.empty()){
            auto [r, c] = q.front();
            q.pop();
            for(auto dir : dirs){
                int nrow = r + dir.first;
                int ncol = c + dir.second;
                if(nrow >= 0 && nrow < m && ncol >= 0 && ncol < n && dist[nrow][ncol] == -1){
                    dist[nrow][ncol] = dist[r][c] + 1;
                    q.push({nrow, ncol});
                }
            }
        }
        return dist;
    }
};