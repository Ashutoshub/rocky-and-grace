class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, char> rowtoruinedblocks;
        for(const auto& seat: reservedSeats){
            int row = seat[0];
            int col = seat[1];
            if(col >= 2 && col <= 5) rowtoruinedblocks[row] |= 1;
            if(col >= 4 && col <= 7) rowtoruinedblocks[row] |= 2;
            if(col >= 6 && col <= 9) rowtoruinedblocks[row] |= 4;
        }
        int maxfamily = 2 * n;
        for(auto const& [row, mask] : rowtoruinedblocks){
            if((mask & 1) == 0 && (mask & 4) == 0){
                continue;
            }
            else if((mask & 1) == 0 || (mask & 2) == 0 || (mask & 4) == 0){
                maxfamily -= 1;
            }
            else{
                maxfamily -= 2;
            }
        }
        return maxfamily;
    }
};