class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> counts(26, 0);
        for(char c : s){
            counts[c - 'a']++;
        }
        string lefthalf = "";
        string midchar = "";
        for(int i = 0; i < 26; i++){
            if(counts[i] > 0){
                lefthalf += string(counts[i] / 2, i + 'a');
                if(counts[i] % 2 != 0){
                    midchar = string(1, i + 'a');
                }
            }
        }
        string righthalf = lefthalf;
        reverse(righthalf.begin(), righthalf.end());
        return lefthalf + midchar + righthalf;
    }
};