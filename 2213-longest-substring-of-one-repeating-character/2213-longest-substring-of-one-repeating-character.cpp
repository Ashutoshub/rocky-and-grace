#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to hold the state of each segment tree node
struct Node {
    int max_len;
    int pre_len;
    int suf_len;
    char left_char;
    char right_char;
    int size;
};

class SegmentTree {
    vector<Node> tree;
    string s;
    int n;

    // Helper function to merge two child nodes into a parent node
    void push_up(int node) {
        int left = 2 * node;
        int right = 2 * node + 1;

        // The size and boundary characters are straightforward
        tree[node].size = tree[left].size + tree[right].size;
        tree[node].left_char = tree[left].left_char;
        tree[node].right_char = tree[right].right_char;

        // Calculate prefix length
        tree[node].pre_len = tree[left].pre_len;
        if (tree[left].pre_len == tree[left].size && tree[left].right_char == tree[right].left_char) {
            tree[node].pre_len += tree[right].pre_len;
        }

        // Calculate suffix length
        tree[node].suf_len = tree[right].suf_len;
        if (tree[right].suf_len == tree[right].size && tree[right].left_char == tree[left].right_char) {
            tree[node].suf_len += tree[left].suf_len;
        }

        // Calculate maximum length in the current segment
        tree[node].max_len = max(tree[left].max_len, tree[right].max_len);
        if (tree[left].right_char == tree[right].left_char) {
            tree[node].max_len = max(tree[node].max_len, tree[left].suf_len + tree[right].pre_len);
        }
    }

public:
    SegmentTree(string& str) {
        s = str;
        n = s.length();
        tree.resize(4 * n + 1);
        build(1, 0, n - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start], 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        push_up(node);
    }

    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            tree[node].left_char = c;
            tree[node].right_char = c;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, c);
        } else {
            update(2 * node + 1, mid + 1, end, idx, c);
        }
        push_up(node);
    }

    // The root node always contains the max_len for the entire string
    int getMaxLen() {
        return tree[1].max_len;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        SegmentTree st(s);
        vector<int> ans;
        int k = queryCharacters.size();
        
        for (int i = 0; i < k; ++i) {
            st.update(1, 0, s.length() - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(st.getMaxLen());
        }
        
        return ans;
    }
};