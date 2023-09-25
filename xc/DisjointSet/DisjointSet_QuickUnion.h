//
//  DisjointSet_QuickUnion.h
//  algorithm
//
//  Created by berning on 2015/9/29.
//

#ifndef DisjointSet_QuickUnion_h
#define DisjointSet_QuickUnion_h

#include "DisjointSet.h"

class DisjointSet_QuickUnion : public DisjointSet{
public:
    DisjointSet_QuickUnion(int capacity) : DisjointSet(capacity){}
    int find(int v) override {
        rangecheck(v);
        while (parents[v] != v) {
            v = parents[v];
        }
        return v;
    }
    
    void merge(int v1, int v2) override {
        rangecheck(v1, v2);
        int p1 = find(v1);
        int p2 = find(v2);
        if (p1 == p2) return;
        parents[p1] = p2;
    }
};

class DisjointSet_QuickUnion_Size : public DisjointSet_QuickUnion{
    int *sizes;
public:

    DisjointSet_QuickUnion_Size(int capacity) : DisjointSet_QuickUnion(capacity){
        sizes = new int[capacity];
        for (int i = 0; i < capacity; i++){
            sizes[i] = 1;
        }
    }
    
    ~DisjointSet_QuickUnion_Size() {
        delete[] sizes;
    }
    
    void merge(int v1, int v2) override {
        rangecheck(v1, v2);
        int p1 = find(v1);
        int p2 = find(v2);
        if (p1 == p2) return;
        
        if (sizes[p1] > sizes[p2]) {
            parents[p2] = p1;
            sizes[p1] += sizes[p2];
        }else {
            parents[p1] = p2;
            sizes[p2] += sizes[p1];
        }
    }
};

class DisjointSet_QuickUnion_Rank : public DisjointSet_QuickUnion{
    int *ranks;
public:
    DisjointSet_QuickUnion_Rank(int capacity) : DisjointSet_QuickUnion(capacity){
        ranks = new int[capacity];
        for (int i = 0; i < capacity; i++){
            ranks[i] = 1;
        }
    }
    
    ~DisjointSet_QuickUnion_Rank(){
        delete []ranks;
    }
    
    void merge(int v1, int v2) override {
        rangecheck(v1, v2);
        int p1 = find(v1);
        int p2 = find(v2);
        if (p1 == p2) return;
        
        if (ranks[p1] > ranks[p2]) {
            parents[p2] = p1;
        }else if (ranks[p1] < ranks[p2]){
            parents[p1] = p2;
        }else {
            parents[p1] = p2;
            ranks[p2] += 1;
        }
    }
};


#pragma mark - Optimize
class DisjointSet_QuickUnion_Rank_Compression : public DisjointSet_QuickUnion_Rank{
public:
    DisjointSet_QuickUnion_Rank_Compression(int capacity) : DisjointSet_QuickUnion_Rank(capacity){}
    
    int find(int v) override {
        rangecheck(v);
        if (parents[v] != v) {
            parents[v] = find(parents[v]);
        }
        return parents[v];
    }

};

class DisjointSet_QuickUnion_Rank_Splitting : public DisjointSet_QuickUnion_Rank{
public:
    DisjointSet_QuickUnion_Rank_Splitting(int capacity) : DisjointSet_QuickUnion_Rank(capacity){}
    
    int find(int v) override {
        rangecheck(v);
        int p;
        while (parents[v] != v) {
            p = parents[v];
            parents[v] = parents[p];
            v = p;
        }
        return v;
    }
};

class DisjointSet_QuickUnion_Rank_Halving : public DisjointSet_QuickUnion_Rank{
public:
    DisjointSet_QuickUnion_Rank_Halving(int capacity) : DisjointSet_QuickUnion_Rank(capacity){}
    
    int find(int v) override {
        rangecheck(v);
        while (parents[v] != v) {
            parents[v] = parents[parents[v]];
            v = parents[v];
        }
        return v;
    }
};

#endif /* DisjointSet_QuickUnion_h */
