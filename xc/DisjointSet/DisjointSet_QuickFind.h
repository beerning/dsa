//
//  DisjointSet_QuickFind.h
//  algorithm
//
//  Created by berning on 2015/9/29.
//

#ifndef DisjointSet_QuickFind_h
#define DisjointSet_QuickFind_h

#include "DisjointSet.h"

class DisjointSet_QuickFind : public DisjointSet{
public:
    DisjointSet_QuickFind(int capacity) : DisjointSet(capacity){}
    int find(int v) override {
        rangecheck(v);
        return parents[v];
    }
    
    void merge(int v1, int v2) override {
        rangecheck(v1, v2);
        int p1 = find(v1);
        int p2 = find(v2);
        if (p1 == p2) return;
        
        for (int i = 0; i < size; i++){
            if (parents[i] == p1)
                parents[i] = p2;
        }
    }
};


#endif /* DisjointSet_QuickFind_h */
