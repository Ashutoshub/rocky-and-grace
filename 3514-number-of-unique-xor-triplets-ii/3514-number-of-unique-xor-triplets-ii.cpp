class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        unordered_set<int> unique_set(nums.begin(), nums.end());
        vector<int> unique_nums(unique_set.begin(), unique_set.end());
        vector<bool> currset(2048, false);
        currset[0] = true;
        for(int round = 0; round < 3; ++round){
            vector<bool> nextset(2048, false);
            for(int val = 0; val < 2048; ++val){
                if(currset[val]){
                    for(int num : unique_nums){
                        nextset[val ^ num] = true;
                    }
                }
            }
            currset = nextset;
        }
        int uniquecnt = 0;
        for(bool ispresent : currset){
            if(ispresent){
                uniquecnt++;
            }
        }
        return uniquecnt;
    }
};