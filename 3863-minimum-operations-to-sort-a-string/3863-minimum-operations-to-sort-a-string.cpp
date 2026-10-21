class Solution {
public:
    int minOperations(string s) {
        int n = s.length();
        if(std::is_sorted(s.begin(), s.end())){
            return 0;
        }
        if(n == 2){
            return -1;
        }
        char mn = *std::min_element(s.begin(), s.end());
        char mx = *std::max_element(s.begin(), s.end());
        if(s[0] == mn || s[n - 1] == mx){
            return 1;
        }
        bool mn_in_prefix = false;
        for(int i =0;i < n - 1; ++i){
            if(s[i] == mn){
                mn_in_prefix = true;
                break;
            }
        }
        bool mx_in_suffix = false;
        for(int i = 1; i < n; ++i){
            if(s[i] == mx){
                mx_in_suffix = true;
                break;
            }
        }
        if(mn_in_prefix || mx_in_suffix){
            return 2;
        }
        return 3;
    }
};