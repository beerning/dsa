//
//  Heap.hpp
//  Heap
//
//  Created by berning on 2015/7/13.
//

#ifndef Heap_hpp
#define Heap_hpp

template<class T>
class Heap{
protected:
    int _size;
public:
    Heap() : _size(0){}
    virtual int size() const {return _size;}
    virtual bool isEmpty() const{return _size == 0;}
    
    virtual void add(T v) = 0;
    virtual T get() const = 0;  //top
    virtual T remove() = 0; //top
    virtual T replace(T v) = 0;   //top
    virtual void clear() = 0;

};

#endif /* Heap_hpp */
