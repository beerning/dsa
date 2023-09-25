//
//  HashMap.hpp
//  Map
//
//  Created by berning on 2015/5/30.
//

#ifndef HashMap_hpp
#define HashMap_hpp

#include "Map.hpp"
#include <queue>

class HashMapNode : public MapNode<id, id>{
public:
    int _hash;
    HashMapNode(id key, id value, TreeNode parent) : MapNode<id, id>(key, value, parent){
        int h = key ? key->hashCode() : 0;
        _hash = h ^ (h >> 16 & 0xffff);
    }
};

class HashMap : public Map<id, id>{
    using HashNode = HashMapNode *;
    
    int _size;
    static const int DEFAULT_CAPACITY = 1 << 4;
    constexpr static const float DEFAULT_LOAD_FACTOR = 0.75f;   //装填因子
    TreeNode *_table = new TreeNode[DEFAULT_CAPACITY]{};
    unsigned _length = DEFAULT_CAPACITY;
    
    //bst
    TreeNode successor(TreeNode node) const;
    TreeNode node(id key) const;
    TreeNode node(TreeNode node, id key) const;
    void elementNotNullCheck(id key) const;
        
    //bbst
    void afterPut(TreeNode node);
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
    
    //function
    int index (id obj) const;
    int hash (id key) const;
    
    void resize();
    void move(TreeNode aNode);
    
protected:
    virtual TreeNode newNode(id key, id value, TreeNode parent){
        return  new HashMapNode(key, value, parent);
    }
    virtual void afterRemove(TreeNode n1, TreeNode n2){}
public:
    HashMap() :  _size(0) {}

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

int HashMap::size() const{
    return _size;
}

bool HashMap::isEmpty() const{
    return _size == 0;
}

void HashMap::clear(){
    if (_size == 0) return;
    
    for (int i = 0; i < _length; i++){
        TreeNode root = _table[i];
        while (root) {
            remove(root->_key);
            root = _table[i];
        }
    }
}

id HashMap::put(id key, id value){
    resize();
    
    elementNotNullCheck(key);

    int idx = index(key);
    TreeNode root = _table[idx];
    if (!root) {
        root = newNode(key, value, NULL);
        _size++;
        _table[idx] = root;
        afterPut(root);
        return value;
    }
    
    TreeNode n = root;
    TreeNode parent = root;
    id  k1 = key;
    int h1 = hash(k1);
    
    int cmp = 0;
    bool searched = false;
    TreeNode res = NULL;
    
    while (n) {
        parent = n;
        id  k2 = n->_key;
        int h2 = ((HashNode)n)->_hash;

        if (h1 > h2) cmp = 1;
        else if (h1 < h2) cmp = -1;
        else if (Object::equals(k1, k2)) cmp = 0;
        else if (k1 != NULL && k2 != NULL
                 && strcmp(k1->getClass(), k2->getClass()) == 0
                 && (cmp = k1->compareTo(k2)) != 0){
        }else if (searched){
            cmp = k1 > k2 ? 1 : -1;
        }else {
            if ((n->_right && (res = node(n->_right, k1)) != NULL)
                      || (n->_left && (res = node(n->_left, k1)) != NULL)){
                n = res;
                cmp = 0;
            }else{
                searched = true;
                cmp = k1 > k2 ? 1 : -1;
            }
        }

        if (cmp < 0) n = n->_left;
        else if (cmp > 0) n = n->_right;
        else{
            n->_key = key;
            n->_value = value;
            ((HashNode)n)->_hash = h1;
            return value;
        }
    }
    
    TreeNode node = newNode(key, value, parent);
    if (cmp < 0) {
        parent->_left = node;
    }else{
        parent->_right = node;
    }
    _size++;
    
    afterPut(node);
    return value;
}

id HashMap::get(id key) const{
    TreeNode n = node(key);
    return n ? n->_value : NULL;
}

id HashMap::remove(id key){
    TreeNode n = node(key);
    if(!n) return NULL;
    
    TreeNode m = n;
    
    id v = n->_value;
    int idx = index(key);
    if (n->hasTwins()) {//度为2的节点
        TreeNode suc = successor(n);
        n->_key = suc->_key;
        n->_value = suc->_value;
        ((HashNode)n)->_hash = ((HashNode)suc)->_hash;
        n = suc;
    }//度为2的后继节点的度必为0 或 1
    
    //degreen 1 or 0
    TreeNode leaf = n->_left ? n->_left : n->_right;
    TreeNode parent = n->_parent;
    if (leaf) {//degreen == 1
        leaf->_parent = parent;
        
        if (!parent) { //root
            _table[idx] = leaf;
        }else if(n == parent->_left){
            parent->_left = leaf;
        }else{  //_right
            parent->_right = leaf;
        }
        afterRemove(leaf);
    }else{//degreen == 0
        if (!parent){ //only root
            _table[idx] = NULL;
        }else if (n == parent->_left) {//left
            parent->_left = NULL;
        }else{//rightx
            parent->_right = NULL;
        }
        afterRemove(n);
    }
    
    afterRemove(m, n);
    _size--;
    delete n;
    return v;
}

bool HashMap::containsKey(id key) const{
    return node(key) != NULL;
}

bool HashMap::containsValue(id value) const{
    queue<TreeNode> queue;
    bool res = false;
    for (int i = 0; i < _length; i++){
        TreeNode root = _table[i];
        if (!root) continue;
        queue.push(root);
        while (!queue.empty()){
            TreeNode n = queue.front();
            queue.pop();
            if (Object::equals(n->_value, value))
                res = true;
            
            if (n->_left)
                queue.push(n->_left);
            if (n->_right)
                queue.push(n->_right);
        }
    }
    return res;
}

void HashMap::traversal() const{
    
    queue<TreeNode> queue;

    for (int i = 0; i < _length; i++){
        cout << "idx" << i << " = {";

        TreeNode root = _table[i];
        if (!root) {
            cout << "}" << endl;
            continue;
        }
        cout << endl;
        queue.push(root);

        while (!queue.empty()){
            TreeNode n = queue.front();
            queue.pop();

            string s = n->color() == MapRed ? "R_" : "";
            //n
            id nk =  n->_key;
            id nv = n->_value;
            string nks = nk ? nk->toString() : "NULL";
            string nvs = nv ? nv->toString() : "NULL";
            s = s + nks + " : " + nvs;
            //p
            TreeNode p = n->_parent;
            if (p){
                id pk =  p->_key;
                id pv = p->_value;
                string pks = pk ? pk->toString() : "NULL";
                string pvs = pv ? pv->toString() : "NULL";

                s = s + "_P(" + pks + " : " + pvs + ")";
            }else s = s + "_P(NULL)";
            

            if (n->_left)
                queue.push(n->_left);
            if (n->_right)
                queue.push(n->_right);

            if (!queue.empty()) s = s + ",";
            cout << "\t" << s << endl;;

        }
        cout << "}" << endl;
    }
}

#pragma mark - Private
int HashMap::index(id obj) const{
    return hash(obj) & (_length - 1);
}

int HashMap::hash(id obj) const{
    if (obj == NULL) return 0;
    int h = obj->hashCode();
    return h ^ (h >> 16 & 0xffff);
}

void HashMap::resize() {
    if (_size * 1.0 / _length <= DEFAULT_LOAD_FACTOR) return;

    TreeNode *t = _table;
    unsigned len = _length;
    _length = _length << 1;
    _table = new TreeNode[_length]{};
    
    queue<TreeNode> queue;
    for (int i = 0; i < len; i++){
        TreeNode root = t[i];
        if (!root) continue;
        
        queue.push(root);
        while (!queue.empty()) {
            TreeNode n = queue.front();
            queue.pop();
            
            if (n->_left) queue.push(n->_left);
            if (n->_right) queue.push(n->_right);
           
            move(n);
        }
    }
    delete[] t;
}

void HashMap::move(TreeNode aNode){
    aNode->_left = NULL;
    aNode->_right = NULL;
    aNode->_parent = NULL;
    aNode->setColor(MapRed);
    
    int idx = index(aNode->_key);
    TreeNode root = _table[idx];
    if (!root) {
        _table[idx] = aNode;
        afterPut(aNode);
        return;
    }
    
    TreeNode n = root;
    TreeNode parent = root;
    id  k1 = aNode->_key;
    int h1 = ((HashNode)aNode)->_hash;
    
    int cmp = 0;
    while (n) {
        parent = n;
        id  k2 = n->_key;
        int h2 = ((HashNode)n)->_hash;

        if (h1 > h2) cmp = 1;
        else if (h1 < h2) cmp = -1;
        else if (k1 != NULL && k2 != NULL
                 && strcmp(k1->getClass(), k2->getClass()) == 0
                 && (cmp = k1->compareTo(k2)) != 0){
        }else{
            cmp = k1 > k2 ? 1 : -1;
        }

        if (cmp < 0) n = n->_left;
        else n = n->_right;
    }
    
    if (cmp < 0) {
        parent->_left = aNode;
    }else{
        parent->_right = aNode;
    }
    aNode->_parent = parent;
    afterPut(aNode);
}

void HashMap::afterPut(TreeNode child){
    TreeNode parent = child->_parent;
    if (parent == NULL) {
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
        afterPut(grand);
    }
}

void HashMap::afterRemove(TreeNode node){
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

void HashMap::zig(TreeNode grand){//LL
    TreeNode parent = grand->_left;
    TreeNode child = parent->_right;
    
    grand->_left = child;
    parent->_right = grand;
    zigzaged(grand, parent, child);
}

void HashMap::zag(TreeNode grand){//RR
    TreeNode parent = grand->_right;
    TreeNode child = parent->_left;
    
    grand->_right = child;
    parent->_left = grand;
    zigzaged(grand, parent, child);
}

void HashMap::zigzaged(TreeNode grand, TreeNode parent, TreeNode child){
    parent->_parent = grand->_parent;
    
    if (grand->isLeft()) grand->_parent->_left = parent;
    else if (grand->isRight())grand->_parent->_right = parent;
    else _table[index(grand->_key)] = parent;

    grand->_parent = parent;
    
    if (child) child->_parent = grand;
}

TreeNode HashMap::successor(TreeNode node) const{
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

void HashMap::elementNotNullCheck(id key) const{
    try {
        if (!key) throw "Warning: Key is null.";
    } catch (const char* e) {
        cout << e << endl;
    }
}

TreeNode HashMap::node(id key) const{
    TreeNode root = _table[index(key)];
    return root ? node(root, key) : NULL;
}


TreeNode HashMap::node(TreeNode n, id k1) const{
    int h1 = hash(k1);
    int cmp = 0;
    TreeNode res = NULL;
    
    while (n) {
        id k2 = n->_key;
        int h2 = ((HashNode)n)->_hash;
        
        if (h1 > h2) n = n->_right;
        else if (h1 < h2) n = n->_left;
        else if (Object::equals(k1, k2)) return n;
        else if (k1 != NULL && k2 != NULL
                 && strcmp(k1->getClass(), k2->getClass()) == 0
                 && (cmp = k1->compareTo(k2)) != 0)
            n = cmp > 0 ? n->_right : n->_left;
        else if (n->_right && (res = node(n->_right, k1)) != NULL)
            return res;
        else n = n->_left;
    }
    return NULL;
}


#endif /* HashMap_hpp */
