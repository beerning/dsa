//
//  leetcode_130.h
//  algorithm
//
//  Created by berning on 2015/7/27.
//

#ifndef leetcode_130_h
#define leetcode_130_h

#include <vector>
#include <unordered_map>
#include <unordered_set>

bool _139_wordBreak(string s, vector<string>& wordDict) {
    size_t n = s.size();
    vector<bool> dp(n + 1, false);
    unordered_set<string> set(wordDict.begin(), wordDict.end());
    dp[0] = true;

    int maxlen = 0;
    for (int i = 0; i < wordDict.size(); i++){
        maxlen = max(maxlen, (int)wordDict[i].size());
    }

    for (int send = 1; send <= n; send++){
        int idx = max(0, send - maxlen);
        while (idx < send){
            if (dp[idx] && set.find(s.substr(idx, send - idx)) != set.end()){
                dp[send] = true;
                break;
            }
            idx++;
        }
    }
    return dp[n];
}


#pragma mark - test
void test130(){
    //139
    string dict[] = {"aaaa", "aaa"};
    vector<string> v{dict, dict + sizeof(dict) / sizeof(dict[0])};
    string s = "aaaaaaa";

    cout << _139_wordBreak(s, v) << endl;;
}

#endif /* leetcode_130_h */
