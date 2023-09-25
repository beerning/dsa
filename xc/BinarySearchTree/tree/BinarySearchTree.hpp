//
//  BinarySearchTree.hpp
//  ds
//
//  Created by berning on 2015/4/29.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "BinaryTree.hpp"

template<class T>
class BinarySearchTree : public BinaryTree<T>{
    int (*_comparator)(T, T);
    int compare(T v1, T v2) const;
    Node<T> * node(T v) const;
    void elementNotNullCheck(T v) const;
//    string description(Node<T> *node)const override{ return "bst_" + to_string(node->_element);}
protected:
    virtual Node<T> *newNode(T v, Node<T> *parent){return new Node<T>(v, parent);};
    virtual void afterAdd(Node<T> *node){}
    virtual void afterRemove(Node<T> *node){}

public:
    BinarySearchTree(): BinarySearchTree(NULL){}
    BinarySearchTree(int (*comparator)(T, T)) : _comparator(comparator){}

    void add(T v);
    void remove(T v);
    bool contains(T v) const;
    void clear();
};

#pragma mark - public
template<class T>
void BinarySearchTree<T>::add(T v){
    elementNotNullCheck(v);
    if (!this->_root) {
        this->_root = newNode(v, NULL);
        this->_size++;
        afterAdd(this->_root);
        return;
    }
    
    Node<T> *n = this->_root;
    Node<T> *parent = this->_root;
    int cmp = 0;
    while (n) {
        cmp = compare(v, n->_element);
        parent = n;
        if (cmp < 0) {
            n = n->_left;
        }else if (cmp > 0){
            n = n->_right;
        }else{
            n->_element = v;
            return;
        }
    }
    
    Node<T> *node = newNode(v, parent);
    if (cmp < 0) {
        parent->_left = node;
    }else{
        parent->_right = node;
    }
    this->_size++;
    
    afterAdd(node);
}

template<class T>
void BinarySearchTree<T>::remove(T v){
    Node<T> *n = node(v);
    if(!n) return;
    
    if (n->hasTwins()) {//度为2的节点
        Node<T> *suc = this->successor(n);
        n->_element = suc->_element;
        n = suc;
    }//度为2的后继节点的度必为0 或 1
    
    //degreen 1 or 0
    Node<T> *leaf = n->_left ? n->_left : n->_right;
    if (leaf) {//degreen == 1
        leaf->_parent = n->_parent;
        
        if (!n->_parent) { //root
            this->_root = leaf;
        }else if(n == n->_parent->_left){
            n->_parent->_left = leaf;
        }else{  //_right
            n->_parent->_right = leaf;
        }
        afterRemove(leaf);
    }else{//degreen == 0
        if (!n->_parent){ //only root
            this->_root = NULL;
        }else if (n == n->_parent->_left) {//left
            n->_parent->_left = NULL;
        }else{//right
            n->_parent->_right = NULL;
        }
        afterRemove(n);
    }
    this->_size--;
    delete n;
}

template<class T>
bool BinarySearchTree<T>::contains(T v) const{
    return node(v) != NULL;
}

template<class T>
void BinarySearchTree<T>::clear() {
    while (this->_size) {
        Node<T> *root = this->_root;
        remove(root->_element);
    }
}

#pragma mark - private

template<class T>
void BinarySearchTree<T>::elementNotNullCheck(T v) const{
    try {
        if (!v) throw "Element can't be null.";
    } catch (const char* e) {
        cout << e << endl;
    }
}

template<class T>
int BinarySearchTree<T>::compare(T v1, T v2) const{
    if (_comparator) return _comparator(v1, v2);
    return int(v1 - v2);
}

template<class T>
Node<T> * BinarySearchTree<T>::node(T v) const{
    Node<T> *n = this->_root;
    int cmp = 0;
    while (n) {
        cmp = compare(v, n->_element);
        if (cmp < 0) n = n->_left;
        else if(cmp > 0) n = n->_right;
        else return n;
    }
    return NULL;
}

#pragma mark - template specialization for string
template<>
class BinarySearchTree<string> : public BinaryTree<string>{
    int (*_comparator)(string, string);
    int compare(string v1, string v2) const;
    Node<string> * node(string v) const;
    
    void trim(string &s) const{
        size_t idx = 0;
        while( (idx = s.find(' ', idx)) != string::npos){
            s.erase(idx,1);
        }
    }
    void elementNotNullCheck(string v) const;
//    string description(Node<string> *node)const override{ return "bst_" + node->_element;}
protected:
    virtual Node<string> *newNode(string v, Node<string> *parent){return new Node<string>(v, parent);};
    virtual void afterAdd(Node<string> *node){}
    virtual void afterRemove(Node<string> *node){}

public:
    BinarySearchTree(): BinarySearchTree(NULL){}
    BinarySearchTree(int (*comparator)(string, string)) : _comparator(comparator){}

    void add(string v);
    void remove(string v);
    bool contains(string v) const;
    void clear();
};

#pragma mark - public
void BinarySearchTree<string>::add(string v){
    elementNotNullCheck(v);
    if (!this->_root) {
        this->_root = newNode(v, NULL);
        this->_size++;
        afterAdd(this->_root);
        return;
    }
    
    Node<string> *n = this->_root;
    Node<string> *parent = this->_root;
    int cmp = 0;
    while (n) {
        cmp = compare(v, n->_element);
        parent = n;
        if (cmp < 0) {
            n = n->_left;
        }else if (cmp > 0){
            n = n->_right;
        }else{
            n->_element = v;
            return;
        }
    }
    
    Node<string> *node = newNode(v, parent);
    if (cmp < 0) {
        parent->_left = node;
    }else{
        parent->_right = node;
    }
    this->_size++;
    
    afterAdd(node);
}

void BinarySearchTree<string>::remove(string v){
    Node<string> *n = node(v);
    if(!n) return;
    
    if (n->hasTwins()) {//度为2的节点
        Node<string> *suc = this->successor(n);
        n->_element = suc->_element;
        n = suc;
    }//度为2的后继节点的度必为0 或 1
    
    //degreen 1 or 0
    Node<string> *leaf = n->_left ? n->_left : n->_right;
    if (leaf) {//degreen == 1
        leaf->_parent = n->_parent;
        
        if (!n->_parent) { //root
            this->_root = leaf;
        }else if(n == n->_parent->_left){
            n->_parent->_left = leaf;
        }else{  //_right
            n->_parent->_right = leaf;
        }
        afterRemove(leaf);
    }else{//degreen == 0
        if (!n->_parent){ //only root
            this->_root = NULL;
        }else if (n == n->_parent->_left) {//left
            n->_parent->_left = NULL;
        }else{//right
            n->_parent->_right = NULL;
        }
        afterRemove(n);
    }
    this->_size--;
    delete n;
}

bool BinarySearchTree<string>::contains(string v) const{
    return node(v) != NULL;
}

void BinarySearchTree<string>::clear() {
    while (this->_size) {
        Node<string> *root = this->_root;
        remove(root->_element);
    }
}

#pragma mark - private
void BinarySearchTree<string>::elementNotNullCheck(string v) const{
    try {
        trim(v);
        if (v.length() == 0) {
            throw "warning: Element is an empty string.";
        }
    } catch (const char *e) {
        cout << e << endl;
    }
}

int BinarySearchTree<string>::compare(string v1, string v2) const{
    if (_comparator) return _comparator(v1, v2);
    return v1.compare(v2);
}

Node<string> * BinarySearchTree<string>::node(string v) const{
    Node<string> *n = this->_root;
    int cmp = 0;
    while (n) {
        cmp = compare(v, n->_element);
        if (cmp < 0) n = n->_left;
        else if(cmp > 0) n = n->_right;
        else return n;
    }
    return NULL;
}


#pragma mark - template specialization for const char *
template<>
class BinarySearchTree<const char *> : public BinaryTree<const char *>{
    int (*_comparator)(const char *, const char *);
    int compare(const char * v1, const char * v2) const;
    Node<const char *> * node(const char * v) const;
    
    void trim(string &s) const{
        size_t idx = 0;
        while( (idx = s.find(' ', idx)) != string::npos){
            s.erase(idx,1);
        }
    }
    void elementNotNullCheck(const char * v) const;
//    string description(Node<const char *> *node)const override{
//        string s = node->_element;
//        return "bst_" + s;
//    }
protected:
    virtual Node<const char *> *newNode(const char * v, Node<const char *> *parent){return new Node<const char *>(v, parent);};
    virtual void afterAdd(Node<const char *> *node){}
    virtual void afterRemove(Node<const char *> *node){}

public:
    BinarySearchTree(): BinarySearchTree(NULL){}
    BinarySearchTree(int (*comparator)(const char *, const char *)) : _comparator(comparator){}

    void add(const char * v);
    void remove(const char * v);
    bool contains(const char * v) const;
    void clear();
};

#pragma mark - public
void BinarySearchTree<const char *>::add(const char * v){
    elementNotNullCheck(v);
    if (!this->_root) {
        this->_root = newNode(v, NULL);
        this->_size++;
        afterAdd(this->_root);
        return;
    }
    
    Node<const char *> *n = this->_root;
    Node<const char *> *parent = this->_root;
    int cmp = 0;
    while (n) {
        cmp = compare(v, n->_element);
        parent = n;
        if (cmp < 0) {
            n = n->_left;
        }else if (cmp > 0){
            n = n->_right;
        }else{
            n->_element = v;
            return;
        }
    }
    
    Node<const char *> *node = newNode(v, parent);
    if (cmp < 0) {
        parent->_left = node;
    }else{
        parent->_right = node;
    }
    this->_size++;
    
    afterAdd(node);
}

void BinarySearchTree<const char *>::remove(const char * v){
    Node<const char *> *n = node(v);
    if(!n) return;
    
    if (n->hasTwins()) {//度为2的节点
        Node<const char *> *suc = this->successor(n);
        n->_element = suc->_element;
        n = suc;
    }//度为2的后继节点的度必为0 或 1
    
    //degreen 1 or 0
    Node<const char *> *leaf = n->_left ? n->_left : n->_right;
    if (leaf) {//degreen == 1
        leaf->_parent = n->_parent;
        
        if (!n->_parent) { //root
            this->_root = leaf;
        }else if(n == n->_parent->_left){
            n->_parent->_left = leaf;
        }else{  //_right
            n->_parent->_right = leaf;
        }
        afterRemove(leaf);
    }else{//degreen == 0
        if (!n->_parent){ //only root
            this->_root = NULL;
        }else if (n == n->_parent->_left) {//left
            n->_parent->_left = NULL;
        }else{//right
            n->_parent->_right = NULL;
        }
        afterRemove(n);
    }
    this->_size--;
    delete n;
}

bool BinarySearchTree<const char *>::contains(const char * v) const{
    return node(v) != NULL;
}

void BinarySearchTree<const char *>::clear() {
    while (this->_size) {
        Node<const char *> *root = this->_root;
        remove(root->_element);
    }
}

#pragma mark - private

void BinarySearchTree<const char *>::elementNotNullCheck(const char * v) const{
    try {
        string s = v;
        trim(s);
        if (s.length() == 0) {
            throw "warning: Element is an empty char array.";
        }
    } catch (const char *e) {
        cout << e << endl;
    }
}

int BinarySearchTree<const char *>::compare(const char * v1, const char * v2) const{
    if (_comparator) return _comparator(v1, v2);
    return strcmp(v1, v2);
}

Node<const char *> * BinarySearchTree<const char *>::node(const char * v) const{
    Node<const char *> *n = this->_root;
    int cmp = 0;
    while (n) {
        cmp = compare(v, n->_element);
        if (cmp < 0) n = n->_left;
        else if(cmp > 0) n = n->_right;
        else return n;
    }
    return NULL;
}

#endif /* BinarySearchTree_hpp */
