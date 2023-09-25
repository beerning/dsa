//
//  LinkedHashMap.hpp
//  Map
//
//  Created by berning on 2015/7/13.
//

#ifndef LinkedHashMap_hpp
#define LinkedHashMap_hpp

#include "HashMap.hpp"

class LinkedHashMapNode : public HashMapNode{
public:
    LinkedHashMapNode *_prev;
    LinkedHashMapNode *_next;
    LinkedHashMapNode(id key, id value, TreeNode parent) : _prev(NULL), _next(NULL), HashMapNode(key, value, parent){}
};

class LinkedHashMap : public HashMap{
    using LinkedNode = LinkedHashMapNode *;
    
    LinkedNode _heading;
    LinkedNode _tail;
    
protected:
    TreeNode newNode(id key, id value, TreeNode parent) override{
        LinkedNode n = new LinkedHashMapNode(key, value, parent);
        if (!_heading){
            _heading = _tail = n;
        }else{
            _tail->_next = n;
            n->_prev = _tail;
            _tail = n;
        }
        return n;
    }
    
    void afterRemove(TreeNode tn1, TreeNode tn2) override;
public:
    LinkedHashMap() : _heading(NULL), _tail(NULL), HashMap(){}
    bool containsValue(id value) const override;
    void traversal() const override;
};


bool LinkedHashMap::containsValue(id value) const{
    LinkedNode n = _heading;
    while (n) {
        if (Object::equals(n->_value, value)) return true;
        n = n->_next;
    }
    return false;
}

void LinkedHashMap::traversal() const{
    cout << "{";
    LinkedNode n = _heading;
    if (!n) {
        cout << "}" << endl;
        return;
    }
    cout << endl;
    while (n) {
        string s;
        //n
        id nk =  n->_key;
        id nv = n->_value;
        string nks = nk ? nk->toString() : "NULL";
        string nvs = nv ? nv->toString() : "NULL";
        s = s + nks + " : " + nvs;
        n = n->_next;
        if (n) s = s + ",";
        cout << "\t" << s << endl;
    }
    cout << "}" << endl;
}

#pragma mark - Private
void LinkedHashMap::afterRemove(TreeNode tn1, TreeNode tn2){
    LinkedNode n1 = (LinkedNode)tn1;
    LinkedNode n2 = (LinkedNode)tn2;
    
    //exchange prev/next
    if (n1 != n2){
        LinkedNode temp = n1->_prev;
        n1->_prev = n2->_prev;
        n2->_prev = temp;
        if (n1->_prev){
            n1->_prev->_next = n1;
        }else{
            _heading = n1;
        }
        
        if (n2->_prev){
            n2->_prev->_next = n2;
        }else{
            _heading = n2;
        }

        temp = n1->_next;
        n1->_next = n2->_next;
        n2->_next = temp;
        if (n1->_next){
            n1->_next->_prev = n1;
        }else{
            _tail = n1;
        }
        
        if (n2->_next){
            n2->_next->_prev = n2;
        }else{
            _tail = n2;
        }
    }
    
    //adjust
    LinkedNode prev = n2->_prev;
    LinkedNode next = n2->_next;
    
    if (prev){
        prev->_next = next;
    }else{
        _heading = next;
    }
    
    if (next){
        next->_prev = prev;
    }else{
        _tail = prev;
    }
}

#endif /* LinkedHashMap_hpp */
