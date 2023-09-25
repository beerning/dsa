//
//  TreeMap.hpp
//  Map
//
//  Created by berning on 2015/5/24.
//

#ifndef TreeMap_hpp
#define TreeMap_hpp

#include "Map.hpp"
#include <queue>

class TreeMap : public Map<id, id>{    
    int _size;
    TreeNode _root;
    
    int (*_comparator)(id, id);
    
    //bst
    TreeNode successor(TreeNode node) const;
    int compare(id k1, id k2) const;
    TreeNode  node(id key) const;
    void elementNotNullCheck(id key) const;
    
    void traversal(TreeNode node, string &sb, string prefix) const;
    
    //bbst
    void afterAdd(TreeNode node);
    void afterRemove(TreeNode node);
    
    void zig(TreeNode grand);
    void zag(TreeNode grand);
    void zigzaged(TreeNode grand, TreeNode parent, TreeNode child);
    
    //rb
    MapColor colorOf(TreeNode node) const{ return node ? node->color() : MapBlack;}
    bool isRed(TreeNode node) const{return colorOf(node) == MapRed;}
    bool isBlack(TreeNode node) const{return colorOf(node) == MapBlack;}

    void color(TreeNode node, MapColor color){ if(node) node->setColor(color);}
    void red(TreeNode node){color(node, MapRed);}
    void black(TreeNode node){color(node, MapBlack);}
    
public:
    TreeMap() : TreeMap(NULL) {}
    TreeMap(int (*comparator)(id, id)) : _root(NULL), _size(0), _comparator(comparator) {}

    int size() const override;
    bool isEmpty() const override;
    void clear() override;
    
    id put(id key, id value) override;
    id get(id key) const override;
    id remove(id key) override;
    
    bool containsKey(id key) const override;
    bool containsValue(id value) const override;
    void traversal() const override;
};

#pragma mark - Public
int TreeMap::size() const{
    return _size;
}

bool TreeMap::isEmpty() const{
    return _size == 0;
}

void TreeMap::clear(){
    while (_size) {
        TreeNode root = _root;
        remove(root->_key);
    }
}

id TreeMap::put(id key, id value){
    elementNotNullCheck(key);
    if (!_root) {
        _root = new MapNode<id, id>(key, value, NULL);
        _size++;
        afterAdd(_root);
        return value;
    }
    
    TreeNode n = _root;
    TreeNode parent = _root;
    int cmp = 0;
    while (n) {
        cmp = compare(key, n->_key);
        parent = n;
        if (cmp < 0) {
            n = n->_left;
        }else if (cmp > 0){
            n = n->_right;
        }else{
            n->_key = key;
            n->_value = value;
            return value;
        }
    }
    
    TreeNode node = new MapNode<id, id>(key, value, parent);
    if (cmp < 0) {
        parent->_left = node;
    }else{
        parent->_right = node;
    }
    _size++;
    
    afterAdd(node);
    return value;
}

id TreeMap::get(id key) const{
    TreeNode n = node(key);
    
    if (!n) return NULL;
    return n->_value;
}

id TreeMap::remove(id key){
    TreeNode n = node(key);
    if(!n) return NULL;
    
    id v = n->_value;
    if (n->hasTwins()) {//度为2的节点
        TreeNode suc = successor(n);
        n->_key = suc->_key;
        n->_value = suc->_value;
        n = suc;
    }//度为2的后继节点的度必为0 或 1
    
    //degreen 1 or 0
    TreeNode leaf = n->_left ? n->_left : n->_right;
    if (leaf) {//degreen == 1
        leaf->_parent = n->_parent;
        
        if (!n->_parent) { //root
            _root = leaf;
        }else if(n == n->_parent->_left){
            n->_parent->_left = leaf;
        }else{  //_right
            n->_parent->_right = leaf;
        }
        afterRemove(leaf);
    }else{//degreen == 0
        if (!n->_parent){ //only root
            _root = NULL;
        }else if (n == n->_parent->_left) {//left
            n->_parent->_left = NULL;
        }else{//right
            n->_parent->_right = NULL;
        }
        afterRemove(n);
    }
    _size--;
    delete n;
    return v;
}

bool TreeMap::containsKey(id key) const{
    return node(key) != NULL;
}

bool TreeMap::containsValue(id value) const{
    queue<TreeNode> q;
    q.push(_root);
    while (!q.empty()) {
        TreeNode n = q.front();
        q.pop();
        
        if (n->_value == value) return true;
        if (n->_left) q.push(n->_left);
        if (n->_right) q.push(n->_right);
    }
    
    return false;
}

void TreeMap::traversal() const{
    string s;
    traversal(_root, s, "");
    
    cout << "size = " << _size << endl;
    cout << s << endl;
}

void TreeMap::traversal(TreeNode node, string &sb, string prefix) const{
    if (!node) return;
    traversal(node->_left, sb, prefix + "L---");
    sb.append(prefix).append(node->_key->toString()).append(":").append(node->_value->toString()).append("\n");
    traversal(node->_right, sb, prefix + "R---");
}

#pragma mark - Private
void TreeMap::afterAdd(TreeNode child){
    TreeNode parent = child->_parent;
    if (!parent){
        black(child);
        return;
    }
    if (isBlack(parent)) return; // parent == NULL; color == MapBlack;
    
    //parent != NULL
    TreeNode grand = parent->_parent;
    TreeNode uncle = parent->sibling();
    if (colorOf(uncle) != MapRed){
        red(grand);
        if (parent->isLeft()){
            if (child->isLeft()) { black(parent);}
            else {black(child); zag(parent);}
            zig(grand);
        } else {
            if (child->isRight()) {black(parent);}
            else {black(child); zig(parent);}
            zag(grand);
        }
    }else{
        black(parent);
        black(uncle);
        red(grand);
        afterAdd(grand);
    }
}

void TreeMap::afterRemove(TreeNode node){
    //度1的子node为red 或被删除的node为red
    if (isRed(node)) {black(node); return;}
    
    //root
    TreeNode parent = node->_parent;
    if (!parent) return;
        
    //node is black
    bool isLeft = parent->_left == NULL || node->isLeft();
    TreeNode sibling = isLeft ? parent->_right : parent->_left;

    if (isLeft){ //node is left, sibling is right
        if (isRed(sibling)){ //sibling == red,使sibling == black
            black(sibling);
            red(parent);
            zag(parent);
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
                zig(sibling);
                sibling = parent->_right;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_right);
            zag(parent);
        }
    
    }else {//node is right, sibling is left
        if (isRed(sibling)){
            black(sibling);
            red(parent);
            zig(parent);
            sibling = parent->_left;
        }
        
        if (isBlack(sibling->_left) && isBlack(sibling->_right)){
            bool isb = isBlack(parent);
            red(sibling);
            black(parent);
            if (isb) afterRemove(parent);
        }else {
            if (isBlack(sibling->_left)){
                zag(sibling);
                sibling = parent->_left;
            }
            color(sibling, colorOf(parent));
            black(parent);
            black(sibling->_left);
            zig(parent);
        }
    }
}

void TreeMap::zig(TreeNode grand){//LL
    TreeNode parent = grand->_left;
    TreeNode child = parent->_right;
    
    grand->_left = child;
    parent->_right = grand;
    zigzaged(grand, parent, child);
}

void TreeMap::zag(TreeNode grand){//RR
    TreeNode parent = grand->_right;
    TreeNode child = parent->_left;
    
    grand->_right = child;
    parent->_left = grand;
    zigzaged(grand, parent, child);
}

void TreeMap::zigzaged(TreeNode grand, TreeNode parent, TreeNode child){
    parent->_parent = grand->_parent;
    
    if (grand->isLeft()) grand->_parent->_left = parent;
    else if (grand->isRight())grand->_parent->_right = parent;
    else _root = parent;
    
    grand->_parent = parent;
    
    if (child) child->_parent = grand;
}

TreeNode TreeMap::successor(TreeNode node) const{
    if (!node) return NULL;
    
    TreeNode p = node->_right;
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

void TreeMap::elementNotNullCheck(id key) const{
    try {
        if (!key) throw "Warning: Key is null.";
    } catch (const char* e) {
        cout << e << endl;
    }
}

int TreeMap::compare(id k1, id k2) const{
    if (_comparator) return _comparator(k1, k2);
    int ret = 0;
    if (strcmp(k1->getClass(), k2->getClass()) == 0){
        ret = k1->compareTo(k2);
    }else if (strcmp(k1->superClass(), Number_t) == 0 && strcmp(k2->superClass(), Number_t) == 0){
        ret = k1->compareTo(k2);
    }else{
        int h1 = k1->hashCode();
        int h2 = k2->hashCode();
        ret = h1 > h2 ? 1 : h1 < h2 ? -1 : 0;
    }
    return ret;
}

TreeNode TreeMap::node(id key) const{
    TreeNode n = _root;
    int cmp = 0;
    while (n) {
        cmp = compare(key, n->_key);
        if (cmp < 0) n = n->_left;
        else if(cmp > 0) n = n->_right;
        else return n;
    }
    return NULL;
}

#endif /* TreeMap_hpp */
