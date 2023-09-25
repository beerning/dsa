//
//  leetcode_340.h
//  algorithm
//
//  Created by berning on 2015/9/11.
//

#ifndef leetcode_340_h
#define leetcode_340_h

#include <algorithm>

static bool compare(pair<int, int> n1, pair<int, int> n2){
    return n1.second < n2.second;
}

//347
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> umap;
    auto it = nums.begin();
    while(it != nums.end()){
        umap[*it]++;
        ++it;
    }
    vector<pair<int, int>> v;
    for (auto it = umap.begin(); it != umap.end(); ++it)
        v.emplace_back(*it);
    
    vector<int> vk;
    for (int i = 0; i < k; i++){
        make_heap(v.begin(), v.end(), compare);
        vk.emplace_back(v.front().first);
        v.erase(v.begin());
    }
    return vk;
}

void test340(){
    int a[] = {3, 1, 4, 2, 1, 3, 3, 3, 3, 9, 9, 8, 6, 6};
    
//    int a[] = {1, 2};
    vector<int> v(a, a + sizeof(a) / sizeof(int));
    
    vector<int> topk = topKFrequent(v, 2);
    
    for (auto it = topk.begin(); it != topk.end(); ++it)
        cout << *it << " ";
    cout << endl;
    
}


#endif /* leetcode_340_h */
