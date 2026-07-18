class Solution {
private:
    int getgcd(int a, int b){
        if(b == 0){
            return a;
        }
        return getgcd(b, a % b);
    }
public:
    int findGCD(vector<int>& nums) {
        int mn = nums[0];
        int mx = nums[0];
        for(int num : nums){
            mn = min(mn, num);
            mx = max(mx, num);
        }
        return getgcd(mn, mx);
    }
};