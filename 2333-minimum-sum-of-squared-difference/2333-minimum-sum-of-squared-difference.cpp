class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        vector<long long> count(100001, 0);
        long long total_diff_sum = 0;
        for(int i = 0;i < n; ++i){
            int diff = abs(nums1[i] - nums2[i]);
            count[diff]++;
            total_diff_sum += diff;
        }
        if(k >= total_diff_sum) return 0;
        for(int i = 100000; i > 0 && k > 0; --i){
            if(count[i] > 0){
                long long reductions = min(k, count[i]);
                count[i] -= reductions;
                count[i - 1] += reductions;
                k -= reductions; 
            }
        }
        long long ans = 0;
        for(long long i = 1; i <= 100000; ++i){
            if(count[i] > 0){
                ans += count[i] * (i * i);
            }
        }
        return ans;
    }
};