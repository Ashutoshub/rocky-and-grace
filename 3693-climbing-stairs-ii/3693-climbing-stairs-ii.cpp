class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        for(int j = 1; j <= n; ++j){
            long long step_cost = costs[j - 1];
            for(int k = 1; k <= 3; ++k){
                int i = j - k;
                if(i >= 0 && dp[i] != LLONG_MAX){
                    long long jump_cost = (long long) k * k;
                    dp[j] = min(dp[j], dp[i] + jump_cost + step_cost);
                }
            }
        }
        return dp[n];
    }
};