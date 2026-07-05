class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        vector<vector<int>> dp(n , vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));
        dp[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;
        vector<pair<int, int>> dirs{{1, 0},{0 , 1},{1, 1}};
        for(int r = n - 1; r >= 0; --r){
            for(int c = n - 1; c >= 0; --c){
                if(board[r][c] == 'X' || (r == n - 1 && c == n - 1)){
                    continue;
                }
                int prevmax = -1;
                for(const auto& dir: dirs){
                    int prevr = r + dir.first;
                    int prevc = c + dir.second;
                    if(prevr < n && prevc < n && dp[prevr][prevc] != -1){
                        prevmax = max(prevmax, dp[prevr][prevc]);
                    }
                }
                if(prevmax == -1){
                    continue;
                }
                int currval = (board[r][c] == 'E') ? 0 : (board[r][c] - '0');
                dp[r][c] = prevmax + currval;
                for(const auto& dir : dirs){
                    int prevr = r + dir.first;
                    int prevc = c + dir.second;
                    if(prevr < n && prevc < n && dp[prevr][prevc] == prevmax){
                        ways[r][c] = (ways[r][c] + ways[prevr][prevc]) % MOD;
                    }
                }
            }
        }
        if(dp[0][0] == -1){
            return {0, 0};
        }
        return {dp[0][0], ways[0][0]};  
    }
};