//
//  DisjointSet.h
//  algorithm
//
//  Created by berning on 2015/9/28.
//

#ifndef DisjointSet_h
#define DisjointSet_h

class DisjointSet{
protected:
    int *parents;
    int size;
    void rangecheck(int v){
        if (v < 0 || v >= size)
            throw "the value passed in is out of bounds.";
    }
    
    void rangecheck(int v1, int v2){
        if (v1 < 0 || v1 >= size)
            throw "v1 is out of bounds.";
        if (v2 < 0 || v2 >= size)
            throw "v2 is out of bounds.";
    }

public:
    DisjointSet(int capacity){
        if (capacity < 0)
            throw "capacity can't less than 0.";
        parents = new int[capacity]{};
        size = capacity;
        for (int i = 0; i < size; i++)
            parents[i] = i;
    }
    
    ~DisjointSet(){
        delete[] parents;
    }
    virtual int find(int v) = 0;
    virtual void merge(int v1, int v2) = 0;
    bool isSame(int v1, int v2){
        return find(v1) == find(v2);
    }
};


#endif /* DisjointSet_h */
