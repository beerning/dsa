//
//  BinaryTree.hpp
//  Tree
//
//  Created by berning on 2015/4/27.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp
#include <queue>
#include <stack>

template<class T>
class Node{
public:
    T    _element;
    Node *_parent;
    Node *_left;
    Node *_right;
    Node(T element, Node *parent){
        _element = element;
        _parent  = parent;
        _left    = NULL;
        _right   = NULL;
    }
    
    bool isLeaf() const{ return _left == NULL && _right == NULL;}
    bool hasTwins() const{ return _left != NULL && _right != NULL;}
    bool isLeft() const{ return _parent && this == _parent->_left;}
    bool isRight() const{ return _parent && this == _parent->_right;}
    Node *sibling()const{
        if(isLeft()) return  _parent->_right;
        if(isRight()) return _parent->_left;
        return NULL;
    }
};


#include "printer/Tree.hpp"
template<class T>
class BinaryTree;

template<class T>
ostream &operator <<(ostream &os, const BinaryTree<T> &bst);

template<class T>
class BinaryTree : public TreeInfo<T>{
    void printTree(Node<T> *node, string &sb, string prefix) const;
    
    void preOrder(Node<T> *node)const;
    void inOrder(Node<T> *node)const;
    void postOrder(Node<T> *node)const;
    void levelOrder(Node<T> *node)const;
    
    int  height(Node<T> *node) const;
    bool isComplete(Node<T> *node)const;
    
    void reverse(Node<T> *node);
    
    Node<T> *root()const override{ return _root;}
    Node<T> *left(Node<T> *node)const override {return node->_left;}
    Node<T> *right(Node<T> *node)const override {return node->_right;}
    string description(Node<T> *node)const override {
        string pString;
        Node<T> *parent = node->_parent;
        if (!parent) pString = "_P(NULL)";
        else pString = "_P(" + to_string(parent->_element) + ")";
        string nString = "(" + to_string(node->_element) + ")";
        return nString + pString;
    }
protected:
    int _size;
    Node<T> *_root;

    Node<T> *predecessor(Node<T> *node) const;
    Node<T> *successor(Node<T> *node) const;
public:
    

    BinaryTree() : _size(0), _root(NULL){}

    int  size() const;
    bool isEmpty() const;
    
    //递归遍历
    void preOrder()const;
    void inOrder()const;
    void postOrder()const;
    
    //非递归遍历
    void preOrder2()const;
    void inOrder2()const;
    void postOrder2()const;
    
    void preOrder3()const;

    void levelOrder()const;

    
    int  height()const;
    bool isComplete()const;
    void reverse();
    friend ostream &operator << <>(ostream &os, const BinaryTree<T> &bst);
};

#pragma mark - public
template<class T>
int BinaryTree<T>::size() const{
    return _size;
}

template<class T>
bool BinaryTree<T>::isEmpty() const{
    return _size == 0;
}

#pragma mark Traversal
template<class T>
void BinaryTree<T>::preOrder() const{
    preOrder(_root);
    cout << endl;
}

template<class T>
void BinaryTree<T>::inOrder() const{
    inOrder(_root);
    cout << endl;
}

template<class T>
void BinaryTree<T>::postOrder() const{
    postOrder(_root);
    cout << endl;
}

template<class T>
void BinaryTree<T>::levelOrder() const{
    levelOrder(_root);
    cout << endl;
}

template<class T>
void BinaryTree<T>::preOrder2() const{
    if (!_root) return;
    stack<Node<T> *> s;
    Node<T> *n = _root;
    while (true){
        if (n){
            cout << n->_element << " ";
            if (n->_right) s.emplace(n->_right);
            n = n->_left;
        }else if (s.empty()){
            cout << endl;
            return;
        }else{
            n = s.top();
            s.pop();
        }
    }
}

template<class T>
void BinaryTree<T>::preOrder3() const{
    if (!_root) return;
    stack<Node<T> *> s;
    s.emplace(_root);
    Node<T> *n = NULL;
    
    while (!s.empty()){
        n = s.top();
        s.pop();
        cout << n->_element << " ";
        if (n->_right) s.emplace(n->_right);
        if (n->_left) s.emplace(n->_left);
    }
    cout << endl;            
}


template<class T>
void BinaryTree<T>::inOrder2() const{
    if (!_root) return;
    stack<Node<T> *> s;
    Node<T> *n = _root;
    while (true){
        if (n) {
            s.emplace(n);
            n = n->_left;
        }else if (s.empty()){
            cout << endl;
            return;
        }else{
            n = s.top();
            s.pop();
            cout << n->_element << " ";
            n = n->_right;
        }
    }
}

template<class T>
void BinaryTree<T>::postOrder2() const{
    if (!_root) return;
    stack<Node<T> *> s;
    Node<T> *n = NULL;
    Node<T> *prev = NULL; //上一次访问的节点
    s.emplace(_root);
    while (!s.empty()){
        n = s.top();
        if (n->isLeaf() || (prev && prev->_parent == n) ){
            prev = n;
            s.pop();
            cout << n->_element << " ";
        }else {
            if (n->_right)s.emplace(n->_right);
            if (n->_left) s.emplace(n->_left);
        }
    }
    cout << endl;
}


template<class T>
int BinaryTree<T>::height()const{
//    if (!_root) return 0;
//
//    queue<Node<T> *> queue;
//    queue.push(_root);
//    int height = 0;
//    unsigned long levelSize = 1;
//    while (!queue.empty()) {
//        Node<T> *n = queue.front();
//        queue.pop();
//
//        if (n->_left) {
//            queue.push(n->_left);
//        }
//        if (n->_right) {
//            queue.push(n->_right);
//        }
//        levelSize--;
//
//        if (!levelSize) {
//            height++;
//            levelSize = queue.size();
//        }
//    }
//
//    return height;
    
    //递归实现
    return height(_root);
}

template<class T>
bool BinaryTree<T>::isComplete()const{
    return isComplete(_root);
}

template<class T>
void BinaryTree<T>::reverse(){
    reverse(_root);
}

#pragma mark - private

template<class T>
Node<T> * BinaryTree<T>::predecessor(Node<T> *node) const{
    if (!node) return NULL;
    
    Node<T> *p = node->_left;
    if (p) {
        while (p->_right)
            p = p->_right;
    }else if (!p && node->_parent){
        p = node;
        while (p->_parent && p == p->_parent->_left)
            p = p->_parent;
        p = p->_parent;
    }
    
    return p;
}

template<class T>
Node<T> *  BinaryTree<T>::successor(Node<T> *node) const{
    if (!node) return NULL;
    
    Node<T> *p = node->_right;
    if (p) {
        while (p->_left)
            p = p->_left;
    }else if (!p && node->_parent){
        p = node;
        while (p->_parent && p == p->_parent->_right)
            p = p->_parent;
        p = p->_parent;
    }
    
    return p;
}

template<class T>
void  BinaryTree<T>::printTree(Node<T> *node, string &sb, string prefix) const{
    if (!node) return;
    
    printTree(node->_left, sb, prefix + "L---");
    sb.append(prefix).append(to_string(node->_element)).append("\n");
    printTree(node->_right, sb, prefix + "R---");
}

#pragma mark Traversal
template<class T>
void BinaryTree<T>::preOrder(Node<T> *node)const{
    if (!node) return;
    cout << node->_element << " ";
    preOrder(node->_left);
    preOrder(node->_right);
}

template<class T>
void BinaryTree<T>::inOrder(Node<T> *node)const{
    if (!node) return;
    inOrder(node->_left);
    cout << node->_element << " ";
    inOrder(node->_right);
}

template<class T>
void BinaryTree<T>::postOrder(Node<T> *node)const{
    if (!node) return;
    postOrder(node->_left);
    postOrder(node->_right);
    cout << node->_element << " ";
}

template<class T>
void BinaryTree<T>::levelOrder(Node<T> *node)const{
    if (!node) return;

    queue<Node<T> *> queue;
    queue.push(node);
    while (!queue.empty()) {
        Node<T> *n = queue.front();
        queue.pop();
        cout << n->_element << " ";
        
        if (n->_left) {
            queue.push(n->_left);
        }
        if (n->_right) {
            queue.push(n->_right);
        }
    }
}

template<class T>
int BinaryTree<T>::height(Node<T> *node)const{
    if (!node) return 0;
    return 1 + max(height(node->_left), height(node->_right));
}
template<class T>
bool BinaryTree<T>::isComplete(Node<T> *node)const{
    if (!node) return false;
    
    queue<Node<T> *> queue;
    queue.push(node);
    bool nonTwinsOn = false; //出现度不为2的结点
    while(!queue.empty()){
        Node<T> *n = queue.front();
        queue.pop();
        if (nonTwinsOn && !n->isLeaf()) return false;
        
//        if (n->_left && n->_right) {
//            queue.push(n->_left);
//            queue.push(n->_right);
//        }else if(!n->_left && n->_right){
//            return false;
//        }else if(n->_left && !n->_right){
//            nonTwinsOn = true;
//            queue.push(n->_left);
//        }else{
//            nonTwinsOn = true;
//        }
        if (n->_left){
            queue.push(n->_left);
        }else if(n->_right){
            return false;
        }
        
        if (n->_right){
            queue.push(n->_right);
        }else{
            nonTwinsOn = true;
        }
        
    }
    return true;
}

template<class T>
void BinaryTree<T>::reverse(Node<T> *node){
    if (!node) return;
    reverse(node->_left);
    reverse(node->_right);
    Node<T> *temp = node->_left;
    node->_left = node->_right;
    node->_right = temp;
}

#pragma mark -
template<class T>
ostream &operator <<(ostream &os, const BinaryTree<T> &bst){
    string s;
    bst.printTree(bst._root, s, "");
    os << "size = " << bst.size() << endl;
    return os << s;
}

#pragma mark - template specialization for string
template<>
class BinaryTree<string> : public TreeInfo<string>{
    void printTree(Node<string> *node, string &sb, string prefix) const;
    
    void preOrder(Node<string> *node)const;
    void inOrder(Node<string> *node)const;
    void postOrder(Node<string> *node)const;
    void levelOrder(Node<string> *node)const;
    
    int  height(Node<string> *node) const;
    bool isComplete(Node<string> *node)const;
    
    void reverse(Node<string> *node);
    
    Node<string> *root()const override{ return _root;}
    Node<string> *left(Node<string> *node)const override {return node->_left;}
    Node<string> *right(Node<string> *node)const override {return node->_right;}
    string description(Node<string> *node)const override {
        string pString;
        Node<string> *parent = node->_parent;
        if (!parent) pString = "_P(NULL)";
        else pString = "_P(" + parent->_element + ")";
        string nString = "(" + node->_element + ")";
        return nString + pString;
    }
protected:
    int _size;
    Node<string> *_root;

    Node<string> *predecessor(Node<string> *node) const;
    Node<string> *successor(Node<string> *node) const;
public:
    

    BinaryTree() : _size(0), _root(NULL){}

    int  size() const;
    bool isEmpty() const;
    
    void preOrder()const;
    void inOrder()const;
    void postOrder()const;
    void levelOrder()const;
    
    int  height()const;
    bool isComplete()const;
    void reverse();
    friend ostream &operator <<(ostream &os, const BinaryTree<string> &bst);
};

#pragma mark - public
int BinaryTree<string>::size() const{
    return _size;
}

bool BinaryTree<string>::isEmpty() const{
    return _size == 0;
}

#pragma mark Traversal
void BinaryTree<string>::preOrder() const{
    preOrder(_root);
    cout << endl;
}

void BinaryTree<string>::inOrder() const{
    inOrder(_root);
    cout << endl;
}

void BinaryTree<string>::postOrder() const{
    postOrder(_root);
    cout << endl;
}

void BinaryTree<string>::levelOrder() const{
    levelOrder(_root);
    cout << endl;
}


int BinaryTree<string>::height()const{
    //递归实现
    return height(_root);
}

bool BinaryTree<string>::isComplete()const{
    return isComplete(_root);
}

void BinaryTree<string>::reverse(){
    reverse(_root);
}

#pragma mark - private
Node<string> * BinaryTree<string>::predecessor(Node<string> *node) const{
    if (!node) return NULL;
    
    Node<string> *p = node->_left;
    if (p) {
        while (p->_right)
            p = p->_right;
    }else if (!p && node->_parent){
        p = node;
        while (p->_parent && p == p->_parent->_left)
            p = p->_parent;
        p = p->_parent;
    }
    
    return p;
}

Node<string> *  BinaryTree<string>::successor(Node<string> *node) const{
    if (!node) return NULL;
    
    Node<string> *p = node->_right;
    if (p) {
        while (p->_left)
            p = p->_left;
    }else if (!p && node->_parent){
        p = node;
        while (p->_parent && p == p->_parent->_right)
            p = p->_parent;
        p = p->_parent;
    }
    
    return p;
}

void  BinaryTree<string>::printTree(Node<string> *node, string &sb, string prefix) const{
    if (!node) return;
    
    printTree(node->_left, sb, prefix + "L---");
    sb.append(prefix).append(node->_element).append("\n");
    printTree(node->_right, sb, prefix + "R---");
}

#pragma mark Traversal
void BinaryTree<string>::preOrder(Node<string> *node)const{
    if (!node) return;
    cout << node->_element << " ";
    preOrder(node->_left);
    preOrder(node->_right);
}

void BinaryTree<string>::inOrder(Node<string> *node)const{
    if (!node) return;
    inOrder(node->_left);
    cout << node->_element << " ";
    inOrder(node->_right);
}

void BinaryTree<string>::postOrder(Node<string> *node)const{
    if (!node) return;
    postOrder(node->_left);
    postOrder(node->_right);
    cout << node->_element << " ";
}

void BinaryTree<string>::levelOrder(Node<string> *node)const{
    if (!node) return;

    queue<Node<string> *> queue;
    queue.push(node);
    while (!queue.empty()) {
        Node<string> *n = queue.front();
        queue.pop();
        cout << n->_element << " ";
        
        if (n->_left) {
            queue.push(n->_left);
        }
        if (n->_right) {
            queue.push(n->_right);
        }
    }
}

int BinaryTree<string>::height(Node<string> *node)const{
    if (!node) return 0;
    return 1 + max(height(node->_left), height(node->_right));
}

bool BinaryTree<string>::isComplete(Node<string> *node)const{
    if (!node) return false;
    
    queue<Node<string> *> queue;
    queue.push(node);
    bool nonTwinsOn = false; //出现度不为2的结点
    while(!queue.empty()){
        Node<string> *n = queue.front();
        queue.pop();
        if (nonTwinsOn && !n->isLeaf()) return false;
        if (n->_left){
            queue.push(n->_left);
        }else if(n->_right){
            return false;
        }
        
        if (n->_right){
            queue.push(n->_right);
        }else{
            nonTwinsOn = true;
        }
        
    }
    return true;
}

void BinaryTree<string>::reverse(Node<string> *node){
    if (!node) return;
    reverse(node->_left);
    reverse(node->_right);
    Node<string> *temp = node->_left;
    node->_left = node->_right;
    node->_right = temp;
}

#pragma mark -
ostream &operator <<(ostream &os, const BinaryTree<string> &bst){
    string s;
    bst.printTree(bst._root, s, "");
    os << "size = " << bst.size() << endl;
    return os << s;
}

#pragma mark - template specialization for const char *
template<>
class BinaryTree<const char *> : public TreeInfo<const char *>{
    void printTree(Node<const char *> *node, string &sb, string prefix) const;
    
    void preOrder(Node<const char *> *node)const;
    void inOrder(Node<const char *> *node)const;
    void postOrder(Node<const char *> *node)const;
    void levelOrder(Node<const char *> *node)const;
    
    int  height(Node<const char *> *node) const;
    bool isComplete(Node<const char *> *node)const;
    
    void reverse(Node<const char *> *node);
    
    Node<const char *> *root()const override{ return _root;}
    Node<const char *> *left(Node<const char *> *node)const override {return node->_left;}
    Node<const char *> *right(Node<const char *> *node)const override {return node->_right;}
    string description(Node<const char *> *node)const override {
        string pString;
        Node<const char *> *parent = node->_parent;
        if (!parent) pString = "_P(NULL)";
        else {
            pString = parent->_element;
            pString = "_P(" + pString + ")";
        }
        string nString = node->_element;
        nString = "(" + nString + ")";
        return nString + pString;
    }
protected:
    int _size;
    Node<const char *> *_root;

    Node<const char *> *predecessor(Node<const char *> *node) const;
    Node<const char *> *successor(Node<const char *> *node) const;
public:
    

    BinaryTree() : _size(0), _root(NULL){}

    int  size() const;
    bool isEmpty() const;
    
    void preOrder()const;
    void inOrder()const;
    void postOrder()const;
    void levelOrder()const;
    
    int  height()const;
    bool isComplete()const;
    void reverse();
    friend ostream &operator <<(ostream &os, const BinaryTree<const char *> &bst);
};

#pragma mark - public
int BinaryTree<const char *>::size() const{
    return _size;
}

bool BinaryTree<const char *>::isEmpty() const{
    return _size == 0;
}

#pragma mark Traversal
void BinaryTree<const char *>::preOrder() const{
    preOrder(_root);
    cout << endl;
}

void BinaryTree<const char *>::inOrder() const{
    inOrder(_root);
    cout << endl;
}

void BinaryTree<const char *>::postOrder() const{
    postOrder(_root);
    cout << endl;
}

void BinaryTree<const char *>::levelOrder() const{
    levelOrder(_root);
    cout << endl;
}


int BinaryTree<const char *>::height()const{
    return height(_root);
}

bool BinaryTree<const char *>::isComplete()const{
    return isComplete(_root);
}

void BinaryTree<const char *>::reverse(){
    reverse(_root);
}

#pragma mark - private
Node<const char *> * BinaryTree<const char *>::predecessor(Node<const char *> *node) const{
    if (!node) return NULL;
    
    Node<const char *> *p = node->_left;
    if (p) {
        while (p->_right)
            p = p->_right;
    }else if (!p && node->_parent){
        p = node;
        while (p->_parent && p == p->_parent->_left)
            p = p->_parent;
        p = p->_parent;
    }
    
    return p;
}

Node<const char *> *  BinaryTree<const char *>::successor(Node<const char *> *node) const{
    if (!node) return NULL;
    
    Node<const char *> *p = node->_right;
    if (p) {
        while (p->_left)
            p = p->_left;
    }else if (!p && node->_parent){
        p = node;
        while (p->_parent && p == p->_parent->_right)
            p = p->_parent;
        p = p->_parent;
    }
    
    return p;
}

void  BinaryTree<const char *>::printTree(Node<const char *> *node, string &sb, string prefix) const{
    if (!node) return;
    
    printTree(node->_left, sb, prefix + "L---");
    sb.append(prefix).append(node->_element).append("\n");
    printTree(node->_right, sb, prefix + "R---");
}

#pragma mark Traversal
void BinaryTree<const char *>::preOrder(Node<const char *> *node)const{
    if (!node) return;
    cout << node->_element << " ";
    preOrder(node->_left);
    preOrder(node->_right);
}

void BinaryTree<const char *>::inOrder(Node<const char *> *node)const{
    if (!node) return;
    inOrder(node->_left);
    cout << node->_element << " ";
    inOrder(node->_right);
}

void BinaryTree<const char *>::postOrder(Node<const char *> *node)const{
    if (!node) return;
    postOrder(node->_left);
    postOrder(node->_right);
    cout << node->_element << " ";
}

void BinaryTree<const char *>::levelOrder(Node<const char *> *node)const{
    if (!node) return;

    queue<Node<const char *> *> queue;
    queue.push(node);
    while (!queue.empty()) {
        Node<const char *> *n = queue.front();
        queue.pop();
        cout << n->_element << " ";
        
        if (n->_left) {
            queue.push(n->_left);
        }
        if (n->_right) {
            queue.push(n->_right);
        }
    }
}

int BinaryTree<const char *>::height(Node<const char *> *node)const{
    if (!node) return 0;
    return 1 + max(height(node->_left), height(node->_right));
}

bool BinaryTree<const char *>::isComplete(Node<const char *> *node)const{
    if (!node) return false;
    
    queue<Node<const char *> *> queue;
    queue.push(node);
    bool nonTwinsOn = false; //出现度不为2的结点
    while(!queue.empty()){
        Node<const char *> *n = queue.front();
        queue.pop();
        if (nonTwinsOn && !n->isLeaf()) return false;
       
        if (n->_left){
            queue.push(n->_left);
        }else if(n->_right){
            return false;
        }
        
        if (n->_right){
            queue.push(n->_right);
        }else{
            nonTwinsOn = true;
        }
        
    }
    return true;
}

void BinaryTree<const char *>::reverse(Node<const char *> *node){
    if (!node) return;
    reverse(node->_left);
    reverse(node->_right);
    Node<const char *> *temp = node->_left;
    node->_left = node->_right;
    node->_right = temp;
}

#pragma mark -
ostream &operator <<(ostream &os, const BinaryTree<const char *> &bst){
    string s;
    bst.printTree(bst._root, s, "");
    os << "size = " << bst.size() << endl;
    return os << s;
}

#endif /* BinaryTree_hpp */
