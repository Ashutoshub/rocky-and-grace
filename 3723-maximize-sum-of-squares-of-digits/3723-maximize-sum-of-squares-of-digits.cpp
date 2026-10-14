class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(sum > (long long)num * 9){
            return "";
        }
        int nines = sum / 9;
        int remainder = sum % 9;
        int zeros = num - nines - (remainder > 0 ? 1 : 0);
        string result = "";
        result.append(nines, '9');
        if(remainder > 0){
            result.push_back('0' + remainder);
        }
        result.append(zeros, '0');
        return result;
    }
};