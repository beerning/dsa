//
//  Queue.hpp
//  Queue
//
//  Created by berning on 2015/4/17.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
using namespace std;

#include "LinkList.hpp"

template<class T>
class Queue;

template<class T>
ostream & operator << (ostream &os, const Queue<T> &q);

template<class T>
class Queue{
    LinkList<T> list;
    
public:
    void enQueue(T v);
    T    deQueue();
    T    front()const;
    
    int  size()const;
    bool isEmpty()const;
    void clear();
    
    friend ostream& operator<< <>(ostream &os, const Queue<T> &q);
};

template<class T>
void Queue<T>::enQueue(T v){
    list.add(v);
}

template<class T>
T Queue<T>::deQueue(){
    return list.remove(0);
}

template<class T>
T Queue<T>::front() const{
    return list.valueOf(0);
}

template<class T>
int Queue<T>::size() const{
    return list.size();
}

template<class T>
bool Queue<T>::isEmpty() const{
    return list.isEmpty();
}

template<class T>
void Queue<T>::clear(){
    list.clear();
}

template<class T>
ostream& operator<< (ostream &os, const Queue<T> &q){
    
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
        os << q.list.valueOf(i);
    }
    os << "]";
    return os;
}


#endif /* Queue_hpp */
