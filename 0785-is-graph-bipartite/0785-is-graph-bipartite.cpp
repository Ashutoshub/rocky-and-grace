class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, 0);
        for(int i = 0; i < n; ++i){
            if(color[i] == 0){
                queue<int> q;
                q.push(i);
                color[i] = 1;
                while(!q.empty()){
                    int curr = q.front();
                    q.pop();
                    for(int neigh : graph[curr]){
                        if(color[neigh] == 0){
                            color[neigh] = -color[curr];
                            q.push(neigh);
                        }
                        else if(color[neigh] == color[curr]){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};