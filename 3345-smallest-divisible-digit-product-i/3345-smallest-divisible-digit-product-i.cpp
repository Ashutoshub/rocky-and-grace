class Solution {
public:
    int smallestNumber(int n, int t) {
        while(true){
            int currnum = n;
            int digprod = 1;
            while(currnum > 0){
                digprod *= (currnum % 10);
                currnum /= 10;
            }
            if(digprod % t == 0){
                return n;
            }
            n++;
        }
    }
};