//
//  leetcode_40.h
//  algorithm
//
//  Created by berning on 2015/7/27.
//

#ifndef leetcode_40_h
#define leetcode_40_h

#include<vector>

//42
int trap(vector<int>& height) {
    size_t size = height.size();
    if (size <= 2) return 0;
    
    int left = 0;
    int right = int(size - 1);
    
    int ledge = 0;
    int redge = 0;
    int vol = 0;
    while (left < right){
        ledge = ledge >= height[left] ? ledge : height[left];
        redge = redge >= height[right] ? redge : height[right];
        if (height[left] < height[right]){
            vol += ledge - height[left];
            left++;
        }else{
            vol += redge - height[right];
            right--;
        }
    }
    return vol;
}

//46
void backTrack(vector<vector<int>> &output, vector<int> &list, int k, size_t m){
    if (k > m) return;
    if(k == m){
        output.emplace_back(list);
    }else{
        for(int i = k; i <= m; i++){
            swap(list[k], list[i]);
            backTrack(output, list, k + 1, m);
            swap(list[k], list[i]);
        }
    }
}

vector<vector<int>> _46_perm(vector<int> &list, int first, size_t size){
    vector<vector<int>> output;
    backTrack(output, list, first, size - 1);
    return output;
}



#pragma mark - test
void test40(){
    
//    int height[] = {0,1,0,2,1,0,1,3,2,1,2,1}; ///6
    int height[] = {4,2,0,3,2,5}; //9
    
    vector<int> v42{height, height + sizeof(height) / sizeof(int)};

    //42
    int vol = trap(v42);
    cout << "vol = " << vol << endl;
    
    //46
    int a[] = {1, 2, 3, 4};

    vector<int> v{a, a + 3};
    vector<vector<int>> output = _46_perm(v, 0, v.size());

    cout << "total = " << output.size() << endl;
    int i = 0;
    while (i < output.size()){
        vector<int> res = output[i];
        for (int &x : res)
            cout << x << " ";
        cout << endl;
        i++;
    }
    
    
}



#endif /* leetcode_40_h */
