class Solution {
public:
    int minInsertions(string s) {
        int insertion = 0;
        int right_needed = 0;
        for(char c : s){
            if(c == '('){
                if(right_needed % 2 != 0){
                    insertion++;
                    right_needed--;
                }
                right_needed += 2;
            }
            else{
                right_needed--;
                if(right_needed < 0){
                    insertion++;
                    right_needed += 2;
                }
            }
        }
        return right_needed + insertion;
    }
};