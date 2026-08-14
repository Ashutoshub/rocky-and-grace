class Solution {
public:
    int maximumLengthSubstring(string s) {
        int charcnt[26] = {0};
        int left = 0;
        int maxlen = 0;
        for(int right = 0; right < s.length(); ++right){
            charcnt[s[right] - 'a']++;
            while(charcnt[s[right] - 'a'] > 2){
                charcnt[s[left] - 'a']--;
                left++;
            }
            maxlen = max(maxlen, right - left + 1);
        }
        return maxlen;
    }
};