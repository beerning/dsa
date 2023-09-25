//
//  BinaryHeap.hpp
//  Heap
//
//  Created by berning on 2015/7/14.
//

#ifndef BinaryHeap_hpp
#define BinaryHeap_hpp

#include "Heap.hpp"
#include <vector>
template<class T>
class BinaryHeap : public Heap<T>{
    static const unsigned long DEFAULT_CAPACITY = 0x10;
    
    unsigned long _length;
    T *_table;
    int (*_comparator)(T, T);
    
    int compare(T v1, T v2);
    
    void expand(int capacity);  //expand capacity
    void siftUp(int idx);
    void siftDown(int idx);
    
    void heapify();
public:
    BinaryHeap(vector<T> *table, int (*comparator)(T, T)) : Heap<T>(), _comparator(comparator){
        if (table == NULL || table->size() == 0){
            _length = DEFAULT_CAPACITY;
            _table = new T[_length]{};
        }else{
            int size = (int)table->size();
            _length = DEFAULT_CAPACITY >= size ? DEFAULT_CAPACITY : size;
            _table = new T[_length]{};

            for (int i = 0; i < size; i++) {
                _table[i] = table->at(i);
            }
            this->_size = size;
        }
        heapify();
    }
    BinaryHeap() : BinaryHeap(NULL, NULL) {}
    BinaryHeap(vector<T> *table) : BinaryHeap(table, NULL) {}
    BinaryHeap(int (*comparator)(T, T)) : BinaryHeap(NULL, comparator) {}
    
    
    void add(T v) override;
    T get() const override;  //top
    T remove() override; //top
    T replace(T v) override;   //top
    void clear() override;
    
    void print() const;
};

template<class T>
void BinaryHeap<T>::print() const{
    for (int i = 0; i < this->_size; i++){
        if (i > 0) cout << ", ";
        cout << _table[i];
    }
    cout << endl;
}

template<class T>
void BinaryHeap<T>::add(T v){
    int idx = this->_size;
    expand(idx);
    _table[idx] = v;
    siftUp(idx);
    this->_size++;
}

template<class T>
T BinaryHeap<T>::get() const{
    return _table[0];
}

template<class T>
T BinaryHeap<T>::remove(){
    T top = _table[0];
    int lastIdx = this->_size - 1;
    _table[0] = _table[lastIdx];
    _table[lastIdx] = NULL;
    this->_size--;
    siftDown(0);
    return top;
}

template<class T>
T BinaryHeap<T>::replace(T v){
    if (this->_size == 0) return NULL;
    T top = _table[0];
    _table[0] = v;
    siftDown(0);
    return top;
}

template<class T>
void BinaryHeap<T>::clear(){
    delete []_table;
    _table = new T[_length = DEFAULT_CAPACITY]{};
    this->_size = 0;
}

#pragma mark - Private
template<class T>
void BinaryHeap<T>::heapify(){
//    for (int i = 1; i < this->_size; i++){
//        siftUp(i);
//    }
    
    for (int i = (this->_size >> 1) - 1; i >= 0; i--){
        siftDown(i);
    }
}

template<class T>
int BinaryHeap<T>::compare(T v1, T v2){
    if (_comparator) return _comparator(v1, v2);
    return v1 > v2 ? 1 : v1 < v2 ? -1 : 0;
}


template<class T>
void BinaryHeap<T>::expand(int size){
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
void BinaryHeap<T>::siftUp(int idx){
    T v = _table[idx];
    while (idx > 0){
        int pdx = (idx - 1) >> 1;
        T p = _table[pdx];
        if (compare(v, p) <= 0) break;
        _table[idx] = p;
        idx = pdx;
    }
    _table[idx] = v;
}

template<class T>
void BinaryHeap<T>::siftDown(int idx){
    T v = _table[idx];
    int size = this->_size;
    int half = size >> 1;
    while (idx < half) {
        int cdx = (idx << 1) + 1;
        int rdx = cdx + 1;
    
        T child = _table[cdx];
        if (rdx < size && compare(_table[rdx], child) > 0)
            child = _table[cdx = rdx];
        
        if (compare(v, child) >= 0) break;
        _table[idx] = child;
        idx = cdx;
    }
    _table[idx] = v;
}


#endif /* BinaryHeap_hpp */
