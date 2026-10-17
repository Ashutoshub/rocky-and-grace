class Solution {
private:
    // Helper function to calculate the sum of digits
    int getDigitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Store elements with their original indices
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {nums[i], i};
        }
        
        // Step 2: Sort the array based on the problem's custom rules
        sort(arr.begin(), arr.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
            int sumA = getDigitSum(a.first);
            int sumB = getDigitSum(b.first);
            
            if (sumA != sumB) {
                return sumA < sumB; // Primary: sort by digit sum
            }
            return a.first < b.first; // Tie-breaker: sort by actual value
        });
        
        // Step 3: Cycle detection to calculate minimum swaps
        vector<bool> visited(n, false);
        int totalSwaps = 0;
        
        for (int i = 0; i < n; ++i) {
            // Skip if already resolved in a previous cycle or already in the correct place
            if (visited[i] || arr[i].second == i) {
                continue;
            }
            
            // Trace the cycle
            int cycleSize = 0;
            int j = i;
            
            while (!visited[j]) {
                visited[j] = true;
                // Move to the index where the current element originally belonged
                j = arr[j].second; 
                cycleSize++;
            }
            
            // Add (L - 1) to the total swaps
            if (cycleSize > 1) {
                totalSwaps += (cycleSize - 1);
            }
        }
        
        return totalSwaps;
    }
};