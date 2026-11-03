class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int maxval = nums[0];
        int totalsum = 0;
        for(int num : nums){
            if(num > maxval){
                maxval = num;
            }
            totalsum += num;
        }
        return (n * maxval) - totalsum;
    }
};