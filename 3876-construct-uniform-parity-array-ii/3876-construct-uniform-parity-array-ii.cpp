class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minval = nums1[0];
        bool hasodd = false;
        for(int num : nums1){
            if(num < minval){
                minval = num;
            }
            if(num % 2 != 0){
                hasodd = true;
            }
        }
        return (minval % 2 != 0) || !hasodd; 
    }
};