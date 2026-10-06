class Solution {
public:
    int minAddToMakeValid(string s) {
        int opencnt = 0;
        int addneeded = 0;
        for(char c : s){
            if(c == '('){
                opencnt++;
            }
            else{
                if(opencnt > 0){
                    opencnt--;
                }
                else{
                    addneeded++;
                }
            }
        }
        return addneeded + opencnt;
    }
};