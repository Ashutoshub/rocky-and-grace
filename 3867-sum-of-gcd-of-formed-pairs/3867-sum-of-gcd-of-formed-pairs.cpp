class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int  n = nums.size();
        vector<int> prefixgcd(n);
        int currmax = 0;
        for(int i = 0; i < n; ++i){
            currmax = max(currmax, nums[i]);
            prefixgcd[i] = std::gcd(nums[i], currmax); 
        }
        sort(prefixgcd.begin(), prefixgcd.end());
        long long totsum = 0;
        int left = 0;
        int right = n - 1;
        while(left < right){
            totsum += std::gcd(prefixgcd[left], prefixgcd[right]);
            left++;
            right--;
        }
        return totsum;
    }
};