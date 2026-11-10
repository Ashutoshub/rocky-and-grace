/**
 * @param {number} n
 * @param {number[]} costs
 * @return {number}
 */
var climbStairs = function(n, costs) {
    // dp[j] will store the minimum cost to reach step j.
    // Since costs is 0-indexed in code but represents 1-indexed steps, 
    // let's be careful with indexing. 
    // costs[i] corresponds to step i+1 in the problem description.
    
    const dp = new Array(n + 1).fill(Infinity);
    dp[0] = 0; // Base case: start at step 0 with cost 0

    for (let j = 1; j <= n; j++) {
        // Try jumping from i to j, where i can be j-1, j-2, or j-3
        for (let k = 1; k <= 3; k++) {
            let i = j - k;
            if (i >= 0) {
                // cost[j - 1] because the array 'costs' is 0-indexed
                let jumpCost = dp[i] + costs[j - 1] + (j - i) * (j - i);
                dp[j] = Math.min(dp[j], jumpCost);
            }
        }
    }

    return dp[n];
};