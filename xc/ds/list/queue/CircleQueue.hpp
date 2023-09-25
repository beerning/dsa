//
//  CircleQueue.hpp
//  Queue
//
//  Created by berning on 2015/4/17.
//

#ifndef CircleQueue_hpp
#define CircleQueue_hpp

#include <iostream>
using namespace std;

template<class T>
class CircleQueue;

template<class T>
ostream & operator << (ostream &os, const CircleQueue<T> &q);

template<class T>
class CircleQueue{
    static const int DEFAULT_CAPACITY;
    int _capacity;
    int _size;
    int _front;
    T   *_arr;
    T   INIT_VALUE;
    
    void ensureCapacity();
    void optimize();
    int index(int idx) const;
public:
    CircleQueue();
    CircleQueue(int capacity);
    ~CircleQueue();
    
    void enQueue(T v);
    T    deQueue();
    T    front()const;
    
    int  size()const;
    bool isEmpty()const;
    void clear();
    
    friend ostream& operator<< <>(ostream &os, const CircleQueue<T> &q);
};

template<class T>
const int CircleQueue<T>::DEFAULT_CAPACITY = 10;

template<class T>
CircleQueue<T>::CircleQueue(int capacity){
    _capacity = capacity > DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY;
    _arr = new T[_capacity]();
    _size = 0;
    _front = 0;
    INIT_VALUE = _arr[0];
}

template<class T>
CircleQueue<T>::CircleQueue() : CircleQueue(DEFAULT_CAPACITY){}

template<class T>
CircleQueue<T>::~CircleQueue(){
    delete []_arr;
}

template<class T>
void CircleQueue<T>::enQueue(T v){
    ensureCapacity();
    _arr[index(_size)] = v;
    _size++;
}

template<class T>
T CircleQueue<T>::deQueue(){
    T v = _arr[_front];
    _arr[_front] = INIT_VALUE;
    _front = index(1); //_front++
    _size--;
    optimize();
    return v;
}

template<class T>
T CircleQueue<T>::front() const{
    return _arr[_front];
}

template<class T>
int CircleQueue<T>::size() const{
    return _size;
}

template<class T>
bool CircleQueue<T>::isEmpty() const{
    return _size == 0;
}

template<class T>
void CircleQueue<T>::clear(){
    delete []_arr;
    _arr = new T[_capacity = DEFAULT_CAPACITY]();
    _size = 0;
    _front = 0;
}

template<class T>
int CircleQueue<T>::index(int idx) const{
    idx += _front;
    return idx - (idx < _capacity ? 0 : _capacity);
}

template<class T>
void CircleQueue<T>::ensureCapacity(){
    if (_size < _capacity) return;
    int c = _capacity + (_capacity >> 1);
    T *newArr = new T[c]();
    for (int i = 0; i < _size; i++) {
        newArr[i] = _arr[index(i)];
    }
    _capacity = c;
    delete [] _arr;
    _arr = newArr;
    _front = 0;
}

template<class T>
void CircleQueue<T>::optimize(){
    int half = _capacity >> 1;
    if (_size >= half || _capacity <= DEFAULT_CAPACITY) return;
    
    int c = half < DEFAULT_CAPACITY ? DEFAULT_CAPACITY : half;
    T *newArr = new T[c];
    for(int i = 0; i < _size; i++){
        newArr[i] = _arr[index(i)];
    }
    _capacity = c;
    delete [] _arr;
    _arr = newArr;
    _front = 0;
}

template<class T>
ostream& operator<< (ostream &os, const CircleQueue<T> &q){
    
    os << "size = " << q.size() << ", ";
    string isEmpty = q.isEmpty() ? "YES" : "NO";
    os << "isEmpty = " << isEmpty << ", ";
    if(q.size())
        os << "front = " << q.front();
    else
        os << "front = NULL";
    
    os << ", [";
    for (int i = 0; i < q.size(); i++) {
        if (i > 0) {
            os << ", ";
        }
        os << q._arr[q.index(i)];
    }
    os << "]";

    return os;
}




#endif /* CircleQueue_hpp */
