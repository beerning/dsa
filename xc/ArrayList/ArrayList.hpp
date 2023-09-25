//
//  ArrayList.hpp
//  ds
//
//  Created by berning on 2015/4/13.
//

#ifndef ArrayList_hpp
#define ArrayList_hpp

#include <iostream>
using namespace std;

template<class T>
class ArrayList;

template<class T>
ostream & operator<<(ostream &os, const ArrayList<T> &list);

template<class T>
class ArrayList{
    static const int ELEMENT_NOT_FOUND = -1;
    static const int DEFAULT_CAPACITY = 10;
    int _size;
    int _capacity;
    T *_arr;
    T INIT_VALUE;
    void rangeCheck(int idx) const;
    void rangeCheckForAdd(int idx) const;
    void outBounds(int idx) const;
    void ensureCapacity(int size);
    void optimize();
public:
    ArrayList();
    ArrayList(int capacity);
    ~ArrayList();
    
    int  size() const;
    bool isEmpty() const;
    
    void add(T v);
    void insert(T v, int idx);
    T replace(T v, int idx);
    
    T  valueOf(int idx) const;
    int  indexOf(T v) const;
    bool contains(T v) const;
    
    T  remove(int idx);
    void clear();
    
    friend ostream & operator<< <>(ostream &os, const ArrayList<T> &list);
    
};

template <class T>
ArrayList<T>::ArrayList(int capacity){
    _size = 0;
    _capacity = (capacity < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : capacity;
    _arr = new T[_capacity]{};
    INIT_VALUE = _arr[0];
}

template <class T>
ArrayList<T>::~ArrayList(){
    delete []_arr;
}

template <class T>
ArrayList<T>::ArrayList() : ArrayList(DEFAULT_CAPACITY){}

template <class T>
int ArrayList<T>::size() const{
    return _size;
}

template <class T>
bool ArrayList<T>::isEmpty() const{
    return _size == 0;
}

template <class T>
void ArrayList<T>::add(T v){
    insert(v, _size);
}

template <class T>
void ArrayList<T>::insert(T v, int idx){
    rangeCheckForAdd(idx);
    ensureCapacity(_size);
    int i = _size - 1;
    while (i >= idx) {
        _arr[i+1] = _arr[i];
        i--;
    }
    _arr[idx] = v;
    _size++;
}

template <class T>
T ArrayList<T>::replace(T v, int idx){
    rangeCheck(idx);
    T old = valueOf(idx);
    _arr[idx] = v;
    return old;
}

template <class T>
T ArrayList<T>::valueOf(int idx) const{
    rangeCheck(idx);
    return _arr[idx];
}

template <class T>
int ArrayList<T>::indexOf(T v) const{
    for (int i = 0; i < _size; i++) {
        if (v == _arr[i]) {
            return i;
        }
    }
    return ELEMENT_NOT_FOUND;
}

template <class T>
bool ArrayList<T>::contains(T v) const{
    return indexOf(v) != ELEMENT_NOT_FOUND;
}


template <class T>
T ArrayList<T>::remove(int idx){
    rangeCheck(idx);
    T old = _arr[idx];
    int i = idx;
    int last = _size - 1;
    while (i < last) {
        _arr[i] = _arr[i + 1];
        i++;
    }
    _arr[--_size] = INIT_VALUE;
    
    optimize();
    return old;
}

template <class T>
void ArrayList<T>::clear(){
    delete []_arr;
    _arr = new T[_capacity = DEFAULT_CAPACITY]{};
    _size = 0;
}

template <class T>
void ArrayList<T>::ensureCapacity(int size){
    if (_capacity > size) return;

    _capacity = _capacity + (_capacity >> 1);
    T *newArr = new T[_capacity]{};
    for(int i = 0; i < _size; i++){
        newArr[i] = _arr[i];
    }
    delete [] _arr;
    _arr = newArr;
}

template<class T>
void ArrayList<T>::optimize(){
    int half = _capacity >> 1;
    if (_size >= half || _capacity <= DEFAULT_CAPACITY) return;
    
    _capacity = half < DEFAULT_CAPACITY ? DEFAULT_CAPACITY : half;
    T *newArr = new T[_capacity];
    for(int i = 0; i < _size; i++){
        newArr[i] = _arr[i];
    }
    delete [] _arr;
    _arr = newArr;
}

template <class T>
void ArrayList<T>::rangeCheck(int idx) const{
    if (idx < 0 || idx >= _size) {
        outBounds(idx);
    }
}

template <class T>
void ArrayList<T>::rangeCheckForAdd(int idx) const{
    if (idx < 0 || idx > _size) {
        outBounds(idx);
    }
}

template <class T>
void ArrayList<T>::outBounds(int idx) const{
    string s = "\"Index ";
    s.append(to_string(idx));
    s.append(" is out of bounds\". Exception:\n");
    cout << s;
    throw s;
}

template<class T>
ostream & operator<< (ostream &os, const ArrayList<T> &list){
    os << "size = " << list._size <<"/" << list._capacity << ", [";
    
    int size = list._size;
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            os << ", ";
        }
        os << list.valueOf(i);

    }
    os << "]";
    return os;
}


#endif /* ArrayList_hpp */
