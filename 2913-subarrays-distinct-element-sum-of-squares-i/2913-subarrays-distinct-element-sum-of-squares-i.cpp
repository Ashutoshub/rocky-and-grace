class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int totalsum = 0;
        int n = nums.size();
        for(int i = 0; i < n; ++i){
            unordered_set<int> distinct_element;
            for(int j = i; j < n; ++j){
                distinct_element.insert(nums[j]);
                int count = distinct_element.size();
                totalsum += count * count;
            }
        }
        return totalsum;
    }
};