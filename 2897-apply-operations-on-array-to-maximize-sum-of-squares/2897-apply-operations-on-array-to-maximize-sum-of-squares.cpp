class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        long long mod = 1e9 + 7;
        vector<int> bitCount(32, 0);
        for(int num : nums){
            for(int i = 0; i < 32; ++i){
                if((num >> i) & 1){
                    bitCount[i]++;
                }
            }
        }
        long long maxsum = 0;
        for(int i = 0; i < k; ++i){
            long long currnum = 0;
            for(int bit = 0;bit < 32; ++bit){
                if(bitCount[bit] > 0){
                    currnum |= (1LL << bit);
                    bitCount[bit]--;
                }
            }
            maxsum = (maxsum + (currnum * currnum) % mod) % mod;
        }
        return maxsum;
    }
};