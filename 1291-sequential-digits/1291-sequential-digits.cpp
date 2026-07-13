class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        string digits = "123456789";
        vector<int> result;
        for(int len = 2; len <= 9; ++len){
            for(int strt = 0; strt <= 9 - len; ++strt){
                string sub = digits.substr(strt, len);
                int num = stoi(sub);
                if(num >= low && num <= high){
                    result.push_back(num);
                }
            }
        }
        return result;
    }
};