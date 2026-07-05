class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int orgcol = image[sr][sc];
        if(orgcol != color){
            dfs(image, sr, sc, orgcol, color);
        }
        return image;
    }
private:
    void dfs(vector<vector<int>>& image,int r, int c, int orgcol, int newcol){
        if(r < 0 || r >= image.size() || c < 0 || c >= image[0].size() || image[r][c] != orgcol){
            return;
        }
        image[r][c] = newcol;
        dfs(image, r - 1, c, orgcol, newcol);
        dfs(image, r + 1, c, orgcol, newcol);
        dfs(image, r, c - 1, orgcol, newcol);
        dfs(image, r, c + 1, orgcol, newcol);
    }
};