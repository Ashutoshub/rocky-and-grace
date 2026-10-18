class Solution {
    long long mod = 1e9 + 7;
    vector<vector<long long>> table;
public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        table.resize(n + 1, vector<long long>(n + 1, 0));
        for(int i = 0; i <= n; ++i){
            table[i][0] = 1;
            table[i][i] = 1;
            for(int j = 1; j < i; ++j){
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j])% mod;
            }
        }
        return (dfs(nums) - 1 + mod) % mod;
    }
private:
    long long dfs(vector<int>& nums){
        int m = nums.size();
        if(m <= 2){
            return 1;
        }
        vector<int> left, right;
        int root = nums[0];
        for(int i = 1; i < m; ++i){
            if(nums[i] < root){
                left.push_back(nums[i]);
            }
            else{
                right.push_back(nums[i]);
            }
        }
        long long left_ways = dfs(left) % mod;
        long long right_ways = dfs(right) % mod;
        int L = left.size();
        int R = right.size();
        long long currways = table[L  + R][L];
        return (((currways * left_ways)% mod)* right_ways) % mod;
    }
};