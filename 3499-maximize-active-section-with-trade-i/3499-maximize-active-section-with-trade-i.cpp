class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        string t = "1" + s + "1";
        vector<int> blocks;
        int n = t.length();
        int cnt = 1;
        for(int i = 1;i < n; ++i){
            if(t[i] == t[i - 1]){
                cnt++;
            }
            else{
                blocks.push_back(cnt);
                cnt = 1;
            }
        }
        blocks.push_back(cnt);
        int maxgain = 0;
        for(int i = 2; i < (int)blocks.size() - 1; i += 2){
            int currgain = blocks[i - 1] + blocks[i + 1];
            maxgain = max(maxgain, currgain);
        }
        int ogones = 0;
        for(char c : s){
            if(c == '1') ogones++;
        }
        return ogones + maxgain;
    }
};