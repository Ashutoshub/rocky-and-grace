class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int lesscnt = 0;
        int equalcnt = 0;
        for(int num : nums){
            if(num < target){
                lesscnt++;
            }
            else if(num == target){
                equalcnt++;
            }
        }
        vector<int> result;
        result.reserve(equalcnt);
        for(int i = 0; i < equalcnt; ++i){
            result.push_back(lesscnt + i);
        }
        return result;
    }
};