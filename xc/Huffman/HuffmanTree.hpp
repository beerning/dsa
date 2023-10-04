//
//  HuffmanTree.hpp
//  Huffman
//
//  Created by berning on 2015/7/20.
//

#ifndef HuffmanTree_hpp
#define HuffmanTree_hpp

#include "BinaryHeap.hpp"
#include <unordered_map>
#include <queue>
#include <fstream>
#include <string>

class HuffmanNode{
public:
    int _idx;
    wchar_t _c;
    int _weight;
    string _code;
    HuffmanNode *_parent;
    HuffmanNode *_left;
    HuffmanNode *_right;
    
    HuffmanNode(wchar_t c, int weight) : HuffmanNode(-1, c, weight, "", NULL, NULL, NULL) {}
    HuffmanNode(int idx, wchar_t c, int weight, string code, HuffmanNode *parent, HuffmanNode *left, HuffmanNode *right){
        _idx = idx;
        _c = c;
        _weight = weight;
        _code = code;
        _parent = parent;
        _left = left;
        _right = right;
    }
    
    bool isLeaf() const{ return _left == NULL && _right == NULL;}
    bool isLeft() const{ return _parent && this == _parent->_left;}
    bool isRight() const{ return _parent && this == _parent->_right;}
};

using Node = HuffmanNode *;
using Hmap = unordered_map<wchar_t, Node>;
using Smap = unordered_map<string, wchar_t>;
using Array = vector<Node>;
using BHeap = BinaryHeap<Node>;

class HuffmanTree{
    string _s;
    string _code;
    Node _root;
    Hmap _map;
    Array _leaves;
    
    string getText(string s) const;
    Array statisChar(string s);
    void treeify(string s);
    void minK(Array &array, Node &n1, Node &n2, int k);
    void remove(Array &array, Node n);
public:
    HuffmanTree();
    HuffmanTree(string s);
    
    void encode(string s);
    string decode(string s);
    string code();
    
    // print weight && code
    void printWeight();     //weight info
    void printCodeLevel();  //code by level
    void printCodeOrder();  //code by order
};

#pragma mark - Public
HuffmanTree::HuffmanTree() : HuffmanTree("") {}
HuffmanTree::HuffmanTree(string s) : _s(s), _code(""), _root(NULL){
    if (s.length() == 0) return;
   encode(s);
}

void HuffmanTree::encode(string s){
    if (_code != "") {
        _code = "";
        _map.clear();
        _leaves.clear();
    }
    
    _s = s = getText(s);
    treeify(s);
    
    queue<Node> q;
    q.push(_root);
    while (!q.empty()){
        Node n = q.front();
        q.pop();
        if (n->_left) q.push(n->_left);
        if (n->_right) q.push(n->_right);
        
        if (n->isLeaf()){
            string code;
            Node node = n;
            while (node->_parent){
                code.insert(0, node->isLeft() ? "0" : "1");
                node = node->_parent;
            }
            n->_code = code;
            _leaves.push_back(n);
            _map[n->_c] = n;
        }
    }
    size_t len = s.length();
    for (int i = 0; i < len; i++){
        wchar_t c = s[i];
        _code += _map[c]->_code;
    }
}

string HuffmanTree::decode(string s){
    Smap map;
    for (Hmap::iterator it = _map.begin(); it != _map.end(); ++it){
        Node n = it->second;
        map[n->_code] = n->_c;
    }
    
    string decode;
    size_t len = _code.length();
    for (int i = 0; i < len;){
        int sublen = 1;
        bool matching = true;
        Smap::iterator it;
        while (matching) {
            string k = _code.substr(i, sublen);
            it = map.find(k);
            if (it == map.end()) sublen++;
            else matching = false;
        }
        decode += it->second;
        i += sublen;
    }
    return decode;
}

string HuffmanTree::code(){
    return _code;
}

void HuffmanTree::printWeight(){
    if (_s.length() == 0) return;
    Array array = statisChar(_s);
    cout << "---weight---" << endl;
    for (Node n : array)
        cout  << n->_idx << " : " << n->_c << " => " << n->_weight << endl;
}

void HuffmanTree::printCodeOrder(){
    if (_s.length() == 0) return;
    cout << "--code_order--" << endl;
    for (Hmap::iterator it = _map.begin(); it != _map.end(); ++it){
        Node n = it->second;
        cout << n->_c << " => " << n->_code << endl;
    }
}

void HuffmanTree::printCodeLevel(){
    if (_s.length() == 0) return;
    cout << "--code_level--" << endl;
    for (Node n : _leaves){
        cout << n->_c << " => " << n->_code << endl;
    }
}

#pragma mark - Private
string HuffmanTree::getText(string s) const{
    ifstream fin;
    fin.open(s);
    if (!fin.is_open()) {
    }else{
        string buff, str;
        while (getline(fin, buff))
            s = str += buff += "\n";
    }
    fin.close();
    return s;
}

void HuffmanTree::treeify(string s){
    Array array = statisChar(s);
    Node n1 = NULL;
    Node n2 = NULL;
    
    while (array.size() > 1){
        minK(array, n1, n2, 2);
        int idx = (int)array.size();
        int weight =  n1->_weight + n2->_weight;
        Node parent = new HuffmanNode(idx, '\0', weight, "", NULL, n1, n2);
        n1->_parent = parent;
        n2->_parent = parent;
        
        _root = parent;
        array.push_back(parent);
    }
}

Array HuffmanTree::statisChar(string s){
    Hmap map;
    Array array;
    size_t len = s.length();
    int idx = 0;
    for (int i = 0; i < len; i++){
        wchar_t c = s[i];
        if (map[c] == NULL){
            Node n = new HuffmanNode(c, 1);
            n->_idx = idx;
            map[c] = n;
            array.push_back(n);
            idx++;
        }else{
            map[c]->_weight++;
        }
    }
    return array;
}

void HuffmanTree::minK(Array &array, Node &n1, Node &n2, int k){
    BHeap heap([](Node v1, Node v2) -> int{
        return v1->_weight - v2->_weight;
    });
    size_t size = array.size();
    for (int i = 0; i < size; i++){
        Node n = array[i];
        if (heap.size() < k) heap.add(n);
        else if (n->_weight < heap.get()->_weight) heap.replace(n);
    }
    n2 = heap.get();
    heap.remove();
    n1 = heap.get();
    remove(array, n1);
    remove(array, n2);
}

void HuffmanTree::remove(Array &array, Node n){
    array.erase(array.begin() + n->_idx);
    int idx = n->_idx;
    for (int i = idx; i < array.size(); i++){
        Node n = array[i];
        n->_idx = idx;
        idx++;
    }
}

#endif /* HuffmanTree_hpp */
