//
//  BTree.hpp
//  B-Tree
//
//  Created by berning on 2015/5/13.
//

#ifndef BTree_hpp
#define BTree_hpp

#include <iostream>
#include <queue>
#include <cmath>
#include <string>
using namespace std;

template<class T>
class Record{
public:
    int _key;
    T _value;
    Record(int key, T value) : _key(key), _value(value){}
};

template<class T>
class BTNode{
public:
    BTNode *_parent;
    Record<T> **_records;
    int _count;
    BTNode **_children;
    int _childs;
    BTNode(Record<T> *record, BTNode *parent, int order);
    void addRecord(Record<T> *record);
    void setRecord(Record<T> *record, int idx);
    void addChild(BTNode *child, int idx);
    void setChild(BTNode *chiid, int idx);
};

template<class T>
BTNode<T>::BTNode(Record<T> *record, BTNode *parent, int order){
    _records = new Record<T>*[order] {record};
    _children = new BTNode<T>*[order + 1] {};
    _parent = parent;
    _count = record ? 1 : 0;
    _childs = 0;
}

template<class T>
void BTNode<T>::addRecord(Record<T> *record){
    if (!record) return;
    Record<T> *rd = NULL;
    int key = record->_key;
    for (int i = _count; i > key; i--){
        rd = _records[i - 1];
        rd->_key = i;
        _records[i] = rd;
    }
    _records[key] = record;
    _count++;
}

template<class T>
void BTNode<T>::setRecord(Record<T> *record, int idx){
    if (!record){ //delete
        if (_count == 0) return;
        Record<T> *rd = NULL;
        int end = _count - 1;
        for (int i = idx; i < end; i++){
            rd = _records[i + 1];
            rd->_key = i;
            _records[i] = rd;
        }
        _records[end] = record;
        if (_count > 0) _count--;
    }else{  //replace
        _records[idx] = record;
    }
}

template<class T>
void BTNode<T>::addChild(BTNode *child, int idx){
    if (!child) return;
    for (int i = _childs; i > idx; i--){
        _children[i] = _children[i - 1];
    }
    _children[idx] = child;
    _childs++;
}

template<class T>
void BTNode<T>::setChild(BTNode *child, int idx){
    if (!child){    //delete
        if (_childs == 0) return;
        int end = _childs - 1;
        for (int i = idx; i < end; i++){
            _children[i] = _children[i + 1];
        }
        _children[end] = child;
        if (_childs > 0) _childs--;
    }else{  //replace
        _children[idx] = child;
    }
}

template<class T>
class Result{
public:
    using BNode = BTNode<T> *;
    int _key;
    BNode _node;
    bool _exists;
    Result(BNode node, int key) : Result(node, key, true){}
    Result(BNode node, int key, bool exists) : _key(key), _node(node), _exists(exists){}
};

#pragma mark - BTree
template<class T> class BTree;
template<class T> ostream & operator<<(ostream &os, const BTree<T> &t);

template<class T>
class BTree{
    using BNode = BTNode<T> *;
    int _order;
    const int LEAST_COUNT_OF_ROOT = 1;
    const int LEAST_COUNT_OF_INTERNAL;

    BNode _root;
    Result<T> *node(T v)const;
    Result<T> *bSearch(BNode n, T v) const;

    Record<T> *split(BNode n, BNode right) const;
    void overflow(BNode node);
    
    void underflow(BNode node, T v);
    Result<T> *successor(BNode node, int key) const;
    void siblings(BNode &lsb, BNode &rsb, int key, BNode parent) const;
    void borrowFromLeft(BNode n, int key, BNode parent, BNode lsb);
    void borrowFromRight(BNode n, int key, BNode parent, BNode rsb);
    T merge(BNode ln, int key, BNode parent, BNode rn);
public:
    BTree(int order) : _root(NULL), LEAST_COUNT_OF_INTERNAL(ceil(order * 0.5) - 1) {
        try {
            if (order < 3) throw "The parameter 'order' should be greater than or equal 3.";
        }
        catch (const char *e) {
            cout << e << endl;
            return;
        }
        _order = order;
    }
    void add(T v);
    void remove(T v);
    bool contains(T v)const;
    
    int height() const;
    
    friend ostream & operator<< <>(ostream &os, const BTree<T> &t);
};

#pragma mark - Public
template<class T>
void BTree<T>::add(T v){
    if (!_root){
        _root = new BTNode<T>(new Record<T>(0, v), NULL, _order);
        return;
    }
    //look up the leaf to add
    Result<T> *rs = node(v);
    if (rs->_exists) return;
    BNode n = rs->_node;
    //add
    n->addRecord(new Record<T>(rs->_key, v));

    //overflow
    if (n->_count < _order) return;
    overflow(n);
}

template<class T>
void BTree<T>::remove(T v){
    Result<T> *rs = node(v);
    if (rs->_exists == false) return;

    BNode n = rs->_node;
    Record<T> *rd = n->_records[rs->_key];
    
    //non-leaf
    if (n->_childs > 0){
        Result<T> *sr = successor(n, rs->_key);
        BNode sn = sr->_node;
        //replace
        Record<T> *sd = sn->_records[sr->_key];
        sd->_key = rs->_key;
        n->setRecord(sd, rs->_key);
        //point to leaf
        v = sd->_value;
        rs = sr;
        n = sn;
    }
    //leaf
    n->setRecord(NULL, rs->_key);
    delete rd;
    if (n == _root){
        if (n->_count >= LEAST_COUNT_OF_ROOT) return;
        delete _root;
        _root = NULL;
    }else{
        if (n->_count >= LEAST_COUNT_OF_INTERNAL) return;
        underflow(n, v); //underflow
    }
}

template<class T>
bool BTree<T>::contains(T v)const{
    return node(v)->_exists;
}

template<class T>
int BTree<T>::height() const{
    BNode n = _root;
    if (!n) return 0;
    int height = 1;
    while (n->_childs != 0){
        height++;
        n = n->_children[0];
    }
    return height;
}

#pragma mark - Private
#pragma mark Search
template<class T>
Result<T> *BTree<T>::node(T v)const{
    BNode n = _root;
    Result<T> *rs = NULL;
    while (n && n->_childs != 0){
        rs = bSearch(n, v);
        if (rs->_exists) return rs;
        //next loop
        n = n->_children[rs->_key];
    }
    return bSearch(n, v);
}

template<class T>
Result<T> *BTree<T>::bSearch(BNode n, T v) const{
    if (!n) return new Result<T>(n, -1, false);
    
    int high = n->_count - 1;
    int low = 0;
    int mid = 0;
    Record<T> *rd = NULL;
    while (high - low >= 0) {
        mid = low + ((high - low) >> 1);
        rd = n->_records[mid];
        if (v > rd->_value) low = mid + 1;
        else if (v < rd->_value) high = mid - 1;
        else return new Result<T>(n, rd->_key, true);
    }
    rd = n->_records[low];
    int key = rd ? rd->_key : n->_count;
    return new Result<T>(n, key, false);
}

#pragma mark Add
template<class T>
Record<T> *BTree<T>::split(BNode n, BNode right) const{
    int count = n->_count;
    int mid = count >> 1;
    Record<T> *mrd = n->_records[mid];
    
    int idx = 0;
    Record<T> *rd = NULL;
    BNode child = NULL;
    for (int i = mid; i < count; i++){
        if (i > mid){
            idx = i - mid - 1;
            //right
            rd = n->_records[mid];
            rd->_key = idx;
            right->addRecord(rd);

            child = n->_children[mid + 1];
            right->addChild(child, idx);
            if (child) child->_parent = right;
            if (i + 1 == count) {
                child = n->_children[mid + 2];
                idx = i - mid;
                right->addChild(child, idx);
                if (child) child->_parent = right;
            }
            //left
            n->setChild(NULL, mid + 1);
            if (i + 1 == count) n->setChild(NULL, mid + 2);
        }
        //left
        n->setRecord(NULL, mid);
    }
    return mrd;
}

template<class T>
void BTree<T>::overflow(BNode n){
    BNode right = new BTNode<T>(NULL, NULL, _order);
    Record<T> *rd = split(n, right);
    if (n == _root){
        rd->_key = 0;
        _root = new BTNode<T>(rd, NULL, _order);
    
        _root->addChild(n, 0);
        _root->addChild(right, 1);

        n->_parent = _root;
        right->_parent = _root;
        
        return;
    }
    BNode parent = n->_parent;
    Result<T> *rs = bSearch(parent, rd->_value);
    int key = rs->_key;
    
    rd->_key = key;
    parent->addRecord(rd);
    parent->addChild(right, key + 1);
    right->_parent = parent;

    if (parent->_count < _order) return;
    overflow(parent);
}

#pragma mark Remove
template<class T>
Result<T> *BTree<T>::successor(BNode node, int key) const{
    BNode  n = node->_children[key + 1];
    Result<T> *rs = NULL;
    if (n){
        while (n->_children[0])
            n = n->_children[0];
        rs = new Result<T>(n, 0);
    }else if(!n && node->_parent){
        n = node;
        if (key == n->_count - 1){
            while (n->_parent && n == n->_parent->_children[n->_parent->_count])
                n = n->_parent;
            n = n->_parent; //the max record  n == NULL
            rs = bSearch(n, node->_records[key]->_value);
        }else{
            rs = new Result<T>(n, key + 1);
        }
    }
    return rs;
}

template<class T>
void  BTree<T>::siblings(BNode &lsb, BNode &rsb, int key, BNode parent) const{
    int end = parent->_childs - 1;
    if (key == 0){
        rsb = parent->_children[key + 1];
    }else if (key == end){
        lsb = parent->_children[key - 1];
    }else{
        lsb = parent->_children[key - 1];
        rsb = parent->_children[key + 1];
    }
}

template<class T>
void BTree<T>::borrowFromLeft(BNode n, int key, BNode parent, BNode lsb){
    //n
    Record<T> *prd = parent->_records[key];
    prd->_key = 0;
    n->addRecord(prd);

    int ck = lsb->_childs > 0 ? lsb->_childs - 1 : 0;
    BNode child = lsb->_children[ck];
    n->addChild(child, 0);
    if (child) child->_parent = n;
    //parent
    int rk = lsb->_count - 1;
    Record<T> *lrd = lsb->_records[rk];
    lrd->_key = key;
    parent->setRecord(lrd, key);
    //sibing
    lsb->setRecord(NULL, rk);

    lsb->setChild(NULL, ck);
}

template<class T>
void BTree<T>::borrowFromRight(BNode n, int key, BNode parent, BNode rsb){
    //n
    Record<T> *prd = parent->_records[key];
    prd->_key = n->_count;
    n->addRecord(prd);

    int ck = 0;
    BNode child = rsb->_children[ck];
    n->addChild(child, n->_childs);
    if (child) child->_parent = n;
    //parent
    int rk = 0;
    Record<T> *rrd = rsb->_records[rk];
    rrd->_key = key;
    parent->setRecord(rrd, key);
    //sibling
    rsb->setRecord(NULL, rk);

    rsb->setChild(NULL, ck);
}

template<class T>
T BTree<T>::merge(BNode ln, int key, BNode parent, BNode rn){
    //merge
    Record<T> *prd = parent->_records[key];
    prd->_key = ln->_count;
    ln->addRecord(prd);
    Record<T> *rrd = NULL;
    for (int i = 0; i < rn->_count; i++){
        rrd = rn->_records[i];
        rrd->_key = ln->_count;
        ln->addRecord(rrd);
    }
    BNode child = NULL;
    for (int i = 0; i < rn->_childs; i++){
        child = rn->_children[i];
        ln->addChild(child, ln->_childs);
        if (child) child->_parent = ln;
    }
    //parent
    parent->setRecord(NULL, key);
    parent->setChild(NULL, key + 1);
    
    return prd->_value;
}

template<class T>
void BTree<T>::underflow(BNode n, T v){
    BNode parent = n->_parent;
    Result<T> *rs = bSearch(parent, v);
    int key = rs->_exists ? rs->_key + 1 : rs->_key;

    BNode lsb = NULL;
    BNode rsb = NULL;
    siblings(lsb, rsb, key, parent);

    if (lsb && lsb->_count > LEAST_COUNT_OF_INTERNAL){ //LL
        borrowFromLeft(n, key - 1, parent, lsb);
    }else if (rsb && rsb->_count > LEAST_COUNT_OF_INTERNAL){ //RR
        borrowFromRight(n, key, parent, rsb);
    }else { //merge
        BNode ln = NULL;
        BNode rn = NULL;
        //merge
        if(lsb){
            ln = lsb;
            rn = n;
            v = merge(ln, key - 1, parent, rn);
        }else{
            ln = n;
            rn = rsb;
            v = merge(ln, key, parent, rn);
        }
        delete rn;
        //underflow parent
        if (parent == _root){
            if (parent->_count >= LEAST_COUNT_OF_ROOT) return;
            delete _root;
            _root = ln;
            ln->_parent = NULL;
        }else{
            if (parent->_count >= LEAST_COUNT_OF_INTERNAL) return;
            underflow(parent, v);
        }
    }
}

#pragma mark - ostream
template<class T>
ostream & operator<<(ostream &os, const BTree<T> &t){
    queue<BTNode<T> *> queue;
    queue.push(t._root);
    while (!queue.empty()) {
        BTNode<T> *n = queue.front();
        queue.pop();
        
        //print like :  [a,b,c,d]_P(f)
        int count = n->_count;
        for (int i = 0; i < count; i++){
            if (i == 0) os << "[";
            if (i > 0) os << ",";
            
            os << n->_records[i]->_value;
            
            if (i + 1 == count) {
                BTNode<T> *p = n->_parent;
                string s;
                if (p) s = to_string(p->_records[0]->_value);
                else s = "NULL";
                os << "]_P(" << s << ")" << "\t";
            }
        }
        //CR/LF by the end of every level
        BTNode<T> *child = n;
        BTNode<T> *parent = child->_parent;
        if (!parent) os << endl << endl;
        while (parent){
            int last = parent->_childs - 1;
            if (child == parent->_children[last]){
                child = parent;
                parent = parent->_parent;
                if (!parent) os << endl << endl;
            }else{
                break;
            }
        }
        //enqueue
        if (n->_childs) {
            for (int i = 0; i < n->_childs; i++){
                queue.push(n->_children[i]);
            }
        }
    }
    return os;
}

#endif /* BTree_hpp */
