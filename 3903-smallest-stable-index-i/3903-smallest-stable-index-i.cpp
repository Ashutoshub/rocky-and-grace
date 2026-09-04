class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 0) return -1;
        vector<int> suffixmin(n);
        suffixmin[n - 1] = nums[n - 1];
        for(int i = n - 2; i >= 0; --i){
            suffixmin[i] = min(suffixmin[i + 1], nums[i]);
        }
        int currmax = nums[0];
        for(int i = 0; i < n; ++i){
            currmax = max(currmax, nums[i]);
            int instabscore = currmax - suffixmin[i];
            if(instabscore <= k){
                return i;
            }
        }
        return -1;
    }
};