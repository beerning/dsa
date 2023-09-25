//
//  LinkList.h
//  LinkList
//
//  Created by berning on 2015/4/13.
//

#ifndef SingleLinkList_h
#define SingleLinkList_h

#include <iostream>
using namespace std;

template<class T>
class SingleLinkList;

template<class T>
ostream & operator<<(ostream &os, const SingleLinkList<T> &list);

template<class T>
class SingleLinkList{
    static const int ELEMENT_NOT_FOUND;
    int _size;
    
    struct Node{
        T _element;
        Node *_next;
        Node(T element, Node *next);
    } *_first;
    
    void rangeCheck(int idx) const;
    void rangeCheckForAdd(int idx) const;
    void outBounds(int idx) const;
    Node* node(int idx) const{
        rangeCheck(idx);
        Node *node = _first;
        for (int i = 0; i < idx; i++) {
            node = node->_next;
        }
        return node;
    }
public:

    SingleLinkList(): _size(0), _first(NULL){}
    int  size() const;
    bool isEmpty() const;
    
    void add(T v);
    void insert(T v, int idx);
    T  replace(T v, int idx);
    
    T  valueOf(int idx) const;
    int  indexOf(T v) const;
    bool contains(T v) const;
    
    T  remove(int idx);
    void clear();

    friend ostream & operator<< <>(ostream &os, const SingleLinkList<T> &list);
};

template<class T>
const int SingleLinkList<T>::ELEMENT_NOT_FOUND = -1;

template<class T>
SingleLinkList<T>::Node::Node(T element, Node *next){
    _element = element;
    _next = next;
}

template<class T>
int SingleLinkList<T>::size() const{
    return _size;
}

template<class T>
bool SingleLinkList<T>::isEmpty() const{
    return _size == 0;
}

template<class T>
void SingleLinkList<T>::add(T v){
    insert(v, _size);
}

template<class T>
void SingleLinkList<T>::insert(T v, int idx){
    rangeCheckForAdd(idx);
    if (idx == 0) {
        _first = new Node(v, _first);
    }else{
        Node *prev = node(idx - 1);
        prev->_next = new Node(v, prev->_next);
    }
    _size++;
}

template<class T>
T SingleLinkList<T>::replace(T v, int idx){
    rangeCheck(idx);
    Node *n = node(idx);
    T old = n->_element;
    n->_element = v;
    return old;
}

template<class T>
T SingleLinkList<T>::valueOf(int idx) const{
    rangeCheck(idx);
    Node *n = node(idx);
    return n->_element;
}

template<class T>
int SingleLinkList<T>::indexOf(T v) const{
    Node *node = _first;
    for (int i = 0; i < _size; i++) {
        if (node->_element == v) return i;
        node = node->_next;
    }
    return ELEMENT_NOT_FOUND;
}

template<class T>
bool SingleLinkList<T>::contains(T v) const{
    return indexOf(v) != ELEMENT_NOT_FOUND;
}

template<class T>
T SingleLinkList<T>::remove(int idx){
    rangeCheck(idx);
    Node *n = _first;
    if (idx == 0) {
        _first = _first->_next;
    }else{
        Node *prev = node(idx - 1);
        n = prev->_next;
        prev->_next = n->_next;
    }
    _size--;
    T del = n->_element;
    delete n;
    return del;
}

template<class T>
void SingleLinkList<T>::clear(){
    int idx = _size - 1;
    while (idx >= 0)
        remove(idx--);
}

template<class T>
void SingleLinkList<T>::rangeCheck(int idx) const{
    if (idx < 0 || idx >= _size) {
        outBounds(idx);
    }
}

template<class T>
void SingleLinkList<T>::rangeCheckForAdd(int idx) const{
    if (idx < 0 || idx > _size) {
        outBounds(idx);
    }
}

template <class T>
void SingleLinkList<T>::outBounds(int idx) const{
    string s = "\"Index ";
    s.append(to_string(idx));
    s.append(" is out of bounds\". Exception:\n");
    cout << s;
    throw s;
}


template<class T>
ostream& operator << (ostream &os, const SingleLinkList<T> &list){
    os << "size = " << list._size << ", [";
    
    int size = list._size;
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            os << ", ";
        }
                
        if(list.node(i) == list._first){
            os << list.valueOf(i) << "(first)";
        }else{
            os << list.valueOf(i);
        }
        
        if (list.node(i)->_next == NULL) {
            os << "->" << "NULL";
        }else{
            os << "->" << list.node(i)->_next->_element;
        }

    }
    os << "]";
    return os;
}

#endif /* SingleLinkList_h */
