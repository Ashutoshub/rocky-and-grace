class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        long long MOD = 1e9 + 7;
        int n = s.length();
        vector<int> ind;
        vector<long long> vals;
        for(int i = 0; i < n; i++){
            if(s[i] != '0'){
                ind.push_back(i);
                vals.push_back(s[i] - '0');
            }
        }
        int m = ind.size();
        vector<long long> prefsum(m + 1, 0);
        vector<long long> prefval(m + 1, 0);
        vector<long long> p10(m + 1, 1);
        for(int i = 0; i < m; i++){
            prefsum[i + 1] = prefsum[i] + vals[i];
            prefval[i + 1] = (prefval[i] * 10 + vals[i]) % MOD;
            p10[i + 1] = (p10[i] * 10) % MOD;
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for(const auto& q : queries){
            int l = q[0], r = q[1];
            auto ita = lower_bound(ind.begin(), ind.end(), l);
            auto itb = upper_bound(ind.begin(), ind.end(), r);
            int a = distance(ind.begin(), ita);
            int b = distance(ind.begin(), itb) - 1;
            if(a > b){
                ans.push_back(0);
            }
            else{
                long long currsum = prefsum[b + 1] - prefsum[a];
                int len = b - a + 1;
                long long curx = (prefval[b + 1] - (prefval[a] * p10[len]) % MOD + MOD) % MOD;
                long long res = (curx * currsum) % MOD;
                ans.push_back(res);
            }
        }
        return ans;
    }
};