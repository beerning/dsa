//
//  HashSet.hpp
//  Map
//
//  Created by berning on 2015/10/6.
//

#ifndef HashSet_hpp
#define HashSet_hpp

#include "map/LinkedHashMap.hpp"

class HashSet{
    LinkedHashMap map;
public:
    
    int size() const;
    bool isEmpty() const;
    void clear();
    
    void add(id v);
    void remove(id v);
    bool contains(id v) const;
    
    void traversal() const;

};

int HashSet::size() const {
    return map.size();
}

bool HashSet::isEmpty() const{
    return map.isEmpty();
}

void HashSet::clear(){
    map.clear();
}

void HashSet::add(id v) {
    map.put(v, NULL);
}

void HashSet::remove(id v){
    map.remove(v);
}

bool HashSet::contains(id v) const{
    return map.containsKey(v);
}

void HashSet::traversal()const {
    map.traversal();
}



#endif /* HashSet_hpp */
