//
//  CircleDeque.hpp
//  Queue
//
//  Created by berning on 2015/4/17.
//

#ifndef CircleDeque_hpp
#define CircleDeque_hpp

#include <iostream>
using namespace std;


template<class T>
class CircleDeque;

template<class T>
ostream & operator << (ostream &os, const CircleDeque<T> &deq);

template<class T>
class CircleDeque{
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
    CircleDeque();
    CircleDeque(int capacity);
    ~CircleDeque();
    
    void enQueueRear(T v);
    T    deQueueFront();
    void enQueueFront(T v);
    T    deQueueRear();
    
    T    front()const;
    T    rear()const;

    int  size()const;
    bool isEmpty()const;
    void clear();

    friend ostream& operator<< <>(ostream &os, const CircleDeque<T> &deq);
};

template<class T>
const int CircleDeque<T>::DEFAULT_CAPACITY = 10;

template<class T>
CircleDeque<T>::CircleDeque(int capacity){
    _capacity = capacity > DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY;
    _arr = new T[_capacity]();
    _size = 0;
    _front = 0;
    INIT_VALUE = _arr[0];
}

template<class T>
CircleDeque<T>::CircleDeque() : CircleDeque(DEFAULT_CAPACITY){}

template<class T>
CircleDeque<T>::~CircleDeque(){
    delete []_arr;
}

template<class T>
void CircleDeque<T>::enQueueRear(T v){
    ensureCapacity();
    _arr[index(_size)] = v;
    _size++;
}

template<class T>
T CircleDeque<T>::deQueueFront(){
    T v = _arr[_front];
    _arr[_front] = INIT_VALUE;
    _front = index(1); //_front++
    _size--;
    optimize();
    return v;
}

template<class T>
void CircleDeque<T>::enQueueFront(T v){
    ensureCapacity();
    
    _front = index(-1);
    _arr[_front] = v;
    _size++;
}

template<class T>
T CircleDeque<T>::deQueueRear(){
    int rear = index(_size - 1);
    T v = _arr[rear];
    _arr[rear] = INIT_VALUE;
    _size--;
    optimize();
    return v;
}


template<class T>
T CircleDeque<T>::front() const{
    return _arr[_front];
}

template<class T>
T CircleDeque<T>::rear() const{
    return _arr[index(_size - 1)];
}


template<class T>
int CircleDeque<T>::size() const{
    return _size;
}

template<class T>
bool CircleDeque<T>::isEmpty() const{
    return _size == 0;
}

template<class T>
void CircleDeque<T>::clear(){
    delete []_arr;
    _arr = new T[_capacity = DEFAULT_CAPACITY]();
    _size = 0;
    _front = 0;
}

template<class T>
int CircleDeque<T>::index(int idx) const{
    idx += _front;
    if (idx < 0) {
        return idx + _capacity;
    }else{
        return idx - (idx < _capacity ? 0 : _capacity);
    }
}

template<class T>
void CircleDeque<T>::ensureCapacity(){
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
void CircleDeque<T>::optimize(){
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
ostream& operator<< (ostream &os, const CircleDeque<T> &deq){
    
    os << "size = " << deq.size() << ", ";
    string isEmpty = deq.isEmpty() ? "YES" : "NO";
    os << "isEmpty = " << isEmpty << ", ";
    if(deq.size())
        os << "front = " << deq.front() << ", rear = " << deq.rear();
    else
        os << "front = NULL, rear = NULL";
    
    os << ", [";
    for (int i = 0; i < deq.size(); i++) {
        if (i > 0) {
            os << ", ";
        }
        os << deq._arr[deq.index(i)];
    }
    os << "]";
    return os;
}

#endif /* CircleDeque_hpp */
