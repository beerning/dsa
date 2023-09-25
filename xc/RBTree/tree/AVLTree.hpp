//
//  AVLTree.hpp
//  Tree
//
//  Created by berning on 2015/4/26.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp
#include "BBST.hpp"

template<class T>
class AVLNode : public Node<T>{
    int _height;

    void childHeight(int &lh, int &rh) const{
        AVLNode<T> *left = (AVLNode<T> *)this->_left;
        AVLNode<T> *right = (AVLNode<T> *)this->_right;
        lh = left ? left->_height : 0;
        rh = right ? right->_height : 0;
    }
public:
    int height() const{ return _height;}
    AVLNode(T v, Node<T> *parent) : Node<T>(v, parent), _height(1){}
    int balanceFactor() const{
        int lh, rh;
        childHeight(lh, rh);
        return lh - rh;
    }
    void updateHeight(){
        int lh, rh;
        childHeight(lh, rh);
        _height = 1 + max(lh, rh);
    }
    
    Node<T> *tallerChild() const{
        int lh, rh;
        childHeight(lh, rh);
        if (lh > rh) return this->_left;
        if (lh < rh) return this->_right;
        return NULL;
    }
};

template <class T>
class AVLTree : public BBST<T>{
    void afterAdd(Node<T> *node) override;
    void afterRemove(Node<T> *node) override;
    Node<T> *newNode(T v, Node<T> *parent) override {return new AVLNode<T>(v, parent);};
    string description(Node<T> *node)const override;
    
    bool isBalanced(Node<T> *node) const;
    void updateHeight(Node<T> *node);
    
    void rebalance(Node<T> *grand);
    
    void rotate(Node<T> *r, Node<T> *b, Node<T> *c, Node<T> *d, Node<T> *e, Node<T> *f) override;
    void zigzaged(Node<T> *grand, Node<T> *parent, Node<T> *child) override;

public:
    AVLTree() : AVLTree(NULL) {}
    AVLTree(int (*comparator)(T, T)) : BBST<T>(comparator){}
};

template<class T>
void AVLTree<T>::afterAdd(Node<T> *node){
    while ((node = node->_parent) != NULL) {
        if (isBalanced(node)){
            updateHeight(node);
        }else{
            rebalance(node);
            break;
        }
    }
}

template<class T>
void AVLTree<T>::afterRemove(Node<T> *node){
    while ((node = node->_parent) != NULL) {
        if (isBalanced(node)){
            updateHeight(node);
        }else{
            rebalance(node);
        }
    }
}

template<class T>
bool AVLTree<T>::isBalanced(Node<T> *node) const{
    AVLNode<T> *n = (AVLNode<T> *)node;
    return abs(n->balanceFactor()) <= 1 ;
}

template<class T>
void AVLTree<T>::updateHeight(Node<T> *node){
    AVLNode<T> *n = (AVLNode<T> *)node;
    n->updateHeight();
}

template<class T>
void AVLTree<T>::rebalance(Node<T> *grand){
    Node<T> *parent = ((AVLNode<T> *)grand)->tallerChild();
    Node<T> *child = ((AVLNode<T> *)parent)->tallerChild();
    
    if (parent->isLeft()){ //L
        if (child->isRight()) this->zag(parent); //LR
        this->zig(grand);
    }else{
        if (child->isLeft()) this->zig(parent);  //RL
        this->zag(grand);
    }
    
//    if (parent->isLeft()){
//        if (child->isLeft()) //LL
//            rotate(grand, child, child->_right, parent, parent->_right, grand);
//        else//LR
//            rotate(grand, parent, child->_left, child, child->_right, grand);
//    }else{
//        if (child->isRight())  //RR
//            rotate(grand, grand, parent->_left, parent, child->_left, child);
//        else//RL
//            rotate(grand, grand, child->_left, child, child->_right, parent);
//    }
}

#pragma mark - uniform rotate
template<class T>
void AVLTree<T>::rotate(Node<T> *r, Node<T> *b, Node<T> *c, Node<T> *d, Node<T> *e, Node<T> *f){
    BBST<T>::rotate(r, b, c, d, e, f);
    updateHeight(b);
    updateHeight(d);
    updateHeight(f);
}

#pragma mark - zig-zag
template<class T>
void AVLTree<T>::zigzaged(Node<T> *grand, Node<T> *parent, Node<T> *child){
    BBST<T>::zigzaged(grand, parent, child);
    updateHeight(grand);
    updateHeight(parent);
}

template<class T>
string AVLTree<T>::description(Node<T> *node)const{
    string pString;
    AVLNode<T> *n = (AVLNode<T> *)node;
    Node<T> *parent = node->_parent;
    if (!parent) pString = "_P(NULL)";
    else pString = "_P(" + to_string(parent->_element) + ")";
    string nString = "(" + to_string(node->_element) + ")";
    string hString = "_H(" + to_string(n->height()) + ")";
    return nString + pString + hString;
}

#pragma mark template specialization for string
template <>
class AVLTree<string> : public BBST<string>{
    void afterAdd(Node<string> *node) override;
    void afterRemove(Node<string> *node) override;
    Node<string> *newNode(string v, Node<string> *parent) override {return new AVLNode<string>(v, parent);};
    string description(Node<string> *node)const override;
    
    bool isBalanced(Node<string> *node) const;
    void updateHeight(Node<string> *node);
    
    void rebalance(Node<string> *grand);
    
    void rotate(Node<string> *r, Node<string> *b, Node<string> *c, Node<string> *d, Node<string> *e, Node<string> *f) override;
    void zigzaged(Node<string> *grand, Node<string> *parent, Node<string> *child) override;

public:
    AVLTree() : AVLTree(NULL) {}
    AVLTree(int (*comparator)(string, string)) : BBST<string>(comparator){}
};

void AVLTree<string>::afterAdd(Node<string> *node){
    while ((node = node->_parent) != NULL) {
        if (isBalanced(node)){
            updateHeight(node);
        }else{
            rebalance(node);
            break;
        }
    }
}

void AVLTree<string>::afterRemove(Node<string> *node){
    while ((node = node->_parent) != NULL) {
        if (isBalanced(node)){
            updateHeight(node);
        }else{
            rebalance(node);
        }
    }
}

bool AVLTree<string>::isBalanced(Node<string> *node) const{
    AVLNode<string> *n = (AVLNode<string> *)node;
    return abs(n->balanceFactor()) <= 1 ;
}

void AVLTree<string>::updateHeight(Node<string> *node){
    AVLNode<string> *n = (AVLNode<string> *)node;
    n->updateHeight();
}

void AVLTree<string>::rebalance(Node<string> *grand){
    Node<string> *parent = ((AVLNode<string> *)grand)->tallerChild();
    Node<string> *child = ((AVLNode<string> *)parent)->tallerChild();
    
    if (parent->isLeft()){ //L
        if (child->isRight()) this->zag(parent); //LR
        this->zig(grand);
    }else{
        if (child->isLeft()) this->zig(parent);  //RL
        this->zag(grand);
    }
    
//    if (parent->isLeft()){
//        if (child->isLeft()) //LL
//            rotate(grand, child, child->_right, parent, parent->_right, grand);
//        else//LR
//            rotate(grand, parent, child->_left, child, child->_right, grand);
//    }else{
//        if (child->isRight())  //RR
//            rotate(grand, grand, parent->_left, parent, child->_left, child);
//        else//RL
//            rotate(grand, grand, child->_left, child, child->_right, parent);
//    }
}

#pragma mark - uniform rotate
void AVLTree<string>::rotate(Node<string> *r, Node<string> *b, Node<string> *c, Node<string> *d, Node<string> *e, Node<string> *f){
    BBST<string>::rotate(r, b, c, d, e, f);
    updateHeight(b);
    updateHeight(d);
    updateHeight(f);
}

#pragma mark - zig-zag
void AVLTree<string>::zigzaged(Node<string> *grand, Node<string> *parent, Node<string> *child){
    BBST<string>::zigzaged(grand, parent, child);
    updateHeight(grand);
    updateHeight(parent);
}

string AVLTree<string>::description(Node<string> *node)const{
    string pString;
    AVLNode<string> *n = (AVLNode<string> *)node;
    Node<string> *parent = node->_parent;
    if (!parent) pString = "_P(NULL)";
    else pString = "_P(" + parent->_element + ")";
    string nString = "(" + node->_element + ")";
    string hString = "_H(" + to_string(n->height()) + ")";
    return nString + pString + hString;
}

#pragma mark template specialization for const char *
template <>
class AVLTree<const char *> : public BBST<const char *>{
    void afterAdd(Node<const char *> *node) override;
    void afterRemove(Node<const char *> *node) override;
    Node<const char *> *newNode(const char * v, Node<const char *> *parent) override {return new AVLNode<const char *>(v, parent);};
    string description(Node<const char *> *node)const override;
    
    bool isBalanced(Node<const char *> *node) const;
    void updateHeight(Node<const char *> *node);
    
    void rebalance(Node<const char *> *grand);
    
    void rotate(Node<const char *> *r, Node<const char *> *b, Node<const char *> *c, Node<const char *> *d, Node<const char *> *e, Node<const char *> *f) override;
    void zigzaged(Node<const char *> *grand, Node<const char *> *parent, Node<const char *> *child) override;

public:
    AVLTree() : AVLTree(NULL) {}
    AVLTree(int (*comparator)(const char *, const char *)) : BBST<const char *>(comparator){}
};

void AVLTree<const char *>::afterAdd(Node<const char *> *node){
    while ((node = node->_parent) != NULL) {
        if (isBalanced(node)){
            updateHeight(node);
        }else{
            rebalance(node);
            break;
        }
    }
}

void AVLTree<const char *>::afterRemove(Node<const char *> *node){
    while ((node = node->_parent) != NULL) {
        if (isBalanced(node)){
            updateHeight(node);
        }else{
            rebalance(node);
        }
    }
}

bool AVLTree<const char *>::isBalanced(Node<const char *> *node) const{
    AVLNode<const char *> *n = (AVLNode<const char *> *)node;
    return abs(n->balanceFactor()) <= 1 ;
}

void AVLTree<const char *>::updateHeight(Node<const char *> *node){
    AVLNode<const char *> *n = (AVLNode<const char *> *)node;
    n->updateHeight();
}

void AVLTree<const char *>::rebalance(Node<const char *> *grand){
    Node<const char *> *parent = ((AVLNode<const char *> *)grand)->tallerChild();
    Node<const char *> *child = ((AVLNode<const char *> *)parent)->tallerChild();
    
    if (parent->isLeft()){ //L
        if (child->isRight()) this->zag(parent); //LR
        this->zig(grand);
    }else{
        if (child->isLeft()) this->zig(parent);  //RL
        this->zag(grand);
    }
    
//    if (parent->isLeft()){
//        if (child->isLeft()) //LL
//            rotate(grand, child, child->_right, parent, parent->_right, grand);
//        else//LR
//            rotate(grand, parent, child->_left, child, child->_right, grand);
//    }else{
//        if (child->isRight())  //RR
//            rotate(grand, grand, parent->_left, parent, child->_left, child);
//        else//RL
//            rotate(grand, grand, child->_left, child, child->_right, parent);
//    }
}

#pragma mark - uniform rotate
void AVLTree<const char *>::rotate(Node<const char *> *r, Node<const char *> *b, Node<const char *> *c, Node<const char *> *d, Node<const char *> *e, Node<const char *> *f){
    BBST<const char *>::rotate(r, b, c, d, e, f);
    updateHeight(b);
    updateHeight(d);
    updateHeight(f);
}

#pragma mark - zig-zag
void AVLTree<const char *>::zigzaged(Node<const char *> *grand, Node<const char *> *parent, Node<const char *> *child){
    BBST<const char *>::zigzaged(grand, parent, child);
    updateHeight(grand);
    updateHeight(parent);
}

string AVLTree<const char *>::description(Node<const char *> *node)const{
    string pString;
    AVLNode<const char *> *n = (AVLNode<const char *> *)node;
    Node<const char *> *parent = node->_parent;
    if (!parent) pString = "_P(NULL)";
    else {
        pString = parent->_element;
        pString = "_P(" + pString + ")";
    }
    string nString = node->_element;
    nString = "(" + nString + ")";
    string hString = "_H(" + to_string(n->height()) + ")";
    return nString + pString + hString;
}

#endif /* AVLTree_hpp */
