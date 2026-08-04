class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(4, 0);
        for(int i = n - 1; i >= 0; i--){
            int ans = stoneValue[i] - dp[(i + 1) % 4];
            if(i + 1 < n){
                ans = max(ans, stoneValue[i] +stoneValue[i + 1] - dp[(i + 2) % 4]);
            }
            if(i + 2 < n){
                ans = max(ans, stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] - dp[(i + 3) % 4]);
            }
            dp[i % 4] = ans;
        }
        if(dp[0] > 0) return "Alice";
        if(dp[0] < 0) return "Bob";
        return "Tie";
    }
};