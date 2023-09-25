//
//  TreeSet.hpp
//  Set
//
//  Created by berning on 2015/5/23.
//

#ifndef TreeSet_hpp
#define TreeSet_hpp
#include <string>

#include "Set.hpp"
#include "tree/RBTree.hpp"

template <class T>
class TreeSet : public Set<T>{
    RBTree<T> tree;
public:
    int size() const override;
    bool isEmpty() const override;
    void clear() override;
    
    void add(T v) override;
    void remove(T v) override;
    bool contains(T v) const override;
    
    void traversal() const override;
};

template<class T>
int TreeSet<T>::size() const{
    return tree.size();
}

template<class T>
bool TreeSet<T>::isEmpty() const{
    return tree.isEmpty();
}

template<class T>
void TreeSet<T>::clear(){
    tree.clear();
}

template<class T>
void TreeSet<T>::add(T v){
    tree.add(v);
}

template<class T>
void TreeSet<T>::remove(T v){
    tree.remove(v);
}

template<class T>
bool TreeSet<T>::contains(T v) const{
    return tree.contains(v);
}

template<class T>
void TreeSet<T>::traversal() const{
    tree.inOrder();
}

#endif /* TreeSet_hpp */
