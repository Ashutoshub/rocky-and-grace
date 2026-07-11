class Solution {
    unordered_map<int, int> parent;
    int comp = 0;
    int find(int x){
        if(!parent.count(x)){
            parent[x] = x;
            comp++;
        }
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x , int y){
        int rootx = find(x);
        int rooty = find(y);
        if(rootx != rooty){
            parent[rootx] = rooty;
            comp--;
        }
    }
public:
    int removeStones(vector<vector<int>>& stones) {
        for(const auto& stone : stones){
            unite(stone[0], stone[1] + 10001);
        }
        return stones.size() - comp;
    }
};