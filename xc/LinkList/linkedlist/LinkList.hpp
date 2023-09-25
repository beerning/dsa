//
//  LinkList.h
//  LinkList
//
//  Created by berning on 2015/4/13.
//

#ifndef LinkList_h
#define LinkList_h

#include <iostream>
using namespace std;

template<class T>
class LinkList;

template<class T>
ostream & operator << (ostream &os, const LinkList<T> &list);

template<class T>
class LinkList{
    static const int ELEMENT_NOT_FOUND;
    int _size;
    struct Node{
        T _element;
        Node *_prev;
        Node *_next;
        Node(Node *prev, T element, Node *next) : _prev(prev), _element(element), _next(next){}
    } *_first, *_last;
    
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

    LinkList() : _size(0), _first(NULL), _last(NULL){};
    
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
    
    friend ostream & operator << <>(ostream &os, const LinkList &list);
};

template<class T>
const int LinkList<T>::ELEMENT_NOT_FOUND = -1;

template<class T>
int LinkList<T>::size() const{
    return _size;
}

template<class T>
bool LinkList<T>::isEmpty() const{
    return _size == 0;
}

template<class T>
void LinkList<T>::add(T v){
    insert(v, _size);
}

template<class T>
void LinkList<T>::insert(T v, int idx){
    rangeCheckForAdd(idx);
    if (idx == 0) {//维护四根指针(自己的_prev和_next;  _first和 下一个节点的_prev或_last )
        //_first = new Node(NULL, v, _first);
        Node* nd = new Node(NULL, v, _first);
        _first = nd;
        if(idx == _size){ //idx == _size 代表0为末尾
            //_last = _first;   //msvc编译_last指向nullptr
            _last = nd;
        }else{
            _first->_next->_prev = _first;
        }
    }else{
        Node *prev = node(idx - 1);
        Node *n = new Node(prev, v, prev->_next);
        prev->_next = n;
        if (idx == _size) { //idx == 末尾
            _last = n;
        }else{
            n->_next->_prev = n;
        }
    }
    _size++;
}


template<class T>
T LinkList<T>::replace(T v, int idx){
    Node *n = node(idx);
    T old = n->_element;
    n->_element = v;
    return old;
}

template<class T>
T LinkList<T>::valueOf(int idx) const{
    return node(idx)->_element;
}

template<class T>
int LinkList<T>::indexOf(T v) const{
    Node *node = _first;
    for (int i = 0; i < _size; i++) {
        if (node->_element == v) return i;
        node = node->_next;
    }
    return ELEMENT_NOT_FOUND;
}

template<class T>
bool LinkList<T>::contains(T v) const{
    return indexOf(v) != ELEMENT_NOT_FOUND;
}

template<class T>
T LinkList<T>::remove(int idx){
    rangeCheck(idx);
//    Node *n = _first;
//    if (idx == 0) { //_size > idx(0), (i.e _size = 1, 2, 3...)
//        _first = _first->_next;
//        if (idx == _size - 1) { //只有一个元素，idx == 0为末尾
//            _last = _first;
//        }else{
//            _first->_prev = NULL;
//        }
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
    
    Node *n = node(idx);
    Node *prev = n->_prev;
    Node *next = n->_next;
    
    if (prev == NULL) {
        _first = next;
    }else{
        prev->_next = next;
    }
    
    if(next == NULL){
        _last = prev;
    }else{
        next->_prev = prev;
    }
    
    _size--;
    T del = n->_element;
    delete n;
    return del;
}

template<class T>
void LinkList<T>::clear(){
    int idx = _size - 1;
    while (idx >= 0)
        remove(idx--);
}

template<class T>
void LinkList<T>::rangeCheck(int idx) const{
    if (idx < 0 || idx >= _size) {
        outBounds(idx);
    }
}

template<class T>
void LinkList<T>::rangeCheckForAdd(int idx) const{
    if (idx < 0 || idx > _size) {
        outBounds(idx);
    }
}

template <class T>
void LinkList<T>::outBounds(int idx) const{
    string s = "\"Index ";
    s.append(to_string(idx));
    s.append(" is out of bounds\". Exception:\n");
    cout << s;
    throw s;
}

template<class T>
ostream & operator << (ostream &os, const LinkList<T> &list){
    os << "size = " << list._size << ", [";
        
    int size = list._size;
    for (int i = 0; i < size ; i++) {
        if (i > 0) {
            os << ", ";
        }
        
        if (list.node(i)->_prev == NULL) {
            os << "NULL" << "<-";
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
        
        if (list.node(i)->_next == NULL) {
            os << "->" << "NULL";
        }else{
            os << "->" << list.node(i)->_next->_element;
        }

    }
    
    os << "]";
    return os;
}

#endif /* LinkList_h */
