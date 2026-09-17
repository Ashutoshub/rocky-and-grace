class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> best_till(n, INT_MAX);
        int ans = INT_MAX;
        int left = 0;
        int windowsum = 0;
        int minlensofar = INT_MAX;
        for(int right = 0; right < n; ++right){
            windowsum += arr[right];
            while(windowsum > target && left <= right){
                windowsum -= arr[left];
                left++;
            }
            if(windowsum == target){
                int currlen = right - left + 1;
                if(left > 0 && best_till[left - 1] != INT_MAX){
                    ans = min(ans, currlen + best_till[left - 1]);
                }
                minlensofar = min(minlensofar, currlen);
            }
            best_till[right] = minlensofar;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};