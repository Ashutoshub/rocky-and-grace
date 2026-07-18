class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        int prev2 = 0;
        int prev1 = 0;
        for(int i =0; i < nums.size(); i++){
            int curr = max(prev2 + nums[i], prev1);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};