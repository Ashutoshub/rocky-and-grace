class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int left = 0;
        int maxlen = 0;
        unordered_map<int, int> freqmap;
        for(int right = 0; right < nums.size(); right++){
            freqmap[nums[right]]++;
            while(freqmap[nums[right]] > k){
                freqmap[nums[left]]--;
                left++;
            }
            maxlen = max(maxlen, right - left + 1);
        }
        return maxlen;
    }
};