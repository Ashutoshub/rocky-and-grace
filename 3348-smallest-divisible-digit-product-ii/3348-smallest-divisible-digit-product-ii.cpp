class Solution {
    int dp[60][40];
    int f2[10] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
    int f3[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
    int f5[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    int f7[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};

    void buildDP() {
        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 40; ++j) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 0;
                    continue;
                }
                dp[i][j] = 1e9;
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 1)][j]);             // use '2'
                dp[i][j] = min(dp[i][j], 1 + dp[i][max(0, j - 1)]);             // use '3'
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 2)][j]);             // use '4'
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 1)][max(0, j - 1)]); // use '6'
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 3)][j]);             // use '8'
                dp[i][j] = min(dp[i][j], 1 + dp[i][max(0, j - 2)]);             // use '9'
            }
        }
    }

public:
    string smallestNumber(string num, long long t) {
        buildDP();

        // 1. Factorize t
        int t2 = 0, t3 = 0, t5 = 0, t7 = 0;
        long long temp = t;
        while (temp % 2 == 0) { t2++; temp /= 2; }
        while (temp % 3 == 0) { t3++; temp /= 3; }
        while (temp % 5 == 0) { t5++; temp /= 5; }
        while (temp % 7 == 0) { t7++; temp /= 7; }
        
        // If t has other prime factors, it's impossible
        if (temp > 1) return "-1";

        int n = num.length();
        int z = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                z = i;
                break;
            }
        }

        // 2. Check if the original num is already valid
        if (z == n) {
            int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
            for (char c : num) {
                c2 += f2[c - '0'];
                c3 += f3[c - '0'];
                c5 += f5[c - '0'];
                c7 += f7[c - '0'];
            }
            if (c2 >= t2 && c3 >= t3 && c5 >= t5 && c7 >= t7) return num;
        }

        // 3. Find the divergence point
        int start_i = min(n - 1, z);
        int p2 = 0, p3 = 0, p5 = 0, p7 = 0;
        
        // Pre-calculate prefix factors up to start_i - 1
        for (int j = 0; j < start_i; ++j) {
            p2 += f2[num[j] - '0'];
            p3 += f3[num[j] - '0'];
            p5 += f5[num[j] - '0'];
            p7 += f7[num[j] - '0'];
        }

        string ans = "";
        for (int i = start_i; i >= 0; --i) {
            // Try to replace num[i] with a strictly greater digit
            for (int d = (num[i] - '0') + 1; d <= 9; ++d) {
                int n2 = p2 + f2[d], n3 = p3 + f3[d], n5 = p5 + f5[d], n7 = p7 + f7[d];
                int r2 = max(0, t2 - n2);
                int r3 = max(0, t3 - n3);
                int r5 = max(0, t5 - n5);
                int r7 = max(0, t7 - n7);

                int rem_len = n - 1 - i;
                
                // If we can satisfy remaining factors in the remaining length
                if (r5 + r7 + dp[r2][r3] <= rem_len) {
                    ans = num.substr(0, i);
                    ans.push_back(d + '0');
                    
                    int cur2 = n2, cur3 = n3, cur5 = n5, cur7 = n7;
                    
                    // Greedily fill the rest with the smallest possible digits
                    for (int k = i + 1; k < n; ++k) {
                        for (int nd = 1; nd <= 9; ++nd) {
                            int tr2 = max(0, t2 - (cur2 + f2[nd]));
                            int tr3 = max(0, t3 - (cur3 + f3[nd]));
                            int tr5 = max(0, t5 - (cur5 + f5[nd]));
                            int tr7 = max(0, t7 - (cur7 + f7[nd]));
                            int trem_len = n - 1 - k;
                            
                            if (tr5 + tr7 + dp[tr2][tr3] <= trem_len) {
                                ans.push_back(nd + '0');
                                cur2 += f2[nd]; cur3 += f3[nd]; cur5 += f5[nd]; cur7 += f7[nd];
                                break;
                            }
                        }
                    }
                    return ans;
                }
            }
            // Remove the contribution of num[i-1] as we backtrack further left
            if (i > 0) {
                p2 -= f2[num[i - 1] - '0'];
                p3 -= f3[num[i - 1] - '0'];
                p5 -= f5[num[i - 1] - '0'];
                p7 -= f7[num[i - 1] - '0'];
            }
        }

        // 4. If no prefix works, build the smallest valid number of a longer length
        int m = max(n + 1, t5 + t7 + dp[t2][t3]);
        int cur2 = 0, cur3 = 0, cur5 = 0, cur7 = 0;
        
        for (int k = 0; k < m; ++k) {
            for (int nd = 1; nd <= 9; ++nd) {
                int tr2 = max(0, t2 - (cur2 + f2[nd]));
                int tr3 = max(0, t3 - (cur3 + f3[nd]));
                int tr5 = max(0, t5 - (cur5 + f5[nd]));
                int tr7 = max(0, t7 - (cur7 + f7[nd]));
                
                if (tr5 + tr7 + dp[tr2][tr3] <= m - 1 - k) {
                    ans.push_back(nd + '0');
                    cur2 += f2[nd]; cur3 += f3[nd]; cur5 += f5[nd]; cur7 += f7[nd];
                    break;
                }
            }
        }
        return ans;
    }
};