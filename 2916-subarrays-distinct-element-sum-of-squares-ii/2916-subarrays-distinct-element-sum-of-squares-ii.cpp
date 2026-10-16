class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        long long MOD = 1e9 + 7;
        
        // Segment tree arrays (4 * n is a safe size)
        vector<long long> sum_sq(4 * n, 0);
        vector<long long> sum(4 * n, 0);
        vector<long long> lazy(4 * n, 0);
        
        // Lambda to apply a lazy update (+val) to a node
        auto apply = [&](int node, int l, int r, long long val) {
            long long len = r - l + 1;
            // Math: (C + val)^2 = C^2 + 2 * val * C + val^2
            sum_sq[node] = (sum_sq[node] + 2 * val * sum[node] % MOD + val * val % MOD * len % MOD) % MOD;
            sum[node] = (sum[node] + val * len % MOD) % MOD;
            lazy[node] = (lazy[node] + val) % MOD;
        };
        
        // Lambda to push pending updates to children
        auto push = [&](int node, int l, int r) {
            if (lazy[node] != 0) {
                int mid = l + (r - l) / 2;
                apply(2 * node + 1, l, mid, lazy[node]);
                apply(2 * node + 2, mid + 1, r, lazy[node]);
                lazy[node] = 0; // clear the pending update
            }
        };
        
        // Recursive segment tree range update
        function<void(int, int, int, int, int, long long)> update = [&](int node, int l, int r, int ql, int qr, long long val) {
            if (ql > r || qr < l) return; // Out of bounds
            if (ql <= l && r <= qr) {     // Completely inside
                apply(node, l, r, val);
                return;
            }
            push(node, l, r);
            int mid = l + (r - l) / 2;
            update(2 * node + 1, l, mid, ql, qr, val);
            update(2 * node + 2, mid + 1, r, ql, qr, val);
            
            // Recalculate parent based on updated children
            sum_sq[node] = (sum_sq[2 * node + 1] + sum_sq[2 * node + 2]) % MOD;
            sum[node] = (sum[2 * node + 1] + sum[2 * node + 2]) % MOD;
        };
        
        unordered_map<int, int> last_pos;
        long long total_ans = 0;
        
        // Process each element iteratively
        for (int i = 0; i < n; i++) {
            // Find the boundary of where this element is "new"
            int start = last_pos.count(nums[i]) ? last_pos[nums[i]] + 1 : 0;
            int end = i;
            
            // Add 1 to the distinct counts of subarrays starting from `start` to `end`
            update(0, 0, n - 1, start, end, 1);
            
            // sum_sq[0] holds the sum of squares for all subarrays ending at current i
            total_ans = (total_ans + sum_sq[0]) % MOD;
            
            // Update the last seen position of the current element
            last_pos[nums[i]] = i;
        }
        
        return total_ans;
    }
};