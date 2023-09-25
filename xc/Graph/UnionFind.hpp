//
//  UnionFind.h
//  algorithm
//
//  Created by berning on 2015/9/30.
//

#ifndef UnionFind_hpp
#define UnionFind_hpp

#include <unordered_map>

template<class T>
class UnionFind{
    class Node{
    public:
        T value;
        Node *parent;
        int rank;
        Node(T v) : value(v), parent(this), rank(1) {}
    };

    unordered_map<T, Node *> map;

    Node *newNode(T v){
        return new Node(v);
    }

    Node *node(T v) const{
        Node *n = map.at(v);
        if (!n) return NULL;

        while(n->parent->value != n->value) {
            n->parent = n->parent->parent;
            n = n->parent;
        }
        return n;
    }

public:
    void set(T v){
        if (map.find(v) != map.end()) return;
        map.emplace(v, newNode(v));
    }
    T find(T v) const {
        Node *n = node(v);
        return !n ? NULL : n->value;
    }
    void merge(T v1, T v2) {
        Node *p1 = node(v1);
        Node *p2 = node(v2);
        if (p1 == NULL || p2 == NULL) return;
        if (p1 == p2) return;

        if (p1->rank > p2->rank) {
            p2->parent = p1;
        }else if ((p1->rank) < p2->rank){ //p1->rank ？？？为什么要加括号
            p1->parent = p2;
        }else {
            p1->parent = p2;
            p2->rank += 1;
        }
    }
    bool isSame(T v1, T v2) const{
        return find(v1) == find(v2);
    }
};

#endif /* UnionFind_h */
