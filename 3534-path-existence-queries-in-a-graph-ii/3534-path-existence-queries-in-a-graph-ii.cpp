class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> S = nums;
        sort(S.begin(), S.end());
        vector<int> comp(n, 0);
        for(int i = 1; i < n; i++){
            if(S[i] - S[i - 1] <= maxDiff){
                comp[i] = comp[i - 1];
            }
            else{
                comp[i] = comp[i - 1] + 1;
            }
        }
        int LOG = 20;
        vector<vector<int>> up(n, vector<int>(LOG, 0));
        for(int i = 0; i < n; i++){
            auto it = upper_bound(S.begin(), S.end(), S[i] + maxDiff);
            up[i][0] = distance(S.begin(), it) - 1;
        }
        for(int k = 1; k < LOG; k++){
            for(int i = 0; i < n; i++){
                up[i][k] = up[up[i][k - 1]][k - 1];
            }
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for(const auto& q: queries){
            int u = q[0], v = q[1];
            if(u == v){
                ans.push_back(0);
                continue;
            }
            int strtval = min(nums[u], nums[v]);
            int tarval = max(nums[u], nums[v]);
            if(strtval == tarval){
                ans.push_back(1);
                continue;
            }
            int L = distance(S.begin(), lower_bound(S.begin(), S.end(), strtval));
            int R = distance(S.begin(), lower_bound(S.begin(), S.end(), tarval));
            if(comp[L] != comp[R]){
                ans.push_back(-1);
                continue;
            }
            int curr = L;
            int jumps = 0;
            for(int k = LOG - 1; k >= 0; k--){
                if(up[curr][k] < R){
                    curr = up[curr][k];
                    jumps += (1 << k);
                }
            }
            ans.push_back(jumps + 1);
        }
        return ans;
    }
};