class Solution {
    vector<int> tree;
    void build(int node, int strt, int end, const vector<int>& V){
        if(strt == end){
            tree[node] = V[strt];
            return;
        }
        int mid = strt + (end - strt) / 2;
        build(2 * node, strt, mid, V);
        build(2 * node + 1,mid + 1, end, V);
        tree[node] = max(tree[2 * node],tree[2 * node + 1]);
    }
    int query_tree(int node, int strt, int end, int l, int r){
        if(r < strt || end < l) return 0;
        if(l <= strt && end <= r) return tree[node];
        int mid = strt + (end - strt)/ 2;
        return max(query_tree(2 * node, strt, mid, l, r), query_tree(2 * node + 1, mid + 1, end, l, r));
    }
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int totones = 0;
        for(char c : s) if(c == '1') totones++;
        vector<pair<int, int>> blocks;
        int strt = -1;
        for(int i = 0; i < n; ++i){
            if(s[i] == '0'){
                if(strt == -1) strt = i;
            }
            else{
                if(strt != -1){
                    blocks.push_back({strt, i - 1});
                    strt = -1;
                }
            }
        }
        if(strt != -1) blocks.push_back({strt, n - 1});
        int m = blocks.size();
        vector<int> V(max(1, m - 1), 0);
        for(int i = 0; i < m - 1; ++i){
            int len1 = blocks[i].second - blocks[i].first + 1;
            int len2 = blocks[i + 1].second - blocks[i + 1].first + 1;
            V[i] = len1 + len2;
        }    
        if(m - 1 > 0){
            tree.assign(4 * (m-1), 0);
            build(1, 0, m-2, V);
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for(const auto& q : queries){
            int L = q[0], R = q[1];
            int a = -1, b = -1;
            int low = 0, high = m - 1;
            while(low <= high){
                int mid = low + (high - low)/ 2;
                if(blocks[mid].second >= L){
                    a = mid;
                    high = mid - 1;
                }
                else{
                    low = mid + 1;
                }
            }
            low = 0; high = m - 1;
            while(low <= high){
                int mid = low + (high - low)/2;
                if(blocks[mid].first <= R){
                    b = mid;
                    low = mid + 1;
                }
                else{
                    high = mid -1;
                }
            } 
            if(a == -1 || b == -1 || a >= b){
                ans.push_back(totones);
                continue;
            }
            auto getlen = [&](int idx){
                return min(R, blocks[idx].second) - max(L, blocks[idx].first) + 1;
            };
            int gain = 0;
            if(b == a + 1){
                gain = getlen(a) + getlen(b);
            }
            else{
                int lena = getlen(a);
                int lena1 = blocks[a+1].second - blocks[a+1].first +1;
                int lenb1 = blocks[b-1].second - blocks[b-1].first +1;
                int lenb = getlen(b);
                gain = max(lena + lena1, lenb1 + lenb);
                if(b - 2 >= a + 1){
                    gain = max(gain, query_tree(1,0,m-2,a+1,b-2));
                }
            }
            ans.push_back(totones + gain);
        }
        return ans;
    }
};