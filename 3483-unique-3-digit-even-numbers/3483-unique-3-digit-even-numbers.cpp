class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int count[10] = {0};
        for(int digit: digits){
            count[digit]++;
        }
        int validnums = 0;
        for(int num = 100; num <= 998; num += 2){
            int c = num % 10;
            int b = (num / 10) % 10;
            int a = num / 100;
            count[c]--;
            count[b]--;
            count[a]--;
            if(count[a] >= 0 && count[b] >= 0 && count[c] >= 0){
                validnums++;
            }
            count[c]++;
            count[b]++;
            count[a]++;
        }
        return validnums;
    }
};