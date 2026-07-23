class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n;
        int msbposition = __lg(n);
        return 1 << (msbposition + 1);
    }
};