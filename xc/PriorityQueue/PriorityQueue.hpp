//
//  PriorityQueue.hpp
//  PriorityQueue
//
//  Created by berning on 2015/7/20.
//

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

#include "Heap/BinaryHeap.hpp"

template<class T>
class PrioriryQueue{
    BinaryHeap<T> *_heap;
public:
    PrioriryQueue() : PrioriryQueue(NULL){}
    PrioriryQueue(int(*comparator)(T, T)) : _heap(new BinaryHeap<T>(comparator)){}
    
    int size() const;
    bool isEmpty() const;
    
    void enQueue(T v);
    T    deQueue();
    T    front() const;
    void clear();
    
    void print()const;
};

template<class T>
void PrioriryQueue<T>::print()const{
    _heap->print();
}

template<class T>
int PrioriryQueue<T>::size() const{
    return _heap->size();
}

template<class T>
bool PrioriryQueue<T>::isEmpty() const{
    return _heap->size() == 0;
}

template<class T>
void PrioriryQueue<T>::enQueue(T v){
    return _heap->add(v);
}

template<class T>
T PrioriryQueue<T>::deQueue(){
    return _heap->remove();
}

template<class T>
T PrioriryQueue<T>::front() const{
    return _heap->get();
}

template<class T>
void PrioriryQueue<T>::clear(){
    return _heap->clear();
}


#endif /* PriorityQueue_hpp */
