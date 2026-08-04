class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<bool> present(101, false);
        int minval = nums[0];
        int maxval = nums[0];
        for(int num : nums){
            if(num < minval) minval = num;
            if(num > maxval) maxval = num;
            present[num] = true;
        }
        vector<int> missing;
        for(int i = minval + 1;i < maxval; ++i){
            if(!present[i]){
                missing.push_back(i);
            }
        }
        return missing;
    }
};