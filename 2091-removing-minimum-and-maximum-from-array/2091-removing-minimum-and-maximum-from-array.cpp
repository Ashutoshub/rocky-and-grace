class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n;
        int minind = 0, maxind = 0;
        for(int k = 1; k < n; ++k){
            if(nums[k] < nums[minind]) minind = k;
            if(nums[k] > nums[maxind]) maxind = k;
        }
        int left = min(minind, maxind);
        int right = max(minind, maxind);
        int delfrnt = right + 1;
        int delback = n - left;
        int delbothends = (left + 1) + (n - right);
        return min({delfrnt, delback, delbothends}); 
    }
};