class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> freq(26, 0);
        for(char c : s){
            freq[c - 'a']++;
        } 
        int max_i = 0;
        while(max_i < n && freq[target[max_i] - 'a'] > 0){
            freq[target[max_i] - 'a']--;
            max_i++;
        }
        int i = max_i;
        if(i == n){
            i--;
            freq[target[i] - 'a']++;
        }
        while(i >= 0){
            char best_c = 0;
            for(int c = target[i] - 'a' + 1; c < 26; c++){
                if(freq[c] > 0){
                    best_c = c + 'a';
                    break;
                }
            }
            if(best_c != 0){
                string res = target.substr(0, i);
                res += best_c;
                freq[best_c - 'a']--;
                for(int c = 0; c < 26; c++){
                    res += string(freq[c], c + 'a');
                }
                return res;
            }
            i--;
            if(i >= 0){
                freq[target[i] - 'a']++;
            }
        }
        return "";
    }
};