class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> comp(n, 0);
        int currcomp = 0;
        for(int i = 1; i < n; ++i){
            if(nums[i] - nums[i - 1] > maxDiff){
                currcomp++;
            }
            comp[i] = currcomp;
        }
        int q = queries.size();
        vector<bool> ans(q);
        for(int i = 0; i < q; ++i){
            int u = queries[i][0];
            int v = queries[i][1];
            ans[i] = (comp[u] == comp[v]);
        }
        return ans;
    }
};