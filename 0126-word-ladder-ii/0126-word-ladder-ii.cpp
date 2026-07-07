class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<vector<string>> ans;
        if(dict.find(endWord) == dict.end()) return ans;
        unordered_map<string, vector<string>> adj;
        queue<string> q;
        q.push(beginWord);
        dict.erase(beginWord);
        bool found = false;
        while(!q.empty() && !found){
            int n = q.size();
            unordered_set<string> vislevel;
            for(int i = 0;i < n; ++i){
                string curr = q.front();
                q.pop();
                string temp = curr;
                for(int j = 0; j < curr.size(); ++j){
                    char orgchar = temp[j];
                    for(char c = 'a';c <= 'z'; ++c){
                        if(c == orgchar) continue;
                        temp[j] = c;
                        if(dict.count(temp)){
                            if(temp == endWord) found = true;
                            vislevel.insert(temp);
                            adj[temp].push_back(curr);        
                        }
                    }
                    temp[j] = orgchar;
                }
            }
            for(const string& w : vislevel){
                dict.erase(w);
                q.push(w);
            }
        }
        if(found){
            vector<string> path = {endWord};
            dfs(endWord, beginWord, adj, path, ans);
        }
        return ans;
    }
private:
    void dfs(string curr, string& beginWord,unordered_map<string, vector<string>>& adj, vector<string>& path, vector<vector<string>>& ans){
        if(curr == beginWord){
            vector<string> validpath = path;
            reverse(validpath.begin(), validpath.end());
            ans.push_back(validpath);
            return;
        }
        for(const string& parent: adj[curr]){
            path.push_back(parent);
            dfs(parent, beginWord, adj, path, ans);
            path.pop_back();
        }
    }
};