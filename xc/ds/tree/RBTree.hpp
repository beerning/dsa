//
//  RBTree.hpp
//  BalancedBST
//
//  Created by berning on 2015/4/29.
//

#ifndef RBTree_hpp
#define RBTree_hpp

#include "BBST.hpp"

typedef enum{
    Red,
    Black
} RBColor;

template<class T>
class RBNode : public Node<T>{
    RBColor _color;
public:
    RBNode(T v, Node<T> *parent) : Node<T>(v, parent), _color(Red) {}
    void setColor(RBColor color){_color = color;}
    RBColor color() const{return _color;}
};

template <class T>
class RBTree : public BBST<T>{
    
    void afterAdd(Node<T> *node) override;
    void afterRemove(Node<T> *node) override;
    Node<T> *newNode(T v, Node<T> *parent) override {return new RBNode<T>(v, parent);}
    string description(Node<T> *node)const override;
    
    RBColor colorOf(Node<T> *node) const{ return node ? ((RBNode<T> *)node)->color() : Black;}
    bool isRed(Node<T> *node) const{return colorOf(node) == Red;}
    bool isBlack(Node<T> *node) const{return colorOf(node) == Black;}

    void color(Node<T> *node, RBColor color){ if(node) ((RBNode<T> *)node)->setColor(color);}
    void red(Node<T> *node){color(node, Red);}
    void black(Node<T> *node){color(node, Black);}

public:
    RBTree() : RBTree(NULL) {}
    RBTree(int (*comparator)(T, T)) : BBST<T>(comparator){}
};

template<class T>
void RBTree<T>::afterAdd(Node<T> *child){
    if (child == this->_root) black(child);
    Node<T> *parent = child->_parent;
    if (isBlack(parent)) return; // parent == NULL; color == Black;
    
    //parent != NULL
    Node<T> *grand = parent->_parent;
    Node<T> *uncle = parent->sibling();
    if (colorOf(uncle) != Red){
        red(grand);
        if (parent->isLeft()){
            if (child->isLeft()) { black(parent);}
            else {black(child); this->zag(parent);}
            this->zig(grand);
        } else {
            if (child->isRight()) {black(parent);}
            else {black(child); this->zig(parent);}
            this->zag(grand);
        }
    }else{
        black(parent);
        black(uncle);
        red(grand);
        afterAdd(grand);
    }
}

template<class T>
void RBTree<T>::afterRemove(Node<T> *node){
    //度1的子node为red 或被删除的node为red
    if (isRed(node)) {black(node); return;}
    
    //node is black
    //node is root
    Node<T> *parent = node->_parent;
    if (!parent) return;
   
    //node is not root
    bool isLeft = parent->_left == NULL || node->isLeft(); //parent->_left == NULL判断叶子节点,node->isLeft()判断parent下溢的情况(line102)
    Node<T> *sibling = isLeft ? parent->_right : parent->_left;

    if (isLeft){ //node is left, sibling is right
        if (isRed(sibling)){ //sibling == red,使sibling == black
            black(sibling);
            red(parent);
            this->zag(parent);
            sibling = parent->_right; //sibling == black
        }
        //sibling == black
        if (isBlack(sibling->_left) && isBlack(sibling->_right)){ //sibling没有red子节点
            bool isb = isBlack(parent);
            black(parent);
            red(sibling);
            if (isb) afterRemove(parent);
        }else {//sibling 至少一个 red 子节点
            if (isBlack(sibling->_right)){  //left red, RL
                this->zig(sibling);
                sibling = parent->_right;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_right);
            this->zag(parent);
        }
    
    }else {//node is right, sibling is left
        if (isRed(sibling)){
            black(sibling);
            red(parent);
            this->zig(parent);
            sibling = parent->_left;
        }
        
        if (isBlack(sibling->_left) && isBlack(sibling->_right)){
            bool isb = isBlack(parent);
            red(sibling);
            black(parent);
            if (isb) afterRemove(parent);
        }else {
            if (isBlack(sibling->_left)){
                this->zag(sibling);
                sibling = parent->_left;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_left);
            this->zig(parent);
        }
    }
}

template<class T>
string RBTree<T>::description(Node<T> *node)const{
    string pString;
    RBNode<T> *n = (RBNode<T> *)node;
//    Node<T> * parent = n->_parent;
//    if (!parent) pString = "_P(NULL)";
//    else pString = "_P(" + to_string(parent->_element) + ")";
    
    string colorString;
    if (!n->color()) colorString = "R_";
    
    string nString = "(" + to_string(n->_element) + ")";
    
    return colorString + nString + pString;
}


#pragma mark - template specialization for string
template <>
class RBTree<string> : public BBST<string>{
    
    void afterAdd(Node<string> *node) override;
    void afterRemove(Node<string> *node) override;
    Node<string> *newNode(string v, Node<string> *parent) override {return new RBNode<string>(v, parent);}
    string description(Node<string> *node)const override;
    
    RBColor colorOf(Node<string> *node) const{ return node ? ((RBNode<string> *)node)->color() : Black;}
    bool isRed(Node<string> *node) const{return colorOf(node) == Red;}
    bool isBlack(Node<string> *node) const{return colorOf(node) == Black;}

    void color(Node<string> *node, RBColor color){ if(node) ((RBNode<string> *)node)->setColor(color);}
    void red(Node<string> *node){color(node, Red);}
    void black(Node<string> *node){color(node, Black);}

public:
    RBTree() : RBTree(NULL) {}
    RBTree(int (*comparator)(string, string)) : BBST<string>(comparator){}
};


void RBTree<string>::afterAdd(Node<string> *child){
    if (child == this->_root) black(child);
    Node<string> *parent = child->_parent;
    if (isBlack(parent)) return; // parent == NULL; color == Black;
    
    //parent != NULL
    Node<string> *grand = parent->_parent;
    Node<string> *uncle = parent->sibling();
    if (colorOf(uncle) != Red){
        red(grand);
        if (parent->isLeft()){
            if (child->isLeft()) { black(parent);}
            else {black(child); this->zag(parent);}
            this->zig(grand);
        } else {
            if (child->isRight()) {black(parent);}
            else {black(child); this->zig(parent);}
            this->zag(grand);
        }
    }else{
        black(parent);
        black(uncle);
        red(grand);
        afterAdd(grand);
    }
}


void RBTree<string>::afterRemove(Node<string> *node){
    if (colorOf(node) == Red) return;
    
    //度为1
    if (isRed(node)) {black(node); return;}
    
    //叶子结点
    Node<string> *parent = node->_parent;
    if (!parent) return;
    
    bool isLeft = parent->_left == NULL || node->isLeft();
    Node<string> *sibling = isLeft ? parent->_right : parent->_left;

    if (isLeft){ //node is left, sibling is right
        if (isRed(sibling)){ //sibling == red,使sibling == black
            black(sibling);
            red(parent);
            this->zag(parent);
            sibling = parent->_right; //sibling == black
        }
        //sibling == black
        if (isBlack(sibling->_left) && isBlack(sibling->_right)){ //sibling没有red子节点
            bool isb = isBlack(parent);
            black(parent);
            red(sibling);
            if (isb) afterRemove(parent);
        }else {//sibling 至少一个 red 子节点
            if (isBlack(sibling->_right)){  //left red, RL
                this->zig(sibling);
                sibling = parent->_right;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_right);
            this->zag(parent);
        }
    
    }else {//node is right, sibling is left
        if (isRed(sibling)){
            black(sibling);
            red(parent);
            this->zig(parent);
            sibling = parent->_left;
        }
        
        if (isBlack(sibling->_left) && isBlack(sibling->_right)){
            bool isb = isBlack(parent);
            red(sibling);
            black(parent);
            if (isb) afterRemove(parent);
        }else {
            if (isBlack(sibling->_left)){
                this->zag(sibling);
                sibling = parent->_left;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_left);
            this->zig(parent);
        }
    }
}

string RBTree<string>::description(Node<string> *node)const{
    string pString;
    RBNode<string> *n = (RBNode<string> *)node;
//    Node<string> * parent = n->_parent;
//    if (!parent) pString = "_P(NULL)";
//    else pString = "_P(" + parent->_element + ")";
    
    string colorString;
    if (!n->color()) colorString = "R_";
    
    string nString = "(" + n->_element + ")";
    
    return colorString + nString + pString;
}

#pragma mark - template specialization for const char *
template <>
class RBTree<const char *> : public BBST<const char *>{
    
    void afterAdd(Node<const char *> *node) override;
    void afterRemove(Node<const char *> *node) override;
    Node<const char *> *newNode(const char * v, Node<const char *> *parent) override {return new RBNode<const char *>(v, parent);}
    string description(Node<const char *> *node)const override;
    
    RBColor colorOf(Node<const char *> *node) const{ return node ? ((RBNode<const char *> *)node)->color() : Black;}
    bool isRed(Node<const char *> *node) const{return colorOf(node) == Red;}
    bool isBlack(Node<const char *> *node) const{return colorOf(node) == Black;}

    void color(Node<const char *> *node, RBColor color){ if(node) ((RBNode<const char *> *)node)->setColor(color);}
    void red(Node<const char *> *node){color(node, Red);}
    void black(Node<const char *> *node){color(node, Black);}

public:
    RBTree() : RBTree(NULL) {}
    RBTree(int (*comparator)(const char *, const char *)) : BBST<const char *>(comparator){}
};


void RBTree<const char *>::afterAdd(Node<const char *> *child){
    if (child == this->_root) black(child);
    Node<const char *> *parent = child->_parent;
    if (isBlack(parent)) return; // parent == NULL; color == Black;
    
    //parent != NULL
    Node<const char *> *grand = parent->_parent;
    Node<const char *> *uncle = parent->sibling();
    if (colorOf(uncle) != Red){
        red(grand);
        if (parent->isLeft()){
            if (child->isLeft()) { black(parent);}
            else {black(child); this->zag(parent);}
            this->zig(grand);
        } else {
            if (child->isRight()) {black(parent);}
            else {black(child); this->zig(parent);}
            this->zag(grand);
        }
    }else{
        black(parent);
        black(uncle);
        red(grand);
        afterAdd(grand);
    }
}


void RBTree<const char *>::afterRemove(Node<const char *> *node){
    if (colorOf(node) == Red) return;
    
    //度为1
    if (isRed(node)) {black(node); return;}
    
    //叶子结点
    Node<const char *> *parent = node->_parent;
    if (!parent) return;
    
    bool isLeft = parent->_left == NULL || node->isLeft();
    Node<const char *> *sibling = isLeft ? parent->_right : parent->_left;

    if (isLeft){ //node is left, sibling is right
        if (isRed(sibling)){ //sibling == red,使sibling == black
            black(sibling);
            red(parent);
            this->zag(parent);
            sibling = parent->_right; //sibling == black
        }
        //sibling == black
        if (isBlack(sibling->_left) && isBlack(sibling->_right)){ //sibling没有red子节点
            bool isb = isBlack(parent);
            black(parent);
            red(sibling);
            if (isb) afterRemove(parent);
        }else {//sibling 至少一个 red 子节点
            if (isBlack(sibling->_right)){  //left red, RL
                this->zig(sibling);
                sibling = parent->_right;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_right);
            this->zag(parent);
        }
    
    }else {//node is right, sibling is left
        if (isRed(sibling)){
            black(sibling);
            red(parent);
            this->zig(parent);
            sibling = parent->_left;
        }
        
        if (isBlack(sibling->_left) && isBlack(sibling->_right)){
            bool isb = isBlack(parent);
            red(sibling);
            black(parent);
            if (isb) afterRemove(parent);
        }else {
            if (isBlack(sibling->_left)){
                this->zag(sibling);
                sibling = parent->_left;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_left);
            this->zig(parent);
        }
    }
}

string RBTree<const char *>::description(Node<const char *> *node)const{
    string pString;
    RBNode<const char *> *n = (RBNode<const char *> *)node;
//    Node<const char *> * parent = n->_parent;
//    if (!parent) pString = "_P(NULL)";
//    else {
//        pString = parent->_element;
//        pString = "_P(" + pString + ")";
//    }
    
    string colorString;
    if (!n->color()) colorString = "R_";
    
    string nString = n->_element;
    nString = "(" + nString + ")";
    return colorString + nString + pString;
}


#endif /* RBTree_hpp */
