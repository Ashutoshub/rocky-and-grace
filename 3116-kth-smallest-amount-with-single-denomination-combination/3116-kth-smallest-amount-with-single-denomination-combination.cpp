class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());
        long long left = 1;
        long long right = (long long)coins[0] * k;
        long long ans = right;
        int n = coins.size();
        auto cntAmounts = [&](long long x){
            long long cnt = 0;
            for(int mask = 1; mask < (1 << n); ++mask){
                long long currlcm = 1;
                int setbits = 0;
                for(int i = 0; i < n; ++i){
                    if(mask &(1 << i)){
                        setbits++;
                        currlcm = std::lcm(currlcm, (long long)coins[i]);
                        if(currlcm > x) break;
                    }
                }
                if(currlcm > x) continue;
                if(setbits % 2 == 1){
                    cnt += (x / currlcm);
                }
                else{
                    cnt -= (x / currlcm);
                }
            }
            return cnt;
        };
        while(left <= right){
            long long mid = left + (right - left) / 2;
            if(cntAmounts(mid) >= k){
                ans = mid;
                right = mid - 1;
            }
            else{
                left = mid + 1;
            }
        }
        return ans;
    }
};