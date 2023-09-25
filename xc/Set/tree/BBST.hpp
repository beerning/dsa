//
//  BBST.hpp
//  RBTree
//
//  Created by berning on 2015/5/5.
//

#ifndef BBST_hpp
#define BBST_hpp

#include "BinarySearchTree.hpp"

template<class T>
class BBST : public BinarySearchTree<T> {
protected:
    void zig(Node<T> *grand);
    void zag(Node<T> *grand);
    virtual void zigzaged(Node<T> *grand, Node<T> *parent, Node<T> *child);
    virtual void rotate(Node<T> *r, Node<T> *b, Node<T> *c, Node<T> *d, Node<T> *e, Node<T> *f);
    BBST(int (*comparator)(T, T)) : BinarySearchTree<T>(comparator){}
};

#pragma mark - uniform rotate
template<class T>
void BBST<T>::rotate(Node<T> *r, Node<T> *b, Node<T> *c, Node<T> *d, Node<T> *e, Node<T> *f){
    //d
    d->_parent = r->_parent;
    if (r->isLeft()) r->_parent->_left = d;
    else if (r->isRight()) r->_parent->_right = d;
    else this->_root = d;
    
    //b,c
    b->_right = c;
    if (c) c->_parent = b;
    
    //e,f
    f->_left = e;
    if (e) e->_parent = f;
    
    //b, d, f
    d->_left = b;
    d->_right = f;
    b->_parent = d;
    f->_parent = d;
}

#pragma mark - zig-zag
template<class T>
void BBST<T>::zig(Node<T> *grand){//LL
    Node<T> *parent = grand->_left;
    Node<T> *child = parent->_right;
    
    grand->_left = child;
    parent->_right = grand;
    zigzaged(grand, parent, child);
}

template<class T>
void BBST<T>::zag(Node<T> *grand){//RR
    Node<T> *parent = grand->_right;
    Node<T> *child = parent->_left;
    
    grand->_right = child;
    parent->_left = grand;
    zigzaged(grand, parent, child);
}

template<class T>
void BBST<T>::zigzaged(Node<T> *grand, Node<T> *parent, Node<T> *child){
    parent->_parent = grand->_parent;
    
    if (grand->isLeft()) grand->_parent->_left = parent;
    else if (grand->isRight())grand->_parent->_right = parent;
    else this->_root = parent;
    
    grand->_parent = parent;
    
    if (child) child->_parent = grand;
}



#endif /* BBST_hpp */
