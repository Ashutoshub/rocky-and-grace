class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int totel = m * n;
        vector<vector<int>> newgrid(m, vector<int>(n,0));
        for(int r = 0; r < m; ++r){
            for(int c = 0; c < n; ++c){
                int flatind = r * n + c;
                int newflatind = (flatind + k) % totel;
                int newr = newflatind / n;
                int newc = newflatind % n;
                newgrid[newr][newc] = grid[r][c];
            }
        }
        return newgrid;
    }
};