//
//  Map.hpp
//  Map
//
//  Created by berning on 2015/5/23.
//

#ifndef Map_hpp
#define Map_hpp
#include "Object/obj.h"

typedef enum{
    MapRed,
    MapBlack
} MapColor;

template<class K, class V>
class MapNode{
    MapColor _color;
public:
    K    _key;
    V    _value;
    MapNode *_parent;
    MapNode *_left;
    MapNode *_right;
    MapNode(K key, V value, MapNode *parent) : _color(MapRed), _key(key), _value(value), _parent(parent), _left(NULL), _right(NULL) {}
    void setColor(MapColor color){_color = color;}
    MapColor color() const{return _color;}

    bool isLeaf() const{ return _left == NULL && _right == NULL;}
    bool hasTwins() const{ return _left != NULL && _right != NULL;}
    bool isLeft() const{ return _parent && this == _parent->_left;}
    bool isRight() const{ return _parent && this == _parent->_right;}
    MapNode *sibling()const{
        if(isLeft()) return  _parent->_right;
        if(isRight()) return _parent->_left;
        return NULL;
    }
};

using TreeNode = MapNode<id, id> *;

template<class K, class V>
class Map{
    
public:
    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    
    virtual V put(K key, V value) = 0;
    virtual V get(K key) const = 0;
    virtual V remove(K key) = 0;
    
    virtual bool containsKey(K key) const = 0;
    virtual bool containsValue(V value) const = 0;
    virtual void traversal() const = 0;
};

#endif /* Map_hpp */
