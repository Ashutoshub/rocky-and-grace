class Solution {
    int memo[205][205][205];
    const int MOD = 1e9 + 7;
    int getgcd(int a , int b){
        if(a == 0) return b;
        if(b == 0) return a;
        return std::gcd(a, b);
    }
    int solve(int i, int g1, int g2, const vector<int>& nums){
        if(i == nums.size()){
            if(g1 == g2 & g1 > 0){
                return 1;
            }
            return 0;
        }
        if(memo[i][g1][g2] != -1){
            return memo[i][g1][g2];
        }
        long long ways = 0;
        ways = (ways + solve(i + 1, g1, g2, nums)) % MOD;
        ways = (ways + solve(i + 1,getgcd(g1, nums[i]), g2, nums)) % MOD;
        ways = (ways + solve(i + 1, g1,getgcd(g2, nums[i]), nums)) % MOD;
        return memo[i][g1][g2] = ways;
    }
public:
    int subsequencePairCount(vector<int>& nums) {
        memset(memo, -1, sizeof(memo));
        return solve(0, 0, 0, nums);
    }
};