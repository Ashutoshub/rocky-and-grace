class DisjointSet{
    vector<int> parent, rank;
public:
    DisjointSet(int n){
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int findparent(int node){
        if(node == parent[node]) return node;
        return parent[node] = findparent(parent[node]);
    }
    void unionbyrank(int u, int v){
        int rootu = findparent(u);
        int rootv = findparent(v);
        if(rootu == rootv) return;
        if(rank[rootu] < rank[rootv]){
            parent[rootu] = rootv;
        }
        else if(rank[rootv] < rank[rootu]){
            parent[rootv] = rootu;
        }
        else{
            parent[rootv] = rootu;
            rank[rootu]++;
        }
    }
};
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> mapmailnode;
        for(int i = 0;i < n ; i++){
            for(int j = 1; j < accounts[i].size(); j++){
                string mail = accounts[i][j];
                if(mapmailnode.find(mail) == mapmailnode.end()){
                    mapmailnode[mail] = i;
                }
                else{
                    ds.unionbyrank(i, mapmailnode[mail]);
                }
            }
        }
        vector<vector<string>> mergedmail(n);
        for(auto it : mapmailnode){
            string mail = it.first;
            int rootnode = ds.findparent(it.second);
            mergedmail[rootnode].push_back(mail);
        }
        vector<vector<string>> ans;
        for(int i = 0; i < n; i++){
            if(mergedmail[i].empty()) continue;
            sort(mergedmail[i].begin(), mergedmail[i].end());
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            for(auto mail : mergedmail[i]){
                temp.push_back(mail);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};