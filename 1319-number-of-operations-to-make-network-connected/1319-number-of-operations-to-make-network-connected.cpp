class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    int comp;
public:
    DSU(int n){
        parent.resize(n);
        rank.resize(n, 0);
        comp = n;
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    int find(int i){
        if(parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j){
        int rooti = find(i);
        int rootj = find(j);
        if(rooti != rootj){
            if(rank[rooti] < rank[rootj]){
                parent[rooti] = rootj;
            }
            else if(rank[rooti] > rank[rootj]){
                parent[rootj] = rooti;
            }
            else{
                parent[rootj] = rooti;
                rank[rooti]++;
            }
            comp--;
        }
    }
    int getcomp(){
        return comp;
    }
};
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if(connections.size() < n - 1){
            return -1;
        }
        DSU dsu(n);
        for(const auto& conn : connections){
            dsu.unite(conn[0], conn[1]);
        }
        return dsu.getcomp() - 1;
    }
};