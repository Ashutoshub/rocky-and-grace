#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    // Custom structure to hold all details, preserving the original index
    struct Interval {
        int start, end;
        long long weight;
        int index;
    };

    // The DP state representing our best choices
    struct State {
        long long score;
        vector<int> indices;
    };

    // Helper function to decide which state wins the tie-breakers
    static State better(const State& a, const State& b) {
        if (a.score > b.score) return a;
        if (b.score > a.score) return b;
        // If scores are equal, C++ vector natively compares lexicographically!
        return a.indices < b.indices ? a : b;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> arr(n);
        
        for (int i = 0; i < n; ++i) {
            arr[i] = {intervals[i][0], intervals[i][1], (long long)intervals[i][2], i};
        }

        // 1. Sort by end times to process chronologically
        sort(arr.begin(), arr.end(), [](const Interval& a, const Interval& b) {
            return a.end < b.end;
        });

        // 2. DP Table: dp[i][c] = best State using prefix of i intervals, picking at most c of them.
        // We use 1-based indexing for 'i' to handle the base case cleanly.
        vector<vector<State>> dp(n + 1, vector<State>(5, {0, {}}));

        for (int i = 1; i <= n; ++i) {
            
            // 3. Binary Search to find the last interval that does not overlap
            int curr_start = arr[i - 1].start;
            int low = 1, high = i - 1;
            int j = 0; // Represents the 1-based index of the compatible interval

            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (arr[mid - 1].end < curr_start) {
                    j = mid;         // This is compatible, try to find a later one
                    low = mid + 1;
                } else {
                    high = mid - 1;  // Overlaps, search left
                }
            }

            // 4. Fill the DP transitions for taking 1 up to 4 intervals
            for (int c = 1; c <= 4; ++c) {
                State skip = dp[i - 1][c];
                
                State take = dp[j][c - 1];
                take.score += arr[i - 1].weight;
                take.indices.push_back(arr[i - 1].index);
                
                // Keep indices sorted so lexicographical comparison evaluates correctly
                sort(take.indices.begin(), take.indices.end());

                // Pick the absolute best out of: skipping, taking, or using fewer intervals
                State best_so_far = better(skip, take);
                dp[i][c] = better(best_so_far, dp[i][c - 1]);
            }
        }

        return dp[n][4].indices;
    }
};