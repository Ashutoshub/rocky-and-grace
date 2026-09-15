class Solution {
public:
    bool isPalindrome(const string& s,int left ,int right){
        while(left < right){
            if(s[left] != s[right]){
                return false;
            }
            left++;
            right--;
        }
        return true;    
    }
    int maxPalindromes(string s, int k) {
        int n = s.length();
        int cnt = 0;
        int lastpicked_end = -1;
        for(int i = 0; i < n; i++){
            if(i - k + 1 > lastpicked_end && isPalindrome(s, i - k + 1, i)){
                cnt++;
                lastpicked_end = i;
                continue;
            }
            if(i - k > lastpicked_end && isPalindrome(s, i - k, i)){
                cnt++;
                lastpicked_end = i;
            }
        }
        return cnt;
    }
};