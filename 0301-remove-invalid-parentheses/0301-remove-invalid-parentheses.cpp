#include <vector>
#include <string>
#include <unordered_set>

class Solution {
public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        int left_rem = 0, right_rem = 0;
        
        // 1. Calculate how many left and right parentheses are misplaced
        for (char c : s) {
            if (c == '(') {
                left_rem++;
            } else if (c == ')') {
                if (left_rem > 0) left_rem--;
                else right_rem++;
            }
        }
        
        std::unordered_set<std::string> valid_results;
        std::string current = "";
        
        // 2. Backtrack to find all combinations
        backtrack(s, 0, left_rem, right_rem, 0, current, valid_results);
        
        return std::vector<std::string>(valid_results.begin(), valid_results.end());
    }

private:
    void backtrack(const std::string& s, int index, int left_rem, int right_rem, int balance, std::string& current, std::unordered_set<std::string>& valid_results) {
        if (index == s.length()) {
            if (left_rem == 0 && right_rem == 0 && balance == 0) {
                valid_results.insert(current);
            }
            return;
        }
        
        char c = s[index];
        
        // Option 1: Remove the current character (if we are allowed to)
        if (c == '(' && left_rem > 0) {
            backtrack(s, index + 1, left_rem - 1, right_rem, balance, current, valid_results);
        } else if (c == ')' && right_rem > 0) {
            backtrack(s, index + 1, left_rem, right_rem - 1, balance, current, valid_results);
        }
        
        // Option 2: Keep the current character
        current.push_back(c);
        
        if (c == '(') {
            backtrack(s, index + 1, left_rem, right_rem, balance + 1, current, valid_results);
        } else if (c == ')') {
            // We can only keep a ')' if there is an unmatched '(' before it
            if (balance > 0) {
                backtrack(s, index + 1, left_rem, right_rem, balance - 1, current, valid_results);
            }
        } else {
            // Keep letters blindly
            backtrack(s, index + 1, left_rem, right_rem, balance, current, valid_results);
        }
        
        // Backtrack step: revert the string state
        current.pop_back();
    }
};