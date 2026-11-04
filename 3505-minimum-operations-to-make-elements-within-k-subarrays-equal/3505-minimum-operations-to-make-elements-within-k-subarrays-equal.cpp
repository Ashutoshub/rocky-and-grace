#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        
        // Step 1: Precompute the cost for each window of size x using dual multisets
        vector<long long> windowCost(n - x + 1, 0);
        multiset<int> leftHeap, rightHeap;
        long long leftSum = 0, rightSum = 0;

        auto balance = [&]() {
            while (leftHeap.size() > rightHeap.size() + 1) {
                int val = *leftHeap.rbegin();
                leftHeap.erase(leftHeap.find(val));
                leftSum -= val;
                rightHeap.insert(val);
                rightSum += val;
            }
            while (rightHeap.size() > leftHeap.size()) {
                int val = *rightHeap.begin();
                rightHeap.erase(rightHeap.find(val));
                rightSum -= val;
                leftHeap.insert(val);
                leftSum += val;
            }
        };

        auto add = [&](int val) {
            if (leftHeap.empty() || val <= *leftHeap.rbegin()) {
                leftHeap.insert(val);
                leftSum += val;
            } else {
                rightHeap.insert(val);
                rightSum += val;
            }
            balance();
        };

        auto remove = [&](int val) {
            auto it = leftHeap.find(val);
            if (it != leftHeap.end()) {
                leftHeap.erase(it);
                leftSum -= val;
            } else {
                rightHeap.erase(rightHeap.find(val));
                rightSum -= val;
            }
            balance();
        };

        // Initialize the first window
        for (int i = 0; i < x; ++i) {
            add(nums[i]);
        }

        auto getCost = [&]() {
            long long median = *leftHeap.rbegin();
            long long lcCount = leftHeap.size();
            long long rcCount = rightHeap.size();
            return (median * lcCount - leftSum) + (rightSum - median * rcCount);
        };

        windowCost[0] = getCost();

        // Slide the window across the array
        for (int i = x; i < n; ++i) {
            remove(nums[i - x]);
            add(nums[i]);
            windowCost[i - x + 1] = getCost();
        }

        // Step 2: Corrected DP for k non-overlapping windows
        // dp[j][i] = min cost using j windows within the first i elements
        const long long INF = 1e18;
        vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));

        // Base case: 0 windows cost 0
        for (int i = 0; i <= n; ++i) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; ++j) {
            for (int i = 1; i <= n; ++i) {
                // Option A: Don't end a window at index i-1
                dp[j][i] = dp[j][i - 1];

                // Option B: End a window of size x ending at index i-1
                // This window spans from index i-x to i-1 (0-based)
                if (i >= x) {
                    dp[j][i] = min(dp[j][i], dp[j - 1][i - x] + windowCost[i - x]);
                }
            }
        }

        return dp[k][n];
    }
};