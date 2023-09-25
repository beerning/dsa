//
//  CircleLinkList.hpp
//  CircleLinkList
//
//  Created by berning on 2015/4/16.
//

#ifndef CircleLinkList_hpp
#define CircleLinkList_hpp

#include <iostream>
using namespace std;

template<class T>
class CircleLinkList;

template<class T>
ostream & operator << (ostream &os, const CircleLinkList<T> &list);

template<class T>
class CircleLinkList{
    static const int ELEMENT_NOT_FOUND;
    int _size;
    struct Node{
        T _element;
        Node *_prev;
        Node *_next;
        Node(Node *prev, T element, Node *next) : _prev(prev), _element(element), _next(next){}
    } *_first, *_last, *_current;
    
    void rangeCheck(int idx) const;
    void rangeCheckForAdd(int idx) const;
    void outBounds(int idx) const;
    Node* node(int idx) const{
        rangeCheck(idx);
        if (idx < _size >> 1) {
            Node *node = _first;
            for (int i = 0; i < idx; i++) {
                node = node->_next;
            }
            return node;
        }else{
            Node *node = _last;
            for (int i = _size - 1; i > idx; i--) {
                node = node->_prev;
            }
            return node;
        }
    }

public:

    CircleLinkList() : _size(0), _first(NULL), _last(NULL){};
    
    int  size() const;
    bool isEmpty() const;
    
    void add(T v);
    void insert(T v, int idx);
    T    replace(T v, int idx);
    
    T    valueOf(int idx) const;
    int  indexOf(T v) const;
    bool contains(T v) const;
    
    T    remove(int idx);
    void clear();
    
    void reset();
    void locate(int idx);
    T    next();
    T    remove();
    friend ostream & operator << <>(ostream &os, const CircleLinkList &list);
};

template<class T>
const int CircleLinkList<T>::ELEMENT_NOT_FOUND = -1;

template<class T>
int CircleLinkList<T>::size() const{
    return _size;
}

template<class T>
bool CircleLinkList<T>::isEmpty() const{
    return _size == 0;
}

template<class T>
void CircleLinkList<T>::add(T v){
    insert(v, _size);
}

template<class T>
void CircleLinkList<T>::insert(T v, int idx){
    rangeCheckForAdd(idx);
    if (idx == 0) {//维护四根指针(自己的_prev和_next;  _first和 下一个节点的_prev或_last )
        Node *nd = new Node(NULL, v, _first);
        _first = nd;
        if(idx == _size){ //idx == size 代表0为末尾
            _last = nd;
        }else{  //_size != 0
            _first->_next->_prev = _first;
        }
    }else{
        Node *prev = node(idx - 1);
        Node *n = new Node(prev, v, prev->_next);
        prev->_next = n;
        if (idx == _size) { //末尾插入
            _last = n;
        }else{
            n->_next->_prev = n;
        }
    }
    _first->_prev = _last;
    _last->_next = _first;

    _size++;
}


template<class T>
T CircleLinkList<T>::replace(T v, int idx){
    Node *n = node(idx);
    T old = n->_element;
    n->_element = v;
    return old;
}

template<class T>
T CircleLinkList<T>::valueOf(int idx) const{
    return node(idx)->_element;
}

template<class T>
int CircleLinkList<T>::indexOf(T v) const{
    Node *node = _first;
    for (int i = 0; i < _size; i++) {
        if (node->_element == v) return i;
        node = node->_next;
    }
    return ELEMENT_NOT_FOUND;
}

template<class T>
bool CircleLinkList<T>::contains(T v) const{
    return indexOf(v) != ELEMENT_NOT_FOUND;
}

template<class T>
T CircleLinkList<T>::remove(int idx){
    rangeCheck(idx);
//    Node *n = _first;
//    if (idx == 0) { //_size > idx(0), (i.e _size = 1, 2, 3...)
//        _first = _first->_next;
//    }else{ //_size > idx(1,2,3...), (i.e _size = 2, 3, 4...)
//        Node *prev = node(idx - 1);
//        n = prev->_next;
//        prev->_next = n->_next;
//        if (idx == _size - 1) { //末尾删除
//            _last = prev;
//        }else{
//            n->_next->_prev = prev;
//        }
//    }
//    _first->_prev = _last;
//    _last->_next = _first;

    
    Node *n = node(idx);
    Node *prev = n->_prev;
    Node *next = n->_next;

    if (prev == _last) {
        _first = next;
    }else{
        prev->_next = next;
    }

    if(next == _first){
        _last = prev;
    }else{
        next->_prev = prev;
    }

    _last->_next = _first;
    _first->_prev = _last;

    _size--;
    T del = n->_element;
    delete n;
    return del;
}

template<class T>
void CircleLinkList<T>::clear(){
    int idx = _size - 1;
    while (idx >= 0)
        remove(idx--);
}

template<class T>
void CircleLinkList<T>::rangeCheck(int idx) const{
    if (idx < 0 || idx >= _size) {
        outBounds(idx);
    }
}

template<class T>
void CircleLinkList<T>::rangeCheckForAdd(int idx) const{
    if (idx < 0 || idx > _size) {
        outBounds(idx);
    }
}

template <class T>
void CircleLinkList<T>::outBounds(int idx) const{
    string s = "\"Index ";
    s.append(to_string(idx));
    s.append(" is out of bounds\". Exception:\n");
    cout << s;
    throw s;
}

template<class T>
void CircleLinkList<T>::reset() {
    _current = _first;
}

template<class T>
void CircleLinkList<T>::locate(int idx){
    rangeCheck(idx);
    _current = node(idx);
}

template<class T>
T CircleLinkList<T>::next(){
    if (!_current) return NULL;
    _current = _current->_next;
    return _current->_element;
}

template<class T>
T CircleLinkList<T>::remove(){
    if (!_current) return NULL;
    Node *next = _current->_next;
    T element = _current->_element;
    remove(indexOf(element));
    if (_size == 0) {
        _current = NULL;
    }else{
        _current = next;
    }
    return element;
}


template<class T>
ostream & operator << (ostream &os, const CircleLinkList<T> &list){
    os << "size = " << list._size << ", [";
        
    int size = list._size;
    for (int i = 0; i < size ; i++) {
        if (i > 0) {
            os << ", ";
        }
        
        if (list.node(i)->_prev == list._last) {
            os << list.node(i)->_prev->_element << "(last)<-";
        }else{
            os << list.node(i)->_prev->_element << "<-";
        }

        if ( list.node(i) == list._first &&  list.node(i) == list._last){
            os << list.valueOf(i) << "(first, last)";
        }else if(list.node(i) == list._first){
            os << list.valueOf(i) << "(first)";
        }else if(list.node(i) == list._last){
            os << list.valueOf(i) << "(last)";
        }
        else{
            os << list.valueOf(i);
        }
        
        if (list.node(i)->_next == list._first) {
            os << "->" << list.node(i)->_next->_element << "(first)";
        }else{
            os << "->" << list.node(i)->_next->_element;
        }

    }
    
    os << "]";
    return os;
}


#endif /* CircleCircleLinkList_hpp */
