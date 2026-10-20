#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();
        
        // s is the target non-decreasing sorted array
        std::vector<int> s = nums;
        std::sort(s.begin(), s.end());

        // Helper function to check if a divisor k is sortable
        auto isSortable = [&](int k) -> bool {
            for (int b = 0; b < n; b += k) {
                // Analyze cyclic rotation property of subarray nums[b ... b+k-1]
                int drops = 0;
                int drop_idx = -1;
                
                for (int i = 0; i < k; ++i) {
                    int curr = nums[b + i];
                    int next = nums[b + (i + 1) % k];
                    if (curr > next) {
                        drops++;
                        drop_idx = i;
                    }
                }

                // A cyclically sorted array can have at most 1 drop
                if (drops > 1) {
                    return false;
                }

                // If drops == 0, offset is 0. If drops == 1, start offset is (drop_idx + 1) % k
                int offset = (drops == 1) ? (drop_idx + 1) % k : 0;

                // Validate element-by-element match with s[b ... b+k-1]
                for (int i = 0; i < k; ++i) {
                    if (nums[b + (offset + i) % k] != s[b + i]) {
                        return false;
                    }
                }
            }
            return true;
        };

        // Find all divisors of n
        std::vector<int> divisors;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                divisors.push_back(i);
                if (i * i != n) {
                    divisors.push_back(n / i);
                }
            }
        }

        long long total_sum = 0;
        for (int k : divisors) {
            if (isSortable(k)) {
                total_sum += k;
            }
        }

        return static_cast<int>(total_sum);
    }
};