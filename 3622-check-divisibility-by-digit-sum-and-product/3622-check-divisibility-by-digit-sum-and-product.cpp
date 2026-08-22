class Solution {
public:
    bool checkDivisibility(int n) {
        int temp = n;
        int digsum = 0;
        int digprod = 1;
        while(temp > 0){
            int dig = temp % 10;
            digsum += dig;
            digprod *= dig;
            temp /= 10;
        }
        int combined = digsum + digprod;
        return n % combined == 0;
    }
};