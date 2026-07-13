class DSU {
    vector<int> parent;
    vector<int> size;
public:
    DSU(int n){
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n;++i){
            parent[i] = i;
        }
    }
    int find(int x){
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int x, int y){
        int rootx = find(x);
        int rooty = find(y);
        if(rootx != rooty){
            if(size[rootx] < size[rooty]) swap(rootx, rooty);
            parent[rooty] = rootx;
            size[rootx] += size[rooty];
        }
    }
    bool connected(int x, int y){
        return find(x) == find(y);
    }
};
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int, int>> pos(n * n);
        for(int r = 0; r < n; ++r){
            for(int c = 0; c < n; ++c){
                pos[grid[r][c]] = {r, c}; 
            }
        }
        DSU dsu(n * n);
        int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(int t = 0; t < n * n; ++t){
            int r = pos[t].first;
            int c = pos[t].second;
            int currind = r * n + c;
            for(auto& dir : dirs){
                int nr = r + dir[0];
                int nc = c + dir[1];
                if(nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] < t){
                    int neighborind = nr * n + nc;
                    dsu.unite(currind, neighborind);
                }
            }
            if(dsu.connected(0, n * n -1)){
                return t;
            }
        }
        return 0;
    }
};