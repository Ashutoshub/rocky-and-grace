class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int valid_island = 0;
        for(int i = 0;i < m; ++i){
            for(int j = 0;j < n; ++j){
                if(grid[i][j] > 0){
                    long long curr_island_sum = 0;
                    dfs(grid, i, j, m, n, curr_island_sum);
                    if(curr_island_sum % k == 0){
                        valid_island++;
                    }
                }
            }
        }
        return valid_island;
    }
private:
    void dfs(vector<vector<int>>& grid, int r, int c, int m, int n, long long& curr_sum){
        if(r < 0 || r >= m ||c < 0 ||c >= n || grid[r][c] == 0){
            return;
        }
        curr_sum += grid[r][c];
        grid[r][c] = 0;
        dfs(grid, r + 1, c, m, n, curr_sum);
        dfs(grid, r - 1, c, m, n, curr_sum);
        dfs(grid, r, c + 1, m, n, curr_sum);
        dfs(grid, r, c - 1, m, n, curr_sum);
    }
};