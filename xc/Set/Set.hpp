//
//  Set.hpp
//  Set
//
//  Created by berning on 2015/5/23.
//

#ifndef Set_hpp
#define Set_hpp

template<class T>
class Set{
protected:
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    
    virtual void add(T v) = 0;
    virtual void remove(T v) = 0;
    virtual bool contains(T v) const = 0;
    
    virtual void traversal() const = 0;
};
#endif /* Set_hpp */
