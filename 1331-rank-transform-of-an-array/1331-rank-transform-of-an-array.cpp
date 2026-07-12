class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sortedarr = arr;
        sort(sortedarr.begin(), sortedarr.end());
        unordered_map<int, int> rankmap;
        int currrank = 1;
        for(int num : sortedarr){
            if(rankmap.find(num) == rankmap.end()){
                rankmap[num] = currrank;
                currrank++;
            }
        }
        vector<int> result(arr.size());
        for(int i = 0; i < arr.size(); ++i){
            result[i] = rankmap[arr[i]];
        }
        return result;
    }
};