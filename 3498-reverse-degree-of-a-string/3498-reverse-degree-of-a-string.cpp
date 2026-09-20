class Solution {
public:
    int reverseDegree(string s) {
        int totalSum = 0;
        for(int i = 0; i < s.length(); ++i){
            int reverse = 26 - (s[i] - 'a');
            int position = i + 1;
            totalSum += reverse * position;
        }
        return totalSum;
    }
};