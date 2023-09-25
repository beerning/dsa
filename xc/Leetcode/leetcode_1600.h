//
//  leetcode_1600.h
//  algorithm
//
//  Created by berning on 2015/9/21.
//

#ifndef leetcode_1600_h
#define leetcode_1600_h

//1622
class Fancy {
    int *array;
    int size;
public:
    Fancy() {
        array = new int[10]{};
        size = 0;
    }
    
    void append(int val) {
        array[size++] = val;
    }
    
    void addAll(int inc) {
        int idx = size - 1;
        while (idx >= 0){
            array[idx--] += inc;
        }
    }
    
    void multAll(int m) {
        int idx = size - 1;
        while (idx >= 0){
            array[idx--] *= m;
        }
    }
    
    int getIndex(int idx) {
        int left = 0;
        int right = size - 1;
        
        while (right > left){

        }
        return 0;
    }
};

#endif /* leetcode_1600_h */
