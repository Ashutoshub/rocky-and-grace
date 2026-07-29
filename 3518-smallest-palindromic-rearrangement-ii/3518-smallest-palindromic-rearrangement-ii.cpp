class Solution {
public:
    long long getways(vector<int>& counts){
        long long ways = 1;
        int totalspots = 0;
        for(int c : counts){
            for(int j = 1;j <= c; ++j){
                totalspots++;
                ways = (ways * totalspots)/ j;
                if(ways > 1000000){
                    return 1000001;
                }
            }
        }
        return ways;
    }
    string smallestPalindrome(string s, int k) {
        vector<int> counts(26, 0);
        for(char c: s) counts[c - 'a']++;
        vector<int> halfcnt(26, 0);
        char midchar = 0;
        int n = s.length() / 2;
        for(int i = 0; i < 26; ++i){
            halfcnt[i] = counts[i] / 2;
            if(counts[i] % 2 != 0){
                midchar = i + 'a';
            }
        }
        long long totalways = getways(halfcnt);
        if(totalways < k) return "";
        string firsthalf = "";
        for(int i = 0; i < n; ++i){
            for(int charidx = 0;charidx < 26; ++charidx){
                if(halfcnt[charidx] > 0){
                    halfcnt[charidx]--;
                    long long ways = getways(halfcnt);
                    if(ways >= k){
                        firsthalf += (char)(charidx + 'a');
                        break;
                    }
                    else{
                        k -= ways;
                        halfcnt[charidx]++;
                    }
                }
            }
        }
        string result = firsthalf;
        if(s.length() % 2 != 0){
            result += midchar;
        }
        string secondhalf = firsthalf;
        reverse(secondhalf.begin(), secondhalf.end());
        result += secondhalf;
        return result;
    }
};