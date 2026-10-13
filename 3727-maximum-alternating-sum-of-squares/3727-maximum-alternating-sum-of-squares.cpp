class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(),[](int a, int b){
            return abs(a) < abs(b);
        });
        long long maxscore = 0;
        int subtracthalf = n / 2;
        for(int i = 0;i < n; ++i){
            long long square =(long long)(nums[i] * nums[i]);
            if(i < subtracthalf){
                maxscore -= square;
            }
            else{
                maxscore += square;
            }
        }
        return maxscore;
    }
};