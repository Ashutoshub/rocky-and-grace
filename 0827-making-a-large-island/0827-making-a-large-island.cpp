class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int island_id = 2;
        unordered_map<int ,int> islandareas;
        int maxarea = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    int area = dfs(grid, i, j, island_id);
                    islandareas[island_id] = area;
                    maxarea = max(maxarea, area);
                    island_id++;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j =0; j < n; j++){
                if(grid[i][j] == 0){
                    unordered_set<int> neighborid;
                    if(i > 0 && grid[i - 1][j] > 1) neighborid.insert(grid[i - 1][j]);
                    if(i < n - 1 && grid[i + 1][j] > 1) neighborid.insert(grid[i + 1][j]);
                    if(j > 0 && grid[i][j - 1] > 1) neighborid.insert(grid[i][j - 1]);
                    if(j < n - 1 && grid[i][j + 1] > 1) neighborid.insert(grid[i][j + 1]);
                    int potarea = 1;
                    for(int id : neighborid){
                        potarea += islandareas[id];
                    }
                    maxarea = max(maxarea, potarea);
                }
            }
        }
        return maxarea;
    }
private:
    int dfs(vector<vector<int>>& grid, int r,int c, int id){
        int n = grid.size();
        if(r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1){
            return 0;
        }
        grid[r][c] = id;
        int area = 1;
        area += dfs(grid, r + 1, c, id);
        area += dfs(grid, r - 1, c, id);
        area += dfs(grid, r, c + 1, id);
        area += dfs(grid, r, c - 1, id);
        return area;
    }
};