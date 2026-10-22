class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0;
        int inc_breaks = 0;
        int dec_breaks = 0;
        int zero_idx = -1;
        for(int i = 0;i < n; ++i){
            if(nums[i] == 0){
                zero_idx = i;
            }
            if((nums[i] + 1) % n != nums[(i + 1) % n]){
                inc_breaks++;
            }
            if((nums[i] - 1 + n) % n != nums[(i + 1) % n]){
                dec_breaks++;
            }
        }
        int min_ops = 1e9;
        if(inc_breaks == 0){
            if(zero_idx == 0) return 0;
            int cost_just_shift = zero_idx;
            int cost_reverse_shift_reverse = n - zero_idx + 2;
            min_ops = min({min_ops,cost_just_shift, cost_reverse_shift_reverse});
        }
        if(dec_breaks == 0){
            int cost_shift_then_reverse = zero_idx + 2;
            int cost_reverse_then_shift = n - zero_idx;
            min_ops = min({min_ops, cost_shift_then_reverse,cost_reverse_then_shift});
        }
        return min_ops == 1e9 ? -1: min_ops; 
    }
};