class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> first(26, -1), last(26, -1);
        for(int i = 0; i < n; ++i){
            if(first[s[i] - 'a'] == -1) first[s[i] - 'a'] = i;
            last[s[i] - 'a'] = i;
        }
        vector<vector<int>> adj(26), radj(26);
        vector<bool> active(26, false);
        for(int i = 0; i < 26; ++i){
            if(first[i] != -1){
                active[i] = true;
                vector<bool> seen(26, false);
                for(int k = first[i]; k <= last[i]; ++k){
                    int j = s[k] - 'a';
                    if(i != j && !seen[j]){
                        seen[j] = true;
                        adj[i].push_back(j);
                        radj[j].push_back(i);
                    }
                }
            }
        }
        vector<bool> visited(26, false);
        vector<int> order;
        function<void(int)> dfs1 = [&](int u){
            visited[u] = true;
            for(int v : adj[u]){
                if(!visited[v]) dfs1(v);
            }
            order.push_back(u);
        };
        for(int i = 0; i < 26; ++i){
            if(active[i] && !visited[i]){
                dfs1(i);
            }
        }
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        function<void(int, vector<int>&)> dfs2 = [&](int u, vector<int>& scc){
            visited[u] = true;
            scc.push_back(u);
            for(int v : radj[u]){
                if(!visited[v]) dfs2(v, scc);
            }
        };
        visited.assign(26, false);
        for(int i = order.size() - 1; i >= 0; --i){
            int u = order[i];
            if(!visited[u]){
                vector<int> scc;
                dfs2(u, scc);
                sccs.push_back(scc);
            }
        }
        vector<string> result;
        for(const auto& scc : sccs){
            bool issink = true;
            vector<bool> inscc(26, false);
            for(int u : scc) inscc[u] = true;
            for(int u : scc){
                for(int v : adj[u]){
                    if(!inscc[v]){
                        issink = false;
                        break;
                    }
                }
                if(!issink) break;
            }
            if(issink){
                int minfirst = n, maxlast = -1;
                for(int u : scc){
                    minfirst = min(minfirst, first[u]);
                    maxlast = max(maxlast, last[u]);
                }
                result.push_back(s.substr(minfirst, maxlast - minfirst + 1));
            }
        }
        return result;
    }
};