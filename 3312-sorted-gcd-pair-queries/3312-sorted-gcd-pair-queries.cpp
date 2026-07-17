class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxval = 0;
        for(int x : nums){
            maxval = max(maxval, x);
        }
        vector<long long> cnt(maxval + 1, 0);
        for(int x : nums){
            cnt[x]++;
        }
        vector<long long> exctcnt(maxval + 1, 0);
        for(int g = maxval; g >= 1; --g){
            long long multiplecnt = 0;
            for(int i = g; i <= maxval; i+= g){
                multiplecnt += cnt[i];
            }
            long long pairs = multiplecnt * (multiplecnt - 1) / 2;
            for(int i = 2 * g; i <= maxval; i += g){
                pairs -= exctcnt[i];
            }
            exctcnt[g] = pairs; 
        }
        vector<long long> prefix(maxval + 1,0);
        for(int i = 1; i <= maxval; ++i){
            prefix[i] = prefix[i - 1] + exctcnt[i];
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for(long long q : queries){
            int left = 1, right = maxval;
            int result = maxval;
            while(left <= right){
                int mid = left + (right - left) / 2;
                if(prefix[mid] > q){
                    result = mid;
                    right = mid - 1;
                }
                else{
                    left = mid + 1;
                }
            }
            ans.push_back(result);
        }
        return ans;
    }
};