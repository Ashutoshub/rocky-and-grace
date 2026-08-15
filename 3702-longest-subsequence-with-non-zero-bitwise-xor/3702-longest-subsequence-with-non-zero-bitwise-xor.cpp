class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int totXOR = 0;
        int zerocnt = 0;
        int n = nums.size();
        for(int num : nums){
            totXOR ^= num;
            if(num == 0){
                zerocnt++;
            }
        }
        if(totXOR != 0){
            return n;
        }
        if(zerocnt == n){
            return 0;
        }
        return n - 1;
    }
};