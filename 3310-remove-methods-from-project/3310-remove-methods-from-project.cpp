class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for(const auto& inv : invocations){
            adj[inv[0]].push_back(inv[1]);
        }
        vector<bool> suspi(n, false);
        queue<int> q;
        q.push(k);
        suspi[k] = true;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            for(int neighbor: adj[curr]){
                if(!suspi[neighbor]){
                    suspi[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        bool canremove = true;
        for(const auto& inv : invocations){
            int u = inv[0];
            int v = inv[1];
            if(!suspi[u] && suspi[v]){
                canremove = false;
                break;
            }
        }
        vector<int> result;
        if(canremove){
            for(int i = 0; i < n; ++i){
                if(!suspi[i]){
                    result.push_back(i);
                }
            }
        }
        else{
            for(int i = 0; i < n; ++i){
                result.push_back(i);
            }
        }
        return result;
        
    }
};