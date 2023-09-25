//
//  Deque.hpp
//  Deque
//
//  Created by berning on 2015/4/17.
//

#ifndef Deque_hpp
#define Deque_hpp

#include <iostream>
using namespace std;

#include "LinkList.hpp"

template<class T>
class Deque;

template<class T>
ostream & operator << (ostream &os, const Deque<T> &deq);

template<class T>
class Deque{
    LinkList<T> list;
    
public:
    void enQueueRear(T v);
    T    deQueueFront();
    void enQueueFront(T v);
    T    deQueueRear();
    
    T    front()const;
    T    rear()const;

    int  size()const;
    bool isEmpty()const;
    void clear();
    
    friend ostream& operator<< <>(ostream &os, const Deque<T> &deq);
};

template<class T>
void Deque<T>::enQueueRear(T v){
    list.add(v);
}

template<class T>
T Deque<T>::deQueueFront(){
    return list.remove(0);
}

template<class T>
void Deque<T>::enQueueFront(T v){
    list.insert(v, 0);
}

template<class T>
T Deque<T>::deQueueRear(){
    return list.remove(list.size() - 1);
}


template<class T>
T Deque<T>::front() const{
    return list.valueOf(0);
}

template<class T>
T Deque<T>::rear() const{
    return list.valueOf(list.size() - 1);
}


template<class T>
int Deque<T>::size() const{
    return list.size();
}

template<class T>
bool Deque<T>::isEmpty() const{
    return list.isEmpty();
}

template<class T>
void Deque<T>::clear(){
    list.clear();
}

template<class T>
ostream& operator<< (ostream &os, const Deque<T> &deq){
    
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
        os << deq.list.valueOf(i);
    }
    os << "]";
    return os;
}




#endif /* Deque_hpp */
