//
//  BinaryHeap.hpp
//  Heap
//
//  Created by berning on 2015/7/14.
//

#ifndef BinaryHeap_hpp
#define BinaryHeap_hpp

#include <vector>
#include <unordered_set>
#include <functional>

template<class T>
class MiniHeap{
    static const unsigned long DEFAULT_CAPACITY = 0x10;
    int _size;
    unsigned long _length;
    T *_table;
//    int (*_comparator)(T, T);
    function<int(T, T)> _comparator;
    
    int compare(T v1, T v2);
    
    void expand(int capacity);  //expand capacity
    void siftUp(int idx);
    void siftDown(int idx);
    
    void heapify();
public:
    MiniHeap(unordered_set<T> *table, function<int(T, T)> comparator) : _comparator(comparator){
        this->_size = 0;
        if (table == NULL || table->size() == 0){
            _length = DEFAULT_CAPACITY;
            _table = new T[_length]{};
        }else{
            int size = (int)table->size();
            _length = DEFAULT_CAPACITY >= size ? DEFAULT_CAPACITY : size;
            _table = new T[_length]{};

            auto it = table->begin();
            int idx = 0;
            while (it != table->end()) {
                _table[idx++] = *it;
                ++it;
            }
            this->_size = size;
        }
        heapify();
    }
    MiniHeap() : MiniHeap(NULL, NULL) {}
    MiniHeap(unordered_set<T> *table) : MiniHeap(table, NULL) {}
    MiniHeap(int (*comparator)(T, T)) : MiniHeap(NULL, comparator) {}
    
    
    int size() const {return _size;}
    bool isEmpty() const{return _size == 0;}
    void add(T v);
    void add(unordered_set<T> *set);
    T get() const;  //top
    T remove(); //top
    T replace(T v);   //top
    void clear();
    
    void print() const;
};

template<class T>
void MiniHeap<T>::print() const{
    for (int i = 0; i < this->_size; i++){
        if (i > 0) cout << ", ";
        cout << _table[i];
    }
    cout << endl;
}

template<class T>
void MiniHeap<T>::add(T v){
    int idx = this->_size;
    expand(idx);
    _table[idx] = v;
    siftUp(idx);
    this->_size++;
}

template<class T>
void MiniHeap<T>::add(unordered_set<T> *set){
    auto it = set->begin();
    while (it != set->end()) {
        add(*it);
        ++it;
    }
}

template<class T>
T MiniHeap<T>::get() const{
    return _table[0];
}

template<class T>
T MiniHeap<T>::remove(){
    T top = _table[0];
    int lastIdx = this->_size - 1;
    _table[0] = _table[lastIdx];
    _table[lastIdx] = NULL;
    this->_size--;
    siftDown(0);
    return top;
}

template<class T>
T MiniHeap<T>::replace(T v){
    if (this->_size == 0) return NULL;
    T top = _table[0];
    _table[0] = v;
    siftDown(0);
    return top;
}


template<class T>
void MiniHeap<T>::clear(){
    delete []_table;
    _table = new T[_length = DEFAULT_CAPACITY]{};
    this->_size = 0;
}

#pragma mark - Private
template<class T>
void MiniHeap<T>::heapify(){
//    for (int i = 1; i < this->_size; i++){
//        siftUp(i);
//    }
    
    for (int i = (this->_size >> 1) - 1; i >= 0; i--){
        siftDown(i);
    }
}

template<class T>
int MiniHeap<T>::compare(T v1, T v2){
    if (_comparator) return _comparator(v1, v2);
    return v1 > v2 ? 1 : v1 < v2 ? -1 : 0;
}


template<class T>
void MiniHeap<T>::expand(int size){
    if (_length > size) return;

    _length = _length + (_length >> 1);
    T *arr = new T[_length]{};
    for(int i = 0; i < size; i++){
        arr[i] = _table[i];
    }
    delete [] _table;
    _table = arr;
}

template<class T>
void MiniHeap<T>::siftUp(int idx){
    T v = _table[idx];
    while (idx > 0){
        int pdx = (idx - 1) >> 1;
        T p = _table[pdx];
        if (compare(v, p) >= 0) break;
        _table[idx] = p;
        idx = pdx;
    }
    _table[idx] = v;
}

template<class T>
void MiniHeap<T>::siftDown(int idx){
    T v = _table[idx];
    int size = this->_size;
    int half = size >> 1;
    while (idx < half) {
        int cdx = (idx << 1) + 1;
        int rdx = cdx + 1;
        
        T child = _table[cdx];
        if (rdx < size && compare(_table[rdx], child) < 0)
            child = _table[cdx = rdx];
        
        if (compare(v, child) <= 0) break;
        _table[idx] = child;
        idx = cdx;
    }
    _table[idx] = v;
}

#endif /* BinaryHeap_hpp */

