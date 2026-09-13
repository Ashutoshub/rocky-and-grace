class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        vector<pair<int, int>> ones1, ones2;
        int n = img1.size();
        for(int r = 0;r < n; ++r){
            for(int c = 0; c < n; ++c){
                if(img1[r][c] == 1) ones1.push_back({r, c});
                if(img2[r][c] == 1) ones2.push_back({r, c});
            }
        }
        unordered_map<int, int> vectorcnt;
        int maxoverlap = 0;
        for(auto& p1 : ones1){
            for(auto& p2: ones2){
                int dr = p2.first - p1.first;
                int dc = p2.second - p1.second;
                int key = (dr + 30)* 100 + (dc + 30);
                vectorcnt[key]++;
                maxoverlap = max(vectorcnt[key], maxoverlap);
            }
        }
        return maxoverlap;
    }
};