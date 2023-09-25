//
//  ListSet.hpp
//  Set
//
//  Created by berning on 2015/5/23.
//

#ifndef ListSet_hpp
#define ListSet_hpp
#include "Set.hpp"
#include "linkedlist/linkedList.h"

template <class T>
class ListSet : public Set<T>{
    LinkList<T> list;
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
int ListSet<T>::size() const{
    return list.size();
}

template<class T>
bool ListSet<T>::isEmpty() const{
    return list.isEmpty();
}

template<class T>
void ListSet<T>::clear(){
    list.clear();
}

template<class T>
void ListSet<T>::add(T v){
    if (list.contains(v)) return;
    list.add(v);
}

template<class T>
void ListSet<T>::remove(T v){
    if (!list.contains(v)) return;
    list.remove(list.indexOf(v));
}

template<class T>
bool ListSet<T>::contains(T v) const{
    return list.contains(v);
}

template<class T>
void ListSet<T>::traversal() const{
    int count = size();
    for (int i = 0; i < count; i++){
        cout << list.valueOf(i) << " ";
    }
    cout << endl;
}

#endif /* ListSet_hpp */
