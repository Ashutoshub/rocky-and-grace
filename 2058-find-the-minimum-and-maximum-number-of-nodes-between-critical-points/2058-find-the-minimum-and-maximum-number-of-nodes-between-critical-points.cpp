/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int firstCritical = -1;
        int lastCritical = -1;
        int minDistance = INT_MAX;
        
        // We need three pointers to compare prev, current, and next
        ListNode* prev = head;
        ListNode* curr = head->next;
        int currentIndex = 1; // Assuming 0-indexed, the second node is index 1
        
        while (curr->next != nullptr) {
            ListNode* nextNode = curr->next;
            
            // Check if it is a local maxima or minima
            if ((curr->val > prev->val && curr->val > nextNode->val) || 
                (curr->val < prev->val && curr->val < nextNode->val)) {
                
                if (firstCritical == -1) {
                    // This is the very first critical point we've seen
                    firstCritical = currentIndex;
                } else {
                    // We've found a previous critical point, so we can calculate a distance
                    minDistance = min(minDistance, currentIndex - lastCritical);
                }
                
                // Update the last critical point to the current index
                lastCritical = currentIndex;
            }
            
            // Move our sliding window of 3 nodes forward
            prev = curr;
            curr = nextNode;
            currentIndex++;
        }
        
        // If we found fewer than 2 critical points
        if (firstCritical == -1 || firstCritical == lastCritical) {
            return {-1, -1};
        }
        
        // Max distance is always the last minus the first
        int maxDistance = lastCritical - firstCritical;
        
        return {minDistance, maxDistance};
    }
};