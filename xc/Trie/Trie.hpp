//
//  Tire.hpp
//  Trie
//
//  Created by berning on 2015/7/22.
//

#ifndef Tire_hpp
#define Tire_hpp

#include <unordered_map>

class TrieNode;
using Node = TrieNode *;

class TrieNode{
    using Map = unordered_map<char, Node>;
public:
    char _c;
    Node _parent;
    Map _children;
    bool _isWord;
    
    TrieNode(char c, Node parent) : _c(c), _parent(parent), _isWord(false){}
};

class Trie{
    Node _root;
    int _size;
    Node node(string key) const;
public:
    
    Trie() : _root(NULL), _size(0){}
    int size() const;
    bool isEmpty() const;
    
    void add(string word);
    void remove(string word);
    bool contains(string word) const;
    void clear();
    
    bool has(string prefix) const;
    
};

int Trie::size() const{
    return _size;
}

bool Trie::isEmpty() const{
    return _size == 0;
}

void Trie::add(string word){
    if (!_root) _root = new TrieNode('\0', NULL);
    
    Node n = _root;
    size_t len = word.length();
    for (int i = 0; i < len; i++){
        char c = word[i];
        Node child = n->_children[c];
        if (!child){
            child = new TrieNode(c, n);
            n->_children[c] = child;
        }
        n = child;
    }
    if (n->_isWord) return;
    n->_isWord = true;
    _size++;
}

void Trie::remove(string word){
    Node n = node(word);
    if (!n || !n->_isWord) return;
    
    _size--;
    if (n->_children.size() != 0) {
        n->_isWord = false;
        return;
    }
    
    Node parent = NULL;
    while ((parent = n->_parent) != NULL) {
        parent->_children.erase(n->_c);
        delete n;
        if (parent->_isWord || parent->_children.size() != 0) break;
        n = parent;
    }
}

bool Trie::contains(string word) const{
    Node n = node(word);
    return n && n->_isWord;
}

void Trie::clear(){
    _root = NULL;
    _size = 0;
}

bool Trie::has(string prefix) const{
    return node(prefix) != NULL;
}

#pragma mark - Private
Node Trie::node(string key) const{
    size_t len = key.length();
    Node n = _root;
    for (int i = 0; i < len; i++){
        if (!n || n->_children.size() == 0) return NULL;;
        n = n->_children[key[i]];
    }
    return n;
}

#endif /* Tire_hpp */
