class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int prefixsum = nums[0];
        for(int i = 1; i < nums.size(); ++i){
            if(nums[i] == nums[i - 1] + 1){
                prefixsum += nums[i];
            }
            else{
                break;
            }
        }
        unordered_set<int> elements(nums.begin(), nums.end());
        int ans = prefixsum;
        while(elements.count(ans)){
            ans++;
        }
        return ans;
    }
};