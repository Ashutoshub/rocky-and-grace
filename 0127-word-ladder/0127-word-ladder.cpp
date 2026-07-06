class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(dict.find(endWord) == dict.end()){
            return 0;
        }
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        if(dict.find(beginWord) != dict.end()){
            dict.erase(beginWord);
        }
        while(!q.empty()){
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();
            if(word == endWord){
                return steps;
            }
            for(int i = 0; i < word.length(); i++){
                char orgchar = word[i];
                for(char c = 'a';c <= 'z'; c++){
                    word[i] = c;
                    if(dict.find(word) != dict.end()){
                        q.push({word,steps + 1});
                        dict.erase(word);
                    }
                }
                word[i] = orgchar;
            }
        }
        return 0;
    }
};